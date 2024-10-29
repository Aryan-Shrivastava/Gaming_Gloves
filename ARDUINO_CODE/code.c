uint8_t buf[8] = {
  0
};  // Keyboard Report Buffer: 8 bytes

#define PIN_1 A0
#define PIN_2 A1
#define PIN_3 A2
#define PIN_4 A4
#define PIN_5 A5


//#define SERIAL_DEBUG  // for serial debug: remove //
// for actual HID: put //

bool currState_1 = HIGH;
bool currState_2 = HIGH;
bool currState_3 = HIGH;
bool currState_4 = HIGH;
bool currState_5 = HIGH;

bool prevState_1 = HIGH;
bool prevState_2 = HIGH;
bool prevState_3 = HIGH;
bool prevState_4 = HIGH;
bool prevState_5 = HIGH;

unsigned long prevTime_1 = 0;
unsigned long prevTime_2 = 0;
unsigned long prevTime_3 = 0;
unsigned long prevTime_4 = 0;
unsigned long prevTime_5 = 0;

unsigned long waitTime_1 = 50;
unsigned long waitTime_2 = 50;
unsigned long waitTime_3 = 50;
unsigned long waitTime_4 = 50;
unsigned long waitTime_5 = 50;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_1, INPUT_PULLUP);
  pinMode(PIN_2, INPUT_PULLUP);
  pinMode(PIN_3, INPUT_PULLUP);
  pinMode(PIN_4, INPUT_PULLUP);
  pinMode(PIN_5, INPUT_PULLUP);

  delay(200);
}

void loop() {
  checkButton();
}

int flag = 0;
void checkButton() {

  int one_read = analogRead(PIN_1);
  int two_read = analogRead(PIN_2);
  int three_read = analogRead(PIN_3);
  int four_read = analogRead(PIN_4);
  int five_read = analogRead(PIN_5);



  char one_ch = 'A';
  int one_int = one_ch - 'A' + 4;

  char two_ch = 'B';
  int two_int = two_ch - 'A' + 4;

  char three_ch = 'C';
  int three_int = three_ch - 'A' + 4;

  char four_ch = 'D';
  int four_int = four_ch - 'A' + 4;

  char five_ch = 'E';
  int five_int = five_ch - 'A' + 4;

  bool currRead_1 = true;
  if (one_read >830) currRead_1 = false;
  bool currRead_2 = true;
  if (two_read > 870) currRead_2 = false;
  bool currRead_3 = true;
  if (three_read >810)currRead_3 = false;
  bool currRead_4 = true;
  if (four_read >840) currRead_4 = false;
  bool currRead_5 = true;
  if (five_read >710) currRead_5 = false;

  if (currRead_1 != prevState_1) {
    prevTime_1 = millis();
  }
  if (currRead_2 != prevState_2) {
    prevTime_2 = millis();
  }
  if (currRead_3 != prevState_3) {
    prevTime_3 = millis();
  }
  if (currRead_4 != prevState_4) {
    prevTime_4 = millis();
  }
  if (currRead_5 != prevState_5) {
    prevTime_5 = millis();
  }

  if ((millis() - prevTime_1) > waitTime_1) {
    {
      if (currRead_1 != currState_1) {
        currState_1 = currRead_1;
        if (currState_1 == LOW) {
          // Send the code
          buf[2] = one_int;  // HID: W key
#ifdef SERIAL_DEBUG
          buf[2] = one_ch;  // Serial: W key
#endif
          Serial.write(buf, 8);  // Send keypress
        } else {
          // Release the keyboard
          releaseKey();
        }
      }
    }
  }


  if ((millis() - prevTime_2) > waitTime_2) {
    if (currRead_2 != currState_2) {
      currState_2 = currRead_2;
      if (currState_2 == LOW) {
        // Send the code
        buf[2] = two_int;  // HID: A key
#ifdef SERIAL_DEBUG
        buf[2] = two_ch;  // Serial: A key
#endif
        Serial.write(buf, 8);  // Send keypress
      } else {
        // Release the keyboard
        releaseKey();
      }
    }
  }

  if ((millis() - prevTime_3) > waitTime_3) {
    if (currRead_3 != currState_3) {
      currState_3 = currRead_3;
      if (currState_3 == LOW) {
        // Send the code
        buf[2] = three_int;  // HID: S key
#ifdef SERIAL_DEBUG
        buf[2] = three_ch;  // Serial: S key
#endif
        Serial.write(buf, 8);  // Send keypress
      } else {
        // Release the keyboard
        releaseKey();
      }
    }
  }

  if ((millis() - prevTime_4) > waitTime_4) {
    if (currRead_4 != currState_4) {
      currState_4 = currRead_4;
      if (currState_4 == LOW) {
        // Send the code
        buf[2] = four_int;  // HID: D key
#ifdef SERIAL_DEBUG
        buf[2] = four_ch;  // Serial: D key
#endif
        Serial.write(buf, 8);  // Send keypress
      } else {
        // Release the keyboard
        releaseKey();
      }
    }
  }

  if ((millis() - prevTime_5) > waitTime_5) {
    {
      if (currRead_5 != currState_5) {
        currState_5 = currRead_5;
        if (currState_5 == LOW) {
          // Send the code
          buf[2] = five_int;  // HID: W key
#ifdef SERIAL_DEBUG
          buf[2] = five_ch;  // Serial: W key
#endif
          Serial.write(buf, 8);  // Send keypress
        } else {
          // Release the keyboard
          releaseKey();
        }
      }
    }
  }

  prevState_1 = currRead_1;
  prevState_2 = currRead_2;
  prevState_3 = currRead_3;
  prevState_4 = currRead_4;
  prevState_5 = currRead_5;

delay(100);
  // Serial.println(five_read);
}

void releaseKey() {
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);  // Release key
}
