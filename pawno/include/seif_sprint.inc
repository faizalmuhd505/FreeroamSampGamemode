
#include <a_samp>

#define SPRINT_NORMAL    0
#define SPRINT_CIVIL     1
#define SPRINT_FAT       2
#define SPRINT_FATOLD    3
#define SPRINT_GANGSTA   4
#define SPRINT_WUZI      5
#define SPRINT_PANIC     6
#define SPRINT_OLD       7

#define SPRINT_TIMER 100
new sprinttime[MAX_PLAYERS];
new sprintStyle[MAX_PLAYERS];

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (((newkeys & KEY_SPRINT && newkeys & KEY_UP) || (newkeys & KEY_SPRINT && newkeys & KEY_DOWN) || (newkeys & KEY_SPRINT && newkeys & KEY_LEFT) || (newkeys & KEY_SPRINT && newkeys & KEY_RIGHT))
		|| ((oldkeys & KEY_SPRINT && newkeys & KEY_UP) || (oldkeys & KEY_SPRINT && newkeys & KEY_DOWN) || (oldkeys & KEY_SPRINT && newkeys & KEY_LEFT) || (oldkeys & KEY_SPRINT && newkeys & KEY_RIGHT))
		|| ((newkeys & KEY_SPRINT && oldkeys & KEY_UP) || (newkeys & KEY_SPRINT && oldkeys & KEY_DOWN) || (newkeys & KEY_SPRINT && oldkeys & KEY_LEFT) || (newkeys & KEY_SPRINT && oldkeys & KEY_RIGHT))
		&& GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		sprinttime[playerid] = SetTimerEx("SprintAnim",SPRINT_TIMER,false,"d",playerid);
	return CallLocalFunction("HOOK_OnPlayerKeyStateChange", "iii", playerid, newkeys, oldkeys);
}

