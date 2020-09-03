/*
==========================================================
NAME:			ELEMENT.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			Alpha definition file for standard atomic element
Last Updated:	October 12, 2018
==========================================================
*/


#include <string.h>

#include "P_TABLE\\LIB\\CDEF.H"
#include "P_TABLE\\LIB\\QTYDEF.H"

#if !defined(__ELEMENT_H)
#define __ELEMENT_H


class __DigitalSignature
{
	char Name[32];
	char Version[32];
	char Author[64];

public:

	//static byte Verify(__DigitalSignature &a, __DigitalSignature &b) { return ((!strcmpi(a.Name, b.Name)) && (!strcmpi(a.Version, b.Version)) && (!strcmpi(a.Author, b.Author))) ? 1 : 0; }

	__DigitalSignature()
	{
		strcpy(Name, "PERIODIC_TABLE_18");
		strcpy(Version, "v 18.0.0.1");
		strcpy(Author, "Rithvik Nishad [www.smartcraft.strikingly.com]");
	}

	__DigitalSignature(const char name[], const char version[], const char author[])
	{
		strcpy(Name, name);
		strcpy(Version, version);
		strcpy(Author, author);
	}

};
__DigitalSignature DigitalSignature = __DigitalSignature("PERIODIC_TABLE_18", "v 18.0.0.1", "Rithvik Nishad [www.smartcraft.strikingly.com]");
__DigitalSignature FileSignature = __DigitalSignature();




class Electron
{
public:
	static double Mass; // kg
	static double Charge; // coulombs

	enum SpinStates
	{ 
		SpinUp = -1,
		SpinDown = 1,
		Disabled = 0 
	};

	byte Active;

	Electron() { Active = Disabled; }

	void SetSpin(SpinStates spinstate)
	{ 
		Active = spinstate;
	}

	float ms() // electron spin quantum number
	{ 
		return (Active == Disabled ? 0 : (Active == SpinUp ? 0.5f : -0.5f));
	}

	float ElectronSpinQuantumNo()
	{ 
		return ms();
	}

};

double Electron::Mass = 9.10938356e-31;
double Electron::Charge = -1.60217662e-19;

class Proton
{
public:
	static double Mass; // kg
	static double Charge; // coulombs
};

double Proton::Mass = 1.672621898e-27;
double Proton::Charge = -1.60217662e-19;

class Neutron
{
public:
	static double Mass; // kg
};

double Neutron::Mass = 1.674927471e-27;



class DegenerativeOrbital
{
public:

	sbyte ml; // magnetic quantum number

	byte Active;

	Electron Electrons[2];

	DegenerativeOrbital(sbyte _ml)
	{
		ml = _ml;
		Active = 1;
	}

	DegenerativeOrbital()
	{
		ml = -100;
		Active = 0;
	}

	byte ElectronCount();

	void ClearElectrons();

	byte AddElectron();

};

byte DegenerativeOrbital::ElectronCount()
{
	byte i = 0;
	for (; (i < 2) && (Electrons[i].Active != Electron::Disabled) && Active; ++i);
	return i;
}

void DegenerativeOrbital::ClearElectrons()
{
	for (byte i = 0; i < 2; ++i)
		Electrons[i].SetSpin(Electron::Disabled);
}

byte DegenerativeOrbital::AddElectron()
{
	if (!Active)
		return 0;

	for (byte i = 0; i < 2; ++i)
	{
		if (Electrons[i].Active == Electron::Disabled)
		{
			Electrons[i].SetSpin(i == 0 ? Electron::SpinUp : Electron::SpinDown);
			return 1;
		}
	}

	return 0;
}


class Orbital
{
public:

	enum SubshellNotation
	{ 
		s = 0, 
		p, 
		d, 
		f, 
		g, 
		h 
	};

	DegenerativeOrbital DegenerativeOrbitals[7];


	Orbital() { }

	Orbital(byte l);

	byte nof_DegenerativeOrbitals();

