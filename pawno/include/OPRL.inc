/*______________________________________________________________________________

						OPRL.inc - OnPlayerRconLogin
						        By Lordz.

	"OPRL" AKA "OnPlayerRconLogin" is an include which procies a callback called
	OnPlayerRconLogin which gets called when a player logins as RCON. This is
	called only when a player ID logs in, not if an IP does.



      This Source Code Form is subject to the
      terms of the Mozilla Public License, v.
      2.0. If a copy of the MPL was not
      distributed with this file, You can
      obtain one at
      http://mozilla.org/MPL/2.0/.

Author : Lordz™ AKA Lordzy.

NOTES:
1)You may have thought why "OPRL_USE_TIMER" define has been kept. OnPlayerUpdate
don't get called if you're not in game. RCON logins can also be done in apps
like RakSAMP which MAY or MAY NOT call OnPlayerUpdate. But as a timer gets -
called, such a define is used. Uncomment "OPRL_USE_TIMER" to use OnPlayerUpdate.

2) Why not "OnRconLoginAttempt"? Because, it may retrieve multiple users who are
   logged in with the same IP address. So, a timer or OnPlayerUpdate is better!


Callbacks:
OnPlayerRconLogin(playerid);

______________________________________________________________________________*/

#if defined _OnPlayerRconLogin_included
	#endinput
#endif

#define _OnPlayerRconLogin_included



//Comment this define in case if you want to avoid timer and use OnPlayerUpdate.
#define OPRL_USE_TIMER

static
	#if defined OPRL_USE_TIMER
	OPRL_LTimer,
	#endif
	bool:OPRL_IsPlayerAdmin[MAX_PLAYERS];


#if defined FILTERSCRIPT
public OnFilterScriptInit() {
	for(new i; i< GetMaxPlayers(); i++) {
	    if(IsPlayerAdmin(i)) OPRL_IsPlayerAdmin[i] = true;
	    else OPRL_IsPlayerAdmin[i] = false;
	}
	#if defined OPRL_USE_TIMER
	    OPRL_LTimer = SetTimer("OPRL_OnUpdate", 600, 1);
	#endif
	#if defined OPRL_OnFilterScriptInit
	    OPRL_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined OPRL_USE_TIMER
public OnFilterScriptExit() {
	KillTimer(OPRL_LTimer);
	#if defined OPRL_OnFilterScriptExit
	    OPRL_OnFilterScriptExit();
	#endif
	return 1;
}
#endif

#else

public OnGameModeInit() {
	for(new i; i< GetMaxPlayers(); i++) {
	    if(IsPlayerAdmin(i)) OPRL_IsPlayerAdmin[i] = true;
	    else OPRL_IsPlayerAdmin[i] = false;
	}
	#if defined OPRL_USE_TIMER
	    SetTimer("OPRL_OnUpdate", 600, 1);
	#endif
	#if defined ORPL_OnGameModeInit
	    OPRL_OnGameModeInit();
	#endif
	return 1;
}

#if defined OPRL_USE_TIMER
public OnGameModeExit() {
	KillTimer(OPRL_LTimer);
	#if defined OPRL_OnGameModeExit
	    OPRL_OnGameModeExit();
	#endif
	return 1;
}
#endif


#endif

#if defined FILTERSCRIPT

	#if defined _ALS_OnFilterScriptInit
	    #undef OnFilterScriptInit
	#else
	    #define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit OPRL_OnFilterScriptInit

	#if defined OPRL_OnFilterScriptInit
	forward OPRL_OnFilterScriptInit();
	#endif
	
	#if defined OPRL_USE_TIMER
	
		#if defined _ALS_OnFilterScriptExit
	    	#undef OnFilterScriptExit
		#else
	    	#define _ALS_OnFilterScriptExit
		#endif
	
		#define OnFilterScriptExit OPRL_OnFilterScriptExit
	
		#if defined OPRL_OnFilterScriptExit
		forward OPRL_OnFilterScriptExit();
		#endif
	#endif
	

#else

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
	    #define _ALS_OnGameModeInit
	#endif
	
	#define OnGameModeInit OPRL_OnGameModeInit

	#if defined OPRL_OnGameModeInit
	forward OPRL_OnGameModeInit();
	#endif
	
	#if defined OPRL_USE_TIMER
	    #if defined _ALS_OnGameModeExit
	        #undef OnGameModeExit
		#else
		    #define _ALS_OnGameModeExit
		#endif
		
		#define OnGameModeExit OPRL_OnGameModeExit
		
		#if defined OPRL_OnGameModeExit
		forward OPRL_OnGameModeExit();
		#endif
	#endif
#endif


static stock OPRL_CheckRCONAdmin(playerid) {
	if(IsPlayerAdmin(playerid) && OPRL_IsPlayerAdmin[playerid] == false) {
		OPRL_IsPlayerAdmin[playerid] = true;
		CallLocalFunction("OnPlayerRconLogin", "i", playerid);
	}
	else if(!IsPlayerAdmin(playerid) && OPRL_IsPlayerAdmin[playerid] == true) {
	    OPRL_IsPlayerAdmin[playerid] = false;
	}
	return 1;
}
#if defined OPRL_USE_TIMER
forward OPRL_OnUpdate();

public OPRL_OnUpdate() {
	for(new i; i< GetMaxPlayers(); i++) {
		if(!IsPlayerConnected(i)) continue;
		OPRL_CheckRCONAdmin(i);
	}
	return 1;
}

#else

public OnPlayerUpdate(playerid) {
	OPRL_CheckRCONAdmin(playerid);
	#if defined OPRL_OnPlayerUpdate
	    OPRL_OnPlayerUpdate(playerid);
	#endif
	return 1;
}

	#if defined _ALS_OnPlayerUpdate
	    #undef OnPlayerUpdate
	#else
	    #define _ALS_OnPlayerUpdate
	#endif
	
	#define OnPlayerUpdate OPRL_OnPlayerUpdate

	#if defined OPRL_OnPlayerUpdate
	forward OPRL_OnPlayerUpdate(playerid);
	#endif
#endif


forward OnPlayerRconLogin(playerid);

/* Copyright(c) 2014 - "OPRL.inc" */