/*
���: ����, ���� ������, ����� ��������, ������������ � ������ ��� �����

	������������ �������:
		fight
		follow
		walk
		stay
		dialog
*/



#define LAI_TYPE_WARRIOR	"warrior"



//���������� ����� ���������
void LAi_warrior_SetCommander(aref chr, aref commander)
{
	chr.chr_ai.type.index = commander.index;
}

//��������� ��� ��������� ������� ��� �����
void LAi_warrior_DialogEnable(aref chr, bool isEnable)
{
	chr.chr_ai.type.dialog = isEnable;
}

//������� ����� ������ ��� ���������� �����
void LAi_warrior_SetStay(aref chr, bool isStay)
{
	chr.chr_ai.type.stay = isStay;
}

//�������������
void LAi_type_warrior_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_WARRIOR) isNew = true;
	}
	if(isNew == true)
	{
		//����� ���
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_WARRIOR;
		chr.chr_ai.type.stay = "0";
		chr.chr_ai.type.index = "";
		chr.chr_ai.type.dialog = "0";
		LAi_tmpl_stay_InitTemplate(chr);
	}else{
		if(!CheckAttribute(chr, "chr_ai.type.stay")) chr.chr_ai.type.stay = "0";
		if(!CheckAttribute(chr, "chr_ai.type.index")) chr.chr_ai.type.index = "";
		if(!CheckAttribute(chr, "chr_ai.type.dialog")) chr.chr_ai.type.dialog = "0";
	}
	bool isMusk = false;
		string sAni = "";
	if (CheckAttribute(chr, "model.animation"))
	{
		sAni = strcut(chr.model.animation, 0, 8);
		if (sAni == "mushketer")
			isMusk = true;
	}
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
		string sMush = "mushket";
		if (chr.model == "MusketeerEnglish_2") sMush = "mushket2x2";
		GiveItem2Character(chr, sMush);
		EquipCharacterbyItem(chr, sMush);
		chr.items.bullet = 300;
		chr.isMusketer = true;
		if (!CheckAttribute(chr, "MusketerDistance"))
			chr.MusketerDistance = 10.0 + frand(10.0);
	}
	else
	{
		LAi_SetDefaultStayAnimation(chr);
	}
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_warrior_CharacterUpdate(aref chr, float dltTime)
{
	int trg = -1;
	//������ �� ����� � �����������
	aref type;
	makearef(type, chr.chr_ai.type);
	// ccc special weapons, rearm disarmed chr. NK 05-07-01 fix chars who do not draw blade
	if(GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE)=="" && FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
	{
		EquipCharacterByItem(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE))
	}
	// ccc end
	//����������� ���������
	string btl = "";
	float dhlt;
	if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
	{
		//�����
		bool isValidate = false;
		trg = LAi_tmpl_fight_GetTarget(chr);
		if(trg >= 0)
		{
			if(LAi_group_ValidateTarget(chr, &Characters[trg]))
			{
				if(!LAi_tmpl_fight_LostTarget(chr))
				{
					isValidate = true;
				}
			}
		}
		if(!isValidate)
		{
			//���� ����� ����
			trg = LAi_group_GetTarget(chr);
			if(trg < 0)
			{
				//��������� � ����� ��������
				LAi_tmpl_stay_InitTemplate(chr);
				LAi_type_warrior_SetWateState(chr);
			}else{
				//������������ �� ����� ����
				LAi_tmpl_SetFight(chr, &Characters[trg]);
				if(rand(100) > 95)
				{
					LAi_type_warrior_PlaySound(chr);
				}
			}
		}
		//Levis:
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
		//Levis: potions
		if(!LAi_IsBottleWork(chr))
		{
			if(LAi_GetCharacterRelHP(chr) < 0.6)
			{
				dhlt = LAi_GetCharacterMaxHP(chr) - LAi_GetCharacterHP(chr);
				btl = FindHealthForCharacter(&Characters[sti(chr.index)], dhlt);
				DoCharacterUsedItem(&Characters[sti(chr.index)], btl);
			}
		}
	}else{
		//���� ����� ����
		trg = LAi_group_GetTarget(chr);
		if(trg >= 0)
		{
			//�������� �� ����� ����
			LAi_tmpl_SetFight(chr, &Characters[trg]);
			if(rand(100) > 95)
			{
				LAi_type_warrior_PlaySound(chr);
			}
		}else{
			if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
			{
				//����� � ��� ����
				LAi_type_warrior_SetWateState(chr);
			}

		}
	}
	//Levis: antidote
	if(CheckAttribute(chr, "chr_ai.poison"))
	{
		if(LAi_GetCharacterRelHP(chr) < 0.8)
		{
			//Levis:
			btl = FindAntidoteForCharacter(chr);
			DoCharacterUsedItem(&Characters[sti(chr.index)], btl);
		}
	}
}

