
int Whr_InitDayStorm(int n)
{
// ====================================================================
// Stormy1

	Weathers[n].id = "Storm01";
	Weathers[n].Hour.Min = 6.00001;
	Weathers[n].Hour.Max = 10;
	Weathers[n].Lighting = "storm1";
	Weathers[n].LightingLm = "storm";
	Weathers[n].InsideBack = "s";
	Weathers[n].Sounds.Sea.Postfix = "_storm";

	Weathers[n].Storm = true;
	Weathers[n].Tornado = true;
	Weathers[n].Shark = false;
	Weathers[n].Lights = 1;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = true;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 4;
	Weathers[n].Lightning.SubTexY = 1;
	Weathers[n].Lightning.ScaleX = 0.7;
	Weathers[n].Lightning.ScaleY = 1.0;
	Weathers[n].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	Weathers[n].Sky.Dir = "weather\skies\Storm01\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.004;
	Weathers[n].Sky.Rotate.Max = 0.008;
	Weathers[n].Sky.Size = 1000.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 14000.0;
	Weathers[n].Fog.Start = 0.0;
	Weathers[n].Fog.Density = 0.030;
	Weathers[n].Fog.IslandDensity = 0.0045;
	Weathers[n].Fog.SeaDensity = 0.019;
	Weathers[n].Fog.Color = argb(0,33,40,50);
	Weathers[n].SpecialSeaFog.Color = argb(0,33,40,50);
	Weathers[n].Bak.Fog.Color = argb(0,33,40,50);
	Weathers[n].Bak.SpecialSeaFog.Color = argb(0,33,40,50);

	Weathers[n].Rain.NumDrops = 10000;
	Weathers[n].Rain.Color = argb(0,63,63,63);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 129;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.09;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(55, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,189,209,228);
	Weathers[n].Sun.Ambient = argb(0,33,33,55);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(90.0);
	Weathers[n].Sun.HeightAngle = 0.95;
	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,67,65,67);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,0,0);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.07;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.1;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,0,0,10);
	Weathers[n].Sea.Pena.Color = argb(0,100,100,100);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.07;
	Weathers[n].Sea.Bump.Ang = 2.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 23.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 1.0;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	Weathers[n].Sea.Harmonics.h1 = "0.0,10.0,0.1202,80.87,-68.00";
	Weathers[n].Sea.Harmonics.h2 = "1.57,10.0,2.1002,82.28,88.00";
	Weathers[n].Sea.Harmonics.h3 = "0.47,7.0,2.2002,82.28,68.00";
	Weathers[n].Sea.Harmonics.h4 = "0.27,47.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h5 = "1.27,57.0,0.0702,82.28,188.00";
	Weathers[n].Sea.Harmonics.h6 = "2.27,57.0,0.0302,82.28,88.00";
	Weathers[n].Sea.Harmonics.h7 = "2.27,37.0,0.1402,82.28,188.00";
	Weathers[n].Sea.Harmonics.h8 = "2.77,17.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h9 = "1.77,17.0,0.1002,82.28,188.00";
	Weathers[n].Sea.Harmonics.h10 = "1.0,14.0,0.5002,82.28,28.00";

	Weathers[n].Sun.Reflection.Enable = false;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.03;
	Weathers[n].Sea2.PosShift = 2.0;

	Weathers[n].Sea2.WaterColor = argb(0, 0, 0, 40);
	Weathers[n].Sea2.SkyColor = argb(0, 155, 155, 155);

	Weathers[n].Sea2.Reflection = 0.5;
	Weathers[n].Sea2.Transparency = 0.05;
	Weathers[n].Sea2.Frenel = 0.6;
	Weathers[n].Sea2.Attenuation = 0.1;

	Weathers[n].Sea2.Amp1 = 60.0;
	Weathers[n].Sea2.AnimSpeed1 = 0.0;
	Weathers[n].Sea2.Scale1 = 0.07;
	Weathers[n].Sea2.MoveSpeed1 = "15.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 2.5;
	Weathers[n].Sea2.AnimSpeed2 = 4.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamK = 0.01;
	Weathers[n].Sea2.FoamV = 20.0;
	Weathers[n].Sea2.FoamUV = 0.2;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 3.59;
	Weathers[n].Wind.Speed.Min = 14.0;
	Weathers[n].Wind.Speed.Max = 18.0;
	
	Weathers[n].doLagoon = false;

	n++;

