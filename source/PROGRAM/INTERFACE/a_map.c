
void InitInterface(string iniName)
{
    GameInterface.title = "titleReserved";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	// CreateExitString();//MAXIMUS: standard exit-string for exit-button

    ref chm = GetMainCharacter();
	CreateString(true,"TIME",GetHumanDate(GetDataYear(), GetDataMonth(), GetDataDay()) + " - " + GetStringTime(GetTime()),"INTERFACE_SMALL",COLOR_BLUE_LIGHT,620,460,SCRIPT_ALIGN_RIGHT,0.5);

	if(CheckAttribute(chm, "maplegend"))		// PB: Show note on Right-Clicking functionality
	{
		CreateString(true, "HelpText", XI_ConvertString("MapHelpString"), FONT_NORMAL, COLOR_MONEY, 320, 478, SCRIPT_ALIGN_CENTER, 0.7);
		DeleteAttribute(chm, "maplegend");	// ... but only once
	}

	HideToolT();
	ShowMap();
	ShowButtons();

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","HideToolT",1);
}

void ShowMap()
{
	object fakeMap;
	ref chm = GetMainCharacter();

	float startX = makefloat(199.0)+makefloat(23.0); //189
	float startY = makefloat(37.0)+makefloat(23.0); //50
	float endX = makefloat(665.0)-makefloat(23.0); //653
	float endY = makefloat(501.0)-makefloat(23.0); //493

	float FAKE_MAP_TO_SEA_SCALE_X = makefloat(2000/stf(endX-startX)) * -1.0;
	float FAKE_MAP_TO_SEA_SCALE_Y = makefloat(2000/stf(endY-startY)) * -1.0;

	float fakeMapPosX = makefloat(sti(stf(endX-startX)/2)+startX);
	float fakeMapPosY = makefloat(sti(stf(endY-startY)/2)+startY);

	fakeMap.X = fakeMapPosX;
	fakeMap.Y = fakeMapPosY;

	fakeMap.poz.X = makefloat(makefloat(worldMap.playerShipX)/FAKE_MAP_TO_SEA_SCALE_X);
	fakeMap.poz.Y = makefloat(makefloat(worldMap.playerShipZ)/FAKE_MAP_TO_SEA_SCALE_Y);

	int fakeShipPosX = makeint(makefloat(fakeMap.X) - makefloat(fakeMap.poz.X));
	int fakeShipPosY = makeint(makefloat(fakeMap.Y) + makefloat(fakeMap.poz.Y))-15;

	ref shipRef = GetShipByType(GetCharacterShipType(chm));
	aref arship; makearef(arship, chm.ship);
	int picScale = 7;

	// PB: Legend -->
	if(bAnimation)
	{
		int x,y;
		x = 45; y = 105;
		CreateString(true,"LEGEND","- LEGEND -","interface_coas",COLOR_YELLOW_LIGHT,x+10,y-5,SCRIPT_ALIGN_LEFT,0.7);
		
		x = x-10; y = y+20;
		CreateString(true,"SHIP_LEGEND",": Ship Position","interface_coas",COLOR_YELLOW_LIGHT,x+10,y-5,SCRIPT_ALIGN_LEFT,0.7);
		CreateImage("SHIP_ICON", "SHIPS16", "Brig1", sti(x-picScale), sti(y-picScale)+2, sti(x+picScale), sti(y+picScale)+2);

		y = y+20;
		CreateString(true,"CONVOY_LEGEND",": Escort Destination","interface_coas",COLOR_YELLOW_LIGHT,x+10,y-5,SCRIPT_ALIGN_LEFT,0.7);
		CreateImage("CONVOY_ICON", "ICONS", "ship speed icon", sti(x-picScale), sti(y-picScale)+2, sti(x+picScale), sti(y+picScale)+2);

		y = y+20;
		CreateString(true,"CARGO_LEGEND",": Cargo Destination","interface_coas",COLOR_YELLOW_LIGHT,x+10,y-5,SCRIPT_ALIGN_LEFT,0.7);
		CreateImage("CARGO_ICON", "ICONS", "ship capacity icon", sti(x-picScale), sti(y-picScale)+2, sti(x+picScale), sti(y+picScale)+2);

		y = y+20;
		CreateString(true,"TREASURE_LEGEND",": Hidden Treasure","interface_coas",COLOR_YELLOW_LIGHT,x+10,y-5,SCRIPT_ALIGN_LEFT,0.7);
		CreateImage("TREASURE_ICON", "MARK", "mark", sti(x-picScale), sti(y-picScale)+2, sti(x+picScale), sti(y+picScale)+2);
	}
	// PB: Legend <--

	// PB: Sextant and Chronometer -->
	bool ShowPosition = iRealismMode == 0 && !NAVIGATION_EQUIPMENT;
	if(!bSeaActive) ShowPosition = true; // You know where you are when you are ashore
	if(CheckCharacterItem(chm,"clock2") && CheckCharacterItem(chm,"sextant")) ShowPosition = true;
	if(ShowPosition)
	{
		CreateImage("SHIP", "SHIPS16", "Brig1", sti(fakeShipPosX-picScale), sti(fakeShipPosY-picScale), sti(fakeShipPosX+picScale), sti(fakeShipPosY+picScale)); // PB: Brig matches with worldmap player ship model
		SetPictureBlind("SHIP",true,minBlindColor,maxBlindColor);
	}
	// PB: Sextant and Chronometer <--

	// stljeffbb Jan 15 2012 -->
	if(iRealismMode>1 || OPEN_SEA_MOD) {
		// SetNodeUsing("MAP", false);
		// SetNodeUsing("MAP_SCALED", true);
		SetNodeUsing("MAP", true);
		SetNodeUsing("MAP_SCALED", false);
	}else{
		SetNodeUsing("MAP", true);
		SetNodeUsing("MAP_SCALED", false);
	}
	// stljeffbb Jan 15 2012 <--

	aref refIsl; makearef(refIsl, worldMap.islands);
	for(int n=0; n<GetAttributesNum(refIsl); n++)
	{
		string isIsland = GetAttributeName(GetAttributeN(refIsl,n));
		if(!CheckAttribute(worldMap,"islands."+isIsland)) continue;
		if (!CheckAttribute(worldMap,"islands."+isIsland+".position")) continue;	// LDH 25Jan09

		string isName = worldMap.islands.(isIsland).label.text;
		float pozX = makefloat(makefloat(worldMap.islands.(isIsland).position.x)/FAKE_MAP_TO_SEA_SCALE_X);
		float pozY = makefloat(makefloat(worldMap.islands.(isIsland).position.z)/FAKE_MAP_TO_SEA_SCALE_Y);

		// PB: Improved Island labels -->
		int fakeX = makeint(makefloat(fakeMap.X) - pozX);
		int fakeY = makeint(makefloat(fakeMap.Y) + pozY)-20;
		switch(isIsland)
		{
			case "IslaMona":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-5,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Battle_Rocks":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-28,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "IslaMuelle":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY+2,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "SaintMartin":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-5,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "QuebradasCostillas":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-10,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Guadeloupe":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-20,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "FalaiseDeFleur":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-30,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Oxbay":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-30,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Conceicao":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-30,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Eleuthera":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY+10,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Cuba":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY+10,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Douwesen":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-30,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Curacao":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-30,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Aruba":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-30,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Colombia":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-30,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Antigua":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-10,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Redmond":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-5,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "Turks":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY+10,SCRIPT_ALIGN_CENTER,0.5);
			break;
			case "":
				CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-5,SCRIPT_ALIGN_CENTER,0.5);
			break;
			CreateString(true,isIsland,isName,"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY,SCRIPT_ALIGN_CENTER,0.5);
		}
		// PB: Improved Island labels <--
		aref wIsland; makearef(wIsland, worldMap.islands.(isIsland).locations);
		for(int c=0; c<GetAttributesNum(wIsland); c++)
		{
			string cityNum = "city"+sti(c+1);
			if(CheckAttribute(wIsland,cityNum))
			{
				string colonyName = wIsland.(cityNum).name;
				pozX = makefloat(makefloat(wIsland.(cityNum).position.x)/FAKE_MAP_TO_SEA_SCALE_X);
				pozY = makefloat(makefloat(wIsland.(cityNum).position.z)/FAKE_MAP_TO_SEA_SCALE_Y);
				int fakeXr = makeint(makefloat(fakeMap.X) + pozX);
				int fakeYr = makeint(makefloat(fakeMap.Y) - pozY)-15;
				if(CheckAttribute(wIsland,cityNum+".real"))
				{
					if(isIsland=="Hispaniola" && cityNum=="city3" && iRealismMode<2 && !OPEN_SEA_MOD) CreateString(true,wIsland.(cityNum).name,FindTownName(colonyName),"seadogs",COLOR_GREEN_LIGHT,fakeX,fakeY-20,SCRIPT_ALIGN_CENTER,0.5);
					if(GetAttribute(chm, "quest.generate_convoy_quest.destination") == wIsland.(cityNum).real)
					{
						CreateImage("CONVOY", "ICONS", "ship speed icon", fakeXr-5, fakeYr+7, fakeXr+9, fakeYr+21);
						if(HasSubStr(chm.location,"tavern") || chm.location == "Antigua_mansion_study")
						{
							SetPictureBlind("CONVOY",true,minBlindColor,maxBlindColor);
							SetPictureBlind("SHIP",false,minBlindColor,maxBlindColor);
						}
					}

					int ShowTradeQuest = 0;
					if(GetAttribute(chm, "quest.generate_trade_quest_progress") == "begin")	ShowTradeQuest = 1;
					if(HasSubStr(chm.location,"store"))										ShowTradeQuest = 2;
					if(GetAttribute(chm, "quest.generate_trade_quest_progress.iTradeColony") == wIsland.(cityNum).real && ShowTradeQuest > 0)
					{
						CreateImage("CARGO", "ICONS", "ship capacity icon", fakeXr-5, fakeYr+7, fakeXr+9, fakeYr+21);
						if(ShowTradeQuest > 1)
						{
							SetPictureBlind("CARGO",true,minBlindColor,maxBlindColor);
							SetPictureBlind("SHIP",false,minBlindColor,maxBlindColor);
						}
					}
				}

				// PB: Treasure Quests -->
				if(GetAttribute(chm, "treasureloc") == wIsland.(cityNum).name)
				{
					CreateImage("MARK", "MARK", "mark", fakeXr-5, fakeYr+7, fakeXr+9, fakeYr+21);
					if(CheckAttribute(chm, "treasuremap"))
					{
						SetPictureBlind("MARK",true,minBlindColor,maxBlindColor);
						SetPictureBlind("SHIP",false,minBlindColor,maxBlindColor);
						DeleteAttribute(chm, "treasuremap");
					}
				}
				// PB: Treasure Quests <--
			}
		}
	}
}

