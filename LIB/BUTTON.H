/*
==========================================================
NAME:			BUTTON.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			Button definition file
Last Updated:	October 18, 2018
==========================================================
*/

#include <graphics.h>
#include <string.h>

#include "P_TABLE\\LIB\\GEL.H"
#include "P_TABLE\\LIB\\CDEF.H"
#include "P_TABLE\\LIB\\POINT2D.H"

#if !defined(__BUTTON_H)
#define __BUTTON_H

void NotImplementedException() {}

class Button
{

	bool PreviousMouseHoverState;

	void Initialize()
	{
		ClickEvent = NotImplementedException;
		Enabled = true;
		PreviousMouseHoverState = MouseHover();
	}

public:
	char Text[32];

	Point2D A, B;

	byte BackColor;
	byte BackColor_Hovered;
	byte BorderColor;
	byte BorderColor_Hovered;
	byte ForeColor;
	byte ForeColor_Hovered;

	bool Enabled;

	void (*ClickEvent)();

	char *SetText(const char text[]);

	void SetBounds(Point2D &a, Point2D &b)
	{
		A.X = a.X;
		A.Y = a.Y;
		B.X = b.X;
		B.Y = b.Y;
	}

	void SetPositionAndSize(Size2D &size, Point2D &a)
	{
		A = a;
		B = Point2D(a.X + size.Width, a.Y + size.Height);
	}

	void SetPositionAndSize(Point2D &midpoint, Size2D &size)
	{
		A = Point2D(midpoint.X - (size.Width / 2), midpoint.Y - (size.Height / 2));
		B = Point2D(midpoint.X + (size.Width / 2), midpoint.Y + (size.Height / 2));
	}

	bool MouseHover()
	{
		return ((Mouse::X < B.X) && (Mouse::X > A.X) && (Mouse::Y < B.Y) && (Mouse::Y > A.Y));
	}

	bool MouseClicked()
	{
		if (MouseHover() != PreviousMouseHoverState)
			Draw();

		if (Mouse::Button && MouseHover())
		{
			if (Enabled)
				ClickEvent();
			return true;
		}
		return false;
	}

	void Draw(bool AutoMouseHide = true, byte TextJustify = CENTER_TEXT)
	{
		if (AutoMouseHide)
			Mouse::Hide();

		GraphicsEngine::FilledRectangle(A.X, A.Y, B.X, B.Y, (MouseHover() && Enabled) ? BackColor_Hovered : BackColor, (MouseHover() && Enabled) ? BorderColor_Hovered : BorderColor);

		settextjustify(TextJustify, CENTER_TEXT);
		settextstyle(0, HORIZ_DIR, 1);

		setcolor(MouseHover() ? ForeColor_Hovered : ForeColor);
		outtextxy((B.X + A.X) / 2, (B.Y + A.Y) / 2, Text);

		if (AutoMouseHide)
			Mouse::Show();

		PreviousMouseHoverState = MouseHover();
	}

	Button()
	{
		Initialize();

		BackColor = LIGHTGRAY;
		BorderColor = DARKGRAY;

		BackColor_Hovered = DARKGRAY;
		BorderColor_Hovered = DARKGRAY;

		ForeColor = DARKGRAY;
		ForeColor_Hovered = WHITE;
	}

	Button(const char text[], byte backcolor, byte forecolor)
	{
		Initialize();

		SetText(text);

		BackColor = backcolor;
		BorderColor = BackColor;
		ForeColor = forecolor;

		BackColor_Hovered = BackColor;
		BorderColor_Hovered = BorderColor;
		ForeColor_Hovered = ForeColor;
	}

	Button(Point2D midpoint, Size2D size, const char text[], byte backcolor, byte backcolor_hovered, byte bordercolor, byte bordercolor_hovered, byte forecolor, byte forecolor_hovered, void (*clickevent)() = NotImplementedException)
	{
		Initialize();

		SetPositionAndSize(midpoint, size);
		SetText(text);

		BackColor = backcolor;
		BackColor_Hovered = backcolor_hovered;

		BorderColor = bordercolor;
		BorderColor_Hovered = bordercolor_hovered;

		ForeColor = forecolor;
		ForeColor_Hovered = forecolor_hovered;

		ClickEvent = clickevent;
	}

	~Button()
	{
		// if (Text != NULL)
		// 	delete Text;

		// if (Text_GC != NULL)
		// 	delete Text_GC;
	}
};

char *Button::SetText(const char text[])
{
	strcpy(Text, text);
	return Text;
}

class PropertyButton
{

	bool PreviousMouseHoverState;

	void Initialize()
	{
		//Text = NULL;
		ClickEvent = NotImplementedException;
		Enabled = true;
		PreviousMouseHoverState = MouseHover();
	}

public:
	char Text[64];

	Point2D A, B;

	bool Enabled;

	void (*ClickEvent)();

	char *SetText(const char text[]);

	void SetPositionAndSize(Point2D &centYAlginedCoord, Size2D &size)
	{
		A.X = centYAlginedCoord.X;
		A.Y = centYAlginedCoord.Y - (size.Height / 2);
		B.X = centYAlginedCoord.X + size.Width;
		B.Y = centYAlginedCoord.Y + (size.Height / 2);
	}

	void SetPositionAndSize(Size2D &size, Point2D &a)
	{
		A = a;
		B = Point2D(a.X + size.Width, a.Y + size.Height);
	}

	bool MouseHover()
	{
		return ((Mouse::X < B.X) && (Mouse::X > A.X) && (Mouse::Y < B.Y) && (Mouse::Y > A.Y));
	}

	bool MouseClicked()
	{
		if (MouseHover() != PreviousMouseHoverState)
			Draw();

		if (Mouse::Button && MouseHover())
		{
			if (Enabled)
				ClickEvent();
			return true;
		}
		return false;
	}

	void Draw(bool AutoMouseHide = true)
	{
		if (AutoMouseHide)
			Mouse::Hide();

		GraphicsEngine::FilledRectangle(A.X, A.Y, B.X, B.Y, DARKGRAY, (MouseHover() && Enabled) ? WHITE : DARKGRAY);

		settextjustify(LEFT_TEXT, CENTER_TEXT);
		settextstyle(0, HORIZ_DIR, 1);

		setcolor(MouseHover() ? LIGHTGRAY : WHITE);
		outtextxy(A.X + 4, (B.Y + A.Y) / 2, Text);

		if (AutoMouseHide)
			Mouse::Show();

		PreviousMouseHoverState = MouseHover();
	}

	PropertyButton()
	{
		Initialize();
	}

	PropertyButton(const char text[])
	{
		Initialize();
		SetText(text);
	}

	PropertyButton(Point2D &centYAlginedCoord, Size2D &size, void (*clickevent)() = NotImplementedException)
	{
		Initialize();
		SetPositionAndSize(centYAlginedCoord, size);
		ClickEvent = clickevent;
	}

	PropertyButton(Point2D &centYAlginedCoord, Size2D &size, const char text[])
	{
		Initialize();
		SetPositionAndSize(centYAlginedCoord, size);
		SetText(text);
	}

	~PropertyButton()
	{
		// if (Text != NULL)
		// 	delete Text;

		// if (Text_GC != NULL)
		// 	delete[] Text_GC;
	}
};

char *PropertyButton::SetText(const char text[])
{

	strcpy(Text, text);

	// if (Text != NULL)
	// 	delete Text;

	// if (text != NULL)
	// {
	// 	Text = (char*)malloc(strlen(text) + 1);
	// 	strcpy(Text, text);
	// }

	return Text;
}

#endif