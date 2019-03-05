/* Library to interface with a matrixed keypad.
   There are already numerous other libraries available. I created this on as
   a simpler alternative, both from a usage standpoint and for ease of
   understanding the code.

   http://gitlab.com/Andy4495/Keypad4495
*/
/* Version History
   1.0.0    03/05/2019  A.T.   Original

*/
#include "Keypad4495.h"

Keypad4495::Keypad4495(char *userKeymap, byte *rowPins, byte *colPins, byte numRows, byte numCols){
  _keymap = userKeymap;
  _rowPins = rowPins;
  _colPins = colPins;
  _numRows = numRows;
  _numCols = numCols;

  int i;

  for (i = 0; i < _numRows; i++) {
    pinMode(_rowPins[i], INPUT_PULLUP);
  }

  for (i = 0; i < _numCols; i++) {
    digitalWrite(_colPins[i], LOW);
    pinMode(_colPins[i], INPUT);
  }
};

// Blocking call -- waits for a keypress before returning
char Keypad4495::waitForKey() {
  bool keypress = false;
  char key;
  int c, r;

  while (!keypress) {
    for (c = 0; c < _numCols; c++) {
      pinMode(_colPins[c], OUTPUT);
      for (r = 0; r < _numRows; r++) {
        if (digitalRead(_rowPins[r]) == LOW) {
          key = _keymap[c * _numCols + r];
          keypress = true;
        }
      }
      pinMode(_colPins[c], INPUT);
    }
  }
  return(key);
};

// Non-blocking. Returns first key found in scan. Returns NO_KEY if no keys are pressed
char Keypad4495::getKey() {
  char key = NO_KEY;
  int c, r;

  for (c = 0; c < _numCols; c++) {
    pinMode(_colPins[c], OUTPUT);
    for (r = 0; r < _numRows; r++) {
      if (digitalRead(_rowPins[r]) == LOW) {
        key = _keymap[c * _numCols + r];
      }
    }
    pinMode(_colPins[c], INPUT);
  }
  return(key);
};

// Scans full matrix and sets corresponding element to 1 if that key is pressed
void Keypad4495::getMatrixStatus(byte* matrix_array) {
  int c, r;

  for (c = 0; c < _numCols; c++) {
    pinMode(_colPins[c], OUTPUT);
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
};
