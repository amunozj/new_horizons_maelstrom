#define INVALID_SHIP_TYPE			-1

ref Fantom_GetNextFantom()
{
	iNumFantoms++;
	return &Characters[FANTOM_CHARACTERS + iNumFantoms];
}

bool TreasureFleet = false; // PB: Treasure Fleet
 // DeathDaisy: Store encounter data
int iGetNumMerchantShips, iGetNumWarShips;
int iGetEncType = -1;

int Fantom_GenerateEncounter(string sGroupName, int iEType, int iNation) // NK // KK
{
	aref	aWar, aMerchant;
	ref		rEnc;
	int		i, iNumMerchantShips, iNumWarShips, iLeadWarship;
	int		iWarClassMax, iWarClassMin, iMerchantClassMax, iMerchantClassMin;

	ref rCharacter = GetMainCharacter();

	makeref(rEnc, EncountersTypes[iEType]);
	makearef(aWar, rEnc.War);
	makearef(aMerchant, rEnc.Trade);

	iNumMerchantShips = MakeInt(aMerchant.ShipsMin) + rand(MakeInt(aMerchant.ShipsMax) - MakeInt(aMerchant.ShipsMin));
	iNumWarShips = MakeInt(aWar.ShipsMin) + rand(MakeInt(aWar.ShipsMax) - MakeInt(aWar.ShipsMin));

	int iRank = sti(rCharacter.Rank);
	if(GetShipCap()) { { if((8-GetCharacterShipClass(rCharacter)) * 2 < iRank) iRank = (8-GetCharacterShipClass(rCharacter)) * 2; } } // NK
	Encounter_GetClassesFromRank(iEType, iRank, &iMerchantClassMin, &iMerchantClassMax, &iWarClassMin, &iWarClassMax);
	//
	/*iWarClassMax = MakeInt(aWar.ClassMax);
	iWarClassMin = MakeInt(aWar.ClassMin);
	iMerchantClassMax = MakeInt(aMerchant.ClassMax);
	iMerchantClassMin = MakeInt(aMerchant.ClassMin);*/

	//Trace("class max = " + iMerchantClassMax + ", class min = " + iMerchantClassMin);

	int iFantomIndex, iShipType;

	//Trace("iNumMerchants = " + iNumMerchantShips);
	//Trace("iNumWars = " + iNumWarShips);

	// PB: Error Checking -->
	string encountertype = "";
	TreasureFleet = false;
	switch(iEType)
	{
		case ENCOUNTER_TYPE_MERCHANT0:
			encountertype = "Merchant 0: single merchant";
		break;
		case ENCOUNTER_TYPE_MERCHANT1:
			encountertype = "Merchant 1: merchants with a light escort";
		break;
		case ENCOUNTER_TYPE_MERCHANT2:
			encountertype = "Merchant 2: a single merchant with heavy escort";
		break;
		case ENCOUNTER_TYPE_PATROL:
			encountertype = "Patrol: a small patrol";
		break;
		case ENCOUNTER_TYPE_FLEET:
			encountertype = "Fleet: warships";
		break;
		case ENCOUNTER_TYPE_CORSAR:
			encountertype = "Corsar: -->PIRATE ONLY<--, warships";
		break;
		case ENCOUNTER_TYPE_PIRATE:
			encountertype = "Pirate: -->PIRATE ONLY<--, small craft";
		break;
		case ENCOUNTER_TYPE_PUNITIVE_SQUADRON:
			encountertype = "Punitive Squadron: a rag-tag bunch";
		break;
		case ENCOUNTER_TYPE_LMERCHANT0:
			encountertype = "L - Merchant 0: Shallow Waters Merchant Fleet, a group of merchants";
		break;
		case ENCOUNTER_TYPE_LMERCHANT1:
			encountertype = "L - Merchant 1: Coastal Waters Merchant Fleet, an escorted group of merchants";
		break;
		case ENCOUNTER_TYPE_LMERCHANT2:
			encountertype = "L - Merchant 2: -->SPAIN ONLY<--, Trans-Atlantic Treasure Fleet, a convoy";
			if(rand(100) < 75)
			{
				TreasureFleet = true;
				trace("Fantom_GenerateEncounter: Spanish Treasure Fleet loaded with Gold and Silver!");
			}
		break;
		case ENCOUNTER_TYPE_LPATROL:
			encountertype = "L - Patrol: Regional Patrol, a large patrol";
		break;
		case ENCOUNTER_TYPE_LFLEET:
			encountertype = "L - Fleet: Regional Patrol, a small fleet";
		break;
		case ENCOUNTER_TYPE_LCORSAR:
			encountertype = "L - Corsar: ARMADA, a battle fleet";
		break;
		case ENCOUNTER_TYPE_LPIRATE:
			encountertype = "L - Pirate, -->PIRATE ONLY<--, a rag-tag bunch";
		break;
		case ENCOUNTER_TYPE_LPUNITIVE_SQUADRON:
			encountertype = "L - Punitive Squadron, a scratch patrol";
		break;
	}
	trace("Fantom_GenerateEncounter: type = "+encountertype+", # Mer = "+iNumMerchantShips+", Mer MAX = "+iMerchantClassMax+", Mer MIN = "+iMerchantClassMin+", # War = "+iNumWarShips+", War MAX = "+iWarClassMax+", War MIN = "+iWarClassMin);
	// PB: Error Checking <--

	// GR: if more than 1 warship, make sure one of them is at the head of the formation, so merchants aren't all ahead of their escorts
	iLeadWarship = 0;
	if (iNumWarShips > 1)
	{
		if(iNumShips >= MAX_SHIPS_ON_SEA) return 0; // NK bugfix
		iShipType = Force_GetShipType(iWarClassMax, iWarClassMin, "War", iNation);
		if (iShipType != INVALID_SHIP_TYPE)
		{
			Fantom_AddFantomCharacter(sGroupName, iShipType, "war", iEType, iNation);
			iLeadWarship =1;
		}
	}
	
	for (i=0; i<iNumMerchantShips; i++)
	{
		if(iNumShips + i >= MAX_SHIPS_ON_SEA) return i; // NK bugfix
		iShipType = Force_GetShipType(iMerchantClassMax, iMerchantClassMin, "Trade", iNation); // NK change to type trade, fixed to swap min,max 04-09-13. Change to Force
		if (iShipType == INVALID_SHIP_TYPE) continue;
		//Trace("Merchant ship class = " + ShipsTypes[iShipType].Class + ", name = " + ShipsTypes[iShipType].Name);
		Fantom_AddFantomCharacter(sGroupName, iShipType, "trade", iEType, iNation);
	}

	for (i=0; i<(iNumWarShips-iLeadWarship); i++)
	{
		if(iNumShips + iNumMerchantShips + i >= MAX_SHIPS_ON_SEA) return iNumMerchantShips + i; // NK bugfix
		iShipType = Force_GetShipType(iWarClassMax, iWarClassMin, "War", iNation); // NK fixed to swap min,max 04-09-13 Change to Force

		if(iShipType == GetShipIndex("FastGalleon4") && TreasureFleet == true)
		{
			trace("Fantom_GenerateEncounter: replacing FastGalleon4 with Mariana");
			iShipType = GetShipIndex("Mariana");	// GR: use custom fast war galleon for treasure fleet
		}

		if (iShipType == INVALID_SHIP_TYPE) continue;
		//Trace("War ship class = " + ShipsTypes[iShipType].Class + ", name = " + ShipsTypes[iShipType].Name);
		Fantom_AddFantomCharacter(sGroupName, iShipType, "war", iEType, iNation);
	}
	
	// DeathDaisy: Save these data for the booty!
	iGetNumMerchantShips = iNumMerchantShips;
	iGetNumWarShips = iNumWarShips;
	iGetEncType = iEType;

	return iNumWarShips + iNumMerchantShips;
}

