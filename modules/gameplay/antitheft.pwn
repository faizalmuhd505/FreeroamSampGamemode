/*******************************************************************************
* NOME DO ARQUIVO :        modules/gameplay/antitheft.pwn
*
* DESCRIPTION : 
 * Prevents other players from stealing the vehicle of others.
*
* NOTAS :
*       -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    if(!ispassenger && IsVehicleOccupied(vehicleid))
    {
        SendClientMessage(playerid, COLOR_WARNING, "* You died for trying to steal another player's vehicle.");
        SetPlayerHealth(playerid, 0.0);
    }
    return 1;
}