//�������� ��������� � �������
bool LAi_type_warrior_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_warrior_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_warrior_TemplateComplite(aref chr, string tmpl)
{
}

//�������� � ������� ������� ������
void LAi_type_warrior_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_warrior_CanDialog(aref chr, aref by)
{
	if(sti(chr.chr_ai.type.dialog) == 0) return false;
	//���� ������ �����, �� ����������
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_FOLLOW) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_WALK) return true;
	return false;
}

//������ ������
void LAi_type_warrior_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_warrior_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
}

//�������� �������� ������� ���������
void LAi_type_warrior_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� �������� ������������������ ���������
void LAi_type_warrior_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� ���������
void LAi_type_warrior_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}


//�������� ��������
void LAi_type_warrior_Attacked(aref chr, aref by)
{
	//����� ����������
//Log_SetStringToLog("LAi_type_warrior_Attacked "+chr.id + " "+by.id);
	if(!LAi_group_IsEnemy(chr, by)) return;
	LAi_group_UpdateTargets(chr);
// boal -->
/*	bool isChangeTarget = false;
	if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
	{
		if(LAi_tmpl_fight_NoActive(chr))
		{
			isChangeTarget = true;
		}
	}else{
		isChangeTarget = true;
	}
	if(isChangeTarget)
	{
		//������ ����
		LAi_tmpl_SetFight(chr, by);*/
//boal fix ai -->
    float dist = -1.0;

	if(!GetCharacterDistByChr3D(chr, by, &dist)) return;
	if(dist < 0.0) return;
	if(dist > 20.0) return;
	//������������
	//LAi_tmpl_SetFight(chr, by); // TIH moved down below after sound check
    // boal <--
    // TIH reduced this repetitive sound by only doing it on change of target and less percent - Aug29'06
    if ( LAi_tmpl_fight_GetTarget(chr) != sti(by.index) ) {
		if(rand(100) > 95)
		{
			LAi_type_warrior_PlaySound(chr);
		}
	}
	LAi_tmpl_SetFight(chr, by);// TIH moved down here from above, so its set after sound - Aug29'06
//	}
}

//��������� � ����� ��������
void LAi_type_warrior_SetWateState(aref chr)
{
	if(sti(chr.chr_ai.type.stay) == 0)
	{
		if(chr.chr_ai.type.index != "")
		{
			int cmd = sti(chr.chr_ai.type.index);
			if(cmd >= 0)
			{
				//������������ � ���������
				LAi_tmpl_SetFollow(chr, &Characters[cmd], -1.0);
			}else{
				//������ � ������� ����
				LAi_tmpl_walk_InitTemplate(chr);
			}
		}else{
			//������ � ������� ����
			LAi_tmpl_walk_InitTemplate(chr);
		}
	}else{
		//������� ���� ���� �� �����
		if(chr.chr_ai.tmpl != LAI_TMPL_STAY)
		{
			LAi_tmpl_stay_InitTemplate(chr);
		}
	}
}

void LAi_type_warrior_PlaySound(aref chr)
{
	if(LAi_IsDead(chr)) return;
	string sname = "";
	if(CheckAttribute(chr, "sex"))
	{
		switch(chr.sex)
		{
		case "man":
			switch(makeint(chr.nation))
			{
				case 0 : sname = "warrior_eng";break;				// english
				case 1 : sname = "warrior_fra";break;				// french
				case 2 : sname = "warrior_spa";break;				// spanish
				case 3 : sname = "warrior_pir";break;				// pirates
				case 4 : sname = "warrior_dut";break;				// dutch
				case 5 : sname = "warrior";break;					// portuguese
			}
			break;
		case "woman":
			sname = "shi_warrior";//MAXIMUS
			break;
		case "skeleton":
			sname = "skeleton";
			break;
		}
	}
	if(sname == "") return;
	LAi_CharacterPlaySound(chr, sname);
}
