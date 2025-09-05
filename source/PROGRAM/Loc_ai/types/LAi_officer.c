/*
���: ������

	������������ �������:
		stay
		dialog
*/



#define LAI_TYPE_OFFICER		"officer"


//�������������
void LAi_type_officer_Init(aref chr)
{
	//����� ���
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_OFFICER;
	LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
	//��������� �������� ���������
	bool isMusk = false;
	string sAni = strcut(chr.model.animation, 0, 8);
	if (sAni == "mushketer")
        isMusk = true;
	if (isMusk && !CheckAttribute(chr, "isMusketer.weapon") && chr.index != getmaincharacterindex() && !isOfficer(chr))
	{
        while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
        {
            TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
        }
        while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
        {
            TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
        }
		GiveItem2Character(chr, "unarmed");
		EquipCharacterbyItem(chr, "unarmed");
		GiveItem2Character(chr, "mushket2x2");
		EquipCharacterbyItem(chr, "mushket2x2");
		chr.items.bullet = 300;
		chr.isMusketer = true;
		if (!CheckAttribute(chr, "MusketerDistance"))
			chr.MusketerDistance = 5.0 + frand(10.0);
		chr.isMusketer.weapon = true;
	}
	else
	{
		LAi_SetDefaultStayAnimation(chr);
	}
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_officer_CharacterUpdate(aref chr, float dltTime)
{
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return;
	if (sti(chr.index) < 0) return;		// LDH fix for negative index
	string btl = "";
    //Log_SetStringToLog("LAi_type_officer_CharacterUpdate "+chr.id ); //boal
	//��� ���������� ����������
	if(CheckAttribute(chr, "chr_ai.poison"))
	{
		if(LAi_GetCharacterRelHP(chr) < 0.8)
		{
			/*bool antidotUse = false;
			if(LAi_GetCharacterRelHP(chr) < 0.6)
			{
				if(GetCharacterItem(&Characters[sti(chr.index)], "potion4") > 0)
				{
					antidotUse = true;
					DoCharacterUsedItem(&Characters[sti(chr.index)], "potion4");
				}
			}
			if(!antidotUse)
			{
				if(GetCharacterItem(&Characters[sti(chr.index)], "potion3") > 0)
				{
					DoCharacterUsedItem(&Characters[sti(chr.index)], "potion3");
				}
			}*/
			//Levis:
			btl = FindAntidoteForCharacter(chr);
			DoCharacterUsedItem(&Characters[sti(chr.index)], btl);
		}
	}
	//��������� �� �������� ���������
	float dist = 0.0;
	float dhlt;
	if(!GetCharacterDistByChr3D(chr, GetMainCharacter(), &dist)) dist = -1.0;
	if(dist < 0.0)
	{
		LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
		return;
	}
	if(!LAi_IsBottleWork(chr))
	{
		if(LAi_GetCharacterRelHP(chr) < 0.6)
		{
			dhlt = LAi_GetCharacterMaxHP(chr) - LAi_GetCharacterHP(chr);
			btl = FindHealthForCharacter(&Characters[sti(chr.index)], dhlt);
			DoCharacterUsedItem(&Characters[sti(chr.index)], btl);
		}
	}
	//������� ��������
	if(chr.chr_ai.tmpl == LAI_TMPL_FOLLOW)
	{
		if(dist < 6.0)
		{
			LAi_type_officer_FindTarget(chr);
		}
	}else{
		if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
		{
			//������� �� ������������� ���������
			if(!LAi_IsBottleWork(chr))
			{
				if(rand(100) < (50 + 49*LAi_GetCharacterFightLevel(chr)))
				{
					int tmp; // NK
					float hlt = MinHealthPotionForCharacter(&Characters[sti(chr.index)], &tmp); // NK changed this function to also get idx. 04-09-08
					if(LAi_GetCharacterRelHP(chr) < 0.9) hlt = dhlt;
					dhlt = LAi_GetCharacterMaxHP(chr) - LAi_GetCharacterHP(chr);
					if(hlt <= dhlt)
					{
						btl = FindHealthForCharacter(&Characters[sti(chr.index)], dhlt);
						DoCharacterUsedItem(&Characters[sti(chr.index)], btl);
					}					
				}
			}
			//Levis let's make them use vegetal if there are enough enemies around
			if(CheckCharacterItem(chr,"vegetal"))
			{
				if(sti(GetAttribute(chr,"quest.vegetal_effect.active")) < 1)
				{
					if(FindNearEnemies(chr, 5, true) > 3)
					{
						UseVegetal(chr);
					}
				}
				if(sti(GetAttribute(chr,"quest.vegetal_effect.active")) > 1)
				{
					if(FindNearEnemies(chr, 5, true) > 6)
					{
						UseVegetal(chr);
					}
				}
			}
			//
			if(LAi_tmpl_fight_LostTarget(chr))
			{
				LAi_type_officer_FindTarget(chr);
		//JRH -->
				if(IsEquipcharacterByItem(chr, "pistolmket"))
				{
					PostEvent("mket_on_back", 1000, "i", chr);
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "blademketK"))
				{
					PostEvent("blademketK_as_gun", 1000, "i", chr);
					PostEvent("mket_on_back", 1500, "i", chr);	//if musket on hip
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "pistolmtoon"))
				{
					PostEvent("mtoon_on_back", 1000, "i", chr);
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "pistolmketB"))
				{
					PostEvent("mketB_on_back", 1000, "i", chr);
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "blademketB"))
				{
					PostEvent("blademketB_as_gun", 1000, "i", chr);
					PostEvent("mketB_on_back", 1500, "i", chr);	//if musket on hip
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "Arguebuse"))
				{
					PostEvent("Arguebuse_on_back", 1000, "i", chr);
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "pistolbbuss"))
				{
					PostEvent("bbuss_on_back", 1000, "i", chr);
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "pistol13"))
				{
					PostEvent("pistol13_on_back", 1000, "i", chr);
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "LongRifle_C"))
				{
					PostEvent("LongRifle_C_on_back", 1000, "i", chr);
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "LongRifle_H"))
				{
					PostEvent("LongRifle_H_on_back", 1000, "i", chr);
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}

				if(IsEquipCharacterByItem(chr, "battleax"))
				{
					PostEvent("bax_on_back", 1000, "i", chr);
					PostEvent("mguns_reset_check", 1000, "i", chr);
				}
		// <-- JRH
			}else{
				if(LAi_tmpl_fight_IsGo(chr))
				{
					if(dist > 12.0)
					{
						//���� ������������
						LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
					}
				}
			}
		}
	}
}

