#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <SimpleTimer.h>
#define DHTPIN D5 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

SimpleTimer timer;

float humi, temp; 
// Ganti dengan kode token anda
char auth[] = ""; 
// Ganti dengan WiFi dan Password anda
char ssid[] = "";
char pass[] = "";

void setup()
{
  Serial.begin(115200); 
  delay(10);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000, sendData);
}

void sendData()
{  
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  Blynk.virtualWrite(10, temp);//virtual input V10 di Blynk (suhu)
  Blynk.virtualWrite(11, humi);//virtual input V11 di Blynk (kelembaban)
}

void loop()
{
  Blynk.run();
  timer.run();
}
