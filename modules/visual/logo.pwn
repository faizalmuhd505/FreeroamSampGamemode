/*******************************************************************************
* NOME DO ARQUIVO :		modules/visual/logo.pwn
*
* DESCRIÇÃO :
*	   Mostra o logo para o jogador.
*
* NOTAS :
*	   -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

static PlayerText:ServerNameTD[MAX_PLAYERS][4];

//------------------------------------------------------------------------------

ShowPlayerLogo(playerid)
{
    PlayerTextDrawShow(playerid, ServerNameTD[playerid][0]);
	PlayerTextDrawShow(playerid, ServerNameTD[playerid][1]);
	PlayerTextDrawShow(playerid, ServerNameTD[playerid][2]);
	PlayerTextDrawShow(playerid, ServerNameTD[playerid][3]);
}

//------------------------------------------------------------------------------

HidePlayerLogo(playerid)
{
    PlayerTextDrawHide(playerid, ServerNameTD[playerid][0]);
	PlayerTextDrawHide(playerid, ServerNameTD[playerid][1]);
	PlayerTextDrawHide(playerid, ServerNameTD[playerid][2]);
	PlayerTextDrawHide(playerid, ServerNameTD[playerid][3]);
}

//------------------------------------------------------------------------------

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_SPECTATING)
    {
        HidePlayerLogo(playerid);
    }
    else if(oldstate == PLAYER_STATE_SPECTATING)
    {
        ShowPlayerLogo(playerid);
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerConnect(playerid)
{
    ServerNameTD[playerid][0] = CreatePlayerTextDraw(playerid, 434.000000, 12.000000, "LEGACY");
	PlayerTextDrawFont(playerid, ServerNameTD[playerid][0], 2);
	PlayerTextDrawLetterSize(playerid, ServerNameTD[playerid][0], 0.333332, 1.850000);
	PlayerTextDrawTextSize(playerid, ServerNameTD[playerid][0], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ServerNameTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ServerNameTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, ServerNameTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, ServerNameTD[playerid][0], -16776961);
	PlayerTextDrawBackgroundColor(playerid, ServerNameTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, ServerNameTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, ServerNameTD[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, ServerNameTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, ServerNameTD[playerid][0], 0);

	ServerNameTD[playerid][1] = CreatePlayerTextDraw(playerid, 453.000000, 26.000000, "FREEROAM");
	PlayerTextDrawFont(playerid, ServerNameTD[playerid][1], 2);
	PlayerTextDrawLetterSize(playerid, ServerNameTD[playerid][1], 0.212500, 0.850000);
	PlayerTextDrawTextSize(playerid, ServerNameTD[playerid][1], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ServerNameTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ServerNameTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, ServerNameTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, ServerNameTD[playerid][1], -1061109505);
	PlayerTextDrawBackgroundColor(playerid, ServerNameTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, ServerNameTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, ServerNameTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, ServerNameTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, ServerNameTD[playerid][1], 0);

	ServerNameTD[playerid][2] = CreatePlayerTextDraw(playerid, 449.000000, 16.000000, "HUD:radardisc");
	PlayerTextDrawFont(playerid, ServerNameTD[playerid][2], 4);
	PlayerTextDrawLetterSize(playerid, ServerNameTD[playerid][2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ServerNameTD[playerid][2], 17.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ServerNameTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ServerNameTD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, ServerNameTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, ServerNameTD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, ServerNameTD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, ServerNameTD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, ServerNameTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, ServerNameTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, ServerNameTD[playerid][2], 0);

	ServerNameTD[playerid][3] = CreatePlayerTextDraw(playerid, 487.000000, 15.000000, "HUD:radarringplane");
	PlayerTextDrawFont(playerid, ServerNameTD[playerid][3], 4);
	PlayerTextDrawLetterSize(playerid, ServerNameTD[playerid][3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ServerNameTD[playerid][3], 8.500000, 12.500000);
	PlayerTextDrawSetOutline(playerid, ServerNameTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, ServerNameTD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, ServerNameTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, ServerNameTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, ServerNameTD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, ServerNameTD[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, ServerNameTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, ServerNameTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, ServerNameTD[playerid][3], 0);
    return 1;
}


hook OnPlayerDisconnect(playerid, reason)
{
    PlayerTextDrawDestroy(playerid, ServerNameTD[playerid][0]);
	PlayerTextDrawDestroy(playerid, ServerNameTD[playerid][1]);
	PlayerTextDrawDestroy(playerid, ServerNameTD[playerid][2]);
	PlayerTextDrawDestroy(playerid, ServerNameTD[playerid][3]);
    return 1;
}