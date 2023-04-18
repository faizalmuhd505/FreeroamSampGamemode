/*******************************************************************************
* NOME DO ARQUIVO :		modules/visual/lobby.pwn
*
* DESCRIÇÃO :
*	   Possiblita o jogador a mudar o modo de jogo através de GUI.
*
* NOTAS :
*	   -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

enum
{
    GAMEMODE_LOBBY,
    GAMEMODE_FREEROAM,
    GAMEMODE_DEATHMATCH,
    GAMEMODE_RACE,
    GAMEMODE_DERBY
}
static gPlayerCurrentMode[MAX_PLAYERS];
static Text:lobbyTextdraw[13];
static bool:gIsLobbyShown[MAX_PLAYERS];

//------------------------------------------------------------------------------

ShowPlayerLobby(playerid)
{
    new tempstr[32];
    format(tempstr, sizeof(tempstr), "Freeroam~n~%d / %d", GetTotalPlayersOfGamemode(GAMEMODE_FREEROAM), MAX_PLAYERS);
    TextDrawSetString(lobbyTextdraw[9], tempstr);
    format(tempstr, sizeof(tempstr), "Deathmatch~n~%d / %d", GetTotalPlayersOfGamemode(GAMEMODE_DEATHMATCH), (MAX_PLAYERS / 3));
    TextDrawSetString(lobbyTextdraw[10], tempstr);
    format(tempstr, sizeof(tempstr), "Race~n~%d / %d", GetTotalPlayersOfGamemode(GAMEMODE_RACE), (MAX_PLAYERS / 3));
    TextDrawSetString(lobbyTextdraw[11], tempstr);
    format(tempstr, sizeof(tempstr), "Derby~n~%d / %d", GetTotalPlayersOfGamemode(GAMEMODE_DERBY), (MAX_PLAYERS / 3));
    TextDrawSetString(lobbyTextdraw[12], tempstr);
    ClearPlayerScreen(playerid, 10);

    HidePlayerDeathmatchHud(playerid);

    for(new i = 0; i < sizeof(lobbyTextdraw); i++)
    {
        TextDrawShowForPlayer(playerid, lobbyTextdraw[i]);
    }
    foreach(new i: Player)
    {
        ShowPlayerNameTagForPlayer(playerid, i, false);
    }
    SelectTextDraw(playerid, 0x0e8893ff);
    gIsLobbyShown[playerid] = true;
}

//------------------------------------------------------------------------------

HidePlayerLobby(playerid)
{
    for(new i = 0; i < sizeof(lobbyTextdraw); i++)
    {
        TextDrawHideForPlayer(playerid, lobbyTextdraw[i]);
    }
    foreach(new i: Player)
    {
        ShowPlayerNameTagForPlayer(playerid, i, true);
    }
    CancelSelectTextDraw(playerid);

    if(GetPlayerGamemode(playerid) == GAMEMODE_DEATHMATCH)
    {
        if(GetPlayerDeathmatchState(GetPlayerDeathmatch(playerid)) == 2 || GetPlayerDeathmatchState(GetPlayerDeathmatch(playerid)) == 3) // started or ending
        {
            ShowPlayerDeathmatchHud(playerid);
        }
    }

    gIsLobbyShown[playerid] = false;
}

//------------------------------------------------------------------------------

GetTotalPlayersOfGamemode(mode)
{
    new total = 0;
    foreach(new i: Player)
    {
        if(gPlayerCurrentMode[i] == mode)
        {
            total++;
        }
    }
    return total;
}

//------------------------------------------------------------------------------

SetPlayerGamemode(playerid, mode)
{
    gPlayerCurrentMode[playerid] = mode;
}

//------------------------------------------------------------------------------

GetPlayerGamemode(playerid)
{
    return gPlayerCurrentMode[playerid];
}

//------------------------------------------------------------------------------

YCMD:lobby(playerid, params[], help)
{
    ShowPlayerLobby(playerid);
    return 1;
}

//------------------------------------------------------------------------------


hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(gIsLobbyShown[playerid] && !IsRaceDialogVisible(playerid) && !IsDerbyDialogVisible(playerid) && !IsDeathmatchDialogVisible(playerid))
    {
        if(clickedid == Text:INVALID_TEXT_DRAW)
        {
            if(gPlayerCurrentMode[playerid] == GAMEMODE_LOBBY)
                SelectTextDraw(playerid, 0x0e8893ff);
            else
            {
                PlayCancelSound(playerid);
                HidePlayerLobby(playerid);
            }
        }
        else if(clickedid == lobbyTextdraw[1])
        {
            if(gPlayerCurrentMode[playerid] == GAMEMODE_FREEROAM)
            {
                PlayCancelSound(playerid);
                HidePlayerLobby(playerid);
            }
            else
            {
                if(GetPlayerGamemode(playerid) == GAMEMODE_RACE)
                {
                    ResetPlayerRaceData(playerid);
                    DisableRemoteVehicleCollisions(playerid, false);
                }
                else if(GetPlayerGamemode(playerid) == GAMEMODE_DERBY)
                {
                    ResetPlayerDerbyData(playerid);
                }
                else if(GetPlayerGamemode(playerid) == GAMEMODE_DEATHMATCH)
                {
                    ResetPlayerDeathmatchData(playerid);
                    ResetPlayerWeapons(playerid);
                }

                if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
                {
                    TogglePlayerSpectating(playerid, false);
                }

                PlayConfirmSound(playerid);
                gPlayerCurrentMode[playerid] = GAMEMODE_FREEROAM;
                SetPlayerPos(playerid, 1119.9399, -1618.7476, 20.5210);
                SetPlayerFacingAngle(playerid, 91.8327);
                SetPlayerInterior(playerid, 0);
                SetPlayerVirtualWorld(playerid, 0);
                SetPlayerHealth(playerid, 100.0);
                HidePlayerLobby(playerid);
            }
        }
        else if(clickedid == lobbyTextdraw[3])
        {
            PlayConfirmSound(playerid);
            ShowPlayerDeathmatchList(playerid);
        }
        else if(clickedid == lobbyTextdraw[5])
        {
            PlayConfirmSound(playerid);
            ShowPlayerRaceList(playerid);
        }
        else if(clickedid == lobbyTextdraw[7])
        {
            PlayConfirmSound(playerid);
            ShowPlayerDerbyList(playerid);
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerDisconnect(playerid, reason)
{
    gIsLobbyShown[playerid]         = false;
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerConnect(playerid)
{
    gPlayerCurrentMode[playerid]    = GAMEMODE_LOBBY;
    return 1;
}

//------------------------------------------------------------------------------

hook OnGameModeInit()
{
    lobbyTextdraw[0] = TextDrawCreate(0.0, 0.0, "_");
    TextDrawLetterSize(lobbyTextdraw[0], 0.406331, 49.766941);
    TextDrawTextSize(lobbyTextdraw[0], 648.000000, 0.000000);
    TextDrawAlignment(lobbyTextdraw[0], 1);
    TextDrawColor(lobbyTextdraw[0], -1);
    TextDrawUseBox(lobbyTextdraw[0], 1);
    TextDrawBoxColor(lobbyTextdraw[0], 255);
    TextDrawSetShadow(lobbyTextdraw[0], 0);
    TextDrawSetOutline(lobbyTextdraw[0], 0);
    TextDrawBackgroundColor(lobbyTextdraw[0], 255);
    TextDrawFont(lobbyTextdraw[0], 2);
    TextDrawSetProportional(lobbyTextdraw[0], 1);
    TextDrawSetShadow(lobbyTextdraw[0], 0);

    lobbyTextdraw[1] = TextDrawCreate(75.0, 151.681564, "ld_pool:ball");
    TextDrawLetterSize(lobbyTextdraw[1], 0.000000, 0.000000);
    TextDrawTextSize(lobbyTextdraw[1], 90.000000, 90.000000);
    TextDrawAlignment(lobbyTextdraw[1], 1);
    TextDrawColor(lobbyTextdraw[1], 0x0c5e65ff);
    TextDrawSetShadow(lobbyTextdraw[1], 0);
    TextDrawSetOutline(lobbyTextdraw[1], 0);
    TextDrawBackgroundColor(lobbyTextdraw[1], 255);
    TextDrawFont(lobbyTextdraw[1], 4);
    TextDrawSetProportional(lobbyTextdraw[1], 0);
    TextDrawSetShadow(lobbyTextdraw[1], 0);
    TextDrawSetSelectable(lobbyTextdraw[1], true);

    lobbyTextdraw[2] = TextDrawCreate(74.066619, 150.851837, ""); // SA-MP logo
    TextDrawLetterSize(lobbyTextdraw[2], 0.000000, 0.000000);
    TextDrawTextSize(lobbyTextdraw[2], 90.000000, 90.000000);
    TextDrawAlignment(lobbyTextdraw[2], 1);
    TextDrawColor(lobbyTextdraw[2], -1);
    TextDrawSetShadow(lobbyTextdraw[2], 0);
    TextDrawSetOutline(lobbyTextdraw[2], 0);
    TextDrawBackgroundColor(lobbyTextdraw[2], 0);
    TextDrawFont(lobbyTextdraw[2], 5);
    TextDrawSetProportional(lobbyTextdraw[2], 0);
    TextDrawSetShadow(lobbyTextdraw[2], 0);
    TextDrawSetPreviewModel(lobbyTextdraw[2], 18750);
    TextDrawSetPreviewRot(lobbyTextdraw[2], 90.000000, 180.000000, 0.000000, 1.000000);

    lobbyTextdraw[3] = TextDrawCreate(200.0, 151.681564, "ld_pool:ball");
    TextDrawLetterSize(lobbyTextdraw[3], 0.000000, 0.000000);
    TextDrawTextSize(lobbyTextdraw[3], 90.000000, 90.000000);
    TextDrawAlignment(lobbyTextdraw[3], 1);
    TextDrawColor(lobbyTextdraw[3], 0x0c5e65ff);
    TextDrawSetShadow(lobbyTextdraw[3], 0);
    TextDrawSetOutline(lobbyTextdraw[3], 0);
    TextDrawBackgroundColor(lobbyTextdraw[3], 255);
    TextDrawFont(lobbyTextdraw[3], 4);
    TextDrawSetProportional(lobbyTextdraw[3], 0);
    TextDrawSetShadow(lobbyTextdraw[3], 0);
    TextDrawSetSelectable(lobbyTextdraw[3], true);

    lobbyTextdraw[4] = TextDrawCreate(200.800079, 156.659286, "");// Weapon
    TextDrawLetterSize(lobbyTextdraw[4], 0.000000, 0.000000);
    TextDrawTextSize(lobbyTextdraw[4], 90.000000, 90.000000);
    TextDrawAlignment(lobbyTextdraw[4], 1);
    TextDrawColor(lobbyTextdraw[4], -1);
    TextDrawSetShadow(lobbyTextdraw[4], 0);
    TextDrawSetOutline(lobbyTextdraw[4], 0);
    TextDrawBackgroundColor(lobbyTextdraw[4], 0);
    TextDrawFont(lobbyTextdraw[4], 5);
    TextDrawSetProportional(lobbyTextdraw[4], 0);
    TextDrawSetShadow(lobbyTextdraw[4], 0);
    TextDrawSetPreviewModel(lobbyTextdraw[4], 356);
    TextDrawSetPreviewRot(lobbyTextdraw[4], 0.000000, 0.000000, 320.000000, 1.000000);

    lobbyTextdraw[5] = TextDrawCreate(325.0, 151.681564, "ld_pool:ball");
    TextDrawLetterSize(lobbyTextdraw[5], 0.000000, 0.000000);
    TextDrawTextSize(lobbyTextdraw[5], 90.000000, 90.000000);
    TextDrawAlignment(lobbyTextdraw[5], 1);
    TextDrawColor(lobbyTextdraw[5], 0x0c5e65ff);
    TextDrawSetShadow(lobbyTextdraw[5], 0);
    TextDrawSetOutline(lobbyTextdraw[5], 0);
    TextDrawBackgroundColor(lobbyTextdraw[5], 255);
    TextDrawFont(lobbyTextdraw[5], 4);
    TextDrawSetProportional(lobbyTextdraw[5], 0);
    TextDrawSetShadow(lobbyTextdraw[5], 0);
    TextDrawSetSelectable(lobbyTextdraw[5], true);

    lobbyTextdraw[6] = TextDrawCreate(323.666564, 147.318603, "");// Vehicle
    TextDrawLetterSize(lobbyTextdraw[6], 0.000000, 0.000000);
    TextDrawTextSize(lobbyTextdraw[6], 90.000000, 90.000000);
    TextDrawAlignment(lobbyTextdraw[6], 1);
    TextDrawColor(lobbyTextdraw[6], -1);
    TextDrawSetShadow(lobbyTextdraw[6], 0);
    TextDrawSetOutline(lobbyTextdraw[6], 0);
    TextDrawBackgroundColor(lobbyTextdraw[6], 0);
    TextDrawFont(lobbyTextdraw[6], 5);
    TextDrawSetProportional(lobbyTextdraw[6], 0);
    TextDrawSetShadow(lobbyTextdraw[6], 0);
    TextDrawSetPreviewModel(lobbyTextdraw[6], 502);
    TextDrawSetPreviewRot(lobbyTextdraw[6], 0.000000, 0.000000, 45.000000, 1.000000);
    TextDrawSetPreviewVehCol(lobbyTextdraw[6], 1, 3);

    lobbyTextdraw[7] = TextDrawCreate(450.0, 151.681564, "ld_pool:ball");
    TextDrawLetterSize(lobbyTextdraw[7], 0.000000, 0.000000);
    TextDrawTextSize(lobbyTextdraw[7], 90.000000, 90.000000);
    TextDrawAlignment(lobbyTextdraw[7], 1);
    TextDrawColor(lobbyTextdraw[7], 0x0c5e65ff);
    TextDrawSetShadow(lobbyTextdraw[7], 0);
    TextDrawSetOutline(lobbyTextdraw[7], 0);
    TextDrawBackgroundColor(lobbyTextdraw[7], 255);
    TextDrawFont(lobbyTextdraw[7], 4);
    TextDrawSetProportional(lobbyTextdraw[7], 0);
    TextDrawSetShadow(lobbyTextdraw[7], 0);
    TextDrawSetSelectable(lobbyTextdraw[7], true);

    lobbyTextdraw[8] = TextDrawCreate(450.033142, 146.703781, "");// Barrel
    TextDrawLetterSize(lobbyTextdraw[8], 0.000000, 0.000000);
    TextDrawTextSize(lobbyTextdraw[8], 90.000000, 90.000000);
    TextDrawAlignment(lobbyTextdraw[8], 1);
    TextDrawColor(lobbyTextdraw[8], -1);
    TextDrawSetShadow(lobbyTextdraw[8], 0);
    TextDrawSetOutline(lobbyTextdraw[8], 0);
    TextDrawBackgroundColor(lobbyTextdraw[8], 0);
    TextDrawFont(lobbyTextdraw[8], 5);
    TextDrawSetProportional(lobbyTextdraw[8], 0);
    TextDrawSetShadow(lobbyTextdraw[8], 0);
    TextDrawSetPreviewModel(lobbyTextdraw[8], 1225);
    TextDrawSetPreviewRot(lobbyTextdraw[8], 0.000000, 0.000000, 0.000000, 1.000000);

    new tempstr[32];
    format(tempstr, sizeof(tempstr), "Freeroam~n~0 / %d", MAX_PLAYERS);
    lobbyTextdraw[9] = TextDrawCreate(120.0, 242.0, tempstr);
    TextDrawLetterSize(lobbyTextdraw[9], 0.229332, 0.878220);
    TextDrawAlignment(lobbyTextdraw[9], 2);
    TextDrawColor(lobbyTextdraw[9], -1);
    TextDrawSetShadow(lobbyTextdraw[9], 0);
    TextDrawSetOutline(lobbyTextdraw[9], 0);
    TextDrawBackgroundColor(lobbyTextdraw[9], 255);
    TextDrawFont(lobbyTextdraw[9], 2);
    TextDrawSetProportional(lobbyTextdraw[9], 1);
    TextDrawSetShadow(lobbyTextdraw[9], 0);

    format(tempstr, sizeof(tempstr), "Deathmatch~n~0 / %d", (MAX_PLAYERS / 3));
    lobbyTextdraw[10] = TextDrawCreate(250.0, 242.0, tempstr);
    TextDrawLetterSize(lobbyTextdraw[10], 0.229332, 0.878220);
    TextDrawAlignment(lobbyTextdraw[10], 2);
    TextDrawColor(lobbyTextdraw[10], -1);
    TextDrawSetShadow(lobbyTextdraw[10], 0);
    TextDrawSetOutline(lobbyTextdraw[10], 0);
    TextDrawBackgroundColor(lobbyTextdraw[10], 255);
    TextDrawFont(lobbyTextdraw[10], 2);
    TextDrawSetProportional(lobbyTextdraw[10], 1);
    TextDrawSetShadow(lobbyTextdraw[10], 0);

    format(tempstr, sizeof(tempstr), "Race~n~0 / %d", (MAX_PLAYERS / 3));
    lobbyTextdraw[11] = TextDrawCreate(375.0, 242.0, tempstr);
    TextDrawLetterSize(lobbyTextdraw[11], 0.229332, 0.878220);
    TextDrawAlignment(lobbyTextdraw[11], 2);
    TextDrawColor(lobbyTextdraw[11], -1);
    TextDrawSetShadow(lobbyTextdraw[11], 0);
    TextDrawSetOutline(lobbyTextdraw[11], 0);
    TextDrawBackgroundColor(lobbyTextdraw[11], 255);
    TextDrawFont(lobbyTextdraw[11], 2);
    TextDrawSetProportional(lobbyTextdraw[11], 1);
    TextDrawSetShadow(lobbyTextdraw[11], 0);

    format(tempstr, sizeof(tempstr), "Derby~n~0 / %d", (MAX_PLAYERS / 3));
    lobbyTextdraw[12] = TextDrawCreate(498.0, 242.0, tempstr);
    TextDrawLetterSize(lobbyTextdraw[12], 0.229332, 0.878220);
    TextDrawAlignment(lobbyTextdraw[12], 2);
    TextDrawColor(lobbyTextdraw[12], -1);
    TextDrawSetShadow(lobbyTextdraw[12], 0);
    TextDrawSetOutline(lobbyTextdraw[12], 0);
    TextDrawBackgroundColor(lobbyTextdraw[12], 255);
    TextDrawFont(lobbyTextdraw[12], 2);
    TextDrawSetProportional(lobbyTextdraw[12], 1);
    TextDrawSetShadow(lobbyTextdraw[12], 0);
    return 1;
}
