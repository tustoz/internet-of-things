#include <ESP8266WiFi.h> 
const char* ssid = "";
const char* password = "";

#define buzzer D1
#define LED1 D5
#define LED2 D6
#define LED3 D7 
#define LED4 D8


WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
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
 
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}
 
void loop() { 
  WiFiClient client = server.available();
  if (!client) {
    return;
  } 
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  } 
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/BlinkLEDon") > 0)  {
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  delay(100);
  digitalWrite(LED2, HIGH);
  delay(105);
  digitalWrite(LED2, LOW);
  delay(105);
  digitalWrite(LED3, HIGH);
  delay(110);
  digitalWrite(LED3, LOW);
  delay(110);
  digitalWrite(LED4, HIGH);
  delay(115);
  digitalWrite(LED4, LOW);
  delay(115);
  digitalWrite(LED3, HIGH);
  delay(110);
  digitalWrite(LED3, LOW);
  delay(110);
  digitalWrite(LED2, HIGH);
  delay(105);
  digitalWrite(LED2, LOW);
  delay(105);
  }
  if (request.indexOf("/BlinkLEDoff") > 0)  {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  }
  if (request.indexOf("/buzzeron") > 0)  {
    tone(buzzer, 1000);
    delay(1000);
  }
  if (request.indexOf("/buzzeroff") >0)  {
    noTone(buzzer);
    delay(1000);
  }
  
  if (request.indexOf("/led1on") > 0)  {
    digitalWrite(LED1, HIGH);
   
  }
  if (request.indexOf("/led1off") >0)  {
    digitalWrite(LED1, LOW);   
  }
   if (request.indexOf("/led2on") > 0)  {
    digitalWrite(LED2, HIGH);   
  }
  if (request.indexOf("/led2off") >0)  {
    digitalWrite(LED2, LOW);   
  }
  
  if (request.indexOf("/led1on") > 0)  {
    digitalWrite(LED3, HIGH);
   
  }
  if (request.indexOf("/led1off") >0)  {
    digitalWrite(LED3, LOW);   
  }
   if (request.indexOf("/led2on") > 0)  {
    digitalWrite(LED4, HIGH);   
  }
  if (request.indexOf("/led2off") >0)  {
    digitalWrite(LED4, LOW);   
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">"); 
  client.println("<hr/><hr>");
  client.println("<h4><center> IoT Starter Kit : Kontrol 4 LED  </center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 1");
  client.println("<a href=\"/led1on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led1off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 2");
  client.println("<a href=\"/led2on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led2off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 3");
  client.println("<a href=\"/led3on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led3off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 4");
  client.println("<a href=\"/led4on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led4off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>"); 
  client.println("Buzzer");
  client.println("<a href=\"/buzzeron\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/buzzeroff\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>"); 
  client.println("<table border=\"5\">");
  client.println("<tr>");
  //=====================
  if (digitalRead(LED1))
         { 
           client.print("<td>LED 1 = ON</td>");        
         }
  else
          {
            client.print("<td>LED 1 = OFF</td>");
          }     
  client.println("<br/>");
  //======================           
  if (digitalRead(LED2))
          { 
           client.print("<td>LED 2 = ON</td>");
          }
  else
          {
            client.print("<td>LED 2 = OFF</td>");
          }
  client.println("</br>");
  //=======================
  if (digitalRead(LED3))
         { 
           client.print("<td>LED 3 = ON</td>");        
         }
  else
          {
            client.print("<td>LED 3 = OFF</td>");
          }     
  client.println("<br />");
  //======================
  if (digitalRead(LED4))
         { 
           client.print("<td>LED 4 = ON</td>");        
         }
  else
          {
            client.print("<td>LED 4 = OFF</td>");
          }     
  client.println("<br/>");
  //======================
  if (digitalRead(buzzer))
         { 
           client.print("<td>buzzer = ON</td>");        
         }
  else
          {
            client.print("<td>buzzer = OFF</td>");
          }     
  client.println("<tr/>");
  //======================
  client.println("<tr>"); 
  client.println("</table>");
  client.println("</center>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println(""); 
}
