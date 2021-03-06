/*
==========================================================
NAME:			CURSOR.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			Cursor / Mouse operations definition file
Last Updated:	October 6, 2018
==========================================================
*/

#include "P_TABLE\\LIB\\CDEF.H"

#if !defined(__CURSOR_H)
#define __CURSOR_H

union REGS i, o;

class Mouse
{
public:
	static byte Button;
	static int X, Y;

	static int Initialize();

	static void Show();
	static void Hide();

	static byte Refresh();
};

byte Mouse::Button = 0;
int Mouse::X = 0;
int Mouse::Y = 0;

int Mouse::Initialize()
{
	i.x.ax = 0;
	int86(0X33, &i, &o);
	return (o.x.ax);
}

void Mouse::Show()
{
	i.x.ax = 1;
	int86(0x33, &i, &o);
}

void Mouse::Hide()
{
	i.x.ax = 2;
	int86(0x33, &i, &o);
}

byte Mouse::Refresh()
{
	i.x.ax = 3;
	int86(0X33, &i, &o);

	X = o.x.cx;
	Y = o.x.dx;
	return (Button = (byte)o.x.bx);
}

#endif