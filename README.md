# NTP Based 7-Segment Clock (ESP + MAX7219)

## Overview

This project creates a **WiFi synchronized digital clock** using an **ESP32** and a **7-segment display driven by MAX7219**.
The ESP connects to the internet, fetches the **current time from an NTP server**, and continuously updates the display.

The goal of the project is to build a **simple, modular clock firmware** where hardware configuration and functionality can be easily modified.

---

## How It Works

1. ESP32 connects to WiFi.
2. It requests the current time from an **NTP server**.
3. The received time is converted to local time.
4. Time is sent via **SPI** to the **MAX7219 display driver**.
5. MAX7219 controls the **7-segment display** and updates the digits every second.

---

## Hardware Required

* ESP32
* MAX7219 7-Segment Display Module
* 4-Digit or 8-Digit 7-Segment Display (Common Anode)
* 5V Power Supply
* Connecting wires

Optional (future improvements):

* RTC module for backup time
* Temperature/Humidity sensor
* Enclosure

---

## Software / Tools

* Arduino IDE or PlatformIO
* ESP32 Board Package
* Required Libraries:

  * WiFi
  * NTPClient
  * MAX7219 display library (e.g. LedControl)

---

## Future Improvements

* RTC backup time
* Brightness auto control
* Temperature and humidity display
* Modular firmware structure
* Multiple display layouts

---

## Project Status

Work in progress. Hardware testing and firmware improvements are ongoing.

