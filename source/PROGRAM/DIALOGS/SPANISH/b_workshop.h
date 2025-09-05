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

	string interiorstr = "mobiliario sencillo";
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

	string adress, sound1, sound2;
	if(NPChar.chr_ai.group==LAI_GROUP_PLAYER ){adress = "patr�n";}else{adress = + XI_ConvertString(GetMyAddressForm(NPChar, PChar, ADDR_CIVIL, false, false));}
	
	// determine production based on interiortype
	tax = taxdays * 1;	// Reward, output of goods, you can change the figure before the ';' to your liking
	string prodstr = " intentando convertir esta peque�a choza en un verdadero taller. Pero sin el equipo adecuado, nunca podr� fabricar nada de utilidad o valor."
	int prodgood = -1;
	string prodname = "nothing";
	sound1 = "ambient\shipyard\hammer.wav";
	sound2 = "ambient\town\vehicle.wav";

	switch(interiorstr)
	{
		case "foundry":
		interiorstr = "fundici�n";
		sound1 = "ambient\sea\squeak3.wav";
		sound2 = "objects\shipcharge\ship_onfire.wav";
		prodgood = GOOD_BALLS;
		tax = tax * 100;  // reward: change figure to change production of BALLS ONLY
		prodname = "balas de ca��n";
		prodstr = " fundiendo balas de ca��n. Es un trabajo caluroso, y peligroso tambi�n, con este alto horno hecho a base de chatarra.";
		break;

		case "dock":
		interiorstr = "muelle de carena";
		sound1 = "ambient\shipyard\hammer.wav";
		sound2 = "ambient\sea\sails2.wav";
		prodgood = GOOD_SAILCLOTH;
		tax = tax*3;  // reward: change figure to change production of SAILCLOTH ONLY
		prodname = " fardos de lona para velas de repuesto";
		prodstr = " cosiendo velas y carenando botes de pesca.";
		break;

		case "mine":
		interiorstr = "mina";
		sound1 = "nature\windmill.wav";
		prodname = " toneladas de arena sin valor";
		prodstr = " excavando en busca de piedras preciosas y minerales. Un trabajo muy frustrante a veces, nunca puedes predecir lo que vas a encontrar. Si es que encontramos algo. A menudo, cavamos durante semanas sin �xito. Y el castillete del pozo minero siempre causa problemas: la gr�a est� hecha con madera de deriva, que es quebradiza y se agrieta a menudo, y como puedes ver, el cable se ha roto... �otra vez! Que podamos producir algo de valor en estas condiciones de trabajo es un milagro. ";
		break;

		case "distillery":
		interiorstr = "destiler�a";
		sound1 = "ambient\tavern\tinkle1.wav";
		prodgood = GOOD_RUM;
		tax = tax*2;  // reward: change figure to change production of RUM ONLY
		prodname = "barriles de ron";
		prodstr = " destilando ron. El mejor y m�s fuerte de todo el Caribe, quema como fuego, lo mismo en la garganta que en un farol. Y a veces la destiler�a entera se quema tambi�n porque el alcohol se filtra por los tubos improvisados y gotea sobre el fuego... ";
		break;

	}
	PlayStereoSound(sound1);
	PlayStereoSound(sound2);
	
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

		  if(bDisableFastReload || objLandInterface.data.riskAlarm==1)
		  {
			  Dialog.text = "Parece que tienes cosas que hacer. Termina tus asuntos pendientes.";
			  link.l1 = "Por supuesto, volver� pronto.";
			  link.l1.go = "exit";
		  }
		  else
		  {
			if(rand(100)<15) // chance for random attack, decrease last figure for fewer attacks
			{
				ChangeCharacterReputation(Pchar, -2);  // punishment: reputationloss. Will be offset if accept the fight
				PlayStereoSound("voice\ENGLISH\Eng_m_a_070.wav");	
				Dialog.text =  LinkRandPhrase("�Gracias a Dios que has venido! Puedes defendernos de estos brutos...", "Ah, tu llegada es un regalo del cielo en un momento crucial: est�n a punto de atacarnos. �AY�DANOS!", "Qu� alegr�a verte, necesitamos desesperadamente a alguien como t�, la clase de " + XI_ConvertString(GetMyAddressForm(NPChar, PChar, ADDR_GENDER, false, false)) + " capaz de luchar para protegernos del ataque...");
				link.l1 = "�Eh, c�lmate! Vaya, pero si est�s temblando de miedo... Ahora, dime lo que est� pasando.";
				if(rand(100)>70) {Link.l1.go = "attack1";}
				else{Link.l1.go = "attack2";}

				link.l9 = "Vamos, vamos, no pongas el grito en el cielo por una peque�a disputa laboral. Usa tus herramientas para defenderte, �quieres? �Yo tengo que supervisar la administraci�n de este negocio y esa tarea no me deja tiempo para peleas sindicales!";
				link.l9.go = "exit";
			}
			else
			{
				Dialog.text =  "�Qu�? Oh, t�... Lo siento, " + adress + ", no tengo mucho tiempo para ti. Estamos muy ocupados" + prodstr;

				if(NPChar.chr_ai.group==LAI_GROUP_PLAYER) // if you are the landlord
				{
					if(interiorstr == "dock")
					{
						link.l14 = "�Puedes reparar mi barco?";
						link.l14.go = "repairfree";
					}
					if(taxdays>0 && interiorstr == "mine")
					{
						link.l14 = "�C�mo va la mina? �Hab�is encontrado algo de valor �ltimamente?";
						link.l14.go = "taxmine";
					}

					if(taxdays>0 && prodname != "nothing" && interiorstr != "mine")
					{
						link.l5 = "Me alegra ver que est�is produciendo mercanc�as... para m�. Despu�s de todo, para eso constru� esta maravilla de " + interiorstr + ". �Qu� hab�is logrado en los " + taxdays + " d�as que han pasado desde mi �ltima inspecci�n?";
						if(rand(100)*sti(pchar.reputation)/50 > 20)   // chance for a refusal of payments, decrease last figure for fewer refusals
						{Link.l5.go = "tax";}
						else{Link.l5.go = "taxevasion";}
					}

					link.l6 = "Hum, me pregunto si este taller puede mejorarse m�s.";
					link.l6.go = "interior";

					if(CheckCharacterItem(PChar,"pistolgrenade") && !CheckCharacterItem(NPChar,"pistolgrenade") )
					{
						link.l7 = "Escucha: hay mucho canalla suelto que acecha por estas islas, saqueadores que disfrutan robando, torturando y violando. Quiz�s vengan aqu�, y en ese caso, necesitar�s algo que puedas usar como �ltimo recurso. Ten, toma esta granada...";
						link.l7.go = "grenade";
					}

					link.l8 = "Este edificio ya no tiene ninguna utilidad para m�. Desmanteladlo, cargad las tablas en la bodega y presentaos al contramaestre para que os asigne vuestros deberes a bordo.";
					link.l8.go = "dismantle";

				}
				else   // if you are NOT the landlord
				{
					if(lcn.id == "Oxbay_port")
					{
						link.l114 = "�Qu� demonios le ha pasado a este hermoso lugar? �Qui�n ha arruinado las vistas amontonando todos estos edificios tan raros en el puerto?";
						link.l114.go = "explain";
					}
					link.l9 = "Solo pasaba por aqu�... ";
					link.l9.go = "exit";
				}

				Link.l10 = "Entonces, no te distraer� m�s de tu trabajo. Adi�s.";
				Link.l10.go = "exit";

				link.l11 = "Eh, �qu� haces ah� sin moverte? " + LinkRandPhrase("�Te has tragado un palo de escoba?...", "Vamos, rel�jate un poco...", "Espero un poco m�s de actividad en los habitantes de mi asentamiento, �me oyes?");
				link.l11.go = "motion";

				link.l12 = "Hum, perdona, no quiero ser tiquismiquis, pero este 'edificio' me parece un poco raro...";
				link.l12.go = "odd";

				link.l13 = "�Eh, t�, enfrente del teclado! Este es un edificio creado POR TI, as� que, �por qu� no creas tu propio di�logo para acompa�arlo? Solo tienes que usar Bloc de Notas para abrir el archivo PROGRAM\DIALOGS\SPANISH\" + NPchar.dialog.filename + " y sobreescribir este texto con el tuyo. Luego sigue las instrucciones en los comentarios.";
				link.l13.go = "your_dialog"; //este es el caso que se ejecuta si eliges la opci�n de di�logo l13. Est� justo debajo.
			}
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
			Dialog.text = "... y si esa escoria se atreve a entrar en mi... tu propiedad, patr�n, lo volar� por los aires." ;
			link.l1 = "�Esa es la actitud! Me alegra tener s�bditos tan leales. Pero ten cuidado con a qui�n vuelas por los aires...";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "pistolgrenade" );
			GiveItem2Character(NPchar, "pistolgrenade");
		break;

