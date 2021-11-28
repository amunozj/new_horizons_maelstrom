/////////////////////////
// NH 2021
/////////////////////////

#include "Weather_NH\WhrUtils.c"
#include "Weather_NH\WhrLightning.c"
#include "Weather_NH\WhrRain.c"
#include "Weather_NH\WhrSea.c"
#include "Weather_NH\WhrSky.c"
#include "Weather_NH\WhrSun.c"
#include "Weather_NH\WhrTornado.c"
#include "Weather_NH\WhrAstronomy.c"
#include "weather_NH\WhrGeneration_NH.c"


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
bool	Whr_IsFog() { return stf(Weather.Fog.SeaDensity)>0.01; }

object Weathers[MAX_WEATHERS];
object WeathersNH;

extern int InitWeather();

#event_handler("EWhr_GetWindAngle", "Whr_GetWindAngle");
#event_handler("EWhr_GetWindSpeed", "Whr_GetWindSpeed");
#event_handler("EWhr_GetShadowDensity", "Whr_GetShadowDensity");
#event_handler("EWhr_GetFogDensity", "Whr_GetFogDensity");
#event_handler("WeatherTimeUpdate", "Whr_TimeUpdate" );

void SetNextWeather(string sWeatherID)
{

	Trace("SetNextWeathr: " + sWeatherID)
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

	Whr_Generator();

	// find weather
	iNextWeatherNum = -1;
	for (int i=0; i<MAX_WEATHERS; i++)
	{
		if (!CheckAttribute(&Weathers[i], "id")) { continue; }
		if (Weathers[i].id == sWeatherID)
		{
			iCurWeatherNum = i;
			if (true)
			{
				Trace("iNextWeatherNum = " + iNextWeatherNum);
			}
			return;
		}
	}

	iCurWeatherNum = FindWeatherByHour(MakeInt(GetHour()));	
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

	if (LoadSegment("Weather_NH\WhrInit.c"))
	{
		iTotalNumWeathers = InitWeather();
		UnloadSegment("Weather_NH\WhrInit.c");
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

void CreateWeatherEnvironment()
{
	string sAttrName;
	string sSky = "";
	int iWeatherFound[MAX_WEATHERS];
	int iNumWeatherFound = 0;
	int iHour = MakeInt(GetHour());

	bool bWhrStorm = false;
	bool bWhrTornado = false;
	bool bRain = false;

	if (CheckAttribute(&WeatherParams,"Storm")) { bWhrStorm = sti(WeatherParams.Storm); }
	if (CheckAttribute(&WeatherParams,"Tornado")) { bWhrTornado = sti(WeatherParams.Tornado); }

	if (iNextWeatherNum != -1)
	{
		if (iPrevWeather == -1) { iPrevWeather = iCurWeatherNum; }
		iCurWeatherHour = iHour;
		iCurWeatherNum = iNextWeatherNum;
		iNextWeatherNum = -1;
	}
	else
	{
		Whr_Generator();
		iCurWeatherHour = iHour;
		iCurWeatherNum = FindWeatherByHour(iHour)		
	}

	addProceduralWeather(iCurWeatherNum);
	
	Whr_Generator();
	iBlendWeatherNum = FindBlendWeather(iCurWeatherNum);
	addProceduralWeather(iBlendWeatherNum);

	int iCurLocation;
	int iTestWeather;
    float fGetTime = GetTime();

	sunIsShine = true;

	// create main module Weather
	DeleteAttribute(&Weather,"");
	if (!isEntity(&Weather))
	{
		CreateEntity(&Weather, "Weather");
	}

	aref aCurWeather = GetCurrentWeather();

	sLightingPath = Whr_GetString(aCurWeather,"Lighting");
	sLmLightingPath = Whr_GetString(aCurWeather,"LightingLm");
	sInsideBack = Whr_GetString(aCurWeather,"InsideBack");
	bWeatherIsNight = Whr_GetLong(aCurWeather,"Night");
	bWeatherIsLight = Whr_GetLong(aCurWeather,"Lights");

	Weather.Wind.Angle = Whr_GetFloat(WeathersNH,"Wind.Angle");
	Weather.Wind.Speed = Whr_GetFloat(WeathersNH,"Wind.Speed");

	pchar.Wind.Angle = Whr_GetFloat(Weather,"Wind.Angle");
	pchar.Wind.Speed = Whr_GetFloat(Weather,"Wind.Speed");

	sCurrentFog = "Fog";
	if (bSeaActive)
	{
		sCurrentFog = "SpecialSeaFog";
	}
	FillWeatherData(iCurWeatherNum, iBlendWeatherNum);

	if (iBlendWeatherNum < 0 )
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

	fFogDensity = Whr_GetFloat(Weather, "Fog.Density");

	fWeatherDelta = 0.0;
	fWeatherAngle = Whr_GetFloat(Weather,"Wind.Angle");
	fWeatherSpeed = Whr_GetFloat(Weather,"Wind.Speed");

    // boal -->
	bRain = true; // Whr_isRainEnable();
    string sLocation = "";
    int iLocation = -1;
    if(CheckAttribute(pchar, "location")) {
       sLocation = pchar.location;
       iLocation = FindLocation(sLocation);
    }
	if(iLocation != -1)
	{
		ref rLoc;
		rLoc = &Locations[iLocation];

		if (CheckAttribute(rLoc, "environment.weather.rain") && !sti(rLoc.environment.weather.rain))
		{
			bRain = false;
		}
		//navy
		else
		{
			if (CheckAttribute(rLoc, "type"))
			{
				if(rLoc.type == "residence"
					|| rLoc.type == "tavern"
					|| rLoc.type == "house"
					|| rLoc.type == "shop"
					|| rLoc.type == "shipyard"
					|| rLoc.type == "church" )
				{
					bRain = false;
				}
			}
		}
	}
	if (bRain)
	{
		WhrCreateRainEnvironment();
	}
	else
	{
		ClearRainEnvironment();
	}
	// boal <--

	WhrCreateSunGlowEnvironment();
	WhrCreateLightningEnvironment();
	WhrCreateAstronomyEnvironment();
	WhrCreateSkyEnvironment();
	WhrCreateSeaEnvironment();

	if (WeathersNH.Tornado==true) { WhrCreateTornadoEnvironment(); }

	Particles.windpower = 0.001 * Clampf(Whr_GetWindSpeed() / WIND_NORMAL_POWER);
	Particles.winddirection.x = sin(Whr_GetWindAngle());
	Particles.winddirection.z = cos(Whr_GetWindAngle());

	bWeatherLoaded = true;

	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = Whr_GetFloat(Weather, "Fog.IslandDensity");
		Sea.Fog.SeaDensity = Whr_GetFloat(Weather, "Fog.SeaDensity");
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));		
	}
	//Trace("Whr: Select id = " + aCurWeather.id);
}

