/*
==========================================================
PROJECT NAME:	PERIODIC TABLE
AUTHOR:		RITHVIK NISHAD & ABHIMANYU
VERSION:	2018.10.17 Build 882 Revision 1239

Pending updates:

	MASTER -> Shift Element Property Display to Property Button
	SCREEN_RENDER -> Standard Dialog Box Returning Properties

==========================================================
*/


void main() { }
// hahahah!! YES! main() is empty. You think it won't run?
// I'm better than you!


/////   STANDARD LIBRARIES   /////
#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream.h>
#include <process.h>
#include <dos.h>
#include <string.h>
#include <iomanip.h>
#include <stddef.h>
#include <math.h>


/////    CUSTOM LIBRARIES    /////
#include "P_TABLE\\LIB\\ELEMENT.H"
#include "P_TABLE\\LIB\\ELM_FILE.H"
#include "P_TABLE\\LIB\\CURSOR.H"
#include "P_TABLE\\LIB\\POINT2D.H"
#include "P_TABLE\\LIB\\SIZE2D.H"
#include "P_TABLE\\LIB\\BUTTON.H"
#include "P_TABLE\\LIB\\ELEM_BTN.H"
#include "P_TABLE\\LIB\\GX_ATOM.H"
#include "P_TABLE\\LIB\\GEL.H"
#include "P_TABLE\\LIB\\CDEF.H"
#include "P_TABLE\\LIB\\QTYDEF.H"



#define GRAPHICS_PATH 				"C:\\TURBOC3\\BGI\\"
#define TOTAL_NUMBER_OF_ELEMENTS 	118
#define DEVELOPMENT_MODE 			1



void Close();



byte itr_1, itr_2; // Global Shared Iterator (RESERVED) (shared for low runtime memory consumption)


ElementButton ElementButtons[TOTAL_NUMBER_OF_ELEMENTS];










int InitializeGraphicsAndCursor()
{
	int gdriver = DETECT;
	int gmode;
	int errorcode;

	initgraph(&gdriver, &gmode, GRAPHICS_PATH);

	errorcode = graphresult();

	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("\n\nPress any key to exit");
		getch();
		exit(1);
	}

	if (!Mouse::Initialize())
		printf("Mouse not supported.");
	else
		Mouse::Show();

	return errorcode;
}









void Display_LoginScreen() 
{
	redo:
	setcolor(GREEN);
	setbkcolor(0x00);

	cleardevice();

	setcolor(8);

	rectangle((getmaxx() / 2) - 250, (getmaxy() / 2) - 150, (getmaxx() / 2) + 250, (getmaxy() / 2) + 150);

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(3, HORIZ_DIR,2);
	setcolor(8);
	setbkcolor(WHITE);
	outtextxy((getmaxx()/2)+10, (getmaxy()/2)-100, "P E R I O D I C   T A B L E");

	settextjustify(LEFT_TEXT, LEFT_TEXT);
	settextstyle(0, HORIZ_DIR, 1);

	outtextxy((getmaxx()/2)-180, (getmaxy()/2)-34, " USERNAME : ");
	outtextxy((getmaxx()/2)-180, (getmaxy()/2)-2, " PASSWORD : ");

	char un[] = "admin", pw[] = "admin", _un[25] = "",_pw[25] = "";

	gotoxy(32, 13);
	gets(_un);

	gotoxy(32, 15);
	gets(_pw);

	if (!strcmpi(un, _un) && !strcmpi(pw, _pw))
		outtextxy((getmaxx()/2)+10, (getmaxy()/2)+100, "Logging in...");
	else
		goto redo;

}


Button ExitButton;
Button BackButton;

class Screens
{

	

	static void DrawDefaultLayout(byte bkcolor, bool drawBackButton, bool drawExitButton, bool drawTitleBar, byte titleBarColor, byte titleTextColor);

	static void _draw_ViewElement_DefaultScreen();

	public:

	static void Initialize();

	static void Logo();

	static void Home();

	static void Table();

	static void ViewElement(ElementButton *sender);

	static void ViewAtomModel();

	static void About();

	static void ResetElements();


};


void Screens::Initialize()
{	
	ExitButton = Button(Point2D(625, 15), Size2D(30, 30), "X", LIGHTRED, RED, RED, LIGHTRED, RED, WHITE, Close);
	BackButton = Button(Point2D(15, 15), Size2D(30, 30), "<", WHITE, LIGHTGRAY, BLUE, BLUE, BLUE, BLUE, Home);
}




void Screens::Logo()
{
	Mouse::Hide();
	cleardevice();
	setbkcolor(BLACK);
	settextjustify(LEFT_TEXT, CENTER_TEXT);
	settextstyle(6, HORIZ_DIR, 12);
	setcolor(MAGENTA);
	outtextxy(260, 200, "Pt");
	Mouse::Show();
}



void Operation_ResetElements()
{
	Files::ResetFactoryDefaults();
	Screens::Home();
}





void Screens::DrawDefaultLayout(byte bkcolor, bool drawBackButton = true, byte drawExitButton = true, bool drawTitleBar = true, byte titleBarColor = LIGHTBLUE, byte titleTextColor = WHITE)
{
	Mouse::Hide();
	cleardevice();

	setbkcolor(bkcolor);

	if (drawTitleBar)
	{
		GraphicsEngine::FilledRectangle(0, 0, getmaxx(), ExitButton.B.Y, titleBarColor);

		settextjustify(LEFT_TEXT, CENTER_TEXT);
		settextstyle(6, HORIZ_DIR, 1);
		setcolor(titleTextColor);
		outtextxy(BackButton.B.X + 8, ((BackButton.A.Y + BackButton.B.Y) / 2) - 5, "P E R I O D I C   T A B L E");
	}

	while (Mouse::Refresh()) {} // to prevent clicking buttons of next screen accidentaly

	if (drawExitButton)
		ExitButton.Draw(false);

	if (drawBackButton)
		BackButton.Draw(false);

	Mouse::Show();
}