// add interior
		case "interior":
			Dialog.text = "Oh, s�, podr�amos reeemplazar esta hermosura de "+interiorstr+" que tenemos aqu�, si quieres darle a este taller una nueva funci�n. Solo necesitar� una parte de tus "+ GetSquadronGoods(pchar,GOOD_PLANKS) +" tablas, "+ pchar.money +" piezas de oro y "+ Pchar.Ship.crew.quantity +" marineros. �En qu� est�s pensando?";
			Link.l1 = "Hum, no creo que deba invertir todav�a m�s dinero aqu�.";
			Link.l1.go = "exit";
			Link.l2 = "Un pozo minero con castillete (transforma un taller en una mina de joyas; 10 tablas, 4000 oro, 5 tripulantes)";
			Link.l2.go = "mine";
			Link.l21 = "Una fundici�n de balas de ca��n (transforma un taller en fundici�n; 10 tablas, 4000 oro, 5 tripulantes)";
			Link.l21.go = "foundry";
			Link.l22 = "Una destiler�a de ron (transforma un taller en destiler�a; 10 tablas, 4000 oro, 5 tripulantes)";
			Link.l22.go = "distillery";
			Link.l23 = "Un muelle de carena (transforma un taller en un astillero; 10 tablas, 4000 oro, 5 tripulantes)";
			Link.l23.go = "dock";
		break;

		case "mine":
			npchar.interior = "mina";
			Dialog.text = "�Has dicho " + npchar.interior + "?";
			Link.l2 = "Correcto. Mi secretario te asignar� los recursos necesarios, y espero que el trabajo est� terminado para mi pr�xima visita. �Hasta entonces!";
			Link.l2.go = "erect";
		break;

		case "foundry":
			npchar.interior = "fundici�n";
			Dialog.text = "�Has dicho " + npchar.interior + "?";
			Link.l2 = "Correcto. Mi secretario te asignar� los recursos necesarios, y espero que el trabajo est� terminado para mi pr�xima visita. �Hasta entonces!";
			Link.l2.go = "erect";
		break;

		case "distillery":
			npchar.interior = "destiler�a";
			Dialog.text = "�Has dicho " + npchar.interior + "?";
			Link.l2 = "Correcto. Mi secretario te asignar� los recursos necesarios, y espero que el trabajo est� terminado para mi pr�xima visita. �Hasta entonces!";
			Link.l2.go = "erect";
		break;

		case "dock":
			npchar.interior = "muelle de carena";
			Dialog.text = "�Has dicho " + npchar.interior + "?";
			Link.l2 = "Correcto. Mi secretario te asignar� los recursos necesarios, y espero que el trabajo est� terminado para mi pr�xima visita. �Hasta entonces!";
			Link.l2.go = "erect";
		break;

		case "erect":
			aref interiornewref;
			Items_FindItem(npchar.interior,&interiornewref);
			planks = sti(interiornewref.building.planks);
			money = sti(interiornewref.building.money);
			crew = sti(interiornewref.building.crew);

			if(money > sti(pchar.money) || crew > sti(Pchar.Ship.crew.quantity) || planks > GetSquadronGoods(pchar,GOOD_PLANKS) )
			{
				Dialog.text = "Hum, " + XI_ConvertString(GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false)) + ", tu proyecto de " + npchar.interior + " requiere " + planks + " tablas, " + money + " piezas de oro y "+crew+" hombres. Pero, como te dec�a, solo tenemos "+ GetSquadronGoods(pchar,GOOD_PLANKS) +" tablas, "+pchar.money+" piezas de oro y "+Pchar.Ship.crew.quantity+" hombres...";
				Link.l3 = "Ups... un peque�o error de c�lculo. Bueno, pues este sitio tendr� que seguir como hasta ahora...";
				Link.l3.go = "exit";
			}
			else
			{
  			DialogExit();
  			NextDiag.CurrentNode = NextDiag.TempNode;

				// take buildingresources
				RemoveCharacterGoods(pchar, GOOD_PLANKS, planks-1 );
				PlayStereoSound("INTERFACE\took_item.wav");
				AddMoneyToCharacter(Pchar, -money);
				Pchar.Ship.crew.quantity = sti(Pchar.Ship.crew.quantity) -crew;
				
				// store new interior
				lcn.building.(nr).interior = npchar.interior;
			}
		break;


