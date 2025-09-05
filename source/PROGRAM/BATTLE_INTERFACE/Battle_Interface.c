#include "battle_interface\msg_control.h"
#include "sea_ai\script_defines.h"
#include "battle_interface\landinterface.c"
#include "battle_interface\ispyglass.c"
#include "battle_interface\reload_tables.c"
#include "battle_interface\utils.c"
#include "battle_interface\ActivePerksShow.c"
#include "battle_interface\procGetSailTextureData.c"		// the function procGetSailTextureData() is now moved into a separate file
#include "battle_interface\flags.c" // KK
#include "battle_interface\WmInterface.c"

#define BI_ICONS_TEXTURE_SHIP1		1

#define BI_ICONS_SHIPS_TEXTURE_NAME "battle_interface\icons.tga.tx"

#define BI_ICONS_ST_NONE		0
#define BI_ICONS_ST_MYSHIPS		1
#define BI_ICONS_ST_COMMAND		2
#define BI_ICONS_ST_TARGETING	3

#define BI_ICONS_TEXTURE_CHARGE		0
#define BI_ICONS_TEXTURE_COMMAND    1
#define BI_ICONS_TEXTURE_LANDTARG1	2
#define BI_ICONS_TEXTURE_LANDTARG2	3
#define BI_ICONS_TEXTURE_CANCEL		4
#define BI_ICONS_TEXTURE_SAILS		5
#define BI_ICONS_TEXTURE_ABILITY    6
#define BI_ICONS_TEXTURE_SKULL		7
#define BI_ICONS_TEXTURE_NATIONS	8
#define BI_ICONS_TEXTURE_ART		9
#define BI_ICONS_TEXTURE_SHIPS10	10
#define BI_ICONS_TEXTURE_SHIPS11		11
#define BI_ICONS_TEXTURE_SHIPS12		12
#define BI_ICONS_TEXTURE_SHIPS13		13
#define BI_ICONS_TEXTURE_SHIPS14		14
#define BI_ICONS_TEXTURE_SHIPS15		15
#define BI_ICONS_TEXTURE_SHIPSALL		16

int bi_icons_ShowType;
int bi_icons_CommandMode;

int bi_idxSelectedPicture;

object BattleInterface;

bool bDisableSailTo = false;

bool bDisableMapEnter = false;

bool bReloadCanBe = false;
bool bMapEnter = false;
bool bSailTo=false;
bool bAttack=false;
bool bDefend=false;

bool bEnableIslandSailTo=false;

bool bDisableAllCommands = false; // KK

int BI_intRetValue;
int BI_retComValue;
int BI_ChargeState[5];
float BI_g_fRetVal;

int BI_intNRetValue[8];

object BI_objRetValue;
object objShipPointer;
object IShipRoll;	// PB
object IShipPower;	// PB

//Boyer change
//#event_handler("DoSailHole","ProcessSailDamage");
#event_handler("evntRandomSailDmg","ProcessRandomSailDmg");
#event_handler("NextDay","ProcessDayRepair");
#event_handler("GetSailTextureData","procGetSailTextureData");
#event_handler("EventMastFall","procMastFall");
//#event_handler("evntBISelectShip","procBISelectShip");
#event_handler("evntGetSmallFlagData","procGetSmallFlagData");

#event_handler(SHIP_CREATE,"BI_CreateShip");

object INLGuns, INRGuns, INFGuns, INBGuns; // KK

void InitBattleInterface()
{
	ref chMain = GetMainCharacter();

	BI_InitializeCommands();
	bi_icons_CommandMode = 0;
	BattleInterface.SelCharacter = -1;
	BattleInterface.ShipSpeedScaler = (1.0 / 2.5);
	bi_idxSelectedPicture = -1;
	BattleInterface.boardRadius = 50;
	BattleInterface.freeDistance = MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;
	if (!CheckAttribute(InterfaceStates, "BIVisible")) InterfaceStates.BIVisible = true; // KK

	// PB: Compasses -->
	string compasstype = CheckCharacterEquipByGroup(chMain, COMPASS_ITEM_TYPE); // KK
	if (iRealismMode>0 || NAVIGATION_EQUIPMENT)
	{
		switch (compasstype)
		{
			case "":         bRealBattleInterface = true;  break; // KK
			case "compass1": bRealBattleInterface = true;  break;
			case "compass2": bRealBattleInterface = false; break;
			case "compass3": bRealBattleInterface = false; break; // KK
		}
	}
	// PB: Compasses <--

	SetParameterData();
	BattleInterface.blindSpeed = 0.003;
	BattleInterface.MaxWind = 30.0;
	BattleInterface.MaxShipSpeed = 20.0;

	BattleInterface.ShowNavigator = InterfaceStates.BattleShow.Navigator; // KK
	BattleInterface.ShowCommands = InterfaceStates.BattleShow.Command;
	//Boyer add
	BattleInterface.MainChrIndex = nMainCharacterIndex;
	CreateEntity(&BattleInterface,"battle_interface");
	DeleteAttribute(&BattleInterface,"CommandTextures");
	DeleteAttribute(&BattleInterface,"CommandShowParam");

// KK -->
	InitDateTimeDisplay();
	if (!bRealBattleInterface)
	{
	    //Boyer change
		CreateEntity(&INLGuns, "ILogAndActions");
		CreateEntity(&INRGuns, "ILogAndActions");
		CreateEntity(&INFGuns, "ILogAndActions");
		CreateEntity(&INBGuns, "ILogAndActions");
		DeleteAttribute(&INLGuns, "");
		DeleteAttribute(&INRGuns, "");
		DeleteAttribute(&INFGuns, "");
		DeleteAttribute(&INBGuns, "");
		LayerAddObject(SEA_EXECUTE, &INLGuns, -257);
		LayerAddObject(SEA_REALIZE, &INLGuns, -257);
		LayerAddObject(SEA_EXECUTE, &INRGuns, -257);
		LayerAddObject(SEA_REALIZE, &INRGuns, -257);
		LayerAddObject(SEA_EXECUTE, &INFGuns, -257);
		LayerAddObject(SEA_REALIZE, &INFGuns, -257);
		LayerAddObject(SEA_EXECUTE, &INBGuns, -257);
		LayerAddObject(SEA_REALIZE, &INBGuns, -257);

		CreateCannonInfo();

		SetEventHandler("evntUpdateCannonInfo", "UpdateCannonInfo", 0);
	}
	LayerAddObject(SEA_EXECUTE,&BattleInterface,-1);
	LayerAddObject(SEA_REALIZE,&BattleInterface,-1);
// <-- KK

	SetEventHandler(SHIP_DELETE,"BI_DeleteShip",0);
	SetEventHandler(SHIP_DEAD,"BI_DeadShip",0);

	SetEventHandler("BI_CommandEndChecking","BI_CommandEndChecking",0);
	SetEventHandler("BI_LaunchCommand","BI_LaunchCommand",0);
	SetEventHandler("BI_GetChargeQuantity","BI_GetChargeQuantity",0);
	SetEventHandler("BI_SetPossibleCommands","BI_SetPossibleCommands",0);
	SetEventHandler("GetCurrentCharge","GetCurrentCharge",0);
	SetEventHandler("evntGetCharacterShipClass","biGetCharacterShipClass",0);
	SetEventHandler(BI_EVENT_SET_VISIBLE,"BI_CommandVisible",0);
	SetEventHandler(BI_EVENT_SET_SEA_STATE,"BI_SetSeaState",0);
	SetEventHandler(BI_EVENT_GET_DATA,"BI_GetData",0);
	SetEventHandler(BI_EVENT_CHECK_SHIPSTATE_SHOW,"BI_GetSSShow",0);
	SetEventHandler("evntGetLandData","BI_GetLandData",0);
	SetEventHandler(BI_EVENT_GET_FORT_RELATION,"BI_GetFortRelation",0);
	SetEventHandler(EVENT_CHANGE_COMPANIONS,"RefreshBattleInterface",0);
	SetEventHandler("BI_CallUpdateShip","BI_UpdateShip",0);
	SetEventHandler("frame","BI_Frame",1);
	SetEventHandler("evntPerkAgainUsable","BI_PerkAgainUsable",0);
	SetEventHandler("evntSetUsingAbility","procSetUsingAbility",0);
	SetEventHandler("evntCheckEnableLocator","procCheckEnableLocator",0);
	SetEventHandler("evntCheckEnableShip","procCheckEnableShip",0);
	SetEventHandler("evntGetSRollSpeed","procGetSRollSpeed",0);
	//Boyer add
	SetEventHandler("DoSailHole","ProcessSailDamage",0);
	SetEventHandler("evntBISelectShip","procBISelectShip",0);

	procLoadIntoNew(); // ?????????????????? ?????????????? ???????????????? ????????????
	SetEventHandler("Control Activation","BI_ProcessControlPress",0);

	RefreshFlags();

	bDisableAllCommands = bQuestDisableAllCommands; // KK

	CreateILogAndActions(LOG_FOR_SEA);

	if (!bRealBattleInterface) Event("evntUpdateCannonInfo"); // KK

	Log_SetActiveAction("Nothing");

	BIVisible(sti(InterfaceStates.BIVisible)); // KK
}

ref BI_GetFortRelation()
{
	BI_intRetValue = BI_RELATION_NEUTRAL;
	aref arLoc = GetEventData();
	int chrIdx = Fort_FindCharacter(AISea.Island,"reload",arLoc.name);
	if(chrIdx>=0)
	{
		if (Ship_GetGroupID(GetCharacter(chrIdx)) == PLAYER_GROUP) BI_intRetValue = BI_RELATION_FRIEND; // KK
		if (SeaAI_GetRelation(chrIdx,GetMainCharacterIndex()) == RELATION_ENEMY) BI_intRetValue = BI_RELATION_ENEMY; // KK
	}
	return &BI_intRetValue;
}

ref BI_GetSSShow()
{
	int charIdx = GetEventData();
	ref mchref = GetMainCharacter();
// KK -->
	BI_intRetValue = false;
	if (charIdx < 0 || CharacterIsDead(GetCharacter(charIdx))) return &BI_intRetValue;
	if (iRealismMode == 0 || Ship_GetGroupID(GetCharacter(charIdx)) == PLAYER_GROUP) {
		switch (GetCharacterEquipByGroup(mchref, SPYGLASS_ITEM_TYPE))
		{
			case "spyglass1": BI_intRetValue = false;	break;
			case "spyglass2": BI_intRetValue = true;	break;
			case "spyglass3": BI_intRetValue = true;	break;
			case "spyglass4": BI_intRetValue = true;	break;
		}
	}
// <-- KK
	return &BI_intRetValue;
}

void BI_CommandVisible()
{
	int visibleFlag = GetEventData();
	InterfaceStates.BIVisible = visibleFlag;
	SendMessage(&BattleInterface,"ll",BI_SET_VISIBLE,visibleFlag);
// KK -->
	LogsVisible(visibleFlag);
	SendMessage(&INRGuns, "ll", LI_SET_VISIBLE, visibleFlag);
	SendMessage(&INLGuns, "ll", LI_SET_VISIBLE, visibleFlag);
	SendMessage(&INFGuns, "ll", LI_SET_VISIBLE, visibleFlag);
	SendMessage(&INBGuns, "ll", LI_SET_VISIBLE, visibleFlag);
// <-- KK
	SendMessage(&IShipRoll, "ll", LI_SET_VISIBLE, visibleFlag);		// PB: Capsizing
	SendMessage(&IShipPower, "ll", LI_SET_VISIBLE, visibleFlag);	// PB: Steam Ships
}

int bi_nReloadTarget=-1;
bool biold_bCanEnterToLand = false;
bool biold_bCanEnterToFort = false; // KK
bool biold_bAbordageShipCanBe = false;
bool biold_bAbordageFortCanBe = false;
bool biold_bReloadCanBe = false;
bool biold_bMapEnter = false;
bool bOldNotEnoughBalls = false;
bool bNotEnoughPowder = false; // TIH new method
bool bOldNotEnoughPowder = false; // TIH new method
//bool outOfGunpowder = false; // TIH depreciated // added by MAXIMUS [gunpowder mod]
void BI_Frame()
{
	bool bYesUpdateCommand = false;
	ref PChar = GetMainCharacter(); // KK

// TIH --> complete rewrite of this action, again Nov12'06

	// TIH --> mod toggle 7-7-06
	if (CANNONPOWDER_MOD && GetCaracterShipCannonsType(PChar) != CANNON_TYPE_NONECANNON) {
		// added by MAXIMUS [gunpowder mod] -->
		int fireGunpowder = 0;
		int ourPwdr = GetCargoGoods(PChar, GOOD_GUNPOWDER);
		ref rCannon; makeref(rCannon,Cannon[GetCaracterShipCannonsType(PChar)]);
		if(CheckAttribute(rCannon,"gunpowder")) fireGunpowder = sti(rCannon.gunpowder);

		// TIH --> Better method that covers all bases of charge status icon Nov12'06
		// - only needs to check arcs until enough powder is ok
		// - arcs are not checked if they have no cannons (otherwise it would always be true for enough gunpowder)
		// - only updates flasher icon when it should
		// - uses a toggle global boolean to insure proper display changes
		// - actually tested and works

		bNotEnoughPowder = true;

		int checkA  	= sti(GetCannonArcCurQty(PChar, 0)) + sti(GetCannonArcCurQty(PChar, 2));
		int checkB  	= sti(GetCannonArcCurQty(PChar, 1));
		int checkC  	= sti(GetCannonArcCurQty(PChar, 3));
		if ( bNotEnoughPowder && checkA >= 1 && ourPwdr >= checkA * fireGunpowder ) { bNotEnoughPowder = false; } // front & rear
		if ( bNotEnoughPowder && checkB >= 1 && ourPwdr >= checkB * fireGunpowder ) { bNotEnoughPowder = false; } // starboard
		if ( bNotEnoughPowder && checkC >= 1 && ourPwdr >= checkC * fireGunpowder ) { bNotEnoughPowder = false; } // port

		/* simply another way to check arcs, but the other above is a bit better, more effecient
		int cannonFrnt  = sti(GetCannonArcCurQty(GetMainCharacter(), 0));
		int cannonRear  = sti(GetCannonArcCurQty(GetMainCharacter(), 2));
		int cannonStar  = sti(GetCannonArcCurQty(GetMainCharacter(), 1));
		int cannonPort  = sti(GetCannonArcCurQty(GetMainCharacter(), 3));
		if ( bNotEnoughPowder && cannonFrnt >= 1 && ourPwdr >= cannonFrnt * fireGunpowder ) { bNotEnoughPowder = false; } // front
		if ( bNotEnoughPowder && cannonRear >= 1 && ourPwdr >= cannonRear * fireGunpowder ) { bNotEnoughPowder = false; } // rear
		if ( bNotEnoughPowder && cannonStar >= 1 && ourPwdr >= cannonStar * fireGunpowder ) { bNotEnoughPowder = false; } // starboard
		if ( bNotEnoughPowder && cannonPort >= 1 && ourPwdr >= cannonPort * fireGunpowder ) { bNotEnoughPowder = false; } // port
		*/

		if(bNotEnoughPowder != bOldNotEnoughPowder)
		{
			bOldNotEnoughPowder = bNotEnoughPowder;
			if (bNotEnoughPowder) 	{ SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,true); }
			else 					{ SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,false); }
		}
		else
		{
			if(bNotEnoughBalls != bOldNotEnoughBalls)
			{
				bOldNotEnoughBalls = bNotEnoughBalls;
				if(bNotEnoughBalls) { SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,true); }
				else 				{ SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,false); }
			}
		}
		// TIH <--

		/* +++ older method which has some ugly issues with it +++
		outOfGunpowder = true;
		if(bNotEnoughBalls!=bOldNotEnoughBalls)
		{
			bOldNotEnoughBalls = bNotEnoughBalls;
			if( ourPwdr>=sti(GetCannonArcCurQty(GetMainCharacter(), 0))*fireGunpowder && ourPwdr>=sti(GetCannonArcCurQty(GetMainCharacter(), 2))*fireGunpowder )
			{
				if(bNotEnoughBalls) SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,true);
				else SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,false);
			}
			else outOfGunpowder = true;
		}
		else
		{
			if( ourPwdr>=sti(GetCannonArcCurQty(GetMainCharacter(), 0))*fireGunpowder && ourPwdr>=sti(GetCannonArcCurQty(GetMainCharacter(), 2))*fireGunpowder )
			{
				SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,false);
				outOfGunpowder = false;
			}
			else
			{
				SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,true);
				outOfGunpowder = true;
			}
		}
		+++ end of old section +++ */

		// added by MAXIMUS [gunpowder mod] <--
	}
	// TIH <-- mod toggle
	else
	{
		if(bNotEnoughBalls != bOldNotEnoughBalls)
		{
			bOldNotEnoughBalls = bNotEnoughBalls;
			if(bNotEnoughBalls) {
				SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,true);
			} else {
				SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,false);
			}
		}
	}

// TIH <-- rewrite

// KK -->
	float fired_time, reload_time;
	int sea_time = GetSeaTime();
	if (CheckAttribute(PChar, "Ship.Cannons.fired_time") && CheckAttribute(PChar, "Ship.Cannons.reload_time")) {
		fired_time = stf(PChar.Ship.Cannons.fired_time);
		reload_time = stf(PChar.Ship.Cannons.reload_time);
		if (makefloat(sea_time) - fired_time >= reload_time) {
			CancelAllGunReadySounds();
			PlayGunReadySound(-1);
		}
	} else {
		for (int arc = 0; arc < 4; arc++)
		{
			string quadstr = GetQuadName(arc);
			if (CheckAttribute(PChar, "Ship.Cannons.Borts." + quadstr + ".fired_time") && CheckAttribute(PChar, "Ship.Cannons.Borts." + quadstr + ".reload_time")) {
				fired_time = stf(PChar.Ship.Cannons.Borts.(quadstr).fired_time);
				reload_time = stf(PChar.Ship.Cannons.Borts.(quadstr).reload_time) + stf(PChar.canfiretime);
				if (makefloat(sea_time) - fired_time >= reload_time) {
					DeleteAttribute(PChar, "Ship.Cannons.Borts." + quadstr + ".fired_time");
					DeleteAttribute(PChar, "Ship.Cannons.Borts." + quadstr + ".reload_time");
					PlayGunReadySound(arc);
				}
			}
		}
	}

	if (CheckAttribute(PChar, "Ship.Sails.Delay")) {
		int starttime = sti(PChar.Ship.Sails.Delay.StartTime);
		int delay = sti(PChar.Ship.Sails.Delay);
		if (sea_time - starttime >= delay) {
			int iSailState = sti(PChar.Ship.Sails.Delay.SailsState);
			DeleteAttribute(PChar, "Ship.Sails.Delay");
			PChar.LastSailState = iSailState;
			float fSailState = makefloat(iSailState) / 2.0;
			fSailState = clampf(fSailState); // NK 05-04-20 bugfix
			SendMessage(&AISea, "laf", AI_MESSAGE_SHIP_SET_SAIL_STATE, PChar, fSailState);
		}
	}

	if (CheckAttribute(PChar, "Anchoring") == true && sti(PChar.Anchoring) == true) {
		if (!CheckAttribute(PChar, "Anchoring.Duration")) PChar.Anchoring.Duration = sea_time;
		if (stf(PChar.Ship.Speed.z) < 0.3 || GetSeaTime() - sti(PChar.Anchoring.Duration) > 3) { // PB: was 5 seconds
			bool bImmediate = CheckAttribute(PChar, "Anchoring.Immediate") == true && sti(PChar.Anchoring.Immediate) == true;
			DeleteAttribute(PChar, "Anchoring");
			PChar.ForceReload = true; // PB: To fix potentially getting stuck
			if (VISIT_DECK == 1 && bImmediate == false)
				GoToDeck();
			else
				AnchorDrop();
		}
		return;
	}
// <-- KK

	if(biold_bAbordageShipCanBe!=bAbordageShipCanBe)
	{
		bYesUpdateCommand = true;
		biold_bAbordageShipCanBe = bAbordageShipCanBe;
	}
	if(biold_bAbordageFortCanBe!=bAbordageFortCanBe)
	{
		bYesUpdateCommand = true;
		biold_bAbordageFortCanBe = bAbordageFortCanBe;
	}