void Screens::Home()
{
	DrawDefaultLayout(BLACK, 0, 0);

	static Button ShowTableButton 		= Button(Point2D((getmaxx() / 2), (getmaxy() / 2) - 60), Size2D(160, 25), 	"VIEW TABLE", 		DARKGRAY, WHITE, DARKGRAY, BLUE, WHITE, BLUE, Screens::Table);
	static Button FactoryResetButton	= Button(Point2D((getmaxx() / 2), (getmaxy() / 2) - 20), Size2D(160, 25), 	"FACTORY RESET", 	DARKGRAY, WHITE, DARKGRAY, BLUE, WHITE, BLUE, Screens::ResetElements);
	static Button AboutButton			= Button(Point2D((getmaxx() / 2), (getmaxy() / 2) + 20), Size2D(160, 25), 	"ABOUT", 			DARKGRAY, WHITE, DARKGRAY, BLUE, WHITE, BLUE, Screens::About);
	static Button _ExitButton		 	= Button(Point2D((getmaxx() / 2), (getmaxy() / 2) + 60), Size2D(160, 25), 	"EXIT", 			RED, RED, RED, RED, WHITE, WHITE,     ExitButton.ClickEvent);

	Mouse::Hide();

	ShowTableButton.Draw(false);
	FactoryResetButton.Draw(false);
	AboutButton.Draw(false);
	_ExitButton.Draw(false);

	Mouse::Show();

	while (1)
	{
		Mouse::Refresh();

		if (ExitButton.MouseClicked() || ShowTableButton.MouseClicked() || FactoryResetButton.MouseClicked() || AboutButton.MouseClicked() || _ExitButton.MouseClicked())
			break;
	}
}




void Screens::Table()
{
	DrawDefaultLayout(LIGHTGRAY);

	BackButton.ClickEvent = Home;

	Mouse::Hide();

	for (itr_1 = 0; itr_1 < TOTAL_NUMBER_OF_ELEMENTS; ++itr_1)
		ElementButtons[itr_1].Draw(false);

	Mouse::Show();

	while (1)
	{
		Mouse::Refresh();

		for (itr_1 = 0; itr_1 < TOTAL_NUMBER_OF_ELEMENTS; ++itr_1)
			if (ElementButtons[itr_1].ElementClicked());

		if (ExitButton.MouseClicked() || BackButton.MouseClicked());
	}
}





#define NO_VALUE "---"

char buff_eba[64];
char buff_ebx[40];
const int __eax = 170, __eby = 158, __vApart = 16;


Element element;


void Screens::_draw_ViewElement_DefaultScreen()
{
	BackButton.Draw(false);
	GraphicsEngine::FilledRectangle(12, 42, getmaxx() - 12, getmaxy() - 12, DARKGRAY);

	setcolor(LIGHTGRAY);

	settextjustify(RIGHT_TEXT, CENTER_TEXT);

	outtextxy(__eax, __eby + (__vApart * 0), "Latin Name:  ");
	outtextxy(__eax, __eby + (__vApart * 1), "Year Discovered:  ");
	outtextxy(__eax, __eby + (__vApart * 2), "Discovered By:  ");
	outtextxy(__eax, __eby + (__vApart * 3), "Electron Shell:  ");
	outtextxy(__eax, __eby + (__vApart * 4), "Atomic Weight:  ");
	outtextxy(__eax, __eby + (__vApart * 5), "Density:  ");
	outtextxy(620, 60, "Block");
	outtextxy(610, 60 + (__vApart * 4), "[G, P]");
	outtextxy(__eax, __eby + (__vApart * 6), "Phase:  ");
	outtextxy(__eax, __eby + (__vApart * 7), "Melting Point:  ");
	outtextxy(__eax, __eby + (__vApart * 8), "Boiling Point:  ");

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextxy(((getmaxx() / 3) * 1) - 110, __eby + (__vApart * 10) - 5, "Electrons:");
	outtextxy(((getmaxx() / 3) * 2) - 110, __eby + (__vApart * 10) - 5, "Protons:");
	outtextxy(((getmaxx() / 3) * 3) - 110, __eby + (__vApart * 10) - 5, "Neutrons:");

	outtextxy(((getmaxx() / 3) * 1) - 110, __eby + (__vApart * 13) - 5, "Atomic Radius:");
	outtextxy(((getmaxx() / 3) * 2) - 110, __eby + (__vApart * 13) - 5, "Covalent Radius:");
	outtextxy(((getmaxx() / 3) * 3) - 110, __eby + (__vApart * 13) - 5, "Van der Waals Radius:");


	settextjustify(RIGHT_TEXT, CENTER_TEXT);

	outtextxy(__eax, __eby + (__vApart * 16), "Oxidation States:  ");
	outtextxy(__eax, __eby + (__vApart * 17), "Half Life:  ");
	outtextxy(__eax, __eby + (__vApart * 18), "Lifetime:  ");

}






