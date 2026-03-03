#include <SPI.h>

#define CS 5

unsigned long delaytime = 200;

// Segment pattern: DP A B C D E F G
// Matches your wiring C1->DP, C2->A ... C8->G
byte Digits[10] = {
  B01111110,  // 0
  B00110000,  // 1
  B01101101,  // 2
  B01111001,  // 3
  B00110011,  // 4
  B01011011,  // 5
  B01011111,  // 6
  B01110000,  // 7
  B01111111,  // 8
  B01111011   // 9
};

void sendCommand(byte address, byte data) {
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(data);
  digitalWrite(CS, HIGH);
}

void setup() {

  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);

  SPI.begin();   // ESP32 default VSPI

  // MAX7219 Init
  sendCommand(0x0F, 0x00);  // Display test OFF
  sendCommand(0x0C, 0x01);  // Shutdown OFF
  sendCommand(0x0B, 0x03);  // Scan limit = 4 digits
  sendCommand(0x0A, 0x08);  // Intensity
  sendCommand(0x09, 0x00);  // Decode mode OFF (RAW mode)
}

void loop() {

  for (int i = 0; i < 9999; i++) {

    int dig1 = i / 1000;
    int dig2 = (i / 100) % 10;
    int dig3 = (i / 10) % 10;
    int dig4 = i % 10;

    sendCommand(4, Digits[dig1]);  // Leftmost
    sendCommand(3, Digits[dig2]);
    sendCommand(2, Digits[dig3]);
    sendCommand(1, Digits[dig4]);  // Rightmost

    delay(delaytime);
  }
}
