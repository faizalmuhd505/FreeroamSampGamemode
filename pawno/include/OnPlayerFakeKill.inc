#include <a_samp>

static
        CountDeaths [ MAX_PLAYERS ],
        StartDeathTick [ MAX_PLAYERS ]
;

public OnPlayerConnect(playerid)
{
        CountDeaths[ playerid ] = 0, StartDeathTick[ playerid ] = 0;

        #if defined fk_OnPlayerConnect
                fk_OnPlayerConnect(playerid);
        #endif
        return true;
}

public OnPlayerDisconnect(playerid, reason)
{
        CountDeaths[ playerid ] = 0, StartDeathTick[ playerid ] = 0;

        #if defined fk_OnPlayerDisconnect
                fk_OnPlayerDisconnect(playerid,  reason);
        #endif
        return true;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    if(!IsPlayerNPC(playerid))
    {
        if(gettime() - StartDeathTick[playerid] < 5) //5 seconds
        {
            CountDeaths[playerid] ++;
            if(CountDeaths[playerid] == 10) 
            {
                CallLocalFunction("OnPlayerFakeKill", "i", playerid);
                return CountDeaths[playerid] = 0;  
            }
        }
        else CountDeaths[playerid] = 1;
        StartDeathTick[playerid] = gettime();
    }
        #if defined fk_OnPlayerDeath
                fk_OnPlayerDeath(playerid, killerid, reason);
        #endif
        return true;
}

#if defined _ALS_OnPlayerConnect
        #undef OnPlayerConnect
#else
        #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect fk_OnPlayerConnect

#if defined _ALS_OnPlayerDisconnect
        #undef OnPlayerDisconnect
#else
        #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect fk_OnPlayerDisconnect

#if defined _ALS_OnPlayerDeath
        #undef OnPlayerDeath
#else
        #define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath fk_OnPlayerDeath

#if defined fk_OnPlayerConnect
        forward fk_OnPlayerConnect(playerid);
#endif

#if defined fk_OnPlayerDisconnect
        forward fk_OnPlayerDisconnect(playerid,  reason);
#endif

#if defined fk_OnPlayerDeath
        forward fk_OnPlayerDeath(playerid, killerid, reason);
#endif

forward OnPlayerFakeKill(playerid);
