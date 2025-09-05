/////////////////////////
// NH Weather Port
/////////////////////////

#include "weather\WhrUtils.c"
#include "weather\WhrLightning.c"
#include "weather\WhrRain.c"
#include "weather\WhrSea.c"
#include "weather\WhrSky.c"
#include "weather\WhrSun.c"
#include "weather\WhrTornado.c"
#include "weather\WhrAstronomy.c"
#include "weather\WhrGeneration.c"
#include "weather\WhrSeaPresets.c"

#define WIND_NORMAL_POWER		20.0 // NK
#define MAX_WEATHERS   36

float fWeatherAngleOld, fWeatherSpeedOld;
int fogBallast, rainBallast, windBallast;
float windABallast;
int goldRain, goldFog, oldWind;
int gWeatherInit = 1;
int curTime, minwind, maxwind;
int wRain = 0;
int winds = 0;
int fog = 0;
int rWind, rRain, rFog;
float fWindA = 0.0;
float rWindA = 0.0;
float fSeaA;
float fSeaB;

// Values for overriding weather or setting it
// ----------------DO NOT CHANGE THESE VALUES HERE------------------------
float OWeatherAngle = -50.0;		 //Value between 0.0 and PIm2 - Determines the wind angle
float OWABallast = -50.0;			 //Value between 0.0 and the MAX defined in InternalSettings.h
int OFog = -50; 					 //Value between 0 and 20 - Determines fog density
int OFBallast = -50;				 //Value between 0 and the MAX defined in InternalSettings.h
int ORain = -50;					 //Value between 0 and 100 - Determines rain density and storm occurance
int ORBallast = -50;				 //Value between 0 and the MAX defined in InternalSettings.h
int OWind = -50;					 //Value between 0 and 30 - Determines the Wind speed
int OWBallast = -50;				 //Value between 0 and the MAX defined in InternalSettings.h
bool gWeatherOvrd = false;			 //This is the bool checked by the weather system, set to to if you've changed one of the above variables
//To set specific weather set the desired variables to the desired values in your code and set gWeatherOvrd to true the system takes care of the rest


object	Weather, WeatherParams, WhrCommonParams;
int		iNextWeatherNum = -1;
int		iCurWeatherNum = -1;
int		iBlendWeatherNum = -1;
int		iCurWeatherHour = -1;
bool	bCurWeatherStorm = false;
int		iTotalNumWeathers = 0;
string	sLightingPath = "day";
string	sLmLightingPath = "day";
string	sInsideBack = "";
string	sNewExecuteLayer, sNewRealizeLayer;
string	sCurrentFog;
float	fWeatherDelta = 0.0;
float	fWeatherAngle, fWeatherSpeed;
float	fFogDensity;
int		iShadowDensity[2];
int		iPrevWeather = -1;
int		sunIsShine = true;
bool	bWeatherLoaded = false;
bool	bWeatherIsNight = false;
bool	bWeatherIsLight = false;
bool	bWeatherIsRain = false;
bool	bWeatherIsStorm = false;
bool	Whr_IsFog() { return stf(WeathersNH.Fog.SeaDensity)>0.01; }

object Weathers[MAX_WEATHERS];
object WeathersNH;  // Variable to use in NH generation

extern int InitWeather();

#event_handler("EWhr_GetWindAngle", "Whr_GetWindAngle");
#event_handler("EWhr_GetWindSpeed", "Whr_GetWindSpeed");
#event_handler("EWhr_GetShadowDensity", "Whr_GetShadowDensity");
#event_handler("EWhr_GetFogDensity", "Whr_GetFogDensity");
#event_handler("WeatherTimeUpdate", "Whr_TimeUpdate" );

void SetNextWeather(string sWeatherID)
{
	string sWeather = sWeatherID;
	if (sWeatherID == "Blue Sky" || sWeatherID == "Moon Night" || sWeatherID == "Red Sky") sWeather = "Clear";
	if (sWeatherID == "Day Storm")								sWeather = "Heavy Storm";
	if (sWeatherID == "alcove") sWeather = "inside";

	switch (sWeather)
	{
	case "Clear":
		wRain = 0;
		ORain = 0;
		ORBallast = 0;
		Fog = 0;
		OFog = 0;
		gWeatherOvrd = true;	// LDH make new weather in CreateWeatherEnvironment 17Feb09
		break;

	case "Cloudy":
		wRain = 60;		// clouds start at 50, overcast starts at 65
		ORain = 60;		// clouds start at 50, overcast starts at 65
		gWeatherOvrd = true;
		sWeatherID = "21 Rain";
		break;

	case "Overcast":
		wRain = 70;		// overcast starts at 65, rain starts at 75
		ORain = 70;		// overcast starts at 65, rain starts at 75
		gWeatherOvrd = true;
		break;

	case "Rainy":
		wRain = 80;		// rain starts at 75, storm starts at 95
		ORain = 80;		// rain starts at 75, storm starts at 95
		gWeatherOvrd = true;
		break;

	case "Heavy Rain":
		wRain = 90;		// rain starts at 75, storm starts at 95
		ORain = 90;		// rain starts at 75, storm starts at 95
		gWeatherOvrd = true;
		break;

	case "Stormy":		// this produces lightning
		wRain = 97;		// storm starts at 95
		ORain = 97;		// storm starts at 95
		OWind = 25;		// twisters start at minwind >= 28
		gWeatherOvrd = true;
		break;

	case "Heavy Storm":	// this produces twisters, "Day Storm"
		wRain = 100;	// storm starts at 95
		ORain = 100;	// storm starts at 95
		ORBallast = 15;
		OWind = 30;		// twisters start at minwind >= 28
		OWBallast = 15;
		gWeatherOvrd = true;
		break;

	case "Foggy":
		Fog = 25;		// produces fog density of 0.00375
		OFog = 25;		// produces fog density of 0.00375
		gWeatherOvrd = true;
		break;

	case "Heavy Fog":
		Fog = 40;		// produces fog density of 0.00625
		OFog = 40;		// produces fog density of 0.00625
		gWeatherOvrd = true;
		break;

	case "Black Pearl Fight":
		wRain = 90;
		Fog = 25;
		OFog = 25;
		OWind = 25;
		gWeatherOvrd = true;
		break;

	case "IslaDeMuerte":
		Fog = 80;		// produces fog density of 0.02
		OFog = 80;		// produces fog density of 0.02
		gWeatherOvrd = true;
		break;

	case "Super Fog":
		Fog = 999;
		OFog = 999;
		gWeatherOvrd = true;
		break;

	}

	//Whr_Generator();

	// find weather
	iNextWeatherNum = -1;

	iCurWeatherNum = FindWeatherByHour(MakeInt(GetHour()));
	iBlendWeatherNum = FindBlendWeather( iCurWeatherNum );
	Whr_LoadNextWeather(0);
}

// call this with sDir = "" to use old wind direction
// call this with speed < 0 to use old wind speed
void SetNextWind(string sDir, int speed)
{
	int dir = -1;
	switch (sDir)
	{
	case "N":	dir =  0; break;
	case "NNE":	dir =  1; break;
	case "NE": 	dir =  2; break;
	case "ENE":	dir =  3; break;
	case "E":  	dir =  4; break;
	case "ESE":	dir =  5; break;
	case "SE": 	dir =  6; break;
	case "SSE":	dir =  7; break;
	case "S":  	dir =  8; break;
	case "SSW":	dir =  9; break;
	case "SW": 	dir = 10; break;
	case "WSW":	dir = 11; break;
	case "W":  	dir = 12; break;
	case "WNW":	dir = 13; break;
	case "NW": 	dir = 14; break;
	case "NNW":	dir = 15; break;
	}
	if (dir != -1)
	{
		OWeatherAngle = Degree2Radian(dir*22.5);
		gWeatherOvrd = true;
	}
	if (speed >= 0)
	{
		OWind = iclamp(5,30,speed);
		gWeatherOvrd = true;
	}
}

void WeatherInit()
{
	//DeleteAttribute(&WeatherParams,"");

	if (LoadSegment("weather\WhrInit.c"))
	{
		iTotalNumWeathers = InitWeather();
		UnloadSegment("weather\WhrInit.c");
	}
}

void DeleteWeatherEnvironment()
{
	iBlendWeatherNum = -1;
	if (isEntity(&Weather))
	{
		DeleteClass(&Weather);
	}
	DeleteAttribute(&Weather,"");
	//WeatherParams.Tornado = false;
	//DeleteAttribute(&WeatherParams,"");

	WhrDeleteRainEnvironment();
	WhrDeleteSkyEnvironment();
	WhrDeleteSunGlowEnvironment();
	WhrDeleteLightningEnvironment();
	WhrDeleteTornadoEnvironment();
	WhrDeleteSeaEnvironment();
	WhrDeleteAstronomyEnvironment();

	DelEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor");
	DelEventHandler("frame","Whr_OnWindChange");

	bWeatherLoaded = false;
}

aref GetCurrentWeather()
{
	//Boyer fix for when iCurWeatherNum = -1...borrowed from function Whr_LoadNextWeather(int nPlus)
	if (iCurWeatherNum < 0)
		iCurWeatherNum = iTotalNumWeathers - 1;

	//End fix
	aref arWeather;
	makearef(arWeather,Weathers[iCurWeatherNum]);

	return arWeather;
}

aref GetTempWeatherObj()
{
	aref arWeather;
	makearef(arWeather, WeathersNH);

	return arWeather;
}