// KK -->
	if (biold_bReloadCanBe != bReloadCanBe) {
		bYesUpdateCommand = true;
		biold_bReloadCanBe = bReloadCanBe;
	}
	if (biold_bCanEnterToFort != bCanEnterToFort) {
		bYesUpdateCommand = true;
		biold_bCanEnterToFort = bCanEnterToFort;
	}
// <-- KK
	if(biold_bCanEnterToLand!=bCanEnterToLand)
	{
		bYesUpdateCommand = true;
		biold_bCanEnterToLand = bCanEnterToLand;
	}
	if(biold_bMapEnter!=bMapEnter)
	{
		bYesUpdateCommand = true;
		biold_bMapEnter = bMapEnter;
	}

	Log_SetActiveAction("Nothing"); // KK
	if (bDisableAllCommands) return; // KK

	if(bYesUpdateCommand)
	{
		BI_SetCommandMode(-1,-1,-1,-1);
		RefreshBattleInterface(false); // PB: No need updating relations when reload status changes
	}

	if(bAbordageShipCanBe)
	{
		Log_SetActiveAction("Board");
		Log_SetActionLabel(BattleInterface.Commands.Board.note); // KK
		return;
	}
	if(bAbordageFortCanBe)
	{
		Log_SetActiveAction("LandTroops");
		Log_SetActionLabel(BattleInterface.Commands.LandTroops.note); // KK
		return;
	}
	if(bCanEnterToLand)
	{
		Log_SetActiveAction("Moor");
		string DestinationType = CheckDestinationType(); // screwface
// KK -->
		if (VISIT_DECK)
			Log_SetActionLabel(BattleInterface.Commands.Moor.note);
		else
			Log_SetActionLabel(BattleInterface.Commands.LandPort.note);
// <-- KK
		return;
	}
// KK -->
// PB: This is unfinished and leads nowhere
/*	if (bCanEnterToFort) {
		Log_SetActiveAction("EnterFort");
		Log_SetActionLabel(BattleInterface.Commands.LandFort.note); // KK
		return;
	}*/
	if(bReloadCanBe)
	{
		Log_SetActiveAction("Transfer");
		Log_SetActionLabel(BattleInterface.Commands.Transfer.note); // KK
		return;
	}
// <-- KK
	if(bMapEnter)
	{
		// Flayed One --->
		if(iRealismMode<2 && !WORLDMAP_DISABLED)
		{
			Log_SetActiveAction("Map");
			Log_SetActionLabel(BattleInterface.Commands.Map.note); // KK
		}
		// Flayed One <---
		return;
	}
}

// KK -->
void BI_SetFlags()
{
	int init = 0;
	if (CheckAttribute(&Characters[GetMainCharacterIndex()], "Flags.waitdelay")) return;
	if (CheckAttribute(&BattleInterface, "DoSetFlags")) {
		init = sti(BattleInterface.DoSetFlags);
		DeleteAttribute(&BattleInterface, "DoSetFlags");
	}
	while (init < iNumShips)
	{
		if (Ships[init] >= 0 && CheckAttribute(&Characters[Ships[init]], "Flags.DoRefresh") == true) {
			DeleteAttribute(&Characters[Ships[init]], "Flags.DoRefresh");
			SetShipFlag(Ships[init]);
			init++;
			BattleInterface.DoSetFlags = init;
			FlagsDelay();
			return;
		}
		init++;
	}
	DelEventHandler("frame", "BI_SetFlags");
}
// <-- KK

// Screwface
void BI_FlagsDelay()
{
	int init = 0;
	// Just in case to avoid some errors
	if (!CheckAttribute(&Characters[GetMaincharacterIndex()],"Flags.waitdelay")) Characters[GetMaincharacterIndex()].Flags.waitdelay = 1;
	if (CheckAttribute(&BattleInterface, "Waitrefreshflags")) init = sti(BattleInterface.Waitrefreshflags);
	//trace("waiting before refresh - Frame : "+init);
	init++;
	BattleInterface.Waitrefreshflags = init;
	if (init >= sti(Characters[GetMaincharacterIndex()].Flags.waitdelay)) {
		DeleteAttribute(&BattleInterface, "Waitrefreshflags");
		DelEventHandler("frame", "BI_FlagsDelay");
		DeleteAttribute(&Characters[GetMaincharacterIndex()], "Flags.waitdelay");
	}
}

// Screwface : to fade from lagoon color to sea blue color
void BI_Refreshseacolor_out()
{
	int init = 0;
	if(CheckAttribute(&BattleInterface, "refreshcolor_out")) init = sti(BattleInterface.refreshcolor_out);
	else{If(CheckAttribute(&BattleInterface, "tempcol")) return;} // if a process is not in progress
	//trace("color updated frame : "+init);
	if(init==0)
	{
		//trace("color : 30,55,100");
		int r = 124;
		int g = 202;
		int b = 215;
		int r2 = 109;
		int g2 = 185;
		int b2 = 240;
		BattleInterface.tempcol.framejump = init;
	}
	else
	{
		r = sti(BattleInterface.tempcol.red);
		g = sti(BattleInterface.tempcol.green);
		b = sti(BattleInterface.tempcol.blue);
		r2 = sti(BattleInterface.tempcol.red2);
		g2 = sti(BattleInterface.tempcol.green2);
		b2 = sti(BattleInterface.tempcol.blue2);
	}
	if(init>sti(BattleInterface.tempcol.framejump)+2)
	{
	//Armada: modified normal shade of blue
		if(r>0) r--; //Was 25
		if(g>35) g--; //Was 55
		if(b>90) b--; //Was 80
 		If(r2<255)r2++;
		If(g2<255) g2++;
		If(b2<255) b2++;
		//Sea.GF3.WaterColor = argb(0,r,g,b);
		//Sea.GF3.SkyColor = argb(0,r2,g2,b2);
		Sea.Sea2.WaterColor = argb(0,r,g,b);
		Sea.Sea2.SkyColor = argb(0,r2,g2,b2);
		//if(stf(GetAttribute(Sea,"WaterAttenuation"))>=0.8)
		//	Sea.WaterAttenuation = 0.8;
		//else
		//	Sea.WaterAttenuation = stf(Sea.WaterAttenuation) + 0.0035;
        if(stf(GetAttribute(Sea,"Sea2.Attenuation"))>=0.8)
			Sea.Sea2.Attenuation = 0.8;
		else
			Sea.Sea2.Attenuation = stf(Sea.Sea2.Attenuation) + 0.0035;

		BattleInterface.tempcol.framejump = init;
	}
	BattleInterface.tempcol.red = r;
	BattleInterface.tempcol.green = g;
	BattleInterface.tempcol.blue = b;
	BattleInterface.tempcol.red2 = r2;
	BattleInterface.tempcol.green2 = g2;
	BattleInterface.tempcol.blue2 = b2;
	init++;
	BattleInterface.refreshcolor_out = init;
	if(r<=30 && g<=55 && b<=100) init= - 1;
	if(init==-1) {
		DeleteAttribute(&BattleInterface, "refreshcolor_out");
		DelEventHandler("frame", "BI_Refreshseacolor_out");
		DeleteAttribute(&BattleInterface, "tempcol");
	}
}

// Screwface : to fade from sea color to lagoon color
void BI_Refreshseacolor_in()
{
	int init = 0;
	if(CheckAttribute(&BattleInterface, "refreshcolor_in")) init = sti(BattleInterface.refreshcolor_in);
	else{If(CheckAttribute(&BattleInterface, "tempcol")) return;} // if a process is not in progress
	//trace("color updated frame : "+init);
	if(init==0)
	{
	//Armada: modified normal shade of blue
		int r = 0; //25
		int g = 35; //55
		int b = 90; //80
		int r2 = 255;
		int g2 = 255;
		int b2 = 255;
		BattleInterface.tempcol.framejump = init;
	}
	else
	{
		r = sti(BattleInterface.tempcol.red);
		g = sti(BattleInterface.tempcol.green);
		b = sti(BattleInterface.tempcol.blue);
		r2 = sti(BattleInterface.tempcol.red2);
		g2 = sti(BattleInterface.tempcol.green2);
		b2 = sti(BattleInterface.tempcol.blue2);
	}
	if(init>sti(BattleInterface.tempcol.framejump)+2)
	{
		if(r<124) r++;
		if(g<202) g++;
		if(b<215) b++;
 		If(r2>109)r2--;
		If(g2>185) g2--;
		If(b2>240) b2--;
		//Sea.GF3.WaterColor = argb(0,r,g,b);
		//Sea.GF3.SkyColor = argb(0,r2,g2,b2);
		Sea.Sea2.WaterColor = argb(0,r,g,b);
		Sea.Sea2.SkyColor = argb(0,r2,g2,b2);
		//if(stf(GetAttribute(Sea,"WaterAttenuation"))<=0.3)
		//	Sea.WaterAttenuation = 0.3;
		//else
		//	Sea.WaterAttenuation = stf(Sea.WaterAttenuation) - 0.0035;
        if(stf(GetAttribute(Sea,"Sea2.Attenuation"))<=0.3)
			Sea.Sea2.Attenuation = 0.3;
		else
			Sea.Sea2.Attenuation = stf(Sea.Sea2.Attenuation) - 0.0035;
		BattleInterface.tempcol.framejump = init;
	}
	BattleInterface.tempcol.red = r;
	BattleInterface.tempcol.green = g;
	BattleInterface.tempcol.blue = b;
	BattleInterface.tempcol.red2 = r2;
	BattleInterface.tempcol.green2 = g2;
	BattleInterface.tempcol.blue2 = b2;
	init++;
	BattleInterface.refreshcolor_in = init;
	if(r>=124 && g>=202 && b>=215) init= - 1;
	if(init==-1) {
		DeleteAttribute(&BattleInterface, "refreshcolor_in");
		DelEventHandler("frame", "BI_Refreshseacolor_in");
		DeleteAttribute(&BattleInterface, "tempcol");
	}
}

void StartBattleInterface()
{
	bi_nReloadTarget = -1;
	bi_icons_ShowType = BI_ICONS_ST_MYSHIPS;
	BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
	BI_SetIslandData();
	InterfaceSpyGlassInit();
	objShipPointer.textures.friend = "battle_interface\Frendly.tga.tx";
	objShipPointer.textures.enemy = "battle_interface\Enemy.tga.tx";
	CreateEntity(&objShipPointer,"shippointer");
	LayerAddObject(SEA_EXECUTE,&objShipPointer,222222);
	//Boyer change
	LayerAddObject(SEA_REALIZE,&objShipPointer,222222);
}

void RefreshBattleInterface(bool CheckRelations)
{
// KK -->
	int i, num, fortidx;
	ref chr;
	aref fortattr;
	string fortstr, sfortidx;
	ref PChar = GetMainCharacter();

	if (!IsEntity(&IShipRoll) && Whr_IsStorm() && CheckAttribute(PChar, "Capsize") && GetCharacterShipClass(PChar) < 8)
	{
		// PB: Capsizing -->
		//Boyer change
		CreateEntity(&IShipRoll, "ILogAndActions");
		DeleteAttribute(&IShipRoll, "");
		LayerAddObject(SEA_EXECUTE, &IShipRoll, -257);
		LayerAddObject(SEA_REALIZE, &IShipRoll, -257);
		CopyAttributes(&IShipRoll, &ILog);
		IShipRoll.Log.width  = RecalculateHIcon(20);
		IShipRoll.Log.height = RecalculateVIcon(10);
		IShipRoll.Log.left   = sti(showWindow.left) + makeint(stf(showWindow.width) * 0.45);
		IShipRoll.Log.up     = sti(showWindow.top) + RecalculateVIcon(40);
		IShipRoll.Log.font   = "interface_normal";
		IShipRoll.Log.color  = argb(0,255,255,255);
		IShipRoll.Log.offsetString = 14;
		IShipRoll.Log.speed  = 1.0;
		IShipRoll.Log.color_speed = 0.0;
		SendMessage(&IShipRoll, "lll", LOG_AND_ACTIONS_INIT, false, true);

		SetEventHandler("frame","UpdateShipRoll",1);
		// PB: Capsizing <--
	}

	if (!IsEntity(&IShipPower) && SteamShip(PChar))
	{
		// PB: Steam Ships -->
		//Boyer change
		CreateEntity(&IShipPower, "ILogAndActions");
		DeleteAttribute(&IShipPower, "");
		LayerAddObject(SEA_EXECUTE, &IShipPower, -257);
		LayerAddObject(SEA_REALIZE, &IShipPower, -257);
		CopyAttributes(&IShipPower, &ILog);
		IShipPower.Log.width  = RecalculateHIcon(20);
		IShipPower.Log.height = RecalculateVIcon(10);
		IShipPower.Log.left   = sti(showWindow.right) - makeint(stf(showWindow.width) * 0.14);
		IShipPower.Log.up     = sti(showWindow.top) + RecalculateVIcon(230);
		IShipPower.Log.font   = "interface_normal";
		IShipPower.Log.color  = argb(0,255,255,255);
		IShipPower.Log.offsetString = 14;
		IShipPower.Log.speed  = 1.0;
		IShipPower.Log.color_speed = 0.0;
		SendMessage(&IShipPower, "lll", LOG_AND_ACTIONS_INIT, false, true);

		SetEventHandler("frame","UpdateShipPower",1);
		// PB: Steam Ships <--
	}

	BI_SetCommandMode(0,-1,-1,-1);

	if (CheckRelations)
	{
		CheckAllShips("forts", true); // PB: Set initial relations for ships
		CheckAllShips("ships", true); // PB: Set initial relations for forts

		UpdateRelations();
	}

	RefreshCannonInfo();
// <-- KK
	SendMessage(&BattleInterface,"l",BI_MSG_REFRESH);
	BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
}

void DeleteBattleInterface()
{
	ref chMain = GetMainCharacter();

	Log_SetActiveAction("Nothing");
	InterfaceSpyGlassRelease();

	DeleteClass(&BattleInterface);
	DeleteClass(&objShipPointer);

	DelEventHandler(SHIP_DELETE, "BI_DeleteShip");
	DelEventHandler(SHIP_DEAD,"BI_DeadShip");
	DelEventHandler("BI_CommandEndChecking", "BI_CommandEndChecking");
	DelEventHandler("BI_LaunchCommand", "BI_LaunchCommand");
	DelEventHandler("BI_GetChargeQuantity","BI_GetChargeQuantity");
	DelEventHandler("BI_SetPossibleCommands","BI_SetPossibleCommands");
	DelEventHandler("GetCurrentCharge","GetCurrentCharge");
	DelEventHandler("evntGetCharacterShipClass","biGetCharacterShipClass");
	DelEventHandler(BI_EVENT_SET_VISIBLE,"BI_CommandVisible");
	DelEventHandler(BI_EVENT_SET_SEA_STATE,"BI_SetSeaState");
	DelEventHandler(BI_EVENT_GET_DATA,"BI_GetData");
	DelEventHandler(BI_EVENT_CHECK_SHIPSTATE_SHOW,"BI_GetSSShow");
	DelEventHandler("evntGetLandData","BI_GetLandData");
	DelEventHandler(BI_EVENT_GET_FORT_RELATION,"BI_GetFortRelation");
	DelEventHandler(EVENT_CHANGE_COMPANIONS,"RefreshBattleInterface");
	DelEventHandler("BI_CallUpdateShip","BI_UpdateShip");
	DelEventHandler("frame","BI_Frame");
	DelEventHandler("evntPerkAgainUsable","BI_PerkAgainUsable");
	DelEventHandler("evntSetUsingAbility","procSetUsingAbility");
	DelEventHandler("evntCheckEnableLocator","procCheckEnableLocator");
	DelEventHandler("evntCheckEnableShip","procCheckEnableShip");
	DelEventHandler("evntGetSRollSpeed","procGetSRollSpeed");
	DelEventHandler("Control Activation","BI_ProcessControlPress");
	DelEventHandler("DoSailHole","ProcessSailDamage");
	DelEventHandler("evntBISelectShip","procBISelectShip");
	if (Whr_IsStorm() && CheckAttribute(chMain, "Capsize") && GetCharacterShipClass(chMain) < 8) DelEventHandler("frame", "UpdateShipRoll");		// PB: Capsizing // KK
	if (SteamShip(chMain)) DelEventHandler("frame", "UpdateShipPower");	// PB: Steam Ships // KK

	// LDH clean up after time display 17Sep06
	DeleteDateTimeDisplay(); // KK

	// NK <--

// KK -->
	bDisableAllCommands = false;
	if (!bRealBattleInterface)
	{
		DelEventHandler("evntUpdateCannonInfo", "UpdateCannonInfo");

		DeleteClass(&INLGuns);
		DeleteClass(&INRGuns);
		DeleteClass(&INFGuns);
		DeleteClass(&INBGuns);
	}
// <-- KK
	DeleteClass(&BattleInterface);
	DeleteClass(&objShipPointer);
	DeleteClass(IShipRoll);		// PB: Capsizing
	DeleteClass(IShipPower);	// PB: Steam Ships
}

ref BI_CommandEndChecking()
{
	BI_retComValue = 0;
	string comName = GetEventData();

	switch(comName)
	{
// FCoHS -->
		case "BI_FCoHS_Hail":
			BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT + BI_COMMODE_FRIEND_SHIP_SELECT + BI_COMMODE_ALLLOCATOR_SELECT;
			BattleInterface.Commands.FCoHS_Hail.EffectRadius	= fFCoHS_HailCanBeDistance;
		break;
		case "BI_FCoHS_Contact":
			BI_retComValue = 0;
		break;
// FCoHS <--
// PB: Kraken Attack -->
		case "BI_KrakenAttack":
			BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT + BI_COMMODE_ALLLOCATOR_SELECT;
			BattleInterface.Commands.KrakenAttack.EffectRadius	= 1.5*MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;
		break;
// PB: Kraken Attack <--
// PB: Flying Dutchman -->
		case "BI_SubmergeDutchman":
			BI_retComValue = 0;
		break;
// PB: Flying Dutchman <--
// PB: Black Pearl -->
		case "BI_PearlSweeps":
			BI_retComValue = 0;
		break;
// PB: Black Pearl  <--
// PB: Queen Anne's Revenge -->
		case "BI_QARSword":
			BI_retComValue = 0;
		break;
// PB: Queen Anne's Revenge <--
// C92: Sword of Triton Attack -->
		case "BI_TritonAttack":
            BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT + BI_COMMODE_ALLLOCATOR_SELECT;
            BattleInterface.Commands.KrakenAttack.EffectRadius    = 1.5*MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;
		break;
// C92: Sword of Triton Attack <--
// TJ&PB: Neptune's Trident -->
		case "BI_NeptuneTrident":
			BI_retComValue = 0;
		break;
// TJ&PB: Neptune's Trident  <--
		// Hoist Flag MOD -Amokachi
		case "BI_HoistFlag":
			BI_retComValue = 0;
		break;
// KK -->
// KAM, MAXIMUS -->
		case "BI_EnterDeck":
			SetUserIcons(comName);
			BI_retComValue = BI_COMMODE_USER_ICONS;
		break;
		case "BI_EnterTartaneDeck":
			BI_retComValue = 0;
		break;
// <-- KAM, MAXIMUS
		case "BI_Port":
			BI_retComValue = 0;
		break;
		case "BI_Shore":
			BI_retComValue = 0;
		break;
// <-- KK
		case "BI_Moor":
			BI_retComValue = 0;
		break;
		case "BI_SailTo":
			if(bEnableIslandSailTo) {
				BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_NEUTRAL_FORT_SELECT+BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_LAND_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
				BattleInterface.Commands.SailTo.EffectRadius	= -1.0;
			} else {
				BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
				BattleInterface.Commands.SailTo.EffectRadius	= MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;
			}
		break;
		case "BI_Board":
			BI_retComValue = 0;
		break;
		case "BI_LandTroops":
			BI_retComValue = 0;
		break;
// KK -->
		case "BI_AttackTown":
			BI_retComValue = 0;
		break;
// <-- KK
		case "BI_Map":
			BI_retComValue = 0;
		break;
		case "BI_Attack":
			BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
		case "BI_Defend":
			BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
		case "BI_SailAway":
			BI_retComValue = 0;
		break;
		case "BI_HeaveToDrift":
			BI_retComValue = 0;
		break;
		case "BI_Transfer": // KK
			BI_retComValue = 0;
		break;
		case "BI_Charge":
			//Boyer add
		    SetUserIcons(comName);
			BI_retComValue = BI_COMMODE_CANNON_CHARGE;
		break;
		case "BI_Speed":
			SetUserIcons(comName); // KK
			BI_retComValue = BI_COMMODE_USER_ICONS;
		break;
		case "BI_CompanionCommand":
			BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
		case "BI_Brander":
			BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
		case "BI_ImmediateReload":
			BI_retComValue = 0;
		break;
		case "BI_InstantBoarding":
			BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
		case "BI_LightRepair":
			BI_retComValue = 0;
		break;
		case "BI_InstantRepair":
			BI_retComValue = 0;
		break;
		case "BI_Turn180":
			BI_retComValue = 0;
		break;
		case "BI_SandbankManeuver":
			BI_retComValue = 0;
		break;
		case "BI_Troopers":
			BI_retComValue = BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
		case "BI_Ability":
			BI_retComValue = BI_COMMODE_ABILITY_ICONS;
		break;
		case "BI_ImmDeath":
			BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
	}

	return &BI_retComValue;
}

