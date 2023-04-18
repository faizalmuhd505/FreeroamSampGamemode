/*******************************************************************************
* Name DO ARQUIVO :		modules/player/cmdss.pwn
*
* DESCRIÇÃO :
*	   command quem podem ser usados por qualquer Player.
*
* NOTAS :
*	   -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

static gplMarkExt[MAX_PLAYERS][2];
static Float:gplMarkPos[MAX_PLAYERS][3];

static gplAutoRepair[MAX_PLAYERS];
static gplHideNameTags[MAX_PLAYERS];
static gplGotoBlocked[MAX_PLAYERS];
static gplDriftActive[MAX_PLAYERS] = {true, ...};
static gplDriftCounter[MAX_PLAYERS];

static gCountDown;

static gplCreatedVehicle[MAX_PLAYERS][MAX_CREATED_VEHICLE_PER_PLAYER];

forward OnCheckVipKey(playerid);

//------------------------------------------------------------------------------

static Airplanes = mS_INVALID_LISTID;
static Bikes = mS_INVALID_LISTID;
static Boats = mS_INVALID_LISTID;
static Convertible = mS_INVALID_LISTID;
static Helicopters = mS_INVALID_LISTID;
static Industrials = mS_INVALID_LISTID;
static Lowrider = mS_INVALID_LISTID;
static OffRoad = mS_INVALID_LISTID;
static PublicService = mS_INVALID_LISTID;
static RC = mS_INVALID_LISTID;
static Saloon = mS_INVALID_LISTID;
static Sports = mS_INVALID_LISTID;
static StationWagon = mS_INVALID_LISTID;
static Trailer = mS_INVALID_LISTID;
static Unique = mS_INVALID_LISTID;

//------------------------------------------------------------------------------

hook OnGameModeInit()
{
	Command_AddAltNamed("command",		"cmds");
	Command_AddAltNamed("window",		"j");
	Command_AddAltNamed("lobby",		"m");
	Command_AddAltNamed("car",			"v");
	Command_AddAltNamed("myacc",		"stats");
	Command_AddAltNamed("myacc",		"rg");
	Command_AddAltNamed("sp",			"marcar");
	Command_AddAltNamed("gotomarkloc",			"irmarca");
	Command_AddAltNamed("ir",			"goto");
	Command_AddAltNamed("pm",			"mp");
	//
	Airplanes = LoadModelSelectionMenu("vehicles/Airplane.txt");
	Bikes = LoadModelSelectionMenu("vehicles/Bike.txt");
	Boats = LoadModelSelectionMenu("vehicles/Boat.txt");
	Convertible = LoadModelSelectionMenu("vehicles/Convertible.txt");
	Helicopters = LoadModelSelectionMenu("vehicles/Helicopter.txt");
	Industrials = LoadModelSelectionMenu("vehicles/Industrial.txt");
	Lowrider = LoadModelSelectionMenu("vehicles/Lowrider.txt");
	OffRoad = LoadModelSelectionMenu("vehicles/OffRoad.txt");
	PublicService = LoadModelSelectionMenu("vehicles/PublicService.txt");
	RC = LoadModelSelectionMenu("vehicles/RC.txt");
	Saloon = LoadModelSelectionMenu("vehicles/Saloon.txt");
	Sports = LoadModelSelectionMenu("vehicles/Sport.txt");
	StationWagon = LoadModelSelectionMenu("vehicles/StationWagon.txt");
	Trailer = LoadModelSelectionMenu("vehicles/Trailer.txt");
	Unique = LoadModelSelectionMenu("vehicles/Unique.txt");
	return 1;
}




//------------------------------------------------------------------------------

YCMD:vipadvantage(playerid, params[], help)
{
	SendClientMessage(playerid, COLOR_TITLE, "---------------------------------------- VIP Advantages ----------------------------------------");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* With a VIP account besides being helping us to keep the server online,");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* You also get benefits!");
	SendClientMessage(playerid, COLOR_SUB_TITLE, " ");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* Chat only for vips.");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* Tag [vip] before your name on chat.");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* /kitvip");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* /vipinfo");
	SendClientMessage(playerid, COLOR_TITLE, "---------------------------------------- VIP Advantages ----------------------------------------");
	return 1;
}

//------------------------------------------------------------------------------

YCMD:vipinfo(playerid, params[], help)
{
	if(!IsPlayerVIP(playerid))
		return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permissiono.");

	SendClientMessage(playerid, COLOR_TITLE, "---------------------------------------- VIP HELP ----------------------------------------");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* /kitvip - Receives a VIP weapon kit.");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* Use ! Before your messages to talk about Chat VIP.");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* Example !hai ");
	SendClientMessagef(playerid, COLOR_SUB_TITLE, "* Your VIP Account Expiras in: %s", convertTimestamp(GetPlayerVIP(playerid)));
	SendClientMessage(playerid, COLOR_TITLE, "---------------------------------------- VIP HELP ----------------------------------------");
	return 1;
}

//------------------------------------------------------------------------------

YCMD:kitvip(playerid, params[], help)
{
	if(!IsPlayerVIP(playerid))
		return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	if(IsPlayerInEvent(playerid))
		return SendClientMessage(playerid, COLOR_ERROR, "* You cannot use this command at an event.");

	if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
		return SendClientMessage(playerid, COLOR_ERROR, "* You can only use this command in Freeroam.");

	GivePlayerWeapon(playerid, 4, 1);
	GivePlayerWeapon(playerid, 16, 50);
	GivePlayerWeapon(playerid, 24, 250);
	GivePlayerWeapon(playerid, 26, 1000);
	GivePlayerWeapon(playerid, 29, 1000);
	GivePlayerWeapon(playerid, 30, 1000);
	GivePlayerWeapon(playerid, 34, 1000);
	GivePlayerWeapon(playerid, 39, 1000);

	PlayerPlaySound(playerid, 5203, 0.0, 0.0, 0.0);
	SendClientMessage(playerid, COLOR_SUCCESS, "* You received your VIP kit.");
	return 1;
}

//------------------------------------------------------------------------------

YCMD:rules(playerid, params[], help)
{
	ShowPlayerDialog(playerid, DIALOG_RULES, DIALOG_STYLE_MSGBOX, "{59c72c}LF - {FFFFFF}Rules",
	"{59c72c}1 - {ffffff}Cheats is not allowed to use.\n\
	{59c72c}2 - {ffffff}It is not allowed to disrespect other players.\n\
	{59c72c}3 - {ffffff}It is not allowed to make announcement of other servers.",
	"X", "");
	return 1;
}


//------------------------------------------------------------------------------

YCMD:credit(playerid, params[], help)
{
	ShowPlayerCredits(playerid);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:countdown(playerid, params[], help)
{
	if(gCountDown > 0)
		return SendClientMessage(playerid, COLOR_ERROR, "* A count is already underway.");

	new timer;
	sscanf(params, "I(3)", timer);

	if(timer > 10 || timer < 3)
		return SendClientMessage(playerid, COLOR_ERROR, "* The count cannot be less than 3 and greater than 10.");

	gCountDown = timer;
	CountDown();
	SendClientMessageToAllf(0xc2d645ff, "* %s started a countdown!", GetPlayerNamef(playerid));
	return 1;
}

//------------------------------------------------------------------------------

YCMD:myacc(playerid, params[], help)
{
	new ip[16];
	GetPlayerIp(playerid, ip, 16);
	SendClientMessage(playerid, COLOR_TITLE, "---------------------------------------- My account ----------------------------------------");
	SendClientMessagef(playerid, COLOR_SUB_TITLE, "Name: %s - Money: $%d - Banco: $%d - IP: %s", GetPlayerNamef(playerid), GetPlayerCash(playerid), GetPlayerBankCash(playerid), ip);
	SendClientMessagef(playerid, COLOR_SUB_TITLE, "Last login: %s - Time Played: %s", convertTimestamp(GetPlayerLastLogin(playerid)), GetPlayerPlayedTimeStamp(playerid));
	SendClientMessage(playerid, COLOR_TITLE, "---------------------------------------- My account ----------------------------------------");
	return 1;
}

//------------------------------------------------------------------------------

YCMD:kill(playerid, params[], help)
{
	SetPlayerHealth(playerid, 0.0);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:drift(playerid, params[], help)
{
	if(!gplDriftActive[playerid])
	{
		PlayConfirmSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You activated the drift counter.");
		gplDriftActive[playerid] = true;
	}
	else
	{
		PlayCancelSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You disabled the drift counter.");
		gplDriftActive[playerid] = false;

		if(gplDriftCounter[playerid] == 0)
		{
			HidePlayerDriftTextdraw(playerid, true);
		}
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:driftcounterstyle(playerid, params[], help)
{
	if(!gplDriftCounter[playerid])
	{
		PlayConfirmSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You changed the drift counter to the #2 style.");
		gplDriftCounter[playerid] = true;
		HidePlayerDriftTextdraw(playerid, true);
	}
	else
	{
		PlayConfirmSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You changed the drift counter to the #1 style.");
		gplDriftCounter[playerid] = false;
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:togtele(playerid, params[], help)
{
	if(!gplGotoBlocked[playerid])
	{
		PlayCancelSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You blocked the teleport to you.");
		gplGotoBlocked[playerid] = true;
	}
	else
	{
		PlayConfirmSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You unlocked the teleport to you.");
		gplGotoBlocked[playerid] = false;
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:nick(playerid, params[], help)
{
	if(!gplHideNameTags[playerid])
	{
		PlayCancelSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You hid all nicks.");
		gplHideNameTags[playerid] = true;

		foreach(new i: Player)
		{
			ShowPlayerNameTagForPlayer(playerid, i, false);
		}
	}
	else
	{
		PlayConfirmSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You showed all the nicks.");
		gplHideNameTags[playerid] = false;

		foreach(new i: Player)
		{
			ShowPlayerNameTagForPlayer(playerid, i, true);
		}
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:autorepair(playerid, params[], help)
{
	if(!gplAutoRepair[playerid])
	{
		PlayConfirmSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You activated automatic repair to your Vehicles.");
		gplAutoRepair[playerid] = true;
	}
	else
	{
		PlayCancelSound(playerid);
		SendClientMessage(playerid, COLOR_SUCCESS, "* You disabled automatic repair to your Vehicles.");
		gplAutoRepair[playerid] = false;
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:givemoney(playerid, params[], help)
{
	new	targetid, value;
	if(sscanf(params, "ui", targetid, value))
		return SendClientMessage(playerid, COLOR_INFO, "* /givemoney [playerid] [value]");

	else if(!IsPlayerLogged(targetid))
		return SendClientMessage(playerid, COLOR_ERROR, "* Player not connected.");

	else if(GetPlayerDistanceFromPlayer(playerid, targetid) > 5.0)
		return SendClientMessage(playerid, COLOR_ERROR, "* You are not close to the player.");

	else if(GetPlayerCash(playerid) < value)
		return SendClientMessage(playerid, COLOR_ERROR, "* You don't have this amount of Money.");

	SendClientMessagef(playerid, 0xa5f413ff, "* You gave $%d for %s.", value, GetPlayerNamef(targetid));
	SendClientMessagef(targetid, 0xa5f413ff, "* %s it gave $%d for you.", GetPlayerNamef(playerid), value);

	new message[38 + MAX_PLAYER_NAME];
	format(message, sizeof(message), "Di Am An Amount of Money to %s.", GetPlayerNamef(targetid));
	SendClientActionMessage(playerid, 20.0, message);

	SetPlayerCash(playerid, GetPlayerCash(playerid) - value);
	SetPlayerCash(targetid, GetPlayerCash(targetid) + value);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:activatevip(playerid, params[], help)
{
	new	key[30];
	if(sscanf(params, "s[30]", key))
		return SendClientMessage(playerid, COLOR_INFO, "* /activatevip [key]");

	else if(IsPlayerVIP(playerid))
		return SendClientMessage(playerid, COLOR_ERROR, "* You are already VIP.");

	new query[128];
    mysql_format(gMySQL, query, sizeof(query), "SELECT * FROM `vip_keys` WHERE `serial` = '%e' LIMIT 1", key);
    mysql_tquery(gMySQL, query, "OnCheckVipKey", "i", playerid);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:changeacc(playerid, params[], help)
{
	new	current_password[32], newName[MAX_PLAYER_NAME];
	if(sscanf(params, "s[32]s[32]", current_password, newName))
		return SendClientMessage(playerid, COLOR_INFO, "* /changeacc [current password] [New Name]");

	if(strlen(newName) > MAX_PLAYER_NAME)
		return SendClientMessage(playerid, COLOR_ERROR, "* Name very long.");

	if(!strcmp(GetPlayerPassword(playerid), current_password) && !isnull(current_password))
	{
		ChangePlayerName(playerid, newName);
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "* Incorrect current password.");
	}
	return 1;
}
//------------------------------------------------------------------------------

YCMD:changepass(playerid, params[], help)
{
	new	current_password[32], new_password[32];
	if(sscanf(params, "s[32]s[32]", current_password, new_password))
		return SendClientMessage(playerid, COLOR_INFO, "* /changepass [current password] [New Password]");

	if(strlen(new_password) > 31)
		return SendClientMessage(playerid, COLOR_ERROR, "* Very long password.");

	if(!strcmp(GetPlayerPassword(playerid), current_password) && !isnull(current_password))
	{
		SetPlayerPassword(playerid, new_password);
		SendClientMessage(playerid, COLOR_SUCCESS, "* Password changed successfully.");
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "* Incorrect current password.");
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:eu(playerid, params[], help)
{
	if(isnull(params))
		return SendClientMessage(playerid, COLOR_INFO, "* /eu [message]");

	SendClientActionMessage(playerid, 20.0, params);
	return 1;
}


//------------------------------------------------------------------------------

YCMD:id(playerid, params[], help)
{
	new targetid;
	if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_INFO, "* /id [Player]");

	else if(!IsPlayerLogged(targetid))
		SendClientMessage(playerid, COLOR_ERROR, "* Player not connected.");

    new output[40];
	format(output, sizeof(output), "* %s(ID: %i)", GetPlayerNamef(targetid), targetid);
	SendClientMessage(playerid, COLOR_INFO, output);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:window(playerid, params[], help)
{
    if(!IsPlayerInAnyVehicle(playerid))
        SendClientMessage(playerid, COLOR_ERROR, "* You are not in a Vehicle.");
    else
    {
        new driver, passenger, backleft, backright;
        new vehicleid = GetPlayerVehicleID(playerid);
        GetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, backright);

        switch(GetPlayerVehicleSeat(playerid))
        {
            case 0:
            {
                if(driver == -1 || driver == 1)
                {
                    SendClientActionMessage(playerid, 15.0, "Open the driver's window.");
                    SetVehicleParamsCarWindows(vehicleid, 0, passenger, backleft, backright);
                }
                else
                {
                    SendClientActionMessage(playerid, 15.0, "Closes the driver's window.");
                    SetVehicleParamsCarWindows(vehicleid, 1, passenger, backleft, backright);
                }
            }
            case 1:
            {
                if(passenger == -1 || passenger == 1)
                {
                    SendClientActionMessage(playerid, 15.0, "Open the passenger window.");
                    SetVehicleParamsCarWindows(vehicleid, driver, 0, backleft, backright);
                }
                else
                {
                    SendClientActionMessage(playerid, 15.0, "Closes the passenger window.");
                    SetVehicleParamsCarWindows(vehicleid, driver, 1, backleft, backright);
                }
            }
            case 2:
            {
                if(backleft == -1 || backleft == 1)
                {
                    SendClientActionMessage(playerid, 15.0, "Opens the passenger window.");
                    SetVehicleParamsCarWindows(vehicleid, driver, passenger, 0, backright);
                }
                else
                {
                    SendClientActionMessage(playerid, 15.0, "Closes the passenger window.");
                    SetVehicleParamsCarWindows(vehicleid, driver, passenger, 1, backright);
                }
            }
            case 3:
            {
                if(backright == -1 || backright == 1)
                {
                    SendClientActionMessage(playerid, 15.0, "Open the passenger window.");
                    SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, 0);
                }
                else
                {
                    SendClientActionMessage(playerid, 15.0, "Closes the passenger window.");
                    SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, 1);
                }
            }
            default:
            {
                SendClientMessage(playerid, COLOR_ERROR, "* You can't open this window.");
            }
        }
    }
    return 1;
}

//------------------------------------------------------------------------------
YCMD:carlight(playerid, params[], help)
{
    if(!IsPlayerInAnyVehicle(playerid))
        SendClientMessage(playerid, COLOR_ERROR, "*You are not in a Vehicle.");
    else if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        SendClientMessage(playerid, COLOR_ERROR, "* You are not the driver.");
    else
    {
        new engine, lights, alarm, doors, bonnet, boot, objective, vehicleid;
        vehicleid = GetPlayerVehicleID(playerid);
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

        if(lights == VEHICLE_PARAMS_OFF || lights == VEHICLE_PARAMS_UNSET)
		{
			PlayConfirmSound(playerid);
			SendClientMessage(playerid, COLOR_SUCCESS, "* You turned on the Vehicle Light.");
			SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
		}
        else
		{
			PlayCancelSound(playerid);
			SendClientMessage(playerid, COLOR_SUCCESS, "* You hung up the Vehicle Light.");
			SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
		}
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:eject(playerid, params[], help)
{
	if(!IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_ERROR, "* You are not in a Vehicle.");

	else if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendClientMessage(playerid, COLOR_ERROR, "* You are not the driver.");

	new targetid;
	if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_INFO, "* /ejetar [playerid]");

	else if(!IsPlayerInVehicle(targetid, GetPlayerVehicleID(playerid)))
		return SendClientMessage(playerid, COLOR_ERROR, "* The player is not in his Vehicle.");

	else if(playerid == targetid)
		return SendClientMessage(playerid, COLOR_ERROR, "* You can't eject yourself.");

	SendClientMessagef(playerid, 0xFFFFFFFF, "* You ejected {00ACE6}%s{FFFFFF} Vehicle.", GetPlayerNamef(targetid));
	SendClientMessagef(targetid, 0xFFFFFFFF, "* You were ejected from Vehicle by {00ACE6}%s{FFFFFF}.", GetPlayerNamef(playerid));
	RemovePlayerFromVehicle(targetid);
	return true;
}

//------------------------------------------------------------------------------

YCMD:afk(playerid, params[], help)
{
	new count = 0, string[86], hours, minutes, seconds, milliseconds;
	SendClientMessage(playerid, COLOR_TITLE, "- Absent players -");

	foreach(new i: Player)
	{
		if(IsPlayerPaused(i))
		{
			milliseconds = GetTickCount() - GetPlayerPausedTime(i);
			seconds = (milliseconds / 1000) % 60;
			minutes = ((milliseconds / (1000*60)) % 60);
			hours   = ((milliseconds / (1000*60*60)) % 24);

			format(string, sizeof string, "* %s {A6A6A6}(ID: %i){FFFFFF} - %02d:%02d:%02d", GetPlayerNamef(i), i, hours, minutes, seconds);
			SendClientMessage(playerid, COLOR_WHITE, string);
			count++;
		}
	}

	if(count == 0)
		SendClientMessage(playerid, COLOR_ERROR, "* No Absent Player Online.");
	return 1;
}

//------------------------------------------------------------------------------

YCMD:admins(playerid, params[], help)
{
	new count = 0, string[74], output[4096];
	foreach(new i: Player)
	{
		if(GetPlayerAdminLevel(i) >= PLAYER_RANK_RECRUIT)
		{
			format(string, sizeof string, "{FFFFFF}* [{%06x}%s{FFFFFF}] %s {A6A6A6}(ID: %i)\n", GetPlayerRankColor(i) >>> 8, GetPlayerAdminRankName(i, true), GetPlayerNamef(i), i);
			strcat(output, string);
			count++;
		}
	}

	if(count == 0)
		SendClientMessage(playerid, COLOR_ERROR, "* No member of online moderation.");
	else
	{
		PlaySelectSound(playerid);
		strcat(output, "\n{ffffff}If you want to talk to an administrator use the field below:");
		ShowPlayerDialog(playerid, DIALOG_ADMIN_REPORT, DIALOG_STYLE_INPUT, "Online Administrators", output, "Send Report", "Cancle");
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:report(playerid, params[], help)
{
	if(isnull(params))
		return SendClientMessage(playerid, COLOR_INFO, "* /report [message]");

	foreach(new i: Player)
	{
		if(GetPlayerAdminLevel(i) < PLAYER_RANK_RECRUIT)
			continue;

		new message[150 + MAX_PLAYER_NAME];
		format(message, 150 + MAX_PLAYER_NAME, "* Report of %s: %s", GetPlayerNamef(playerid), params);
		SendClientMessage(i, 0x5b809eff, message);
	}
	SendClientMessage(playerid, 0x5b809eff, "* Report sent successfully.");
	return 1;
}

//------------------------------------------------------------------------------

YCMD:reportplayer(playerid, params[], help)
{
	new targetid, reason[128];
	if(sscanf(params, "us", targetid, reason))
		return SendClientMessage(playerid, COLOR_INFO, "* /reportplayer [playerid] [reason]");

	if(playerid == targetid)
		return SendClientMessage(playerid, COLOR_ERROR, "* You cannot report yourself.");

	if(IsPlayerNPC(targetid) || !IsPlayerLogged(targetid))
		return SendClientMessage(playerid, COLOR_ERROR, "* Player not connected.");

	if(GetPlayerAdminLevel(targetid) > PLAYER_RANK_RECRUIT)
		return SendClientMessage(playerid, COLOR_ERROR, "* You cannot report administrators, use Discord to report.");

	foreach(new i: Player)
	{
		if(GetPlayerAdminLevel(i) < PLAYER_RANK_RECRUIT)
			continue;

		new message[150 + MAX_PLAYER_NAME];
		format(message, 150 + MAX_PLAYER_NAME, "* %s reported %s. Reason: %s", GetPlayerNamef(playerid), GetPlayerNamef(targetid), reason);
		SendClientMessage(i, 0x5b809eff, message);
	}
	SendClientMessage(playerid, 0x5b809eff, "* Player reported successfully.");
	return 1;
}

//------------------------------------------------------------------------------

YCMD:markloc(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    gplMarkExt[playerid][0] = GetPlayerInterior(playerid);
    gplMarkExt[playerid][1] = GetPlayerVirtualWorld(playerid);
    GetPlayerPos(playerid, gplMarkPos[playerid][0], gplMarkPos[playerid][1], gplMarkPos[playerid][2]);
	SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You marked your current position. (%.2f, %.2f, %.2f, %d, %d)", gplMarkPos[playerid][0], gplMarkPos[playerid][1], gplMarkPos[playerid][2], gplMarkExt[playerid][0], gplMarkExt[playerid][1]);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:gotomarkloc(playerid, params[], help)
{
	if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
		return SendClientMessage(playerid, COLOR_ERROR, "* You do not use this command in this game mode.");

    SetPlayerInterior(playerid, gplMarkExt[playerid][0]);
    SetPlayerVirtualWorld(playerid, gplMarkExt[playerid][1]);
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        SetPlayerPos(playerid, gplMarkPos[playerid][0], gplMarkPos[playerid][1], gplMarkPos[playerid][2]);
    else
        SetVehiclePos(GetPlayerVehicleID(playerid), gplMarkPos[playerid][0], gplMarkPos[playerid][1], gplMarkPos[playerid][2]);
	SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You went to the marked position. (%.2f, %.2f, %.2f, %d, %d)", gplMarkPos[playerid][0], gplMarkPos[playerid][1], gplMarkPos[playerid][2], gplMarkExt[playerid][0], gplMarkExt[playerid][1]);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:mdist(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "*You do not have permission.");

	SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You are %.2f units from a distance from the marked position. (%.2f, %.2f, %.2f, %d, %d)",
    GetPlayerDistanceFromPoint(playerid, gplMarkPos[playerid][0], gplMarkPos[playerid][1], gplMarkPos[playerid][2]), gplMarkPos[playerid][0], gplMarkPos[playerid][1], gplMarkPos[playerid][2], gplMarkExt[playerid][0], gplMarkExt[playerid][1]);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:plate(playerid, params[], help)
{
	new plate[32];
	if(sscanf(params, "s[32]", plate))
		return SendClientMessage(playerid, COLOR_INFO, "* /plate [text]");

	if(!IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_ERROR, "* You are not in a Vehicle");

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendClientMessage(playerid, COLOR_ERROR, "* You are not the driver of this Vehicle.");

	new vehicleid = GetPlayerVehicleID(playerid);
	new Float:x, Float:y, Float:z, Float:a;
	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);

	SetVehicleNumberPlate(vehicleid, plate);
	SetVehicleToRespawn(vehicleid);

	SetVehiclePos(vehicleid, x, y, z);
	SetVehicleZAngle(vehicleid, a);
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	PutPlayerInVehicle(playerid, vehicleid, 0);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:day(playerid, params[], help)
{
	SetPlayerTime(playerid, 12, 00);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:noon(playerid, params[], help)
{
	SetPlayerTime(playerid, 18, 00);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:night(playerid, params[], help)
{
	SetPlayerTime(playerid, 01, 00);
	return 1;
}
//------------------------------------------------------------------------------

YCMD:fightstyle(playerid, params[], help)
{
	PlayConfirmSound(playerid);
	ShowPlayerDialog(playerid, DIALOG_FIGHTING_LIST, DIALOG_STYLE_LIST, "Fight", "Normal\nBoxing\nKungfu\nKneeHead\nGrabKick\nElbow", "Definir", "Sair");
	return 1;
}
//------------------------------------------------------------------------------

YCMD:v(playerid, params[], help)
{
	PlayConfirmSound(playerid);
	ShowPlayerDialog(playerid, DIALOG_VEHICLE_LIST, DIALOG_STYLE_LIST, "Car list", "Planes\nBikes\nBoat\nConvertible\nHelicopter\nIndustrial\nLowrider\nOff Road\nPublic services\nRC\nSedan\nSports\nTruck\nTrailers\nUnique", "Select", "X");
	return 1;
}


//------------------------------------------------------------------------------

YCMD:x(playerid, params[], help)
{
	if(!IsPlayerInAnyVehicle(playerid))
		SendClientMessage(playerid, COLOR_ERROR, "* You are not in a Vehicle.");
	else
	{
		new Float:a;
		GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
		SetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:repairveh(playerid, params[], help)
{
	if(!IsPlayerInAnyVehicle(playerid))
		SendClientMessage(playerid, COLOR_ERROR, "*You are not in a Vehicle.");
	else
	{
		PlayBuySound(playerid);
		RepairVehicle(GetPlayerVehicleID(playerid));
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:myweather(playerid, params[], help)
{
	new weatherid;
	if(sscanf(params, "i", weatherid))
	   return SendClientMessage(playerid, COLOR_INFO, "* /myweather [weatherid]");

	SetPlayerWeather(playerid, weatherid);
	SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You changed the ID of your weather to %i.", weatherid);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:goto(playerid, params[], help)
{
	if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
		return SendClientMessage(playerid, COLOR_ERROR, "* You do not use this command in this game mode.");

	new targetid;
	if(sscanf(params, "u", targetid))
		return SendClientMessage(playerid, COLOR_INFO, "* /igotor [playerid]");

	else if(!IsPlayerLogged(targetid))
		return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

	else if(targetid == playerid)
		return SendClientMessage(playerid, COLOR_ERROR, "* You can't go to yourself.");

	else if(gplGotoBlocked[targetid])
		return SendClientMessage(playerid, COLOR_ERROR, "* This player blocked the teleport to him.");

	else if(GetPlayerGamemode(targetid) != GAMEMODE_FREEROAM)
		return SendClientMessage(playerid, COLOR_ERROR, "* This player is not in Freeroam mode.");

	new Float:x, Float:y, Float:z;
	GetPlayerPos(targetid, x, y, z);

	SetPlayerInterior(playerid, GetPlayerInterior(targetid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { SetPlayerPos(playerid, x, y, z); }
	else
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		SetVehiclePos(vehicleid, x, y, z);
		LinkVehicleToInterior(vehicleid, GetPlayerInterior(targetid));
		SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(targetid));
	}

	SendClientMessagef(targetid, COLOR_PLAYER_COMMAND, "* %s came to you.", GetPlayerNamef(playerid));
	SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You went to %s.", GetPlayerNamef(targetid));
	return 1;
}


//------------------------------------------------------------------------------

YCMD:pm(playerid, params[], help)
{
   new targetid, message[128];
   if(sscanf(params, "us[128]", targetid, message))
	   return SendClientMessage(playerid, COLOR_INFO, "* /pm [playerid] [message]");

   else if(!IsPlayerLogged(targetid))
	   return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

   else if(playerid == targetid)
	   return SendClientMessage(playerid, COLOR_ERROR, "*You can't send private message to yourself.");

   new output[144];
   format(output, sizeof(output), "* [PM] %s(ID: %d): %s", GetPlayerNamef(playerid), playerid, message);
   SendClientMessage(targetid, COLOR_MUSTARD, output);
   format(output, sizeof(output), "* [PM] for %s(ID: %d): %s", GetPlayerNamef(targetid), targetid, message);
   SendClientMessage(playerid, COLOR_MUSTARD, output);
   return 1;
}

//------------------------------------------------------------------------------

YCMD:ls(playerid, params[], help)
{
	if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
		return SendClientMessage(playerid, COLOR_ERROR, "* You do not use this command in this game mode.");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        SetPlayerPos(playerid, 1540.3774, -1675.6068, 13.5505);
    else
        SetVehiclePos(GetPlayerVehicleID(playerid), 1540.3774, -1675.6068, 13.5505);

    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
 	return 1;
}

//------------------------------------------------------------------------------

YCMD:sf(playerid, params[], help)
{
	if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
		return SendClientMessage(playerid, COLOR_ERROR, "* You do not use this command in this game mode.");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        SetPlayerPos(playerid, -1816.0549, 590.1733, 35.1641);
    else
        SetVehiclePos(GetPlayerVehicleID(playerid), -1816.0549, 590.1733, 35.1641);

    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:lv(playerid, params[], help)
{
	if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
		return SendClientMessage(playerid, COLOR_ERROR, "* You do not use this command in this game mode.");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        SetPlayerPos(playerid, 2023.5212, 1341.9235, 10.82035);
    else
        SetVehiclePos(GetPlayerVehicleID(playerid), 2023.5212, 1341.9235, 10.8203);

    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:lb(playerid, params[], help)
{
	if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
		return SendClientMessage(playerid, COLOR_ERROR, "* You do not use this command in this game mode.");

    SetPlayerInterior(playerid, 1);
    SetPlayerVirtualWorld(playerid, 0);
	SetPlayerPos(playerid, -766.5842, 505.1011, 1376.5531);
    return 1;
}

//------------------------------------------------------------------------------
YCMD:cmds(playerid, params[], help)
{
	PlaySelectSound(playerid);
	SendClientMessage(playerid, COLOR_TITLE, "---------------------------------------- Command - All ----------------------------------------");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "VEH: /car /repairveh /tuning /x /v /plate /eject /carlight /window /autorepair /drift /driftcounterstyle");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "PLAYER: /credit /countdown /myacc /kill /togtele /nick /givemoney /activatevip /changeacc /changepass");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "PLAYER: /eu /id /afk /admins /report /reportplayer /markloc /gotomarkloc /mdist /day /noon /night");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "PLAYER: /v /car /fightstyle /myweather /goto /pm /vipinfo /kitvip");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "TELEPORT: /ls /sf /lv /lb");
	//SendClientMessage(playerid, COLOR_SUB_TITLE, "PLAYER: ");
	return 1;
}

YCMD:car(playerid, params[], help)
{
	if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
		return SendClientMessage(playerid, COLOR_ERROR, "* You cannot create vehicles in this game mode.");

	new vehicleName[32], color1, color2, idx, iString[128];
	if(sscanf(params, "s[32]I(-1)I(-1)", vehicleName, color1, color2))
		return SendClientMessage(playerid, COLOR_INFO, "* /car [name] [cor] [cor]");

  	idx = GetVehicleModelIDFromName(vehicleName);

  	if(idx == -1)
  	{
  		idx = strval(iString);

  		if(idx < 400 || idx > 611)
  			return SendClientMessage(playerid, COLOR_ERROR, "* Invalid vehicle.");
  	}

	new Float:x, Float:y, Float:z, Float:a;
	if(IsPlayerInAnyVehicle(playerid))
	{
		GetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
		GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	else
	{
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, a);
	}

	new bool:vehicle_created = false;
	for(new i = 0; i < MAX_CREATED_VEHICLE_PER_PLAYER; i++)
	{
		if(IsPlayerInVehicle(playerid, gplCreatedVehicle[playerid][i]))
		{
			vehicle_created = true;
			DestroyVehicle(gplCreatedVehicle[playerid][i]);
			gplCreatedVehicle[playerid][i] = CreateVehicle(idx, x, y, z, a, color1, color2, -1);
			SetVehicleVirtualWorld(gplCreatedVehicle[playerid][i], GetPlayerVirtualWorld(playerid));
			LinkVehicleToInterior(gplCreatedVehicle[playerid][i], GetPlayerInterior(playerid));
			PutPlayerInVehicle(playerid, gplCreatedVehicle[playerid][i], 0);
			SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You created a %s.", GetVehicleName(gplCreatedVehicle[playerid][i]));
			ShowPlayerVehicleName(playerid);
			break;
		}
	}

	if(!vehicle_created)
	{
		for(new i = 0; i < MAX_CREATED_VEHICLE_PER_PLAYER; i++)
		{
			if(!gplCreatedVehicle[playerid][i])
			{
				vehicle_created = true;
				gplCreatedVehicle[playerid][i] = CreateVehicle(idx, x, y, z, a, color1, color2, -1);
				SetVehicleVirtualWorld(gplCreatedVehicle[playerid][i], GetPlayerVirtualWorld(playerid));
				LinkVehicleToInterior(gplCreatedVehicle[playerid][i], GetPlayerInterior(playerid));
				PutPlayerInVehicle(playerid, gplCreatedVehicle[playerid][i], 0);
				SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You created a %s.", GetVehicleName(gplCreatedVehicle[playerid][i]));
				break;
			}
		}
	}

	if(!vehicle_created)
	{
		vehicle_created = true;
		new vehicleid = random(MAX_CREATED_VEHICLE_PER_PLAYER);
		DestroyVehicle(gplCreatedVehicle[playerid][vehicleid]);
		gplCreatedVehicle[playerid][vehicleid] = CreateVehicle(idx, x, y, z, a, color1, color2, -1);
		SetVehicleVirtualWorld(gplCreatedVehicle[playerid][vehicleid], GetPlayerVirtualWorld(playerid));
		LinkVehicleToInterior(gplCreatedVehicle[playerid][vehicleid], GetPlayerInterior(playerid));
		PutPlayerInVehicle(playerid, gplCreatedVehicle[playerid][vehicleid], 0);
		SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You created a %s.", GetVehicleName(gplCreatedVehicle[playerid][vehicleid]));
		SendClientMessage(playerid, COLOR_WARNING, "* You reached the vehicle limit per player, one of your old vehicles was destroyed.");
	}

	return 1;
}

hook OnPlayerModelSelection(playerid, response, listid, modelid)
{
	if(listid == Airplanes || listid == Bikes || listid == Boats || listid == Convertible || listid == Helicopters || listid == Industrials || listid == Lowrider || listid == OffRoad || listid == PublicService || listid == RC || listid == Saloon || listid == Sports || listid == StationWagon || listid == Trailer || listid == Unique)
    {
        if(response)
        {
			new command[140];
			PlayBuySound(playerid);
			format(command, sizeof(command), "/car %s", GetVehicleNameFromModel(modelid));
			CallRemoteFunction("OnPlayerCommandText", "is", playerid, command);
        }
        else
		{
			PlayCancelSound(playerid);
		}
    }
	return 1;
}

//------------------------------------------------------------------------------

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_ADMIN_REPORT:
		{
			if(!response)
				PlayCancelSound(playerid);
			else
			{
				if(strlen(inputtext) < 1)
				{
					CallRemoteFunction("OnPlayerCommandText", "is", playerid, "/admins");
				}
				else
				{
					new command[140];
					PlaySelectSound(playerid);
					format(command, sizeof(command), "/report %s", inputtext);
					CallRemoteFunction("OnPlayerCommandText", "is", playerid, command);
				}
			}
		}
		case DIALOG_VEHICLE_LIST:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
			}
			else
			{
				PlaySelectSound(playerid);
				switch(listitem)
				{
					case 0:
						ShowModelSelectionMenu(playerid, Airplanes, ConvertToGameText("Planes"));
					case 1:
						ShowModelSelectionMenu(playerid, Bikes, "Bikes");
					case 2:
						ShowModelSelectionMenu(playerid, Boats, "Boat");
					case 3:
						ShowModelSelectionMenu(playerid, Convertible, "Convertible");
					case 4:
						ShowModelSelectionMenu(playerid, Helicopters, "Helicopter");
					case 5:
						ShowModelSelectionMenu(playerid, Industrials, "Industriais");
					case 6:
						ShowModelSelectionMenu(playerid, Lowrider, "Lowrider");
					case 7:
						ShowModelSelectionMenu(playerid, OffRoad, "Off-Road");
					case 8:
						ShowModelSelectionMenu(playerid, PublicService, ConvertToGameText("Public service"));
					case 9:
						ShowModelSelectionMenu(playerid, RC, "RC");
					case 10:
						ShowModelSelectionMenu(playerid, Saloon, "Sedans");
					case 11:
						ShowModelSelectionMenu(playerid, Sports, "Sports");
					case 12:
						ShowModelSelectionMenu(playerid, StationWagon, "Caminhonetes");
					case 13:
						ShowModelSelectionMenu(playerid, Trailer, "Trailers");
					case 14:
						ShowModelSelectionMenu(playerid, Unique, "Unique");
				}
			}
			return -2;
		}
		case DIALOG_FIGHTING_LIST:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
			}
			else
			{
				PlayConfirmSound(playerid);
				switch (listitem)
				{
					case 0:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_NORMAL);
					case 1:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
					case 2:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU);
					case 3:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);
					case 4:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
					case 5:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_ELBOW);
				}
			}
			return -2;
		}
	}
	return 1;
}

//------------------------------------------------------------------------------

/*
		Error & Return type

	COMMAND_ZERO_RET	  = 0 , // The command returned 0.
	COMMAND_OK			= 1 , // Called corectly.
	COMMAND_UNDEFINED	 = 2 , // Command doesn't exist.
	COMMAND_DENIED		= 3 , // Can't use the command.
	COMMAND_HIDDEN		= 4 , // Can't use the command don't let them know it exists.
	COMMAND_NO_PLAYER	 = 6 , // Used by a player who shouldn't exist.
	COMMAND_DISABLED	  = 7 , // All commands are disabled for this player.
	COMMAND_BAD_PREFIX	= 8 , // Used "/" instead of "#", or something similar.
	COMMAND_INVALID_INPUT = 10, // Didn't type "/something".
*/

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success)
{
	if(!IsPlayerLogged(playerid))
	{
		SendClientMessage(playerid, COLOR_ERROR, "* You need to be logged in to use a command.");
		return COMMAND_DENIED;
	}
	else if(IsPlayerInTutorial(playerid))
    {
		PlayErrorSound(playerid);
        return COMMAND_DENIED;
    }
	else if(success != COMMAND_OK)
		SendClientMessage(playerid, COLOR_ERROR, "* This command does not exist. Look /cmds.");
	return COMMAND_OK;
}

