#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define Ultrasonic Sensor Pins
const int trigPin = 5;
const int echoPin = 18;

// Define LED Pins
const int lowLED = 25;
const int midLED = 26;
const int highLED = 27;

// Initialize LCD with correct I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Set Ultrasonic Sensor Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set LED Pins
  pinMode(lowLED, OUTPUT);
  pinMode(midLED, OUTPUT);
  pinMode(highLED, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Trigger Ultrasonic Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read Echo Pulse
  long duration = pulseIn(echoPin, HIGH);

  // Convert duration to distance in cm
  float distance = (duration * 0.01) / 2;

  // 🔍 Clamp invalid readings
  if (distance <= 0 || distance > 400) {
    distance = 0; // Set invalid readings to 0
  }

  // Print to Serial Monitor (Debugging)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display Distance on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Level:");
  lcd.setCursor(0, 1);

  if (distance == 0) {
    lcd.print("Invalid");
  } else {
    lcd.print(distance);
    lcd.print(" cm");
  }

  // Light LEDs Based on Distance
  if (distance == 0) {
    // All off if invalid reading
    digitalWrite(lowLED, LOW);
    digitalWrite(midLED, LOW);
    digitalWrite(highLED, LOW);
  } else if (distance > 30) {
    digitalWrite(lowLED, HIGH);
    digitalWrite(midLED, LOW);
    digitalWrite(highLED, LOW);
  } else if (distance <= 30 && distance > 15) {
    digitalWrite(lowLED, LOW);
    digitalWrite(midLED, HIGH);
    digitalWrite(highLED, LOW);
  } else {
    digitalWrite(lowLED, LOW);
    digitalWrite(midLED, LOW);
    digitalWrite(highLED, HIGH);
  }

  delay(1000); // Delay for stability (1 sec)
}
