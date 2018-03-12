/*
		plcshield.h - Library for PLC Shield.
		Created by Pepe Melendez, March 10, 2018.
*/

#ifndef PLCSHIELD_H
#define PLCSHIELD_H

/* External libraries */
#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* LCD Instance*/
LiquidCrystal_I2C plc_lcd(0x3F,16,2);

/* MUX propagation delay (us) */
#define plc_MUX_DELAY 1

/* Error codes */
typedef enum
{
	plc_Ok = 0, ///< No error
	plc_Error = -1 ///< Generic error
}plc_errors;

/* MUX pins */
typedef enum
{
	plc_MUX_SIGNAL = A5, ///< Arduino pin used for MUX output

	plc_MUX_SELECT_0 = 3, ///< Arduino pin used for MUX select 0
	plc_MUX_SELECT_1 = 2, ///< Arduino pin used for MUX select 1
	plc_MUX_SELECT_2 = 1, ///< Arduino pin used for MUX select 2
	plc_MUX_SELECT_3 = 0, ///< Arduino pin used for MUX select 3

	plc_MUX_ENABLE = 5,
}plc_muxe;

/* Digital output pins */
typedef enum
{
	plc_DO1 = A0, ///< Arduino pin used for digital output 1
	plc_DO2 = A1, ///< Arduino pin used for digital output 2
	plc_DO3 = A2, ///< Arduino pin used for digital output 3
	plc_DO4 = A3, ///< Arduino pin used for digital output 4
	plc_DO5 = A4, ///< Arduino pin used for digital output 5
	plc_DO6 = 6 ///< Arduino pin used for digital output 6
}plc_doe;

/* Digital input multiplexer pins */
typedef enum
{
	plc_DI1 = 0, ///< MUX pin used for digital input 1
	plc_DI2 = 1, ///< MUX pin used for digital input 2
	plc_DI3 = 2, ///< MUX pin used for digital input 3
	plc_DI4 = 3, ///< MUX pin used for digital input 4
	plc_DI5 = 4, ///< MUX pin used for digital input 5
	plc_DI6 = 5 ///< MUX pin used for digital input 6
}plc_die;

/* Analog input multiplexer pins */
typedef enum
{
	plc_AI1 = 15, ///< MUX pin used for analog input 1
	plc_AI2 = 14, ///< MUX pin used for analog input 2
	plc_AI3 = 13, ///< MUX pin used for analog input 3
	plc_AI4 = 12, ///< MUX pin used for analog input 4
	plc_AI5 = 11, ///< MUX pin used for analog input 5
	plc_AI6 = 10 ///< MUX pin used for analog input 6
}plc_aie;

/** Buttons */
typedef enum
{
	plc_B1 = 7, ///< MUX pin used for button 1
	plc_B2 = 8, ///< MUX pin used for button 2
	plc_B3 = 9, ///< MUX pin used for button 3
}plc_be;

/* Private functions */

/** Map digital output number to arduino pin
@param d digital output number
@param p arduino pin placeholder
@return Error code
*/
static uint8_t _doToPin(uint8_t d, uint8_t *p)
{
	switch(d)
	{
	case 1: *p = plc_DO1; break;
	case 2: *p = plc_DO2; break;
	case 3: *p = plc_DO3; break;
	case 4: *p = plc_DO4; break;
	case 5: *p = plc_DO5; break;
	case 6: *p = plc_DO6; break;
	default: return plc_Error;
	}
	return plc_Ok;
}

/** Map digital input number to MUX pin
@param i digital input number
@param m MUX pin placeholder
@return Error code
*/
static uint8_t _diToMux(uint8_t i, uint8_t *m)
{
	switch(i)
	{
	case 1: *m = plc_DI1; break;
	case 2: *m = plc_DI2; break;
	case 3: *m = plc_DI3; break;
	case 4: *m = plc_DI4; break;
	case 5: *m = plc_DI5; break;
	case 6: *m = plc_DI6; break;
	default: return plc_Error;
	}
	return plc_Ok;
}

