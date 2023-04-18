/*******************************************************************************
* Name DO ARQUIVO :		modules/gameplay/racecreator.pwn
*
* DESCRIPTION : 
 * Allows events to be created within the server and players 
 * Partip. 
 * 
 * GRADES :
*	   -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

// ID do virtual world dos events
static const VIRTUAL_WORLD = 1999;

//------------------------------------------------------------------------------

// Interiors where players will spawn on each map
static const gPlayerSpawnsData[][][] =
{
    // K.A.C.C
    { 0, "K.A.C.C" },
    // RC Battlefield
    { 10, "Battlefield R.C" },
    // San fierro SHIP
    { 0, "San Fierro Navio" }
};

// Locais onde os jogadores irão dar spawn em cada mapa
static const Float:gPlayerSpawns[][][] =
{
    // K.A.C.C
    {
        {   2540.6560, 2848.4426,  10.8203,    227.6038     },
        {   2546.0940, 2836.8591,  10.8203,    2.170000     },
        {   2585.9043, 2848.9812,  10.8203,    126.8779     },
        {   2573.4312, 2848.3315,  10.8203,    228.2305     },
        {   2596.0417, 2805.9031,  10.8203,    35.86540     },
        {   2615.7966, 2849.2153,  10.8203,    141.6047     },
        {   2605.7920, 2805.8025,  10.8203,    321.1230     },
        {   2614.1472, 2848.3218,  19.9922,    88.94080     },
        {   2562.1228, 2848.2454,  19.9922,    274.4125     },
        {   2543.5471, 2805.7273,  19.9999,    268.9409     },
        {   2584.9009, 2825.5068,  19.9922,    202.1277     },
        {   2563.6899, 2848.8738,  10.8203,    117.3095     }
    },
    // RC Battlefield
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
        {   -1005.3085,   1078.5878,  1343.1176,  80.8140     },
        {   -1005.3085,   1078.5878,  1343.1176,  80.8140     },
        {   -1005.3085,   1078.5878,  1343.1176,  80.8140     }
    },
    // San fierro SHIP
    {
        {   -2438.4280, 1538.8979,  11.7656,    341.1123    },
        {   -2425.3489, 1534.6957,  2.11720,    18.08600    },
        {   -2402.7271, 1550.9099,  2.11720,    4.275900    },
        {   -2391.2837, 1539.8258,  2.11720,    177.5273    },
        {   -2370.6228, 1533.5748,  10.8209,    41.53940    },
        {   -2366.5286, 1534.2919,  2.11720,    6.109000    },
        {   -2379.7495, 1542.1860,  2.11720,    264.5880    },
        {   -2403.1509, 1540.5975,  2.11720,    103.8465    },
        {   -2391.2615, 1554.8647,  2.11720,    81.26290    },
        {   -2440.7769, 1555.1104,  2.12310,    263.9146    },
        {   -2416.0430, 1557.1355,  10.8281,    173.6503    },
        {   -2379.5281, 1554.7286,  2.11720,    234.4609    }
    }
};

//------------------------------------------------------------------------------

static const weaponSlotList[][] =
{
    "Pulse",
    "Melee",
    "Pistols",
    "Shotguns",
    "Submachiners",
    "Assault",
    "Rifles",
    "Heavy weaponry",
    "Explosives",
    "Spray",
    "Others"
};

static const weaponHandNames[][][] =
{
    {0, "Pulse"},
    {1, "English punch"}
};

static const weaponMeeleNames[][][] =
{
    {2, "Golf Club"},
    {3, "Cassettete"},
    {4, "make"},
    {5, "Baseball bat"},
    {6, "Town"},
    {7, "PoolCue"},
    {8, "Katana"},
    {9, "Chainsaw"}
};

static const weaponPistolNames[][][] =
{
    {22, "Colt45"},
    {23, "Silent"},
    {24, "Desert Eagle"}
};

static const weaponShotgunNames[][][] =
{
    {25, "Shotgun"},
    {26, "Pipe"},
    {27, "Automatic"}
};

static const weaponSubmachineNames[][][] =
{
    {28, "Uzi"},
    {29, "MP5"},
    {32, "TEC9"}
};

static const weaponAssaultNames[][][] =
{
    {30, "AK-47"},
    {31, "M4"}
};

static const weaponRifleNames[][][] =
{
    {33, "Carbine"},
    {34, "Sniper"}
};

static const weaponHeavyNames[][][] =
{
    {35, "Rocket"},
    {36, "Missel Follower"},
    {37, "Launches Flames"},
    {38, "Minigun"}
};

static const weaponExplosivesNames[][][] =
{
    {16, "Grenade"},
    {18, "Molotov"},
    {39, "Remote"}
};

static const weaponSprayNames[][][] =
{
    {41, "Can of paint"},
    {42, "Extinguisher"}
};

static const weaponOtherNames[][][] =
{
    {10, "Dildo Purple"},
    {11, "Dildo Small"},
    {12, "Vibrator"},
    {13, "Vibrador Silver"},
    {14, "Flowers"},
    {15, "Walking stick"}
};

//------------------------------------------------------------------------------

enum
{
    EVENT_STATE_NONE,
    EVENT_STATE_STARTING,
    EVENT_STATE_STARTED
}

enum
{
    EVENT_PLAYER_STATE_NONE,
    EVENT_PLAYER_STATE_ALIVE,
    EVENT_PLAYER_STATE_DEAD
}

// Player data
static bool:gIsPlayerInEvent[MAX_PLAYERS];
static bool:gIsPlayerCreatingEvent[MAX_PLAYERS];
static gPlayerSpectateTargetID[MAX_PLAYERS];
static gPlayerState[MAX_PLAYERS];
static gPlayerSpecTick[MAX_PLAYERS];

// Event data
static gEventState;
static gEventWeapons[11];
static gEventSpawn = -1;
static gEventPrize = 0;
static gEventCountdown = 0;
static gEventPlayersID[MAX_PLAYERS];
static gEventPlayersCount;
static Timer:gEventTimer;

//------------------------------------------------------------------------------

hook OnGameModeInit()
{
    // Portões do mapa K.A.C.C
    CreateDynamicObject(971, 2539.19995117, 2823.00000000, 13.19999981, 0.00000000, 0.00000000, 90.00000000, VIRTUAL_WORLD);
    CreateDynamicObject(971, 2616.60009766, 2830.69995117, 13.39999962, 0.00000000, 0.00000000, 270.0000000, VIRTUAL_WORLD);
    // Portões do mapa Navio de San Fierro
    CreateDynamicObject(19912, -2439.26000, 1550.32000000, 16.21000000, 90.00000000, 90.000000, 0.000000000, VIRTUAL_WORLD);
    CreateDynamicObject(19912, -2439.26000, 1538.83000000, 16.21000000, 90.00000000, 90.000000, 0.000000000, VIRTUAL_WORLD);
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerDisconnect(playerid, reason)
{
    gPlayerState[playerid] = EVENT_PLAYER_STATE_NONE;
    gIsPlayerInEvent[playerid] = false;
    ResetPlayerEventCreatorData(playerid);
    return 1;
}

//------------------------------------------------------------------------------

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch (dialogid)
    {
        case DIALOG_EVENT_CREATOR:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
                ResetPlayerEventCreatorData(playerid);
                SendClientMessage(playerid, COLOR_INFO, "* You canceled the creation of the event.");
            }
            else
            {
                PlaySelectSound(playerid);
                switch (listitem)
                {
                    case 0:
                    {
                        new output[148], string[24];
                        strcat(output, "Slot\tName\n");
                        for(new i = 0; i < sizeof(weaponSlotList); i++)
                        {
                            format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Weapon of event", output, "Select", "X");
                    }
                    case 1:
                    {
                        new output[256], string[64];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(gPlayerSpawnsData); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", gPlayerSpawnsData[i][1], (gEventSpawn == i) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_SPAWN, DIALOG_STYLE_TABLIST_HEADERS, "Event location", output, "Select", "X");
                    }
                    case 2:
                    {
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_PRIZE, DIALOG_STYLE_INPUT, "Event award", "Enter the winner's prize value", "Save", "X");
                    }
                    case 3:
                    {
                        if(gEventSpawn == -1)
                        {
                            PlayErrorSound(playerid);
                            SendClientMessage(playerid, COLOR_ERROR, "* You did not define the place of the event.");
                            ShowPlayerEventDialog(playerid);
                        }
                        else if(gEventPrize == 0)
                        {
                            PlayErrorSound(playerid);
                            SendClientMessage(playerid, COLOR_ERROR, "* You did not define the award of the event.");
                            ShowPlayerEventDialog(playerid);
                        }
                        else
                        {
                            PlayBuySound(playerid);
                            gEventCountdown = EVENT_COUNT_DOWN;
                            gEventState = EVENT_STATE_STARTING;
                            gIsPlayerCreatingEvent[playerid] = false;
                            gEventTimer = repeat OnEventUpdate();
                            SendClientMessageToAllf(COLOR_SUCCESS, "* %s Created an event, use /gotoevent to participate.", GetPlayerNamef(playerid));
                        }
                    }
                }
            }
        }
        case DIALOG_EVENT_CREATOR_PRIZE:
        {
            new prize;
            if(sscanf(inputtext, "i", prize))
            {
                PlayErrorSound(playerid);
                SendClientMessage(playerid, COLOR_ERROR, "* Invalid value.");
                ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_PRIZE, DIALOG_STYLE_INPUT, "Award of Event", "Enter the winner's award value", "Save", "X");
            }
            else if(prize < 0)
            {
                PlayErrorSound(playerid);
                SendClientMessage(playerid, COLOR_ERROR, "* Valor inválido.");
                ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_PRIZE, DIALOG_STYLE_INPUT, "Award of Event", "Enter the winner's award value", "Save", "X");
            }
            else
            {
                gEventPrize = prize;
                PlaySelectSound(playerid);
                SendClientMessagef(playerid, 0x35CEFBFF, "* You defined the winner's prize as $%d.", prize);
                ShowPlayerEventDialog(playerid);
            }
        }
        case DIALOG_EVENT_CREATOR_SPAWN:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
                ShowPlayerEventDialog(playerid);
            }
            else
            {
                gEventSpawn = listitem;
                new output[256], string[64];
                strcat(output, "Name\tStatus\n");
                for(new i = 0; i < sizeof(gPlayerSpawnsData); i++)
                {
                    format(string, sizeof(string), "%s\t%s\n", gPlayerSpawnsData[i][1], (gEventSpawn == i) , "X" , " ");
                    strcat(output, string);
                }
                ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_SPAWN, DIALOG_STYLE_TABLIST_HEADERS, "Event location", output, "Select", "X");
            }
        }
        case DIALOG_EVENT_CREATOR_WEAPON:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
                ShowPlayerEventDialog(playerid);
            }
            else
            {
                PlaySelectSound(playerid);
                switch (listitem)
                {
                    case 0:
                    {
                        new output[64], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponHandNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponHandNames[i][1], (gEventWeapons[0] == weaponHandNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_0, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 1:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponMeeleNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponMeeleNames[i][1], (gEventWeapons[1] == weaponMeeleNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_1, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 2:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponPistolNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponPistolNames[i][1], (gEventWeapons[2] == weaponPistolNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_2, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 3:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponShotgunNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponShotgunNames[i][1], (gEventWeapons[3] == weaponShotgunNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_3, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 4:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponSubmachineNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponSubmachineNames[i][1], (gEventWeapons[4] == weaponSubmachineNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_4, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 5:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponAssaultNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponAssaultNames[i][1], (gEventWeapons[5] == weaponAssaultNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_5, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 6:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponRifleNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponRifleNames[i][1], (gEventWeapons[6] == weaponRifleNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_6, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 7:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponHeavyNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponHeavyNames[i][1], (gEventWeapons[7] == weaponHeavyNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_7, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 8:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponExplosivesNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponExplosivesNames[i][1], (gEventWeapons[8] == weaponExplosivesNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_8, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 9:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponSprayNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponSprayNames[i][1], (gEventWeapons[9] == weaponSprayNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_9, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                    case 10:
                    {
                        new output[148], string[24];
                        strcat(output, "Name\tStatus\n");
                        for(new i = 0; i < sizeof(weaponOtherNames); i++)
                        {
                            format(string, sizeof(string), "%s\t%s\n", weaponOtherNames[i][1], (gEventWeapons[10] == weaponOtherNames[i][0][0]) , "X" , " ");
                            strcat(output, string);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EVENT_CR_WP_SLOT_10, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
                    }
                }
            }
        }
        case DIALOG_EVENT_CR_WP_SLOT_0:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                gEventWeapons[0] = listitem;
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_1:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                gEventWeapons[1] = (listitem + 2);
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_2:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                gEventWeapons[2] = (listitem + 22);
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_3:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                gEventWeapons[3] = (listitem + 25);
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_4:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                switch (listitem)
                {
                    case 0:
                        gEventWeapons[4] = 28;
                    case 1:
                        gEventWeapons[4] = 29;
                    case 2:
                        gEventWeapons[4] = 32;
                }
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_5:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                gEventWeapons[5] = (listitem + 30);
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_6:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                gEventWeapons[6] = (listitem + 33);
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_7:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                gEventWeapons[7] = (listitem + 35);
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_8:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                switch (listitem)
                {
                    case 0:
                        gEventWeapons[8] = 16;
                    case 1:
                        gEventWeapons[8] = 18;
                    case 2:
                        gEventWeapons[8] = 39;
                }
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_9:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                gEventWeapons[9] = (listitem + 41);
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
        case DIALOG_EVENT_CR_WP_SLOT_10:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                PlayConfirmSound(playerid);
                gEventWeapons[10] = (listitem + 10);
            }

            new output[148], string[24];
            strcat(output, "Slot\tName\n");
            for(new i = 0; i < sizeof(weaponSlotList); i++)
            {
                format(string, sizeof(string), "%i\t%s\n", i, weaponSlotList[i]);
                strcat(output, string);
            }
            ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, "Event Weapon", output, "Select", "X");
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

timer OnEventUpdate[1000]()
{
    if(gEventState == EVENT_STATE_STARTING && gEventCountdown > 0)
    {
        gEventCountdown--;
        foreach(new i: Player)
        {
            if(gIsPlayerInEvent[i])
            {
                if(gEventCountdown > 0)
                {
                    new countstr[38];
                    format(countstr, sizeof(countstr), "~b~Starting Event~n~%02d", gEventCountdown);
                    GameTextForPlayer(i, countstr, 1250, 3);

                    if(gEventCountdown < 6)
                        PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0);
                }
                else
                {
                    GameTextForPlayer(i, "~w~Einitiate Vent!", 1250, 3);
                    PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
                    TogglePlayerControllable(i, true);
                }
            }
        }
    }
    else if(gEventState == EVENT_STATE_STARTING && gEventCountdown == 0)
    {
        gEventState = EVENT_STATE_STARTED;
    }
    else if(gEventState == EVENT_STATE_STARTED && gEventPlayersCount < 2)
    {
        foreach(new i: Player)
        {
            if(gIsPlayerInEvent[i])
            {
                PlayErrorSound(i);
                GameTextForPlayer(i, "~r~event canceled!", 1250, 3);
                SendClientMessage(i, COLOR_ERROR, "* The event was canceled due to lack of players.");

                gIsPlayerInEvent[i] = false;
                SetPlayerGamemode(i, GAMEMODE_FREEROAM);
                SetPlayerPos(i, 1119.9399, -1618.7476, 20.5210);
                SetPlayerFacingAngle(i, 91.8327);
                SetPlayerInterior(i, 0);
                SetPlayerVirtualWorld(i, 0);
                SetPlayerHealth(i, 100.0);
                ResetPlayerWeapons(i);
                TogglePlayerControllable(i, true);

                EndEvent();
            }
        }
    }
}

//------------------------------------------------------------------------------

timer EndEvent[7500]()
{
    foreach(new i: Player)
    {
        if(gIsPlayerInEvent[i])
        {
            TogglePlayerSpectating(i, false);
            gIsPlayerInEvent[i] = false;
            SetPlayerGamemode(i, GAMEMODE_FREEROAM);
            SetPlayerPos(i, 1119.9399, -1618.7476, 20.5210);
            SetPlayerFacingAngle(i, 91.8327);
            SetPlayerInterior(i, 0);
            SetPlayerVirtualWorld(i, 0);
            SetPlayerHealth(i, 100.0);
            ResetPlayerWeapons(i);
            PlayerPlaySound(i, 1063, 0.0, 0.0, 0.0);
        }
    }

    for(new i = 0; i < sizeof(gEventPlayersID); i++)
    {
        gEventPlayersID[i] = INVALID_PLAYER_ID;
    }

    for(new i = 0; i < sizeof(gEventWeapons); i++)
    {
        gEventWeapons[i] = 0;
    }

    gEventState         = EVENT_STATE_NONE;
    gEventSpawn         = -1;
    gEventPrize         = 0;
    gEventCountdown     = 0;
    gEventPlayersCount  = 0;
    stop gEventTimer;
}

//------------------------------------------------------------------------------


hook OnPlayerDeath(playerid, killerid, reason)
{
    if(gIsPlayerInEvent[playerid])
    {
        new remaining_players = 0;
        new winnerid = INVALID_PLAYER_ID;
        for(new i = 0; i < gEventPlayersCount; i++)
        {
            new j = gEventPlayersID[i];
            if(GetPlayerState(j) == PLAYER_STATE_ONFOOT)
            {
                winnerid = j;
                remaining_players++;
            }
        }
        gPlayerState[playerid] = EVENT_PLAYER_STATE_DEAD;
        TogglePlayerSpectating(playerid, true);
        PlayerSpectatePlayer(playerid, killerid);

        if(remaining_players < 2)
        {
            new str[64];
            format(str, sizeof(str), "~w~%s won the event!", GetPlayerNamef(winnerid));
            for(new i = 0; i < gEventPlayersCount; i++)
            {
                GameTextForPlayer(gEventPlayersID[i], str, 7500, 3);
                PlayerPlaySound(i, 1062, 0.0, 0.0, 0.0);
            }
            GivePlayerCash(winnerid, gEventPrize);
            defer EndEvent();
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerUpdate(playerid)
{
    if(gIsPlayerInEvent[playerid] && gPlayerState[playerid] == EVENT_PLAYER_STATE_DEAD)
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
        {
            again:
            gPlayerSpectateTargetID[playerid]++;
            if(gPlayerSpectateTargetID[playerid] == gEventPlayersCount)
                gPlayerSpectateTargetID[playerid] = 0;

            if(gPlayerState[gEventPlayersID[gPlayerSpectateTargetID[playerid]]] == EVENT_PLAYER_STATE_DEAD || gPlayerState[gEventPlayersID[gPlayerSpectateTargetID[playerid]]] == EVENT_PLAYER_STATE_NONE)
                goto again;

            PlayerSpectatePlayer(playerid, gEventPlayersID[gPlayerSpectateTargetID[playerid]]);
        }
        else if(gPlayerSpecTick[playerid] < GetTickCount())
        {
            new Keys, ud, lr;
            GetPlayerKeys(playerid, Keys, ud, lr);
            if(lr == KEY_RIGHT || lr == KEY_LEFT)
            {
                again:
                gPlayerSpectateTargetID[playerid]++;
                if(gPlayerSpectateTargetID[playerid] == gEventPlayersCount)
                    gPlayerSpectateTargetID[playerid] = 0;

                if(gPlayerState[gEventPlayersID[gPlayerSpectateTargetID[playerid]]] == EVENT_PLAYER_STATE_DEAD || gPlayerState[gEventPlayersID[gPlayerSpectateTargetID[playerid]]] == EVENT_PLAYER_STATE_NONE)
                    goto again;

                PlayerSpectatePlayer(playerid, gEventPlayersID[gPlayerSpectateTargetID[playerid]]);
                gPlayerSpecTick[playerid] = GetTickCount() + 50;
            }
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

YCMD:criarevent(playerid, params[], help)
{
	if(GetPlayerAdminLevel(playerid) >= PLAYER_RANK_SUB_OWNER)
	{
        if(gEventState == EVENT_STATE_NONE)
        {
            if(!gIsPlayerCreatingEvent[playerid])
    		{
                if(!IsSomeoneCreatingEvent())
                {
                    PlaySelectSound(playerid);
                    gIsPlayerCreatingEvent[playerid] = true;
        			ShowPlayerEventDialog(playerid);
                }
                else
        		{
        			SendClientMessage(playerid, COLOR_ERROR, "* Someone is already creating an event.");
        		}
    		}
    		else
    		{
    			SendClientMessage(playerid, COLOR_ERROR, "* You are already creating an event.");
    		}
        }
        else
    	{
    		SendClientMessage(playerid, COLOR_ERROR, "* An event is already in progress.");
    	}
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "* You do not have permission.");
	}
	return 1;
}

//------------------------------------------------------------------------------

YCMD:gotoevent(playerid, params[], help)
{
    if(GetPlayerGamemode(playerid) != GAMEMODE_FREEROAM)
        return SendClientMessage(playerid, COLOR_ERROR, "*You need to be in the Freeroam gamemode to go to the event.");
        
    if(!gIsPlayerInEvent[playerid])
    {
        if(gEventState == EVENT_STATE_STARTING)
        {
            new rand = random(4);
            PlaySelectSound(playerid);
            SetPlayerVirtualWorld(playerid, VIRTUAL_WORLD);
            SetPlayerInterior(playerid, gPlayerSpawnsData[gEventSpawn][0][0]);
            SetPlayerPos(playerid, gPlayerSpawns[gEventSpawn][rand][0], gPlayerSpawns[gEventSpawn][rand][1], gPlayerSpawns[gEventSpawn][rand][2]);
            SetPlayerFacingAngle(playerid, gPlayerSpawns[gEventSpawn][rand][3]);
            for(new i = 0; i < sizeof(gEventWeapons); i++)
            {
                GivePlayerWeapon(playerid, gEventWeapons[i], 99999);
            }
            gPlayerState[playerid] = EVENT_PLAYER_STATE_ALIVE;
            gEventPlayersID[gEventPlayersCount] = playerid;
            gEventPlayersCount++;
            gIsPlayerInEvent[playerid] = true;
            SetPlayerHealth(playerid, 100.0);
            SetPlayerArmour(playerid, 100.0);
            TogglePlayerControllable(playerid, false);
        }
        else if(gEventState == EVENT_STATE_STARTED)
        {
            SendClientMessage(playerid, COLOR_ERROR, "* The event has already started, you can no longer participate.");
        }
        else
        {
            SendClientMessage(playerid, COLOR_ERROR, "* There is no active event at the moment.");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_ERROR, "* You are already in the event.");
    }
	return 1;
}

//------------------------------------------------------------------------------

ShowPlayerEventDialog(playerid)
{
	ShowPlayerDialog(playerid, DIALOG_EVENT_CREATOR, DIALOG_STYLE_LIST, "Creating an Event", "Weapon\nLocation\nAward\nStart", "Select", "Cancelar");
}

//------------------------------------------------------------------------------

IsSomeoneCreatingEvent()
{
    foreach(new i: Player)
    {
        if(gIsPlayerCreatingEvent[i])
        {
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------

IsPlayerInEvent(playerid)
{
    return gIsPlayerInEvent[playerid];
}

//------------------------------------------------------------------------------

ResetPlayerEventCreatorData(playerid)
{
    gEventSpawn = -1;
    gEventPrize = 0;
    for(new i = 0; i < sizeof(gEventWeapons); i++)
    {
        gEventWeapons[i] = 0;
    }
    gIsPlayerCreatingEvent[playerid] = false;
}
