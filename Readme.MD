# Fake Gmail Sign-In Page Using ESP8266

## Overview
This project uses the **ESP8266** development board to create a **fake Gmail sign-in page** that can be accessed via Wi-Fi. The ESP8266 acts as a Wi-Fi access point, hosting a web page designed to mimic a real login portal.

## Features
- Hosts a **captive portal** to redirect users to a fake Gmail sign-in page.
- Uses **ESP8266 WebServer library** to serve HTML content.
- Captures and logs entered credentials (for ethical testing purposes only).
- Can be customized for different login page designs.

## Hardware Requirements
- **ESP8266** development board (NodeMCU, Wemos D1 Mini, etc.)
- Micro USB cable for flashing the firmware
- Computer with **Arduino IDE** installed

## Software Requirements
- **Arduino IDE** with ESP8266 board package installed
- Required libraries:
  - ESP8266WiFi
  - ESP8266WebServer

## Installation & Setup
1. Install **Arduino IDE** (if not already installed).
2. Add **ESP8266 board support** via **Boards Manager** in Arduino IDE.
3. Install the required **ESP8266 libraries**.
4. Clone this repository:
5. Open the `.ino` file in Arduino IDE.
6. Select the correct **ESP8266 board** and **COM port**.
7. Compile and upload the sketch to the ESP8266.

## Usage
- After flashing, the ESP8266 will create a Wi-Fi hotspot (Named:., `Free WiFi`).
- Connect to it using any device.
- A fake login page will appear when opening a browser.
- Entered credentials will be captured and displayed in the **Serial Monitor**.

## Disclaimer
**This project is for educational and ethical hacking purposes only.** Unauthorized use of this project for malicious activities is strictly prohibited. Always obtain permission before testing on any network.

## License
This project is open-source under the **MIT License**.

---
🚀 **Created by premshah1111**