/** Map analog input number to MUX pin
@param i analog input number
@param m MUX pin placeholder
@return Error code
*/
static uint8_t _aiToMux(uint8_t i, uint8_t *m)
{
	switch(i)
	{
	case 1: *m = plc_AI1; break;
	case 2: *m = plc_AI2; break;
	case 3: *m = plc_AI3; break;
	case 4: *m = plc_AI4; break;
	case 5: *m = plc_AI5; break;
	case 6: *m = plc_AI6; break;
	default: return plc_Error;
	}
	return plc_Ok;
}

/** Map button number to MUX pin
@param b button number
@param m MUX pin placeholder
@return Error code
*/
static uint8_t _buttonToMux(uint8_t b, uint8_t *m)
{
	switch(b)
	{
	case 1: *m = plc_B1; break;
	case 2: *m = plc_B2; break;
	case 3: *m = plc_B3; break;
	default: return plc_Error;
	}
	return plc_Ok;
}

/** Select MUX input
@param n desired input
@return Error code
*/
static uint8_t _muxSelect(uint8_t n)
{
	if (n < 0 || n > 15)
		return plc_Error;

	digitalWrite(plc_MUX_SELECT_0, n & 0x01);
	digitalWrite(plc_MUX_SELECT_1, n & 0x02);
	digitalWrite(plc_MUX_SELECT_2, n & 0x04);
	digitalWrite(plc_MUX_SELECT_3, n & 0x08);

	delayMicroseconds(plc_MUX_DELAY);

	return plc_Ok;
}

/** Initialize LCD
@param Nothing
@return Nothing
*/
static void _setupLcd(void)
{
	// Initialize LCD object
	plc_lcd.init();

	// Turn on background light
	plc_lcd.backlight();

	// Print mockupt text
	plc_lcd.setCursor(0, 0);
	plc_lcd.print("PLC Shield");
}

/* Public functions */

/** Setup PLC Shield. Configs IO, enables MUX, and displays some text in LCD. Call it at the begining.
@param Nothing
@return Nothing
*/
void plc_setup()
{
	// Configure I/O
	pinMode(plc_MUX_SIGNAL, INPUT);
	pinMode(plc_DO1, OUTPUT);
	pinMode(plc_DO2, OUTPUT);
	pinMode(plc_DO3, OUTPUT);
	pinMode(plc_DO4, OUTPUT);
	pinMode(plc_DO5, OUTPUT);
	pinMode(plc_DO6, OUTPUT);
	pinMode(plc_MUX_ENABLE, OUTPUT);

	// Enable MUX operation
	digitalWrite(plc_MUX_ENABLE, LOW);

	// Configure LCD
	_setupLcd();
}

/** Digital write
@param digital_output digital output number [1..6]
@param level desired logical level in output [0..1]
@return Error code
*/
uint8_t plc_digitalWrite(uint8_t digital_output, uint8_t level)
{
	uint8_t pin;

	if (_doToPin(digital_output, &pin) != plc_Ok)
		return plc_Error;

	digitalWrite(pin, level);

	return plc_Ok;
}

/** Digital read
@param digital_input digital input number [1..6]
@return logic level in input [0..1] or plc_Error if bad argument
*/
uint8_t plc_digitalRead(uint8_t digital_input)
{
	uint8_t mux;

	if (_diToMux(digital_input, &mux) != plc_Ok)
		return plc_Error;

	if(_muxSelect(mux) != plc_Ok)
		return plc_Error;

	return !digitalRead(plc_MUX_SIGNAL); // Correct logic
}

/** Button read
@param button button number [1..3]
@return logic level in button [0..1] or plc_Error if bad argument
*/
uint8_t plc_buttonRead(uint8_t button)
{
	uint8_t mux;

	if (_buttonToMux(button, &mux) != plc_Ok)
		return plc_Error;

	if(_muxSelect(mux) != plc_Ok)
		return plc_Error;

	return !digitalRead(plc_MUX_SIGNAL); // Correct logic
}

/** Analog read
@param analog_input analog input number [1..6]
@return adc value [0..1024] or plc_Error if bad argument
*/
int plc_analogRead(uint8_t analog_input)
{
	uint8_t mux;

	if (_aiToMux(analog_input, &mux) != plc_Ok)
		return plc_Error;

	if(_muxSelect(mux) != plc_Ok)
		return plc_Error;

	return analogRead(plc_MUX_SIGNAL);
}

#endif // PLCSHIELD_H
