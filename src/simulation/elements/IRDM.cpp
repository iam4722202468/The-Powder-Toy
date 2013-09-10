#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_IRDM PT_IRDM 177
Element_IRDM::Element_IRDM()
{
	Identifier = "DEFAULT_PT_IRDM";
	Name = "IRDM";
	Colour = PIXPACK(0xD3D4CF);
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
	Meltable = 1;
	Hardness = 4;
	
	Weight = 100;
	
	Temperature = R_TEMP+0.0f +273.15f;
	HeatConduct = 251;
	Description = "A very hard, brittle, and dense metal.";
	
	State = ST_SOLID;
	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_HOT_GLOW;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 2739.0f;
	HighTemperatureTransition = PT_IRDL;
	
	Update = &Element_IRDM::update;
	
}

//#TPT-Directive ElementHeader Element_IRDM static int update(UPDATE_FUNC_ARGS)
int Element_IRDM::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, rt;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				switch (r&0xFF)
				{
				case PT_LAVA:
					if (!(rand()%67) && (parts[pmap[y+ry][x+rx]>>8].ctype == PT_SALT))
						sim->delete_part(x, y);
					break;
				default:
					break;
				}
			}
	if (parts[i].type == PT_IRDM)
	{
		if ((sim->pv[y/CELL][x/CELL] > 4.3f))
			sim->create_part(i, x, y, PT_IRDP);
	}
	return 0;
}


Element_IRDM::~Element_IRDM() {}