	byte l() { return ((nof_DegenerativeOrbitals() - 1) / 2); }

	SubshellNotation OrbitCategory();

	char OrbitalNotation();

	byte Available() { return (nof_DegenerativeOrbitals() > 0) ? 1 : 0; }

	byte ElectronCount();

	void ClearElectrons();

	byte IsHalfFilled() { return ((ElectronCount() >= nof_DegenerativeOrbitals()) ? 1 : 0); }

	byte IsStrictlyHalfFilled() { return ((ElectronCount() == nof_DegenerativeOrbitals()) ? 1 : 0); }

	byte AddElectron(); // returns true if success else false

	byte AddElectrons(byte count); // returns number of electrons not added (0 => success)

	byte HaveElectrons(byte count); // returns number of electrons not added (0 => success)

};

Orbital::Orbital(byte L)
{
	for (sbyte ml = -L; ml <= L; ++ml)
		DegenerativeOrbitals[ml + L] = DegenerativeOrbital(ml);
}

byte Orbital::nof_DegenerativeOrbitals()
{
	byte i = 0;
	for (; i < 7 && DegenerativeOrbitals[i].Active; ++i);
	return i;
}

Orbital::SubshellNotation Orbital::OrbitCategory()
{
	if (!Available())
		return g;

	switch (l())
	{
	case 0: return s;
	case 1: return p;
	case 2: return d;
	case 3: return f;
	case 4: return g;

	default: return g;
	}
}

char Orbital::OrbitalNotation()
{
	if (!Available())
		return '0';

	switch (l())
	{
	case 0: return 's';
	case 1: return 'p';
	case 2: return 'd';
	case 3: return 'f';
	case 4: return 'g';
	default: return '0';
	}
}

byte Orbital::ElectronCount()
{
	byte count = 0;
	for (byte i = 0; i < nof_DegenerativeOrbitals() && DegenerativeOrbitals[i].ElectronCount(); ++i)
		count += DegenerativeOrbitals[i].ElectronCount();

	return count;
}

void Orbital::ClearElectrons()
{
	for (byte i = 0; i < 7; ++i)
		DegenerativeOrbitals[i].ClearElectrons();
}

byte Orbital::AddElectron()
{
	for (byte i = 0; i < nof_DegenerativeOrbitals(); ++i)
	{
		if (DegenerativeOrbitals[i].ElectronCount() == IsHalfFilled())
		{
			if (DegenerativeOrbitals[i].AddElectron())
				return 1;
		}
	}

	return 0;
}

byte Orbital::AddElectrons(byte count)
{
	for (; count > 0 && AddElectron(); --count);
	return count;
}

byte Orbital::HaveElectrons(byte count)
{
	ClearElectrons();
	return AddElectrons(count);
}


class Shell
{

	byte ___n;

public:

	Orbital Orbitals[4];

	Shell() { }

	Shell(byte n);

	byte nof_Orbitals();

	byte n() { return ___n; }

	char ShellNotation() { return char('J' + n()); }

	byte Available() { return (n() > 0); }

	byte ElectronCount();

	void ClearElectrons();

};

byte Shell::nof_Orbitals()
{
	byte i = 0;
	for (; i < 4 && Orbitals[i].Available(); ++i);
	return i;
}

Shell::Shell(byte _n)
{
	___n = _n;
	for (byte l = 0; l < _n && l < 4; ++l)
		Orbitals[l] = Orbital(l);
}

byte Shell::ElectronCount()
{
	byte count = 0;
	for (byte i = 0; i < nof_Orbitals() && Orbitals[i].ElectronCount(); ++i)
		count += Orbitals[i].ElectronCount();

	return count;
}

void Shell::ClearElectrons()
{
	for (byte i = 0; i < 4; ++i)
		Orbitals[i].ClearElectrons();
}




class NuclearProperties
{
public:

	Duration HalfLife;
	Duration Lifetime;

	NuclearProperties();

