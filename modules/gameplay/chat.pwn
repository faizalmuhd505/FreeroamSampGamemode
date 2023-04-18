/*******************************************************************************
* NOME DO ARQUIVO :        modules/gameplay/chat.pwn
*
* DESCRIÇÃO :
*       Comandos apenas usados por administradores.
*
* NOTAS :
*       -
*/

//------------------------------------------------------------------------------

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

hook OnPlayerText(playerid, text[])
{
    if(!IsPlayerLogged(playerid))
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You are not logged in.");
        return -1;
    }
    else if(IsPlayerInTutorial(playerid))
    {
        PlayErrorSound(playerid);
        return -1;
    }
    else if(IsPlayerMuted(playerid))
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You are mutated.");
        return -1;
    }
    else if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_RECRUIT && strfind(text, "@", true) == 0 && strlen(text) > 1)
	{
		strdel(text, 0, 1);
		new message[144];
		format(message, 144, "@ [{%06x}%s{ededed}] %s: {e3e3e3}%s", GetPlayerRankColor(playerid) >>> 8, GetPlayerAdminRankName(playerid, true), GetPlayerNamef(playerid), text);
		SendAdminMessage(PLAYER_RANK_RECRUIT, 0xedededff, message);
		return -1;
	}
    else if(IsPlayerVIP(playerid) && strfind(text, "!", true) == 0 && strlen(text) > 1)
	{
		strdel(text, 0, 1);
		new message[144];
		format(message, 144, "! [{ff0000}VIP{ededed}] %s: {e3e3e3}%s", GetPlayerNamef(playerid), text);
		SendVIPMessage(0xedededff, message);
		return -1;
	}
    else
    {
        new message[144];
        format(message, sizeof(message), "%s (%i): {ffffff}%s", GetPlayerNamef(playerid), playerid, text);

        if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_RECRUIT)
        {
            new rankName[14];
            format(rankName, 14, "[%s] ", GetPlayerAdminRankName(playerid, true));
            strins(message, rankName, 0);
        }
        else if(IsPlayerVIP(playerid))
        {
            strins(message, "[VIP] ", 0);
        }

        foreach(new i: Player)
        {
            if(GetPlayerGamemode(i) != GAMEMODE_LOBBY && !IsPlayerInTutorial(i))
            {
                SendClientMessage(i, GetPlayerColor(playerid), message);
            }
        }
    }
    return -1;
}