// random attacks
		case "attack1":
			Dialog.text = "�Demasiado tarde! Aqu� vienen... �Los salvajes can�bales akellani! Oh, si tan solo tuvi�ramos bastiones, empalizadas, minas y ca�ones...";
			link.l1 = RandSwear() + "�Estos marineros de agua dulce est�n paralizados de miedo! La vida en tierra los ha ablandado. Parece que tendr� que luchar sin su ayuda.";
			link.l1.go = "exit_attack1";
		break;

		case "attack2":
			Dialog.text = "Es una revuelta de aprendices. Alg�n alborotador les ha metido en la cabeza la idea de que los est�s explotando...";
			link.l1 = RandSwear() + "�Qu�? �Acaso no les he dado la oportunidad de vivir en c�modos cobertizos en vez de en la h�meda y f�tida bodega de un barco? �Ya no hay gratitud en el mundo! Est� bien, les har� entender lo que es la gratitud a palos...";
			link.l1.go = "exit_attack2";
		break;

		case "Exit_attack1":
		// PB: To prevent the fight from starting before the dialog is closed
			Ambush("natives", 3+sti(pchar.skill.fencing), LAI_GROUP_ENEMY, LAI_GROUP_ENEMY, "");
			ChangeCharacterReputation(Pchar, 4);  // reward: reputation. Change figure to your liking
			if(AUTO_SKILL_SYSTEM) { AddPartyExpChar(PChar, "Leadership", (3+sti(pchar.skill.fencing)) * 100 ); }
			else { AddPartyExp(PChar, (3+sti(pchar.skill.fencing)) * 100 ); }  // reward: experience. Change last figure to your liking

			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "Exit_attack2":
		// PB: To prevent the fight from starting before the dialog is closed
			Ambush("Lower_Citizens",  3+sti(pchar.skill.fencing), LAI_GROUP_ENEMY, LAI_GROUP_ENEMY, "");
			ChangeCharacterReputation(Pchar, 4);  // reward: reputation. Change figure to your liking
			if(AUTO_SKILL_SYSTEM) { AddPartyExpChar(PChar, "Leadership", (3+sti(pchar.skill.fencing)) * 100 ); }
			else { AddPartyExp(PChar, (3+sti(pchar.skill.fencing)) * 100 ); }  // reward: experience. Change last figure to your liking

			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