int Fantom_GetShipType(int iClassMax, int iClassMin, string sShipType, int iNation) // NK
{
	int iShips[2];		// was 512 - must be careful!!!!
	SetArraySize(&iShips, SHIP_TYPES_QUANTITY*10); // new version of chance
	int i, iShipsNum, iClass;
	for(i = 0; i < SHIP_TYPES_QUANTITY*10; i++) iShips[i] = INVALID_SHIP_TYPE;
	// NK -->
	int shipnation = -1;
	float NatSkipChance;
	ref rShip;
	if(iNation == PIRATE) { NatSkipChance = NOSKIP_CHANCE_WRONGNATION_PIRATE; }
	else { NatSkipChance = NOSKIP_CHANCE_WRONGNATION; }
	if(sShipType == "pirate")
	{
		if(PIRATES_USE_BOTH_TYPES) { sShipType = ""; }
		else { sShipType = "war"; }
	}
	iShipsNum = 0;
	// move class clamps things to Force_... 05-05-11
	for (i=0; i<SHIP_TYPES_QUANTITY; i++)
	{
		rShip = GetShipByType(i); // why was this type object? 05-05-11
		iClass = sti(rShip.Class);
		if (iClass > iClassMin) { continue; }
		if (iClass < iClassMax) { continue; }
		if (sti(rShip.CanEncounter) != true) { continue; }
		// KK: Periods -->
		if (iNation >= 0 && iNation < NATIONS_QUANTITY) {
			string sNation = GetNationIDByType(iNation);
            if (NATIONAL_PAINT_SCHEMES){
				if (CheckAttribute(rShip, sNation) == true && stf(rShip.(sNation)) < FRAND(1.0)) continue;
			}
		}
		string sPeriod = GetCurrentPeriod();
		if (CheckAttribute(rShip, "period."+sPeriod) && stf(rShip.period.(sPeriod)) < FRAND(1.0)) continue;
		// KK: Periods <--
		// new version of chance - old was if(CheckAttribute(rShip,"chance")) { if(frnd() > stf(rShip.chance)) { continue; } } // 04-09-10 will skip if chance not met
		// NK mod so we can disregard shiptype if we want to: 04-09-04
		// LDH --> new fix for missing sShipType 03Sep06
//		if(sShipType != "") { if (!sti(rShip.Type.(sShipType))) { continue; } }	// Original NK code
		if(sShipType != "")
		{
			if (CheckAttribute(rShip, "Type."+sShipType))
			{
				if (!sti(rShip.Type.(sShipType))) continue;
			}
			else
			{
				trace("Fantom_GetShipType(): Ship " + rShip.id + " has no shiptype");
				continue;
			}
		}
		// LDH <--
		// NK -->
		if(CheckAttribute(rShip,"Nation") && iNation != -1)
		{
			shipnation = sti(rShip.Nation);
			if(shipnation != iNation && frnd() > NatSkipChance) { continue; }
		}
		iShips[iShipsNum] = i;
		iShipsNum++;
	}
	if (iShipsNum==0)
	{
	//	Trace("Can't find ship type '" + sShipType + "' with ClassMin = " + iClassMin + " and ClassMax = " + iClassMax);
		return INVALID_SHIP_TYPE;
	}
	i = rand(iShipsNum-1);
	while(i > 0 && iShips[i] == INVALID_SHIP_TYPE) i--;
	return iShips[i];
}

