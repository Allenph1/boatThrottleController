// Rotary Encoder
#include "encoder.h"
// Tranciever
#include "tranciever.h"
// OLED Display
#include "display.h"
// Servo
#include "servo.h"

// Configuration
int role = 1; // Role 0 is remote, and Role 1 is base

void setup() {
  Serial.begin(115200);
  // Initialize encoder and counter.
  if (!role) {
    prepareRotaryEncoder();
    prepareDisplay();
  } else {
    prepareServo();
  }
  //Initialize Tranciever
  prepareTranciever(role);
}

void loop() {
  if (!role) {
    clearDisplay();
    displayCounterString(counterString);
    sendData(counterString);
  } else {
    getRecievedData();
    if (newRecievedData) {
      positionServo(atoi(dataReceived));
      Serial.println(dataReceived);
      newRecievedData = false;
    }
  }
}

