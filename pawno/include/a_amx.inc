/*  MTA AMX compatibility layer
 *
 *  Extension functions
 */

#if defined _amx_included
	#endinput
#endif
#define _amx_included

// MTA
native lua(const fn[], {Float,_}:...);
native amxRegisterPawnPrototypes(const prototype[][]);
native amxVersion(&Float:ver);
native amxVersionString(buffer[], maxsize);
native md5hash(str[], const buf[], bufsize);

// Events
forward OnBotConnect(botid, name[]);
forward OnBotEnterVehicle(botid, vehicleid, seatid);
forward OnBotExitVehicle(botid, vehicleid);
forward OnBotDeath(botid, killerid, weaponid, bodypart);
forward OnVehicleDamage(vehicleid, Float:loss);
forward OnPlayerShootingPlayer(playerid, attackerid, bodypart, Float:loss);
forward OnPlayerWeaponSwitch(playerid, previousWeaponID, currentWeaponID);
forward OnPlayerShoot(playerid, weapon, ammo, ammoInClip, Float:hitX, Float:hitY, Float:hitZ);
forward OnMarkerCreate(markerid);
forward OnMarkerHit(markerid, elemtype[], elemid, matchingDimension);
forward OnMarkerLeave(markerid, elemtype[], elemid, matchingDimension);

// World
native SetSkyGradient(topRed = 0, topGreen = 0, topBlue = 0, bottomRed = 0, bottomGreen = 0, bottomBlue = 0);
native ResetSkyGradient();
native GetCloudsEnabled();
native SetCloudsEnabled(stateid);
native IsGarageOpen(garageid);
native SetGarageOpen(garageid, stateid);
native IsGlitchEnabled(name[]);
native SetGlitchEnabled(name[], stateid);
native SetFPSLimit(fps);
native GetPlayerCount();
native GetRandomPlayer();
native GetDistanceBetweenPoints2D(Float:X1, Float:Y1, Float:X2, Float:Y2);
native GetDistanceBetweenPoints3D(Float:X1, Float:Y1, Float:Z1, Float:X2, Float:Y2, Float:Z2);

// Water
native GetWaveHeight();
native SetWaveHeight(Float:height);
native SetWaterLevel(Float:level);

// Pickups
native GetPickupType(pickupid);
native SetPickupType(pickupid, typeid, amount, ammo = 500);
native GetPickupWeapon(pickupid);
native GetPickupAmount(pickupid);
native GetPickupAmmo(pickupid);

// Native Markers
native CreateMarker(Float:X, Float:Y, Float:Z, type[], Float:size, red, green, blue, alpha);
native DestroyMarker(markerid);
native GetMarkerColor(markerid, colorid); // Color IDs: 0 = Red, 1 = Green, 2 = Blue, 3 = Alpha
native GetMarkerIcon(markerid); // 0 = No icon, 1 = Arrow, 2 = Race finish
native GetMarkerSize(markerid, &Float:size);
native GetMarkerTarget(markerid, &Float:X, &Float:Y, &Float:Z);
native GetMarkerType(markerid); // 0 = Checkpoint, 1 = Ring, 2 = Cylinder, 3 = Arrow, 4 = Corona
native SetMarkerColor(markerid, red, green, blue, alpha);
native SetMarkerIcon(markerid, iconid); // 0 = No icon, 1 = Arrow, 2 = Race finish
native SetMarkerSize(markerid, Float:size);
native SetMarkerTarget(markerid, Float:X, Float:Y, Float:Z);
native SetMarkerType(markerid, typeid); // 0 = Checkpoint, 1 = Ring, 2 = Cylinder, 3 = Arrow, 4 = Corona
native IsPlayerInMarker(markerid, playerid);
native IsBotInMarker(markerid, botid);
native IsVehicleInMarker(markerid, vehicleid);

// Rules
native GetRuleValue(rule[], const buf[], bufsize);
native SetRuleValue(rule[], value[]);
native RemoveRuleValue(rule[]);

// Objects
native GetObjectAlpha(objectid);
native SetObjectAlpha(objectid, alpha);

