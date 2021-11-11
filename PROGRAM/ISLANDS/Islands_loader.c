/////////////////////////
// GOF 1.2
/////////////////////////

#define DIRECTSAILDEBUG	1;

#define DIR_PORTBOW 1
#define DIR_FORWARD 2
#define DIR_STARBOW 3
#define DIR_STAR 4
#define DIR_PORT 5
#define DIR_PORTSTERN 6
#define DIR_ABAFT 7
#define DIR_STARSTERN 8

// #define DIRECTENCOUNTERCHANCE 50   // chance in percent that an encounter fleet appears every hour
#define DIRECTENCOUNTERDISTANCE 1000 // distance from player at which random ships appear

float wmDistanceNow = 75000.0;

//Boyer POTC change
string DiscoveredIsland(float discoveryDistance)
{
    DSGTrace("DiscoveredIsland worldMap.playerShipX = " + worldMap.playerShipX);
	string sReturn = WDM_NONE_ISLAND;
	int nextisland = getWMclosestIsland();
	if(nextisland < 0)
		return sReturn;
	DSGTrace("DiscoveredIsland distance = " + wmDistanceNow);
	if(wmDistanceNow > discoveryDistance)
		return sReturn;
	sReturn = Islands[nextisland].id;
	DSGTrace("DiscoveredIsland found: " + sReturn);
	return sReturn;
}

void CheckIslandChange()
{
	int nextisland = getRTclosestIsland();

	DSGTrace("CheckIslandChange: nextisland=" + nextisland);

	if (nextisland != FindIsland(pchar.location))
	{
		//only switch if pretty close
		ref rIsland = GetIslandByIndex(nextisland);//makeref(rIsland, Islands[inum]);
		string sNewIslandId = rIsland.id;
		string sIslandNow = pchar.location;

		float RTplayerShipX = getRelRTplayerShipX(pchar.location);
		float RTplayerShipZ = getRelRTplayerShipZ(pchar.location);

		float distToCurIsland;
		if (pchar.location == WDM_NONE_ISLAND) distToCurIsland = 50000.0;
		else distToCurIsland = GetDistance2D(RTplayerShipX, RTplayerShipZ, stf(worldMap.islands.(sIslandNow).position.x), stf(worldMap.islands.(sIslandNow).position.z));
		float distToClosestIsland = GetDistance2D(RTplayerShipX, RTplayerShipZ, stf(worldMap.islands.(sNewIslandId).position.x), stf(worldMap.islands.(sNewIslandId).position.z));

		DSGTrace("CheckIslandChange: distToCurIsland=" + distToCurIsland + ", distToClosestIsland=" + distToClosestIsland);

		//only change if getting close
		if (distToClosestIsland * 2 > distToCurIsland)
		{
			return;
		}

		// aborts function if enemyships near, so that you aren't teleported out of an engagement
		int enemydist = 0;
		int nextenemy = 0;
		int enemyDistLimit   = 1000;
		int neutralDistLimit = 1000;

		nextenemy = FindClosestShipofRel(GetMainCharacterIndex(), &enemydist, RELATION_ENEMY);
		DSGTrace("DirectsailCheck; next enemy: "+nextenemy + " dist: "+enemydist);
		if(nextenemy!= -1 && enemydist<enemyDistLimit )
		{
			DSGTrace("Directsail aborted due to hostile ship, dist = " + enemydist);	// LDH - 07Jan09
			return;
		}

		// Jan 07, same for neutral ships
		nextenemy = FindClosestShipofRel(GetMainCharacterIndex(), &enemydist, RELATION_NEUTRAL);
		DSGTrace("DirectsailCheck; next neutral ship: "+nextenemy + " dist: "+enemydist);
		if(nextenemy!= -1 && enemydist<neutralDistLimit && Characters[nextenemy].ship.type != SHIP_FORT ) // LDH added fort check 08Jan09
		{
		  DSGTrace("Directsail aborted due to neutral ship, dist = " + enemydist);	// LDH added logit to trace - 07Jan09
		  return;
		}

		// looks like this doesn't always work, so I added another check for being in battle
		if(!bMapEnter) {
			DSGTrace("Directsail aborted in battle");
			return;
		}		// LDH added logit to trace 07Jan09

		ChangeSeaMapNew(sNewIslandId);

		DSGTrace("Directsail GOF would trigger here");

	}
 }

