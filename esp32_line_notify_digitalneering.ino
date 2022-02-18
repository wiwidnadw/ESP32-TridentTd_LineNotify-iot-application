
 //This is program
//to build IoT Application between ESP32 and Line Notify
// step by step are explain on YouTube channel

// YouTube channel : Digitalneering

//dont forget to subscribe channel to supporting
//download TridentTd_LineNotify libraries on Arduino's application

#include <TridentTD_LineNotify.h>
#include <WiFi.h>


#define LINE_TOKEN  "Your token"
#define potentio 34
#define led1 26
#define led2 27
#define led3 25




const char* ssid     = "Your SSID";
const char* password = "Password";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(led1, OUTPUT);      // set the LED pin mode
    pinMode(led2, OUTPUT);
    pinMode(potentio, INPUT);
    delay(10);

    // We start by connecting to a WiFi network

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
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
    LINE.setToken(LINE_TOKEN);
}

int value = 0;

void loop(){
  WiFiClient client = server.available();
  int sensorvalue = analogRead(potentio);
 
  if (client) {
   Serial.println("New Client.");
   
  while (client.connected()){
  String request = client.readStringUntil('\r');
  Serial.print(request);
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.print("Click <a href=\"/led1\">here</a> to turn the LED on pin 26 .<br>");
  client.print("Click <a href=\"/led2\">here</a> to turn the LED on pin 27 .<br>");
  
  if(request.indexOf("led1") != -1 ) {
    digitalWrite(led1, !digitalRead(led1));
  }
  if(request.indexOf("led2") != -1 ) {
    digitalWrite(led2, !digitalRead(led2));
  }
  if(request.indexOf("led3") != -1 ) {
    digitalWrite(led3, !digitalRead(led3));
  }
   
   
   
   
   
   client.print(sensorvalue);
   client.print(",");
   client.print("Led 1 = ");
   client.print(digitalRead(led1));
   client.print(",");
   client.print("Led 2 = ");
   client.println(digitalRead(led2));

      //logic condition for notify line
     if (digitalRead(led1) == 1) {
     LINE.notify("Led 1 pin 26 status on"); 
     }
     if (digitalRead(led2) == 1) {
     LINE.notify("Led 1 pin 27 status on"); 
     }
     
   break; 
    }  
  
  
   delay(1);
   client.stop();
   Serial.println("Client disconnected");
   
  }
       //logic condition for notify line
      if (sensorvalue >= 2200) {
      LINE.notify("Sensor too high value");
      
     }
Serial.println(sensorvalue);
delay(1000);
}
