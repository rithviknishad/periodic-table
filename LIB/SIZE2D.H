/*
==========================================================
NAME:			SIZE2D.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			2D Size Componenets definition
Last Updated:	October 6, 2018
==========================================================
*/

#if !defined(__SIZE2D_H)
#define __SIZE2D_H

class Size2D
{

public:
	int Width;
	int Height;

	void SetSize(int width, int height)
	{
		Width = width;
		Height = height;
	}

	Size2D()
	{
		SetSize(0, 0);
	}

	Size2D(int width, int height)
	{
		SetSize(width, height);
	}

	Size2D(Size2D &size2D)
	{
		SetSize(size2D.Width, size2D.Height);
	}
};

#endif