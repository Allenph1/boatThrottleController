#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

void prepareDisplay() {
  u8g2.begin();
}

char counterDisplayString[32];

void displayCounterString(char counter[3]) {
  Serial.println(counter);
  strcat(counterDisplayString, "T: ");
  strcat(counterDisplayString, counter);
  strcat(counterDisplayString, "%");
  u8g2.setFont(u8g2_font_logisoso28_tr);
  u8g2.drawStr(4, 29, counterDisplayString);
  u8g2.sendBuffer();
  counterDisplayString[0] = '\0';
}

void clearDisplay() {
  u8g2.clearBuffer();
}