void Whr_UpdateWeather(bool reinit_weather) // NK 04-09-21
{
	// LDH cleanup 16Feb09
//	Traceandlog("Whr_UpdateWeather start weather update " + "Time: " + GetStringTime(GetTime()) +" reinit: " +reinit_weather);	// LDH 05Sep06 trace for CTD

	if(reinit_weather) WeatherInit(); // NK 04-09-21
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);

	trace("Whr_UpdateWeather finish weather update");

	if(bSeaActive && !ownDeckStarted())
	{
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
	Log_TestInfo("Weather ID: " + Weathers[iCurWeatherNum].id + " Lighting: " + Weathers[iCurWeatherNum].Lighting);
	Log_TestInfo("Sun: HeightAngle: " + Weathers[iCurWeatherNum].Sun.HeightAngle);

	iNextWeatherNum = iCurWeatherNum;
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);

	aref	aCurWeather = GetCurrentWeather();
	iCurWeatherHour = sti(aCurWeather.Hour.Min);

	SetCurrentTime(iCurWeatherHour, 0);
	Weather.Time.time = GetTime();
}

void Whr_OnWindChange()
{
	//creates the constant minor wind fluctuations
	float fDeltaTime = MakeFloat(GetDeltaTime()) * 0.001;
	fWeatherDelta = fWeatherDelta + fDeltaTime;

	float fSpd = fWeatherSpeed + (fWeatherSpeed / 6.0) * 0.1 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));
	float fAng = fWeatherAngle + 0.02 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));

	Weather.Wind.Angle = fAng;
	Weather.Wind.Speed = fSpd;
}

