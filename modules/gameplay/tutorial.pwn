/*******************************************************************************
* NOME DO ARQUIVO :        modules/gameplay/tutorial.pwn
*
* DESCRIÇÃO :
*       Mostra o tutorial para novos jogadores.
*
* NOTAS :
*       -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

static bool:gIsPlayerInTutorial[MAX_PLAYERS];
static gPlayerTutorialStep[MAX_PLAYERS];

//------------------------------------------------------------------------------

static const gTutorialText[][][] =
{
    {
        "Welcome",
        "Hello, welcome to freeroam! ~ N ~~ n ~ You will now pass \
        by a tutorial that will explain some of the possibilities that you \
        You can do it on our server. ~ n ~~ n ~ We hope you have a lot of fun here \
        How we have fun building it! ~ n ~~ n ~ any doubts use the command\
        /Admit to talk to an administrator."},
    {
        "Lobby",
        "Our server has several different game modes, being them:~n~~n~\
        | Freeroam~n~| DeathMatch~n~| Corrida~n~| Derby~n~~n~To access the modes \
        game use the command /lobby.~n~To get out of a game mode use \
        the command /lobby also!"
    },
    {
        "Racing",
        "Race game mode has several races for you to try.\
        ~n~~n~In this game mode you receive a vehicle and face other players at high speed \
        To find out who the best behind the wheel is.~n~~n~Upon finishing the race you will be sent to the room again to run again.~n~~n~\
        If you want to go another race or game mode use the command /lobby."
    },
    {
        "DeathMatch",
        "In the knockout your goal is to kill the largest number of players to win the match \
        If you commit suicide you will lose 1 slaughter.~n~~n~\
        Below their money the wanted stars symbolize their Killing Spree, The more stars the better your performance is.~n~~n~\
        The player who reaches the defined limit wins the match!"
    },
    {
        "Derby",
        "Derby is where players receive vehicles and must overthrow other players on the platform to win,\
        The last player will be the winner.~n~~n~If you leave the vehicle or it explodes, you will be disqualified too."
    },
    {
        "Freeroam",
        "AThu is where everything is allowed! ~ n ~~ n ~ you can jump from parachutes, maneuvers \
        radicals, dives, drift, explore mountains, cities, give some drinks \
        at the bar, buy clothes and accessories ... anyway!~n~~n~A imaginação é o limite!"
    },
    {
        "Rules",
        "Our server has pre-defined rules so that we can all have a good community of the community.~n~~n~\
        | The use of any type of cheats is not allowed~n~\
        | It is not allowed to do spam/flood~n~\
        | It is not allowed to disrespect other players~n~\
        | It is not allowed to disclose other servers"
    },
    {
        "Final considerations",
        "Thank you for your fair participation on our server, we hope you \
        Have many hours of fun! ~ n ~~ n ~ we find you out there!"
    }

};

static Float:gTutorialCameras[][] =
{
    {0.0, 0.0, 1160.6168, -1647.9303, 48.0613, 1159.7582, -1647.4125, 47.4964},
    {0.0, 0.0, -1547.3136, 147.4965, 233.6728, -1548.0375, 146.8079, 227.9120},
    {7.0, 0.0, -1289.0591, -101.9945, 1073.6915, -1289.7101, -102.7518, 1073.3661},
    {0.0, 0.0, -2438.4839, 1548.2484, 11.7867, -2437.4902, 1548.2019, 11.4309},
    {0.0, 3000.0, 2827.3196, -3137.8960, 152.8835, 2828.2671, -3138.2141, 152.2936},
    {14.0, 0.0, -1501.9048, 1580.8624, 1079.7107, -1500.9312, 1581.0876, 1079.4043},
    {10.0, 0.0, 241.4963, 112.6989, 1003.8539, 240.4985, 112.7370, 1003.9284},
    {0.0, 0.0, -2287.1135, 1755.7581, 74.4123, -2288.1118, 1755.7615, 74.5221}
};

//------------------------------------------------------------------------------

hook OnPlayerDisconnect(playerid, reason)
{
    gIsPlayerInTutorial[playerid] = false;
    gPlayerTutorialStep[playerid] = 0;
    return 1;
}

//------------------------------------------------------------------------------

public OnPlayerClickTutorial(playerid, bool:direction)
{
    /*
    * Direction
    *   0 - left
    *   1 - right
    */
    if(!direction)
    {
        if(gPlayerTutorialStep[playerid] > 0)
        {
            PlaySelectSound(playerid);
            gPlayerTutorialStep[playerid]--;
            SetPlayerTutorialText(playerid, ConvertToGameText(gTutorialText[gPlayerTutorialStep[playerid]][0]), ConvertToGameText(gTutorialText[gPlayerTutorialStep[playerid]][1]));

            SetPlayerInterior(playerid, floatround(gTutorialCameras[gPlayerTutorialStep[playerid]][0]));
            SetPlayerVirtualWorld(playerid, floatround(gTutorialCameras[gPlayerTutorialStep[playerid]][1]));
            SetPlayerCameraPos(playerid, gTutorialCameras[gPlayerTutorialStep[playerid]][2], gTutorialCameras[gPlayerTutorialStep[playerid]][3], gTutorialCameras[gPlayerTutorialStep[playerid]][4]);
            SetPlayerCameraLookAt(playerid, gTutorialCameras[gPlayerTutorialStep[playerid]][5], gTutorialCameras[gPlayerTutorialStep[playerid]][6], gTutorialCameras[gPlayerTutorialStep[playerid]][7]);
        }
        else
        {
            PlayErrorSound(playerid);
        }
    }
    else
    {
        if(gPlayerTutorialStep[playerid] < sizeof(gTutorialText) - 1)
        {
            PlaySelectSound(playerid);
            gPlayerTutorialStep[playerid]++;
            SetPlayerTutorialText(playerid, ConvertToGameText(gTutorialText[gPlayerTutorialStep[playerid]][0]), ConvertToGameText(gTutorialText[gPlayerTutorialStep[playerid]][1]));

            SetPlayerInterior(playerid, floatround(gTutorialCameras[gPlayerTutorialStep[playerid]][0]));
            SetPlayerVirtualWorld(playerid, floatround(gTutorialCameras[gPlayerTutorialStep[playerid]][1]));
            SetPlayerCameraPos(playerid, gTutorialCameras[gPlayerTutorialStep[playerid]][2], gTutorialCameras[gPlayerTutorialStep[playerid]][3], gTutorialCameras[gPlayerTutorialStep[playerid]][4]);
            SetPlayerCameraLookAt(playerid, gTutorialCameras[gPlayerTutorialStep[playerid]][5], gTutorialCameras[gPlayerTutorialStep[playerid]][6], gTutorialCameras[gPlayerTutorialStep[playerid]][7]);
        }
        else
        {
            PlayerPlaySound(playerid, 1188, 0.0, 0.0, 0.0);
            gIsPlayerInTutorial[playerid] = false;
            HidePlayerTutorialText(playerid);
            TogglePlayerSpectating(playerid, false);
            ShowPlayerLobby(playerid);
            SetPlayerTutorial(playerid, true);
        }
    }
}

//------------------------------------------------------------------------------

SendPlayerToTutorial(playerid)
{
    ClearPlayerScreen(playerid);
    PlayerPlaySound(playerid, 1187, 0.0, 0.0, 0.0);
    gIsPlayerInTutorial[playerid] = true;
    gPlayerTutorialStep[playerid] = 0;
    SetPlayerTutorialText(playerid, ConvertToGameText(gTutorialText[0][0]), ConvertToGameText(gTutorialText[0][1]));
    ShowPlayerTutorialText(playerid);

    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);

    TogglePlayerSpectating(playerid, true);
    InterpolateCameraPos(playerid, 1160.6168, -1647.9303, 48.0613, 1160.6168, -1647.9303, 48.1613, 1000, CAMERA_MOVE);
    InterpolateCameraLookAt(playerid, 1159.7582, -1647.4125, 47.4964, 1159.7582, -1647.4125, 47.5964, 1000, CAMERA_MOVE);

    SelectTextDraw(playerid, 0x74c624ff);
}

//------------------------------------------------------------------------------

IsPlayerInTutorial(playerid)
{
    return gIsPlayerInTutorial[playerid];
}