void BI_LaunchCommand()
{
	//int tmpLangFileID = LanguageOpenFile("interface_strings.txt");
	int charIdx = GetEventData();
	string commandName = GetEventData();
	int targetNum = GetEventData();
	string locName = GetEventData();
	ref chRef = GetCharacter(charIdx);
	int compIdx, cc, i;
	float x,y,z;
	ref PChar = GetMainCharacter();
	ref rCharacter;

	if( LAi_IsDead(chRef) ) return;

	if(targetNum==-1 && locName=="cancel") commandName = "";

	string alternativeCommand;
	if( CheckAttribute( &BattleInterface, "AbilityIcons."+commandName+".quest" ) )
	{
		alternativeCommand = commandName;
		commandName = "BI_UseItemAbilitie";
	}

	switch(commandName)
	{
	// Hoist Flag MOD -Amokachi
	case "BI_HoistFlag":
		PChar.orgnation = GetCurrentFlag();	// ccc dec 05: store old playernation
		HoistFlag(PIRATE);					// become an evil pirate
	break;
// KK -->
	case "BI_EnterShip":
		iShipCaptain = sti(locName);
		bEmergeOnStartloc = true;
		Sea_DeckStartNow(iShipCaptain, GetCharacterShipQDeck(GetCharacter(iShipCaptain)));
		/*switch (locName) {
			case "ShipDeck":
				bEmergeOnStartloc = true;
				Sea_DeckStartNow(GetMainCharacterIndex(), GetCharacterShipQDeck(PChar));
			break;
			case "Cabin":
				Sea_CabinStartNow(PChar);
			break;
			// default:
				Sea_DeckStartNow(GetMainCharacterIndex(), locName);
		}*/
	break;
	/*case "BI_EnterTartaneDeck":
		bEmergeOnStartloc = true;
		Sea_DeckStartNow(GetMainCharacterIndex(), "ShipDeck1");
	break;*/
	case "BI_Port":
		bDisableAllCommands = true;
		PostEvent("BI_SetPossibleCommands", 0, "l", -1);
		Sea_ImmediateLandLoad(false);
	break;
	case "BI_Shore":
		bDisableAllCommands = true;
		PostEvent("BI_SetPossibleCommands", 0, "l", -1);
		Sea_ImmediateLandLoad(false);
	break;
	case "BI_Fort":
		bDisableAllCommands = true;
		PostEvent("BI_SetPossibleCommands", 0, "l", -1);
		Sea_ImmediateLandLoad(true);
	break;
// <-- KK
	case "BI_Charge":
		int chargeType = -1; // KK
		//Boyer
		int nChgType[8];
		nChgType = GetCurrentCharge();
		if (nChgType[0] == 4) break; // KK
		switch(targetNum)
		{
			case 1:
				if (nChgType[0] == 2) break; // KK
				Log_SetStringToLog(XI_ConvertString("Balls"));
				chargeType=GOOD_BALLS;
			break;
			case 2:
				if (nChgType[0] == 3) break; // KK
				Log_SetStringToLog(XI_ConvertString("Grapes"));
				chargeType=GOOD_GRAPES;
			break;
			case 3:
				if (nChgType[0] == 0) break; // KK
				Log_SetStringToLog(XI_ConvertString("Knippels"));
				chargeType=GOOD_KNIPPELS;
			break;
			case 4:
				if (nChgType[0] == 1) break; // KK
				Log_SetStringToLog(XI_ConvertString("Bombs"));
				chargeType=GOOD_BOMBS;
			break;
		}
		Ship_ChangeCharge(chRef, chargeType);
	break;
	case "BI_Map":
		Sea_MapLoad();
	break;
	case "BI_Moor":
// KK -->
		bDisableAllCommands = true;
		PostEvent("BI_SetPossibleCommands", 0, "l", -1);
// <-- KK
		Sea_LandLoad();
	break;
	case "BI_Board":
		Sea_AbordageLoad(SHIP_ABORDAGE,true);
	break;
	case "BI_LandTroops":
		Sea_AbordageLoad(FORT_ABORDAGE, true);
	break;
// KK -->
	case "BI_AttackTown":
		Sea_AbordageLoad(TOWN_ABORDAGE, true);
	break;
// <-- KK
	case "BI_SailAway":
		Ship_SetTaskRunAway(SECONDARY_TASK,charIdx);
	break;
	case "BI_HeaveToDrift":
		Ship_SetTaskDrift(SECONDARY_TASK,charIdx);
	break;
	case "BI_Defend":
		Ship_SetTaskDefend(SECONDARY_TASK,charIdx,GetTargChrIndex(targetNum,locName));
	break;
	case "BI_Attack":
		Ship_SetTaskAttack(SECONDARY_TASK,charIdx,GetTargChrIndex(targetNum,locName));
	break;
// KK -->
	case "BI_Transfer":
		if(bi_nReloadTarget!=-1)
		{
			PChar.shiptransferinterface.calledfrominterface = 0; // NK 05-04-14 to reset back to off.
			LaunchTransferMain(chRef,GetCharacter(bi_nReloadTarget),"");
		}
	break;
// <-- KK
	case "BI_SailTo":
		if(targetNum==-1)
		{ // ???????????????? ?? ?????????????? ?? ???????????? locName
			SeaAI_SailToLocator(locName);
		}
		else
		{ // ?????????????? ?????????? ?? ???????????????? targetNum
			SeaAI_SailToCharacter(targetNum);
		}
	break;
	case "BI_Speed":
		switch(locName)
		{
			case "sail_none":
				Ship_SetSailState(charIdx, 0);
			break;
			case "sail_midi":
				Ship_SetSailState(charIdx, 1);
			break;
			case "sail_fast":
				Ship_SetSailState(charIdx, 2);
			break;
		}
	break;
	case "BI_CompanionCommand":
		BI_SetSpecCommandMode(BI_COMMODE_COMMAND_SELECT,-1,-1,targetNum,1);
		return;
	break;
	case "BI_ImmDeath":
		if(targetNum==-1)
		{ // ???????????? ??????????
			targetNum = Fort_FindCharacter(AISea.Island,"reload",locName);
			if(targetNum>=0)
			{
				Fort_SetAbordageMode(PChar, GetCharacter(targetNum));
			}
		}
		else
		{
			ShipDead(targetNum,KILL_BY_BALL,GetMainCharacterIndex());
		}
	break;
	case "BI_Brander":
		ActivateCharacterPerk(PChar,"Brander");
		Ship_SetTaskBrander(SECONDARY_TASK, charIdx, targetNum);
	break;
	case "BI_ImmediateReload":
		ActivateCharacterPerk(GetCharacter(charIdx),"ImmediateReload");
	break;
	case "BI_InstantBoarding":
		ActivateCharacterPerk(GetCharacter(charIdx),"InstantBoarding");
		CharacterPerkOff(GetCharacter(charIdx),"InstantBoarding");
		if(CheckSuccesfullBoard(GetCharacter(charIdx),GetCharacter(targetNum))) {
			Sea_AbordageStartNow(SHIP_ABORDAGE,targetNum,true,true);
		} else {
			Log_SetStringToLog( XI_ConvertString("failed to board") );
			Event("BI_LaunchCommand","lsls", charIdx, "BI_SailTo", targetNum, locName);
			return;
		}
	break;
	case "BI_LightRepair":
		ActivateCharacterPerk(GetCharacter(charIdx),"LightRepair");
		ActivateSpecRepair(GetCharacter(charIdx),0);
	break;
	case "BI_InstantRepair":
		ActivateCharacterPerk(GetCharacter(charIdx),"InstantRepair");
		ActivateSpecRepair(GetCharacter(charIdx),1);
	break;
	case "BI_Turn180":
		ActivateCharacterPerk(GetCharacter(charIdx),"Turn180");
		Ship_Turn180(GetCharacter(charIdx));
	break;
	case "BI_SandbankManeuver":
		ActivateCharacterPerk(GetCharacter(charIdx),"SandbankManeuver");
	break;
	case "BI_Troopers":
		ActivateCharacterPerk(PChar,"Troopers");
	break;
	// items abilities
	case "BI_UseItemAbilitie":
		CompleteQuestName( BattleInterface.AbilityIcons.(alternativeCommand).quest );
	break;
// FCoHS -->
	case "BI_FCoHS_Hail":
		Event("FCoHS_BICom_HailShip", "l", targetNum);
	break;
	case "BI_FCoHS_Contact":
		Event("FCoHS_BICom_ContactShip");
	break;
// FCoHS <--
// PB: Kraken Attack -->
	case "BI_KrakenAttack":
		KrakenAttack(Characters[targetNum], GetCharacterShipHP(Characters[targetNum])/100 );
	break;
// PB: Kraken Attack <--
// PB: Flying Dutchman -->
	case "BI_SubmergeDutchman":
		if(!CheckAttribute(PChar, "ship.SubmergeDutchman")) PChar.ship.SubmergeDutchman = PChar.ship.CorrectImmersion;
		else PChar.ship.EmergeDutchman = 0;
		DeleteAttribute(PChar, "ship.PlayedSplash");
	break;
// PB: Flying Dutchman <--
// PB: Black Pearl -->
	case "BI_PearlSweeps":
		AddPerkToActiveList("PearlSweeps");
		LogIt("Haul on the main brace! Make ready the guns! And run out the sweeps...");
		PChar.ship.speedburst = "PearlSweeps";
		PChar.Ship.Impulse.Rotate.z = 0.08; // = 4 knots max
		PostEvent("FinishSpeedBurst",120000);
	break;
// PB: Black Pearl <--
// PB: Queen Anne's Revenge -->
	case "BI_QARSword":
		if(IsPerkIntoList("QARSword"))
		{
			pchar.Ship.Impulse.Rotate.z = 0.0;
			DelPerkFromActiveList("QARSword");
			PChar.ship.speedburst = "QARSword";
			PostEvent("SpeedBurstFinished",120000, "i", pchar);
		}
		else
		{
			AddPerkToActiveList("QARSword");
			PChar.Ship.Impulse.Rotate.z = 0.16; // = 8 knots max
		}
	break;
// PB: Queen Anne's Revenge <--
// C92: Sword of Triton Attack -->
    case "BI_TritonAttack":
		float fDamageMultiply = 0.5;
		ref        rShip = GetShipByType(GetCharacterShipType(&Characters[targetNum]));
		float fBaseSailHP = stf(rShip.SP);
		MakeSailDmg(targetNum, fDamageMultiply * fBaseSailHP);
		Ship_ApplyCrewHitpoints(GetCharacter(targetNum), fDamageMultiply * GetCrewQuantity(GetCharacter(targetNum)));
		PChar.ship.speedburst = "QARSword";
		PostEvent("SpeedBurstFinished",120000, "i", pchar);
    break;
// C92: Sword of Triton Attack <--
// TJ&PB: Neptune's Trident -->
	case "BI_NeptuneTrident":
		pchar.skipWeatherLogs = true;
		if(Whr_IsStorm())
		{
			LogIt("By the power of Neptune, I command this storm to end!");
			while(Whr_IsStorm())
			{
				SetNextWind(-1, 20);
				SetNextWeather("Clear");
				CreateWeatherEnvironment();
				MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
			}
			iStormLockSeconds = 0;
		}
		else
		{
			LogIt("I call upon the sea goddess Calypso to bring a storm onto my foes!");
			while(!Whr_IsStorm())
			{
				SetNextWeather("Heavy Storm");
				CreateWeatherEnvironment();
				MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
			}
		}
		DeleteAttribute(PChar, "skipWeatherLogs");

		x = stf(pchar.Ship.pos.x);
		y = stf(pchar.Ship.pos.y);
		z = stf(pchar.Ship.pos.z);

		for(i = 0; i < 100; i++)
		{
			CreateParticleSystemX("cancloud_stock", x+rand(40)-20  , y+rand(15)+3, z+rand(40)-20  , x, y, z,20);
			CreateParticleSystemX("cancloud"      , x+rand(60)-30  , y+rand(20)+3, z+rand(60)-30  , x, y, z,20);
		}
		PlaySound("objects\DUEL\lightning.wav");
	break;
// TJ&PB: Neptune's Trident <--
	}

	BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
//	LanguageCloseFile(tmpLangFileID);
}

void BI_SetIslandData()
{
	if(!CheckAttribute(AISea,"Island")) return;
	int isln = FindIsland(AISea.Island);
	if(isln==-1) return;

	ref atmp;
	atmp = GetIslandByIndex(isln);
	SendMessage(&BattleInterface,"la",BI_MSG_SET_ISLAND,atmp);
}

void BI_UpdateShip()
{
	int charIndex = GetEventData();
	AddShipToInterface(charIndex);
}

void BI_CreateShip()
{
	int charIndex = GetEventData();
	if(charIndex>=0) ClearActiveChrPerks(GetCharacter(charIndex));
	if( IsEntity(&BattleInterface) ) {
		AddShipToInterface(charIndex);
	}
}

void AddShipToInterface(int charIndex)
{
	if(charIndex==-1)
	{
		Trace("ERROR: Invalid character index for create ship");
		return;
	}
	ref chRef = GetCharacter(charIndex);
	int st = GetCharacterShipType(chRef);
	if( st==SHIP_NOTUSED )
	{
		Trace("WARNING!!! Character id = "+chRef.id+" hav`t ship.");
		return;
	}

// LDH -->
	if (CheckAttribute(chRef, "NeedSailDmg"))
	{
		float fDamage = stf(chRef.NeedSailDmg);
		DeleteAttribute(chRef, "NeedSailDmg");
		MakeSailDmg(charIndex, fDamage);	// this applies the damage to SP and makes holes in the sails, moved from AIShip.c
	}
// LDH <--

	chRef.unknownShip = true; // KK
	chRef.nation.known = -2; // KK

	// NK 05-04-15 PRS3 data bars
	ref realshipRef = GetShipByType(st);
	ref mainChRef = GetMainCharacter(); // KK
	int idx, i;
	if(CheckAttribute(chRef,"curshipnum")) {
		idx = sti(chRef.curshipnum);
	}
	else
	{
		for(i = 0; i < MAX_SHIPS_ON_SEA; i++)
		{
			if(Ships[i] == charIndex)
			{
				idx = i;
				chRef.curshipnum = i;
			}
		}
	}
// KK -->
	if (idx < 0) {
		for(i = 0; i < COMPANION_MAX; i++)
		{
			if (GetCompanionIndex(mainChRef, i) >= 0 && GetRemovable(GetCharacter(GetCompanionIndex(mainChRef, i))))
			{
				if (GetCompanionIndex(mainChRef, i) == charIndex) {
					idx = i;
					chRef.curshipnum = i;
				}
			}
		}
	}
// <-- KK
	ref shipRef = &ShipStats[idx];
	DeleteAttribute(shipRef,""); // clear out
	aref arshipstats; makearef(arshipstats, chRef.ship.stats);
	CopyAttributes(&shipRef, &realshipRef); // copy base ship over.
	/*trace("*****************************for character " + chRef.id + " with curshipnum " + idx + " we will now dump stats before apply local.");
	DumpAttributes(shipRef);*/
	string tat;
	for(i = 0; i < GetAttributesNum(arshipstats); i++) // overwrite with local stats if exist.
	{
		tat = GetAttributeName(GetAttributeN(arshipstats, i));
		shipRef.(tat) = GetAttributeValue(GetAttributeN(arshipstats, i));
	}
	/*trace("***************And after:");
	DumpAttributes(shipRef);*/
	// NK <--
	int myShip = false;
	int shipRelation = BI_RELATION_NEUTRAL;
// KK -->
	if (SeaAI_GetRelation(charIndex, GetMainCharacterIndex()) == RELATION_ENEMY) shipRelation = BI_RELATION_ENEMY;
	if (Ship_GetGroupID(chRef) == PLAYER_GROUP) shipRelation = BI_RELATION_FRIEND;
// <-- KK

	for(i=0; i<COMPANION_MAX; i++) // NK i declared above. 05-04-15
	{
		if(GetCompanionIndex(mainChRef,i) == charIndex)
		{
			myShip = true;
		}
	}

	if( CharacterIsDead(chRef) )
	{
		if( !CheckAttribute(chRef,"ship.shipsink") || sti(chRef.ship.shipsink)==false )
			return;
	}

	//Screwface : No other ships infos in bars in menu in realistic mod
	if(iRealismMode>0 && charIndex != GetMainCharacterIndex() && !IsCompanion(chRef)) DeleteAttribute(shipRef,"");

	SendMessage(&BattleInterface,"llaall",BI_IN_CREATE_SHIP,charIndex,chRef,shipRef,myShip,shipRelation);
}

void BI_DeleteShip()
{
	ref chr; // KK
	int charIndex = GetEventData();
	if (charIndex == -1) {
		Trace("ERROR: Invalid character index");
		return;
	}
	chr = GetCharacter(charIndex);
	if (IsCompanion(chr)) RemoveCharacterCompanion(GetMainCharacter(), chr);
	DeleteAttribute(chr, "ship.shipsink");
	DeleteAttribute(chr, "curshipnum"); // NK 05-04-15 used in addshiptointerface
	DeleteAttribute(chr, "nation.known"); // KK
	if (CheckAttribute(chr, "unknownShip")) DeleteAttribute(chr, "unknownShip"); // KK
	RefreshBattleInterface(false);
}

void BI_DeadShip()
{
	ref chr; // KK
	int charIndex = GetEventData();
	if (charIndex == -1) {
		Trace("ERROR: Invalid character index");
		return;
	}
	chr = GetCharacter(charIndex);
	if (IsCompanion(chr)) RemoveCharacterCompanion(GetMainCharacter(),GetCharacter(charIndex));
	if (GetMainCharacterIndex() == charIndex) SeaCameras_SetMyShip(); // KK
	chr.ship.shipsink = true;
	RefreshBattleInterface(false);
}

void BI_SetCommandMode(int commode, int texNum, int picNum, int chIdx)
{
	bi_icons_CommandMode = commode;
	SendMessage(&BattleInterface,"llllll",BI_IN_SET_COMMAND_MODE,commode,texNum,picNum,chIdx,-1);
}

void BI_SetSpecCommandMode(int commode, int texNum, int picNum, int chIdx, int comState)
{
	bi_icons_CommandMode = commode;
	SendMessage(&BattleInterface,"llllll",BI_IN_SET_COMMAND_MODE,commode,texNum,picNum,chIdx,comState);
}