void CreateWeatherEnvironment()
{
    pchar = GetMainCharacter();
    DeleteAttribute(&Weather,"");

	string sAttrName;
	string sSky = "";
	int iWeatherFound[MAX_WEATHERS];
	int iNumWeatherFound = 0;
	int iHour = MakeInt(GetHour());

	bool bWhrStorm = false;
	bool bWhrTornado = false;
	bool bRain = false;

	bWeatherIsStorm = false; // screwface
	bWeatherIsRain = false; // screwface
	Whr_Generator(iHour);

	if (CheckAttribute(&WeatherParams,"Storm")) { bWhrStorm = sti(WeatherParams.Storm); }
	if (CheckAttribute(&WeatherParams,"Tornado")) { bWhrTornado = sti(WeatherParams.Tornado); }

	//bWeatherIsStorm = false; // screwface
	//bWeatherIsRain = false; // screwface
	//Whr_Generator(iHour);
    //WeatherParams.Storm = false;
	//WeatherParams.Tornado = false;

	int iMonth = GetDataMonth();
	int iTmp; //, iChance;
	if (CheckAttribute(&WeatherParams,"Rain")) { bRain = sti(WeatherParams.Rain); }
	// --> Mirsaneli: rewritten rain logic
	if (!CheckAttribute(&WeatherParams, "Rain.ThisDay") || !sti(WeatherParams.Rain.ThisDay))
	{
		WeatherParams.Rain.ThisDay = false;

		int iChance = 0;

		// Higher rain chance in tropical months
		if (iMonth >= 5 && iMonth <= 9) {
			iChance = 30;  // Wet season
		} else {
			iChance = 15;  // Dry season
		}

		// Only allow rain to begin between 5 AM and 3 PM
		if (iHour >= 5 && iHour <= 15)
		{
			bool shouldRain = (rand(100) < iChance);
			if (shouldRain)
			{
				WeatherParams.Rain.ThisDay   = true;
				WeatherParams.Rain.StartTime = iHour + 2 + rand(2); // Starts 2-3 hours later
				WeatherParams.Rain.Duration  = 60 + rand(90);       // Duration in minutes (1-2.5 hours)

				// Log_TestInfo("Scheduled rain at hour: " + WeatherParams.Rain.StartTime);
				// Log_TestInfo("Rain duration (min): " + WeatherParams.Rain.Duration);
			}
		}
	}
	// <-- Mirsaneli: rewritten rain logic

	if (bRain)
	{
		iTmp = sti(WeatherParams.Rain.StartTime) + (sti(WeatherParams.Rain.Duration)/60 + 0.5);
		if (iHour > iTmp)
		{
			bRain = false;
			WeatherParams.Rain = false;
			WeatherParams.Rain.ThisDay = false;
		}
	}
//navy <-- Rain

if (iNextWeatherNum != -1)
	{
		if (iPrevWeather == -1) { iPrevWeather = iCurWeatherNum; }
		iCurWeatherHour = iHour;
		iCurWeatherNum = iNextWeatherNum;
		iNextWeatherNum = -1;
		//Trace("Weather: used preset weather " + iCurWeatherNum);
	}
	else
	{
		// search weather for hour
		for (int i=0;i<MAX_WEATHERS;i++)
		{
			//navy -->
			if (!bRain && sti(Weathers[i].Rain.NumDrops) > 0 && sti(Weathers[i].Rain.NumDrops) < 5100)
			{
				Weathers[i].Rain.NumDrops = 0;
				Weathers[i].Lightning.Enable = false;
			}
			if (CheckAttribute(&WeatherParams, "Rain.ThisDay") && !sti(WeatherParams.Rain.ThisDay) && CheckAttribute(&Weathers[i], "Bak"))
			{
				// Weathers[i].Fog.Color		= Weathers[i].Bak.Fog.Color;
				// Weathers[i].Fog.Height		= Weathers[i].Bak.Fog.Height;
				// Weathers[i].Fog.Density		= Weathers[i].Bak.Fog.Density;
				// Weathers[i].Fog.SeaDensity	= Weathers[i].Bak.Fog.SeaDensity;
				// Weathers[i].Fog.IslandDensity	= Weathers[i].Bak.Fog.IslandDensity;

				// Weathers[i].Sun.Glow.Enable		= Weathers[i].Bak.Sun.Glow.Enable;
				// Weathers[i].Sun.Overflow.Enable	= Weathers[i].Bak.Sun.Overflow.Enable;

				// DeleteAttribute(&Weathers[i], "Bak");
			}
			if (!bRain) Weathers[i].Rainbow.Enable = false;
			//navy <--
			if (!CheckAttribute(&Weathers[i], "hour")) { continue; }
			if (CheckAttribute(&Weathers[i], "skip"))
			{
				if (sti(Weathers[i].skip)) { continue; }
			}

			bool bCanStorm = sti(Weathers[i].Storm);
			bool bCanTornado = sti(Weathers[i].Tornado);
			int iMin = sti(Weathers[i].Hour.Min);
			int iMax = sti(Weathers[i].Hour.Max);
			if (iMin == iMax && iMin != iHour) { continue; }
			if (iMin > iMax)
			{
				if (iHour < iMin && iHour > iMax) { continue; }
			}
			if (iMin < iMax)
			{
				if (iHour < iMin || iHour > iMax) { continue; }
			}
			if (bWhrStorm != bCanStorm) { continue; }
			if (bWhrTornado == true && bWhrTornado != bCanTornado) { continue; }

			iWeatherFound[iNumWeatherFound] = i;
			iNumWeatherFound++;
		}
		iCurWeatherHour = iHour;

		if (iNumWeatherFound == 0)
		{
			Trace("Error: iNumWeatherFound = 0, for hour = " + iHour);
			iCurWeatherNum = 0;
		}
		else
		{
			iCurWeatherNum = iWeatherFound[rand(iNumWeatherFound-1)];
		}
	}
	int iCurLocation;
	int iTestWeather;
	bool bQuestlockWeather;
    float fGetTime = GetTime();

	bQuestlockWeather = false;
	sunIsShine = true;

	if(CheckAttribute(pchar, "location"))
	{
		iCurLocation = reload_location_index;
		if(iCurLocation != -1)
		{
			if(CheckAttribute(&locations[iCurLocation], "storm"))
			{
				bWhrStorm = 1;
			}
			if(CheckAttribute(&locations[iCurLocation], "tornado"))
			{
				bWhrTornado = 1;
			}
			if(CheckAttribute(&locations[iCurLocation], "alwaysStorm"))
			{
				if (fGetTime >= 6.0 && fGetTime < 10.0) locations[iCurLocation].QuestlockWeather = "Storm01_add";
				else { if (fGetTime >= 10.0 && fGetTime < 18.0) locations[iCurLocation].QuestlockWeather = "Storm02_add";
				else { if (fGetTime >= 18.0 && fGetTime < 22.0) locations[iCurLocation].QuestlockWeather = "Storm03_add";
				else { locations[iCurLocation].QuestlockWeather = "Storm04_add";
				}}}
				if (CheckAttribute(&locations[iCurLocation], "alwaysStorm.WaveHeigh")) locations[iCurLocation].MaxWaveHeigh = 2.5;
			}
			else { if(CheckAttribute(&locations[iCurLocation], "alwaysStorm_2")) //COAS escape
                {
                    if (fGetTime >= 6.0 && fGetTime < 10.0) locations[iCurLocation].QuestlockWeather = "Storm01";
                    else { if (fGetTime >= 10.0 && fGetTime < 18.0) locations[iCurLocation].QuestlockWeather = "Storm02";
                    else { if (fGetTime >= 18.0 && fGetTime < 22.0) locations[iCurLocation].QuestlockWeather = "Storm03";
                    else { locations[iCurLocation].QuestlockWeather = "Storm04";
                    }}}
                    if (CheckAttribute(&locations[iCurLocation], "alwaysStorm_2.WaveHeigh")) locations[iCurLocation].MaxWaveHeigh = 28.0; //40.0;
                }
			}
			if(CheckAttribute(&locations[iCurLocation], "QuestlockWeather"))
			{
				iTestWeather = FindWeather(locations[iCurLocation].QuestlockWeather);
				if(iTestWeather != -1)
				{
					iCurWeatherNum = iTestWeather;
					bQuestlockWeather = true;
					if (CheckAttribute(&locations[iCurLocation], "lockWeather") && locations[iCurLocation].lockWeather == "Inside")
					{
						sunIsShine = false;
					}
				}
			}
		}
		else
		{
			iCurLocation = FindIsland(pchar.location);
			if(iCurLocation != -1)
			{
				if(CheckAttribute(&Islands[iCurLocation], "storm"))
				{
					bWhrStorm = 1;
				}
				if(CheckAttribute(&Islands[iCurLocation], "tornado"))
				{
					bWhrTornado = 1;
				}
				if(CheckAttribute(&Islands[iCurLocation], "alwaysStorm"))
				{
					if (fGetTime >= 6.0 && fGetTime < 10.0) Islands[iCurLocation].QuestlockWeather = "Storm01";
					else { if (fGetTime >= 10.0 && fGetTime < 18.0) Islands[iCurLocation].QuestlockWeather = "Storm02";
					else { if (fGetTime >= 18.0 && fGetTime < 22.0) Islands[iCurLocation].QuestlockWeather = "Storm03";
					else { Islands[iCurLocation].QuestlockWeather = "Storm04";
					}}}
				}
				if(CheckAttribute(&Islands[iCurLocation], "QuestlockWeather"))
				{
					iTestWeather = FindWeather(Islands[iCurLocation].QuestlockWeather);
					if(iTestWeather != -1)
					{
						iCurWeatherNum = iTestWeather;
						bQuestlockWeather = true;
					}
				}
			}
		}
	}
	bWeatherIsStorm = bWhrStorm;
	bCurWeatherStorm = bWhrStorm;

	if (!bQuestlockWeather)
	{
		iBlendWeatherNum = FindBlendWeather(iCurWeatherNum);
	}
	else
	{
		iBlendWeatherNum = -1;
	}
	/*
	if (bMainMenu)
    {
        iTestWeather = sti(InterfaceStates.mainmenuweather);
        if(iTestWeather != -1)
        {
            iCurWeatherNum = iTestWeather;
            bQuestlockWeather = true;
        }
    }

	if (startGameWeather)
	{
		iTestWeather = sti(InterfaceStates.startGameWeather);
		if(iTestWeather != -1)
		{
			iCurWeatherNum = iTestWeather;
			bQuestlockWeather = true;
		}
		startGameWeather = false;
	}
	*/
	DeleteAttribute(&Weather,"");
	if (!isEntity(&Weather))
	{
		CreateEntity(&Weather, "Weather");
	}

    SetSunriseHours();

	aref aCurWeather = GetCurrentWeather();

	sLightingPath = Whr_GetString(aCurWeather,"Lighting");
	sLmLightingPath = Whr_GetString(aCurWeather,"LightingLm");
	sInsideBack = Whr_GetString(aCurWeather,"InsideBack");
	bWeatherIsNight = Whr_GetLong(aCurWeather,"Night");
	bWeatherIsLight = Whr_GetLong(aCurWeather,"Lights");
	Weather.Wind.Speed = Whr_GetFloat(aCurWeather,"Wind.Speed");
	pchar.wind.speed = Weather.Wind.Speed;

	Weather.Wind.Angle = Whr_GetLong(&WeathersNH, "Wind.Angle");
	sCurrentFog = "Fog";
	if (bSeaActive)
	{
		if (CheckAttribute(aCurWeather, "SpecialSeaFog")) { sCurrentFog = "SpecialSeaFog"; }
	}
	FillWeatherData(iCurWeatherNum, iBlendWeatherNum, true);
	//FillWeatherData(iCurWeatherNum, -1);

	// trace("CWE Weather density: " + Whr_GetFloat(Weather, "Fog.Density"));
	// trace("CWE Weather islandDensity: " + Whr_GetFloat(Weather, "Fog.IslandDensity"));
	// trace("CWE Weather SeaDensity: " + Whr_GetFloat(Weather, "Fog.SeaDensity"));
	// trace("CWE Weather color: " + Whr_GetLong(Weather, "Fog.Color"));

	if (iBlendWeatherNum < 0 || bQuestlockWeather)
	{
		Weather.Time.time = fGetTime;
		Weather.Time.speed = 350.0;
		Weather.Time.updatefrequence = 12;
	} else {
		Weather.Time.time = fGetTime;
		Weather.Time.speed = 450;
		Weather.Time.updatefrequence = 15;
		if (bSeaActive && !bAbordageStarted)
		{
			/*
			if (iArcadeSails == 1)
            {
                Weather.Time.speed = 250;
                Weather.Time.updatefrequence = 10;
            }
		*/
		}
		else
		{
			Weather.Time.speed = 350;
			Weather.Time.updatefrequence = 12;
		}
	}
	Weather.isDone = "";

	SetEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor",0);
	SetEventHandler("frame","Whr_OnWindChange",0);


	fFogDensity = stf(WeathersNH.Fog.Density);



	fWeatherDelta = 0.0;
	fWeatherAngle = stf(Weather.Wind.Angle);
	//fWeatherAngle = GetAngleY(stf(worldMap.WindX), stf(worldMap.WindZ));
	fWeatherSpeed = stf(Weather.Wind.Speed);

    // // boal -->
	bRain = true; // Whr_isRainEnable();
    string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);

	if (bCabinStarted) bRain = false;
	if(iLocation != -1)
	{
		ref rLoc;
		rLoc = &Locations[iLocation];

		if (CheckAttribute(rLoc, "environment.weather.rain") && !sti(rLoc.environment.weather.rain))
		{
			bRain = false;
		}
		//navy
		else {
			if (CheckAttribute(rLoc, "type"))
			{
				// ??? ?????????
				if(rLoc.type == "residence"
					|| rLoc.type == "tavern"
					|| rLoc.type == "house"
					|| rLoc.type == "shop"
					|| rLoc.type == "shipyard"
					|| rLoc.type == "church" )
				{
					//??? ?????
					bRain = false;
				}
			}
		}
	}
	//trace("bRain " + bRain);
	//trace("iLocation " + iLocation);
	//trace("bCabinStarted " + bCabinStarted);
	//trace("loadedlocation " + Locations[iLocation].id);
	//trace("loadedlocation " + Locations[iLocation].type);
	if (bRain)
	{
		WhrCreateRainEnvironment();
	}
	else
	{
		ClearRainEnvironment();
	}

	WhrCreateSunGlowEnvironment();
	WhrCreateLightningEnvironment();
	WhrCreateAstronomyEnvironment();
	WhrCreateSkyEnvironment();
	WhrCreateSeaEnvironment();

	// if(iLocation != -1)
	// {
	// 	if(CheckAttribute(&Locations[iLocation], "lockWeather"))
	// 	{
	// 		bWhrTornado = false;
	// 	}
	// }
	if (bWhrTornado) { WhrCreateTornadoEnvironment(); }

	Particles.windpower = 0.025 * Clampf(Whr_GetWindSpeed() / WIND_NORMAL_POWER);
	Particles.winddirection.x = sin(Whr_GetWindAngle());
	Particles.winddirection.z = cos(Whr_GetWindAngle());

	bWeatherLoaded = true;
	// PB: Only show this if you've actually got a compass -->
	// FlayedOne
	bool ShowWindLog = false;
	string logstr = "";
	string compasstype = CheckCharacterEquipByGroup(pchar, COMPASS_ITEM_TYPE);
	if (winds == 0)			logstr = TranslateString("", "The air is calm");
	if (winds > 0 && winds <= 2)	logstr = TranslateString("", "There are light airs");
	if (winds > 2 && winds <= 6)	logstr = TranslateString("", "There is a light breeze");
	if (winds > 6 && winds <=10)	logstr = TranslateString("", "There is a gentle breeze");
	if (winds >10 && winds <=15)	logstr = TranslateString("", "There is a moderate breeze");
	if (winds >15 && winds <=20)	logstr = TranslateString("", "There is a fresh breeze");
	if (winds >20 && winds <=27)	logstr = TranslateString("", "There is a strong breeze");
	if (winds >27)			logstr = TranslateString("", "There is a near gale");

	if (winds>0)
	{
		switch (compasstype)
		{
			case "compass1":
				switch(LanguageGetLanguage())
				{
					case "Russian":
						logstr = TranslateString("", "wind_from_the") + " " + TranslateString("", GetCompassDirFromHeading16(fWindA + Degree2Radian(180.0))) + " " + logstr;
					break;
					logstr = logstr + " " + TranslateString("wind_from_the", GetCompassDirFromHeading16(fWindA + Degree2Radian(180.0)));
				}
			break;
			case "compass2":
				switch(LanguageGetLanguage())
				{
					case "Russian":
						logstr = TranslateString("", "wind_from_the") + " " + TranslateString("", GetCompassDirFromHeading16(fWindA + Degree2Radian(180.0))) + " " + TranslateString("", "Wind is from the") + " " + TranslateString("", "wind_at") + " " +  winds + " " + TranslateString("", "kts");
					break;
					logstr = TranslateString("Wind is from the", "") + " " + TranslateString(GetCompassDirFromHeading16(fWindA + Degree2Radian(180.0)), "") + " " + TranslateString("", "wind_at") + " " + winds + " " + TranslateString("", "kts");
				}
			break;
			case "compass3":
				switch(LanguageGetLanguage())
				{
					case "Russian":
						logstr = TranslateString("", "wind_from_the") + " " + TranslateString("", GetCompassDirFromHeading16(fWindA + Degree2Radian(180.0))) + " " + TranslateString("", "Wind is from the") + " " + TranslateString("", "wind_at") + " " +  winds + " " + TranslateString("", "kts");
					break;
					logstr = TranslateString("Wind is from the", "") + " " + TranslateString(GetCompassDirFromHeading16(fWindA + Degree2Radian(180.0)), "") + " " + TranslateString("", "wind_at") + " " + winds + " " + TranslateString("", "kts");
				}
			break;
			// In Russian translation, "Wind is from the" translates to "wind"
		}
	}
	if(bSeaActive && compasstype == "")			ShowWindLog = true;
	if(CheckAttribute(PChar, "skipWeatherLogs"))		ShowWindLog = false;
	if(ShowWindLog)						LogIt(logstr);
	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = WeathersNH.Fog.IslandDensity;
		Sea.Fog.SeaDensity = WeathersNH.Fog.SeaDensity;
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(WeathersNH.Fog.IslandDensity));
	}
	//Trace("Whr: Select id = " + aCurWeather.id);
}

