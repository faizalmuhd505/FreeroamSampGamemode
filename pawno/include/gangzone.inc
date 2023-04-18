/*
        Interactive Gangzones (gangzones.inc)
        * Add boders to your gangzones and fully customizable gangzones. New dynamic functions for gangzones.
 
        Author: (creator)
        * Gammix
 
        Contributors:
        * Pottus - Virtual world fixing
        * Y_Less - Hooking suggestion
        * Incognito - Streamer plugin, used dynamic areas
 
        (c) Copyright 2015
        * This file is provided as is (no warranties).
*/
/*
FUNCTIONS:
native GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy, color = -1, interior = -1, virtualworld = -1, Float:bordersize = 1.0, bordercolor = 0x00000060);
native GangZoneDestory(zone);
native GangZoneExist(zone);
native GangZoneShowForPlayer(playerid, zone, color = -1, bordercolor = -1);
native GangZoneShowForAll(zone, color = -1, bordercolor = -1);
native GangZoneHideForPlayer(playerid, zone);
native GangZoneHideForAll(zone);
native GangZoneSetColorForPlayer(playerid, zone, color, bordercolor = -1);
native GangZoneSetColorForAll(zone, color, bordercolor = -1);
native GangZoneFlashForPlayer(playerid, zone, flashcolor);
native GangZoneFlashForAll(zone, flashcolor);
native GangZoneStopFlashForPlayer(playerid, zone);
native GangZoneStopFlashForAll(zone);
native GangZoneSetInterior(zone, interior);
native GangZoneGetInterior(zone);
native GangZoneSetVirtualWorld(zone, virtualworld);
native GangZoneGetVirtualWorld(zone);
native CountAllGangZones();
native DestroyAllGangZones();
native ShowAllGangZonesForPlayer(playerid, color = -1, bordercolor = -1);
native ShowAllGangZonesForAll(color = -1, bordercolor = -1);
native HideAllGangZonesForPlayer(playerid);
native HideAllGangZonesForAll();
native IsPlayerInGangZone(playerid, zone);
 
CALLBACKS:
public OnPlayerEnterGangZone(playerid, zone);
public OnPlayerLeaveGangZone(playerid, zone);
*/
 
#include <streamer>
 
#define MAX_ZONES 1024//maximum gangzones your server can have, the limit is upto 1024 and minimum 5
//Note: Creating one interactive gangzone makes total 5 zones, 4 for borders and 1 for the main zone!
 
enum GangzoneInfo
{
        bool:E_exist,
        E_border[4],
        E_interior,
        E_virtualworld,
        Float:E_minx,
        Float:E_miny,
        Float:E_maxx,
        Float:E_maxy,
        E_dynamic
}
new gGangzone[MAX_ZONES][GangzoneInfo];
 
new bool:gPlayerShown[MAX_PLAYERS][MAX_ZONES];
new gPlayerColor[MAX_PLAYERS][MAX_ZONES];
new gPlayerBorderColor[MAX_PLAYERS][MAX_ZONES];
 
new gPlayerWorld[MAX_PLAYERS];
 
//Note: if you use this in a filterscript, please define "FILTERSCRIPT" in your script
#if defined FILTERSCRIPT// if used in a filterscript
 
        public OnFilterScriptInit()
        {
            DestroyAllGangZones();//destory all gangzones
 
            #if defined Hook_OnFilterScriptInit
                        Hook_OnFilterScriptInit();
                #endif
                return 1;
        }
        #if defined _ALS_OnFilterScriptInit
                #undef OnFilterScriptInit
        #else
                #define _ALS_OnFilterScriptInit
        #endif
        #define OnFilterScriptInit Hook_OnFilterScriptInit
        #if defined Hook_OnFilterScriptInit
                forward Hook_OnFilterScriptInit();
        #endif
 
        public OnFilterScriptExit()
        {
            DestroyAllGangZones();//destory all gangzones
 
            #if defined Hook_OnFilterScriptExit
                        Hook_OnFilterScriptExit();
                #endif
                return 1;
        }
        #if defined _ALS_OnFilterScriptExit
                #undef OnFilterScriptExit
        #else
                #define _ALS_OnFilterScriptExit
        #endif
        #define OnFilterScriptExit Hook_OnFilterScriptExit
        #if defined Hook_OnFilterScriptExit
                forward Hook_OnFilterScriptExit();
        #endif
 
