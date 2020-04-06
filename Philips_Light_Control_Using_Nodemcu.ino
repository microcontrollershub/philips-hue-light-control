// Include necessary header files
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// WiFi Details
// You should change following three lines according to your settings
const char* ssid = "Subscribe To";  
const char* password = "Microcontrollershub";
const char* endpoint = "http://192.168.0.3/api/MhK4WdkWiu5aqY3JtLGyC1Sai78vuNh3TqyZQvSS/lights/1/state";

void setup(void) 
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)           // Connect with the wifi
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
}
void loop()
{ 
   TrunOffLight();
   delay(2000);
   TrunOnLight();
   delay(2000);
   for (int i = 0; i<10; i++)
   {
     ChangeColor(random(0,65535));                  // Generate the random number and change the colour accordingly
     delay(1000);
   }   
}
void TrunOnLight()
{
  sendHTTPMessage("{\"on\":true}");                 // HTTP message to turn the light on
}
void TrunOffLight()
{ 
  sendHTTPMessage("{\"on\":false}");               // HTTP message to turn the light off
}
void ChangeColor (unsigned int colorCode)
{
  String message = "{\"on\":true, \"sat\":254, \"bri\":150,\"hue\":";
  message = message + String(colorCode) + "}";
  sendHTTPMessage(message);
}
void sendHTTPMessage(String message)                // Function to do HTTP PUT request
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(endpoint);
    http.addHeader("Content-Type", "text/plain;charset=UTF-8");
    http.PUT(message);
    http.end();
  } 
  else
  {
    Serial.println("Request not sent: Not connected");
  }
}