void Whr_UpdateWeather(bool reinit_weather) // NK 04-09-21
{
	// LDH cleanup 16Feb09
//	Traceandlog("Whr_UpdateWeather start weather update " + "Time: " + GetStringTime(GetTime()) +" reinit: " +reinit_weather);	// LDH 05Sep06 trace for CTD

	if(reinit_weather) { //#20220311-01
        WeatherInit(); // NK 04-09-21
        CreateWeatherEnvironment();
        MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
	}

	//trace("Whr_UpdateWeather finish weather update");

	if(bSeaActive && !ownDeckStarted())
	{
		Sea.Sea2.Transparency = 0;
		PlayStereoSound("nature\wind_sea4.wav"); // squall i.e. weatherchange
		DirectsailCheck(true);	//  triggers change to other island and ship encounters, necessary to run here
	}
}

void Whr_LoadNextWeather(int nPlus)
{
	if (!isEntity(&Weather)) { return; }
	//WeatherInit();

	iCurWeatherHour = MakeInt(GetHour());
	iCurWeatherNum = iCurWeatherNum + nPlus;

	if (iCurWeatherNum < 0)
	{
		iCurWeatherNum = iTotalNumWeathers - 1;
	}
	if (iCurWeatherNum >= iTotalNumWeathers)
	{
		iCurWeatherNum = 0;
	}
	if (CheckAttribute(&Weathers[iCurWeatherNum], "Skip"))
	{
		if (sti(Weathers[iCurWeatherNum].skip))
		{
			Whr_LoadNextWeather(nPlus);
			return;
		}
	}
	// Log_TestInfo("Weather ID: " + Weathers[iCurWeatherNum].id + " Lighting: " + Weathers[iCurWeatherNum].Lighting);
	// Log_TestInfo("Sun: HeightAngle: " + Weathers[iCurWeatherNum].Sun.HeightAngle);

	iNextWeatherNum = iCurWeatherNum;
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);

	//aref aCurWeather = GetCurrentWeather();
	//iCurWeatherHour = sti(aCurWeather.Hour.Min);

	//SetCurrentTime(iCurWeatherHour, 0);
	Weather.Time.time = GetTime();
}

