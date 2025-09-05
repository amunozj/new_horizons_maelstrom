//#include "DIALOGS\Tia Dalma_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
	aref Link, Diag;
	string NPC_meeting;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);


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
			Dialog.snd = "voice\THDI\THDI001";

			Dialog.mood = "normal";

			d.text = DLG_TEXT[59];
			link.l1 = DLG_TEXT[60];
			link.l1.go = "exit";

			if(GetAttribute(pchar, "quest.Tia_Dalma") == "start")
			{
				d.text = DLG_TEXT[0] + GetMyFullName(PChar) + DLG_TEXT[1];
				link.l1 = DLG_TEXT[2];
				link.l1.go = "speak1";
			}
		break;

		case "speak1":
			dialog.text = DLG_TEXT[3] + pchar.lastname + DLG_TEXT[4];
			link.l1 = DLG_TEXT[5];
			link.l1.go = "speak2";
		break;

		case "speak2":
			dialog.text = DLG_TEXT[6];
			link.l1 = DLG_TEXT[7];
			link.l1.go = "speak3";
		break;

		case "speak3":
			dialog.text = DLG_TEXT[8];
			link.l1 = DLG_TEXT[9];
			link.l1.go = "speak4";
		break;

		case "speak4":
			dialog.text = DLG_TEXT[10];
			link.l1 = DLG_TEXT[11];
			link.l1.go = "speak5";
		break;

		case "speak5":
			dialog.text = DLG_TEXT[12];
			link.l1 = DLG_TEXT[13];
			link.l1.go = "speak6";
		break;

		case "speak6":
			dialog.text = DLG_TEXT[14];
			link.l1 = DLG_TEXT[15];
			link.l1.go = "speak7";
		break;

		case "speak7":
			dialog.text = DLG_TEXT[16];
			link.l1 = DLG_TEXT[17];
			link.l1.go = "speak8";
		break;

		case "speak8":
			dialog.text = DLG_TEXT[18];
			link.l1 = DLG_TEXT[19];
			link.l1.go = "speak10";
		break;

		case "speak10":
			dialog.text = DLG_TEXT[20];
			link.l1 = DLG_TEXT[21];
			link.l1.go = "speak11";
		break;

		case "speak11":
			dialog.text = DLG_TEXT[22];
			link.l1 = DLG_TEXT[23];
			link.l1.go = "exitfirst";
		break;

		case "exitfirst":
			LAi_ActorAttack(CharacterFromID("Pirates_1"), PChar, "");
			LAi_ActorAttack(CharacterFromID("Pirates_2"), PChar, "");
			LAi_ActorAttack(CharacterFromID("Pirates_3"), PChar, "");
			AddDialogExitQuest("go_to_fight_Slave_Traders");
			DialogExit();
			pchar.quest.Tia_Dalma = "done";
			Diag.CurrentNode = "speaktoTiaagain";
		break;

		case "speaktoTiaagain":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "voice\THDI\THDI001";

			dialog.text = DLG_TEXT[24];
			link.l1 = DLG_TEXT[25];
			link.l1.go = "speakagain";
		break;

		case "speakagain":
			dialog.text = DLG_TEXT[26] + pchar.lastname + DLG_TEXT[27];
			link.l1 = DLG_TEXT[28];
			link.l1.go = "speakagain2";
		break;

		case "speakagain2":
			dialog.text = DLG_TEXT[29];
			link.l1 = DLG_TEXT[30];
			link.l1.go = "speakagain3";
		break;

		case "speakagain3":
			if (CheckQuestAttribute("Jacks_early_days", "Mings_First_run_Beckett"))
			{
			dialog.text = DLG_TEXT[43];
			link.l1 = DLG_TEXT[44];
			link.l1.go = "speakagainforMings";
			}else{
			dialog.text = DLG_TEXT[31];
			link.l1 = DLG_TEXT[32];
			link.l1.go = "speakagain4";
			}
		break;

		case "speakagain4":
			dialog.text = DLG_TEXT[33];
			link.l1 = DLG_TEXT[34];
			link.l1.go = "speakagain5";
		break;

		case "speakagain5":
			dialog.text = DLG_TEXT[35];
			link.l1 = DLG_TEXT[36];
			link.l1.go = "speakagain6";
		break;

		case "speakagain6":
			AddQuestRecord("Beckett",14);
			AddMoneyToCharacter(pchar, -500);
			dialog.text = DLG_TEXT[37];
			link.l1 = DLG_TEXT[38];
			link.l1.go = "speakagain7";
		break;

		case "speakagain7":
			GiveModel2Player("depp", true);
			GiveItem2Character(Pchar,"aztec_compass");
			pchar.compass = "1";
			dialog.text = DLG_TEXT[39];
			link.l1 = DLG_TEXT[40];
			link.l1.go = "speakagain8";
		break;

		case "speakagain8":
			dialog.text = DLG_TEXT[41];
			link.l1 = DLG_TEXT[42];
			if (CheckQuestAttribute("Jacks_early_days", "Mings_First_run_Beckett"))
			{
			link.l1.go = "exit3";
			}else{
			link.l1.go = "exit2";
			}
			if (GetAttribute(pchar, "compass") == "1" && GetAttribute(pchar, "map") == "1")
			{
				AddQuestRecord("Aztec", 4);
			}
		break;

		case "speakagainforMings":
			AddQuestRecord("Beckett",15);
			AddMoneyToCharacter(pchar, -500);
			dialog.text = DLG_TEXT[45];
			link.l1 = DLG_TEXT[46];
			link.l1.go = "speakagain7";
		break;

		case "Failed task Mings":
			dialog.text = DLG_TEXT[47];
			link.l1 = DLG_TEXT[48];
			link.l1.go = "Failed task Mings2";
		break;

		case "Failed task Mings2":
			dialog.text = DLG_TEXT[49];
			link.l1 = DLG_TEXT[50];
			link.l1.go = "Failed task Mings3";
			link.l2 = DLG_TEXT[51];
			link.l2.go = "Exit_No_Compass";
		break;

		case "Failed task Mings3":
			dialog.text = DLG_TEXT[52];
			link.l1 = DLG_TEXT[30];
			link.l1.go = "Failed task Mings4";
			GiveModel2Player("depp", true);
			GiveItem2Character(Pchar,"aztec_compass");
			pchar.compass = "1";
			GiveItem2Character(Pchar,"albatross");
		break;

		case "Failed task Mings4":
			dialog.text = DLG_TEXT[53];
			link.l1 = DLG_TEXT[54];
			link.l1.go = "Failed task Mings5";
			pchar.money = 0;
			if (GetAttribute(pchar, "compass") == "1" && GetAttribute(pchar, "map") == "1")
			{
				AddQuestRecord("Aztec", 4);
			}
			AddQuestRecord("The Brotherhood",12);
		break;

		case "Failed task Mings5":
			dialog.text = DLG_TEXT[55];
			link.l1 = DLG_TEXT[56];
			link.l1.go = "Exit3";
		break;

		case "Tia_Talk_to_Davy_early":
			dialog.text = DLG_TEXT[57];
			link.l1 = DLG_TEXT[58];
			link.l1.go = "Exit";
			addDialogExitQuest("Tia_to_Davy_early2");
		break;

		case "Tia_Talk_to_Davy_DMC":
			dialog.text = DLG_TEXT[61];
			link.l1 = DLG_TEXT[62];
			link.l1.go = "Exit";
			addDialogExitQuest("Tia_to_Davy_DMC2");
		break;

		case "Take_Tia_to_Shack":
			dialog.text = DLG_TEXT[63];
			link.l1 = DLG_TEXT[64];
			link.l1.go = "Exit";

			addDialogExitQuest("reload_to_sea_after_davy");
			AddQuestRecord("Contact", 14);

			/*PChar.quest.at_Shack_Warning.win_condition.l1 = "location";
			PChar.quest.at_Shack_Warning.win_condition.l1.location = "Tia_shack";
			PChar.quest.at_Shack_Warning.win_condition = "at_Shack_Warning";*/
		break;
		
		//DMC Quest 
		case "Arrived_to_antigua_talk":
			dialog.text = DLG_TEXT[65];
			link.l1 = DLG_TEXT[66];
			link.l1.go = "Exit";

			addDialogExitQuest("Swamp_near_shack");
			//AddQuestRecord("Dead mans chest", 4);
  
		break;
		
		case "to_the_shack":
			dialog.text = DLG_TEXT[67];
			link.l1 = DLG_TEXT[68];
			link.l1.go = "Exit";

			addDialogExitQuest("To_shack_follow");
  
		break;
		//Explain what do DMC
		case "find_the_key":
			dialog.text = DLG_TEXT[69];
			link.l1 = DLG_TEXT[70];
			link.l1.go = "find_the_key2";
  
		break;
		
		//Explain what do DMC
		case "find_the_key2":
			dialog.text = DLG_TEXT[71];
			link.l1 = DLG_TEXT[72];
			link.l1.go = "find_the_key3";
  
		break;
		
		//Explain what do DMC
		case "find_the_key3":
			dialog.text = DLG_TEXT[73];
			link.l1 = DLG_TEXT[74];
			link.l1.go = "Exit";
			AddDialogExitQuest("shack_open1");
  
		break;
		
		//Explain what do DMC2
		case "find_the_key4":
			Logit("find_the_key4");
			dialog.text = DLG_TEXT[75];
			link.l1 = DLG_TEXT[76];
			link.l1.go = "find_the_key5";
		break;
		
		//Explain what do DMC2
		case "find_the_key5":
			Logit("find_the_key5");
			dialog.text = DLG_TEXT[77];
			link.l1.go = "Exit";
			AddDialogExitQuest("At_Shack_Warning2_3");
		break;
		
		//Explain what do DMC2
		case "find_the_key6":
			Logit("find_the_key6");
			dialog.text = DLG_TEXT[78];
			link.l1 = DLG_TEXT[79];
			link.l1.go = "find_the_key7";
		break;
		
		//Explain what do DMC2
		case "find_the_key7": 
			Logit("find_the_key7");
			dialog.text = DLG_TEXT[80];
			link.l1 = DLG_TEXT[81];
			link.l1.go = "Exit";
			link.l1.go = "find_the_key7_2";
		break;
		
		//Explain what do DMC2
		case "find_the_key7_2": 
			Logit("find_the_key7_2");
			dialog.text = DLG_TEXT[82];
			link.l1 = DLG_TEXT[83];
			link.l1.go = "Exit";
			AddDialogExitQuest("At_Shack_Warning2_5");
		break;
		
		
		//Explain what do DMC2
		case "find_the_key8": 
			dialog.text = DLG_TEXT[84];
			link.l1.go = "Exit";
			AddDialogExitQuest("At_Shack_Warning2_7");
		break;
		
		//Explain what do DMC2
		case "find_the_key9": 
			dialog.text = DLG_TEXT[85];
			link.l1 = DLG_TEXT[86];
			link.l1.go = "find_the_key9_1";
		break;
		
		//Explain what do DMC2
		case "find_the_key9_1": 
			dialog.text = DLG_TEXT[87];
			link.l1.go = "Exit";
			AddDialogExitQuest("At_Shack_Warning2_10");
		break;
		
		//Explain what do DMC2
		case "find_the_key10": 
			dialog.text = DLG_TEXT[88];
			link.l1.go = "find_the_key10_1";	
		break;
		
		//Explain what do DMC2
		case "find_the_key10_1": 
			dialog.text = DLG_TEXT[89];
			link.l1.go = "Exit";	
			AddDialogExitQuest("At_Shack_Warning2_12");
		break;
		
		//Explain what do DMC2
		case "find_the_key11": 
			dialog.text = DLG_TEXT[90];
			link.l1.go = "Exit";	
			AddDialogExitQuest("Video_to_shipwreck");
		break;
		
		case "Exit":
			DialogExit();
			Diag.CurrentNode = "First time";
		break;

		case "Exit_No_Compass":
			AddQuestRecord("The Brotherhood",13);
			AddDialogExitQuest("Back to Mings from Antigua");
			DisableFastTravel(false);
			DialogExit();
			Diag.CurrentNode = "First time";
		break;

		case "Exit2":
			AddDialogExitQuest("Goodbye Tia Dalma");
			DialogExit();
			Diag.CurrentNode = "First time";
		break;

		case "Exit3":
			AddQuestRecord("Beckett",15);
			pchar.quest.Jacks_early_days = "Got_the_Magic_Compass";
			AddDialogExitQuest("Back to Mings from Antigua");
			DialogExit();
			Diag.CurrentNode = "First time";
		break;
	}
}
