#include "scripts\Food.h"

#define FOOD_BY_SLAVES     160.0
#define FOOD_BY_PASSENGERS 140.0

//bool bInterfaceFood = false;
//int iFoodQuantity = 0;

int CalculateFood()
{
	int chrIndex;
	int iCrewQuantity = 0;
	float foodNeeded = 0.0;
	int iSlavesQuantity = 0;
	int iFoodQuantity = 0;

	for (int i=0; i<COMPANION_MAX; i++)
	{
		chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex != -1)
		{
            if (!GetRemovable(&characters[chrIndex])) continue;
			if (characters[chrIndex].ship.type != SHIP_NOTUSED)
			{
				iCrewQuantity   = iCrewQuantity   + sti(characters[chrIndex].ship.crew.quantity);
				iFoodQuantity   = iFoodQuantity   + GetCargoGoods(&characters[chrIndex], GOOD_WHEAT);
			}
		}
	}
	int iPassQuantity = GetPassengersQuantity(pchar);

	foodNeeded = makefloat(iCrewQuantity/FOOD_PER_CREW + iPassQuantity/FOOD_BY_PASSENGERS + iSlavesQuantity/FOOD_BY_SLAVES);

	if (foodNeeded < 1)
	{
		foodNeeded = 1;
	}
	iFoodQuantity = makeint(iFoodQuantity/foodNeeded + 0.2);

	return iFoodQuantity;
}

//#20200226-03
int CalculateRum()
{
	int chrIndex;
	int iCrewQuantity = 0;
	int iRumQuantity = 0;
	float rumNeededPerDay = 0.0;
	int iRumDays = 0;

	if (!CheckAttribute(pchar, "CrewPerRum")) {
		pchar.CrewPerRum = 50;
	}
	for (int i=0; i<COMPANION_MAX; i++)
	{
		chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex != -1)
		{
            if (!GetRemovable(&characters[chrIndex])) continue;
			if (characters[chrIndex].ship.type != SHIP_NOTUSED)
			{
				iCrewQuantity += sti(characters[chrIndex].ship.crew.quantity);
                iRumQuantity += GetCargoGoods(&characters[chrIndex], GOOD_RUM);
			}
		}
	}
	rumNeededPerDay = makefloat(makeint((iCrewQuantity+5.1) / stf(pchar.CrewPerRum))+ 1);

	if (rumNeededPerDay < 1)
	{
		rumNeededPerDay = 1;
	}
	iRumDays = makeint(iRumQuantity/rumNeededPerDay);

	return iRumDays;
}