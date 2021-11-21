void Whr_SetAzmAng(){

	// PURSEON ========Begin Moon Phases at night code===========>
	string moonpic = "weather\sun\glow\moonglowfull.tga";   //default in case moon state is not known
	switch (getMoonStateName(getMoonState())){
		case FULL_MOON:
			moonpic = "weather\sun\glow\moonglowfull.tga";
		break;
		case NEW_MOON:
			moonpic = "weather\sun\glow\moonglownew.tga";
		break;
		case QUARTER_ONE:
			moonpic = "weather\sun\glow\moonglowwaxc.tga";
		break;
		case QUARTER_TWO:
			moonpic = "weather\sun\glow\moonglowwax.tga";
		break;
		case QUARTER_THREE:
			moonpic = "weather\sun\glow\moonglowwan.tga";
		break;
		case QUARTER_FOUR:
			moonpic = "weather\sun\glow\moonglowwanc.tga";
		break;
	}
//-----------------------------------------

	// sun position based on Havana, May 16, 1690 - experimental 03Mar09
	switch (curTime)
	{
		case  6:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(160.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(2.0);
			break;
		case  7:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(165.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(15.0);
			break;
		case  8:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(170.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(28.0);
			break;
		case  9:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(175.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(42.0);
			break;
		case 10:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(180.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(56.0);
			break;
		case 11:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(187.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(70.0);
			break;
		case 12:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(213.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(83.0);
			break;
		case 13:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(335.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(81.0);
			break;
		case 14:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(355.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(68.0);
			break;
		case 15:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(1.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(54.0);
			break;
		case 16:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(6.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(40.0);
			break;
		case 17:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(11.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(27.0);
			break;
		case 18:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(16.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(13.0);
			break;
		case 19:
			WeathersNH.Sun.AzimuthAngle = Degree2Radian(21.0);
			WeathersNH.Sun.HeightAngle = Degree2Radian(0.1);
			break;
// default:
//		TraceAndLog("***** Hour was " + curTime);
	}
//TraceAndLog("Whr: AzimuthAngle = " + Radian2Degree(stf(WeathersNH.Sun.AzimuthAngle)) + ", HeightAngle = " + Radian2Degree(stf(WeathersNH.Sun.HeightAngle)));

	// modify SpecialSeaFog color for fog - 26Feb09

	int fogColor;
	if (CheckAttribute(&WeathersNH, "SpecialSeaFog.color")){
		fogColor = sti(WeathersNH.SpecialSeaFog.color);
	}else{
		if (CheckAttribute(&WeathersNH, "Fog.color")){
			fogColor = sti(WeathersNH.Fog.color);
		}else{
			fogColor = argb(0,145,145,145);
		}
	}

	int R = and(shr(fogColor, 16), 255);
	int G = and(shr(fogColor, 8), 255);
	int B = and(fogColor, 255);
//Trace("Original fog color = " + R + "," + G + "," + B);
	float avg = makefloat(R+G+B) / 3.0;		// average of R,G,B
	// adjust color to make it lighter
	avg *= 1.0 + stf(WeathersNH.SpecialSeaFog.Density)*100.0;	// fog of 0.001 gives 1.1 here
	// desaturate it a bit, makes fog more grey
	R = (avg*2.0 + R) / 3.0 + 0.5; if (R > 255) R = 255;
	G = (avg*2.0 + G) / 3.0 + 0.5; if (G > 255) G = 255;
	B = (avg*2.0 + B) / 3.0 + 0.5; if (B > 255) B = 255;
	WeathersNH.SpecialSeaFog.color = argb(0,R,G,B);
//Trace("Adjusted fog color = " + R + "," + G + "," + B);

}
