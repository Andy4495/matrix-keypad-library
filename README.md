Keypad4495 Library
====================

This library is designed to <<< simple to use, simple to understand>>>

Does not keep any state information -- each call to check the keypad is independent of any previous calls. The library does not currently support debouncing, that needs to be handled in the sketch itself (see examples folder for a debouncing implementation).

Note the name of the include file is "Keypad4495.h", to avoid name conflicts with other existing keypad libraries.

Specifics on usage with BOOST-IR boosterpack -- conflict with hardware serial TX/RX.

Explain how to use example program to figure out the key matrix array.

Usage
-----

Include the header file:

    #include "Keypad4495.h"

Define the size of the keypad (rows and columns) and array storage for the keymap, row pins, and column pins used by keypad object. Note that the array storage needs to be in-scope for the entire time that you use the keypad object:

    #define NUM_ROWS 4
    #define NUM_COLS 4
    byte rowPins[NUM_ROWS] = {13, 12, 11, 5};
    byte colPins[NUM_COLS] = {2, 3, 6, 8};
    char keymap[] = { 'D', 'C', 'B', 'A', 'R', '9', '6', '3', '0', '8', '5', '2', 'L', '7', '4', '1' };

Use the constructor to create the keypad object:

    Keypad4495 myKeypad(keymap, rowPins, colPins, NUM_ROWS, NUM_COLS);

Once you have created a Keypad object, the following methods are available:

    char waitForKey();          // Blocking call -- waits for a keypress before returning
    char getKey();              // Non-blocking. Returns first key found in scan. Returns NO_KEY if no keys are pressed
    void getMatrixStatus(byte* matrix_array); // Scans full matrix and sets corresponding element to 1 if that key is pressed


References
----------
+ [Reference](https:)
+ BOOST-IR
