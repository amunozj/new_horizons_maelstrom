// ccc Buildingset, new file	
/*
ccc Dec06:
� ������� �� ����������� ������ ������ � ���� �����, ���� �������� �� ������ ��������� ������, �� � ������������ ��� � �����.

��������� ����� ������� ��� �������� �������� ������������ ��� �������� ��������� ���������� ���������� �����. 
������ ����, ����� ������� ������ �� ����������� � ������������ ����� ������, � ����������� �������� �����.. 
������ ������ ����������� �������� ������� ��������� PotC. : 
��� �������� �������� �����  "x-dialog.c" ��������� ������ ������������� �������� ���� ���������� ������� "x-dialog.h"  �� �������� dialogs\english (��� �� ����� Russian, ���� �� ����������� ���� ����). 
��� ���������� ����� ������ ����.

������ � ����������� ����� ��� � ������� ����� � ����� ����� �� ���� ��������:
-������ ������� �����
-� ��� ������� ������ ����� � �������������� ��������
-���������� � �����, ������� ������ �� �������� ���, ������� ����� ������ � �������� ����.
��������� ����� �������� ����� ��� ����, ������ ��� �� ������ ���� ������������ ��� �����, ������� ����� ������ ���������� ���������.
��� ������ � ������������� �������� ���������� ������ "��� ���� ���������� �����".

� �������� ������� ������� ����������� � �������� ��� ����� �� � �������� ����� \dialogs, � � �������� \dialogs\English.
�������, ���� �� ������ ��������� ���� ������, �� ������ ������ ����������� "��� ���� ���������� �����" � �������� ��� ������ ����� � ��������� ��� ���������� �����..
���, ����������, ����� ������ ������ � �������, ��� ����� ��������� ��� �����. 
�� ������ ��� � ������ � ���������, ������� ������ �������� �������.
*/
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();
	ref lcn = &Locations[FindLocation(PChar.location)];

	string nr = NPChar.lastname;

	string buildingstr = NPChar.equip.blade;
	aref buildingref;
	Items_FindItem(buildingstr,&buildingref);

	string interiorstr = "";
	if(CheckAttribute(Npchar,"equip.gun"))
	{
	interiorstr = NPChar.equip.gun;
	aref interiorref;
	Items_FindItem(interiorstr,&interiorref);
	}

	int planks = 0;
	int money = 0;
	int crew = 0;

	int grgbonus = 0;

	int iDYear = sti(lcn.building.(nr).taxyear);
	int iDMonth = sti(lcn.building.(nr).taxMonth);
	int iDDay = sti(lcn.building.(nr).taxDay);
	int taxdays = GetPastTime("day", iDYear, iDMonth, iDDay, 1, GetDataYear(), GetDataMonth(), GetDataDay(), 1);
	int tax = 0;

	string adress;
	if(NPChar.chr_ai.group==LAI_GROUP_PLAYER ){adress = " Commander, Sir, ";}else{adress = "";}

	switch(Dialog.CurrentNode)
	{
		case "First time":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "voice\PADI\PADI001";

			if(rand(100)<30) // ���� ��� ��������� �����, ��������� ��������� ����� ��� �������� ���������� ����
			{
				ChangeCharacterReputation(Pchar, -2);  // ���������: ������ ���������. ����� ��������������, ���� ������� ���	
				PlayStereoSound("voice\Eng_m_a_070.wav");	
				Dialog.text = adress + LinkRandPhrase(" ���������� ��������� ����. ������������� � �������.", " ��������� ������������ � ����� �������! ������������!", "�������������� �������� � ������ ���������, �������!");

				link.l1 = "��������� �����, ������, ������ ��.";
				if(rand(100)>50) {Link.l1.go = "attack1";}
				else{Link.l1.go = "attack2";}

				link.l9 = "������ ���� � ���� � �����, ��� ���� ������! � ����� ������, ������ ��� ����� � ���� � �����: � �������� ��������� ����... ���.. ��������. � ���� ��� ����� ��� �������: � ������ ��������� ������� � ���� ���������� ����� ���, ������ ���� �������� ������� � ���������� ��������� ������ ��������� � ����� �����������.";
				link.l9.go = "exit";
			}
			else
			{
				PlayStereoSound("objects\duel\reload2.wav");
	      		PlayStereoSound("voice\ENGLISH\Eng_m_c_044.wav");
				Dialog.text =  "��������, ��� ������ " + buildingstr + " �������������� �������� � ������ � ��� ," + adress + " � ���� ������� ��� ��������.";

				if(NPChar.chr_ai.group==LAI_GROUP_PLAYER)
				{
					link.l1 = "�� ������������ �� ���� �������. ������������ ��� " + buildingstr + ", ��������� ����� � ��� ���� � �������� �������� ���� ������� ���������� � ���������� � ��������.";
					link.l1.go = "dismantle";

					if(sti(pchar.money)>5000 && !CheckCharacterItem(NPChar,"cannon") )
					{
					link.l21 = "��� ���������� ��������� �� ������� ����� ������� � ������. �� ������ ��� �� ���������� ������� ����. ���, ������, ������ ��� 5000 ������� � ������ ����� ��� ����� �������.";
					link.l21.go = "cannon";
					}

					if(CheckCharacterItem(PChar,"pistolgrenade") && !CheckCharacterItem(NPChar,"pistolgrenade") )
					{
					link.l22 = "������� ���������, � ���� ���� ��� ���� ������ �������: ���, ������ ��� �������, � ���� ��������� ��������� � ����� ���������� ��� �������, ������������ ��...";
					link.l22.go = "grenade";
					}
				}
				else
				{
					link.l1 = "������ �������� ����... ";
					link.l1.go = "exit";
				}

				Link.l4 = "����� ������, ������� ���������, �����������.";
				Link.l4.go = "exit";

				link.l6 = "������, ����� ��� ���������� �� ������� ������ � ������, ����� ���������� ���������?";
				link.l6.go = "odd";

				link.l5 = "��, ������ �� ������ ����� ��� ����������? " + LinkRandPhrase("�� ��������� �����...", "�����, ���������� �������... ���������!", "� ������ ������� ������� ���������� �� ���� ������� ����������, �� ���� �������?");
				link.l5.go = "motion";

				link.l9 = "��, �� ���, ����� �����������! ��� ������, ������� �� �������, ��� ��� ������ ����, ����� ������� ���� ����������� ������? ������ ����������� �������, ����� ������� ���� program\dialogs\" " + NPchar.dialog.filename + " ������������ ���� ����� �����. ����� �������� ����������� � ������������.";
				link.l9.go = "your_dialog"; //��� ��� ������, ������� �����������, ���� �� ��������� ���������� ����� l9. ��� ����� �����.
			}
		break;
                
		case "your_dialog":
			Dialog.text = "������������ ��� ���������� ������� NPC." ;

			link.l1 = "����� ����� ������� ������ link.l1, ������� ��������� ������ ";
			link.l1.go = "exit";	// ������ l1 ��������� ������

			link.l2 = "����� ����� ������� ������ link.l2, ������� ����� � ������� ������ ";
			link.l2.go = "your_dialog2";	// l2 �������� � ������ your_dialog2
		break;	// ����� �������� "���_������"
                
		case "your_dialog2":
			Dialog.text = "������������ ��� ���������� ������� NPC." ;

			link.l1 = "����� ����� ������� ������ link.l1, ������� ��������� ������";
			link.l1.go = "exit";	// ������ l1 ��������� ������

			// ��� ��������� ������� ������, ������� ���� ��� ������, ��������, ������ ��� ����. ����� ������������ ��, ������� ����� ����� ����������� �//� ����� �����. �� ������ �������� ����� �� ���� ����������.

			// AddMoneyToCharacter(Pchar, 1000);

			// GiveItem2Character(Pchar, "Spyglass3");
			// GiveItem2Character(Pchar, "Jewelry5");
			// GiveItem2Character(Pchar, "Mineral3");
			// TakenItems(Pchar, "potion1", 3);

 			// AddCharacterGoods(pchar, GOOD_SANDAL, 10 );
			// AddCharacterGoods(pchar, GOOD_SILK, 10 );
			// AddCharacterGoods(pchar, GOOD_RUM, 20 );
			// AddCharacterGoods(pchar, GOOD_WHEAT, 20 );

			// AddPartyExp(PChar, 100 );


		break;	// ����� �������� "���_������2"

// ���� ������� ������ ��� �����������               
		case "grenade":
			Dialog.text = "...� ������� �� � ��� � ����. � ���� ���� ����, ���������!" ;
			link.l1 = "��� ��� ���, ������� ���������! � ����� �������� ����� �� ����� ������� ��������. (..���� ��������� ��� �����..)";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "pistolgrenade" );
			GiveItem2Character(NPchar, "pistolgrenade");
		break;

		case "cannon":
			PlayStereoSound("INTERFACE\took_item.wav");
			AddMoneyToCharacter(Pchar, -5000);
			Pchar.Ship.crew.quantity = sti(Pchar.Ship.crew.quantity) -3;
			lcn.building.(nr).interior = "cannon";
			Dialog.text = "��, " + GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false) + ", � �������� ������ ���� �������� �������� ������ �����������. �� 5000 ������� �� ������ �� ��� ���� ����������. ������ ��� ��� ��������� �����." ;
			link.l1 = "��� ��� ���, ������� ���������! � ����� ���������� ��������� �� ����� ������� ��������. (..���� ��������� ��� �����..)";
			link.l1.go = "exit";
		break;


