/*
���: ����, ��������� �������� ����������

	������������ �������:
		stay
		goto
		runto
		follow
		dialog
*/



#define LAI_TYPE_ACTOR	"actor"


//�������������
void LAi_type_actor_Init(aref chr)
{
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_ACTOR) isNew = true;
	}
	if(isNew == true)
	{
		//����� ���
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_ACTOR;
		chr.chr_ai.type.quest = "";
		chr.chr_ai.type.state = "wait";
		chr.chr_ai.type.checkhp = "";
		chr.chr_ai.type.lock = "0";
		chr.chr_ai.type.mode = "stay";
		//��������� ������ �������
		LAi_tmpl_stay_InitTemplate(chr);
	}else{
		//�������������� ���������
		if(!CheckAttribute(chr, "chr_ai.type.state")) chr.chr_ai.type.state = "wait";
		if(!CheckAttribute(chr, "chr_ai.type.quest")) chr.chr_ai.type.quest = "";
		if(!CheckAttribute(chr, "chr_ai.type.checkhp")) chr.chr_ai.type.checkhp = "";
		if(!CheckAttribute(chr, "chr_ai.type.lock")) chr.chr_ai.type.lock = "0";
		if(!CheckAttribute(chr, "chr_ai.type.mode")) chr.chr_ai.type.mode = "stay";
	}
	bool isMusk = false;
	if(CheckAttribute(chr, "model.animation")) {
        string sAni = strcut(chr.model.animation, 0, 8);
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
	//��������� �������� ���������
	if(chr.chr_ai.type.mode == "sit")
	{
		LAi_ActorSetSitMode(chr);
	}else{
		if(chr.chr_ai.type.mode == "lay")
		{
			LAi_ActorSetLayMode(chr);
		}else{
			if(chr.chr_ai.type.mode == "huber") //ASVS
			{
				LAi_ActorSetHuberMode(chr);		//ASVS
			}else{
				LAi_ActorSetStayMode(chr);
				}
			}
		}
	}
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_actor_CharacterUpdate(aref chr, float dltTime)
{
	aref type;
	makearef(type, chr.chr_ai.type);
	if(type.state == "dialogcan")
	{
		LAi_type_actor_CheckStartDialog(chr);
	}else{
		if(type.state == "attack")
		{
			if(LAi_tmpl_fight_LostTarget(chr))
			{
				LAi_Character_TemplateComplite(chr, LAI_TMPL_FIGHT);
			}
		}
	}
}

//�������� ��������� � �������
bool LAi_type_actor_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_actor_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_actor_TemplateComplite(aref chr, string tmpl)
{
	//���� ��� �������� �����, �� ������ �������
	if(chr.chr_ai.type.state == "wait") return;
	//���� ��� ����� ����� ������, �� ���� �������
	if(chr.chr_ai.tmpl != tmpl) return;
	//����� �� ����� �� ����������
	string quest = chr.chr_ai.type.quest;
	chr.chr_ai.type.quest = "";
	if(chr.chr_ai.type.state == "dialoggo")
	{
		//������ � ���������, �������� ������
		chr.chr_ai.type.lock = "0";
		LAi_ActorDialogNow(chr, &Characters[sti(chr.chr_ai.type.dlgchr)], quest, stf(chr.chr_ai.type.dlgtime));
		return;
	}
	if(chr.chr_ai.type.state == "exitfromloc")
	{
		//����� �� ��������, ������������� � ������ �������
		ChangeCharacterAddressGroup(chr, chr.chr_ai.type.location, chr.chr_ai.type.group, chr.chr_ai.type.locator);
	}
	//�������� ���������
	chr.chr_ai.type.lock = "0";
	//���� �� ����������, ������� ���������
	bool isResetActor = true;
	if(tmpl == LAI_TMPL_FOLLOW)
	{
		isResetActor = false;
	}
	if(tmpl == LAI_TMPL_ANI)
	{
		if(quest == "")
		{
			isResetActor = false;
		}
	}
	if(isResetActor)
	{
		LAi_type_actor_Reset(chr);
	}
	if(quest != "") CompleteQuestName(quest);
}