	bool Radioactive()
	{ 
		return (HalfLife.Value || Lifetime.Value || (HalfLife.Unit == Duration::Infinite) || (Lifetime.Unit == Duration::Infinite));
	}

};

NuclearProperties::NuclearProperties()
{
	HalfLife = Duration(0, Duration::Nanoseconds);
	Lifetime = Duration(0, Duration::Nanoseconds);
}


enum oxiphases
{
	n1 = 0x1,
	n2 = 0x2,
	n3 = 0x4, 
	n4 = 0x8, 
	n5 = 0x10,
	p1 = 0x20,
	p2 = 0x40,
	p3 = 0x80,
	p4 = 0x100,
	p5 = 0x200,
	p6 = 0x400,
	p7 = 0x800,
	p8 = 0x1000,
	p9 = 0x2000,
	phase_solid = 0x4000,
	phase_liquid = 0x8000,
	phase_gas = 0xC000
};


class AtomicProperties
{
public:

	enum Phases
	{ 
		Solid = 0, 
		Liquid, 
		Gas, 
		Other
	};

	float AtomicWeight;
	float Density;
	float AtomicRadius;
	unsigned int CovalentRadius;
	unsigned int VanderWaalsRadius;

	Temperature MeltingPoint;
	Temperature BoilingPoint;
		
	oxiphases mem_oxiphase; // 2 bytes for storing oxidation states and standard phase

	AtomicProperties();

	Phases Phase()
	{
		if ((mem_oxiphase & phase_gas) == phase_gas)
			return Gas;
		else if ((mem_oxiphase & phase_liquid) == phase_liquid)
			return Liquid;
		else if ((mem_oxiphase & phase_solid) == phase_solid)
			return Solid;
		return Other;
	}

};

AtomicProperties::AtomicProperties()
{
	AtomicWeight = 0;
	Density = 0;

	mem_oxiphase = (oxiphases) 0;

	AtomicRadius = 0; //pm
	CovalentRadius = 0;
	VanderWaalsRadius = 0;
}



class Element : public AtomicProperties, public NuclearProperties
{

public:

	enum Categories 
	{ 
		Other_NonMetals = 0, 
		NobleGases, 
		AlkaliMetals, 
		AlkalineEarthMetals, 
		TransitionMetals, 
		PostTransitionMetals, 
		Metalloids, 
		Halogens, 
		Lanthanoids, 
		Actinoids, 
		SuperActinoid, 
		NotDefined
	};

	byte Category;

	char X[4];
	char Name[24];
	char LatinName[32];
	char DiscoveredBy[64];

	enum Blocks
	{ 
		s_block,
		p_block,
		d_block,
		f_block,
		g_block, 
		h_block
	};

	unsigned int YearDiscovered;

	Shell ElectronShells[7];

	ubyte ProtonCount;

	ubyte NeutronCount;

	Element();
	

	void Initialize(const char x[], byte z, unsigned int a, const char name[], const char latinname[], Categories category, const char discoveredby[], unsigned int yeardiscovered, float atomicweight, float density, float meltingpointK, float boilingpointK, oxiphases oxiphase, float atomicradius, unsigned int covalentradius, unsigned int vanderwaalsradius, Duration halflife, Duration lifetime);
	
	Element(const char x[], byte z, unsigned int a);


	Element(const char x[], byte z, unsigned int a, const char name[], Categories category, const char discoveredby[], unsigned int yeardiscovered, float atomicweight, float density, float meltingpointK, float boilingpointK, oxiphases oxiphase, float atomicradius, unsigned int covalentradius, unsigned int vanderwaalsradius)
	{
		Initialize(x, z, a, name, "", category, discoveredby, yeardiscovered, atomicweight, density, meltingpointK, boilingpointK, oxiphase, atomicradius, covalentradius, vanderwaalsradius, Duration(0, Duration::Seconds), Duration(0, Duration::Seconds));
	}
	