// ====================================================================
// Overcast2

	Weathers[n].id = "Storm02";
	Weathers[n].Hour.Min = 10.00001;
	Weathers[n].Hour.Max = 18;
	Weathers[n].Lighting = "storm2";
	Weathers[n].LightingLm = "storm";
	Weathers[n].InsideBack = "s";
	Weathers[n].Sounds.Sea.Postfix = "_storm";

	Weathers[n].Storm = true;
	Weathers[n].Tornado = true;
	Weathers[n].Shark = false;
	Weathers[n].Lights = 1;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = true;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 4;
	Weathers[n].Lightning.SubTexY = 1;
	Weathers[n].Lightning.ScaleX = 0.7;
	Weathers[n].Lightning.ScaleY = 1.0;
	Weathers[n].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	Weathers[n].Sky.Dir = "weather\skies\Storm01\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.004;
	Weathers[n].Sky.Rotate.Max = 0.008;
	Weathers[n].Sky.Size = 1000.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 14000.0;
	Weathers[n].Fog.Start = 0.0;
	Weathers[n].Fog.Density = 0.030;
	Weathers[n].Fog.IslandDensity = 0.0045;
	Weathers[n].Fog.SeaDensity = 0.019;
	Weathers[n].Fog.Color = argb(0,33,40,50);
	Weathers[n].SpecialSeaFog.Color = argb(0,33,40,50);
	Weathers[n].Bak.Fog.Color = argb(0,33,40,50);
	Weathers[n].Bak.SpecialSeaFog.Color = argb(0,33,40,50);

	Weathers[n].Rain.NumDrops = 10000;
	Weathers[n].Rain.Color = argb(0,63,63,63);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 129;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.09;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(55, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,189,209,228);
	Weathers[n].Sun.Ambient = argb(0,33,33,55);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(90.0);
	Weathers[n].Sun.HeightAngle = 0.95;
	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,67,65,67);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,0,0);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.07;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.1;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,0,0,10);
	Weathers[n].Sea.Pena.Color = argb(0,100,100,100);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.07;
	Weathers[n].Sea.Bump.Ang = 2.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 23.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 1.0;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	Weathers[n].Sea.Harmonics.h1 = "0.0,10.0,0.1202,80.87,-68.00";
	Weathers[n].Sea.Harmonics.h2 = "1.57,10.0,2.1002,82.28,88.00";
	Weathers[n].Sea.Harmonics.h3 = "0.47,7.0,2.2002,82.28,68.00";
	Weathers[n].Sea.Harmonics.h4 = "0.27,47.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h5 = "1.27,57.0,0.0702,82.28,188.00";
	Weathers[n].Sea.Harmonics.h6 = "2.27,57.0,0.0302,82.28,88.00";
	Weathers[n].Sea.Harmonics.h7 = "2.27,37.0,0.1402,82.28,188.00";
	Weathers[n].Sea.Harmonics.h8 = "2.77,17.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h9 = "1.77,17.0,0.1002,82.28,188.00";
	Weathers[n].Sea.Harmonics.h10 = "1.0,14.0,0.5002,82.28,28.00";

	Weathers[n].Sun.Reflection.Enable = false;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.03;
	Weathers[n].Sea2.PosShift = 2.0;

	Weathers[n].Sea2.WaterColor = argb(0, 0, 0, 40);
	Weathers[n].Sea2.SkyColor = argb(0, 155, 155, 155);

	Weathers[n].Sea2.Reflection = 0.5;
	Weathers[n].Sea2.Transparency = 0.05;
	Weathers[n].Sea2.Frenel = 0.6;
	Weathers[n].Sea2.Attenuation = 0.1;

	Weathers[n].Sea2.Amp1 = 60.0;
	Weathers[n].Sea2.AnimSpeed1 = 0.0;
	Weathers[n].Sea2.Scale1 = 0.07;
	Weathers[n].Sea2.MoveSpeed1 = "15.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 2.5;
	Weathers[n].Sea2.AnimSpeed2 = 4.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamK = 0.01;
	Weathers[n].Sea2.FoamV = 20.0;
	Weathers[n].Sea2.FoamUV = 0.2;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 3.59;
	Weathers[n].Wind.Speed.Min = 14.0;
	Weathers[n].Wind.Speed.Max = 18.0;
	
	Weathers[n].doLagoon = false;

	n++;

