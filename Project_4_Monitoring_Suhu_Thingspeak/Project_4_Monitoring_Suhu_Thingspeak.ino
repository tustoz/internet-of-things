int outputpin= A0;
int analogValue;
float millivolts,celsius;
#include <ESP8266WiFi.h>

// ganti dengan API Keys anda di Thingspeak
String apiKey = "";
const char* ssid = "";
const char* password = "";
const char* server = "api.thingspeak.com";
WiFiClient client;
//========================
void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

//==========================================
void loop() {
  analogValue = analogRead(outputpin);
  millivolts = (analogValue/1024.0) * 3300; 
  celsius = millivolts/10;
  if (client.connect(server,80)) { 
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(celsius);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(celsius);
    Serial.print(" Celcius ");
    Serial.println(" send to Thingspeak");
  }
  client.stop();
  Serial.println("Waiting…");
  delay(20000); //minimal nunggu 15 detik update Thingspeak
}
