// Debug Flags
#define GENERATIONDEBUG 0
#define RAINDEBUG 1
#define RANDOMDEBUG 1

// dependence of fog height on fog amplitude
#define FOGHEIGHTFACTOR 40.0

// Dependnece of Wave properties on rain and wind 
#define WIND2WAVESPEED 0.25
#define WIND2WAVELENGTH 6.0
#define WIND2AMPLITUDE 0.3

#define RAIN2AMPLITUDE 2.0
#define RAIN2WIND 0.75

#define WIND2WAVELENGTH2 1.5
#define WIND2AMPLITUDE2 0.1
#define WIND2BUMPSCALE 1.0
#define WIND2FOAMV 0.175

//  Randomness of wave properties
#define AMPLITUDERANDOM 0.4
#define SCALERANDOM 0.4
#define FOAMRANDOM 0.025

// Night and lagoon color properties
#define NIGHTCOLORBLEND 6.0
#define SHORECOLORDISTANCE 20.0

// Evolution of fog on the generator
#define MINIMUMFOG 2
#define FOGFACTOR 0.0003
#define FOG2TRANSPARENCY 150.0

#define MAXFOG 20
#define FOGDECAY 2.0

// wRain levels 
#define WRAINOVERCAST 30
#define WRAINRAIN 50
#define WRAINSTORM 70
#define WRAINTORNADO 90

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