void Screens::ViewElement(ElementButton *sender)
{	
	DrawDefaultLayout(LIGHTGRAY, 0);

	BackButton.ClickEvent = Table;

	static Button CATFilterButton;
	static Button RadioactiveFilterButton = Button("RADIOACTIVE", YELLOW, DARKGRAY);

	Mouse::Hide();
	
	_draw_ViewElement_DefaultScreen();

	element = Files::GetElement(sender -> Z);

	// draw element specific thematic stuff
	GraphicsEngine::DrawLine(Point2D(12, 137), Point2D(getmaxx() - 12, 137), 2, sender -> BorderColor);

	CATFilterButton.BackColor = sender -> BorderColor;
	CATFilterButton.BorderColor = sender -> BorderColor;
	CATFilterButton.Enabled = false;

	static Point2D ___CatFCA = Point2D(12, 54);
	
	switch ( element.Category )
	{
		case Element::Other_NonMetals:
			CATFilterButton.SetPositionAndSize(Size2D(160, 24), ___CatFCA);
			CATFilterButton.ForeColor = DARKGRAY;
			CATFilterButton.SetText("OTHER NONMETALS");
			break;

		case Element::NobleGases:
			CATFilterButton.SetPositionAndSize(Size2D(120, 24), ___CatFCA);
			CATFilterButton.ForeColor = WHITE;
			CATFilterButton.SetText("NOBLE GASES");
			break;
		
		case Element::AlkaliMetals:
			CATFilterButton.SetPositionAndSize(Size2D(120, 24), ___CatFCA);
			CATFilterButton.ForeColor = WHITE;
			CATFilterButton.SetText("ALKALI METALS");
			break;

		case Element::AlkalineEarthMetals:
			CATFilterButton.SetPositionAndSize(Size2D(200, 24), ___CatFCA);
			CATFilterButton.ForeColor = WHITE;
			CATFilterButton.SetText("ALKALINE EARTH METALS");
			break;

		case Element::TransitionMetals:
			CATFilterButton.SetPositionAndSize(Size2D(160, 24), ___CatFCA);
			CATFilterButton.ForeColor = WHITE;
			CATFilterButton.SetText("TRANSITION METALS");
			break;

		case Element::PostTransitionMetals:
			CATFilterButton.SetPositionAndSize(Size2D(200, 24), ___CatFCA);
			CATFilterButton.ForeColor = WHITE;
			CATFilterButton.SetText("POST-TRANSITION METALS");
			break;

		case Element::Metalloids:
			CATFilterButton.SetPositionAndSize(Size2D(120, 24), ___CatFCA);
			CATFilterButton.ForeColor = DARKGRAY;
			CATFilterButton.SetText("METALLOIDS");
			break;

		case Element::Halogens:
			CATFilterButton.SetPositionAndSize(Size2D(100, 24), ___CatFCA);
			CATFilterButton.ForeColor = WHITE;
			CATFilterButton.SetText("HALOGENS");
			break;

		case Element::Lanthanoids:
			CATFilterButton.SetPositionAndSize(Size2D(120, 24), ___CatFCA);
			CATFilterButton.ForeColor = WHITE;
			CATFilterButton.SetText("LANTHANOIDS");
			break;

		case Element::Actinoids:
			CATFilterButton.SetPositionAndSize(Size2D(120, 24), ___CatFCA);
			CATFilterButton.ForeColor = WHITE;
			CATFilterButton.SetText("ACTINOIDS");
			break;

		case Element::SuperActinoid:
			CATFilterButton.SetPositionAndSize(Size2D(160, 24), ___CatFCA);
			CATFilterButton.ForeColor = DARKGRAY;
			CATFilterButton.SetText("SUPER-ACTINOIDS");
			break;

		default:
			CATFilterButton.SetPositionAndSize(Size2D(100, 24), ___CatFCA);
			CATFilterButton.ForeColor = DARKGRAY;
			CATFilterButton.SetText("UNKNOWN");
			break;

	}

	CATFilterButton.Draw(false);

	if (element.Radioactive())
	{
		RadioactiveFilterButton.SetPositionAndSize(Size2D(120, 24), Point2D(CATFilterButton.B.X, CATFilterButton.A.Y));
		RadioactiveFilterButton.Draw(false);
	}

	// --------------------------------------------------------------------------
	// Symbol: X
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(6, HORIZ_DIR, 5);
	setcolor(WHITE);
	outtextxy(56, 98, element.X);

	// --------------------------------------------------------------------------
	// element name

	setcolor(CATFilterButton.BackColor);
	
	for (itr_1 = 0; itr_1 <= 13; itr_1++)
		circle(110, 108, itr_1);

	setcolor(CATFilterButton.ForeColor);

	settextstyle(0, HORIZ_DIR, 1);
	itoa(element.Z(), buff_eba, 10);
	outtextxy(110, 108, buff_eba);

	setcolor(WHITE);

	settextjustify(LEFT_TEXT, CENTER_TEXT);
	settextstyle(6, HORIZ_DIR, 3);
	strcpy(buff_eba, SapcedString(element.Name));
	outtextxy(136, 94, buff_eba);

	// --------------------------------------------------------------------------
	// element atomic weight
	settextstyle(0, HORIZ_DIR, 1);
	strcpy(buff_eba, "");
	gcvt(element.AtomicWeight, 5, buff_eba);
	strcat(buff_eba, " (g/mol)");
	outtextxy(136, 120, buff_eba);
	

	// --------------------------------------------------------------------------
	// values
	setcolor(WHITE);


	static PropertyButton LatinName			(Point2D(__eax, __eby + (__vApart * 0)), Size2D(440, __vApart - 2));
	static PropertyButton YearDiscovered	(Point2D(__eax, __eby + (__vApart * 1)), Size2D(440, __vApart - 2));
	static PropertyButton DiscoveredBy		(Point2D(__eax, __eby + (__vApart * 2)), Size2D(440, __vApart - 2));
	static PropertyButton ElectronConfig	(Point2D(__eax, __eby + (__vApart * 3)), Size2D(440, __vApart - 2), Screens::ViewAtomModel);
	static PropertyButton AtomicWeight		(Point2D(__eax, __eby + (__vApart * 4)), Size2D(440, __vApart - 2));
	static PropertyButton Density			(Point2D(__eax, __eby + (__vApart * 5)), Size2D(440, __vApart - 2));
	static PropertyButton Phase				(Point2D(__eax, __eby + (__vApart * 6)), Size2D(440, __vApart - 2));
	static PropertyButton MeltingPoint		(Point2D(__eax, __eby + (__vApart * 7)), Size2D(440, __vApart - 2));
	static PropertyButton BoilingPoint		(Point2D(__eax, __eby + (__vApart * 8)), Size2D(440, __vApart - 2));

	static PropertyButton AtomicRadius		(Point2D(((getmaxx() / 3) * 1) - 110, __eby + (__vApart * 14) - 5), Size2D(100 , __vApart));
	static PropertyButton CovalentRadius	(Point2D(((getmaxx() / 3) * 3) - 110, __eby + (__vApart * 14) - 5), Size2D(100 , __vApart));
	static PropertyButton VanderWaalsRadius	(Point2D(((getmaxx() / 3) * 2) - 110, __eby + (__vApart * 14) - 5), Size2D(100 , __vApart));

	static PropertyButton OxidationStates	(Point2D(__eax, __eby + (__vApart * 16)), Size2D(440, __vApart - 2));
	static PropertyButton HalfLife			(Point2D(__eax, __eby + (__vApart * 17)), Size2D(440, __vApart - 2));
	static PropertyButton Lifetime			(Point2D(__eax, __eby + (__vApart * 18)), Size2D(440, __vApart - 2));
	



	AtomicWeight.SetText(buff_eba);
	AtomicWeight.Draw(false);

	LatinName.SetText(strcmpi(element.LatinName, "") ? element.LatinName : NO_VALUE);
	LatinName.Draw(false);
	


	if (element.YearDiscovered)
		itoa(element.YearDiscovered, buff_eba, 10);
	else
		strcpy(buff_eba, NO_VALUE);

	YearDiscovered.SetText(buff_eba);
	YearDiscovered.Draw(false);


	DiscoveredBy.SetText(strcmpi(element.DiscoveredBy, "") ? element.DiscoveredBy : NO_VALUE);
	DiscoveredBy.Draw(false);


	strcpy(buff_ebx, "");
	for (itr_1 = 0; itr_1 < (sizeof(element.ElectronShells) / sizeof(Shell)) && element.ElectronShells[itr_1].ElectronCount(); ++itr_1)
	{
		static char buff_sk[2];
		*buff_sk = element.ElectronShells[itr_1].ShellNotation();
		*(buff_sk + 1) = '\0';
		strcat(buff_ebx, buff_sk);

		
		itoa((int)element.ElectronShells[itr_1].ElectronCount(), buff_eba, 10);
		strcat(buff_ebx, buff_eba);

		strcat(buff_ebx, " ");
	}

	ElectronConfig.SetText(buff_ebx);
	ElectronConfig.Draw(false);	

	if (element.Density)
	{
		gcvt(element.Density, 8, buff_eba);
		strcat(buff_eba, " (g/cm^3)");
	}
	else
		strcpy(buff_eba, NO_VALUE);

	Density.SetText(buff_eba);
	Density.Draw(false);


	switch (element.Block())
	{
		case Orbital::s:	strcpy(buff_eba, "S");	break;
		case Orbital::p:	strcpy(buff_eba, "P");	break;
		case Orbital::d:	strcpy(buff_eba, "D");	break;
		case Orbital::f:	strcpy(buff_eba, "F");	break;
		case Orbital::g:	strcpy(buff_eba, "G");	break;
		default:			strcpy(buff_eba, "");	break;
	}
	outtextxy(560, 60, buff_eba);


	strcpy(buff_eba, "[");
	if (element.Group())
		itoa((int)element.Group(), buff_ebx, 10);
	else
		strcpy(buff_ebx, "--");
	strcat(buff_eba, buff_ebx);
	strcat(buff_eba, ", ");
	itoa((int)element.Period(), buff_ebx, 10);
	strcat(buff_eba, buff_ebx);
	strcat(buff_eba, "]");	
	outtextxy(560, 60 + (__vApart * 3), buff_eba);


	switch (element.Phase())
	{
		case AtomicProperties::Solid:	strcpy(buff_eba, "Solid");	setcolor(LIGHTGREEN);	break;
		case AtomicProperties::Liquid:	strcpy(buff_eba, "Liquid");	setcolor(BLUE);			break;
		case AtomicProperties::Gas:		strcpy(buff_eba, "Gas");							break;
		default:						strcpy(buff_eba, NO_VALUE);							break;
	}
	
	Phase.SetText(buff_eba);
	Phase.Draw(false);

	setcolor(WHITE);

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(6, HORIZ_DIR, 2);

	itoa((int)element.ElectronCount(), buff_eba, 10);
	outtextxy(((getmaxx() / 3) * 1) - 110, __eby + (__vApart * 11) - 5, buff_eba);

	itoa((int)element.ProtonCount, buff_eba, 10);
	outtextxy(((getmaxx() / 3) * 2) - 110, __eby + (__vApart * 11) - 5, buff_eba);

	itoa((int)element.NeutronCount, buff_eba, 10);
	outtextxy(((getmaxx() / 3) * 3) - 110, __eby + (__vApart * 11) - 5, buff_eba);

	

	if (element.AtomicRadius)
	{
		gcvt(element.AtomicRadius, 5, buff_eba);
		strcat(buff_eba, " pm");
	}
	else
		strcpy(buff_eba, NO_VALUE);

	AtomicRadius.SetText(buff_eba);
	AtomicRadius.Draw(false);


	if (element.CovalentRadius)
	{
		gcvt(element.CovalentRadius, 5, buff_eba);
		strcat(buff_eba, " pm");
	}
	else
		strcpy(buff_eba, NO_VALUE);

	CovalentRadius.SetText(buff_eba);
	CovalentRadius.Draw(false);


	if (element.VanderWaalsRadius)
	{
		gcvt(element.VanderWaalsRadius, 5, buff_eba);
		strcat(buff_eba, " pm");
	}
	else
		strcpy(buff_eba, NO_VALUE);

	VanderWaalsRadius.SetText(buff_eba);
	VanderWaalsRadius.Draw(false);


	strcpy(buff_eba, "");
	
	if ((element.mem_oxiphase & n1) == n1)
		strcat(buff_eba, "-1 ");
	if ((element.mem_oxiphase & n2) == n2)
		strcat(buff_eba, "-2 ");
	if ((element.mem_oxiphase & n3) == n3)
		strcat(buff_eba, "-3 ");
	if ((element.mem_oxiphase & n4) == n4)
		strcat(buff_eba, "-4 ");
	if ((element.mem_oxiphase & n5) == n5)
		strcat(buff_eba, "-5 ");
	if ((element.mem_oxiphase & p1) == p1)
		strcat(buff_eba, "+1 ");
	if ((element.mem_oxiphase & p2) == p2)
		strcat(buff_eba, "+2 ");
	if ((element.mem_oxiphase & p3) == p3)
		strcat(buff_eba, "+3 ");
	if ((element.mem_oxiphase & p4) == p4)
		strcat(buff_eba, "+4 ");
	if ((element.mem_oxiphase & p5) == p5)
		strcat(buff_eba, "+5 ");
	if ((element.mem_oxiphase & p6) == p6)
		strcat(buff_eba, "+6 ");
	if ((element.mem_oxiphase & p7) == p7)
		strcat(buff_eba, "+7 ");
	if ((element.mem_oxiphase & p8) == p8)
		strcat(buff_eba, "+8 ");
	if ((element.mem_oxiphase & p9) == p9)
		strcat(buff_eba, "+9 ");

	OxidationStates.SetText(strcmpi(buff_eba, "") ? buff_eba : NO_VALUE);
	OxidationStates.Draw(false);


	if (element.MeltingPoint.GetValue(Temperature::Kelvin))
	{
		gcvt(element.MeltingPoint.GetValue(Temperature::Kelvin), 5, buff_eba);
		strcat(buff_eba, " K");
	}
	else
		strcpy(buff_eba, NO_VALUE);
	
	MeltingPoint.SetText(buff_eba);
	MeltingPoint.Draw(false);


	if (element.BoilingPoint.GetValue(Temperature::Kelvin))
	{
		gcvt(element.BoilingPoint.GetValue(Temperature::Kelvin), 5, buff_eba);
		strcat(buff_eba, " K");
	}
	else
		strcpy(buff_eba, NO_VALUE);
	
	BoilingPoint.SetText(buff_eba);
	BoilingPoint.Draw(false);


	if (element.Radioactive())
	{
		setcolor(LIGHTRED);


		gcvt(element.HalfLife.Value, 5, buff_eba);
		switch (element.HalfLife.Unit)
		{
			case Duration::Days:			strcat(buff_eba, " days");			break;
			case Duration::Hours:			strcat(buff_eba, " hours");			break;
			case Duration::Years:			strcat(buff_eba, " years");			break;
			case Duration::Seconds:			strcat(buff_eba, " seconds");			break;
			case Duration::Nanoseconds:		strcat(buff_eba, " nanoseconds");		break;
			case Duration::Microseconds:	strcat(buff_eba, " microseconds");	break;
			case Duration::Milliseconds:	strcat(buff_eba, " milliseconds");	break;
			case Duration::Minutes:			strcat(buff_eba, " minutes");			break;
		}

		gcvt(element.Lifetime.Value, 5, buff_ebx);
		switch (element.Lifetime.Unit)
		{
			case Duration::Days:			strcat(buff_ebx, " days");			break;
			case Duration::Hours:			strcat(buff_ebx, " hours");			break;
			case Duration::Years:			strcat(buff_ebx, " years");			break;
			case Duration::Seconds:			strcat(buff_ebx, " seconds");		break;
			case Duration::Nanoseconds:		strcat(buff_ebx, " nanoseconds");	break;
			case Duration::Microseconds:	strcat(buff_ebx, " microseconds");	break;
			case Duration::Milliseconds:	strcat(buff_ebx, " milliseconds");	break;
			case Duration::Minutes:			strcat(buff_ebx, " minutes");		break;
		}

		if (element.HalfLife.Unit == Duration::Infinite)
			strcpy(buff_eba, "Infinite");

		if (element.Lifetime.Unit == Duration::Infinite)
			strcpy(buff_ebx, "Infinite");

	}
	else
	{
		strcpy(buff_eba, NO_VALUE);
		strcpy(buff_ebx, NO_VALUE);
	}

	HalfLife.SetText(buff_eba);
	HalfLife.Draw(false);

	Lifetime.SetText(buff_ebx);
	Lifetime.Draw(false);
	
	
	Mouse::Show();

	while (1)
	{
		Mouse::Refresh();

		if 
		(
			ExitButton.MouseClicked() 			|| 
			BackButton.MouseClicked() 			|| 
			CATFilterButton.MouseClicked() 		|| 
			AtomicWeight.MouseClicked() 		||
			LatinName.MouseClicked()			||
			YearDiscovered.MouseClicked()		||
			DiscoveredBy.MouseClicked()			||
			ElectronConfig.MouseClicked()		||
			Density.MouseClicked()				||
			Phase.MouseClicked()				||
			MeltingPoint.MouseClicked()			||
			BoilingPoint.MouseClicked()			||
			AtomicRadius.MouseClicked()			||
			CovalentRadius.MouseClicked()		||
			VanderWaalsRadius.MouseClicked()	||
			OxidationStates.MouseClicked()		||
			HalfLife.MouseClicked()				||
			Lifetime.MouseClicked()
		);

	}
}






