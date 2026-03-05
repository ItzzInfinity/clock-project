// ================V2==================
#include <WiFi.h>
#include <SPI.h>
#include <time.h>

#define CS 5

// ======== WIFI CREDENTIALS =========
const char* ssid     = "Itzz_Infinity";
const char* password = "123456789";

// ======== NTP SETTINGS =========
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;     // IST = 5.5 * 3600
const int   daylightOffset_sec = 0;

// Segment pattern: DP A B C D E F G
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

void setupMAX7219() {
  sendCommand(0x0F, 0x00);  // Display test OFF
  sendCommand(0x0C, 0x01);  // Shutdown OFF
  sendCommand(0x0B, 0x03);  // Scan limit = 4 digits
  sendCommand(0x0A, 0x08);  // Intensity
  sendCommand(0x09, 0x00);  // Decode OFF (RAW)
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
void displayTime(int hour, int minute, bool blinkState) {

  int h1 = hour / 10;
  int h2 = hour % 10;
  int m1 = minute / 10;
  int m2 = minute % 10;

  byte seg_h1 = Digits[h1];
  byte seg_h2 = Digits[h2];
  byte seg_m1 = Digits[m1];
  byte seg_m2 = Digits[m2];

  // Blink DP on digit 2 (between HH:MM)
  if (blinkState)
    seg_h2 |= 0x80;   // Turn DP ON
  else
    seg_h2 &= 0x7F;   // Turn DP OFF

  sendCommand(4, seg_h1);
  sendCommand(3, seg_h2);
  sendCommand(2, seg_m1);
  sendCommand(1, seg_m2);
}

void setup() {
  Serial.begin(115200);

  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  SPI.begin();
  setupMAX7219();

  connectWiFi();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {

  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to get time");
    delay(1000);
    return;
  }

  int hour   = timeinfo.tm_hour;
  int minute = timeinfo.tm_min;
  int second = timeinfo.tm_sec;

  bool blinkState = (second % 2 == 0);

  Serial.print("Second: ");
  Serial.print(second);
  Serial.print("  BlinkState: ");
  Serial.println(blinkState);

  displayTime(hour, minute, blinkState);

  delay(1000);   // IMPORTANT: make it 1000ms for clean observation
}
