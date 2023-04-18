/*******************************************************************************
* NOME DO ARQUIVO :        modules/core/timers.pwn
*
* DESCRIÇÃO :
*       Temporizadores gerais.
*
* NOTAS :
*       -
*/

#include <YSI\y_hooks>

ptask UpdatePlayerData[1000](playerid)
{
    // If the player is not logged in, ignore
	if(!IsPlayerLogged(playerid))
		return 1;

    if(GetPlayerCash(playerid) != GetPlayerMoney(playerid))
    {
        ResetPlayerMoney(playerid);
        GivePlayerMoney(playerid, GetPlayerCash(playerid));
    }

	SetPlayerPlayedTime(playerid, GetPlayerPlayedTime(playerid) + 1);
    return 1;
}