void Screens::ViewAtomModel()
{

	DrawDefaultLayout(WHITE, false, false, false);

	Mouse::Hide();

	AtomGraphics::DrawNucleus(LIGHTGRAY);

	float rotation_buff = 0;

	while (!Mouse::Refresh())
	{

		rotation_buff += 0.01745;
		
		if (rotation_buff >= 6.28318)
			rotation_buff = 0;

		for (itr_1 = 0; itr_1 < 7 && element.ElectronShells[itr_1].ElectronCount(); ++itr_1)
		{
			AtomGraphics::DrawElectrons(WHITE, WHITE, itr_1 + 1, element.ElectronShells[itr_1].ElectronCount(), rotation_buff - 0.01745);
			AtomGraphics::DrawElectrons(itr_1 + 1, itr_1 + 1, itr_1 + 1, element.ElectronShells[itr_1].ElectronCount(), rotation_buff);
			AtomGraphics::DrawOrbit(itr_1 + 1, itr_1 + 1);
		}
		delay(10);
	}
	
	Mouse::Show();
	Screens::Table();

}








// void Screens::ViewAtomModel()
// {

// 	DrawDefaultLayout(BLACK);

// 	float rotation_buff = 0;

// 	Mouse::Hide();

// 	while (!Mouse::Button)
// 	{
// 		cleardevice();

