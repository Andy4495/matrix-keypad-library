/******************************************************************************
  Matrix Keypad Library Example

  https://github.com/Andy4495/matrix-keypad-library

   Version History
   1.0.0    03/08/2019  A.T.   Original

******************************************************************************/
#define NUM_COLS 4
#define NUM_ROWS 4
byte colPins[NUM_COLS] = {2, 3, 6, 8};
byte rowPins[NUM_ROWS] = {13, 12, 11, 5};

#include "Keypad4495.h"

// For BOOST-IR, scan order is bottom-right to top-left, up-first, then left
char keymap[NUM_COLS * NUM_ROWS] = { 'D', 'C', 'B', 'A', 'R', '9', '6', '3', '0', '8', '5', '2', 'L', '7', '4', '1' };
Keypad4495 myKeypad(keymap, rowPins, colPins, NUM_ROWS, NUM_COLS);

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Keypad4495");
  Serial.println("==========");
}

void loop() {

  int i;

  Serial.println("Blocking wait for a key press");
  Serial.println("Loop for 10 times, then move to next example.");

  for (i = 0; i < 10; i++) {
    Serial.print("Test ");
    Serial.print(i+1);
    Serial.println(" of 10:");
    waitForKeyExample();
    delay(200);
  }

  Serial.println("Non-blocking wait for a key press");
  Serial.println("Loop for approximately 10 seconds, then move to next example.");
  for (i = 0; i < 10; i++) {
    getKeyExample();
  }

  Serial.println("Non-blocking wait for a key press");
  Serial.println("Loop 10 times, with 1 second delay between loops.");
  for (i = 0; i < 10; i++) {
    getMatrixStatusExample();
    delay(1000);
  }

  Serial.println("Pausing for 5 seconds, then starting example over...");
  delay(5000);
}

void waitForKeyExample() {
  char c;

  Serial.print("Waiting for key press....");
  c = myKeypad.waitForKey(); // Nothing else happens while we wait for the key: BLOCKING call
  Serial.print("key press detected --> ");
  Serial.println(c);
}

void getKeyExample() {
  char c;
  unsigned long prevMillis = 0;

  prevMillis = millis();

  if (millis() - prevMillis < 10000) {
    Serial.print("Checking if key pressed...");
    c = myKeypad.getKey(); // Non-blocking. We could do other stuff while we w
    if (c != Keypad4495::NO_KEY) {
      Serial.print("key press detected --> ");
      Serial.println(c);
    }
    else {
      Serial.println("No key detected.");
    }
    delay(100); // Slow this down just for the purpose of an example; normal coding would not use delay() here
  }


}

void getMatrixStatusExample() {
  // use this routine to manually figure out the character
  // positions of the keymap. Press each key on the keypad one at
  // a time, and display the scan order and array index position

  // getMatrixStatus can also be used to detect multiple simultaneous key presses

  byte matrix[NUM_ROWS * NUM_COLS];

  myKeypad.getMatrixStatus(matrix);

  for (int i = 0; i < NUM_ROWS * NUM_COLS; i++) {
    if (matrix[i] == 1) {
      Serial.print("Keymap array index: [");
      Serial.print(i);
      Serial.print("], Keymap character: ");
      Serial.println(keymap[i]);
    }
  }
}