void Whr_OnWindChange()
{
	//creates the constant minor wind fluctuations
	float fDeltaTime = MakeFloat(GetDeltaTime()) * 0.001;
	fWeatherDelta = fWeatherDelta + fDeltaTime;

	float fSpd = fWeatherSpeed + (fWeatherSpeed / 6.0) * 0.1 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));
	float fAng = fWeatherAngle + 0.02 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));

	WeathersNH.Wind.Angle = fAng;
	WeathersNH.Wind.Speed = fSpd;
}

int Whr_OnCalcFogColor()
{
    int iAlpha, iColor;
    float x, y, z;

    x = GetEventData();
    y = GetEventData();
    z = GetEventData();

    int iFogColor = sti(Weather.Fog.Color);
    
    // Adjust alpha based on fog height or special conditions
    if (iBlendWeatherNum < 0)
    {
        iAlpha = 255 - MakeInt(255.0 * Clampf(y / stf(WeathersNH.SpecialSeaFog.Height)));
    }
    else
    {
        float fBlend = stf(Environment.time) - sti(Environment.time);
        float fH = Whr_BlendFloat(fBlend, stf(Weathers[iCurWeatherNum].(sCurrentFog).Height), stf(Weathers[iBlendWeatherNum].(sCurrentFog).Height));

        iAlpha = 255 - MakeInt(255.0 * Clampf(y / fH));
    }

    iAlpha = iAlpha * 1.4;  // Mirsaneli: Darkens the fog alpha and fixes distand islands that looked like flying above the sea

    // Ensure the alpha is within the valid range (0-255)
    iAlpha = clamp(iAlpha, 0, 255);

    // Adjust the final color based on the fog color and the alpha value
    iColor = or(shl(iAlpha, 24), iFogColor);
    return iColor;
}

float Whr_BlendFloat(float fBlend, float f1, float f2)
{
	float f = f1 + fBlend * (f2-f1);
	return f;
}

int Whr_BlendLong(float fBlend, int i1, int i2)
{
	int i = makeint(i1 + fBlend * (i2-i1));
	return i;
}