// 		Mouse::Refresh();

// 		rotation_buff += 0.01745;
		
// 		if (rotation_buff >= 6.28318)
// 			rotation_buff = 0;

// 		AtomGraphics::DrawNucleus(DARKGRAY);

// 		for (itr_1 = 0; itr_1 < 7 && element.ElectronShells[itr_1].ElectronCount(); ++itr_1)
// 		{
// 			AtomGraphics::DrawElectrons(itr_1 + 1, itr_1 + 1, itr_1 + 1, element.ElectronShells[itr_1].ElectronCount(), rotation_buff);
// 			AtomGraphics::DrawOrbit(itr_1 + 1, itr_1 + 1);
// 		}
// 		delay(50);
// 	}

// 	Mouse::Show();
// 	Screens::Table();

// }






void Screens::About()
{
	DrawDefaultLayout(DARKGRAY);

	BackButton.ClickEvent = Home;

	Mouse::Hide();

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(0, HORIZ_DIR, 1);
	setcolor(YELLOW);

	outtextxy(getmaxx() / 2, (getmaxy() / 2) - 40, "ABOUT");
	outtextxy(getmaxx() / 2, (getmaxy() / 2) - 20, "PERIODIC TABLE v 2018.10.15 Build 558");
	outtextxy(getmaxx() / 2, (getmaxy() / 2) + 20, "Developed by: Rithvik Nishad & Abhimanyu Rajeesh");

	Mouse::Show();

	while (1)
	{
		Mouse::Refresh();

		if (ExitButton.MouseClicked() || BackButton.MouseClicked())
			break;
	}
}




