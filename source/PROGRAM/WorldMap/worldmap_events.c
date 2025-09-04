
bool wdmDisableRelease = true;

//=========================================================================================
//Events
//=========================================================================================

void wdmEvent_EncounterCreate()	// Mirsaneli: fixed mein2 missing attribute
{
	float dltTime = GetEventData();
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();

	// Save player ship position
	worldMap.playerShipX = playerShipX;
	worldMap.playerShipZ = playerShipZ;
	worldMap.playerShipAY = playerShipAY;

	// Handle current island
	if (wdmCurrentIsland != WDM_NONE_ISLAND && CheckAttribute(&worldMap, "islands." + wdmCurrentIsland + ".name"))
	{
		// Set island name for sea login
		wdmLoginToSea.island = worldMap.islands.(wdmCurrentIsland).name;

		// Get island reference position
		float ix = MakeFloat(worldMap.islands.(wdmCurrentIsland).position.rx);
		float iz = MakeFloat(worldMap.islands.(wdmCurrentIsland).position.rz);

		// Calculate player ship's relative display position
		worldMap.playerShipDispX = (playerShipX - ix);
		worldMap.playerShipDispZ = (playerShipZ - iz);
	}
	else
	{
		// Invalid island reference; reset displacement to zero
		Trace("WARNING: Invalid or missing island data for wdmCurrentIsland: " + wdmCurrentIsland);
		worldMap.playerShipDispX = 0.0;
		worldMap.playerShipDispZ = 0.0;

		// Optional: reset the island value if it’s invalid
		// wdmCurrentIsland = WDM_NONE_ISLAND;
	}

	// Skip encounters if 'noenc' flag is set
	if (CheckAttribute(&worldMap, "noenc") && worldMap.noenc == "true")
	{
		return;
	}

	// Generate storm and ship encounters
	wdmStormGen(dltTime, playerShipX, playerShipZ, playerShipAY);
	wdmShipEncounter(dltTime, playerShipX, playerShipZ, playerShipAY);
	wdmQuestShipEncounter(dltTime, playerShipX, playerShipZ, playerShipAY);
}

void wdmEvent_InsideIsland()
{
	wdmDisableTornadoGen = true;
	wdmCurrentIsland = GetEventData();
	trace("InsideIsland position:");
    trace("wdmCurrentIsland = " + wdmCurrentIsland);
    trace("x = " + worldMap.island.x);
    trace("z = " + worldMap.island.z);
    Trace("Inside to "+wdmCurrentIsland);
	//Trace("Inside to "+wdmCurrentIsland);
	// PlayLandHo(); // NK // added by KAM after build 11 // KK
}

// KK -->
void PlayLandHo()
{
	if (ENABLE_EXTRA_SOUNDS == 0) return;
	if (actLoadFlag == 1) return;
	if (!CheckAttribute(&worldMap, "outsideIsland")) return;
	DeleteAttribute(&worldMap, "outsideIsland");
	PlaySound("#land_ho");
}
// <-- KK

void wdmEvent_OutsideIsland()
{
	wdmCurrentIsland = GetEventData();
	//Trace("Outside from "+wdmCurrentIsland);
	wdmCurrentIsland = WDM_NONE_ISLAND;
	worldMap.outsideIsland = true; // KK
}

void wdmEvent_PlayerInStorm()
{
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	int stormIndex = GetEventData();
	wdmDisableTornadoGen = false;
	if (CheckAttribute(pchar, "stormIndex")) return; // PW storm immunity otherwise locked in storm
    	pchar.stormIndex = stormIndex;//PW set up variable for storm immunity (cleared in daily crew update)

	wdmReloadToSea();
}

