/*
  Made by kirr2
  Special for Honda 2000 year of release (Odyssey RA6, Avancier TA2, etc)

  You need connect in A0 pin positive supply via 4.7 kOhm.
  Finally, connect one pin in A0, second pin - ground from Honda buttons.

  A0 -+------------+
    |            |
    4.7 kOhm    (Honda buttons)
    |            |
   +5 V         (GND)

  Default, Honda buttons block has a 10 (9.8) kOhm resistance
  When you hold a button, resistance change to:

  890 Ohm - when CH is hold
  304 Ohm - when Vol+ is hold
  46 Ohm - when Vol-
  2350 Ohm - when AM/FM
  9800 Ohm - when all buttons is not hold

  verified on Honda Avancier TA2 2000 year release.
*/

/*
   Sketch for SUPRA SFD-106U

   Tested on Honda Avancier TA2.
*/

#define RANGE_VOL_min a > 5 && a < 30 //range between 5 and 30 from analogRead() for VOL-
#define RANGE_VOL_plus a > 40 && a < 120
#define RANGE_CH a > 130 && a < 270
#define RANGE_FMAM a > 280 && a < 550

#define DELAY_BETWEEN_CLICKS_MAX 30 //30 * 10 = 300 ms
#define DELAY_BETWEEN_VOL_CLICKS 70 // 70 ms

#define ANALOG_PIN A0 //A0 Pin in Arduino UNO R3
#define BTN_NEXT_CONTROL_PIN 9 //Control buttons on SUPRA
#define BTN_BACK_CONTROL_PIN 11
#define BTN_RDM_CONTROL_PIN 13
#define MODE_CONTROL_PIN 4 //Control Power, radio, sd-card and aux mode
#define VOL_ENCODER_A_PIN 2 //Simulated encoder of volume
#define VOL_ENCODER_B_PIN 3

#define DEBUG 1 // 0 - off, 1 - on

boolean _free = false;

void _do_vol_m() { //Vol -
  digitalWrite(VOL_ENCODER_A_PIN, LOW);
  delay(30);
  digitalWrite(VOL_ENCODER_B_PIN, LOW);
  delay(30);
  digitalWrite(VOL_ENCODER_A_PIN, HIGH);
  delay(30);
  digitalWrite(VOL_ENCODER_B_PIN, HIGH);
  delay(30);
}

void _do_vol_p() { //Vol +
  digitalWrite(VOL_ENCODER_B_PIN, LOW);
  delay(30);
  digitalWrite(VOL_ENCODER_A_PIN, LOW);
  delay(30);
  digitalWrite(VOL_ENCODER_B_PIN, HIGH);
  delay(30);
  digitalWrite(VOL_ENCODER_A_PIN, HIGH);
  delay(30);
}

void _do_ch1() { //CH 1 func (1 click)
  digitalWrite(BTN_NEXT_CONTROL_PIN, HIGH);
  delay(140);
  digitalWrite(BTN_NEXT_CONTROL_PIN, LOW);
  delay(70);
}
void _do_ch2() { //CH 2 func (double click)
  digitalWrite(BTN_BACK_CONTROL_PIN, HIGH);
  delay(140);
  digitalWrite(BTN_BACK_CONTROL_PIN, LOW);
  delay(70);
}
void _do_ch3() { //CH 3 func (hold button)
  digitalWrite(BTN_RDM_CONTROL_PIN, HIGH);
  delay(140);
  digitalWrite(BTN_RDM_CONTROL_PIN, LOW);
  delay(70);
}

void _do_fmam() { //FM/AM
  digitalWrite(MODE_CONTROL_PIN, HIGH);
  delay(140);
  digitalWrite(MODE_CONTROL_PIN, LOW);
  delay(70);
}

void _do_free() { //free for working encoder, buttons not work.
  digitalWrite(VOL_ENCODER_A_PIN, LOW);
  digitalWrite(VOL_ENCODER_B_PIN, LOW);
}

void _do_notfree() { //encoder not work, buttons work. Encoder MUST be "in-between", i.e. must free line, otherwise buttons can't work with line A and B.
  digitalWrite(VOL_ENCODER_A_PIN, HIGH);
  digitalWrite(VOL_ENCODER_B_PIN, HIGH);
}