void Screens::ResetElements()
{
	DrawDefaultLayout(BLACK);

	BackButton.ClickEvent = Home;

	static Button ConfirmButton = Button(Point2D((getmaxx() / 2) + 55, 300), Size2D(100, 25), "CONFIRM", RED, RED, LIGHTRED, LIGHTRED, WHITE, WHITE, Operation_ResetElements);
	static Button CancelButton  = Button(Point2D((getmaxx() / 2) - 55, 300), Size2D(100, 25), "CANCEL", LIGHTGREEN, GREEN, GREEN, GREEN, WHITE, WHITE, Home);

	Mouse::Hide();

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(3, HORIZ_DIR, 1);
	setcolor(YELLOW);
	outtextxy(getmaxx() / 2, (getmaxy() / 2) - 40, "Caution! Irreversible Operation.");
	settextstyle(6, HORIZ_DIR, 1);
	outtextxy(getmaxx() / 2, (getmaxy() / 2), "Are you sure you want to reset all elements?");

	
	
	ConfirmButton.Draw(false);
	CancelButton.Draw(false);

	Mouse::Show();

	while (1)
	{
		Mouse::Refresh();
		
		if (ExitButton.MouseClicked() || BackButton.MouseClicked() || ConfirmButton.MouseClicked() || CancelButton.MouseClicked())
			break;
	}

}






