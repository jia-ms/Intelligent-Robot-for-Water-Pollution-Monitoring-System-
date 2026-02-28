# Intelligent-Robot-for-Water-Pollution-Monitoring-System-

An IoT-based autonomous robotic system designed to monitor and analyze water quality parameters in real time. The robot is equipped with multiple environmental sensors to detect turbidity, pH level, and odor (gas presence) in water bodies. The system continuously collects water quality data and transmits it to the cloud using IoT communication protocols. Users can remotely monitor pollution levels through the Blynk IoT mobile application, which displays real-time sensor readings and pollution status indicators.

Additionally, the robot provides location tracking capability, allowing users to request and identify the exact position of the robot during operation.

🚀 Key Features

Real-time Turbidity Monitoring

pH Level Detection

Gas/Smell Detection for Water Contamination

Live Location Tracking on Request

IoT Integration with Blynk App

Remote Monitoring & Alerts

🛠️ Technologies Used

Microcontroller (ESP32)

Water Quality Sensors (Turbidity, pH, Gas)

GPS and GSM Module for Location Tracking

Blynk IoT Platform

Wireless Communication (WiFi/Bluetooth)

📊 Output

Sensor readings and pollution levels are visualized on the Blynk IoT dashboard, enabling users to assess water quality remotely and efficiently.

1. Requirements
🔹 Hardware

Arduino (Uno/Nano)

USB cable

Turbidity sensor

pH sensor

Gas sensor (MQ series)

GPS module (optional)

Jumper wires

Breadboard

Power supply / Battery

🔹 Software

Arduino IDE

Blynk IoT app

Required Arduino libraries

STEPS TO TAKE:

✅ 2. Install Arduino IDE

Download Arduino IDE from the official website.

Install and open the IDE.

Go to Tools → Board → Select your board (e.g., Arduino Uno).

Go to Tools → Port → Select COM Port.

✅ 3. Connect Arduino to PC

Connect board using USB cable.

Green power LED should turn ON.

Confirm correct board and port are selected.

✅ 4. Connect Sensors to Arduino
🔹 Turbidity Sensor
🔹 pH Sensor (REECOMMENDATION: USE SEPERATE 5V BATTERY FOR ph)
🔹 Gas Sensor (MQ)
🔹 GPS Module (Optional)

✅ 5. Write / Paste the Code

Open Arduino IDE.

Create a new sketch.

Paste your sensor + Blynk code.

Install required libraries from Sketch → Include Library → Manage Libraries.
<WiFi.h>
<BlynkSimpleEsp32.h>
<TinyGPSPlus.h>

✅ 6. Verify the Code

Click Verify (✓) button.

Fix errors if any.

✅ 7. Upload Code to Microcontroller

Click Upload (→) button.

Wait for “Done Uploading” message.

Now the code is dumped into the Arduino.

✅ 8. Monitor Output

Open Serial Monitor to check sensor readings.

Blynk IoT Setup for ESP32 (Step-by-Step)
✅ 1. Install Requirements

Install Blynk IoT app and create account

Install Arduino IDE

In Arduino IDE:

Go to Board Manager → Install ESP32 by Espressif Systems

Install Blynk library from Library Manager

✅ 2. Create Template in Blynk

Open Blynk Console (web)

Click Create Template

Hardware: ESP32

Connection: WiFi

Save it

✅ 3. Create Datastreams

Go to Datastreams → Virtual Pin (RECOMMENDATION: For a moving bot set the pins according to the directions like forward, backward, left and right.)

V0 → Turbidity (Float)

V1 → pH (Float)

V2 → Gas Sensor (Integer)

V3 → GPS (Location)

Save all.

✅ 4. Add Device

Go to Devices → New Device → From Template

Copy BLYNK_TEMPLATE_ID and AUTH TOKEN

✅ 5. Sample ESP32 + Blynk Code
#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_DEVICE_NAME "WaterMonitor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

✅ 6. Upload Code

Select Board → ESP32 Dev Module

Select correct COM Port

Click Upload

✅ 7. Setup Mobile Dashboard

In Blynk App:

Add Gauge → V0 (Turbidity)

Add Gauge → V1 (pH)

Add Value Display → V2 (Gas)

Add Map Widget → V3 (GPS)

Press ▶ Run.

Open Blynk App to view live water quality data.
