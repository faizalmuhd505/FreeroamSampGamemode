/************************************
*   Include: Map Maker File Core    *
*   Created By: finch and ReGeX     *
*   Date: 01/12/2007  Ver: 1.0      *
************************************/

#if defined _MapFileCore_included
  #endinput
#endif
#define _MapFileCore_included
#pragma library MapFileCore

#include <a_samp>
#include <dini>

// Defines
#define white 0xFFFFFFAA
#define yellow 0xFFFF00AA
#define green 0x32CD32AA
#define red 0xFF0000AA
#define MAX_MAP_OBJECTS 200
//#define MAX_LOADED_MAPS 218 // Permanent maps + player maps
#define MAX_LOADED_MAPS 100

new pname[32];
new logstring[256];
new string2[128];

// Include Variables
enum MapObjectData {
	StreamId,
	ObjectId, // model ID to be precisely
	Float:XCoord,
	Float:YCoord,
	Float:ZCoord,
	Float:XRotation,
	Float:YRotation,
	Float:ZRotation
}
new Map[MAX_LOADED_MAPS][MAX_MAP_OBJECTS][MapObjectData],
		MapNames[MAX_LOADED_MAPS][256],
		bool:IsMapLoaded[MAX_LOADED_MAPS] = false,
		MapEditorStatus[MAX_PLAYERS] = -1,
		ObjectEditorStatus[MAX_PLAYERS] = -1;