float getRTplayerShipX()
{
	float zeroX = MakeFloat(worldMap.zeroX);
	float SeaX = stf(pchar.Ship.Pos.x);
	int scale = WDM_MAP_TO_SEA_SCALE;

	float RTplayerShipX = (SeaX/scale) + zeroX;
	return RTplayerShipX;
}

float getRTplayerShipZ()
{
	float zeroZ = MakeFloat(worldMap.zeroZ);
	float SeaZ = stf(pchar.Ship.Pos.z);
	int scale = WDM_MAP_TO_SEA_SCALE;

	float RTplayerShipZ = (SeaZ/scale) + zeroZ;
	return RTplayerShipZ;
}

float getRelRTplayerShipX(string Island)
{
	/*
		Function to determine the x position of the player given an island
	*/

	float zeroX = MakeFloat(worldMap.islands.(Island).position.rx);
	float SeaX = stf(pchar.Ship.Pos.x);
	int scale = WDM_MAP_TO_SEA_SCALE;

	float RTplayerShipX = (SeaX/scale) + zeroX;
	return RTplayerShipX;
}

float getRelRTplayerShipZ(string Island)
{
	/*
		Function to determine the z position of the player given an island
	*/

	float zeroZ = MakeFloat(worldMap.islands.(Island).position.rz);
	float SeaZ = stf(pchar.Ship.Pos.z);
	int scale = WDM_MAP_TO_SEA_SCALE;

	float RTplayerShipZ = (SeaZ/scale) + zeroZ;
	return RTplayerShipZ;
}

float getRTplayerShipAY()
{
	float RTplayerShipAY = stf(pchar.Ship.Ang.y);
	return RTplayerShipAY;
}

//Boyer add
int getWMclosestIsland()
{
	DSGTrace("getWMclosestIsland. curr island: " + pchar.location);

	float RTplayerShipX = worldMap.playerShipX;
	float RTplayerShipZ = worldMap.playerShipZ:

	float distance;

	int nextisland = -1;
	ref rIsland;
	string islandTemp;
	float scale = 1 / WDM_MAP_TO_SEA_SCALE;

	wmDistanceNow = 75000.0;

	for (int inum=0; inum<MAX_ISLANDS; inum++)
	{
		rIsland = GetIslandByIndex(inum);//makeref(rIsland, Islands[inum]);
		if(!CheckAttribute(rIsland, "id")) {
            //trace("Islands_loader.c no id: " + inum);
            continue;
		}
		islandTemp = rIsland.id;

		float isX = stf(worldMap.islands.(islandTemp).position.x);
		float isZ = stf(worldMap.islands.(islandTemp).position.z);		

		if(!CheckAttribute(&worldMap, "islands." + islandTemp)) continue;
		distance = GetDistance2D(RTplayerShipX, RTplayerShipZ, isX, isZ);
		distance = distance / scale;
		DSGTrace("getWMclosestIsland. islandTemp=" + islandTemp + " at " + isX + "," + isZ + ", distance=" + distance + ", wmDistanceNow=" + wmDistanceNow);

		if (distance < wmDistanceNow)
		{
			wmDistanceNow = distance
			nextisland = inum;
		}
	}

	DSGTrace("getWMclosestIsland. closest island: " + Islands[nextisland].id + ", idx=" + nextisland);

	return nextisland;
}