void ShowButtons()
{
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, "EXIT_BUTTON");

	for(int i=0; i<ISLANDS_QUANTITY+1; i++)
	{
		string rcString = "RECTANGLE"+sti(i+2);
		SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, rcString);
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	if(comName!="rclick") return;
//	if (!bRMouseDown) return; // PB: Add functionality to left button too

	for(int i=0; i<ISLANDS_QUANTITY+2; i++)
	{
		string rcString = "RECTANGLE"+sti(i+1);
		if(nodName!=rcString) continue;
		ShowIslandInfo(i); break;
	}
}

void ShowIslandInfo(int Idx) 
{
	string sHeader = "";
	string sText1 = "";
	int isIdx = Idx;
	if(Idx==22) { isIdx = 9; }
	sHeader = Islands[isIdx].id;
	int colonyNation = -1;

	string isIsland = Islands[isIdx].id;
	
	string itmName = "map" + isIsland;
	
	// PB: On left-click, try to open Island Map -->
	ref PChar = GetMainCharacter();
	if (!bRMouseDown)
	{
		if (CheckCharacterItem(PChar, itmName) == true)
		{
			aref itmRef;
			if (Items_FindItem(itmName, &itmRef) >= 0 && CheckAttribute(itmRef, "index")) GameInterface.ItemIdx = itmRef.index;
			
			PChar.from_map = true;
			
			PostEvent("LaunchIAfterFrame",1,"sl", "I_MAP", 2);
			InterfaceStack.SelectMenu_node = "I_MAP";
			interfaceResultCommand = RC_INTERFACE_ITEMS_EXIT;
			EndCancelInterface(false);
		}
	}
	// PB: On left-click, try to open Island Map <--
	else
	{
		for(int c=1; c<10; c++)
		{
			string cityNum = "city"+c;
			if(CheckAttribute(worldMap,"islands."+isIsland+".locations."+cityNum+".label.text") && CheckAttribute(worldMap,"islands."+isIsland+".locations."+cityNum+".real") && CheckAttribute(worldMap,"islands."+isIsland+".locations."+cityNum+".label.icon"))
			{
				string colonyName = worldMap.islands.(isIsland).locations.(cityNum).name;
				string colonyId = worldMap.islands.(isIsland).locations.(cityNum).name;
				colonyNation = sti(worldMap.islands.(isIsland).locations.(cityNum).label.icon);
				if (colonyNation == 8)	colonyNation = PERSONAL_NATION;
				if(Idx==9 && cityNum=="city3") { sText1 += ""; colonyNation = sti(worldMap.islands.(isIsland).locations.city2.label.icon); }
				else sText1 += TranslateString("", FindTownName(colonyId))+" - "+XI_ConvertString(GetNationNameByType(colonyNation)) +"                                                                                             ";
				if(Idx==22 && cityNum=="city3") { sHeader = FindTownName(colonyId); isIsland = worldMap.islands.(isIsland).locations.(cityNum).name; sText1 = TranslateString("", FindTownName(colonyId))+" - "+XI_ConvertString(GetNationNameByType(colonyNation)); } // Tortuga
			}
		}
		if(Idx!=22) // For all except Tortuga
		{
			colonyNation = Islands[isIdx].smuggling_nation;
			sHeader = TranslateString("", FindIslandName(sHeader));
		}
		CreateTooltip(sHeader, sText1, colonyNation);
	}
}