// taxes and other profits and rewards

		case "taxmine":
  			lcn.building.(nr).taxyear = GetDataYear();
  			lcn.building.(nr).taxMonth = GetDataMonth();
  			lcn.building.(nr).taxDay = GetDataDay();

				if(rand(100)<15) // punishment, chance for no jewels, decrease last figure for more success
				{	
					Dialog.text =  "Odio tener que decirte esto," + adress + ", pero no hemos encontrado nada de valor, aunque hemos removido toneladas de arena y arcilla. Lo siento, pero este negocio es muy impredecible.";
					link.l1 = RandSwear() + "Esto de la miner�a tiene m�s de juego de azar que de negocio. Espero que hay�is tenido m�s �xito cuando haga mi pr�xima visita.";
					link.l1.go = "exit";
				}
				else
				{
					if(rand(100)>50) {GiveItem2Character(PChar, "jewelry"+ makeint(1 + rand(3)) );}
					else{GiveItem2Character(PChar, "mineral"+ makeint(1 + rand(2)) );}

					Dialog.text =  "Oh, esta vez hemos tenido lago de suerte y hemos encontrado algunas piedras preciosas. Aqu� las tienes, ser� mejor que las pongas a buen recaudo.";
					link.l1 = "Oh, estupendo, muchas gracias. Continuad con el trabajo y buena suerte.";
					link.l1.go = "exit";
				}
		break;

		case "tax":
			npchar.tax = tax * 1;	// Reward goods, you can change the figure before the ';' to your liking
			npchar.tax = makeint( sti(npchar.tax) * sti(pchar.reputation)/50 );	// Reputationinfluence on tax, delete line to disable that 

			Dialog.text = "Bueno, desde t� �ltima 'inspecci�n' hemos conseguido acunular " + tax + " " + prodname + ". Ya he contactado con un posible comprador, y los beneficios de esta venta podr�n reinvertirse en el negocio." ;
			link.l1 = LinkRandPhrase("�Reinvertir? �Quiero una rentabilidad por mi capital! �Valor para el accionista! ","�Para qu� necesit�is dinero? Despu�s de todo, yo os proporciono todo lo que necesit�is: protecci�n, materiales, trabajo... ","Yo me embolsar� es... quiero decir, yo me encargar� de eso. Apuesto a que ese comprador te estafar�a, as� que es mejor que yo me encargue personalmente de la venta.") +" Env�alo todo a mi barco.";
			link.l1.go = "taxfull";
			link.l2 = LinkRandPhrase("Buen trabajo. Te dejar� la mitad de la producci�n a ti. �sala sabiamente para acrecentar tu fortuna (y la mia tambi�n).","Entonces, has trabajado duro, �eh? Como recompensa por tus desvelos, te dejar� la mitad de la producci�n para ti (con la esperanza de que eso te anime a trabajar a�n m�s duro).","Escucha, te dejar� la mitad de este dinero para que puedas mejorar tus condiciones de vida y trabajo. Quiero que mi propiedad sea un lugar feliz y decente (y eficiente y rentable).");
			link.l2.go = "taxhalf";
			link.l4 = "�Tanto? Hum, tendr� que comprobar si queda suficiente espacio en la bodega para todo eso. Ser�a un poco frustrante si los frutos de todo este trabajo tuvieran que acabar abandonados en la playa por falta de capacidad de almacenaje, �eh?";
			link.l4.go = "exit";
			link.l3 = "�Por qu� " + npchar.tax + "? �C�mo salen estas cuentas? �Puedes explic�rmelo, por favcor?";
			link.l3.go = "economy";
		break;

		case "taxevasion":
			ChangeCharacterReputation(Pchar, -1);  // punishment: reputationdrop. Change figure to your liking
			npchar.tax = tax * 1;	// Reward taxmoney, you can change the figure before the ';' to your liking
			npchar.tax = makeint( sti(npchar.tax) * sti(pchar.reputation)/50 );	// Reputationinfluence on tax, delete line to disable that 

			Dialog.text = RandSwear() + LinkRandPhrase("Oh, mis disculpas, Excelencia, pero hemos pasado por tiempos duros �ltimamente: la fiebre amarilla nos he debilitado y no hemos podido trabajar...", "Lo siento mucho, Se�or�a, pero no me queda ni una moneda en el bolsillo: justo la otra noche, un ladr�n rob� todo lo que ten�a almacenado para ti. Deber�as hacer algo m�s por la seguridad de tus propiedades...", "Odio tener que dec�rtelo, Excelencia, pero el equipamiento que nos has proporcionado es un mont�n de chatarra. Hemos estado tan ocupados repar�ndolo que no hemos podido producir nada.") ;
			link.l1 = LinkRandPhrase("Bueno, si las cosas est�n tan dif�ciles para vosotros, no voy a complic�roslas m�s: os librar�is por esta vez, pero solo esta vez. Porque no puedo permitirme mostrar debilidad demasiado a menudo, solo puedo mantener a mi tripulaci�on bajo control si me muestro inflexible.", "Est� bien, aceptar� tu explicaci�n esta vez. Pero, para la pr�xima, no quiero o�r m�s excusas... Despu�s de todo, se supone que los beneficios de esta operaci�n son para financiar mi barco, y a la tripulaci�n no le har� gracia tener que renunciar a sus dividendos.", "Hum, no tiene sentido matar a la vaca que quieres orde�ar, �verdad? No tomar� medidas esta vez, pero espero que reanudes la producci�n en cuanto se apsoible. Aunque mi tripulaci�n se quejar� de que soy demasiado indulgente con vosotros.");
			link.l1.go = "moraledrop";

			link.l2 = LinkRandPhrase("Ya basta de lloriqueos, he o�do esas excusas vac�as demasiadas veces como para darles m�s cr�dito. Tendr�s que pagar una penalizaci�n por incumplimiento de contrato si no puedes entregar las mercanc�as que debes producir.", "Bueno, seg�n nuestro contrato, tienes que pagar una compensaci�n si no haces la entrega... Vamos, esto no te matar�... Solo reclamo lo que me corresponde, nada m�s, pero tampoco nada menos.", "�Calla, llorica malversador! Probablemente has vendido la producci�n por tu propia cuenta, �eh? Conmigo eso no funcionar�, confiscar� tu dinero. Es m�o, de todas formas.");
			switch(Rand(5))   // chance for taxevader backing down, increase figure for less revolts and suicides
			{
			case 1: link.l2.go = "taxsuicide"; break;
			case 2: link.l2.go = "taxrevolt"; break;
			link.l2.go = "taxforced"; break;
			}
		break;

		case "taxhalf":
      // next 3 lines reset taxdays to 0
      lcn.building.(nr).taxyear = GetDataYear();
      lcn.building.(nr).taxMonth = GetDataMonth();
      lcn.building.(nr).taxDay = GetDataDay();
			AddCharacterGoods(pchar, prodgood, sti(npchar.tax)/2);
			ChangeCharacterReputation(Pchar, 1);  // reward: reputation. Change figure to your liking
			Dialog.text = "Es muy generoso por tu parte, " + XI_ConvertString(GetMyAddressForm(NPChar, PChar, ADDR_POLITE, false, false)) + ". �Le dir� a todo el mundo que eres un patr�n amable y que se preocupa por sus trabajadores, te lo aseguro!";
			link.l1 = "Oh, no te molestes, no me importa tanto mi reputaci�n. Por cierto, te concedo la noche libre. �Por qu� no vas a la ciudad, confraternizas con los vecinos, hablas con ellos...? �Divi�rtete!";
			link.l1.go = "exit";
		break;

		case "taxfull":
      // next 3 lines reset taxdays to 0
      lcn.building.(nr).taxyear = GetDataYear();
      lcn.building.(nr).taxMonth = GetDataMonth();
      lcn.building.(nr).taxDay = GetDataDay();
			AddCharacterGoods(pchar, prodgood, sti(npchar.tax));
			ChangeCharacterReputation(Pchar, -2);  // punishment: reputationdrop. Change figure to your liking
			Dialog.text =  RandSwear() + LinkRandPhrase("Est� bien, es tu taller, as� que si quieres arruinarlo... Pero no te quejes si te encuentras pronto sin trabajadores porque se han muerto de hambre...", "Es poco acertado exprimir un negocio solo para incrementar el beneficio a corto plazo, si quieres mi opini�n. Pero supongo que no me la has pedido, �eh? Bueno, obtendr�s tu rentabilidad, as� te atragante scon ella...", "�Quieres esquilmar todo el resultado de nuestro duro trabajo? Bueno, pues d�selo a mis... tus trabajadores. Y no te sorprendas si algunas de las mercanc�as se caen accidentalmente al mar en el camino a tu barco.") ;
			link.l1 = "Hum, me pregunto si ha sido buena idea manchar mi buena reputaci�n y arruinar la moral de mis artesanos llev�ndome todo el fruto de su trabajo. ";
			link.l1.go = "exit";
		break;

		case "taxforced":
      // next 3 lines reset taxdays to 0
      lcn.building.(nr).taxyear = GetDataYear();
      lcn.building.(nr).taxMonth = GetDataMonth();
      lcn.building.(nr).taxDay = GetDataDay();
			tax = taxdays * 10;	// Reward rentmoney, you can change the figure before the ';' to your liking
			PlayStereoSound("INTERFACE\took_item.wav");
			AddMoneytoCharacter(Pchar, tax);
			ChangeCharacterReputation(Pchar, -2);  // punishment: reputationdrop. Change figure to your liking
			Dialog.text =  RandSwear() + LinkRandPhrase("Est� bien, toma tu maldito dinero. Pero no te quejes si te encuentras pronto sin trabajadores porque se han muerto de hambre...", "Entonces, no tendr� otra opci�n que pedir prestado el dinero que t edebo aun usurero. Lo que significa que probablemente acabar� con un brazo roto..., en el mejor de los casos...", "Est� bien, sanguijuela, toma. Toma este dinero que hab�a ahorrado para ayudar a mi madre enferma.") ;
			link.l1 = "Hum, me pregunto si ha sido buena idea manchar mi buena reputaci�n isistiendo en el cobro de estas " + tax + " piezas de oro. ";
			link.l1.go = "exit";
		break;

		case "taxrevolt":
			// next 3 lines reset taxdays to 0
			lcn.building.(nr).taxyear = GetDataYear();
			lcn.building.(nr).taxMonth = GetDataMonth();
			lcn.building.(nr).taxDay = GetDataDay();
			tax = taxdays * 10;	// Reward rentmoney, you can change the figure before the ';' to your liking
			PlayStereoSound("INTERFACE\took_item.wav");
			AddMoneytoCharacter(Pchar, tax);
			ChangeCharacterReputation(Pchar, -2);  // punishment: reputationdrop. Change figure to your liking
			Ambush("Lower_Citizens", 3+sti(pchar.skill.fencing), LAI_GROUP_ENEMY, LAI_GROUP_ENEMY, "");
			Dialog.text = RandSwear() + "Est� bien, toma mi dinero. No tengo otra alternativa que pagar. Pero esta dureza que muestra no te har� ning�n favor. �Acabar�s con una revuelta entre manos cuando se corra la voz entre los trabajadores!";
			link.l1 =  RandSwear() + "�Protestas laborales en MI propiedad? �Me encargar� de ello, cr�eme!";
			link.l1.go = "exit";
		break;

		case "taxsuicide":
			// next 3 lines reset taxdays to 0
			lcn.building.(nr).taxyear = GetDataYear();
			lcn.building.(nr).taxMonth = GetDataMonth();
			lcn.building.(nr).taxDay = GetDataDay();
			Dialog.text =  RandSwear() + LinkRandPhrase("�Si t� me arrebatas mis posesiones, yo te arrebatar� las tuyas! �Con una de tus propias granadas! Ir�nico, �verdad? Mi vida no es m�s que una farsa...","�Eres mi ruina! �C�mo voy a seguir viviendo? �Morir� de hambre!... �NO! �No lo har�! �Prefiero morir r�pido, arder como una estrella y no consumirme como una vela! �D�nde est� mi barril de p�lvora?","�Has destruido mi vida, chupasangre! Lo �nico que me queda es este barril de ron... Delicioso ron, del fuerte, del que quema la garganta como los fuegos del infienro... Los fuegos del infierno, eso es lo que te espera... �ME OYES, CHUPASANGRE? �YO TE ENSE�AR� LOS FUEGOS DEL INFIERNO! Este alcohol no solo quema en la garganta...");
			link.l1 = LinkRandPhrase("Oh, vamos, no seas tan dram�tico...","�Eh!, �qu� est�s tramando? Cuidado, podr�as causar un accidente...","Est� bien, m�tate si te apetece. Los perdedores como t� son f�ciles de reemplazar...");
			link.l1.go = "taxsuicide2";
		break;

		case "taxsuicide2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			Explosion (NPchar, 20);
			Lai_KillCharacter(NPchar);
		break;