// Players
native AddPlayerClothes(playerid, type, index);
native GetPlayerClothes(playerid, type);
native RemovePlayerClothes(playerid, type);
native ShowPlayerMarker(playerid, show);
native IsPlayerInWater(playerid);
native IsPlayerOnFire(playerid);
native IsPlayerDucked(playerid);
native IsPlayerOnGround(playerid);
//native GetPlayerFightingStyle(playerid);
//native SetPlayerFightingStyle(playerid, styleid);
native SetPlayerOnFire(playerid, fire);
native GetPlayerStat(playerid, statid);
native SetPlayerStat(playerid, statid, Float:value);
native GetPlayerCanBeKnockedOffBike(playerid);
native SetPlayerCanBeKnockedOffBike(playerid, stateid);
native GetPlayerDoingDriveBy(playerid);
native SetPlayerDoingDriveBy(playerid, stateid);
native SetPlayerWeaponSlot(playerid, slotid);
native SetPlayerHeadless(playerid, stateid);
native GetPlayerBlurLevel(playerid);
native SetPlayerBlurLevel(playerid, level);
native GetPlayerAlpha(playerid);
native SetPlayerAlpha(playerid, alpha);
native FadePlayerCamera(playerid, fadeIn, Float:timeToFade = 1.0, red = 0, green = 0, blue = 0);
//native GetPlayerVehicleSeat(playerid);
//native GetPlayerVelocity(playerid, &Float:X, &Float:Y, &Float:Z);
//native SetPlayerVelocity(playerid, Float:X, Float:Y, Float:Z);
native SetPlayerControlState(playerid, control[], stateid);

// Vehicles
//native GetVehicleMaxPassengers(vehicleid);
//native GetVehicleVelocity(vehicleid, &Float:vx, &Float:vy, &Float:vz);
//native SetVehicleVelocity(vehicleid, Float:vx, Float:vy, Float:vz);
native SetVehicleModel(vehicleid, model);
native GetVehicleEngineState(vehicleid);
native SetVehicleEngineState(vehicleid, stateid);
native GetVehicleDoorState(vehicleid, door);
native SetVehicleDoorState(vehicleid, door, stateid);
native GetVehicleLightState(vehicleid, lightid);
native SetVehicleLightState(vehicleid, lightid, stateid);
native GetVehicleOverrideLights(vehicleid);
native SetVehicleOverrideLights(vehicleid, stateid);
native GetVehicleWheelState(vehicleid, wheelid);
native SetVehicleWheelState(vehicleid, frontLeft = -1, rearLeft = -1, frontRight = -1, rearRight = -1);
native GetVehiclePanelState(vehicleid, panelid);
native SetVehiclePanelState(vehicleid, panelid, stateid);
native GetVehicleAlpha(vehicleid);
native SetVehicleAlpha(vehicleid, alpha);
native GetVehiclePaintjob(vehicleid);
//native GetVehicleComponentInSlot(vehicleid, slot);
native GetVehicleSirensOn(vehicleid);
native SetVehicleSirensOn(vehicleid, stateid);
native IsTrainDerailable(vehicleid);
native IsTrainDerailed(vehicleid);
native SetTrainDerailable(vehicleid, stateid);
native SetTrainDerailed(vehicleid, stateid);
native GetTrainDirection(vehicleid);
native SetTrainDirection(vehicleid, direction);
native GetTrainSpeed(vehicleid, &Float:speed);
native SetTrainSpeed(vehicleid, &Float:speed);

// Bots
native CreateBot(modelid, Float:x, Float:y, Float:z, name[] = "Bot");
native SetBotHealth(botid, Float:health);
native GetBotHealth(botid, &Float:health);
native SetBotArmour(botid, Float:armour);
native GetBotArmour(botid, &Float:armour);
native SetBotPos(botid, Float:X, Float:Y, Float:Z);
native GetBotPos(botid, &Float:X, &Float:Y, &Float:Z);
native SetBotRot(botid, Float:RotX, Float:RotY, Float:RotZ);
native GetBotRot(botid, &Float:RotX, &Float:RotY, &Float:RotZ);
native IsBotInWater(botid);
native IsBotOnFire(botid);
native IsBotDucked(botid);
native IsBotOnGround(botid);
native GetBotFightingStyle(botid);
native SetBotFightingStyle(botid, styleid);
native SetBotOnFire(botid, fire);
native GetBotStat(botid, statid);
native SetBotStat(botid, statid, Float:value);
native GetBotState(botid);
native PutBotInVehicle(botid, vehicleid, seatid);
native RemoveBotFromVehicle(botid);
native SetBotControlState(botid, control[], stateid);
native SetBotAimTarget(botid, &Float:X, &Float:Y, &Float:Z);
native GetBotDoingDriveBy(botid);
native SetBotDoingDriveBy(botid, stateid);
native GetBotCanBeKnockedOffBike(botid);
native SetBotCanBeKnockedOffBike(botid, stateid);
native SetBotWeaponSlot(botid, slotid);
native SetBotHeadless(botid, stateid);
native BotKill(botid);
native GetBotAlpha(botid);
native SetBotAlpha(botid, alpha);
native GetBotName(botid, const buf[], bufsize);
native GetBotVehicleSeat(botid);
native GetBotVelocity(botid, &Float:X, &Float:Y, &Float:Z);
native SetBotVelocity(botid, Float:X, Float:Y, Float:Z);