	Element(const char x[], byte z, unsigned int a, const char name[], const char latinname[], Categories category, const char discoveredby[], unsigned int yeardiscovered, float atomicweight, float density, float meltingpointK, float boilingpointK, oxiphases oxiphase, float atomicradius, unsigned int covalentradius, unsigned int vanderwaalsradius)
	{
		Initialize(x, z, a, name, latinname, category, discoveredby, yeardiscovered, atomicweight, density, meltingpointK, boilingpointK, oxiphase, atomicradius, covalentradius, vanderwaalsradius, Duration(0, Duration::Seconds), Duration(0, Duration::Seconds));
	}


	Element(const char x[], byte z, unsigned int a, const char name[], Categories category, const char discoveredby[], unsigned int yeardiscovered, float atomicweight, float density, float meltingpointK, float boilingpointK, oxiphases oxiphase, float atomicradius, unsigned int covalentradius, unsigned int vanderwaalsradius, Duration halflife, Duration lifetime)
	{
		Initialize(x, z, a, name, "", category, discoveredby, yeardiscovered, atomicweight, density, meltingpointK, boilingpointK, oxiphase, atomicradius, covalentradius, vanderwaalsradius, halflife, lifetime);
	}
	
	Element(const char x[], byte z, unsigned int a, const char name[], const char latinname[], Categories category, const char discoveredby[], unsigned int yeardiscovered, float atomicweight, float density, float meltingpointK, float boilingpointK, oxiphases oxiphase, float atomicradius, unsigned int covalentradius, unsigned int vanderwaalsradius, Duration halflife, Duration lifetime)
	{
		Initialize(x, z, a, name, latinname, category, discoveredby, yeardiscovered, atomicweight, density, meltingpointK, boilingpointK, oxiphase, atomicradius, covalentradius, vanderwaalsradius, halflife, lifetime);
	}




	Orbital* GetOrbital(byte n, byte l)
	{ 
		return &ElectronShells[n - 1].Orbitals[l];
	}

	Orbital* OrbitalFillArrangement(byte position);

	byte SetElectrons(byte count);

	void SetProtons(ubyte count);

	void SetNeutrons(ubyte count);


	int Z();

	int A();

	byte ElectronCount();

	Orbital* OutermostOrbit();

	Shell* OutermostShell();

	byte IsStable()
	{ 
		return Group() == 18;
	}

	Orbital::SubshellNotation Block()
	{ 
		return OutermostOrbit() -> OrbitCategory();
	}

	byte Group();

	byte Period()
	{ 
		return OutermostShell() -> n(); 
	}

};

Element::Element()
{
	strcpy(X, "-");

	for (ubyte i = 0; i < 7; ++i)
		ElectronShells[i] = Shell(i + 1);

	SetElectrons(0);
	SetProtons(0);
	SetNeutrons(0);

	Category = NotDefined;
}

Element::Element(const char x[], byte z, unsigned int a)
{
	strcpy(X, x);

	for (byte i = 0; i < 7; ++i)
		ElectronShells[i] = Shell(i + 1);

	SetElectrons(z);
	SetProtons(z);
	SetNeutrons(a - z);

	Category = NotDefined;
	strcpy(Name, "");
	strcpy(LatinName, "");
	strcpy(DiscoveredBy, "");
	YearDiscovered = 0;
	
}

void Element::Initialize(const char x[], byte z, unsigned int a, const char name[], const char latinname[], Categories category, const char discoveredby[], unsigned int yeardiscovered, float atomicweight, float density, float meltingpointK, float boilingpointK, oxiphases oxiphase, float atomicradius, unsigned int covalentradius, unsigned int vanderwaalsradius, Duration halflife, Duration lifetime)
{
	strcpy(X, x);
	
	for (byte i = 0; i < 7; ++i)
		ElectronShells[i] = Shell(i + 1);

	SetElectrons(z);
	SetProtons(z);
	SetNeutrons(a - z);

	strcpy(Name, name);
	strcpy(LatinName, latinname);
	Category = category;
	strcpy(DiscoveredBy, discoveredby);
	YearDiscovered = yeardiscovered;
	AtomicWeight = atomicweight;
	Density = density;
	MeltingPoint = Temperature(meltingpointK, Temperature::Kelvin);
	BoilingPoint = Temperature(boilingpointK, Temperature::Kelvin);
	
	mem_oxiphase = oxiphase;

	AtomicRadius = atomicradius;
	CovalentRadius = covalentradius;
	VanderWaalsRadius = vanderwaalsradius;

	HalfLife = halflife;
	Lifetime = lifetime;
}