// ====================================================================
//

	Weathers[n].id = "Storm03";
	Weathers[n].Hour.Min = 18.00001;
	Weathers[n].Hour.Max = 22;
	Weathers[n].Lighting = "storm3";
	Weathers[n].LightingLm = "storm";
	Weathers[n].InsideBack = "s";
	Weathers[n].Sounds.Sea.Postfix = "_storm";

	Weathers[n].Storm = true;
	Weathers[n].Tornado = true;
	Weathers[n].Shark = false;
	Weathers[n].Lights = 1;
	Weathers[n].Night = true;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = true;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 4;
	Weathers[n].Lightning.SubTexY = 1;
	Weathers[n].Lightning.ScaleX = 0.7;
	Weathers[n].Lightning.ScaleY = 1.0;
	Weathers[n].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	Weathers[n].Sky.Dir = "weather\skies\Storm03\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.004;
	Weathers[n].Sky.Rotate.Max = 0.008;
	Weathers[n].Sky.Size = 1000.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 14000.0;
	Weathers[n].Fog.Start = 0.0;
	Weathers[n].Fog.Density = 0.030;
	Weathers[n].Fog.IslandDensity = 0.0045;
	Weathers[n].Fog.SeaDensity = 0.019;
	Weathers[n].Fog.Color = argb(0,33,40,50);
	Weathers[n].SpecialSeaFog.Color = argb(0,33,40,50);
	Weathers[n].Bak.Fog.Color = argb(0,33,40,50);
	Weathers[n].Bak.SpecialSeaFog.Color = argb(0,33,40,50);

	Weathers[n].Rain.NumDrops = 10000;
	Weathers[n].Rain.Color = argb(0,63,63,63);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 129;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.09;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(55, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,189,209,228);
	Weathers[n].Sun.Ambient = argb(0,33,33,55);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(90.0);
	Weathers[n].Sun.HeightAngle = 0.95;
	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,67,65,67);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,0,0);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.07;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.1;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,0,0,10);
	Weathers[n].Sea.Pena.Color = argb(0,100,100,100);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.07;
	Weathers[n].Sea.Bump.Ang = 2.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 23.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 1.0;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	Weathers[n].Sea.Harmonics.h1 = "0.0,10.0,0.1202,80.87,-68.00";
	Weathers[n].Sea.Harmonics.h2 = "1.57,10.0,2.1002,82.28,88.00";
	Weathers[n].Sea.Harmonics.h3 = "0.47,7.0,2.2002,82.28,68.00";
	Weathers[n].Sea.Harmonics.h4 = "0.27,47.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h5 = "1.27,57.0,0.0702,82.28,188.00";
	Weathers[n].Sea.Harmonics.h6 = "2.27,57.0,0.0302,82.28,88.00";
	Weathers[n].Sea.Harmonics.h7 = "2.27,37.0,0.1402,82.28,188.00";
	Weathers[n].Sea.Harmonics.h8 = "2.77,17.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h9 = "1.77,17.0,0.1002,82.28,188.00";
	Weathers[n].Sea.Harmonics.h10 = "1.0,14.0,0.5002,82.28,28.00";

	Weathers[n].Sun.Reflection.Enable = false;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.03;
	Weathers[n].Sea2.PosShift = 2.0;

	Weathers[n].Sea2.WaterColor = argb(0, 0, 0, 40);
	Weathers[n].Sea2.SkyColor = argb(0, 155, 155, 155);

	Weathers[n].Sea2.Reflection = 0.5;
	Weathers[n].Sea2.Transparency = 0.05;
	Weathers[n].Sea2.Frenel = 0.6;
	Weathers[n].Sea2.Attenuation = 0.1;

	Weathers[n].Sea2.Amp1 = 60.0;
	Weathers[n].Sea2.AnimSpeed1 = 0.0;
	Weathers[n].Sea2.Scale1 = 0.07;
	Weathers[n].Sea2.MoveSpeed1 = "15.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 2.5;
	Weathers[n].Sea2.AnimSpeed2 = 4.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamK = 0.01;
	Weathers[n].Sea2.FoamV = 20.0;
	Weathers[n].Sea2.FoamUV = 0.2;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 3.59;
	Weathers[n].Wind.Speed.Min = 14.0;
	Weathers[n].Wind.Speed.Max = 18.0;
	
	Weathers[n].doLagoon = false;

	n++;

