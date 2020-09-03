/*
==========================================================
NAME:			POINT2D.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			Spacial 2D Point definition header file
Last Updated:	October 6, 2018
==========================================================
*/

#if !defined(__POINT2D_H)
#define __POINT2D_H

class Point2D
{
public:

	int X;
	int Y;

	void SetPoint(int x, int y)
	{
		X = x;
		Y = y;
	}

	Point2D()
	{
		SetPoint(0, 0);
	}

	Point2D(int x, int y)
	{
		SetPoint(x, y);
	}

	Point2D(Point2D &point2D)
	{
		SetPoint(point2D.X, point2D.Y);
	}
	
};

#endif