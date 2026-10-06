# 🌬️ Windmill Voltage Monitor

An Arduino sketch that reads the output voltage of a small DC
generator/motor (e.g. driven by a toy or model windmill) and displays it
live on a 16x2 I2C LCD.

## How it works

The generator's output is fed through a resistive voltage divider before
reaching the Arduino's analog input, because a small DC generator can easily
produce more than the 5V an analog pin can safely read. The divider scales
the input down by roughly 11x, and the sketch multiplies the ADC reading
back up by that same factor to recover the real voltage.

```
Generator (+) ──>── [10kΩ] ───┬───>── [1kΩ] ───>── GND
                               │
                              A0 (Arduino analog input)

Generator (−) ─────────────────────────────────────>── GND
```

## Hardware

| Component | Notes |
|---|---|
| Arduino Uno / Nano (or compatible) | |
| DC generator / small windmill motor | the thing being measured |
| 10kΩ resistor | top half of the divider |
| 1kΩ resistor | bottom half of the divider |
| 16x2 LCD with I2C backpack | address usually `0x27` or `0x3F` |

**LCD wiring:**

| LCD (I2C) | Arduino (Uno/Nano) |
|---|---|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

## Setup

1. Wire the circuit as above.
2. Open [`windmill.ino`](windmill.ino) in the Arduino IDE.
3. Install the **LiquidCrystal I2C** library (Library Manager → search
   "LiquidCrystal I2C" by Frank de Brabander, or Marco Schwartz's fork).
4. If the display stays blank, run an I2C scanner sketch to confirm the
   backpack's address and update `LiquidCrystal_I2C lcd(0x27, 16, 2);`
   accordingly.
5. Upload to the board. The LCD shows a brief title, then live voltage
   readings refreshed every 500ms.

## Tuning

- `DIVIDER_RATIO` — set this to match your actual resistor values:
  `(R1 + R2) / R2`. The default (11.0) assumes 10kΩ over 1kΩ.
- `SAMPLE_INTERVAL_MS` — how often the reading refreshes.

## Status

This sketch mirrors the working logic from the original version but has
not been re-flashed to hardware as part of this cleanup pass — the circuit
and constants are unchanged from the tested design, only code structure and
comments were improved.
