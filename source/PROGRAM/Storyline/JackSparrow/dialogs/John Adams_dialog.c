//#include "DIALOGS\John Adams_dialog.h"

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
			if (CheckQuestAttribute("Jackpot", "search"))
			{
				link.l1 = DLG_TEXT[35];
				if (IsBrothelEnabled()) 
				{
					link.l1.go = "gov_2";
				}
				else
				{
					link.l1.go = "gov_1";
				}
			}
			if (CheckQuestAttribute("Jacks_early_days", "arrival_at_Tortuga"))
			{
				link.l1 = DLG_TEXT[40];
				link.l1.go = "some_advice";
			}
			link.l99 = DLG_TEXT[16];
			link.l99.go = "second time";
		break;

		case "some_advice":
			dialog.snd = "Voice\REGR\REGR008";
			dialog.text = DLG_TEXT[41];
			link.l1 = DLG_TEXT[42];
			link.l1.go = "some_advice2";
		break;		

		case "some_advice2":
			dialog.snd = "Voice\REGR\REGR008";
			dialog.text = DLG_TEXT[43];
			link.l1 = DLG_TEXT[44];
			link.l1.go = "Exit_some_advice";
		break;
		
		case "room":
			dialog.snd = "Voice\FADU\FADU005";
			if(CheckAttribute(pchar,"jack"))
			{
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
			}
			else
			{
				dialog.text = DLG_TEXT[45];
				link.l1 = DLG_TEXT[46];
				link.l1.go = "exit";
				AddDialogExitQuest("opening_1");
			}
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

		case "Exit_some_advice":
			pchar.quest.Jacks_early_days = "News_at_Tortuga";		
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Brinkley_left_Tortuga");			
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

		case "gov_1":
			dialog.snd = "Voice\REGR\REGR008";
			dialog.text = DLG_TEXT[36];
			link.l1 = DLG_TEXT[37];
			link.l1.go = "exit";
			AddQuestRecord("Chevalle", 14);
		break;

		case "gov_2":
			dialog.snd = "Voice\REGR\REGR008";
			dialog.text = DLG_TEXT[38];
			link.l1 = DLG_TEXT[39];
			link.l1.go = "exit";
			AddQuestRecord("Chevalle", 12);
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
	}
}