void DisplayElement(byte z)
{
	Element me = Files::GetElement(z);
	cout << "\n" << me.X << "  " << me.Name << " [ Z: " << (int)me.Z() << " | A: " << (int)me.A() << " ]\n";
	cout << "\nLatinName: " << me.LatinName << "\nDiscoveredBy: " << me.DiscoveredBy << "\nYearDiscovered: " << me.YearDiscovered;
	cout << "\n\nAtomicWeight: " << me.AtomicWeight << " g/mol   Density: " << me.Density << " g/(cm^3)    Phase: " << (int)me.Phase();
	cout << "\nAtomicRadius: " << me.AtomicRadius << " pm    CovalentRadius: " << me.CovalentRadius << " pm    Van der Waals Radius: " << me.VanderWaalsRadius << " pm";
	cout << "\nMeltingPoint: " << me.MeltingPoint.GetValue(Temperature::Kelvin) << "K   Boiling Point: " << me.BoilingPoint.GetValue(Temperature::Kelvin) << "K";
	cout << "\nRadioactive: " << (int)me.Radioactive() << "  HalfLife: " << me.HalfLife.Value << "  LifeTime: " << me.Lifetime.Value;
	cout << "\nmem_oxiphase:  "; cout << (unsigned int)me.mem_oxiphase;
	cout << "\n\nDerived Datas:\nGroup: " << (int)me.Group() << "   Period: " << (int)me.Period();
	cout << "\nNoble Gas: " << (int)me.IsStable();
	cout << "\nBlock: " << (int)me.Block();

}

void InitializeData() {
	
	char input;

	cout << "\nInitializing global variables...";


	if (!Files::CheckFiles())
	{
		cout << "\n>> Files::CheckFiles() returned error : 0. \nSuggested: Perform Files::Clean() operation. This will delete existing files assosicated with the program, and create a new file with DigitalSignature. (Y/N)";

		input = getch();
		if (input == 'y' || input == 'Y')
		{
			if (!Files::Clean())
				cout << "\n>> FATAL ERROR! Files::Clean() operation returned error: 0.";
			else
				cout << "\nFiles::Clean() operation success. Restart of program required.";

			cout << "\nProgram will terminate now...";
			delay(4096);
			exit(1);
		}
		else
			exit(1);
	}
	else
		cout << "Files::CheckFiles() returned success.";

	cout << "\nReading all elements...";
	byte a = Files::ElementCount();
	
	fstream f;
	f.open(Files::path, ios::in | ios::binary);

	if (!f)
		cout << "\nFILE_ERROR-WHILE_READING_ELEMENTS";

	//f.read((char*)&FileSignature, sizeof(DigitalSignature));

	f.seekg(0);
	
	Element *cache = new Element;

	for (byte itr_1 = 0; (itr_1 < a) && (f.read((char*)cache, sizeof(Element))); ++itr_1)
	{	
		ElementButtons[itr_1] = ElementButton(cache);
		clrscr();
		cout << "\n\nCaching necessary informations into buffer...\n";
		for (byte itr_2 = 0; itr_2 < (int)((float)itr_1 * 0.65); itr_2++)
			cout << char(178);
		cout << char(177) << char(177) << char (176) << char(176);
		cout << "\n\n\n $ Processing Element -> " << (int)cache -> Z() << " " << cache -> X << " " << " [A: " << (int)cache -> A() << "] " << cache -> Name;
		cout << "\nAuto Electron Fill >  " << (int)cache -> ElectronCount() << " electron(s) pushed into appropriate theoretical orbit\n[Group, Period] = [" << (int)cache -> Group() << " , " << (int)cache -> Period() ;
		cout << "]\n\nExtracting... -> mem_oxi_phase (decoding: 0x" << hex << cache -> mem_oxiphase << ")   2 B -> 66 B" << dec;
		cout << "\nSize: " << sizeof(*cache) << " bytes\n";
		if (cache -> Radioactive())
			cout << "$ auto - RADIOACTIVE ELEMENT !\n";

	}

	delete cache;

	f.close();

	cout << "\n" << (int)a << " Elements cached into memory.";
	cout << "\n\nCached: " << sizeof(ElementButton) * (int)a << "  bytes  out of " << sizeof(Element) * (int)a << " bytes";
	cout << "\n $ PERIODIC_TABLE_INSTANCE_1 > ";

	getch();
}

void Operation__RemoveElements()
{
	int z;
	cout << "\n\nEnter Element Atomic Number to Remove: ";
	cin >> z;
	DisplayElement(z);
	cout << "\n\nRemove Operation Result: " << (int)Files::RemoveElement(z);
}