#else// if used in a gamemode
 
        public OnGameModeInit()
        {
            DestroyAllGangZones();//destory all gangzones
 
            #if defined Hook_OnGameModeInit
                        Hook_OnGameModeInit();
                #endif
                return 1;
        }
        #if defined _ALS_OnGameModeInit
                #undef OnGameModeInit
        #else
                #define _ALS_OnGameModeInit
        #endif
        #define OnGameModeInit Hook_OnGameModeInit
        #if defined Hook_OnGameModeInit
                forward Hook_OnGameModeInit();
        #endif
 
        public OnGameModeExit()
        {
            DestroyAllGangZones();//destory all gangzones
 
            #if defined Hook_OnGameModeExit
                        Hook_OnGameModeExit();
                #endif
                return 1;
        }
        #if defined _ALS_OnGameModeExit
                #undef OnGameModeExit
        #else
                #define _ALS_OnGameModeExit
        #endif
        #define OnGameModeExit Hook_OnGameModeExit
        #if defined Hook_OnGameModeExit
                forward Hook_OnGameModeExit();
        #endif
 
#endif
 
stock GangZoneCreate_(Float:minx, Float:miny, Float:maxx, Float:maxy, color = -1, interior = -1, virtualworld = -1, Float:bordersize = 1.0, bordercolor = 0x00000060)
{
        new E_zone = GangZoneCreate(minx, miny, maxx, maxy);//the main zone
 
        gGangzone[E_zone][E_minx] = minx;
        gGangzone[E_zone][E_miny] = miny;
        gGangzone[E_zone][E_maxx] = maxx;
        gGangzone[E_zone][E_maxy] = maxy;
 
        gGangzone[E_zone][E_interior] = interior;
        gGangzone[E_zone][E_virtualworld] = virtualworld;
 
        for(new players = 0; players < MAX_PLAYERS; players++)//setting player data
        {
        gPlayerShown[players][E_zone] = false;
        gPlayerColor[players][E_zone] = color;
        gPlayerBorderColor[players][E_zone] = bordercolor;
        }
 
        #define SEPERATION  (2.0*bordersize)//the seperation value to differenciate borders from gangzone, set accordingly! (Default: 2.0)
        gGangzone[E_zone][E_border][0] = GangZoneCreate(minx - SEPERATION, miny, minx + SEPERATION, maxy);//border 1
        gGangzone[E_zone][E_border][1] = GangZoneCreate(minx - SEPERATION, maxy - SEPERATION, maxx, maxy + SEPERATION);//border 2
        gGangzone[E_zone][E_border][2] = GangZoneCreate(maxx - SEPERATION, miny, maxx + SEPERATION, maxy);//border 3
        gGangzone[E_zone][E_border][3] = GangZoneCreate(minx - SEPERATION, miny - SEPERATION, maxx, miny + SEPERATION);//border 4
 
        gGangzone[E_zone][E_dynamic] = CreateDynamicRectangle(minx, miny, maxx, maxy, virtualworld, interior, -1);//creating the dynamic zone
 
        gGangzone[E_zone][E_exist] = true;//finally, zone exists!
        return E_zone;
}
#if defined _ALS_GangZoneCreate
    #undef GangZoneCreate
#else
    #define _ALS_GangZoneCreate
#endif
#define GangZoneCreate GangZoneCreate_
 
