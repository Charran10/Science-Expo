Automated Plant Watering System
This project automates plant watering based on soil moisture, temperature, humidity, and rain detection. It uses an Arduino Uno to control various sensors and a water pump, ensuring your plants get the right amount of water.

Components
Arduino Uno: The microcontroller.
DHT11 Sensor: Measures temperature and humidity.
Soil Moisture Sensor: Detects soil moisture levels.
Rain Sensor: Detects rainfall.
Relay Module: Controls the water pump.
Water Pump: Activated when soil is dry.
16x2 LCD Display: Displays sensor data.
Breadboard and Jumper Wires: Used to connect components.
Full Wiring Diagram
Arduino to LCD Display (16x2) Connections:
GND (LCD) -> GND (Arduino)
VCC (LCD) -> 5V (Arduino)
SDA -> A4 (Arduino)
SCL -> A5 (Arduino)
Arduino to DHT11 Sensor:
VCC (DHT11) -> 5V (Arduino)
GND (DHT11) -> GND (Arduino)
Data (DHT11) -> Pin 7 (Arduino)
Arduino to Soil Moisture Sensor:
VCC (Soil Sensor) -> 5V (Arduino)
GND (Soil Sensor) -> GND (Arduino)
Signal Pin (Soil Sensor) -> A0 (Arduino)
Arduino to Rain Sensor:
VCC (Rain Sensor) -> 5V (Arduino)
GND (Rain Sensor) -> GND (Arduino)
Signal Pin (Rain Sensor) -> A1 (Arduino)
Arduino to Relay Module:
VCC (Relay) -> 5V (Arduino)
GND (Relay) -> GND (Arduino)
IN (Relay) -> Pin 8 (Arduino)
NO (Relay) -> Water Pump's Positive lead
COM (Relay) -> External Power Supply (+ side)
Arduino to Water Pump:
Water Pump Positive lead -> NO (Normally Open) on Relay
Water Pump Negative lead -> External Power Supply Ground
Code Explanation
The Arduino code reads sensor values and controls the water pump based on soil moisture and rain conditions. It also displays data on the LCD and triggers temperature/humidity alerts.

Code Overview
Pin Setup:
cpp
Copy code
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11
#define SOIL_PIN A0
#define RELAY_PIN 8
#define RAIN_SENSOR_PIN A1

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);
Main Functions:
setupLCD(): Initializes the LCD and displays a welcome message.
initializeSensors(): Checks if the DHT11 and soil moisture sensors are functioning.
readTemperature(): Reads temperature from the DHT11 sensor.
readHumidity(): Reads humidity from the DHT11 sensor.
readSoilMoisture(): Reads the soil moisture level.
readRainSensor(): Reads the rain sensor value.
controlWaterPump(): Turns on/off the water pump based on soil moisture.
checkAlerts(): Displays alerts for high temperature or humidity.
handleRainDetection(): Stops the pump if rain is detected.
How It Works
System Initialization: When powered on, the LCD displays a welcome message and initializes the sensors.
Data Monitoring: The system continuously reads data from the soil moisture sensor, rain sensor, and DHT11 sensor.
Water Pump Control: When the soil is dry, the water pump is activated. It stops when the soil is moist or if rain is detected.
LCD Display: The LCD alternates between displaying temperature, humidity, and soil moisture levels.
Troubleshooting
LCD Issues: Check the connections to the SDA and SCL pins. Ensure the I2C address is correct.
Sensor Reading Issues: Verify wiring for the DHT11, soil moisture sensor, and rain sensor.
Water Pump Issues: Ensure the relay module is wired properly and the external power supply is working.
Conclusion
This project automates plant watering and provides environmental data to help maintain optimal plant growth. The system is easy to use and can be expanded with additional sensors or features.

Enjoy automating your plant care!