void BI_SetPossibleCommands()
{
	int chIdx = GetEventData();
	ref mainCh = GetMainCharacter();
	int mainIdx = sti(mainCh.index);

	if( chIdx<0 || CharacterIsDead(GetCharacter(chIdx)) || bDisableAllCommands==true) // KK
	{
		aref aroot,arcur;
		makearef(aroot,BattleInterface.Commands);
		int q = GetAttributesNum(aroot);
		for(int i=0; i<q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		BattleInterface.Commands.Cancel.enable = true;
		return;
	}

	// ?????? ???????????????? ??????????????????
	if(mainIdx==chIdx)
	{
		BattleInterface.Commands.Moor.enable				= bCanEnterToLand;
		string DestinationType = ""; // MAXIMUS
		if(bCanEnterToLand) DestinationType = CheckDestinationType(); // KK // MAXIMUS
		BattleInterface.Commands.LandPort.enable			= VISIT_DECK == 1 && bCanEnterToLand == true && DestinationType != "seashore"; // KK
		BattleInterface.Commands.LandShore.enable			= VISIT_DECK == 1 && bCanEnterToLand == true && DestinationType == "seashore"; // KK
		BattleInterface.Commands.Board.enable				= bAbordageShipCanBe;
		BattleInterface.Commands.SailAway.enable			= false;
		BattleInterface.Commands.HeaveToDrift.enable		= false;
		BattleInterface.Commands.Charge.enable				= CheckAttribute(mainCh,"Ship.Cannons.Charge.Type") && GetCaracterShipCannonsType(mainCh) != CANNON_TYPE_NONECANNON; // KK
		BattleInterface.Commands.LandTroops.enable			= bAbordageFortCanBe;
		BattleInterface.Commands.AttackTown.enable			= bAbordageTownCanBe; // KK
		//BattleInterface.Commands.LandFort.enable			= bCanEnterToFort; // KK - PB: This is unfinished and leads nowhere
		BattleInterface.Commands.Attack.enable				= false;
		BattleInterface.Commands.Defend.enable				= false;
		BattleInterface.Commands.Transfer.enable			= bReloadCanBe; // KK
		BattleInterface.Commands.HoistFlag.enable			= sti(mainCh.nation) != PIRATE;										// PB: No Hoisting Pirate Flag if Already Pirate!
		BattleInterface.Commands.KrakenAttack.enable		= KrakenAttackEnabled();											// PB: Kraken Attack
		BattleInterface.Commands.SubmergeDutchman.enable	= GetAttribute(mainCh, "ship.type") == "CursedDutchman";			// PB: Flying Dutchman
		BattleInterface.Commands.PearlSweeps.enable			= BPSweepsEnabled();												// PB: Black Pearl
		BattleInterface.Commands.QARSword.enable			= QARSwordEnabled();												// PB: Queen Anne's Revenge
		BattleInterface.Commands.TritonAttack.enable		= QARSwordEnabled();								                // C92: Sword of Triton Attack
		BattleInterface.Commands.NeptuneTrident.enable		= CheckCharacterItem(mainCh, "Trident_Neptune");					// TJ&PB: Neptune's Trident

// FCoHS -->
		BattleInterface.Commands.FCoHS_Hail.enable			= bFCoHS_HailCanBe;
		BattleInterface.Commands.FCoHS_Contact.enable		= bFCoHS_ContactCanBe;
// FCoHS <--

		// Flayed One --->
		if(iRealismMode>1 || SAILTO_DISABLED) 		BattleInterface.Commands.SailTo.enable			= false;
		else										BattleInterface.Commands.SailTo.enable			= !bDisableSailTo && bSailTo;
		if(iRealismMode>1 || WORLDMAP_DISABLED) 	BattleInterface.Commands.Map.enable				= false;
		else										BattleInterface.Commands.Map.enable				= bMapEnter;
		// Flayed One <---

		BattleInterface.Commands.EnterShip.enable		= bMapEnter; // KK
		BattleInterface.Commands.Speed.enable			= true;
		BattleInterface.Commands.CCommand.enable		= GetCompanionQuantity(mainCh)>1;
		BattleInterface.Commands.Ability.enable			= true;
	}
	// ?????? ??????????????????
	else
	{
		BattleInterface.Commands.Moor.enable				= false;
		BattleInterface.Commands.LandPort.enable			= false; // KK
		BattleInterface.Commands.LandShore.enable			= false; // KK
		BattleInterface.Commands.Board.enable				= false;
		BattleInterface.Commands.SailAway.enable			= true;
		BattleInterface.Commands.HeaveToDrift.enable		= true;
		BattleInterface.Commands.Charge.enable				= false;
		BattleInterface.Commands.LandTroops.enable			= false;
		BattleInterface.Commands.AttackTown.enable			= false; // KK
		BattleInterface.Commands.LandFort.enable			= false; // KK
		BattleInterface.Commands.Attack.enable				= bAttack;
		BattleInterface.Commands.Defend.enable				= bDefend;
		BattleInterface.Commands.Transfer.enable			= false; // KK
		BattleInterface.Commands.KrakenAttack.enable		= false; // PB: Kraken Attack
		BattleInterface.Commands.SubmergeDutchman.enable	= false; // PB: Flying Dutchman
		BattleInterface.Commands.PearlSweeps.enable			= false; // PB: Black Pearl
		BattleInterface.Commands.QARSword.enable			= false; // PB: Queen Anne's Revenge
		BattleInterface.Commands.TritonAttack.enable		= false; // C92: Sword of Triton Attack
		BattleInterface.Commands.NeptuneTrident.enable		= false; // TJ&PB: Neptune's Trident
// FCoHS -->
		BattleInterface.Commands.FCoHS_Hail.enable			= false;
		BattleInterface.Commands.FCoHS_Contact.enable		= false;
// FCoHS <--
		BattleInterface.Commands.SailTo.enable				= false;
		BattleInterface.Commands.Map.enable					= false;
		BattleInterface.Commands.EnterShip.enable			= false; // KK // KAM, MAXIMUS Deck
		BattleInterface.Commands.Speed.enable				= false;
		BattleInterface.Commands.CCommand.enable			= false;
		BattleInterface.Commands.Ability.enable				= true;
	}
}

void BI_InitializeCommands()
{
	int idLngFile = LanguageOpenFile("commands_name.txt");

	//#20171121-02 Add option to battle commands to highlight active companion ship
	BattleInterface.HighlightActiveShip = true;
	//#20171121-01 Add option to battle commands to always revert back to main char
	BattleInterface.EscRevertMainChar = true;

// KK -->
	BattleInterface.Commands.Cancel.enable			= false;
	BattleInterface.Commands.Cancel.picNum			= 0;
	BattleInterface.Commands.Cancel.selPicNum			= 1;
	BattleInterface.Commands.Cancel.texNum			= BI_ICONS_TEXTURE_CANCEL; // KK
	BattleInterface.Commands.Cancel.event			= "Cancel";
	BattleInterface.Commands.Cancel.note			= LanguageConvertString(idLngFile, "sea_Cancel");
	BattleInterface.Commands.Moor.enable			= false;
	BattleInterface.Commands.Moor.picNum			= 1;
	BattleInterface.Commands.Moor.selPicNum			= 5;
	BattleInterface.Commands.Moor.texNum		    = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Moor.event				= "BI_Moor";
	BattleInterface.Commands.Moor.note				= LanguageConvertString(idLngFile, "sea_Moor");
	BattleInterface.Commands.LandPort.enable		= false;
	BattleInterface.Commands.LandPort.picNum		= 1;
	BattleInterface.Commands.LandPort.selPicNum		= 5;
	BattleInterface.Commands.LandPort.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.LandPort.event			= "BI_Port";
	BattleInterface.Commands.LandPort.note			= LanguageConvertString(idLngFile, "sea_Port");
	BattleInterface.Commands.LandShore.enable		= false;
	BattleInterface.Commands.LandShore.picNum		= 1;
	BattleInterface.Commands.LandShore.selPicNum		= 5;
	BattleInterface.Commands.LandShore.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.LandShore.event		= "BI_Shore";
	BattleInterface.Commands.LandShore.note			= LanguageConvertString(idLngFile, "sea_Shore");
	BattleInterface.Commands.Board.enable			= false;
	BattleInterface.Commands.Board.picNum			= 2;
	BattleInterface.Commands.Board.selPicNum			= 6;
	BattleInterface.Commands.Board.texNum		    = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Board.event			= "BI_Board";
	BattleInterface.Commands.Board.note				= LanguageConvertString(idLngFile, "sea_Board");
// KK -->
	BattleInterface.Commands.AttackTown.enable		= false;
	BattleInterface.Commands.AttackTown.picNum		= 8;
	BattleInterface.Commands.AttackTown.selPicNum		= 12;
	BattleInterface.Commands.AttackTown.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.AttackTown.event		= "BI_AttackTown";
	BattleInterface.Commands.AttackTown.note		= LanguageConvertString(idLngFile, "sea_LandTroops");
	BattleInterface.Commands.LandFort.enable		= false;
	BattleInterface.Commands.LandFort.texNum		= BI_ICONS_TEXTURE_LANDTARG1;
	BattleInterface.Commands.LandFort.event			= "BI_Fort";
	BattleInterface.Commands.LandFort.note			= LanguageConvertString(idLngFile, "sea_Fort");
// <-- KK
	BattleInterface.Commands.SailTo.enable			= false;
	BattleInterface.Commands.SailTo.picNum			= 3;
	BattleInterface.Commands.SailTo.selPicNum			= 7;
	BattleInterface.Commands.SailTo.texNum		    = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailTo.event			= "BI_SailTo";
	BattleInterface.Commands.SailTo.note			= LanguageConvertString(idLngFile, "sea_SailTo");
	BattleInterface.Commands.LandTroops.enable		= false;
	BattleInterface.Commands.LandTroops.picNum		= 8;
	BattleInterface.Commands.LandTroops.selPicNum		= 12;
	BattleInterface.Commands.LandTroops.texNum		= BI_ICONS_TEXTURE_LANDTARG1;
	BattleInterface.Commands.LandTroops.event		= "BI_LandTroops";
	BattleInterface.Commands.LandTroops.note		= LanguageConvertString(idLngFile, "sea_LandTroops");
	BattleInterface.Commands.Map.enable				= false;
	BattleInterface.Commands.Map.picNum				= 9;
	BattleInterface.Commands.Map.selPicNum				= 13;
	BattleInterface.Commands.Map.texNum		        = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Map.event				= "BI_Map";
	BattleInterface.Commands.Map.note				= LanguageConvertString(idLngFile, "sea_Map");

	BattleInterface.Commands.Attack.enable			= false;
	BattleInterface.Commands.Attack.picNum			= 11;
	BattleInterface.Commands.Attack.selPicNum			= 15;
	BattleInterface.Commands.Attack.texNum		    = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Attack.event			= "BI_Attack";
	BattleInterface.Commands.Attack.note			= LanguageConvertString(idLngFile, "sea_Attack");
	BattleInterface.Commands.Defend.enable			= false;
	BattleInterface.Commands.Defend.picNum			= 16;
	BattleInterface.Commands.Defend.selPicNum			= 20;
	BattleInterface.Commands.Defend.texNum		    = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Defend.event			= "BI_Defend";
	BattleInterface.Commands.Defend.note			= LanguageConvertString(idLngFile, "sea_Defend");
	BattleInterface.Commands.SailAway.enable		= false;
	BattleInterface.Commands.SailAway.picNum		= 17;
	BattleInterface.Commands.SailAway.selPicNum		= 21;
	BattleInterface.Commands.SailAway.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailAway.event			= "BI_SailAway";
	BattleInterface.Commands.SailAway.note			= LanguageConvertString(idLngFile, "sea_SailAway");
	BattleInterface.Commands.HeaveToDrift.enable	= false;
	BattleInterface.Commands.HeaveToDrift.picNum	= 18;
	BattleInterface.Commands.HeaveToDrift.selPicNum	= 22;
	BattleInterface.Commands.HeaveToDrift.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.HeaveToDrift.event		= "BI_HeaveToDrift";
	BattleInterface.Commands.HeaveToDrift.note		= LanguageConvertString(idLngFile, "sea_HeaveToDrift");
	//BattleInterface.Commands.CCommand.enable		= false;
	//BattleInterface.Commands.CCommand.picNum		= 26;
	//BattleInterface.Commands.CCommand.selPicNum		= 30;
	//BattleInterface.Commands.CCommand.texNum		= BI_ICONS_TEXTURE_COMMAND;
	//BattleInterface.Commands.CCommand.event			= "BI_CompanionCommand";
	//BattleInterface.Commands.CCommand.note			= LanguageConvertString(idLngFile, "sea_CCommand");
	BattleInterface.Commands.Ability.enable			= false;
	BattleInterface.Commands.Ability.picNum			= 25;
	BattleInterface.Commands.Ability.selPicNum			= 29;
	BattleInterface.Commands.Ability.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Ability.event			= "BI_Ability";
	BattleInterface.Commands.Ability.note			= LanguageConvertString(idLngFile, "sea_Ability");
	BattleInterface.Commands.Transfer.enable		= false;
	BattleInterface.Commands.Transfer.picNum		= 10;
	BattleInterface.Commands.Transfer.selPicNum		= 14;
	BattleInterface.Commands.Transfer.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Transfer.event			= "BI_Transfer";
	BattleInterface.Commands.Transfer.note			= LanguageConvertString(idLngFile, "sea_Transfer");
// FCoHS -->
	BattleInterface.Commands.FCoHS_Hail.enable		= false;
	BattleInterface.Commands.FCoHS_Hail.picNum		= 26;
	BattleInterface.Commands.FCoHS_Hail.selPicNum		= 30;
	BattleInterface.Commands.FCoHS_Hail.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.FCoHS_Hail.event		= "BI_FCoHS_Hail";
	BattleInterface.Commands.FCoHS_Hail.note		= LanguageConvertString(idLngFile, "sea_FCoHS_Hail"); // PB: Add text
	BattleInterface.Commands.FCoHS_Contact.enable	= false;
	BattleInterface.Commands.FCoHS_Contact.picNum	= 33;
	BattleInterface.Commands.FCoHS_Contact.selPicNum	= 37;
	BattleInterface.Commands.FCoHS_Contact.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.FCoHS_Contact.event	= "BI_FCoHS_Contact";
	BattleInterface.Commands.FCoHS_Contact.note		= LanguageConvertString(idLngFile, "sea_FCoHS_Contact"); // PB: Add text
// FCoHS <--
// PB: Kraken Attack -->
	BattleInterface.Commands.KrakenAttack.enable	= false;
	BattleInterface.Commands.KrakenAttack.picNum	= 35;
	BattleInterface.Commands.KrakenAttack.selPicNum	= 39;
	BattleInterface.Commands.KrakenAttack.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.KrakenAttack.event		= "BI_KrakenAttack";
	BattleInterface.Commands.KrakenAttack.note		= LanguageConvertString(idLngFile, "sea_KrakenAttack");
// PB: Kraken Attack <--
// PB: Flying Dutchman -->
	BattleInterface.Commands.SubmergeDutchman.enable	= false;
	BattleInterface.Commands.SubmergeDutchman.picNum	= 40;
	BattleInterface.Commands.SubmergeDutchman.selPicNum	= 44;
	BattleInterface.Commands.SubmergeDutchman.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SubmergeDutchman.event		= "BI_SubmergeDutchman";
	BattleInterface.Commands.SubmergeDutchman.note		= LanguageConvertString(idLngFile, "sea_SubmergeDutchman");
// PB: Flying Dutchman <--
// PB: Black Pearl -->
	BattleInterface.Commands.PearlSweeps.enable		= false;
	BattleInterface.Commands.PearlSweeps.picNum		= 41;
	BattleInterface.Commands.PearlSweeps.selPicNum		= 45;
	BattleInterface.Commands.PearlSweeps.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.PearlSweeps.event		= "BI_PearlSweeps";
	BattleInterface.Commands.PearlSweeps.note		= LanguageConvertString(idLngFile, "sea_PearlSweeps");
// PB: Black Pearl <--
// PB: Queen Anne's Revenge -->
	BattleInterface.Commands.QARSword.enable		= false;
	BattleInterface.Commands.QARSword.picNum		= 42;
	BattleInterface.Commands.QARSword.selPicNum		= 46;
	BattleInterface.Commands.QARSword.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.QARSword.event			= "BI_QARSword";
	BattleInterface.Commands.QARSword.note			= LanguageConvertString(idLngFile, "sea_QARSword");
// PB: Queen Anne's Revenge <--
// C92: Sword of Triton Attack -->
	BattleInterface.Commands.TritonAttack.enable	= false;
	//Boyer note:  Need to check .picNum in texture and also add .selPicNum
	BattleInterface.Commands.TritonAttack.picNum	= 24;
	//BattleInterface.Commands.TritonAttack.selPicNum		= 24;
	BattleInterface.Commands.TritonAttack.event		= "BI_TritonAttack";
	BattleInterface.Commands.TritonAttack.note		= LanguageConvertString(idLngFile, "sea_TritonAttack");
// C92: Sword of Triton Attack <--
// TJ&PB: Neptune's Trident -->
	BattleInterface.Commands.NeptuneTrident.enable	= false;
	BattleInterface.Commands.NeptuneTrident.picNum	= 43;
	BattleInterface.Commands.NeptuneTrident.selPicNum	= 47;
	BattleInterface.Commands.NeptuneTrident.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.NeptuneTrident.event	= "BI_NeptuneTrident";
	BattleInterface.Commands.NeptuneTrident.note	= LanguageConvertString(idLngFile, "sea_NeptuneTrident");
// TJ&PB: Neptune's Trident <--
	BattleInterface.Commands.Charge.enable			= false;
	BattleInterface.Commands.Charge.picNum			= 19;
	BattleInterface.Commands.Charge.selPicNum			= 23;
	BattleInterface.Commands.Charge.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Charge.event			= "BI_Charge";
	BattleInterface.Commands.Charge.note			= LanguageConvertString(idLngFile, "sea_Charge");
	BattleInterface.Commands.Speed.enable			= false;
	BattleInterface.Commands.Speed.picNum			= 24;
	BattleInterface.Commands.Speed.selPicNum			= 28;
	BattleInterface.Commands.Speed.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Speed.event			= "BI_Speed";
	BattleInterface.Commands.Speed.note				= LanguageConvertString(idLngFile, "sea_Speed");
	BattleInterface.Commands.ImmediateDeath.enable	= false;
	BattleInterface.Commands.ImmediateDeath.picNum	= 0;
	BattleInterface.Commands.ImmediateDeath.selPicNum	= 1;
	BattleInterface.Commands.ImmediateDeath.event	= "BI_ImmDeath";
	BattleInterface.Commands.ImmediateDeath.texNum	= BI_ICONS_TEXTURE_SKULL;
	BattleInterface.Commands.ImmediateDeath.note	= LanguageConvertString(idLngFile, "sea_ImmediateDeath");

	BattleInterface.AbilityIcons.Brander.enable				= false;
	BattleInterface.AbilityIcons.Brander.picNum				= 0;
	BattleInterface.AbilityIcons.Brander.selPicNum				= 4;
	BattleInterface.AbilityIcons.Brander.texNum				= BI_ICONS_TEXTURE_ABILITY;
	BattleInterface.AbilityIcons.Brander.event				= "BI_Brander";
	BattleInterface.AbilityIcons.Brander.note				= LanguageConvertString(idLngFile, "sea_Brander");
	BattleInterface.AbilityIcons.ImmediateReload.enable		= false;
	BattleInterface.AbilityIcons.ImmediateReload.picNum		= 10;
	BattleInterface.AbilityIcons.ImmediateReload.selPicNum		= 14;
	BattleInterface.AbilityIcons.ImmediateReload.texNum		= BI_ICONS_TEXTURE_ABILITY;
	BattleInterface.AbilityIcons.ImmediateReload.event		= "BI_ImmediateReload";
	BattleInterface.AbilityIcons.ImmediateReload.note		= LanguageConvertString(idLngFile, "sea_FastReload");
	BattleInterface.AbilityIcons.InstantBoarding.enable		= false;
	BattleInterface.AbilityIcons.InstantBoarding.picNum		= 11;
	BattleInterface.AbilityIcons.InstantBoarding.selPicNum		= 15;
	BattleInterface.AbilityIcons.InstantBoarding.texNum		= BI_ICONS_TEXTURE_ABILITY;
	BattleInterface.AbilityIcons.InstantBoarding.event		= "BI_InstantBoarding";
	BattleInterface.AbilityIcons.InstantBoarding.note		= LanguageConvertString(idLngFile, "sea_InstantBoarding");
	BattleInterface.AbilityIcons.LightRepair.enable			= false;
	BattleInterface.AbilityIcons.LightRepair.picNum			= 9;
	BattleInterface.AbilityIcons.LightRepair.selPicNum			= 13;
	BattleInterface.AbilityIcons.LightRepair.texNum			= BI_ICONS_TEXTURE_ABILITY;
	BattleInterface.AbilityIcons.LightRepair.event			= "BI_LightRepair";
	BattleInterface.AbilityIcons.LightRepair.note			= LanguageConvertString(idLngFile, "sea_LightRepair");
	BattleInterface.AbilityIcons.InstantRepair.enable		= false;
	BattleInterface.AbilityIcons.InstantRepair.picNum		= 1;
	BattleInterface.AbilityIcons.InstantRepair.selPicNum		= 5;
	BattleInterface.AbilityIcons.InstantRepair.texNum		= BI_ICONS_TEXTURE_ABILITY;
	BattleInterface.AbilityIcons.InstantRepair.event		= "BI_InstantRepair";
	BattleInterface.AbilityIcons.InstantRepair.note			= LanguageConvertString(idLngFile, "sea_InstantRepair");
	BattleInterface.AbilityIcons.Turn180.enable				= false;
	BattleInterface.AbilityIcons.Turn180.picNum				= 2;
	BattleInterface.AbilityIcons.Turn180.selPicNum				= 6;
	BattleInterface.AbilityIcons.Turn180.texNum				= BI_ICONS_TEXTURE_ABILITY;
	BattleInterface.AbilityIcons.Turn180.event				= "BI_Turn180";
	BattleInterface.AbilityIcons.Turn180.note				= LanguageConvertString(idLngFile, "sea_Turn180");
	BattleInterface.AbilityIcons.SandbankManeuver.enable	= false;
	BattleInterface.AbilityIcons.SandbankManeuver.picNum	= 3;
	BattleInterface.AbilityIcons.SandbankManeuver.selPicNum	= 7;
	BattleInterface.AbilityIcons.SandbankManeuver.texNum	= BI_ICONS_TEXTURE_ABILITY;
	BattleInterface.AbilityIcons.SandbankManeuver.event		= "BI_SandbankManeuver";
	BattleInterface.AbilityIcons.SandbankManeuver.note		= LanguageConvertString(idLngFile, "sea_SandbankManeuver");
	BattleInterface.AbilityIcons.Troopers.enable			= false;
	BattleInterface.AbilityIcons.Troopers.picNum			= 8;
	BattleInterface.AbilityIcons.Troopers.selPicNum			= 12;
	BattleInterface.AbilityIcons.Troopers.texNum			= BI_ICONS_TEXTURE_ABILITY;
	BattleInterface.AbilityIcons.Troopers.event				= "BI_Troopers";
	BattleInterface.AbilityIcons.Troopers.note				= LanguageConvertString(idLngFile, "sea_Troopers");

// MAXIMUS Deck -->
// KK -->
	ref mainCh = GetMainCharacter();
	if (GetCompanionQuantity(mainCh) == 1) {
		int st = GetCharacterShipType(mainCh);
		if (st >= 0 && st < SHIP_TYPES_QUANTITY) {
			BattleInterface.Commands.EnterShip.enable = true;
			BattleInterface.Commands.EnterShip.picNum = sti(ShipsTypes[st].BI.Pic);
			//Boyer change
			if(CheckAttribute(ShipsTypes[st], "BI.selPic"))
                BattleInterface.Commands.EnterShip.selPicNum = sti(ShipsTypes[st].BI.selPic);
            else
                BattleInterface.Commands.EnterShip.selPicNum = sti(ShipsTypes[st].BI.Pic) + 1;
			BattleInterface.Commands.EnterShip.texNum = sti(ShipsTypes[st].BI.Tex);
			BattleInterface.Commands.EnterShip.event  = "BI_EnterShip";
			BattleInterface.Commands.EnterShip.note   = GetMyShipName(mainCh);
			BattleInterface.Commands.EnterShip.name   = GetMainCharacterIndex();
		}
	} else {
		BattleInterface.Commands.EnterShip.enable = true;
		BattleInterface.Commands.EnterShip.picNum = 9;
		BattleInterface.Commands.EnterShip.selPicNum = 13;
		BattleInterface.Commands.EnterShip.texNum = BI_ICONS_TEXTURE_LANDTARG1;
		BattleInterface.Commands.EnterShip.event  = "BI_EnterShip";
		BattleInterface.Commands.EnterShip.note   = LanguageConvertString(idLngFile, "sea_EnterDeck");
	}
// <-- KK
// MAXIMUS Deck <--

	// Hoist Flag MOD -Amokachi
	BattleInterface.Commands.HoistFlag.enable			= false;
	BattleInterface.Commands.HoistFlag.picNum			= 27; // KK
	BattleInterface.Commands.HoistFlag.selPicNum			= 31;
	BattleInterface.Commands.HoistFlag.texNum = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.HoistFlag.event			= "BI_HoistFlag";
	BattleInterface.Commands.HoistFlag.note			= LanguageConvertString(idLngFile, "sea_HoistFlag");

	LanguageCloseFile(idLngFile);
}

ref BI_GetChargeQuantity()
{
	int chIdx = GetEventData();
	ref refChar = GetCharacter(chIdx);
	BI_ChargeState[0] = 4;
	BI_ChargeState[1] = GetCargoGoods(refChar,GOOD_BALLS);
	BI_ChargeState[2] = GetCargoGoods(refChar,GOOD_GRAPES);
	BI_ChargeState[3] = GetCargoGoods(refChar,GOOD_KNIPPELS);
	BI_ChargeState[4] = GetCargoGoods(refChar,GOOD_BOMBS);

	return &BI_ChargeState;
}

ref GetCurrentCharge()
{
	ref refChar = GetMainCharacter();
	BI_intRetValue = -1;

	if( CheckAttribute(refChar,"Ship.Cannons.Charge.Type") )
	{
		switch(sti(refChar.Ship.Cannons.Charge.Type))
		{
		case GOOD_BALLS:
			BI_intNRetValue[0] = 2;
			break;
		case GOOD_GRAPES:
			BI_intNRetValue[0] = 3;
			break;
		case GOOD_KNIPPELS:
			BI_intNRetValue[0] = 0;
			break;
		case GOOD_BOMBS:
			BI_intNRetValue[0] = 1;
			break;
		}
		if(bNotEnoughPowder) BI_intNRetValue[0] = 4; // TIH varname update // changed by MAXIMUS [gunpowder mod]
	}
	BI_intNRetValue[2] = 61;

	return &BI_intNRetValue;
}

ref biGetCharacterShipClass()
{
	int nChrIdx = GetEventData();
	BI_intRetValue = 1;
	if( nChrIdx>=0 && nChrIdx<TOTAL_CHARACTERS ) {
		BI_intRetValue = GetCharacterShipClass( &Characters[nChrIdx] );
	}
	return &BI_intRetValue;
}

void BI_SetSeaState()
{
	bool bTmp;
	bSailTo = GetEventData();
	bTmp = GetEventData();
	bMapEnter = GetEventData();
	bAttack = GetEventData();
	bDefend = GetEventData();
	bReloadCanBe = GetEventData();
	bi_nReloadTarget = GetEventData();
	if(bDisableMapEnter)	bMapEnter = false; // PB: Moved up so Sail-To gets disabled correctly
	bEnableIslandSailTo = bMapEnter;
}

ref BI_GetData()
{
	int dataType = GetEventData();
// KK -->
	int chrIdx = GetEventData();
	int st;
	ref chRef;
	float distance;
	bool enable = false;
	if (chrIdx < 0) return &BI_intNRetValue;
	chRef = GetCharacter(chrIdx);
	distance = Ship_GetDistance2D(GetMainCharacter(), chRef);
// <-- KK

	switch (dataType)
	{
	// ???????????????? ?????????? ???????????????? ??????????????
		case BIDT_SHIPPICTURE:
			enable = distance < GetCharVisibilityRange(GetMainCharacter(), 1); // PB: Ship type is visible inside LONG range
			if (CheckAttribute(chRef, "unknownShip") == true && sti(chRef.unknownShip) == true) {
				if (enable) DeleteAttribute(chRef, "unknownShip");
			} else {
				enable = true;
			}
			if (iRealismMode == 0 || enable) {
				if (CharacterIsDead(chRef)) {
					BI_intNRetValue[0] = 0;
					BI_intNRetValue[1] = 1;
					BI_intNRetValue[2] = 7;
					BI_intNRetValue[3] = true;
					break;
				}
			}
// KK -->
			BI_intNRetValue[0] = 9;
			BI_intNRetValue[1] = 13;
			BI_intNRetValue[2] = 2;
			st = GetCharacterShipType(chRef);
			if (st >= 0 && st < SHIP_TYPES_QUANTITY) {
				if (iRealismMode == 0 || enable) {
					if (CheckAttribute(&ShipsTypes[st], "BI.Pic") && CheckAttribute(&ShipsTypes[st], "BI.Tex")) {
						BI_intNRetValue[0] = sti(ShipsTypes[st].BI.Pic);
						//Boyer change
                        if(CheckAttribute(ShipsTypes[st], "BI.selPic"))
                            BI_intNRetValue[1] = sti(ShipsTypes[st].BI.selPic);
                        else
                            BI_intNRetValue[1] = sti(ShipsTypes[st].BI.Pic) + 1;
						BI_intNRetValue[2] = sti(ShipsTypes[st].BI.Tex);
					} else {
						BI_intNRetValue[0] = 0;
						BI_intNRetValue[1] = 1;
						BI_intNRetValue[2] = 16; //11;
					}
				}
// <-- KK
				BI_intNRetValue[3] = false;
			}
		break;

		case BIDT_GERALD_DATA:
			enable = distance < GetCharVisibilityRange(GetMainCharacter(), 2); // Ship nation is visible inside MEDIUM range
			if (enable == true && CheckAttribute(chRef, "nation.known") == true && sti(chRef.nation.known) == -2) chRef.nation.known = sti(chRef.nation);
			BI_intNRetValue[0] = 8;
			if (Ship_GetGroupID(chRef) == PLAYER_GROUP) {
				BI_intNRetValue[1] = 10;
				st = sti(chRef.nation);
			} else {
				if (iRealismMode == 0) {
					st = sti(chRef.nation);
					switch (SeaAI_GetRelation(chrIdx, GetMainCharacterIndex()))
					{
						case RELATION_FRIEND:  BI_intNRetValue[1] = 11; break;		//changed by KAM
						case RELATION_NEUTRAL: BI_intNRetValue[1] = 11; break;		//changed by KAM
						case RELATION_ENEMY:   BI_intNRetValue[1] = 9;  break;		//changed by KAM
					}
				} else {
					BI_intNRetValue[1] = -1;
					st = sti(chRef.nation.known);
					if (CheckAttribute(chRef, "nation.known") == true && st != -1) {
						switch (GetNationRelation(sti(Characters[GetMainCharacterIndex()].nation), st))
						{
							case RELATION_FRIEND:  BI_intNRetValue[1] = 11; break;		//changed by KAM
							case RELATION_NEUTRAL: BI_intNRetValue[1] = 11; break;		//changed by KAM
							case RELATION_ENEMY:   BI_intNRetValue[1] = 9;  break;		//changed by KAM
						}
					}
				}
			}
			BI_intNRetValue[2] = 8;
			switch (st)
			{
				case ENGLAND:         BI_intNRetValue[3] = 3;  break;
				case FRANCE:          BI_intNRetValue[3] = 2;  break;
				case SPAIN:           BI_intNRetValue[3] = 0;  break;
				case PIRATE:          BI_intNRetValue[3] = 5;  break;
				case HOLLAND:         BI_intNRetValue[3] = 4;  break;
				case PORTUGAL:        BI_intNRetValue[3] = 1;  break;
				case GUEST1_NATION:   BI_intNRetValue[3] = 6;  break;		// KK
				case GUEST2_NATION:   BI_intNRetValue[3] = 7;  break;		// KK
				case NEUTRAL_NATION:  BI_intNRetValue[3] = 8;  break;		//added by KAM
				case UNKNOWN_NATION:  BI_intNRetValue[3] = 8;  break;		//added by KAM
				case PERSONAL_NATION: BI_intNRetValue[3] = 12; break;		// KK
				// default:
				                      BI_intNRetValue[3] = -1; break;
			}
		break;
	}
	return &BI_intNRetValue;
}

void SetParameterData()
{
    int fTmp, fTmp2;
	int idLngFile = LanguageOpenFile("commands_name.txt"); // KK
	ref PChar = GetMainCharacter(); // PB
	string compasstype = CheckCharacterEquipByGroup(PChar, COMPASS_ITEM_TYPE); // KK
	if (iRealismMode == 0 && !NAVIGATION_EQUIPMENT) compasstype = "compass3"; // Erwin Lindemann

	BattleInterface.CommandTextures.list.t0.name = "battle_interface\cicons_charge.tga.tx";
	BattleInterface.CommandTextures.list.t0.xsize = 2;
	BattleInterface.CommandTextures.list.t0.ysize = 4;

	BattleInterface.CommandTextures.list.t1.name = "battle_interface\cicons_command.tga.tx";
	BattleInterface.CommandTextures.list.t1.xsize = 8;
	BattleInterface.CommandTextures.list.t1.ysize = 8; // FCoHS

// KK -->
	BattleInterface.CommandTextures.list.t2.name = "battle_interface\LandTarget1.tga.tx";
	BattleInterface.CommandTextures.list.t2.xsize = 8;
	BattleInterface.CommandTextures.list.t2.ysize = 2;

	BattleInterface.CommandTextures.list.t3.name = "battle_interface\LandTarget4.tga.tx";
	BattleInterface.CommandTextures.list.t3.xsize = 16;
	BattleInterface.CommandTextures.list.t3.ysize = 4;

	BattleInterface.CommandTextures.list.t4.name = "battle_interface\Cancel.tga.tx";
	BattleInterface.CommandTextures.list.t4.xsize = 2;
	BattleInterface.CommandTextures.list.t4.ysize = 1;
// <-- KK

	BattleInterface.CommandTextures.list.t5.name = "battle_interface\SailControls.tga.tx";
	BattleInterface.CommandTextures.list.t5.xsize = 8;
	BattleInterface.CommandTextures.list.t5.ysize = 1;

	BattleInterface.CommandTextures.list.t6.name = "battle_interface\sea_abilitys.tga.tx";
	BattleInterface.CommandTextures.list.t6.xsize = 8;
	BattleInterface.CommandTextures.list.t6.ysize = 2;

	BattleInterface.CommandTextures.list.t7.name = "battle_interface\scull.tga.tx";
	BattleInterface.CommandTextures.list.t7.xsize = 2;
	BattleInterface.CommandTextures.list.t7.ysize = 1;

	BattleInterface.CommandTextures.list.t8.name = "battle_interface\small_nations"+GetCurrentPeriod()+".tga.tx"; // PB
	BattleInterface.CommandTextures.list.t8.xsize = 16; //32;					//changed by KAM
	BattleInterface.CommandTextures.list.t8.ysize = 1;

	BattleInterface.CommandTextures.list.t9.name = "battle_interface\Artefact.tga.tx";
	BattleInterface.CommandTextures.list.t9.xsize = 2;
	BattleInterface.CommandTextures.list.t9.ysize = 1;

// KK -->
	BattleInterface.CommandTextures.list.t10.name = "battle_interface\ships_16.tga.tx";
	BattleInterface.CommandTextures.list.t10.xsize = 8;
	BattleInterface.CommandTextures.list.t10.ysize = 4;

	BattleInterface.CommandTextures.list.t11.name = "battle_interface\ships_1.tga.tx";
	BattleInterface.CommandTextures.list.t11.xsize = 2;
	BattleInterface.CommandTextures.list.t11.ysize = 1;

	BattleInterface.CommandTextures.list.t12.name = "battle_interface\ships_2.tga.tx";
	BattleInterface.CommandTextures.list.t12.xsize = 2;
	BattleInterface.CommandTextures.list.t12.ysize = 2;

	BattleInterface.CommandTextures.list.t13.name = "battle_interface\08shs_02.tga.tx";	//Mod Ship by Duke Surak'nar 17/08/2003
	BattleInterface.CommandTextures.list.t13.xsize = 2;
	BattleInterface.CommandTextures.list.t13.ysize = 1;

	BattleInterface.CommandTextures.list.t14.name = "battle_interface\ships_32.tga.tx";
	BattleInterface.CommandTextures.list.t14.xsize = 8;
	BattleInterface.CommandTextures.list.t14.ysize = 4;

	BattleInterface.CommandTextures.list.t15.name = "battle_interface\ships_48.tga.tx";
	BattleInterface.CommandTextures.list.t15.xsize = 8;
	BattleInterface.CommandTextures.list.t15.ysize = 4;
// <-- KK
    BattleInterface.CommandTextures.list.t16.name = "battle_interface\ships_all.tga.tx";
	BattleInterface.CommandTextures.list.t16.xsize = 16;
	BattleInterface.CommandTextures.list.t16.ysize = 16;

	BattleInterface.CommandTextures.ChargeTexNum = 0;
	BattleInterface.CommandTextures.CommandTexNum = 1;

	//Boyer add
	BattleInterface.charge.charge1.picNum = 0; // balls
	BattleInterface.charge.charge1.selPicNum = 1;
	BattleInterface.charge.charge2.picNum = 2; // grapes
	BattleInterface.charge.charge2.selPicNum = 3;
	BattleInterface.charge.charge3.picNum = 4; // "Knippels"
	BattleInterface.charge.charge3.selPicNum = 5;
	BattleInterface.charge.charge4.picNum = 6; // bombs
	BattleInterface.charge.charge4.selPicNum = 7;

	BattleInterface.CommandShowParam.maxShowQuantity = 10;
	BattleInterface.CommandShowParam.iconDistance = 4;
	BattleInterface.CommandShowParam.iconWidth = RecalculateHIcon(64);
	BattleInterface.CommandShowParam.iconHeight = RecalculateVIcon(64);
	BattleInterface.CommandShowParam.leftIconsOffset = sti(showWindow.left)+RecalculateHIcon(30);
	BattleInterface.CommandShowParam.downIconsOffset = sti(showWindow.bottom)-RecalculateVIcon(80);
	BattleInterface.CommandShowParam.buttonWidth = RecalculateHIcon(8);
	BattleInterface.CommandShowParam.buttonHeight = RecalculateVIcon(64);
	BattleInterface.CommandShowParam.buttonOffset = RecalculateHIcon(4);
	BattleInterface.CommandShowParam.buttonTexture = "battle_interface\lr_buttons.tga.tx";
	BattleInterface.CommandShowParam.shipStateWidth = RecalculateHIcon(64);
	BattleInterface.CommandShowParam.shipStateHeight = RecalculateVIcon(16);
	BattleInterface.CommandShowParam.shipStateTexture = "battle_interface\indicators.tga.tx";
	BattleInterface.CommandShowParam.shipStateOffset = RecalculateVIcon(0);
	BattleInterface.CommandShowParam.GeraldWidth = RecalculateHIcon(32);
	BattleInterface.CommandShowParam.GeraldHeight = RecalculateVIcon(32);
	BattleInterface.CommandShowParam.commandFont = "bold_numbers";
	BattleInterface.CommandShowParam.printXOffset = RecalculateHIcon(32);
	BattleInterface.CommandShowParam.printYOffset = RecalculateVIcon(-26);
	BattleInterface.CommandShowParam.commandNoteFont = "interface_normal";
	BattleInterface.CommandShowParam.noteXOffset = RecalculateHIcon(0);
	BattleInterface.CommandShowParam.noteYOffset = RecalculateVIcon(-28);
	BattleInterface.CommandShowParam.argbTFactorColor = argb(256,64,64,64);

// KK -->
	BattleInterface.UserIcons.ui1.enable = true;
	BattleInterface.UserIcons.ui1.pic = 0;
	BattleInterface.UserIcons.ui1.selpic = 4;
	BattleInterface.UserIcons.ui1.tex = BI_ICONS_TEXTURE_SAILS;
	BattleInterface.UserIcons.ui1.name = "sail_none";
	BattleInterface.UserIcons.ui1.note = LanguageConvertString(idLngFile, "sea_LowerSails");
	//----------------------------------------------
	BattleInterface.UserIcons.ui2.enable = true;
	BattleInterface.UserIcons.ui2.pic = 1;
	BattleInterface.UserIcons.ui2.selpic = 5;
	BattleInterface.UserIcons.ui2.tex = BI_ICONS_TEXTURE_SAILS;
	BattleInterface.UserIcons.ui2.name = "sail_midi";
	BattleInterface.UserIcons.ui2.note = LanguageConvertString(idLngFile, "sea_BattleSails");
	//----------------------------------------------
	BattleInterface.UserIcons.ui3.enable = true;
	BattleInterface.UserIcons.ui3.pic = 2;
	BattleInterface.UserIcons.ui3.selpic = 6;
	BattleInterface.UserIcons.ui3.tex = BI_ICONS_TEXTURE_SAILS;
	BattleInterface.UserIcons.ui3.name = "sail_fast";
	BattleInterface.UserIcons.ui3.note = LanguageConvertString(idLngFile, "sea_FullSails");
	//----------------------------------------------
	BattleInterface.UserIcons.ui4.enable = true;
	BattleInterface.UserIcons.ui4.pic = 5;
	BattleInterface.UserIcons.ui4.selpic = 9;
	BattleInterface.UserIcons.ui4.tex = BI_ICONS_TEXTURE_LANDTARG1;
	BattleInterface.UserIcons.ui4.name = -1;
	BattleInterface.UserIcons.ui4.note = "";
	//----------------------------------------------
	BattleInterface.UserIcons.ui5.enable = true;
	BattleInterface.UserIcons.ui5.pic = 9;
	BattleInterface.UserIcons.ui5.selpic = 13;
	BattleInterface.UserIcons.ui5.tex = BI_ICONS_TEXTURE_LANDTARG1;
	BattleInterface.UserIcons.ui5.name = -1;
	BattleInterface.UserIcons.ui5.note = "";
	//----------------------------------------------
	BattleInterface.UserIcons.ui6.enable = true;
	BattleInterface.UserIcons.ui6.pic = 9;
	BattleInterface.UserIcons.ui6.selpic = 13;
	BattleInterface.UserIcons.ui6.tex = BI_ICONS_TEXTURE_LANDTARG1;
	BattleInterface.UserIcons.ui6.name = -1;
	BattleInterface.UserIcons.ui6.note = "";
	//----------------------------------------------
	BattleInterface.UserIcons.ui7.enable = true;
	BattleInterface.UserIcons.ui7.pic = 9;
	BattleInterface.UserIcons.ui7.selpic = 13;
	BattleInterface.UserIcons.ui7.tex = BI_ICONS_TEXTURE_LANDTARG1;
	BattleInterface.UserIcons.ui7.name = -1;
	BattleInterface.UserIcons.ui7.note = "";
// <-- KK

	//===============================================
	BattleInterface.navigation.aspectRatio				= showWindow.aspectRatio;
	if (bRealBattleInterface) {
		BattleInterface.navigation.navigatorWidth		= RecalculateHIcon(95); // BB 192
		BattleInterface.navigation.navigatorHeight		= RecalculateVIcon(95); // BB 192
		BattleInterface.navigation.rightPos				= sti(showWindow.left)+RecalculateHIcon(105); // BB showWindow.right
		BattleInterface.navigation.topPos				= sti(showWindow.bottom)-RecalculateVIcon(190); // ccc showWindow.top
		BattleInterface.navigation.speedOutYOffset		= sti(showWindow.bottom)-RecalculateVIcon(80); // ccc -88
		BattleInterface.navigation.shipSpeedXOffset		= RecalculateHIcon(37); // ccc 80
		BattleInterface.navigation.windSpeedXOffset		= RecalculateHIcon(-35); // ccc -80
		BattleInterface.navigation.fontScale			= 0.35; // ccc 0.75
		BattleInterface.navigation.windWidth			= 15; // ccc 30
		BattleInterface.navigation.windHeight			= 50; // ccc 120
	} else {
		BattleInterface.navigation.navigatorWidth		= RecalculateHIcon(192);
		BattleInterface.navigation.navigatorHeight		= RecalculateVIcon(192);
		BattleInterface.navigation.rightPos				= sti(showWindow.right) - RecalculateHIcon(25);
		BattleInterface.navigation.topPos				= sti(showWindow.top) + RecalculateVIcon(18);
		BattleInterface.navigation.speedOutYOffset		= RecalculateVIcon(-88);
		BattleInterface.navigation.shipSpeedXOffset		= RecalculateHIcon(85);
		BattleInterface.navigation.windSpeedXOffset		= RecalculateHIcon(-110);
		BattleInterface.navigation.fontScale			= 0.75;
		BattleInterface.navigation.windWidth			= 30;
		BattleInterface.navigation.windHeight			= 120;
	}

// KK -->
	if (GetCaracterShipCannonsType(PChar) != CANNON_TYPE_NONECANNON)
		BattleInterface.navigation.cannonsTexture     = "battle_interface\indicators_cannons_reload.tga.tx";
	else
		BattleInterface.navigation.cannonsTexture     = "empty.tga.tx";
	if (compasstype == "") {
		BattleInterface.navigation.compasTexture      = "empty.tga.tx";
		BattleInterface.navigation.speedTexture       = "empty.tga.tx";
		BattleInterface.navigation.emptyTexture       = "battle_interface\indicators_dark_and_center_ship_nowind.tga.tx";
		BattleInterface.navigation.windTexture        = "empty.tga.tx";
		BattleInterface.navigation.mapRadius          = 0.0;
		BattleInterface.navigation.shipShowRadius     = 0.0;
	} else {
// PB: Recode to switch -->
		switch(ONSEA_COMPASS)
		{
			case 0: BattleInterface.navigation.compasTexture = "battle_interface\compass.tga.tx"; break; // Stock default
			case 1: BattleInterface.navigation.compasTexture = "battle_interface\compass1.tga.tx"; break; // Catalina The Pirate version
			case 2: BattleInterface.navigation.compasTexture = "battle_interface\compass2.tga.tx"; break; // Age of Pirates version
		}
// PB: Recode to switch <--
		if (compasstype == "compass1") {
			BattleInterface.navigation.speedTexture         = "empty.tga.tx";
			BattleInterface.navigation.emptyTexture         = "battle_interface\indicators_dark_and_center_ship_nowind.tga.tx";
			BattleInterface.navigation.shipShowRadius       = 0.0;
		} else {
			BattleInterface.navigation.speedTexture         = "battle_interface\indicators_wind_and_ship.tga.tx";
			BattleInterface.navigation.emptyTexture         = "battle_interface\indicators_dark_and_center_ship.tga.tx";
			BattleInterface.navigation.shipShowRadius       = 8.0;
		}
		BattleInterface.navigation.speedShowFont            = "bold_numbers";
		BattleInterface.navigation.windTexture              = "battle_interface\wind_pointer.tga.tx";

		if (bRealBattleInterface) {
			BattleInterface.navigation.mapRadius            = 5; // ccc 54
		} else {
			BattleInterface.navigation.mapRadius            = 54;
		}
		if(iRealismMode>1 || ONSEA_DATA_DISABLED)
		{
			BattleInterface.navigation.mapRadius			= 0.0;
			BattleInterface.navigation.shipShowRadius		= 0.0;
		}
	}
	BattleInterface.navigation.leftChargeBegAngle		= 215;
	BattleInterface.navigation.leftChargeEndAngle		= 325;
	BattleInterface.navigation.rightChargeBegAngle		= 145;
	BattleInterface.navigation.rightChargeEndAngle		= 35;
	BattleInterface.navigation.forwardChargeBegAngle	= 335;
	BattleInterface.navigation.forwardChargeEndAngle	= 385;
	BattleInterface.navigation.backwardChargeBegAngle	= 205;
	BattleInterface.navigation.backwardChargeEndAngle	= 155;
	BattleInterface.navigation.shipSpeedBegAngle		= 175;
	BattleInterface.navigation.shipSpeedEndAngle		= 55;
	BattleInterface.navigation.windSpeedBegAngle		= 180;
	BattleInterface.navigation.windSpeedEndAngle		= 410;

	BattleInterface.navigation.horizontRadius			= 400;
	BattleInterface.navigation.minScale					= 0.5;
	BattleInterface.navigation.maxScale					= 4;
	BattleInterface.navigation.scaleStep				= 0.05;		// LDH 19Jan09 was 0.1, slows down the zoom speed
	BattleInterface.navigation.argbReadyCannonColor		= argb(255,0,155,0);
	BattleInterface.navigation.argbChargeCannonColor	= argb(255,255,0,0);
	BattleInterface.navigation.argbSeaColor				= argb(255,10,30,80);
	BattleInterface.navigation.argbFireZoneColor		= argb(60,250,250,250);
	if (compasstype != "compass3") {
		BattleInterface.navigation.argbEnemyShipColor		= argb(255,128,128,128);
		BattleInterface.navigation.argbFrendShipColor		= argb(255,128,128,128);
	} else {
		BattleInterface.navigation.argbEnemyShipColor		= argb(255,255,0,0);
		BattleInterface.navigation.argbFrendShipColor		= argb(255,0,255,0);
	}
	BattleInterface.navigation.argbNeutralShipColor		= argb(255,128,128,128);
	BattleInterface.navigation.argbDeadShipColor		= argb(255,0,0,255);
	BattleInterface.navigation.argbBackMaxColor			= argb(0,0,0,128); // KK was: argb(255,0,0,128);
	BattleInterface.navigation.argbBackMinColor			= argb(0,0,0,128);
	if (GetCaracterShipCannonsType(PChar) != CANNON_TYPE_NONECANNON) {
		if (CANNONPOWDER_MOD) {// TIH --> mod toggle 7-7-06
			// changed by MAXIMUS [gunpowder mod] -->
			BattleInterface.navigation.chargeTexture			= "battle_interface\small_cannons_gunpowder.tga.tx";
			BattleInterface.navigation.chargeTextureGreed		= "1,8";
			// changed by MAXIMUS [gunpowder mod] <--
		} else {
			BattleInterface.navigation.chargeTexture			= "battle_interface\small_cannons.tga.tx";
			BattleInterface.navigation.chargeTextureGreed		= "1,4";
		}// TIH <-- mod toggle
	} else {
		BattleInterface.navigation.chargeTexture			= "empty.tga.tx";
	}
	if(bRealBattleInterface)
	{
		BattleInterface.navigation.chargePos			= RecalculateHIcon(20)+","+RecalculateVIcon(125); //ccc 160 & 174
		BattleInterface.navigation.chargePictureSize	= "30,30"; //ccc "32,32"
	}
	else
	{
		BattleInterface.navigation.chargePos			= RecalculateHIcon(52)+","+RecalculateVIcon(74);
		//BattleInterface.navigation.chargePos			= RecalculateHIcon(160)+","+RecalculateVIcon(174);
		BattleInterface.navigation.chargePictureSize	= "32,32";
	}

	//===============================================
	BattleInterface.MessageIcons.IconWidth = RecalculateHIcon(64);
	BattleInterface.MessageIcons.IconHeight = RecalculateVIcon(24);
	BattleInterface.MessageIcons.IconDist = RecalculateVIcon(2);
	if (bRealBattleInterface)
		BattleInterface.MessageIcons.IconBottom = sti(BattleInterface.navigation.topPos)-RecalculateVIcon(20);
	else
		BattleInterface.MessageIcons.IconBottom = sti(showWindow.bottom)-RecalculateVIcon(80+20);
	BattleInterface.MessageIcons.IconMaxQuantity = 4;
	BattleInterface.MessageIcons.BlendTime = 3.0;
	BattleInterface.MessageIcons.FallSpeed = 22.0;
	BattleInterface.MessageIcons.argbHighBlind = argb(255,128,128,128);
	BattleInterface.MessageIcons.argbLowBlind = argb(255,68,68,68);
	BattleInterface.MessageIcons.BlindUpTime = 0.5;
	BattleInterface.MessageIcons.BlindDownTime = 1.0;
	BattleInterface.MessageIcons.texture = "battle_interface\MessageIcons.tga.tx";
	BattleInterface.MessageIcons.TexHSize = 2;
	BattleInterface.MessageIcons.TexVSize = 2;

	//Boyer add
	BattleInterface.battleborder.used = false;
	BattleInterface.battleborder.color1 = argb(255,255,255,255);
	BattleInterface.battleborder.color2 = argb(155,255,255,255);
	BattleInterface.battleborder.extpos = "0,0," + ShowWindow.right + "," + ShowWindow.bottom;
	BattleInterface.battleborder.intpos1 =
		RecalculateHIcon(20) + "," +
		RecalculateVIcon(20) + "," +
		(sti(ShowWindow.right)-RecalculateHIcon(20)) + "," +
		(sti(ShowWindow.bottom)-RecalculateVIcon(20));
	BattleInterface.battleborder.intpos2 =
		RecalculateHIcon(10) + "," +
		RecalculateVIcon(10) + "," +
		(sti(ShowWindow.right)-RecalculateHIcon(10)) + "," +
		(sti(ShowWindow.bottom)-RecalculateVIcon(10));
	BattleInterface.battleborder.speed = 1.5;
	BattleInterface.battleborder.texture = "battle_interface\battleborder.tga.tx";

	BattleInterface.ShipIcon.sailorfontid			= "interface_normal";
	BattleInterface.ShipIcon.sailorfontcolor		= argb(255,255,255,255);
	BattleInterface.ShipIcon.sailorfontscale		= 0; // was 1.1 removed to mach original NH / Mirsaneli

	BattleInterface.ShipIcon.shipnamefontid			= "interface_normal";
	BattleInterface.ShipIcon.shipnamefontcolor		= argb(255,255,255,255);
	BattleInterface.ShipIcon.shipnamefontscale		= 0; //was 1.1 removed to mach original NH / Mirsaneli

	BattleInterface.ShipIcon.backtexturename		= "battle_interface\empty.tga.tx"; //was ShipBackIcon.tga.tx
	BattleInterface.ShipIcon.backcolor				= argb(255,128,128,128);
	BattleInterface.ShipIcon.backuv					= "0.0,0.0,1.0,1.0";
	BattleInterface.ShipIcon.backoffset				= "0.0,0.0";
	BattleInterface.ShipIcon.backiconsize			= "128,128";

	BattleInterface.ShipIcon.shipstatetexturename	= "battle_interface\ShipState.tga.tx";
	BattleInterface.ShipIcon.shipstatecolor			= argb(255,128,128,128);
	BattleInterface.ShipIcon.shiphpuv				= "0.0,0.109,0.5,0.6875";
	BattleInterface.ShipIcon.shiphpoffset			= "-33,-15";
	BattleInterface.ShipIcon.shiphpiconsize			= "64,70";
	BattleInterface.ShipIcon.shipspuv				= "0.5,0.109,1.0,0.6875";

	BattleInterface.ShipIcon.shipspoffset			= "33,-15";
	BattleInterface.ShipIcon.shipspiconsize			= "64,70";

	BattleInterface.ShipIcon.shipclasstexturename	= "battle_interface\empty.tga.tx"; //was Shipclass.tga.tx changed to fool it, beacuse it doesn't exist in original Mod / Mirsaneli
	BattleInterface.ShipIcon.shipclasscolor			= argb(255,128,128,128);
	BattleInterface.ShipIcon.shipclassuv			= "0.0,0.0,1.0,1.0";
	BattleInterface.ShipIcon.shipclassoffset		= "-14,-50";
	BattleInterface.ShipIcon.shipclassiconsize		= "64,16";
	BattleInterface.ShipIcon.gunchargeprogress		= "0.0625, 0.219, 0.359, 0.5, 0.641, 0.781, 0.983";

	BattleInterface.ShipIcon.shiptexturename		= "battle_interface\ships_all.tga.tx"; //"battle_interface\ship_icons2.tga.tx";
	BattleInterface.ShipIcon.shipcolor				= argb(255,128,128,128);
	//BattleInterface.ShipIcon.shipoffset				= "-14,-10";
	BattleInterface.ShipIcon.shipiconsize			= "64,64";
	//Boyer add
	BattleInterface.ShipIcon.xsize = 16;
    BattleInterface.ShipIcon.ysize = 16;

	//BattleInterface.ShipIcon.commandlistverticaloffset = -40;

	//BattleInterface.ShipIcon.iconoffset1 = "70,70";
	//BattleInterface.ShipIcon.iconoffset2 = "70,198";
	//BattleInterface.ShipIcon.iconoffset3 = "70,326";
	//BattleInterface.ShipIcon.iconoffset4 = "70,454";
	//BattleInterface.ShipIcon.iconoffset5 = "70,582";
	//int nPlace = sti(showWindow.right) - RecalculateHIcon(64);
	//BattleInterface.ShipIcon.iconoffset1 = nPlace + ",300";
    //BattleInterface.ShipIcon.iconoffset2 = nPlace + ",428";
    //BattleInterface.ShipIcon.iconoffset3 = nPlace + ",556";
    //BattleInterface.ShipIcon.iconoffset4 = nPlace + ",684";
    //BattleInterface.ShipIcon.iconoffset5 = nPlace + ",712";

    fTmp = RecalculateHIcon(-14);
    fTmp2 =  RecalculateVIcon(-12);
    BattleInterface.ShipIcon.shipoffset = fTmp + "," + fTmp2;
    fTmp = RecalculateHIcon(-43);
    BattleInterface.ShipIcon.commandlistverticaloffset = fTmp;
    fTmp = RecalculateHIcon(70);
    int nCmpNum = GetCompanionQuantity(pchar);
    int i;
    string sOff = "iconoffset";
    int fTmp3 = RecalculateVIcon(70);
    if(bRealBattleInterface) {
        fTmp2 = sti(showWindow.bottom) -  RecalculateVIcon(59);
        if(nCmpNum == 1) {
            BattleInterface.ShipIcon.iconoffset1 = fTmp + "," + fTmp2;
        }
        else {
            for(i = nCmpNum; i > 0; i--) {
                sOff = "iconoffset" + i;
                BattleInterface.ShipIcon.(sOff) = fTmp + "," + fTmp2;
                fTmp2 -= fTmp3;
            }
        }
        //BattleInterface.ShipIcon.iconoffset1 = "70,840";
        //BattleInterface.ShipIcon.iconoffset2 = "180,835";
        //BattleInterface.ShipIcon.iconoffset3 = "290,835";
        //BattleInterface.ShipIcon.iconoffset4 = "400,835";
        //BattleInterface.ShipIcon.iconoffset5 = "510,835";
    }
    else {
        if(nCmpNum == 1) {
            fTmp2 = sti(showWindow.bottom) -  RecalculateVIcon(55);
            BattleInterface.ShipIcon.iconoffset1 = fTmp + "," + fTmp2;
        }
        else {
            fTmp2 = sti(showWindow.bottom) -  RecalculateVIcon(30);
            for(i = nCmpNum; i > 0; i--) {
                sOff = "iconoffset" + i;
                BattleInterface.ShipIcon.(sOff) = fTmp + "," + fTmp2;
                fTmp2 -= fTmp3;
            }
        }
        //BattleInterface.ShipIcon.iconoffset1 = "70,840";
        //BattleInterface.ShipIcon.iconoffset2 = "180,835";
        //BattleInterface.ShipIcon.iconoffset3 = "290,835";
        //BattleInterface.ShipIcon.iconoffset4 = "400,835";
        //BattleInterface.ShipIcon.iconoffset5 = "510,835";
    }

	BattleInterface.CommandList.CommandMaxIconQuantity = 10; //boal
	BattleInterface.CommandList.CommandIconSpace = 1;
	BattleInterface.CommandList.CommandIconLeft = 108;//157;
	//BattleInterface.CommandList.CommandIconLeft = sti(showWindow.right) - (11 * RecalculateHIcon(64));
	BattleInterface.CommandList.CommandIconWidth = RecalculateHIcon(64);
	BattleInterface.CommandList.CommandIconHeight = RecalculateVIcon(64);

	BattleInterface.CommandList.CommandNoteFont = "interface_normal";
	BattleInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
	BattleInterface.CommandList.CommandNoteScale = 1.0;
	BattleInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(-54);

	BattleInterface.CommandList.UDArrow_Texture = "battle_interface\arrowly.tga.tx";
	BattleInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
	BattleInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
	BattleInterface.CommandList.UDArrow_Size = RecalculateHIcon(32) + "," + RecalculateVIcon(32);
	BattleInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(-41) + "," + RecalculateVIcon(-30);
	BattleInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(-41) + "," + RecalculateVIcon(46);

	LanguageCloseFile(idLngFile);
// <-- KK
}

ref ProcessSailDamage()
{
	// ???? ???????? ????????
	int shootIdx = GetEventData();
	// ????????
	int chrIdx = GetEventData();
	string sMastName = GetEventData();
	// ???????????????????? ????????????
	string reyName = GetEventData();
	int groupNum = GetEventData();
	// ???????????? ?? ????????????
	int holeCount = GetEventData();
	int holeData = GetEventData();
	int maxHoleCount = GetEventData();
	// ???????????????? ????????????
	float sailPower = GetEventData();

// KK -->
	if (shootIdx == chrIdx) {
		BI_g_fRetVal = 0.0;
		return &BI_g_fRetVal;
	}
// <-- KK

	ref chref = GetCharacter(chrIdx);
	string groupName = ""+groupNum;
	aref arSail;
	makearef(arSail,chref.ship.sails.(reyName).(groupName));

	float sailDmg = 0.0;
	float sailDmgMax = GetCharacterShipSP(chref) * sailPower;
	if( !CheckAttribute(arSail,"dmg") )	{ sailDmg = 0.0; }

	if(sMastName=="*")
	{
		sailDmg += GetRigDamage(shootIdx,sti(AIBalls.CurrentBallType),chref);
		if(sailDmg>sailDmgMax)	{ sailDmg = sailDmgMax; }
		int needHole = GetNeedHoleFromDmg(sailDmg,sailDmgMax,maxHoleCount);
		if(holeCount!=needHole)
		{
			if(holeCount<needHole)
			{
				holeData = RandomHole2Sail(chrIdx,reyName,groupNum, maxHoleCount, holeData, needHole-holeCount);
				holeCount = needHole;
			}
			else
			{
				sailDmg = GetNeedDmgFromHole(holeCount,sailDmgMax,maxHoleCount);
			}
		}
	}
	else
	{
		if(sMastName!="#")	{ arSail.mastFall = sMastName; }
		sailDmg = sailDmgMax;
	}

	arSail.hc = holeCount;
	arSail.hd = holeData;
	arSail.mhc = maxHoleCount;
	arSail.sp = sailPower;
	arSail.dmg = sailDmg;

	chref.ship.SP = CalculateShipSP(chref);
	BI_g_fRetVal = sailDmg;
	return &BI_g_fRetVal;
}

void ProcessDayRepair()
{
	//trace("Gauging: NEXTDAY_start PDR");
	int i, cn;
	float matQ, tmpf, repPercent;
	ref chref;
	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(GetMainCharacter(),i);
		if(cn==-1) continue;
		chref = GetCharacter(cn);
		RepairAllCannons(&chref); // NK can qty. For now repair all fixable guns. Later go back and set repair rates. 05-04-19

		// ???????????? ?????????????? ??????????????
		if( GetHullPercent(chref)<100.0 )
		{
			repPercent = GetHullRPD(chref);
			matQ = repPercent*GetHullPPP(chref);
			tmpf = GetRepairGoods(true,chref);
			if(tmpf<matQ)	{ repPercent = tmpf/GetHullPPP(chref); }
			repPercent = ProcessHullRepair(chref,repPercent);
			matQ = repPercent*GetHullPPP(chref);
			RemoveRepairGoods(true,chref,matQ);
		}

		// ???????????? ?????????????? ??????????????
		if( GetSailPercent(chref)<100.0 )
		{
			repPercent = GetSailRPD(chref);
			matQ = repPercent*GetSailSPP(chref);
			tmpf = GetRepairGoods(false,chref);
			if(tmpf<matQ)	{ repPercent = tmpf/GetSailSPP(chref); }
			repPercent = ProcessSailRepair(chref,repPercent);
			matQ = repPercent*GetSailSPP(chref);
			RemoveRepairGoods(false,chref,matQ);
		}
	}
	//trace("Gauging: NEXTDAY_end PDR");
}