void CreateTooltip(string header, string text1, int colonyNation)
{
	SetNodeUsing("WINDOW_FAD",true);
	SetNodeUsing("RECT",true);
	SetNodeUsing("INFO_PICT",true);
	SetNodeUsing("TEXT",true);
	SetCurrentNode("TEXT");
	SetFormatedText("TEXT",header);
	SetNodeUsing("INFO_TEXT",true);
	SetFormatedText("INFO_TEXT",text1);
	SetSelectable("EXIT_BUTTON",false);

	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 1, "WINDOW_FAD");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 2, "RECT");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 3, "INFO_PICT");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 3, "INFO_TEXT");
	SendMessage(&GameInterface,"lls", MSG_INTERFACE_LOCK_NODE, 3, "TEXT");

	SetNewPicture("INFO_PICT", "interfaces\flags\Crest_" + GetNationFlagImage(colonyNation) + ".tga");
}

void HideToolT()
{
	if (bRMouseDown) return;

	SendMessage(&GameInterface,"ll", MSG_INTERFACE_LOCK_NODE, 0);

	SetNodeUsing("WINDOW_FAD",false);
	SetNodeUsing("RECT", false);
	SetNodeUsing("INFO_PICT",false);
	SetNodeUsing("TEXT",false);
	SetNodeUsing("INFO_TEXT",false);
	SetSelectable("EXIT_BUTTON",true);
	SetCurrentNode("OFFIC_1");
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_A_MAP_EXIT );
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","HideToolT");

	ref PChar = GetMainCharacter();
	if(CheckAttribute(PChar, "inventory"))
	{
		DeleteAttribute(GameInterface, "islandlist");
		DeleteAttribute(GameInterface, "maplist");
		PostEvent("LaunchIAfterFrame",1,"sl", "I_ITEMS", 2);
		InterfaceStack.SelectMenu_node = "I_ITEMS";
		interfaceResultCommand = exitCode;
		EndCancelInterface(false);
	}
	else
	{
		interfaceResultCommand = exitCode;
		EndCancelInterface(true);
	}
}
