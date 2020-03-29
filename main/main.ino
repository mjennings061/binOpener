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

#include <Stepper.h>

// Turn on debug statements to the serial output
#define DEBUG 1// enables debug serial prints
#ifdef DEBUG
#define DEBUG_PRINT(x)      Serial.print (x)
#define DEBUG_PRINTLN(x)  Serial.println (x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

#define TRIG_PIN 6    // Trigger
#define ECHO_PIN 7    // Echo

const int stepsPerRevolution = 200;  //change this to fit the number of steps per revolution
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); //initialize the stepper library on pins 8 through 11
int stepCount = 0;         //number of steps the motor has taken

void setup() {
  Serial.begin (9600);
  // I/O declaration
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}
 
void loop() {
  long dist = distInCm(); //calculate distance in centimeters
  Serial.print(dist);
  Serial.print(" cm\t");
  myStepper.step(1);
  Serial.print("steps: ");
  Serial.println(stepCount);
  stepCount++;
  delay(250);
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