//------------------------------------------------------------------------------

ptask OnPlayerAutoRepair[1250](playerid)
{
	if(gplAutoRepair[playerid] && IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(GetPlayerGamemode(playerid) != GAMEMODE_DERBY)
			RepairVehicle(GetPlayerVehicleID(playerid));
	}
}

//------------------------------------------------------------------------------

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	if(gplAutoRepair[playerid] && IsPlayerInVehicle(playerid, vehicleid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !gplDriftActive[playerid])
	{
		if(GetPlayerGamemode(playerid) != GAMEMODE_DERBY)
			RepairVehicle(GetPlayerVehicleID(playerid));
	}
	return 1;
}

timer CountDown[1000]()
{
	if(gCountDown == 0)
	{
		GameTextForAll("~g~GO!", 1000, 3);
		foreach(new i: Player)
			PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
	}
	else
	{
		new string[8];
		format(string, sizeof(string), "~r~%i", gCountDown);
		GameTextForAll(string, 1000, 3);
		foreach(new i: Player)
			PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0);

		gCountDown--;
		defer CountDown();
	}
}

//------------------------------------------------------------------------------

hook OnPlayerDisconnect(playerid, reason)
{
	for(new i = 0; i < MAX_CREATED_VEHICLE_PER_PLAYER; i++)
	{
		if(gplCreatedVehicle[playerid][i])
		{
			DestroyVehicle(gplCreatedVehicle[playerid][i]);
			gplCreatedVehicle[playerid][i] = 0;
		}
	}
	gplAutoRepair[playerid]		= false;
	gplHideNameTags[playerid]	= false;
	gplGotoBlocked[playerid]	= false;
	gplDriftActive[playerid]	= true;
	gplDriftCounter[playerid]	= 0;
	return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerStreamIn(playerid, forplayerid)
{
	if(gplHideNameTags[forplayerid])
	{
		ShowPlayerNameTagForPlayer(forplayerid, playerid, false);
	}
	return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(newkeys & KEY_FIRE)
	    {
			AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
	    }
	}
    return 1;
}

