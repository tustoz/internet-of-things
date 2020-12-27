/*************************************
 * Program : Tes Koneksi WiFi NodeMCU V3
 * Input : -
 * Output : Serial Monitor
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/

#include <ESP8266WiFi.h> 
const char* ssid = "FirnasAbe"; //nama Wifi sesuaikan dengan WiFi anda
const char* password = ""; //password WiFi sesuaikan dengan WiFi anda
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(2000); 
  // Connect to WiFi network
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
 
void loop() {  
}
 
