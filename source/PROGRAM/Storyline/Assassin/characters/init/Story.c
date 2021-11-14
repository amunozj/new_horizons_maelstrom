void CreateStoryCharacters(ref n)
{
	object chobj;
	ref ch;
	makeref(ch, chobj);

	 // Salvadore Benavides
	ch.old.name = "Salvadore";
	ch.old.lastname = "Benavides";
	ch.name 	= TranslateString("", "Salvadore");
	ch.lastname = TranslateString("", "Benavides");
	ch.id		= "Salvadore Benavides";
	ch.model	= "Salvadore";
	ch.sex = "man";
	ch.location	= "Havana_House_03";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Salvadore Benavides_dialog.c";
	ch.rank 	= 15;
	ch.reputation = "80";
	ch.experience = "0";
	ch.skill.Leadership = "10";
	ch.skill.Fencing = "7";
	ch.skill.Sailing = "4";
	ch.skill.Accuracy = "6";
	ch.skill.Cannons = "4";
	ch.skill.Grappling = "4";
	ch.skill.Repair = "4";
	ch.skill.Defence = "5";
	ch.skill.Commerce = "10";
	ch.skill.Sneak = "0";
	ch.money = "10000";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetLoginTime(ch, 0.0, 24.0);	
	ch.greeting = "Gr_christofor manuel de alencar";
	AddGameCharacter(n, ch);

// Spanish Soldier.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "spanish_soldat_01";
	ch.model = "Soldier_Spa_16";
	ch.sex = "man";
	ch.sound_type = "soldier";
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Havana_House_03";
	ch.location.group = "goto";
	ch.location.locator = "goto9";
	ch.Dialog.Filename = "Isla Muelle soldier_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetStayType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SPAIN_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);
	
// Spanish Soldier.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "spanish_soldat_02";
	ch.model = "Soldier_Spa2_16";
	ch.sex = "man";
	ch.sound_type = "soldier";
	GiveItem2Character(ch, "pistol1a");
	ch.equip.gun = "pistol1a";
	//JRH ammo mod -->
	if (ENABLE_AMMOMOD) {	// LDH change
		TakenItems(ch, "gunpowder", 1 + rand(2));
		TakenItems(ch, "pistolbullets", 1 + rand(2));
	}
	//JRH ammo mod <--		
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Quest_Oranjestad_exit";
	ch.location.group = "goto";
	ch.location.locator = "goto9";
	ch.Dialog.Filename = "Isla Muelle soldier_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetStayType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SIEGE_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

// Spanish Soldier.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "spanish_soldat_03";
	ch.model = "Soldier_Spa3_16";
	ch.sex = "man";
	ch.sound_type = "soldier";
	GiveItem2Character(ch, "pistol1a");
	ch.equip.gun = "pistol1a";
	//JRH ammo mod -->
	if (ENABLE_AMMOMOD) {	// LDH change
		TakenItems(ch, "gunpowder", 1 + rand(2));
		TakenItems(ch, "pistolbullets", 1 + rand(2));
	}
	//JRH ammo mod <--		
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Quest_Oranjestad_exit";
	ch.location.group = "goto";
	ch.location.locator = "goto8";
	ch.Dialog.Filename = "Isla Muelle soldier_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetStayType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SIEGE_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

// Spanish Soldier.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "spanish_soldat_04";
	ch.model = "Soldier_Spa4_16";
	ch.sex = "man";
	ch.sound_type = "soldier";
	GiveItem2Character(ch, "pistol1a");
	ch.equip.gun = "pistol1a";
	//JRH ammo mod -->
	if (ENABLE_AMMOMOD) {	// LDH change
		TakenItems(ch, "gunpowder", 1 + rand(2));
		TakenItems(ch, "pistolbullets", 1 + rand(2));
	}
	//JRH ammo mod <--		
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Quest_Oranjestad_exit";
	ch.location.group = "goto";
	ch.location.locator = "goto7";
	ch.Dialog.Filename = "Isla Muelle soldier_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetStayType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SIEGE_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

// Spanish Soldier.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "spanish_soldat_05";
	ch.model = "Soldier_Spa5_16";
	ch.sex = "man";
	ch.sound_type = "soldier";
	GiveItem2Character(ch, "pistol1a");
	ch.equip.gun = "pistol1a";
	//JRH ammo mod -->
	if (ENABLE_AMMOMOD) {	// LDH change
		TakenItems(ch, "gunpowder", 1 + rand(2));
		TakenItems(ch, "pistolbullets", 1 + rand(2));
	}
	//JRH ammo mod <--		
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Quest_Oranjestad_exit";
	ch.location.group = "goto";
	ch.location.locator = "goto6";
	ch.Dialog.Filename = "Isla Muelle soldier_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetStayType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SIEGE_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

// Spanish Soldier.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "spanish_soldat_06";
	ch.model = "Soldier_Spa6_16";
	ch.sex = "man";
	ch.sound_type = "soldier";
	GiveItem2Character(ch, "pistol1a");
	ch.equip.gun = "pistol1a";
	//JRH ammo mod -->
	if (ENABLE_AMMOMOD) {	// LDH change
		TakenItems(ch, "gunpowder", 1 + rand(2));
		TakenItems(ch, "pistolbullets", 1 + rand(2));
	}
	//JRH ammo mod <--		
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Quest_Oranjestad_exit";
	ch.location.group = "goto";
	ch.location.locator = "goto5";
	ch.Dialog.Filename = "Isla Muelle soldier_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetStayType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SIEGE_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

// Spanish Soldier.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "spanish_soldat_07";
	ch.model = "Soldier_Spa_16";
	ch.sex = "man";
	ch.sound_type = "soldier";
	GiveItem2Character(ch, "pistol1a");
	ch.equip.gun = "pistol1a";
	//JRH ammo mod -->
	if (ENABLE_AMMOMOD) {	// LDH change
		TakenItems(ch, "gunpowder", 1 + rand(2));
		TakenItems(ch, "pistolbullets", 1 + rand(2));
	}
	//JRH ammo mod <--		
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Quest_Oranjestad_exit";
	ch.location.group = "goto";
	ch.location.locator = "goto2";
	ch.Dialog.Filename = "Isla Muelle soldier_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetStayType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SIEGE_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

//------------- Vera Cruz characters -----------------------	
			// Soldier
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz Soldier 01";
	ch.model = 1; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_port";
	ch.location.group = "goto";
	ch.location.locator = "goto19";
	ch.Dialog.Filename = "Isla Muelle Soldier_dialog.c";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "50";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "3";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetGuardianType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SPAIN_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

			// Soldier
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz Soldier 02";
	ch.model = 2; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_port";
	ch.location.group = "goto";
	ch.location.locator = "goto18";
	ch.Dialog.Filename = "Isla Muelle Soldier_dialog.c";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "50";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetGuardianType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SPAIN_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

			// Soldier
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz Soldier 03";
	ch.model = 5; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_port";
	ch.location.group = "goto";
	ch.location.locator = "goto3";
	ch.Dialog.Filename = "Isla Muelle Soldier_dialog.c";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "50";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetPatrolType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SPAIN_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

			// patrol
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz patrol 01";
	ch.model = 4; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_port";
	ch.location.group = "goto";
	ch.location.locator = "goto8";
	ch.Dialog.Filename = "Patrol_dialog.c";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "50";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "3";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetPatrolType(ch);
	LAi_SetLoginTime(ch, 22.0, 5.98333);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SPAIN_SOLDIERS");
	ch.greeting = "Gr_Patrol";
	AddGameCharacter(n, ch);

			// patrol
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz patrol 02";
	ch.model = 3; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_port";
	ch.location.group = "goto";
	ch.location.locator = "goto7";
	ch.Dialog.Filename = "Patrol_dialog.c";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "50";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "2";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetPatrolType(ch);
	LAi_SetLoginTime(ch, 22.0, 5.98333);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "SPAIN_SOLDIERS");
	ch.greeting = "Gr_Patrol";
	AddGameCharacter(n, ch);

			// Soldier.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz Soldier 04";
	ch.model = 2; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_01";
	ch.location.group = "goto";
	ch.location.locator = "goto9";
	ch.Dialog.Filename = "Isla Muelle soldier_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetGuardianType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "VERA_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

			// Soldier.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz Soldier 05";
	ch.model = 3; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_01";
	ch.location.group = "goto";
	ch.location.locator = "goto11";
	ch.Dialog.Filename = "Isla Muelle soldier_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetGuardianType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "VERA_SOLDIERS");
	ch.greeting = "Gr_isla muelle soldier";
	AddGameCharacter(n, ch);

			// Patrol.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz patrol 03";
	ch.model = 6; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_01";
	ch.location.group = "goto";
	ch.location.locator = "goto23";
	ch.Dialog.Filename = "patrol_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "2";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetPatrolType(ch);
	LAi_SetLoginTime(ch, 22.0, 5.98333);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "VERA_SOLDIERS");
	ch.greeting = "Gr_Patrol";
	AddGameCharacter(n, ch);

			// Patrol.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz patrol 04";
	ch.model = 4; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_01";
	ch.location.group = "goto";
	ch.location.locator = "goto62";
	ch.Dialog.Filename = "patrol_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "2";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetPatrolType(ch);
	LAi_SetLoginTime(ch, 22.0, 5.98333);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "VERA_SOLDIERS");
	ch.greeting = "Gr_Patrol";
	AddGameCharacter(n, ch);

			// Patrol.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz patrol 05";
	ch.model = 3; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_01";
	ch.location.group = "goto";
	ch.location.locator = "goto82";
	ch.Dialog.Filename = "patrol_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "2";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetPatrolType(ch);
	LAi_SetLoginTime(ch, 22.0, 5.98333);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "VERA_SOLDIERS");
	ch.greeting = "Gr_Patrol";
	AddGameCharacter(n, ch);

			// Patrol.
	ch.nation = SPAIN;
	ch.old.name = "Soldier";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Soldier");
	ch.lastname = "";
	ch.id		= "Vera Cruz patrol 06";
	ch.model = 6; // PB
	ch.sex = "man";
	ch.sound_type = "soldier";
	LAi_CharacterReincarnation(ch, true, false);
	GiveItem2Character(ch, "blade2");
	ch.equip.blade = "blade2";
	ch.location	= "Vera_Cruz_01";
	ch.location.group = "goto";
	ch.location.locator = "goto94";
	ch.Dialog.Filename = "patrol_dialog.c";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "2";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetPatrolType(ch);
	LAi_SetLoginTime(ch, 22.0, 5.98333);
	LAi_SetHP(ch, 80.0, 80.0);
	LAi_group_MoveCharacter(ch, "VERA_SOLDIERS");
	ch.greeting = "Gr_Patrol";
	AddGameCharacter(n, ch);

			// Indian 1.
	ch.nation = SPAIN;
	ch.old.name = "Indian";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Indian");
	ch.lastname = "";
	ch.id		= "Indian 1";
	ch.model = "Indian1_1";
	ch.sex = "man";
	ch.sound_type = "male_citizen";
	ch.location	= "Vera_Cruz_01";
	ch.location.group = "goto";
	ch.location.locator = "goto79";
	ch.Dialog.Filename = "Isla Muelle citizen_dialog.c";
	ch.greeting = "Gr_isla muelle citizen";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetCitizenType(ch);
	LAi_SetLoginTime(ch, 8.0, 20.0);		
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	AddGameCharacter(n, ch);

			// Indian 2.
	ch.nation = SPAIN;
	ch.old.name = "Indian";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Indian");
	ch.lastname = "";
	ch.id		= "Indian 2";
	ch.model = "Indian1_2";
	ch.sex = "man";
	ch.sound_type = "male_citizen";
	ch.location	= "Vera_Cruz_01";
	ch.location.group = "goto";
	ch.location.locator = "goto52";
	ch.Dialog.Filename = "Isla Muelle citizen_dialog.c";
	ch.greeting = "Gr_isla muelle citizen";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetCitizenType(ch);
	LAi_SetLoginTime(ch, 8.0, 20.0);		
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	AddGameCharacter(n, ch);

			// Indian 3.
	ch.nation = SPAIN;
	ch.old.name = "Indian";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Indian");
	ch.lastname = "";
	ch.id		= "Indian 3";
	ch.model = "Indian1_3";
	ch.sex = "man";
	ch.sound_type = "male_citizen";
	ch.location	= "Vera_Cruz_01";
	ch.location.group = "goto";
	ch.location.locator = "goto100";
	ch.Dialog.Filename = "Isla Muelle citizen_dialog.c";
	ch.greeting = "Gr_isla muelle citizen";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetCitizenType(ch);
	LAi_SetLoginTime(ch, 8.0, 20.0);		
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	AddGameCharacter(n, ch);

			// Indian 4.
	ch.nation = SPAIN;
	ch.old.name = "Indian";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Indian");
	ch.lastname = "";
	ch.id		= "Indian 4";
	ch.model = "Indian2";
	ch.sex = "man";
	ch.sound_type = "male_citizen";
	ch.location	= "Vera_Cruz_port";
	ch.location.group = "goto";
	ch.location.locator = "goto11";
	ch.Dialog.Filename = "Isla Muelle citizen_dialog.c";
	ch.greeting = "Gr_isla muelle citizen";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetCitizenType(ch);
	LAi_SetLoginTime(ch, 8.0, 20.0);		
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	AddGameCharacter(n, ch);

			// Indian 5.
	ch.nation = SPAIN;
	ch.old.name = "Indian";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Indian");
	ch.lastname = "";
	ch.id		= "Indian 5";
	ch.model = "Indian3";
	ch.sex = "man";
	ch.sound_type = "male_citizen";
	ch.location	= "Vera_Cruz_port";
	ch.location.group = "goto";
	ch.location.locator = "goto4";
	ch.Dialog.Filename = "Isla Muelle citizen_dialog.c";
	ch.greeting = "Gr_isla muelle citizen";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetCitizenType(ch);
	LAi_SetLoginTime(ch, 8.0, 20.0);		
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	AddGameCharacter(n, ch);

			// Indian 6.
	ch.nation = SPAIN;
	ch.old.name = "Indian";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Indian");
	ch.lastname = "";
	ch.id		= "Indian 6";
	ch.model = "Indian_girl1";
	ch.sex = "woman";
	ch.sound_type = "female_citizen";
	ch.location	= "Vera_Cruz_port";
	ch.location.group = "goto";
	ch.location.locator = "goto8";
	ch.Dialog.Filename = "Isla Muelle citizen_dialog.c";
	ch.greeting = "Gr_Woman_English citizen";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetCitizenType(ch);
	LAi_SetLoginTime(ch, 8.0, 20.0);	
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	AddGameCharacter(n, ch);

	//beggar indian
	ch.old.name = "Indian";
	ch.old.lastname = "";
	ch.name = TranslateString("", "Indian");
	ch.lastname = "";
	ch.id		= "IndianBeggar";
	ch.model	= "Native"; 
	ch.sound_type = "poorman";
	ch.sex = "man";
	ch.nation = SPAIN;
	ch.location	= "Vera_Cruz_Port";
	ch.location.group = "goto";
	ch.location.locator = "goto12";
	ch.Dialog.Filename = "beggar_dialog.c";
	ch.greeting = "Gr_beggar_spa";
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "1";
	ch.skill.Fencing = "1";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "1";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "1";
	ch.money = "10";
	ch.beggar = true; // a simple virtual sailor
	LAi_SetPoorType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	AddGameCharacter(n, ch);

	ch.old.name = "Street";
	ch.old.lastname = "Merchant";
	ch.name = TranslateString("Street", "Merchant");
	ch.lastname = "";
	ch.id		= "VeraCruz_Street_merchant";
	ch.model	= "Man2";
	ch.sound_type = "merchant";
	ch.sex = "man";
	ch.location = "Vera_Cruz_01";
	ch.location.group = "merchant";
	ch.location.locator = "merchant2";
	ch.dialog.filename = "Item Trader_Dialog.c";
	ch.greeting = "Gr_isla muelle citizen";
	ch.nation = SPAIN;
	ch.rank 	= 1;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "6";
	ch.skill.Fencing = "3";
	ch.skill.Sailing = "4";
	ch.skill.Accuracy = "9";
	ch.skill.Cannons = "5";
	ch.skill.Grappling = "5";
	ch.skill.Repair = "6";
	ch.skill.Defence = "8";
	ch.skill.Commerce = "7";
	ch.skill.Sneak = "8";
	ch.quest.area = "Havana";
	ch.money = "10";
	LAi_SetMerchantType(ch);
	LAi_SetHP(ch, 80.0, 80.0);
	AddGameCharacter(n, ch);

			// Aruba Indian Chief
	ch.nation = HOLLAND;
	ch.old.name = "Indian";
	ch.old.lastname = "Chief";
	ch.name = TranslateString("Indian", "Chief");
	ch.lastname = "";
	ch.id		= "Indian Chief";
	ch.model = "Native_Chief";
	ch.sex = "man";
	ch.sound_type = "male_citizen";
    TakeNItems(ch, "bladearrows", 1 + rand(2));
    ch.equip.blade = "bladearrows";
    GiveItem2Character(ch, "pistolbow");
    ch.equip.gun = "pistolbow";
	ch.location	= "Indian_Village";
	ch.location.group = "goto";
	ch.location.locator = "goto7";
	ch.Dialog.Filename = "Indian Chief_dialog.c";
	ch.greeting = "Gr_Douwesen Citizen";
	ch.rank 	= 10;
	ch.reputation = "None";
	ch.experience = "0";
	ch.skill.Leadership = "8";
	ch.skill.Fencing = "6";
	ch.skill.Sailing = "1";
	ch.skill.Accuracy = "1";
	ch.skill.Cannons = "1";
	ch.skill.Grappling = "1";
	ch.skill.Repair = "1";
	ch.skill.Defence = "3";
	ch.skill.Commerce = "1";
	ch.skill.Sneak = "5";
	ch.money = "10";
	ch.quest.meeting = "0";
	LAi_SetStayType(ch);
    LAi_SetImmortal(ch, true);	
	LAi_SetLoginTime(ch, 0.0, 24.0);
	AddGameCharacter(n, ch);

