#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_IRDL PT_IRDL 178
Element_IRDL::Element_IRDL()
{
	Identifier = "DEFAULT_PT_IRDL";
	Name = "IRDL";
	Colour = PIXPACK(0xCFCFCF);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;
	
	Advection = 0.8f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.2f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;
	
	Flammable = 0;
	Explosive = 0;
	Meltable = 5;
	Hardness = 20;
	
	Weight = 90;
	
	Temperature = R_TEMP+3000.0f	+273.15f;
	HeatConduct = 29;
	Description = "Liquid Iridium.";
	
	State = ST_LIQUID;
	Properties = TYPE_LIQUID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_NEUTPASS;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 2736.0f;
	LowTemperatureTransition = PT_IRDM;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	Update = NULL;
	
}

Element_IRDL::~Element_IRDL() {}