void procBISelectShip()
{
	int chrIdx = GetEventData();
	int isMyChr = GetEventData();

	if(chrIdx==GetMainCharacterIndex())	chrIdx = -1;

	float fShSpeed = 0.005;
	float fShAmp = 1.0;
	float fShW = 1.0;
	float fShH = 1.0;
	float fTop = 10.0;

	SendMessage(&objShipPointer,"lllfffff",MSG_SP_CHANGESHIP,chrIdx,isMyChr,fShSpeed,fShAmp,fShW,fShH,fTop);
}

ref procGetSmallFlagData()
{
	int chrIdx = GetEventData();
	int nMainCharacterIndex = GetMainCharacterIndex();
	BI_intNRetValue[0] = BI_ICONS_TEXTURE_NATIONS;
	BI_intNRetValue[1] = 8;
	if( chrIdx >= 0 ) {
		int iNation = sti(Characters[chrIdx].nation);
		switch( iNation )
		{
			case PORTUGAL: BI_intNRetValue[1] = 1; break;
            case SPAIN: BI_intNRetValue[1] = 0; break;
            case PIRATE: BI_intNRetValue[1] = 5; break;
            case ENGLAND: BI_intNRetValue[1] = 3; break;
            case HOLLAND: BI_intNRetValue[1] = 4; break;
            case FRANCE: BI_intNRetValue[1] = 2; break;
            case AMERICA: BI_intNRetValue[1] = 6; break;
            case NEUTRAL_NATION: BI_intNRetValue[1] = 8; break;	// added by KAM
            case UNKNOWN_NATION: BI_intNRetValue[1] = 8; break;	// added by KAM
            case PERSONAL_NATION: BI_intNRetValue[1] = 12; break; // KK
		}

		BI_intNRetValue[2] = 11;
		switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
		{
			case RELATION_FRIEND:	BI_intNRetValue[2] = 10; break;
			case RELATION_NEUTRAL:	BI_intNRetValue[2] = 11; break;
			case RELATION_ENEMY:	BI_intNRetValue[2] = 9; break;
		}
	}
	return &BI_intNRetValue;
}

