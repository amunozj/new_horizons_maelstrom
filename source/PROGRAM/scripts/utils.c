/////////////////////////
// GOF 1.2
/////////////////////////

#include "scripts\seaspeak.c" //Philippe
#include "scripts\food.c"
//int LowerSkillBooks = 0;
#define CHAR_ITEMS_WEIGHT        70
#define SPECIAL_S	"Strength"   //15
#define SPECIAL_P	"Perception"
#define SPECIAL_E	"Endurance"
#define SPECIAL_C	"Charisma"
#define SPECIAL_I	"Intellect"
#define SPECIAL_A	"Agility"
#define SPECIAL_L	"Luck"  //21

//#define REAL_SHIPS_QUANTITY 900

//object	RealShips[REAL_SHIPS_QUANTITY];
int	NationsRelations2MainCharacter[MAX_NATIONS];

//#20181102-03
void NationUpdate()
{
    UpdateRelations();
    if(bSeaActive)
    {
        RefreshBattleInterface(true);
    }
}

int GetSummonSkillFromName(ref _refCharacter, string skillName)
{
    int sumSkill;

    // boal 051104
    if (CheckAttribute(_refCharacter, "BakSkill." + skillName))
    {
        if (sti(_refCharacter.BakSkillCount.(skillName)) < 25 )
        {
            _refCharacter.BakSkillCount.(skillName) = sti(_refCharacter.BakSkillCount.(skillName)) + 1;
            return sti(_refCharacter.BakSkill.(skillName));
        }
    }

    sumSkill = GetSummonSkillFromNameSimple(_refCharacter, skillName);

    // boal 27.01.2004
 	sumSkill = ApplayNavyPenaltyToSkill(_refCharacter, skillName, sumSkill);
    // boal 27.01.2004 <--

    _refCharacter.BakSkill.(skillName)      =  sumSkill;
    _refCharacter.BakSkillCount.(skillName) = rand(5);

    return sumSkill;
}

int GetSummonSkillFromNameSimple(ref _refCharacter, string skillName)
{
    int sumSkill = GetCharacterSkillSimple(_refCharacter,skillName);

	if (sti(_refCharacter.index) == sti(pchar.index))
	{
	    int iOfficer = -1;
		int iOffSkill = -1;
		switch (skillName)
		{
			/*case SKILL_LEADERSHIP:
				iOfficer = sti(pchar.Fellows.Passengers.boatswain);
			break;
			case SKILL_SAILING:
				iOfficer = sti(pchar.Fellows.Passengers.navigator);
			break;
			case SKILL_CANNONS:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;
			case SKILL_ACCURACY:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;
			case SKILL_GRAPPLING:
				iOfficer = sti(pchar.Fellows.Passengers.boatswain);
			break;
			case SKILL_DEFENCE:
				iOfficer = sti(pchar.Fellows.Passengers.doctor);
			break;
			case SKILL_REPAIR:
				iOfficer = sti(pchar.Fellows.Passengers.carpenter);
			break;
			case SKILL_COMMERCE:
				iOfficer = sti(pchar.Fellows.Passengers.treasurer);
			break;*/
		}

		if(iOfficer != -1)
		{
			iOffSkill = GetCharacterSkillSimple(&characters[iOfficer], skillName);
			if (iOffSkill > sumSkill)
			{
				sumSkill = iOffSkill;
			}
		}
	}
	return sumSkill;
}

int ApplayNavyPenaltyToSkill(ref _refCharacter, string skillName, int sumSkill)
{
    if (IsCompanion(_refCharacter) && GetRemovable(_refCharacter))//sti(_refCharacter.index) == GetMainCharacterIndex())
    {
        int sailSkill;

        /*if (skillName == SKILL_SAILING)
        {
            sailSkill = sumSkill;
        }
        else
        { */
            sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);
        //}

        int shipClass = GetCharacterShipClass(_refCharacter);
        int needSkill = GetShipClassNavySkill(shipClass);

        if (sailSkill < needSkill)
        {
			sailSkill = needSkill - sailSkill;
			sumSkill = sumSkill - sailSkill;
	        if (sumSkill < 1) sumSkill = 1;
        }
    }
    return  sumSkill;
}