// return new added fantom character
void Fantom_AddFantomCharacter(string sGroupName, int iShipType, string sFantomType, int iEncounterType, int iNation) // NK 04-09-05 add nation argument
{
	ref rFantom = GetFantomCharacter(iNumFantoms);
	ClearCharacter(rFantom); // PB: Clear ALL attributes from previous character
	rFantom.nation = iNation; // NK

	rFantom.SeaAI.Group.Name = sGroupName;
	rFantom.Ship.Type = GetShipID(iShipType); // PS
	//trace("added fantom " + rFantom.index + " with ship " + rFantom.ship.type);
	rFantom.Ship.idx = iShipType; // PS
	rFantom.Ship.Mode = sFantomType;
	rFantom.ship.cannons.Charge.Type = GOOD_BALLS;
//NK -->
	// PRS3 -->
	aref arship; makearef(arship, rFantom.ship);
//KB - Tuning ships - changed call to SetRandomStatsToShip
	SetRandomStatsToShip(sti(rFantom.index), iShipType, iNation);
//KB - orig   SetRandomStatsToShip(arship, iShipType, iNation);
//KB
// PRS3 <--
	if(sti(rFantom.nation) == PIRATE) { sFantomType = "pirate"; }
	else { if(sFantomType == "pirate") { sFantomType = "war"; } }
	rFantom.shiptype = GetShipID(iShipType); // PS
	rFantom.FantomType = sFantomType;
	float mult = 1.0;
	if(DEBUG_EXPERIENCE>0) TraceAndLog("Fantom_AddFantomCharacter: Set officer type for " + GetMySimpleName(rFantom));
	/*switch(sFantomType)
	{
		case "trade":
			mult *= 1.0;
			rFantom.quest.officertype = OFFIC_TYPE_CAPMERCHANT;
			break;
			
		case "war":
			mult *= 1.25;
			rFantom.quest.officertype = OFFIC_TYPE_CAPNAVY;
			break;
			
		case "pirate":
			mult *= 1.25;
			rFantom.quest.officertype = OFFIC_TYPE_CAPPIRATE;
			break;

		case "error":
			mult *= 1.0;
			rFantom.quest.officertype = OFFIC_TYPE_CAPPIRATE;
			break;
	}*/
	//Levis moved this to already existing functions
	rFantom.quest.officertype = GetCaptainType(rFantom);
	rFantom.rank = GetCaptainRank(rFantom);
	mult *= CaptainMultFromOfficerType(rFantom.quest.officertype);
	ref Shiptype = GetShipByType(iShipType);
	int iMCShipClass = makeint(GetCharacterShipClass(GetMainCharacter()));
	if (sti(Shiptype.Class) < iMCShipClass) {
		mult *= 1.15;
	} else {
		if (makeint(Shiptype.Class) > iMCShipClass) mult *= 0.85;
	}
	rFantom.Points = mult * stf(GetLocalShipAttrib(&arship,&Shiptype,"Weight")) / 5000; // PRS3
	//Log_SetStringToLog("Type: " + rFantom.FantomType + "; Mult: " + rFantom.Points);
// NK <--
	InitAutoSkillsSystem(rFantom,false); //Levis: Reset this character
	iNumFantoms++;
}

void Fantom_SetRandomMoney(ref rFantom, string sFantomType)
{
//NK, based on Stone-D -->
	// clear money from character
	rFantom.ShipMoney = 0;

	// ship class
	ref rShip = GetShipByType(GetCharacterShipType(rFantom));
	aref arship; makearef(arship, rFantom.ship); // PRS3 on down
	float cap = stf(GetLocalShipAttrib(arship,rShip,"Capacity")); //get ship's capacity.
	float weight = makefloat(sti(GetLocalShipAttrib(arship,rShip,"Weight"))) * 10000 / 508; //get ship's weight. Changed 04-09-19 to be more accurate, was simply *19.7
	int rank = sti(rFantom.rank);
	//make rankscalar
	float ranksc = makefloat(rank);
	if(ranksc<=5.0) ranksc = ranksc/5.0
	else ranksc = sqrt(ranksc) - 1.236;
	ranksc = ranksc*10;
	int rscale = makeint(ranksc);
	// add money
	// 04-09-22 add SHIPMONEY_MULT
	switch (rFantom.FantomType)
	{
		case "trade":
			rFantom.ShipMoney = makeint(SHIPMONEY_MULT * (cap * makefloat(30 + rand(20) + rand(20)) * (rscale/2.0 + rand(rscale))/40.0 + (rand(10)+5.0)/30.0));
			return;
		break;
		case "war":
			rFantom.ShipMoney = makeint(SHIPMONEY_MULT * (weight * makefloat(40 + rand(10) + rand(10)) * (rscale/2.0 + rand(rscale))/20.0 + (rand(10)+5.0)/30.0));
			return;
		break;
		case "pirate":
			rFantom.ShipMoney = makeint(SHIPMONEY_MULT * (weight * (5.0 + (rand(5)+1.0) * (rand(5)+1.0)) * (rscale/2.0 + rand(rscale))/20.0 + (rand(10)+5.0)/15.0));
			return;
		break;
	}
	//Trace("Fantom index = " + rFantom.index + ", group id = " + rFantom.SeaAI.Group.Name + ", have invalid encounter type = " + sFantomType);
// NK <--
}

