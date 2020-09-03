/*
==========================================================
NAME:			ELEM_BTN.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			Element Button -> Specific Tool Definition Optimized for Low Resource usage
Last Updated:	October 14, 2018
==========================================================
*/

#include <graphics.h>
#include <string.h>
#include <stdlib.h>

#include "P_TABLE\\LIB\\CDEF.H"
#include "P_TABLE\\LIB\\POINT2D.H"
#include "P_TABLE\\LIB\\GEL.H"
#include "P_TABLE\\LIB\\CURSOR.H"
#include "P_TABLE\\LIB\\ELEMENT.H"

#if !defined(__ELEM_BTN_H)
#define __ELEM_BTN_H

extern void ShowElement(char*);

class ElementButton
{

	bool PreviousMouseHoverState;

	public:

	byte Z;
	char X[4];
    char _z[4];

	byte BorderColor;

	Point2D Midpoint;

	void Initialize(Element *element);

	ElementButton()
	{
		Z = 0;
	}

	ElementButton(byte z)
	{
		Initialize(&Files::GetElement(z));
	}

	ElementButton(Element element)
	{
		Initialize(&element);
	}

	ElementButton(Element *element)
	{
		Initialize(element);
	}

	bool Draw(bool AutoHideMouse = false)
	{
		if (!Z)
			return MouseHover();

		if (AutoHideMouse)
			Mouse::Hide();

		GraphicsEngine::FilledRectangle(Midpoint.X - 17, Midpoint.Y - 20, Midpoint.X + 17, Midpoint.Y + 20, MouseHover() ? DARKGRAY : LIGHTGRAY, BorderColor);

		setcolor(LIGHTGRAY);
		rectangle(Midpoint.X - 17, Midpoint.Y - 20, Midpoint.X + 17, Midpoint.Y + 20);

		GraphicsEngine::DrawLine(Point2D(Midpoint.X - 16, Midpoint.Y + 19), Point2D(Midpoint.X + 16, Midpoint.Y + 19), 2, BorderColor);

		settextjustify(CENTER_TEXT, CENTER_TEXT);
		settextstyle(6, HORIZ_DIR, 1);
		setcolor(MouseHover() ? WHITE : DARKGRAY);
		outtextxy(((Midpoint.X + 17) + (Midpoint.X - 17)) / 2, (((Midpoint.Y + 20) + (Midpoint.Y - 20)) / 2) - 8, X);

		settextstyle(0, HORIZ_DIR, 1);
		setcolor(MouseHover() ? LIGHTGRAY : DARKGRAY);
		outtextxy(((Midpoint.X + 17) + (Midpoint.X - 17)) / 2, Midpoint.Y + 14, _z);

		if (AutoHideMouse)
			Mouse::Show();

		return MouseHover();
	}

	bool MouseHover()
	{
		return ((Mouse::X < (Midpoint.X + 17)) && (Mouse::X > (Midpoint.X - 17)) && (Mouse::Y < (Midpoint.Y + 20)) && (Mouse::Y > (Midpoint.Y - 20)));
	}

	bool ElementClicked()
	{
		if (MouseHover() != PreviousMouseHoverState)
			PreviousMouseHoverState = Draw(true);

		if (Mouse::Button && MouseHover())
		{
			ShowElement((char*)this);
			return true;
		}
		return false;
	}

};

void ElementButton::Initialize(Element *element)
{
	Z = element -> Z(); // commenting this code makes app highly unstable
	strcpy(X, element -> X);
	itoa(Z, _z, 10);

	Midpoint = ((element -> Group()) ? Point2D((element -> Group() * 34) - 3, (element -> Period() * 43) + 30) : Point2D(((Z - (element -> Period() == 6 ? 54 : 86)) * 34) - 3, ((element -> Period() + 3) * 43) + 5));

	switch (element -> Category)
	{
		case Element::Other_NonMetals:		BorderColor = LIGHTGREEN;	break;
		case Element::NobleGases:			BorderColor = MAGENTA;		break;
		case Element::AlkaliMetals:			BorderColor = RED;			break;
		case Element::AlkalineEarthMetals:	BorderColor = LIGHTBLUE;	break;
		case Element::TransitionMetals:		BorderColor = CYAN;			break;
		case Element::PostTransitionMetals:	BorderColor = BLUE;			break;
		case Element::Metalloids:			BorderColor = YELLOW;		break;
		case Element::Halogens:				BorderColor = GREEN;		break;
		case Element::Lanthanoids:			BorderColor = LIGHTRED;		break;
		case Element::Actinoids:			BorderColor = BROWN;		break;
		case Element::SuperActinoid:		BorderColor = WHITE;		break;
		default:							BorderColor = WHITE;		break;
	}

	PreviousMouseHoverState = false;

}

#endif