int GetCharacterSkillSimple(ref _refCharacter, string skillName)
{
	if( !CheckAttribute(_refCharacter,"Skill."+skillName) ) return 1;
	int skillN = sti(_refCharacter.Skill.(skillName));

	bool   bHero = (sti(_refCharacter.index) == GetMainCharacterIndex());

    if (bHero || CheckAttribute(_refCharacter, "Payment")) //IsCompanion(_refCharacter) || IsOfficer(_refCharacter))
    {
        // Health
        if (bHero && MOD_SKILL_ENEMY_RATE > 1)
        {
            if (isSelfTypeSkill(skillName))
            {
                skillN = skillN + 5*(GetHealthNum(_refCharacter) - 6); // max -5
            }
        }

		float iLev1Bonus, iLev2Bonus, iLev3Bonus, iLev12Bonus, iLev15Bonus, iLev25Bonus, iLev35Bonus
		//strange you can put float's in a function that expects ints
		//if (LowerSkillBooks) {
		//	//JA: I thought the skill bonues stacking to 60% was too much
		//	iLev1Bonus = 1;
		//	iLev2Bonus = 1;
		//	iLev3Bonus = 1;
		//	iLev12Bonus = 0.5;
		//	iLev15Bonus = 0.8;
		//	iLev25Bonus = 1;
		//	iLev35Bonus = 1.5;
		//} else {
			//original skill bonuses
			iLev1Bonus = 1;
			iLev2Bonus = 2;
			iLev3Bonus = 3;
			iLev12Bonus = 1.2;
			iLev15Bonus = 1.5;
			iLev25Bonus = 2.5;
			iLev35Bonus = 3.5;
		//}
		/*
		// itmname_bookleader_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "bookleader_1", iLev1Bonus);

    	// itmname_booklight_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "booklight_1", iLev1Bonus);

    	// itmname_bookfencing_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "bookfencing_1", iLev1Bonus);

    	// itmname_bookheavy_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, "bookheavy_1", iLev1Bonus);

    	// itmname_bookleader_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "bookleader_2", iLev2Bonus);

    	// itmname_booklight_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "booklight_2", iLev2Bonus);

    	// itmname_bookfencing_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "bookfencing_2", iLev2Bonus);

    	// itmname_bookheavy_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, "bookheavy_2", iLev2Bonus);

    	// itmname_bookleader_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "bookleader_3", iLev3Bonus);

    	// itmname_booklight_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "booklight_3", iLev3Bonus);

    	// itmname_bookfencing_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "bookfencing_3", iLev3Bonus);

    	// itmname_bookheavy_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, "bookheavy_3", iLev3Bonus);

    	// itmname_bookpistols_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_PISTOL, "bookpistols_1", iLev1Bonus);

    	// itmname_bookluck_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "bookluck_1", iLev1Bonus);

    	// itmname_bookstealth_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "bookstealth_1", iLev1Bonus);

    	// itmname_booknavigation_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SAILING, "booknavigation_1", iLev1Bonus);

    	// itmname_bookpistols_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_PISTOL, "bookpistols_2", iLev2Bonus);

    	// itmname_bookluck_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "bookluck_2", iLev2Bonus);

    	// itmname_bookstealth_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "bookstealth_2", iLev2Bonus);

    	// itmname_booknavigation_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SAILING, "booknavigation_2", iLev2Bonus);

    	// itmname_bookpistols_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_PISTOL, "bookpistols_3", iLev3Bonus);

    	// itmname_bookluck_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "bookluck_3", iLev3Bonus);

    	// itmname_bookstealth_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "bookstealth_3", iLev3Bonus);

    	// itmname_booknavigation_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SAILING, "booknavigation_3", iLev3Bonus);

    	// itmname_bookaccurate_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_ACCURACY, "bookaccurate_1", iLev1Bonus);

    	// itmname_bookcannon_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_CANNONS, "bookcannon_1", iLev1Bonus);

    	// itmname_bookgrapple_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_GRAPPLING, "bookgrapple_1", iLev1Bonus);

    	// itmname_defend_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_DEFENCE, "bookdefend_1", iLev1Bonus);

    	// itmname_bookaccurate_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_ACCURACY, "bookaccurate_2", iLev2Bonus);

    	// itmname_bookcannon_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_CANNONS, "bookcannon_2", iLev2Bonus);

    	// itmname_bookgrapple_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_GRAPPLING, "bookgrapple_2", iLev2Bonus);

    	// itmname_defend_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_DEFENCE, "bookdefend_2", iLev2Bonus);

    	// itmname_bookaccurate_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_ACCURACY, "bookaccurate_3", iLev3Bonus);

    	// itmname_bookcannon_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_CANNONS, "bookcannon_3", iLev3Bonus);

    	// itmname_bookgrapple_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_GRAPPLING, "bookgrapple_3", iLev3Bonus);

    	// itmname_defend_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_DEFENCE, "bookdefend_3", iLev3Bonus);

    	// itmname_bookrepairs_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_REPAIR, "bookrepairs_1", iLev1Bonus);

    	// itmname_bookmoney_1
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_COMMERCE, "bookmoney_1", iLev1Bonus);

    	// itmname_bookrepairs_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_REPAIR, "bookrepairs_2", iLev2Bonus);

    	// itmname_bookmoney_2
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_COMMERCE, "bookmoney_2", iLev2Bonus);

    	// itmname_bookrepairs_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_REPAIR, "bookrepairs_3", iLev3Bonus);

    	// itmname_bookmoney_3
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_COMMERCE, "bookmoney_3", iLev3Bonus);

		// itmname_bookwrestling
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "bookwrestling", iLev25Bonus);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "bookwrestling", iLev12Bonus);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, "bookwrestling", iLev12Bonus);

		//itmname_booklgtweapman
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "booklgtweapman", iLev25Bonus);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "booklgtweapman", iLev15Bonus);

		//itmname_bookmedweapman
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "bookmedweapman", iLev15Bonus);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "bookmedweapman", iLev35Bonus);

		//itmname_bookheavweapman
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "bookheavweapman", iLev15Bonus)
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, "bookheavweapman", iLev35Bonus);

		if (CheckAttribute(_refCharacter, "cirassId"))
		{
		    switch (Items[sti(_refCharacter.cirassId)].id)
		    {
		        case "suit_1":
                    skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "suit_1", iLev2Bonus);
		        break;
		        case "suit_2":
                    skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_COMMERCE, "suit_2", iLev2Bonus);
		        break;
		        case "suit_3":
                    skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "suit_3", iLev2Bonus);
		        break;
		        case "suit_4":
                    skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "suit_4", iLev2Bonus);
		        break;
		        case "suit_5":
                    skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_DEFENCE, "suit_5", iLev2Bonus);
		        break;
		        case "suit_6":
                    skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "suit_6", iLev2Bonus);
		        break;
		    }
		} */
        //Boyer fix...moved from GetCharacterSPECIALSimple

        skillN = skillN + SetCharacterSkillBySculArtefact(_refCharacter, skillName);
    	//  itmname_Coins
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Coins", -50);

        //End Boyer fix

    	// boal
    	if ( GetItemsWeight(_refCharacter) > GetMaxItemsWeight(_refCharacter))
    	{
   	        skillN -= 20;
    	}
	}
	// boal <--
	if (skillN <= 1) skillN = 1;
	if( skillN > SKILL_MAX ) skillN = SKILL_MAX;

	return skillN;
}

