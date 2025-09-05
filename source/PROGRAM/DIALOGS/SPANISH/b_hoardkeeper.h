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
			NextDiag.TempNode = "first time";
			dialog.text = "Joven, cuya voz impaciente resuena en estas tan venerables b�vedas, manifiesta tu deseo con modales nobles, o deja que el silencio reine una vez m�s sobre los antigos muros. Muros anta�o vestidos con tapices de seda y terciopelo, que una vez vieron grandes banquetes y grandes batallas... �y grandes traciones y asesinatos! Ahora el silencio es el �nico manto que cubre estas ruinas, el �nico velo de estas fr�as piedras, por los siglos de los siglos. �Silencio de paz? �Silencio de muerte? Cu�l ser� para ti a�n no est� escrito.";
			link.l1 = "�Eh? �Qu�...? No he o�do la puerta... �De d�nde has salido tan de repente y sin hacer ruido?";
			link.l1.go = "help_2";
			link.l4 = "�T� eres el famoso guardi�n de tesoros? �Qu� garant�as tengo de que no te apropiar�s de mis cosas, eh?";
			link.l4.go = "help_3";
			link.l2 = "(Maldita sea, �d�nde est� mi ejemplar de 'Shakespeare para escolares'? Ah, aqu�..) Ejem... Aqu� me presento, humilde e insignificante ante el rostro de los siglos y la sabidur�a, deseando confiarte, oh, confidencial tesorero, mi modesto peculio, bien que s� que no ha de compararse su valor con el de esos ojos y estas piedras que han sido testigos de m�s encumbrados tesoros, �y m�s encumbrados hombres!";
			link.l2.go = "items";
			link.l3 = "Oh, por favor, �no podemos ir al grano?";
			link.l3.go = "items1";
		break;

		case "help_2":
			dialog.text = "Qui�n si no yo, que he recorrido estos antiguos muros desde hace tantos a�os que me asemejo al mortero que une las piedras: quebradizo, s�, pero a�n erguido y orgulloso, �qui�n si no hab�a de conocer los caminos ocultos que hombres olvidados tiempo ha constuyeron en un vano af�n por esconder sus actos ru�nes? Vano, pues todas sus maldades, �ay!, nada hicieron para eludir su fat�dico sino. Su sino, �habr� de ser tambi�n el tuyo? �Qui�n sabe? �Qui�n sabe cu�ndo golpear�? �Qui�n sabr� de ti, una vez que haya golpeado? �Nadie, nunca m�s!";
			link.l1 = "Tus palabras son muy ciertas, oh, anciano Guardi�n, �del polvo salimos para convertirnos en polvo nuevamente! Pero lo que en ese intervalo logramos es lo que diferencia a hombres de ratones. Ser rico y famoso, o no ser nada, esa es la cuesti�n. ";
			link.l1.go = "items";
		break;

		case "help_3":
			dialog.text = "�No oses, bergante, cuestionar el honor de mi sangre! Mi casa sirvi� a reyes y condes y barones por largos siglos sin m�cula. Uno de mi misma sangre tuvo a su cuidado el rescate de Coraz�n de Le�n, y ni una blanca gast� que no fuera para procurar la libertad de su se�or. Otro de mi sangre, guardi�n de la real Torre de Londinum en tiempos del Tercer Ricardo, que all� ten�a encadenados a los hijos de su hermano, no pudiendo soportar el cruel crimen que su juramento de lealtad le obligaba a perpetrar, decidi� poner fin a su vida con honor antes de traicionar a su se�or, por depravado que este fuera. Pero no antes de cumplir la triste tarea de sellar el destino de los desdichados pr�ncipes. Un acto atroz, sin duda, y que mortific� el alma de mi antepasado tanto como los cuerpos de sus v�citmas fueron mortificados. Pero siempre tuvo su deber en mayor estima que su bienestar, �incluso que su salvaci�n, s�! �Como yo, mientras tenga aliento de vida!";
			link.l1 = "Ahorra aliento, entonces, fidel�isimo Guardi�n, para que puedas por mucho tiempo cumplir tu pesado deber. En cuanto a esos viles reyes y barones, �la peste caiga sobre sus casas!";
			link.l1.go = "items";
		break;

		case "items":
			if(AUTO_SKILL_SYSTEM) { AddPartyExpChar(PChar, "Sneak", 100 ); }
			else { AddPartyExp(PChar, 100 ); }
			WaitDate("", 0, 0, 0, 2, 0);
			dialog.text = "��C�mo osas, r�stica criatura?! �No escarnezcas al Bardo, imitando sus palabras de belleza suma con tu torpe lengua, empa�ando la verdad de su venerable verso con vano ingenio! �Oye ahora su verdadero texto, truh�n, y que sus palabras valgan para ganarte cien c�ntimos de sabidur�a! (el Guardi�n recita Hamlet... durante dos horas) �Pero, alto, basta de palabras ociosas, las arenas del tiempo se nos escapan entre los dedos! �Abrir� ahora el tomo de lo que tus malvados planes y vanas maquinaciones te han reportado?";
			link.l1 = "Eh... �S�, por favor! Bien est� lo que bien acaba, �eh?";
			link.l1.go = "items1";
		break;

		case "items1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LaunchCharacterItemChange(NPChar);

			ChangeCharacterAddress(NPChar, "none", "");
			Logit("El Guardi�n desaparece sin decir ni una palabra ni hacer ni un sonido, como si los antiguos muros se lo hubieran tragado...")
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			ChangeCharacterAddress(NPChar, "none", "");
			Logit("El Guardi�n desaparece sin decir ni una palabra ni hacer ni un sonido, como si los antiguos muros se lo hubieran tragado...")
		break;
	}
}
