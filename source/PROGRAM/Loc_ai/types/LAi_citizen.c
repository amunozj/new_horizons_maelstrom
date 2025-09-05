

#define LAI_TYPE_CITIZEN	"citizen"


//�������������
void LAi_type_citizen_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_CITIZEN) isNew = true;
	}
	if(isNew == true)
	{
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_CITIZEN;
		//��������� ������ �������
		LAi_tmpl_walk_InitTemplate(chr);
	}	
	chr.chr_ai.type.notalk = rand(10);
	chr.chr_ai.type.checkFight = rand(5)+2;
	//��������� �������� ���������
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_citizen_CharacterUpdate(aref chr, float dltTime)
{	
	int i;
	int trg = -1;
	float time;
	if(chr.chr_ai.tmpl == LAI_TMPL_WALK)
	{
		trg = LAi_type_citizen_FindNearEnemy(chr);
		if(trg >= 0)
		{
			if(LAi_IsSetBale(chr))
			{
				//��������� � ������ �����
				LAi_tmpl_SetFight(chr, &Characters[trg]);
			}else{
				//������
				LAi_tmpl_afraid_SetAfraidCharacter(chr, &Characters[trg], true);
				LAi_SetAfraidDead(chr);
			}
		}else{
			//������ � ����������� ����������
			// NK 05-07-17 allow citizens to pause when player is near for dlg.
			bool isDialog = false; // NK move here
			time = stf(chr.chr_ai.type.notalk) - dltTime;
			int num = FindNearCharacters(chr, 3.0, -1.0, -1.0, 0.001, true, true);
			if (CheckAttribute(chr, "talker") && time < 10.0)
			{
				for(i = 0; i < num; i++)
				{
					idx = sti(chrFindNearCharacters[i].index);
					if (idx == nMainCharacterIndex)
					{
						if (sti(chr.talker) > rand(10) && LAi_Character_CanDialog(chr, pchar))
						{
							LAi_tmpl_SetDialog(chr, pchar, -1.0);
							DeleteAttribute(chr, "talker");
							break;
						}
						else time = 50.0;
					}
				}
			}
			if (stf(chr.chr_ai.type.checkFight) < 0.0)
			{
				for(i = 0; i < num; i++)
				{
					idx = sti(chrFindNearCharacters[i].index);
					by = &Characters[idx];
					chr.chr_ai.type.checkFight = 1.5;
					if (LAi_CheckFightMode(by))
					{
						LAi_tmpl_afraid_SetAfraidCharacter(chr, by, true);
					}
				}
			}
			else
			{
				chr.chr_ai.type.checkFight = stf(chr.chr_ai.type.checkFight) - dltTime;
			}
			if(time <= 0.0)
			{
				if(rand(100) < 10)
				{
					int idx = sti(chrFindNearCharacters[0].index);
					if(idx > 0) // TIH changed from '>=' to '>' : to not include mainchar in this block, mainchar handled below Nov15'06
					{
						ref by = &Characters[idx];
						//���
						if(CheckAttribute(by, "chr_ai.type"))
						{
							// NK moved out of this if - bool isDialog = false;
							switch(by.chr_ai.type)
							{
							case LAI_TYPE_CITIZEN:
								isDialog = true;
								break;
							case LAI_TYPE_GUARDIAN:
								isDialog = true;
								break;
							case LAI_TYPE_PATROL:
								isDialog = true;
								break;
							}
							//���������
							time = -1.0;
							if(GetCharacterDistByChr(chr, by, &time))
							{
								if(time < 0.0) isDialog = false;								
								if(time > 2.5) isDialog = false;
							}
							if(isDialog)
							{
								chr.chr_ai.type.notalk = 10.0 + rand(20);
								if(LAi_Character_CanDialog(chr, by))
								{
									if(!LAi_tmpl_SetDialog(chr, by, 3.0 + rand(10)))
									{
										LAi_tmpl_walk_InitTemplate(chr);
									}
								}
							}
						}
					}
				}
			}
			else
			{
				chr.chr_ai.type.notalk = time;
			}
			// TIH do not do any of this if player is in dialog Nov15'06
			// also fixed floats being used as ints (added .0 to the values for safety)
			// changed misused 'time' var to 'dist' for distances
			if (!dialogRun) {
				// NK pause-for-pchar 05-07-17
				float dist = 100.0;
				GetCharacterDistByChr(chr, GetMainCharacter(), &dist);
				if(!CheckAttribute(chr, "chr_ai.type.player")) chr.chr_ai.type.player = "5";
				float ptime = stf(chr.chr_ai.type.player);
				if (ptime > 0.0) { // TIH only update if greater than zero
					ptime = retmax(0.0, ptime - dltTime);
					chr.chr_ai.type.player = ptime;
				}
				// TIH --> time between talking for any NPC to the mainchar
				ref rMainChar = GetMainCharacter();
				if(!CheckAttribute(rMainChar, "citizentalktime")) rMainChar.citizentalktime = "5";
				float mptime = stf(rMainChar.citizentalktime);
				if (mptime > 0.0) { // TIH only update if greater than zero
					mptime = retmax(0.0, mptime - dltTime); 
					rMainChar.citizentalktime = mptime;
				}
				// TIH <--
				if(dist >= 0.0 && dist <= 2.5 && !LAi_group_IsActivePlayerAlarm())
				{
					// TIH add time between talk for all
					if(mptime <= 0.0 && ptime <= 0.0 && frnd() < CITIZEN_TALKCHANCE && LAi_Character_CanDialog(chr, GetMainCharacter()))
					{
						chr.chr_ai.type.player = ((TIME_BETWEEN_DLG + rand(TIME_BETWEEN_DLG)) * TIMESCALAR_LAND);// TIH
						rMainChar.citizentalktime = ((TIME_BETWEEN_DLG_ALL + rand(TIME_BETWEEN_DLG_ALL)) * TIMESCALAR_LAND);// TIH
						//LAi_tmpl_walk_InitTemplate(chr);
						LAi_tmpl_SetDialog(chr, GetMainCharacter(), -1.0);
					}
					else
					{
						if(frnd() < CITIZEN_STOPCHANCE)
						{
							chr.chr_ai.tmpl.state = "look";
							chr.chr_ai.tmpl.state.time = 0;
							chr.chr_ai.tmpl.state.maxtime = 4 + rand(3);
							chr.chr_ai.tmpl.state.index = GetMainCharacterIndex();
							CharacterTurnByChr(chr, GetMainCharacter());
						}
					}
				}
				// NK <--
			}
			// TIH <--
		}
	}else{
		if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
		{
			//�����, ����������� �� �������� ����
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
				//������� ��������� ����
				trg = LAi_type_citizen_FindNearEnemy(chr);
				if(trg >= 0)
				{
					LAi_tmpl_SetFight(chr, &Characters[trg]);
				}else{
					LAi_tmpl_walk_InitTemplate(chr);
				}
			}
		}else{
			if(chr.chr_ai.tmpl == LAI_TMPL_AFRAID)
			{
				if(LAi_tmpl_afraid_IsNoActive(chr))
				{
					//������� � ���������� �����
					LAi_SetDefaultDead(chr);
					LAi_tmpl_walk_InitTemplate(chr);
				}
			}
		}
	}
}