void wdmEvent_ShipEncounter()
{
	wdmDisableTornadoGen = true;
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	int eshipIndex = GetEventData();
	//Trace("Player ship hit in ship encounter with index " + eshipIndex);

	//Boyer add
	if (CheckAttribute(pchar, "SkipEshipIndex") && pchar.SkipEshipIndex == eshipIndex) return; // boal
	pchar.SkipEshipIndex = eshipIndex;
	if(CheckAttribute(worldMap, "evwin") != 0)
	{
		if(worldMap.evwin == "true")
		{
			wdmMessage("Sails on horizon!# Pirate ships ahead.", "Engage", "Skip");
			return;
		}
	}
	// boal -->
//changed by MAXIMUS: for new "Sail Ho" and DirectSail-Mod -->
    CalculateEncInfoData();
/*	ref messenger = DirectSailMessenger("sail_ho");
	messenger.SailHo = true;
	messenger.Dialog.Filename = "Enc_WorldMap_dialog.c";
	Log_SetActiveAction("Nothing");
	BLI_RefreshCommandMenu();
	BLI_DisableShow();
	SelfDialog(messenger);*/
	LaunchBoalMapScreen();
//changed by MAXIMUS: for new "Sail Ho" and DirectSail-Mod <--
	//wdmReloadToSea();
	// boal <--

}

void wdmEvent_DeleteShipEncounter()
{
	if(wdmDisableRelease == true)
	{
		int type = GetEventData();
		if(type >= 0) ReleaseMapEncounter(type);
	}
}

void wdmEvent_EventWindowChangeSelectoin()
{
	int select = GetEventData();
}

void wdmEvent_EventWindowSelect()
{
	int result = GetEventData();

	//Trace("Event window select is " + result);
	if(result == 0) wdmReloadToSea();
}

void wdmEvent_WaitMenuChangeSelectoin()
{
	int selectItem = GetEventData();
}

void wdmEvent_WaitMenuSelect()
{
	int selectItem = GetEventData();

	//Trace("Wait menu select is " + selectItem);
}

void wdmEvent_UpdateDate()
{
	Environment.date.day = worldMap.date.day;
	Environment.date.month = worldMap.date.month;
	Environment.date.year = worldMap.date.year;
	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = GetEventData();
}



#event_handler("NextDay", "wdmNextDayUpdate");
void wdmNextDayUpdate()
{
	// NK -->
	ref PChar = GetMainCharacter();
	if(!CheckAttribute(PChar,"articles")) {PChar.articles = 0;}
	if(!CheckAttribute(PChar,"LastPayMonth")) {PChar.LastPayMonth = GetDataMonth();} // PB: NOT at the beginning of the game
	/*if( sti(PChar.LastPayMonth) != GetDataMonth() )
	{
		if( GetDataDay() >= 7 && !sti(PChar.articles) )
		{
			wdmLockReload = true;
			PChar.LastPayMonth = GetDataMonth();
			PostEvent("Event_CheckMoneyData", 0);
		}
	}*/ //This is in daily updates already
	/*DailyCrewUpdate();
	// NK <--
	UpdateAllTowns(false); // NK
	DailyShipBerthingUpdate(); 		// added after build 11 by KAM
	UpdateAllItemTraders(false); // NK itemtrade 05-04-02 do all trader update.
	UpdateMoonInfo(LogsToggle == LOG_VERBOSE); // added by Levis*/
	DoDailyUpdates("all"); //Changed to this by levis to take everything in account
}


/*#event_handler("Event_CheckMoneyData", "wdmCheckMoneyData");
void wdmCheckMoneyData()
{
	trace("wdmCheckMoneyData on day: "+ worldMap.date.day);
	LaunchSalaryScreen();
	wdmLockReload = false;
}*/ //in daily updates already

#event_handler("WorldMap_IsSkipEnable", "wdmIsSkipEnable");
bool wdmSkipReturnBool = false;
bool wdmIsSkipEnable()
{
	wdmSkipReturnBool = false;
	if(IsCharacterPerkOn(GetMainCharacter(), "SailingProfessional"))
	{
		if(rand(100) <= 50)
		{
			wdmSkipReturnBool = true;
		}
	}
	return wdmSkipReturnBool;
}

