// Represents throttle percentage.
int counter = 0;
char counterString[3] = "0";

//Encoder Variables
const int encoderPinA = 2;
const int encoderPinB = 3;
// Push button pin.
const int pushButtonPinRead = 4;
const int pushButtonPinReadBit = bit (PCINT20);
const int pushButtonPinReadBitRange = bit (PCIF2);
// Encoder state definitions.
const int states[4][2] = {
  {0, 1},
  {0, 0},
  {1, 0},
  {1, 1}
};
int currentEncoderState[2] = {1, 1};
int expectedClockwiseState = 0;
int expectedCounterClockwiseState = 2;

// Refresh counter string. (For when counter int changes)
void refreshCounterString() {
  sprintf(counterString, "%d", counter);
}

// Set counter to 0.
void zeroCounter() {
  counter = 0;
  refreshCounterString();
}

// Read the rotary encoder and assess if we should change the counter.
void refreshCounter() {
  currentEncoderState[0] = digitalRead(encoderPinA);
  currentEncoderState[1] = digitalRead(encoderPinB);
  if (currentEncoderState[0] == states[expectedClockwiseState][0] && currentEncoderState[1] == states[expectedClockwiseState][1]) {
    if (expectedClockwiseState == 3) {
      expectedClockwiseState = 0;
    } else {
      expectedClockwiseState++;
    }
    if (counter != 100) {
      counter++;
    }
  } else if (currentEncoderState[0] == states[expectedCounterClockwiseState][0] && currentEncoderState[1] == states[expectedCounterClockwiseState][1]) {
    if (expectedCounterClockwiseState == 0) {
      expectedCounterClockwiseState = 3;
    } else {
      expectedCounterClockwiseState--;
    }
    if (counter != 0) {
      counter--;
    }
  }
  refreshCounterString();
}

// Push button change callback.
void refreshPushButton() {
  if (digitalRead(pushButtonPinRead) == LOW) {
    zeroCounter();
  }
}

// Set up pin states for rotary encoder.
void prepareRotaryEncoder() {
  // Set register to allow pin change interrupts on push button pin.
  PCMSK2 |= pushButtonPinReadBit;
  PCIFR  |= pushButtonPinReadBitRange;
  PCICR  |= pushButtonPinReadBitRange;
  // Setup turn sensing pins.
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), refreshCounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), refreshCounter, CHANGE);
  // Setup push button pins.
  pinMode(pushButtonPinRead, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pushButtonPinRead), refreshPushButton, CHANGE);
}