int Whr_OnCalcFogColor()
{
	int		iAlpha, iColor;
	float	x, y, z;

	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	// if( iBlendWeatherNum < 0 )
	// {
	aref aCurWeather = GetCurrentWeather();

	if (!CheckAttribute(&aCurWeather, sCurrentFog + ".Height")){
		trace(aCurWeather.id + " doesn't have height for fog " + sCurrentFog);
	}else{
		iAlpha = 255 - MakeInt(255.0 * Clampf(y / stf(aCurWeather.(sCurrentFog).Height)));	
	}

	// trace("current weather: " + Weathers[iCurWeatherNum].id + " Fog: " + sCurrentFog + " Color:" + Weathers[iCurWeatherNum].Bak.(sCurrentFog).Color + " Height: " + Weathers[iCurWeatherNum].(sCurrentFog).Height)

	// 	//iColor = argb(0,0,0,0);
	int iFogColor = sti(Weather.Fog.Color);
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

int Whr_BlendColor(float fBlend, int col1, int col2)
{
	int r1 = shr(and(col1,16711680), 16); // get red color 1
	int r2 = shr(and(col2,16711680), 16); // get red color 2

	int g1 = shr(and(col1,65280), 8); // get green color 1
	int g2 = shr(and(col2,65280), 8); // get green color 2

	int b1 = and(col1,255); // get blue color 1
	int b2 = and(col2,255); // get blue color 2

	int r = r1 + MakeInt(fBlend * (r2-r1));
	int g = g1 + MakeInt(fBlend * (g2-g1));
	int b = b1 + MakeInt(fBlend * (b2-b1));

	return argb(0,r,g,b);
}

void Whr_TimeUpdate()
{
	float fTime = GetEventData();
	//float fBlend = fTime - makeint(fTime);

	//
	Environment.time = fTime;
	int nOldHour = sti(Environment.date.hour);
	int nNewHour = makeint(fTime);
	int nNewMin = makeint((fTime - nNewHour)*60);
	int nNewSec = makeint(((fTime - nNewHour)*60 - nNewMin)*60);
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
	iCurWeatherNum = FindWeatherByHour( makeint(fTime) );
	iBlendWeatherNum = FindBlendWeather( iCurWeatherNum );

	if( iBlendWeatherNum < 0 ) {return;}

	sCurrentFog = "Fog";
	if (bSeaActive)
	{
		sCurrentFog = "SpecialSeaFog";
	}	

	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = Whr_GetFloat(Weather, "Fog.IslandDensity");
		Sea.Fog.SeaDensity = Whr_GetFloat(Weather, "Fog.SeaDensity");
	}

	if (WeathersNH.Rain == true)
	{
		WeatherParams.Rain.Sound = true;
		Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));
	}else
	{
		if (CheckAttribute(&WeatherParams, "Rain.Sound") && sti(WeatherParams.Rain.Sound))
		{
			WeatherParams.Rain = false;
			WeatherParams.Rain.Sound = false;
			Whr_SetRainSound(false, sti(Weathers[iCurWeatherNum].Night));
		}
	}

	if( nNewHour != nOldHour )
	{
		Whr_UpdateWeatherHour();
	}
	// update weather: sun lighting
	FillWeatherData(iCurWeatherNum, iBlendWeatherNum);
	Weather.isDone = "";

	//update rain: rain drops, rain colors, rain size, rainbow
	//navy -- 5.03.07
	if (WeathersNH.Rain == true)
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

