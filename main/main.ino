/*
 * Inspired by Rui Santos, https://randomnerdtutorials.com
 * Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */

#include <CheapStepper.h>

// Turn on debug statements to the serial output
#define DEBUG 0// enables debug serial prints
#ifdef DEBUG
#define DEBUG_PRINT(x)      Serial.print (x)
#define DEBUG_PRINTLN(x)  Serial.println (x)
#else
#define DEBUG_PRINT(x) 
#define DEBUG_PRINTLN(x) 
#endif

#define TRIG_PIN 6    // Trigger
#define ECHO_PIN 7    // Echo
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

CheapStepper stepper (8,9,10,11);
bool cw = 1;  //invert this if the motor direction is opposite  
bool openFlag = 0;  //lid starts closed
bool closedFlag = 1;  //lid starts closed

void setup() {
  Serial.begin (9600);
  // I/O declaration
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  stepper.setRpm(12); 
}
 
void loop() {
  long dist = distInCm(); //calculate distance in centimeters
  DEBUG_PRINT(dist);
  DEBUG_PRINTLN(" cm");
  if(dist <= 10){
    switch (openFlag) {
      case 0:
        DEBUG_PRINT("Opening...");
        stepper.moveDegrees (cw, 90);
        openFlag = 1;
        DEBUG_PRINTLN("Opened...");
        break;
      case 1:
        DEBUG_PRINT("Closing...");
        stepper.moveDegrees (!cw, 90);
        openFlag = 0;
        DEBUG_PRINTLN("... Closed");
        break;
      default:
        DEBUG_PRINTLN("Error");
        break;
    }
  }
  delay(100);
}

long distInCm(void){
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHO_PIN, INPUT);
  long duration = pulseIn(ECHO_PIN, HIGH);
 
  // Convert the time into a distance
  long cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  return cm;
}
