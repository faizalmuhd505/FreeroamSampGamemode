/*******************************************************************************
* NOME DO ARQUIVO :        modules/admin/commands.pwn
*
* DESCRIÇÃO :
*       Comandos apenas usados por administradores.
*
* NOTAS :
*       -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

static bool:gAdminDuty[MAX_PLAYERS] = {true, ...};

forward OnDeleteAccount(playerid);

enum e_survey_data
{
    e_survey_question[128],
    e_survey_yes,
    e_survey_no,
    e_survey_active
}
static gSurveyData[e_survey_data];

//------------------------------------------------------------------------------

// Recomendável manter a lista em até 10 linhas, para melhor visualização
YCMD:acmds(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
 		return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new output[2088];
	if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_RECRUIT)
    {
        strcat(output, "{229f09}Level 1\n{FFFFFF}/toplay - /onduty - /service - /infoplayer - /checkip - /ann - /unlockallcar - /kickar\n");
        strcat(output, "/slap - /spec - /specoff - /texto - /a - /particular - /players - /contagem - /ccall\n");
        strcat(output, "/tarik - /setskin - /gotopos - /pdist - /say - /fakekick\n\n");
    }

	if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_HELPER)
    {
        strcat(output, "{229f09}Level 2\n{FFFFFF}/banir - /setarinterior - /setarvw - /advertir - /jetpack - /sethp - /setarmor - /freeze - /unfreeze\n");
        strcat(output, "/giveweapon - /disweapon - /respawnallcar - /destroyveh - /calar - /descalar - /forcedrive - /forcarskin - /tarikall - /moveplayer\n");
        strcat(output, "/fakeban\n\n");
    }

	if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_MODERATOR)
    {
        strcat(output, "{229f09}Level 3\n{FFFFFF}/respawncar - /gotocar - /tarikcar - /timeall - /weatherall - /ejectplayer - /setarpos - /setpoint - /setpos\n");
        strcat(output, "/banip - /unbanip - /crash - /setpcolor - /setplayername - /setarskin - /godmode - /survey - /explode\n\n");
    }

	if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        strcat(output, "{229f09}Level 4\n{FFFFFF}/restartserver - /criarcorrida - /deletarcorrida - /criardm - /deletardm - /criarevento - /setmoney - /setbankmoney - /setvip\n");
        strcat(output, "/disweaponall - /fakechat - /invisible - /visible - /setintall - /freezeall - /unfreezeall - /ips - /killall\n");
        strcat(output, "/darvip - /removevip - /deleteacc - /kickall - /gerarchavevip\n\n");
    }

	if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_OWNER)
    {
        strcat(output, "{229f09}Level 5\n{FFFFFF}/setadmin - /lockserver - /unlockserver - /setgmtext - /sethostname - /setmapname - /setgravity\n");
        strcat(output, "/abuildingcmds");
    }

    ShowPlayerDialog(playerid, DIALOG_ADMIN_COMMANDS, DIALOG_STYLE_MSGBOX, "{59c72c}LF - {FFFFFF}Comandos administrativos", output, "X", "");
	return 1;
}

/*


RRRRRRRRRRRRRRRRR   EEEEEEEEEEEEEEEEEEEEEE       CCCCCCCCCCCCCRRRRRRRRRRRRRRRRR   UUUUUUUU     UUUUUUUUIIIIIIIIIITTTTTTTTTTTTTTTTTTTTTTT
R::::::::::::::::R  E::::::::::::::::::::E    CCC::::::::::::CR::::::::::::::::R  U::::::U     U::::::UI::::::::IT:::::::::::::::::::::T
R::::::RRRRRR:::::R E::::::::::::::::::::E  CC:::::::::::::::CR::::::RRRRRR:::::R U::::::U     U::::::UI::::::::IT:::::::::::::::::::::T
RR:::::R     R:::::REE::::::EEEEEEEEE::::E C:::::CCCCCCCC::::CRR:::::R     R:::::RUU:::::U     U:::::UUII::::::IIT:::::TT:::::::TT:::::T
R::::R     R:::::R  E:::::E       EEEEEEC:::::C       CCCCCC  R::::R     R:::::R U:::::U     U:::::U   I::::I  TTTTTT  T:::::T  TTTTTT
R::::R     R:::::R  E:::::E            C:::::C                R::::R     R:::::R U:::::D     D:::::U   I::::I          T:::::T
R::::RRRRRR:::::R   E::::::EEEEEEEEEE  C:::::C                R::::RRRRRR:::::R  U:::::D     D:::::U   I::::I          T:::::T
R:::::::::::::RR    E:::::::::::::::E  C:::::C                R:::::::::::::RR   U:::::D     D:::::U   I::::I          T:::::T
R::::RRRRRR:::::R   E:::::::::::::::E  C:::::C                R::::RRRRRR:::::R  U:::::D     D:::::U   I::::I          T:::::T
R::::R     R:::::R  E::::::EEEEEEEEEE  C:::::C                R::::R     R:::::R U:::::D     D:::::U   I::::I          T:::::T
R::::R     R:::::R  E:::::E            C:::::C                R::::R     R:::::R U:::::D     D:::::U   I::::I          T:::::T
R::::R     R:::::R  E:::::E       EEEEEEC:::::C       CCCCCC  R::::R     R:::::R U::::::U   U::::::U   I::::I          T:::::T
RR:::::R     R:::::REE::::::EEEEEEEE:::::E C:::::CCCCCCCC::::CRR:::::R     R:::::R U:::::::UUU:::::::U II::::::II      TT:::::::TT
R::::::R     R:::::RE::::::::::::::::::::E  CC:::::::::::::::CR::::::R     R:::::R  UU:::::::::::::UU  I::::::::I      T:::::::::T
R::::::R     R:::::RE::::::::::::::::::::E    CCC::::::::::::CR::::::R     R:::::R    UU:::::::::UU    I::::::::I      T:::::::::T
RRRRRRRR     RRRRRRREEEEEEEEEEEEEEEEEEEEEE       CCCCCCCCCCCCCRRRRRRRR     RRRRRRR      UUUUUUUUU      IIIIIIIIII      TTTTTTTTTTT

*/

//------------------------------------------------------------------------------

YCMD:ccall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    foreach(new i: Player)
    {
        if(IsPlayerLogged(i))
        {
            ClearPlayerScreen(i);
        }
    }
    SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* The administrator %s cleaned the chat.", GetPlayerNamef(playerid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:players(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new count = 0;
    foreach(new i: Player)
    {
        count++;
    }
    SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* Players Online: %d / %d", count, GetMaxPlayers());
    return 1;
}

//------------------------------------------------------------------------------

