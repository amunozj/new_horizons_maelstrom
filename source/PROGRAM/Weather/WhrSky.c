#event_handler("frame", "UpdateSky");

object Sky;
string selectedSkyFolder = "";  // Mirsaneli: Declare global variable
string lastSelectedSkyFolder; // Stores the selected sky folder globally
int lastSkyUpdateHour = -1;   // Tracks the last updated hour

//float fPrevCameraAX = 0;

void WhrDeleteSkyEnvironment()
{
	if(isEntity(&Sky))
	{
		DeleteClass(&Sky);
	}

	DeleteAttribute(&Sky, "");
}

void WhrCreateSkyEnvironment()
{
	aref aCurWeather = GetCurrentWeather();
	aref aSky;
	makearef(aSky, aCurWeather.Sky);

	DeleteAttribute(&Sky, "")
	if(!isEntity(&Sky))
	{
		CreateEntity(&Sky, "Sky");
		//#20180613-01, #20180615-01
		if(bSeaActive)
            LayerAddObject("sea_reflection", &Sky, 1);
        else
            LayerAddObject("sea_reflection", &Sky, 11);
	}

	FillSkyDir(&Sky);
	//Sky.Dir = Whr_GetString(aSky, "Dir");

	Sky.Color = Whr_GetColor(aSky, "Color");
	Sky.RotateSpeed = Whr_GetFloat(aSky, "Rotate"); // Warship 02.06.09
	Sky.Angle = Whr_GetFloat(aSky, "Angle");
	Sky.Size = Whr_GetFloat(aSky, "Size");

	//#20180615-01

    if(bSeaActive) {
        Sky.Size = Whr_GetFloat(aSky, "Size");
        Sky.techSky = "Sky";
        Sky.techSkyBlend = "SkyBlend";
        Sky.techskyAlpha = "skyblend_alpha";
        Sky.techSkyFog = "SkyFog";
	}
	else {
	    Sky.Size = 2048; // == 512.0 * 4;
	    Sky.techSky = "SkyLand";
        Sky.techSkyBlend = "SkyBlendLand";
        Sky.techskyAlpha = "skyblend_alphaLand";
        Sky.techSkyFog = "SkyFogLand";
	}

	Sky.isDone = "";
}

// Warship 02.06.09
void UpdateSky()
{
	float windSpeed = 5.0;
	float timeScale = 1.0 + TimeScaleCounter * 0.25;

	if(timeScale <= 2.0)
	{
		timeScale = 1.0;
	}
	else
	{
		timeScale /= 2.0;
	}
	if(CheckAttribute(Weather, "Wind.Speed"))
	{
		windSpeed = stf(Weather.Wind.Speed);
	}

	// Sky.RotateSpeed == 0.05
	Sky.RotateSpeed = windSpeed / 3000 / timeScale;
}

void FillSkyDir(aref aSky) // Mirsaneli: random skies + storm override only during day
{
    int i;
    string satr;
    aref aCurWeather = GetCurrentWeather();
    string sDir;

    DeleteAttribute(aSky, "Dir");

    if (iBlendWeatherNum < 0)
    {
        aSky.Dir.d1 = aCurWeather.Sky.Dir;
        aSky.Dir = GetHour();
    }
    else
    {
        // Randomly select a sky folder once per function call
        string selectedSkyFolder;
        switch (rand(3))  
        {
            case 0: selectedSkyFolder = "skies"; break;
            case 1: selectedSkyFolder = "skies1"; break;
            case 2: selectedSkyFolder = "skies2"; break;
            case 3: selectedSkyFolder = "skies3"; break;
        }

        for (i = 0; i < MAX_WEATHERS; i++)
        {
            if (!CheckAttribute(&Weathers[i], "Hour")) { continue; }
            if (CheckAttribute(&Weathers[i], "Skip") && sti(Weathers[i].Skip) == true) { continue; }
            if (CheckAttribute(&Weathers[i], "Storm") && sti(Weathers[i].Storm) == true) { continue; }

            satr = "d" + sti(Weathers[i].Hour.Min);
            if (satr == "d24") { continue; }

            // Convert hour to proper folder name
            int hourInt = makeint(GetHour()); 
            string hourStr;

            if (hourInt == 0)      { hourStr = "24"; }  
            else if (hourInt < 10) { hourStr = "0" + hourInt; }
            else                   { hourStr = "" + hourInt; }

            sDir = "weather\\" + selectedSkyFolder + "\\" + hourStr + "\\";

            // Assign sky normally first
            aSky.Dir.(satr) = sDir;

            // Override with storm sky only during daytime if it's raining
			if (CheckAttribute(&WeatherParams, "Rain.ThisDay") && sti(WeatherParams.Rain.ThisDay))
			{
				int hourMin = sti(Weathers[i].Hour.Min);
				if (hourMin >= 7 && hourMin <= 20) // Only override for 6h to 20h
				{
					aSky.Dir.(satr) = "weather\\skies\\Storm01\\";
				}
			}
        }

        aSky.Dir = GetTime();
    }
}

