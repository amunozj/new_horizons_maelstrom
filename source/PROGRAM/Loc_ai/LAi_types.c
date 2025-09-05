
//������������ ���� ��� ���������

//�����
#include "Loc_ai\types\LAi_player.c"
//������
#include "Loc_ai\types\LAi_officer.c"
//���������
#include "Loc_ai\types\LAi_citizen.c"
//�������
#include "Loc_ai\types\LAi_guardian.c"
//�������
#include "Loc_ai\types\LAi_patrol.c"
//����
#include "Loc_ai\types\LAi_warrior.c"
//��������
#include "Loc_ai\types\LAi_merchant.c"
//������� �������
#include "Loc_ai\types\LAi_stay.c"
//������� �������
#include "Loc_ai\types\LAi_sit.c"
//������
#include "Loc_ai\types\LAi_barman.c"
//����������
#include "Loc_ai\types\LAi_waitress.c"
//�����
#include "Loc_ai\types\LAi_poor.c"
//����������, ������� �� �����
#include "Loc_ai\types\LAi_huber.c"
//����������, ������� �� ���������
#include "Loc_ai\types\LAi_huberstay.c"
//��������
#include "Loc_ai\types\LAi_priest.c"
//����
#include "Loc_ai\types\LAi_actor.c"
//��������-������
#include "Loc_ai\types\LAi_monkey.c"

#include "Loc_ai\types\LAi_stunned.c" // NK 05-07-10 CCC's stun type

#include "Loc_ai\types\LAi_building.c" // ccc building kit Aug 05
//������
#include "Loc_ai\types\LAi_lay.c" // MAXIMUS 17.09.2007
//����������
#include "Loc_ai\types\LAi_staywork.c" // MAXIMUS 17.09.2007

//------------------------------------------------------------------------------------------
//Player
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ������
void LAi_SetPlayerType(aref chr)
{
	//��� ��������� �� ���������
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	//������ �����������
	LAi_type_player_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
}

//------------------------------------------------------------------------------------------
//Officer
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �������
void LAi_SetOfficerType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_officer_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
}

//------------------------------------------------------------------------------------------
//Citizen
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ����������
void LAi_SetCitizenType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_citizen_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ����������, ��� ����������� � ������
void LAi_SetCitizenTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_citizen_Init(chr);
}

//------------------------------------------------------------------------------------------
//Guardian
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ���������
void LAi_SetGuardianType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.chr_ai.soldiertype = "Guardian";	// GR: For resurrecting to correct type
	LAi_type_guardian_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_GUARDS);
	chr.isSoldier = true; // KK
}

//���������� ��������� ��� ���������, ��� ����������� � ������
void LAi_SetGuardianTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_guardian_Init(chr);
}

// KK -->
void LAi_SetCivilianGuardianType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_guardian_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_GUARDS);
}
// <-- KK

//------------------------------------------------------------------------------------------
//Patrol
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �������
void LAi_SetPatrolType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	chr.chr_ai.soldiertype = "Patrol";	// GR: For resurrecting to correct type
	LAi_SetPatrolTypeNoGroup(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PATROL);
	chr.isSoldier = true; // KK
}

//���������� ��������� ��� �������, ��� ����������� � ������
void LAi_SetPatrolTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_patrol_Init(chr);
}

// KK -->
void LAi_SetCivilianPatrolType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_SetPatrolTypeNoGroup(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PATROL);
}
// <-- KK

//------------------------------------------------------------------------------------------
//Warrior
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �����
void LAi_SetWarriorType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_warrior_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_GUARDS);
	chr.isWarrior = true;
}

//���������� ��������� ��� �����, ��� ����������� � ������
void LAi_SetWarriorTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_warrior_Init(chr);
	chr.isWarrior = true;
}


//------------------------------------------------------------------------------------------
//Merchant
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ��������
void LAi_SetMerchantType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_merchant_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
	chr.isMerchant = true; //Levis
}

//���������� ��������� ��� ��������, ��� ����������� � ������
void LAi_SetMerchantTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_merchant_Init(chr);
	chr.isMerchant = true; //Levis
}

//------------------------------------------------------------------------------------------
//Stay
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ��������
void LAi_SetStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_stay_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ��������, ��� ����������� � ������
void LAi_SetStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_stay_Init(chr);
}

//------------------------------------------------------------------------------------------
//Sit
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ��������
void LAi_SetSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_sit_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ��������, ��� ����������� � ������
void LAi_SetSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_sit_Init(chr);
}


//------------------------------------------------------------------------------------------
//Barmen
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ������� (only man)
void LAi_SetBarmanType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_barman_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
	chr.isMerchant = true; //Levis
}

//���������� ��������� ��� ����������, ��� ����������� � ������ (only man)
void LAi_SetBarmanTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_barman_Init(chr);
	chr.isMerchant = true; //Levis
}

//------------------------------------------------------------------------------------------
//Waitress
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ���������� (only woman)
void LAi_SetWaitressType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_waitress_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ����������, ��� ����������� � ������ (only woman)
void LAi_SetWaitressTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_waitress_Init(chr);
}


//------------------------------------------------------------------------------------------
//Poor
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �������
void LAi_SetPoorType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_poor_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� �������, ��� ����������� � ������
void LAi_SetPoorTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_poor_Init(chr);
}

//------------------------------------------------------------------------------------------
//Huber
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �����������
void LAi_SetHuberType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huber_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_HUBER);
}

//���������� ��������� ��� �����������, ��� ����������� � ������
void LAi_SetHuberTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huber_Init(chr);
}

//------------------------------------------------------------------------------------------
//HuberStay
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �����������, �������� �� �������
void LAi_SetHuberStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huberstay_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_HUBER);
}

//���������� ��������� ��� �����������, �������� �� �������, ��� ����������� � ������
void LAi_SetHuberStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huberstay_Init(chr);
}

//------------------------------------------------------------------------------------------
//Priest
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ���������
void LAi_SetPriestType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huberstay_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ���������, ��� ����������� � ������
void LAi_SetPriestTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huberstay_Init(chr);
}


//------------------------------------------------------------------------------------------
//Actor
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �����
void LAi_SetActorType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_actor_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_ACTOR);
}

//���������� ��������� ��� �����, ��� ����������� � ������
void LAi_SetActorTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_actor_Init(chr);
}

//------------------------------------------------------------------------------------------
//Monkey
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ��������-�������
void LAi_SetMonkeyType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_monkey_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_MONSTERS);
}

//���������� ��������� ��� ��������-�������, ��� ����������� � ������
void LAi_SetMonkeyTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_monkey_Init(chr);
}

//------------------------------------------------------------------------------------------
// Stunned -- NK 05-07-10 CCC's stun type
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �������
void LAi_SetStunnedType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Stunned_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� �������, ��� ����������� � ������
void LAi_SetStunnedTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Stunned_Init(chr);
}

//------------------------------------------------------------------------------------------
// Building -- ccc aug05
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ������
void LAi_SetBuildingType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Building_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ������, ��� ����������� � ������
void LAi_SetBuildingTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Building_Init(chr);
}

//------------------------------------------------------------------------------------------
//Lay - MAXIMUS 17.09.2007
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ��������
void LAi_SetLayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_lay_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ��������, ��� ����������� � ������
void LAi_SetLayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_lay_Init(chr);
}

//���������� ��������� ��� �����������
void LAi_SetStayworkType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_staywork_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� �����������, ��� ����������� � ������
void LAi_SetStayworkTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_staywork_Init(chr);
}
