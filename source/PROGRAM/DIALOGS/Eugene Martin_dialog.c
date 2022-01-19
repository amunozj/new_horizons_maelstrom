void ProcessDialogEvent()
{
	ref NPChar;
	
	DeleteAttribute(&Dialog,"Links");
	aref Link, NextDiag;
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	int iTest;

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	ref PChar = GetMainCharacter();
	PChar.storekeeper.Idx = -1;//MAXIMUS
	if(!CheckAttribute(NPChar, "quest.item_date")) NPChar.quest.item_date = NPChar.quest.meeting;


	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			if(TradeCheck(PChar, NPChar, true))
			{ // NK
				if (npchar.quest.meeting == "0")
				{
					Dialog.snd = "voice\PEBL\PEBL001";
					Dialog.Text = DLG_TEXT[0] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[1] + GetMyFullName(NPChar) + DLG_TEXT[2];
					Link.l1 = DLG_TEXT[3] + GetMyFullName(PChar) + DLG_TEXT[4];
					link.l1.go = "node_1";
				}
				NextDiag.TempNode = "Second time";
			// NK -->
			}
			else
			{
				dialog.text = DLG_TEXT[23] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[24];
				Link.l1 = DLG_TEXT[25];
				Link.l1.go = "exit";
				if(sti(PChar.Skill.Commerce)>=5)
				{
					Link.l2 = TranslateString("","low_trade_1");
					Link.l2.go = "low_price";
				}
				NextDiag.TempNode = "First time";
			}
			// NK <--
		break;

		case "low_price":
			dialog.text = TranslateString("","low_trade_2");
			link.l1 = TranslateString("","low_trade_3");
			link.l1.go = "market_low";
			link.l3 = TranslateString("","low_trade_4");
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "market_low":
			dialog.Text = TranslateString("","low_trade_5");
			Link.l1 = TranslateString("","low_trade_6");
			Link.l1.go = "trade_low";
			Link.l3 = TranslateString("","low_trade_4");
			Link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "trade_low":
			NextDiag.TempNode = "First time";
			DialogExit();
			tradeLow = true;
			PChar.storekeeper.Idx = sti(NPChar.index);//MAXIMUS
			LaunchStore(GetCurrentStore(NPChar.location));
		break;

		case "second time":
			if(TradeCheck(PChar, NPChar, true))
			{ // NK
				Dialog.snd = pcharrepphrase("voice\PEBL\PEBL002", "voice\PEBL\PEBL003");
				dialog.text = pcharrepphrase(DLG_TEXT[5] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[6], DLG_TEXT[7]);
				Link.l1 = pcharrepphrase(DLG_TEXT[8] + GetMyName(NPChar) + DLG_TEXT[9], DLG_TEXT[10]); 
				link.l1.go = "node_1";
			// NK -->
			}
			else
			{
				dialog.text = DLG_TEXT[23] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[24];
				Link.l1 = DLG_TEXT[25];
				Link.l1.go = "exit";
			}
			// NK <--
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			Dialog.snd = "voice\PEBL\PEBL004";
			dialog.text = DLG_TEXT[11];
			link.l1 = DLG_TEXT[12];
			link.l1.go = "trade";
			link.l2 = DLG_TEXT[13];
			link.l2.go = "quests";
			link.l3 = DLG_TEXT[14];
			link.l3.go = "exit";
		break;

		case "trade":
			Dialog.snd = "voice\PEBL\PEBL005";
			dialog.Text = DLG_TEXT[15];
			Link.l1 = DLG_TEXT[16];
			Link.l1.go = "trade_1";
			Link.l2 = DLG_TEXT[17];
			Link.l2.go = "items";
			Link.l3 = DLG_TEXT[18];
			Link.l3.go = "exit";
		break;

		case "trade_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.storekeeper.Idx = sti(NPChar.index);//MAXIMUS
			LaunchStore(GetCurrentStore(NPChar.location));
		break;

		case "items":
			if (!CheckAttribute(npchar, "quest.item_date") || npchar.quest.item_date != lastspeak_date) // KK
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;

		case "quests":
			iTest = 0;
			Dialog.snd = "voice\PEBL\PEBL006";
			Dialog.text = DLG_TEXT[19];
			if (CheckAttribute(pchar, "quest.generate_trade_quest_progress.iQuantityGoods"))	// LDH was quest.quest.generate, fixed 01Jan09
			{
				int iQuantityShipGoods = sti(pchar.quest.generate_trade_quest_progress.iQuantityGoods);
				int iQuestTradeGoods = sti(pchar.quest.generate_trade_quest_progress.iTradeGoods);
			}
			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
			{
				if (pchar.quest.generate_trade_quest_progress.iTradeColony == GetCurrentTownID() && CheckAttribute(PChar, "quest.generate_trade_quest_progress.iTradeExp"))
				{
					link.l1 = DLG_TEXT[26];
					if (GetSquadronGoods(pchar, iQuestTradeGoods) >= iQuantityShipGoods)
					{
						link.l1.go = "generate_quest_2";
					}
					else
					{
						link.l1.go = "cargo_missing";
					}
				}
			}
			else
			{
				if (!CheckQuestAttribute("generate_trade_quest_progress", "begin"))
				{
					link.l1 = DLG_TEXT[27];
					link.l1.go = "generate_quest";
				}
			}
			link.l99 = DLG_TEXT[28];
			Link.l99.go = "exit";
		break;

		case "generate_quest":
			if(!CheckAttribute(npchar,"quest.trade_date")) npchar.quest.trade_date = ""; // added by MAXIMUS
			if(npchar.quest.trade_date != lastspeak_date)
			{
				npchar.quest.trade_date = lastspeak_date;
				//�������� ������������ ��� ������ ��������
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY) // KK
				{
					Preprocessor_Add("nation_desc", GetNationDescByType(sti(NPChar.nation)));
					dialog.snd = "Voice\EMRI\EMRI007";
					dialog.text = DLG_TEXT[29];
					link.l1 = DLG_TEXT[30];
					link.l1.go = "exit";
				}
				else
				{
					int iTradeNation = GenerateNationTrade(sti(NPChar.nation)); // KK
					if (iTradeNation < 0)
					{
						dialog.snd = "Voice\EMRI\EMRI008";
						dialog.text = DLG_TEXT[31];
						link.l1 = DLG_TEXT[32];
						link.l1.go = "exit";
					}
					else
					{
						//��������� ������/�������
						float fprice, tprice;
						// NK redo this to take price into account 05-05-12 -->
						int iTradeGoods = GenerateGoodForTrade(sti(NPChar.nation), iTradeNation, &fprice, &tprice); // KK
						string sNation = GenerateTradeQuest(pchar, iTradeNation, iTradeGoods, fprice, tprice, true);// MAXIMUS: all was moved into MAXIMUS_Functions.c - returns translated string
						//��������� ��������� ����� ��� ���� ������ ��������� �� ������� ���� 100 ������ ���������� �����
						if (GetSquadronFreeSpace(pchar, iTradeGoods) < 100 || sNation=="")
						{
							dialog.snd = "Voice\EMRI\EMRI009";
							dialog.text = DLG_TEXT[33];
							link.l1 = DLG_TEXT[34];
							link.l1.go = "exit";
						}
						else
						{
							dialog.snd = "Voice\EMRI\EMRI010";
							dialog.text = DLG_TEXT[35] + sNation + DLG_TEXT[36] + pchar.quest.generate_trade_quest_progress.iMoney + DLG_TEXT[37];
							link.l1 = XI_ConvertString("quest_map");
							link.l1.go = "exit_map";
							link.l2 = DLG_TEXT[38];
							link.l2.go = "exit_trade";
							link.l3  = DLG_TEXT[39];
							link.l3.go = "exit";
						}
					}
				}
			}
			else
			{
				dialog.snd = "Voice\EMRI\EMRI011";
				dialog.text = DLG_TEXT[40];
				link.l1 = DLG_TEXT[41];
				link.l1.go = "exit";
			}
		break;

		case "exit_map":
			NextDiag.CurrentNode = "after_map";
			DialogExit();
			LaunchPelagoMap();
		break

		case "after_map":
			dialog.snd = "Voice\EMRI\EMRI010";
			dialog.text = XI_ConvertString("quest_talk")+" "+GetMyName(PChar)+"?";
			link.l1 = DLG_TEXT[38];
			link.l1.go = "exit_trade";
			link.l2 = XI_ConvertString("quest_map");
			link.l2.go = "exit_map";
			link.l3  = DLG_TEXT[39];
			link.l3.go = "exit";
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.snd = "Voice\EMRI\EMRI012";
				dialog.text = DLG_TEXT[42];
				link.l1 = DLG_TEXT[43];
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -1);
				// PB: Enable Future Ones -->
				RemoveCharacterGoods(PChar, makeint(PChar.quest.generate_trade_quest_progress.iTradeGoods), makeint(PChar.quest.generate_trade_quest_progress.iQuantityGoods));
				DeleteAttribute(pchar,"quest.generate_trade_quest_progress");
				// PB: Enable Future Ones <--
			}
			else
			{
				dialog.snd = "Voice\EMRI\EMRI013";
				dialog.text = DLG_TEXT[44] + GetMyAddressForm(NPChar, PChar, ADDR_GENDER, false, false) + ".";
				link.l1 = DLG_TEXT[45];
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 1);
				TradeQuestDone();
			}
			AddDialogExitQuest("close_trade_quest");
		break;

		case "cargo_missing":
			AddQuestRecord("trade", 3);
			Preprocessor_Add("quantity", sti(pchar.quest.generate_trade_quest_progress.iQuantityGoods));
			Preprocessor_Add("cargo", XI_ConvertString(Goods[sti(pchar.quest.generate_trade_quest_progress.iTradeGoods)].name));
			dialog.snd = "Voice\EMRI\EMRI013";
			dialog.text = DLG_TEXT[49];
			link.l1 = DLG_TEXT[50];
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