void Fantom_SetCannons(ref rFantom, string sFantomType)
{
	int iSClass = GetCharacterShipClass(rFantom);
	ref rShip = GetShipByType(GetCharacterShipType(rFantom));

//NK -->
	aref arship; makearef(arship, rFantom.ship); // PRS3
	int iCaliber = sti(GetLocalShipAttrib(arship, rShip,"MaxCaliber")); // PRS3
	string sCannonType;
	ResetCannons(&rFantom); // whoops, need this!
	if(USE_REAL_CANNONS)
	{
		//KNB -->
		sCannonType = "long gun";
		if(rFantom.FantomType == "trade")
		{
			switch(rand(3))
			{
				case 0:
					iCaliber = 4;
				break;
				case 1:
					iCaliber = 6;
				break;
				case 2:
					iCaliber = 9;
				break;
				case 3:
					iCaliber = 12;
				break;
			}
			// NK start gun qty code 05-04-18 -->
			if(sti(rShip.Cannons.Borts.cannonl.qty) > 1) // if broadsides have >1 guns each
			{
				int newbsqty = 1+rand(sti(rShip.Cannons.Borts.cannonl.qty)-1); // new bs qty is random between 1 and normal
				arship.Cannons.Borts.cannonl.qty = newbsqty;
				arship.Cannons.Borts.cannonr.qty = newbsqty;
			}
			if(sti(rShip.Cannons.Borts.cannonb.qty) > 1) { arship.Cannons.Borts.cannonb.qty = 1+rand(sti(rShip.Cannons.Borts.cannonb.qty)-1); }
			// NK <--
		}
		else
		{
			if(rand(1) && iCaliber >= 6 && iCaliber <= 12) { sCannonType = "carronade"; }
		}
		if(iCaliber>sti(rShip.MaxCaliber)) { iCaliber=sti(rShip.MaxCaliber); }
		//KNB <--
	}
	else
	{
		sCannonType = "cannon";
		if(rFantom.FantomType == "trade") iCaliber = 12;
		else { if(rand(1) && iCaliber < 32) { sCannonType = "culverine"; } }
	}
	rFantom.Ship.Cannons.Type = GetCannonByTypeAndCaliber(sCannonType, iCaliber);
// NK <--
}

void Fantom_SetSails(ref rFantom, string sFantomType)
{
	rFantom.Ship.Sails.Gerald = false;
	if (sFantomType == "war") rFantom.Ship.Sails.Gerald = true;
}

// TIH --> used to reset the goods so they do not carry over from prior fantom slot thus causing overloaded ships
void Fantom_ClearCargo(ref rFantom)
{
	//Trace("CARGO: Fantom_ClearCargo prior char cargo load: " + GetCargoLoad(rFantom) + ", max: " + GetCargoMaxSpace(rFantom) );
	for (int i=0; i<GOODS_QUANTITY; i++)
	{
		string goodsName = Goods[i].Name;
		rFantom.Ship.Cargo.Goods.(goodsName) = 0;
	}
	RecalculateCargoLoad(&rFantom);
}
// TIH <--