forward LoadMapMode(MapName[256],ActualMapName[], worldid);
forward UnloadMapMode(MapName[256],ActualMapName[]);
//==============================================================================
stock CreateMapFile(playerid,MapName[256],ActualMapName[], Password[]) {
	if(dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 0 : SendClientMessage(playerid,red,">> ERROR: This map has already been created. Try another name."));
	dini_Create(MapName);
	new name[24];
	GetPlayerName(playerid, name, 24);
	dini_Set(MapName,"Creator",name);
	dini_Set(MapName,"Password",Password);
	for(new i = 1; i <= MAX_MAP_OBJECTS; i++) { new Key[4]; valstr(Key,i); dini_Set(MapName,Key,"-1"); }
	new string[256]; format(string,256,"[MAP] You have created the map '%s'. To load your map, type /LOADMAP %s %s.",ActualMapName,ActualMapName,Password);
	SendClientMessage(playerid,yellow,string);
	GetPlayerName(playerid, pname, sizeof(pname));
	format(string2,sizeof(string2),"[MAPinfo] %s has created the map '%s'.",pname, ActualMapName);
	SendMessageToAdmins(yellow, string2, 1);
	format(string2,sizeof(string2),"7,5[MAPinfo] %s has created the map '%s'.",pname, ActualMapName);
	IRC_GroupSay(1, "@#xmovie", string2);
	return LoadMap(playerid,MapName,ActualMapName, Password);
}
//==============================================================================
stock RemoveMapFile(playerid,MapName[]) {
	if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));
	GetPlayerName(playerid, pname, sizeof(pname));
	format(string2,128,"[MAPinfo] %s has removed the map '%s'.",pname, MapName);
	SendMessageToAdmins(yellow, string2, 1);
    return dini_Remove(MapName);
}
//==============================================================================
stock ChangeMapPassword(playerid,MapName[],ActualMapName[], Password[], NewPassword[]) {
	if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));

	new pass[256];
	pass = dini_Get(MapName,"Password");
	if(!pass[0] || strcmp(pass,Password,true))
	return SendClientMessage(playerid,red,">> ERROR: The entered password is incorrect.");

	dini_Set(MapName,"Password",NewPassword);
	new string[256]; format(string,256, "You have changed the password of the map '%s' to '%s', remember it.",ActualMapName,NewPassword);
	SendClientMessage(playerid,yellow,string);

	new creator[256];
	creator = dini_Get(MapName,"Creator");
	GetPlayerName(playerid, pname, sizeof(pname));
	format(string2,128,"[MAPinfo] %s has changed the password for '%s'. (Original creator: %s)",pname, ActualMapName, creator);
	SendMessageToAdmins(yellow, string2, 1);
	format(string2,128,"7,5[MAPinfo] %s has changed the password for '%s'. (Original creator: %s)",pname, ActualMapName, creator);
	IRC_GroupSay(1, "@#xmovie", string2);
	return 1;
}
//==============================================================================
stock ChangeVMapPassword(playerid,MapName[],ActualMapName[], Password[], ViewPassword[]) {
	if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));

	new pass[256];
	pass = dini_Get(MapName,"Password");
	if(!pass[0] || strcmp(pass,Password,true))
	return SendClientMessage(playerid,red,">> ERROR: The entered map-password is incorrect.");

	dini_Set(MapName,"ViewPassword",ViewPassword);
	new string[256]; format(string,256, "You have changed the view_password of the map '%s' to '%s', remember it.",ActualMapName,ViewPassword);
	return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,yellow,string));
}
//==============================================================================
stock AddObject(playerid,MapID,ObjectID,Float:X,Float:Y,Float:Z,Float:XRot,Float:YRot,Float:ZRot) {
	new MapName[256]; MapName = GetLoadedMapName(MapID);
	if(!strcmp(MapName,"...",true)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: Your map does not appear to be loaded."));
	if(!IsValidModel(ObjectID)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: This is not a valid object model id."));
	for(new i = 1; i <= MAX_MAP_OBJECTS; i++) {
		new Key[4], Value[256], pWorld = GetPlayerVirtualWorld(playerid); valstr(Key,i), Value = dini_Get(MapName,Key);
	    if(!strcmp(Value,"-1",true)) {
			new string[256]; format(string,256,"%d %f %f %f %f %f %f",ObjectID,X,Y,Z,XRot,YRot,ZRot);
			// Set Map Array Object Data
			Map[MapID][i-1][ObjectId] = ObjectID,
			Map[MapID][i-1][XCoord] = X,
			Map[MapID][i-1][YCoord] = Y,
			Map[MapID][i-1][ZCoord] = Z,
			Map[MapID][i-1][XRotation] = XRot,
			Map[MapID][i-1][YRotation] = YRot,
			Map[MapID][i-1][ZRotation] = ZRot;
		 	dini_Set(MapName,Key,string);
			Map[MapID][i-1][StreamId] = CreateDynamicObject(ObjectID, X, Y, Z, XRot, YRot, ZRot, pWorld);
			Streamer_Update(playerid);
		 	format(string,256,"[MAP] You have added Model ID %d [MAP ITEM ID %d] to map \'%s\' and are currently editing it.",ObjectID,i,ReturnMapNameFromFile(GetLoadedMapName(MapID)));
			ObjectEditorStatus[playerid] = i;
			return SendClientMessage(playerid,yellow,string);
		}
	}
	return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: This map has achieved the maximum amount of objects."));
}
//==============================================================================
stock DeleteObject(playerid,MapID,FileObjectID) {
    new MapName[256]; MapName = GetLoadedMapName(MapID);
	if(!strcmp(MapName,"...",true)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: Your map does not appear to be loaded."));
	new Key[4], Value[256]; valstr(Key,FileObjectID), Value = dini_Get(MapName,Key);
	if(!strcmp(Value,"-1",true) || FileObjectID < 1 || FileObjectID > MAX_MAP_OBJECTS) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: You have entered an invalid map item ID."));

	DestroyDynamicObject(Map[MapID][FileObjectID-1][StreamId]);
	Map[MapID][FileObjectID-1][StreamId] = -1, Map[MapID][FileObjectID-1][ObjectId] = 0, Map[MapID][FileObjectID-1][XCoord] = Map[MapID][FileObjectID-1][YCoord] = Map[MapID][FileObjectID-1][ZCoord] = Map[MapID][FileObjectID-1][XRotation] = Map[MapID][FileObjectID-1][YRotation] = Map[MapID][FileObjectID-1][ZRotation] = 0.0;
	new string[256]; format(string,256,"[MAP] You have destroyed object %d in map \'%s\'.",FileObjectID,ReturnMapNameFromFile(GetLoadedMapName(MapID)));
	SendClientMessage(playerid,yellow,string);
	return dini_Set(MapName,Key,"-1");
}
//==============================================================================
stock UpdateObject(playerid,MapID,FileObjectID,Rule[256],Float:RuleValue) {
	new MapName[256]; MapName = GetLoadedMapName(MapID);
	if(!strcmp(MapName,"...",true)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: Your map does not appear to be loaded."));
	new Key[4], Value[256]; valstr(Key,FileObjectID), Value = dini_Get(MapName,Key);
	if(!strcmp(Value,"-1",true) || FileObjectID < 1 || FileObjectID > MAX_MAP_OBJECTS) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: This object has not been set to be updated."));

	if(!strcmp(Rule,"X",false)) Map[MapID][FileObjectID-1][XCoord] += RuleValue;
	else if(!strcmp(Rule,"Y",false)) Map[MapID][FileObjectID-1][YCoord] += RuleValue;
	else if(!strcmp(Rule,"Z",false)) Map[MapID][FileObjectID-1][ZCoord] += RuleValue;
	else if(!strcmp(Rule,"XRot",false)) Map[MapID][FileObjectID-1][XRotation] += RuleValue;
	else if(!strcmp(Rule,"YRot",false)) Map[MapID][FileObjectID-1][YRotation] += RuleValue;
	else if(!strcmp(Rule,"ZRot",false)) Map[MapID][FileObjectID-1][ZRotation] += RuleValue;
	else if(!strcmp(Rule,"ObjectID",false)) Map[MapID][FileObjectID-1][ObjectId] = floatround(RuleValue,floatround_floor);
	//DestroyDynamicObject(Map[MapID][FileObjectID-1][StreamId]);
	//Map[MapID][FileObjectID-1][StreamId] = CreateDynamicObject(Map[MapID][FileObjectID-1][ObjectId], Map[MapID][FileObjectID-1][XCoord], Map[MapID][FileObjectID-1][YCoord], Map[MapID][FileObjectID-1][ZCoord], Map[MapID][FileObjectID-1][XRotation], Map[MapID][FileObjectID-1][YRotation], Map[MapID][FileObjectID-1][ZRotation], pWorld);
	//Streamer_Update(playerid);
	SetDynamicObjectPos(Map[MapID][FileObjectID-1][StreamId], Map[MapID][FileObjectID-1][XCoord], Map[MapID][FileObjectID-1][YCoord], Map[MapID][FileObjectID-1][ZCoord]);
	SetDynamicObjectRot(Map[MapID][FileObjectID-1][StreamId], Map[MapID][FileObjectID-1][XRotation], Map[MapID][FileObjectID-1][YRotation], Map[MapID][FileObjectID-1][ZRotation]);
	new string[256]; format(string, sizeof(string),"%d %f %f %f %f %f %f",Map[MapID][FileObjectID-1][ObjectId],Map[MapID][FileObjectID-1][XCoord],Map[MapID][FileObjectID-1][YCoord],Map[MapID][FileObjectID-1][ZCoord],Map[MapID][FileObjectID-1][XRotation],Map[MapID][FileObjectID-1][YRotation],Map[MapID][FileObjectID-1][ZRotation]);
	dini_Set(MapName,Key,string);
	format(string, sizeof(string),"[MAP] You have modified Object %d's %s position by %.4f units in map \'%s\'.",FileObjectID,Rule,RuleValue,ReturnMapNameFromFile(GetLoadedMapName(MapID)));
	return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,yellow,string));
}
//==============================================================================
stock LoadMap(playerid,MapName[256],ActualMapName[], Password[]) {
	if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));
	if(GetMapID(MapName) != -1 && IsMapLoaded[GetMapID(MapName)]) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: This map has already been loaded."));
	if(GetNextMapID() == -1) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: No more maps can be loaded at this time."));

	new pass[256];
	pass = dini_Get(MapName,"Password");
	if(!pass[0] || strcmp(pass,Password,true))
	return SendClientMessage(playerid,red,">> ERROR: The entered password is incorrect.");

	//SendClientMessage(playerid,red,"[Warning] Be sure to unload your map before leaving the server or it might get lost!");
	new NextMapID = GetNextMapID(),
	    pWorld = GetPlayerVirtualWorld(playerid);
	for(new i = 1, Index = 0; i <= MAX_MAP_OBJECTS; i++) {
	    new Key[4],Value[256]; valstr(Key,i), Value = dini_Get(MapName,Key);
	    if(!strcmp(Value,"-1",true)) continue;
		Map[NextMapID][i-1][ObjectId] = strval(Token(Value,Index)),
		Map[NextMapID][i-1][XCoord] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][YCoord] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][ZCoord] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][XRotation] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][YRotation] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][ZRotation] = floatstr(Token(Value,Index));
		Map[NextMapID][i-1][StreamId] = CreateDynamicObject(Map[NextMapID][i-1][ObjectId], Map[NextMapID][i-1][XCoord], Map[NextMapID][i-1][YCoord], Map[NextMapID][i-1][ZCoord], Map[NextMapID][i-1][XRotation], Map[NextMapID][i-1][YRotation], Map[NextMapID][i-1][ZRotation], pWorld);
		Index = 0;
	}
	pname = "INVALID_PLAYER_ID";
	IsMapLoaded[NextMapID] = true;
	//MapNames[NextMapID] = MapName;
	strmid(MapNames[NextMapID], MapName, 0, sizeof(MapName));
	if(playerid != INVALID_PLAYER_ID) {
	    Streamer_Update(playerid);
	    MapEditorStatus[playerid] = NextMapID;
	    new string[256]; format(string,256,"[MAP] You have loaded map \'%s\' (ID: %d) successfully, and can now edit it.",ActualMapName,NextMapID);
	    SendClientMessage(playerid,yellow,string);
	    GetPlayerName(playerid, pname, sizeof(pname));
	    new creator[256];
	    creator = dini_Get(MapName,"Creator");
	    format(string2,128,"[MAPinfo] %s has loaded the map '%s'. (Original creator: %s)",pname, ActualMapName, creator);
	    SendMessageToAdmins(yellow, string2, 1);
	    format(string2,128,"7,5[MAPinfo] %s has loaded the map '%s'. (Original creator: %s)",pname, ActualMapName, creator);
	    IRC_GroupSay(1, "@#xmovie", string2);
	    SetPlayerScore(playerid, 1);
	}
	format(logstring,sizeof(logstring),"The map \"%s\" has been loaded (ID: %d) by %s.",MapName,NextMapID,pname);
	printlog("MAPLO", logstring);
	return 1;
}
//==============================================================================
stock UnloadMap(playerid,MapName[256],ActualMapName[], Password[]) {
	if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));
	if(GetMapID(MapName) == -1) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: This map has already been unloaded."));

	if(strcmp(Password,"UnloadAllMapsxMovie321",false))
	{
		new pass[256];
		pass = dini_Get(MapName,"Password");
		if(!pass[0] || strcmp(pass,Password,true))
		return SendClientMessage(playerid,red,">> ERROR: The entered password is incorrect.");
	}

	new MapID = GetMapID(MapName);
	for(new i = 1; i <= MAX_MAP_OBJECTS; i++)
	{
	    new Key[4],Value[256]; valstr(Key,i), Value = dini_Get(MapName,Key);
	    if(!strcmp(Value,"-1",true)) continue;
	    DestroyDynamicObject(Map[MapID][i-1][StreamId]);
	    Map[MapID][i-1][StreamId] = -1, Map[MapID][i-1][ObjectId] = 0, Map[MapID][i-1][XCoord] = Map[MapID][i-1][YCoord] = Map[MapID][i-1][ZCoord] = Map[MapID][i-1][XRotation] = Map[MapID][i-1][YRotation] = Map[MapID][i-1][ZRotation] = 0.0;
	}
	pname = "INVALID_PLAYER_ID";
	if(playerid != INVALID_PLAYER_ID)
	{
 	    for(new i = 0; i < MAX_PLAYERS; i++)
  	    {
		if (IsPlayerConnected(i) && MapEditorStatus[i] == MapID)
		{
	  		MapEditorStatus[i] = -1;
			player[i][maphelping] = 0;
			SetPlayerScore(i, 0);
		}
	    }
	    new string[256]; format(string,256,"[MAP] You have unloaded map \'%s\' (ID: %d) successfully.",ActualMapName,MapID);
	    SendClientMessage(playerid,yellow,string);
	    GetPlayerName(playerid, pname, sizeof(pname));
	    format(string2,128,"[MAPinfo] %s has unloaded the map '%s'.",pname, ActualMapName);
	    SendMessageToAdmins(yellow, string2, 1);
	    format(string2,128,"7,5[MAPinfo] %s has unloaded the map '%s'.",pname, ActualMapName);
	    IRC_GroupSay(1, "@#xmovie", string2);
	}
	IsMapLoaded[MapID] = false;
	MapNames[MapID] = "NA";
	format(logstring,sizeof(logstring),"The map \"%s\" has been unloaded (ID: %d) by %s.",MapName,MapID,pname);
	printlog("MAPUL",logstring);
	return 1;
}

