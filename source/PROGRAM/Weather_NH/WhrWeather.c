/////////////////////////
// NH 2021
/////////////////////////

#include "Weather_NH\WhrWeather.h"
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
#define PARTICLESPOWER 0.0

#define DEBUG_SEA_OPTICAL 0

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

int shipsLights = false;
bool ignoreSeasons = false;
int extraBallast = 5;
int maxwRain = 5;
bool morningFogChecked = false; 
bool morningFog = false; 
int randomFog = 0; 

object	Weather, WeatherParams, WhrCommonParams;
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
bool	bWRainStatus = false;
bool	bWStormStatus = false;
bool	bLightningStatus = false;
bool	bTornadoStatus = false;
bool	Whr_IsFog() { return stf(Weather.Fog.SeaDensity)>0.01; }

object Weathers[MAX_WEATHERS];
object WeathersNH;
object currentWeather;
object nextWeather;

extern int InitWeather();

#event_handler("EWhr_GetWindAngle", "Whr_GetWindAngle");
#event_handler("EWhr_GetWindSpeed", "Whr_GetWindSpeed");
#event_handler("EWhr_GetShadowDensity", "Whr_GetShadowDensity");
#event_handler("EWhr_GetFogDensity", "Whr_GetFogDensity");
#event_handler("WeatherTimeUpdate", "Whr_TimeUpdate" );

