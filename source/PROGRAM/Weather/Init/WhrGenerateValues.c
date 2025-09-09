#define MAX_RAIN_OFFSET 50

int Whr_GetRainRisk(int month)
{
    int rainrisk = 100;

	switch(month)
	{
		case 1:  rainrisk = 15; break;
		case 2:  rainrisk = 15; break;
		case 3:  rainrisk = 20; break;
		case 4:  rainrisk = 25; break;
		case 5:  rainrisk = 30; break; // beginning of the wet season
		case 6:  rainrisk = 35; break;
		case 7:  rainrisk = 40; break;
		case 8:  rainrisk = 45; break;
		case 9:  rainrisk = 50; break; // twister maximal risk
		case 10: rainrisk = 50; break; // twister maximal risk
		case 11: rainrisk = 40; break;
		case 12: rainrisk = 30; break; // dry season
	}
	return rainrisk;
}

void Whr_GenerateValues(int fogCheck){

// Screwface : Chance to have weather conditions degrade is according to the month and seasons in Caribbean
	float hour = GetHour();
	int month = GetDataMonth();
	int rainrisk = Whr_GetRainRisk(month);
	float hour_rain_contribution = 0.0;
	float rain_wind_influence = 0.0;

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

	WTrace("Hour: " + hour + " MAX_RAIN_HOUR: " + MAX_RAIN_HOUR);
	hour_rain_contribution = hour - MAX_RAIN_HOUR - 12;
	if (hour_rain_contribution < - 12){hour_rain_contribution = hour_rain_contribution + 24;}
	if (hour_rain_contribution < 0){hour_rain_contribution = hour_rain_contribution * -1;}
	WTrace("Hour rain contribution: " + hour_rain_contribution + " rRain: " + rRain + " rainrisk: " + (rainrisk + hour_rain_contribution*RAIN_HOUR_FACTOR) + " rainballast: " + rainBallast);
			

	if(rand(100) > (50 - rainBallast) && RAND(100) <= rainrisk + hour_rain_contribution*RAIN_HOUR_FACTOR){
		if(goldRain <= rainrisk + MAX_RAIN_OFFSET - rRain){wRain = goldRain + rRain; }
		else{ wRain = rainrisk + MAX_RAIN_OFFSET; }
		rainBallast += rRain;
	}
	else{
		if(goldRain >= rRain){ wRain = goldRain - rRain; }
		else{ wRain = 0; }
		rainBallast -= rRain;
	}

	if(fogCheck != 0){
		if(rand(100) > (50 - fogBallast)){
			if(goldFog <= (20-rFog) || (goldFog - rFog) < 0){ fog = goldFog + rFog;}
			else{ fog = 20; }
			fogBallast += rFog;
		}
		else{
			if(goldFog >= rFog){ fog = goldFog - rFog;}
			else{ fog = 0; }
			fogBallast -= rFog;
		}
		if(wRain <= WRAINRAIN){
			if(goldFog >= 2){ fog = goldFog/2;}
			else{ fog = 0; }
		}
	}
	else{ fog = 0; }

	if (wRain < MAX_RAIN_INFLUENCE){rain_wind_influence = 0.0;}		
	else{rain_wind_influence = wRain - MAX_RAIN_INFLUENCE;}	

	if(rand(100) > 50 - rain_wind_influence + windBallast){
		if(oldWind <= MAX_WIND - rWind + rain_wind_influence/3){winds = oldWind + rWind + rain_wind_influence/3;}
		else{ winds = MAX_WIND + rain_wind_influence/3; }
		windBallast += rWind;
	}
	else{
		if(oldWind >= rWind){winds = oldWind - rWind;}
		else{ winds = 0; }
		windBallast -= rWind;
	}
	// if (winds < 0) winds = 0;
	if (winds < 5) winds = 5;	// LDH 12Feb09

	WTrace("Weather values: wind angle " + fWindA + ", wind speed " + winds + ", rain " + wRain + ", fog " + fog);

}
