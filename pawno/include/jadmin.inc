/*******************************************************************************

-> Jake's Administration System 4.0 include
-> by JaKe Elite 
-> Patched: 2017 

Supports the following functions:
	* Online Time Controls
	* Chocolate Bar checking/setting
	• Logging checking/setting
	• Admin checking/setting
	• Mute for both chat and commands checking/setting
	• accountID checking
	• Jail checking/setting
	• Warn checking/setting
	• Kills checking/setting
	• Deaths checking/setting
	* Private Message call back.
	* Idle Check. (AFK)
	* Tabbed Out check. (On Pause Menu, browsing outside the game)

Natives:

native SetPlayerGameTime(playerid, hour, minute, second);
native GetPlayerGameTime(playerid, &hour, &minute, &second);
native SetPlayerChocolate(playerid, amount);
native GetPlayerChocolate(playerid);
native CheckLogin(playerid);
native SetPlayerLogged(playerid, toggle);
native SavePlayer(playerid);
native CheckAdmin(playerid);
native SetPlayerAdmin(playerid, level);
native CheckPlayerMute(playerid);
native CheckPlayerMuteSecond(playerid);
native CheckPlayerCMute(playerid);
native CheckPlayerCMuteSecond(playerid);
native SetPlayerMute(playerid, toggle);
native SetPlayerMuteSecond(playerid, seconds);
native SetPlayerCMuteSecond(playerid, seconds);
native CheckPlayerJail(playerid);
native CheckPlayerJailSecond(playerid);
native SetPlayerJail(playerid, toggle);
native SetPlayerJailSecond(playerid, seconds);
native CheckAccountID(playerid);
native CheckPlayerWarn(playerid);
native SetPlayerWarn(playerid, warn);
native CheckPlayerKills(playerid);
native SetPlayerKill(playerid, kill);
native CheckPlayerDeaths(playerid);
native SetPlayerDeath(playerid, death);
native IsPlayerIdle(playerid);
native IsPlayerTabbed(playerid);

*******************************************************************************/

#if defined _jadmin3_included
	#endinput
#endif
#define _jadmin3_included

forward OnPlayerPrivMessage(playerid, id, text[]);

stock SetPlayerGameTime(playerid, hour, minute, second)
{
	return CallRemoteFunction("set_playingtime", "dddd", playerid, hour, minute, second);
}

stock GetPlayerGameTime(playerid, &hour, &minute, &second)
{
    CallRemoteFunction("check_playingtime", "d", playerid);
	hour = GetPVarInt(playerid, "account_hour");
	minute = GetPVarInt(playerid, "account_minute");
	second = GetPVarInt(playerid, "account_second");
	return 1;
}

stock IsPlayerIdle(playerid)
	return CallRemoteFunction("check_playerafk", "d", playerid);

stock IsPlayerTabbed(playerid)
	return CallRemoteFunction("check_playertabbed", "d", playerid);
	
stock GetPlayerChocolate(playerid)
{
	return CallRemoteFunction("check_chocolate", "d", playerid);
}

stock SetPlayerChocolate(playerid, amount)
{
	return CallRemoteFunction("set_chocolate", "dd", playerid, amount);
}

stock CheckLogin(playerid)
{
	return CallRemoteFunction("check_login", "d", playerid);
}

stock SavePlayer(playerid)
{
	return CallRemoteFunction("save_player", "d", playerid);
}

stock CheckAdmin(playerid)
{
	return CallRemoteFunction("check_admin", "d", playerid);
}

stock SetPlayerAdmin(playerid, level)
{
	return CallRemoteFunction("set_admin", "dd", playerid, level);
}

stock SetPlayerLogged(playerid, toggle)
{
	return CallRemoteFunction("set_log", "dd", playerid, toggle);
}

stock CheckPlayerMute(playerid)
{
	return CallRemoteFunction("check_mute", "d", playerid);
}

stock CheckPlayerMuteSecond(playerid)
{
	return CallRemoteFunction("check_mutesec", "d", playerid);
}

stock CheckPlayerCMute(playerid)
{
	return CallRemoteFunction("check_cmute", "d", playerid);
}

stock CheckPlayerCMuteSecond(playerid)
{
	return CallRemoteFunction("check_cmutesec", "d", playerid);
}

stock SetPlayerMute(playerid, toggle)
{
	return CallRemoteFunction("set_mute", "dd", playerid, toggle);
}

stock SetPlayerMuteSecond(playerid, second)
{
	return CallRemoteFunction("set_mutesec", "dd", playerid, second);
}

stock SetPlayerCMute(playerid, toggle)
{
	return CallRemoteFunction("set_cmute", "dd", playerid, toggle);
}

stock SetPlayerCMuteSecond(playerid, second)
{
	return CallRemoteFunction("set_cmutesec", "dd", playerid, second);
}

stock CheckPlayerJail(playerid)
{
	return CallRemoteFunction("check_jail", "d", playerid);
}

stock CheckPlayerJailSecond(playerid)
{
	return CallRemoteFunction("check_jailsec", "d", playerid);
}

stock SetPlayerJail(playerid, toggle)
{
	return CallRemoteFunction("set_jail", "dd", playerid, toggle);
}

stock SetPlayerJailSecond(playerid, sec)
{
	return CallRemoteFunction("set_jailsec", "dd", playerid, sec);
}

stock CheckAccountID(playerid)
{
	return CallRemoteFunction("check_id", "d", playerid);
}

stock CheckPlayerWarn(playerid)
{
	return CallRemoteFunction("check_warn", "d", playerid);
}

stock SetPlayerWarn(playerid, warn)
{
	return CallRemoteFunction("set_warn", "dd", playerid, warn);
}

stock CheckPlayerKills(playerid)
{
	return CallRemoteFunction("check_kills", "d", playerid);
}

stock SetPlayerKills(playerid, amount)
{
	return CallRemoteFunction("set_kills", "dd", playerid, amount);
}

stock CheckPlayerDeaths(playerid)
{
	return CallRemoteFunction("check_deaths", "d", playerid);
}

stock SetPlayerDeath(playerid, amount)
{
	return CallRemoteFunction("set_death", "dd", playerid, amount);
}