void SetNextWeather(string sWeatherID)
{

	int iHour = MakeInt(GetHour());
	// Trace("SetNextWeathr: " + sWeatherID)
	string sWeather = sWeatherID;
	if (sWeatherID == "Blue Sky" || sWeatherID == "Moon Night" || sWeatherID == "Red Sky") {sWeather = "Clear";}
	if (sWeatherID == "Day Storm") {sWeather = "Heavy Storm";}	
	if (sWeatherID == "alcove") {sWeather = "inside";}
	
	switch (sWeather)
	{
		case "Clear":
			wRain = 0;
			goldRain = 0;
			ORBallast = 0;
			fog = 0;
			goldFog = 0;
			gWeatherOvrd = true;	// LDH make new weather in CreateWeatherEnvironment 17Feb09
			makeCurrentFutureRealizations(iHour);
			break;

			case "Cloudy":
				wRain = WRAINOVERCAST;		// clouds start at 50, overcast starts at 65
				goldRain = WRAINOVERCAST;		// clouds start at 50, overcast starts at 65
				gWeatherOvrd = true;
				ignoreSeasons = true;
				makeCurrentFutureRealizations(iHour);
				break;

		case "Overcast":
			wRain = WRAINOVERCAST+10;		// overcast starts at 65, rain starts at 75
			goldRain = WRAINOVERCAST+10;		// overcast starts at 65, rain starts at 75
			gWeatherOvrd = true;
			ignoreSeasons = true;
			makeCurrentFutureRealizations(iHour);
			break;

		case "Rainy":
			wRain = WRAINRAIN+10;		// rain starts at 75, storm starts at 95
			goldRain = WRAINRAIN+10;		// rain starts at 75, storm starts at 95
			gWeatherOvrd = true;
			ignoreSeasons = true;
			makeCurrentFutureRealizations(iHour);
			break;

		case "Heavy Rain":
			wRain = WRAINSTORM;		// rain starts at 75, storm starts at 95
			goldRain = WRAINSTORM;		// rain starts at 75, storm starts at 95
			gWeatherOvrd = true;
			ignoreSeasons = true;
			makeCurrentFutureRealizations(iHour);
			break;

		case "Stormy":		// this produces lightning
			wRain = WRAINSTORM+10;		// storm starts at 95
			goldRain = WRAINSTORM+10;		// storm starts at 95
			oldWind = 15;		// twisters start at minwind >= 28
			gWeatherOvrd = true;
			ignoreSeasons = true;
			makeCurrentFutureRealizations(iHour);
			break;

		case "Heavy Storm":	// this produces twisters, "Day Storm"
			wRain = WRAINTORNADO+5;	// storm starts at 95
			goldRain = WRAINTORNADO+5;	// storm starts at 95
			ORBallast = 15;
			oldWind = 30;		// twisters start at minwind >= 28
			OWBallast = 15;
			gWeatherOvrd = true;
			ignoreSeasons = true;
			makeCurrentFutureRealizations(iHour);
			break;

		case "Foggy":
			Fog = 25;		// produces fog density of 0.00375
			goldFog = 25;		// produces fog density of 0.00375
			gWeatherOvrd = true;
			ignoreSeasons = true;
			makeCurrentFutureRealizations(iHour);
			break;

		case "Heavy Fog":
			Fog = 40;		// produces fog density of 0.00625
			goldFog = 40;		// produces fog density of 0.00625
			gWeatherOvrd = true;
			ignoreSeasons = true;
			makeCurrentFutureRealizations(iHour);
			break;

		case "Black Pearl Fight":
			wRain = WRAINSTORM;
			Fog = 25;
			goldFog = 25;
			oldWind = 25;
			gWeatherOvrd = true;
			ignoreSeasons = true;
			makeCurrentFutureRealizations(iHour);
			break;

		case "IslaDeMuerte":
			Fog = 80;		// produces fog density of 0.02
			goldFog = 80;		// produces fog density of 0.02
			gWeatherOvrd = true;
			makeCurrentFutureRealizations(iHour);
			break;

		case "Super Fog":
			Fog = 999;
			goldFog = 999;
			gWeatherOvrd = true;
			makeCurrentFutureRealizations(iHour);
			break;

	}

	// // find weather
	// iNextWeatherNum = -1;
	// for (int i=0; i<MAX_WEATHERS; i++)
	// {
	// 	if (!CheckAttribute(&Weathers[i], "id")) { continue; }
	// 	if (Weathers[i].id == sWeatherID)
	// 	{
	// 		iCurWeatherNum = i;
	// 		if (true)
	// 		{
	// 			Trace("iNextWeatherNum = " + iNextWeatherNum);
	// 		}
	// 		makeCurrentFutureRealizations(Weathers[i].Hour.Min);
	// 		return;
	// 	}
	// }

	makeCurrentFutureRealizations(iHour);	
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

void makeCurrentFutureRealizations(int iHour)
{
	Whr_Generator(iHour);
	addProceduralWeather(&currentWeather);

	int nextHour = iHour+1;
	if (nextHour > 23) {nextHour=0;}

	Whr_Generator(nextHour);
	addProceduralWeather(&nextWeather);

}

void WeatherInit()
{
	//DeleteAttribute(&WeatherParams,"");

	if (LoadSegment("Weather_NH\WhrInit.c"))
	{
		iTotalNumWeathers = InitWeather();
		UnloadSegment("Weather_NH\WhrInit.c");
	}

	int iHour = MakeInt(GetHour());
	makeCurrentFutureRealizations(iHour);

}

void DeleteWeatherEnvironment()
{
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
	aref curW;
	makearef(curW, currentWeather);
	return curW;
}

void CreateWeatherEnvironment()
{
	string sAttrName;
	string sSky = "";
	int iHour = MakeInt(GetHour());

	bool bWhrStorm = false;
	bool bWhrTornado = false;
	bool bRain = false;

	int day = GetDataDay();
	int daym1 = GetDataDay()-1;
	if (!CheckAttribute(currentWeather, "imprinted") || !CheckAttribute(nextWeather, "imprinted"))
	{
		trace("Imprint weather on weathers")
		makeCurrentFutureRealizations(iHour);
	}
	else
	{
		trace("Current weather has been imprinted");
	}

	if (DEBUG_SEA_OPTICAL){makeCurrentFutureRealizations(iHour);}

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

	Weather.Sun.BeginAngle = 3.14159265358979323846;
    Weather.Sun.EndAngle = 0.0;
    Weather.Moon.BeginAngle = 3.14159265358979323846;
    Weather.Moon.EndAngle = 0.0;	



	sLightingPath = Whr_GetString(currentWeather,"Lighting");
	sLmLightingPath = Whr_GetString(currentWeather,"LightingLm");
	sInsideBack = Whr_GetString(currentWeather,"InsideBack");
	bWeatherIsNight = Whr_GetLong(currentWeather,"Night");
	bWeatherIsLight = Whr_GetLong(currentWeather,"Lights");
	if (daytimeLights()) bWeatherIsLight = true;	
	doShipLightChange(currentWeather, true);	

	sCurrentFog = "Fog";
	if (bSeaActive)
	{
		sCurrentFog = "SpecialSeaFog";
	}

	FillWeatherData();
	// update sun glow: sun\moon, flares

	WhrFillSunGlowData();

	// Fill Sea data
	FillSeaData();	

	// Fill Sky data
	FillSkyData();


	// trace("Weather wind speed: " + Whr_GetFloat(Weather, "Wind.Speed"));

	pchar.Wind.Angle = fWeatherAngle;
	pchar.Wind.Speed = fWeatherSpeed;

	// if (WeathersNH.Rain == true)
	// {
	// 	FillRainData();
	// 	Rain.isDone = "";
	// }

	Weather.Time.time = fGetTime;
	Weather.Time.speed = 40.0*100.0/makeFloat(TIMESCALAR_SEA);
	// float updateFactor = GetTimeScale()+2.0;
	// if (GetTimeScale()==1.0){updateFactor = 1.0;}
	// Weather.Time.updatefrequence = makeInt(60.0/updateFactor);	
	Weather.Time.updatefrequence = 60;	

	SetEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor",0);
	SetEventHandler("frame","Whr_OnWindChange",0);

	fFogDensity = Whr_GetFloat(Weather, "Fog.Density");

	fWeatherDelta = 0.0;
	// fWeatherAngle = Whr_GetFloat(Weather,"Wind.Angle");
	// fWeatherSpeed = Whr_GetFloat(Weather,"Wind.Speed");

    // boal -->'
	WhrCreateRainEnvironment();
	bRain = bWeatherIsRain; // Whr_isRainEnable();
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

	if (bRain == false)
	{
		ClearRainEnvironment();
		if (CheckAttribute(&WeatherParams, "Rain.Sound") && sti(WeatherParams.Rain.Sound))
		{
			WeatherParams.Rain.Sound = false;
			Whr_SetRainSound(false, sti(currentWeather.Night));
		}
		WeatherParams.Rain = false;			
	}
	else
	{
		WeatherParams.Rain.Sound = true;
		WeatherParams.Rain = true;		
		Whr_SetRainSound(true, sti(currentWeather.Night));
		FillRainData();
		Rain.isDone = "";
	}

	// if (bWeatherIsStorm != bWStormStatus || bWeatherIsRain != bWRainStatus)
	// {
	bWStormStatus = bWeatherIsStorm;
	bWRainStatus = bWeatherIsRain;
	PostEvent("LoadSceneSound", 10);


	// Rain.isDone = "";		
	// }	
	// boal <--

	WhrCreateSunGlowEnvironment();
	WhrCreateLightningEnvironment();
	WhrCreateAstronomyEnvironment();
	WhrCreateSkyEnvironment();
	WhrCreateSeaEnvironment();

	// FillWeatherData();
	// update sun glow: sun\moon, flares
	WhrFillSunGlowData();

	// Fill Sea data
	FillSeaData();	

	// Fill Sky data
	FillSkyData();

	// Run astronomy 
	aref aStars;
	makearef(aStars, currentWeather.Stars);
	FillStars(aStars);
	// FillAstronomyFadeValue();
	Astronomy.isDone = true;
	Astronomy.TimeUpdate = 1;


	btornado = Whr_GetLong(Weather, "Tornado"); //screwface
	bstorm = Whr_GetLong(Weather, "Storm") //screwface

	WeatherParams.Storm = Whr_GetLong(Weather, "Storm");
	WeatherParams.Tornado = Whr_GetLong(Weather, "Tornado");	


	if (Whr_GetLong(Weather, "Tornado") == true) { WhrCreateTornadoEnvironment(); }
	else{
		WhrDeleteTornadoEnvironment();
	}

	Particles.windpower = PARTICLESPOWER * Clampf(Whr_GetWindSpeed() / WIND_NORMAL_POWER);
	Particles.winddirection.x = sin(Whr_GetWindAngle());
	Particles.winddirection.z = cos(Whr_GetWindAngle());
	
	ParticlesXPS.windpower = PARTICLESPOWER * Clampf(Whr_GetWindSpeed() / WIND_NORMAL_POWER);
	ParticlesXPS.winddirection.x = sin(Whr_GetWindAngle());
	ParticlesXPS.winddirection.z = cos(Whr_GetWindAngle());

	bWeatherLoaded = true;
	Weather.isDone = "";


	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = Whr_GetFloat(Weather, "Fog.IslandDensity");
		Sea.Fog.SeaDensity = Whr_GetFloat(Weather, "Fog.SeaDensity");
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));		
	}
	//Trace("Whr: Select id = " + aCurWeather.id);
}