// ====================================================================
//

	Weathers[n].id = "Storm04";
	Weathers[n].Hour.Min = 22.00001;
	Weathers[n].Hour.Max = 6;
	Weathers[n].Lighting = "storm4";
	Weathers[n].LightingLm = "storm";
	Weathers[n].InsideBack = "s";
	Weathers[n].Sounds.Sea.Postfix = "_storm";

	Weathers[n].Storm = true;
	Weathers[n].Tornado = true;
	Weathers[n].Shark = false;
	Weathers[n].Lights = 1;
	Weathers[n].Night = true;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = true;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 4;
	Weathers[n].Lightning.SubTexY = 1;
	Weathers[n].Lightning.ScaleX = 0.7;
	Weathers[n].Lightning.ScaleY = 1.0;
	Weathers[n].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	Weathers[n].Sky.Dir = "weather\skies\Storm04\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.004;
	Weathers[n].Sky.Rotate.Max = 0.008;
	Weathers[n].Sky.Size = 1000.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 14000.0;
	Weathers[n].Fog.Start = 0.0;
	Weathers[n].Fog.Density = 0.030;
	Weathers[n].Fog.IslandDensity = 0.0045;
	Weathers[n].Fog.SeaDensity = 0.019;
	Weathers[n].Fog.Color = argb(0,33,40,50);
	Weathers[n].SpecialSeaFog.Color = argb(0,33,40,50);
	Weathers[n].Bak.Fog.Color = argb(0,33,40,50);
	Weathers[n].Bak.SpecialSeaFog.Color = argb(0,33,40,50);

	Weathers[n].Rain.NumDrops = 10000;
	Weathers[n].Rain.Color = argb(0,63,63,63);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 129;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.09;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(43, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,189,209,228);
	Weathers[n].Sun.Ambient = argb(0,33,33,55);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(90.0);
	Weathers[n].Sun.HeightAngle = 0.95;
	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,67,65,67);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,0,0);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.07;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.1;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,0,0,10);
	Weathers[n].Sea.Pena.Color = argb(0,100,100,100);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.07;
	Weathers[n].Sea.Bump.Ang = 2.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 23.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 1.0;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	Weathers[n].Sea.Harmonics.h1 = "0.0,10.0,0.1202,80.87,-68.00";
	Weathers[n].Sea.Harmonics.h2 = "1.57,10.0,2.1002,82.28,88.00";
	Weathers[n].Sea.Harmonics.h3 = "0.47,7.0,2.2002,82.28,68.00";
	Weathers[n].Sea.Harmonics.h4 = "0.27,47.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h5 = "1.27,57.0,0.0702,82.28,188.00";
	Weathers[n].Sea.Harmonics.h6 = "2.27,57.0,0.0302,82.28,88.00";
	Weathers[n].Sea.Harmonics.h7 = "2.27,37.0,0.1402,82.28,188.00";
	Weathers[n].Sea.Harmonics.h8 = "2.77,17.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h9 = "1.77,17.0,0.1002,82.28,188.00";
	Weathers[n].Sea.Harmonics.h10 = "1.0,14.0,0.5002,82.28,28.00";

	Weathers[n].Sun.Reflection.Enable = false;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.03;
	Weathers[n].Sea2.PosShift = 2.0;

	Weathers[n].Sea2.WaterColor = argb(0, 0, 0, 15);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.7;
	Weathers[n].Sea2.Transparency = 0.05;
	Weathers[n].Sea2.Frenel = 0.6;
	Weathers[n].Sea2.Attenuation = 0.2;

	Weathers[n].Sea2.Amp1 = 60.0;
	Weathers[n].Sea2.AnimSpeed1 = 0.0;
	Weathers[n].Sea2.Scale1 = 0.07;
	Weathers[n].Sea2.MoveSpeed1 = "15.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 2.5;
	Weathers[n].Sea2.AnimSpeed2 = 4.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamK = 0.01;
	Weathers[n].Sea2.FoamV = 20.0;
	Weathers[n].Sea2.FoamUV = 0.2;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;


	Weathers[n].Wind.Angle = 3.59;
	Weathers[n].Wind.Speed.Min = 14.0;
	Weathers[n].Wind.Speed.Max = 18.0;
	
	Weathers[n].doLagoon = false;

	n++;

