SmartFarm-Monitoring-System

 Overview
An IoT-based smart farming solution that monitors soil moisture and sends automated SMS alerts to farmers. This system provides regular and on-demand moisture reports, enabling precision agriculture even in remote locations.

 Features
- GSM-based soil moisture monitoring
- Automatic SMS updates every 30 minutes
- Manual updates triggered by SMS keywords
- Moisture data provided as both raw ADC and percentage values
- Filters non-Kenyan numbers for security
- Real-time serial debug output for development and diagnostics

 Hardware Used
- Microcontroller: Arduino Mega
- GSM Module: SIM800L
- Soil Moisture Sensor: Analog (resistive)
- Power Source: 12V Battery Supply
- Optional: 16x2 LCD (for local display)

 Software
- Written in C++ using Arduino IDE
- Uses SoftwareSerial for GSM communication
- Includes modular functions for:
  - SMS sending/receiving
  - Sensor reading and conversion
  - Scheduled task execution

 Setup Instructions
1. Connect the hardware as per the schematic (to be uploaded in `/docs`).
2. Flash the code from the `/src` directory using Arduino IDE.
3. Insert a SIM card into the GSM module (ensure PIN is disabled).
4. Power the system and monitor serial output for logs.
5. Send SMS with the word Moisture to receive an update manually.

Phase 1 Goals Achieved
- Moisture sensing and percentage conversion
- Stable SMS communication via SIM800L
- Command parsing via keyword detection
- Working security filter (Kenyan numbers only)

License
This project is licensed under the MIT License.
