# Driver for Honda steering wheel buttons

This sketch made for Arduino UNO R3 (ATMega328), but may convert for any other platforms.

The program reads the state of the buttons through ADC of microcontroller.

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

This is sketch for SUPRA SFD-106U

Communication occurs through transistors.
KEY1 in plume closes to ground via resistor; for each button its a resistor.

For simulate buttons: (github not showing normal, see local version)

PIN -- (220 Ohm) -------------------- B 
	    (+5 V) -- (RESISTOR N Ohm) -- C
	                                  E -- (GND)

Used KT315 (N-P-N) transistor (for example).

For simulate power button, encoder:

PIN -- (220 Ohm) -------------------- B 
	    (+5 V)   -------------------- C
	                                  E -- (10 Ohm) -- (GND)

// v1.1
Fixed bug: VOL- very small resistance, fix range.