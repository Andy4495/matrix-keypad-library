/* Library to interface with a matrixed keypad.
   There are already numerous other libraries available. I created this on as
   a simpler alternative, both from a usage standpoint and for ease of
   understanding the code.

   https://github.com/Andy4495/matrix-keypad-library
*/
/* Version History
   1.0.0    03/05/2019  A.T.   Original
   1.0.1    04/05/2019  A.T.   Added support for "Keep Active" mode

*/
#ifndef KEYPAD4495_LIBRARY
#define KEYPAD4495_LIBRARY

#include "Arduino.h"

class Keypad4495 {
public:
  enum {NO_KEY=0, NO_PIN=255};
  Keypad4495(char *userKeymap, byte *rowPins, byte *colPins, byte numRows, byte numCols, bool keepActive=false);
  char waitForKey();          // Blocking call -- waits for a keypress before returning
  char getKey();              // Non-blocking. Returns first key found in scan. Returns NO_KEY if no keys are pressed
  void getMatrixStatus(byte* matrix_array); // Scans full matrix and sets corresponding element to 1 if that key is pressed

private:
  char *_keymap;
  byte *_rowPins;
  byte *_colPins;
  byte _numRows;
  byte _numCols;
  bool _keepActive;
  void disableCols();
  void enableCols();
};

#endif