void Whr_UpdateSea() // NK 04-09-21
{
	// LDH cleanup 16Feb09
//	Traceandlog("Whr_UpdateWeather start weather update " + "Time: " + GetStringTime(GetTime()) +" reinit: " +reinit_weather);	// LDH 05Sep06 trace for CTD


	WhrCreateSeaEnvironment();
	// Fill Sea data
	FillSeaData();	
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);

	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = Whr_GetFloat(Weather, "Fog.IslandDensity");
		Sea.Fog.SeaDensity = Whr_GetFloat(Weather, "Fog.SeaDensity");
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));		
	}
	// if(bSeaActive && !ownDeckStarted())
	// {
	// 	PlayStereoSound("nature\wind_sea4.wav"); // squall i.e. weatherchange
	// }
}


void Whr_UpdateWeather(bool reinit_weather) // NK 04-09-21
{
	// LDH cleanup 16Feb09
//	Traceandlog("Whr_UpdateWeather start weather update " + "Time: " + GetStringTime(GetTime()) +" reinit: " +reinit_weather);	// LDH 05Sep06 trace for CTD

	CreateWeatherEnvironment();
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);

	trace("Whr_UpdateWeather finish weather update");

	if(bSeaActive && !ownDeckStarted())
	{
		PlayStereoSound("nature\wind_sea4.wav"); // squall i.e. weatherchange

		if (GetSeaTime()>60) DirectsailCheck(true);	//  triggers change to other island and ship encounters, necessary to run here
	}
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

	if (!CheckAttribute(Weather, "Fog.Height")){
		trace("Weather doesn't have height fog height");
	}else{
		iAlpha = 255 - MakeInt(255.0 * Clampf(y / Whr_GetFloat(Weather, "Fog.Height")));	
	}

	// trace("Fog Height: " + Whr_GetFloat(Weather, "Fog.Height"));
	// trace("Fog color: " + Whr_GetLong(Weather, "Fog.Color"));

	// 	//iColor = argb(0,0,0,0);
	int iFogColor = Whr_GetLong(Weather, "Fog.Color");
	iColor = or(shl(iAlpha, 24), iFogColor);

	// trace("Return Color: " + iColor);

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
	// trace("High precision time timeupdate start: " + fHighPrecisionDeltaTime);
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

	ref mchr = GetMainCharacter();
	mchr.CurrentTime = fTime;
	
	// if( nNewHour < nOldHour )
	// {
	// 	AddDataToCurrent(0,0,1,true);
	// 	Weather.Time.time = GetTime();
	// } // to_do CalcLocalTime
	// float updateFactor = GetTimeScale()+2.0;
	// if (GetTimeScale()==1.0){updateFactor = 1.0;}
	// Weather.Time.updatefrequence = makeInt(60.0/updateFactor);	
	// Weather.Time.updatefrequence = 60;		

	// trace("Environment.time: " + fTime + " Weather update frequency: " + Weather.Time.updatefrequence + " Timescale: " + GetTimeScale());

	Weather.Time.time = fTime;

	if (bSeaActive && !bAbordageStarted)					// PB: Not while on a ship deck!
	{
		AccumSailTime();	// LDH accumulate sailing experience - 21Dec08
	}
    // if( iBlendWeatherNum < 0 ) {return;}
	//navy --> Rain
	string sTmp;
	int iTmp, iTime;

	// trace("Whr_TimeUpdate: find current and next weather");

	//navy <-- Rain

	sCurrentFog = "Fog";
	if (bSeaActive)
	{
		sCurrentFog = "SpecialSeaFog";
	}	

	// trace("Whr_TimeUpdate: update rain");

	// if( sti(Rain.NumDrops) > 0 ) {bWeatherIsRain = true;}

	FillWeatherData();

	if (bWeatherIsStorm != bWStormStatus || bWeatherIsRain != bWRainStatus)
	{
		// Trace("Change rain status.  Rain: " + bWeatherIsRain + " rain status: " + bWRainStatus + " Storm: " + bWeatherIsStorm + " storm status: " + bWStormStatus);
		if (bWeatherIsRain == true && bWRainStatus == false){
			WhrCreateRainEnvironment();
			WeatherParams.Rain.Sound = true;
			WeatherParams.Rain = true;		
			Whr_SetRainSound(true, sti(currentWeather.Night));
			Rain.isDone = "";			
		}
		
		if (bWeatherIsRain == false && bWRainStatus == true){
			ClearRainEnvironment();
		} 

		if (bWeatherIsRain == true){

			Particles.windpower = PARTICLESPOWER * Clampf(Whr_GetWindSpeed() / WIND_NORMAL_POWER);
			Particles.winddirection.x = sin(Whr_GetWindAngle());
			Particles.winddirection.z = cos(Whr_GetWindAngle());
			ParticlesXPS.windpower = PARTICLESPOWER * Clampf(Whr_GetWindSpeed() / WIND_NORMAL_POWER);
			ParticlesXPS.winddirection.x = sin(Whr_GetWindAngle());
			ParticlesXPS.winddirection.z = cos(Whr_GetWindAngle());

			FillRainData();				
		}else{

			if (CheckAttribute(&WeatherParams, "Rain.Sound") && sti(WeatherParams.Rain.Sound))
			{
				WeatherParams.Rain.Sound = false;
				Whr_SetRainSound(false, sti(currentWeather.Night));
			}
			WeatherParams.Rain = false;	
		}

		bWStormStatus = bWeatherIsStorm;
		bWRainStatus = bWeatherIsRain;
		MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
		StopSound(0,0);
		PostEvent("LoadSceneSound", 0);
	}

	if (bWeatherIsRain == true && nNewMin%15 == 0){
		FillRainData();
			Rain.isDone = "";	
	}

	if (bWeatherIsStorm == true){
		Seafoam.storm = "true";
		mchr.Capsize.Warning = ROLL_ANGLE_WARNING;
	}else{
		Seafoam.storm = "false";
		mchr.Capsize.Warning = 100;
	}

	btornado = Whr_GetLong(Weather, "Tornado"); //screwface
	bstorm = Whr_GetLong(Weather, "Storm") //screwface

	WeatherParams.Storm = Whr_GetLong(Weather, "Storm");
	WeatherParams.Tornado = Whr_GetLong(Weather, "Tornado");		

	if (Whr_GetLong(Weather, "Lightning.Enable") != bLightningStatus){
		bLightningStatus = Whr_GetLong(Weather, "Lightning.Enable");

		if (bLightningStatus == true){
			WhrCreateLightningEnvironment();
		}else{
			WhrDeleteLightningEnvironment();
		}
		MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
		StopSound(0,0);
		PostEvent("LoadSceneSound", 0);			
	}

	if (Whr_GetLong(Weather, "Tornado") != bTornadoStatus){
		bTornadoStatus = Whr_GetLong(Weather, "Tornado");

		if (bTornadoStatus == true){
			WhrCreateTornadoEnvironment();
		}else{
			WhrDeleteTornadoEnvironment();
		}
		MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
		StopSound(0,0);
		PostEvent("LoadSceneSound", 0);				
	}	

	if( nNewHour != nOldHour )
	{
		
		ignoreSeasons = false;
		Whr_UpdateWeatherHour();
		MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
		// PostEvent("LoadSceneSound", 10);
	}

	Weather.isDone = "";

	// update sun glow: sun\moon, flares
	WhrFillSunGlowData();
	SunGlow.isDone = true;


	// trace("Whr_TimeUpdate: Fill Sea");	

	// Fill Sea data
	FillSeaData();	

	// trace("Whr_TimeUpdate: Fill Sky");	

	// Fill Sky data
	FillSkyData();

	// trace("Whr_TimeUpdate: Set fog");	

	sLightingPath = Whr_GetString(currentWeather,"Lighting");
	sLmLightingPath = Whr_GetString(currentWeather,"LightingLm");

	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = Whr_GetFloat(Weather, "Fog.IslandDensity");
		Sea.Fog.SeaDensity = Whr_GetFloat(Weather, "Fog.SeaDensity");
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));	
		
	}

	fFogDensity = Whr_GetFloat(Weather, "Fog.Density");

	// trace("Whr_TimeUpdate: change lights");	
	aref aCurWeather = GetCurrentWeather();
	doShipLightChange(aCurWeather, false);	

	// trace("Whr_TimeUpdate: do astronomy");	
	//#20191020-01
	aref aStars;
	makearef(aStars, aCurWeather.Stars);
	FillStars(aStars);

	// trace("Whr_TimeUpdate: Mark astronomy done");
	// FillAstronomyFadeValue();
	Astronomy.isDone = true;
	Astronomy.TimeUpdate = 1;

	// trace("High precision time timeupdate end: " + fHighPrecisionDeltaTime);

	// trace("Whr_TimeUpdate: update sky time: " + isEntity(&Sky));
	// update sky: fog
	Sky.TimeUpdate = ftime;
	
}