stock GangZoneDestroy_(zone)
{
        if(! gGangzone[zone][E_exist]) return false;//check if exists
 
        for(new players = 0; players < MAX_PLAYERS; players++)//remove player data
        {
        gPlayerColor[players][zone] = -1;
        gPlayerShown[players][zone] = false;
        gPlayerBorderColor[players][zone] = -1;
        }
 
        gGangzone[zone][E_minx] = 0.0;
        gGangzone[zone][E_miny] = 0.0;
        gGangzone[zone][E_maxx] = 0.0;
        gGangzone[zone][E_maxy] = 0.0;
 
        gGangzone[zone][E_interior] = -1;
        gGangzone[zone][E_virtualworld] = -1;
 
        gGangzone[zone][E_dynamic] = -1;
 
        GangZoneDestroy(zone);//destroy main zone
 
        for(new border = 0; border < 4; border++)//destroy all 4 borders
        {
                GangZoneDestroy(gGangzone[zone][E_border][border]);
        }
 
        DestroyDynamicArea(gGangzone[zone][E_dynamic]);//destory dynamic area
 
        gGangzone[zone][E_exist] = false;//finally, zone doesn't exists
        return true;
}
#if defined _ALS_GangZoneDestroy
    #undef GangZoneDestroy
#else
    #define _ALS_GangZoneDestroy
#endif
#define GangZoneDestroy GangZoneDestroy_
 
stock GangZoneExist(zone)
{
    if(zone < 0 || zone >= MAX_ZONES)
    {
                printf("Error::GangZoneExist()::Out Of Bounds::%i", zone);//by pottus
                return false;//if invalid zone id
    }
 
    return gGangzone[zone][E_exist];//check if zone exists!
}
 
stock GangZoneShowForPlayer_(playerid, zone, color = -1, bordercolor = -1)
{
        /*
        NOTE: if color is "-1" and if bordercolor is "-1", then the system will set
                        the zone color automatically to default(the one set on creating the zone)!
        */
 
        if(! GangZoneExist(zone)) return false;
 
        if(color != -1) gPlayerColor[playerid][zone] = color;
        if(bordercolor != -1) gPlayerBorderColor[playerid][zone] = bordercolor;
 
        GangZoneShowForPlayer(playerid, zone, gPlayerColor[playerid][zone]);
        for(new border = 0; border < 4; border++) GangZoneShowForPlayer(playerid, gGangzone[zone][E_border][border], gPlayerBorderColor[playerid][zone]);
 
        gPlayerShown[playerid][zone] = true;
 
        return true;
}
#if defined _ALS_GangZoneShowForPlayer
    #undef GangZoneShowForPlayer
#else
    #define _ALS_GangZoneShowForPlayer
#endif
#define GangZoneShowForPlayer GangZoneShowForPlayer_
 
stock GangZoneShowForAll_(zone, color = -1, bordercolor = -1)
{
        if(! GangZoneExist(zone)) return false;
 
        for(new players = 0; players < MAX_PLAYERS; players++)
        {
                GangZoneShowForPlayer(players, zone, color);
                for(new border = 0; border < 4; border++) GangZoneShowForPlayer(players, gGangzone[zone][E_border][border], bordercolor);
        }
        return true;
}
#if defined _ALS_GangZoneShowForAll
    #undef GangZoneShowForAll
#else
    #define _ALS_GangZoneShowForAll
#endif
#define GangZoneShowForAll GangZoneShowForAll_
 
stock GangZoneHideForPlayer_(playerid, zone)
{
        if(! GangZoneExist(zone)) return false;
 
        GangZoneHideForPlayer(playerid, zone);
        for(new border = 0; border < 4; border++) GangZoneHideForPlayer(playerid, gGangzone[zone][E_border][border]);
 
        gPlayerShown[playerid][zone] = false;
        return true;
}
#if defined _ALS_GangZoneHideForPlayer
    #undef GangZoneHideForPlayer
#else
    #define _ALS_GangZoneHideForPlayer
#endif
#define GangZoneHideForPlayer GangZoneHideForPlayer_
 
