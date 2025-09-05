bool CheckEnemyCompanionDistance2GoAway(bool _loadForm)
{
	if (DISABLE_SAILTO_RESTRICTIONS) return true; // <-- ADD THIS
	
    aref	arUpdate;
	int		i, k, cn, iRelation;
	//#20180524-01 Remove unneeded sqrt
	float	fDistance, fMapDisable;
	string  attr;

	ref rCharacter, rFortCharacter, rShipCharacter;

	makearef(arUpdate, pchar.SeaAI.Update);

	if (!CheckAttribute(arUpdate, "Ships")) { return true; }
	if (!CheckAttribute(arUpdate, "Forts")) { return true; }

	aref aShips, aForts;
	aref aFort;
	aref aShip;

	makearef(aShips, arUpdate.Ships);
	makearef(aForts, arUpdate.Forts);

	// check forts for abordage
	int iShipsNum = GetAttributesNum(aShips);

	int iFortsNum = GetAttributesNum(aForts);
	int iFortMode;

	DeleteAttribute(pchar, "CheckEnemyCompanionDistance");
	for (k=1; k<COMPANION_MAX; k++)
	{
		cn = GetCompanionIndex(pchar, k);
		if( cn>=0 )
		{
            attr = "CompIDX" + k;
			rCharacter = GetCharacter(cn);
			if (!GetRemovable(rCharacter)) continue;

			for (i=0; i<iFortsNum; i++)
			{
				aFort = GetAttributeN(aForts, i);
				iRelation = sti(aFort.relation);

				rFortCharacter = GetCharacter(sti(aFort.idx));
				if (LAi_IsDead(rFortCharacter)) { continue; }
				iFortMode = sti(rFortCharacter.Fort.Mode);

				switch (iFortMode)
				{
					case FORT_NORMAL:
						if (iRelation == RELATION_ENEMY)
						{
						    //#20180524-01 Remove unneeded sqrt
						    fMapDisable =  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT *  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER_FORT;
		                    fDistance = Ship_GetDistance2DRel(rCharacter, rFortCharacter);
							if (fDistance < fMapDisable)
							{
							    if (!_loadForm) return false;
								pchar.CheckEnemyCompanionDistance.(attr)) = cn;
							}
						}
					break;
				}
			}
			// check ships for abordage
			for (i=0; i<iShipsNum; i++)
			{
				aShip = GetAttributeN(aShips, i);

				rShipCharacter = GetCharacter(sti(aShip.idx));
				iRelation = sti(aShip.relation);

				if (LAi_IsDead(rShipCharacter)) { continue; }
				if (iRelation != RELATION_ENEMY) { continue; }
		        //#20180524-01 Remove unneeded sqrt
                fMapDisable =  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER *  MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;
                fDistance = Ship_GetDistance2DRel(rCharacter, rShipCharacter);
                if (fDistance < fMapDisable)
				{
				    if (!_loadForm) return false;
					pchar.CheckEnemyCompanionDistance.(attr)) = cn;
				}
			}
		}
	}
	if (_loadForm && CheckAttribute(pchar, "CheckEnemyCompanionDistance"))
	{
		return false;
	}
	return true;
}