YCMD:toplay(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    gAdminDuty[playerid] = false;
    SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* The administrator %and is now playing.", GetPlayerNamef(playerid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:onduty(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    gAdminDuty[playerid] = true;
    SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* The administrator %and is now onduty.", GetPlayerNamef(playerid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:service(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    if(gAdminDuty[playerid])
    {
        CallRemoteFunction("OnPlayerCommandText", "is", playerid, "/toplay");
    }
    else
    {
        CallRemoteFunction("OnPlayerCommandText", "is", playerid, "/onduty");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:unlockallcar(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new engine, lights, alarm, doors, bonnet, boot, objective;
    for(new i = 0; i < MAX_VEHICLES; i++)
    {
        GetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(i, engine, lights, alarm, VEHICLE_PARAMS_OFF, bonnet, boot, objective);
    }
    SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* The administrator %s unlocked all vehicles.", GetPlayerNamef(playerid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:spec(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    else if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
        return SendClientMessage(playerid, COLOR_ERROR, "* You can only use this command in Freeroam.");

    new targetid;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_INFO, "* /spec [playerid]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(targetid == playerid)
        return SendClientMessage(playerid, COLOR_ERROR, "* You can't watch yourself.");

    TogglePlayerSpectating(playerid, true);
    SetPlayerSpecatateTarget(playerid, targetid);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:specoff(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    else if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
        return SendClientMessage(playerid, COLOR_ERROR, "* You are not watching.");

    else if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
        return SendClientMessage(playerid, COLOR_ERROR, "* You can only use this command in Freeroam.");

    TogglePlayerSpectating(playerid, false);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:texto(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new message[128];
    if(sscanf(params, "s[128]", message))
        return SendClientMessage(playerid, COLOR_INFO, "* /texto [texto]");

    new output[144];
    format(output, sizeof(output), "~y~%s: ~w~%s", GetPlayerNamef(playerid), message);
    GameTextForAll(output, 2000, 4);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:ann(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new message[128];
    if(sscanf(params, "s[128]", message))
        return SendClientMessage(playerid, COLOR_INFO, "* /ann [texto]");

    new output[144];
    format(output, sizeof(output), "Admin %s [level %d]: %s", GetPlayerNamef(playerid), GetPlayerAdminLevel(playerid), message);
    SendClientMessageToAll(COLOR_ADMIN_COMMAND, "________________________Administration Notice________________________");
    SendClientMessageToAll(COLOR_ADMIN_COMMAND, output);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:a(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new text[128];
    if(sscanf(params, "s[128]", text))
        return SendClientMessage(playerid, COLOR_INFO, "* /a [texto]");

    new output[144];
    format(output, 144, "@ [{%06x}%s{ededed}] %s: {e3e3e3}%s", GetPlayerRankColor(playerid) >>> 8, GetPlayerAdminRankName(playerid, true), GetPlayerNamef(playerid), text);
    SendAdminMessage(PLAYER_RANK_RECRUIT, 0xedededff, output);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:checkip(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_INFO, "* /checkip [playerid]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    new ip[16];
    GetPlayerIp(targetid, ip, 16);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* (ID: %i)%s - %s.", targetid, GetPlayerNamef(targetid), ip);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:slap(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_INFO, "* /slap [playerid]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "*The player is not connected.");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(targetid, x, y, z);
    SetPlayerPos(targetid, x, y, z + 2.5);
    PlayerPlaySound(targetid, 1190, 0.0, 0.0, 0.0);

    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You slapped %s.", GetPlayerNamef(targetid));
    SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s slapped you.", GetPlayerNamef(playerid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:infoplayer(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_INFO, "* /infoplayer [playerid]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not logged in.");

    new output[512], string[128], ip[16];
    GetPlayerIp(targetid, ip, 16);
    format(string, sizeof(string), "{FFFFFF}Name: {11D41E}%s{FFFFFF}\n\n{11D41E}Cash:{FFFFFF} $%d\n{11D41E}Bank:{FFFFFF} $%d\n{11D41E}Admin Level:{FFFFFF} %d\n{11D41E}Muted:{FFFFFF} %s\n", GetPlayerNamef(targetid), GetPlayerCash(targetid), GetPlayerBankCash(targetid), GetPlayerAdminLevel(targetid), (IsPlayerMuted(targetid)) , "Sim" , "Não");
    strcat(output, string);

    format(string, sizeof(string), "{11D41E}WARNINGS:{FFFFFF} %d \n{11D41E}IP:{FFFFFF} %s", GetPlayerWarning(targetid), ip);
    strcat(output, string);

    ShowPlayerDialog(playerid, DIALOG_INFO_PLAYER, DIALOG_STYLE_MSGBOX, "{59c72c}LF - {FFFFFF}Player Information", output, "X", "");
    return 1;
}

//------------------------------------------------------------------------------

YCMD:tarik(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_INFO, "* /tarik [playerid]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(targetid == playerid)
        return SendClientMessage(playerid, COLOR_ERROR, "* You can't pull yourself.");

    else if(GetPlayerGamemode(targetid) != GAMEMODE_FREEROAM)
        return SendClientMessage(playerid, COLOR_ERROR, "* This player is not in Freeroam mode.");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    SetPlayerInterior(targetid, GetPlayerInterior(playerid));
    SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
    if(GetPlayerState(targetid) != PLAYER_STATE_DRIVER) { SetPlayerPos(targetid, x, y, z); }
    else
    {
        new vehicleid = GetPlayerVehicleID(targetid);
        SetVehiclePos(vehicleid, x, y, z);
        LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));
        SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
    }

    SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s pulled you.", GetPlayerNamef(playerid));
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You pulled %s.", GetPlayerNamef(targetid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:say(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

   new message[128];
   if(sscanf(params, "s[128]", message))
       return SendClientMessage(playerid, COLOR_INFO, "* /say [message]");

   new output[144];
   format(output, sizeof(output), "* Admin %s: %s", GetPlayerNamef(playerid), message);
   SendClientMessageToAll(0x97e632ff, output);
   return 1;
}

//------------------------------------------------------------------------------

YCMD:gotopos(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new Float:x, Float:y, Float:z, i, w;
	if(sscanf(params, "fffI(0)I(0)", x, y, z, i, w))
		SendClientMessage(playerid, COLOR_INFO, "* /gotopos [float x] [float y] [float z] [interior<opcional>] [world<opcional>]");
	else
    {
		SetPlayerInterior(playerid, i);
		SetPlayerVirtualWorld(playerid, w);
		SetPlayerPos(playerid, x, y, z);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:pdist(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid;
    if(sscanf(params, "u", targetid))
        SendClientMessage(playerid, COLOR_INFO, "* /pdist [playerid]");
    else if(!IsPlayerLogged(targetid))
        SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");
	else
		SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You are at %.2F Units away from the player.", GetPlayerDistanceFromPlayer(playerid, targetid));
	return 1;
}

//------------------------------------------------------------------------------

YCMD:kick(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

   new targetid, reason[128];
   if(sscanf(params, "us[128]", targetid, reason))
       return SendClientMessage(playerid, COLOR_INFO, "* /kick [playerid] [reason]");

   else if(!IsPlayerLogged(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

   else if(playerid == targetid)
       return SendClientMessage(playerid, COLOR_ERROR, "* You can't Kick yourself.");

   else if(IsPlayerNPC(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* You can't Kick an NPC.");

   else if(GetPlayerAdminLevel(targetid) > PLAYER_RANK_RECRUIT)
       return SendClientMessage(playerid, COLOR_ERROR, "* You cannot kick a member of the Administration.");

   new output[144];
   format(output, sizeof(output), "* %s It was kicked by %s. Reason: %s", GetPlayerNamef(targetid), GetPlayerNamef(playerid), reason);
   SendClientMessageToAll(0xf26363ff, output);
   Kick(targetid);
   return 1;
}

//------------------------------------------------------------------------------

YCMD:fakekick(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_RECRUIT)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

   new targetid, reason[128];
   if(sscanf(params, "us[128]", targetid, reason))
       return SendClientMessage(playerid, COLOR_INFO, "* /fakekick [playerid] [reason]");

   else if(!IsPlayerLogged(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

   else if(playerid == targetid)
       return SendClientMessage(playerid, COLOR_ERROR, "* You can't FakeKick yourself.");

   else if(IsPlayerNPC(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* You can't FakeKick an NPC.");

   else if(GetPlayerAdminLevel(targetid) > PLAYER_RANK_RECRUIT)
       return SendClientMessage(playerid, COLOR_ERROR, "* VYou cannot be a member of the Administration.");

   new output[144];
   format(output, sizeof(output), "* %s Has Been Kick By %s. reason: %s", GetPlayerNamef(targetid), GetPlayerNamef(playerid), reason);
   SendClientMessageToAll(0xf26363ff, output);
   SendClientMessage(targetid, 0xA9C4E4FF, "Server closed the connection.");
   return 1;
}


/*


HHHHHHHHH     HHHHHHHHHEEEEEEEEEEEEEEEEEEEEEELLLLLLLLLLL             PPPPPPPPPPPPPPPPP   EEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR
H:::::::H     H:::::::HE::::::::::::::::::::EL:::::::::L             P::::::::::::::::P  E::::::::::::::::::::ER::::::::::::::::R
H:::::::H     H:::::::HE::::::::::::::::::::EL:::::::::L             P::::::PPPPPP:::::P E::::::::::::::::::::ER::::::RRRRRR:::::R
HH::::::H     H::::::HHEE::::::EEEEEEEEE::::ELL:::::::LL             PP:::::P     P:::::PEE::::::EEEEEEEEE::::ERR:::::R     R:::::R
H:::::H     H:::::H    E:::::E       EEEEEE  L:::::L                 P::::P     P:::::P  E:::::E       EEEEEE  R::::R     R:::::R
H:::::H     H:::::H    E:::::E               L:::::L                 P::::P     P:::::P  E:::::E               R::::R     R:::::R
H::::::HHHHH::::::H    E::::::EEEEEEEEEE     L:::::L                 P::::PPPPPP:::::P   E::::::EEEEEEEEEE     R::::RRRRRR:::::R
H:::::::::::::::::H    E:::::::::::::::E     L:::::L                 P:::::::::::::PP    E:::::::::::::::E     R:::::::::::::RR
H:::::::::::::::::H    E:::::::::::::::E     L:::::L                 P::::PPPPPPPPP      E:::::::::::::::E     R::::RRRRRR:::::R
H::::::HHHHH::::::H    E::::::EEEEEEEEEE     L:::::L                 P::::P              E::::::EEEEEEEEEE     R::::R     R:::::R
H:::::H     H:::::H    E:::::E               L:::::L                 P::::P              E:::::E               R::::R     R:::::R
H:::::H     H:::::H    E:::::E       EEEEEE  L:::::L         LLLLLL  P::::P              E:::::E       EEEEEE  R::::R     R:::::R
HH::::::H     H::::::HHEE::::::EEEEEEEE:::::ELL:::::::LLLLLLLLL:::::LPP::::::PP          EE::::::EEEEEEEE:::::ERR:::::R     R:::::R
H:::::::H     H:::::::HE::::::::::::::::::::EL::::::::::::::::::::::LP::::::::P          E::::::::::::::::::::ER::::::R     R:::::R
H:::::::H     H:::::::HE::::::::::::::::::::EL::::::::::::::::::::::LP::::::::P          E::::::::::::::::::::ER::::::R     R:::::R
HHHHHHHHH     HHHHHHHHHEEEEEEEEEEEEEEEEEEEEEELLLLLLLLLLLLLLLLLLLLLLLLPPPPPPPPPP          EEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR

*/

//------------------------------------------------------------------------------

YCMD:warning(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, reason[128];
    if(sscanf(params, "us[128]", targetid, reason))
        return SendClientMessage(playerid, COLOR_INFO, "* /warning [playerid] [reason]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(playerid == targetid)
        return SendClientMessage(playerid, COLOR_ERROR, "* You can't Ann yourself.");

    else if(IsPlayerNPC(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* You can't ann an NPC.");

    else if(GetPlayerAdminLevel(targetid) > PLAYER_RANK_RECRUIT)
        return SendClientMessage(playerid, COLOR_ERROR, "* You cannot Ann a member of the Administration.");

    if(GetPlayerWarning(targetid) == 2)
    {
        new output[144];
        format(output, sizeof(output), "* %s kicked by  %s. reason: 3 warnings.", GetPlayerNamef(targetid), GetPlayerNamef(playerid));
        SendClientMessageToAll(0xf26363ff, output);
        SetPlayerWarning(targetid, 0);
        Kick(targetid);
    }
    else
    {
        new output[144];
        format(output, sizeof(output), "* %s was warned by %s. reason: %s", GetPlayerNamef(targetid), GetPlayerNamef(playerid), reason);
        SendClientMessageToAll(0xf26363ff, output);
        SetPlayerWarning(targetid, GetPlayerWarning(targetid) + 1);
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:setskin(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, skinid;
    if(sscanf(params, "ui", targetid, skinid))
        return SendClientMessage(playerid, COLOR_INFO, "* /setskin [playerid] [skin]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(skinid < 0 || skinid > 311)
        return SendClientMessage(playerid, COLOR_ERROR, "* Invalid Skin.");

    SetPlayerSkin(targetid, skinid);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed your skin to %d.", GetPlayerNamef(playerid), skinid);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the skin of %s to %d.", GetPlayerNamef(targetid), skinid);
    SetSpawnInfo(targetid, 255, skinid, 1119.9399, -1618.7476, 20.5210, 91.8327, 0, 0, 0, 0, 0, 0);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:forcedrive(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, vehicleid;
    if(sscanf(params, "ui", targetid, vehicleid))
        return SendClientMessage(playerid, COLOR_INFO, "* /forcedrive [playerid] [veiculo]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s Forced you to drive the vehicle %d.", GetPlayerNamef(playerid), vehicleid);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You forced %s driving the vehicle %d.", GetPlayerNamef(targetid), vehicleid);
    PutPlayerInVehicle(targetid, vehicleid, 0);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:moveplayer(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, Float:x, Float:y, Float:z, int, world;
    if(sscanf(params, "ufffI(0)I(0)", targetid, x, y, z, int, world))
        return SendClientMessage(playerid, COLOR_INFO, "* /moveplayer [playerid] [x] [y] [z] [interior(optional)] [world(optional)]");

    if(playerid != targetid)
        SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* %s moved you to %.2f %.2f %.2f %i %i.", GetPlayerNamef(playerid), x, y, z, int, world);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You moved %s for %.2f %.2f %.2f %i %i.", GetPlayerNamef(targetid), x, y, z, int, world);

    SetPlayerInterior(targetid, int);
    SetPlayerVirtualWorld(targetid, world);
    SetPlayerPos(targetid, x, y, z);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:tarikall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    foreach(new i: Player)
    {
        if(i != playerid && GetPlayerGamemode(i) == GAMEMODE_FREEROAM)
            SetPlayerPos(i, x, y, z);
    }
    SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s brought all players.", GetPlayerNamef(playerid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:setint(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, interior;
    if(sscanf(params, "ui", targetid, interior))
        return SendClientMessage(playerid, COLOR_INFO, "* /setint [playerid] [interior]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(interior < 0)
        return SendClientMessage(playerid, COLOR_ERROR, "* Invalid interior.");

    SetPlayerInterior(targetid, interior);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed its interior to %d.", GetPlayerNamef(playerid), interior);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the interior of %s for %d.", GetPlayerNamef(targetid), interior);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:setvw(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, virtualworld;
    if(sscanf(params, "ui", targetid, virtualworld))
        return SendClientMessage(playerid, COLOR_INFO, "* /setvw [playerid] [interior]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(virtualworld < 0)
        return SendClientMessage(playerid, COLOR_ERROR, "* Virtual World Invalid.");

    SetPlayerVirtualWorld(targetid, virtualworld);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed your virtual world to %d.", GetPlayerNamef(playerid), virtualworld);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the virtual world of %s for %d.", GetPlayerNamef(targetid), virtualworld);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:jetpack(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:ban(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

   new targetid, expire, reason[128];
   if(sscanf(params, "uis[128]", targetid, expire, reason))
       return SendClientMessage(playerid, COLOR_INFO, "* /ban [playerid] [duração(dias) | -1 = permanente] [reason]");

   else if(!IsPlayerLogged(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

   else if(playerid == targetid)
       return SendClientMessage(playerid, COLOR_ERROR, "* You can't ban yourself.");

   else if(IsPlayerNPC(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* You cannot ban NPC.");

   else if(expire == 0)
       return SendClientMessage(playerid, COLOR_ERROR, "* Banity duration cannot be 0.");

   else if(expire < -1)
       return SendClientMessage(playerid, COLOR_ERROR, "* Banity duration cannot be less than -1.");

   else if(GetPlayerAdminLevel(targetid) > PLAYER_RANK_RECRUIT)
       return SendClientMessage(playerid, COLOR_ERROR, "* You cannot ban a member of the Administration.");

   new output[144];
   format(output, sizeof(output), "* %s has banned by %s. reason: %s", GetPlayerNamef(targetid), GetPlayerNamef(playerid), reason);
   SendClientMessageToAll(0xf26363ff, output);

   new query[300];
   mysql_format(gMySQL, query, sizeof(query), "INSERT INTO `bans` (`username`, `admin`, `created_at`, `expire`, `reason`) VALUES ('%e', '%e', %d, %d, '%e')", GetPlayerNamef(targetid), GetPlayerNamef(playerid), gettime(), (expire == -1) ? expire : (expire * 86400) + gettime(), reason);
   mysql_tquery(gMySQL, query);

   Ban(targetid);
   return 1;
}

//------------------------------------------------------------------------------

YCMD:fakeban(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

   new targetid, reason[128];
   if(sscanf(params, "us[128]", targetid, reason))
       return SendClientMessage(playerid, COLOR_INFO, "* /fakeban [playerid] [reason]");

   else if(!IsPlayerLogged(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

   else if(playerid == targetid)
       return SendClientMessage(playerid, COLOR_ERROR, "* You can't ban yourself.");

   else if(IsPlayerNPC(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* You cannot ban NPC.");

   else if(GetPlayerAdminLevel(targetid) > PLAYER_RANK_RECRUIT)
       return SendClientMessage(playerid, COLOR_ERROR, "* You cannot ban a member of the administration.");

   new output[144];
   format(output, sizeof(output), "* %s was banned by %s. reason: %s", GetPlayerNamef(targetid), GetPlayerNamef(playerid), reason);
   SendClientMessageToAll(0xf26363ff, output);

   SendClientMessage(targetid, 0xA9C4E4FF, "Server closed the connection.");
   return 1;
}

//------------------------------------------------------------------------------

YCMD:freeze(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_INFO, "* /freeze [playerid]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    TogglePlayerControllable(targetid, false);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s Freezed you.", GetPlayerNamef(playerid));
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* VYou froze %s.", GetPlayerNamef(targetid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:unfreeze(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_INFO, "* /unfreeze [playerid]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    TogglePlayerControllable(targetid, true);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s Unfreeze You.", GetPlayerNamef(playerid));
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You Unfreeze %s.", GetPlayerNamef(targetid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:sethp(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, Float:health;
    if(sscanf(params, "uf", targetid, health))
        return SendClientMessage(playerid, COLOR_INFO, "* /sethp [playerid] [valor]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    SetPlayerHealth(targetid, health);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed your HP to %.2f.", GetPlayerNamef(playerid), health);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the HP of %s for %.2f.", GetPlayerNamef(targetid), health);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:setarmor(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, Float:armour;
    if(sscanf(params, "uf", targetid, armour))
        return SendClientMessage(playerid, COLOR_INFO, "* /setarmor [playerid] [valor]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    SetPlayerArmour(targetid, armour);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed your armor to %.2f.", GetPlayerNamef(playerid), armour);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the armor %s for %.2f.", GetPlayerNamef(targetid), armour);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:giveweapon(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

   new targetid, weaponid, ammo;
   if(sscanf(params, "uii", targetid, weaponid, ammo))
       return SendClientMessage(playerid, COLOR_INFO, "* /giveweapon [playerid] [weapon] [ammunition]");

   else if(!IsPlayerLogged(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

   else if(weaponid < 0 || weaponid > 46)
       return SendClientMessage(playerid, COLOR_ERROR, "* Invalid weapon.");

   else if(ammo < 1)
       return SendClientMessage(playerid, COLOR_ERROR, "* Invalid ammunition.");

   new weaponname[32];
   GivePlayerWeapon(targetid, weaponid, ammo);
   GetWeaponName(weaponid, weaponname, sizeof(weaponname));
   if(playerid != targetid)
       SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s Gave one %scomm %d Bullets for you.", GetPlayerNamef(playerid), weaponname, ammo);
   SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You gave a %s com %d bullets for %s.", weaponname, ammo, GetPlayerNamef(targetid));
   return 1;
}

//------------------------------------------------------------------------------

YCMD:disweapon(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

   new targetid;
   if(sscanf(params, "u", targetid))
       return SendClientMessage(playerid, COLOR_INFO, "* /disweapon [playerid]");

   else if(!IsPlayerLogged(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

   if(playerid != targetid)
       SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s disarmed you.", GetPlayerNamef(playerid));
   SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You disarmed %s.", GetPlayerNamef(targetid));
   ResetPlayerWeapons(targetid);
   return 1;
}

//------------------------------------------------------------------------------

YCMD:muted(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_INFO, "* /muted [playerid]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(IsPlayerMuted(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is already mutated.");

    TogglePlayerMute(targetid, true);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s Muted You.", GetPlayerNamef(playerid));
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You Muted %s.", GetPlayerNamef(targetid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:desmuted(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid;
    if(sscanf(params, "u", targetid))
        return SendClientMessage(playerid, COLOR_INFO, "* /desmuted [playerid]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(!IsPlayerMuted(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not mutated.");

    TogglePlayerMute(targetid, false);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s desmuted you.", GetPlayerNamef(playerid));
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You desmuted %s.", GetPlayerNamef(targetid));
    return 1;
}

//------------------------------------------------------------------------------

YCMD:destroyveh(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
   {
       SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
   }
   else
   {
       new vehicleid;
       if(IsPlayerInAnyVehicle(playerid))
       {
           vehicleid = GetPlayerVehicleID(playerid);
       }
       else if(sscanf(params, "i", vehicleid))
       {
           SendClientMessage(playerid, COLOR_INFO, "* /destroyveh [vehicleid]");
       }
       SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You destroyed the ID vehicle %s.", vehicleid);
       DestroyVehicle(vehicleid);
   }
   return 1;
}

//------------------------------------------------------------------------------

YCMD:respawnallcar(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_HELPER)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

   SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s gave respawnallcar in all vehicles.", GetPlayerNamef(playerid));
   for(new i = 0; i < MAX_VEHICLES; i++)
   {
       SetVehicleToRespawn(i);
   }
   return 1;
}

/*


MMMMMMMM               MMMMMMMM     OOOOOOOOO     DDDDDDDDDDDDD
M:::::::M             M:::::::M   OO:::::::::OO   D::::::::::::DDD
M::::::::M           M::::::::M OO:::::::::::::OO D:::::::::::::::DD
M:::::::::M         M:::::::::MO:::::::OOO:::::::ODDD:::::DDDDD:::::D
M::::::::::M       M::::::::::MO::::::O   O::::::O  D:::::D    D:::::D
M:::::::::::M     M:::::::::::MO:::::O     O:::::O  D:::::D     D:::::D
M:::::::M::::M   M::::M:::::::MO:::::O     O:::::O  D:::::D     D:::::D
M::::::M M::::M M::::M M::::::MO:::::O     O:::::O  D:::::D     D:::::D
M::::::M  M::::M::::M  M::::::MO:::::O     O:::::O  D:::::D     D:::::D
M::::::M   M:::::::M   M::::::MO:::::O     O:::::O  D:::::D     D:::::D
M::::::M    M:::::M    M::::::MO:::::O     O:::::O  D:::::D     D:::::D
M::::::M     MMMMM     M::::::MO::::::O   O::::::O  D:::::D    D:::::D
M::::::M               M::::::MO:::::::OOO:::::::ODDD:::::DDDDD:::::D
M::::::M               M::::::M OO:::::::::::::OO D:::::::::::::::DD
M::::::M               M::::::M   OO:::::::::OO   D::::::::::::DDD
MMMMMMMM               MMMMMMMM     OOOOOOOOO     DDDDDDDDDDDDD

*/

//------------------------------------------------------------------------------

YCMD:respawncar(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    else if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, COLOR_ERROR, "* You are not in a vehicle.");

	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	return 1;
}

//------------------------------------------------------------------------------

YCMD:explode(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new targetid;
	if(sscanf(params, "u", targetid))
		SendClientMessage(playerid, COLOR_INFO, "* /explode [playerid]");
	else
    {
		SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You exploded %s.", GetPlayerNamef(targetid));
		SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s exploded you.", GetPlayerNamef(playerid));

        new Float:x, Float:y, Float:z;
        GetPlayerPos(targetid, x, y, z);
        CreateExplosion(x, y, z, 2, 10.0);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:gotocar(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new vehicleid;
	if(sscanf(params, "i", vehicleid))
		SendClientMessage(playerid, COLOR_INFO, "* /gotocar [vehicleid id]");
    else if(GetVehicleModel(vehicleid) == 0)
		SendClientMessage(playerid, COLOR_ERROR, "* Vehicle does not exist.");
	else
    {
		SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You went to the vehicle %d.", vehicleid);

        new Float:x, Float:y, Float:z;
        GetVehiclePos(vehicleid, x, y, z);
        SetPlayerPos(playerid, x, y, z);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:tarikcar(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new vehicleid;
	if(sscanf(params, "i", vehicleid))
		SendClientMessage(playerid, COLOR_INFO, "* /tarikcar [veículo id]");
    else if(GetVehicleModel(vehicleid) == 0)
    	SendClientMessage(playerid, COLOR_ERROR, "* Vehicle does not exist.");
	else
    {
		SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You pulled the vehicle %d.", vehicleid);

        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        SetVehiclePos(vehicleid, x, y, z);
        LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));
        SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:timeall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new hour, minute;
	if(sscanf(params, "ii", hour, minute))
		SendClientMessage(playerid, COLOR_INFO, "* /timeall [hora] [minuto]");
    else if(hour < 0 || hour > 23)
    	SendClientMessage(playerid, COLOR_ERROR, "* Invalid hour.");
    else if(minute < 0 || minute > 59)
        SendClientMessage(playerid, COLOR_ERROR, "* Invalid minute.");
	else
    {
        SetWorldTime(hour);
        foreach(new i: Player)
        {
            SetPlayerTime(playerid, hour, minute);
        }
		SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s changed the server time to %02d:%02d.", GetPlayerNamef(playerid), hour, minute);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:weatherall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new weatherid;
	if(sscanf(params, "i", weatherid))
		SendClientMessage(playerid, COLOR_INFO, "* /weatherall [weather id]");
	else
    {
        SetWeather(weatherid);
		SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s changed the weather of the server to %d.", GetPlayerNamef(playerid), weatherid);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:ejectplayer(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new targetid;
	if(sscanf(params, "u", targetid))
		SendClientMessage(playerid, COLOR_INFO, "* /ejectplayer [playerid]");
	else
    {
        if(!IsPlayerInAnyVehicle(targetid))
        {
            SendClientMessage(playerid, COLOR_ERROR, "* The player is not in a vehicle.");
        }
        else
        {
            RemovePlayerFromVehicle(targetid);
            SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s removed you from the vehicle.", GetPlayerNamef(playerid));
            SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You were removed by %s from the vehicle.", GetPlayerNamef(targetid));
        }
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:setpoint(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new targetid, score;
	if(sscanf(params, "ui", targetid, score))
		SendClientMessage(playerid, COLOR_INFO, "* /setpoint [playerid] [points]");
	else
    {
        SetPlayerDriftPoints(playerid, score * 1000);
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed its points to %d.", GetPlayerNamef(playerid), score);
        SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the points of %s for %d.", GetPlayerNamef(targetid), score);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:banip(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new ip[16];
	if(sscanf(params, "s[16]", ip))
		SendClientMessage(playerid, COLOR_INFO, "* /banip [ip]");
	else
    {
        new rconcmd[64];
        format(rconcmd, sizeof(rconcmd), "banip %s", ip);
        SendRconCommand(rconcmd);
        SendRconCommand("reloadbans");

        SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You banned the IP: %s.", ip);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:unbanip(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new ip[16];
	if(sscanf(params, "s[16]", ip))
		SendClientMessage(playerid, COLOR_INFO, "* /unbanip [ip]");
	else
    {
        new rconcmd[64];
        format(rconcmd, sizeof(rconcmd), "unbanip %s", ip);
        SendRconCommand(rconcmd);
        SendRconCommand("reloadbans");

        SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You Unbanned IP: %s.", ip);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:crash(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new targetid, reason[128];
	if(sscanf(params, "us[128]", targetid, reason))
		SendClientMessage(playerid, COLOR_INFO, "* /crash [playerid] [reason]");
	else
    {
        SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "*Adm %s crash %s. reason: %s.", GetPlayerNamef(playerid), GetPlayerNamef(targetid), reason);
        GameTextForPlayer(targetid, "~k~~INVALID_KEY~", 5000, 5);
        SendClientMessage(targetid, -1, "");
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:setplayername(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new targetid, name[MAX_PLAYER_NAME];
	if(sscanf(params, "us[26]", targetid, name))
		SendClientMessage(playerid, COLOR_INFO, "* /setplayername [playerid] [name]");
	else
    {
        SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the name of %s for %s.", GetPlayerNamef(targetid), name);
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed your name to %s.", GetPlayerNamef(playerid), name);
        ChangePlayerName(targetid, name);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:setpcolor(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new targetid, color;
	if(sscanf(params, "ux", targetid, color))
		SendClientMessage(playerid, COLOR_INFO, "* /setpcolor [playerid] [cor]");
	else
    {
        SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the color of %s to {%06x}this.", GetPlayerNamef(targetid), color >>> 8);
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed its color to {%06x}this.", GetPlayerNamef(playerid), color >>> 8);
        SetPlayerColor(targetid, color);
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:godmode(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	SetPlayerHealth(playerid, 999999.0);
	return 1;
}

//------------------------------------------------------------------------------

YCMD:survey(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    else if(gSurveyData[e_survey_active])
        return SendClientMessage(playerid, COLOR_ERROR, "* A poll is already active.");

    new question[128];
	if(sscanf(params, "s[128]", question))
		SendClientMessage(playerid, COLOR_INFO, "* /survey [question]");
	else
    {
        gSurveyData[e_survey_active] = true;
        gSurveyData[e_survey_yes] = 0;
        gSurveyData[e_survey_no] = 0;
        format(gSurveyData[e_survey_question], sizeof(gSurveyData[e_survey_question]), question);

        SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* %s Created a poll!", GetPlayerNamef(playerid));
        SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* Question: %s", question);

        new output[356];
        format(output, sizeof(output), "{ffffff}Poll created by: %s.\nQuestion: %s", GetPlayerNamef(playerid), question);
        foreach(new i: Player)
        {
            if(IsPlayerLogged(i))
            {
                ShowPlayerDialog(i, DIALOG_SURVEY, DIALOG_STYLE_MSGBOX, question, output, "Yes", "No");
            }
        }

        defer EndSurvey();
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:setpos(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_MODERATOR)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

	new targetid;
	if(sscanf(params, "u", targetid))
		SendClientMessage(playerid, COLOR_INFO, "* /setpos [playerid]");
	else
    {
        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(targetid, x, y, z);
        GetPlayerFacingAngle(targetid, a);
        SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "*The player %s is in the coordinates: %.2f, %.2f, %.2f, %.2f, %i, %i.", GetPlayerNamef(targetid), x, y, z, a, GetPlayerInterior(targetid), GetPlayerVirtualWorld(targetid));
	}
	return 1;
}

/*


SSSSSSSSSSSSSSS UUUUUUUU     UUUUUUUUBBBBBBBBBBBBBBBBB             OOOOOOOOO     WWWWWWWW                           WWWWWWWWNNNNNNNN        NNNNNNNNEEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR
SS:::::::::::::::SU::::::U     U::::::UB::::::::::::::::B          OO:::::::::OO   W::::::W                           W::::::WN:::::::N       N::::::NE::::::::::::::::::::ER::::::::::::::::R
S:::::SSSSSS::::::SU::::::U     U::::::UB::::::BBBBBB:::::B       OO:::::::::::::OO W::::::W                           W::::::WN::::::::N      N::::::NE::::::::::::::::::::ER::::::RRRRRR:::::R
S:::::S     SSSSSSSUU:::::U     U:::::UUBB:::::B     B:::::B     O:::::::OOO:::::::OW::::::W                           W::::::WN:::::::::N     N::::::NEE::::::EEEEEEEEE::::ERR:::::R     R:::::R
S:::::S             U:::::U     U:::::U   B::::B     B:::::B     O::::::O   O::::::O W:::::W           WWWWW           W:::::W N::::::::::N    N::::::N  E:::::E       EEEEEE  R::::R     R:::::R
S:::::S             U:::::D     D:::::U   B::::B     B:::::B     O:::::O     O:::::O  W:::::W         W:::::W         W:::::W  N:::::::::::N   N::::::N  E:::::E               R::::R     R:::::R
S::::SSSS          U:::::D     D:::::U   B::::BBBBBB:::::B      O:::::O     O:::::O   W:::::W       W:::::::W       W:::::W   N:::::::N::::N  N::::::N  E::::::EEEEEEEEEE     R::::RRRRRR:::::R
SS::::::SSSSS     U:::::D     D:::::U   B:::::::::::::BB       O:::::O     O:::::O    W:::::W     W:::::::::W     W:::::W    N::::::N N::::N N::::::N  E:::::::::::::::E     R:::::::::::::RR
SSS::::::::SS   U:::::D     D:::::U   B::::BBBBBB:::::B      O:::::O     O:::::O     W:::::W   W:::::W:::::W   W:::::W     N::::::N  N::::N:::::::N  E:::::::::::::::E     R::::RRRRRR:::::R
SSSSSS::::S  U:::::D     D:::::U   B::::B     B:::::B     O:::::O     O:::::O      W:::::W W:::::W W:::::W W:::::W      N::::::N   N:::::::::::N  E::::::EEEEEEEEEE     R::::R     R:::::R
S:::::S U:::::D     D:::::U   B::::B     B:::::B     O:::::O     O:::::O       W:::::W:::::W   W:::::W:::::W       N::::::N    N::::::::::N  E:::::E               R::::R     R:::::R
S:::::S U::::::U   U::::::U   B::::B     B:::::B     O::::::O   O::::::O        W:::::::::W     W:::::::::W        N::::::N     N:::::::::N  E:::::E       EEEEEE  R::::R     R:::::R
SSSSSSS     S:::::S U:::::::UUU:::::::U BB:::::BBBBBB::::::B     O:::::::OOO:::::::O         W:::::::W       W:::::::W         N::::::N      N::::::::NEE::::::EEEEEEEE:::::ERR:::::R     R:::::R
S::::::SSSSSS:::::S  UU:::::::::::::UU  B:::::::::::::::::B       OO:::::::::::::OO           W:::::W         W:::::W          N::::::N       N:::::::NE::::::::::::::::::::ER::::::R     R:::::R
S:::::::::::::::SS     UU:::::::::UU    B::::::::::::::::B          OO:::::::::OO              W:::W           W:::W           N::::::N        N::::::NE::::::::::::::::::::ER::::::R     R:::::R
SSSSSSSSSSSSSSS         UUUUUUUUU      BBBBBBBBBBBBBBBBB             OOOOOOOOO                 WWW             WWW            NNNNNNNN         NNNNNNNEEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR


*/

//------------------------------------------------------------------------------

YCMD:restartserver(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_SUB_OWNER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    GameTextForAll("~b~~h~Restarting the server...", 15000, 3);
    foreach(new i: Player)
    {
        if(IsPlayerLogged(i))
        {
            ClearPlayerScreen(i);
            SavePlayerAccount(i);
            SetPlayerLogged(i, false);
        }
    }
    defer RestartGameMode();
    return 1;
}

//------------------------------------------------------------------------------

YCMD:setmoney(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_SUB_OWNER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, value;
    if(sscanf(params, "ui", targetid, value))
        return SendClientMessage(playerid, COLOR_INFO, "* /setmoney [playerid] [quantia]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(value < 0 || value > 2147483647)
        return SendClientMessage(playerid, COLOR_ERROR, "* Invalid value. (0 - 2.147.483.647)");

    SetPlayerCash(targetid, value);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed your money to $%d.", GetPlayerNamef(playerid), value);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the money from %s for $%d.", GetPlayerNamef(targetid), value);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:setbankmoney(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) < PLAYER_RANK_SUB_OWNER)
        return SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");

    new targetid, value;
    if(sscanf(params, "ui", targetid, value))
        return SendClientMessage(playerid, COLOR_INFO, "* /setbankmoney [playerid] [quantia]");

    else if(!IsPlayerLogged(targetid))
        return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

    else if(value < 0 || value > 2147483647)
        return SendClientMessage(playerid, COLOR_ERROR, "* Invalid value. (0 - 2.147.483.647)");

    SetPlayerBankCash(targetid, value);
    if(playerid != targetid)
        SendClientMessagef(targetid, COLOR_ADMIN_COMMAND, "* %s changed your bank money to $%d.", GetPlayerNamef(playerid), value);
    SendClientMessagef(playerid, COLOR_ADMIN_COMMAND, "* You changed the money from the %s for $%d.", GetPlayerNamef(targetid), value);
    return 1;
}

//------------------------------------------------------------------------------

YCMD:setvip(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        new targetid, days;
        if(sscanf(params, "ui", targetid, days))
            return SendClientMessage(playerid, COLOR_INFO, "* /setvip [playerid] [dias]");

        else if(!IsPlayerLogged(targetid))
            return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

        else if(days < 0)
            return SendClientMessage(playerid, COLOR_ERROR, "* Invalid value.");

        SetPlayerVIP(targetid, gettime() + (days * 86400));
        if(playerid != targetid)
        {
            if(!days)
                SendClientMessagef(targetid, COLOR_PLAYER_COMMAND, "* %s removed its VIP.", GetPlayerNamef(playerid));
            else
                SendClientMessagef(targetid, COLOR_PLAYER_COMMAND, "* %s activated your vip for %d days.", GetPlayerNamef(playerid), days);
        }

        if(!days)
            SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You removed the VIP from %s.", GetPlayerNamef(targetid));
        else
        {
            PlayerPlaySound(targetid, 5203, 0.0, 0.0, 0.0);
            SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You activated VIP from %s by %d days.", GetPlayerNamef(targetid), days);
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:removevip(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        new targetid;
        if(sscanf(params, "u", targetid))
            return SendClientMessage(playerid, COLOR_INFO, "* /removevip [playerid]");

        else if(!IsPlayerLogged(targetid))
            return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

        if(playerid != targetid)
        {
            SendClientMessagef(targetid, COLOR_PLAYER_COMMAND, "* %s Removed your VIP.", GetPlayerNamef(playerid));
        }

        SetPlayerVIP(targetid, 0);
        SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You removed the VIP from %s.", GetPlayerNamef(targetid));
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:deleteacc(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        new userName[MAX_PLAYER_NAME];
        if(sscanf(params, "s[26]", userName))
            return SendClientMessage(playerid, COLOR_INFO, "* /deleteacc [username]");

        new playerName[MAX_PLAYER_NAME];
        foreach(new i: Player)
        {
            GetPlayerName(i, playerName, MAX_PLAYER_NAME);
            if(!strcmp(playerName, userName))
            {
                Kick(i);
            }
        }

        new query[64];
        mysql_format(gMySQL, query, sizeof(query), "DELETE FROM `users` WHERE `name`='%e'", userName);
        mysql_tquery(gMySQL, query, "OnDeleteAccount", "i", playerid);
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:gerarchavevip(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        PlaySelectSound(playerid);
        ShowPlayerDialog(playerid, DIALOG_GENERATE_VIP_KEY, DIALOG_STYLE_LIST, "Generate VIP Key", "Days\nType\nGenerate", "Select", "X");
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:kickall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s Kickou all players on the server.", GetPlayerNamef(playerid));
        foreach(new i: Player)
        {
            if(GetPlayerAdminLevel(i) < 1)
                Kick(i);
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:disweaponall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s disarmed everyone.", GetPlayerNamef(playerid));
        foreach(new i: Player)
        {
            ResetPlayerWeapons(i);
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:fakechat(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        new targetid, text[128];
        if(sscanf(params, "us[128]", targetid, text))
            return SendClientMessage(playerid, COLOR_INFO, "* /fakechat [playerid] [text]");

        new message[144];
        format(message, sizeof(message), "%s (%i): {ffffff}%s", GetPlayerNamef(targetid), targetid, text);

        if(GetPlayerAdminLevel(targetid) >= PLAYER_RANK_RECRUIT)
        {
            new rankName[14];
            format(rankName, 14, "[%s] ", GetPlayerAdminRankName(targetid, true));
            strins(message, rankName, 0);
        }
        else if(IsPlayerVIP(targetid))
        {
            strins(message, "[VIP] ", 0);
        }

        foreach(new i: Player)
        {
            if(GetPlayerGamemode(i) != GAMEMODE_LOBBY)
            {
                SendClientMessage(i, GetPlayerColor(targetid), message);
            }
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:setintall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        new interior;
        if(sscanf(params, "i", interior))
            return SendClientMessage(playerid, COLOR_INFO, "* /setintall [interior]");

        SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s changed the interior of all to %d.", GetPlayerNamef(playerid), interior);
        foreach(new i: Player)
        {
            if(GetPlayerGamemode(i) == GAMEMODE_LOBBY)
            {
                SetPlayerInterior(i, interior);
            }
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:killall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s killed all.", GetPlayerNamef(playerid));
        foreach(new i: Player)
        {
            if(GetPlayerGamemode(i) == GAMEMODE_LOBBY && i != playerid)
            {
                SetPlayerHealth(i, 0.0);
            }
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:freezeall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s Freezed all.", GetPlayerNamef(playerid));
        foreach(new i: Player)
        {
            if(GetPlayerGamemode(i) == GAMEMODE_LOBBY && i != playerid)
            {
                TogglePlayerControllable(i, false);
            }
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:unfreezeall(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s UnFreezed all.", GetPlayerNamef(playerid));
        foreach(new i: Player)
        {
            if(GetPlayerGamemode(i) == GAMEMODE_LOBBY)
            {
                TogglePlayerControllable(i, true);
            }
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:ips(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        new output[4096], ip[16], string[48];
        strcat(output, "Nome\tIP\n");
        foreach(new i: Player)
        {
            GetPlayerIp(i, ip, 16);
            format(string, sizeof(string), "%s\t%s\n", GetPlayerNamef(i), ip);
            strcat(output, string);
        }
        ShowPlayerDialog(playerid, DIALOG_PLAYERS_IP, DIALOG_STYLE_TABLIST_HEADERS, "Players IP", output, "X", "");
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:invisible(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
            return SendClientMessage(playerid, COLOR_ERROR, "* You need to be at Freeroam.");
        SendClientMessage(playerid, COLOR_ADMIN_COMMAND, "* You are invisible, use /visible to return.");
        SetPlayerVirtualWorld(playerid, 8976);
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:visible(playerid, params[], help)
{
    if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
    {
        if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
            return SendClientMessage(playerid, COLOR_ERROR, "* You need to be at Freeroam.");
        SendClientMessage(playerid, COLOR_ADMIN_COMMAND, "* You have been visible again.");
        SetPlayerVirtualWorld(playerid, 0);
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
    }
    return 1;
}

/*
OOOOOOOOO     WWWWWWWW                           WWWWWWWWNNNNNNNN        NNNNNNNNEEEEEEEEEEEEEEEEEEEEEERRRRRRRRRRRRRRRRR
OO:::::::::OO   W::::::W                           W::::::WN:::::::N       N::::::NE::::::::::::::::::::ER::::::::::::::::R
OO:::::::::::::OO W::::::W                           W::::::WN::::::::N      N::::::NE::::::::::::::::::::ER::::::RRRRRR:::::R
O:::::::OOO:::::::OW::::::W                           W::::::WN:::::::::N     N::::::NEE::::::EEEEEEEEE::::ERR:::::R     R:::::R
O::::::O   O::::::O W:::::W           WWWWW           W:::::W N::::::::::N    N::::::N  E:::::E       EEEEEE  R::::R     R:::::R
O:::::O     O:::::O  W:::::W         W:::::W         W:::::W  N:::::::::::N   N::::::N  E:::::E               R::::R     R:::::R
O:::::O     O:::::O   W:::::W       W:::::::W       W:::::W   N:::::::N::::N  N::::::N  E::::::EEEEEEEEEE     R::::RRRRRR:::::R
O:::::O     O:::::O    W:::::W     W:::::::::W     W:::::W    N::::::N N::::N N::::::N  E:::::::::::::::E     R:::::::::::::RR
O:::::O     O:::::O     W:::::W   W:::::W:::::W   W:::::W     N::::::N  N::::N:::::::N  E:::::::::::::::E     R::::RRRRRR:::::R
O:::::O     O:::::O      W:::::W W:::::W W:::::W W:::::W      N::::::N   N:::::::::::N  E::::::EEEEEEEEEE     R::::R     R:::::R
O:::::O     O:::::O       W:::::W:::::W   W:::::W:::::W       N::::::N    N::::::::::N  E:::::E               R::::R     R:::::R
O::::::O   O::::::O        W:::::::::W     W:::::::::W        N::::::N     N:::::::::N  E:::::E       EEEEEE  R::::R     R:::::R
O:::::::OOO:::::::O         W:::::::W       W:::::::W         N::::::N      N::::::::NEE::::::EEEEEEEE:::::ERR:::::R     R:::::R
OO:::::::::::::OO           W:::::W         W:::::W          N::::::N       N:::::::NE::::::::::::::::::::ER::::::R     R:::::R
OO:::::::::OO              W:::W           W:::W           N::::::N        N::::::NE::::::::::::::::::::ER::::::R     R:::::R
OOOOOOOOO                 WWW             WWW            NNNNNNNN         NNNNNNNEEEEEEEEEEEEEEEEEEEEEERRRRRRRR     RRRRRRR

*/

//------------------------------------------------------------------------------

YCMD:setadmin(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) == PLAYER_RANK_OWNER || IsPlayerAdmin(playerid))
   {
       new targetid, level;
       if(sscanf(params, "ui", targetid, level))
           return SendClientMessage(playerid, COLOR_INFO, "* /setadmin [playerid] [level]");

       else if(!IsPlayerLogged(targetid))
           return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

       else if(level < 0 || level > 5)
           return SendClientMessage(playerid, COLOR_ERROR, "* Invalid administrative level.");

       SetPlayerAdminLevel(targetid, level);
       if(playerid != targetid)
       {
           SendClientMessagef(targetid, COLOR_PLAYER_COMMAND, "* %s changed your administrative position to %s.", GetPlayerNamef(playerid), GetPlayerAdminRankName(targetid));
       }
       SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You changed the administrative position of %s for %s.", GetPlayerNamef(targetid), GetPlayerAdminRankName(targetid));
   }
   else
   {
       SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
   }
   return 1;
}

//------------------------------------------------------------------------------

YCMD:setgmtext(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) == PLAYER_RANK_OWNER)
   {
       new name[64];
       if(sscanf(params, "s[64]", name))
           return SendClientMessage(playerid, COLOR_INFO, "* /setgmtext [name]");

       SetGameModeText(name);
       SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s changed the name of the gamemode to %s.", GetPlayerNamef(playerid), name);
   }
   else
   {
       SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
   }
   return 1;
}

//------------------------------------------------------------------------------

YCMD:sethostname(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) == PLAYER_RANK_OWNER)
   {
       new name[64];
       if(sscanf(params, "s[64]", name))
           return SendClientMessage(playerid, COLOR_INFO, "* /sethostname [name]");

       new rconcmd[80];
       format(rconcmd, sizeof(rconcmd), "hostname %s", name);
       SendRconCommand(rconcmd);
       SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s changed the server name to %s.", GetPlayerNamef(playerid), name);
   }
   else
   {
       SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
   }
   return 1;
}

//------------------------------------------------------------------------------

YCMD:setmapname(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) == PLAYER_RANK_OWNER)
   {
       new name[64];
       if(sscanf(params, "s[64]", name))
           return SendClientMessage(playerid, COLOR_INFO, "* /setmapname [nome]");

       new rconcmd[80];
       format(rconcmd, sizeof(rconcmd), "mapname %s", name);
       SendRconCommand(rconcmd);
       SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s changed the name of the server map to %s.", GetPlayerNamef(playerid), name);
   }
   else
   {
       SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
   }
   return 1;
}

//------------------------------------------------------------------------------

YCMD:setgravity(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) == PLAYER_RANK_OWNER)
   {
       new Float:gravity;
       if(sscanf(params, "f", gravity))
           return SendClientMessage(playerid, COLOR_INFO, "* /setgravity [gravity]");

       SetGravity(gravity);
       SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s changed the gravity of the server to %.2f.", GetPlayerNamef(playerid), gravity);
   }
   else
   {
       SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
   }
   return 1;
}

//------------------------------------------------------------------------------

YCMD:lockserver(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) == PLAYER_RANK_OWNER)
   {
       new password[64];
       if(sscanf(params, "s[64]", password))
           return SendClientMessage(playerid, COLOR_INFO, "* /lockserver [password]");

       new rconcmd[80];
       format(rconcmd, sizeof(rconcmd), "password %s", password);
       SendRconCommand(rconcmd);
       SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s locked the server.", GetPlayerNamef(playerid));
   }
   else
   {
       SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
   }
   return 1;
}

//------------------------------------------------------------------------------

YCMD:unlockserver(playerid, params[], help)
{
   if(GetPlayerAdminLevel(playerid) == PLAYER_RANK_OWNER)
   {
       SendRconCommand("password 0");
       SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* %s locked the server.", GetPlayerNamef(playerid));
   }
   else
   {
       SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
   }
   return 1;
}

//------------------------------------------------------------------------------

hook OnGameModeInit()
{
	Command_AddAltNamed("tarik",        "tarik");
	Command_AddAltNamed("kick",         "kick");
	Command_AddAltNamed("ban",          "ban");
	Command_AddAltNamed("warning",      "warning");
	Command_AddAltNamed("pm",           "pm");
	Command_AddAltNamed("ann",          "ann");
	Command_AddAltNamed("setint",       "setarintersetintior");
	Command_AddAltNamed("setvw",        "setvw");
	Command_AddAltNamed("muted",        "muted");
	Command_AddAltNamed("desmuted",     "desmuted");
    Command_AddAltNamed("sethp",        "sethp");
	Command_AddAltNamed("setarmor",     "setarmour");
	Command_AddAltNamed("setskin",      "setskin");
	Command_AddAltNamed("setvip",       "setvip");
	Command_AddAltNamed("moveplayer",   "moveplayer");
	Command_AddAltNamed("setskin",      "setskin");
	return 1;
}

//------------------------------------------------------------------------------

public OnDeleteAccount(playerid)
{
    if(cache_affected_rows() > 0)
    {
        SendClientMessage(playerid, COLOR_SUCCESS, "* Successful deleted user.");
    }
    else
    {
        PlayErrorSound(playerid);
        SendClientMessage(playerid, COLOR_ERROR, "* User not found.");
    }
}

//------------------------------------------------------------------------------

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch (dialogid)
    {
        case DIALOG_SURVEY:
        {
            PlaySelectSound(playerid);
            if(response)
            {
                gSurveyData[e_survey_yes]++;
                SendClientMessage(playerid, COLOR_SUCCESS, "* You voted yes.");
            }
            else
            {
                gSurveyData[e_survey_no]++;
                SendClientMessage(playerid, COLOR_SUCCESS, "* You voted no.");
            }
        }
        case DIALOG_GENERATE_VIP_KEY:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                switch (listitem)
                {
                    case 0:
                        ShowPlayerDialog(playerid, DIALOG_GEN_VIP_KEY_DAYS, DIALOG_STYLE_INPUT, "Generate VIP Key: Days", "Enter how many days this VIP will last:", "Confirm", "Cancle");
                    case 1:
                        ShowPlayerDialog(playerid, DIALOG_GEN_VIP_KEY_TYPE, DIALOG_STYLE_LIST, "Generate VIP Key: Type", "Bronze\nSilver\nGold", "Confirm", "Cancle");
                    case 2:
                    {
                        if(GetPVarInt(playerid, "gen_vip_days") < 1)
                        {
                            PlayErrorSound(playerid);
                            SendClientMessage(playerid, COLOR_ERROR, "* You did not define the days.");
                            ShowPlayerDialog(playerid, DIALOG_GENERATE_VIP_KEY, DIALOG_STYLE_LIST, "Generate VIP Key", "Days\nType\nTo generate", "Select", "X");
                            return 1;
                        }

                        new key[30], type[30];
                        key = GenerateKey();

                        if(GetPVarInt(playerid, "gen_vip_type") == 0)
                            type = "Bronze";
                        else if(GetPVarInt(playerid, "gen_vip_type") == 1)
                            type = "Silver";
                        else if(GetPVarInt(playerid, "gen_vip_type") == 2)
                            type = "Gold";

                        SendClientMessagef(playerid, COLOR_TITLE, "Generated vip key!");
                        SendClientMessagef(playerid, COLOR_SUB_TITLE, "Days: %d", GetPVarInt(playerid, "gen_vip_days"));
                        SendClientMessagef(playerid, COLOR_SUB_TITLE, "Type: %s", type);
                        SendClientMessagef(playerid, COLOR_SUB_TITLE, "Key: %s", key);

                        new query[148];
                        mysql_format(gMySQL, query, sizeof(query), "INSERT INTO `vip_keys` (`serial`, `days`, `type`, `used`) VALUES ('%e', %d, %d, 0)", key, GetPVarInt(playerid, "gen_vip_days"), GetPVarInt(playerid, "gen_vip_type"));
                        mysql_tquery(gMySQL, query);
                    }
                }
            }
        }
        case DIALOG_GEN_VIP_KEY_DAYS:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
                ShowPlayerDialog(playerid, DIALOG_GENERATE_VIP_KEY, DIALOG_STYLE_LIST, "Generate VIP Key", "Days\nType\nTo generate", "Select", "X");
            }
            else
            {
                new days;
                if(sscanf(inputtext, "i", days))
                {
                    PlayErrorSound(playerid);
                    ShowPlayerDialog(playerid, DIALOG_GEN_VIP_KEY_DAYS, DIALOG_STYLE_INPUT, "Generate VIP Key: Days", "Enter how many days this VIP will last:", "Confirm", "Cancle");
                }

                else if(days < 1)
                {
                    PlayErrorSound(playerid);
                    SendClientMessage(playerid, COLOR_ERROR, "* Days cannot be less than 1.");
                    ShowPlayerDialog(playerid, DIALOG_GEN_VIP_KEY_DAYS, DIALOG_STYLE_INPUT, "Generate VIP Key: Days", "Enter how many days this VIP will last:", "Confirm", "Cancle");
                }

                else
                {
                    PlaySelectSound(playerid);
                    SetPVarInt(playerid, "gen_vip_days", days);
                    ShowPlayerDialog(playerid, DIALOG_GENERATE_VIP_KEY, DIALOG_STYLE_LIST, "Generate VIP Key", "Days\nType\nTo generate", "Select", "X");
                }
            }
        }
        case DIALOG_GEN_VIP_KEY_TYPE:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
                ShowPlayerDialog(playerid, DIALOG_GENERATE_VIP_KEY, DIALOG_STYLE_LIST, "Generate VIP Key", "Days\nType\nTo generate", "Select", "X");
            }
            else
            {
                PlaySelectSound(playerid);
                SetPVarInt(playerid, "gen_vip_type", listitem);
                ShowPlayerDialog(playerid, DIALOG_GENERATE_VIP_KEY, DIALOG_STYLE_LIST, "Generate VIP Key", "Days\nType\nTo generate", "Select", "X");
            }
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

timer RestartGameMode[5000]()
{
    SendRconCommand("restartserver");
}

//------------------------------------------------------------------------------

timer EndSurvey[60000]()
{
    SendClientMessageToAll(COLOR_ADMIN_COMMAND, "* Survey ended, results:");
    SendClientMessageToAll(COLOR_ADMIN_COMMAND, " ");
    SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* Yes: %d", gSurveyData[e_survey_yes]);
    SendClientMessageToAllf(COLOR_ADMIN_COMMAND, "* No: %d", gSurveyData[e_survey_no]);
    gSurveyData[e_survey_active] = false;
}
