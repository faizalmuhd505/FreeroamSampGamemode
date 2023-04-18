/*******************************************************************************
 *                                                                             *
 *                    LIFE:CMD Powered by © Fusion Technology                  *
 *                           © All rights reserved                             *
 *                          Copyrights © Kazon 2012                            *
 *                         LIFE:CMD Created: 1/01/13.                          *
 *                                                                             *
 *******************************************************************************/
native LIFECMD(playerid, cmdtext[]);

#if !defined LIFE_SPEED
static bool:F_CMD[3];	
/*==================================[Public's]=================================*/
public OnGameModeInit()
{
	F_CMD[0] = funcidx("OnPlayerCommandCall") != -1;
	F_CMD[1] = funcidx("OnPlayerCommandFinish") != -1;
	F_CMD[2] = funcidx("F_OnPlayerCommandText") != -1;
	if(funcidx("F_OnGameModeInit") != -1) return CallLocalFunction("F_OnGameModeInit", "");
	return true;
}
#endif

public OnPlayerCommandText(playerid, cmdtext[])
{	
#if !defined LIFE_SPEED
	if(F_CMD[0] && !CallLocalFunction("OnPlayerCommandCall", "is", playerid, cmdtext)) return true;
	if(F_CMD[1]) CallLocalFunction("OnPlayerCommandFinish", "isi", playerid, cmdtext, LIFECMD(playerid, cmdtext));
	else LIFECMD(playerid, cmdtext);
	if(F_CMD[2]) return CallLocalFunction("F_OnPlayerCommandText", "is", playerid, cmdtext);
	return true;
#else
	return LIFECMD(playerid, cmdtext);
#endif
}
/*==================================[Forward's]================================*/
forward OnPlayerCommandReceived(playerid, cmdtext[]);
forward OnPlayerCommandPerformed(playerid, cmdtext[], success);
forward F_OnGameModeInit();
forward OnPlayerCommandCall(playerid, cmdtext[]);
forward F_OnPlayerCommandText(playerid, cmdtext[]);
forward OnPlayerCommandFinish(playerid, cmdtext[], success);
/*==================================[Define's]================================*/
#if !defined isnull
	#define isnull(%0) ((!(%0[0])) || (((%0[0]) == '\1') && (!(%0[1]))))
#endif

#define COMMAND:%0(%1,%2)       \
		forward cmd_%0(%1,%2);  \
		public cmd_%0(%1,%2)

#define cmd::%0(%1,%2) cmd_%0(%1,%2)
#define CMD:%0(%1,%2) COMMAND:%0(%1,%2)
#define FCMD:%0(%1,%2) COMMAND:%0(%1,%2)
#define LIFE:%0(%1,%2) COMMAND:%0(%1,%2)
#define FUSION:%0(%1,%2) COMMAND:%0(%1,%2)
#define Call::(%0,%1) OnPlayerCommandText(%0, %1);
/*==================================[UnDefine's]================================*/
#if !defined LIFE_SPEED
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit F_OnGameModeInit
#endif

#if defined _ALS_OnPlayerCommandText
    #undef OnPlayerCommandText
#else
    #define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText F_OnPlayerCommandText