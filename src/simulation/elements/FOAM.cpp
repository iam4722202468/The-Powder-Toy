#include "simulation/Elements.h"
#include "simulation/Air.h"
//#TPT-Directive ElementClass Element_FOAM PT_FOAM 176
Element_FOAM::Element_FOAM()
{
	Identifier = "DEFAULT_PT_FOAM";
	Name = "FOAM";
	Colour = PIXPACK(0x707070);
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
	Hardness = 50;
	
	Weight = 100;
	
	Temperature = R_TEMP+0.0f +273.15f;
	HeatConduct = 251;
	Description = "Absorbs pressure.";
	
	State = ST_SOLID;
	Properties = TYPE_SOLID|PROP_LIFE_DEC|PROP_LIFE_KILL_DEC;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 1200.0f;
	HighTemperatureTransition = PT_CO2;
	
	Update = &Element_FOAM::update;
	
}

//#TPT-Directive ElementHeader Element_FOAM static int update(UPDATE_FUNC_ARGS)
int Element_FOAM::update(UPDATE_FUNC_ARGS)
 {
	int rx, ry, tmp = parts[i].tmp, foam = 0;
	if(nt<=2)
		foam = 2;
	else if(parts[i].tmp)
		foam = 2;
	else if(nt<=6)
		for (rx=-1; rx<2; rx++) {
			for (ry=-1; ry<2; ry++) {
				if ((!rx != !ry) && BOUNDS_CHECK) {
					if((pmap[y+ry][x+rx]&0xFF)==PT_FOAM)
						foam++;
				}
			}
		}

	if(foam>=2) {
		sim->air->bmap_blockair[y/CELL][x/CELL] = 1;
		sim->air->bmap_blockairh[y/CELL][x/CELL] = 1;
	}
	
	if (sim->pv[y/CELL][x/CELL]> 1.0f)
	{
		tmp += 5;
		for (rx=-1; rx<2; rx++) 
		{
			for (ry=-1; ry<2; ry++) 
			{
		        sim->pv[(y+ry)/CELL][(x+rx)/CELL] = 0.0f;
				parts[i].tmp = tmp;
			}
		}
	}
	
	if (!parts[i].life && (tmp > 2700) && (rand()%(tmp-3000)))
		parts[i].life = 5;
		
	if (parts[i].life)
	{
		float advection = 0.1f;
		parts[i].vx += advection*sim->vx[y/CELL][x/CELL];
		parts[i].vy += advection*sim->vy[y/CELL][x/CELL];
	}
	
	return 0;
}



Element_FOAM::~Element_FOAM() {}
