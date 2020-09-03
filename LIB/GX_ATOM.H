/*
==========================================================
NAME:			GX_ATOM.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			Component Graphics Render Engine -> Atom Model
Last Updated:	October 16, 2018
==========================================================
*/

#include "P_TABLE\\LIB\\POINT2D.H"
#include "P_TABLE\\LIB\\CDEF.H"
#include "P_TABLE\\LIB\\GEL.H"

#if !defined(__GX_ATOM_H)
#define __GX_ATOM_H

class AtomGraphics
{

	public:

	static Point2D center();

	static unsigned int GetRadiusOfShell(byte shell);

	static void DrawNucleus(byte color);

	static void DrawOrbit(byte color, byte shell);

	static void DrawElectrons(byte fillcolor, byte bordercolor, byte shell, byte count, float radian_offset);

};


Point2D AtomGraphics::center()
{
	return Point2D(getmaxx() / 2, (getmaxy() / 2));
}

unsigned int AtomGraphics::GetRadiusOfShell(byte shell)
{
	return (shell * 26) + 16;
}

void AtomGraphics::DrawNucleus (byte color)
{
	GraphicsEngine::FilledCircle(center(), 8, color);
}


void AtomGraphics::DrawOrbit(byte color, byte shell)
{
    GraphicsEngine::Circle(center(), GetRadiusOfShell(shell), color);
}

void AtomGraphics::DrawElectrons(byte fillcolor, byte bordercolor, byte shell, byte count, float radian_offset = PI / 2)
{
	for (int i = 0; i < count; ++i)
	{
		float deployAngle = (((2 * i * PI)) / ((float)count)) + radian_offset;
		Point2D deployPoint = Point2D((cos(deployAngle) * GetRadiusOfShell(shell)) + center().X, (sin(deployAngle) * GetRadiusOfShell(shell)) + center().Y);
		GraphicsEngine::FilledCircle(deployPoint, 4, fillcolor, bordercolor);
	}
}

#endif