#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_MTOR PT_MTOR 177
Element_MTOR::Element_MTOR()
{
	Identifier = "DEFAULT_PT_MTOR";
	Name = "MTOR";
	Colour = PIXPACK(0xA80000);
	MenuVisible = 1;
	MenuSection = SC_EXPLOSIVE;
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
	Description = "Meteor.";
	
	State = ST_SOLID;
	Properties = TYPE_PART|PROP_CONDUCTS;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	Update = &Element_MTOR::update;
}

//#TPT-Directive ElementHeader Element_MTOR static int update(UPDATE_FUNC_ARGS)
int Element_MTOR::update(UPDATE_FUNC_ARGS)
{
	parts[i].vx=rand()%3-1;
	parts[i].vy=rand()%3+1;
	sim->create_part(-1, x+rand()%3-1, y+rand()%3-1, PT_BRAY);
	
	int rx, ry, rrx, rry, r;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if ( !r || (r&0xFF)==PT_BRAY || (r&0xFF)==PT_MTOR)
				    return 0;
				else
				{
					sim->pv[y/CELL][x/CELL] = 255.0f;
					sim->delete_part(x, y);
					
					for (rrx=-1; rrx<2; rrx++)
						for (rry=-1; rry<2; rry++)
							sim->create_part( -1, x+rrx, y+rry, PT_DEST);
				}
			}

    return 0;
}

Element_MTOR::~Element_MTOR() {}