void Fantom_SetBalls(ref rFantom, string sFantomType)
{
	//Trace("CARGO: Fantom_SetBalls cargo load prior: " + GetCargoLoad(rFantom) + ", max: " + GetCargoMaxSpace(rFantom) );

	float fKBalls;   int crewQ = GetCrewQuantity(rFantom);

	if (CANNONPOWDER_MOD) {// TIH --> mod toggle 7-7-06
		// added by MAXIMUS [gunpowder mod] -->
		float fKGunpowder = 0;
		ref rCannon; makeref(rCannon,Cannon[GetCaracterShipCannonsType(rFantom)]);
		if(CheckAttribute(rCannon,"gunpowder")) fKGunpowder = sti(rCannon.gunpowder)*sti(GetCannonCurQuantity(rFantom));
		// added by MAXIMUS [gunpowder mod] <--
	}// TIH <-- mod toggle

	if(USE_REAL_CANNONS)
	{
		  // KNB-->
		fKBalls = GetCannonQuantity(rFantom)/10;
		float fKGrape = fKBalls; //GetCannonQuantity(rFantom)/10;
		float fKChain = fKBalls; //GetCannonQuantity(rFantom)/10;

		switch (sFantomType)
		{
			case "war":
				if (CANNONPOWDER_MOD) fKGunpowder *= 0.45; //15-25 rpg // added by MAXIMUS [gunpowder mod]  // TIH mod toggle 7-7-06
				fKBalls *= 1.5; //15-25 rpg
				fKGrape *= 0.75; //8-13 rpg
				fKChain *= 0.45; //5-8 rpg
				Fantom_SetCharacterGoods(rFantom, GOOD_WHEAT, MakeInt(crewQ*FOOD_PER_CREW*30 + Rand(makeint(crewQ*FOOD_PER_CREW*30)) + Rand(makeint(crewQ*FOOD_PER_CREW*30))));
				Fantom_SetCharacterGoods(rFantom, GOOD_RUM, MakeInt(crewQ*FOOD_PER_CREW*5 + Rand(makeint(crewQ*FOOD_PER_CREW*10)) + Rand(makeint(crewQ*FOOD_PER_CREW*10))));
			break;
			case "trade":
				if (CANNONPOWDER_MOD) fKGunpowder *= 0.4; //8-13 rpg // added by MAXIMUS [gunpowder mod]  // TIH mod toggle 7-7-06
				fKBalls *= 0.5; //8-13 rpg
				fKGrape *= 0;
				fKChain *= 0.4; //6-10 rpg
				Fantom_SetCharacterGoods(rFantom, GOOD_WHEAT, MakeInt(crewQ*FOOD_PER_CREW*20 + Rand(makeint(crewQ*FOOD_PER_CREW*10)) + Rand(makeint(crewQ*FOOD_PER_CREW*10)) + Rand(2) * Rand(makeint(crewQ*FOOD_PER_CREW*60))));
				Fantom_SetCharacterGoods(rFantom, GOOD_RUM, MakeInt(Rand(2)*Rand(makeint(crewQ*FOOD_PER_CREW*5))));
			break;
			case "pirate":
				if (CANNONPOWDER_MOD) fKGunpowder *= 0.45; //12-20 rpg // added by MAXIMUS [gunpowder mod]  // TIH mod toggle 7-7-06
				fKBalls *= 1.2; //12-20 rpg
				fKGrape *= 0.9; //9-15 rpg
				fKChain *= 0.45; //5-8 rpg
				Fantom_SetCharacterGoods(rFantom, GOOD_WHEAT, MakeInt(crewQ*FOOD_PER_CREW*10 + Rand(makeint(crewQ*FOOD_PER_CREW*20)) + Rand(makeint(crewQ*FOOD_PER_CREW*10))));
				Fantom_SetCharacterGoods(rFantom, GOOD_RUM, MakeInt(crewQ*FOOD_PER_CREW*15 + Rand(makeint(crewQ*FOOD_PER_CREW*10)) + Rand(makeint(crewQ*FOOD_PER_CREW*10))));
			break;
		}

		// 15-25 rounds/gun baseline for all ammo types
		if (CANNONPOWDER_MOD) Fantom_SetCharacterGoods(rFantom, GOOD_GUNPOWDER, MakeInt(50 * fKGunpowder + rand(100 * fKGunpowder) + crewQ*3)); // added by MAXIMUS [gunpowder mod] // TIH mod toggle 7-7-06
		Fantom_SetCharacterGoods(rFantom, GOOD_BALLS, MakeInt(150 * fKBalls + rand(100 * fKBalls)));
		Fantom_SetCharacterGoods(rFantom, GOOD_GRAPES, MakeInt(150 * fKGrape + rand(100 * fKGrape)));
		Fantom_SetCharacterGoods(rFantom, GOOD_KNIPPELS, MakeInt(150 * fKChain + rand(100 * fKChain)));

		// KNB <--
	}
	else
		{
		// NK -->
		fKBalls = GetCannonQuantity(rFantom)/6; // 1.5 * (7 - GetCharacterShipClass(rFantom));

		switch (sFantomType)
		{
			case "war":
				if (CANNONPOWDER_MOD) fKGunpowder *= 0.75; // added by MAXIMUS // TIH mod toggle 7-7-06
				fKBalls = fKBalls * 1.5;
				Fantom_SetCharacterGoods(rFantom, GOOD_WHEAT, MakeInt(crewQ*FOOD_PER_CREW*30 + Rand(makeint(crewQ*FOOD_PER_CREW*30)) + Rand(makeint(crewQ*FOOD_PER_CREW*30))));
				Fantom_SetCharacterGoods(rFantom, GOOD_RUM, MakeInt(crewQ*FOOD_PER_CREW*5 + Rand(makeint(crewQ*FOOD_PER_CREW*10)) + Rand(makeint(crewQ*FOOD_PER_CREW*10))));
			break;
			case "trade":
				if (CANNONPOWDER_MOD) fKGunpowder *= 0.75; // added by MAXIMUS // TIH mod toggle 7-7-06
				fKBalls = fKBalls * 0.7;
				Fantom_SetCharacterGoods(rFantom, GOOD_WHEAT, MakeInt(crewQ*FOOD_PER_CREW*20 + Rand(makeint(crewQ*FOOD_PER_CREW*10)) + Rand(makeint(crewQ*FOOD_PER_CREW*10)) + Rand(2) * Rand(makeint(crewQ*FOOD_PER_CREW*60))));
				Fantom_SetCharacterGoods(rFantom, GOOD_RUM, MakeInt(Rand(2)*Rand(makeint(crewQ*FOOD_PER_CREW*5))));
			break;
			case "pirate":
				if (CANNONPOWDER_MOD) fKGunpowder *= 0.8; // added by MAXIMUS // TIH mod toggle 7-7-06
				fKBalls = fKBalls * 1.25;
				Fantom_SetCharacterGoods(rFantom, GOOD_WHEAT, MakeInt(crewQ*FOOD_PER_CREW*10 + Rand(makeint(crewQ*FOOD_PER_CREW*20)) + Rand(makeint(crewQ*FOOD_PER_CREW*10))));
				Fantom_SetCharacterGoods(rFantom, GOOD_RUM, MakeInt(crewQ*FOOD_PER_CREW*15 + Rand(makeint(crewQ*FOOD_PER_CREW*10)) + Rand(makeint(crewQ*FOOD_PER_CREW*10))));
			break;
		}

		if (CANNONPOWDER_MOD) Fantom_SetCharacterGoods(rFantom, GOOD_GUNPOWDER, MakeInt(80 * fKGunpowder + rand(25 * fKGunpowder) + GetCrewQuantity(rFantom))); // added by MAXIMUS // TIH mod toggle 7-7-06
		Fantom_SetCharacterGoods(rFantom, GOOD_BALLS, MakeInt(200 * fKBalls + rand(50 * fKBalls))); // was 150,250
		Fantom_SetCharacterGoods(rFantom, GOOD_GRAPES, MakeInt(80 * fKBalls + rand(120 * fKBalls))); // was 130,140
		Fantom_SetCharacterGoods(rFantom, GOOD_KNIPPELS, MakeInt(50 * fKBalls + rand(150 * fKBalls))); // was 100,50
		Fantom_SetCharacterGoods(rFantom, GOOD_BOMBS, MakeInt(50 * fKBalls + rand(200 * fKBalls))); // was 100,200
		// NK <--
	}
/* this was done poorly, commented out and added to goods section
// START MOD Code by Stone-D : 01/08/2003
	// Stone-D : Let's let the encounter AI repair themselves, shall we?
	Fantom_SetCharacterGoods(rFantom, GOOD_SAILCLOTH, MakeInt(10 * fKBalls + rand(50 * fKBalls)));
	Fantom_SetCharacterGoods(rFantom, GOOD_PLANKS, MakeInt(20 * fKBalls + rand(100 * fKBalls)));
// END MOD Code by Stone-D : 01/08/2003
*/
	RecalculateCargoLoad(&rFantom);
	//Trace("CARGO: Fantom_SetBalls cargo load result: " + GetCargoLoad(rFantom));
}