// ��������� �����
		case "attack1":
			Dialog.text = "����� ��������� �������� ������������, " + GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false) + "! ��, ���� �� � ��� ���� �������� ��� ���������, ����������, ��� � �����...";
			link.l1 = RandSwear() + " ��������, ������! ����������� ��� �������, ��� �� �� ���������. ����������� ��������, �� ���������� ����� ������� ��� � ������� ���. � ������ �� �� ����...";
			link.l1.go = "exit_attack1";
		break;

		case "attack2":
			Dialog.text = "��������� ������� ������� � ��� ���� ��������������� ������������� ������������, " + GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false) + "! ����� �����, ������� � �������������... ��, ���� �� � ��� ���� �������� ��� ���������, ����������, ��� � �����...";
			link.l1 = RandSwear() + " ��������, ������! ����������� ��� �������, ��� �� �� ���������. ����������� ��������, �� ���������� ����� ������� ��� � ������� ���. � ������ �� �� ����...";
			link.l1.go = "exit_attack2";
		break;

		case "Exit_attack1":
		// PB: ����� ��� �� ������� �� �������� �������.
			Ambush("natives", 3+sti(pchar.skill.fencing), LAI_GROUP_ENEMY, LAI_GROUP_ENEMY, "");
			ChangeCharacterReputation(Pchar, 4);  // �������: ���������. �������� �� ������ �����
			if(AUTO_SKILL_SYSTEM) { AddPartyExpChar(PChar, "Fencing", (3+sti(pchar.skill.fencing)) * 100 ); }
			else { AddPartyExp(PChar, (3+sti(pchar.skill.fencing)) * 100 ); }  // �������: ����. �������� ��������� ����� �� ���� ����������

			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "Exit_attack2":
		// PB: ����� ��� �� ������� �� �������� �������
			Ambush("Soldier_Spa2_15",  3+sti(pchar.skill.fencing), LAI_GROUP_ENEMY, LAI_GROUP_ENEMY, "");
			ChangeCharacterReputation(Pchar, 4);  // �������: ���������. �������� �� ������ �����
			if(AUTO_SKILL_SYSTEM) { AddPartyExpChar(PChar, "Fencing", (3+sti(pchar.skill.fencing)) * 100 ); }
			else { AddPartyExp(PChar, (3+sti(pchar.skill.fencing)) * 100 ); }  // �������: ����. �������� ��������� ����� �� ���� ����������

			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