forward SprintAnim(playerid);
public SprintAnim(playerid)
{
	new keys, updown, leftright;
	GetPlayerKeys(playerid,keys,updown,leftright);
	if (GetPlayerSprintStyle(playerid) == SPRINT_NORMAL)
	{
 	 	if ((keys & KEY_SPRINT && updown & KEY_UP) || (keys & KEY_SPRINT && updown & KEY_DOWN) || (keys & KEY_SPRINT && leftright & KEY_LEFT) || (keys & KEY_SPRINT && leftright & KEY_RIGHT))
		{
		   	KillTimer(sprinttime[playerid]);
			ApplyAnimation(playerid,"PED","run_playe",4.1,1,1,1,1,1);
			sprinttime[playerid] = SetTimerEx("SprintAnim",SPRINT_TIMER,false,"d",playerid);
		}
		else ApplyAnimation(playerid,"PED","run_playe",4.0,0,0,0,0,1), KillTimer(sprinttime[playerid]);
	}
	else if (GetPlayerSprintStyle(playerid) == SPRINT_CIVIL)
	{
 	 	if ((keys & KEY_SPRINT && updown & KEY_UP) || (keys & KEY_SPRINT && updown & KEY_DOWN) || (keys & KEY_SPRINT && leftright & KEY_LEFT) || (keys & KEY_SPRINT && leftright & KEY_RIGHT))
		{
		   	KillTimer(sprinttime[playerid]);
			ApplyAnimation(playerid,"PED","run_civi",4.1,1,1,1,1,1);
			sprinttime[playerid] = SetTimerEx("run_civi",SPRINT_TIMER,false,"d",playerid);
		}
		else ApplyAnimation(playerid,"PED","run_fat",4.0,0,0,0,0,1), KillTimer(sprinttime[playerid]);
	}
	else if (GetPlayerSprintStyle(playerid) == SPRINT_FAT)
	{
 	 	if ((keys & KEY_SPRINT && updown & KEY_UP) || (keys & KEY_SPRINT && updown & KEY_DOWN) || (keys & KEY_SPRINT && leftright & KEY_LEFT) || (keys & KEY_SPRINT && leftright & KEY_RIGHT))
		{
		   	KillTimer(sprinttime[playerid]);
			ApplyAnimation(playerid,"PED","run_fat",4.1,1,1,1,1,1);
			sprinttime[playerid] = SetTimerEx("SprintAnim",SPRINT_TIMER,false,"d",playerid);
		}
		else ApplyAnimation(playerid,"PED","run_fat",4.0,0,0,0,0,1), KillTimer(sprinttime[playerid]);
	}
	else if (GetPlayerSprintStyle(playerid) == SPRINT_FATOLD)
	{
 	 	if ((keys & KEY_SPRINT && updown & KEY_UP) || (keys & KEY_SPRINT && updown & KEY_DOWN) || (keys & KEY_SPRINT && leftright & KEY_LEFT) || (keys & KEY_SPRINT && leftright & KEY_RIGHT))
		{
		   	KillTimer(sprinttime[playerid]);
			ApplyAnimation(playerid,"PED","run_fatold",4.1,1,1,1,1,1);
			sprinttime[playerid] = SetTimerEx("SprintAnim",SPRINT_TIMER,false,"d",playerid);
		}
		else ApplyAnimation(playerid,"PED","run_fatold",4.0,0,0,0,0,1), KillTimer(sprinttime[playerid]);
	}
	else if (GetPlayerSprintStyle(playerid) == SPRINT_GANGSTA)
	{
 	 	if ((keys & KEY_SPRINT && updown & KEY_UP) || (keys & KEY_SPRINT && updown & KEY_DOWN) || (keys & KEY_SPRINT && leftright & KEY_LEFT) || (keys & KEY_SPRINT && leftright & KEY_RIGHT))
		{
		   	KillTimer(sprinttime[playerid]);
			ApplyAnimation(playerid,"PED","run_gang1",4.1,1,1,1,1,1);
			sprinttime[playerid] = SetTimerEx("SprintAnim",SPRINT_TIMER,false,"d",playerid);
		}
		else ApplyAnimation(playerid,"PED","run_gang1",4.0,0,0,0,0,1), KillTimer(sprinttime[playerid]);
	}
	else if (GetPlayerSprintStyle(playerid) == SPRINT_WUZI)
	{
 	 	if ((keys & KEY_SPRINT && updown & KEY_UP) || (keys & KEY_SPRINT && updown & KEY_DOWN) || (keys & KEY_SPRINT && leftright & KEY_LEFT) || (keys & KEY_SPRINT && leftright & KEY_RIGHT))
		{
		   	KillTimer(sprinttime[playerid]);
			ApplyAnimation(playerid,"PED","Sprint_Wuzi",4.1,1,1,1,1,1);
			sprinttime[playerid] = SetTimerEx("SprintAnim",SPRINT_TIMER,false,"d",playerid);
		}
		else ApplyAnimation(playerid,"PED","Sprint_Wuzi",4.0,0,0,0,0,1), KillTimer(sprinttime[playerid]);
	}
	else if (GetPlayerSprintStyle(playerid) == SPRINT_PANIC)
	{
 	 	if ((keys & KEY_SPRINT && updown & KEY_UP) || (keys & KEY_SPRINT && updown & KEY_DOWN) || (keys & KEY_SPRINT && leftright & KEY_LEFT) || (keys & KEY_SPRINT && leftright & KEY_RIGHT))
		{
		   	KillTimer(sprinttime[playerid]);
			ApplyAnimation(playerid,"PED","sprint_panic",4.1,1,1,1,1,1);
			sprinttime[playerid] = SetTimerEx("SprintAnim",SPRINT_TIMER,false,"d",playerid);
		}
		else ApplyAnimation(playerid,"PED","sprint_panic",4.0,0,0,0,0,1), KillTimer(sprinttime[playerid]);
	}
	else if (GetPlayerSprintStyle(playerid) == SPRINT_OLD)
	{
 	 	if ((keys & KEY_SPRINT && updown & KEY_UP) || (keys & KEY_SPRINT && updown & KEY_DOWN) || (keys & KEY_SPRINT && leftright & KEY_LEFT) || (keys & KEY_SPRINT && leftright & KEY_RIGHT))
		{
		   	KillTimer(sprinttime[playerid]);
			ApplyAnimation(playerid,"PED","run_old",4.1,1,1,1,1,1);
			sprinttime[playerid] = SetTimerEx("SprintAnim",SPRINT_TIMER,false,"d",playerid);
		}
		else ApplyAnimation(playerid,"PED","run_old",4.0,0,0,0,0,1), KillTimer(sprinttime[playerid]);
	}
	return 1;
}

stock SetPlayerSprintStyle(playerid, style)
{
	sprintStyle[playerid] = style;
}

stock GetPlayerSprintStyle(playerid)
{
	return sprintStyle[playerid];
}

#if defined _ALS_OnPlayerKeyStateChange
#undef OnPlayerKeyStateChange
#else
#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange HOOK_OnPlayerKeyStateChange
forward HOOK_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);

