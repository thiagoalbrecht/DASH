#include <WiFi.h>
#include <WebSocketsServer.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <Stepper.h>

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

const char *ssid = "UThings";
const char *password = "n8WrQBszemA34Puz";

#define LED 2

#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25

#define BTN_1 0xFF6897
#define BTN_2 0xFF9867
#define BTN_3 0xFFB04F
#define BTN_4 0xFF30CF
#define BTN_AST 0xFF42BD

const uint16_t kIrLed = 33;

IRsend irsend(kIrLed); 

Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);
WebServer server(80);
HTTPClient http;
WebSocketsServer webSocket = WebSocketsServer(81);

int motorDirection = 0;

#include "website.h"
#include "functions.h"

String myIP;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  Serial.println();
  myIP = WiFi.localIP().toString();
  Serial.print("Local IP: ");
  Serial.println(myIP);  
  server.on("/", webpage);
  server.begin(); 
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  irsend.begin();

  myStepper.setSpeed(15);
  
  //Make a HTTP GET request to update the dash.onthewifi.com DNS to the current assigned device IP:
  http.begin("http://dynupdate.no-ip.com/nic/update?hostname=dash.onthewifi.com&myip=" + myIP); 
  http.setAuthorization("thiagomine", "ymj0hxm6DKP0cvy@dhz");
  int httpCode = http.GET();
  if (httpCode > 0) { //Check for the returning code
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  }
  
  else {
    Serial.println("Error on HTTP request");
  }
  http.end();
}

void loop()
{
  webSocket.loop();
  server.handleClient();
/*  
  if (ToLeft)
    myStepper.step(1);
  else if (ToRight)
    myStepper.step(-1); 
*/

 myStepper.step(motorDirection);
 
}