// boal 20.03.2004 -->
int GetShipClassNavySkill(int shipClass)
{
    int needSkill = 0;

    switch (shipClass)
    {
            case 1 : needSkill = 95; break;
            case 2 : needSkill = 80; break;
            case 3 : needSkill = 65; break;
            case 4 : needSkill = 40; break;
            case 5 : needSkill = 25; break;
            case 6 : needSkill = 1; break;
            case 7 : needSkill = 0; break;
    }
    return needSkill;
}

bool isSelfTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "SelfType." + _param);
}

int GetHealthNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.HP) + 9) / 10.0);

    return i;
}

// boal 15/01/04
int SetCharacterSkillByItem(ref _refCharacter, string _skillName, string _itemSkillName, string _item, int _addValue)
{
    if (_skillName == _itemSkillName &&	GetCharacterItem(_refCharacter, _item)>0)
	{
       return makeint(10*_addValue);
    }
    return 0;
}

int SetCharacterSkillBySculArtefact(ref _refCharacter, string _skillName)
{
    if (_skillName == SKILL_LEADERSHIP || _skillName == SKILL_ACCURACY || _skillName == SKILL_SAILING || _skillName == SKILL_GRAPPLING)
	{
       if (GetCharacterItem(_refCharacter, "sculMa1")>0 && GetCharacterItem(_refCharacter, "sculMa2")>0 && GetCharacterItem(_refCharacter, "sculMa3")>0)
       {
           switch (_skillName)
           {
               case  SKILL_LEADERSHIP:
                   return 20;
               break;
               case  SKILL_ACCURACY:
                   return 20;
               break;
               case  SKILL_SAILING:
                   return 30;
               break;
               case  SKILL_GRAPPLING:
                   return 20;
               break;
           }
       }
    }
    return 0;
}

