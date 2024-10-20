#include <LiquidCrystal.h>
#include <DHT.h>

// Constants for sensor pins
#define DHTPIN 7              // Pin for DHT11
#define DHTTYPE DHT11         // DHT type
#define SOIL_PIN A0           // Pin for Soil Moisture sensor
#define RELAY_PIN 8           // Pin for Relay (Water Pump or Water Tank)
#define RAIN_SENSOR_PIN A1    // Pin for Rain Water Sensor

// Moisture thresholds
#define WET_THRESHOLD 400     // Moisture level for wet soil
#define DRY_THRESHOLD 700     // Moisture level for dry soil
#define RAIN_THRESHOLD 500    // Moisture level for rain detection

// Alert thresholds
#define TEMP_ALERT 30         // Temperature alert threshold (30°C)
#define HUMIDITY_ALERT 70     // Humidity alert threshold (70%)

// Initialize the LCD and DHT libraries
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// Function prototypes
void setupLCD();
void welcomeMessage();
bool initializeSensors();
float readTemperature();
float readHumidity();
int readSoilMoisture();
int readRainSensor();
void displaySensorData(float temperature, float humidity, int soilMoisture);
void handleRainDetection(int rainSensorValue);
void controlWaterPump(int soilMoisture);
void checkAlerts(float temperature, float humidity);
void errorHandling(const char* errorMsg);
void resetSystem();

void setup() {
    Serial.begin(9600); // Start serial communication
    setupLCD(); // Setup LCD
    welcomeMessage(); // Display welcome message

    dht.begin(); // Initialize DHT sensor
    pinMode(RELAY_PIN, OUTPUT); // Set relay pin as output
    digitalWrite(RELAY_PIN, LOW); // Turn off the pump/tank initially

    // Check if sensors are functioning correctly
    if (!initializeSensors()) {
        errorHandling("Sensor Error! Check connections.");
    }
}

void loop() {
    float temperature = readTemperature();
    float humidity = readHumidity();
    int soilMoisture = readSoilMoisture();
    int rainSensorValue = readRainSensor();

    // Display sensor readings on the LCD
    displaySensorData(temperature, humidity, soilMoisture);
    
    // Handle rain detection and control water pump
    handleRainDetection(rainSensorValue);
    controlWaterPump(soilMoisture);
    checkAlerts(temperature, humidity);

    delay(1000); // Wait for 1 second before the next iteration
}

// Function Definitions
void setupLCD() {
    lcd.begin(16, 2); // Initialize LCD
}

void welcomeMessage() {
    lcd.print("WELCOME TO");
    lcd.setCursor(0, 1);
    lcd.print("SCIENCE EXPO");
    delay(3000); // Wait for 3 seconds
    lcd.clear();
    lcd.print("Initializing...");
    delay(2000); // Wait for 2 seconds
}

bool initializeSensors() {
    // Check DHT sensor
    if (isnan(dht.readHumidity()) || isnan(dht.readTemperature())) {
        return false; // DHT sensor error
    }

    // Check soil moisture sensor
    int soilMoisture = analogRead(SOIL_PIN);
    if (soilMoisture < 0 || soilMoisture > 1023) {
        return false; // Soil moisture sensor error
    }

    return true; // All sensors are functioning correctly
}

float readTemperature() {
    return dht.readTemperature(); // Read temperature from DHT11
}

float readHumidity() {
    return dht.readHumidity(); // Read humidity from DHT11
}

int readSoilMoisture() {
    return analogRead(SOIL_PIN); // Read soil moisture
}

int readRainSensor() {
    return analogRead(RAIN_SENSOR_PIN); // Read rain sensor
}

void displaySensorData(float temperature, float humidity, int soilMoisture) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print(" %");

    delay(3000); // Display temperature and humidity for 3 seconds

    lcd.clear();
    lcd.setCursor(0, 0);
    displaySoilMoistureStatus(soilMoisture);
    lcd.setCursor(0, 1);
    lcd.print("Moist: ");
    lcd.print(soilMoisture);
    delay(3000); // Display soil moisture for 3 seconds
}

void displaySoilMoistureStatus(int soilMoisture) {
    if (soilMoisture < WET_THRESHOLD) {
        lcd.print("Soil: Wet");
    } else if (soilMoisture > DRY_THRESHOLD) {
        lcd.print("Soil: Dry");
    } else {
        lcd.print("Soil: Moist");
    }
}

void handleRainDetection(int rainSensorValue) {
    if (rainSensorValue < RAIN_THRESHOLD) {
        Serial.println("Rain detected! Opening water tank.");
        digitalWrite(RELAY_PIN, LOW); // Turn off the pump when it rains
        lcd.clear();
        lcd.print("Rain Detected!");
        delay(2000); // Display for 2 seconds
    }
}

void controlWaterPump(int soilMoisture) {
    if (soilMoisture > DRY_THRESHOLD) {
        digitalWrite(RELAY_PIN, HIGH); // Turn on the pump (dry soil)
        Serial.println("Pump ON");
    } else if (soilMoisture < WET_THRESHOLD) {
        digitalWrite(RELAY_PIN, LOW); // Turn off the pump (wet soil)
        Serial.println("Pump OFF");
    }
}

void checkAlerts(float temperature, float humidity) {
    if (temperature > TEMP_ALERT) {
        Serial.println("Temperature Alert!");
        lcd.clear();
        lcd.print("Temp Alert!");
        delay(2000);
    }

    if (humidity > HUMIDITY_ALERT) {
        Serial.println("Humidity Alert!");
        lcd.clear();
        lcd.print("Humidity Alert!");
        delay(2000);
    }
}

void errorHandling(const char* errorMsg) {
    lcd.clear();
    lcd.print(errorMsg);
    Serial.println(errorMsg);
    delay(3000); // Wait for 3 seconds
    resetSystem(); // Optionally reset system for recovery
}

void resetSystem() {
    // Optional: Implement a soft reset or halt
    Serial.println("Resetting system...");
    while (true); // Halt execution until the user resets the device
}
