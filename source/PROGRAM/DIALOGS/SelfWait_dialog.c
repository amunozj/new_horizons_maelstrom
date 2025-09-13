// Mirsaneli & Vex
// Standalone "waste time / rest" dialog for the player.

void DoWaitHours(int hrs)
{
    if (hrs <= 0) return;
    if (hrs > 72) hrs = 72;

    WaitDate("", 0, 0, 0, hrs, 0);

    Event("WeatherTimeUpdate", "f", GetTime());
    Whr_UpdateWeather(true);
    Whr_UpdateWeatherHour();

    // --- show sand clock fader ---
    if (!IsEntity(&reload_fader)) {
        CreateEntity(&reload_fader, "fader");
        SendMessage(&reload_fader, "ls", FADER_PICTURE, "loading\sandclock.tga.tx"); // your custom image
        SendMessage(&reload_fader, "lfl", FADER_IN, 1.0, false); // fade in over 1 second
        SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, true); // fade out after
    }

    // --- then reload same location ---
    ref pchar = GetMainCharacter();
    string curLoc = pchar.location;
	
	string curLocGroup = "goto"; // default group
	string curLocLocator = "goto1"; // fallback

	if (CheckAttribute(pchar, "SelfWaitLocator")) {
		curLocLocator = pchar.SelfWaitLocator;
	}
    DoQuestReloadToLocation(curLoc, curLocGroup, curLocLocator, "pchar_back_to_player");
}

int HoursUntil(int targetHour) // targetHour: 0..23
{
    int h = GetHour();
    int delta = (24 - h + targetHour) % 24;
    if (delta == 0) delta = 24;
    return delta;
}

void DialogExit_Self()
{
    locCameraSleep(false);
    DialogExit();
}

void ProcessDialogEvent()
{
    aref Link;
    DeleteAttribute(&Dialog, "Links");
    makearef(Link, Dialog.Links);

    switch (Dialog.CurrentNode)
    {
        case "TalkSelf_Main":
            Dialog.Text = "How long do you want to rest?";

            Link.l1  = "1 hour";                 Link.l1.go  = "Wait_1";
            Link.l2  = "3 hours";                Link.l2.go  = "Wait_3";
            Link.l3  = "6 hours";                Link.l3.go  = "Wait_6";
            Link.l4  = "12 hours";               Link.l4.go  = "Wait_12";

            // Exit
            Link.l10 = "Nevermind";              Link.l10.go = "Exit";
        break;

        case "Wait_1":       DoWaitHours(1);                 DialogExit_Self(); break;
        case "Wait_3":       DoWaitHours(3);                 DialogExit_Self(); break;
        case "Wait_6":       DoWaitHours(6);                 DialogExit_Self(); break;
        case "Wait_12":      DoWaitHours(12);                DialogExit_Self(); break;

        case "Exit":
            DialogExit_Self();
        break;
    }
}