// Define the clamp function
int clamp(int value, int min, int max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

int Whr_BlendColor(float fBlend, int col1, int col2)
{
    int a1 = shr(and(col1, 4278190080), 24); // get alpha 1
    int a2 = shr(and(col2, 4278190080), 24); // get alpha 2
	
    int r1 = shr(and(col1, 16711680), 16);   // get red color 1
    int r2 = shr(and(col2, 16711680), 16);   // get red color 2

    int g1 = shr(and(col1, 65280), 8);       // get green color 1
    int g2 = shr(and(col2, 65280), 8);       // get green color 2

    int b1 = and(col1, 255);                 // get blue color 1
    int b2 = and(col2, 255);                 // get blue color 2

    int r = r1 + MakeInt(fBlend * (r2 - r1));
    int g = g1 + MakeInt(fBlend * (g2 - g1));
    int b = b1 + MakeInt(fBlend * (b2 - b1));
    int a = a1 + MakeInt(fBlend * (a2 - a1));

    // **Night-time dimming (gradual darkening instead of a hard cut)**
    float nightFactor = 1.0;
    if (iCurWeatherHour >= 18 && iCurWeatherHour <= 23) { // Sunset to Midnight
        nightFactor = 0.8 - ((iCurWeatherHour - 18) / 6.0) * 0.4; // Darkens up to 40% at midnight
    } 
    else if (iCurWeatherHour >= 0 && iCurWeatherHour < 6) { // Midnight to Dawn
        nightFactor = 0.6 + ((iCurWeatherHour) / 6.0) * 0.4; // Gradually lightens back up
    }

    r = r * nightFactor;
    g = g * nightFactor;
    b = b * nightFactor;
    a = a * nightFactor;

    // Ensure valid range (0-255)
    r = clamp(r, 0, 255);
    g = clamp(g, 0, 255);
    b = clamp(b, 0, 255);
    a = clamp(a, 0, 255);

    return argb(a, r, g, b);
}

void Whr_TimeUpdate()
{
	float fTime = GetEventData();
	//float fBlend = fTime - makeint(fTime);
	//
	//int nOldDay = GetDataDay();
	float oldTime = stf(Environment.time);
	int nOldHour = sti(Environment.date.hour);
	Environment.time = fTime;
	int nNewHour = makeint(fTime);
	int nNewMin = makeint((fTime - nNewHour)*60);
	int nNewSec = makeint(((fTime - nNewHour)*60 - nNewMin)*60);
	int nTimeR = GetTimeScale();
	if (nTimeR > 3) {
        if (nTimeR > 10) {
            oldTime -= 0.2;
        }
        else {
            if(nTimeR > 5) {
                oldTime -= 0.1;
            }
            else {
                oldTime -= 0.05;
            }
        }
        nOldHour = makeint(oldTime);
	}
	Environment.date.min = nNewMin;
	Environment.date.hour = nNewHour;
	Environment.date.sec = nNewSec;
	worldMap.date.hour = nNewHour;
	worldMap.date.min  = nNewMin;
	if( nNewHour < nOldHour )
	{
		AddDataToCurrent(0,0,1,true);
		Weather.Time.time = GetTime();
	} // to_do CalcLocalTime
    if( iBlendWeatherNum < 0 ) {return;}
	//navy --> Rain
	string sTmp;
	int iTmp, iTime;
	bool bRain = false;
	if (CheckAttribute(&WeatherParams,"Rain")) { bRain = sti(WeatherParams.Rain); }
	//navy <-- Rain
	aref oldWeather = GetCurrentWeather();
	bool isLagoon = CheckAttribute(oldWeather, "Sea.inlagoon");
	iCurWeatherNum = FindWeatherByHour( makeint(fTime) );
	iBlendWeatherNum = FindBlendWeather( iCurWeatherNum );

	if( iBlendWeatherNum < 0 ) {return;}

	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = WeathersNH.Fog.IslandDensity;
		Sea.Fog.SeaDensity = WeathersNH.Fog.SeaDensity;
	}
	//navy --> Rain
	bool  bIsRainEnable = Whr_isRainEnable();

	if (bIsRainEnable)
	{
		if (bRain)
		{
			int nRainDuration = sti(WeatherParams.Rain.Duration);
			iTmp = 3;

			iTime = GetQuestPastMinutesParam("Rain.Duration");
			if (iTime > nRainDuration)
			{
				iTmp = 3;
				bRain = false;
			}
			if (iTime < (4*nRainDuration/5))
			{
				iTmp = 2;
			}
			if (iTime < (2*nRainDuration/3))
			{
				iTmp = 1;
			}
			if (iTime < (nRainDuration/3))
			{
				iTmp = 0;
			}
			// Log_TestInfo("Is Raining...");
			switch (iTmp)
			{
				case 0:
					WeatherParams.Rain.Sound = true;
					break;
				case 1:
					if (rand(100) < 40)
					{
						// Log_TestInfo("Starting the Lightning...");
						Weathers[iCurWeatherNum].Lightning.Enable = true;
						Weathers[iCurWeatherNum].Lightning.SubTexX = 4;
						Weathers[iCurWeatherNum].Lightning.SubTexY = 1;
						Weathers[iCurWeatherNum].Lightning.ScaleX = 0.7;
						Weathers[iCurWeatherNum].Lightning.ScaleY = 1.0;
						Weathers[iCurWeatherNum].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";
					}
					break;
				case 2:
					break;
				case 3:
					if (CheckAttribute(&WeatherParams, "Rain.Sound") && sti(WeatherParams.Rain.Sound))
					{
						WeatherParams.Rain = false;
						WeatherParams.Rain.Sound = false;
						Whr_SetRainSound(false, sti(Weathers[iCurWeatherNum].Night));
						Weathers[iCurWeatherNum].Lightning.Enable = false;
						if (nNewHour > 5 && nNewHour < 20) //navy -- 5.03.07
						{
							Weathers[iCurWeatherNum].Rainbow.Enable = true;
						}

						DeleteAttribute(&WeatherParams, "Rain.StartTime");
					}
					WeatherParams.Rain.ThisDay = false;
					break;
			}
			if (iTmp != 0)
			{
				Weathers[iCurWeatherNum].Rain.NumDrops = 3500 + rand(1500);
				Weathers[iCurWeatherNum].Rain.DropLength = 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color = argb(0,23,23,23);
			}
			if (iTmp != 3)
			{
				Weathers[iBlendWeatherNum].Rain.NumDrops = 3500 + rand(1500);
				Weathers[iBlendWeatherNum].Rain.DropLength = 4 + rand(8);
				Weathers[iBlendWeatherNum].Rain.Color = argb(0,23,23,23);

				if (!CheckAttribute(&Weathers[iBlendWeatherNum], "Bak"))
				{
					Weathers[iBlendWeatherNum].Bak.Fog.Color		= Weathers[iBlendWeatherNum].Fog.Color;
					Weathers[iBlendWeatherNum].Bak.Fog.Height		= Weathers[iBlendWeatherNum].Fog.Height;
					Weathers[iBlendWeatherNum].Bak.Fog.Density		= Weathers[iBlendWeatherNum].Fog.Density;
					Weathers[iBlendWeatherNum].Bak.Fog.SeaDensity	= Weathers[iBlendWeatherNum].Fog.SeaDensity;
					Weathers[iBlendWeatherNum].Bak.Fog.IslandDensity	= Weathers[iBlendWeatherNum].Fog.IslandDensity;

					Weathers[iBlendWeatherNum].Bak.Sun.Glow.Enable		= Weathers[iBlendWeatherNum].Sun.Glow.Enable;
					Weathers[iBlendWeatherNum].Bak.Sun.Overflow.Enable	= Weathers[iBlendWeatherNum].Sun.Overflow.Enable;
				}
				Weathers[iBlendWeatherNum].Fog.Color = argb(0,50,60,65);
				Weathers[iBlendWeatherNum].Fog.Height = 1000;
				Weathers[iBlendWeatherNum].Fog.Density = 0.003;
				Weathers[iBlendWeatherNum].Fog.SeaDensity = 0.0022;
				Weathers[iBlendWeatherNum].Fog.IslandDensity = 0.0015;

				Weathers[iBlendWeatherNum].Sun.Glow.Enable = false;
				Weathers[iBlendWeatherNum].Sun.Overflow.Enable = false;
			}
		}
		else
		{
			if (CheckAttribute(&WeatherParams, "Rain.ThisDay") && sti(WeatherParams.Rain.ThisDay) && sti(WeatherParams.Rain.StartTime) <= nOldHour)
			{
				Weathers[iBlendWeatherNum].Rain.NumDrops = 2000 + rand(3000);
				Weathers[iBlendWeatherNum].Rain.DropLength = 2 + rand(10);
				Weathers[iBlendWeatherNum].Rain.Color = argb(0,23,23,23);

				if (!CheckAttribute(&Weathers[iBlendWeatherNum], "Bak"))
				{
					Weathers[iBlendWeatherNum].Bak.Fog.Color		= Weathers[iBlendWeatherNum].Fog.Color;
					Weathers[iBlendWeatherNum].Bak.Fog.Height		= Weathers[iBlendWeatherNum].Fog.Height;
					Weathers[iBlendWeatherNum].Bak.Fog.Density		= Weathers[iBlendWeatherNum].Fog.Density;
					Weathers[iBlendWeatherNum].Bak.Fog.SeaDensity	= Weathers[iBlendWeatherNum].Fog.SeaDensity;
					Weathers[iBlendWeatherNum].Bak.Fog.IslandDensity	= Weathers[iBlendWeatherNum].Fog.IslandDensity;

					Weathers[iBlendWeatherNum].Bak.Sun.Glow.Enable		= Weathers[iBlendWeatherNum].Sun.Glow.Enable;
					Weathers[iBlendWeatherNum].Bak.Sun.Overflow.Enable	= Weathers[iBlendWeatherNum].Sun.Overflow.Enable;
				}
				Weathers[iBlendWeatherNum].Fog.Color = argb(0,50,60,65);
				Weathers[iBlendWeatherNum].Fog.Height = 1000;
				Weathers[iBlendWeatherNum].Fog.Density = 0.003;
				Weathers[iBlendWeatherNum].Fog.SeaDensity = 0.0022;
				Weathers[iBlendWeatherNum].Fog.IslandDensity = 0.0015;

				Weathers[iBlendWeatherNum].Sun.Glow.Enable = false;
				Weathers[iBlendWeatherNum].Sun.Overflow.Enable = false;

				SaveCurrentQuestDateParam("Rain.Duration");
				WeatherParams.Rain = true;
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));
				Log_TestInfo("Rain Started");
			}
		}
	}
	//navy <-- Rain
	if( nNewHour != nOldHour )
	{
	    if (isLagoon) {
            DeleteAttribute(oldWeather, "Sea.inlagoon");
            Weathers[iCurWeatherNum].Sea.inlagoon = 1;
	    }
		Whr_UpdateWeatherHour();
		FillWeatherData(iCurWeatherNum, iBlendWeatherNum, true);
		// Add for transparent water in ports/beaches
		if (IsEntity(&objLandInterface)) {		// Mirsaneli: repeat this from locations.loader.c to keep the previous hour parameters
			Sea.MaxSeaHeight = 1.2;
			Sea.Sea2.Transparency = 0.2;
			//Sea.Sea2.LodScale = 1.0; //0.22;
			//Sea.Sea2.GridStep = 0.0375; //0.07
			Sea.Sea2.PosShift = 0.005;
			Sea.Sea2.Amp1 = 1.5; //1.0
			Sea.Sea2.Scale1 = 2.50; //2.0
			Sea.Sea2.Amp2 = 0.02;
			Sea.Sea2.Scale2 = 7.0; //11.0
			Sea.Sea2.AnimSpeed1 = 0.003;
			Sea.Sea2.MoveSpeed1 = "0.6, 0.0, 0.003";
			Sea.Sea2.AnimSpeed2 = 0.002;
			Sea.Sea2.MoveSpeed2 = "0.7, 0.0, 0.003";
		}
	}
	else {
        // update weather: sun lighting
        FillWeatherData(iCurWeatherNum, iBlendWeatherNum, false);
	}
	Weather.isDone = "";

	//update rain: rain drops, rain colors, rain size, rainbow
	//navy -- 5.03.07
	if (bIsRainEnable)
	{
		FillRainData(iCurWeatherNum, iBlendWeatherNum);
		Rain.isDone = "";
	}
	// update sun glow: sun\moon, flares
	WhrFillSunGlowData(iCurWeatherNum, iBlendWeatherNum);
	SunGlow.isDone = true;

	// update sky: fog
	Sky.TimeUpdate = fTime;
}

#event_handler("eChangeDayNight", "eChangeDayNight");

void Whr_UpdateWeatherHour() // Mirsaneli: rewritten Whr_UpdateWeatherHour for FillSkyDir randomizers
{
    bool bOldIsDay = Whr_IsDay();
    bool doLightChange = false;
    int i, iCharIdx;

    Whr_addWaves2weather(&Sea);

    bWeatherIsLight = Whr_GetLong(&Weathers[iCurWeatherNum], "Lights");
    bWeatherIsNight = Whr_GetLong(&Weathers[iCurWeatherNum], "Night");

    aref aCurWeather = GetCurrentWeather();
    aref aStars;
    makearef(aStars, aCurWeather.Stars);
    FillStars(aStars);
    Astronomy.isDone = true;
    Astronomy.TimeUpdate = 1;

    if (Whr_IsDay() != bOldIsDay)
    {
        Whr_ChangeDayNight();
        Event("eChangeDayNight");
        doLightChange = true;
    }

    if (bSeaActive && !bAbordageStarted)
    {
        bool isSeaEnt = IsEntity(&Sea);

        Whr_WindChange();

        int islandIdx = FindIsland(pchar.location);
        if (islandIdx != -1 && isSeaEnt)
        {
            if (stf(Sea.MaxSeaHeight) != SetMaxSeaHeight(islandIdx))
            {
                string sPreset = WhrGetSeaPresetFromWind(fWeatherSpeed);
                WhrSetSeaPreset(iCurWeatherNum, sPreset, fWeatherSpeed);
                WhrCreateSeaEnvironment();
            }
        }

        if (doLightChange && isSeaEnt) {
            doShipLightChange(aCurWeather);
        }
    }

    // **Ensure sky update happens only once per hour**
    int currentHour = makeint(GetHour()); 

    if (lastSkyUpdateHour != currentHour) 
    {
        lastSkyUpdateHour = currentHour; // Store last updated hour

        // **Ensure sky update happens!**
        aref aSky;
        makearef(aSky, aCurWeather.Sky);
        FillSkyDir(aSky);
        aCurWeather.Sky.Dir = aSky.Dir;

        // **Force Weather Refresh**
        Whr_LoadNextWeather(aCurWeather);

        trace("Updated sky directory: " + aCurWeather.Sky.Dir);
    }
}

void doShipLightChange(ref aCurWeather)
{
    int j, iCharIdx;

    ref rChar;
    Sea.Lights = aCurWeather.Lights;
    for(j = 0; j < iNumShips; j++) {
        iCharIdx = Ships[j];
        if (iCharIdx < 0 || iCharIdx >= TOTAL_CHARACTERS) continue;
        rChar = GetCharacter(Ships[j]);
        Ship_SetLightsAndFlares(rChar);
        SendMessage(&characters[iCharIdx], "l", MSG_SHIP_LIGHTSRESET);
    }
}

