/*
==========================================================
NAME:			ELM_FILE.H
AUTHOR:			RITHVIK NISHAD
ABOUT:			Alpha definition file for standard atomic element
Last Updated:	October 14, 2018
==========================================================
*/

#include <fstream.h>

#include "P_TABLE\\LIB\\CDEF.H"
#include "P_TABLE\\LIB\\QTYDEF.H"

#include "P_TABLE\\LIB\\ELEMENT.H"

#if !defined(__ELM_FILE_H)
#define __ELM_FILE_H

class Files
{
public:

	static char path[64];
	static char tempPath[64];

	static bool CheckFiles();

	static Element GetElement(byte z);

	static byte ElementCount();

	static bool AddElement(Element &element);
	static byte RemoveElement(byte z);
	
	static bool Clean();

	static void ResetFactoryDefaults();

};


char Files::path[] = "P_TABLE\\SRC\\ELEM.DAT";
char Files::tempPath[] = "P_TABLE\\SRC\\~TEL.DAT";

bool Files::CheckFiles()
{
	fstream f;
	f.open(path, ios::in | ios::out | ios::binary);

	if (!f)
		return false;

	f.seekg(0); // signature signed at beggining of file
	//f.read((char*)&FileSignature, sizeof(DigitalSignature));	
	f.close();

	return true;//(__DigitalSignature::Verify(DigitalSignature, FileSignature));
}

Element Files::GetElement(byte z)
{
	fstream f;
	f.open(path, ios::in | ios::binary);

	if (!f)
		return Element("N/A", 0, 20);

	//f.read((char*)&FileSignature, sizeof(DigitalSignature));

	Element buffer = Element("N/A", 0, 50);

	f.seekg(0);

	while(f.read((char*)&buffer, sizeof(buffer)))
	{
		if (buffer.Z() == z)
		{
			f.close();
			return buffer;
		}
	}

	f.close();
	return Element();
}

byte Files::ElementCount()
{
	fstream f;
	f.open(path, ios::in | ios::binary);

	if (!f)
		return 0;

	f.seekg(0);
	//f.read((char*)&FileSignature, sizeof(DigitalSignature));

	Element buffer;

	byte count = 0;
	for (; f.read((char*)&buffer, sizeof(buffer)); ++count);
	
	f.close();

	return count;
}

bool Files::AddElement(Element &element)
{
	fstream f;
	f.open(path, ios::out | ios::app | ios::binary);

	if(!f)
		return false;

	// Element buffer;

	// f.seekg(0);

	// while(f.read((char*)&buffer, sizeof(buffer)))
	// {
	// 	if (buffer.Z() == element.Z())
	// 	{
	// 		f.seekp(f.tellg() - sizeof(buffer));
	// 		f.write((char*)&element, sizeof(element));
	// 		f.close();
	// 		return 2;
	// 	}
	// }

	// f.seekp(ios::end);

	f.write((char*)&element, sizeof(element));
	f.close();

	return true;
}

byte Files::RemoveElement(byte z)
{
	fstream fO, fN;

	fO.open(path, ios::in | ios::binary);
	fN.open(tempPath, ios::out | ios::binary | ios::app);

	if (!fO || !fN)
		return 0;

	byte deleted = 0;

	for (Element buffer; fO.read((char*)&buffer, sizeof(buffer));)
	{
		if (buffer.Z() != z)
			fN.write((char*)&buffer, sizeof(buffer));
		else 
			++deleted;
	}

	fO.close();
	fN.close();

	remove(path);
	rename(tempPath, path);

	return deleted;
}

bool Files::Clean()
{
	remove(path);

	fstream f;

	f.open(path, ios::out | ios::binary | ios::trunc);

	if (!f)
		return false;

	f.seekp(0);
	//f.write((char*)&DigitalSignature, sizeof(DigitalSignature));
	f.close();

	return CheckFiles();
}