int getRTclosestIsland()
{
	DSGTrace("getRTclosestIsland. pchar.location: " + pchar.location);
	DSGTrace("getRTclosestIsland. curr island: " + worldMap.island);

	float RTplayerShipX = getRelRTplayerShipX(pchar.location);
	float RTplayerShipZ = getRelRTplayerShipZ(pchar.location);

	DSGTrace("Ship position: " + RTplayerShipX + "," + RTplayerShipZ)

	float distance;
	float iDistanceNow = 50000.0;

	int nextisland = -1;
	ref rIsland;
	string islandTemp;

	for (int inum=0; inum<ISLANDS_QUANTITY; inum++)
	{
		rIsland = GetIslandByIndex(inum);//makeref(rIsland, Islands[inum]);
		if(!CheckAttribute(rIsland, "id")) continue;
		islandTemp = rIsland.id;

		float isX = stf(worldMap.islands.(islandTemp).position.x);
		float isZ = stf(worldMap.islands.(islandTemp).position.z);			

		if(!CheckAttribute(&worldMap, "islands." + islandTemp)) continue;
		distance = GetDistance2D(RTplayerShipX, RTplayerShipZ, isX, isZ);

		DSGTrace("getWMclosestIsland. islandTemp=" + islandTemp + " at " + isX + "," + isZ + ", distance=" + distance + ", wmDistanceNow=" + iDistanceNow);

		if (distance < iDistanceNow)
		{
			iDistanceNow = distance
			nextisland = inum;
		}
	}

	DSGTrace("getRTclosestIsland. closest island: " + Islands[nextisland].id + ", idx=" + nextisland);

	return nextisland;
}

void ChangeSeaMapNew(string sNewIslandId)
{
	//ShipsInit();
	DeleteSeaEnvironment();
	SetEventHandler("Sea2Sea_Reload", "Sea2Sea_Reload", 0);
	PostEvent("Sea2Sea_Reload", 1);

}

void Sea2Sea_Reload()
{
	DelEventHandler("Sea2Sea_Reload", "Sea2Sea_Reload");

	object seaLoginToSea;

	float CX = getRelRTplayerShipX(pchar.location);
	float CZ = getRelRTplayerShipZ(pchar.location);
	float CAY = getRTplayerShipAY();
	int nextisland = getRTclosestIsland();
	ref rIsland = GetIslandByIndex(nextisland);
	string CIsland = rIsland.id;

	float psX = MakeFloat(CX);
	float psZ = MakeFloat(CZ);
	float ix = MakeFloat(worldMap.islands.(CIsland).position.x);
	float iz = MakeFloat(worldMap.islands.(CIsland).position.z);
	int scale = WDM_MAP_TO_SEA_SCALE;

	seaLoginToSea.playerGroup.x = (psX - ix)*scale;
	seaLoginToSea.playerGroup.z = (psZ - iz)*scale;
	seaLoginToSea.playerGroup.ay = CAY;
	seaLoginToSea.island = CIsland;

	string imageName = "loading\sea.tga.tx";
	seaLoginToSea.imageName = imageName;

	SeaLogin(&seaLoginToSea);

	worldMap.playerShipX = getRTplayerShipX();
	worldMap.playerShipZ = getRTplayerShipZ();
	worldMap.playerShipAY = getRTplayerShipAY();
	worldMap.island = rIsland.id;
	worldMap.zeroX = ix;
	worldMap.zeroZ = iz;

}

void DSGTrace(string logtext)
{
	if (DIRECTSAILDEBUG)
	{
		LogIt(logtext);
	}
	Trace("DSGOF: " + logtext);
	return;
}

int ClosestDirFA(float dir)
{
	/*
		Function to determine the heading of the ship to only direct sail to islands roughly 
		ahead and not necessarily the closest

	*/
    float aX[6];
    float aZ[6];
    //Bug in compiler...array inits don't work in .c files
    aX[0] = -1.0; aX[1] = 0.0; aX[2] = 1.0; aX[3] = -1.0; aX[4] = 0.0; aX[5] = 1.0;
    aZ[0] = 0.5; aZ[1] = 1.0; aZ[2] = 0.5; aZ[3] = 0.0; aZ[4] = -1.0; aZ[5] = 0.0;

    float maxDot = -99999999.0;
    int nRet = 0;
    for(int i = 0; i < 6; i++) {
        float v = GetAngleY(aX[i], aZ[i]);
        float t = GetDotProduct(v, dir);
        if (t > maxDot) {
             nRet = i + 1;
             maxDot = t;
         }
    }
    if(nRet < 4)
        nRet = DIR_FORWARD;
    else
        nRet = DIR_ABAFT;

    return nRet;
}