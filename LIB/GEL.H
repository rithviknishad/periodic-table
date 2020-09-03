/*
==========================================================
NAME:			GELS.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			Custom Graphics Render Engine (GRAPHICS.H Extended Definition)
Last Updated:	October 2, 2018
==========================================================
*/

#include <graphics.h>

#include "P_TABLE\\LIB\\POINT2D.H"
#include "P_TABLE\\LIB\\CDEF.H"

#if !defined(__GEL_H)
#define __GEL_H


class GraphicsEngine
{

    public:

    static void Rectangle(int left, int top, int right, int bottom, byte backcolor);
    static void Rectangle(Point2D A, Point2D B, byte bordercolor);

    static void FilledRectangle(int left, int top, int right, int bottom, byte bgcolor, byte bordercolor);
    static void FilledRectangle(Point2D A, Point2D B, byte bgcolor, byte bordercolor);


    static void Circle(int cx, int cy, unsigned int radius, byte bordercolor);
    static void Circle(Point2D axis, unsigned int radius, byte bordercolor);

    static void FilledCircle(int cx, int cy, unsigned int radius, byte backcolor, byte bordercolor);
    static void FilledCircle(Point2D axis, unsigned int radius, byte backcolor, byte bordercolor);


    static void DrawLine(Point2D A, Point2D B, int thickness, byte color);
    
};


void GraphicsEngine::Rectangle(int left, int top, int right, int bottom, byte bordercolor)
{
    setcolor(bordercolor);
    rectangle(left, top, right, bottom);
}


void GraphicsEngine::Rectangle(Point2D A, Point2D B, byte bordercolor)
{
    Rectangle(A.X, A.Y, B.X, B.Y, bordercolor);
}


void GraphicsEngine::FilledRectangle(int left, int top, int right, int bottom, byte bgcolor, byte bordercolor = 0)
{
    bordercolor = bordercolor ? bordercolor : bgcolor;
    
    Rectangle(left, top, right, bottom, bordercolor);

	setfillstyle(SOLID_FILL, bgcolor);
	floodfill(left + 1, top + 1, bordercolor);
}

void GraphicsEngine::FilledRectangle(Point2D A, Point2D B, byte bgcolor, byte bordercolor = 0)
{
    FilledRectangle(A.X, A.Y, B.X, B.Y, bgcolor, bordercolor);
}


void GraphicsEngine::Circle(int cx, int cy, unsigned int radius, byte bordercolor)
{
    setcolor(bordercolor);
    circle(cx, cy, radius);
}

void GraphicsEngine::Circle(Point2D axis, unsigned int radius, byte bordercolor)
{
    Circle(axis.X, axis.Y, radius, bordercolor);
}


void GraphicsEngine::FilledCircle(int cx, int cy, unsigned int radius, byte backcolor, byte bordercolor = 0)
{
    bordercolor = bordercolor ? bordercolor : backcolor;
    
    Circle(cx, cy, radius, bordercolor);

    setfillstyle(SOLID_FILL, backcolor);
    floodfill(cx, cy, bordercolor);
}

void GraphicsEngine::FilledCircle(Point2D axis, unsigned int radius, byte backcolor, byte bordercolor = 0)
{
    FilledCircle(axis.X, axis.Y, radius, backcolor, bordercolor);
}



void GraphicsEngine::DrawLine(Point2D A, Point2D B, int thickness, byte color)
{
    static int x;

    setcolor(color);
    for (x = 0; x < thickness; ++x)
        line(A.X, A.Y + x, B.X, B.Y + x);
}

#endif