// Stormy1

	Weathers[n].id = "Storm01_add";
	Weathers[n].Hour.Min = 6.00001;
	Weathers[n].Hour.Max = 10;
	Weathers[n].Lighting = "storm1";
	Weathers[n].LightingLm = "storm";
	Weathers[n].InsideBack = "s";
	Weathers[n].Sounds.Sea.Postfix = "_storm";

	Weathers[n].Storm = true;
	Weathers[n].skip = true;
	Weathers[n].Tornado = true;
	Weathers[n].Shark = false;
	Weathers[n].Lights = 1;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = true;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 4;
	Weathers[n].Lightning.SubTexY = 1;
	Weathers[n].Lightning.ScaleX = 0.7;
	Weathers[n].Lightning.ScaleY = 1.0;
	Weathers[n].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	Weathers[n].Sky.Dir = "weather\skies\Storm01\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.004;
	Weathers[n].Sky.Rotate.Max = 0.008;
	Weathers[n].Sky.Size = 1000.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 14000.0;
	Weathers[n].Fog.Start = 0.0;
	Weathers[n].Fog.Density = 0.030;
	Weathers[n].Fog.IslandDensity = 0.0045;
	Weathers[n].Fog.SeaDensity = 0.019;
	Weathers[n].Fog.Color = argb(0,33,40,50);
	Weathers[n].SpecialSeaFog.Color = argb(0,33,40,50);
	Weathers[n].Bak.Fog.Color = argb(0,33,40,50);
	Weathers[n].Bak.SpecialSeaFog.Color = argb(0,33,40,50);

	Weathers[n].Rain.NumDrops = 10000;
	Weathers[n].Rain.Color = argb(0,63,63,63);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 129;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.09;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(45, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,189,209,228);
	Weathers[n].Sun.Ambient = argb(0,33,33,55);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(90.0);
	Weathers[n].Sun.HeightAngle = 0.95;
	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,67,65,67);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,0,0);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.07;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.1;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,0,0,10);
	Weathers[n].Sea.Pena.Color = argb(0,100,100,100);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.07;
	Weathers[n].Sea.Bump.Ang = 2.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 23.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 1.0;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	Weathers[n].Sea.Harmonics.h1 = "0.0,10.0,0.1202,80.87,-68.00";
	Weathers[n].Sea.Harmonics.h2 = "1.57,10.0,2.1002,82.28,88.00";
	Weathers[n].Sea.Harmonics.h3 = "0.47,7.0,2.2002,82.28,68.00";
	Weathers[n].Sea.Harmonics.h4 = "0.27,47.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h5 = "1.27,57.0,0.0702,82.28,188.00";
	Weathers[n].Sea.Harmonics.h6 = "2.27,57.0,0.0302,82.28,88.00";
	Weathers[n].Sea.Harmonics.h7 = "2.27,37.0,0.1402,82.28,188.00";
	Weathers[n].Sea.Harmonics.h8 = "2.77,17.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h9 = "1.77,17.0,0.1002,82.28,188.00";
	Weathers[n].Sea.Harmonics.h10 = "1.0,14.0,0.5002,82.28,28.00";

	Weathers[n].Sun.Reflection.Enable = false;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.03;
	Weathers[n].Sea2.PosShift = 2.0;

	Weathers[n].Sea2.WaterColor = argb(0, 0, 0, 40);
	Weathers[n].Sea2.SkyColor = argb(0, 155, 155, 155);

	Weathers[n].Sea2.Reflection = 0.5;
	Weathers[n].Sea2.Transparency = 0.05;
	Weathers[n].Sea2.Frenel = 0.6;
	Weathers[n].Sea2.Attenuation = 0.1;

	Weathers[n].Sea2.Amp1 = 60.0;
	Weathers[n].Sea2.AnimSpeed1 = 0.0;
	Weathers[n].Sea2.Scale1 = 0.07;
	Weathers[n].Sea2.MoveSpeed1 = "15.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 2.5;
	Weathers[n].Sea2.AnimSpeed2 = 4.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamK = 0.01;
	Weathers[n].Sea2.FoamV = 20.0;
	Weathers[n].Sea2.FoamUV = 0.2;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 3.59;
	Weathers[n].Wind.Speed.Min = 14.0;
	Weathers[n].Wind.Speed.Max = 18.0;
	
	Weathers[n].doLagoon = false;

	n++;