void setup() {
  if (DEBUG == 1) Serial.begin(9600);
  pinMode(BTN_NEXT_CONTROL_PIN, OUTPUT);
  pinMode(BTN_BACK_CONTROL_PIN, OUTPUT);
  pinMode(BTN_RDM_CONTROL_PIN, OUTPUT);
  pinMode(MODE_CONTROL_PIN, OUTPUT);
  pinMode(VOL_ENCODER_A_PIN, OUTPUT);
  pinMode(VOL_ENCODER_B_PIN, OUTPUT);

  digitalWrite(BTN_NEXT_CONTROL_PIN, LOW);
  digitalWrite(BTN_BACK_CONTROL_PIN, LOW);
  digitalWrite(BTN_RDM_CONTROL_PIN, LOW);
  digitalWrite(MODE_CONTROL_PIN, LOW);

  _do_notfree();
  _free = false;
  
}

void loop() {
  delay(50);

  int a = analogRead(ANALOG_PIN);

  if (RANGE_VOL_min) {
    //Vol-
    int i = 0;
    if (DEBUG == 1) Serial.println("VOL-");
    while (a < 550 && i <= DELAY_BETWEEN_CLICKS_MAX) {
      a = analogRead(ANALOG_PIN);
      delay(10);
      i++;
    }

    if (i >= DELAY_BETWEEN_CLICKS_MAX) {
      while (a < 550) { //many clicks while hold
        a = analogRead(ANALOG_PIN);
        if (DEBUG == 1) Serial.println("-");
        _do_vol_m();
        delay(DELAY_BETWEEN_VOL_CLICKS); //delay between clicks for volume
      }
    }
    else { //second click
      if (DEBUG == 1) Serial.println("--");
      _do_vol_m();
    }
  }

  else if (RANGE_VOL_plus) {
    //Vol+
    int i = 0;
    if (DEBUG == 1) if (DEBUG == 1) Serial.println("VOL+");
    while (a < 550 && i <= DELAY_BETWEEN_CLICKS_MAX) {
      a = analogRead(ANALOG_PIN);
      delay(10);
      i++;
    }

    if (i >= DELAY_BETWEEN_CLICKS_MAX) {
      while (a < 550) {
        a = analogRead(ANALOG_PIN);
        if (DEBUG == 1) Serial.println("+");
        _do_vol_p();
        delay(DELAY_BETWEEN_VOL_CLICKS);
      }
    }
    else {
      if (DEBUG == 1) Serial.println("++");
      _do_vol_p();
    }
  }

  else if (RANGE_CH) {
    //CH
    if (DEBUG == 1) Serial.println("CH");
    int i = 0;

    while (a < 550) {
      a = analogRead(ANALOG_PIN);
      delay(10);
      i++;
    }
    if (i <= DELAY_BETWEEN_CLICKS_MAX) {
      i = 0;
      while (a < 550) {
        a = analogRead(ANALOG_PIN);
        delay(10);
        i++;
      }

      if (analogRead(ANALOG_PIN) > 550 && i <= DELAY_BETWEEN_CLICKS_MAX) {
        i = 0;
        while (i <= DELAY_BETWEEN_CLICKS_MAX) {
          delay(10);
          i++;
          a = analogRead(ANALOG_PIN);
          if (a < 550) {
            if (DEBUG == 1) Serial.println("F1");
            _do_ch2();
            while (a < 550) a = analogRead(ANALOG_PIN);
            break;
          }
          if (i >= 29) {
            if (DEBUG == 1) Serial.println("F2");
            _do_ch1();
            while (a < 550) a = analogRead(ANALOG_PIN);
            break;
          }
        }
      }
    }
    else {
      if (DEBUG == 1) Serial.println("F3");
      _do_ch3();
      while (a < 550) a = analogRead(ANALOG_PIN);
    }
  }

  else if (RANGE_FMAM) {
    //FM/AM
    int i = 0;
    if (DEBUG == 1) Serial.println("FM/AM");
    while (a < 550 && i <= DELAY_BETWEEN_CLICKS_MAX) {
      a = analogRead(ANALOG_PIN);
      delay(10);
      i++;
    }

    if (i >= DELAY_BETWEEN_CLICKS_MAX) {
      if (!_free) {
        if (DEBUG == 1) Serial.println("FREE");
        _do_free();
        _free = true;
      }
      else {
        if (DEBUG == 1) Serial.println("NOT FREE");
        _do_notfree();
        _free = false;
      }
    }
    else { //second click
      if (DEBUG == 1) Serial.println("MODE");
      _do_fmam();
    }

    while (a < 550) a = analogRead(ANALOG_PIN);
  }

}
