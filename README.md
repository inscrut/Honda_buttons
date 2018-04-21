# Driver for Honda steering wheel buttons

This sketch made for Arduino UNO R3 (ATMega328), but may convert for any other platforms.

The program reads the state of the buttons through the microcontroller ADC.

Initially, the Honda Odyssey / Avancier has four buttons:
- CH
- VOL+
- VOL-
- AM/FM

Functionality for each button:
+ CH
-- one click
-- double click
-- hold ( > 1 sec)

+ VOL+ and VOL-
-- one click (second click)
-- hold (while hold, volume to max or low)

+ AM/FM
-- one click or hold (second click)

This is base sketch.