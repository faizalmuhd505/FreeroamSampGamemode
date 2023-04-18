#include <a_samp>
#include <YSI\y_bit>

static stock
    Float:AC_Position[3],
    pLastPosTick[MAX_PLAYERS],
    BitArray:AC_SafeTP<MAX_PLAYERS>
;

forward OnPlayerTeleport(playerid, Float:distance);

public OnPlayerSpawn(playerid)
{
    GetPlayerPos(playerid, AC_Position[0], AC_Position[1], AC_Position[2]);
    #if defined pds_OnPlayerSpawn
        pds_OnPlayerSpawn(playerid);
    #endif
    return true;
}

#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn  
#else
    #define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn pds_OnPlayerSpawn
    
#if defined pds_OnPlayerSpawn
    forward pds_OnPlayerSpawn(playerid);
#endif

public OnPlayerUpdate(playerid)
{   
    if(gettime( ) - pLastPosTick[ playerid ] > 1) //updates the player location every 2 seconds.
    {
        //on-foot
        if( !IsPlayerInRangeOfPoint(playerid, 50.0, AC_Position[0], AC_Position[1], AC_Position[2]) && !Bit_Get(AC_SafeTP, playerid) && !IsPlayerNPC(playerid) 
        && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            CallLocalFunction("OnPlayerTeleport", "if", playerid, GetPlayerDistanceFromPoint(playerid, AC_Position[ 0 ], AC_Position[ 1 ], AC_Position[ 2 ])); 
        }
        //on-vehicle
        else if( !IsPlayerInRangeOfPoint(playerid, 300.0, AC_Position[0], AC_Position[1], AC_Position[2]) && !Bit_Get(AC_SafeTP, playerid) && !IsPlayerNPC(playerid) 
        && GetVehicleSpeed( GetPlayerVehicleID(playerid) ) <= 50 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
        {
            CallLocalFunction("OnPlayerTeleport", "if", playerid, GetPlayerDistanceFromPoint(playerid, AC_Position[0], AC_Position[1], AC_Position[2]));
        }
        GetPlayerPos(playerid, AC_Position[ 0 ], AC_Position[ 1 ], AC_Position[ 2 ]);
        Bit_Set(AC_SafeTP, playerid, false);
        pLastPosTick[ playerid ] = gettime( ) + 2;
    }
    #if defined pds_OnPlayerUpdate
        pds_OnPlayerUpdate(playerid);
    #endif
    return true;
}

#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate pds_OnPlayerUpdate
    
#if defined pds_OnPlayerUpdate
    forward pds_OnPlayerUpdate(playerid);
#endif

stock pds_SetPlayerPos(playerid, Float:PosX, Float:PosY, Float:PosZ)
{
    GetPlayerPos(playerid, AC_Position[0], AC_Position[1], AC_Position[2]);
    Bit_Set(AC_SafeTP, playerid, true);
    return SetPlayerPos(playerid, PosX, PosY, PosZ);
}

#if defined _ALS_SetPlayerPos
    #undef SetPlayerPos
#else
    #define _ALS_SetPlayerPos
#endif

#define SetPlayerPos pds_SetPlayerPos

stock pds_SetPlayerPosFindZ(playerid, Float:PosX, Float:PosY, Float:PosZ) 
{ 
    GetPlayerPos(playerid, AC_Position[0], AC_Position[1], AC_Position[2]);
    Bit_Set(AC_SafeTP, playerid, true);
    return SetPlayerPosFindZ(playerid, PosX, PosY, PosZ);
}

#if defined _ALS_SetPlayerPosFindZ
    #undef SetPlayerPosFindZ  
#else
    #define _ALS_SetPlayerPosFindZ
#endif

#define SetPlayerPosFindZ pds_SetPlayerPosFindZ


stock pds_PutPlayerInVehicle(playerid, vehicleid, seatid) 
{ 
    GetPlayerPos(playerid, AC_Position[0], AC_Position[1], AC_Position[2]);
    Bit_Set(AC_SafeTP, playerid, true);
    return PutPlayerInVehicle(playerid, vehicleid, seatid);
}

#if defined _ALS_PutPlayerInVehicle
    #undef PutPlayerInVehicle  
#else
    #define _ALS_PutPlayerInVehicle
#endif

#define PutPlayerInVehicle pds_PutPlayerInVehicle

stock pds_SetPlayerInterior(playerid, interiorid) 
{ 
    GetPlayerPos(playerid, AC_Position[0], AC_Position[1], AC_Position[2]);
    Bit_Set(AC_SafeTP, playerid, true);
    return SetPlayerInterior(playerid, interiorid);
}


#if defined _ALS_SetPlayerInterior
    #undef SetPlayerInterior  
#else
    #define _ALS_SetPlayerInterior
#endif

#define SetPlayerInterior pds_SetPlayerInterior

forward Float: GetVehicleSpeed(vehicleid);
public Float: GetVehicleSpeed(vehicleid)
{
	new Float: speed = -1;
	if(vehicleid != INVALID_VEHICLE_ID)
	{
		new Float: x,
			Float: y,
			Float: z,
			Float: angle;
		GetVehicleVelocity(vehicleid, x, y, z);
		GetVehicleZAngle(vehicleid, angle);
		speed = x / floatsin(-angle, degrees);
		speed *= 100.0;
	}
	return speed;
}