#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_IRDP PT_IRDP 179
Element_IRDP::Element_IRDP()
{
	Identifier = "DEFAULT_PT_IRDP";
	Name = "IRDP";
	Colour = PIXPACK(0xD3D4CF);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;
	
	Advection = 0.7f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.96f;
	Loss = 0.90f;
	Collision = -0.1f;
	Gravity = 0.05f;
	Diffusion = 0.01f;
	HotAir = -0.00005f* CFDS;
	Falldown = 1;
	
	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;
	
	Weight = 94;
	
	Temperature = R_TEMP+30.0f+273.15f;
	HeatConduct = 46;
	Description = "Iridium powder.";
	
	State = ST_SOLID;
	Properties = TYPE_PART|PROP_CONDUCTS;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 2739.0f;
	HighTemperatureTransition = PT_IRDL;
	
	Update = &Element_IRDP::update;
	
}

//#TPT-Directive ElementHeader Element_IRDP static int update(UPDATE_FUNC_ARGS)
int Element_IRDP::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, rt;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				switch (r&0xFF)
				{
				case PT_SALT:
					if (!(parts[i].life) && !(rand()%47))
						sim->delete_part(x, y);
					break;
				case PT_FIRE:
				    if (!(rand()%20))
				        sim->create_part(i, x, y, PT_FIRE);
				    break;
				case PT_PLSM:
				    if (!(rand()%10))
				        sim->create_part(i, x, y, PT_FIRE);
				    break;
				default:
					break;
				}
			}
	return 0;
}


Element_IRDP::~Element_IRDP() {}