// �������� ����� ������
		case "dismantle":
			DialogExit();
			planks += sti(buildingref.building.planks);
			crew += sti(buildingref.building.crew);

			if(CheckAttribute(Npchar,"equip.gun"))
			{
				planks += sti(interiorref.building.planks);
				crew += sti(interiorref.building.crew);
			}
			AddCharacterGoods(pchar, GOOD_PLANKS, planks);
			AddCharacterCrew(pchar, crew);   // ccc mar06
			Lai_KillCharacter(npchar);
		break;

// ���������� � ��������              
		case "odd":
			if(buildingstr == "bastion")
			{
				Dialog.text = "������� �����? ������, � ��� ����� �� ����������� ������� �� ������� �����������, ��� � ��� ������� ����������, ������� ������ ����� ��� ��� ������������� ��������� ����� � ��������-����������. �� ����������� ������ ������� ������� �������� ����� �����������. ������ ������� ����� �������� ������ ������� ���������� ����� ��������. �������, ��� ��������� ������ ����� ��������� �� ������ ���������, ���� ���� ���������� ���������� ��������, ��� ����� �� ��������." ;
			} else {
				Dialog.text = "��, ��, ��� ��������� ��������� ���� �� �����, ��� ��� ��� �������� ��������� ���� �������� �� ������ ������� � �����. ������, ���� ���������� ������� �����, ����� ������� ��������� ����� ������������. �� ���� ���� ���������� ���������� ��������, ��� ����� �� ��������.";
			}
			link.l2 = "��� ��� ���������� - ���� �� �����? ��� � ���� ���������� ���� ����� ��������� �������?";
			link.l2.go = "odd2";
		break;

		case "odd2":
			Dialog.text = "������������ ��������� ���������� � ������� ������, ����� ��� ����� ������������ ���� �����, �� �� ��������� ������, ����� ��� ��� ����������� ����� ������������. �� ��������� ������� �������, ������� ��������� �� ���� �������� ������� �����, � �� ��� ����� ������� ���������, ������� ����� ������������ ���������, ������� ���������. �� ������ ���������, ����� ����� �� ����� ����� �� ����� �� ����� ����. �� ������� ��������� ���� ������� ������� ����, ��� ��������� ����� � �����. ��������� �������� �� ��� ��� ��������� ����� � �������, ��� �� ������ � ������������." ;
			link.l1 = "���, � �� ������, ��� ���� ���� ��� ���������... �� ������� �� ������ �� ����������� 17 ����.";
			link.l1.go = "exit";
		break;

		case "motion":
			Dialog.text = LinkRandPhrase(GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false) + ", �� ������ ����� �� ������ ������ � ����������� ����������. ��� ����������, � ���������� - ��� ���.", "� ������������ �� �������������� �����, � � �� ���� ������� ������ ��. '����� ���� ����, ������� �� ����������, ������� �� ������' ��� ������� ������� ������ �������.", "������ ������� ����������: �������� ���������� ��������. ��� ��� ������� �� ��������, ���� � ���� ��� �������������.");
			link.l1 = "������, � �������... ���������.";
			link.l1.go = "exit";
		break;


// ���������� ������
		case "moraledrop":
			lcn.building.(nr).taxyear = GetDataYear();
			lcn.building.(nr).taxMonth = GetDataMonth();
			lcn.building.(nr).taxDay = GetDataDay();
			pchar.ship.crew.morale=makeint(stf(pchar.ship.crew.morale) -5 );  // ���������: ������ ��� �������. �������� �� ������ �����
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}