// shiprepair
		case "repairfree":
		  if(taxdays>0)  
		  {
  			Dialog.text = "Oh, s�, ser� un placer ayudar a nuestro patr�n y, por supuesto, no te ocstar� nada. Si tus marineros nos echan una mano, solo tardaremos dos d�as. Aunque... Bueno, aqu� solo tenemos un muelle peque�o, apropiado solo para barcas de pesca y embarcaciones costeras. Podemos varar tu barco en la playa, carenarlo, calafatearlo y cambiar la tablaz�n da�ada. Pero si hay alg�n da�o grave en la quilla o las cuadernas, no podremos hacer nada al respecto. En algunos casos, incluso podr�amos provocar m�s da�o y perjudicar la estructura. " ;
  			link.l1 = "As� que dejaros toquetear el casco de mi barco es como un juego de azar, �eh? Lo m�s probable es que obtenga una reparaci�n decente gratis, pero puede pasar que acabe peor de lo que empez�, �es as�? Ejem... Tengo que arriesgarme, no tengo tiempo para acudir a otro astillero. Adelante, haced lo que pod�is, rezar� para que sea suficiente... ";
  			link.l1.go = "repairfreeall";
  			link.l2 = "Pero arreglar el aparejo no necesita ning�n equipo especial, �verdad? Pues encarg�os solo de eso, por favor, y dejad el casco como est�. ";
  			link.l2.go = "repairfreerig";
  			link.l3 = "Hum... Quiz�s lo mejor sea llevar mi barco a un astillero de verdad. ";
  			link.l3.go = "exit";
			}
			else
		  {
  			Dialog.text = "Hum... Podr�a..., si no acabaras de despojarnos de todos nuestros materiales y recursos... " ;
  			link.l1 = "Oh... Ya... Bueno, volver� otro d�a. ";
  			link.l1.go = "exit";
			}
		break;

		case "repairfreeall":
      WaitDate("", 0,0, 2,0,0);
		  PlaySound("ambient\shipyard\axe.wav");
		  PlaySound("ambient\shipyard\vehicle.wav"); 
		
		  if(rand(100)<50) // punishment, chance for major damage, decrease last figure for less disasters 
		  {
  			LAi_Fade("", "");
  			WaitDate("", 0,0,2,0,0);
  			RecalculateJumpTable();
			PlaySound("ambient\shipyard\axe.wav");
			PlaySound("ambient\shipyard\vehicle.wav");

			pchar.ship.hp = GetCharacterShipHP(pchar) * (30+rand(20))/100; // 'repairs' hull to 30-50 %
		
    		pchar.ship.sp = GetCharacterShipSP(pchar);
    		DeleteAttribute(pchar,"ship.sails");
    		DeleteAttribute(pchar,"ship.masts");

  			lcn.building.(nr).taxyear = GetDataYear();
  			lcn.building.(nr).taxMonth = GetDataMonth();
  			lcn.building.(nr).taxDay = GetDataDay();
		    
			Dialog.text = RandSwear() + LinkRandPhrase("Malas noticias, Excelencia: varias ligazones est�n totalmente podridas. Probablemente, los constructores de este bajel usaron madera verde para hacerlas. �As� se pudran ellos por su taca�er�a!", "Lo lamento much�simo, Se�or�a, ", "Odio tener que dec�rtelo, Excelencia, pero te estafaron con este barco: est� lleno de pernos falsos. Los pernos que sujetan las tablas del costado a las cuadernas no son de cobre, sino de hierro recubierto de cobre, que sale mucho m�s barato. Est�n casi completamente consumidos por la corrosi�n y es posible que en la pr�xima tormenta las tablas se desprendan. El caso es que nosotros no tenemos muchos pernos de cobre aqu�, as� que") + " me temo que no contamos con los recursos para reparar tu barco.";
  			link.l2 = RandSwear() + "Ser� mejor llevar mi barco a un astillero de verdad. ";
  			link.l2.go = "exit";
			}
			else
			{
  			DialogExit();
  			NextDiag.CurrentNode = NextDiag.TempNode;

  			LAi_Fade("", "");
  			WaitDate("", 0,0,2,0,0);
  			RecalculateJumpTable();
			PlaySound("ambient\shipyard\axe.wav");
			PlaySound("ambient\shipyard\vehicle.wav");

  			lcn.building.(nr).taxyear = GetDataYear();
  			lcn.building.(nr).taxMonth = GetDataMonth();
  			lcn.building.(nr).taxDay = GetDataDay();

			pchar.ship.hp = GetCharacterShipHP(pchar) * (80+rand(20))/100; // reward, repairs hull to 80-100 %, delete '* (80+rand(20))/100' for always 100%
		
    		pchar.ship.sp = GetCharacterShipSP(pchar);
    		DeleteAttribute(pchar,"ship.sails");
    		DeleteAttribute(pchar,"ship.masts");
     		Logit("Dos d�as despu�s, la mayor parte del da�o ha sido reparado.");
			}
		break;

		case "repairfreerig":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_Fade("", "");
			WaitDate("", 0,0,2,0,0);
			RecalculateJumpTable();
			PlaySound("ambient\shipyard\axe.wav");
			PlaySound("ambient\shipyard\vehicle.wav"); 

			lcn.building.(nr).taxyear = GetDataYear();
			lcn.building.(nr).taxMonth = GetDataMonth();
			lcn.building.(nr).taxDay = GetDataDay();
		
  			pchar.ship.sp = GetCharacterShipSP(pchar);
  			DeleteAttribute(pchar,"ship.sails");
  			DeleteAttribute(pchar,"ship.masts");
  			Logit("Dos d�as despu�s, tus velas y tus jarcias estan casi como nuevas.");
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
			Dialog.text = "Ah, lo que me quieres decir es que... �tengo que trabajar todo el d�a con este equipo improvisado! Todo precariamente montado a base de chatarra y madera de deriva. No puedes ni entrar en ese cobertizo sin golpearte en la cabeza con alg�n madero suelto. Pero lo peor es que las paredes est�n tan agrietadas que la gente puede colarse por ellas. �C�mo se supone que voy a trabajar si cualquier zoquete puede atravesar mi puesto de trabajo? Todo es culpa del desgraciado arquitecto que dise�� esto, Couchcaptain Charles. Ese empoll�n picac�digo no tiene ni la menor idea sobre modelos de edificios, solo ha robado dise�os de Inez Diaz y los ha plantado en los lugares m�s imposibles." ;
			link.l1 = "�Eh, deja de quejarte! �No es mejor tener un taller improvisado que no tener nada en absoluto? �Preferir�as estar en el paro? Por mi parte, yo pienso disfrutar de las vistas y de las capacodades de mis nuevos edificios en vez de perder el tiempo con comentarios quisiquillosos.";
			link.l1.go = "exit";
			link.l2 = "En vez de quejarte sobre lo que hacen otros, deber�as mover el culo y resolver el problema t� mismo. �Cu�l es la causa exacta de este problema? S� algunas cosas sobre modelos 3D, �quiz�s pueda ayudar?";
			link.l2.go = "odd2";
			link.l3 = "�Qu� importa el aspecto que tenga? Lo que no me gusta es el aspecto econ�mico: la cantidad de productos y beneficios. Y la frecuencia de ataques y eventos, las penalizaciones...";
			link.l3.go = "tweaking";
		break;


		case "odd2":
			Dialog.text = "Cualquier tipo de ayuda ser� muy apreciada. A algunos de estos modelos de edificios les vendr�a bien una remodelaci�n. El prinicpal problema es que estos modelos de edificios no son parte del modelo del mapa, sino objetos ligados a personajes inm�viles, como yo. Por lo tanto, el 'walkpatch' del modelo del mapa -lo que impide a los personajes caminar a trav�s de las paredes- dno cubres estos nuevos edificios. Lo que neceistamos es un 'walkpatch' alrededor de los objetos que componen el edificio. O alrededor del personaje al que el edificio est� ligado. Si conoces una soluci�n a este problema, ponte en contacto con el foro de la comunidad de creadores de mods de PotC en "+PA_INET;
			link.l1 = "Hum, lo pensar�...";
			link.l1.go = "exit";
		break;

		case "tweaking":
			Dialog.text = "Eso tiene f�cil arreglo. Puedes hacer esa clase de cambios a tu gusto editando un archivo de texto. Por ejemplo, aqu� puedes reducir los pagos que recibes por este negocio: abre el archivo 'Pirates of the Caribbean\PROGRAM\DIALOGS\SPANISH\ " + NPchar.dialog.filename + " ' con un editor d etexto como Bloc de Notas. Usa la funci�n de b�squeda y busca la palabra clave 'reward'. Esto te llevar� a una l�nea similar a esta: ' tax = taxdays * 1;	// Reward ...  '. Reemplaza el '1' por '0.5' para reducir lo que te pago a la mitad (no esperar�s que te diga c�mo aumentarlo ;) ). Del mismo modo, puedes modificar otras cosas buscando las palabras clave 'chance' para la proababilidad de activar eventos, o 'punishment' para cosas como la p�rdida de reputaci�n. Los comentarios que hay detr�s de las '//' barras dobles te explicar�n qu� es lo que hace el c�digo que tienen delante. Para desactivar la infleucnai de la reputaci�n sobre los beneficios, busca las l�neas con el comentario '// reputationinfluence..' y b�rralas. Si necesitas m�s informaci�n, ponte en contacto con el foro de la comunidad de creadores de mods de PotC en "+PA_INET;
			link.l1 = "Gracias por las indicaciones. Parece que moddear no es tan dif�cil, �eh? Solo requiere un poco de paciencia y dedicaci�n. Pero si me manejo jugando a este juego, tambi�n deber�a ser capaz de modificarlo un poco.";
			link.l1.go = "exit";
		break;

		case "economy":
			Dialog.text = "Est� bien, aqu� va una peque�a lecci�n sobre la socioeconom�a de tu propiedad: cada d�a, tus trabajadores y arrendatarios trbaajan en tu propiedad, ahorran sus ganancias o acumulan productos. Cu�nto ahorran y cu�nto acunulan depende en gran medida de tu comportamiento: los trbajadores contentos son m�s eficientes, los trabajadores que se sienten seguros ahorran para el futuro, y si tratas a tus trabajadores con decencia y los proteges, estar�n m�s dispuestos a entregarte dinero o productos. En caso contrario, se vuelven vagos, malversan tu dinero o incluso se rebelan. Tu reputaci�n es importante: cuanto mejor se atu reputaci�n, mayores ser�n tus beneficios, y viceversa. Cuanto mejor sea tu comportamiento en tus propiedades, mejor ser� tu reputaci�n. As� que debes aprender a buscar un equilibrio entre tus necesidades inmediatas de dinero y mercanc�as y la prosperidad de tu negocio a largo plazo. Un buen patr�n es estricto cuando debe y generoso cuando puede." ;
			link.l1 = "�A eso lo llamas socioeconom�a? A m� me suena a vud�. �Para qu� necesit�is ahorros? Despu�s de todo, yo os proporciono todo lo que pod�is necesitar: protecci�n, alojamiento, comida, trabajo... As� que lo correcto ser�a que todo vuestro oro acabe en mis cofr... en los cofres comunales. �Eso es lo que yo llamo socioeconom�a, lo aprend� de un tipo muy listo llamado Marx!";
			link.l1.go = "taxfull";
			link.l2 = "Ya veo... Escucha, os dejar� la mitad de vuestros ahorros para que pod�is mejorar vuestras condiciones d evida y trabajo. Quiero que mi propiedad sea un lugar decente y feliz (y eficiente y rentable).";
			link.l2.go = "taxhalf";
			link.l3 = "Todo esto no me gusta. Sacrificar�a este pago a cambio de informaci�n sobre c�mo editar el mod a mi gusto. Todos estos eventos e influencias mutuas no casan con mi forma de jugar.";
			link.l3.go = "tweaking";
		break;

		case "motion":
			Dialog.text = LinkRandPhrase("Oh, me abruma tanto tu presencia que no puedo moverme.", "He estado trabajando todo el d�a, me duelen los huesos y no dejar� que me impidas tomarme un bien merecido descanso.", "�Me creer�as si te dijera que tengo que soportar todo el peso del edificio? Se vendr�a abajo si hago el m�s m�nimo movimiento...");
			link.l1 = "Est� bien, lo comprendo... Adi�s.";
			link.l1.go = "exit";
		break;

		case "explain":
			Dialog.text = "El mayor magnate inmobiliario de la ciudad, Donald Dump, ha hecho una fortuna con estos proyectos de desarrollo urban�stico en los suburbios de #sOxbay# y #sGreenford#. Y para promover su reputaci�n, ha gastado parte de sus beneficios en fortificaciones adicionales para el puerto, incluyendo una flamante puerta de estilo renacentista y una torre del reloj a la que ha llamado 'Torre Dump'. Es cierto, que esta arquitectura moderna puede parecer un poco fuera de lugar, pero los ca�ones funcionan bien. Si quieres verlos en acci�n, no tienes m�s que atacarme... ";
			link.l1 = "�Odio a los magantes inmobiliarios eg�latras! Sobre todo si arruinan el paisaje con esos suburbios prefabricados que son todos iguales.";
			link.l1.go = "explain2";
		break;

		case "explain2":
			Dialog.text = "Oh, deber�as echarle un vistazo a los suburbios reci�n reconstruidos. Ofrecen un cambio considerable respecto a los lugares de siempre. Y en vez de quejarte de un boom inmobiliario del que t� tambi�n podr�as beneficiarte, l�nzate a desarrollar tus propios asentamientos y recibir los beneficios en forma de rentas, impuestos y los bienes que tus granjas y talleres produzcan. S�, ahora puedes erigir tus propios edificios donde quieras. Solo necesitas un oficial, tablas y dinero.";
			link.l1 = "Hum... O podr�a construir mi propia guarida pirata... o mi propia base naval... o mi propia fortaleza, �eh? �Eso s� que es un cambio! Bueno, me temo que tengo que irme. Tengo que encontrar un buen solar donde construir...";
			link.l1.go = "exit";
			link.l2 = "Todo eso est� muy bien, pero, �esos edificios prefabricados son relamente lo bastante robustos? En estas latitudes abundan los terremotos. Hablando de terremotos, �no sientes la tierra temblando bajo tus pies?";
			link.l2.go = "explain3";
		break;

		case "explain3":  // PB: Buildings will disappear after leaving Oxbay, done in quests_common.c
			Dialog.text = RandSwear() + " �Es un terremoto de verdad! Pero no te preocupes. Estos nuevos edificios son perfectamente resistentes. No se vendr�n abajo. *Para sus adentros:* No se vendr�n abajo. *empieza a murmurar para sus adentros*";
			link.l1 = "De repente, no pareces tener mucha fe en la fortaleza de estos edificios. �No me sorprender�a que se hayan convertido en un mont�n de ruinas la pr�xima vez que venga por aqu�!";
			link.l1.go = "Exit";
			pchar.quest.oxbay_port_earthquake.win_condition.l1 = "MapEnter";
			pchar.quest.oxbay_port_earthquake.win_condition = "oxbay_port_earthquake"; // PB: Add building removal option to ALL storylines
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