// ====================================================================
// Overcast2

	Weathers[n].id = "Storm02_add";
	Weathers[n].Hour.Min = 10.00001;
	Weathers[n].Hour.Max = 18;
	Weathers[n].Lighting = "storm2";
	Weathers[n].LightingLm = "storm";
	Weathers[n].InsideBack = "s";
	Weathers[n].Sounds.Sea.Postfix = "_storm";

	Weathers[n].Storm = true;
	Weathers[n].skip = true;
	Weathers[n].Tornado = true;
	Weathers[n].Shark = false;
	Weathers[n].Lights = 1;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = true;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 4;
	Weathers[n].Lightning.SubTexY = 1;
	Weathers[n].Lightning.ScaleX = 0.7;
	Weathers[n].Lightning.ScaleY = 1.0;
	Weathers[n].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	Weathers[n].Sky.Dir = "weather\skies\Storm02\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.004;
	Weathers[n].Sky.Rotate.Max = 0.008;
	Weathers[n].Sky.Size = 1000.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 14000.0;
	Weathers[n].Fog.Start = 0.0;
	Weathers[n].Fog.Density = 0.030;
	Weathers[n].Fog.IslandDensity = 0.0045;
	Weathers[n].Fog.SeaDensity = 0.019;
	Weathers[n].Fog.Color = argb(0,33,40,50);
	Weathers[n].SpecialSeaFog.Color = argb(0,33,40,50);
	Weathers[n].Bak.Fog.Color = argb(0,33,40,50);
	Weathers[n].Bak.SpecialSeaFog.Color = argb(0,33,40,50);
	//Wathers[n].Fog.Color = argb(0,100,95,85);

	Weathers[n].Rain.NumDrops = 10000;
	Weathers[n].Rain.Color = argb(0,63,63,63);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 129;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.09;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(45, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,189,209,228);
	Weathers[n].Sun.Ambient = argb(0,33,33,55);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(90.0);
	Weathers[n].Sun.HeightAngle = 0.95;
	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,67,65,67);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,0,0);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.07;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.1;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,0,0,10);
	Weathers[n].Sea.Pena.Color = argb(0,100,100,100);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.07;
	Weathers[n].Sea.Bump.Ang = 2.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 23.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 1.0;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	Weathers[n].Sea.Harmonics.h1 = "0.0,10.0,0.1202,80.87,-68.00";
	Weathers[n].Sea.Harmonics.h2 = "1.57,10.0,2.1002,82.28,88.00";
	Weathers[n].Sea.Harmonics.h3 = "0.47,7.0,2.2002,82.28,68.00";
	Weathers[n].Sea.Harmonics.h4 = "0.27,47.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h5 = "1.27,57.0,0.0702,82.28,188.00";
	Weathers[n].Sea.Harmonics.h6 = "2.27,57.0,0.0302,82.28,88.00";
	Weathers[n].Sea.Harmonics.h7 = "2.27,37.0,0.1402,82.28,188.00";
	Weathers[n].Sea.Harmonics.h8 = "2.77,17.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h9 = "1.77,17.0,0.1002,82.28,188.00";
	Weathers[n].Sea.Harmonics.h10 = "1.0,14.0,0.5002,82.28,28.00";

	Weathers[n].Sun.Reflection.Enable = false;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.03;
	Weathers[n].Sea2.PosShift = 0.3;

	Weathers[n].Sea2.WaterColor = argb(0, 0, 0, 40);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.8;
	Weathers[n].Sea2.Transparency = 0.05;
	Weathers[n].Sea2.Frenel = 0.3;
	Weathers[n].Sea2.Attenuation = 0.3;

	Weathers[n].Sea2.Amp1 = 60.0;
	Weathers[n].Sea2.AnimSpeed1 = 0.0;
	Weathers[n].Sea2.Scale1 = 0.07;
	Weathers[n].Sea2.MoveSpeed1 = "15.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 2.5;
	Weathers[n].Sea2.AnimSpeed2 = 4.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamK = 0.01;
	Weathers[n].Sea2.FoamV = 20.0;
	Weathers[n].Sea2.FoamUV = 0.2;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;

	Weathers[n].Wind.Angle = 3.59;
	Weathers[n].Wind.Speed.Min = 14.0;
	Weathers[n].Wind.Speed.Max = 18.0;
	
	Weathers[n].doLagoon = false;

	n++;

