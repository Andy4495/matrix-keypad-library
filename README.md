Keypad4495 Library
====================

This library is designed to be simple-to-use from a sketch-writing perspective. It is also desgined to have a simple-to-understand implementation so that others can easily understand how it works and extend it if desired.

The keypad object used by the library does not keep any state information related to keypresses -- each call to get a key status is independent of any previous calls.

To avoid naming conflicts with other existing keypad libraries, the keypad object type is `Keypad4495` and the include file is `Keypad4495.h`

Usage
-----

*See the example sketch in the `examples` folder.*

When deciding on which pins to use for rows and columns, this library assumes that the columns are the `OUTPUT` pins and the rows will be configured as `INPUT_PULLUP`.

In the default operation mode, the column lines are only configured as `OUTPUT` when that column is being scanned; they are configured as `INPUT` at all other times.

There is also a "Keep Active" mode where the column lines are set to `OUTPUT` at all times. This mode can be useful in certain situations where the column lines are multiplexed with some other output lines (e.g., sharing the lines with another parallel interface).

The row lines are configured as `INPUT_PULLUP` as soon as the constructor is called.

First, **include the header file**:

    #include "Keypad4495.h"

Next, **define the row size and column size** of the keypad, and then **define array storage for the keymap, row pins, and column pins** used by keypad object. Note that the array storage needs to be in-scope for the entire time that you use the keypad object. So either create the arrays as global variables, or create the arrays within the same code block that the keypad object is created. For example (representing a 4x4 keypad):

    #define NUM_ROWS 4
    #define NUM_COLS 4
    byte rowPins[NUM_ROWS] = {13, 12, 11, 5};
    byte colPins[NUM_COLS] = {2, 3, 6, 8};
    char keymap[NUM_COLS * NUM_ROWS] = { 'D', 'C', 'B', 'A', 'R', '9', '6', '3', '0', '8', '5', '2', 'L', '7', '4', '1' };

`keymap` is an array of characters that represents the buttons on your keypad. The order of the characters in the array should be in the same order that they are scanned. The keys are scanned one column at a time, and then the rows within that column. Using the values in the example above, the keys are scanned as follows:

    Scan     keymap      Column    Row     Keymap
    Order   Subscript     Pin      Pin    Character
    -----   ---------    ------    ---    ---------
     1st        0          2       13        'D'
     2nd        1          2       12        'C'
     3rd        2          2       11        'B'
     4th        3          2        5        'A'
     5th        4          3       13        'R'
     6th        5          3       12        '9'
     7th        6          3       11        '6'
     8th        7          3        5        '3'
     9th        8          6       13        '0'
    10th        9          6       12        '8'
    11th       10          6       11        '5'
    12th       11          6        5        '2'
    13th       12          8       13        'L'
    14th       13          8       12        '7'
    15th       14          8       11        '4'
    16th       15          8        5        '1'


Then, **use the constructor to create the keypad object**, using the arrays and size values defined above. The first form of the constructor is for the default mode where the column lines are only set to `OUTPUT` when the keypad is being scanned:

    Keypad4495 myKeypad(keymap, rowPins, colPins, NUM_ROWS, NUM_COLS);

The alternate form of the constructor is used for "Keep Active" mode where the column lines are set to `OUTPUT` at all times. This mode may be used in cases where the column lines are shared by other devices. Note that the actual pin values are not retained, just the `OUTPUT` setting:

    Keypad4495 myKeypad(keymap, rowPins, colPins, NUM_ROWS, NUM_COLS, true);

And finally, **to get a keypress, use either `waitForKey()` or `getKey()`**.

For example, using the keypad object defined above:

    char c;
    c = myKeypad.waitForKey();      // Blocking call
    c = myKeypad.getKey();          // Non-blocking call

`waitForKey()` is a blocking call -- it waits for a keypress before returning. Your sketch will therefore do nothing (besides interrupts) until a key is pressed.

`getKey()` is non-blocking. If a key is currently pressed, it will return the character defined by your keymap representing that key. If nothing is pressed, then it will return `Keypad4495::NO_KEY`.

Both of the above methods will return a maximum of one key (the last one found while scanning the keypad matrix).

Alternatively, **if you want to detect multiple keys pressed at the same time**, or use a more elaborate key detection routine (possibly as part of a debouncing algorithm), then **use `getMatrixStatus()`**. This takes as a parameter an array of bytes that is equal to the size of the matrix (i.e., NUM_ROWS * NUM_COLS). Upon return, it will have set the corresponding element of the array to `1` if that key is pressed and `0` if it is not pressed:

    void getMatrixStatus(byte* matrix_array);

Debouncing
----------

The library includes methods to debounce the button presses. The default debounce time is 20 ms when the keypad object is created. This can be changed with the `setDebounce(uint8_t debounce_time)` method. Values from 0 to 255 ms are supported.

To have the library debounce the buttons, use either of the following methods:

`waitForKeyWithDebounce()` works the same as `waitForKey()`, except it debounces the button before returning the key value. Just like `waitForKey()`, it is a blocking call and will not return until it detects and debounces a button. Debouncing includes waiting for the key to be released after the debounce time.

`getKeyWithDebounce()` works the same as `getKey()`, except that if it detects a key press, then it waits to debounce the key before returning. If no key is pressed, or the key does not stay pressed during the debounce time, then `Keypad4495::NO_KEY` is returned. If no keys are pressed when the method is called, then it is non-blocking. If a key is pressed, then the method blocks until the debounce routine is completed.

Using the Texas Instruments BOOST-IR BoosterPack
------------------------------------------------

This library was originally designed for a project using TI's [BOOST-IR][1] BoosterPack. However, it is written generally enough that it should work with any standard matrix keypad.

The BOOST-IR keypad uses BoosterPack pin 2 for one of the column scan pins. Pin 2 is also the Hardware Serial RX pin on some LaunchPads (e.g. MSP-EXP430FR4133, MSP-EXP430FR2433, and MSP-EXP430FR2533G2). When using those LaunchPads, it is necessary to disconnect the RXD jumper from the emulation section of the LaunchPad for proper operation of the BOOST-IR keypad.

The BOOST-IR also uses the Hardware Serial TX pin for hardware IR modulation, so the TX pin needs to be disconnected from the emulation section of the LaunchPad when using the hardware IR modulation functionality of the board.

References
----------
+ [Keypad library][2] from Arduino Playground
+ Texas Instruments [BOOST-IR][1] BoosterPack

License
-------
The software and other files in this repository are released under what is commonly called the [MIT License][100]. See the file [`LICENSE.txt`][101] in this repository.

[1]:http://www.ti.com/tool/BOOST-IR
[2]:http://playground.arduino.cc/Code/Keypad
[100]: https://choosealicense.com/licenses/mit/
[101]: ./LICENSE.txt