void Fantom_SetGoods(ref rFantom, string sFantomType)
{
	RecalculateCargoLoad(&rFantom);
	//Trace("CARGO: Fantom_SetGoods cargo load prior: " + GetCargoLoad(rFantom) + ", max: " + GetCargoMaxSpace(rFantom) );

	int iMultiply = 10;
	int iRandMultiply = 1;
	bool bBlockTreasure = false;
	int fillCargo, fillQuantity;

	int iShipClass = 8 - GetCharacterShipClass(rFantom);

	// START MOD Code by Stone-D : 01/08/2003
	switch (rFantom.FantomType) // NK
	{
		case "war":
		break;
		case "trade":
			iMultiply = (rand(10)+10) * (rand(iShipClass) + 2); // Stone-D : They ARE traders after all!
			iRandMultiply = 2 + rand(iShipClass);
		break;
		case "pirate":
			iMultiply = (rand(5)+5) * (rand(iShipClass) + 1); // Stone-D : They may have just come from a successful pillage
			iRandMultiply = 1 + rand(iShipClass / 2);
		break;
	}
	// END MOD Code by Stone-D : 01/08/2003

	// TIH --> rare gold & silver shipments mod Sep3'06
	// PB: Treasure Fleet -->
	bool RareShipment = false;
	if(rFantom.FantomType == "trade")
	{

		// GR: Block massive treasure hauls from unescorted merchants, boost massive treasure hauls on well-escorted merchants.
		switch(iGetEncType)
		{
			case ENCOUNTER_TYPE_MERCHANT0:
				trace("CARGO: Fantom_SetGoods No treasure for encounter type Merchants");
				RareShipment = false;
				bBlockTreasure = true;
			break;
			case ENCOUNTER_TYPE_LMERCHANT0:
				trace("CARGO: Fantom_SetGoods: No treasure for encounter type Group of Merchants");
				RareShipment = false;
				bBlockTreasure = true;
			break;
			case ENCOUNTER_TYPE_MERCHANT2:
				if(rand(100) < 17)
				{
					RareShipment = true;
					trace("CARGO: Fantom_SetGoods: Passed 17 percent chance of treasure for encounter type Single Merchant with Heavy Escort");
				}
			break;
			case ENCOUNTER_TYPE_LMERCHANT1:
				if(iGetNumWarShips > 1 && rand(100) < 8)
				{
					RareShipment = true;
					trace("CARGO: Fantom_SetGoods: Passed 8 percent chance of treasure for encounter type Escorted Group of Merchants");
				}
			break;
			case ENCOUNTER_TYPE_LMERCHANT2:
				if(TreasureFleet && rFantom.nation == SPAIN) RareShipment = true; // Always on Spanish Treasure Fleets
				trace("CARGO: Fantom_SetGoods: Convoy already has 75 percent chance of treasure");
			break;
			trace("CARGO: Fantom_SetGoods: No block on treasure due to encounter type");
			if(rand(100) < 5) RareShipment = true; // 5% chance of finding one of these
		}
	}

	if ( RareShipment )
	// PB: Treasure Fleet <--
	{
		switch(rand(2)) // one in three chance it will be gold! all gold!
		{
			case 0:
				Fantom_SetCharacterGoods(rFantom, GOOD_GOLD, GetCharacterFreeSpace(rFantom,GOOD_GOLD));
				Trace("CARGO: Fantom_SetGoods rare chance gold shipment!");
				break;
			//default:
				Fantom_SetCharacterGoods(rFantom, GOOD_SILVER, GetCharacterFreeSpace(rFantom,GOOD_SILVER));
				Trace("CARGO: Fantom_SetGoods rare chance silver shipment!");
		}
		return;// no point in continuing with this function now, the hold is full!
	}
	// TIH <--

	Fantom_SetCharacterGoods(rFantom, GOOD_SAILCLOTH, makeint(iShipClass + rand(iRandMultiply * 5))); // give ships a little bit of repair goods
	Fantom_SetCharacterGoods(rFantom, GOOD_PLANKS, makeint(iShipClass + rand(iRandMultiply * 5))); // give ships a little bit of repair goods

	//int iStart = GOOD_BOMBS + 1;
	int iStart = GOOD_PLANKS + 1;// TIH we start after repair goods now for random cargo

	// TIH --> we generate random different types now, instead of always 7 different types
	int randGoods = 1 + rand(6);
	for (int r=0;r<randGoods;r++)
	{
		fillCargo = iStart + rand(GOODS_QUANTITY - iStart - 1);
		fillQuantity = makeint(iMultiply * rand(iRandMultiply * 3));
		if(bBlockTreasure)
		{
			if(fillCargo == GOOD_GOLD || fillCargo == GOOD_SILVER)
			{
				trace("CARGO: Fantom_SetGoods: reducing " + fillQuantity + " of '" + Goods[fillCargo].name + "'");
				fillQuantity = makeint(frand(fillQuantity));
			}
		}
		if(iGetEncType == ENCOUNTER_TYPE_MERCHANT2 && rFantom.FantomType == "trade")
		{
//			if(fillCargo == GOOD_COPRA || fillCargo == GOOD_BRICKS || fillCargo == GOOD_LEATHER)
			if(fillCargo >= GOODS_QUANTITY -3)
			{
				trace("CARGO: Fantom_SetGoods: reducing " + fillQuantity + " of '" + Goods[fillCargo].name + "'");
				fillQuantity = makeint(frand(fillQuantity));
			}
		}
		trace("CARGO: Fantom_SetGoods: adding " + fillQuantity + " of '" + Goods[fillCargo].name + "'");
		Fantom_SetCharacterGoods(rFantom, fillCargo, fillQuantity);
	}
	/* prior method
	Fantom_SetCharacterGoods(rFantom, iStart + rand(GOODS_QUANTITY - iStart - 1), iMultiply * rand(iRandMultiply * 3));
	Fantom_SetCharacterGoods(rFantom, iStart + rand(GOODS_QUANTITY - iStart - 1), iMultiply * rand(iRandMultiply * 3));
	Fantom_SetCharacterGoods(rFantom, iStart + rand(GOODS_QUANTITY - iStart - 1), iMultiply * rand(iRandMultiply * 3));
	Fantom_SetCharacterGoods(rFantom, iStart + rand(GOODS_QUANTITY - iStart - 1), iMultiply * rand(iRandMultiply * 3));
	Fantom_SetCharacterGoods(rFantom, iStart + rand(GOODS_QUANTITY - iStart - 1), iMultiply * rand(iRandMultiply * 3));
	Fantom_SetCharacterGoods(rFantom, iStart + rand(GOODS_QUANTITY - iStart - 1), iMultiply * rand(iRandMultiply * 3));
	Fantom_SetCharacterGoods(rFantom, iStart + rand(GOODS_QUANTITY - iStart - 1), iMultiply * rand(iRandMultiply * 3));
	*/
	// TIH <--

	// TIH --> better method, prevents overloaded ships due to innept mathmatics Sep3'06
	if(rFantom.FantomType == "trade")
	{
		fillCargo = iStart + rand(GOODS_QUANTITY - iStart - 1);// random pick a good to be maxed
		if(bBlockTreasure)
		{
			while(fillCargo == GOOD_GOLD || fillCargo == GOOD_SILVER)
			{
				trace("CARGO: Fantom_SetGoods: trying not to put '" + Goods[fillCargo].name + "' into unescorted merchant");
				fillCargo = iStart + rand(GOODS_QUANTITY - iStart - 1);
			}
		}
		if(iGetEncType == ENCOUNTER_TYPE_MERCHANT2)
		{
			trace("Initial fill cargo = '" + Goods[fillCargo].name + "': GOODS_QUANTITY = " + GOODS_QUANTITY + ": fillcargo = " + fillcargo);
//			while(fillCargo == GOOD_COPRA || fillCargo == GOOD_BRICKS || fillCargo == GOOD_LEATHER)
			while(fillCargo >= (GOODS_QUANTITY - 3))
			{
				trace("CARGO: Fantom_SetGoods: trying not to put '" + Goods[fillCargo].name + "' into Single Merchant with Heavy Escort");
				fillCargo = iStart + rand(GOODS_QUANTITY - iStart - 1);
			}
		}
		fillQuantity = GetCargoGoods(rFantom,fillCargo) + GetCharacterFreeSpace(rFantom,fillCargo);// fill up the hold
		trace("CARGO: Fantom_SetGoods: filling hold with " + fillQuantity + " of '" + Goods[fillCargo].name + "'");
		Fantom_SetCharacterGoods(rFantom, fillCargo, fillQuantity);
	}
	/* causes overloaded ships
	//NK -->
	//Fill ship up to >= 90% full.
	float rndscl = 0.3 * frnd();
	if(rFantom.FantomType == "trade") {
		while(GetCargoFreeSpace(rFantom) > GetCargoMaxSpace(rFantom) * rndscl && GetCargoFreeSpace(rFantom) > 4) {
			AddCharacterGoods(rFantom, iStart + rand(GOODS_QUANTITY - iStart - 1), iMultiply * rand(iRandMultiply * 3)); } }
	// NK <--
	*/
	// TIH <--

	RecalculateCargoLoad(&rFantom);// moved down here after final additions are done (not really needed, but just in case)
	//Trace("CARGO: Fantom_SetGoods cargo load result: " + GetCargoLoad(rFantom));
}

