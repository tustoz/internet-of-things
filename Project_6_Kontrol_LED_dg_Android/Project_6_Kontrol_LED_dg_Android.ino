#include <ESP8266WiFi.h>
#define ON 1
#define OFF 0

const char* ssid = ""; // Ganti dengan nama jaringan wifi anda
const char* password = ""; // Ganti dengan password wifi anda

#define LED1  D5 //D5 ESP Board 
#define LED2  D6 //D7 ESP Board
#define LED3  D7 //D6 ESP Board
#define LED4  D8 //D5 ESP Board 

bool value1 = LOW;
bool value2 = LOW;
bool value3 = LOW;
bool value4 = LOW;

WiFiServer server(80); // Nomor PORT WiFi
//====================================
void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

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

  server.begin();
  Serial.println("Server started");

  delay (2000);
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  delay (2000);
}
//=====================================
void loop() {

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  delay(1000);
  client.flush();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<fieldset>");
  client.println("<font color = redq>");
  client.print("Control 4 LED Via Wifi");
  client.println("</font>");
  client.println("</fieldset>");
  client.println("<br><br>");

  // Kontrol LED 1
  if (request.indexOf("/status1=1") != -1)  {
    digitalWrite(LED1, ON);
    value1 = HIGH;
  }
  if (request.indexOf("/status1=0") != -1)  {
    digitalWrite(LED1, OFF);
    value1 = LOW;
  }
  if (value1 == HIGH) {
    client.println("<br><br>");
    client.print("status1=1");
  }
  if (value1 == LOW) {
    client.println("<br><br>");
    client.print("status1=0");
  }

  // Kontrol LED 2
  if (request.indexOf("/status2=1") != -1)  {
    digitalWrite(LED2, ON);
    value2 = HIGH;
  }
  if (request.indexOf("/status2=0") != -1)  {
    digitalWrite(LED2, OFF);
    value2 = LOW;
  }
  if (value2 == HIGH) {
    client.println("<br><br>");
    client.print("status2=1");
  }
  if (value2 == LOW) {
    client.println("<br><br>");
    client.print("status2=0");
  }


  // Kontrol LED 3
  if (request.indexOf("/status3=1") != -1)  {
    digitalWrite(LED3, ON);
    value3 = HIGH;
  }
  if (request.indexOf("/status3=0") != -1)  {
    digitalWrite(LED3, OFF);
    value3 = LOW;
  }
  if (value3 == HIGH) {
    client.println("<br><br>");
    client.print("status3=1");
  }
  if (value3 == LOW) {
    client.println("<br><br>");
    client.print("status3=0");
  }

  // Kontrol LED 4
  if (request.indexOf("/status4=1") != -1)  {
    digitalWrite(LED4, ON);
    value4 = HIGH;
  }
  if (request.indexOf("/status4=0") != -1)  {
    digitalWrite(LED4, OFF);
    value4 = LOW;
  }
  if (value4 == HIGH) {
    client.println("<br><br>");
    client.print("status4=1");
  }
  if (value4 == LOW) {
    client.println("<br><br>");
    client.print("status4=0");
  }
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
  delay(1000);
}
