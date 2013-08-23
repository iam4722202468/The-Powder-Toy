#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_XOR PT_XOR 183
Element_XOR::Element_XOR()
{
	Identifier = "DEFAULT_PT_XOR";
	Name = "XOR";
	Colour = PIXPACK(0x009456);
	MenuVisible = 1;
	MenuSection = SC_ADVELEC;
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
	Hardness = 50;
	
	Weight = 100;
	
	Temperature = R_TEMP+0.0f +273.15f;
	HeatConduct = 251;
	Description = "Logical XOR gate.  Use tmp to set delay. In: PSCN, Out: NSCN";
	
	State = ST_SOLID;
	Properties = TYPE_SOLID;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1687.0f;
	HighTemperatureTransition = PT_LAVA;
	
	Update = &Element_XOR::update;
	
}

//#TPT-Directive ElementHeader Element_XOR static int update(UPDATE_FUNC_ARGS)
int Element_XOR::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, nscnpos;
	bool sprkcunt = false;
	if (!parts[i].tmp)
		parts[i].tmp = 6;
		
	for (rx=-2; rx<3; rx++)
		for (ry=-2; ry<3; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if ((r&0xFF)==PT_SPRK)
				    if (parts[r>>8].ctype == PT_PSCN)
				    {
				        if (sprkcunt)
							goto output;
				        else
							sprkcunt = true;
				    }
				    
				if ((r&0xFF)==PT_NSCN)
					nscnpos = r;
			}
			
	r = nscnpos;	
	if ((r&0xFF)==PT_NSCN && !parts[r>>8].life && sprkcunt)
	{
		parts[r>>8].type = PT_SPRK;
		parts[r>>8].ctype = PT_NSCN;
		parts[r>>8].life = parts[i].tmp;
	}

	return 0;
	
	output:
		for (rx=-2; rx<3; rx++)
			for (ry=-2; ry<3; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y+ry][x+rx];
					if ( (r&0xFF)==PT_NSCN && !parts[r>>8].life || (((r&0xFF)==PT_SPRK) && (parts[r>>8].ctype == PT_NSCN)))
					{
						parts[r>>8].type = PT_NSCN;
						parts[r>>8].life = 8;
					}
				}						
	return 0;
}

Element_XOR::~Element_XOR() {}
