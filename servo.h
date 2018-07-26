#include <Servo.h>

int maxAngle = 175;

Servo throttleServo;

void prepareServo() {
  throttleServo.attach(6);
}

void positionServo(int throttlePercentage) {
  int throttleAngle = throttlePercentage * maxAngle / 100;
  throttleServo.write(throttleAngle);
  delay(15);
}