stock UnloadAllMaps() {
 	for(new i = 0; i < MAX_LOADED_MAPS; i++)
	{
    	    if(strcmp(MapNames[i],"NA",false))
	    UnloadMap(INVALID_PLAYER_ID,MapNames[i],MapNames[i],"UnloadAllMapsxMovie321");
	}
	return 1;
}
//==============================================================================
stock VLoadMap(playerid,MapName[256],ActualMapName[], Password[]) {
	if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));
	if(GetMapID(MapName) != -1 && IsMapLoaded[GetMapID(MapName)]) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: This map has already been loaded."));
	if(GetNextMapID() == -1) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: No more maps can be loaded at this time."));

	new pass[256];
	pass = dini_Get(MapName,"ViewPassword");
	if(!pass[0])
	return SendClientMessage(playerid,red,">> ERROR: Please ask the map owner to set a view_password.");

	if(strcmp(pass,Password,true))
	return SendClientMessage(playerid,red,">> ERROR: The entered password is incorrect.");

	new NextMapID = GetNextMapID(),
	    pWorld = GetPlayerVirtualWorld(playerid);
	for(new i = 1, Index = 0; i <= MAX_MAP_OBJECTS; i++) {
	    new Key[4],Value[256]; valstr(Key,i), Value = dini_Get(MapName,Key);
	    if(!strcmp(Value,"-1",true)) continue;
		Map[NextMapID][i-1][ObjectId] = strval(Token(Value,Index)),
		Map[NextMapID][i-1][XCoord] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][YCoord] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][ZCoord] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][XRotation] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][YRotation] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][ZRotation] = floatstr(Token(Value,Index));
		Map[NextMapID][i-1][StreamId] = CreateDynamicObject(Map[NextMapID][i-1][ObjectId], Map[NextMapID][i-1][XCoord], Map[NextMapID][i-1][YCoord], Map[NextMapID][i-1][ZCoord], Map[NextMapID][i-1][XRotation], Map[NextMapID][i-1][YRotation], Map[NextMapID][i-1][ZRotation], pWorld);
		Index = 0;
	}
	pname = "INVALID_PLAYER_ID";
	IsMapLoaded[NextMapID] = true;
	//MapNames[NextMapID] = MapName;
	strmid(MapNames[NextMapID], MapName, 0, sizeof(MapName));
	if(playerid != INVALID_PLAYER_ID) {
	    Streamer_Update(playerid);
	    player[playerid][mapviewer] = NextMapID;
	    new string[256]; format(string,256,"[MAP] You have loaded map \'%s\' (ID: %d) successfully, and may only view it.",ActualMapName,NextMapID);
	    SendClientMessage(playerid,yellow,string);
	    GetPlayerName(playerid, pname, sizeof(pname));
	    format(string2,128,"[MAPinfo] %s has loaded the map '%s' (view-mode).",pname, ActualMapName);
	    SendMessageToAdmins(yellow, string2, 1);
	    SetPlayerScore(playerid, 3);
	}
	format(logstring,sizeof(logstring),"The map \"%s\" has been loaded (ID: %d) by %s (view-mode).",MapName,NextMapID,pname);
	printlog("MAPLO", logstring);
	return 1;
}
//==============================================================================
stock VUnloadMap(playerid,MapName[256],ActualMapName[], Password[]) {
	if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));
	if(GetMapID(MapName) == -1) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: This map has already been unloaded."));

	new pass[256];
	pass = dini_Get(MapName,"ViewPassword");
	if(!pass[0])
	return SendClientMessage(playerid,red,">> ERROR: Please ask the map owner to set a view_password.");

	if(strcmp(pass,Password,true))
	return SendClientMessage(playerid,red,">> ERROR: The entered password is incorrect.");

	new mapID = player[playerid][mapviewer];
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if (MapEditorStatus[i] == mapID)
		return SendClientMessage(playerid,red,">> ERROR: Another player is currently EDITTING this map.");
	}

	new MapID = GetMapID(MapName);
	for(new i = 1; i <= MAX_MAP_OBJECTS; i++)
	{
	    new Key[4],Value[256]; valstr(Key,i), Value = dini_Get(MapName,Key);
	    if(!strcmp(Value,"-1",true)) continue;
	    DestroyDynamicObject(Map[MapID][i-1][StreamId]);
	    Map[MapID][i-1][StreamId] = -1, Map[MapID][i-1][ObjectId] = 0, Map[MapID][i-1][XCoord] = Map[MapID][i-1][YCoord] = Map[MapID][i-1][ZCoord] = Map[MapID][i-1][XRotation] = Map[MapID][i-1][YRotation] = Map[MapID][i-1][ZRotation] = 0.0;
	}
	pname = "INVALID_PLAYER_ID";
	if(playerid != INVALID_PLAYER_ID)
	{
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if (IsPlayerConnected(i) && player[i][mapviewer] == MapID)
			{
				player[i][mapviewer] = -1;
				SetPlayerScore(i, 0);
			}
		}	
		new string[256]; format(string,256,"[MAP] You have unloaded map \'%s\' (ID: %d) successfully.",ActualMapName,MapID);
		SendClientMessage(playerid,yellow,string);
		GetPlayerName(playerid, pname, sizeof(pname));
		format(string2,128,"[MAPinfo] %s has unloaded the map '%s' (view-mode).",pname, ActualMapName);
		SendMessageToAdmins(yellow, string2, 1);
	}
	IsMapLoaded[MapID] = false;
	MapNames[MapID] = "NA";
	format(logstring,sizeof(logstring),"The map \"%s\" has been unloaded (ID: %d) by %s (view-mode).",MapName,MapID,pname);
	printlog("MAPUL",logstring);
	return 1;
}
//==============================================================================
public LoadMapMode(MapName[256],ActualMapName[], worldid) {
	if(!dini_Exists(MapName)) return SendMessageToAdmins(yellow, "ServerError: The given mapname does not exist.", 1);
	if(GetMapID(MapName) != -1 && IsMapLoaded[GetMapID(MapName)]) return SendMessageToAdmins(yellow, "ServerError: The given mapname is already loaded.", 1);

	new NextMapID = GetNextMapID();
	for(new i = 1, Index = 0; i <= MAX_MAP_OBJECTS; i++) {
	    new Key[4],Value[256]; valstr(Key,i), Value = dini_Get(MapName,Key);
	    if(!strcmp(Value,"-1",true)) continue;
		Map[NextMapID][i-1][ObjectId] = strval(Token(Value,Index)),
		Map[NextMapID][i-1][XCoord] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][YCoord] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][ZCoord] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][XRotation] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][YRotation] = floatstr(Token(Value,Index)),
		Map[NextMapID][i-1][ZRotation] = floatstr(Token(Value,Index));
		Map[NextMapID][i-1][StreamId] = CreateDynamicObject(Map[NextMapID][i-1][ObjectId], Map[NextMapID][i-1][XCoord], Map[NextMapID][i-1][YCoord], Map[NextMapID][i-1][ZCoord], Map[NextMapID][i-1][XRotation], Map[NextMapID][i-1][YRotation], Map[NextMapID][i-1][ZRotation], worldid);
		Index = 0;
	}
	IsMapLoaded[NextMapID] = true;
	//MapNames[NextMapID] = MapName;
	strmid(MapNames[NextMapID], MapName, 0, sizeof(MapName));
	format(logstring,sizeof(logstring),"The map \"%s\" has been loaded (ID: %d) (permanent/derby).",MapName,NextMapID);
	printlog("MAPLO", logstring);
	return 1;
}

