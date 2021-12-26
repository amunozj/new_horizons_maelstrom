void Whr_InitStateVariable()
{

	WeathersNH.id = "11 Hour";
	WeathersNH.Hour.Min = 11;
	WeathersNH.Hour.Max = 11;
	WeathersNH.Lighting = "day11";
	WeathersNH.LightingLm = "day1";
	WeathersNH.InsideBack = "d";
	//WeathersNH.Sounds.Sea.Postfix = "_day";

	WeathersNH.Storm = false;
	WeathersNH.Tornado = false;
	WeathersNH.Shark = true;
	WeathersNH.Lights = 0;
	WeathersNH.Night = false;

	WeathersNH.Shadow.Density.Head = argb(255,96,96,96);
	WeathersNH.Shadow.Density.Foot = argb(255,96,96,64);

	WeathersNH.Lightning.Enable = false;
	WeathersNH.Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	WeathersNH.Lightning.FlickerTime = 32;
	WeathersNH.Lightning.SubTexX = 1;
	WeathersNH.Lightning.SubTexY = 1;

	WeathersNH.Sky.Dir = "weather\skies\11\";
	WeathersNH.Sky.Color = argb(0,255,255,255);
	WeathersNH.Sky.Rotate.Min = 0.0;
	WeathersNH.Sky.Rotate.Max = 0.0;
	WeathersNH.Sky.Size = 1000.0;
	WeathersNH.Sky.Angle = 0.0;

	WeathersNH.Planets.enable = false;

	WeathersNH.Fog.Enable = true;
	WeathersNH.Fog.Height = 150;
	WeathersNH.Fog.Start = 10;
	WeathersNH.Fog.Density = 0.0003;
	WeathersNH.Fog.IslandDensity = 0.0003;
	WeathersNH.Fog.SeaDensity = 0.00006;
	//WeathersNH.Fog.Color = argb(0,115,140,155);
	WeathersNH.Fog.Color = argb(0,135,168,205);

	WeathersNH.Rain.NumDrops = 0;
	WeathersNH.Rain.Color = argb(0,73,73,73);
	WeathersNH.Rain.DropLength = 2.12;
	WeathersNH.Rain.Height = 30.0;
	WeathersNH.Rain.Radius = 30.0;
	WeathersNH.Rain.Speed = 18.0;
	WeathersNH.Rain.Jitter = 0.4;
	WeathersNH.Rain.WindSpeedJitter = 0.5;
	WeathersNH.Rain.MaxBlend = 49;
	WeathersNH.Rain.TimeBlend = 2000;

    WeathersNH.Rain.DropsNearNum = 0;
    WeathersNH.Rain.DropsFarNum = 0;
    WeathersNH.Rain.DropsNearRadius = 12.0;
    WeathersNH.Rain.DropsFarRadius = 55.0;
    WeathersNH.Rain.DropsLifeTime = 0.25;
    WeathersNH.Rain.DropsSize = 0.07;
    WeathersNH.Rain.DropsTexture = "Weather_GOF\rain_drops.tga.tx";
    WeathersNH.Rain.DropsColor = argb(63, 255, 255, 255);

	WeathersNH.Rainbow.Enable = false;
	WeathersNH.Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	WeathersNH.Sun.Color = argb(0,130,130,100);
	WeathersNH.Sun.Ambient = argb(0,105,105,90);
	WeathersNH.Sun.AzimuthAngle = Degree2Radian(150.0);
	WeathersNH.Sun.HeightAngle = 0.70;
	WeathersNH.Sun.Glow.Enable = true;
	WeathersNH.Sun.Glow.Dist = 3500.0;
	WeathersNH.Sun.Glow.Size = 1250.0;
	WeathersNH.Sun.Glow.RotateSpeed = 1.0;
	WeathersNH.Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	WeathersNH.Sun.Glow.DecayTime = 8.0;
	WeathersNH.Sun.Glow.TechniqueNoZ = "sunglow_noz";
	WeathersNH.Sun.Glow.TechniqueZ = "sunglow_z";
	WeathersNH.Sun.Glow.Color = argb(0,255,255,255);
	WeathersNH.Sun.Overflow.Enable = false;
	WeathersNH.Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	WeathersNH.Sun.Overflow.Color = argb(0, 100, 100, 100);
	WeathersNH.Sun.Overflow.Size = 5500.0;
	WeathersNH.Sun.Overflow.Technique = "sunoverflow";
	WeathersNH.Sun.Overflow.Start = 0.7;
	WeathersNH.Sun.Reflection.Enable = true;
	WeathersNH.Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	WeathersNH.Sun.Reflection.Technique = "sunglow_z";
	WeathersNH.Sun.Reflection.Dist = 3500.0;
	WeathersNH.Sun.Reflection.Size = 500.0;
	WeathersNH.Sun.Reflection.Color = argb(0, 200, 200, 200);
	WeathersNH.Sun.Flare.Enable = true;
	WeathersNH.Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	WeathersNH.Sun.Flare.Dist = 3500.0;
	WeathersNH.Sun.Flare.TexSizeX = 2;
	WeathersNH.Sun.Flare.TexSizeY = 2;
	WeathersNH.Sun.Flare.Technique = "sunflare";
	WeathersNH.Sun.Flare.Scale = 2.0;
	WeathersNH.Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	WeathersNH.Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	WeathersNH.Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	WeathersNH.Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	WeathersNH.Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	WeathersNH.Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	WeathersNH.Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	WeathersNH.Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	WeathersNH.Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	WeathersNH.Sea.GF2MX.Water.Color = argb(0,25,55,80);
	WeathersNH.Sea.GF2MX.Bump.Tile = 0.05;
	WeathersNH.Sea.GF2MX.Bump.AnimSpeed = 7.0;
	WeathersNH.Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	WeathersNH.Sea.Transparency = 0.9;
	WeathersNH.Sea.FrenelCoefficient = 0.5;
	WeathersNH.Sea.WaterReflection = 0.9;
	WeathersNH.Sea.WaterAttenuation = 0.2;
	WeathersNH.Sea.Sky.Color = argb(0,190,190,190);
	WeathersNH.Sea.Water.Color = argb(0,25,55,80);
	WeathersNH.Sea.Pena.Color = argb(0,175,175,155);
	WeathersNH.Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	WeathersNH.Sea.Bump.Tile = 0.04;
	WeathersNH.Sea.Bump.Ang = 0.0;
	WeathersNH.Sea.Bump.Speed = 0.01;
	WeathersNH.Sea.Bump.AnimSpeed = 15.0;
	WeathersNH.Sea.Bump.Scale = 2.0;
	WeathersNH.Sea.SunRoad.Start = 0.99;
	WeathersNH.Sea.SunRoad.Color1 = argb(0,128,55,0);
	WeathersNH.Sea.SunRoad.Color2 = argb(0,255,200,150);
	WeathersNH.Sea.SunRoad.Power = 0.2;
	//????, ???????, ?????? ????? ? ??????, ????????? ??????? ?????, ???????? ?????
	WeathersNH.Sea.Harmonics.h1 = "0.0, 2.5, 3.0, 0.0, 10.00";
	WeathersNH.Sea.Harmonics.h2 = "90.0, 5.0, 1.5, 0.0, 50.00";
	WeathersNH.Sea.Harmonics.h3 = "45.0, 8.0, 2.5, 0.0, 200.00";
	WeathersNH.Sea.Harmonics.h4 = "13.0, 6.0, 1.0, 0.0, 150.00";
	WeathersNH.Sea.Harmonics.h5 = "90.0, 50.0, 0.2, 0.0, 20.00";

	WeathersNH.Sun.Reflection.Enable = true;
	WeathersNH.Sun.Reflection.Texture = "weather\sun\reflection\refl_day.tga.tx";
	WeathersNH.Sun.Reflection.Technique = "sunreflection";
	WeathersNH.Sun.Reflection.Dist = 3500.0;
	WeathersNH.Sun.Reflection.Size = 500.0;
	WeathersNH.Sun.Reflection.Color = argb(200, 200, 200, 200);

	WeathersNH.Sea2.BumpScale = 0.05; //?????? ?????
	WeathersNH.Sea2.PosShift = 0.0; //??????????????? ????

	//WeathersNH.Sea2.WaterColor = argb(0, 10, 90, 120);
	//WeathersNH.Sea2.SkyColor = argb(0, 255, 255, 255);

	WeathersNH.Sea2.WaterColor = argb(0, 25, 55, 80);
	WeathersNH.Sea2.SkyColor = argb(0, 205, 255, 255);

	WeathersNH.Sea2.Reflection = 0.9;
	WeathersNH.Sea2.Transparency = 0.9;
	WeathersNH.Sea2.Frenel = 0.45;
	WeathersNH.Sea2.Attenuation = 0.3;

	WeathersNH.Sea2.Amp1 = 7.0; //????????? 1 ?????
	WeathersNH.Sea2.AnimSpeed1 = 2.0; //???????? ????????
	WeathersNH.Sea2.Scale1 = 0.30; //??????? ?????
	WeathersNH.Sea2.MoveSpeed1 = "2.0, 0.0, 0.0"; //???????? ????????

	WeathersNH.Sea2.Amp2 = 1.1;
	WeathersNH.Sea2.AnimSpeed2 = 19.0;
	WeathersNH.Sea2.Scale2 = 3;
	WeathersNH.Sea2.MoveSpeed2 = "1.0, 0.0, 1.0";
	
	WeathersNH.Sea2.FoamK = 0.2;
	WeathersNH.Sea2.FoamV = 4.0;
	WeathersNH.Sea2.FoamUV = 0.2;
	WeathersNH.Sea2.FoamTexDisturb = 0.2;

	WeathersNH.Wind.Angle = 2.0;
	WeathersNH.Wind.Speed.Min = 4.0;
	WeathersNH.Wind.Speed.Max = 7.0;

	WeathersNH.Sea2.FoamEnable = true;	

}