// ====================================================================
//

	Weathers[n].id = "Storm03_add";
	Weathers[n].Hour.Min = 18.00001;
	Weathers[n].Hour.Max = 22;
	Weathers[n].Lighting = "storm3";
	Weathers[n].LightingLm = "storm";
	Weathers[n].InsideBack = "s";
	Weathers[n].Sounds.Sea.Postfix = "_storm";

	Weathers[n].Storm = true;
	Weathers[n].skip = true;
	Weathers[n].Tornado = true;
	Weathers[n].Shark = false;
	Weathers[n].Lights = 1;
	Weathers[n].Night = true;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = true;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 4;
	Weathers[n].Lightning.SubTexY = 1;
	Weathers[n].Lightning.ScaleX = 0.7;
	Weathers[n].Lightning.ScaleY = 1.0;
	Weathers[n].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	Weathers[n].Sky.Dir = "weather\skies\Storm03\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.004;
	Weathers[n].Sky.Rotate.Max = 0.008;
	Weathers[n].Sky.Size = 1000.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 14000.0;
	Weathers[n].Fog.Start = 0.0;
	Weathers[n].Fog.Density = 0.030;
	Weathers[n].Fog.IslandDensity = 0.0045;
	Weathers[n].Fog.SeaDensity = 0.019;
	Weathers[n].Fog.Color = argb(0,33,40,50);
	Weathers[n].SpecialSeaFog.Color = argb(0,33,40,50);
	Weathers[n].Bak.Fog.Color = argb(0,33,40,50);
	Weathers[n].Bak.SpecialSeaFog.Color = argb(0,33,40,50);

	Weathers[n].Rain.NumDrops = 10000;
	Weathers[n].Rain.Color = argb(0,63,63,63);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 129;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.09;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(50, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,189,209,228);
	Weathers[n].Sun.Ambient = argb(0,33,33,55);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(90.0);
	Weathers[n].Sun.HeightAngle = 0.95;
	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,67,65,67);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,0,0);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.07;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.1;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,0,0,10);
	Weathers[n].Sea.Pena.Color = argb(0,100,100,100);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.07;
	Weathers[n].Sea.Bump.Ang = 2.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 23.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 1.0;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	Weathers[n].Sea.Harmonics.h1 = "0.0,10.0,0.1202,80.87,-68.00";
	Weathers[n].Sea.Harmonics.h2 = "1.57,10.0,2.1002,82.28,88.00";
	Weathers[n].Sea.Harmonics.h3 = "0.47,7.0,2.2002,82.28,68.00";
	Weathers[n].Sea.Harmonics.h4 = "0.27,47.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h5 = "1.27,57.0,0.0702,82.28,188.00";
	Weathers[n].Sea.Harmonics.h6 = "2.27,57.0,0.0302,82.28,88.00";
	Weathers[n].Sea.Harmonics.h7 = "2.27,37.0,0.1402,82.28,188.00";
	Weathers[n].Sea.Harmonics.h8 = "2.77,17.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h9 = "1.77,17.0,0.1002,82.28,188.00";
	Weathers[n].Sea.Harmonics.h10 = "1.0,14.0,0.5002,82.28,28.00";

	Weathers[n].Sun.Reflection.Enable = false;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.03;
	Weathers[n].Sea2.PosShift = 0.8;

	Weathers[n].Sea2.WaterColor = argb(0, 0, 0, 40);
	Weathers[n].Sea2.SkyColor = argb(0, 155, 155, 155);

	Weathers[n].Sea2.Reflection = 0.2;
	Weathers[n].Sea2.Transparency = 0.05;
	Weathers[n].Sea2.Frenel = 0.6;
	Weathers[n].Sea2.Attenuation = 0.2;

	Weathers[n].Sea2.Amp1 = 60.0;
	Weathers[n].Sea2.AnimSpeed1 = 0.0;
	Weathers[n].Sea2.Scale1 = 0.07;
	Weathers[n].Sea2.MoveSpeed1 = "15.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 2.5;
	Weathers[n].Sea2.AnimSpeed2 = 4.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamK = 0.01;
	Weathers[n].Sea2.FoamV = 20.0;
	Weathers[n].Sea2.FoamUV = 0.2;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;


	Weathers[n].Wind.Angle = 3.59;
	Weathers[n].Wind.Speed.Min = 14.0;
	Weathers[n].Wind.Speed.Max = 18.0;
	
	Weathers[n].doLagoon = false;
	
	n++;