#event_handler("eChangeDayNight", "eChangeDayNight");

void Whr_UpdateWeatherHour()
{

	int iHour = makeint(Environment.time); 
	bool bOldIsDay = Whr_IsDay();
	//#20190211-01
	bool doLightChange = false;
	int i, j, iCharIdx;

	bWeatherIsLight = Whr_GetLong(currentWeather,"Lights");
	if (daytimeLights()==1) bWeatherIsLight = 1;
	bWeatherIsNight = Whr_GetLong(currentWeather,"Night");

	//#20191020-01
	aref aCurWeather = GetCurrentWeather();
	aref aStars;
	makearef(aStars, aCurWeather.Stars);
	FillStars(aStars);
	// FillAstronomyFadeValue();
	Astronomy.isDone = true;
	Astronomy.TimeUpdate = 1;

	if( Whr_IsDay() != bOldIsDay )
	{
		Whr_ChangeDayNight();
		Event("eChangeDayNight");
		//#20190211-01
        doLightChange = true;
 	}
	// trace("Weather hourly update before wind change");
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

 	}

	int nextHour = iHour+1;
	if (nextHour > 23) {nextHour=0;}

	aref curW, nextW;
	makearef(curW, currentWeather);
	makearef(nextW, nextWeather);
	CopyAttributes(curW, nextW); //Copies from nextW to curW

	Whr_Generator(nextHour);
	addProceduralWeather(nextWeather);
	Whr_UpdateSea();
	 
}