// Sneak barque
	ch.old.name = "";
	ch.old.lastname = "";
	ch.name = "";
	ch.lastname = "";
	ch.id		= "Sneak barque";
	ch.nation	= PIRATE;
	ch.model	= "Pirat8";
	ch.sound_type = "soldier";
	LAi_NoRebirthEnable(ch);
	ch.sex = "man";			
	ch.location	= "";
	ch.location.group = "";
	ch.location.locator = "";
	ch.Dialog.Filename = "";
	ch.rank 	= 4;
	ch.reputation = "70";
	ch.experience = "0";
	ch.money = "0";
	ch.Ship.Name = "Le Malicieux";
	ch.Ship.Type = "TartaneWar";
	ch.Ship.Stopped = true; 
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	AddGameCharacter(n, ch);

// Sneak barque 2
	ch.old.name = "";
	ch.old.lastname = "";
	ch.name = "";
	ch.lastname = "";
	ch.id		= "Sneak barque2";
	ch.nation	= PIRATE;
	ch.model	= "Pirat8";
	ch.sound_type = "soldier";
	LAi_NoRebirthEnable(ch);
	ch.sex = "man";			
	ch.location	= "";
	ch.location.group = "";
	ch.location.locator = "";
	ch.Dialog.Filename = "";
	ch.reputation = "70";
	ch.experience = "0";
	ch.Ship.Name = "Le Malicieux";
	ch.Ship.Type = "FR_Dilligente";
	ch.Ship.Stopped = true; 
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 80.0, 80.0);
	AddGameCharacter(n, ch);			
}
