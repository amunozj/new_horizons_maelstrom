object Rain;

void WhrDeleteRainEnvironment()
{
	if (isEntity(&Rain))
	{
		DeleteClass(&Rain);
	}
	DeleteAttribute(&Rain,"");
}

void WhrCreateRainEnvironment()
{
	bWeatherIsRain = false;

	if (!isEntity(&Rain))
	{
		CreateEntity(&Rain,"rain");
	}
	FillRainData();
	Rain.isDone = "";

	if( sti(Rain.NumDrops) > 0 ) {bWeatherIsRain = true;}
}

void ClearRainEnvironment()
{
	if (!isEntity(&Rain))
	{
		CreateEntity(&Rain,"rain");
	}

	FillRainData();
	Rain.NumDrops = 0.0;
	Rain.DropLength = 0.1;
	Rain.isDone = "";

	bWeatherIsRain = false;
}

void FillRainData()
{
	aref aRain1; makearef(aRain1, WeathersNH.Rain);
	aref aRainbow1; makearef(aRainbow1, WeathersNH.Rainbow);

	Rain.Clear = "";
	DeleteAttribute(&Rain,"");

	Rain.NumDrops = Whr_GetLong(aRain1,"NumDrops");
	Rain.Color = Whr_GetColor(aRain1,"Color");
	Rain.DropLength = Whr_GetFloat(aRain1,"DropLength");
	Rain.Height = Whr_GetFloat(aRain1,"Height");
	Rain.Radius = Whr_GetFloat(aRain1,"Radius");
	Rain.Speed = Whr_GetFloat(aRain1,"Speed");
	Rain.Jitter = Whr_GetFloat(aRain1,"Jitter");
	Rain.WindSpeedJitter = Whr_GetFloat(aRain1,"WindSpeedJitter");
	Rain.TimeBlend = Whr_GetLong(aRain1,"TimeBlend");
	Rain.MaxBlend = Whr_GetLong(aRain1,"MaxBlend");

	Rain.RainDrops.DropsNearNum = Whr_GetLong(aRain1, "DropsNearNum");
	Rain.RainDrops.DropsFarNum = Whr_GetLong(aRain1, "DropsFarNum");
	Rain.RainDrops.DropsNearRadius = Whr_GetFloat(aRain1, "DropsNearRadius");
	Rain.RainDrops.DropsFarRadius = Whr_GetFloat(aRain1, "DropsFarRadius");
	Rain.RainDrops.DropsLifeTime = Whr_GetFloat(aRain1, "DropsLifeTime");
	Rain.RainDrops.DropsSize = Whr_GetFloat(aRain1, "DropsSize");
	Rain.RainDrops.DropsColor = Whr_GetLong(aRain1, "DropsColor");
	Rain.RainDrops.DropsTexture = Whr_GetString(aRain1, "DropsTexture");

	Rain.Rainbow.Enable = Whr_GetLong(aRainbow1,"Enable");
	Rain.Rainbow.Texture = Whr_GetString(aRainbow1,"Texture");

}

void MoveRainToLayers(string sExecuteLayer, string sRealizeLayer)
{
	LayerDelObject("execute",&Rain);
	LayerDelObject("realize",&Rain);
	LayerDelObject(SEA_EXECUTE,&Rain);
	LayerDelObject(SEA_REALIZE,&Rain);

	LayerAddObject(sExecuteLayer, &Rain, 65537);
	LayerAddObject(sRealizeLayer, &Rain, 65537);
}

void ShowRain(int bShow)
{
	SendMessage(Rain,"ll",1,bShow);
}
