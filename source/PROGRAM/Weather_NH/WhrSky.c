#event_handler("frame", "UpdateSky");

object Sky;

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
	// Sky.Dir = Whr_GetString(aSky, "Dir");

	// Sky.Dir.d1 = aCurWeather.Sky.Dir;
	// Sky.Dir = GetHour();

	// if (wRain > 60)
	// {
	// 	Sky.Dir = "weather\skies\Storm01\";
	// }

	FillSkyData();
	// Sky.Color = Whr_GetColor(aSky, "Color");
	Sky.RotateSpeed = 0.05; // Warship 02.06.09
	Sky.Angle = Whr_GetFloat(aSky, "Angle");
	Sky.Size = 2048;

	//#20180615-01

    if(bSeaActive) {
        Sky.Size = 2048;
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

void FillSkyData()
{

	aref aSky; makearef(aSky,  currentWeather.Sky);

	float waveSpeedXf, waveSpeedZf, waveSpeed2Xf, waveSpeed2Zf;

	aref aSky2; makearef(aSky2, nextWeather.Sky);
	float fBlend = stf(Environment.Time) - sti(Environment.Time);

	Sky.Color =  Whr_BlendColor( fBlend, Whr_GetColor(aSky, "Color"), Whr_GetColor(aSky2, "Color") );

	int iHour = MakeInt(GetHour());
	int nextHour = iHour+1;
	if (nextHour > 23) {nextHour=0;}

	string satr = "d" + sti(iHour);
	aSky.Dir.(satr) = currentWeather.Sky.Dir;
	satr = "d" + sti(nextHour);
	aSky.Dir.(satr) = nextWeather.Sky.Dir;

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
	Sky.RotateSpeed = windSpeed / 2500 / timeScale;
}

void FillSkyDir(aref aSky)
{
// 	int i, nStart, nDur;
// 	string satr;
// 	aref aCurWeather = GetCurrentWeather();
// 	string sDir;

// 	DeleteAttribute(aSky,"Dir");
// 	if( iBlendWeatherNum < 0 )
// 	{
// 		aSky.Dir.d1 = aCurWeather.Sky.Dir;
// 		aSky.Dir = GetHour();
// 	} else {
// 		for (i=0;i<MAX_WEATHERS;i++)
// 		{
// 			if (!CheckAttribute(&Weathers[i], "Hour")) {continue;}
// 			if (CheckAttribute(&Weathers[i], "Skip") && sti(Weathers[i].Skip)==true) {continue;}
// 			if (CheckAttribute(&Weathers[i], "Storm")&& sti(Weathers[i].Storm)==true) {continue;}

// 			satr = "d" + sti(Weathers[i].Hour.Min);
// 			if( satr=="d24" ) {continue;}

// //navy -->
// 			sDir = Weathers[i].Sky.Dir;
// 			// trace("aSky.Dir.(satr) in fillskydir: " + sDir);
// //navy <--
// 			aSky.Dir.(satr) = sDir;
// 		}
// 		aSky.Dir = GetTime();
// 	}



	string satr;
	int i;

	for (i=0;i<24;i++){
		satr = "d" + i;

		if (i==23 || i==5) {
			aSky.Dir.(satr) = skydir_twilight1();
		}
		if (i==0 || i==4) {
			aSky.Dir.(satr) = skydir_twilight2();
		}
		if (i >= 6 && i <= 10 ) {
			aSky.Dir.(satr) = skydir_morningAFternoon();			
		}
		if (i >= 18 && i <= 22 ) {
			aSky.Dir.(satr) = skydir_morningAFternoon();			
		}
		if (i >= 11 && i <= 17 ) {
			aSky.Dir.(satr) = skydir_day();		
		}
		if (i >= 1 && i <= 3 ) {
			aSky.Dir.(satr) = skydir_night();
		}
	}

	aSky.Dir = GetTime();

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