//�������� � ������� ������� ������
void LAi_type_actor_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_actor_CanDialog(aref chr, aref by)
{
	bool canDialog = false;
	if(chr.chr_ai.type.state == "dialogwait")
	{
		if(sti(chr.chr_ai.type.dlgchr) == sti(by.index)) canDialog = true;
	}else{
		if(chr.chr_ai.type.state == "dialoggo")
		{
			if(sti(chr.chr_ai.type.dlgchr) == sti(by.index)) canDialog = true;
		}
	}
	return canDialog;
}

//������ ������
void LAi_type_actor_StartDialog(aref chr, aref by)
{
	if(chr.chr_ai.type.state == "dialogself")
	{
		LAi_tmpl_stay_InitTemplate(chr);
		return;
	}else{
		if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG)
		{
			//���� �� �������, ��������� ������ ��� ������� ����������
			LAi_tmpl_SetActivatedDialog(chr, by);
			chr.chr_ai.type.state = "dialog";
		}
		if(chr.chr_ai.type.mode == "stay")
		{
			CharacterTurnByChr(chr, by);
		}else{
			LAi_tmpl_dialog_NoAni(chr);
		}
	}
}

//��������� ������
void LAi_type_actor_EndDialog(aref chr, aref by)
{
	if(chr.chr_ai.type.state == "dialogself")
	{
		LAi_tmpl_stay_InitTemplate(chr);
		LAi_type_actor_TemplateComplite(chr, LAI_TMPL_STAY);
	}else{
		if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG) Trace("LAi_type_actor_EndDialog -> LAi_type_actor_Reset");
		LAi_type_actor_TemplateComplite(chr, LAI_TMPL_DIALOG);
	}
}

//�������� �������� ������� ���������
void LAi_type_actor_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� �������� ������������������ ���������
void LAi_type_actor_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� ���������
void LAi_type_actor_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}

//�������� ��������
void LAi_type_actor_Attacked(aref chr, aref by)
{

}

bool LAi_type_actor_Error(aref chr, bool lockTest)
{
	if(CheckAttribute(chr,"chr_ai.type") && chr.chr_ai.type != LAI_TYPE_ACTOR)
	{
		Trace("Actor error: character <" + chr.id + "> now is not actor, his have type <" + chr.chr_ai.type + ">");
		return true;
	}
	if(lockTest)
	{
		if(CheckAttribute(chr,"chr_ai.type.lock") && sti(chr.chr_ai.type.lock) != 0)
		{
			Trace("Actor error: character <" + chr.id + "> now is do template <" + chr.chr_ai.tmpl + ">, his not is free for new task");
			return true;
		}
	}
	return false;
}


//------------------------------------------------------------------------------------------
//Scripters ai program interface
//------------------------------------------------------------------------------------------
//
// �������� quest:
//           ���� "" �� ������� ������� �� ��������� �������� �� �����
//           ���� "questName" �� �� ��������� �������� ��������� ��������� �����
// �������� timeout:
//           ���� -1 �� ������� ����� �����������, ���� �� �����������
//           ���� >= 0 �� �� ��������� ��������� ������� ��������������� ���������� �������
//
//------------------------------------------------------------------------------------------

//������� ����� ������
void LAi_ActorStay(aref chr)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.state = "stay";
	chr.chr_ai.type.quest = "";
	LAi_tmpl_stay_InitTemplate(chr);
}

//������� ����� ���� � �������� �������
void LAi_ActorGoToLocator(aref chr, string group, string locator, string quest, float timeout)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "goto";
	chr.chr_ai.type.quest = quest;
	LAi_tmpl_goto_InitTemplate(chr);
	LAi_tmpl_goto_SetLocator(chr, group, locator, timeout);
	chr.chr_ai.type.lock = "1";
}

// --> JRH
void LAi_ActorGoToLocatorJRH(aref chr, string group, string locator, float timeout)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "goto";
    //chr.chr_ai.type.quest = quest;
	LAi_tmpl_goto_InitTemplate(chr);
	LAi_tmpl_goto_SetLocator(chr, group, locator, timeout);
	chr.chr_ai.type.lock = "1";
}
// <-- JRH

