/*******************************************************************************
* NOME DO ARQUIVO :        modules/core/ads.pwn
*
*DESCRIPTION : 
 * Sends pre-defined ads every x seconds to everyone on the server. 
 * 
 * GRADES : 
 * -
*/

#include <YSI\y_hooks>

static messages[][] = {
    "To see the VIP advantages type '{f00c0c}/vipadvantage{FFFFFF}'.",
    "Are you in doubt? type it '{f00c0c}/cmds{FFFFFF}' or ask an administrator for help {f00c0c}/admins{FFFFFF}.",
    "Did you see a cheater? Contact an administrator using '{f00c0c}/report{FFFFFF}'."
};

task SendGlobalAdvertise[ADVERTISE_INTERVAL]()
{
    foreach(new i: Player)
    {
        if(!IsPlayerInTutorial(i) && GetPlayerGamemode(i) != GAMEMODE_LOBBY)
        {
            SendClientMessage(i, COLOR_WHITE, messages[random(sizeof(messages))]);
        }
    }
}

//------------------------------------------------------------------------------

static hostnames[][] = {
    "« FREEROAM (0.3.7) »"
};

task UpdateHostName[UPDATE_HOSTNAME_INTERVAL]()
{
    new cmd[128];
    format(cmd, sizeof(cmd), "hostname            %s", hostnames[random(sizeof(hostnames))]);
    SendRconCommand(cmd);
}

hook OnGameModeInit()
{
    UpdateHostName();
    return 1;
}