// ====================================================================
//

	Weathers[n].id = "Storm04_add";
	Weathers[n].Hour.Min = 22.00001;
	Weathers[n].Hour.Max = 6;
	Weathers[n].Lighting = "storm4";
	Weathers[n].LightingLm = "storm";
	Weathers[n].InsideBack = "s";
	Weathers[n].Sounds.Sea.Postfix = "_storm";

	Weathers[n].Storm = true;
	Weathers[n].skip = true;
	Weathers[n].Tornado = true;
	Weathers[n].Shark = false;
	Weathers[n].Lights = 1;
	Weathers[n].Night = true;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = true;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning_storm.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 4;
	Weathers[n].Lightning.SubTexY = 1;
	Weathers[n].Lightning.ScaleX = 0.7;
	Weathers[n].Lightning.ScaleY = 1.0;
	Weathers[n].Lightning.Flash.Texture = "Weather\lightning\flash.tga.tx";

	Weathers[n].Sky.Dir = "weather\skies\Storm04\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.004;
	Weathers[n].Sky.Rotate.Max = 0.008;
	Weathers[n].Sky.Size = 1000.0;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 14000.0;
	Weathers[n].Fog.Start = 0.0;
	Weathers[n].Fog.Density = 0.030;
	Weathers[n].Fog.IslandDensity = 0.0045;
	Weathers[n].Fog.SeaDensity = 0.019;
	Weathers[n].Fog.Color = argb(0,33,40,50);
	Weathers[n].SpecialSeaFog.Color = argb(0,33,40,50);
	Weathers[n].Bak.Fog.Color = argb(0,33,40,50);
	Weathers[n].Bak.SpecialSeaFog.Color = argb(0,33,40,50);

	Weathers[n].Rain.NumDrops = 10000;
	Weathers[n].Rain.Color = argb(0,63,63,63);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 129;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.09;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(37, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,189,209,228);
	Weathers[n].Sun.Ambient = argb(0,33,33,55);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(90.0);
	Weathers[n].Sun.HeightAngle = 0.95;
	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,255,255,255);
	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = false;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,67,65,67);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,0,0);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.07;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.1;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,0,0,10);
	Weathers[n].Sea.Pena.Color = argb(0,100,100,100);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.07;
	Weathers[n].Sea.Bump.Ang = 2.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 23.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 1.0;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,0,0,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	Weathers[n].Sea.Harmonics.h1 = "0.0,10.0,0.1202,80.87,-68.00";
	Weathers[n].Sea.Harmonics.h2 = "1.57,10.0,2.1002,82.28,88.00";
	Weathers[n].Sea.Harmonics.h3 = "0.47,7.0,2.2002,82.28,68.00";
	Weathers[n].Sea.Harmonics.h4 = "0.27,47.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h5 = "1.27,57.0,0.0702,82.28,188.00";
	Weathers[n].Sea.Harmonics.h6 = "2.27,57.0,0.0302,82.28,88.00";
	Weathers[n].Sea.Harmonics.h7 = "2.27,37.0,0.1402,82.28,188.00";
	Weathers[n].Sea.Harmonics.h8 = "2.77,17.0,0.0502,82.28,288.00";
	Weathers[n].Sea.Harmonics.h9 = "1.77,17.0,0.1002,82.28,188.00";
	Weathers[n].Sea.Harmonics.h10 = "1.0,14.0,0.5002,82.28,28.00";

	Weathers[n].Sun.Reflection.Enable = false;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.03;
	Weathers[n].Sea2.PosShift = 2.0;

	Weathers[n].Sea2.WaterColor = argb(0, 0, 0, 15);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.7;
	Weathers[n].Sea2.Transparency = 0.05;
	Weathers[n].Sea2.Frenel = 0.6;
	Weathers[n].Sea2.Attenuation = 0.2;

	Weathers[n].Sea2.Amp1 = 60.0;
	Weathers[n].Sea2.AnimSpeed1 = 0.0;
	Weathers[n].Sea2.Scale1 = 0.07;
	Weathers[n].Sea2.MoveSpeed1 = "15.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 2.5;
	Weathers[n].Sea2.AnimSpeed2 = 4.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "1.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamK = 0.01;
	Weathers[n].Sea2.FoamV = 20.0;
	Weathers[n].Sea2.FoamUV = 0.2;
	Weathers[n].Sea2.FoamTexDisturb = 0.7;


	Weathers[n].Wind.Angle = 3.59;
	Weathers[n].Wind.Speed.Min = 14.0;
	Weathers[n].Wind.Speed.Max = 18.0;
	
	Weathers[n].doLagoon = false;

	n++;

	return n;
}
