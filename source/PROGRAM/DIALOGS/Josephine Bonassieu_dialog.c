//#include "DIALOGS\Josephine Bonassieu_dialog.h"

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int NPC_Meeting;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();

	
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			
			dialog.snd = "Voice\FADU\FADU001";
			dialog.text = DLG_TEXT[0] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[1];
			link.l1 = DLG_TEXT[2];
			link.l1.go = "node_2";
			NextDiag.TempNode = "second time";
		break;

		case "node_2":
			dialog.snd = "Voice\FADU\FADU002";
			dialog.text = DLG_TEXT[3];
			link.l1 = pcharrepphrase(DLG_TEXT[4], DLG_TEXT[5]);
			link.l1.go = "second time";
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
			
			dialog.snd = "Voice\FADU\FADU003";
			dialog.text = DLG_TEXT[6];
			link.l1 = pcharrepphrase(DLG_TEXT[7], DLG_TEXT[8]);
			link.l1.go = "crew";
			link.l2 = DLG_TEXT[9];
			link.l2.go = "rumours";
			Link.l3 = pcharrepphrase(DLG_TEXT[10], DLG_TEXT[11]);
			Link.l3.go = "room";
			link.l99 = DLG_TEXT[12];
			link.l99.go = "exit";
		break;

		case "rumours":
			dialog.snd = "Voice\FADU\FADU004";
			dialog.text = DLG_TEXT[13] + GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false) + DLG_TEXT[14];
			link.l99 = DLG_TEXT[16];
			if (PChar.quest.Bonnie_talk == "Sailing_for_Turks")
			{
				link.l1 = DLG_TEXT[41];
				link.l1.go = "Where_to_go";
			}
			link.l99.go = "second time";
		break;

		case "room":
			dialog.snd = "Voice\FADU\FADU005";
			dialog.text = DLG_TEXT[17];
			string roomWait = "";
			if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
			{
				roomWait = "eveningwait";
				link.l1 = DLG_TEXT[18];
				link.l1.go = "room_day";
			}
			else
			{
				roomWait = "daywait";
				link.l1 = DLG_TEXT[19];
				link.l1.go = "room_night";
			}
			link.l2 = XI_ConvertString("Until tomorrow") + " " + XI_ConvertString(roomWait) + ".";
			link.l2.go = "room_24";
		break;

		case "room_24":
			dialog.snd = "Voice\ANLE\ANLE014";
			Dialog.text = DLG_TEXT[20];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[21];
				link.l1.go = "room_24_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[22], DLG_TEXT[23]);
			link.l2.go = "hall_24_wait";
			link.l3 = DLG_TEXT[24];
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
			dialog.snd = "Voice\FADU\FADU006";
			Dialog.text = DLG_TEXT[20];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[21];
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[22], DLG_TEXT[23]);
			link.l2.go = "hall_day_wait";
			link.l3 = DLG_TEXT[24];
			link.l3.go = "second time";
		break;

		case "room_night":
			dialog.snd = "Voice\FADU\FADU007";
			Dialog.text = DLG_TEXT[25];
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = DLG_TEXT[26];
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase(DLG_TEXT[27], DLG_TEXT[28]);
			link.l2.go = "hall_night_wait";
			link.l3 = DLG_TEXT[29];
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

		case "crew":
			if (makeint(environment.time) <= 22.0 && makeint(environment.time) >= 10.0)
			{
				DialogExit();
				NextDiag.CurrentNode =  NextDiag.TempNode;
				launchhirecrew();
			}
			else
			{
				dialog.snd = "Voice\FADU\FADU008";
				dialog.text = DLG_TEXT[30];
				link.l1 = DLG_TEXT[31];
				link.l1.go = "room";
				link.l2 = DLG_TEXT[32];
				link.l2.go = "second time";
			}
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
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

			dialog.snd = "Voice\FADU\FADU009";
			dialog.text = DLG_TEXT[33];
			link.l1 = DLG_TEXT[34];
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		// A French Companion -->
		case "begin_1":
			dialog.snd = "Voice\CLLA\CLLA005";
			dialog.text = DLG_TEXT[35];
			link.l1 = DLG_TEXT[36];
			link.l1.go = "begin_2";		
			break;
			
		case "begin_2":
			dialog.snd = "Voice\CLLA\CLLA005";
			dialog.text = DLG_TEXT[37];
			link.l1 = DLG_TEXT[38];
			link.l1.go = "begin_3";
			break;

		case "begin_3":
			dialog.snd = "Voice\CLLA\CLLA005";
			dialog.text = DLG_TEXT[39];
			link.l1 = DLG_TEXT[40];
			link.l1.go = "exit";
			AddDialogExitQuest("Talks_Laura_Cotton");			
			break;
		// <-- A French Companion

		// Devlin Opera -->
		case "Where_to_go":
			DisableFastTravel(true);
			ChangeCharacterAddressGroup(characterfromID("Merciless Mark"),"Turks_townhall", "sit", "sit6");
			LAi_SetSitType(characterfromID("Merciless Mark"));
			ChangeCharacterAddressGroup(characterfromID("Robert Cook"),"Turks_townhall", "sit", "sit4");
			LAi_SetSitType(characterfromID("Robert Cook"));
			ChangeCharacterAddressGroup(characterfromID("Couch Captain Charles"),"Turks_townhall", "sit", "sit5");
			LAi_SetSitType(characterfromID("Couch Captain Charles"));
			ChangeCharacterAddressGroup(characterfromID("Maximus"),"Turks_townhall", "sit", "sit3");
			LAi_SetSitType(characterfromID("Maximus"));
			ChangeCharacterAddressGroup(characterfromID("Sir Christopher Mings"),"Turks_townhall", "sit", "sit7");
			LAi_SetSitType(characterfromID("Sir Christopher Mings"));
			ChangeCharacterAddressGroup(characterfromID("Nathan Kell"),"Turks_townhall", "goto", "goto6");
			ChangeCharacterAddressGroup(characterfromID("Thomas the Terror"),"Turks_townhall", "goto", "goto4");
			ChangeCharacterAddressGroup(characterfromID("Petros"),"Turks_townhall", "goto", "goto5");
			ChangeCharacterAddressGroup(characterfromID("Catalina the Pirate"),"Turks_townhall", "goto", "goto1");
			ChangeCharacterAddressGroup(characterfromID("Morgan Terror"),"Turks_port", "goto", "T3_citizen03"); // JRH: new Turks
			pchar.quest.Morgan_talk = "Approach_Residence";
			Pchar.quest.to_find_Short_Jack_Gold2.win_condition.l1 = "location";
			PChar.quest.to_find_Short_Jack_Gold2.win_condition.l1.character = Pchar.id;
			Pchar.quest.to_find_Short_Jack_Gold2.win_condition.l1.location = "Turks_townhall";
			Pchar.quest.to_find_Short_Jack_Gold2.win_condition = "to_find_Short_Jack_Gold2";
			dialog.text = DLG_TEXT[42];
			link.l99 = DLG_TEXT[43];
			link.l99.go = "Exit";
		break;
		// <-- Devlin Opera	
	}
}