float GetItemsWeight(ref _chref)
{
    return 0.0;
}

int GetMaxItemsWeight(ref _chref)
{
	if (CheckAttribute(_chref, "Skill.Fencing"))
    {
        int iBonus = 0;
        if (IsCharacterPerkOn(_chref, "Grus")) iBonus = 30;
        //GetCharacterSPECIAL
        iBonus = iBonus + CHAR_ITEMS_WEIGHT + GetCharacterSPECIALSimple(_chref, SPECIAL_S)*(GetCharacterSPECIALSimple(_chref, SPECIAL_E) + 12 - MOD_SKILL_ENEMY_RATE);
        return  iBonus;
    }
    else
    {
        return 10000;
    }
}

int GetCharacterSPECIALSimple(ref _refCharacter, string skillName)
{
	if (!CheckAttribute(_refCharacter,"SPECIAL."+skillName) )
    {
        return 3;
    }
	int skillN = sti(_refCharacter.SPECIAL.(skillName));
    // Health
    if (sti(_refCharacter.index) == GetMainCharacterIndex() && MOD_SKILL_ENEMY_RATE > 1)
    {
        skillN = skillN + GetHealthNum(_refCharacter) - 6; // max -5
    }
    // boal
    /*if (IsCompanion(_refCharacter) || IsOfficer(_refCharacter))
    {
	//Boyer fix...the following should be moved to GetCharacterSkillSimple

        //skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "jewelry9", 1);

	skillN = skillN + SetCharacterSkillBySculArtefact(_refCharacter, skillName);
    	//  itmname_Coins
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Coins", -50);

    	if (GetItemsWeight(_refCharacter) > GetMaxItemsWeight(_refCharacter))
    	{
  	        skillN -=2;
    	}
    	// boal 19.01.2004 <--
	} */
	// boal <--
	if (skillN <= 1) skillN = 1;
	if( skillN > SPECIAL_MAX ) skillN = SPECIAL_MAX;

	return skillN;
}