float wdmGetMoral()
{
	int iMorale = 0;
	int cn = -1;
	int iRealCompNum = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			iMorale = iMorale + GetCharacterCrewMorale(&characters[cn]);
			iRealCompNum++;
		}
	}
	iMorale = iMorale / iRealCompNum;
	return stf(iMorale);
}

int GetCharacterCrewMorale(ref chr)
{
	if(!CheckAttribute(chr, "ship.crew.morale"))
	{
		chr.ship.crew.morale = MORALE_NORMAL;
	}
	return sti(chr.ship.crew.morale);
}

#event_handler("WorldMap_GetMoral", "wdmGetMorale");
float wdmGetMorale()
{
	ref pchar = GetMainCharacter();
	return stf(pchar.Ship.Crew.Morale);
}

// food and rum display in world map

#event_handler("WorldMap_GetFood", "wdmGetFood");
float wdmGetFood()
{
	ref pchar = GetMainCharacter();
	return CalculateFoodRations(pchar);
}

#event_handler("WorldMap_GetRum", "wdmGetRum");
float wdmGetRum()
{
	ref pchar = GetMainCharacter();
	return CalculateRumRations(pchar);
}

float CalculateFoodRations(ref character)
{
	float food_quantity = GetFleetFoodAvailable(character);
	float daily_food_consumed = GetFleetFoodConsumption(character);

	if (daily_food_consumed <= 0) {
		return -1.0;
	}

	return food_quantity/daily_food_consumed;
}

float CalculateRumRations(ref character)
{
	float rum_quantity = GetFleetRumAvailable(character);
	float daily_rum_consumed = GetFleetRumConsumption(character);

	if (daily_rum_consumed <= 0) {
		return -1.0;
	}

	return rum_quantity/daily_rum_consumed;
}

float GetFleetFoodAvailable(ref leader) {
	int food_quantity = GetSquadronGoods(leader, GOOD_WHEAT);

	float consumed_food = 0;
	if (CheckAttribute(leader, "crewStatus.foodUsed") ) {
		consumed_food += stf(leader.crewStatus.foodUsed);
	}

	return makefloat(food_quantity) - consumed_food;
}

float GetFleetFoodConsumption(ref leader) {
	int crew_quantity = GetFleetLivingCrew(leader);

	float consumption_rate = 1.0;

	if (CheckAttribute(leader, "crewStatus.foodRations") ) {
		consumption_rate /= stf(leader.crewStatus.foodRations);
	}

	if (CheckPerkForGroup(leader, "Cooking") ) {
		consumption_rate *= 0.9;
	}

	return makefloat(crew_quantity) * consumption_rate * FOOD_PER_CREW;
}

float GetFleetRumAvailable(ref leader) {
	int rum_quantity = GetSquadronGoods(leader, GOOD_RUM);

	float consumed_rum = 0;
	if (CheckAttribute(leader, "crewStatus.rumUsed") ) {
		consumed_rum += stf(leader.crewStatus.rumUsed);
	}

	return makefloat(rum_quantity) - consumed_rum;
}


float GetFleetRumConsumption(ref leader) {
	int crew_quantity = GetFleetLivingCrew(leader);

	float consumption_rate = 0.5;

	if (CheckAttribute(leader, "crewStatus.rumRations") ) {
		consumption_rate = 1.0 / stf(leader.crewStatus.rumRations);
	}

	return makefloat(crew_quantity) * consumption_rate * FOOD_PER_CREW;
}

int GetFleetLivingCrew(ref leader) {
	int crew_quantity = GetSquadronTotalCrewQuantity(leader);
	// PB: Cursed Coins -->
	if (CheckCharacterItem(leader,"cursedcoin") ) {
		int cursed_count_count = GetCursedCoinCount();
		crew_quantity -= cursed_count_count;
	}
	// PB: Cursed Coins <--
	crew_quantity += GetUnremovableCrewQuantity(leader);
	if (crew_quantity < 0) {
		crew_quantity = 0;
	}
	return crew_quantity;
}