void Operation__AddElements()
{
	int z, a; char symbol[4] = "";
	cout << "Enter Atomic Number (Z): "; cin >> z;
	cout << "Enter Symbol        (X): "; gets(symbol);
	cout << "Enter Atomic Weight (A): "; cin >> a;

	Element newElement  = Element(symbol, z, a);
	
	cout << "\nEnter Name: "; gets(newElement.Name);
	cout << "Enter LatinName: "; gets(newElement.LatinName);
	cout << "Enter DiscoveredBy: "; gets(newElement.DiscoveredBy);
	cout << "Enter Year Discovered: "; cin >> newElement.YearDiscovered;
	cout << "\nAtomic Properties:\n";
	cout << "Atomic Weight (g/mol): "; cin >> newElement.AtomicWeight;
	cout << "Density (g/cm^3): "; cin >> newElement.Density;
	cout << "Atomic Radius (pm): "; cin >> newElement.AtomicRadius;
	cout << "CovalentRadius (pm): "; cin >> newElement.CovalentRadius;
	cout << "VanderWaalsRadius (pm): "; cin >> newElement.VanderWaalsRadius;
	cout << "mem_oxiphase: "; cin >> (unsigned int) newElement.mem_oxiphase;
	float buff;
	cout << "Melting Point (K): "; cin >> buff; newElement.MeltingPoint = Temperature(buff, Temperature::Kelvin);
	cout << "Boiling Point (K): "; cin >> buff; newElement.BoilingPoint = Temperature(buff, Temperature::Kelvin);
	cout << "\nNuclear Properties:\n";

	float temp;
	cout << "HalfLife = (years) "; cin >> temp;
	newElement.HalfLife.Set(temp, Duration::Years);
	cout << "LifeTime = (years) "; cin >> temp;
	newElement.Lifetime.Set(temp, Duration::Years);

	cout << "\n\nAll Properties entered. Creating element...";

	while ((Files::GetElement(z).Z() == z) && (z != 0))
		cout << "\nRemove Operation Result: " << (int)Files::RemoveElement(z);

	cout << "\nAdd Operation Result: " << (int)Files::AddElement(newElement);
}

void Operation_QuickAddElement()
{
	int z = 127, n = 127; char symbol[4] = "NA";

	while (1)
	{
		clrscr();
		cout << "Z (Enter 0 to stop quick entry): "; cin >> z;

		if (z == 0)
			return;

		cout << "#Neutrons: "; cin >> n;
		cout << "X: "; gets(symbol);
		Element element = Element(symbol, z, z + n);
		cout << "Enter Name: "; gets(element.Name);

		if (!Files::AddElement(element))
		{
			cout << "\nAdd Operation failed!";
			getch();
			return;
		}
	}
}

void PerformAdvancedStartup()
{
	while (1)
	{
		clrscr();
		InitializeData();
		cout << "\n";
		cout << "\n +----------------------------------------------------------------------------+";
		cout << "\n |                         P E R I O D I C   T A B L E                        |";
		cout << "\n |               A D V A N C E D   S T A R T U P   O P T I O N S              |";
		cout << "\n +----------------------------------------------------------------------------+";
		cout << "\n |                                                                            |";
		cout << "\n |  < 01 >   CONTINUE RUNNING                                                 |";
		cout << "\n |  < 02 >   REMOVE ELEMENT                             (Advanced Operation)  |";
		cout << "\n |  < 03 >   ADD ELEMENT                                (Advanced Operation)  |";
		cout << "\n |  < 04 >   EDIT ELEMENT                               (   Unavailable!   )  |";
		cout << "\n |  < 05 >   VIEW ELEMENT                               (Advanced Operation)  |";
		cout << "\n |  < 06 >   GET #ELEMENTS IN FILE                                            |";
		cout << "\n |  < 07 >   QUICK ADD ELEMENT                          (Advanced Operation)  |";
		cout << "\n |  < 08 >   QUICK AUTO ADD ELEMENTS                    (   Unavailable!   )  |";
		cout << "\n |  < 09 >   RESET FACTORY DEFAULTS                     (Advanced Operation)  |";
		cout << "\n |  < 64 >   EXIT                                                             |";
		cout << "\n |                                                                            |";
		cout << "\n +----------------------------------------------------------------------------+";
		cout << "\n";
		cout << "\n   ENTER CHOICE: ";

		int choice;
		cin >> choice;

		if (choice == 1)
			break;

		else if (choice == 2)
			Operation__RemoveElements();

		else if (choice == 3)
			Operation__AddElements();

		else if (choice == 4)
		{
			cout << "\nOperation Not Available";
			// cout << "Enter Element Z to be edited: "; cin >> choice;
			// DisplayElement(choice);
			// cout << "\n\n";
			// Operation__AddElements();
		}

		else if (choice == 5)
		{
			cout << "\n\nEnter Atomic Number of element to be viewed: ";
			cin >> choice;
			if (Files::GetElement(choice).Z() == choice)
				DisplayElement(choice);
			else
				cout << "\nNo Such Element Found in file.";
		}

		else if (choice == 6)
			cout << "\nNumber of Elements = " << (int)Files::ElementCount();

		else if (choice == 7)
			Operation_QuickAddElement();

		else if (choice == 8)
		{
			cout << "\nOperation Not Available";
			// for (int itr_1 = 1; itr_1 <= TOTAL_NUMBER_OF_ELEMENTS; ++itr_1)
			// {
			// 	Element element = Element("N/A", itr_1, ((byte)(itr_1 * 2)));
			// 	Files::AddElement(element);
			// }
		}
		
		else if (choice == 9)
			Files::ResetFactoryDefaults();

		else if (choice == 64)
			exit(0);

		cout << "\n\nPress any key to restart...";
		getch();
		clrscr();
		cout << "Restarting.........";
		delay(50);
	}
}

class PeriodicTable
{
	public:

	PeriodicTable()
	{
		PerformAdvancedStartup();
		InitializeGraphicsAndCursor();
		Screens::Initialize();

		Screens::Logo();
		//delay(4000);

		Screens::Table();

		Close();
	}

} Instance1;

void Close()
{
	cleardevice();
	closegraph();
	exit(0);
}

void ShowElement(char *sender)
{
	Screens::ViewElement((ElementButton*)sender);
}