//������� ����� ������ � �������� �������
void LAi_ActorRunToLocator(aref chr, string group, string locator, string quest, float timeout)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "runto";
	chr.chr_ai.type.quest = quest;
	LAi_tmpl_runto_InitTemplate(chr);
	LAi_tmpl_runto_SetLocator(chr, group, locator, timeout);
	chr.chr_ai.type.lock = "1";
}

// --> JRH
void LAi_ActorRunToLocatorJRH(aref chr, string group, string locator, float timeout)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "runto";
    //chr.chr_ai.type.quest = quest;
	LAi_tmpl_runto_InitTemplate(chr);
	LAi_tmpl_runto_SetLocator(chr, group, locator, timeout);
	chr.chr_ai.type.lock = "1";
}
// <-- JRH

//������� ����� ���� � �������� �������
void LAi_ActorGoToLocation(aref chr, string groupExit, string locatorExit, string locID, string groupEnter, string locatorEnter, string quest, float timeout)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "exitfromloc";
	chr.chr_ai.type.quest = quest;
	chr.chr_ai.type.location = locID;
	chr.chr_ai.type.group = groupEnter;
	chr.chr_ai.type.locator = locatorEnter;
	LAi_tmpl_goto_InitTemplate(chr);
	LAi_tmpl_goto_SetLocator(chr, groupExit, locatorExit, timeout);
	chr.chr_ai.type.lock = "1";
}

//������� ����� ������ � �������� �������
void LAi_ActorRunToLocation(aref chr, string groupExit, string locatorExit, string locID, string groupEnter, string locatorEnter, string quest, float timeout)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "exitfromloc";
	chr.chr_ai.type.quest = quest;
	chr.chr_ai.type.location = locID;
	chr.chr_ai.type.group = groupEnter;
	chr.chr_ai.type.locator = locatorEnter;
	LAi_tmpl_runto_InitTemplate(chr);
	LAi_tmpl_runto_SetLocator(chr, groupExit, locatorExit, timeout);
	chr.chr_ai.type.lock = "1";
}

//������� ����� c�������� �� ���������� � �������� �������
//��� ������ ������� ��� ��������� ������� ��������� �����
void LAi_ActorFollow(aref chr, aref follow, string quest, float timeout)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "follow";
	chr.chr_ai.type.quest = quest;
	LAi_tmpl_SetFollow(chr, follow, timeout);
	chr.chr_ai.type.lock = "1";
}

//������� ����� c�������� �� ������� �� ���� ��������
//��� ������ ������� ��� ��������� ������� ��������� �����
void LAi_ActorFollowEverywhere(aref chr, string quest, float timeout)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.location.follower = "1";
	LAi_ActorFollow(chr, GetMainCharacter(), quest, timeout);
	chr.chr_ai.type.lock = "0";
}

//������� ����� �� ���� �������
void LAi_ActorAttack(aref chr, aref enemy, string quest)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "attack";
	chr.chr_ai.type.quest = quest;
	LAi_tmpl_SetFight(chr, enemy);
	chr.chr_ai.type.lock = "1";
}

//������� ����� ������� ������� ���������
void LAi_ActorAfraid(aref chr, aref by, bool canMove)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "afraid";
	chr.chr_ai.type.quest = "";
	LAi_tmpl_afraid_SetAfraidCharacter(chr, by, canMove);
	chr.chr_ai.type.lock = "0";
}


//To activate dialogue between the actor and other character with the approach to each other
void LAi_ActorDialog(aref chr, aref to, string quest, float timeout, float dlgTime)
{
	if(LAi_type_actor_Error(chr, true))
	{
		trace("ActorDialog got error in type_actor_error");		// LDH 11Sep06 report errors to see why dialog isn't initiated
		return;
	}
	chr.chr_ai.type.state = "dialoggo";
	chr.chr_ai.type.quest = quest;
	chr.chr_ai.type.dlgtime = dlgTime;
	chr.chr_ai.type.dlgchr = to.index;
	LAi_tmpl_SetFollow(chr, to, timeout);
	chr.chr_ai.type.lock = "1";
}

