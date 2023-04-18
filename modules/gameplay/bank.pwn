/*******************************************************************************
* NOME DO ARQUIVO :        modules/gameplay/bank.pwn
*
* DESCRIPTION : 
 * Adds bank account to players. 
 * 
 * GRADES :
*       -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

YCMD:transfer(playerid, params[], help)
{
   new targetid, amount;
   if(sscanf(params, "ui", targetid, amount))
       return SendClientMessage(playerid, COLOR_INFO, "* /transfer [playerid] [amount]");

   else if(!IsPlayerLogged(targetid))
       return SendClientMessage(playerid, COLOR_ERROR, "* The player is not connected.");

   else if(targetid == playerid)
       return SendClientMessage(playerid, COLOR_ERROR, "* You cannot transfer to yourself.");

   else if(GetPlayerBankCash(playerid) < amount)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have this amount of money in the bank.");

   else if(amount < 1)
       return SendClientMessage(playerid, COLOR_ERROR, "* Only values above 0 are allowed.");

   SetPlayerBankCash(playerid, GetPlayerBankCash(playerid) - amount);
   SetPlayerBankCash(targetid, GetPlayerBankCash(targetid) + amount);
   SendClientMessagef(targetid, COLOR_PLAYER_COMMAND, "* %s transferred $%d for you.", GetPlayerNamef(playerid), amount);
   SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You transferred $%d for %s.", amount, GetPlayerNamef(targetid));
   return 1;
}

//------------------------------------------------------------------------------

YCMD:deposit(playerid, params[], help)
{
   new amount;
   if(sscanf(params, "i", amount))
       return SendClientMessage(playerid, COLOR_INFO, "* /deposit [quantia]");

   else if(GetPlayerCash(playerid) < amount)
       return SendClientMessage(playerid, COLOR_ERROR, "* You don't have this amount of money in hand.");

   else if(amount < 1)
       return SendClientMessage(playerid, COLOR_ERROR, "* Only values above 0 are allowed.");

   SetPlayerCash(playerid, GetPlayerCash(playerid) - amount);
   SetPlayerBankCash(playerid, GetPlayerBankCash(playerid) + amount);
   SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You deposited $%d.", amount);
   return 1;
}

//------------------------------------------------------------------------------

YCMD:cashout(playerid, params[], help)
{
   new amount;
   if(sscanf(params, "i", amount))
       return SendClientMessage(playerid, COLOR_INFO, "* /cashout [amount]");

   else if(GetPlayerBankCash(playerid) < amount)
       return SendClientMessage(playerid, COLOR_ERROR, "* You do not have this amount of money in the bank.");

   else if(amount < 1)
       return SendClientMessage(playerid, COLOR_ERROR, "* Only values above 0 are allowed.");

   SetPlayerCash(playerid, GetPlayerCash(playerid) + amount);
   SetPlayerBankCash(playerid, GetPlayerBankCash(playerid) - amount);
   SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You drew $%d.", amount);
   return 1;
}

//------------------------------------------------------------------------------

YCMD:balance(playerid, params[], help)
{
   SendClientMessagef(playerid, COLOR_PLAYER_COMMAND, "* You have $%d In bank.", GetPlayerBankCash(playerid));
   return 1;
}

//------------------------------------------------------------------------------