stock GangZoneHideForAll_(zone)
{
        if(! GangZoneExist(zone)) return false;
 
        GangZoneHideForAll(zone);
        for(new border = 0; border < 4; border++) GangZoneHideForAll(gGangzone[zone][E_border][border]);
 
        for(new players = 0; players < MAX_PLAYERS; players++) gPlayerShown[players][zone] = false;
 
        return true;
}
#if defined _ALS_GangZoneHideForAll
    #undef GangZoneHideForAll
#else
    #define _ALS_GangZoneHideForAll
#endif
#define GangZoneHideForAll GangZoneHideForAll_
 
stock GangZoneSetColorForPlayer(playerid, zone, color, bordercolor = -1)
{
        if(! GangZoneExist(zone)) return false;
 
    if(gPlayerShown[playerid][zone]) GangZoneShowForPlayer(playerid, zone, color, bordercolor);
 
    return true;
}
 
stock GangZoneSetColorForAll(zone, color, bordercolor = -1)
{
        if(! GangZoneExist(zone)) return false;
 
    for(new players = 0; players < MAX_PLAYERS; players++)
        {
            if(gPlayerShown[players][zone])
            {
                GangZoneShowForPlayer(players, zone, color, bordercolor);
            }
    }
        return true;
}
//the flashing functions are same as that of samp!
// GangZoneFlashForPlayer(playerid, zone, flashcolor);
 
// GangZoneFlashForAll(zone, flashcolor);
 
// GangZoneStopFlashForPlayer(playerid, zone);
 
// GangZoneStopFlashForAll(zone);
 
stock GangZoneSetInterior(zone, interior)
{
        /*
        NOTE: if interior is set to "-1", it means all the interiors, so the zone will be visible in all interiors!
        */
 
        if(! GangZoneExist(zone)) return false;
 
    gGangzone[zone][E_interior] = interior;
        return true;
}
 
stock GangZoneGetInterior(zone)
{
        if(! GangZoneExist(zone)) return false;
 
        return gGangzone[zone][E_interior];
}
 
stock GangZoneSetVirtualWorld(zone, virtualworld)
{
        /*
        NOTE: if virtualworld is set to "-1", it means all the virtualworld, so the zone will be visible in all virtualworld!
        */
 
        if(! GangZoneExist(zone)) return false;
 
    gGangzone[zone][E_virtualworld] = virtualworld;
        return true;
}
 
stock GangZoneGetVirtualWorld(zone)
{
        if(! GangZoneExist(zone)) return false;
 
        return gGangzone[zone][E_virtualworld];
}
 
stock CountAllGangZones()
{
        new count = 0;
    for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                count ++;
                }
        }
        return count;
}
 
stock DestroyAllGangZones()
{
        for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                GangZoneDestroy(zone);
                }
        }
        return true;
}
 
stock ShowAllGangZonesForPlayer(playerid, color = -1, bordercolor = -1)
{
        for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                GangZoneShowForPlayer(playerid, zone, color, bordercolor);
                }
        }
        return true;
}
 
stock ShowAllGangZonesForAll(color = -1, bordercolor = -1)
{
        for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                GangZoneShowForAll(zone color, bordercolor);
                }
        }
        return true;
}
 
stock HideAllGangZonesForPlayer(playerid)
{
        for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                GangZoneHideForPlayer(playerid, zone);
                }
        }
        return true;
}
 
stock HideAllGangZonesForAll()
{
        for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                GangZoneHideForAll(zone);
                }
        }
        return true;
}
 
 
stock IsPlayerInGangZone(playerid, zone)
{
        if(! GangZoneExist(zone)) return false;
 
        if(IsPlayerInDynamicArea(playerid, gGangzone[zone][E_dynamic])) return true;
        return false;
}
 
public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
    for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                if(gPlayerShown[playerid][zone])
                {
                        if(gGangzone[zone][E_interior] != -1)
                        {
                            if(newinteriorid != gGangzone[zone][E_interior])
                            {
                                                GangZoneHideForPlayer(playerid, zone);
                            }
                        }
                        }
                }
        }
        #if defined Hook_OnPlayerInteriorChange
                Hook_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
        #endif
        return 1;
}
#if defined _ALS_OnPlayerInteriorChange
        #undef OnPlayerInteriorChange