//------------------------------------------------------------------------------

ShowPlayerCredits(playerid)
{
	ShowPlayerDialog(playerid, DIALOG_CREDITS, DIALOG_STYLE_MSGBOX, "{59c72c}LF - {FFFFFF}Credits",
	"{59c72c}Legacy {59c72c}Freeroam{ffffff}\n{ffffff}Developed by the team {59c72c}L{ffffff}:{59c72c}F\n\n\
	{ffffff}Contributing:\nY_Less, Incognito, BlueG, PawnHunter, NexiusTailer, SA-MP Team, You", "X", "");
}

//------------------------------------------------------------------------------

public OnCheckVipKey(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields, gMySQL);
	if(!rows)
	{
        PlayErrorSound(playerid);
		SendClientMessage(playerid, COLOR_ERROR, "* This key does not exist.");
	}
    else
    {
		if(cache_get_field_content_int(0, "used", gMySQL) != 0)
		{
			PlayErrorSound(playerid);
			SendClientMessage(playerid, COLOR_ERROR, "* This key has already been used.");
		}
		else
		{
			new days = cache_get_field_content_int(0, "days", gMySQL);
			SetPlayerVIP(playerid, gettime() + (86400 * days));
			PlayerPlaySound(playerid, 5203, 0.0, 0.0, 0.0);
			SendClientMessagef(playerid, COLOR_SUCCESS, "* Your VIP account was activated bydaysdias!", days);

			new query[64];
	    	mysql_format(gMySQL, query, sizeof(query), "UPDATE `vip_keys` SET `used`=1 WHERE `id`=%d", cache_get_field_content_int(0, "id", gMySQL));
	    	mysql_pquery(gMySQL, query);
		}
    }
	return 1;
}

//------------------------------------------------------------------------------

TogglePlayerAutoRepair(playerid, toggle)
{
	gplAutoRepair[playerid] = toggle;
}

GetPlayerAutoRepairState(playerid)
{
	return gplAutoRepair[playerid];
}

TogglePlayerNameTags(playerid, toggle)
{
	gplHideNameTags[playerid] = toggle;
}

GetPlayerNameTagsState(playerid)
{
	return gplHideNameTags[playerid];
}

TogglePlayerGoto(playerid, toggle)
{
	gplGotoBlocked[playerid] = toggle;
}

GetPlayerGotoState(playerid)
{
	return gplGotoBlocked[playerid];
}

TogglePlayerDrift(playerid, toggle)
{
	gplDriftActive[playerid] = toggle;
}

GetPlayerDriftState(playerid)
{
	return gplDriftActive[playerid];
}

TogglePlayerDriftCounter(playerid, toggle)
{
	gplDriftCounter[playerid] = toggle;
}

GetPlayerDriftCounter(playerid)
{
	return gplDriftCounter[playerid];
}