string FindRussianMoneyString(int imoney)
{
	string sMoney = imoney;
	int iLen1 = strlen(&sMoney) - 1;
	int iLen2 = strlen(&sMoney) - 2;

	string sChar1 = GetSymbol(&sMoney, iLen1);
	string sChar2 = GetSymbol(&sMoney, iLen2);

	if(false) //LanguageGetLanguage() != "Russian")
	{
		if(imoney == 1 || imoney == 0)
		{
			sMoney = XI_ConvertString("gold2");
		}
		else
		{
			sMoney = XI_ConvertString("gold1");
		}
	}
	else
	{
		if(imoney < 10)
		{
			switch (sChar1)
			{
				case "0":
					sMoney = XI_ConvertString("gold1");
				break;
				case "1":
					sMoney = XI_ConvertString("gold2");
				break;
				case "2":
					sMoney = XI_ConvertString("gold3");
				break;
				case "3":
					sMoney = XI_ConvertString("gold3");
				break;
				case "4":
					sMoney = XI_ConvertString("gold3");
				break;
				case "5":
					sMoney = XI_ConvertString("gold1");
				break;
				case "6":
					sMoney = XI_ConvertString("gold1");
				break;
				case "7":
					sMoney = XI_ConvertString("gold1");
				break;
				case "8":
					sMoney = XI_ConvertString("gold1");
				break;
				case "9":
					sMoney = XI_ConvertString("gold1");
				break;
			}
		}
		else
		{
			if(sChar2 == "1")
			{
				switch (sChar1)
				{
					case "0":
						sMoney = XI_ConvertString("gold1");
					break;
					case "1":
						sMoney = XI_ConvertString("gold1");
					break;
					case "2":
						sMoney = XI_ConvertString("gold1");
					break;
					case "3":
						sMoney = XI_ConvertString("gold1");
					break;
					case "4":
						sMoney = XI_ConvertString("gold1");
					break;
					case "5":
						sMoney = XI_ConvertString("gold1");
					break;
					case "6":
						sMoney = XI_ConvertString("gold1");
					break;
					case "7":
						sMoney = XI_ConvertString("gold1");
					break;
					case "8":
						sMoney = XI_ConvertString("gold1");
					break;
					case "9":
						sMoney = XI_ConvertString("gold1");
					break;
				}
			}
			else
			{
				switch (sChar1)
				{
					case "0":
						sMoney = XI_ConvertString("gold1");
					break;
					case "1":
						sMoney = XI_ConvertString("gold2");
					break;
					case "2":
						sMoney = XI_ConvertString("gold3");
					break;
					case "3":
						sMoney = XI_ConvertString("gold3");
					break;
					case "4":
						sMoney = XI_ConvertString("gold3");
					break;
					case "5":
						sMoney = XI_ConvertString("gold1");
					break;
					case "6":
						sMoney = XI_ConvertString("gold1");
					break;
					case "7":
						sMoney = XI_ConvertString("gold1");
					break;
					case "8":
						sMoney = XI_ConvertString("gold1");
					break;
					case "9":
						sMoney = XI_ConvertString("gold1");
					break;
				}
			}
		}
	}
	sMoney = MakeMoneyShow(imoney, MONEY_SIGN,MONEY_DELIVER) + " " + sMoney;
	return sMoney;
}

void SetNationRelations()
{
    Nations_SetAllFriends();

	SetNationRelationBoth(ENGLAND, PIRATE, RELATION_ENEMY);
	SetNationRelationBoth(ENGLAND, FRANCE, RELATION_NEUTRAL);

	SetNationRelationBoth(HOLLAND, PIRATE, RELATION_ENEMY);
	SetNationRelationBoth(FRANCE, PIRATE, RELATION_ENEMY);

	SetNationRelationBoth(SPAIN, ENGLAND, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, PIRATE, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, FRANCE, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, HOLLAND, RELATION_NEUTRAL);

    SetNationRelationBoth(HOLLAND, ENGLAND, RELATION_ENEMY);
    SetNationRelationBoth(HOLLAND, FRANCE, RELATION_FRIEND);

	pchar = GetMainCharacter();
	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(sti(pchar.nation), ENGLAND));
	SetNationRelation2MainCharacter(FRANCE,  GetNationRelation(sti(pchar.nation), FRANCE));
	SetNationRelation2MainCharacter(SPAIN,   GetNationRelation(sti(pchar.nation), SPAIN));
	SetNationRelation2MainCharacter(PIRATE,  GetNationRelation(sti(pchar.nation), PIRATE));
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(sti(pchar.nation), HOLLAND));
}

void Nations_SetAllFriends()
{
	int i;

	for(i=0;i<MAX_NATIONS_SQR;i++)
	{
		NationsRelations[i] = RELATION_FRIEND;
	}

	for(i=0;i<MAX_NATIONS;i++)
	{
		NationsRelations2MainCharacter[i] = RELATION_FRIEND;
	}
}

//ref GetRealShip(int iType)
//{
//	if(iType >= REAL_SHIPS_QUANTITY)
//	{
//		trace ("--- Wrong Ship Index. iType is " + iType);
//		Log_TestInfo("--- Wrong Ship Index. iType is " + iType);
//		//return &ShipsTypes[SHIP_TYPES_QUANTITY + 1];
//		return &ShipsTypes[SHIP_TYPES_QUANTITY]; // Boyer fix as index too big
//	}
//	return &RealShips[iType];
//}