#else
        #define _ALS_OnPlayerInteriorChange
#endif
#define OnPlayerInteriorChange Hook_OnPlayerInteriorChange
#if defined Hook_OnPlayerInteriorChange
        forward Hook_OnPlayerInteriorChange(playerid);
#endif
 
stock SetPlayerVirtualWorld_(playerid, worldid)
{
    gPlayerWorld[playerid] = worldid;
    return SetPlayerVirtualWorld(playerid, worldid);
}
#if defined _ALS_SetPlayerVirtualWorld
    #undef SetPlayerVirtualWorld
#else
    #define _ALS_SetPlayerVirtualWorld
#endif
#define SetPlayerVirtualWorld SetPlayerVirtualWorld_
 
public OnPlayerUpdate(playerid)
{
        if(gPlayerWorld[playerid] != GetPlayerVirtualWorld(playerid))
        {
            CallLocalFunction("OnPlayerVirtualWorldChange", "iii", playerid, gPlayerWorld[playerid], GetPlayerVirtualWorld(playerid));
            gPlayerWorld[playerid] = GetPlayerVirtualWorld(playerid);
        }
    #if defined Hook_OnPlayerUpdate
                Hook_OnPlayerUpdate(playerid);
        #endif
        return 1;
}
#if defined _ALS_OnPlayerUpdate
        #undef OnPlayerUpdate
#else
        #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate Hook_OnPlayerUpdate
#if defined Hook_OnPlayerUpdate
        forward Hook_OnPlayerUpdate(playerid);
#endif
 
forward OnPlayerVirtualWorldChange(playerid, newworld, oldword);
public OnPlayerVirtualWorldChange(playerid, newworld, oldword)
{
        for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                if(gPlayerShown[playerid][zone])
                {
                        if(gGangzone[zone][E_virtualworld] != -1)
                        {
                            if(newworld != gGangzone[zone][E_virtualworld])
                            {
                                                GangZoneHideForPlayer(playerid, zone);
                            }
                        }
                        }
                }
        }
        return 1;
}
 
public OnPlayerEnterDynamicArea(playerid, areaid)
{
    for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                        if(areaid == gGangzone[zone][E_dynamic])
                {
                    CallLocalFunction("OnPlayerEnterGangZone", "dd", playerid, zone);
                    break;
                }
            }
        }
    #if defined Hook_OnPlayerEnterDynamicArea
                Hook_OnPlayerEnterDynamicArea(playerid, areaid);
        #endif
        return 1;
}
#if defined _ALS_OnPlayerEnterDynamicArea
        #undef OnPlayerEnterDynamicArea
#else
        #define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea Hook_OnPlayerEnterDynamicArea
#if defined Hook_OnPlayerEnterDynamicArea
        forward Hook_OnPlayerEnterDynamicArea(playerid, areaid);
#endif
 
//the system callback
forward OnPlayerEnterGangZone(playerid, zone);
 
public OnPlayerLeaveDynamicArea(playerid, areaid)
{
    for(new zone = 0; zone < MAX_ZONES; zone++)
        {
            if(GangZoneExist(zone))
            {
                        if(areaid == gGangzone[zone][E_dynamic])
                {
                    CallLocalFunction("OnPlayerLeaveGangZone", "dd", playerid, zone);
                    break;
                }
            }
        }
    #if defined Hook_OnPlayerLeaveDynamicArea
                Hook_OnPlayerLeaveDynamicArea(playerid, areaid);
        #endif
        return 1;
}
#if defined _ALS_OnPlayerLeaveDynamicArea
        #undef OnPlayerLeaveDynamicArea
#else
        #define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea Hook_OnPlayerLeaveDynamicArea
#if defined Hook_OnPlayerLeaveDynamicArea
        forward Hook_OnPlayerLeaveDynamicArea(playerid, areaid);
#endif
 
//the system callback
forward OnPlayerLeaveGangZone(playerid, zone);