//�������� ��������� � �������
bool LAi_type_citizen_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_citizen_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_citizen_TemplateComplite(aref chr, string tmpl)
{

}

//�������� � ������� ������� ������
void LAi_type_citizen_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_citizen_CanDialog(aref chr, aref by)
{
	// NK this kills dialog! return false;	// ccc Greater Oxbay, so that even enemies talk
	// NK allow dlg in boarding 05-07-12 - if(LAi_IsBoardingProcess()) return false;
	// this is I think what you want false, CCC - if(LAi_CanNearEnemy(chr, 5.0)) return false;
	//���� ������ �����, �� ���������� �� ������
	if(chr.chr_ai.tmpl == LAI_TMPL_WALK)
	{
		if(sti(by.index) != GetMainCharacterIndex())
		{
			if(stf(chr.chr_ai.type.notalk) <= 0.0)
			{
				return true;
			}
			return false;
		}
		return true;
	}
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)	
	{
		if(sti(by.index) == GetMainCharacterIndex())
		{
			if(LAi_tmpl_dialog_StopNPC(chr)) return true;
		}
	}
	return false;
}

//������ ������
void LAi_type_citizen_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_citizen_EndDialog(aref chr, aref by)
{
	LAi_CharacterRestoreAy(chr);
	LAi_tmpl_walk_InitTemplate(chr);
	chr.chr_ai.type.notalk = 10.0 + rand(20);
}

//�������� �������� ������� ���������
void LAi_type_citizen_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� �������� ������������������ ���������
void LAi_type_citizen_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{

}

//�������� ���������
void LAi_type_citizen_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}


//�������� ��������
void LAi_type_citizen_Attacked(aref chr, aref by)
{
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		LAi_tmpl_dialog_StopNPC(chr);
		LAi_type_citizen_CharacterUpdate(chr, 0.0);
	}
}


int LAi_type_citizen_FindNearEnemy(aref chr)
{
	int num = FindNearCharacters(chr, 5.0, -1.0, -1.0, 0.001, false, true);
	if(num <= 0)
	{
		chrFindNearCharacters[0].index = "-1";
		return -1;
	}
	int cnt = 0;
	for(int i = 0; i < num; i++)
	{
		int idx = sti(chrFindNearCharacters[i].index);
		if(LAi_group_IsEnemy(chr, &Characters[idx])) return idx;
	}
	return -1;
}
