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

	switch(Dialog.CurrentNode)
	{
		//-----------------------------------������ ������ - ������ �������
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			
			dialog.snd = "Voice\CLBU\CLBU001";
			Dialog.Text = DLG_TEXT[0] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[1];
			Link.l1 = pcharrepphrase(DLG_TEXT[2] + GetMyFullName(PChar) + DLG_TEXT[3], DLG_TEXT[4] + GetMyFullName(PChar) + DLG_TEXT[5]);
			Link.l1.go = "node_1"; 
			NextDiag.TempNode = "second time";
		break;

		case "second time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";

			dialog.snd1 = "Voice\CLBU\CLBU002";
			dialog.snd2 = "Voice\CLBU\CLBU003";
			dialog.snd3 = "Voice\CLBU\CLBU004";
			dialog.text = randphrase(DLG_TEXT[6], DLG_TEXT[7] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[8], DLG_TEXT[9], &dialog, dialog.snd1, dialog.snd2, dialog.snd3);
			link.l1 = pcharrepphrase(DLG_TEXT[10], DLG_TEXT[11]);
			link.l1.go = "node_1";
			link.l2 = pcharrepphrase(DLG_TEXT[12], DLG_TEXT[13]);
			link.l2.go = "exit";
		break;

		case "node_1":
			if (npchar.quest.meeting == "0")
			{
				dialog.snd = "Voice\CLBU\CLBU005";
				dialog.text = DLG_TEXT[14] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[15] + GetMyFullName(NPChar) + DLG_TEXT[16];
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.snd = "Voice\CLBU\CLBU006";
				dialog.text = DLG_TEXT[17] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[18];
			}
			link.l1 = pcharrepphrase(DLG_TEXT[19], DLG_TEXT[20]);
			link.l1.go = "crew";
			link.l2 = DLG_TEXT[21];
			link.l2.go = "quests";
			link.l3 = pcharrepphrase(DLG_TEXT[22], DLG_TEXT[23]);
			link.l3.go = "room";
			link.l99 = pcharrepphrase(DLG_TEXT[24], DLG_TEXT[25]);
			link.l99.go = "exit";
		break;
		
		case "quests":
			iTest = 0;
			dialog.snd = "Voice\CLBU\CLBU007";
			dialog.text = DLG_TEXT[26];
			if (checkQuestAttribute("mayan_temple", "find_guide"))
			{
				link.l9 = DLG_TEXT[57];
				link.l9.go = "temple_guide";
			}
			if (CheckQuestAttribute("OPERA", "ask_Ramos_for_Jauri"))
			{
				link.l1 = DLG_TEXT[60];
				link.l1.go = "Jauri1";
			}
			if (!CheckQuestAttribute("generate_convoy_quest_progress", "begin") && npchar.work != lastspeak_date)
			{
				link.l10 = DLG_TEXT[27];
				link.l10.go = "convoy";
			}
			link.l99 = DLG_TEXT[28];
			link.l99.go = "node_1";
		break;
		
		case "crew":
			if (makeint(environment.time) > 22.0 || makeint(environment.time) < 10.0)
			{
				dialog.snd = "Voice\CLBU\CLBU022";
				Dialog.text = DLG_TEXT[29];
				link.l1 = DLG_TEXT[30];
				link.l1.go = "room";
				link.l2 = DLG_TEXT[31];
				link.l2.go = "quests";
			}
			else
			{
				Dialog.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchHireCrew();
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
			dialog.snd = "Voice\CLBU\CLBU023";
			dialog.text = DLG_TEXT[32];
			string roomWait = "";
			if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
			{
				roomWait = "eveningwait";
				link.l1 = DLG_TEXT[33];
				link.l1.go = "room_day";
			}
			else
			{
				roomWait = "daywait";
				link.l1 = DLG_TEXT[34];
				link.l1.go = "room_night";
			}
			link.l2 = XI_ConvertString("Until tomorrow") + " " + XI_ConvertString(roomWait) + ".";
			link.l2.go = "room_24";
		break;

		case "room_24":
			dialog.snd = "Voice\ANLE\ANLE014";
			Dialog.text = DLG_TEXT[35];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[36];
				link.l1.go = "room_24_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[37], DLG_TEXT[38]);
			link.l2.go = "hall_24_wait";
			link.l3 = DLG_TEXT[39];
			link.l3.go = "second time";
		break;

		case "room_24_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			PlayStereoSound("INTERFACE\took_item.wav");
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			WaitDate("",0,0,0,24,1);
			RecalculateJumpTable();
		break;

		case "hall_24_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			LAi_Fade("", "");
			WaitDate("",0,0,0,24,1);
			RecalculateJumpTable();
		break;

		case "room_day":
			dialog.snd = "Voice\CLBU\CLBU024";
			Dialog.text = DLG_TEXT[35];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[36];
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[37], DLG_TEXT[38]);
			link.l2.go = "hall_day_wait";
			link.l3 = DLG_TEXT[39];
			link.l3.go = "second time";
		break;

		case "room_night":
			dialog.snd = "Voice\CLBU\CLBU025";
			Dialog.text = DLG_TEXT[40];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[41];
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[42], DLG_TEXT[43]);
			link.l2.go = "hall_night_wait";
			link.l3 = DLG_TEXT[44];
			link.l3.go = "second time";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			PlayStereoSound("INTERFACE\took_item.wav");
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate2("wait_night");
		break;

		case "hall_night_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			PlayStereoSound("INTERFACE\took_item.wav");
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate2("wait_day");
		break;

		case "hall_day_wait":
			DialogExit();
			NextDiag.CurrentNode =  NextDiag.TempNode;
			TavernWaitDate("wait_day");
		break;

		case "tavern_keeper":
			NextDiag.TempNode = "second time";
			
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			
			dialog.snd = "Voice\CLBU\CLBU026";
			dialog.text = DLG_TEXT[45];
			link.l1 = DLG_TEXT[46];
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		case "convoy":
			npchar.work = lastspeak_date;
			if (GetCompanionIndex(pchar,1) != -1 && GetCompanionIndex(pchar,2) != -1 && GetCompanionIndex(pchar,3) != -1)
			{
				dialog.text = DLG_TEXT[47];
				link.l1 = DLG_TEXT[48];
				link.l1.go = "exit";
			}
			else
			{
				if (GetNationRelation2MainCharacter(GetCurrentLocationNation()) == RELATION_ENEMY) // KK
				{
					dialog.text = DLG_TEXT[49];
					link.l1 = DLG_TEXT[50];
					link.l1.go = "exit";
				}
				else
				{
					if (makeint(pchar.reputation) <25)
					{
						dialog.text = DLG_TEXT[51];
						link.l1 = DLG_TEXT[52];
						link.l1.go = "exit";
					}
					else
					{
						int randomGod = rand(1);
						if (randomGod == 1)
						{
							dialog.text = DLG_TEXT[53];
							link.l1 = DLG_TEXT[54];
							link.l1.go = "exit";
							AddDialogExitQuest("prepare_for_convoy_quest");
							
						}
						else
						{
							dialog.text = DLG_TEXT[55];
							link.l1 = DLG_TEXT[56];
							link.l1.go = "exit";
						}
					}
				}
			}
		break;

		case "temple_guide":
			dialog.text = DLG_TEXT[58];
			link.l1 = DLG_TEXT[59];
			link.l1.go = "Exit";
		break;

		case "Jauri1":
			dialog.text = DLG_TEXT[61];
			link.l1 = DLG_TEXT[62];
			link.l1.go = "Exit";
			AddDialogExitQuest("enter_the_kid");
		break;
	}
}