void procMastFall()
{
	int chrIdx = GetEventData();
	string mastName = GetEventData();
	int bFirstFall = GetEventData();

	if(chrIdx<0) return;
	ref mchr = GetMainCharacter(); // KK
	Characters[chrIdx].fallen = 1; //screwface
	int mastNum = strcut(mastName,4,strlen(mastName)-1);
	trace("For character "+chrIdx+" fall Mast name "+mastName+" has index "+mastNum);
	if(!CheckAttribute(mchr, "Flags.waitdelay"))
	{
		mchr.Flags.waitdelay = 1000; //screwface : big value needed !!!!!
		FlagsDelay();
	}
	else
	{
		// A waitdelay is still running so we increase its time
		if(CheckAttribute(&BattleInterface, "Waitrefreshflags"))
			mchr.Flags.waitdelay = sti(BattleInterface.Waitrefreshflags) + 1000; // executed frames number + 1000 new frames
		else
			mchr.Flags.waitdelay = sti(mchr.Flags.waitdelay) + 1000;
	}
	SendMessage(&PeopleOnShip, "lal", MSG_PEOPLES_ON_SHIP_MASTFALL, GetCharacter(chrIdx), mastNum);
}

bool CheckInstantRepairCondition(ref chref)
{
	//int tmpLangFileID = LanguageOpenFile("interface_strings.txt");
//boal -->
	//if(!GetCharacterPerkUsing(chref,"InstantRepair")) return false;

//ccc realistic shipyard repair at anchorage only->
	// LDH 02Oct06
	if(!bMapEnter) return false;
//ccc repair <-

	/*bool	retRepair = GetCharacterPerkUsing(chref,"InstantRepair");
	if(!retRepair)
	{
		int cn;
		for(int i=1; i<4; i++)
		{
			cn = GetOfficersIndex(chref,i);
			if(cn!=-1)
			{
				if(GetCharacterPerkUsing(GetCharacter(cn),"InstantRepair"))
				{
					retRepair = true;
					break;
				}
			}
		}
	}*/ // ASVS commented that out, see below.
	if(!GetOfficersPerkUsing(chref,"InstantRepair")) //ASVS - come on, we have a function for that, why not using it?
		return false;
//boal <--

	if(GetHullPercent(chref) < 90.0 && GetCargoGoods(chref, GOOD_PLANKS) > 0) return true;
	return GetSailPercent(chref) < 90.0 && GetCargoGoods(chref, GOOD_SAILCLOTH) > 0;
}

