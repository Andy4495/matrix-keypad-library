/* Library to interface with a matrixed keypad.
   There are already numerous other libraries available. I created this on as
   a simpler alternative, both from a usage standpoint and for ease of
   understanding the code.

   https://gitlab.com/Andy4495/matrix-keypad-library
*/
/* Version History
   1.0.0    03/05/2019  A.T.   Original
   1.0.1    04/05/2019  A.T.   Added support for "Keep Active" mode
*/
#include "Keypad4495.h"

Keypad4495::Keypad4495(char *userKeymap, byte *rowPins, byte *colPins, byte numRows, byte numCols, bool keepActive){
  _keymap = userKeymap;
  _rowPins = rowPins;
  _colPins = colPins;
  _numRows = numRows;
  _numCols = numCols;
  _keepActive = keepActive;

  int i;

  for (i = 0; i < _numRows; i++) {
    pinMode(_rowPins[i], INPUT_PULLUP);
  }

  // If keepActive is true, then we leave the column pins in
  // output mode all the time (except when scanning the keypad)
  if (_keepActive == true) {
    enableCols();
  }
  else { // Otherwise, column pins are set to input mode unless scanning keypad
    for (i = 0; i < _numCols; i++) {
        pinMode(_colPins[i], INPUT);
      }
  }
};

// Blocking call -- waits for a keypress before returning
char Keypad4495::waitForKey() {
  bool keypress = false;
  char key;
  int c, r;

  // Need to disable the columns so that only one is active at a time when scanning
  if (_keepActive == true) {
    disableCols();
  }

  while (!keypress) {
    for (c = 0; c < _numCols; c++) {
      pinMode(_colPins[c], OUTPUT);
      digitalWrite(_colPins[c], LOW);
      for (r = 0; r < _numRows; r++) {
        if (digitalRead(_rowPins[r]) == LOW) {
          key = _keymap[c * _numCols + r];
          keypress = true;
        }
      }
      pinMode(_colPins[c], INPUT);
    }
  }

  if (_keepActive == true) {
    enableCols();
  }
  return(key);
};

// Non-blocking. Returns first key found in scan. Returns NO_KEY if no keys are pressed
char Keypad4495::getKey() {
  char key = NO_KEY;
  int c, r;

  // Need to disable the columns so that only one is active at a time when scanning
  if (_keepActive == true) {
    disableCols();
  }

  for (c = 0; c < _numCols; c++) {
    pinMode(_colPins[c], OUTPUT);
    digitalWrite(_colPins[c], LOW);
    for (r = 0; r < _numRows; r++) {
      if (digitalRead(_rowPins[r]) == LOW) {
        key = _keymap[c * _numCols + r];
      }
    }
    pinMode(_colPins[c], INPUT);
  }

  if (_keepActive == true) {
    enableCols();
  }
  return(key);
};

// Scans full matrix and sets corresponding element to 1 if that key is pressed
void Keypad4495::getMatrixStatus(byte* matrix_array) {
  int c, r;

  // Need to disable the columns so that only one is active at a time when scanning
  if (_keepActive == true) {
    disableCols();
  }

  for (c = 0; c < _numCols; c++) {
    pinMode(_colPins[c], OUTPUT);
    digitalWrite(_colPins[c], LOW);
    for (r = 0; r < _numRows; r++) {
      if (digitalRead(_rowPins[r]) == LOW) {
        matrix_array[c * _numCols + r] = 1;
      }
      else {
        matrix_array[c * _numCols + r] = 0;
      }
    }
    pinMode(_colPins[c], INPUT);
  }

  if (_keepActive == true) {
    enableCols();
  }
};

// -------------------------------------------------------------------
// Private methods
// -------------------------------------------------------------------
void Keypad4495::disableCols() {
  int i;
  for (i=0; i < _numCols; i++) {
    pinMode(_colPins[i], INPUT);
  }

};

void Keypad4495::enableCols() {
  int i;
  for (i=0; i < _numCols; i++) {
    pinMode(_colPins[i], OUTPUT);
  }
};