// To activate dialogue between the actor and other character immediately
void LAi_ActorDialogNow(aref chr, aref to, string quest, float dlgTime)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "dialogcan";
	chr.chr_ai.type.quest = quest;
	chr.chr_ai.type.dlgtime = dlgTime;
	chr.chr_ai.type.dlgchr = to.index;
	//LAi_tmpl_SetFollow(chr, to, -1.0);
	LAi_type_actor_CheckStartDialog(chr);
	chr.chr_ai.type.lock = "1";
}

//������������ ������ � ����� �����
void LAi_ActorSelfDialog(aref chr, string quest)
{
	if(LAi_type_actor_Error(chr, true)) return;
	chr.chr_ai.type.state = "dialogself";
	chr.chr_ai.type.quest = quest;
	LAi_tmpl_stay_InitTemplate(chr);
	SelfDialog(chr);
	chr.chr_ai.type.lock = "1";
}

//������� ����� ������ � ����� ������� �� ������� ���������
void LAi_ActorWaitDialog(aref chr, aref by)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.state = "dialogwait";
	chr.chr_ai.type.quest = "";
	chr.chr_ai.type.dlgchr = by.index;
	LAi_tmpl_stay_InitTemplate(chr);
	chr.chr_ai.type.lock = "1";
}

// To lose for animation for the actor, on the termination to cause a quest
// If animation ??? the quest will be caused on the expiration of time
void LAi_ActorAnimation(aref chr, string animation, string quest, float timeout)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.state = "animation";
	chr.chr_ai.type.quest = quest;
	LAi_tmpl_ani_PlayAnimation(chr, animation, timeout);
	chr.chr_ai.type.lock = "1";
}

//������������� ����� �� ��������� (����������)
void LAi_ActorTurnToCharacter(aref chr, aref to)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.state = "";
	LAi_tmpl_stay_InitTemplate(chr);
	CharacterTurnByChr(chr, to);
	chr.chr_ai.type.lock = "0";
}

//������������� ����� �� ��������
void LAi_ActorTurnByLocator(aref chr, string group, string locator)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.state = "";
	LAi_tmpl_stay_InitTemplate(chr);
	CharacterTurnByLoc(chr, group, locator);
	chr.chr_ai.type.lock = "0";
}

//������������� ����� �� �������
void LAi_ActorTurnToLocator(aref chr, string group, string locator)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.state = "";
	LAi_tmpl_stay_InitTemplate(chr);
	CharacterTurnToLoc(chr, group, locator);
	chr.chr_ai.type.lock = "0";
}

//���������� �������� �������� ���������
void LAi_ActorSetStayMode(aref chr)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.mode = "stay";
	LAi_SetDefaultStayAnimation(chr);
}

//���������� �������� �������� ���������
void LAi_ActorSetSitMode(aref chr)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.mode = "sit";
	LAi_SetDefaultSitAnimation(chr);
}

// ASVS --->
void LAi_ActorSetHuberMode(aref chr)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.mode = "huber";
	LAi_SetHuberSitAnimation(chr);
}
// ASVS <---

//���������� �������� �������� ���������
void LAi_ActorSetLayMode(aref chr)
{
	if(LAi_type_actor_Error(chr, false)) return;
	chr.chr_ai.type.mode = "lay";
	BeginChangeCharacterActions(chr);
	chr.actions.idle.i1 = "Lay_1";
	EndChangeCharacterActions(chr);
}

//------------------------------------------------------------------------------------------
//���������� �������
//------------------------------------------------------------------------------------------

//������� � ��������� �������� ����� �������
void LAi_type_actor_Reset(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	if(LAi_type_actor_Error(chr, false)) return;
	LAi_tmpl_stay_InitTemplate(chr);
	chr.chr_ai.type.state = "wait";
	chr.chr_ai.type.lock = "0";
	CharacterPlayAction(chr, "");
}

//������ �� ����������� ������
void LAi_type_actor_CheckStartDialog(aref chr)
{
	if(LAi_type_actor_Error(chr, false)) return;
	if(chr.chr_ai.type.state != "dialogcan") return;
	int idx = sti(chr.chr_ai.type.dlgchr);
	if(LAi_Character_CanDialog(chr, &Characters[idx]))
	{
		chr.chr_ai.type.state = "dialogwait";
		LAi_tmpl_SetDialog(chr, &Characters[idx], stf(chr.chr_ai.type.dlgtime));
	}
}