// changed 05-05-02 by NK to set, not add, goods.
void Fantom_SetCharacterGoods(ref rFantom, int iGoods, int iQuantity)
{
	int traceprior = GetCargoLoad(rFantom);

	if (iQuantity == 0) { return; }
	string sGood = Goods[iGoods].name;
	
	int iFreeQuantity = GetCargoGoods(rFantom,iGoods) + GetCharacterFreeSpace(rFantom,iGoods);// TIH use proper functions
	if (iFreeQuantity < 0) { iFreeQuantity = 0; }
	if (iQuantity <= iFreeQuantity) { rFantom.Ship.Cargo.Goods.(sGood) = iQuantity; }
	else	{ rFantom.Ship.Cargo.Goods.(sGood) = iFreeQuantity;	}
// NK <-- 

	RecalculateCargoLoad(&rFantom);
	//Trace("CARGO: Fantom_SetCharacterGoods cargo load: " + traceprior + ", adding: " + sGood + " " + iQuantity + "qty" + ", set to: " + rFantom.Ship.Cargo.Goods.(sGood) + "qty");
}




void SDLog_AIFantom(string logtext)
{
// Ultra basic debugger. Uncomment this line if you want some feedback.
	if(DEBUGINFO) Log_SetStringToLog(logtext);
	return;
}

