/*
 * Windmill Voltage Monitor
 *
 * Reads the output of a small DC generator (e.g. a windmill/turbine motor
 * used as a generator) through a resistive voltage divider and displays the
 * computed voltage on a 16x2 I2C LCD.
 *
 * Wiring:
 *   DC generator (+)  -> top of a 10k resistor
 *   10k/1k junction    -> Arduino A0
 *   bottom of 1k       -> GND
 *   DC generator (-)   -> Arduino GND
 *
 *   The 10k:1k divider scales the generator's voltage down by ~11x, so a
 *   generator producing up to ~55V still lands safely within the Arduino's
 *   0-5V ADC range. See README.md for the full wiring diagram.
 *
 *   LCD (16x2, I2C backpack):
 *     VCC -> 5V, GND -> GND, SDA -> A4, SCL -> A5 (Uno/Nano)
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C address is usually 0x27 or 0x3F depending on the backpack - adjust if
// the display stays blank. An I2C scanner sketch will confirm the address.
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int VOLTAGE_PIN = A0;
const float ADC_MAX = 1023.0;
const float ADC_REFERENCE_VOLTS = 5.0;
const float DIVIDER_RATIO = 11.0; // (10k + 1k) / 1k
const unsigned long SAMPLE_INTERVAL_MS = 500;

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Windmill Voltage");
  delay(2000);
  lcd.clear();
}

void loop() {
  float voltage = readVoltage(VOLTAGE_PIN);

  lcd.setCursor(0, 0);
  lcd.print("Windmill");
  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(voltage, 2);
  lcd.print("V   "); // trailing spaces clear leftover digits from longer readings

  delay(SAMPLE_INTERVAL_MS);
}

float readVoltage(int analogPin) {
  int raw = analogRead(analogPin);
  return (raw * ADC_REFERENCE_VOLTS / ADC_MAX) * DIVIDER_RATIO;
}
