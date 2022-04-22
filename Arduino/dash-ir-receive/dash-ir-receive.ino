/*
 * List of button values:
 * 1: 0xFF6897
 * 2: 0xFF9867
 * 3: 0xFFB04F
 * 4: 0xFF30CF
 * 
 * Copy and paste the respective value to the THIS_SERVO_COMMAND_1/2 constant
 */

#include <IRLibDecodeBase.h>  
#include <IRLib_P01_NEC.h>   
#include <IRLib_HashRaw.h>  
#include <IRLibCombo.h> 
#include <Servo.h>
#include <FastLED.h>


// Adjust the servo here:
#define THIS_SERVO_COMMAND_1 0xFF6897
#define THIS_SERVO_COMMAND_2 0xFF9867
#define STATUS_LED 0xFF42BD
const int servoOffset = 2; // Position offset. Adjust this so that the servo horn is parallel to the body/mounting tabs
const int servoMovementAmount = 13; // Amount of rotation of the servo
const int rotationDirection = 1; // 1 = counterclockwise, -1 = clockwise
const int returnDelay = servoMovementAmount * 15; // Automatically set the delay based on amount of rotation (15ms per degree)

const int servoOffset2 = 2; // Position offset. Adjust this so that the servo horn is parallel to the body/mounting tabs
const int servoMovementAmount2 = 13; // Amount of rotation of the servo
const int rotationDirection2 = 1; // 1 = counterclockwise, -1 = clockwise
const int returnDelay2 = servoMovementAmount2 * 15; // Automatically set the delay based on amount of rotation (15ms per degree)

unsigned long receivedMillis = 0;



IRdecode myDecoder;

// Include a receiver either this or IRLibRecvPCI or IRLibRecvLoop
#include <IRLibRecv.h> 
IRrecv myReceiver(2);    //create a receiver on pin number 2

Servo servoNode1;
Servo servoNode2;

CRGB led1[1];
CRGB led2[1];

void setup() {
  Serial.begin(9600);
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
  servoNode1.attach(9);
  servoNode1.write(50 + servoOffset);
  servoNode2.attach(10);
  servoNode2.write(50 + servoOffset);
  FastLED.addLeds<NEOPIXEL, 5>(led1, 1);
  FastLED.addLeds<NEOPIXEL, 6>(led2, 1);
}

void loop() {
  unsigned long currentMillis = millis();
  if(myReceiver.getResults()) {
    myDecoder.decode();
    //myDecoder.dumpResults(false);
    Serial.println(myDecoder.value, HEX);
    switch(myDecoder.value){
      case THIS_SERVO_COMMAND_1:
       Serial.println("Command 1 received");
       led1[0] = CRGB::Green;
       
       FastLED.show();
       servoNode1.write(50 + (servoMovementAmount * rotationDirection) + servoOffset);
       delay(returnDelay);
       servoNode1.write(50 + servoOffset);
       led1[0] = CRGB::Black;
       FastLED.show();
      break;
      case THIS_SERVO_COMMAND_2:
       led2[0] = CRGB::Green;
       FastLED.show();
       Serial.println("Command 2 received");
       servoNode2.write(50 + (servoMovementAmount2 * rotationDirection2) + servoOffset2);
       delay(returnDelay2);
       servoNode2.write(50 + servoOffset2);
       led2[0] = CRGB::Black;
       FastLED.show();
      break;
      case STATUS_LED:
       led1[0] = CRGB::DarkCyan;
       led2[0] = CRGB::DarkCyan;
       FastLED.show();
       delay(350);
       led1[0] = CRGB::Black;
       led2[0] = CRGB::Black;
       FastLED.show();
      }
    myReceiver.enableIRIn(); 
  }

}