// PB -->
void Fantom_SetRandomModel(ref rFantom, string sFantomType)
{
	string sModel;
	switch (sFantomType)
	{
		case "war":
			sModel = GetRandomModelForTypeExSubCheck(true, "navy", "man", sti(rFantom.nation));
			if(sModel == DEFAULT_MODEL)
			{
				switch(rand(1))
				{
					case 0: sModel = GetRandomModelForTypeExSubCheck(true, "Land_Officers", "man", sti(rFantom.nation)); break;
					case 1: sModel = GetRandomModelForTypeExSubCheck(true, "Captains", "man", sti(rFantom.nation)); break;
				}
			}
		break;
		case "trade":
			switch(rand(3))
			{
				case 0: sModel = GetRandomModelForTypeExSubCheck(true, "Mates", "man", sti(rFantom.nation)); break;
				case 1: sModel = GetRandomModelForTypeExSubCheck(true, OFFIC_TYPE_FIRSTMATE, "man", sti(rFantom.nation)); break;
				case 2: sModel = GetRandomModelForTypeExSubCheck(true, OFFIC_TYPE_NAVIGATOR, "man", sti(rFantom.nation)); break;
				case 3: sModel = GetRandomModelForTypeExSubCheck(true, OFFIC_TYPE_QMASTER, "man", sti(rFantom.nation)); break;
			}
		break;
		case "pirate":
			if (rand(10) == 0) {
				sModel = GetRandomModelForTypeExSubCheck(true, "Captains", "woman", sti(rFantom.nation));
			} else {
				switch(rand(3))
				{
					case 0: sModel = GetRandomModelForTypeExSubCheck(true, "Captains", "man", sti(rFantom.nation)); break;
					case 1: sModel = GetRandomModelForTypeExSubCheck(true, "Mates", "man", sti(rFantom.nation)); break;
					case 2: sModel = GetRandomModelForTypeExSubCheck(true, OFFIC_TYPE_FIRSTMATE, "man", sti(rFantom.nation)); break;
					case 3: sModel = GetRandomModelForTypeExSubCheck(true, OFFIC_TYPE_NAVIGATOR, "man", sti(rFantom.nation)); break;
				}
			}
		break;
	}

	string mAni = Models[GetModelIndex(sModel)].ani;
	string mSex = Models[GetModelIndex(sModel)].sex;
	float mHeight = stf(Models[GetModelIndex(sModel)].height);
	SetModel(&rFantom, sModel, mAni, mSex, mHeight, false);
}
// <-- PB
