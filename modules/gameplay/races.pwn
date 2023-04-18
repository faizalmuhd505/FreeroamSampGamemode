/*******************************************************************************
* NOME DO ARQUIVO :		modules/gameplay/races.pwn
*
* DESCRIÇÃO :
*	   Permite que jogadores participem de corridas.
*
* NOTAS :
*	   -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

static const VIRTUAL_WORLD = 2000;

//------------------------------------------------------------------------------

forward OnRaceLoad();
forward OnRaceDelete(playerid, raceid);
forward OnRaceExport(playerid);
forward OnRaceGridLoad(raceid);
forward OnRaceCheckpointLoad(raceid);
forward OnPlayerEnterRace(playerid, raceid);

//------------------------------------------------------------------------------

enum
{
    RACE_STATE_WAITING_PLAYERS,
    RACE_STATE_STARTING,
    RACE_STATE_STARTED
}

enum
{
    RACE_PLAYER_STATE_NONE,
    RACE_PLAYER_STATE_RACING,
    RACE_PLAYER_STATE_SPECTATING
}

enum
{
	E_PLAYER_RACE_STATE_NONE,
	E_PLAYER_CREATING_RACE,
	E_PLAYER_CREATING_CHECKPOINT,
	E_PLAYER_CREATING_GRID
}

enum e_race_data
{
    e_race_id,
    e_race_name[MAX_RACE_NAME],
    e_race_leaderboard[MAX_RACE_PLAYERS],
    e_race_counter,
    e_race_state,
    e_race_interior,
    e_race_vmodel,
    e_race_cp_type,
    Float:e_race_cp_size
}
static gRaceData[MAX_RACES][e_race_data];

enum e_cp_data
{
    e_race_id,
    Float:e_checkpoint_x,
    Float:e_checkpoint_y,
    Float:e_checkpoint_z
}
static gCheckpointData[MAX_RACES][MAX_RACE_CHECKPOINTS][e_cp_data];

enum e_grid_data
{
    e_race_id,
    e_vehicle_id,
    Float:e_vehicle_x,
    Float:e_vehicle_y,
    Float:e_vehicle_z,
    Float:e_vehicle_a
}
static gVehicleData[MAX_RACES][MAX_RACE_PLAYERS][e_grid_data];
static gPrizeData[MAX_RACES][MAX_RACE_PLAYERS];

static Float:gLobbySpawns[][] =
{
    {   -974.8712,    1061.1549,  1345.6719,  88.9761     },
    {   -1041.3506,   1078.1920,  1347.8082,  251.8641    },
    {   -1065.9036,   1086.8920,  1346.4971,  124.6496    },
    {   -1063.5520,   1055.0902,  1347.4911,  87.0493     },
    {   -1089.4988,   1043.9332,  1347.3552,  81.9892     },
    {   -1101.5830,   1021.7955,  1342.0938,  358.9316    },
    {   -1128.0201,   1028.8192,  1345.7084,  276.8375    },
    {   -1131.4199,   1057.5118,  1346.4143,  272.4508    },
    {   -977.2980,    1089.4580,  1344.9617,  84.8873     },
    {   -1005.3085,   1078.5878,  1343.1176,  80.8140     }
};

static gPlayerCurrentRace[MAX_PLAYERS] = {INVALID_RACE_ID, ...};
static gRaceCountdown[MAX_RACES];

enum e_player_race_data
{
    e_grid_id,
    e_checkpoint_id,
    e_start_time,
    e_end_time,
    e_state,
    e_spec_targetid
}
static gPlayerData[MAX_PLAYERS][e_player_race_data];
static bool:gIsDialogShown[MAX_PLAYERS];
static gPlayerSpecTick[MAX_PLAYERS];

//------------------------------------------------------------------------------

enum e_vehicle_data
{
	e_vehicle_id,
	Float:e_vehicle_x,
	Float:e_vehicle_y,
	Float:e_vehicle_z,
	Float:e_vehicle_a
}
static gPlayerVehicles[MAX_PLAYERS][MAX_RACE_PLAYERS][e_vehicle_data];
static gPlayerCurrentVehicle[MAX_PLAYERS];

enum e_checkpoint_data
{
	Float:e_checkpoint_x,
	Float:e_checkpoint_y,
	Float:e_checkpoint_z
}
static gPlayerCheckpoints[MAX_PLAYERS][MAX_RACE_CHECKPOINTS][e_checkpoint_data];
static gPlayerCurrentCheckpoint[MAX_PLAYERS];

static gIsPlayerCreatingRace[MAX_PLAYERS];
static gPlayerRacePrize[MAX_PLAYERS][MAX_RACE_PLAYERS];
static gPlayerCurrentPrize[MAX_PLAYERS];
static Float:gPlayerCheckpointSize[MAX_PLAYERS] = {3.5, ...};
static gPlayerCheckpointType[MAX_PLAYERS] = {1, ...};
static gPlayerRaceName[MAX_PLAYERS][MAX_RACE_NAME];
static gPlayerRaceVehicleModel[MAX_PLAYERS];

//------------------------------------------------------------------------------

public OnRaceLoad()
{
    new rows, fields;
	cache_get_data(rows, fields, gMySQL);
    for(new i = 0; i < rows; i++)
    {
        if(i == MAX_RACES)
        {
            print("[error] Trying to load more races than defined in MAX_RACES.");
            break;
        }

        gRaceData[i][e_race_id]         = cache_get_field_content_int(i, "id", gMySQL);
        gRaceData[i][e_race_cp_type]    = cache_get_field_content_int(i, "cp_type", gMySQL);
        gRaceData[i][e_race_cp_size]    = cache_get_field_content_float(i, "cp_size", gMySQL);
        gRaceData[i][e_race_interior]   = cache_get_field_content_int(i, "interior", gMySQL);
        gRaceData[i][e_race_vmodel]     = cache_get_field_content_int(i, "vehicleid", gMySQL);
        cache_get_field_content(i, "name", gRaceData[i][e_race_name], gMySQL, MAX_RACE_NAME);

        new query[64];
        mysql_format(gMySQL, query, sizeof(query), "SELECT * FROM race_vehicles WHERE race_id = %d", gRaceData[i][e_race_id]);
        mysql_tquery(gMySQL, query, "OnRaceGridLoad", "i", i);
        mysql_format(gMySQL, query, sizeof(query), "SELECT * FROM race_checkpoints WHERE race_id = %d", gRaceData[i][e_race_id]);
        mysql_tquery(gMySQL, query, "OnRaceCheckpointLoad", "i", i);
    }
}

//------------------------------------------------------------------------------

public OnRaceDelete(playerid, raceid)
{
    if(cache_affected_rows() > 0)
    {
        PlaySelectSound(playerid);
        SendClientMessage(playerid, COLOR_SUCCESS, "* Successful deleted map, it will still be available to play until the server restarts.");
    }
    else
    {
        PlayErrorSound(playerid);
        SendClientMessage(playerid, COLOR_ERROR, "* This map has already been deleted.");
    }
}

//------------------------------------------------------------------------------

public OnRaceExport(playerid)
{
    new race_id = cache_insert_id();

	new query[138];
	for(new i = 0; i < gPlayerCurrentCheckpoint[playerid]; i++)
	{
	    mysql_format(gMySQL, query, sizeof(query), "INSERT INTO race_checkpoints (race_id, x, y, z) VALUES (%d, %.2f, %.2f, %.2f)",
		race_id, gPlayerCheckpoints[playerid][i][e_checkpoint_x], gPlayerCheckpoints[playerid][i][e_checkpoint_y], gPlayerCheckpoints[playerid][i][e_checkpoint_z]);
	    mysql_tquery(gMySQL, query);
	}

	for(new i = 0; i < gPlayerCurrentVehicle[playerid]; i++)
	{
	    mysql_format(gMySQL, query, sizeof(query), "INSERT INTO race_vehicles (race_id, x, y, z, a, prize) VALUES (%d, %.2f, %.2f, %.2f, %.2f, %d)",
		race_id, gPlayerVehicles[playerid][i][e_vehicle_x], gPlayerVehicles[playerid][i][e_vehicle_y], gPlayerVehicles[playerid][i][e_vehicle_z], gPlayerVehicles[playerid][i][e_vehicle_a], gPlayerRacePrize[playerid][i]);
	    mysql_tquery(gMySQL, query);
	}

	PlayBuySound(playerid);
	SendClientMessage(playerid, COLOR_SUCCESS, "* Successful created.");

    // Carregando a corrida criada
    new bool:found = false;
    for(new i = 0; i < MAX_RACES; i++)
    {
        if(gRaceData[i][e_race_id])
            continue;

        found = true;
        gRaceData[i][e_race_id]         = race_id;
        gRaceData[i][e_race_cp_type]    = gPlayerCheckpointType[playerid];
        gRaceData[i][e_race_cp_size]    = gPlayerCheckpointSize[playerid];
        gRaceData[i][e_race_interior]   = GetPlayerInterior(playerid);
        gRaceData[i][e_race_vmodel]     = gPlayerRaceVehicleModel[playerid];
        format(gRaceData[i][e_race_name], MAX_RACE_NAME, "%s", gPlayerRaceName[playerid]);

        for(new j = 0; j < gPlayerCurrentCheckpoint[playerid]; j++)
    	{
    	    gCheckpointData[i][j][e_race_id]       = race_id;
            gCheckpointData[i][j][e_checkpoint_x]  = gPlayerCheckpoints[playerid][j][e_checkpoint_x];
            gCheckpointData[i][j][e_checkpoint_x]  = gPlayerCheckpoints[playerid][j][e_checkpoint_y];
            gCheckpointData[i][j][e_checkpoint_x]  = gPlayerCheckpoints[playerid][j][e_checkpoint_z];
    	}

        for(new j = 0; j < gPlayerCurrentVehicle[playerid]; j++)
    	{
    	    gVehicleData[i][j][e_race_id]    = race_id;
            gVehicleData[i][j][e_vehicle_x]  = gPlayerVehicles[playerid][j][e_vehicle_x];
            gVehicleData[i][j][e_vehicle_y]  = gPlayerVehicles[playerid][j][e_vehicle_y];
            gVehicleData[i][j][e_vehicle_z]  = gPlayerVehicles[playerid][j][e_vehicle_z];
            gVehicleData[i][j][e_vehicle_a]  = gPlayerVehicles[playerid][j][e_vehicle_a];
    	}
        break;
    }

    if(!found)
        SendClientMessage(playerid, COLOR_ERROR, "* The race could not be carried because it has reached the racing limit.");

	// Limpando dados temporários
	for(new i = 0; i < MAX_RACE_PLAYERS; i++)
	{
		if(gPlayerVehicles[playerid][i][e_vehicle_id])
		{
			DestroyVehicle(gPlayerVehicles[playerid][i][e_vehicle_id]);
			gPlayerVehicles[playerid][i][e_vehicle_id] = 0;
		}
	}
	gPlayerCheckpointType[playerid]		= 1;
	gPlayerCheckpointSize[playerid]		= 3.5;
	gIsPlayerCreatingRace[playerid]		= E_PLAYER_RACE_STATE_NONE;
	gPlayerCurrentVehicle[playerid]		= 0;
	gPlayerCurrentCheckpoint[playerid]	= 0;
	gPlayerRaceName[playerid][0]		= '\0';
	gPlayerRaceVehicleModel[playerid]	= 0;
	DisablePlayerRaceCheckpoint(playerid);

	// Escrevendo no server_log
    new playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, sizeof(playerName));
	printf("[mysql] new race inserted on database. ID: %d, by: %s", race_id, playerName);
	return 1;
}

//------------------------------------------------------------------------------

public OnRaceGridLoad(raceid)
{
    new rows, fields;
	cache_get_data(rows, fields, gMySQL);
    for(new i = 0; i < rows; i++)
    {
        gVehicleData[raceid][i][e_race_id]      = cache_get_field_content_int(i, "race_id", gMySQL);
        gVehicleData[raceid][i][e_vehicle_x]    = cache_get_field_content_float(i, "x", gMySQL);
        gVehicleData[raceid][i][e_vehicle_y]    = cache_get_field_content_float(i, "y", gMySQL);
        gVehicleData[raceid][i][e_vehicle_z]    = cache_get_field_content_float(i, "z", gMySQL);
        gVehicleData[raceid][i][e_vehicle_a]    = cache_get_field_content_float(i, "a", gMySQL);
        gPrizeData[raceid][i]                   = cache_get_field_content_int(i, "prize", gMySQL);
    }
}

//------------------------------------------------------------------------------

public OnRaceCheckpointLoad(raceid)
{
    new rows, fields;
	cache_get_data(rows, fields, gMySQL);
    for(new i = 0; i < rows; i++)
    {
        gCheckpointData[raceid][i][e_race_id]       = cache_get_field_content_int(i, "race_id", gMySQL);
        gCheckpointData[raceid][i][e_checkpoint_x]  = cache_get_field_content_float(i, "x", gMySQL);
        gCheckpointData[raceid][i][e_checkpoint_y]  = cache_get_field_content_float(i, "y", gMySQL);
        gCheckpointData[raceid][i][e_checkpoint_z]  = cache_get_field_content_float(i, "z", gMySQL);
    }
}

//------------------------------------------------------------------------------

hook OnGameModeInit()
{
    mysql_tquery(gMySQL, "SELECT * FROM races", "OnRaceLoad");

    for(new raceid = 0; raceid < MAX_RACES; raceid++)
    {
        for(new i = 0; i < MAX_RACE_PLAYERS; i++)
        {
            gRaceData[raceid][e_race_leaderboard][i] = INVALID_PLAYER_ID;
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES)
    {
		switch (gIsPlayerCreatingRace[playerid])
		{
			case E_PLAYER_CREATING_CHECKPOINT:
			{
				if(gPlayerCurrentCheckpoint[playerid] < MAX_RACE_CHECKPOINTS)
				{
					new Float:x, Float:y, Float:z;
					if(IsPlayerInAnyVehicle(playerid))
					{
						GetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
					}
					else
					{
						GetPlayerPos(playerid, x, y, z);
					}

					gPlayerCheckpoints[playerid][gPlayerCurrentCheckpoint[playerid]][e_checkpoint_x] = x;
					gPlayerCheckpoints[playerid][gPlayerCurrentCheckpoint[playerid]][e_checkpoint_y] = y;
					gPlayerCheckpoints[playerid][gPlayerCurrentCheckpoint[playerid]][e_checkpoint_z] = z;
					gPlayerCurrentCheckpoint[playerid]++;

					PlaySelectSound(playerid);
					GenerateCheckpoint(playerid);
					SendClientMessagef(playerid, 0x35CEFBFF, "* You created the %dº Checkpoint in the coordinates %f, %f, %f.", gPlayerCurrentCheckpoint[playerid], x, y, z);
				}
				else
				{
					PlayErrorSound(playerid);
					SendClientMessage(playerid, COLOR_ERROR, "* You have reached the maximum checkpoints limit per race.");
				}
			}
			case E_PLAYER_CREATING_GRID:
			{
				if(gPlayerCurrentVehicle[playerid] < MAX_RACE_PLAYERS)
				{
					new Float:x, Float:y, Float:z, Float:a;
					if(IsPlayerInAnyVehicle(playerid))
					{
						GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
						GetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
					}
					else
					{
						GetPlayerPos(playerid, x, y, z);
						GetPlayerFacingAngle(playerid, a);
					}

					gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_x] = x;
					gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_y] = y;
					gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_z] = z;
					gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_a] = a;

					PlaySelectSound(playerid);
					GenerateVehicle(playerid, false);
					SendClientMessagef(playerid, 0x35CEFBFF, "* You created the%dº VEHICLE IN THE COORDINATES %f, %f, %f, %f.", gPlayerCurrentVehicle[playerid] + 1, x, y, z, a);
					gPlayerCurrentVehicle[playerid]++;
				}
				else
				{
					PlayErrorSound(playerid);
					SendClientMessage(playerid, COLOR_ERROR, "* You have reached the maximum limit of players per race.");
				}
			}
		}
    }
	else if(newkeys & KEY_NO)
    {
		switch (gIsPlayerCreatingRace[playerid])
		{
			case E_PLAYER_CREATING_CHECKPOINT:
			{
				if(gPlayerCurrentCheckpoint[playerid] > 0)
				{
					new Float:x, Float:y, Float:z;
					gPlayerCurrentCheckpoint[playerid]--;
					x = gPlayerCheckpoints[playerid][gPlayerCurrentCheckpoint[playerid]][e_checkpoint_x];
					y = gPlayerCheckpoints[playerid][gPlayerCurrentCheckpoint[playerid]][e_checkpoint_y];
					z = gPlayerCheckpoints[playerid][gPlayerCurrentCheckpoint[playerid]][e_checkpoint_z];

					PlayCancelSound(playerid);
					GenerateCheckpoint(playerid);
					SendClientMessagef(playerid, 0x35CEFBFF, "* You deleted the %dº Checkpoint in the coordinates %f, %f, %f.", gPlayerCurrentCheckpoint[playerid] + 1, x, y, z);
				}
			}
			case E_PLAYER_CREATING_GRID:
			{
				if(gPlayerCurrentVehicle[playerid] > 0)
				{
					new Float:x, Float:y, Float:z, Float:a;
					gPlayerCurrentVehicle[playerid]--;
					x = gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_x];
					y = gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_y];
					z = gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_z];
					a = gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_a];

					PlayCancelSound(playerid);
					GenerateVehicle(playerid, true);
					SendClientMessagef(playerid, 0x35CEFBFF, "*You deleted the %dº VEHICLE IN THE COORDINATES%f, %f, %f, %f.", gPlayerCurrentVehicle[playerid] + 1, x, y, z, a);
				}
			}
		}
    }
	else if(((newkeys & KEY_CROUCH) && IsPlayerInAnyVehicle(playerid)) || ((newkeys & KEY_CTRL_BACK) && !IsPlayerInAnyVehicle(playerid)))
    {
		if (gIsPlayerCreatingRace[playerid] > E_PLAYER_RACE_STATE_NONE)
		{
			PlaySelectSound(playerid);
			ShowPlayerRaceDialog(playerid);
		}
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch (dialogid)
    {
        case DIALOG_RACE:
        {
            if(!response || !gRaceData[listitem][e_race_id])
            {
                PlayCancelSound(playerid);
            }
            else if(GetRacePlayerPoolSize(listitem) == GetRaceMaxPlayers(listitem))
            {
                PlayErrorSound(playerid);
                SendClientMessage(playerid, COLOR_ERROR, "* This race is crowded.");
                ShowPlayerRaceList(playerid);
            }
            else if(gRaceData[listitem][e_race_state] == RACE_STATE_STARTED)
            {
                PlaySelectSound(playerid);
                SendClientMessage(playerid, COLOR_INFO, "* This race has already started, you will be by viewer until the next match.");
                ResetPlayerRaceData(playerid);
                OnPlayerEnterRace(playerid, listitem);
            }
            else
            {
                PlaySelectSound(playerid);
                ResetPlayerRaceData(playerid);
                OnPlayerEnterRace(playerid, listitem);
            }
            gIsDialogShown[playerid] = false;
        }
        case DIALOG_RACE_LEADERBOARD:
        {
            PlaySelectSound(playerid);
        }
        case DIALOG_RACE_DELETE:
        {
            if(!response || !gRaceData[listitem][e_race_id])
            {
                PlayCancelSound(playerid);
            }
            else
            {
                new query[64];
                mysql_format(gMySQL, query, sizeof(query), "DELETE FROM `races` WHERE `races`.`id` = %d", gRaceData[listitem][e_race_id]);
                mysql_tquery(gMySQL, query, "OnRaceDelete", "ii", playerid, gRaceData[listitem][e_race_id]);
            }
            gIsDialogShown[playerid] = false;
        }
        case DIALOG_RACE_CREATOR:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
			}
			else
			{
				switch (listitem)
				{
					case 0:
					{
						PlaySelectSound(playerid);
						gIsPlayerCreatingRace[playerid] = E_PLAYER_CREATING_CHECKPOINT;
						SendClientMessage(playerid, COLOR_INFO, " ");
						SendClientMessage(playerid, 0x35CEFBFF, "* You are creating checkpoints.");
						SendClientMessage(playerid, COLOR_SUCCESS, "* Press y to put a checkpoint in your position, n to delete the last checkpoint created and h to open the dialog.");
					}
					case 1:
					{
						PlaySelectSound(playerid);
						gIsPlayerCreatingRace[playerid] = E_PLAYER_CREATING_GRID;
						SendClientMessage(playerid, COLOR_INFO, " ");
						SendClientMessage(playerid, 0x35CEFBFF, "* You are positioning the vehicles.");
						SendClientMessage(playerid, COLOR_SUCCESS, "*Press Y to place a vehicle in your position, n to delete the last vehicle created and h to open the dialog.");
					}
					case 2:
					{
						PlaySelectSound(playerid);
						gIsPlayerCreatingRace[playerid] = E_PLAYER_CREATING_RACE;

						new output[132], bool:found = false;
						for(new i = 0; i < MAX_RACE_PLAYERS; i++)
						{
							if(gPlayerVehicles[playerid][i][e_vehicle_id])
							{
								found = true;
								new string[32];
								format(string, sizeof(string), "%dº position\n", i + 1);
								strcat(output, string);
							}
						}

						if(found)
						{
							ShowPlayerDialog(playerid, DIALOG_RACE_CREATOR_PRIZE, DIALOG_STYLE_LIST, "Awards", output, "Select", "X");
						}
						else
						{
							PlayErrorSound(playerid);
							SendClientMessage(playerid, COLOR_ERROR, "* You haven't created the start grid yet.");
							ShowPlayerRaceDialog(playerid);
						}
					}
					case 3:
					{
						PlaySelectSound(playerid);
						ShowPlayerDialog(playerid, DIALOG_RACE_CREATOR_CONFIG, DIALOG_STYLE_LIST, "Configuration", "Race Name\nVehicle Model\nCheckpoint Type\nCheckpoint size", "Select", "X");
					}
					case 4:
					{
						if(gPlayerCurrentVehicle[playerid] < MINIMUM_PLAYERS_TO_START_RACE)
						{
							PlayErrorSound(playerid);
							ShowPlayerRaceDialog(playerid);
							SendClientMessagef(playerid, COLOR_ERROR, "* You need to create at least %d GRID positions to export.", MINIMUM_PLAYERS_TO_START_RACE);
						}
						else if(gPlayerCurrentCheckpoint[playerid] < 1)
						{
							PlayErrorSound(playerid);
							ShowPlayerRaceDialog(playerid);
							SendClientMessage(playerid, COLOR_ERROR, "* You Need to Create at Least 1 Checkpoint to Export.");
						}
						else if(strlen(gPlayerRaceName[playerid]) < 1)
						{
							PlayErrorSound(playerid);
							ShowPlayerRaceDialog(playerid);
							SendClientMessage(playerid, COLOR_ERROR, "* You did not define Race Names.");
						}
						else if(gPlayerRaceVehicleModel[playerid] == 0)
						{
							PlayErrorSound(playerid);
							ShowPlayerRaceDialog(playerid);
							SendClientMessage(playerid, COLOR_ERROR, "* You did not define the race vehicle.");
						}
						else
						{
							new query[200];
			                mysql_format(gMySQL, query, sizeof(query), "INSERT INTO races (user_id, name, cp_type, cp_size, interior, vehicleid, created_at) VALUES (%d, '%e', %d, %.2f, %d, %d, now())", GetPlayerDatabaseID(playerid), gPlayerRaceName[playerid], gPlayerCheckpointType[playerid], gPlayerCheckpointSize[playerid], GetPlayerInterior(playerid), gPlayerRaceVehicleModel[playerid]);
			            	mysql_tquery(gMySQL, query, "OnRaceExport", "i", playerid);
						}
					}
					case 5:
					{
						for(new i = 0; i < MAX_RACE_PLAYERS; i++)
						{
							if(gPlayerVehicles[playerid][i][e_vehicle_id])
							{
								DestroyVehicle(gPlayerVehicles[playerid][i][e_vehicle_id]);
								gPlayerVehicles[playerid][i][e_vehicle_id] = 0;
							}
						}
						PlayCancelSound(playerid);
						gPlayerRaceName[playerid][0]		= '\0';
						gPlayerRaceVehicleModel[playerid]	= 0;
						gPlayerCheckpointType[playerid]		= 1;
						gPlayerCheckpointSize[playerid]		= 3.5;
						gIsPlayerCreatingRace[playerid]		= E_PLAYER_RACE_STATE_NONE;
						gPlayerCurrentVehicle[playerid]		= 0;
						gPlayerCurrentCheckpoint[playerid]	= 0;
						gPlayerRaceVehicleModel[playerid]	= 0;
						DisablePlayerRaceCheckpoint(playerid);
						SendClientMessage(playerid, 0x35CEFBFF, "* You canceled the creation of the race.");
					}
				}
			}
		}
		case DIALOG_RACE_CREATOR_PRIZE:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
				ShowPlayerRaceDialog(playerid);
			}
			else
			{
				new caption[32];
				format(caption, sizeof(caption), "Award: %dº placed", listitem + 1);
				ShowPlayerDialog(playerid, DIALOG_RACE_PRIZE_VALUE, DIALOG_STYLE_INPUT, caption, "Enter the prize value:", "Save", "X");
				gPlayerCurrentPrize[playerid] = listitem;
			}
		}
		case DIALOG_RACE_PRIZE_VALUE:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
			}
			else
			{
				new prize;
				if(sscanf(inputtext, "i", prize))
				{
					PlayErrorSound(playerid);
					SendClientMessage(playerid, COLOR_ERROR, "* Invalid value.");

					new caption[32];
					format(caption, sizeof(caption), "Award: %dº placed", gPlayerCurrentPrize[playerid] + 1);
					ShowPlayerDialog(playerid, DIALOG_RACE_PRIZE_VALUE, DIALOG_STYLE_INPUT, caption, "Enter the prize value:", "Save", "X");
					return 1;
				}
				else
				{
					PlaySelectSound(playerid);
					SendClientMessagef(playerid, 0x35CEFBFF, "* You defined the prize of %dº placement as $%d.", gPlayerCurrentPrize[playerid] + 1, prize);
					gPlayerRacePrize[playerid][gPlayerCurrentPrize[playerid]] = prize;
				}
			}
			new output[132];
			for(new i = 0; i < MAX_RACE_PLAYERS; i++)
			{
				if(gPlayerVehicles[playerid][i][e_vehicle_id])
				{
					new string[32];
					format(string, sizeof(string), "%dº position\n", i + 1);
					strcat(output, string);
				}
			}
			ShowPlayerDialog(playerid, DIALOG_RACE_CREATOR_PRIZE, DIALOG_STYLE_LIST, "Awards", output, "Select", "X");
		}
		case DIALOG_RACE_CREATOR_CONFIG:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
				ShowPlayerRaceDialog(playerid);
			}
			else
			{
				switch (listitem)
				{
					case 0:
					{
						ShowPlayerDialog(playerid, DIALOG_RACE_CONFIG_CP_NAME, DIALOG_STYLE_INPUT, "Race Name", "Enter Race Names", "Confirm", "X");
					}
					case 1:
					{
						ShowPlayerDialog(playerid, DIALOG_RACE_CONFIG_VMODEL, DIALOG_STYLE_INPUT, "Vehicle Model", "Enter the ID of the race model of the race", "Confirm", "X");
					}
					case 2:
					{
						ShowPlayerDialog(playerid, DIALOG_RACE_CONFIG_CP_TYPE, DIALOG_STYLE_LIST, "Checkpoint Type", "Terrestrial\nAerero", "Confirm", "X");
					}
					case 3:
					{
						ShowPlayerDialog(playerid, DIALOG_RACE_CONFIG_CP_SIZE, DIALOG_STYLE_INPUT, "Checkpoint Size", "Enter the checkpoint size\nRecommended: 3.5", "Confirm", "X");
					}
				}
			}
		}
		case DIALOG_RACE_CONFIG_CP_TYPE:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
			}
			else
			{
				switch (listitem)
				{
					case 0:
						gPlayerCheckpointType[playerid] = 1;
					case 1:
						gPlayerCheckpointType[playerid] = 4;
				}
				PlaySelectSound(playerid);
				GenerateCheckpoint(playerid);
			}
			ShowPlayerDialog(playerid, DIALOG_RACE_CREATOR_CONFIG, DIALOG_STYLE_LIST, "Configuration", "Race Name\nVehicle Model\nCheckpoint Type\nCheckpoint Size", "Select", "X");
		}
		case DIALOG_RACE_CONFIG_CP_SIZE:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
			}
			else
			{
				new Float:size;
				if(sscanf(inputtext, "f", size))
				{
					PlayErrorSound(playerid);
					SendClientMessage(playerid, COLOR_ERROR, "* Invalid value.");
					ShowPlayerDialog(playerid, DIALOG_RACE_CONFIG_CP_SIZE, DIALOG_STYLE_INPUT, "Checkpoint Size", "Enter the checkpoint size\nRecommended: 3.5", "Confirm", "X");
					return 1;
				}
				else
				{
					PlaySelectSound(playerid);
					SendClientMessagef(playerid, 0x35CEFBFF, "* You defined checkpoint size %.2f.", size);
					gPlayerCheckpointSize[playerid] = size;
					GenerateCheckpoint(playerid);
				}
			}
			ShowPlayerDialog(playerid, DIALOG_RACE_CREATOR_CONFIG, DIALOG_STYLE_LIST, "Configuration", "Race Name\nVehicle Model\nCheckpoint Type\nCheckpoint Size", "Select", "X");
		}
		case DIALOG_RACE_CONFIG_CP_NAME:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
			}
			else
			{
				new name[MAX_RACE_NAME];
				if(sscanf(inputtext, "s[" #MAX_RACE_NAME "]", name))
				{
					PlayErrorSound(playerid);
					SendClientMessage(playerid, COLOR_ERROR, "* Invalid invalid name.");
					ShowPlayerDialog(playerid, DIALOG_RACE_CONFIG_CP_NAME, DIALOG_STYLE_INPUT, "Checkpoint Size", "Enter Race Name", "Confirm", "X");
					return 1;
				}
				else
				{
					PlaySelectSound(playerid);
					SendClientMessagef(playerid, 0x35CEFBFF, "* You defined Race Name: %s.", name);
					format(gPlayerRaceName[playerid], MAX_RACE_NAME, "%s", name);
				}
			}
			ShowPlayerDialog(playerid, DIALOG_RACE_CREATOR_CONFIG, DIALOG_STYLE_LIST, "Configuration", "Race Name\nVehicle Model\nCheckpoint Type\nCheckpoint Size", "Select", "X");
		}
		case DIALOG_RACE_CONFIG_VMODEL:
		{
			if(!response)
			{
				PlayCancelSound(playerid);
			}
			else
			{
				new vehicle_model;
				if(sscanf(inputtext, "i", vehicle_model))
				{
					PlayErrorSound(playerid);
					SendClientMessage(playerid, COLOR_ERROR, "* Invalid vehicle.");
					ShowPlayerDialog(playerid, DIALOG_RACE_CONFIG_VMODEL, DIALOG_STYLE_INPUT, "Vehicle Model", "Insira o ID do Vehicle Model da corrida", "Confirm", "X");
					return 1;
				}
				else if(vehicle_model < 400 || vehicle_model > 611)
				{
					PlayErrorSound(playerid);
					SendClientMessage(playerid, COLOR_ERROR, "* Invalid vehicle.");
					ShowPlayerDialog(playerid, DIALOG_RACE_CONFIG_VMODEL, DIALOG_STYLE_INPUT, "Vehicle Model", "Insira o ID do Vehicle Model da corrida", "Confirm", "X");
					return 1;
				}
				else
				{
					PlaySelectSound(playerid);
					gPlayerRaceVehicleModel[playerid] = vehicle_model;
					SendClientMessagef(playerid, 0x35CEFBFF, "* You defined the race vehicle: %d.", vehicle_model);
				}
			}
			ShowPlayerDialog(playerid, DIALOG_RACE_CREATOR_CONFIG, DIALOG_STYLE_LIST, "Configuration", "Race Name\nVehicle Model\nCheckpoint Type\nCheckpoint Size", "Select", "X");
		}
    }
    return 1;
}

//------------------------------------------------------------------------------

public OnPlayerEnterRace(playerid, raceid)
{
    if(GetPlayerGamemode(playerid) == GAMEMODE_DERBY)
    {
        ResetPlayerDerbyData(playerid);
    }
    else if(GetPlayerGamemode(playerid) == GAMEMODE_DEATHMATCH)
    {
        ResetPlayerDeathmatchData(playerid);
        ResetPlayerWeapons(playerid);
    }
    else if(GetPlayerGamemode(playerid) == GAMEMODE_RACE)
    {
        ResetPlayerRaceData(playerid);
        DisableRemoteVehicleCollisions(playerid, false);
    }

    HidePlayerLobby(playerid);
    SetPlayerRace(playerid, raceid);
    SetPlayerHealth(playerid, 9999.0);
    TogglePlayerControllable(playerid, true);
    SetPlayerGamemode(playerid, GAMEMODE_RACE);
    DisableRemoteVehicleCollisions(playerid, true);
    SetPlayerVirtualWorld(playerid, (raceid + VIRTUAL_WORLD));

    if(gRaceData[raceid][e_race_state] == RACE_STATE_WAITING_PLAYERS || gRaceData[raceid][e_race_state] == RACE_STATE_STARTING)
    {
        new rand = random(sizeof(gLobbySpawns));
        SetPlayerInterior(playerid, 10);
        SetPlayerPos(playerid, gLobbySpawns[rand][0], gLobbySpawns[rand][1], gLobbySpawns[rand][2]);
        SetPlayerFacingAngle(playerid, gLobbySpawns[rand][3]);
        SendClientMessagef(playerid, COLOR_SUCCESS, "* You entered the race %s!", gRaceData[raceid][e_race_name]);
        gPlayerData[playerid][e_state] = RACE_PLAYER_STATE_RACING;
    }

    if(gRaceData[raceid][e_race_state] == RACE_STATE_WAITING_PLAYERS)
    {
        GameTextForPlayer(playerid, "~y~Waiting for players...", 1250, 3);
        SendClientMessage(playerid, COLOR_SUCCESS, "* Awaiting more players to start...");

        new count = 0;
        foreach(new i: Player)
        {
            if(GetPlayerRace(i) == raceid)
            {
                count++;
            }
        }

        if(count >= MINIMUM_PLAYERS_TO_START_RACE)
        {
            foreach(new i: Player)
            {
                if(GetPlayerRace(i) == raceid)
                {
                    GameTextForPlayer(i, "~g~Starting Race..", 1250, 3);
                    SendClientMessagef(i, COLOR_SUCCESS, "* The minimum amount of players has been reached, the race will start in %d second.", RACE_COUNT_DOWN);
                }
            }
            gRaceCountdown[raceid] = RACE_COUNT_DOWN;
            gRaceData[raceid][e_race_state] = RACE_STATE_STARTING;
        }
    }
    else if(gRaceData[raceid][e_race_state] == RACE_STATE_STARTED)
    {
        gPlayerData[playerid][e_state] = RACE_PLAYER_STATE_SPECTATING;
        TogglePlayerSpectating(playerid, true);

        foreach(new i: Player)
        {
            if(GetPlayerRace(i) == raceid && gPlayerData[i][e_state] == RACE_PLAYER_STATE_RACING)
            {
                SetPlayerInterior(playerid, 0);
                SetPlayerSpecatateTarget(playerid, i);
                break;
            }
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

task OnRaceUpdate[1000]()
{
    for(new raceid = 0; raceid < MAX_RACES; raceid++)
    {
        if(!gRaceData[raceid][e_race_id])
            break;

        if(gRaceData[raceid][e_race_state] == RACE_STATE_WAITING_PLAYERS)
        {
            foreach(new i: Player)
            {
                if(GetPlayerRace(i) == raceid)
                {
                    if(gRaceData[raceid][e_race_state] == RACE_STATE_WAITING_PLAYERS)
                    {
                        GameTextForPlayer(i, "~y~Waiting for players...", 1250, 3);
                    }
                }
            }
        }
        else if(gRaceData[raceid][e_race_state] == RACE_STATE_STARTING)
        {
            if(gRaceCountdown[raceid] > 0)
            {
                foreach(new i: Player)
                {
                    if(GetPlayerRace(i) == raceid)
                    {
                        new countstr[38];
                        format(countstr, sizeof(countstr), "~g~Starting Running~n~%02d", gRaceCountdown[raceid]);
                        GameTextForPlayer(i, countstr, 1250, 3);

                        if(gRaceCountdown[raceid] < 6)
                            PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0);
                    }
                }
                gRaceCountdown[raceid]--;
            }
            else
            {
                new racer_id = 0;
                gRaceData[raceid][e_race_state] = RACE_STATE_STARTED;
                gRaceCountdown[raceid] = 6;
                foreach(new i: Player)
                {
                    if(GetPlayerRace(i) == raceid)
                    {
                        PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0);
                        GameTextForPlayer(i, "~g~~h~A corrida ira iniciar~n~get ready", 1250, 3);
                        gPlayerData[i][e_grid_id] = racer_id;
                        gPlayerData[i][e_checkpoint_id] = 0;
                        gVehicleData[raceid][racer_id][e_vehicle_id] = CreateVehicle(gRaceData[raceid][e_race_vmodel], gVehicleData[raceid][racer_id][e_vehicle_x], gVehicleData[raceid][racer_id][e_vehicle_y], gVehicleData[raceid][racer_id][e_vehicle_z], gVehicleData[raceid][racer_id][e_vehicle_a], -1, -1, -1);
                        LinkVehicleToInterior(gVehicleData[raceid][racer_id][e_vehicle_id], gRaceData[raceid][e_race_interior]);
                        SetVehicleVirtualWorld(gVehicleData[raceid][racer_id][e_vehicle_id], (raceid + VIRTUAL_WORLD));
                        SetPlayerInterior(i, gRaceData[raceid][e_race_interior]);
                        PutPlayerInVehicle(i, gVehicleData[raceid][racer_id][e_vehicle_id], 0);
                        SetCameraBehindPlayer(i);
                        TogglePlayerControllable(i, false);
                        racer_id++;
                    }
                }
            }
        }
        else if(gRaceData[raceid][e_race_state] == RACE_STATE_STARTED)
        {
            if(gRaceCountdown[raceid] > 1)
            {
                gRaceCountdown[raceid]--;
                foreach(new i: Player)
                {
                    if(GetPlayerRace(i) == raceid)
                    {
                        new countstr[38];
                        format(countstr, sizeof(countstr), "~r~%02d", gRaceCountdown[raceid]);
                        GameTextForPlayer(i, countstr, 1250, 3);
                        PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0);
                    }
                }
            }
            else if(gRaceCountdown[raceid] == 1)
            {
                gRaceCountdown[raceid]--;
                foreach(new i: Player)
                {
                    if(GetPlayerRace(i) == raceid)
                    {
                        GameTextForPlayer(i, "~g~GO!", 3000, 3);
                        PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
                        ShowPlayerRaceCheckpoint(i);
                        TogglePlayerControllable(i, true);
                        gPlayerData[i][e_start_time] = GetTickCount();
                    }
                }
            }
        }
    }
}

//------------------------------------------------------------------------------

hook OnPlayerSpawn(playerid)
{
    if(GetPlayerRace(playerid) != INVALID_RACE_ID && gPlayerData[playerid][e_state] == RACE_PLAYER_STATE_RACING)
    {
        new raceid = GetPlayerRace(playerid);
        new racer_id = gPlayerData[playerid][e_grid_id];
        new vehicleid = gVehicleData[raceid][racer_id][e_vehicle_id];
        SetVehicleToRespawn(vehicleid);

        new cid = gPlayerData[playerid][e_checkpoint_id];
        new Float:x, Float:y, Float:z;
        if(cid > 0)
        {
            x = gCheckpointData[raceid][cid - 1][e_checkpoint_x];
            y = gCheckpointData[raceid][cid - 1][e_checkpoint_y];
            z = gCheckpointData[raceid][cid - 1][e_checkpoint_z];
        }
        else
        {
            x = gVehicleData[raceid][racer_id][e_vehicle_x];
            y = gVehicleData[raceid][racer_id][e_vehicle_y];
            z = gVehicleData[raceid][racer_id][e_vehicle_z];
        }
        SetVehiclePos(vehicleid, x, y, z);
        PutPlayerInVehicle(playerid, vehicleid, 0);
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerUpdate(playerid)
{
    if(GetPlayerRace(playerid) != INVALID_RACE_ID && gPlayerData[playerid][e_state] == RACE_PLAYER_STATE_SPECTATING)
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
        {
            new raceid = GetPlayerRace(playerid);
            TogglePlayerSpectating(playerid, true);
            foreach(new i: Player)
            {
                if(GetPlayerRace(i) == raceid && gPlayerData[i][e_state] == RACE_PLAYER_STATE_RACING)
                {
                    SetPlayerSpecatateTarget(playerid, i);
                    break;
                }
            }
        }
        else if(gPlayerSpecTick[playerid] < GetTickCount())
        {
            new
                raceid = GetPlayerRace(playerid),
                Keys,
                ud,
                lr
            ;
            GetPlayerKeys(playerid, Keys, ud, lr);
            gPlayerSpecTick[playerid] = GetTickCount() + 50;
            if(lr == KEY_LEFT)
            {
                foreach(new i: Player)
                {
                    if(GetPlayerRace(i) == raceid && gPlayerData[i][e_state] == RACE_PLAYER_STATE_RACING)
                    {
                        if(gPlayerData[playerid][e_spec_targetid] > i)
                        {
                            SetPlayerSpecatateTarget(playerid, i);
                        }
                    }
                }
            }
            else if(lr == KEY_RIGHT)
            {
                foreach(new i: Player)
                {
                    if(GetPlayerRace(i) == raceid && gPlayerData[i][e_state] == RACE_PLAYER_STATE_RACING)
                    {
                        if(gPlayerData[playerid][e_spec_targetid] < i)
                        {
                            SetPlayerSpecatateTarget(playerid, i);
                        }
                    }
                }
            }
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerEnterRaceCP(playerid)
{
    new raceid = GetPlayerRace(playerid);
    if(raceid != INVALID_RACE_ID && gRaceData[raceid][e_race_state] == RACE_STATE_STARTED)
    {
        PlaySelectSound(playerid);
        gPlayerData[playerid][e_checkpoint_id]++;

        new cid     = gPlayerData[playerid][e_checkpoint_id];
        new Float:x = gCheckpointData[raceid][cid][e_checkpoint_x];
        new Float:y = gCheckpointData[raceid][cid][e_checkpoint_y];
        new Float:z = gCheckpointData[raceid][cid][e_checkpoint_z];
        if(cid == MAX_RACE_CHECKPOINTS || (x == 0.0 && y == 0.0 && z == 0.0))
        {
            gRaceData[raceid][e_race_leaderboard][gRaceData[raceid][e_race_counter]] = playerid;
            gRaceData[raceid][e_race_counter]++;
            gPlayerData[playerid][e_end_time] = GetTickCount();
            DisablePlayerRaceCheckpoint(playerid);

            new minutes         = (gPlayerData[playerid][e_end_time] - gPlayerData[playerid][e_start_time]) / 60000;
            new seconds         = (((gPlayerData[playerid][e_end_time] - gPlayerData[playerid][e_start_time]) % (1000 * 60 * 60)) % (1000 * 60)) / 1000;
            new milliseconds    = (gPlayerData[playerid][e_end_time] - gPlayerData[playerid][e_start_time]) % 1000;

            new gameText[64];
            format(gameText, sizeof(gameText), "~g~Completed Race~n~~w~%02d:%02d:%03d", minutes, seconds, milliseconds);
            GameTextForPlayer(playerid, gameText, 3000, 3);

            // Verifica se ainda há jogadores correndo
            new remaining_racers = 0;
            foreach(new i: Player)
            {
                if(GetPlayerRace(i) == raceid && gPlayerData[i][e_state] == RACE_PLAYER_STATE_RACING && gPlayerData[i][e_end_time] == 0)
                {
                    remaining_racers++;
                }
            }

            // Se não houver mais corredores finaliza a corrida,
            // Se houver, aguarda a corrida finalizar
            if(remaining_racers == 0)
            {
                new output[512];
                strcat(output, "#\tPlayer\tTime\n");
                for(new i = 0; i < MAX_RACE_PLAYERS; i++)
                {
                    new j = gRaceData[raceid][e_race_leaderboard][i];

                    if(j == INVALID_PLAYER_ID)
                        continue;

                    new j_minutes         = (gPlayerData[j][e_end_time] - gPlayerData[j][e_start_time]) / 60000;
                    new j_seconds         = (((gPlayerData[j][e_end_time] - gPlayerData[j][e_start_time]) % (1000 * 60 * 60)) % (1000 * 60)) / 1000;
                    new j_milliseconds    = (gPlayerData[j][e_end_time] - gPlayerData[j][e_start_time]) % 1000;

                    GivePlayerCash(j, gPrizeData[raceid][i]);
                    if(i == 0)
                    {
                        SetPlayerPoint(j, GetPlayerPoint(j) + 5);
                        SetPlayerRaceWins(j, GetPlayerRaceWins(j) + 1);
                    }
                    else if(i == 1)
                        SetPlayerPoint(j, GetPlayerPoint(j) + 3);
                    else
                        SetPlayerPoint(j, GetPlayerPoint(j) + 1);

                    new string[64];
                    format(string, sizeof(string), "%d\t%s\t%02d:%02d:%03d\n", i + 1, GetPlayerNamef(j), j_minutes, j_seconds, j_milliseconds);
                    strcat(output, string);
                }

                foreach(new i: Player)
                {
                    if(GetPlayerRace(i) == raceid)
                    {
                        ShowPlayerDialog(i, DIALOG_RACE_LEADERBOARD, DIALOG_STYLE_TABLIST_HEADERS, "FINAL RESULTS", output, "Close", "");
                    }
                }
                defer EndRace(raceid);
            }
            else
            {
                TogglePlayerSpectating(playerid, true);
                gPlayerData[playerid][e_state] = RACE_PLAYER_STATE_SPECTATING;
                new grid = gPlayerData[playerid][e_grid_id];
                DestroyVehicle(gVehicleData[raceid][grid][e_vehicle_id]);
                gVehicleData[raceid][grid][e_vehicle_id] = INVALID_VEHICLE_ID;
                foreach(new i: Player)
                {
                    if(GetPlayerRace(i) == raceid && gPlayerData[i][e_state] == RACE_PLAYER_STATE_RACING && i != playerid)
                    {
                        SetPlayerSpecatateTarget(playerid, i);
                        break;
                    }
                }
            }
        }
        else
        {
            ShowPlayerRaceCheckpoint(playerid);
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerDisconnect(playerid, reason)
{
    gIsDialogShown[playerid] = false;
    ResetPlayerRaceData(playerid);

    gIsPlayerCreatingRace[playerid]		= E_PLAYER_RACE_STATE_NONE;
	gPlayerCheckpointType[playerid]		= 1;
	gPlayerCheckpointSize[playerid]		= 3.5;
	gPlayerCurrentVehicle[playerid]		= 0;
	gPlayerCurrentCheckpoint[playerid]	= 0;
	gPlayerRaceVehicleModel[playerid]	= 0;
	gPlayerRaceName[playerid][0]		= '\0';
    return 1;
}

//------------------------------------------------------------------------------

timer EndRace[7500](raceid)
{
    // Reseta todas as variaveis e envia o jogadores para o lobby da corrida

    gRaceData[raceid][e_race_state] = RACE_STATE_WAITING_PLAYERS;
    gRaceData[raceid][e_race_counter] = 0;
    for(new i = 0; i < MAX_RACE_PLAYERS; i++)
    {
        gRaceData[raceid][e_race_leaderboard][i] = INVALID_PLAYER_ID;
    }

    for(new i = 0; i < MAX_RACE_PLAYERS; i++)
    {
        DestroyVehicle(gVehicleData[raceid][i][e_vehicle_id]);
        gVehicleData[raceid][i][e_vehicle_id] = INVALID_VEHICLE_ID;
    }

    foreach(new i: Player)
    {
        if(GetPlayerRace(i) == raceid)
        {
            if(GetPlayerState(i) == PLAYER_STATE_SPECTATING)
            {
                TogglePlayerSpectating(i, false);
                gPlayerData[i][e_spec_targetid] = INVALID_PLAYER_ID;
            }

            gPlayerData[i][e_grid_id] = 0;
            gPlayerData[i][e_checkpoint_id] = 0;
            gPlayerData[i][e_start_time] = 0;
            gPlayerData[i][e_end_time] = 0;
            gPlayerData[i][e_state] = RACE_PLAYER_STATE_NONE;
            OnPlayerEnterRace(i, raceid);
        }
    }
}

//------------------------------------------------------------------------------

YCMD:createrace(playerid, params[], help)
{
	if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
	{
		if(!gIsPlayerCreatingRace[playerid])
		{
			gIsPlayerCreatingRace[playerid] = E_PLAYER_CREATING_RACE;
			PlaySelectSound(playerid);
			ShowPlayerRaceDialog(playerid);
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "* You are already creating a race.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:deleterace(playerid, params[], help)
{
	if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
	{
        ShowPlayerRaceList(playerid, true);
        PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COLOR_WARNING, "* ATTENTION: This operation has no return!");
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
	}
	return 1;
}

//------------------------------------------------------------------------------

ShowPlayerRaceCheckpoint(playerid)
{
    new cid     = gPlayerData[playerid][e_checkpoint_id];
    new raceid  = GetPlayerRace(playerid);
    new Float:x = gCheckpointData[raceid][cid][e_checkpoint_x];
    new Float:y = gCheckpointData[raceid][cid][e_checkpoint_y];
    new Float:z = gCheckpointData[raceid][cid][e_checkpoint_z];
    new ctype = gRaceData[raceid][e_race_cp_type];
    new Float:size = gRaceData[raceid][e_race_cp_size];

    if(cid >= (MAX_RACE_CHECKPOINTS - 1))
    {
        SetPlayerRaceCheckpoint(playerid, ctype, x, y, z, 0.0, 0.0, 0.0, size);
    }
    else
    {
        new Float:nextx = gCheckpointData[raceid][cid + 1][e_checkpoint_x];
        new Float:nexty = gCheckpointData[raceid][cid + 1][e_checkpoint_y];
        new Float:nextz = gCheckpointData[raceid][cid + 1][e_checkpoint_z];
        if(nextx == 0.0 && nexty == 0.0 && nextz == 0.0)
        {
            SetPlayerRaceCheckpoint(playerid, ctype, x, y, z, 0.0, 0.0, 0.0, size);
        }
        else
        {
            SetPlayerRaceCheckpoint(playerid, (ctype == 4) ? 3 : 0, x, y, z, nextx, nexty, nextz, size);
        }
    }
}

//------------------------------------------------------------------------------

ResetPlayerRaceData(playerid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
        TogglePlayerSpectating(playerid, false);

    new raceid = GetPlayerRace(playerid);
    SetPlayerRace(playerid, INVALID_RACE_ID);
    if(raceid != INVALID_RACE_ID)
    {
        if(gRaceData[raceid][e_race_state] == RACE_STATE_STARTED)
        {
            if(gPlayerData[playerid][e_state] == RACE_PLAYER_STATE_RACING)
            {
                new grid = gPlayerData[playerid][e_grid_id];
                DestroyVehicle(gVehicleData[raceid][grid][e_vehicle_id]);
                gVehicleData[raceid][grid][e_vehicle_id] = INVALID_VEHICLE_ID;
            }
            DisablePlayerRaceCheckpoint(playerid);

            // Verifica se ainda há jogadores correndo
            new remaining_racers = 0;
            foreach(new i: Player)
            {
                if(GetPlayerRace(i) == raceid && gPlayerData[i][e_state] == RACE_PLAYER_STATE_RACING)
                {
                    remaining_racers++;
                }
            }

            // Se não houver mais corredores finaliza a corrida,
            // Se houver, aguarda a corrida finalizar
            if(remaining_racers == 0)
            {
                new output[512];
                strcat(output, "#\tPlayer\tTime\n");
                for(new i = 0; i < MAX_RACE_PLAYERS; i++)
                {
                    new j = gRaceData[raceid][e_race_leaderboard][i];

                    if(j == INVALID_PLAYER_ID)
                        continue;

                    new j_minutes         = (gPlayerData[j][e_end_time] - gPlayerData[j][e_start_time]) / 60000;
                    new j_seconds         = (((gPlayerData[j][e_end_time] - gPlayerData[j][e_start_time]) % (1000 * 60 * 60)) % (1000 * 60)) / 1000;
                    new j_milliseconds    = (gPlayerData[j][e_end_time] - gPlayerData[j][e_start_time]) % 1000;

                    GivePlayerCash(j, gPrizeData[raceid][i]);
                    if(i == 0)
                    {
                        SetPlayerPoint(j, GetPlayerPoint(j) + 5);
                        SetPlayerRaceWins(j, GetPlayerRaceWins(j) + 1);
                    }
                    else if(i == 1)
                        SetPlayerPoint(j, GetPlayerPoint(j) + 3);
                    else
                        SetPlayerPoint(j, GetPlayerPoint(j) + 1);

                    new string[64];
                    format(string, sizeof(string), "%d\t%s\t%02d:%02d:%03d\n", i + 1, GetPlayerNamef(j), j_minutes, j_seconds, j_milliseconds);
                    strcat(output, string);
                }

                foreach(new i: Player)
                {
                    if(GetPlayerRace(i) == raceid)
                    {
                        ShowPlayerDialog(i, DIALOG_RACE_LEADERBOARD, DIALOG_STYLE_TABLIST_HEADERS, "FINAL RESULTS", output, "Close", "");
                    }
                }
                defer EndRace(raceid);
            }
        }
        gPlayerData[playerid][e_grid_id] = 0;
        gPlayerData[playerid][e_checkpoint_id] = 0;
        gPlayerData[playerid][e_start_time] = 0;
        gPlayerData[playerid][e_end_time] = 0;
        gPlayerData[playerid][e_state] = RACE_PLAYER_STATE_NONE;

        // Se não houver nenhum jogador correndo, reiniciar a corrida
        if(GetRacePlayerPoolSize(raceid) == 0)
        {
            EndRace(raceid);
        }
    }
}

//------------------------------------------------------------------------------

static GenerateCheckpoint(playerid)
{
	if(gPlayerCurrentCheckpoint[playerid] > 0)
	{
		new Float:x, Float:y, Float:z;
		x = gPlayerCheckpoints[playerid][gPlayerCurrentCheckpoint[playerid] - 1][e_checkpoint_x];
		y = gPlayerCheckpoints[playerid][gPlayerCurrentCheckpoint[playerid] - 1][e_checkpoint_y];
		z = gPlayerCheckpoints[playerid][gPlayerCurrentCheckpoint[playerid] - 1][e_checkpoint_z];
		SetPlayerRaceCheckpoint(playerid, (gPlayerCheckpointType[playerid] > 0) ? gPlayerCheckpointType[playerid] : 1, x, y, z, 0.0, 0.0, 0.0, (gPlayerCheckpointSize[playerid] > 0.0) ? gPlayerCheckpointSize[playerid] : 3.5);
	}
	else
	{
		DisablePlayerRaceCheckpoint(playerid);
	}
}

//------------------------------------------------------------------------------

static GenerateVehicle(playerid, bool:delete)
{
	if(gPlayerCurrentVehicle[playerid] < MAX_RACE_PLAYERS)
	{
		if(delete)
		{
			if(gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_id])
			{
				DestroyVehicle(gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_id]);
				gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_id] = 0;
			}
		}
		else
		{
			new Float:x, Float:y, Float:z, Float:a;
			x = gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_x];
			y = gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_y];
			z = gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_z];
			a = gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_a];

			if(gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_id])
			{
				DestroyVehicle(gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_id]);
			}
			gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_id] = CreateVehicle((IsPlayerInAnyVehicle(playerid)) ? GetVehicleModel(GetPlayerVehicleID(playerid)) : 494, x, y, z + 5.0, a, -1, -1, -1);
			LinkVehicleToInterior(gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_id], GetPlayerInterior(playerid));
			SetVehicleVirtualWorld(gPlayerVehicles[playerid][gPlayerCurrentVehicle[playerid]][e_vehicle_id], GetPlayerVirtualWorld(playerid));
		}
	}
}

//------------------------------------------------------------------------------

SetPlayerSpecatateTarget(playerid, targetid)
{
    if(IsPlayerInAnyVehicle(targetid))
    {
        PlayerSpectateVehicle(playerid, GetPlayerVehicleID(targetid));
    }
    else
    {
        PlayerSpectatePlayer(playerid, targetid);
    }
    gPlayerData[playerid][e_spec_targetid] = targetid;
}

//------------------------------------------------------------------------------

SetPlayerRace(playerid, raceid)
{
    gPlayerCurrentRace[playerid] = raceid;
}

GetPlayerRace(playerid)
{
    return gPlayerCurrentRace[playerid];
}

GetRacePlayerPoolSize(raceid)
{
    new count = 0;
    foreach(new i: Player)
    {
        if(GetPlayerRace(i) == raceid)
        {
            count++;
        }
    }
    return count;
}

GetRaceMaxPlayers(raceid)
{
    new count = 0;
    for(new i = 0; i < MAX_RACE_PLAYERS; i++)
    {
        if(gVehicleData[raceid][i][e_race_id] == 0)
            break;

        count++;
    }
    return count;
}

IsRaceDialogVisible(playerid)
{
    return gIsDialogShown[playerid];
}

//------------------------------------------------------------------------------

ShowPlayerRaceList(playerid, bool:delete = false)
{
    new output[4096], string[64], status[24], count = 0;
    strcat(output, "Name\tPlayers\tStatus\n");
    for(new i = 0; i < MAX_RACES; i++)
    {
        if(!gRaceData[i][e_race_id])
            break;

        switch (gRaceData[i][e_race_state])
        {
            case RACE_STATE_WAITING_PLAYERS:
                status = "Waiting for players";
            case RACE_STATE_STARTING:
                status = "About to start";
            case RACE_STATE_STARTED:
                status = "In progress";
        }
        format(string, sizeof(string), "%s\t%d / %d\t%s\n", gRaceData[i][e_race_name], GetRacePlayerPoolSize(i), GetRaceMaxPlayers(i), status);
        strcat(output, string);
        count++;
    }
    gIsDialogShown[playerid] = true;

    if(count)
        ShowPlayerDialog(playerid, (!delete) ? DIALOG_RACE : DIALOG_RACE_DELETE, DIALOG_STYLE_TABLIST_HEADERS, "Racing", output, "Select", "X");
    else
        ShowPlayerDialog(playerid, (!delete) ? DIALOG_RACE : DIALOG_RACE_DELETE, DIALOG_STYLE_LIST, "Corridas", "No existing room.", "X", "");
}

//------------------------------------------------------------------------------

ShowPlayerRaceDialog(playerid)
{
	ShowPlayerDialog(playerid, DIALOG_RACE_CREATOR, DIALOG_STYLE_LIST, "Creating a race", "Checkpoints\nSparking grid\nAwards\nConfiguration\nExport\nCancel", "Select", "X");
}
