// ccc Buildingset, new file	
/*
ccc Dec06:
Unlike most other files in this folder this one contains not only a textarray but code and English text merged.

The buildingset has recently been messed up by the attempt to localize my original all-English dialogfiles. 
Instead of spending weeks with fixing and testing the new files I restored my original files. 
However, the localization project has changed the structure of PotC for good : 
Upon loading a  "x-dialog.c" codefile the program now automatically includes a  "x-dialog.h" text array file from the dialogs\english subfolder(or from the Russian folder if you use that language). 
There the dialogtext is supposed to be.

However, I prefer to have code AND plain text in one file, for 3 reasons:
-It is much easier to write
-You have much less bugs with not matching texts
-It is much easier to read and understand the file for debuggers and people who would like to change it
The last point is especially important for me cause the Buildingset is supposed to be a tool for people who want to start modding.
That's why I stick to the original "code plus English text" dialogfiles.

As a concession to the localization project I put these files NOT into the \dialogs rootfolder but into the \dialogs\English subfolder.
So if you want to translate this dialog you can simply copy the "code plus English text" into the subfolder for your language and translate the English text there.
That will certainly be less work and trouble than messing up my files again. 
Not mention the work and trouble that the debuging always causes.
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
	if(NPChar.chr_ai.group==LAI_GROUP_PLAYER ){adress = " mi comandante,";}else{adress = "";}

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

			if(rand(100)<30) // chance for random attack, decrease last figure for fewer attacks
			{
				ChangeCharacterReputation(Pchar, -2);  // punishment: reputationloss. Will be offset if accept the fight
				PlayStereoSound("voice\Eng_m_a_070.wav");	
				Dialog.text = adress + LinkRandPhrase(", fuerzas hostiles avistadas. Preparad la defensa.", ", �movimientos enemigos en nustro sector! �Zafarrancho de combate!", "�Movimientos sospechosos en el per�metro, todos a sus puestos!");

				link.l1 = "Un informe detallado, soldado. Ahora.";
				if(rand(100)>50) {Link.l1.go = "attack1";}
				else{Link.l1.go = "attack2";}

				link.l9 = "�D�jame en paz con esas tonter�as, ese es tu trabajo! Para eso os he contratado como carne de ca�... ca�oneros expertos. De todas formas no tengo tiempo: tengo que irme.";
				link.l9.go = "exit";
			}
			else
			{
				PlayStereoSound("objects\duel\reload2.wav");
	      		PlayStereoSound("voice\ENGLISH\Eng_m_c_044.wav");
				Dialog.text =  "Informo de que la fortificaci�n est� guarnecida y lista para el combate," + adress + " todo est� tranquilo en este sector.";

				if(NPChar.chr_ai.group==LAI_GROUP_PLAYER)
				{
					link.l1 = "Nos retiramos de esta posici�n. Desmantelad la fortificaci�n, cargad las tablas en la bodega y presentaos al contramaestre para que os asigne vuestros deberes a bordo.";
					link.l1.go = "dismantle";

					if(sti(pchar.money)>5000 && !CheckCharacterItem(NPChar,"cannon") )
					{
					link.l21 = "Esta fortificaci�n tendr�a un aspecto mucho m�s formidable con un ca��n. Por no mencionar el aumento en potencia de fuego. Soldado, toma estas 5000 piezas de oro y procura un ca��n para esta posici�n.";
					link.l21.go = "cannon";
					}

					if(CheckCharacterItem(PChar,"pistolgrenade") && !CheckCharacterItem(NPChar,"pistolgrenade") )
					{
					link.l22 = "Soldado, tengo una misi�n especial para ti. Toma esta granada, y si el enemigo nos supera y asalta esta posici�n...";
					link.l22.go = "grenade";
					}
				}
				else
				{
					link.l1 = "Solo pasaba pora qu�... ";
					link.l1.go = "exit";
				}

				Link.l4 = "Muy bien, soldado. Contin�a.";
				Link.l4.go = "exit";

				link.l6 = "Soldado, �no es esta fortificaci�n demasiado baja y d�bil para detener un asalto?";
				link.l6.go = "odd";

				link.l5 = "Eh, �qu� haces ah� sin moverte? " + LinkRandPhrase("�Te has tragado un palo de escoba?...", "Vamos, rel�jate un poco... �DESCANSE, SOLDADO!", "Espero un poco m�s de actividad por parte de mis infantes de marina, �me oyes?");
				link.l5.go = "motion";

				link.l9 = "�Eh, t�, enfrente del teclado! Este es un edificio creado POR TI, as� que, �por qu� no creas tu propio di�logo para acompa�arlo? Solo tienes que usar Bloc de Notas para abrir el archivo PROGRAM\DIALOGS\SPANISH\" + NPchar.dialog.filename + " y sobreescribir este texto con el tuyo. Luego sigue las instrucciones en los comentarios.";
				link.l9.go = "your_dialog"; //this is the case that runs if you choose the dialogoption l9. It is right below.
			}
		break;
                
		case "your_dialog":
			Dialog.text = "Escribe aqu� el texto de di�logo del NPC." ;

			link.l1 = "Texto de di�logo del jugador: opci�n link.l1, que cierra el di�logo ";
			link.l1.go = "exit";	// link l1 exits the dialog

			link.l2 = "Texto de di�logo del jugador: opci�n link.l2, que conduce a otro intercambio ";
			link.l2.go = "your_dialog2";	// l2 leads to the case your_dialog2
		break;	// end of case "your_dialog"
                
		case "your_dialog2":
			Dialog.text = "Escribe aqu� el texto de di�logo del NPC." ;

			link.l1 = "Texto de di�logo del jugador: opci�n link.l1, que cierra el di�logo";
			link.l1.go = "exit";	// link l1 exits the dialog

			// Here are some codelines that give you money, items, goods or experience. To activate them delete the comment slashes '//' in front of the code. You can change the amounts to your liking.

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


		break;	// end of case "your_dialog2"

// give grenade to building for selfdefense                
		case "grenade":
			Dialog.text = "..., los volar� en pedazos. �Conozco mi deber, mi comandante!" ;
			link.l1 = "�As� se habla, soldado! Con tu sentido del deber, pronto llegar�s a cabo (... si vives lo sifciente).";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "pistolgrenade" );
			GiveItem2Character(NPchar, "pistolgrenade");
		break;

		case "cannon":
			PlayStereoSound("INTERFACE\took_item.wav");
			AddMoneyToCharacter(Pchar, -5000);
			Pchar.Ship.crew.quantity = sti(Pchar.Ship.crew.quantity) -3;
			lcn.building.(nr).interior = "cannon";
			Dialog.text = "S�, " + XI_ConvertString(GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false)) + ", conozco bastante bien al sargento mayor del arsenal local. Por 5000 piezas de oro, vender�a toda su artiller�a. Solo necesitar� unas pocas horas." ;
			link.l1 = "�As� se habla, soldado! Con tu buen entendimiento de la log�stica, pronto llegar�s a cabo (.. si vive lo suficiente).";
			link.l1.go = "exit";
		break;


// random attacks
		case "attack1":
			Dialog.text = "�Se acercan los salvajes can�bales akellani, " + XI_ConvertString(GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false)) + "! Oh, si tan solo tuvi�ramos m�s bastiones, empalizadas, minas y ca�ones...";
			link.l1 = RandSwear() + " �Atenci�n, soldado! Mant�n esta posici�n pase lo que pase. No dejes de dispararg y no dejes que el enemigo te arrastre a un combate cuerpo a cuerpo. Yo me ocupar� de eso...";
			link.l1.go = "exit_attack1";
		break;

		case "attack2":
			Dialog.text = "�Francisco Pizarro el Joven y su horda de conquistadores merodeadores se acercan, " + XI_ConvertString(GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false)) + "! �vidos de sangre, bot�n y bajos instintos... Oh, si tan solo tuvi�ramos m�s bastiones, empalizadas, minas y ca�ones...";
			link.l1 = RandSwear() + " �Atenci�n, soldado! Mant�n esta posici�n pase lo que pase. No dejes de dispararg y no dejes que el enemigo te arrastre a un combate cuerpo a cuerpo. Yo me ocupar� de eso...";
			link.l1.go = "exit_attack2";
		break;

		case "Exit_attack1":
		// PB: To prevent the fight from starting before the dialog is closed
			Ambush("natives", 3+sti(pchar.skill.fencing), LAI_GROUP_ENEMY, LAI_GROUP_ENEMY, "");
			ChangeCharacterReputation(Pchar, 4);  // reward: reputation. Change figure to your liking
			if(AUTO_SKILL_SYSTEM) { AddPartyExpChar(PChar, "Fencing", (3+sti(pchar.skill.fencing)) * 100 ); }
			else { AddPartyExp(PChar, (3+sti(pchar.skill.fencing)) * 100 ); }  // reward: experience. Change last figure to your liking

			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "Exit_attack2":
		// PB: To prevent the fight from starting before the dialog is closed
			Ambush("Soldier_Spa2_15",  3+sti(pchar.skill.fencing), LAI_GROUP_ENEMY, LAI_GROUP_ENEMY, "");
			ChangeCharacterReputation(Pchar, 4);  // reward: reputation. Change figure to your liking
			if(AUTO_SKILL_SYSTEM) { AddPartyExpChar(PChar, "Fencing", (3+sti(pchar.skill.fencing)) * 100 ); }
			else { AddPartyExp(PChar, (3+sti(pchar.skill.fencing)) * 100 ); }  // reward: experience. Change last figure to your liking

			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

// dismantling of this building
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

// info about modding                
		case "odd":
			if(buildingstr == "bastion")
			{
				Dialog.text = "�Demasiado baja? Parece que tienes las mismas ideas anticuadas en cuanto a arquitectura militar que esos canteros rusos que construyeron todos esos ayuntamientos y fuertes medievales por el archipi�lago. Pero la invenci�n de la p�lvora ha dejado obsoletos los muros altos y almenados. El perfil bajo de este basti�n ofrece a la artiller�a de sitio un objetivo m�s dif�cil. No importa que la infanter�a enemiga pueda escalar los parapetos bajos; mientras nuestra artiller�a siga disparando, no vivir�n para llegar hasta la base del muro." ;
			} else {
				Dialog.text = "Bueno, toda la madera buena se destina a los astilleros, as� que hemos tenido que construir esta empalizada con troncos quebradizos y madera de deriva. Es verdad, hay huecos lo bastante grandes para que un enemigo pueda colarse. Pero mientras nuestra artiller�a siga disparando, no vivir�n mucho tiempo.";
			}
			link.l2 = "�As� que la artiller�a es la clave de todo? �C�mo puedo depslegar los ca�ones de la forma m�s efectiva?";
			link.l2.go = "odd2";
		break;

		case "odd2":
			Dialog.text = "Concentra varias fortificaciones con ca�ones para que puedan apoyarse unas a otras, pero no tan cerca como para que todas puedan ser atacadas a la vez. En primera l�nea, un robusto basti�n que pueda soportar el grueso del ataque, y detr�s empalizadas m�s baratas desde las que disparar a los atacantes mientras est�n ocupados con el basti�n. Pero aseg�rate de que ninguno de tus hombres se mete en la l�nea de fuego. A largas distancias, nuestras granadas volar�n por los aires a cualquiera que est� cerca del objetivo. No te involucres directamente en el combate o qu�date cerca de los ca�ones, donde su punter�a es mejor." ;
			link.l1 = "Hum, no s� si puedo permitirme todo eso... Pero gracias por la lecci�n en fortificaciones del siglo XVII.";
			link.l1.go = "exit";
		break;

		case "motion":
			Dialog.text = LinkRandPhrase(XI_ConvertString(GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false)) + ", siempre nos ponemos firmes en presencia de un superior. Esa es nuestra instrucci�n y la instrucci�n lo es todo.", "Le tengo el ojo echado a un objetivo sospechoso y no quiero perderlo. 'Apunta bien, no te muevas, no parpadees', sol�a decir nuestro sargento instructor.", "La primera regla del camuflaje: el movimiento atrae la atenci�n. As� que nunca te muevas si no tienes que hacerlo.");
			link.l1 = "Est� bien, entiendo... Contin�a.";
			link.l1.go = "exit";
		break;


// dialogexits
		case "moraledrop":
			lcn.building.(nr).taxyear = GetDataYear();
			lcn.building.(nr).taxMonth = GetDataMonth();
			lcn.building.(nr).taxDay = GetDataDay();
			pchar.ship.crew.morale=makeint(stf(pchar.ship.crew.morale) -5 );  // punishment: crew moraledrop. Change figure to your liking
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}
