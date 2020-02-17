# LCD2x16
C library code for 2x16 LCDs.

General info (took from lcd_lib.h file):

```text
A typical LCD has the following pinouts: 

    _______________________________ VSS (Ground)
   |  _____________________________ VDD (+5V Power)
   | |  ___________________________ VE (Contrast)
   | | |  _________________________ Register Select
   | | | |  _______________________ Read/Write
   | | | | |  _____________________ Enable
   | | | | | |  ___________________ Data #0
   | | | | | | |   ________________ Data #1
   | | | | | | | |  _______________ Data #2         
   | | | | | | | | |  _____________ Data #3
   | | | | | | | | | |  ___________ Data #4
   | | | | | | | | | | |  _________ Data #5
   | | | | | | | | | | | |  _______ Data #6
   | | | | | | | | | | | | |  _____ Data #7
   | | | | | | | | | | | | | |  ___ LED POSITIVE
   | | | | | | | | | | | | | | |  _ LED NEGATIVE
   | | | | | | | | | | | | | | | |
   | | | | | | | | | | | | | | | |
 __|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|___________________
|+ 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0                  +|
|  ________________________________________________  |
|  ________________________________________________  |
|  ____________________  L C D  ___________________  |
|  ________________________________________________  |
|  ________________________________________________  |
|+__________________________________________________+|

(For comprehensive info, search up "Hitachi HD44780 LCD Datasheet", HD44780 is the driver that is typically used in LCDs)

What you would do with the above pinouts, is that VSS gets connected to ground and VDD to +5V of the power supply. VE pin is used to adjust contrast. Connect it to +5V to get the maximum contrast or to ground to get the minimum contrast. What you might want to do is to use a potentiometer in a voltage divider circuit to get an adjustable contrast with the potentiometer.
The next 3 pins, namely Register Select, Read/Write and Enable should wire up to 3 pins of our microcontroller (in output mode).
these three pins are used by the LCD to be inform on what to do with the data that is passed to it (via next 8 data pins).
Next 8/4 pins (depending on what mode you want to use the LCD), get connected to another 8/4 pins of the microcontroller. These pins are used by the LCD to pass the actual data or command to the LCD.
Last two pins are the backlight LEDs, which your LCD may use or not. 

After the wirings, we can use the following instruction code to send commands to our LCD.

Instruction Table is as follows;
  Instruction            |  RS  |  R/W  |  DB7  |  DB6  |  DB5  |  DB4  |  DB3  |  DB2  |  DB1  |  DB0  |  Description |
  Clear Display          |   0  |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   1   |      *1      |
  Return Home            |   0  |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   1   |   X   |      *2      | 
  Entry Set mode         |   0  |   0   |   0   |   0   |   0   |   0   |   0   |   1   |  I/D  |   S   |      *3      |
  Display ON/OFF         |   0  |   0   |   0   |   0   |   0   |   0   |   1   |   D   |   C   |   B   |      *4      |
  Cursor/display Shift   |   0  |   0   |   0   |   0   |   0   |   1   |  S/C  |  R/L  |   X   |   X   |      *5      |
  Function Set           |   0  |   0   |   0   |   0   |   1   |  DL   |   N   |   F   |   X   |   X   |      *6      |
  Set CGRAM Addr         |   0  |   0   |   0   |   1   |  AC5  |  AC4  |  AC3  |  AC2  |  AC1  |  AC0  |      *7      | 
  Set DDRAM Addr         |   0  |   0   |   1   |  AC6  |  AC5  |  AC4  |  AC3  |  AC2  |  AC1  |  AC0  |      *8      |
  Read Busy flag/Addr    |   0  |   1   |   BF  |  AC6  |  AC5  |  AC4  |  AC3  |  AC2  |  AC1  |  AC0  |      *9      |
  Write Data to Address  |   1  |   0   |   D7  |   D6  |   D5  |   D4  |   D3  |   D2  |   D1  |   D0  |      *10     |
  Read Data from Address |   0  |   1   |   D7  |   D6  |   D5  |   D4  |   D3  |   D2  |   D1  |   D0  |      *11     |

For example, assuming PORTB is the 8/4 bit data port, following line:

PORTB = 0x01;

Outputs '0000 0001' on PORTB which executes clearscreen command on the LCD. Something to note here is that
to make that command execute, the Enable Signal should be triggered. To do so, simply set it to off, and with 
a little delay set it on again. This procedure can be done with the following lines (assuming PORTC is the control port):

PORTC = (0<<0)|(0<<1)|(1<<2);
_delay_ms(1);
PORTC = (0<<0)|(0<<1)|(0<<2);

Often macros are defining instead of using the actual pin number in shifiting section. That is:

#define rs PINC0
#define rw PINC1
#define en PINC2

Consequently, Switching on and off the Enable signal could be replaced with these commands instead:

PORTC = (0<<0)|(0<<1)|(1<<2);
_delay_ms(1);
PORTC = (0<<0)|(0<<1)|(0<<2);

```