void BI_PerkAgainUsable()
{
	BI_SetCommandMode(-1,-1,-1,-1);
}

float GetRepairGoods(bool bIsHull, ref chref)
{
	float fGoodsQ = 0.0;

	if( bIsHull )
	{
		fGoodsQ = GetCargoGoods(chref,GOOD_PLANKS);
		if( CheckAttribute(chref,"RepairMaterials.forHull") )
		{	fGoodsQ += stf(chref.RepairMaterials.forHull);
		}
	}
	else
	{
		fGoodsQ = GetCargoGoods(chref,GOOD_SAILCLOTH);
		if( CheckAttribute(chref,"RepairMaterials.forSails") )
		{	fGoodsQ += stf(chref.RepairMaterials.forSails);
		}
	}

	return fGoodsQ;
}

void RemoveRepairGoods(bool bIsHull, ref chref, float matQ)
{
	int nGoodsQ = 0;
	float fGoodsQ = GetRepairGoods(bIsHull,chref);

	if( bIsHull )
	{
		if(fGoodsQ<=matQ)	{ DeleteAttribute(chref,"RepairMaterials.forHull"); }
		else
		{
			fGoodsQ -= matQ;
			nGoodsQ = makeint(fGoodsQ);
			chref.RepairMaterials.forHull = fGoodsQ - nGoodsQ;
		}
		SetCharacterGoods(chref,GOOD_PLANKS,nGoodsQ);
	}
	else
	{
		if(fGoodsQ<=matQ)	{ DeleteAttribute(chref,"RepairMaterials.forSails"); }
		else
		{
			fGoodsQ -= matQ;
			nGoodsQ = makeint(fGoodsQ);
			chref.RepairMaterials.forSails = fGoodsQ - nGoodsQ;
		}
		SetCharacterGoods(chref,GOOD_SAILCLOTH,nGoodsQ);
	}

}

float GetRigDamage(int shootIdx, int iBallType, ref damage_chr)
{
	ref rBall = GetGoodByType(iBallType);
	float fDmgRig = stf(rBall.DamageRig);
	ref shoot_chr;
	if(shootIdx >=0 && shootIdx != GetMainCharacterIndex() && CheckAttribute(damage_chr,"surrendered")) return 0.0; // NK because AI doesn't respect surrender. 05-04-23
	if(USE_REAL_CANNONS)
	{
		if( shootIdx>=0 )
		{
			shoot_chr = GetCharacter(shootIdx);
			if( IsCharacterPerkOn(shoot_chr,"CannonProfessional") ) { fDmgRig *= 1.20; }
			else
			{
				if( IsCharacterPerkOn(shoot_chr,"SailsDamageUp") )  { fDmgRig *= 1.10; }
			}
		}

		if( IsCharacterPerkOn(damage_chr,"RiggingAdvance") ) { fDmgRig *= 0.75; }
		else
		{
			if( IsCharacterPerkOn(damage_chr,"Rigging") )  { fDmgRig *= 0.85; }
		}
// KK --> //KB - Tuning ships
//KB - Tuning ships - gchasers effect on sails
//KB if ( sti(shoot_chr.index) == 0 ) {Trace("KB - Chaser  before " + fDmgRig);}
		float chasercritchance = 0.0;
		ref tempref; makeref(tempref, AIBalls);
		if (CheckAttribute(tempref,"quad")) {
			if (tempref.quad == "cannonf" ) {  //KB It's a chaser
				if (CheckTun(shootIdx, "gchasers")) chasercritchance += makefloat(GCSAILCRIT/100);
				chasercritchance += makefloat(CSAILCRIT/100);
				if ( frnd() < chasercritchance ) {   //KB it's a critical
					Trace ("KB - Tuning - Critical sail by chasers ");
					fDmgRig *= makefloat(CSAILCRITDMG);
				}
			}
		}
//KB if ( sti(shoot_chr.index) == 0 ) {Trace("KB - Chaser  after " + fDmgRig);}
// KB Tuning ships - new sails will reduce the amount of damage received
		if (CheckTun(GetCharacterIndex(damage_chr.id), "nsails")) {
				//Trace("KB - Tuning ships Damage limited by nsails");
				fDmgRig *= makefloat(1-stf(damage_chr.ship.tune.nsails.sails)/100);
		}
//KB - END Tuning ships
	}
	else
	{
		if( shootIdx>=0 )
		{
			shoot_chr = GetCharacter(shootIdx);
			if( IsCharacterPerkOn(shoot_chr,"CannonProfessional") )	{ fDmgRig *= 1.3; }
			else
			{
				if( IsCharacterPerkOn(shoot_chr,"SailsDamageUp") )	{ fDmgRig *= 1.15; }
			}
		}

		if( IsCharacterPerkOn(damage_chr,"RiggingAdvance") ) { fDmgRig *= 0.6; }
		else
		{
			if( IsCharacterPerkOn(damage_chr,"Rigging") )  { fDmgRig *= 0.8; }
		}
	}
	return fDmgRig;
}

void MakeSailDmg(int chrIdx, float dmg)
{
	object objSail;
	if( !FindClass(&objSail,"sail") ) return;
	if(LAi_IsImmortal(&Characters[chrIdx])) return; // PB: Prevent sail damage
	SendMessage(&objSail,"lslf", MSG_SAIL_SCRIPT_PROCESSING,"RandomSailsDmg", chrIdx,dmg);
}

ref ProcessRandomSailDmg()
{
	BI_g_fRetVal = 0.0;
	//"lslfflll"
	int chrIdx = GetEventData();
	string nodeName = GetEventData();
	int grNum = GetEventData();
	float fDmg = GetEventData();
	float fSPow = GetEventData();
	int hc_new = GetEventData();
	int mhc = GetEventData();
	int hdat_new = GetEventData();

	if(chrIdx<0) return &BI_g_fRetVal;
	ref chref = GetCharacter(chrIdx);

	aref arSail;
	string groupName = ""+grNum;
	makearef(arSail,chref.ship.sails.(nodeName).(groupName));

	int hc_old = 0;
	if( CheckAttribute(arSail,"hc") )	hc_old = sti(arSail.hc);
	float fDmg_old = 0.0;
	if( CheckAttribute(arSail,"dmg") )	fDmg_old = stf(arSail.dmg);

	int itmp = hc_new;
	float sailDmgMax = GetCharacterShipSP(chref) * fSPow;

	float fTopDmg = sailDmgMax;
	if(itmp<mhc)	fTopDmg = GetNeedDmgFromHole(itmp+1,sailDmgMax,mhc) - 0.0001;
	if(fTopDmg>fDmg_old+fDmg)	fTopDmg = fDmg_old+fDmg;

	fDmg = fTopDmg-fDmg_old;
	if(fDmg<=0.0)	return &BI_g_fRetVal;
	chref.ship.SP = stf(chref.ship.SP)-fDmg;

	itmp = GetNeedHoleFromDmg(fTopDmg,sailDmgMax,mhc);
	if(itmp>hc_old)
	{
		BI_g_fRetVal = fDmg;
		arSail.hc = hc_new;
		arSail.hd = hdat_new;
	}
	else
	{
		BI_g_fRetVal = -fDmg;
		if( !CheckAttribute(arSail,"hc") )	arSail.hc = 0;
		if( !CheckAttribute(arSail,"hd") )	arSail.hd = 0;
	}

	arSail.mhc = mhc;
	arSail.sp = fSPow;
	arSail.dmg = fTopDmg;

	return &BI_g_fRetVal;
}

