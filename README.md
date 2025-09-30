# SmartHomeSecuritySystem
# Smart Home Security System
EEE-416 Microprocessor and Embedded System Laboratory  
Bangladesh University of Engineering and Technology (BUET)  
Section: B2 | Group: 03  

## Overview
This project is a Smart Home Security System integrating **gas and fire detection, password protection, and intruder image capture**.  
It is built using ESP32, ESP32-CAM, flame and gas sensors, keypad, solenoid lock, LCD, and IoT (Blynk + Google Drive).  

### Features
- 🔥 Fire and gas leakage detection with real-time alerts.
- 🔑 Password-protected door lock system.
- 📸 Intruder detection via ESP32-CAM (wrong password triggers camera).
- ☁️ Cloud storage of intruder images using Google Drive.
- 📱 Remote monitoring and notifications via Blynk app.

## Hardware Components
- ESP32
- ESP32-CAM
- Flame Sensor (KY-026)
- Gas Sensor (MQ-9)
- 4x4 Keypad
- LCD I2C Display
- Solenoidal Lock + Relay
- CD4047 Multivibrator + 74HC191 Counter
- Custom PCB

## Software
- Arduino IDE (ESP32, ESP32-CAM programming)
- Blynk IoT Cloud
- Google Apps Script (for Drive uploads)
- Proteus (for simulation and PCB design)

## Repository Contents
- `Firmware/ESP32_MainHub.ino` → Handles sensors, keypad, LCD, password logic, Blynk alerts.
- `Firmware/ESP32_Cam.ino` → Captures intruder image and uploads to Google Drive.
- `GoogleScript/DriveUpload.gs` → Google Apps Script for receiving and saving images.
- `Documentation/SmartHome_4-1.pdf` → Full project report.

## Usage
1. Upload **ESP32_MainHub.ino** to ESP32 using Arduino IDE.
2. Upload **ESP32_Cam.ino** to ESP32-CAM.
3. Deploy **DriveUpload.gs** in Google Apps Script linked with your Google Drive.
4. Configure Blynk template ID, WiFi credentials, and Google Script ID in code.
5. Run the system — monitor via **Blynk app** and Google Drive.

## Future Work
- Implement encryption for password storage.
- Camera trigger after multiple failed attempts (to reduce false alarms).
- Compact PCB design for easier installation.
- Full home automation integration.

## Authors
- Shadman Sobhan (1906109)  
- Fahim Ahmed (1906110)  
- Kazi Abrar Mahmud (1906112)  
- Anik Biswas (1906125)  
