/**********************************
 *                                *
 *   @Author:      ZeeX           *
 *   @Version:     0.3.1          *
 *   @Released:    31/10/2009     *
 *                                *
 **********************************/

#if defined _zbryan_included
	#endinput
#endif	
#define _zbryan_included

#include <a_samp>

#define MAX_FUNC_NAME (32)

#define COMMAND:%1(%2)			\
			forward bryan_%1(%2); \
			public bryan_%1(%2)		
			
#define BRYAN:%1(%2) \
			COMMAND:%1(%2)

#define command(%1,%2,%3) \
			COMMAND:%1(%2, %3)

#define cmd(%1,%2,%3) \
			COMMAND:%1(%2, %3)

#if !defined isnull
	#define isnull(%1) \
				((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif


forward OnPlayerCommandReceived(playerid, cmdtext[]); 
forward OnPlayerCommandPerformed(playerid, cmdtext[], success); 


static
	bool:zbryan_g_HasOPCS = false,
	bool:zbryan_g_HasOPCE = false;

#if defined FILTERSCRIPT

public OnFilterScriptInit()
{
	zbryan_g_HasOPCS = funcidx("OnPlayerCommandReceived") != -1;
	zbryan_g_HasOPCE = funcidx("OnPlayerCommandPerformed") != -1;
	return CallLocalFunction("zbryan_OnFilterScriptInit", "");
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit zbryan_OnFilterScriptInit
forward zbryan_OnFilterScriptInit();

#else /*not a filterscript*/

public OnGameModeInit()
{
	zbryan_g_HasOPCS = funcidx("OnPlayerCommandReceived") != -1;
	zbryan_g_HasOPCE = funcidx("OnPlayerCommandPerformed") != -1;
	if (funcidx("zbryan_OnGameModeInit") != -1)
	{
		return CallLocalFunction("zbryan_OnGameModeInit", "");
	}	
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit zbryan_OnGameModeInit
forward zbryan_OnGameModeInit();

#endif /*if defined FILTERSCRIPT*/

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (zbryan_g_HasOPCS && !CallLocalFunction("OnPlayerCommandReceived", "is", playerid, cmdtext))
	{
		return 1;
	}
	new
		pos,
		funcname[MAX_FUNC_NAME];
	while (cmdtext[++pos] > ' ') 
	{
		funcname[pos-1] = tolower(cmdtext[pos]); 
	}
	format(funcname, sizeof(funcname), "bryan_%s", funcname);
	while (cmdtext[pos] == ' ') pos++;
	if (!cmdtext[pos])
	{
		if (zbryan_g_HasOPCE)
		{
			return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(funcname, "is", playerid, "\1"));
		}
		return CallLocalFunction(funcname, "is", playerid, "\1");	
	}
	if (zbryan_g_HasOPCE)
	{
		return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(funcname, "is", playerid, cmdtext[pos]));
	}
	return CallLocalFunction(funcname, "is", playerid, cmdtext[pos]);
}

#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText zbryan_OnPlayerCommandText
forward zbryan_OnPlayerCommandText(playerid, cmdtext[]);