void Whr_UpdateWeatherHour()
{
	bool bOldIsDay = Whr_IsDay();
	//#20190211-01
	bool doLightChange = false;
	int i, j, iCharIdx;

	bWeatherIsLight = Whr_GetLong(&Weathers[iCurWeatherNum],"Lights");
	bWeatherIsNight = Whr_GetLong(&Weathers[iCurWeatherNum],"Night");

	//#20191020-01
	aref aCurWeather = GetCurrentWeather();
	aref aStars;
	makearef(aStars, aCurWeather.Stars);
	FillStars(aStars);
	//FillAstronomyFadeValue();
	Astronomy.isDone = true;
	Astronomy.TimeUpdate = 1;

	if( Whr_IsDay() != bOldIsDay )
	{
		Whr_ChangeDayNight();
		Event("eChangeDayNight");
		//#20190211-01
        doLightChange = true;
 	}
 	if (bSeaActive && !bAbordageStarted)
	{
	    bool isSeaEnt = false;
	    if (IsEntity(&Sea))
            isSeaEnt = true;
        Whr_WindChange();
		i = FindIsland(pchar.location)
        if ( i != -1)
        {
            //#20190211-01
            if (isSeaEnt) {
                if(!CheckAttribute(&Sea, "MaxSeaHeight") || stf(Sea.MaxSeaHeight) != SetMaxSeaHeight(i))
                    WhrCreateSeaEnvironment();
	 		}
 		}
 		//#20190211-01
        if(doLightChange && isSeaEnt) {
            doShipLightChange(aCurWeather);
        }
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

void FillWeatherData(int nw1, int nw2)
{
	if( nw1<0 || nw1>=MAX_WEATHERS ) {return;}

	string sCurFog = Whr_GetCurrentFog();
	trace("Current Fog: " + sCurFog);
	if( nw2<0)
	{
		Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");
		Weather.Fog.Start = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start");
		Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density");
		Weather.Fog.Color = Whr_GetColor(&Weathers[nw1], sCurFog + ".Color");
		Weather.Fog.IslandDensity = Whr_GetFloat(&Weathers[nw1], "Fog.IslandDensity");
		Weather.Fog.SeaDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity");

		Weather.Sun.Color = Whr_GetColor(&Weathers[nw1],"Sun.Color");
		Weather.Sun.HeightAngle = Whr_GetFloat(&Weathers[nw1],"Sun.HeightAngle");
		Weather.Sun.AzimuthAngle = Whr_GetFloat(&Weathers[nw1],"Sun.AzimuthAngle");
		Weather.Sun.Ambient = Whr_GetColor(&Weathers[nw1],"Sun.Ambient");
	}
	else
	{
		float fBlend = stf(Environment.Time) - sti(Environment.Time);
		Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");
		Weather.Fog.Start = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Start") );
		Weather.Fog.Density = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".Density") );
		Weather.Fog.Color = Whr_BlendColor( fBlend, Whr_GetColor(&Weathers[nw1], sCurFog + ".Color"), Whr_GetColor(&Weathers[nw2], sCurFog + ".Color") );
		Weather.Fog.IslandDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1], "Fog.IslandDensity"), Whr_GetFloat(&Weathers[nw2], "Fog.IslandDensity") );
		Weather.Fog.SeaDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity"), Whr_GetFloat(&Weathers[nw2], sCurFog + ".SeaDensity") );

		Weather.Sun.Color = Whr_BlendColor( fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Color"), Whr_GetColor(&Weathers[nw2],"Sun.Color") );
		Weather.Sun.HeightAngle = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1],"Sun.HeightAngle"), Whr_GetFloat(&Weathers[nw2],"Sun.HeightAngle") );
		Weather.Sun.AzimuthAngle = Whr_BlendFloat( fBlend, Whr_GetFloat(&Weathers[nw1],"Sun.AzimuthAngle"), Whr_GetFloat(&Weathers[nw2],"Sun.AzimuthAngle") );
		Weather.Sun.Ambient = Whr_BlendColor( fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Ambient"), Whr_GetColor(&Weathers[nw2],"Sun.Ambient") );
	}
}

