#include <SPI.h>

#define CS 5

void sendCommand(byte address, byte data) {
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(data);
  digitalWrite(CS, HIGH);
}

void clearDisplay() {
  for (int i = 1; i <= 8; i++) {
    sendCommand(i, 0x00);
  }
}

void setup() {
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);

  SPI.begin();  // Default ESP32 VSPI pins

  sendCommand(0x0F, 0x00);  // Display test OFF
  sendCommand(0x0C, 0x01);  // Shutdown OFF (normal mode)
  sendCommand(0x0B, 0x07);  // Scan limit = 8 digits
  sendCommand(0x0A, 0x08);  // Intensity
  sendCommand(0x09, 0x00);  // No decode for matrix

  clearDisplay();
}

void loop() {
  for (int row = 1; row <= 8; row++) {
    clearDisplay();
    sendCommand(row, 0xFF);
    delay(300);
  }
}
