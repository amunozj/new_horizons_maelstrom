//#include "DIALOGS\Juan_Dialog.h"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag; //NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();
	
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode; //"First time";
			DialogExit();
		break;

	
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[1];
			link.l1.go = "number2";
		break;

		case "number2":
			dialog.text = DLG_TEXT[2];
			link.l1 = DLG_TEXT[3];
			link.l1.go = "exit_stillsleepy";
			AddDialogExitQuest("Juan_search_bucket");
		break;

		case "stillsleepy":
			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[3];
			link.l1.go = "exit_stillsleepy";
		break;

		case "exit_stillsleepy":
			Diag.CurrentNode = Diag.TempNode; //"First time";
			DialogExit();

			Characters[GetCharacterIndex("Juan")].Dialog.CurrentNode = "stillsleepy";
		break;

		case "Awaiting_water":
			dialog.text = DLG_TEXT[0];
			link.l1 = DLG_TEXT[4];
			link.l1.go = "exit";
			AddDialogExitQuest("Juan_showertime");
		break;

		case "Finally_awake":
			dialog.text = DLG_TEXT[5];
			link.l1 = DLG_TEXT[6];
			link.l1.go = "Finally_awake2";
		break;

		case "Finally_awake2":
			dialog.text = DLG_TEXT[7];
			link.l1 = DLG_TEXT[8];
			link.l1.go = "exit";
			AddDialogExitQuest("Juan_returns");
		break;
	}
}