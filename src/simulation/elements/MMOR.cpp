#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_MMOR PT_MMOR 189
Element_MMOR::Element_MMOR()
{
	Identifier = "DEFAULT_PT_MMOR";
	Name = "MMOR";
	Colour = PIXPACK(0x000056);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;
	
	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;
	
	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;
	
	Weight = 100;
	
	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 251;
	Description = "MMORer for photons, changes the color.";
	
	State = ST_SOLID;
	Properties = TYPE_SOLID;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	Update = &Element_MMOR::update;
	Graphics = &Element_MMOR::graphics;
}
//#TPT-Directive ElementHeader Element_MMOR static int update(UPDATE_FUNC_ARGS)
int Element_MMOR::update(UPDATE_FUNC_ARGS) 
{
	int r, rt, rx, ry;
	for (rx=-2; rx<3; rx++)
		for (ry=-2; ry<3; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				rt = r&0xFF;
				if (rt == PT_MMOR)
					parts[i].tmp = parts[r>>8].tmp;
				if (rt && rt != PT_MMOR)
					parts[i].tmp = sim->elements[rt].Colour;
			}
		
	return 0;
}

//#TPT-Directive ElementHeader Element_MMOR static int graphics(GRAPHICS_FUNC_ARGS)
int Element_MMOR::graphics(GRAPHICS_FUNC_ARGS)

{
	int b = cpart->tmp;
	*colr = b%256;
	*colg = (int(b / 256) % 256);
	*colb = (int(b / 256 / 256) % 256);
	return 0;
}


Element_MMOR::~Element_MMOR() {}
