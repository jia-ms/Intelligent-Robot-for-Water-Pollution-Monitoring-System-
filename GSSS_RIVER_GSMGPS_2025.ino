#define BLYNK_TEMPLATE_ID "TMPL3JQqly1lm"
#define BLYNK_TEMPLATE_NAME "RIVER BOT"
#define BLYNK_AUTH_TOKEN "QJ-5M8aKrg1JQLhrW3445T6RH5Fz_5Z5"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <TinyGPSPlus.h>

// ---------- PIN DEFINITIONS ----------
#define RELAY1  13   // Motor R+
#define RELAY2  12   // Motor R-
#define RELAY3  14   // Motor L+
#define RELAY4  27   // Motor L-
#define GAS_PIN  23 // Digital gas sensor
#define TURBIDITY_PIN 34 // Analog turbidity
#define PH_PIN  35   // Analog pH sensor
#define GPS_RX  16   // GPS TX -> ESP32 RX
#define GPS_TX  17   // GPS RX -> ESP32 TX
#define GSM_RX  4    // GSM TX -> ESP32 RX
#define GSM_TX  2    // GSM RX -> ESP32 TX

// ---------- BLYNK VIRTUAL PINS ----------
#define VPIN_GPS_SEND V4
#define VPIN_TURB     V5
#define VPIN_GAS      V6
#define VPIN_PH       V7

// ---------- NETWORK CONFIG ----------
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ROBOT";
char pass[] = "12345678";

BlynkTimer timer;

// ---------- SERIALS ----------
HardwareSerial SerialGPS(1);
HardwareSerial SerialGSM(2);
TinyGPSPlus gps;

// ---------- GLOBALS ----------
String gpsData = "No Fix";
float pHValue = 0.0;

void setup() {
  Serial.begin(115200);
  delay(100);

  // Initialize serials
  SerialGPS.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  SerialGSM.begin(9600, SERIAL_8N1, GSM_RX, GSM_TX);

  // Setup pins
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(GAS_PIN, INPUT);
  pinMode(TURBIDITY_PIN, INPUT);

  stopMotors();

  Serial.println("Connecting to WiFi & Blynk...");
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, sensorUpdate);

  Serial.println("✅ Robot Initialized!");
}

// ---------- SENSOR READING ----------
void sensorUpdate() {
  int gasVal = digitalRead(GAS_PIN);
  int turbVal = analogRead(TURBIDITY_PIN);
  int phRaw = analogRead(PH_PIN);
 if(gasVal==0)
 {
  Blynk.virtualWrite(VPIN_GAS, "POLLUTED SMELL DETECTED");
  delay(5000);
  Blynk.virtualWrite(VPIN_GAS, "   ");
 }
  // --- Convert pH sensor analog to voltage and pH value ---
  float voltage = (phRaw / 4095.0) * 3.3;   // ADC to volts
  pHValue = 7 + ((1.65 - voltage) / 0.18);  // Approx linear calibration (adjust after testing)

  // --- Read GPS ---
  while (SerialGPS.available()) {
    gps.encode(SerialGPS.read());
  }

  if (gps.location.isValid()) {
    gpsData = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
  } else {
    gpsData = "No Fix";
  }


if((turbVal>=0)&&(turbVal<500))
{ 
  Blynk.virtualWrite(VPIN_TURB,"HIGHLY POLUTED WATER"); 
  Serial.println("HIGHLY POLUTED WATER");
}
if((turbVal>500)&&(turbVal<900))
{ 
  Blynk.virtualWrite(VPIN_TURB,"MODERATELY POLUTED WATER"); 
  Serial.println("MODERATELY POLUTED WATER");
}
if(turbVal>900)
{ 
  Blynk.virtualWrite(VPIN_TURB,"WATER IS CLEAR"); 
  Serial.println("WATER IS CLEAR");
}
  // --- Send to Blynk ---
  Blynk.virtualWrite(VPIN_GAS, gasVal);
  Blynk.virtualWrite(VPIN_PH, pHValue);

  // --- Debug Serial ---
  Serial.print("Turbidity: ");
  Serial.print(turbVal);
  Serial.print(" | Gas: ");
  Serial.print(gasVal);
  Serial.print(" | pH: ");
  Serial.print(pHValue);
  Serial.print(" | GPS: ");
  Serial.println(gpsData);
}

// ---------- GSM SMS FUNCTION ----------
void sendSMS(String msg) {
  SerialGSM.println("AT");
  delay(200);
  SerialGSM.println("AT+CMGF=1");
  delay(200);
  SerialGSM.println("AT+CMGS=\"+917676015363\"");  // replace with your number
  delay(200);
  SerialGSM.print(msg);
  SerialGSM.write(26); // CTRL+Z
  delay(3000);
  Serial.println("📩 SMS Sent: " + msg);
}

// ---------- BLYNK HANDLERS ----------
BLYNK_WRITE(VPIN_GPS_SEND) {
  int req = param.asInt();
  if (req == 1) {
    if (gps.location.isValid()) {
      String msg = "GPS: https://maps.google.com/?q=" +
                   String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
      sendSMS(msg);
    } else {
      sendSMS("GPS signal not fixed!");
    }
  }
}

// ---------- BLYNK MOTOR CONTROLS ----------
BLYNK_WRITE(V0) { // Forward
  if (param.asInt()) moveForward(); else stopMotors();
}

BLYNK_WRITE(V1) { // Reverse
  if (param.asInt()) moveReverse(); else stopMotors();
}

BLYNK_WRITE(V2) { // Right
  if (param.asInt()) turnRight(); else stopMotors();
}

BLYNK_WRITE(V3) { // Left
  if (param.asInt()) turnLeft(); else stopMotors();
}

// ---------- MOTOR FUNCTIONS ----------
void moveForward() {
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, LOW);
  Serial.println("⬆️ Moving Forward");
}

void moveReverse() {
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, HIGH);
  Serial.println("⬇️ Moving Reverse");
}

void turnRight() {
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, LOW);
  Serial.println("➡️ Turning Right");
}

void turnLeft() {
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, HIGH);
  Serial.println("⬅️ Turning Left");
}

void stopMotors() {
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, LOW);
  Serial.println("🛑 Stopped");
}

// ---------- MAIN LOOP ----------
void loop() {
  Blynk.run();
  timer.run();
}
