/*
Zombie NPC Include by Gasman v0.1
native CreateZombieForPlayer(playerid,Float:x,Float:y,Float:z,Float:a,Float:distancespawn = 70.0,timerespawn = 20000);
native DestroyZombieForPlayer(playerid);
native IsZombieCreatedForPlayer(playerid);
native IsPlayerZombie(playerid);
public OnPlayerKillZombie(playerid,zombieid,weaponid)
public OnZombieKillPlayer(zombieid,playerid)
*Changelog
-v0.1:Release.
*/
#include <a_samp>
#include <fcnpc>
#include <YSI\y_timers>
#if !defined MAX_ZOMBIE_FOR_PLAYER
	#define MAX_ZOMBIE_FOR_PLAYER 	(10)
#endif
#if !defined DefaultZAttackRange
	#define DefaultZAttackRange (30.0)
#endif
#if !defined ShootAttackRange
	#define ShootAttackRange    (70.0)
#endif
#if !defined ZAttackDmg
	#define ZAttackDmg          (50.0)
#endif
/***********************ZOMBIE*****************************/
new ZombieIsAttack[MAX_PLAYERS];
new ZombieAttackPID[MAX_PLAYERS];
new Timer:ZombieTimer[MAX_PLAYERS];
new IsAZombie[MAX_PLAYERS];
new Zinc_RandSkinZombie[]=
{
	78,79,132,134,135,136,137,159,160,
	162,168,196,200,209,212,213,218,230,
	239,264
};
/***********************PLAYER*****************************/
new Float:DistanceZSpawn[MAX_PLAYERS];
new PlayerZombieCount[MAX_PLAYERS];
new ZombieForPlayerID[MAX_PLAYERS][MAX_ZOMBIE_FOR_PLAYER];
new Timer:PlayerZTimer[MAX_PLAYERS];
new Float:PlayerRangeZAttack[MAX_PLAYERS];
new TimerRespawnZombie[MAX_PLAYERS];
new IsPlayerCreatedZombie[MAX_PLAYERS];
/*********************MATCH********************************/
stock bool:IsZombieCreatedForPlayer(playerid)
{
	if(IsPlayerCreatedZombie[playerid] == 1)return true;
	else return false;
}
stock bool:IsPlayerZombie(playerid)
{
	if(IsPlayerNPC(playerid)&&IsAZombie[playerid]==1) return true;
	else return false;
}
stock Float:Zinc_absoluteangle(Float:angle)
{
	while(angle < 0.0)angle += 360.0;
	while(angle > 360.0)angle -= 360.0;
	return angle;
}
stock Float:Zinc_GetAngleToPoint(Float:fPointX, Float:fPointY, Float:fDestX, Float:fDestY)//Thank Southclaw
	return Zinc_absoluteangle(-(90-(atan2((fDestY - fPointY), (fDestX - fPointX)))));
/***********CALLBACKS*************************************/
forward OnPlayerKillZombie(playerid,zombieid,weaponid);
forward OnZombieKillPlayer(zombieid,playerid);
public OnFilterScriptInit()
{
	if(FCNPC_InitZMap("scriptfiles/FCNPC/ZMap.hmap"))
	{
	print("ZMAP Init");
	}
	#if defined Zinc_OnFilterScriptInit
        Zinc_OnFilterScriptInit();
    #endif
    return true;
}
#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif

#define OnFilterScriptInit Zinc_OnFilterScriptInit
    
#if defined Zinc_OnFilterScriptInit
    forward Zinc_OnFilterScriptInit();
#endif