void Whr_ChangeDayNight()
{
	int loadLocationIndex = FindLoadedLocation();
	if( loadLocationIndex >= 0 )
	{
		LocationSetLights(&Locations[loadLocationIndex]);
		if( Whr_IsDay() )
		{
			SendMessage( &Locations[loadLocationIndex], "ls", MSG_LOCATION_EX_MSG, "DelFlys" );
		}
	}
}

void FillWeatherData(int nw1, int nw2, bool updateFog)
{
	if( nw1<0 || nw1>=MAX_WEATHERS ) {return;}

	string sCurFog = Whr_GetCurrentFog();
	if( nw2<0)
	{
        if (updateFog) {
            Weather.Fog.Enable = Whr_GetLong(&WeathersNH, sCurFog + ".Enable");
            Weather.Fog.Start = Whr_GetFloat(&WeathersNH, sCurFog + ".Start");
			Weather.Fog.Height = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Height");
            Weather.Fog.Density = Whr_GetFloat(&WeathersNH, sCurFog + ".Density");
            Weather.Fog.Color = Whr_getCurrentBlendedFogColor();
            Weather.Fog.IslandDensity = Whr_GetFloat(&WeathersNH, "Fog.IslandDensity");
            Weather.Fog.SeaDensity = Whr_GetFloat(&WeathersNH, sCurFog + ".SeaDensity");
        }

		Weather.Sun.Color = Whr_GetColor(&Weathers[nw1],"Sun.Color");
		Weather.Sun.HeightAngle = Whr_GetFloat(&Weathers[nw1],"Sun.HeightAngle");
		Weather.Sun.AzimuthAngle = Whr_GetFloat(&Weathers[nw1],"Sun.AzimuthAngle");
		Weather.Sun.Ambient = Whr_GetColor(&Weathers[nw1],"Sun.Ambient");
		Sky.Color = Whr_GetColor(&Weathers[nw1], "Sky.Color");
	}
	else
	{
		float fBlend = stf(Environment.Time) - sti(Environment.Time);

        if (updateFog) {
            Weather.Fog.Enable = Whr_GetLong(&WeathersNH, sCurFog + ".Enable");
            Weather.Fog.Start = Whr_BlendFloat( fBlend, Whr_GetFloat(&WeathersNH, sCurFog + ".Start"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Start") );
            Weather.Fog.Density = Whr_BlendFloat( fBlend, Whr_GetFloat(&WeathersNH, sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Density") );
            Weather.Fog.Color = Whr_BlendColor( fBlend, Whr_getCurrentBlendedFogColor(), Whr_GetColor(&Weathers[nw2], sCurFog + ".Color") );
            Weather.Fog.IslandDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(&WeathersNH, "Fog.IslandDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".IslandDensity") );
            Weather.Fog.SeaDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(&WeathersNH, sCurFog + ".SeaDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".SeaDensity") );
			Weather.Fog.Height = Whr_BlendFloat( fBlend, Whr_GetFloat(&WeathersNH, sCurFog + ".Height"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Height") );
        }
		Weather.Sun.Color = Whr_BlendColor( fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Color"), Whr_GetColor(&Weathers[nw2],"Sun.Color") );
		Weather.Sun.HeightAngle = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1],"Sun.HeightAngle"), Whr_GetFloat(&Weathers[nw2],"Sun.HeightAngle") );
		Weather.Sun.AzimuthAngle = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1],"Sun.AzimuthAngle"), Whr_GetFloat(&Weathers[nw2],"Sun.AzimuthAngle") );
		Weather.Sun.Ambient = Whr_BlendColor( fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Ambient"), Whr_GetColor(&Weathers[nw2],"Sun.Ambient") );
		Sky.Color = Whr_BlendColor( fBlend, Whr_GetColor(&Weathers[nw1],"Sky.Color"), Whr_GetColor(&Weathers[nw2],"Sky.Color") );
	}
	Whr_addwind2weather(&Weather);
    //arWeather.Lightning.Enable = false;
    Whr_addRain2weather(&Weather);
    //Whr_addfog2weather(&Weather);
    //Whr_addWaves2weather(&Sea);
}

int FindWeatherByHour(int nHour)
{
	// trace("getting weather by hour.  Stormy sky: " + WeathersNH.StormSky);
	for (int n=0; n<MAX_WEATHERS; n++)
	{
		if (!CheckAttribute(WeathersNH, "StormSky") || WeathersNH.StormSky==false){
			// trace("Calm weather");
			if (!CheckAttribute(&Weathers[n], "hour")) {continue;}
			if (CheckAttribute(&Weathers[n], "skip") && sti(Weathers[n].skip)==true) {continue;}
			if (CheckAttribute(&Weathers[n], "Storm") && sti(Weathers[n].Storm)==true) {continue;}
			if( sti(Weathers[n].hour.min) == nHour ) {return n;}

		}else{
			// trace("Stormy weather");
			if (CheckAttribute(&Weathers[n], "Storm") && sti(Weathers[n].Storm)==false) {continue;}
			if (sti(Weathers[n].hour.min) > sti(Weathers[n].hour.max))
			{
				if (nHour < sti(Weathers[n].hour.min) && nHour > sti(Weathers[n].hour.max)) {return n;}
			}
			if (sti(Weathers[n].hour.min) < sti(Weathers[n].hour.max))
			{
				if (nHour < sti(Weathers[n].hour.min) || nHour > sti(Weathers[n].hour.max)) {return n;}
			}
		}
	}
	return -1;
}

int FindBlendWeather(int iWeatherNum)
{
	if( iWeatherNum<0 || iWeatherNum>=MAX_WEATHERS ) {return -1;}

	if( !CheckAttribute(&Weathers[iWeatherNum], "hour") ) {return -1;}
	if( CheckAttribute(&Weathers[iWeatherNum],"Storm") && sti(Weathers[iWeatherNum].Storm)==true ) {return -1;}
	if( CheckAttribute(&Weathers[iWeatherNum],"skip") && sti(Weathers[iWeatherNum].skip)==true ) {return -1;}

	int nBlendWeatherHour = sti(Weathers[iWeatherNum].hour.min) + 1;
	if( nBlendWeatherHour>=24 ) {nBlendWeatherHour = 0;}

	return FindWeatherByHour(nBlendWeatherHour);
}

void CreateWeather(string sExecuteLayer, string sRealizeLayer)
{
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sExecuteLayer, sRealizeLayer);
}

void DeleteWeather()
{
	DeleteWeatherEnvironment();
}

void MoveWeatherToLayers(string sExecuteLayer, string sRealizeLayer)
{
	LayerDelObject("execute",&Weather);
	LayerDelObject("realize",&Weather);
	LayerDelObject(SEA_EXECUTE,&Weather);
	LayerDelObject(SEA_REALIZE,&Weather);

	sNewExecuteLayer = sExecuteLayer;
	sNewRealizeLayer = sRealizeLayer;

	LayerAddObject(sExecuteLayer,&Weather,1000000);
	LayerAddObject(sRealizeLayer,&Weather,65530);

	MoveRainToLayers(sExecuteLayer, sRealizeLayer);
	MoveLightningToLayers(sExecuteLayer, sRealizeLayer);
	MoveSkyToLayers(sExecuteLayer, sRealizeLayer);
	MoveSunGlowToLayers(sExecuteLayer, sRealizeLayer);
	MoveAstronomyToLayers(sExecuteLayer, sRealizeLayer);
}

float Whr_GetFogDensity() { return fFogDensity; }

float Whr_GetWindAngle()
{
	if (!CheckAttribute(&Weather,"Wind.Angle")) { return 0.0; }
	return stf(Weather.Wind.Angle);
}

float Whr_GetWindSpeed()
{
	if (!CheckAttribute(&Weather,"Wind.Speed")) { return 3.0; }
	return stf(Weather.Wind.Speed);
}

ref Whr_GetShadowDensity()
{
	aref	aCurWeather = GetCurrentWeather();

	iShadowDensity[0] = argb(255,96,96,96);
	iShadowDensity[1] = argb(255,96,96,64);

	if (bWeatherLoaded)
	{
		iShadowDensity[0] = Whr_GetColor(aCurWeather,"Shadow.Density.Head");
		iShadowDensity[1] = Whr_GetColor(aCurWeather,"Shadow.Density.Foot");
	}
	return &iShadowDensity;
}

string	Whr_GetCurrentFog() { return sCurrentFog; }

string	Whr_GetInsideBack() { return sInsideBack; }
/*
string	GetLightingPath()
{
	if (CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
	return sLightingPath;
}
string	GetLmLightingPath()
{
	if (CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return "storm";
	}
	return sLmLightingPath;
}
*/
string	GetLightingPath()
{
//navy -->
	if (CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
//navy <--
	// Myth (Dmitry) fix for lighting, no need New Game
    string sLightingPathOld = sLightingPath;
    switch(sLightingPathOld)
    {
    case "day11":
        sLightingPath = "day2";
        break;
    case "day12":
        sLightingPath = "day2";
        break;
    case "day13":
        sLightingPath = "day1";
        break;
    case "day14":
        sLightingPath = "day1";
        break;
    case "day15":
        sLightingPath = "day1";
        break;
    case "day16":
        sLightingPath = "day1";
        break;
    case "day17":
        sLightingPath = "day2";
        break;
    case "day18":
        sLightingPath = "day2";
        break;
    case "evening19":
        sLightingPath = "evening1";
        break;
    case "evening20":
        sLightingPath = "night1";
        break;
    case "evening21":
        sLightingPath = "night1";
        break;
    case "evening22":
        sLightingPath = "night1";
        break;
    case "evening23":
        sLightingPath = "night1";
        break;
    case "night0":
        sLightingPath = "night1";
        break;
    case "night1":
        sLightingPath = "night1";
        break;
    case "night2":
        sLightingPath = "night1";
        break;
    case "night3":
        sLightingPath = "night1";
        break;
    case "night4":
        sLightingPath = "night1";
        break;
    case "night5":
        sLightingPath = "night1";
        break;
    case "morning6":
        sLightingPath = "night1";
        break;
    case "morning7":
        sLightingPath = "day3";
        break;
    case "morning8":
        sLightingPath = "morning1";
        break;
    case "morning9":
        sLightingPath = "morning1";
        break;
    case "morning10":
        sLightingPath = "morning1";
        break;
    case "storm1":
        sLightingPath = "evening1";
        break;
    case "storm2":
        sLightingPath = "evening2";
        break;
    case "storm3":
        sLightingPath = "evening1";
        break;
    case "storm4":
        sLightingPath = "night1";
        break;
    }
	return sLightingPath;
}

string	GetLmLightingPath()
{
//navy -->
	if (CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return "storm";
	}
//navy <--
	//Myth (Dmitry) fix shadows
    string sPart = strcut(sLmLightingPath, 0, 2);
    if (sPart == "day")
        return "day";
    //else
	return sLmLightingPath;
}

bool	Whr_IsDay() { return !bWeatherIsNight; }
bool	Whr_IsNight() { return bWeatherIsNight; }
bool	Whr_IsLight() { return bWeatherIsLight; }
bool	Whr_IsRain() { return bWeatherIsRain; }
bool	Whr_IsStorm() { return bWeatherIsStorm; }

int FindWeather(string sWeatherID)
{
	for (int i=0;i<MAX_WEATHERS;i++)
	{
		if (!CheckAttribute(&Weathers[i], "id"))
		{
			continue;
		}
		if(Weathers[i].id == sWeatherID)
		{
			return i;
		}
	}
	return -1;
}

//navy --> Rain ??????
void Whr_SetRainSound(bool _set, bool _isNight)
{
//	return;

	string scheme = "land";
	//land, sea, town
	if (!bSeaActive || bAbordageStarted)
	{
		if (IsEntity(loadedLocation) && CheckAttribute(loadedLocation, "type"))
		{
			switch (loadedLocation.type)
			{
			case "town":
				scheme = "town";
				break;
			case "land":
				scheme = "land";
				break;
			case "deck":
				scheme = "deck";
				break;
			}
		}
	}
	else
	{
		scheme = "sea";
	}
	if (_isNight)
    {
		scheme = scheme+"_night";
    }
	else
	{
		scheme = scheme+"_day";
	}
	if (_set)
	{
		scheme = scheme + "_rain";
	}

	//trace(": Set Rain Sound... " + _set);
	SetSoundScheme(scheme);
}

string Whr_GetRainyLightningPath()
{
	//trace("__GET__COL__");
	return "evening3"; //storm1";
}
//navy <--

// --> Mirsaneli
void SetTradeWinds()
{
    if (FORCE_TRADE_WINDS)
    {
        ref pchar = GetMainCharacter();

        // --- Base angle: East (-90°), allow variation ±30° (i.e. NE to SE)
        float baseAngle = Degree2Radian(-90.0);
        float variance = Degree2Radian(30.0); // ±30°
        float angleDelta = (frand(variance * 2.0)) - variance; // from -30° to +30°

        float fixedAngle = baseAngle + angleDelta;
        if (fixedAngle < 0.0) fixedAngle += PIm2;
        if (fixedAngle >= PIm2) fixedAngle -= PIm2;

        float fixedSpeed = 13.0 + frand(4.0); // ~4 Beaufort with variation

        Weather.Wind.Angle = fixedAngle;
        Weather.Wind.Speed = fixedSpeed;

        pchar.wind.angle = fixedAngle;
        pchar.wind.speed = fixedSpeed;

        gWeatherOvrd = true;
    }
}
// <-- Mirsaneli

// boal -->
void Whr_WindChange()
{
    aref aCurWeather = GetCurrentWeather();

    // --- WIND ANGLE: Constrain new angle within ±45° of the previous angle ---
    float oldAngle = fWeatherAngle; // the last known angle (in radians)
    float delta = (frand(PI / 2.0)) - (PI / 4.0); // random delta between -45° and +45°
    float newAngle = oldAngle + delta;

    // Wrap the angle between 0 and 2*PI
    if (newAngle < 0.0) newAngle += PIm2;
    if (newAngle >= PIm2) newAngle -= PIm2;

    Weather.Wind.Angle = newAngle;
    pchar.wind.angle = newAngle;

    // --- WIND SPEED: Use current weather's base speed ---
    Weather.Wind.Speed = Whr_GetFloat(aCurWeather, "Wind.Speed");
    pchar.wind.speed = Weather.Wind.Speed;

    // --- Quest logic ---
    pchar.quest.EraseWind.win_condition.l1 = "ExitFromSea";
    pchar.quest.EraseWind.win_condition = "EraseWind";

    // --- Store globally for fluctuation logic ---
    fWeatherAngle = newAngle;
    fWeatherSpeed = stf(Weather.Wind.Speed);

    // CheckIslandChange(); // optional logic if you use this elsewhere
}

bool Whr_isRainEnable()
{
	bool bRain  = true;

	if (bCabinStarted) bRain = false;
	if (CheckAttribute(GetMainCharacter(), "HeroParam") && IsEntity(&loadedLocation)) // pchar ??????????? ??? ?? ????
	{
        if (CheckAttribute(&loadedLocation, "environment.weather.rain") && !sti(loadedLocation.environment.weather.rain))
		{
			bRain = false;
		}
		else
		{
			if (CheckAttribute(loadedLocation, "type"))
			{
				if(loadedLocation.type == "residence"
					|| loadedLocation.type == "tavern"
					|| loadedLocation.type == "house"
					|| loadedLocation.type == "shop"
					|| loadedLocation.type == "shipyard"
					|| loadedLocation.type == "church" )
				{
					bRain = false;
				}
			}
		}
	}
	else
	{
		if (bSeaActive && bAbordageStarted ) // bLandInterfaceStart
		{
			if (IsEntity(&loadedLocation) && CheckAttribute(&loadedLocation, "environment.weather.rain") && !sti(loadedLocation.environment.weather.rain))
			{
				bRain = false;
			}
		}
	}
	return bRain;
}
// boal <--

void Whr_addwind2weather(ref tmpweather)
{
	tmpweather.Wind.Angle = Whr_GetFloat(&WeathersNH, "Wind.Angle");
	//tmpweather.Wind.Speed.Min = Whr_GetFloat(&WeathersNH, "Wind.Speed.Min");
	//tmpweather.Wind.Speed.Max = Whr_GetFloat(&WeathersNH, "Wind.Speed.Max");
	tmpweather.Wind.Speed = Whr_GetFloat(&WeathersNH, "Wind.Speed");

	// Weather.Wind.Angle = sti(WeathersNH.Wind.Angle;
	// Weather.Wind.Speed.Min = sti(WeathersNH.Wind.Speed.Min;
	// Weather.Wind.Speed.Max = sti(WeathersNH.Wind.Speed.Max;
	
	if (FORCE_TRADE_WINDS)
	{
		SetTradeWinds();
	}
}

void Whr_addfog2weather(ref tmpweather, int nw1, int nw2)
{
	// trace("Fog height: " + sti(WeathersNH.Fog.Height + " fog density:" + sti(WeathersNH.Fog.Density + " fog seadensity:" + sti(WeathersNH.Fog.SeaDensity)

    if( nw1<0 || nw1>=MAX_WEATHERS ) {return;}

	string sCurFog = Whr_GetCurrentFog();
	if( nw2<0)
	{
        tmpweather.Fog.Enable = Whr_GetLong(&WeathersNH, sCurFog + ".Enable");
        tmpweather.Fog.Start = Whr_GetFloat(&WeathersNH, sCurFog + ".Start");
        tmpweather.Fog.Density = Whr_GetFloat(&WeathersNH, sCurFog + ".Density"));
        tmpweather.Fog.Color = Whr_getCurrentBlendedFogColor();
        tmpweather.Fog.IslandDensity = Whr_GetFloat(&WeathersNH, "Fog.IslandDensity");
        tmpweather.Fog.SeaDensity = Whr_GetFloat(&WeathersNH, sCurFog + ".SeaDensity");
	}
	else
	{
		float fBlend = stf(Environment.Time) - sti(Environment.Time);

        tmpweather.Fog.Enable = Whr_GetLong(&WeathersNH, sCurFog + ".Enable");
		tmpweather.Fog.Start = Whr_BlendFloat( fBlend, Whr_GetFloat(&WeathersNH, sCurFog + ".Start"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Start") );
		tmpweather.Fog.Density = Whr_BlendFloat( fBlend, Whr_GetFloat(&WeathersNH, sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Density") );
		tmpweather.Fog.Color = Whr_BlendColor( fBlend, Whr_getCurrentBlendedFogColor(), Whr_GetColor(&Weathers[nw2], sCurFog + ".Color") );
		tmpweather.Fog.IslandDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(&WeathersNH, "Fog.IslandDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".IslandDensity") );
		tmpweather.Fog.SeaDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(&WeathersNH, sCurFog + ".SeaDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".SeaDensity") );
	}

	int rainfogcolor;
	if (iCurWeatherHour<6 || iCurWeatherHour>19){
		rainfogcolor = argb(0,20,15,15);
	}else{
		int lightfog = argb(0,230,230,230);
		int darkfog = argb(0,50,60,65);
		fblend = MakeFloat(wRain)/100.0;
		rainfogcolor =  Whr_BlendColor(fblend, lightfog, darkfog);
	}
	// trace("light fog: " + lightfog + " dark fog: " + darkfog + " blended fog:" + rainfogcolor + " blend constant: " + fblend);


	float tmpdensity = Whr_GetFloat(&WeathersNH, "Fog.Density");
	// trace("sti(WeathersNH.Fog.Density: " + tmpdensity + " before clamp: " + tmpdensity*100.0);
	float fblend2 = Clampf(tmpdensity*100.0);

	//int rainfogcolor2 =  Whr_BlendColor(fblend2, tmpweather.Bak.Fog.Color, rainfogcolor);
	// trace("weather fog: " + tmpweather.Bak.Fog.Color + " lightdark fog:" + rainfogcolor + " blended fog:" + rainfogcolor2 + " blend constant: " + fblend2);

	tmpweather.Fog.Color = rainfogcolor;
	//tmpweather.SpecialSeaFog.Color = rainfogcolor;
}

int Whr_getCurrentBlendedFogColor()
{
    int rainfogcolor;
    
    // More realistic light & dark fog colors
    int lightfog = argb(0, 200, 220, 230); // Soft bluish fog (morning/daytime)
    int darkfog = argb(0, 40, 50, 60);     // Deeper blue-gray fog (night)
    
    float fblend = MakeFloat(wRain) / 100.0 * 0.8; // Blending factor for rain

    // Adjust fog color based on time of day
    if (iCurWeatherHour < 6) {
        // Dawn (colder bluish fog)
        rainfogcolor = argb(0, 80, 100, 120);
    } else if (iCurWeatherHour > 19) {
        // Night (deep blue-gray)
        rainfogcolor = argb(0, 30, 40, 50);
    } else if (iCurWeatherHour < 9) {
        // Morning (warmer golden fog)
        rainfogcolor = argb(0, 180, 200, 220);
    } else if (iCurWeatherHour > 16) {
        // Evening (slightly orange/pink hue in fog)
        rainfogcolor = argb(0, 160, 180, 190);
    } else {
        // Daytime blending between lightfog and darkfog
        rainfogcolor = Whr_BlendColor(fblend, lightfog, darkfog);
    }

    float tmpdensity = Whr_GetFloat(&WeathersNH, "Fog.Density");
    float fblend2 = Clampf(tmpdensity * 100.0);

    // Final blending with weather-specific fog
    int rainfogcolor2 = Whr_BlendColor(fblend2, Whr_GetLong(&Weathers[iCurWeatherNum], "Bak.Fog.Color"), rainfogcolor);

    return rainfogcolor2;
}

void Whr_addRain2weather(ref tmpweather)
{
//trace("Whr_addRain2weather called");
	// tmpweather.Sun.Glow.Enable = false;
	// tmpweather.Sun.Overflow.Enable = false;

	tmpweather.Rain.NumDrops = sti(WeathersNH.Rain.NumDrops);
	tmpweather.Rain.Color = sti(WeathersNH.Rain.Color);
	tmpweather.Rain.DropLength = sti(WeathersNH.Rain.DropLength);
	tmpweather.Rain.Height = sti(WeathersNH.Rain.Height);
	tmpweather.Rain.Radius = sti(WeathersNH.Rain.Radius);
	tmpweather.Rain.Speed = sti(WeathersNH.Rain.Speed);
	tmpweather.Rain.Jitter = sti(WeathersNH.Rain.Jitter);
	tmpweather.Rain.WindSpeedJitter = sti(WeathersNH.Rain.WindSpeedJitter);
	tmpweather.Rain.MaxBlend = sti(WeathersNH.Rain.MaxBlend);
	tmpweather.Rain.TimeBlend = sti(WeathersNH.Rain.TimeBlend);

	// trace("WeathersNH LE:" + sti(WeathersNH.Lightning.Enable);

	//if (CheckAttribute(&WeathersNH,"Lightning.Enable")) {WeathersNH.Lightning.Enable = sti(WeathersNH.Lightning.Enable);}
	Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";
	Lightning.FlickerTime = 32;
	Lightning.SubTexX = 4;
	Lightning.SubTexY = 1;
	Lightning.ScaleX = 0.7;
	Lightning.ScaleY = 1.0;
	Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";
}

void Whr_addWaves2weather(ref tmpweather){
//trace("Whr_addWaves2weather called");
	// tmpweather.Sea2.BumpScale = Whr_GetFloat(&WeathersNH, "Sea2.BumpScale");
	tmpweather.Sea2.PosShift = Whr_GetFloat(&WeathersNH, "Sea2.PosShift");

	tmpweather.Sea2.Amp1 = Whr_GetFloat(&WeathersNH, "Sea2.Amp1");
	tmpweather.Sea2.AnimSpeed1 = Whr_GetFloat(&WeathersNH, "Sea2.AnimSpeed1");
	tmpweather.Sea2.Scale1 = Whr_GetFloat(&WeathersNH, "Sea2.Scale1");
	tmpweather.Sea2.MoveSpeed1 = Whr_GetString(&WeathersNH, "Sea2.MoveSpeed1");

	tmpweather.Sea2.Amp2 = Whr_GetFloat(&WeathersNH, "Sea2.Amp2");
	tmpweather.Sea2.AnimSpeed2 = Whr_GetFloat(&WeathersNH, "Sea2.AnimSpeed2");
	tmpweather.Sea2.Scale2 = Whr_GetFloat(&WeathersNH, "Sea2.Scale2");
	tmpweather.Sea2.MoveSpeed2 = Whr_GetString(&WeathersNH, "Sea2.MoveSpeed2");

	aref	aCurWeather = GetCurrentWeather();
	aref	aSea2; makearef(aSea2, aCurWeather.Sea2);
	aref	aSea; makearef(aSea, aCurWeather.Sea);

	// tmpweather.Sea.Bump.Dir = Whr_GetString(aSea, "Bump.Dir");
	// tmpweather.Sea.Bump.Tile = Whr_GetFloat(aSea, "Bump.Tile");
	// tmpweather.Sea.Bump.Ang = Whr_GetFloat(aSea, "Bump.Ang");
	// tmpweather.Sea.Bump.Speed = Whr_GetFloat(aSea, "Bump.Speed");
	// tmpweather.Sea.Bump.Scale = Whr_GetFloat(aSea, "Bump.Scale");
	// tmpweather.Sea.Bump.AnimSpeed = Whr_GetFloat(aSea, "Bump.AnimSpeed");
	tmpweather.Sea.Sky.Color = Whr_GetColor(aSea, "Sky.Color");
	tmpweather.Sea.Water.Color = Whr_GetColor(aSea,"Water.Color");

	tmpweather.Sea.Transparency = Whr_GetFloat(aSea,"Transparency");
	tmpweather.Sea.FrenelCoefficient = Whr_GetFloat(aSea,"FrenelCoefficient");
	tmpweather.Sea.WaterReflection = Whr_GetFloat(aSea,"WaterReflection");
	tmpweather.Sea.WaterAttenuation = Whr_GetFloat(aSea,"WaterAttenuation");

	if (!CheckAttribute(aCurWeather, "Sea.inlagoon")) {
        //trace("Whr_addWaves2weather no lagoon " + aCurWeather.id);
        tmpweather.Sea2.WaterColor = Whr_GetColor(aSea2, "WaterColor");
        tmpweather.Sea2.SkyColor = Whr_GetColor(aSea2, "SkyColor");
	}
	//else {
    //    trace("Whr_addWaves2weather still lagoon " + aCurWeather.id);
	//}
	tmpweather.Sea2.Reflection = Whr_GetFloat(aSea2, "Reflection");
	tmpweather.Sea2.Transparency = Whr_GetFloat(aSea2, "Transparency");
	tmpweather.Sea2.Attenuation = Whr_GetFloat(aSea2, "Attenuation");
	tmpweather.Sea2.Frenel = Whr_GetFloat(aSea2, "Frenel");
	// tmpweather.Sea2.BumpScale = Whr_GetFloat(aSea2, "BumpScale");

	tmpweather.Sea2.FoamV = Whr_GetFloat(&WeathersNH, "Sea2.FoamV");
	tmpweather.Sea2.FoamK = Whr_GetFloat(&WeathersNH, "Sea2.FoamK");
	tmpweather.Sea2.FoamUV = Whr_GetFloat(&WeathersNH, "Sea2.FoamUV");
	tmpweather.Sea2.FoamTexDisturb = Whr_GetFloat(&WeathersNH, "Sea2.FoamTexDisturb");
}

string Whr_getMoonTexture(){

	// PURSEON ========Begin Moon Phases at night code===========>
	string moonpic = "weather\sun\glow\moonglowfull.tga.tx";   //default in case moon state is not known
	switch (getMoonStateName(getMoonState())){
		case FULL_MOON:
			moonpic = "weather\sun\glow\moonglowfull.tga.tx";
		break;
		case NEW_MOON:
			moonpic = "weather\sun\glow\moonglownew.tga.tx";
		break;
		case QUARTER_ONE:
			moonpic = "weather\sun\glow\moonglowwaxc.tga.tx";
		break;
		case QUARTER_TWO:
			moonpic = "weather\sun\glow\moonglowwax.tga.tx";
		break;
		case QUARTER_THREE:
			moonpic = "weather\sun\glow\moonglowwan.tga.tx";
		break;
		case QUARTER_FOUR:
			moonpic = "weather\sun\glow\moonglowwanc.tga.tx";
		break;
	}

	return moonpic;
}