int daytimeLights()
{
	// Turn on lights due to time
	int Lights = 0;
	int Hour = MakeInt(GetHour())
	if (Hour < 7 || Hour > 22)
	{
		Lights = 1;
	}
	return Lights;
}

void doShipLightChange(ref aCurWeather, bool forceUpdate)
{
    int j, iCharIdx;

	// Combine time and weather
    Sea.Lights =  Whr_GetLong(aCurWeather, "Lights");
	if (daytimeLights() == 1) Sea.Lights = 1;

	if (shipsLights != Whr_GetLong(Sea, "Lights") || forceUpdate == true)
	{
		ref rChar;
		for(j = 0; j < iNumShips; j++) {
			iCharIdx = Ships[j];
			if (iCharIdx < 0 || iCharIdx >= TOTAL_CHARACTERS) continue;
			rChar = GetCharacter(Ships[j]);
			Ship_SetLightsAndFlares(rChar);
			SendMessage(&characters[iCharIdx], "l", MSG_SHIP_LIGHTSRESET);
		}

		shipsLights =  Whr_GetLong(Sea, "Lights");
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

void FillWeatherData()
{
	float angle1, angle2, blendedAngle;

	string sCurFog = Whr_GetCurrentFog();

	float fBlend = stf(Environment.Time) - sti(Environment.Time);

	Weather.Fog.Enable = Whr_GetLong(currentWeather, sCurFog + ".Enable");
	Weather.Fog.Start = Whr_BlendFloat( fBlend, Whr_GetFloat(currentWeather, sCurFog + ".Start"), Whr_GetFloat(nextWeather, sCurFog + ".Start") );
	Weather.Fog.Density = Whr_BlendFloat( fBlend, Whr_GetFloat(currentWeather, sCurFog + ".Density"), Whr_GetFloat(nextWeather, sCurFog + ".Density") );
	Weather.Fog.Color = Whr_BlendColor( fBlend, Whr_GetColor(currentWeather, sCurFog + ".Color"), Whr_GetColor(nextWeather, sCurFog + ".Color") );
	Weather.Fog.IslandDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(currentWeather, "Fog.IslandDensity"), Whr_GetFloat(nextWeather, "Fog.IslandDensity") );
	Weather.Fog.SeaDensity = Whr_BlendFloat( fBlend, Whr_GetFloat(currentWeather, sCurFog + ".SeaDensity"), Whr_GetFloat(nextWeather, sCurFog + ".SeaDensity") );
	Weather.Fog.Height = Whr_BlendFloat( fBlend, Whr_GetFloat(currentWeather, sCurFog + ".Height"), Whr_GetFloat(nextWeather, sCurFog + ".Height") );

	Weather.Sun.Color = Whr_BlendColor( fBlend, Whr_GetColor(currentWeather,"Sun.Color"), Whr_GetColor(nextWeather,"Sun.Color") );
	Weather.Sun.Ambient = Whr_BlendColor( fBlend, Whr_GetColor(currentWeather,"Sun.Ambient"), Whr_GetColor(nextWeather,"Sun.Ambient") );

	// trace("w1 angle: " + Whr_GetFloat(currentWeather, "Wind.Angle") + "w2 angle: " + Whr_GetFloat(nextWeather, "Wind.Angle"));

	// 
	fWeatherSpeed = Whr_BlendFloat( fBlend, Whr_GetFloat(currentWeather, "Wind.seaWindSpeed"), Whr_GetFloat(nextWeather, "Wind.seaWindSpeed") );

	angle1 =  Whr_GetFloat(currentWeather, "Wind.Angle");
	angle2 =  Whr_GetFloat(nextWeather, "Wind.Angle");

	if (abs(angle1-angle2) > PI)
	{
		if (angle1 > PI) angle1 = angle1 - PIm2;
		if (angle2 > PI) angle2 = angle1 - PIm2;
	}
	blendedAngle = Whr_BlendFloat( fBlend, angle1, angle2);
	if (blendedAngle < 0) blendedAngle = blendedAngle + PIm2;

	fWeatherAngle = blendedAngle;
	// trace("Resulting angle: " + fWeatherAngle);

	if (Whr_GetLong(currentWeather, "Rain") == true || Whr_GetLong(nextWeather, "Rain") == true){Weather.Rain = true;}
	else{Weather.Rain = false;}



	Weather.Tornado = Whr_GetLong(currentWeather, "Tornado");
	Weather.Storm = Whr_GetLong(currentWeather, "Storm");
	Weather.Lightning.Enable = Whr_GetLong(WeathersNH, "Lightning.Enable");

	if (Whr_GetLong(Weather, "Rain") == true){
		bWeatherIsRain = true;
	}
	else{
		bWeatherIsRain = false;
	}

	if (Whr_GetLong(Weather, "Storm") == true){
		bWeatherIsStorm = true;
		WeatherParams.Storm = true;
		// bWhrStorm = true;
	}else{
		bWeatherIsStorm = false;
		WeatherParams.Storm = false;
	}

	if (Whr_GetLong(Weather, "Tornado") == true){
		WeatherParams.tornado = true;
		// bWhrStorm = true;
		// bWhrTornado = true;
	}else{
		WeatherParams.tornado = false;
	}

}

int FindWeatherByHour(int nHour)
{
	// for (int n=0; n<MAX_WEATHERS; n++)
	// {

	// 		if (!CheckAttribute(weather2imprint, "hour")) {continue;}
	// 		if (CheckAttribute(weather2imprint, "skip") && sti(weather2imprint.skip)==true) {continue;}
	// 		if( sti(weather2imprint.hour.min) == nHour ) {return n;}

	// }
	return -1;
}

void addProceduralWeather(ref weather2imprint)
{

	// Sea Definition -----------------------------------------------------
	weather2imprint.Sea2.BumpScale = Whr_GetFloat(WeathersNH, "Sea2.BumpScale");
	weather2imprint.Sea2.PosShift = Whr_GetFloat(WeathersNH, "Sea2.PosShift");

	weather2imprint.Sea2.Amp1 = Whr_GetFloat(WeathersNH, "Sea2.Amp1");
	weather2imprint.Sea2.AnimSpeed1 = Whr_GetFloat(WeathersNH, "Sea2.AnimSpeed1");
	weather2imprint.Sea2.Scale1 = Whr_GetFloat(WeathersNH, "Sea2.Scale1");
	weather2imprint.Sea2.MoveSpeed1 = Whr_GetString(WeathersNH, "Sea2.MoveSpeed1");

	weather2imprint.Sea2.Amp2 = Whr_GetFloat(WeathersNH, "Sea2.Amp2");
	weather2imprint.Sea2.AnimSpeed2 = Whr_GetFloat(WeathersNH, "Sea2.AnimSpeed2");
	weather2imprint.Sea2.Scale2 = Whr_GetFloat(WeathersNH, "Sea2.Scale2");
	weather2imprint.Sea2.MoveSpeed2 = Whr_GetString(WeathersNH, "Sea2.MoveSpeed2");

	weather2imprint.Sea2.FoamEnable = true;
	weather2imprint.Sea2.FoamV = Whr_GetFloat(WeathersNH, "Sea2.FoamV");
	weather2imprint.Sea2.FoamK = Whr_GetFloat(WeathersNH, "Sea2.FoamK");
	weather2imprint.Sea2.FoamUV = Whr_GetFloat(WeathersNH, "Sea2.FoamUV");
	weather2imprint.Sea2.FoamTexDisturb = Whr_GetFloat(WeathersNH, "Sea2.FoamTexDisturb");

	weather2imprint.Sea2.Frenel = Whr_GetFloat(WeathersNH, "Sea2.Frenel");
	weather2imprint.Sea2.Reflection = Whr_GetFloat(WeathersNH, "Sea2.Reflection");
	weather2imprint.Sea2.Attenuation = Whr_GetFloat(WeathersNH, "Sea2.Attenuation");
	weather2imprint.Sea2.Transparency = Whr_GetFloat(WeathersNH, "Sea2.Transparency");


	// Fog deffinition ---------------------------------------------------------------------
	weather2imprint.Fog.Enable = Whr_GetLong(WeathersNH, "Fog.Enable");
	weather2imprint.Fog.Start =  Whr_GetFloat(WeathersNH, "Fog.Start");
	weather2imprint.Fog.Height = Whr_GetFloat(WeathersNH, "Fog.Height");
	weather2imprint.Fog.Density = Whr_GetFloat(WeathersNH, "Fog.Density");
	weather2imprint.Fog.SeaDensity = Whr_GetFloat(WeathersNH, "Fog.SeaDensity");
	weather2imprint.Fog.IslandDensity = Whr_GetFloat(WeathersNH, "Fog.IslandDensity");

	weather2imprint.SpecialSeaFog.Enable =  Whr_GetLong(WeathersNH, "SpecialSeaFog.Enable");
	weather2imprint.SpecialSeaFog.Height =  Whr_GetFloat(WeathersNH, "SpecialSeaFog.Height");		
	weather2imprint.SpecialSeaFog.Start =  Whr_GetFloat(WeathersNH, "SpecialSeaFog.Start");
	weather2imprint.SpecialSeaFog.Density =  Whr_GetFloat(WeathersNH, "SpecialSeaFog.Density");
	weather2imprint.SpecialSeaFog.SeaDensity =  Whr_GetFloat(WeathersNH, "SpecialSeaFog.SeaDensity");	

	weather2imprint.Fog.Color = Whr_GetColor(WeathersNH, "Fog.Color");
	weather2imprint.SpecialSeaFog.Color = Whr_GetColor(WeathersNH, "SpecialSeaFog.Color");

	// Sea Definition -----------------------------------------------------
	weather2imprint.Sea2.WaterColor = Whr_GetColor(WeathersNH, "Sea2.WaterColor");

	//Sky definition
	weather2imprint.Sea2.SkyColor = Whr_GetColor(WeathersNH, "Sea2.SkyColor");
	weather2imprint.Sky.Dir = Whr_GetString(WeathersNH, "Sky.Dir");
	weather2imprint.Sky.Angle = 0.0;
	weather2imprint.Sky.Color = Whr_GetColor(WeathersNH, "Sea2.SkyColor");
	Trace("Imprint weather sky.dir: " + Whr_GetString(WeathersNH, "Sky.Dir"));

	// Rain definition
	weather2imprint.Rain = Whr_GetLong(WeathersNH , "Rain");
	weather2imprint.Storm = Whr_GetLong(WeathersNH , "Storm");
	weather2imprint.Tornado = Whr_GetLong(WeathersNH , "Tornado");

	weather2imprint.Rain.NumDrops = Whr_GetLong(WeathersNH , "Rain.NumDrops");
	weather2imprint.Rain.Color = Whr_GetLong(WeathersNH, "Rain.Color");
	weather2imprint.Rain.DropLength = Whr_GetFloat(WeathersNH, "Rain.DropLength");
	weather2imprint.Rain.Height = Whr_GetFloat(WeathersNH, "Rain.Height");
	weather2imprint.Rain.Radius = Whr_GetFloat(WeathersNH, "Rain.Radius");
	weather2imprint.Rain.Speed = Whr_GetFloat(WeathersNH, "Rain.Speed");
	weather2imprint.Rain.Jitter = Whr_GetFloat(WeathersNH, "Rain.Jitter");
	weather2imprint.Rain.WindSpeedJitter = Whr_GetFloat(WeathersNH, "Rain.WindSpeedJitter");
	weather2imprint.Rain.MaxBlend = Whr_GetLong(WeathersNH, "Rain.MaxBlend");
	weather2imprint.Rain.TimeBlend = Whr_GetLong(WeathersNH, "Rain.TimeBlend");
	weather2imprint.Rain.DropsTexture = "weather\rain_drops.tga.tx";
	weather2imprint.Rain.DropsNearNum = Whr_GetLong(WeathersNH, "Rain.DropsNearNum");

	weather2imprint.Rain.DropsFarNum = Whr_GetLong(WeathersNH, "Rain.DropsFarNum");
	weather2imprint.Rain.DropsNearRadius = Whr_GetFloat(WeathersNH, "Rain.DropsNearRadius");
	weather2imprint.Rain.DropsFarRadius = Whr_GetFloat(WeathersNH, "Rain.DropsFarRadius");
	weather2imprint.Rain.DropsLifeTime = Whr_GetFloat(WeathersNH, "Rain.DropsLifeTime");
	weather2imprint.Rain.DropsSize = Whr_GetFloat(WeathersNH, "Rain.DropsSize");
	weather2imprint.Rain.DropsColor = Whr_GetLong(WeathersNH, "Rain.DropsColor"); 

	// Storm and tornados
	weather2imprint.Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";	
	weather2imprint.Lightning.FlickerTime = 32;
	weather2imprint.Lightning.SubTexX = 4;
	weather2imprint.Lightning.SubTexY = 1;
	weather2imprint.Lightning.ScaleX = 0.7;
	weather2imprint.Lightning.ScaleY = 1.0;
	weather2imprint.Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	weather2imprint.Lightning.Enable = Whr_GetLong(WeathersNH, "Lightning.Enable");
	weather2imprint.Rainbow.Enable = Whr_GetLong(WeathersNH , "Rainbow.Enable");
	weather2imprint.Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	weather2imprint.Tornado = Whr_GetLong(WeathersNH, "Tornado");

	// Sun glow and flare
	
	weather2imprint.Sun.Moon = Whr_GetLong(WeathersNH, "Sun.Moon");
	weather2imprint.Sun.Color = Whr_GetColor(WeathersNH, "Sun.Color");
	weather2imprint.Sun.Ambient = Whr_GetColor(WeathersNH, "Sun.Ambient");

	weather2imprint.Sun.Reflection.Enable = Whr_GetLong(WeathersNH, "Sun.Reflection.Enable");
	weather2imprint.Sun.Reflection.Dist = 3500.0;
	weather2imprint.Sun.Reflection.Color = argb(200, 200, 200, 200);
	weather2imprint.Sun.Reflection.Technique = "sunreflection";
	weather2imprint.Sun.Reflection.Size = 500.0;
	weather2imprint.Sun.Reflection.Texture = Whr_GetString(WeathersNH, "Sun.Reflection.Texture");	

	weather2imprint.Sun.Overflow.Enable = Whr_GetLong(WeathersNH, "Sun.Overflow.Enable");
	weather2imprint.Sun.Overflow.Technique = "sunoverflow";
	weather2imprint.Sun.Overflow.Size = 5500.0;
	weather2imprint.Sun.Overflow.Start = 0.7;
	weather2imprint.Sun.Overflow.Color = argb(0, 100, 100, 100);
	weather2imprint.Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";

	weather2imprint.Sun.Flare.Enable = Whr_GetLong(WeathersNH, "Sun.Flare.Enable");
	weather2imprint.Sun.Flare.TexSizeX = 2;
	weather2imprint.Sun.Flare.TexSizeY = 2;
	weather2imprint.Sun.Flare.Dist = 3500.0;
	weather2imprint.Sun.Flare.Technique = "sunflare";
	weather2imprint.Sun.Flare.Scale = 2.0;
	weather2imprint.Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";

	weather2imprint.Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	weather2imprint.Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	weather2imprint.Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	weather2imprint.Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	weather2imprint.Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	weather2imprint.Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	weather2imprint.Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	weather2imprint.Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	weather2imprint.Sun.Glow.Enable = Whr_GetLong(WeathersNH, "Sun.Glow.Enable");
	weather2imprint.Sun.Glow.Dist = 3500.0;
	weather2imprint.Sun.Glow.Size = Whr_GetFloat(WeathersNH, "Sun.Glow.Size");
	weather2imprint.Sun.Glow.RotateSpeed  = Whr_GetFloat(WeathersNH, "Sun.Glow.RotateSpeed");
	weather2imprint.Sun.Glow.DecayTime = 8.0;
	weather2imprint.Sun.Glow.TechniqueNoZ = "sunglow_noz";
	weather2imprint.Sun.Glow.TechniqueZ = "sunglow_z";
	weather2imprint.Sun.Glow.Texture = Whr_GetString(WeathersNH, "Sun.Glow.Texture");
	weather2imprint.Sun.Glow.Color = Whr_GetColor(WeathersNH, "Sea2.SkyColor");
	
	// Stars and planets
	weather2imprint.Planets.enable = Whr_GetLong(WeathersNH, "Planets.enable");
	weather2imprint.Stars.Enable = Whr_GetLong(WeathersNH, "Stars.Enable");
	weather2imprint.Stars.Texture = "weather\astronomy\stars.tga.tx";
	weather2imprint.Stars.Color = Whr_GetColor(WeathersNH, "Stars.Color");
	weather2imprint.Stars.Radius = Whr_GetFloat(WeathersNH, "Stars.Radius");
	weather2imprint.Stars.Size = Whr_GetFloat(WeathersNH, "Stars.Size");
	weather2imprint.Stars.HeightFade = Whr_GetFloat(WeathersNH, "Stars.HeightFade");
	weather2imprint.Stars.SunFade = Whr_GetFloat(WeathersNH, "Stars.SunFade");
	weather2imprint.Stars.VisualMagnitude = Whr_GetFloat(WeathersNH, "Stars.VisualMagnitude");

	// Weather lights
	weather2imprint.Lights = Whr_GetLong(WeathersNH, "Lights");
	weather2imprint.Night = Whr_GetLong(WeathersNH, "Night");

	// Wind parameters
	if (CheckAttribute(WeathersNH,"Wind.seaWindSpeed"))  weather2imprint.Wind.seaWindSpeed = Whr_GetFloat(WeathersNH, "Wind.seaWindSpeed");
	else  weather2imprint.Wind.seaWindSpeed = Whr_GetFloat(WeathersNH, "Wind.Speed");

	// trace("Imprinted sea wind speed: " + Whr_GetFloat(weather2imprint, "Wind.seaWindSpeed"));
	weather2imprint.Wind.Angle = Whr_GetFloat(WeathersNH, "Wind.Angle");

	// Storing day of imprint
	weather2imprint.imprinted = true;

	// Lighting path
	weather2imprint.Lighting =  Whr_GetString(WeathersNH, "Lighting");
	weather2imprint.LightingLm =  Whr_GetString(WeathersNH, "LightingLm");
	weather2imprint.InsideBack =  Whr_GetString(WeathersNH, "InsideBack");

	// Shadows
	weather2imprint.Shadow.Density.Head = Whr_GetColor(WeathersNH, "Shadow.Density.Head");
	weather2imprint.Shadow.Density.Foot = Whr_GetColor(WeathersNH, "Shadow.Density.Foot");			

	Weather.Sun.BeginAngle = 3.14159265358979323846;
    Weather.Sun.EndAngle = 0.0;
    Weather.Moon.BeginAngle = 3.14159265358979323846;
    Weather.Moon.EndAngle = 0.0;

}

int FindBlendWeather(int nHour)
{

	nHour = nHour + 1;
	if( nHour>23 ) {nHour = 0;}

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
        sLightingPath = "day1";
        break;
    case "morning9":
        sLightingPath = "day1";
        break;
    case "morning10":
        sLightingPath = "day1";
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

// boal -->
void Whr_WindChange()
{
	// aref aCurWeather = GetCurrentWeather();

    // if(CheckAttribute(pchar, "wind.angle"))
    // {
    // 	Weather.Wind.Angle = stf(pchar.wind.angle) +  frand((PI/4.0)) - (PI / 8.0);
    // 	if (stf(Weather.Wind.Angle) < 0)  Weather.Wind.Angle = PIm2 + stf(Weather.Wind.Angle);
    // }
    // else
    // {
	// 	Weather.Wind.Angle = frand(PIm2);
	// }
	pchar.wind.angle = Weather.Wind.Angle;

	// Weather.Wind.Speed = Whr_GetFloat(aCurWeather,"Wind.Speed");
	pchar.wind.speed = Weather.Wind.Speed;

	pchar.quest.EraseWind.win_condition.l1 = "ExitFromSea";
	pchar.quest.EraseWind.win_condition = "EraseWind";

	// fWeatherAngle = stf(Weather.Wind.Angle);
	// fWeatherSpeed = stf(Weather.Wind.Speed);

	// CheckIslandChange();
}

bool Whr_isRainEnable()
{
	bool bRain  = true;
	if (CheckAttribute(GetMainCharacter(), "HeroParam") && IsEntity(&loadedLocation)) // pchar ??????????? ??? ?? ????
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

void clearImprintedWeather(){

	for (int i=0; i<MAX_WEATHERS; i++)
	{
		Weathers[i].lastImprint = -1;
	}

}