public OnGameModeInit()
{
	if(FCNPC_InitZMap("scriptfiles/FCNPC/ZMap.hmap"))
	{
	print("ZMAP Init");
	}
	#if defined Zinc_OnGameModeInit
        Zinc_OnGameModeInit();
    #endif
    return true;
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit Zinc_OnGameModeInit
    
#if defined Zinc_OnGameModeInit
    forward Zinc_OnGameModeInit();
#endif
public OnPlayerDeath(playerid, killerid, reason)
{
	if(IsPlayerZombie(killerid) == true)
	{
		CallLocalFunction("OnZombieKillPlayer","ii",killerid,playerid);
	}
	PlayerRangeZAttack[playerid] = DefaultZAttackRange;
	#if defined Zinc_OnPlayerDeath
        Zinc_OnPlayerDeath(playerid, killerid, reason);
    #endif
    return true;
}
#if defined _ALS_OnPlayerDeath
    #undef OnPlayerDeath
#else
    #define _ALS_OnPlayerDeath
#endif

#define OnPlayerDeath Zinc_OnPlayerDeath
    
#if defined Zinc_OnPlayerDeath
    forward Zinc_OnPlayerDeath(playerid, killerid, reason);
#endif
public OnPlayerConnect(playerid)
{
    PlayerRangeZAttack[playerid] = DefaultZAttackRange;
    PlayerZombieCount[playerid] = 0;
	#if defined Zinc_OnPlayerConnect
        Zinc_OnPlayerConnect(playerid);
    #endif
    return true;
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect Zinc_OnPlayerConnect
    
#if defined Zinc_OnPlayerConnect
    forward Zinc_OnPlayerConnect(playerid);
#endif
public OnPlayerDisconnect(playerid,reason)
{
	if(IsZombieCreatedForPlayer(playerid) == true)
	{
		DestroyZombieForPlayer(playerid);
	}
	#if defined Zinc_OnPlayerDisconnect
        Zinc_OnPlayerDisconnect(playerid,reason);
    #endif
    return true;
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect Zinc_OnPlayerDisconnect
    
#if defined Zinc_OnPlayerDisconnect
    forward Zinc_OnPlayerDisconnect(playerid,reason);
#endif
public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
    if(issuerid != INVALID_PLAYER_ID && IsPlayerNPC(issuerid))
    {
        if(weaponid == 1)
        {
            new Float:hp;
            GetPlayerHealth(playerid,hp);
			SetPlayerHealth(playerid,hp-ZAttackDmg);
        }
    }
    #if defined Zinc_OnPlayerTakeDamage
        Zinc_OnPlayerTakeDamage(playerid, issuerid,amount, weaponid, bodypart);
    #endif
    return true;
}
#if defined _ALS_OnPlayerTakeDamage
    #undef OnPlayerTakeDamage
#else
    #define _ALS_OnPlayerTakeDamage
#endif

#define OnPlayerTakeDamage Zinc_OnPlayerTakeDamage
    
#if defined Zinc_OnPlayerTakeDamage
    forward Zinc_OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart);
#endif
public FCNPC_OnTakeDamage(npcid, damagerid, weaponid, bodypart, Float:health_loss)
{
    foreach(new i: Player)
	{
	    for(new z=0;z<MAX_ZOMBIE_FOR_PLAYER;z++)
	    {
	    	if(npcid == ZombieForPlayerID[i][z])
	    	{
	    	    SetZombieAttack(npcid,damagerid,ShootAttackRange);
	    	}
		}
	}
	#if defined Zinc_FCNPC_OnTakeDamage
        Zinc_FCNPC_OnTakeDamage(npcid, damagerid, weaponid, bodypart,health_loss);
    #endif
    return true;
}
#if defined _ALS_FCNPC_OnTakeDamage
    #undef FCNPC_OnTakeDamage
#else
    #define _ALS_FCNPC_OnTakeDamage
#endif

#define FCNPC_OnTakeDamage Zinc_FCNPC_OnTakeDamage
    
#if defined Zinc_FCNPC_OnTakeDamage
    forward Zinc_FCNPC_OnTakeDamage(npcid, damagerid, weaponid, bodypart, Float:health_loss);
#endif
public FCNPC_OnDeath(npcid, killerid, weaponid)
{
 	foreach(new i: Player)
	{
	    for(new z=0;z<MAX_ZOMBIE_FOR_PLAYER;z++)
	    {
	    	if(npcid == ZombieForPlayerID[i][z])
	    	{
	    	    ZombieIsAttack[npcid] = 0;
	    	    ZombieAttackPID[npcid] = i;
	    	    ApplyAnimation(npcid,"PED","WALK_DRUNK",4.1,1,1,1,1,1);
				CallLocalFunction("OnPlayerKillZombie","iii",killerid,npcid,weaponid);
	    	}
	    }
	}
	#if defined Zinc_FCNPC_OnDeath
        Zinc_FCNPC_OnDeath(npcid, killerid, weaponid);
    #endif
    return true;
}
#if defined _ALS_FCNPC_OnDeath
    #undef FCNPC_OnDeath
#else
    #define _ALS_FCNPC_OnDeath
#endif

#define FCNPC_OnDeath Zinc_FCNPC_OnDeath
    
#if defined Zinc_FCNPC_OnDeath
    forward Zinc_FCNPC_OnDeath(npcid, killerid, weaponid);
#endif
public FCNPC_OnSpawn(npcid)
{
    foreach(new i: Player)
	{
	    for(new z=0;z<MAX_ZOMBIE_FOR_PLAYER;z++)
	    {
	    	if(npcid == ZombieForPlayerID[i][z])
	    	{
	    	FCNPC_SetWeapon(npcid,1);
	    	FCNPC_SetAmmo(npcid,1);
	    	ApplyAnimation(npcid,"PED","WALK_DRUNK",4.1,1,1,1,1,1);
	    	}
		}
	}
	#if defined Zinc_FCNPC_OnSpawn
        Zinc_FCNPC_OnSpawn(npcid);
    #endif
    return true;
}
#if defined _ALS_FCNPC_OnSpawn
    #undef FCNPC_OnSpawn
#else
    #define _ALS_FCNPC_OnSpawn
#endif

#define FCNPC_OnSpawn Zinc_FCNPC_OnSpawn
    
#if defined Zinc_FCNPC_OnSpawn
    forward Zinc_FCNPC_OnSpawn(npcid);
#endif
public FCNPC_OnRespawn(npcid)
{
    foreach(new i: Player)
	{
	    for(new z=0;z<MAX_ZOMBIE_FOR_PLAYER;z++)
	    {
	    	if(npcid == ZombieForPlayerID[i][z])
	    	{
	    	FCNPC_SetWeapon(npcid,1);
	    	FCNPC_SetAmmo(npcid,1);
	    	}
		}
	}
	#if defined Zinc_FCNPC_OnRespawn
        Zinc_FCNPC_OnRespawn(npcid);
    #endif
    return true;
}
#if defined _ALS_FCNPC_OnRespawn
    #undef FCNPC_OnRespawn
#else
    #define _ALS_FCNPC_OnRespawn
#endif

#define FCNPC_OnRespawn Zinc_FCNPC_OnRespawn
    
#if defined Zinc_FCNPC_OnRespawn
    forward Zinc_FCNPC_OnRespawn(npcid);
#endif
/*********************TIMER****************************************************/
timer RespawnZombieForPlayer[TimerRespawnZombie[playerid]](playerid)
{
	new Float:x,Float:y,Float:z,Float:a;
    for(new i = 0;i<MAX_ZOMBIE_FOR_PLAYER;i++)
	{
	    if(FCNPC_IsDead(ZombieForPlayerID[playerid][i]))
		{
			FCNPC_Respawn(ZombieForPlayerID[playerid][i]);
		}
	    if(FCNPC_IsSpawned(ZombieForPlayerID[playerid][i]) && ZombieIsAttack[ZombieForPlayerID[playerid][i]] == 0)
	    {
	        GetPlayerPos(playerid,x,y,z);
		    a=float(random(360));
			x=x+DistanceZSpawn[playerid]*floatsin(a,degrees);
			y=y+DistanceZSpawn[playerid]*floatcos(a,degrees);
			z=z+0.7;
			FCNPC_GetZGround(x,y,z);
			FCNPC_SetPosition(ZombieForPlayerID[playerid][i],x,y,z+0.7);
		    FCNPC_SetAngle(ZombieForPlayerID[playerid][i],a);
 	    	FCNPC_Stop(ZombieForPlayerID[playerid][i]);
     		FCNPC_StopAttack(ZombieForPlayerID[playerid][i]);
		    ZombieAttackPID[ZombieForPlayerID[playerid][i]] = playerid;
	    }
	}
	return 1;
}
timer ZombieMove[500](zombieid)
{
	new Float:x,Float:y,Float:z,Float:zombiepos[3];
	if(FCNPC_IsDead(zombieid)) return 1;
	GetPlayerPos(ZombieAttackPID[zombieid],x,y,z);
	if(IsPlayerInRangeOfPoint(zombieid,1.7,x,y,z))
 	{
 	    ZombieIsAttack[zombieid] = 2;
		FCNPC_GetPosition(zombieid,zombiepos[0],zombiepos[1],zombiepos[2]);
		FCNPC_SetAngle(zombieid,Zinc_GetAngleToPoint(zombiepos[0],zombiepos[1],x,y));
 	    FCNPC_MeleeAttack(zombieid,100);
  	}
  	else if(IsPlayerInRangeOfPoint(zombieid,10.0,x,y,z))
 	{
 	    if(ZombieIsAttack[zombieid] == 2)
 	    {
			FCNPC_Stop(zombieid);
			FCNPC_StopAttack(zombieid);
 	    }
	    ZombieIsAttack[zombieid] = 1;
	    FCNPC_GoTo(zombieid,x,y,z,MOVE_TYPE_SPRINT,1,1);
  	}
	else if(IsPlayerInRangeOfPoint(zombieid,PlayerRangeZAttack[ZombieAttackPID[zombieid]],x,y,z))
	{
	    if(ZombieIsAttack[zombieid] == 2)
 	    {
 	    FCNPC_Stop(zombieid);
        FCNPC_StopAttack(zombieid);
 	    }
	    ZombieIsAttack[zombieid] = 1;
	    FCNPC_GoToPlayerEx(zombieid, ZombieAttackPID[zombieid],5,5,MOVE_TYPE_SPRINT,1);
	}
	else
	{
	    ZombieIsAttack[zombieid] = 0;
	  	ApplyAnimation(zombieid,"PED","WALK_DRUNK",4.1,1,1,1,1,1);
	    PlayerRangeZAttack[ZombieAttackPID[zombieid]] = DefaultZAttackRange;
	}
	return 1;
}
/*******************STOCKS******************************************************/

stock DestroyZombieForPlayer(playerid)
{
    for(new i = 0;i<MAX_ZOMBIE_FOR_PLAYER;i++)
	{
	    if(FCNPC_IsSpawned(ZombieForPlayerID[playerid][i]))
	    {
	        FCNPC_Destroy(ZombieForPlayerID[playerid][i]);
			IsAZombie[ZombieForPlayerID[playerid][i]] =0;
	        stop ZombieTimer[ZombieForPlayerID[playerid][i]];
	        PlayerZombieCount[playerid]--;
	    }
	}
	stop PlayerZTimer[playerid];
	IsPlayerCreatedZombie[playerid] = 0;
	return 1;
}
stock CreateZombieForPlayer(playerid,Float:x,Float:y,Float:z,Float:a,Float:distancespawn = 70.0,timerespawn = 20000)
{
	if(PlayerZombieCount[playerid] > 0 ||IsZombieCreatedForPlayer(playerid) == true) return 0;
    new str[128];
	IsPlayerCreatedZombie[playerid] = 1;
	DistanceZSpawn[playerid] = distancespawn;
	TimerRespawnZombie[playerid] = timerespawn;
	for(new i = 0;i<MAX_ZOMBIE_FOR_PLAYER;i++)
	{
	    format(str,sizeof(str),"Zp%s%d",Zinc_GetName(playerid),MAX_PLAYERS-(i+playerid));
	    ZombieForPlayerID[playerid][i] = FCNPC_Create(str);
		a=float(random(360));
		x=x+DistanceZSpawn[playerid]*floatsin(a,degrees);
		y=y+DistanceZSpawn[playerid]*floatcos(a,degrees);
		z=z+0.7;
        FCNPC_GetZGround(x,y,z);
	    FCNPC_Spawn(ZombieForPlayerID[playerid][i],Zinc_RandSkinZombie[random(sizeof(Zinc_RandSkinZombie))],x,y,z+0.7);
	    FCNPC_SetAngle(ZombieForPlayerID[playerid][i],a);
	    ZombieAttackPID[ZombieForPlayerID[playerid][i]] = playerid;
	    PlayerZombieCount[playerid]++;
	    ZombieTimer[ZombieForPlayerID[playerid][i]] = repeat ZombieMove(ZombieForPlayerID[playerid][i]);
	    SetPlayerColor(ZombieForPlayerID[playerid][i],0xFF0000FF);
		IsAZombie[ZombieForPlayerID[playerid][i]] = 1;
	}
	PlayerZTimer[playerid] = repeat RespawnZombieForPlayer(playerid);
	return 1;
}
stock SetZombieAttack(zombieid,attackid,Float:range)
{
    ZombieIsAttack[zombieid] = 1;
    ZombieAttackPID[zombieid] = attackid;
    PlayerRangeZAttack[ZombieAttackPID[zombieid]] = range;
	return 1;
}
stock FCNPC_GoToPlayerEx(npcid, playerid, Float:dist, Float:rangle, movetype = MOVE_TYPE_WALK, UseZMap = 0)//Thank Pottus
{
	new Float:x, Float:y, Float:z, Float:fa;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, fa);
	rangle += fa;
	x = (x + dist * floatsin(-rangle,degrees));
	y = (y + dist * floatcos(-rangle,degrees));
    FCNPC_GoTo(npcid, x, y, z, movetype,1,UseZMap);
    return 1;
}
stock Zinc_GetName(playerid)
{
	new name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid,name,sizeof(name));
	return name;
}