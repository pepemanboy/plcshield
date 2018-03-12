# Plcshield

# Software

Plcshield.h is a library for Arduino Ethernet PLC Shield.

## Installation

Download the folder plcshield and move it to your Arduino libraries folder (eg. C:\Users\ExampleUser\Documents\Arduino\libraries)

## Public functions

### void plc_setup()

Description:
This function must be called prior to any other call to this library.
It initializes the inputs and outputs (outputs are initialized to NC).
LCD is initialized and it displays a sample text.

Parameters: Nothing

Returns: Nothing

### uint8_t plc_digitalWrite(uint8_t digital_output, bool level)

Description:
Digital write to a PLC output.

Parameters:

digital_output - Digital output number [1 .. 6]

level - Desired logical level in output [bool]

### bool plc_digitalRead(uint8_t digital_input)

Description:
Digital read from a PLC input.

Parameters:

digital_input - Digital input number [1 .. 6]

Returns: Logic level in input [bool] or -1 if the argument given is not in the range 1 to 6.

### bool plc_buttonRead(uint8_t button)

Description:
Read a button from the PLC.

Parameters:

button - Button number [1 .. 3]

Returns: Logic level in button [bool] or -1 if the argument given is not in the range 1 to 3.

### int plc_analogRead(uint8_t analog_input)

Description:
Read an analog input from the PLC.

Parameters:

analog_input - Analog input number [1 .. 6]

Returns: 10 bit ADC value [0 .. 1024] or -1 if the argument given is not in the range 1 to 6.

## Example
```
#import "plcshield.h"

void setup(){
  plc_setup(); // Setup PLC library
}

void loop(){
  int a = plc_digitalRead(1); // Read PLC digital input 1
  int b = plc_analogRead(5); // Read PLC analog input 5
  plc_digitalWrite(1,a); // Write PLC digital output 1 to the level read in a
}
```

## Using LCD
The library used for LCD control is (https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)

## LCD Functions

## Example

```
#import "plcshield.h"
void setup()
{
  plc_setup(); // Initialize PLC Library
  
  plc_lcd.clear(); // Clear the screen 
  
  plc_lcd.setCursor(0,0); // Set the cursor in Column 0, Row 0 of the LCD
  
  plc_lcd.print("Cirotec"); // Print this text where the cursor is
  
  plc_lcd.setCursor(0,1); // Set the cursor in Column 0, Row 1 of the LCD
  
  plc_lcd.print("Automation"); // Print this text where the cursor is
}


void loop()
{
}
```
