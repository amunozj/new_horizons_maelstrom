#include "Weather\Init\WhrGenerateValues_NH.c"
#include "Weather\Init\WhrFogRainCheck_NH.c"
#include "Weather\Init\WhrDebugInfo_NH.c"

#define WIND2WAVESPEED 0.25
#define WIND2WAVELENGTH 8.0
#define WIND2AMPLITUDE 0.3

#define RAIN2AMPLITUDE 0.15
#define RAIN2WAVELENGTH 0.25
#define RAIN2ANIM 0.01
#define RAIN2FOAMV 0.025
#define RAIN2BUMPSCALE 0.35

#define WIND2WAVELENGTH2 2.0
#define WIND2AMPLITUDE2 0.1
#define WIND2BUMPSCALE 1.0
#define WIND2FOAMV 0.175


// #define REALISTIC_WAVES 1

void Whr_ResetOvrd(){
	OWeatherAngle = -50.0;
	OWABallast = -50.0;
	OFog = -50;
	OFBallast = -50;
	ORain = -50;
	ORBallast = -50;
	OWind = -50;
	OWBallast = -50;
	gWeatherOvrd = false;
}

void Whr_Generator(){
// ====================================================================
// JL - Less Random Weather Generator -- hopefully
// ====================================================================

	//Traceandlog("WhrInit.c : Whr_Generator() called -- gWeatherInit: " +gWeatherInit); //JL - Figuring out this weather system
	bool bWhrTornado = false;
	bool bWhrStorm = false;
	
	if(gWeatherInit == 1){
		goldRain = rand(100);
		goldFog = rand(20);
//		oldWind = rand(30);
		oldWind = rand(25) + 5;		// LDH 09Feb09
		fWeatherAngleOld = frand(PIm2);
		gWeatherInit = 0;
		fogBallast = 0; 
		rainBallast = 0; 
		windBallast = 0; 
		windABallast = 0;
		Trace(" !gWeatherInit Whr_Generator() - Initialized ");
	}

	//Logit("BugTracker - goldFog: " + goldFog + " goldRain: " + goldRain + " oldWind: " + oldWind + " gWeatherInit: " + gWeatherInit);
	curTime = MakeInt(GetHour()); //Causing problems
	bWeatherIsStorm = false; // screwface
	bWeatherIsRain = false; // screwface

	rWind = rand(MAX_WINDCHANGE);
	rFog = rand(MAX_FOGCHANGE); 
	rRain = rand(MAX_RAINCHANGE);
	rWindA = frand(MAX_ANGLECHANGE);
	
	Whr_GenerateValues(FREE_FOG);
	
	//--Testing Settings--------------------------------------------------------
	
	// wRain = 80;
	//fog = 20;
	//curTime = 6;
	// winds = 20;
	//rainBallast = 20;

	//--Testing Settings--------------------------------------------------------
	
	if(gWeatherOvrd){
		if(oWeatherAngle != -50.0){fWindA = OWeatherAngle;	}
		if(OWABallast != -50.0){windABallast = OWABallast; }
		if(OFog != -50){fog = OFog;}
		if(OFBallast != - 50){fogBallast = OFBallast;}
		if(ORain != -50){wRain = ORain;}
		if(ORBallast != -50){rainBallast = ORBallast;}
		if(OWind != -50){winds = OWind;}
		if(OWBallast != -50){windBallast = OWBallast;}
		Whr_ResetOvrd();
	}
	
	if (CheckAttribute(&WeatherParams,"Storm")) { bWhrStorm = sti(WeatherParams.Storm); } 
	if (CheckAttribute(&WeatherParams,"Tornado")) { bWhrTornado = sti(WeatherParams.Tornado); } 
	WeatherParams.Storm = false;
	WeatherParams.Tornado = false;
	
	if(bWhrStorm){
		wRain = 95;
		winds = 25;
		windBallast = 10;
		rainBallast = 10;
		fog = 75; //Armada
		//WeathersNH.Fog.Color = argb(0,33,40,50);
		bWeatherIsStorm = true; // screwface
	}
	if(bWhrTornado){
		wRain = 100;
		winds = 30;
		windBallast = 20;
		rainBallast = 20;
		fog = 75; //Armada
		//WeathersNH.Fog.Color = argb(0,33,40,50);
	}
	btornado = bWhrTornado; //screwface
	bstorm = bWhrStorm; //screwface
	
	goldRain = wRain;	
	goldFog = fog;
	oldWind = winds;
	fWeatherAngleOld = fWindA;
	
	if(windABallast >=  MAX_ABALLAST || windABallast <= -MAX_ABALLAST ){ windABallast = 0;}
	if(rainBallast  >=  MAX_RBALLAST )                                 { rainBallast = -MAX_RBALLAST;}
	if(rainBallast  <= -MAX_RBALLAST )                                 { rainBallast =  MAX_RBALLAST;}
	if(windBallast  >=  MAX_WBALLAST )                                 { windBallast = -MAX_WBALLAST;}
	if(windBallast  <= -MAX_WBALLAST )                                 { windBallast =  MAX_WBALLAST;}
	if(fogBallast   >=  MAX_FBALLAST )                                 { fogBallast  = -MAX_FBALLAST;}
	if(fogBallast   <= -MAX_FBALLAST )                                 { fogBallast  =  MAX_FBALLAST;}
	
	if(wRain >= 85 && winds <= 10){ windBallast = 15;}
	if(winds <= 25 && wRain >= 90){ rainBallast = -15;}
	if(fog > 0 && curTime >= 7 && curTime <= 20 && wRain <= 75){fogBallast = -30;}
	if(fogBallast < 0 && curTime > 20 || curTime < 7){fogBallast = 0;}
	if(fogBallast < 0 && curTime >= 7 && curTime <=20 && wRain > 75){fogBallast = 0;}
	
	minwind = winds - rand(2);
	maxwind = winds + rand(2);
	if(minwind < 5){minwind = 5;}	// LDH up from 0 - 12Feb09
	if(maxwind > 30){maxwind = 30;}
	if(minwind > maxwind){ minwind = maxwind; } // JL - Temporary catch all for weird wind bug
	
	// Whr_InitGValues(); //Setup generic values based on ToD
	Whr_FogRainCheck();	 //Set wRain and fog values

	// NK & Mith-->
	// LDH fixes - 16Mar09
	string direction1, direction2, direction3;

	fSeaA = PIm2 - fWindA;
	if (fSeaA >= (3.0 * PId2))
	{
		fSeaB = (fSeaA + PId2 - PIm2);
	}
	else
	{
		fSeaB = fSeaA + PId2;
	}
	WeathersNH.Wind.Angle = fWindA;
	WeathersNH.Wind.Speed.Min = minwind;
	WeathersNH.Wind.Speed.Max = maxwind;

	direction1 = fts(fSeaB, 4);
	direction2 = fts((fSeaB + (PId2 / 2.0)), 4);
	direction3 = fts((fSeaB - (PId2 / 2.0)), 4);

	float myWind = maxwind;
	// if (maxwind > 25.0 && !bWhrStorm && !bWhrTornado)
	// 	myWind = 25.0;

	// float windStrength1 = myWind / 26.0;
	// float windStrength2 = myWind / 30.0;
	// float windStrength3 = myWind / 28.0;

	float testfactor = 2.0
	float windStrength1 = testfactor * myWind / 26.0;
	float windStrength2 = testfactor * myWind / 30.0;
	float windStrength3 = testfactor * myWind / 28.0;


	string seaStrength1 = f2s(windStrength1, 4);
	string seaStrength2 = f2s(windStrength2, 4);
	string seaStrength3 = f2s(windStrength3, 4);

	if(Characters[GetMainCharacterIndex()].location !="")
	{
		Sea.MaxSeaHeight = 30.0;
	}


	float bumpscale = WIND2BUMPSCALE*WIND2WAVELENGTH/(winds + RAIN2BUMPSCALE*wRain);
	if (bumpscale > 1.0) {bumpscale = 1.0;}
	WeathersNH.Sea2.BumpScale = bumpscale;
	trace("WeathersNH.Sea2.BumpScale:" + WeathersNH.Sea2.BumpScale);
	WeathersNH.Sea2.PosShift = 0.2;

	WeathersNH.Sea2.Amp1 = 3 + WIND2AMPLITUDE*winds + RAIN2AMPLITUDE*wRain;
	// WeathersNH.Sea2.Amp1 = 9;
	WeathersNH.Sea2.AnimSpeed1 = 4 - RAIN2ANIM*wRain;

	float scale1 = WIND2WAVELENGTH/(winds + RAIN2WAVELENGTH*wRain);
	if (scale1 > 1.0) {scale1 = 1.0;}
	WeathersNH.Sea2.Scale1 = scale1;


	string waveSpeedZ = f2s(WIND2WAVESPEED*winds*sin(fWindA), 2);
	string waveSpeedX = f2s(WIND2WAVESPEED*winds*cos(fWindA), 2);
	WeathersNH.Sea2.MoveSpeed1 = waveSpeedX + ", 0.0, " + waveSpeedZ;



	WeathersNH.Sea2.Amp2 = WIND2AMPLITUDE*WIND2AMPLITUDE2*winds;
	WeathersNH.Sea2.AnimSpeed2 = 8.0;
	WeathersNH.Sea2.Scale2 = WIND2WAVELENGTH*WIND2WAVELENGTH2/winds;


	float randomDir = frnd()*PI;
	trace("random dir: " + randomDir);
	string waveSpeed2Z = f2s(-WIND2WAVESPEED*winds*sin(randomDir), 2);
	string waveSpeed2X = f2s(-WIND2WAVESPEED*winds*cos(randomDir), 2);
	WeathersNH.Sea2.MoveSpeed2 = waveSpeed2X + ", 0.0, " + waveSpeed2Z;

	WeathersNH.Sea2.FoamV = 1.0 + WIND2FOAMV*winds + RAIN2FOAMV*wRain;
	WeathersNH.Sea2.FoamK = 0.2;
	WeathersNH.Sea2.FoamUV = 0.2;
	WeathersNH.Sea2.FoamTexDisturb = 0.2;



	trace("WeathersNH.Sea2.Amp:" + WeathersNH.Sea2.Amp1 + ", " + WeathersNH.Sea2.Amp2);
	trace("WeathersNH.Sea2.AnimSpeed:" + WeathersNH.Sea2.AnimSpeed1+ ", " + WeathersNH.Sea2.AnimSpeed2);
	trace("WeathersNH.Sea2.Scale:" + WeathersNH.Sea2.Scale1 + ", " + WeathersNH.Sea2.Scale2);
	trace("WeathersNH.Sea2.MoveSpeed:" + WeathersNH.Sea2.MoveSpeed1 + ", " + WeathersNH.Sea2.MoveSpeed2);

	// Whr_DebugInfo();
}


string f2s(float fl,int nDigAfterPoint)
{
	float fmul = pow(10.0,nDigAfterPoint);
	fl = fl + 0.5/fmul;
	int p1 = makeint(fl);
	int p2 = makeint((fl-p1)*fmul);
	if (p1 == 0 && p2 == 0) return fts(fl,nDigAfterPoint);
	string minusstr = ""; if(fl < 0) minusstr = "-";
	string decimal = "0000000000" + abs(p2);
	decimal = strRight(decimal,nDigAfterPoint);
	string retval = minusstr + abs(p1) + "." + decimal;
	while (strRight(retval,1) == "0") retval = strLeft(retval, strLen(retval)-1);
	if (strRight(retval,1) == ".")    retval = strLeft(retval, strLen(retval)-1);
	return retval;
}
