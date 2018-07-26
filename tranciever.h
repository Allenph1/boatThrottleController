// Tranciever Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Configuration
int channel = 124;

// Driver singleton.
RF24 radio(9,10);

// Transmit variables
char dataToSend[32];
const byte recieverAddress[5] = {'R','x','A','A','A'};

// Recieve variables
char dataReceived[32];
bool newRecievedData = false;

void prepareTranciever(int role) {
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  if(role){
    // This arduino is the base.
    radio.openReadingPipe(1, recieverAddress);
    radio.startListening();
  } else {
    // This arduino is the remote.
    radio.openWritingPipe(recieverAddress);
  }
}

void sendData(char message[32]) {
  strncpy(dataToSend, message, 32);
  bool rslt;
  rslt = radio.write( &dataToSend, sizeof(dataToSend) );
  Serial.println(message);
  Serial.println(rslt);
  return rslt;
}

void getRecievedData() {
  if ( radio.available() ) {
    radio.read(&dataReceived, sizeof(dataReceived));
    newRecievedData = true;
  }
}


