void CreateFortCommandantsCharacters(ref n)
{
	object chobj;
	ref ch;

	makeref(ch, chobj);

	ch.old.name = "Rauf";
	ch.old.lastname = "Mallard";
	ch.name 	= TranslateString("", "Rauf");
	ch.lastname 	= TranslateString("","Mallard");
	ch.id		= "Redmond Commander";
	ch.model	= Nations[ENGLAND].fantomModel.m0; // KK was "Soldier_eng3"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Redmond";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = ENGLAND;
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "5";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "8";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = 2122.685 // PB
	ch.ship.pos.z = -1132.215 // PB
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 18; // KK
	ch.Fort.Cannons.Type.2.Quantity = 30; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Redmond";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Stanley";
	ch.old.lastname = "Ransome";
	ch.name 	= TranslateString("", "Stanley");
	ch.lastname 	= TranslateString("","Ransome");
	ch.id		= "Oxbay Commander";
	ch.model	= Nations[ENGLAND].fantomModel.m0; // KK was "Soldier_eng2"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location	= "none";
	ch.location = "Oxbay";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort2";
	ch.nation = ENGLAND;
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "5";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "8";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -795.8871; // PB
	ch.ship.pos.z = 1666.402; // PB
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 20; // KK
	ch.Fort.Cannons.Type.2.Quantity = 0; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	ch.town = "Oxbay"; // RM
	AddGameCharacter(n, ch);

	ch.old.name = "William";
	ch.old.lastname = "Bishop";
	ch.name 	= TranslateString("", "William");
	ch.lastname 	= TranslateString("","Bishop");
	ch.id		= "Greenford Commander";
	ch.model	= Nations[ENGLAND].fantomModel.m0; // KK was "Soldier_eng6"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Oxbay";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.Dialog.Filename = "Greenford Commander_dialog.c";
	ch.nation = ENGLAND;
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "5";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "8";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -906.7187 // PB
	ch.ship.pos.z = -1639.882 // PB
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 12; // KK
	ch.Fort.Cannons.Type.2.Quantity = 20; // KK
	ch.greeting = "Gr_Greenford Commander";
	LAi_SetHP(ch, 100.0, 100.0);
	ch.town = "Greenford"; // RM
	AddGameCharacter(n, ch);

	ch.old.name = "Gerard";
	ch.old.lastname = "Cahusac";
	ch.name 	= TranslateString("", "Gerard");
	ch.lastname 	= TranslateString("","Cahusac");
	ch.id		= "FalaiseDeFleur Commander";
	ch.model = Nations[FRANCE].fantomModel.m0; // KK was "Soldier_fra"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "FalaiseDeFleur";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = FRANCE;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -322.6504; // PB
	ch.ship.pos.z = -317.9496; // PB
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 22; // KK
	ch.Fort.Cannons.Type.2.Quantity = 16; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Falaise de Fleur";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Basil";
	ch.old.lastname = "Vespucci";
	ch.name 	= TranslateString("", "Basil");
	ch.lastname 	= TranslateString("","Vespucci");
	ch.id		= "Conceicao Commander";
	ch.model = Nations[PORTUGAL].fantomModel.m0; // KK was "soldier_por"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Conceicao";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = PORTUGAL;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -2566.726; // PB
	ch.ship.pos.z = -2080.765; // PB
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 15; // KK
	ch.Fort.Cannons.Type.2.Quantity = 20; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Conceicao";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Frank";
	ch.old.lastname = "Voorwerp";
	ch.name 	= TranslateString("", "Frank");
	ch.lastname 	= TranslateString("","Voorwerp");
	ch.id		= "Douwesen Commander";
	ch.model = Nations[HOLLAND].fantomModel.m0; // KK was "Soldier_hol"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Douwesen";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = HOLLAND;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = 1698.886; // PB
	ch.ship.pos.z = 68.87842; // PB
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 15; // KK
	ch.Fort.Cannons.Type.2.Quantity = 22; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Douwesen";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Miguel";
	ch.old.lastname = "Almadovar";
	ch.name 	= TranslateString("", "Miguel");
	ch.lastname 	= TranslateString("","Almadovar");
	ch.id		= "IslaMuelle Commander";
	ch.model = Nations[SPAIN].fantomModel.m0; // KK was "soldier_spa"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "IslaMuelle";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = 1716.492; // PB
	ch.ship.pos.z = 1302.121; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 12; // KK
	ch.Fort.Cannons.Type.2.Quantity = 22; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Isla Muelle";
	// RM <--
	AddGameCharacter(n, ch);

///SCREWFACE : Fort commanders of new islands
///////////////////////////////////////////////

	ch.old.name = "Teseus";
	ch.old.lastname = "Woods";
	ch.name 	= TranslateString("","Teseus");
	ch.lastname 	= TranslateString("","Woods");
	ch.id		= "St John's Commander";
	ch.model = Nations[ENGLAND].fantomModel.m0; // KK was "soldier_eng"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Antigua";
	ch.location.group = "reload";
	ch.location.locator = "reload_1";
	ch.nation = ENGLAND;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -1711.641; // PB
	ch.ship.pos.z = 954.9787; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 29; // KK
	ch.Fort.Cannons.Type.2.Quantity = 40; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "St John's";
	// RM <--
	AddGameCharacter(n, ch);
	
	ch.old.name = "Nicholas";
	ch.old.lastname = "Quinton";
	ch.name 	= TranslateString("","Nicholas");
	ch.lastname 	= TranslateString("","Quinton");
	ch.id		= "Grand Cayman Commander";
	ch.model = Nations[ENGLAND].fantomModel.m0; // KK was "soldier_eng"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Cayman";
	ch.location.group = "reload";
	ch.location.locator = "reload1_2";
	ch.nation = ENGLAND;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -904.6331; // PB
	ch.ship.pos.z = -967.0954; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	ch.Fort.Cannons.Type.1.Quantity = 5; // KK
	ch.Fort.Cannons.Type.2.Quantity = 10; // KK
	// KNB <--
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Grand Cayman";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Pedro";
	ch.old.lastname = "Navarro";
	ch.name 	= TranslateString("","Pedro");
	ch.lastname 	= TranslateString("","Navarro");
	ch.id		= "Santiago Commander";
	ch.model = Nations[SPAIN].fantomModel.m0; // KK was "soldier_spa"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Cuba";
	ch.location.group = "reload";
	ch.location.locator = "reload1_2";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = 7234.018; // PB
	ch.ship.pos.z = -4732.157; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 30; // KK
	ch.Fort.Cannons.Type.2.Quantity = 40; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Santiago";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Maurellus";
	ch.old.lastname = "Maradona";
	ch.name 	= TranslateString("","Maurellus");
	ch.lastname 	= TranslateString("","Maradona");
	ch.id		= "Havana Commander";
	ch.model = Nations[SPAIN].fantomModel.m0; // KK was "soldier_spa"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Cuba";
	ch.location.group = "reload";
	ch.location.locator = "reload_4";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -9210.628; // PB
	ch.ship.pos.z = 1676.017; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 30; // KK
	ch.Fort.Cannons.Type.2.Quantity = 40; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Havana";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Francois";
	ch.old.lastname = "Vautrin";
	ch.name 	= TranslateString("","Francois");
	ch.lastname 	= TranslateString("","Vautrin");
	ch.id		= "Pointe a Pitre Commander"; // KK
	ch.model = Nations[FRANCE].fantomModel.m0; // KK was "soldier_fra"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Guadeloupe";
	ch.location.group = "reload";
	ch.location.locator = "reload_1";
	ch.nation = FRANCE;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -2623.564; // PB
	ch.ship.pos.z = -2333.141; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 30; // KK
	ch.Fort.Cannons.Type.2.Quantity = 40; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Pointe a Pitre"; // KK
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Bernard";
	ch.old.lastname = "Fokke";
	ch.name 	= TranslateString("","Bernard");
	ch.lastname 	= TranslateString("","Fokke");
	ch.id		= "Philipsburg Commander";
	ch.model = Nations[HOLLAND].fantomModel.m0; // KK was "soldier_hol"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "SaintMartin";
	ch.location.group = "reload";
	ch.location.locator = "reload1_2";
	ch.nation = HOLLAND;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = 60.82787; // PB
	ch.ship.pos.z = 1282.235; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 29; // KK
	ch.Fort.Cannons.Type.2.Quantity = 40; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Philipsburg";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Pierre";
	ch.old.lastname = "Luniere";
	ch.name 	= TranslateString("","Pierre");
	ch.lastname 	= TranslateString("","Luniere");
	ch.id		= "Marigot Commander";
	ch.model = Nations[FRANCE].fantomModel.m0; // KK was "soldier_fra"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "SaintMartin";
	ch.location.group = "reload";
	ch.location.locator = "reload_5";
	ch.nation = FRANCE;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -1199.019; // PB
	ch.ship.pos.z = -972.0608; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 6; // KK
	ch.Fort.Cannons.Type.2.Quantity = 14; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Marigot";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Honore";
	ch.old.lastname = "Rimbaut";
	ch.name 	= TranslateString("","Honore");
	ch.lastname 	= TranslateString("","Rimbaut");
	ch.id		= "Port au Prince Commander";
	ch.model = Nations[FRANCE].fantomModel.m0; // KK was "soldier_fra"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Hispaniola";
	ch.location.group = "reload";
	ch.location.locator = "reload1_2";
	ch.nation = FRANCE;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -4116.84; // PB
	ch.ship.pos.z = -1384.702; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 30; // KK
	ch.Fort.Cannons.Type.2.Quantity = 40; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Port au Prince";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Arno";
	ch.old.lastname = "Salsa";
	ch.name 	= TranslateString("","Arno");
	ch.lastname 	= TranslateString("","Salsa");
	ch.id		= "Santo Domingo Commander";
	ch.model = Nations[SPAIN].fantomModel.m0; // KK was "soldier_spa"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Hispaniola";
	ch.location.group = "reload";
	ch.location.locator = "reload_8";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = 4338.215; // PB
	ch.ship.pos.z = -2254.132; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 30; // KK
	ch.Fort.Cannons.Type.2.Quantity = 40; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Santo Domingo";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Walter";
	ch.old.lastname = "Talleyrand";
	ch.name 	= TranslateString("","Walter");
	ch.lastname 	= TranslateString("","Talleyrand");
	ch.id		= "Tortuga Commander";
	ch.model = "50Grey1";
	ch.sex = "man";
	ch.act.type = "pirate";
	ch.location = "Hispaniola";
	ch.location.group = "reload";
	ch.location.locator = "reload_6";
	ch.nation = FRANCE;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -95.08528; // PB
	ch.ship.pos.z = 7897.716; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	ch.Fort.Cannons.Type.1.Quantity = 30; // KK
	ch.Fort.Cannons.Type.2.Quantity = 40; // KK
	// KNB <--
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Tortuga";
	// RM <--
	AddGameCharacter(n, ch);

// KK -->
	ch.old.name = "Marius";
	ch.old.lastname = "Yberville";
	ch.name 	= TranslateString("","Marius");
	ch.lastname 	= TranslateString("","Yberville");
	ch.id		= "Grand Turk Commander";
	ch.model = "50Grey1";
	ch.sex = "man";
	ch.act.type = "pirate";
	ch.location = "Turks";
	ch.location.group = "reload";
	ch.location.locator = "reload1_2";
	ch.nation = PIRATE;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -1645.387; // PB
	ch.ship.pos.z = 23.00062; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	ch.Fort.Cannons.Type.1.Quantity = 6; // KK
	ch.Fort.Cannons.Type.2.Quantity = 14; // KK
	// KNB <--
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Grand Turk";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Gerrit";
	ch.old.lastname = "Schotte";
	ch.name 	= TranslateString("","Gerrit");
	ch.lastname 	= TranslateString("","Schotte");
	ch.id		= "Willemstad Commander";
	ch.model = Nations[HOLLAND].fantomModel.m0;
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Curacao";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = HOLLAND;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "9";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "5";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = 770.1185; // PB
	ch.ship.pos.z = -1871.272; // PB
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 13; // KK
	ch.Fort.Cannons.Type.2.Quantity = 25; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Willemstad";
	// RM <--
	AddGameCharacter(n, ch);

	ch.old.name = "Philip";
	ch.old.lastname = "Rockridge";
	ch.name 	= TranslateString("","Philip");
	ch.lastname 	= TranslateString("","Rockridge");
	ch.id		= "Eleuthera Commander";
	ch.model = Nations[ENGLAND].fantomModel.m0;
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Eleuthera";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = ENGLAND;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "4";
	ch.skill.Fencing = "5";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "6";
	ch.skill.Cannons = "5";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "3";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = 991.127; // PB
	ch.ship.pos.z = -839.5062; // PB
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 0; //69?; // KK
	ch.Fort.Cannons.Type.2.Quantity = 88; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Eleuthera";
	// RM <--
	AddGameCharacter(n, ch);

	/*ch.old.name = "Oranjestad Fort";
	ch.old.lastname = "Commandant";
	ch.name 	= TranslateString("","Oranjestad Fort");
	ch.lastname 	= TranslateString("","Commandant");
	ch.id		= "Oranjestad Commander";
	ch.model = Nations[HOLLAND].fantomModel.m0; // KK was "Soldier_hol"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Aruba";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = HOLLAND;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	ch.Fort.Cannons.Type.1.Quantity = 18; // KK
	ch.Fort.Cannons.Type.2.Quantity = 30; // KK
	// KNB <--
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Oranjestad";
	// RM <--
	AddGameCharacter(n, ch);*/
// <-- KK

	ch.old.name = "Pedro";
	ch.old.lastname = "de Heredia";
	ch.name 	= TranslateString("", "Pedro");
	ch.lastname 	= TranslateString("","de Heredia");
	ch.id		= "Cartagena Commander";
	ch.model = Nations[SPAIN].fantomModel.m0;
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "Colombia";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "65";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "7";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "4";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.money.quest = "0";
	ch.quest.meeting = "0";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = 128.2023; // PB
	ch.ship.pos.z = -394.4997; // PB
	ch.ship.crew.quantity = 500;
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 31;
	ch.Fort.Cannons.Type.2.Quantity = 30;
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Cartagena";
	// RM <--
	AddGameCharacter(n, ch);
	
	ch.old.name = "John";
	ch.old.lastname = "Smith";
	ch.name 	= TranslateString("", "John");
	ch.lastname 	= TranslateString("","Smith");
	ch.id		= "Charlestown Commander";
	ch.model	= Nations[ENGLAND].fantomModel.m0; // KK was "Soldier_eng3"
	ch.sex = "man";
	ch.act.type = "Soldier";
	ch.location = "QuebradasCostillas";
	ch.location.group = "reload";
	ch.location.locator = "reload_fort1";
	ch.nation = ENGLAND;
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "9";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "5";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "8";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.ship.type = SHIP_FORT_NAME; // PS
	ch.ship.pos.x = -1075.986; // PB
	ch.ship.pos.z = -651.965; // PB
	ch.Fort.Cannons.Charge.Type = GOOD_BOMBS;
	// KNB -->
	if(USE_REAL_CANNONS)
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_LONG_LBS42;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CARRONADE_LBS68;
	}
	else
	{
		ch.Fort.Cannons.Type.1 = CANNON_TYPE_CULVERINE_LBS24;
		ch.Fort.Cannons.Type.2 = CANNON_TYPE_CANNON_LBS32;
	}
	// KNB <--
	ch.Fort.Cannons.Type.1.Quantity = 22; // KK
	ch.Fort.Cannons.Type.2.Quantity = 28; // KK
	LAi_SetHP(ch, 100.0, 100.0);
	// RM -->
	ch.town = "Charlestown";
	// RM <--
	AddGameCharacter(n, ch);	

///////////////////////////////////////////////////
}
