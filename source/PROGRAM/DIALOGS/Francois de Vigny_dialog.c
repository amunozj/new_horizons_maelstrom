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

	ref PChar;
	PChar = GetMainCharacter();

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------|����� ������ - ������ �������
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			if(TradeCheck(PChar, NPChar, true)) { // NK

			if (npchar.quest.meeting == "0")
			{
				dialog.snd = "Voice\EMRI\EMRI001";
				Dialog.Text = DLG_TEXT[0] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[1] + GetMyFullName(NPChar) + DLG_TEXT[2];
				Link.l1 = pcharrepphrase(DLG_TEXT[3] + GetMyFullName(PChar) + DLG_TEXT[4], DLG_TEXT[5] + GetMyFullName(PChar) + DLG_TEXT[6]);
				link.l1.go = "node_3";
			}
			else
			{
				dialog.snd = "Voice\EMRI\EMRI002";
				dialog.text = DLG_TEXT[7] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[8];
				Link.l1 = pcharrepphrase(DLG_TEXT[9], DLG_TEXT[10]); 
				link.l1.go = "node_3";
			}
			// NK -->
			}
			else
			{
				dialog.text = DLG_TEXT[47] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[48];
				Link.l1 = DLG_TEXT[49];
				Link.l1.go = "exit";
			}
			// NK <--
			NextDiag.TempNode = "First time";
		break;

		case "node_3":
			dialog.snd = "Voice\EMRI\EMRI003";
			dialog.text = DLG_TEXT[11];
			if(TradeCheck(PChar, NPChar, false)) {
			link.l1 = pcharrepphrase(DLG_TEXT[12], DLG_TEXT[13]);
			link.l1.go = "market"; }
			link.l2 = pcharrepphrase(DLG_TEXT[14], DLG_TEXT[15]);
			link.l2.go = "quests";
			link.l3 = pcharrepphrase(DLG_TEXT[16], DLG_TEXT[17]);
			link.l3.go = "exit";
		break;

		case "market":
			dialog.snd = "Voice\EMRI\EMRI004";
			dialog.Text = DLG_TEXT[18];
			Link.l1 = DLG_TEXT[19];
			Link.l1.go = "trade_1";
			Link.l2 = DLG_TEXT[20];
			Link.l2.go = "items";
			Link.l3 = DLG_TEXT[21];
			Link.l3.go = "exit";
		break;

		case "trade_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.storekeeper.Idx = sti(NPChar.index);//MAXIMUS
			LaunchStore(MARIGOT_STORE);
		break;

		case "items":
			if (npchar.quest.item_date != lastspeak_date)
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
			dialog.snd = "Voice\EMRI\EMRI005";
			Preprocessor_Add("sir", GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false)); // DeathDaisy
			Dialog.text = DLG_TEXT[22];
			if (CheckAttribute(pchar, "quest.generate_trade_quest_progress.iQuantityGoods"))	// LDH was quest.quest.generate, fixed 01Jan09
			{
				int iQuantityShipGoods = pchar.quest.generate_trade_quest_progress.iQuantityGoods;
				int iQuestTradeGoods = pchar.quest.generate_trade_quest_progress.iTradeGoods;
			}
			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
			{
				if (GetSquadronGoods(pchar, iQuestTradeGoods) >= iQuantityShipGoods && pchar.quest.generate_trade_quest_progress.iTradeColony == GetCurrentTownID() && CheckAttribute(PChar, "quest.generate_trade_quest_progress.iTradeExp"))
				{
					dialog.snd = "Voice\EMRI\EMRI006";
					dialog.text = DLG_TEXT[23];
					link.l1 = DLG_TEXT[24];
					link.l1.go = "generate_quest_2";
				}
			}
			else
			{
				if (!CheckQuestAttribute("generate_trade_quest_progress", "begin"))
				{
					link.l1 = DLG_TEXT[25];
					link.l1.go = "generate_quest";
				}
			}
			link.l99 = DLG_TEXT[26];
			Link.l99.go = "no_quests";
		break;

		case "generate_quest":
			if(!CheckAttribute(npchar,"quest.trade_date")) npchar.quest.trade_date = ""; // added by MAXIMUS
			if(npchar.quest.trade_date != lastspeak_date)
			{
				npchar.quest.trade_date = lastspeak_date;
				//�������� ������������ ��� ������ ��������
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY) // KK
				{
					dialog.snd = "Voice\EMRI\EMRI007";
					dialog.text = DLG_TEXT[27];
					link.l1 = DLG_TEXT[28];
					link.l1.go = "exit";
				}
				else
				{
					int iTradeNation = GenerateNationTrade(sti(NPChar.nation)); // KK
					if (iTradeNation < 0)
					{
						dialog.snd = "Voice\EMRI\EMRI008";
						dialog.text = DLG_TEXT[29];
						link.l1 = DLG_TEXT[30];
						link.l1.go = "exit";
					}
					else
					{
						//��������� ������/�������
						float fprice, tprice;
						// NK redo this to take price into account 05-05-12 -->
						int iTradeGoods = GenerateGoodForTrade(sti(NPChar.nation), iTradeNation, &fprice, &tprice); // KK
						string sNation = GenerateTradeQuest(pchar, iTradeNation, iTradeGoods, fprice, tprice, true);// MAXIMUS: all was moved into MAXIMUS_Functions.c - returns translated string
						//��������� ��������� ����� (��� ���� ������ ��������� �� ������� ���� 100 ������ ���������� �����
						if (GetSquadronFreeSpace(pchar, iTradeGoods) < 100 || sNation=="")
						{
							dialog.snd = "Voice\EMRI\EMRI009";
							dialog.text = DLG_TEXT[31];
							link.l1 = DLG_TEXT[32];
							link.l1.go = "exit";
						}
						else
						{
							dialog.snd = "Voice\EMRI\EMRI010";
							dialog.text = DLG_TEXT[33] + sNation + DLG_TEXT[34] + pchar.quest.generate_trade_quest_progress.iMoney + DLG_TEXT[35];
							link.l1 = XI_ConvertString("quest_map");
							link.l1.go = "exit_map";
							link.l2 = DLG_TEXT[36];
							link.l2.go = "exit_trade";
							link.l3  = DLG_TEXT[37];
							link.l3.go = "exit";
						}
					}
				}
			}
			else
			{
				dialog.snd = "Voice\EMRI\EMRI011";
				dialog.text = DLG_TEXT[38];
				link.l1 = DLG_TEXT[39];
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
			link.l1 = DLG_TEXT[36];
			link.l1.go = "exit_trade";
			link.l2 = XI_ConvertString("quest_map");
			link.l2.go = "exit_map";
			link.l3  = DLG_TEXT[37];
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
				dialog.text = DLG_TEXT[40];
				link.l1 = DLG_TEXT[41];
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
				dialog.text = DLG_TEXT[42] + GetMyAddressForm(NPChar, PChar, ADDR_GENDER, false, false) + ".";
				link.l1 = DLG_TEXT[43];
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 1);
				TradeQuestDone();
			}
			AddDialogExitQuest("close_trade_quest");
		break;
		
		case "no_quests":
			dialog.snd = "Voice\EMRI\EMRI014";
			dialog.text = DLG_TEXT[44];
			link.l1 = pcharrepphrase(DLG_TEXT[45], DLG_TEXT[46]);
			link.l1.go = "node_3";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
