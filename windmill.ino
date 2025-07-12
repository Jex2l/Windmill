#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD I2C address (try 0x27 or 0x3F depending on your module)
LiquidCrystal_I2C lcd(0x27, 16, 2); 
const int analogPin = A0;

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Windmill Voltage");
  delay(3000);
}

void loop() {
  int analogValue = analogRead(analogPin);
  // Convert to voltage: (Analog value / 1023) * 5V * 11 (because of 10k & 1k divider)
  float voltage = (analogValue * 5.0 / 1023.0) * 11.0;
  lcd.setCursor(0, 1);
  lcd.print("Voltage : ");
  lcd.print(voltage, 2);  // Display voltage with 2 decimal places
  lcd.print("       ");    // Clear extra chars
  delay(500);
}


// 🔧 CONNECTIONS
// 1. 🌀 DC Motor (Generator)
// Motor + terminal → Top of 10kΩ resistor (Voltage Divider Input)

// Motor – terminal → Arduino GND

// 2. ⚙️ Voltage Divider
// Connect 10kΩ resistor between motor + output and the junction point

// Connect 1kΩ resistor between junction point and GND

// Connect junction point (between 10k and 1k) to Arduino A0

// ⚠️ This will divide input voltage by ~11 so Arduino gets max 5V even if motor generates 55V.

// less
// Copy
// Edit
// DC Motor + ──>── [10kΩ] ───+───>── [1kΩ] ───>── GND
//                           |
//                          A0 (Arduino analog pin)
// 3. 📟 16x2 LCD with I2C Module
// LCD I2C Pin	Arduino UNO/Nano
// VCC	5V
// GND	GND
// SDA	A4
// SCL	A5