int FindWeatherByHour(int nHour)
{
	// trace("getting weather by hour.  Stormy sky: " + WeathersNH.StormSky);
	for (int n=0; n<MAX_WEATHERS; n++)
	{
		if (WeathersNH.StormSky==false){
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

void addProceduralWeather(int iTmp)
{
	// Fog deffinition ---------------------------------------------------------------------
	Weathers[iTmp].Fog.Enable = Whr_GetLong(WeathersNH, "Fog.Enable");
	Weathers[iTmp].Fog.Start =  Whr_GetFloat(WeathersNH, "Fog.Start");
	Weathers[iTmp].Fog.Height = Whr_GetFloat(WeathersNH, "Fog.Height");
	Weathers[iTmp].Fog.Density = Whr_GetFloat(WeathersNH, "Fog.Density");
	Weathers[iTmp].Fog.SeaDensity = Whr_GetFloat(WeathersNH, "Fog.SeaDensity");
	Weathers[iTmp].Fog.IslandDensity = Whr_GetFloat(WeathersNH, "Fog.IslandDensity");

	Weathers[iTmp].SpecialSeaFog.Enable =  Whr_GetLong(WeathersNH, "SpecialSeaFog.Enable");
	Weathers[iTmp].SpecialSeaFog.Height =  Whr_GetFloat(WeathersNH, "SpecialSeaFog.Height");		
	Weathers[iTmp].SpecialSeaFog.Start =  Whr_GetFloat(WeathersNH, "SpecialSeaFog.Start");
	Weathers[iTmp].SpecialSeaFog.Density =  Whr_GetFloat(WeathersNH, "SpecialSeaFog.Density");
	Weathers[iTmp].SpecialSeaFog.SeaDensity =  Whr_GetFloat(WeathersNH, "SpecialSeaFog.SeaDensity");	

	int rainfogcolor;
	if (iCurWeatherHour<6 || iCurWeatherHour>19){
		rainfogcolor = argb(0,20,15,15);
	}else{
		int lightfog = argb(0,128,128,128);
		int darkfog = argb(0,33,40,50);
		float fblend = MakeFloat(wRain)/100.0;
		rainfogcolor =  Whr_BlendColor(fblend, lightfog, darkfog);
	}

	float tmpdensity = Whr_GetFloat(WeathersNH, "Fog.Density");
	float fblend2 = Clampf(tmpdensity*50.0);
	int rainfogcolor2 =  Whr_BlendColor(fblend2, Weathers[iTmp].Bak.Fog.Color, rainfogcolor);

	Weathers[iTmp].Fog.Color = rainfogcolor;
	Weathers[iTmp].SpecialSeaFog.Color = rainfogcolor;


	// Sea Definition -----------------------------------------------------
	Weathers[iTmp].Sea2.BumpScale = Whr_GetFloat(WeathersNH, "Sea2.BumpScale");
	Weathers[iTmp].Sea2.PosShift = Whr_GetFloat(WeathersNH, "ea2.PosShift");

	Weathers[iTmp].Sea2.Amp1 = Whr_GetFloat(WeathersNH, "Sea2.Amp1");
	Weathers[iTmp].Sea2.AnimSpeed1 = Whr_GetFloat(WeathersNH, "Sea2.AnimSpeed1");
	Weathers[iTmp].Sea2.Scale1 = Whr_GetFloat(WeathersNH, "Sea2.Scale1");
	Weathers[iTmp].Sea2.MoveSpeed1 = Whr_GetString(WeathersNH, "Sea2.MoveSpeed1");

	Weathers[iTmp].Sea2.Amp2 = Whr_GetFloat(WeathersNH, "Sea2.Amp2");
	Weathers[iTmp].Sea2.AnimSpeed2 = Whr_GetFloat(WeathersNH, "Sea2.AnimSpeed2");
	Weathers[iTmp].Sea2.Scale2 = Whr_GetFloat(WeathersNH, "Sea2.Scale2");
	Weathers[iTmp].Sea2.MoveSpeed2 = Whr_GetString(WeathersNH, "Sea2.MoveSpeed2");

	Weathers[iTmp].Sea2.FoamV = Whr_GetFloat(WeathersNH, "Sea2.FoamV");
	Weathers[iTmp].Sea2.FoamK = Whr_GetFloat(WeathersNH, "Sea2.FoamK");
	Weathers[iTmp].Sea2.FoamUV = Whr_GetFloat(WeathersNH, "Sea2.FoamUV");
	Weathers[iTmp].Sea2.FoamTexDisturb = Whr_GetFloat(WeathersNH, "Sea2.FoamTexDisturb");


	// Rain Definition -----------------------------------------------------------------


	Weathers[iTmp].Rain.NumDrops = Whr_GetLong(WeathersNH , "Rain.NumDrops");
	Weathers[iTmp].Rain.Color = Whr_GetLong(WeathersNH, "Rain.Color");
	Weathers[iTmp].Rain.DropLength = Whr_GetFloat(WeathersNH, "Rain.DropLength");
	Weathers[iTmp].Rain.Height = Whr_GetFloat(WeathersNH, "Rain.Height");
	Weathers[iTmp].Rain.Radius = Whr_GetFloat(WeathersNH, "Rain.Radius");
	Weathers[iTmp].Rain.Speed = Whr_GetFloat(WeathersNH, "Rain.Speed");
	Weathers[iTmp].Rain.Jitter = Whr_GetFloat(WeathersNH, "Rain.Jitter");
	Weathers[iTmp].Rain.WindSpeedJitter = Whr_GetFloat(WeathersNH, "Rain.WindSpeedJitter");
	Weathers[iTmp].Rain.MaxBlend = Whr_GetLong(WeathersNH, "Rain.MaxBlend");
	Weathers[iTmp].Rain.TimeBlend = Whr_GetLong(WeathersNH, "Rain.TimeBlend");

	Weathers[iTmp].Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";	
	Weathers[iTmp].Lightning.FlickerTime = 32;
	Weathers[iTmp].Lightning.SubTexX = 4;
	Weathers[iTmp].Lightning.SubTexY = 1;
	Weathers[iTmp].Lightning.ScaleX = 0.7;
	Weathers[iTmp].Lightning.ScaleY = 1.0;
	Weathers[iTmp].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	Weathers[iTmp].Lightning.Enable = Whr_GetLong(WeathersNH, "Lightning.Enable");
	// Weathers[iTmp].Sun.Glow.Enable = Whr_GetLong(WeathersNH, "Sun.Glow.Enable");
	// Weathers[iTmp].Sun.Flare.Enable = Whr_GetLong(WeathersNH, "Sun.Flare.Enable");
	// Weathers[iTmp].Sun.Overflow.Enable = Whr_GetLong(WeathersNH, "Sun.Overflow.Enable");

}

int FindBlendWeather(int nHour)
{

	nHour = nHour + 1;
	if( nHour>=24 ) {nHour = 0;}

	int iTmp = FindWeatherByHour(nHour);

	return iTmp;

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
    string sLightingPathOld = sLightingPath;
    switch(sLightingPathOld)
    {
    case "day11":
        sLightingPath = "day1";
        break;
    case "day12":
        sLightingPath = "day1";
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
        sLightingPath = "day1";
        break;
    case "day18":
        sLightingPath = "day1";
        break;
    case "evening19":
        sLightingPath = "evening3";
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
        sLightingPath = "day1";
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
        sLightingPath = "evening3";
        break;
    case "storm2":
        sLightingPath = "evening3";
        break;
    case "storm3":
        sLightingPath = "evening3";
        break;
    case "storm4":
        sLightingPath = "night1";
        break;
    }

	if (CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain) && sLightingPath != "night1")
	{
		return Whr_GetRainyLightningPath();
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

//navy --> Rain ������
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

// boal -->
void Whr_WindChange()
{
	aref aCurWeather = GetCurrentWeather();

    if(CheckAttribute(pchar, "wind.angle"))
    {
    	Weather.Wind.Angle = stf(pchar.wind.angle) +  frand((PI/4.0)) - (PI / 8.0);
    	if (stf(Weather.Wind.Angle) < 0)  Weather.Wind.Angle = PIm2 + stf(Weather.Wind.Angle);
    }
    else
    {
		Weather.Wind.Angle = frand(PIm2);
	}
	pchar.wind.angle = Weather.Wind.Angle;

	Weather.Wind.Speed = Whr_GetFloat(aCurWeather,"Wind.Speed");
	pchar.wind.speed = Weather.Wind.Speed;

	pchar.quest.EraseWind.win_condition.l1 = "ExitFromSea";
	pchar.quest.EraseWind.win_condition = "EraseWind";

	fWeatherAngle = stf(Weather.Wind.Angle);
	fWeatherSpeed = stf(Weather.Wind.Speed);

	// CheckIslandChange();
}

bool Whr_isRainEnable()
{
	bool bRain  = true;
	if (CheckAttribute(GetMainCharacter(), "HeroParam") && IsEntity(&loadedLocation)) // pchar ����������� ��� �� ����
	{
        if (CheckAttribute(&loadedLocation, "environment.weather.rain") && !sti(loadedLocation.environment.weather.rain))
		{
			bRain = false;
		}
		/*else
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
		}*/
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
