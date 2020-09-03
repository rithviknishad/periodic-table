/*
==========================================================
NAME:			QTYDEF.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			Quantities Definitions
Last Updated:	October 12, 2018
==========================================================
*/

#include "P_TABLE\\LIB\\CDEF.H"

#if !defined(__QTYDEF_H)
#define __QTYDEF_H

class Temperature
{

protected:
	float kelvin;

public:
	enum Units
	{
		Kelvin,
		Celsius,
		Fahrenheit
	};

	Temperature()
	{
		SetValue(0, Kelvin);
	}

	Temperature(float value, Units unit)
	{
		SetValue(value, unit);
	}

	Temperature(const Temperature &temperature)
	{
		kelvin = temperature.kelvin;
	}

	float SetValue(float value, Units unit);

	float GetValue(Units unit);
};

float Temperature::SetValue(float value, Temperature::Units unit)
{
	switch (unit)
	{
	case Temperature::Kelvin:
		kelvin = value;
		break;

	case Temperature::Celsius:
		kelvin = 273.15 + value;
		break;

	case Temperature::Fahrenheit:
		SetValue((value - 32) / 1.8, Celsius);
		break;
	}

	return kelvin;
}

float Temperature::GetValue(Temperature::Units unit)
{
	switch (unit)
	{
	case Temperature::Kelvin:
		return kelvin;

	case Temperature::Celsius:
		return kelvin + 273.15;

	case Temperature::Fahrenheit:
		return (1.8 * GetValue(Celsius)) + 32;
	}

	return 0;
}

class Duration
{

public:
	enum Units
	{
		Nanoseconds = 0,
		Microseconds,
		Milliseconds,
		Seconds,
		Minutes,
		Hours,
		Days,
		Years,
		Infinite
	};

	float Value;
	byte Unit;

	Duration()
	{
		Set(0, Seconds);
	}

	Duration(float value, Units unit)
	{
		Set(value, unit);
	}

	Duration(Units unit)
	{
		Set(0, unit);
	}

	void Set(float value, Units unit)
	{
		Value = value;
		Unit = unit;
	}
};

#endif