Orbital* Element::OrbitalFillArrangement(byte position)
{
	switch (position)
	{
	case 0: return GetOrbital(1, Orbital::s);
	case 1: return GetOrbital(2, Orbital::s);
	case 2: return GetOrbital(2, Orbital::p);
	case 3: return GetOrbital(3, Orbital::s);
	case 4: return GetOrbital(3, Orbital::p);
	case 5: return GetOrbital(4, Orbital::s);
	case 6: return GetOrbital(3, Orbital::d);
	case 7: return GetOrbital(4, Orbital::p);
	case 8: return GetOrbital(5, Orbital::s);
	case 9: return GetOrbital(4, Orbital::d);
	case 10: return GetOrbital(5, Orbital::p);
	case 11: return GetOrbital(6, Orbital::s);
	case 12: return GetOrbital(4, Orbital::f);
	case 13: return GetOrbital(5, Orbital::d);
	case 14: return GetOrbital(6, Orbital::p);
	case 15: return GetOrbital(7, Orbital::s);
	case 16: return GetOrbital(5, Orbital::f);
	case 17: return GetOrbital(6, Orbital::d);
	case 18: return GetOrbital(7, Orbital::p);
	case 19: return GetOrbital(5, Orbital::g);
	case 20: return GetOrbital(6, Orbital::f);
	case 21: return GetOrbital(7, Orbital::d);
	case 22: return GetOrbital(6, Orbital::g);
	case 23: return GetOrbital(7, Orbital::f);
	case 24: return GetOrbital(6, Orbital::h);
	case 25: return GetOrbital(7, Orbital::g);
	case 26: return GetOrbital(7, Orbital::h);
	default: return GetOrbital(7, Orbital::f);
	}
}

byte Element::SetElectrons(byte count)
{
	for (byte i = 0; i < 19 && count; ++i)
		count = OrbitalFillArrangement(i) -> AddElectrons(count);

	return count;
}

void Element::SetProtons(ubyte count)
{ 
	ProtonCount = count;
}

void Element::SetNeutrons(ubyte count)
{ 
	NeutronCount = count; 
}

int Element::Z()
{ 
	return (int)ProtonCount; 
}

int Element::A()
{ 
	return (int)NeutronCount + (int)ProtonCount; 
}


byte Element::ElectronCount()
{
	byte count = 0, i = 0;
	for (; i < 7;)
		count += ElectronShells[i++].ElectronCount();

	return count;
}

Orbital* Element::OutermostOrbit()
{
	byte i = 0;

	while (i < 19 && OrbitalFillArrangement(i) -> ElectronCount())
		++i;


	return OrbitalFillArrangement(i - 1);
}

Shell* Element::OutermostShell()
{
	byte i = 0;
	while (i < 7 && ElectronShells[i].ElectronCount())
		++i;

	return &ElectronShells[i - 1];
}

byte Element::Group()
{
	if (Z() == 2)
		return 18;

	if (Z() == 71 || Z() == 103)
		return 0;

	switch (Block())
	{
	case Orbital::s: return OutermostShell() -> ElectronCount();
	case Orbital::p: return OutermostShell() -> ElectronCount() + 10;
	case Orbital::d: return (GetOrbital(OutermostShell() -> n() - 1, Orbital::d) -> ElectronCount() + GetOrbital(OutermostShell() -> n(), Orbital::s) -> ElectronCount());
	}
	return 0;
}

#endif