void procSetUsingAbility()
{
	int q;
	int chIdx = GetEventData();
	ref mainCh = GetMainCharacter();
	int mainIdx = sti(mainCh.index);
	aref aroot,arcur;
	string tmpStr;

	if( chIdx<0 || CharacterIsDead(GetCharacter(chIdx)) )
	{
		makearef(aroot,BattleInterface.AbilityIcons);
		q = GetAttributesNum(aroot);
		for(int i=0; i<q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		return;
	}

	// ?????? ???????????????? ??????????????????
	if (mainIdx == chIdx)
	{
		BattleInterface.AbilityIcons.Brander.enable			= false;
		BattleInterface.AbilityIcons.Troopers.enable		= false;

		BattleInterface.AbilityIcons.ImmediateReload.enable	= GetOfficersPerkUsing(mainCh,"ImmediateReload");
		BattleInterface.AbilityIcons.InstantBoarding.enable	= GetOfficersPerkUsing(mainCh,"InstantBoarding") && bAttack && !Whr_IsStorm(); // KK

		BattleInterface.AbilityIcons.LightRepair.enable		= false;
		if(GetOfficersPerkUsing(mainCh, "LightRepair" ))
		{	if(GetHullPercent(mainCh)<10.0 || GetSailPercent(mainCh)<10.0)
			{	BattleInterface.AbilityIcons.LightRepair.enable = true;
			}
		}
		BattleInterface.AbilityIcons.InstantRepair.enable		= CheckInstantRepairCondition(mainCh);
		BattleInterface.AbilityIcons.Turn180.enable				= GetOfficersPerkUsing(mainCh,"Turn180");
		BattleInterface.AbilityIcons.SandbankManeuver.enable	= GetOfficersPerkUsing(mainCh,"SandbankManeuver");

		// Set items abilities
		q = FindQuestUsableItem(&arcur,0);
		while( q>0 )
		{
			tmpStr = arcur.id;
			if( GetCharacterItem(mainCh,arcur.id)>0 )
			{
				BattleInterface.AbilityIcons.(tmpStr).enable	= true;
				BattleInterface.AbilityIcons.(tmpStr).picNum	= arcur.quest.pic;
				BattleInterface.AbilityIcons.(tmpStr).selPicNum	= arcur.quest.pic + 1;
				BattleInterface.AbilityIcons.(tmpStr).texNum	= 9;
				BattleInterface.AbilityIcons.(tmpStr).event		= arcur.id;
				BattleInterface.AbilityIcons.(tmpStr).quest		= arcur.quest;
			}
			else
			{
				BattleInterface.AbilityIcons.(tmpStr).enable	= false;
			}
			q = FindQuestUsableItem(&arcur,q+1);
		}
	}

	else
	{
		BattleInterface.AbilityIcons.Brander.enable			= false;
		if(bAttack && GetRemovable(GetCharacter(chIdx)) && GetOfficersPerkUsing(mainCh, "Brander"))
			BattleInterface.AbilityIcons.Brander.enable		= true;

		BattleInterface.AbilityIcons.Troopers.enable		= GetOfficersPerkUsing(mainCh, "Troopers");

		BattleInterface.AbilityIcons.ImmediateReload.enable	= false;
		BattleInterface.AbilityIcons.InstantBoarding.enable	= false;
		BattleInterface.AbilityIcons.LightRepair.enable		= false;
		BattleInterface.AbilityIcons.InstantRepair.enable	= false;
		BattleInterface.AbilityIcons.Turn180.enable			= false;
		BattleInterface.AbilityIcons.SandbankManeuver.enable= false;
	}
}

ref procCheckEnableLocator()
{
	BI_intRetValue = true;

	string comName = GetEventData();
	aref arLoc = GetEventData();

	if(comName=="BI_SailTo")
	{
		if( CheckAttribute(&AISea,"Island") && CheckAttribute(arLoc,"name") )
		{
			BI_intRetValue = Island_isGotoEnableLocal(AISea.Island,arLoc.name);

			// screwface : enable sail-to forts for hostile nation sail-to-port for neutral
			if (CheckAttribute(arLoc, "go") && arLoc.go != "")
			{
				// a fort
				if(CheckAttribute(arLoc, "GoAfterBoard.location") && Island_isGotoEnableLocal(AISea.Island,arLoc.GoAfterBoard.location) == true) // if we have the associated port in sailto list
				{
					if(arLoc.go == "Fort" && arLoc.commander !="")
					{
						if(GetNationRelation(sti(Characters[GetCharacterIndex(arLoc.commander)].nation), sti(Characters[GetMainCharacterIndex()].nation)) == RELATION_ENEMY)
						{
							BI_intRetValue = true;
						}
						else
						{
							BI_intRetValue = false;
						}
					}
				}

				// a Port
				if(BI_intRetValue == true)
				{
					if(CheckAttribute(Locations[FindLocation(arLoc.go)], "type"))
					{
						if(Locations[FindLocation(arLoc.go)].type == "port" || Locations[FindLocation(arLoc.go)].type == "town")
						{
							if(GetNationRelation(GetLocationNationFromID(arLoc.go), sti(Characters[GetMainCharacterIndex()].nation)) != RELATION_ENEMY)
							{
								BI_intRetValue = true;
							}
							else
							{
								BI_intRetValue = false;
							}
						}
					}
				}
			} // Screwface : end
		}
	}

	return &BI_intRetValue;
}

ref procCheckEnableShip()
{
	BI_intRetValue = true;

	string comName = GetEventData();
	int cn = GetEventData();

	if(cn>=0)
	{
		switch(comName)
		{
		case "BI_InstantBoarding":
			BI_intRetValue = Character_IsAbordageEnable(GetCharacter(cn));
		break;
		}
	}

	return &BI_intRetValue;
}

void BI_ProcessControlPress()
{
	string ControlName = GetEventData();
// KK -->
	ref PChar = GetMainCharacter();
	if (HasSubStr(ControlName, "BI_Charge")) {
		if (GetCaracterShipCannonsType(PChar) == CANNON_TYPE_NONECANNON) return;
		if (bDisableAllCommands) return;
	}
	if (HasSubStr(ControlName, "Ship_") && bDisableAllCommands) return;
	if (HasSubStr(ControlName, "Telescope") && bDisableAllCommands) return;
// <-- KK

	//int tmpNameFileID = LanguageOpenFile("interface_strings.txt");// MAXIMUS 02.10.2006

//boal -->
	int chargeType=GOOD_BALLS;

	int ammoQty = 0;

	int nChgType[8];
    nChgType = GetCurrentCharge();
	switch(ControlName)
	{
		case "BI_ChargeCannonballs":
			if (nChgType[0] == 2) break; // KK
			ammoQty = GetCargoGoods(PChar, GOOD_BALLS);
			if ( ammoQty > 0 )
			{
				Log_SetStringToLog(XI_ConvertString("Balls"));
				chargeType=GOOD_BALLS;
				Ship_ChangeCharge(PChar, chargeType);
			}
			else
			{
				Log_SetStringToLog(TranslateString("","No Balls to Load"));// MAXIMUS 02.10.2006
			}
		break;
		case "BI_ChargeGrapes":
			if (nChgType[0] == 3) break; // KK
			ammoQty = GetCargoGoods(PChar, GOOD_GRAPES);
			if ( ammoQty > 0 )
			{
				Log_SetStringToLog(XI_ConvertString("Grapes"));
				chargeType=GOOD_GRAPES;
				Ship_ChangeCharge(PChar, chargeType);
			}
			else
			{
				Log_SetStringToLog(TranslateString("","No Grapes to Load"));// MAXIMUS 02.10.2006
			}
		break;
		case "BI_ChargeKnippels":
			if (nChgType[0] == 0) break; // KK
			ammoQty = GetCargoGoods(PChar, GOOD_KNIPPELS);
			if ( ammoQty > 0 )
			{
				Log_SetStringToLog(XI_ConvertString("Chains"));
				chargeType=GOOD_KNIPPELS;
				Ship_ChangeCharge(PChar, chargeType);
			}
			else
			{
				Log_SetStringToLog(TranslateString("","No Chains to Load"));// MAXIMUS 02.10.2006
			}
		break;
		case "BI_ChargeBombs":
				if (nChgType[0] == 1) break; // KK
			ammoQty = GetCargoGoods(PChar, GOOD_BOMBS);
			if ( ammoQty > 0 )
			{
				//if (USE_REAL_CANNONS == 0) { // TIH allow quick charge to stolen bombs Aug31'06
				Log_SetStringToLog(XI_ConvertString("Bombs"));
				chargeType=GOOD_BOMBS;
				Ship_ChangeCharge(PChar, chargeType);
				//}
			}
			else
			{
				Log_SetStringToLog(TranslateString("","No Bombs to Load"));// MAXIMUS 02.10.2006
			}
		break;
	}
// boal <--
	//LanguageCloseFile(tmpNameFileID);// MAXIMUS 02.10.2006
}

ref procGetSRollSpeed()
{
	int chrIdx = GetEventData();
	BI_g_fRetVal = 0.0;
	if(chrIdx>=0) BI_g_fRetVal = GetRSRollSpeed(GetCharacter(chrIdx));
	return &BI_g_fRetVal;
}

float GetRSRollSpeed(ref chref)
{
	float fRollSpeed;
	if(USE_REAL_SAILING) { fRollSpeed = 0.2 + 0.05 * makefloat( GetShipSkill(chref,SKILL_SAILING) ); } //0.5  KNB
	else fRollSpeed = 0.5 + 0.05 * makefloat( GetShipSkill(chref,SKILL_SAILING) );
	int crewQ = GetCrewQuantity(chref);
	int crewMin = GetMinCrewQuantity(chref);
	if(crewQ<crewMin) fRollSpeed *= makefloat(crewQ)/makefloat(crewMin);
	return fRollSpeed;
}

ref BI_GetLandData()
{
	string attrName;
	aref arLoc, arIsl, arList;
	arLoc = GetEventData();

	BI_intNRetValue[0] = 0;
	BI_intNRetValue[1] = BI_RELATION_NEUTRAL;
	BI_intNRetValue[2] = -1;
	BI_intNRetValue[3] = -1;

	if (CheckAttribute(arLoc,"fort.model")) {
		BI_intNRetValue[0] = 1;
		int chrIdx = Fort_FindCharacter(AISea.Island,"reload",arLoc.name);
		if (chrIdx >= 0) {
			if (CheckAttribute(&characters[chrIdx], "chr_ai.group") == true && characters[chrIdx].chr_ai.group == LAI_GROUP_PLAYER) BI_intNRetValue[1] = BI_RELATION_FRIEND; // KK
			if (SeaAI_GetRelation(chrIdx,GetMainCharacterIndex()) == RELATION_ENEMY) BI_intNRetValue[1] = BI_RELATION_ENEMY; // KK
		}
	}

	if( CheckAttribute(arLoc,"tex") && CheckAttribute(arLoc,"pic") )
	{
		makearef( arIsl, Islands[FindIsland(AISea.Island)] );
		attrName = "InterfaceTextures." + arLoc.tex;
		if( CheckAttribute(arIsl,attrName) )
		{
			BI_intNRetValue[2] = AddTextureToList( &BattleInterface, arIsl.(attrName), sti(arIsl.(attrName).h), sti(arIsl.(attrName).v) );
			BI_intNRetValue[3] = sti(arLoc.pic);
			//Boyer change for location interface textures
			if(CheckAttribute(arLoc, "selpic"))
                BI_intNRetValue[4] = sti(arLoc.selpic);
            else
                BI_intNRetValue[4] = sti(arLoc.pic) + 4;
		}
	}
	// NK EUROLANG -->
	if( CheckAttribute(arLoc,"label") ) {
        int idLngFile = LanguageOpenFile("LocLables.txt");
		arLoc.labelLoc = LanguageConvertString(idLngFile,arLoc.label);
        LanguageCloseFile(idLngFile);
		if( arLoc.labelLoc == "" ) {
            arLoc.labelLoc = arLoc.label;
			Trace("Warning! Language: string <"+arLoc.label+"> has not translation in file <LocLables.txt>");
		}
	}
	// NK <--

	// ????????????????
	if( BI_intNRetValue[2]<0 || BI_intNRetValue[3]<0 )
	{
		BI_intNRetValue[2] = AddTextureToList( &BattleInterface, "battle_interface\LandTarget1.tga.tx", 4, 2 ); // KK
		if( BI_intNRetValue[0]==0 ) {
			BI_intNRetValue[3] = 2; // KK
		} else {
			BI_intNRetValue[3] = 1; // KK
		}
	}

	return &BI_intNRetValue;
}

int GetTargChrIndex(int targNum, string locName)
{
	if(targNum==-1) {
		return Fort_FindCharacter(AISea.Island,"reload",locName);
	} else {
		return targNum;
	}
}

bool CheckSuccesfullBoard(ref rBoarderChr, ref rSieger)
{
	// skill = 1 -> k = 0.5; skill = 10 -> k = 2.0
	float k = 0.333 + GetShipSkill(rBoarderChr, SKILL_SNEAK)*0.167;

	// skill = 1 -> limit = 0.45 -> 0.2^0.5 (20%);   skill = 10 -> limit = 0.81 -> 0.9^2 (90%)
	float topLimit = 0.41 + GetShipSkill(rBoarderChr, SKILL_GRAPPLING)*0.04;

	if( pow(rand(1000)/1000.0, k) < topLimit ) return true;
	return false;
}

// KK -->
void SetUserIcons(string parent)
{
	ref mchr = GetMainCharacter();
	switch (parent)
	{
		case "BI_EnterShip":
			int ndecks = GetCharacterShipCannonsDeckCount(mchr);
			int nholds = GetCharacterShipCargoHoldCount(mchr);
			BattleInterface.UserIcons.ui1.enable = false;
			BattleInterface.UserIcons.ui2.enable = false;
			BattleInterface.UserIcons.ui3.enable = false;
			for (int i = 0; i < COMPANION_MAX; i++) {
				string ui = "ui" + (COMPANION_MAX + i);
				BattleInterface.UserIcons.(ui).enable = false;
				int cn = GetCompanionIndex(mchr, i);
				if (cn < 0 || cn == iShipCaptain) continue;
				ref curchr = GetCharacter(cn);
				int st = GetCharacterShipType(curchr);
				if (st >= 0 && st < SHIP_TYPES_QUANTITY) {
					BattleInterface.UserIcons.(ui).enable = true;
					BattleInterface.UserIcons.(ui).pic    = sti(ShipsTypes[st].BI.Pic);
					BattleInterface.UserIcons.(ui).selpic    = sti(ShipsTypes[st].BI.Pic) + 1;
					BattleInterface.UserIcons.(ui).tex    = sti(ShipsTypes[st].BI.Tex);
					BattleInterface.UserIcons.(ui).note   = GetMyShipName(curchr);
					BattleInterface.UserIcons.(ui).name   = cn;
				}
			}
		break;
		case "BI_Speed":
			BattleInterface.UserIcons.ui1.enable = true;
			BattleInterface.UserIcons.ui2.enable = true;
			BattleInterface.UserIcons.ui3.enable = true;
			BattleInterface.UserIcons.ui4.enable = false;
			BattleInterface.UserIcons.ui5.enable = false;
			BattleInterface.UserIcons.ui6.enable = false;
			BattleInterface.UserIcons.ui7.enable = false;
		break;
	}
}

string CheckDestinationType()
{
	aref LocatorRef = GetReloadMapRef(&arIslandReload, "name", sIslandLocator);
	if (CheckAttribute(LocatorRef, "go") == false || LocatorRef.go == "") return "";
	if (!CheckAttribute(Locations[FindLocation(LocatorRef.go)], "type")) return "";
	if(!CheckAttribute(Locations[FindLocation(LocatorRef.go)], "id")) return "";// MAXIMUS
	characters[GetMainCharacterIndex()].location.from_sea = LocatorRef.go;// MAXIMUS
	if(CheckAttribute(LocatorRef,"goto_enable") && LocatorRef.goto_enable == false){DeleteAttribute(LocatorRef,"goto_enable");} // Screwface : enable the sailto after you discovered the anchor
	return Locations[FindLocation(LocatorRef.go)].type;
}

void CreateCannonInfo()
{
	ref rtmp;
	ref mchr = GetMainCharacter();

	InterfaceStates.BI.RGunsVisible = GetCannonArcMaxQty(mchr, 1) > 0;
	makeref(rtmp, INRGuns);
	DeleteAttribute(rtmp, "");
	CopyAttributes(rtmp, &ILog);
	INRGuns.Log.width = RecalculateHIcon(20);
	INRGuns.Log.height = RecalculateVIcon(10);
	INRGuns.Log.left = sti(showWindow.left) + sti(showWindow.width) - RecalculateHIcon(30);
	INRGuns.Log.up = sti(showWindow.top) + RecalculateVIcon(100);
	INRGuns.Log.font = "small_bold_numbers";
	INRGuns.Log.color = argb(0,255,255,255);
	INRGuns.Log.offsetString = 14;
	INRGuns.Log.speed = 1.0;
	INRGuns.Log.color_speed = 0.0;
	SendMessage(&INRGuns, "lll", LOG_AND_ACTIONS_INIT, false, sti(InterfaceStates.BI.RGunsVisible));

	InterfaceStates.BI.LGunsVisible = GetCannonArcMaxQty(mchr, 3) > 0;
	makeref(rtmp, INLGuns);
	DeleteAttribute(rtmp, "");
	CopyAttributes(rtmp, &ILog);
	INLGuns.Log.width = RecalculateHIcon(20);
	INLGuns.Log.height = RecalculateVIcon(10);
	INLGuns.Log.left = sti(showWindow.left) + sti(showWindow.width) - RecalculateHIcon(240);
	INLGuns.Log.up = sti(showWindow.top) + RecalculateVIcon(100);
	INLGuns.Log.font = "small_bold_numbers";
	INLGuns.Log.color = argb(0,255,255,255);
	INLGuns.Log.offsetString = 14;
	INLGuns.Log.speed = 1.0;
	INLGuns.Log.color_speed = 0.0;
	SendMessage(&INLGuns, "lll", LOG_AND_ACTIONS_INIT, false, sti(InterfaceStates.BI.LGunsVisible));

	InterfaceStates.BI.FGunsVisible = GetCannonArcMaxQty(mchr, 0) > 0;
	makeref(rtmp, INFGuns);
	DeleteAttribute(rtmp, "");
	CopyAttributes(rtmp, &ILog);
	INFGuns.Log.width = RecalculateHIcon(20);
	INFGuns.Log.height = RecalculateVIcon(10);
	INFGuns.Log.left = sti(showWindow.left) + sti(showWindow.width) - RecalculateHIcon(130);
	INFGuns.Log.up = sti(showWindow.top) + 1;
	INFGuns.Log.font = "small_bold_numbers";
	INFGuns.Log.color = argb(0,255,255,255);
	INFGuns.Log.offsetString = 14;
	INFGuns.Log.speed = 1.0;
	INFGuns.Log.color_speed = 0.0;
	SendMessage(&INFGuns, "lll", LOG_AND_ACTIONS_INIT, false, sti(InterfaceStates.BI.FGunsVisible));

	InterfaceStates.BI.BGunsVisible = GetCannonArcMaxQty(mchr, 2) > 0;
	makeref(rtmp, INBGuns);
	DeleteAttribute(rtmp, "");
	CopyAttributes(rtmp, &ILog);
	INBGuns.Log.width = RecalculateHIcon(20);
	INBGuns.Log.height = RecalculateVIcon(10);
	INBGuns.Log.left = sti(showWindow.left) + sti(showWindow.width) - RecalculateHIcon(130);
	INBGuns.Log.up = sti(showWindow.top) + RecalculateVIcon(206);
	INBGuns.Log.font = "small_bold_numbers";
	INBGuns.Log.color = argb(0,255,255,255);
	INBGuns.Log.offsetString = 14;
	INBGuns.Log.speed = 1.0;
	INBGuns.Log.color_speed = 0.0;
	SendMessage(&INBGuns, "lll", LOG_AND_ACTIONS_INIT, false, sti(InterfaceStates.BI.BGunsVisible));
}

void RefreshCannonInfo()
{
	ref mchr = GetMainCharacter();
	InterfaceStates.BI.RGunsVisible = GetCannonArcMaxQty(mchr, 1) > 0;
	SendMessage(&INRGuns, "ll", LI_SET_VISIBLE, sti(InterfaceStates.BI.RGunsVisible));
	InterfaceStates.BI.LGunsVisible = GetCannonArcMaxQty(mchr, 3) > 0;
	SendMessage(&INLGuns, "ll", LI_SET_VISIBLE, sti(InterfaceStates.BI.LGunsVisible));
	InterfaceStates.BI.FGunsVisible = GetCannonArcMaxQty(mchr, 0) > 0;
	SendMessage(&INFGuns, "ll", LI_SET_VISIBLE, sti(InterfaceStates.BI.FGunsVisible));
	InterfaceStates.BI.BGunsVisible = GetCannonArcMaxQty(mchr, 2) > 0;
	SendMessage(&INBGuns, "ll", LI_SET_VISIBLE, sti(InterfaceStates.BI.BGunsVisible));
}

void UpdateCannonInfo()
{
	if (sti(InterfaceStates.BIVisible) == false) return;
	ref mchr = GetMainCharacter();
	int qty;
	string sqty;
	if (sti(InterfaceStates.BI.RGunsVisible) == true)
	{
		qty = GetCannonArcQty(mchr, 1);
		sqty = qty;
		if (qty < 10) sqty = " " + qty;
		SendMessage(&INRGuns, "lls", LOG_ADD_STRING, true, sqty);
	}
	if (sti(InterfaceStates.BI.LGunsVisible) == true)
	{
		qty = GetCannonArcQty(mchr, 3);
		sqty = qty;
		if (qty < 10) sqty = " " + qty;
		SendMessage(&INLGuns, "lls", LOG_ADD_STRING, true, sqty);
	}
	if (sti(InterfaceStates.BI.FGunsVisible) == true) SendMessage(&INFGuns, "lls", LOG_ADD_STRING, true, "" + GetCannonArcQty(mchr, 0));
	if (sti(InterfaceStates.BI.BGunsVisible) == true) SendMessage(&INBGuns, "lls", LOG_ADD_STRING, true, "" + GetCannonArcQty(mchr, 2));
}

void BIVisible(bool visibleFlag)
{
	Event(BI_EVENT_SET_VISIBLE, "l", visibleFlag);
}
// <-- KK

void SetShipPictureDataByShipTypeName(string sType)
{
	switch(sType)
	{
	case "tartane":
  		BI_intNRetValue[0] = 0+4*8;
		BI_intNRetValue[1] = 0+4*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;
    case "WarTartane":  // fix
  		BI_intNRetValue[0] = 2+4*8;
		BI_intNRetValue[1] = 2+4*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;
	case "lugger":
		BI_intNRetValue[0] = 0+0*8;
		BI_intNRetValue[1] = 0+0*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "sloop":
		BI_intNRetValue[0] = 0+1*8;
		BI_intNRetValue[1] = 0+1*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "barque":
		BI_intNRetValue[0] = 0+3*8;
		BI_intNRetValue[1] = 0+3*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "schooner":
		BI_intNRetValue[0] = 0+2*8;
		BI_intNRetValue[1] = 0+2*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "caravel":
		BI_intNRetValue[0] = 2+0*8;
		BI_intNRetValue[1] = 2+0*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "barkentine":
		BI_intNRetValue[0] = 2+2*8;
		BI_intNRetValue[1] = 2+2*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "brig":
		BI_intNRetValue[0] = 2+2*8;
		BI_intNRetValue[1] = 2+2*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "fleut":
		BI_intNRetValue[0] = 2+1*8;
		BI_intNRetValue[1] = 2+1*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "brigantine":
		BI_intNRetValue[0] = 2+2*8;
		BI_intNRetValue[1] = 2+2*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "galeon_l":
		BI_intNRetValue[0] = 2+3*8;
		BI_intNRetValue[1] = 2+3*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "galeon_h":
		BI_intNRetValue[0] = 4+1*8;
		BI_intNRetValue[1] = 4+1*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "pinnace":
		BI_intNRetValue[0] = 4+2*8;
		BI_intNRetValue[1] = 4+2*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "frigate":
		BI_intNRetValue[0] = 4+3*8;
		BI_intNRetValue[1] = 4+3*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "corvette":
		BI_intNRetValue[0] = 4+0*8;
		BI_intNRetValue[1] = 4+0*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "battleship":
		BI_intNRetValue[0] = 6+2*8;
		BI_intNRetValue[1] = 6+2*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "lineship":
		BI_intNRetValue[0] = 6+0*8;
		BI_intNRetValue[1] = 6+0*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "warship":
		BI_intNRetValue[0] = 6+1*8;
		BI_intNRetValue[1] = 6+1*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "manowar":
		BI_intNRetValue[0] = 6+3*8;
		BI_intNRetValue[1] = 6+3*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "SoleyRu":
		BI_intNRetValue[0] = 4+4*8;
		BI_intNRetValue[1] = 4+4*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "BrigQeen":
		BI_intNRetValue[0] = 2+2*8;
		BI_intNRetValue[1] = 2+2*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "BrigSW":
		BI_intNRetValue[0] = 2+2*8;
		BI_intNRetValue[1] = 2+2*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "XebekVML":
  		BI_intNRetValue[0] = 2+4*8;
		BI_intNRetValue[1] = 2+4*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "Corvette_quest":
		BI_intNRetValue[0] = 4+0*8;
		BI_intNRetValue[1] = 4+0*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "ArabellaShip":
		BI_intNRetValue[0] = 4+3*8;
		BI_intNRetValue[1] = 4+3*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;

	case "Flyingdutchman":
		BI_intNRetValue[0] = 6+1*8;
		BI_intNRetValue[1] = 6+1*8 + 1;
		BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;
		break;
	}
	BI_intNRetValue[3] = false;
}
