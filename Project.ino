#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "ESP8266WiFi.h"
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "internship-243816.firebaseio.com"
#define FIREBASE_AUTH "9MGTHBnLGdRxOGOoS0Ehi7ILW8uru468xqOpGtOj"
#define WIFI_SSID "Smart_Bin_Wifi"
#define WIFI_PASSWORD "bluesailroxx"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
 
char myssid[] = "Smart_Bin_WiFi";         // your network SSID (name)
char mypass[] = "blusailroxx";          // your network password
 
 
//Credentials for Google GeoLocation API...
const char* Host = "www.googleapis.com";
String thisPage = "/geolocation/v1/geolocate?key=";
 
String key = "AIzaSyCUWLaUyAjrNPFacia_nObeyFTcGZzoHdk";
 
int status = WL_IDLE_STATUS;
String jsonString = "{\n";
 
double latitude    = 0.0;
double longitude   = 0.0;
double accuracy    = 0.0;
int more_text = 1;
 
 
 
 
void setup()   {
  Serial.begin(9600);
 
 
  Serial.println("Start");
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");
  Serial.print("Connecting to ");
  Serial.println(myssid);
  WiFi.begin(myssid, mypass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".");

 //----------------------------------------
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Firebase
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

 String path = "/ESP8266_Test";

  String jsonStr = "";
 
  Serial.println("------------------------------------");
  Serial.println("Set double test...");

  for (uint8_t i = 0; i < 10; i++)
  {

    if (Firebase.setDouble(firebaseData, path + "/Double/Data" + (i + 1), ((i + 1) * 10) + 0.123456789))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.print("VALUE: ");
      if (firebaseData.dataType() == "int")
        Serial.println(firebaseData.intData());
      else if (firebaseData.dataType() == "float")
        Serial.println(firebaseData.floatData(), 5);
      else if (firebaseData.dataType() == "double")
        printf("%.9lf\n", firebaseData.doubleData());
      else if (firebaseData.dataType() == "boolean")
        Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
      else if (firebaseData.dataType() == "string")
        Serial.println(firebaseData.stringData());
      else if (firebaseData.dataType() == "json")
        Serial.println(firebaseData.jsonData());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }

  Serial.println("------------------------------------");
  Serial.println("Get double test...");

  for (uint8_t i = 0; i < 10; i++)
  {

    if (Firebase.getInt(firebaseData, path + "/Double/Data" + (i + 1)))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.print("VALUE: ");
      if (firebaseData.dataType() == "int")
        Serial.println(firebaseData.intData());
      else if (firebaseData.dataType() == "float")
        Serial.println(firebaseData.floatData(), 5);
      else if (firebaseData.dataType() == "double")
        printf("%.9lf\n", firebaseData.doubleData());
      else if (firebaseData.dataType() == "boolean")
        Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
      else if (firebaseData.dataType() == "string")
        Serial.println(firebaseData.stringData());
      else if (firebaseData.dataType() == "json")
        Serial.println(firebaseData.jsonData());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }

  Serial.println("------------------------------------");
  Serial.println("Push integer test...");

  for (uint8_t i = 0; i < 5; i++)
  {

    if (Firebase.pushInt(firebaseData, path + "/Push/Int", (i + 1)))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }

  Serial.println("------------------------------------");
  Serial.println("Push JSON test...");

  for (uint8_t i = 5; i < 10; i++)
  {

    jsonStr = "{\"Data" + String(i + 1) + "\":" + String(i + 1) + "}";

    if (Firebase.pushJSON(firebaseData, path + "/Push/Int", jsonStr))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }

  Serial.println("------------------------------------");
  Serial.println("Update test...");

  for (uint8_t i = 0; i < 5; i++)
  {

    jsonStr = "{\"Data" + String(i + 1) + "\":" + String(i + 5.5) + "}";

    if (Firebase.updateNode(firebaseData, path + "/Int", jsonStr))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      //No ETag available
      Serial.print("VALUE: ");
      if (firebaseData.dataType() == "int")
        Serial.println(firebaseData.intData());
      else if (firebaseData.dataType() == "float")
        Serial.println(firebaseData.floatData(), 5);
      else if (firebaseData.dataType() == "double")
        printf("%.9lf\n", firebaseData.doubleData());
      else if (firebaseData.dataType() == "boolean")
        Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
      else if (firebaseData.dataType() == "string")
        Serial.println(firebaseData.stringData());
      else if (firebaseData.dataType() == "json")
        Serial.println(firebaseData.jsonData());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
}
  }
}
 
 
void loop() 
{
 
  char bssid[6];
  DynamicJsonDocument<200> doc;
  Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found...");
 
    if (more_text) {
      Serial.println("{");
      Serial.println("\"homeMobileCountryCode\": 91,");   //Country code
      Serial.println("\"homeMobileNetworkCode\": 91,");   // Mobile
      Serial.println("\"radioType\": \"gsm\",");          // for gsm
      Serial.println("\"carrier\": \"Cell carrier\",");       // cell carrier
      Serial.println("\"cellTowers\": [");                // no cell tower
      Serial.println("],");
      Serial.println("\"wifiAccessPoints\": [");
     for (int i = 0; i < n; ++i)
     {
       Serial.println("{");
       Serial.print("\"macAddress\" : \"");
       Serial.print(WiFi.BSSIDstr(i));
       Serial.println("\",");
       Serial.print("\"signalStrength\": ");
       Serial.println(WiFi.RSSI(i));
       if (i < n - 1)
       {
         Serial.println("},");
       }
       else
       {
         Serial.println("}");
       }
     }
     Serial.println("]");
     Serial.println("}");
   }
   Serial.println(" ");
 }
 jsonString = "{\n";
 jsonString += "\"homeMobileCountryCode\": 234,\n"; // Country code
 jsonString += "\"homeMobileNetworkCode\": 27,\n";  // network code
 jsonString += "\"radioType\": \"gsm\",\n";         // for gsm
 jsonString += "\"carrier\": \"JIO\",\n";      // Carrier
 jsonString += "\"wifiAccessPoints\": [\n";
 for (int j = 0; j < n; ++j)
 {
   jsonString += "{\n";
   jsonString += "\"macAddress\" : \"";
   jsonString += (WiFi.BSSIDstr(j));
   jsonString += "\",\n";
   jsonString += "\"signalStrength\": ";
   jsonString += WiFi.RSSI(j);
   jsonString += "\n";
   if (j < n - 1)
   {
     jsonString += "},\n";
   }
   else
   {
     jsonString += "}\n";
   }
 }
 jsonString += ("]\n");
 jsonString += ("}\n");
 
 Serial.println("");
 
 WiFiClientSecure client;
 
 //Connect to the client and make the api call
 Serial.print("Requesting URL: ");
 Serial.println("https://" + (String)Host + thisPage + "AIzaSyCUWLaUyAjrNPFacia_nObeyFTcGZzoHdk");
 Serial.println(" ");
 if (client.connect(Host, 443)) {
   Serial.println("Connected");
   client.println("POST " + thisPage + key + " HTTP/1.1");
   client.println("Host: " + (String)Host);
   client.println("Connection: close");
   client.println("Content-Type: application/json");
   client.println("User-Agent: Arduino/1.0");
   client.print("Content-Length: ");
   client.println(jsonString.length());
   client.println();
   client.print(jsonString);
   delay(500);
 }
 
 //Read and parse all the lines of the reply from server
 while (client.available()) {
   String line = client.readStringUntil('\r');
   if (more_text) {
     Serial.print(line);
   }
   JsonObject& root = jsonBuffer.parseObject(line);
   if (root.success()) {
     latitude    = root["location"]["lat"];
     longitude   = root["location"]["lng"];
     accuracy   = root["accuracy"];
   }
 }
 
 Serial.println("closing connection");
 Serial.println();
 client.stop();
 
 Serial.print("Latitude = ");
 Serial.println(latitude, 6);
 Serial.print("Longitude = ");
 Serial.println(longitude, 6);
 Serial.print("Accuracy = ");
 Serial.println(accuracy);
 
 delay(10000);
 
 Serial.println();
 Serial.println("Restarting...");
 Serial.println();
 
 delay(2000);
 
 
}