void Files::ResetFactoryDefaults()
{	
	Clean();

	Element *buff = 0;

	buff = new Element("H", 		1, 		1, 		"Hydrogen", 	"Hydrogenium", 	Element::Other_NonMetals, 		"Henry Cavendish", 													1766, 	1.0079, 	0.0000899, 	14.05, 		20.25, 		phase_gas | n1 | p1, 												29, 	38, 	120);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("He",		2, 		4, 		"Helium", 						Element::NobleGases, 			"Pierre Jules Cesar Janssen, Joseph Norman Lockyer", 				1895, 	4.0026, 	0.00017846, 0.95, 		4.25, 		phase_gas, 															31, 	32, 	140);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Li",		3, 		7, 		"Lithium", 						Element::AlkaliMetals, 			"Johan August Arfwedson", 											1817, 	6.941, 		0.534, 		453.65, 	1615.15, 	phase_solid | p1, 													145, 	134, 	182);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Be",		4, 		9, 		"Beryllium", 					Element::AlkalineEarthMetals,	"Louis-Nicolas Vauquelin", 											1797, 	9.0121, 	1.848, 		1551.15, 	3243.15, 	phase_solid | p1 | p2, 												112, 	90, 	153);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("B", 		5, 		11, 	"Boron", 		"Borum", 		Element::Metalloids, 			"Joseph Louis Gay-Lussac, Louis Jacques Thenard, Haumphry Davy", 	1808, 	10.811, 	2.34, 		2348.95, 	4199.95, 	phase_solid | n1 | n3 | n5 | p1 | p2 | p3,							87, 	82, 	192);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("C", 		6, 		12, 	"Carbon", 		"Carbonium", 	Element::Other_NonMetals, 		"Humphry Davy", 													1791, 	12.0107,	2.26, 		3823.15, 	4300.15, 	phase_solid | n1 | n2 | n3 | n4 | p1 | p2 | p3 | p4,				77, 	77, 	170);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("N", 		7, 		14, 	"Nitrogen", 	"Nitrogenium",	Element::Other_NonMetals , 		"Daniel Rutherford", 												1772, 	14.0067,	0.001251, 	63.25, 		77.35, 		phase_gas | n1 | n2 | n3 | p1 | p2 | p3 | p4 | p5,	 				92, 	75, 	155);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("O", 		8, 		16, 	"Oxygen", 		"Oxygenium", 	Element::Other_NonMetals, 		"Michal Sediwoj, Joseph Priestley, Carl Wilhelm Scheele", 			1774, 	15.9994,	0.00142987, 54.75, 		90.25, 		phase_gas | n1 | n2 | p1 | p2, 										48, 	73, 	152);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("F", 		9, 		19, 	"Flourine", 	"Fluorum", 		Element::Halogens, 				"Ferdinand Frederic Henri Moissan", 								1886, 	18.9984,	0.001696, 	53.45, 		85.05, 		phase_gas | n1, 													73, 	71, 	147);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ne",		10,		20, 	"Neon", 						Element::NobleGases, 			"Sir William Ramsay", 												1898, 	20.1797,	0.0009002, 	24.55, 		27.05, 		phase_gas, 															38, 	69, 	154);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Na",		11,		23, 	"Sodium", 		"Natrium", 		Element::AlkaliMetals, 			"Humphry Davy", 													1807, 	22.9897,	0.971, 		370.95, 	1156.1, 	phase_solid | n1 | p1, 												190, 	154, 	227);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Mg",		12,		24, 	"Magnesium", 					Element::AlkalineEarthMetals, 	"Grigory Nikolaevich Neuimin, Joseph Black", 						1755, 	24.3050,	1.738, 		923.15, 	1363.15, 	phase_solid | p1 | p2, 												143, 	130, 	173);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Al",		13,		27, 	"Aluminium", 					Element::PostTransitionMetals, 	"Hans Christian Orsted", 											1825, 	26.9815,	2.6989, 	933.15, 	2791.97, 	phase_solid | n1 | n2 | p1 | p2 | p3, 								143, 	118, 	184);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Si",		14,		28, 	"Silicon", 		"Silicum", 		Element::Metalloids, 			"Jons Jakob Berzelius", 											1824, 	28.0855,	2.33, 		1688.0, 	3172.95, 	phase_solid | n1 | n2 | n3 | n4 | p1 | p2 | p3 | p4, 				132, 	111, 	210);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("P", 		15,		31, 	"Phosphorus", 					Element::Other_NonMetals, 		"Hennig Brand", 													1669, 	30.9737,	2.82, 		317.3, 		555.0, 		phase_solid | n1 | n2 | n3 | p1 | p2 | p3 | p4 | p5, 				128, 	106, 	180);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("S", 		16,		32, 	"Sulphur", 						Element::Other_NonMetals,      "",																	1774, 	32.065, 	2.070, 		386.0, 		717.82, 	phase_solid | n1 | n2 | p1 | p2 | p3 | p4 | p5 | p6, 				127, 	102, 	180);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Cl",		17,		35, 	"Chlorine", 	"Clorum", 		Element::Halogens, 				"Carl Wilhelm Scheele", 											1774, 	35.453, 	0.003214, 	172.2, 		238.6, 		phase_gas | n1 | p1 | p2 | p3 | p4 | p5 | p6 | p7, 					99, 	99, 	175);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ar",		18,		40, 	"Argon", 						Element::NobleGases, 			"Sir William Ramsay", 												1894, 	39.948, 	0.001784, 	83.8, 		87.3, 		phase_gas,															71, 	97, 	188);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("K", 		19,		39, 	"Potassium", 	"Kalium", 		Element::AlkaliMetals, 			"Humphry Davy", 													1807, 	39.0983, 	0.856, 		336.8, 		1047.0, 	phase_solid | n1 | p1, 												235, 	196, 	275);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ca",		20,		40,		"Calcium",						Element::AlkalineEarthMetals,	"Humphry Davy",														1808, 	40.078,		1.55,		1112.0,		1757.0,		phase_solid | p1 | p2,												197,	174,	231);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Sc",		21, 	45,		"Scandium", 					Element::TransitionMetals, 		"Lars Fredrik Nilson",												1879, 	44.9559,	2.99,		1814.15,	3109.15,	phase_solid | p1 | p2 | p3,											162,	144,	211);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ti",		22, 	48, 	"Titanium",						Element::TransitionMetals,		"William Gregor", 													1791, 	47.867,		4.54,		1933.15,	3558.15,	phase_solid | n1 | n2 | p1 | p2 | p3 | p4, 							147,	136,	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("V", 		23, 	51, 	"Vanadium",						Element::TransitionMetals, 		"Andres Manuel del Rio",											1801, 	50.9415,	6.11,		2183.15,	3680.15,	phase_solid | n1 | n3 | p1 | p2 | p3 | p4 | p5,						134,	125,	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Cr",		24, 	52, 	"Chromium", 					Element::TransitionMetals, 		"Louis-Nicolas Vauquelin", 											1797, 	51.9961,	7.19,		2128.15,	2943.15,	phase_solid | n1 | n2 | n4 | p1 | p2 | p3 | p4 | p5 | p6, 			130,	127,	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Mn",		25, 	55, 	"Manganese", 	"Manganum", 	Element::TransitionMetals, 		"Johan Gottlieb Gahn, Ignatius Gottfried Kaim", 					1774, 	54.9380, 	7.21, 		1515.15, 	2233.15, 	phase_solid | n1 | n2 | n4 | p1 | p2 | p3 | p4 | p5 | p6 | p7, 		127,	139,	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Fe",		26, 	56, 	"Iron", 		"Ferrum", 		Element::TransitionMetals,		"",																	0, 		55.845, 	7.88, 		1809.0, 	3132.15, 	phase_solid | n1 | n2 | n4 | p1 | p2 | p3 | p4 | p5 | p6, 			126,	125,	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Co",		27, 	59, 	"Cobalt", 		"Cobaltum", 	Element::TransitionMetals, 		"Georg Brandt", 													1735, 	58.9331, 	8.9, 		1766.15, 	3141.15, 	phase_solid | n1 | n3 | p1 | p2 | p3 | p4 | p5,						125, 	126, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ni",		28, 	59, 	"Nickel", 		"Niccolum", 	Element::TransitionMetals, 		"Axel Fredric von Cronstedt", 										1751, 	58.6932,	8.902, 		1726.15, 	3005.15, 	phase_solid | n1 | n2 | p1 | p2 | p3 | p4, 							124, 	121, 	163);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Cu",		29, 	63, 	"Copper", 		"Cuprum", 		Element::TransitionMetals,		"",																	1735, 	63.546, 	8.92, 		1356.55, 	2838.15, 	phase_solid | n2 | p1 | p2 | p3 | p4, 								128, 	138, 	140);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Zn",		30, 	65, 	"Zinc", 		"Zincum", 		Element::TransitionMetals, 		"Andreas Sigismund Marggraf", 										1738, 	65.409,		7.133, 		692.75, 	1179.35, 	phase_solid | n2 | p1 | p2,											142,	131, 	139);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ga",		31, 	70,		"Gallium", 						Element::PostTransitionMetals, 	"Paul Emile Lecoq de Boisbaudran", 									1875, 	69.723, 	5.91, 		302.95, 	2475.15, 	phase_solid | n1 | n2 | n4 | n5 | p1 | p2 | p3, 					141, 	126, 	187);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ge",		32, 	73, 	"Germanium", 					Element::Metalloids, 			"Clemens Alexander Winkler", 										1886, 	72.64, 		5.323, 		1208.75, 	3101.15, 	phase_solid | n1 | n2 | n3 | n4 | p1 | p2 | p3 | p4, 				122, 	122, 	211);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("As",		33, 	75, 	"Arsenic", 		"Arsenicum", 	Element::Metalloids, 			"", 																1250, 	74.9216, 	5.72, 		1089.95, 	886.15, 	phase_solid | n1 | n2 | n3 | p1 | p2 | p3 | p4 | p5,				139,	119, 	185);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Se",		34, 	79, 	"Selenium", 					Element::Other_NonMetals, 		"Jons Jakob Berzelius", 											1817, 	78.96, 		4.79, 		488.15, 	956.25, 	phase_solid | n1 | n2 | p1 | p2 | p3 | p4 | p5 | p6, 				140,	116, 	190);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Br",		35, 	80, 	"Bromine", 		"Bromum", 		Element::Halogens, 				"Antoine-Jerome Balard, Karl Jakob Leuwich", 						1826, 	79.904, 	3.14, 		264.85, 	331.95, 	phase_liquid | n1 | p1 | p3 | p4 | p5 | p7, 						115,	114, 	185);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Kr",		36, 	84, 	"Krypton", 						Element::NobleGases, 			"Sir William Ramsay, Morris William Travers", 						1898, 	83.798, 	0.003749, 	116.55, 	120.85, 	phase_gas | p2, 													88, 	110, 	202);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Rb",		37, 	85, 	"Rubidium", 					Element::AlkaliMetals, 			"Robert Wilhelm Bunsen, Gustav Robert Kirchhoff", 					1861, 	85.467, 	1.53, 		312.15, 	961.15, 	phase_solid | n1 | p1, 												265, 	211, 	303);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Sr",		38, 	88, 	"Strontium", 					Element::AlkalineEarthMetals, 	"Adair Crawford", 													1790, 	87.62, 		2.54, 		1050.15, 	1655.15, 	phase_solid | p1 | p2, 												215, 	192, 	249);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Y",			39, 	89, 	"Yttrium", 						Element::TransitionMetals, 		"Johan Godalin", 													1794, 	88.905, 	4.47, 		1798.15, 	3610.15, 	phase_solid | p1 | p2 | p3, 										212,	162, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Zr",		40, 	91, 	"Zirconium", 					Element::TransitionMetals, 		"Martin Heinrich Klaproth", 										1789, 	91.224,		6.51, 		2125.15, 	4650.15, 	phase_solid | n2 | p1 | p2 | p3 | p4, 								160, 	148, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Nb",		41, 	92, 	"Niobium", 						Element::TransitionMetals, 		"Charles Hatchett", 												1801, 	92.906, 	8.58, 		2741.15, 	5015.15, 	phase_solid |  n1 | n3 | p1 | p2 | p3 | p4 | p5, 					146, 	137, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Mo",		42, 	96, 	"Molybdenum", 					Element::TransitionMetals, 		"Carl Wilhelm Scheele", 											1781, 	95.94, 		10.22, 		2890.15, 	4883.15, 	phase_solid | n1 | n2 | n4 | p1 | p2 | p3 | p4 | p5 | p6, 			139, 	145, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Tc",		43, 	98, 	"Technetium", 					Element::TransitionMetals, 		"Emilio Gino Segre, Carlo Perrier", 								1937, 	98.906, 	11.49, 		2430.15, 	4538.15, 	phase_solid | n1 | n3 | p1 | p2 | p3 | p4 | p5 | p6 | p7, 			136, 	156, 	0,		Duration(41194, Duration::Years),	Duration(60207, Duration::Years));
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ru",		44, 	102, 	"Ruthenium", 					Element::TransitionMetals, 		"Karl Ernst Claus", 												1844, 	101.07, 	12.41, 		2607.15, 	4350.15, 	phase_solid | n2 | n4 | p1 | p2 | p3 | p4 | p5 | p6 | p7 | p8, 		134, 	126, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Rh",		45, 	102, 	"Rhodium", 						Element::TransitionMetals, 		"William Hyde Wollaston", 											1803, 	102.905, 	12.41, 		2239.15, 	4000.15, 	phase_solid | n1 | n3 | p1 | p2 | p3 | p4 | p5 | p6, 				134,	135, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Pd",		46, 	106, 	"Palladium", 					Element::TransitionMetals, 		"William Hyde Wollaston", 											1803, 	106.4, 		12.02, 		1825.15, 	2938.15, 	phase_solid | p1 | p2 | p3 | p4, 									137,	131, 	163);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ag",		47, 	108, 	"Silver", 		"Argentum", 	Element::TransitionMetals,		"",																	0, 		107.868, 	10.49, 		1235.05,	2435.15, 	phase_solid | n1 | n2 | p1 | p2 | p3, 								144, 	153, 	172);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Cd",		48, 	112, 	"Cadmium", 						Element::TransitionMetals,		"",																	1817, 	112.411, 	8.64, 		592.25, 	1038.15, 	phase_solid | n2 | p1 | p2, 										154,	148, 	158);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("In",		49, 	115, 	"Indium", 						Element::PostTransitionMetals, 	"Ferdinan Reich",													1863, 	114.818, 	7.31, 		428.35, 	2353.15, 	phase_solid | n1 | n2 | n5 | p1 | p2 | p3, 							166, 	144, 	193);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Sn",		50, 	119, 	"Tin", 			"Stannum", 		Element::PostTransitionMetals, 	"", 																0, 		118.710, 	7.29, 		505.15, 	2871.15, 	phase_solid | n1 | n2 | n3 | n4 | p1 | p2 | p3 | p4, 				162,	141, 	217);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Sb",		51, 	121, 	"Antimony", 	"Stibium", 		Element::Metalloids, 			"Basil Valentine", 													0, 		121.760, 	6.69, 		903.85, 	1860.15, 	phase_solid | n1 | n2 | n3 | p1 | p2 | p3 | p4 | p5, 				133, 	138, 	206);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Te",		52, 	127, 	"Tellurium", 					Element::Metalloids, 			"", 																1783, 	127.60, 	6.25, 		722.75, 	1263.15, 	phase_solid | n1 | n2 | p1 | p2 | p3 | p4 | p5 | p6,				160, 	135, 	206);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("I", 		53, 	127, 	"Iodine", 		"Iodium", 		Element::Halogens, 				"", 																1811, 	126.904, 	4.94, 		386.65, 	457.55, 	phase_solid | n1 | p1 | p3 | p4 | p5 | p6 | p7,						136, 	133, 	198);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Xe",		54, 	131, 	"Xenon", 						Element::NobleGases,			"", 																1898, 	131.293, 	0.005894, 	161.25, 	166.15, 	phase_gas | p2 | p4 | p6 | p8, 										108,	130, 	216);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Cs",		55, 	133, 	"Caesium", 						Element::AlkaliMetals, 			"Robert Wihelm Bunsen, Gustav Robert Kirchhoff", 					1860, 	132.905, 	1.9, 		301.59, 	963.15, 	phase_solid | n1 | p1, 												267,	225, 	343);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ba",		56, 	137, 	"Barium", 						Element::AlkalineEarthMetals, 	"Humphry Davy", 													1808, 	137.327, 	3.5, 		1000.15, 	2170.15, 	phase_solid | p1 | p2, 												222, 	198, 	268);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("La",		57,		139, 	"Lanthanum", 					Element::Lanthanoids, 			"Carl Gustaf Mosander", 											1839, 	138.905, 	6.16, 		1193.15, 	3727.15, 	phase_solid | p1 | p2 | p3, 										187, 	169, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ce",		58, 	140, 	"Cerium", 						Element::Lanthanoids, 			"", 																1803, 	140.116, 	6.77, 		1071.15, 	3716.15, 	p2 | p3 | p4, 														181, 	0,		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Pr",		59,		141, 	"Praseodymium", 				Element::Lanthanoids, 			"Andre-Louis Debieren", 											1885, 	140.904, 	6.773, 		1204.15, 	3563.15, 	phase_solid | p2 | p3 | p4 | p5, 									182, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Nd",		60, 	144,	"Neodymium", 					Element::Lanthanoids, 			"Andr-Louis Debieren", 												1885, 	144.242, 	7, 			1283.15, 	3339.15, 	p2 | p3 | p4, 														182, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Pm",		61, 	146, 	"Promethium", 					Element::Lanthanoids, 			"", 																1945, 	146.915, 	7.2, 		1439.15, 	3271.15, 	phase_solid | p2 | p3, 												183, 	0, 		0,		Duration(18, Duration::Years), 		Duration(25.5, Duration::Years));
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Sm",		62, 	150,	"Samarium", 					Element::Lanthanoids, 			"Paul Emile Lecoq de Boisbaudran", 									1879, 	150.36, 	7.54, 		1345.15, 	2051.15, 	phase_solid | p2 | p3, 												181, 	166, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Eu",		63, 	152, 	"Europium", 					Element::Lanthanoids, 			"Eugene-Anatole Demarcay", 											1901, 	151.964, 	5.25, 		1095.15, 	1870.15, 	phase_solid | p2 | p3, 												199, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Gd",		64, 	157, 	"Gadaolinium", 					Element::Lanthanoids, 			"Jean Charles Galissard de Marignac", 								1880, 	157.25, 	7.89, 		1584.15, 	3537.15, 	phase_solid | p1 | p2 | p3, 										179, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Tb",		65, 	158, 	"Terbium", 						Element::Lanthanoids, 			"Carl Gustaf Mosander", 											1843, 	158.925, 	8.25, 		1633.15, 	3294.15, 	phase_solid | p1 | p2 | p3 | p4, 									180, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Dy",		66, 	162, 	"Dysprosium", 					Element::Lanthanoids, 			"Paul Emile Lecoq de Boisbaudran", 									1886, 	162.5, 		8.56, 		1682.15, 	2833.15, 	p2 | p3 | p4, 														180, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ho",		67, 	164, 	"Holmium", 						Element::Lanthanoids, 			"Auguste Honore Charlois", 											1878, 	164.93, 	8.78, 		1743.15, 	2966.15, 	phase_solid | p2 | p3, 												179, 	0,		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Er",		68,		167, 	"Erbium", 						Element::Lanthanoids, 			"Carl Gustaf Mosander", 											1842, 	167.259, 	9.05, 		1795.15, 	3134.15, 	phase_solid | p2 | p3, 												178, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Tm",		69, 	168, 	"Thulium", 						Element::Lanthanoids, 			"", 																1879, 	168.934, 	9.32, 		1818.15, 	2218.15, 	phase_solid | p2 | p3, 												177, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Yb",		70, 	169, 	"Ytterbium", 					Element::Lanthanoids, 			"Jean Charles Galissard de Marignac", 								1878, 	173.04, 	6.97, 		1097.15, 	1466.15, 	phase_solid | p2 | p3, 												194, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Lu",		71, 	175, 	"Lutetium", 					Element::Lanthanoids, 			"", 																1907, 	174.967, 	9.84, 		1929.15, 	366.15, 	phase_solid | p3, 													175, 	0, 		0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Hf",		72, 	178, 	"Hafnium", 						Element::TransitionMetals,		"",																	1923, 	178.49, 	13.31, 		2506.15, 	4876.15, 	phase_solid | n2 | p1 | p2 | p3 | p4, 								167, 	150, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Ta",		73, 	180, 	"Tantalum", 					Element::TransitionMetals,		"",																	1802, 	180.947, 	16.68, 		3290.15, 	5731.15, 	phase_solid |  n1 | n3 | p1 | p2 | p3 | p4 | p5, 					149, 	138, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("W",			74, 	184, 	"Tungsten", 					Element::TransitionMetals, 		"Carl Wilhelm Scheele", 											1783, 	183.84, 	19.26, 		3860.15, 	5828.15, 	phase_solid | n1 | n2 | n4 | p1 | p2 | p3 | p4 | p5 | p6,			141,	146, 	0);
	AddElement(*buff);	
	delete buff;	

	buff = new Element("Re",		75, 	186, 	"Rhenium", 						Element::TransitionMetals, 		"",																	1925, 	186.207, 	21.03, 		3453.15, 	5896.15, 	phase_solid | n1 | n3 | p1 | p2 | p3 | p4 | p5 | p6 | p7, 			137, 	159, 	0);
	AddElement(*buff);
	delete buff;

	buff = new Element("Os",		76, 	190, 	"Osmium", 						Element::TransitionMetals, 		"Smithson Tennant", 												1803, 	190.23, 	22.587, 	3318.15, 	5300.15, 	phase_solid | n1 | n2 | n4 | p1 | p2 | p3 | p4 | p5 | p6 | p7 | p8,	135, 	128, 	0);
	AddElement(*buff);
	delete buff;

	buff = new Element("Ir",		77, 	192, 	"Iridium", 						Element::TransitionMetals, 		"Smithson Tennant", 												1803, 	192.217, 	22.562, 	2683.15, 	4701.15, 	phase_solid | n1 | n3 | p1 | p2 | p3 | p4 | p5 | p6 | p7 | p8 | p9, 	136, 	137, 	0);
	AddElement(*buff);
	delete buff;

	buff = new Element("Pt",		78, 	195, 	"Platinum", 					Element::TransitionMetals, 		"Antonio de Ulloa", 												1735, 	195.084, 	21.45, 		2041.15, 	4098.15, 	phase_solid | n1 | n2 | n3 | p1 | p2 | p3 | p4 | p5 | p6, 			139, 	128, 	175);
	AddElement(*buff);
	delete buff;

	buff = new Element("Au",		79, 	197, 	"Gold", 		"Aurum", 		Element::TransitionMetals,		"",																	1732, 	196.966, 	19.3, 		1337.55, 	3129.15, 	phase_solid | n1 | n2 | n3 | p1 | p3, 								144, 	144, 	186);
	AddElement(*buff);
	delete buff;

	buff = new Element("Hg",		80, 	200, 	"Mercury", 		"Hydragyrum", 	Element::TransitionMetals,		"",																	1735, 	200.59, 	13.55, 		234.25, 	629.75, 	phase_liquid | n2 | p1 | p2, 										157, 	149, 	155);
	AddElement(*buff);
	delete buff;

	buff = new Element("Tl",		81, 	204, 	"Thallium", 					Element::PostTransitionMetals, 	"William Crookes", 													1861, 	204.383, 	11.85, 		576.75, 	1746.15, 	phase_solid | n1 | n2 | n5 | p1 | p2 | p3, 							171, 	148, 	196);
	AddElement(*buff);
	delete buff;

	buff = new Element("Pb",		82, 	207, 	"Lead", 		"Plumbum", 		Element::PostTransitionMetals, 	"", 																1899, 	207.2, 		11.34, 		600.65, 	2013.15, 	phase_solid | n1 | n2 | n4 | p1 | p2 | p3 | p4,						175, 	147, 	202);
	AddElement(*buff);
	delete buff;

	buff = new Element("Bi",		83, 	209, 	"Bismuth", 		"Bismuthum", 	Element::PostTransitionMetals, 	"Claude Francois Geoffrey", 										1739, 	208.9804, 	9.8, 		544.55, 	1833.15, 	phase_solid | n1 | n2 | n3 | p1 | p2 | p3 | p4 | p5 | p6, 			170, 	146, 	207);
	AddElement(*buff);
	delete buff;

	buff = new Element("Po",		84, 	210, 	"Polonium", 					Element::Metalloids, 			"Pierre Curie, Marie Sklodowska Curie", 							1898, 	208.9824, 	9.2, 		527.15, 	1235.15, 	phase_solid | n2 | p2 | p4 | p5 | p6, 								176, 	146, 	197,	Duration(102, Duration::Years), 	Duration(148, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("At", 		85, 	211, 	"Astatine", 	"Astatum", 		Element::Halogens, 				"Paul Emile Lecoq de Boisbaudran", 									1940, 	209.9871, 	6.4, 		503.15, 	575.15, 	phase_solid | n1 | p1 | p3 | p5 | p7, 								145, 	0, 		202, 	Duration(8.2, Duration::Hours), 	Duration(11.6, Duration::Hours));
	AddElement(*buff);
	delete buff;

	buff = new Element("Rn", 		86, 	222, 	"Radon", 						Element::NobleGases, 			"Friedreich Enrst Dorn", 											1900, 	222.0176, 	0.0098, 	202.15, 	211.35, 	phase_gas | p2 | p6, 												214, 	145, 	220, 	Duration(3.8, Duration::Days), 		Duration(5.5, Duration::Days));
	AddElement(*buff);
	delete buff;

	buff = new Element("Fr", 		87, 	223, 	"Francium", 					Element::AlkaliMetals, 			"Marguerite Perey", 												1939, 	223.0197, 	1.87, 		293.15, 	923.15, 	phase_solid | p1, 													2.7, 	0, 		348, 	Duration(21.6, Duration::Minutes), 	Duration(30, Duration::Minutes));
	AddElement(*buff);
	delete buff;

	buff = new Element("Ra", 		88, 	226, 	"Radium", 						Element::AlkalineEarthMetals, 	"Pierre Curie, Marie Sklodowska Curie", 							1898, 	226.0254, 	5.5, 		1231.15, 	2008.15, 	phase_solid | p2, 													215, 	0, 		283, 	Duration(1584, Duration::Years), 	Duration(2313, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("Ac", 		89, 	227,	"Actinium", 					Element::Actinoids, 			"Andre-Louis Debieren", 											1899, 	227.0278, 	10.07, 		1320.15, 	3470.15, 	phase_solid | p3, 													188, 	0, 		0, 		Duration(21.7, Duration::Years), 	Duration(31.5, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("Th", 		90, 	232, 	"Thorium", 						Element::Actinoids, 			"Jons Jakob Berzelius", 											1828, 	232.038, 	11.72, 		2023.15, 	5060.15, 	phase_solid | p1 | p2 | p3 | p4 | p5, 								180, 	0, 		0, 		Duration(Duration::Infinite),		Duration(Duration::Infinite));
	AddElement(*buff);
	delete buff;

	buff = new Element("Pa", 		91, 	231, 	"Protactinium", 				Element::Actinoids, 			"Willima Crookes", 													1913, 	231.0358,	15.37, 		2113.15, 	4303.15, 	phase_solid | p3 | p4 | p5, 										161, 	0, 		0, 		Duration(32765, Duration::Years), 	Duration(47246, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("U", 		92, 	238, 	"Uranium", 						Element::Actinoids, 			"Martin Heinrich Klaproth", 										1789, 	238.0289, 	19.05, 		1405.55, 	4016.15, 	phase_solid | p1 | p2 | p3 | p4 | p5 | p6, 							156, 	196, 	186, 	Duration(Duration::Infinite), 		Duration(Duration::Infinite));
	AddElement(*buff);
	delete buff;

	buff = new Element("Np", 		93, 	239, 	"Neptunium", 					Element::Actinoids, 			"", 																1940, 	237.0482, 	20.48, 		913.15, 	4173.15, 	phase_solid | p2 | p3 | p4 | p5 | p6 | p7, 							130, 	0, 		0, 		Duration(2144, Duration::Years), 	Duration(31000, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("Pu", 		94, 	244, 	"Plutonium", 					Element::Actinoids, 			"Glenn Theodore Seaborg", 											1940, 	244.0642, 	19.74, 		914.15, 	3508.15, 	phase_solid | p2 | p3 | p4 | p5 | p6 | p7, 							162, 	0, 		0, 		Duration(Duration::Infinite), 		Duration(Duration::Infinite));
	AddElement(*buff);
	delete buff;

	buff = new Element("Am", 		95, 	243, 	"Americium", 					Element::Actinoids, 			"Glenn Theodore Seaborg", 											1944, 	243.0614, 	13.67, 		1449.15, 	2880.15, 	phase_solid | p2 | p3 | p4 | p5 | p6 | p7, 							173, 	0, 		0, 		Duration(7383, Duration::Years), 	Duration(10647, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("Cm", 		96, 	247, 	"Curium", 						Element::Actinoids, 			"Glenn Theodore Seaborg", 											1944, 	247.0703, 	13.51, 		1613.15, 	3381.15, 	phase_solid | p3 | p4 | p6, 										299, 	0, 		0, 		Duration(155905, Duration::Years), 	Duration(224985, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("Bk", 		97, 	247, 	"Berkelium", 					Element::Actinoids, 			"Glenn Theodore Seaborg", 											1949, 	247.0703, 	13.25, 		1259.15, 	2898.15, 	phase_solid | p3 | p4, 												297, 	0, 		0, 		Duration(1378, Duration::Years), 	Duration(1990, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("Cf", 		98, 	251, 	"Californium", 					Element::Actinoids, 			"Glenn Theodore Seaborg", 											1950, 	251.0796, 	15.1, 		1173.15, 	1743.15, 	p2 | p3 | p4, 														295, 	0, 		0, 		Duration(899.9, Duration::Years), 	Duration(1299, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("Es", 		99, 	252, 	"Einsteinium", 					Element::Actinoids, 			"Glenn Theodore Seaborg", 											1952, 	252.0829, 	13.5, 		1133.15, 	0, 			p2 | p3 | p4, 														292, 	0, 		0, 		Duration(1.2, Duration::Years), 	Duration(1.8, Duration::Years));
	AddElement(*buff);
	delete buff;

	buff = new Element("Fm", 		100, 	257, 	"Fermium",	 					Element::Actinoids, 			"Glenn Theodore Seaborg", 											1952, 	257.0951, 	19.05, 		1798.15, 	0, 			p2 | p3, 															290, 	0, 		0, 		Duration(101, Duration::Days), 		Duration(145, Duration::Days));
	AddElement(*buff);
	delete buff;

	buff = new Element("Md", 		101, 	258, 	"Mendelevium", 					Element::Actinoids, 			"Glenn Theodore Seaborg", 											1955, 	258.0951, 	0, 			1098.15, 	0, 			p2 | p3, 															287, 	0, 		0, 		Duration(51.5, Duration::Days), 	Duration(74.3, Duration::Days));
	AddElement(*buff);
	delete buff;

	buff = new Element("No", 		102, 	259, 	"Nobelium",  					Element::Actinoids, 			"Glenn Theodore Seaborg", 											1958, 	259.1009, 	0, 			1098.15, 	0, 			p2 | p3, 															285, 	0, 		0, 		Duration(2.7, Duration::Hours), 	Duration(5.5555, Duration::Hours));
	AddElement(*buff);
	delete buff;

	buff = new Element("Lr", 		103, 	262, 	"Lawrencium", 					Element::Actinoids, 			"Albert Ghiorso", 													1961, 	266.1193, 	0, 			1898.15, 	0, 			p3, 																282, 	0, 		0, 		Duration(10, Duration::Hours), 	Duration(14.4, Duration::Hours));
	AddElement(*buff);
	delete buff;

	buff = new Element("Rf", 		104, 	267, 	"Rutherfordium", 				Element::TransitionMetals, 		"Georgiy Flerov", 													1968, 	261, 		23, 		0, 			0, 			p4, 																0, 		0, 		0, 		Duration(80, Duration::Minutes), 	Duration(1.8, Duration::Hours));
	AddElement(*buff);
	delete buff;

	buff = new Element("Db", 		105, 	268, 	"Dubnium", 						Element::TransitionMetals, 		"Georgiy Flerov", 													1970, 	262, 		29, 		0, 			0, 			p5, 																0, 		0, 		0, 		Duration(5.5, Duration::Hours), 	Duration(8.3, Duration::Hours));
	AddElement(*buff);
	delete buff;

	buff = new Element("Sg", 		106, 	271,	"Seaborgium", 					Element::TransitionMetals, 		"Georgiy Flerov", 													1974, 	262, 		35, 		0, 			0, 			p6, 																0, 		0, 		0, 		Duration(2, Duration::Hours), 		Duration(2.7, Duration::Hours));
	AddElement(*buff);
	delete buff;

	buff = new Element("Bh", 		107, 	270, 	"Bohrium", 						Element::TransitionMetals, 		"Peter Armbruster, Gottfried Munzenber", 							1976, 	264, 		37, 		0, 			0, 			p7, 																0, 		0, 		0, 		Duration(1.5, Duration::Hours), 	Duration(2.1, Duration::Hours));
	AddElement(*buff);
	delete buff;

	buff = new Element("Hs", 		108, 	278, 	"Hassium", 						Element::TransitionMetals, 		"GSI", 																1984, 	269,		0, 			0, 			0, 			p8, 																0, 		0, 		0, 		Duration(1.1, Duration::Hours), 	Duration(1.4, Duration::Hours));
	AddElement(*buff);
	delete buff;

	buff = new Element("Mt", 		109, 	281, 	"Meitnerium", 					Element::TransitionMetals, 		"GSI", 																1982, 	268,		37.4,		0, 			0, 			(oxiphases)0, 														0, 		0, 		0, 		Duration(30, Duration::Minutes), 	Duration(43.3, Duration::Minutes));
	AddElement(*buff);
	delete buff;

	buff = new Element("Ds", 		110, 	281, 	"Darmstadtium", 				Element::TransitionMetals, 		"GSI", 																1994, 	281.1620,	34.8, 		0, 			0, 			(oxiphases)0,														0, 		0, 		0, 		Duration(4, Duration::Minutes), 	Duration(6, Duration::Minutes));
	AddElement(*buff);
	delete buff;

	buff = new Element("Rg", 		111, 	281, 	"Roentgenium",	 				Element::TransitionMetals, 		"GSI", 																1994, 	281.1684,	0, 			0, 			0, 			(oxiphases)0,														0, 		0, 		0, 		Duration(10, Duration::Minutes), 	Duration(14.5, Duration::Minutes));
	AddElement(*buff);
	delete buff;

	buff = new Element("Cn", 		112, 	285, 	"Copernicium", 					Element::TransitionMetals, 		"GSI", 																1996, 	285.1744,	20,			0, 			0, 			p2,																	0, 		0, 		0, 		Duration(40, Duration::Minutes), 	Duration(58, Duration::Minutes));
	AddElement(*buff);
	delete buff;

	buff = new Element("Nh", 		113, 	284, 	"Nihonium", 					Element::PostTransitionMetals,	"GSI", 																2004, 	286.1810,	16, 		698.15,		1428.15,	(oxiphases)0,														170,	0, 		0, 		Duration(20, Duration::Minutes), 	Duration(29, Duration::Minutes));
	AddElement(*buff);
	delete buff;

	buff = new Element("Fl", 		114, 	289, 	"Flerovium", 					Element::PostTransitionMetals, 	"ONRN", 															1999, 	287.1904, 	14, 		341.15, 	419.15, 	(oxiphases)0, 														0, 		0, 		0, 		Duration(80, Duration::Seconds), 	Duration(2, Duration::Minutes));
	AddElement(*buff);
	delete buff;

	buff = new Element("Mc", 		115, 	289, 	"Moscovium", 					Element::PostTransitionMetals, 	"ORNR, LLNL", 														2004, 	288.1943, 	13.5, 		0, 			0, 			(oxiphases)0, 														0, 		0, 		0, 		Duration(60, Duration::Seconds), 	Duration(1.5, Duration::Minutes));
	AddElement(*buff);
	delete buff;

	buff = new Element("Lv", 		116, 	292, 	"Livermorium", 					Element::PostTransitionMetals, 	"ONRN, LLNL", 														2000, 	291.2045, 	0, 			0, 			0, 			(oxiphases)0, 														0, 		175, 	0, 		Duration(0.12, Duration::Seconds), 	Duration(0.173, Duration::Seconds));
	AddElement(*buff);
	delete buff;

	buff = new Element("Ts", 		117, 	294, 	"Tennessine", 					Element::Halogens,	 			"ONRN", 															2010, 	294.2104, 	0, 			0, 			0, 			(oxiphases)0, 														0, 		0, 		0, 		Duration(0.51, Duration::Seconds), 	Duration(0.072, Duration::Seconds));
	AddElement(*buff);
	delete buff;

	buff = new Element("Og", 		118, 	294, 	"Oganesson", 					Element::NobleGases, 			"ONRN", 															2006, 	294.2139, 	5, 			0, 			368.15, 	(oxiphases)0, 														0, 		0, 		0, 		Duration(0.005, Duration::Seconds), Duration(0.007, Duration::Seconds));
	AddElement(*buff);
	delete buff;

	// buff = new Element("Uue", 		119, 	316);
	// AddElement(*buff);
	// delete buff;

	// buff = new Element("Ubn", 		120, 	320);
	// AddElement(*buff);
	// delete buff;

	// buff = new Element("Ubu", 		121, 	320);
	// AddElement(*buff);
	// delete buff;

	// buff = new Element("Ubb", 		122, 	321);
	// AddElement(*buff);
	// delete buff;

	// buff = new Element("Ubt", 		123, 	325);
	// AddElement(*buff);
	// delete buff;

	// buff = new Element("Ubq", 		124, 	330);
	// AddElement(*buff);
	// delete buff;

	// buff = new Element("Ubp", 		125, 	332);
	// AddElement(*buff);
	// delete buff;

	// buff = new Element("Ubh", 		126, 	334);
	// AddElement(*buff);
	// delete buff;

}

#endif