void Whr_SetSkyFogData( int _sky, int curTime, ref _fog)
{
	switch(_sky)
	{
		case 1 :
			switch(curTime)
			{
				case  0: _fog = argb(  0,  6, 13, 23);break;
				case  1: _fog = argb(  0,  5, 12, 19);break;
				case  2: _fog = argb(  0,  5, 12, 19);break;
				case  3: _fog = argb(  0,  3,  8, 15);break;
				case  4: _fog = argb(  0,  5, 13, 26);break;
				case  5: _fog = argb(  0, 29, 46, 54);break;
				case  6: _fog = argb(  0, 99, 74, 70);break;
				case  7: _fog = argb(  0,152,164,155);break;
				case  8: _fog = argb(  0,181,209,221);break;
				case  9: _fog = argb(  0,193,218,228);break;
				case 10: _fog = argb(  0,193,218,228);break;
				case 11: _fog = argb(  0,193,218,228);break;
				case 12: _fog = argb(  0,193,218,228);break;
				case 13: _fog = argb(  0,193,218,228);break;
				case 14: _fog = argb(  0,193,218,228);break;
				case 15: _fog = argb(  0,193,218,228);break;
				case 16: _fog = argb(  0,193,218,228);break;
				case 17: _fog = argb(  0,174,204,215);break;
				case 18: _fog = argb(  0,156,163,164);break;
				case 19: _fog = argb(  0, 98, 82, 76);break;
				case 20: _fog = argb(  0, 60, 54, 54);break;
				case 21: _fog = argb(  0,  7, 15, 23);break;
				case 22: _fog = argb(  0,  5, 12, 20);break;
				case 23: _fog = argb(  0,  6, 13, 21);break;
			}
		break;
		
		case 2 :
			switch(curTime)
			{
				case  0: _fog = argb(  0,  6, 14, 21);break;
				case  1: _fog = argb(  0,  6, 14, 21);break;
				case  2: _fog = argb(  0,  6, 14, 21);break;
				case  3: _fog = argb(  0,  5, 10, 17);break;
				case  4: _fog = argb(  0,  4,  9, 15);break;
				case  5: _fog = argb(  0, 29, 46, 54);break;
				case  6: _fog = argb(  0, 83, 90, 95);break;
				case  7: _fog = argb(  0,130,159,190);break;
				case  8: _fog = argb(  0,150,174,196);break;
				case  9: _fog = argb(  0,144,171,196);break;
				case 10: _fog = argb(  0,144,171,196);break;
				case 11: _fog = argb(  0,144,171,196);break;
				case 12: _fog = argb(  0,144,171,196);break;
				case 13: _fog = argb(  0,144,171,196);break;
				case 14: _fog = argb(  0,144,171,196);break;
				case 15: _fog = argb(  0,144,171,196);break;
				case 16: _fog = argb(  0,144,171,196);break;
				case 17: _fog = argb(  0,144,171,196);break;
				case 18: _fog = argb(  0,156,163,164);break;
				case 19: _fog = argb(  0,135,123,109);break;
				case 20: _fog = argb(  0, 38, 38, 37);break;
				case 21: _fog = argb(  0, 12, 18, 23);break;
				case 22: _fog = argb(  0,  9, 15, 21);break;
				case 23: _fog = argb(  0,  9, 15, 21);break;
			}		
		break;
		
		case 3 :
			switch(curTime)
			{
				case  0: _fog = argb(  0,  6, 14, 21);break;
				case  1: _fog = argb(  0,  6, 14, 21);break;
				case  2: _fog = argb(  0,  6, 14, 21);break;
				case  3: _fog = argb(  0,  5, 10, 17);break;
				case  4: _fog = argb(  0,  4,  9, 15);break;
				case  5: _fog = argb(  0, 29, 46, 54);break;
				case  6: _fog = argb(  0, 29, 46, 54);break;
				case  7: _fog = argb(  0,115,140,156);break;
				case  8: _fog = argb(  0,150,174,196);break;
				case  9: _fog = argb(  0,144,171,196);break;
				case 10: _fog = argb(  0,144,171,196);break;
				case 11: _fog = argb(  0,144,171,196);break;
				case 12: _fog = argb(  0,144,171,196);break;
				case 13: _fog = argb(  0,144,171,196);break;
				case 14: _fog = argb(  0,144,171,196);break;
				case 15: _fog = argb(  0,144,171,196);break;
				case 16: _fog = argb(  0,144,171,196);break;
				case 17: _fog = argb(  0,144,171,196);break;
				case 18: _fog = argb(  0,156,163,164);break;
				case 19: _fog = argb(  0, 41, 47, 69);break;
				case 20: _fog = argb(  0, 20, 26, 35);break;
				case 21: _fog = argb(  0, 12, 18, 23);break;
				case 22: _fog = argb(  0,  9, 15, 21);break;
				case 23: _fog = argb(  0,  9, 15, 21);break;
			}		
		break;		
	}
}

void MoveSkyToLayers(string sExecuteLayer, string sRealizeLayer)
{
	LayerDelObject("execute",&Sky);
	LayerDelObject("realize",&Sky);
	LayerDelObject(SEA_EXECUTE,&Sky);
	LayerDelObject(SEA_REALIZE,&Sky);

	//#20180615-01
	if(bSeaActive) {
        LayerAddObject(sExecuteLayer,&Sky,2);
        LayerAddObject(sRealizeLayer,&Sky,3);
	}
    else {
        LayerAddObject(sExecuteLayer,&Sky,12);
        LayerAddObject(sRealizeLayer,&Sky,13);
    }
}
