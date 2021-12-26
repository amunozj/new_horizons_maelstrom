#include "Weather_NH\WhrWeather.h"

int extraBallast = 5;
int maxwRain = 5;

void Whr_GenerateValues(int fogCheck){

// Screwface : Chance to have weather conditions degrade is according to the month and seasons in Caribbean
	int month = GetDataMonth();

	// trace("Month: " + month);
	switch(month)
	{
		case 1:  
			extraBallast = -5;
			maxwRain = WRAINRAIN + 5;
			break;
		case 2:  
			extraBallast = -10;
			maxwRain = WRAINOVERCAST - 5;
			break;
		case 3:  
			extraBallast = -10;
			maxwRain = WRAINOVERCAST - 5;
			break;
		case 4:  
			extraBallast = 0;
			maxwRain = WRAINRAIN + 5;
			break;
		// beginning of the wet season
		case 5:  
			extraBallast = 5;
			maxwRain = WRAINSTORM + 5;
			break; 
		case 6:  
			extraBallast = 5;
			maxwRain = WRAINSTORM + 10;
			break;
		case 7:  
			extraBallast = 5;
			maxwRain = WRAINSTORM + 15;
			break;
		// Twisters possible
		case 8:  
			extraBallast = 10;
			maxwRain = WRAINTORNADO + 5;
			break;
		case 9:  
			extraBallast = 10;
			maxwRain = 100;
			break;
		case 10: 
			extraBallast = 10;
			maxwRain = 100;
			break;
		// beginning of the dry season
		case 11: 
			extraBallast = 0;
			maxwRain = WRAINRAIN + 5;
			break;
		case 12: 
			extraBallast = -5;
			maxwRain = WRAINRAIN + 5;
			break; 
	}

	// Make sure that set weather is not overriden by random generator
	if (ignoreSeasons == true){
		maxwRain = 100;
		rWind = 0;
		rRain = 0;
		rFog = 0;
	}
// Screwface : end

	if(rand(100) > (50 - windABallast)){
		if(fWeatherAngleOld <= PIm2 - rWindA){fWindA = fWeatherAngleOld + rWindA;}
		else{ fWindA = (fWeatherAngleOld + rWindA) - PIm2;}
		windABallast += (rWindA*5);
	}
	else{
		if(fWeatherAngleOld >= rWindA){ fWindA = fWeatherAngleOld - rWindA; }
		else{ fWindA = PIm2 - (rWindA - fWeatherAngleOld); }
		windABallast -= (rWindA*5);
		
	}
	
	int randomRain = rand(100);
	if (RAINDEBUG) Trace("Month: " + month + " RainBallast : " + rainBallast + " ExtraBallast: " + extraBallast + " randomRain: " + randomRain);
	
	if( randomRain > (50 - rainBallast - extraBallast)){
		if(goldRain <= maxwRain-rRain || (goldRain - rRain) < 0){wRain = goldRain + rRain; }
		else{ wRain = maxwRain; }
		rainBallast += rRain;
	}
	else{
		if(goldRain >= rRain){ wRain = goldRain - rRain; }
		else{ wRain = 0; }
		rainBallast -= rRain;
	}

	if (RAINDEBUG) Trace("wRain: " + wRain);
	
	if(fogCheck != 0){
		if(rand(100) > (50 - fogBallast)){
			if(goldFog <= (MAXFOG-rFog) || (goldFog - rFog) < 0){ goldFog = goldFog + rFog;}
			else{ goldFog = MAXFOG; }
			fogBallast += rFog;
		}
		else{
			if(goldFog >= rFog){ goldFog = goldFog - rFog;}
			else{ goldFog = 0; }
			fogBallast -= rFog;
		}
		if(wRain <= 60){
			if(goldFog >= 2){ fog = goldFog/FOGDECAY;}
			else{ fog = 0; }
		}
	}
	else{ fog = 0; }

	if(rand(100) > 50){
		if(oldWind <= 30-rWind || (oldWind - rWind) < 0){winds = oldWind + rWind;}
		else{ winds = 30; }
		windBallast += rWind;
	}
	else{
		if(oldWind >= rWind){winds = oldWind - rWind;}
		else{ winds = 0 };
		windBallast -= rWind;
	}
	// if (winds < 0) winds = 0;
	// if (winds < 5) winds = 15;	// LDH 12Feb09
	if (winds < 5) winds = 10;	// LDH 12Feb09

	//wRain = wRain + 20; // to test the coming of a storm
	//winds = 30;
	// screwface
	if(wRain >= WRAINSTORM)
	{
		WeatherParams.Storm = true;
	}
	if(wRain >= WRAINTORNADO && winds >= 28)
	{
		WeatherParams.tornado = true;
	}
	// else 
	// {
	// 	WhrDeleteTornadoEnvironment();
	// }
	// screwface : end
}
