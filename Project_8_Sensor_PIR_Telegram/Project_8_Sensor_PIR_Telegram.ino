#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//------- WiFi Settings -------
char ssid[] = "";       // WiFi
char password[] = "";  // password WiFi

#define PIR_Sensor D5
WiFiClientSecure client;
String ipAddress = "";
volatile bool PIRFlag = false;
int sensor;
//===================================
void setup() {
  Serial.begin(115200);
  pinMode(PIR_Sensor, INPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  ipAddress = ip.toString();
}
//==================================================
void sendTelegramMessage() {
  Serial.println("Kirim pesan ke Telegram");
  delay(200);
  String message = "Sensor mendeteksi objek ....";
  message.concat("\n");
  message.concat("WASPADA !!!");
  message.concat("\n");
  message.concat("IoT Starter Kit Inkubatek");
  message.concat("\n");}
  //=====================================================
  void loop() {
    sensor = digitalRead(PIR_Sensor);
    if (sensor == HIGH) {
      delay(500);
      Serial.println("Sensor PIR Aktif");
      while (sensor = digitalRead(PIR_Sensor)); //nunggu low
      sendTelegramMessage();
      delay(2000);
    }
  }