//�������� ��������� � �������
bool LAi_type_officer_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_officer_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_officer_TemplateComplite(aref chr, string tmpl)
{
	if(chr.chr_ai.tmpl != LAI_TMPL_FOLLOW) LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
}

//�������� � ������� ������� ������
void LAi_type_officer_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_officer_CanDialog(aref chr, aref by)
{
	// NK allow dlg in boarding 05-07-12 - if(LAi_IsBoardingProcess()) return false;
	//���� ��� �������, �� �������
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT) return false;
	//���������� �� ������
	return true;
}

//������ ������
void LAi_type_officer_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_officer_EndDialog(aref chr, aref by)
{
	LAi_CharacterRestoreAy(chr);
	LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
}

//�������� �������� ������� ���������
void LAi_type_officer_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� �������� ������������������ ���������
void LAi_type_officer_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� ���������
void LAi_type_officer_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}


//�������� ��������
void LAi_type_officer_Attacked(aref chr, aref by)
{
	//����� ����������
	if(!LAi_group_IsEnemy(chr, by)) return;
	float dist = -1.0;
	//��������� ����������� ����� ����
// boal ������ ������ ����, � �� ���� ������ �� �����
	/*if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
	{
		bool canChange = false;
		if(LAi_tmpl_fight_IsGo(chr)) canChange = true;
		if(LAi_tmpl_fight_LostTarget(chr)) canChange = true;
		if(LAi_tmpl_fight_NoActive(chr)) canChange = true;
		if(!canChange) return;
		dist = -1.0;
		if(!GetCharacterDistByChr3D(chr, by, &dist)) return;
		if(dist >= 0.0)
		{
			if(dist < 5.0) return;
		}
	}*/
	//���������� ��������� �� ������ ����������
	dist = -1.0;
	if(!GetCharacterDistByChr3D(chr, by, &dist)) return;
	if(dist < 0.0) return;
	if(dist > 20.0) return;
	//������������
	if(!LAi_tmpl_SetFight(chr, by))
	{
		LAi_type_officer_FindTarget(chr);
	}
}


void LAi_type_officer_FindTarget(aref chr)
{
	//�������� ������� ������
	int trg = LAi_group_GetTarget(chr);
	if(trg >= 0)
	{
		if(LAi_type_officer_CheckDists(chr, &Characters[trg]))
		{
			if(LAi_tmpl_SetFight(chr, &Characters[trg])) return;
		}
		//else { LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0); return; } // NK
		//if(DEBUGINFO) Log_SetStringToLog("YOU SHOULD NEVER SEE THIS. MWAHAHA.");
		trg = LAi_group_GetTarget(GetMainCharacter());
		if(trg >= 0)
		{
			if(LAi_type_officer_CheckDists(chr, &Characters[trg]))
			{
				if(LAi_tmpl_SetFight(chr, &Characters[trg])) return;
			}
			//else { LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0); } // NK
		}
	}
	trg = LAi_group_GetTarget(GetMainCharacter());
	if(trg >= 0)
	{
		if(LAi_type_officer_CheckDists(chr, &Characters[trg]))
		{
			if(!LAi_tmpl_SetFight(chr, &Characters[trg]))
			{
				//�������� ������������ ������
				LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
			}
		}
	}else{
		if(chr.chr_ai.tmpl != LAI_TMPL_FOLLOW)
		{
			LAi_tmpl_SetFollow(chr, GetMainCharacter(), -1.0);
		}
	}
}

bool LAi_type_officer_CheckDists(aref chr, aref trg)
{
	float dist = -1.0;
	if(!GetCharacterDistByChr3D(GetMainCharacter(), trg, &dist)) dist = -1.0;
	if(dist >= 0.0 && dist < OFFICER_TO_MCHR_DIST) // NK
	{
		if(!GetCharacterDistByChr3D(chr, trg, &dist)) dist = -1.0;
		if(dist >= 0.0 && dist < OFFICER_TO_TARGET_DIST) // NK
		{
			return true;
		}
	}
	return false;
}