public UnloadMapMode(MapName[256],ActualMapName[]) {
	if(!dini_Exists(MapName)) return SendMessageToAdmins(yellow, "ServerError: The given mapname does not exist.", 1);
	if(GetMapID(MapName) == -1) return 1;
	//if(GetMapID(MapName) == -1) return SendMessageToAdmins(yellow, "ServerError: The given mapname is already unloaded.", 1);

	new MapID = GetMapID(MapName);
	for(new i = 1; i <= MAX_MAP_OBJECTS; i++)
	{
	    new Key[4],Value[256]; valstr(Key,i), Value = dini_Get(MapName,Key);
	    if(!strcmp(Value,"-1",true)) continue;
	    DestroyDynamicObject(Map[MapID][i-1][StreamId]);
	    Map[MapID][i-1][StreamId] = -1, Map[MapID][i-1][ObjectId] = 0, Map[MapID][i-1][XCoord] = Map[MapID][i-1][YCoord] = Map[MapID][i-1][ZCoord] = Map[MapID][i-1][XRotation] = Map[MapID][i-1][YRotation] = Map[MapID][i-1][ZRotation] = 0.0;
	}
	IsMapLoaded[MapID] = false;
	MapNames[MapID] = "NA";
	format(logstring,sizeof(logstring),"The map \"%s\" has been unloaded (ID: %d) (permanent/derby).",MapName,MapID);
	printlog("MAPUL",logstring);
	return 1;
}
//==============================================================================
stock ConvertMap(playerid,MapName[256],ActualMapName[]) {
	if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));

	new MapNameFile[100];
	format(MapNameFile, sizeof(MapNameFile), "Maps_converted/%s.map", ActualMapName);

	if(fexist(MapNameFile)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: There is already an existing converted map with this name."));

	new File:cfile = fopen(MapNameFile, io_write);
	new cObjectId, Float:cXCoord, Float:cYCoord, Float:cZCoord, Float:cXRotation, Float:cYRotation, Float:cZRotation, cOutput[200];
	for(new i = 1, Index = 0; i <= MAX_MAP_OBJECTS; i++) {
	    new Key[4],Value[256]; valstr(Key,i), Value = dini_Get(MapName,Key);
	    if(!strcmp(Value,"-1",true)) continue;
		cObjectId = strval(Token(Value,Index)),
		cXCoord = floatstr(Token(Value,Index)),
		cYCoord = floatstr(Token(Value,Index)),
		cZCoord = floatstr(Token(Value,Index)),
		cXRotation = floatstr(Token(Value,Index)),
		cYRotation = floatstr(Token(Value,Index)),
		cZRotation = floatstr(Token(Value,Index));
		format(cOutput, sizeof(cOutput), "CreateObject(%d, %f, %f, %f, %f, %f, %f);\n", cObjectId, cXCoord, cYCoord, cZCoord, cXRotation, cYRotation, cZRotation);
		fwrite(cfile, cOutput);
		Index = 0;
	}
	fclose(cfile);
	new string[256];
	format(string,256,"[CONVERT] The map \"%s\" is now converted to %s", MapName, MapNameFile);
	SendClientMessage(playerid,yellow,string);
	GetPlayerName(playerid, pname, sizeof(pname));
	format(logstring,sizeof(logstring),"The map \"%s\" has been converted by %s.",MapName,pname);
	printlog("MAPCON", logstring);
	return 1;
}
//==============================================================================
stock ClearMap(playerid,MapName[256],ActualMapName[]) {
    if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));
    if(GetMapID(MapName) == -1) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map you are clearing has not been loaded."));
    new MapID = GetMapID(MapName);
    IsMapLoaded[MapID] = false;
    if(playerid != INVALID_PLAYER_ID) SendClientMessage(playerid,yellow,"[MAP] Clearing; expect this to take up to five seconds.");
	for(new i = 1; i <= MAX_MAP_OBJECTS; i++) {
	    new Key[4],Value[256]; valstr(Key,i), Value = dini_Get(MapName,Key);
	    DestroyDynamicObject(Map[MapID][i-1][StreamId]);
	    Map[MapID][i-1][StreamId] = -1, Map[MapID][i-1][ObjectId] = 0, Map[MapID][i-1][XCoord] = Map[MapID][i-1][YCoord] = 0.0, Map[MapID][i-1][ZCoord] = -800.0, Map[MapID][i-1][XRotation] = Map[MapID][i-1][YRotation] = Map[MapID][i-1][ZRotation] = 0.0;
	    dini_Set(MapName,Key,"-1");
	}
	if(playerid != INVALID_PLAYER_ID) {
	    new string[256]; format(string,256,"[MAP] You have cleared map \'%s\' (ID: %d) successfully.",ActualMapName,MapID);
	    SendClientMessage(playerid,yellow,string);
	    GetPlayerName(playerid, pname, sizeof(pname));
	    format(string2,128,"[MAPinfo] %s has cleared the map '%s'.",pname, ActualMapName);
	    SendMessageToAdmins(yellow, string2, 1);
	}
	IsMapLoaded[MapID] = true;
	format(logstring,sizeof(logstring),"The map \"%s\" has been cleared (ID: %d) by %s.",MapName,MapID,pname);
	printlog("MAPCL",logstring);
	return 1;
}
//==============================================================================
stock SelectMapToEdit(playerid,MapName[256],ActualMapName[], Password[]) {
    if(!dini_Exists(MapName)) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map name specified does not exist."));
    if(GetMapID(MapName) == -1) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: The map you have selected has not been loaded."));

	new pass[256];
	pass = dini_Get(MapName,"Password");
	if(!pass[0] || strcmp(pass,Password,true))
	return SendClientMessage(playerid,red,">> ERROR: The entered password is incorrect.");

    new MapID = GetMapID(MapName);
	if(MapID == MapEditorStatus[playerid]) return (playerid == INVALID_PLAYER_ID ? 1 : SendClientMessage(playerid,red,">> ERROR: You are already editing this map."));
	if(playerid != INVALID_PLAYER_ID) {
	    new string[256]; format(string,256,"[MAP] You are now editing map \'%s\' (ID: %d).",ActualMapName,MapID);
	    SendClientMessage(playerid,yellow,string);
	    GetPlayerName(playerid, pname, sizeof(pname));
	    format(string2,128,"[MAPinfo] %s is editting the map '%s'.",pname, ActualMapName);
	    SendMessageToAdmins(yellow, string2, 1);
	    format(string2,128,"7,5[MAPinfo] %s is editting the map '%s'.",pname, ActualMapName);
	    IRC_GroupSay(1, "@#xmovie", string2);
	}
	MapEditorStatus[playerid] = MapID;
	return 1;
}
//==============================================================================
stock SelectObjectToEdit(playerid,ObjectID) {
	new MapName[256]; MapName = GetLoadedMapName(MapEditorStatus[playerid]);
	new Key[4],Value[256]; valstr(Key,ObjectID), Value = dini_Get(MapName,Key);
 	if(!strcmp(Value,"-1",true)) return SendClientMessage(playerid,red,">> ERROR: You have entered an invalid map item ID.");
	ObjectEditorStatus[playerid] = ObjectID;
	if(playerid != INVALID_PLAYER_ID) {
	    new string[256]; format(string,256,"[MAP] You are now editing object %d on map \'%s\'.",ObjectID,ReturnMapNameFromFile(GetLoadedMapName(MapEditorStatus[playerid])));
	    SendClientMessage(playerid,yellow,string);
	}
	return 1;
}
//==============================================================================
stock Token(String[],&Index) {
 	new Offset = 0, Result[50];
	while(Index < strlen(String) && String[Index] <= ' ') Index++;
	Offset = Index;
    while(Index < strlen(String) && String[Index] > ' ' && (Index - Offset) < (sizeof(Result) - 1)) Result[Index - Offset] = String[Index], Index++;
	Result[Index - Offset] = EOS;
	return Result;
}
//==============================================================================
stock GetLoadedMapName(MapID) {
	new MapName[256]; if(!IsMapLoaded[MapID]) MapName = "...";
	else MapName = MapNames[MapID];
	return MapName;
}
//==============================================================================
stock GetMapID(MapName[256]) {
	for(new i = 0; i < MAX_LOADED_MAPS; i++) if(!strcmp(MapName,MapNames[i],true)) return i;
	return -1;
}
//==============================================================================
stock GetNextMapID() {
	for(new i = 0; i < MAX_LOADED_MAPS; i++) if(!IsMapLoaded[i]) return i;
	return -1;
}
//==============================================================================
stock ReturnMapNameFromFile(FileMapName[256]) {
	new string[256];
	string = FileMapName;
	string = strreplace("Maps","",string);
	string = strreplace("/","",string);
	string = strreplace(".ini","",string);
	return string;
}