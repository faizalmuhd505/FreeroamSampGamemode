/*******************************************************************************
* NOME DO ARQUIVO :        modules/data/player.pwn
*
* DESCRIÇÃO :
*       Manipula a conta dos jogadores, salvar, carregar, cadastrar, acessar.
*
* NOTES :
*       Este arquivo deve apenas conter dados de jogadores.
*
*
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

forward OnNameCheck(playerid, name[]);
forward OnEmailCheck(playerid, email[]);
forward OnAccountLoad(playerid);
forward OnAccountCheck(playerid);
forward OnAccountRegister(playerid);
forward OnBannedAccountCheck(playerid);

//------------------------------------------------------------------------------

enum e_player_adata
{
    e_player_database_id,
    e_player_password[MAX_PLAYER_PASSWORD],
    e_player_regdate[32],
    e_player_email[64],
    e_player_ip[16],
    e_player_money,
    e_player_bank,
    e_player_score,
    e_player_gender,
    e_player_age,
    e_player_skin,
    e_player_tutorial,
    bool:e_player_muted,
    e_player_vip,
    e_player_warning,
    e_player_played_time,
    e_player_admin,
    e_player_lastlogin,
    e_player_kills,
    e_player_deaths,
    e_player_race_wins,
    e_player_dm_wins,
    e_player_derby_wins
}
static gPlayerAccountData[MAX_PLAYERS][e_player_adata];

//------------------------------------------------------------------------------

enum e_player_bdata
{
    bool:e_player_banned,
    e_player_badmin_name[MAX_PLAYER_NAME],
    e_player_created_at,
    e_player_expire,
    e_player_reason[255]
}
static gPlayerBannedData[MAX_PLAYERS][e_player_bdata];

//------------------------------------------------------------------------------

enum PlayerState (<<= 1)
{
    E_PLAYER_STATE_NONE,
    E_PLAYER_STATE_LOGGED = 1
}
static PlayerState:gPlayerStates[MAX_PLAYERS];

//------------------------------------------------------------------------------

SetPlayerLogged(playerid, bool:set)
{
    if(set)
        gPlayerStates[playerid] |= E_PLAYER_STATE_LOGGED;
    else
        gPlayerStates[playerid] &= ~E_PLAYER_STATE_LOGGED;
}

//------------------------------------------------------------------------------

IsPlayerLogged(playerid)
{
    if(!IsPlayerConnected(playerid))
        return 0;

    if(gPlayerStates[playerid] & E_PLAYER_STATE_LOGGED)
        return 1;

    return 0;
}

//------------------------------------------------------------------------------

SavePlayerAccount(playerid)
{
    // Caso o jogador não estiver logado, terminar função
    if(!IsPlayerLogged(playerid))
        return 0;

    // Salvar conta
    new query[400];
	mysql_format(gMySQL, query, sizeof(query),
    "UPDATE users SET money=%d, bank=%d, score=%d, skin=%d, admin=%d, vip=%d, \
    kills=%d, deaths=%d, race_wins=%d, dm_wins=%d, derby_wins=%d, \
    tutorial=%d, drift_points=%d, played_time=%d, ip='%s', last_login=%d WHERE id=%d",
    GetPlayerCash(playerid), GetPlayerBankCash(playerid), gPlayerAccountData[playerid][e_player_score],
    GetPlayerSkin(playerid), gPlayerAccountData[playerid][e_player_admin],
    gPlayerAccountData[playerid][e_player_vip],
    gPlayerAccountData[playerid][e_player_kills], gPlayerAccountData[playerid][e_player_deaths],
    gPlayerAccountData[playerid][e_player_race_wins], gPlayerAccountData[playerid][e_player_dm_wins],
    gPlayerAccountData[playerid][e_player_derby_wins],
    gPlayerAccountData[playerid][e_player_tutorial],
    GetPlayerDriftPoints(playerid), gPlayerAccountData[playerid][e_player_played_time],
    gPlayerAccountData[playerid][e_player_ip], gettime(),
    gPlayerAccountData[playerid][e_player_database_id]);
    mysql_pquery(gMySQL, query);

    mysql_format(gMySQL, query, sizeof(query), "UPDATE user_preferences SET color=%d, fight_style=%d, auto_repair=%d, name_tags=%d, goto=%d, drift=%d, drift_counter=%d WHERE user_id=%d",
    GetPlayerColor(playerid), GetPlayerFightingStyle(playerid), GetPlayerAutoRepairState(playerid), GetPlayerNameTagsState(playerid), GetPlayerGotoState(playerid), GetPlayerDriftState(playerid), GetPlayerDriftCounter(playerid), gPlayerAccountData[playerid][e_player_database_id]);
	mysql_pquery(gMySQL, query);
    return 1;
}

//------------------------------------------------------------------------------

ResetPlayerData(playerid)
{
    gPlayerStates[playerid] = E_PLAYER_STATE_NONE;
    gPlayerAccountData[playerid][e_player_database_id]  = 0;
    gPlayerAccountData[playerid][e_player_money]        = 0;
    gPlayerAccountData[playerid][e_player_bank]         = 0;
    gPlayerAccountData[playerid][e_player_score]        = 0;
    gPlayerAccountData[playerid][e_player_age]          = 0;
    gPlayerAccountData[playerid][e_player_skin]         = 0;
    gPlayerAccountData[playerid][e_player_tutorial]     = 0;
    gPlayerAccountData[playerid][e_player_kills]        = 0;
    gPlayerAccountData[playerid][e_player_deaths]       = 0;
    gPlayerAccountData[playerid][e_player_race_wins]    = 0;
    gPlayerAccountData[playerid][e_player_dm_wins]      = 0;
    gPlayerAccountData[playerid][e_player_derby_wins]   = 0;
    gPlayerAccountData[playerid][e_player_vip]          = 0;
    gPlayerAccountData[playerid][e_player_muted]        = false;
    gPlayerAccountData[playerid][e_player_warning]      = 0;
    gPlayerAccountData[playerid][e_player_played_time]  = 0;
    gPlayerAccountData[playerid][e_player_admin]        = 0;
    gPlayerAccountData[playerid][e_player_regdate][0]   = '\0';
    gPlayerAccountData[playerid][e_player_lastlogin]    = gettime();
}

//------------------------------------------------------------------------------

LoadPlayerAccount(playerid)
{
    new query[106 + MAX_PLAYER_NAME], playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, sizeof(playerName));
    mysql_format(gMySQL, query, sizeof(query),"SELECT * FROM users LEFT JOIN user_preferences ON users.id=user_preferences.user_id WHERE username = '%e'", playerName);
    mysql_tquery(gMySQL, query, "OnAccountLoad", "i", playerid);
}

//------------------------------------------------------------------------------

hook OnPlayerConnect(playerid)
{
    ClearPlayerScreen(playerid);
    SetPlayerColor(playerid, 0xACACACFF);
    SendClientMessage(playerid, 0xA9C4E4FF, "Connected to the database, please wait ...");

    // Verifica se o jogador está banido e prossegue com a checagem da conta
    new query[128], playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, sizeof(playerName));
    mysql_format(gMySQL, query, 128, "SELECT * FROM `bans` WHERE `username` = '%e' LIMIT 1", playerName);
    mysql_tquery(gMySQL, query, "OnBannedAccountCheck", "i", playerid);
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerRequestClass(playerid, classid)
{
    if(!IsPlayerLogged(playerid))
    {
        // Camera sobrevoando cidade enquanto faz login
        TogglePlayerSpectating(playerid, true);
        InterpolateCameraPos(playerid, 1080.0939, -1013.4362, 208.6180, 1180.0939, -1113.4362, 203.6180, 30000, CAMERA_MOVE);
        InterpolateCameraLookAt(playerid, 1333.0903, -1205.6227, 203.4406, 1333.0903, -1205.6227, 197.4406, 30000, CAMERA_MOVE);
    }
    else
    {
        SetSpawnInfo(playerid, 255, gPlayerAccountData[playerid][e_player_skin], 1119.9399, -1618.7476, 20.5210, 91.8327, 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerRequestSpawn(playerid)
{
    if(!IsPlayerLogged(playerid))
    {
        PlayErrorSound(playerid);
        SendClientMessage(playerid, COLOR_ERROR, "* You are not logged in.");
        return -1;
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerDisconnect(playerid, reason)
{
    SavePlayerAccount(playerid);
    SetPlayerLogged(playerid, false);
    ResetPlayerData(playerid);
    return 1;
}

//------------------------------------------------------------------------------

public OnAccountCheck(playerid)
{
	new rows, fields, playerName[MAX_PLAYER_NAME];
	cache_get_data(rows, fields, gMySQL);
    GetPlayerName(playerid, playerName, sizeof(playerName));
	if(rows)
	{
        if(gPlayerBannedData[playerid][e_player_banned] && (gPlayerBannedData[playerid][e_player_expire] < 0 || gPlayerBannedData[playerid][e_player_expire] > gettime()))
        {
            new info[564];
            format(info, sizeof(info), "{ffffff}%s, This account is banned!\n\nBanity Date: {fe9ddd}%s.\n{ffffff}Banishment: {fe9ddd}%s.\n{ffffff}Banity Expiration: {fe9ddd}%s\n{ffffff}Reason for banishment:\n{fe9ddd}%s",
            playerName, convertTimestamp(gPlayerBannedData[playerid][e_player_created_at]), gPlayerBannedData[playerid][e_player_badmin_name],
            (gPlayerBannedData[playerid][e_player_expire] > 0) ? convertTimestamp(gPlayerBannedData[playerid][e_player_expire]) : "Never", gPlayerBannedData[playerid][e_player_reason]);
            ShowPlayerDialog(playerid, DIALOG_BANNED, DIALOG_STYLE_MSGBOX, "Banned", info, "Okey", "");
            PlayErrorSound(playerid);
        }
        else
        {
            cache_get_field_content(0, "password", gPlayerAccountData[playerid][e_player_password], gMySQL, MAX_PLAYER_PASSWORD);
            cache_get_field_content(0, "email", gPlayerAccountData[playerid][e_player_email], gMySQL, 128);
            gPlayerAccountData[playerid][e_player_database_id]  = cache_get_field_content_int(0, "id", gMySQL);
            gPlayerAccountData[playerid][e_player_skin]         = cache_get_field_content_int(0, "skin", gMySQL);

            ShowPlayerAuthentication(playerid, true);

            // If the player's banishment expires, delete from the table table
            if(gPlayerBannedData[playerid][e_player_banned])
            {
                new query[57 + MAX_PLAYER_NAME + 1];
                mysql_format(gMySQL, query, sizeof(query),"DELETE FROM `bans` WHERE `username` = '%s'", playerName);
                mysql_tquery(gMySQL, query);
            }
        }
	}
    else
    {
        ShowPlayerAuthentication(playerid, false);
    }
    return 1;
}

//------------------------------------------------------------------------------

public OnNameCheck(playerid, name[])
{
	new rows, fields, playerName[MAX_PLAYER_NAME];
	cache_get_data(rows, fields, gMySQL);
    GetPlayerName(playerid, playerName, sizeof(playerName));
	if(rows)
	{
        SendClientMessage(playerid, COLOR_ERROR, "* This name is already in use.");
        PlayErrorSound(playerid);
	}
    else
    {
        new tempName[MAX_PLAYER_NAME], oldName[MAX_PLAYER_NAME];
        valstr(tempName, gettime());
        GetPlayerName(playerid, oldName, sizeof(oldName));
        SetPlayerName(playerid, tempName);
        switch(SetPlayerName(playerid, name))
        {
            case -1:
            {
                PlayErrorSound(playerid);
                SendClientMessage(playerid, COLOR_ERROR, "* Very long name or has invalid charachters.");
                SetPlayerName(playerid, oldName);
                return 1;
            }
            case 1:
            {
                SendClientMessage(playerid, COLOR_SUCCESS, "* Successfully changed.");
                PlayConfirmSound(playerid);
            }
        }

        new query[128];
    	mysql_format(gMySQL, query, sizeof(query), "UPDATE `users` SET `username`='%s' WHERE `id`=%d", name, gPlayerAccountData[playerid][e_player_database_id]);
    	mysql_pquery(gMySQL, query);
    }
    return 1;
}

//------------------------------------------------------------------------------

public OnEmailCheck(playerid, email[])
{
	new rows, fields, playerName[MAX_PLAYER_NAME];
	cache_get_data(rows, fields, gMySQL);
    GetPlayerName(playerid, playerName, sizeof(playerName));
	if(rows)
	{
        SendClientMessage(playerid, COLOR_ERROR, "* This email is already in use.");
        PlayErrorSound(playerid);
	}
    else
    {
        SetPlayerEmail(playerid, email);
        PlayConfirmSound(playerid);
    }
    return 1;
}

//------------------------------------------------------------------------------

public OnBannedAccountCheck(playerid)
{
	new rows, fields, playerName[MAX_PLAYER_NAME];
	cache_get_data(rows, fields, gMySQL);
    GetPlayerName(playerid, playerName, sizeof(playerName));
	if(rows)
	{
        gPlayerBannedData[playerid][e_player_banned]                = true;
        gPlayerBannedData[playerid][e_player_created_at]            = cache_get_field_content_int(0, "created_at", gMySQL);
        gPlayerBannedData[playerid][e_player_expire]                = cache_get_field_content_int(0, "expire", gMySQL);
        cache_get_field_content(0, "admin", gPlayerBannedData[playerid][e_player_badmin_name], gMySQL, MAX_PLAYER_NAME);
        cache_get_field_content(0, "reason", gPlayerBannedData[playerid][e_player_reason], gMySQL, 255);
	}
    else
    {
        gPlayerBannedData[playerid][e_player_banned]   = false;
    }

    // Após checagem se a conta está banida, prosseguir com o carregamento normalmente.
    new query[57 + MAX_PLAYER_NAME + 1];
    mysql_format(gMySQL, query, sizeof(query),"SELECT * FROM `users` WHERE `username` = '%e' LIMIT 1", playerName);
    mysql_tquery(gMySQL, query, "OnAccountCheck", "i", playerid);
    return 1;
}

//------------------------------------------------------------------------------

public OnAccountRegister(playerid)
{
    gPlayerAccountData[playerid][e_player_database_id] = cache_insert_id();

    new query[64];
    mysql_format(gMySQL, query, sizeof(query), "INSERT INTO user_preferences (user_id) VALUES (%d)", gPlayerAccountData[playerid][e_player_database_id]);
    mysql_tquery(gMySQL, query);

    SetSpawnInfo(playerid, 255, 0, 1119.9399, -1618.7476, 20.5210, 91.8327, 0, 0, 0, 0, 0, 0);
    TogglePlayerSpectating(playerid, false);
    SendPlayerToTutorial(playerid);

    new playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, sizeof(playerName));
	printf("[mysql] new player account registered on database. ID: %d, Username: %s", gPlayerAccountData[playerid][e_player_database_id], playerName);
	return 1;
}

//------------------------------------------------------------------------------

public OnAccountLoad(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields, gMySQL);
	if(rows)
	{
        GetPlayerIp(playerid, gPlayerAccountData[playerid][e_player_ip], 16);
        gPlayerAccountData[playerid][e_player_database_id]  = cache_get_field_content_int(0, "id", gMySQL);
        gPlayerAccountData[playerid][e_player_money]        = cache_get_field_content_int(0, "money", gMySQL);
        gPlayerAccountData[playerid][e_player_bank]         = cache_get_field_content_int(0, "bank", gMySQL);
        gPlayerAccountData[playerid][e_player_skin]         = cache_get_field_content_int(0, "skin", gMySQL);
        gPlayerAccountData[playerid][e_player_admin]        = cache_get_field_content_int(0, "admin", gMySQL);
        gPlayerAccountData[playerid][e_player_played_time]  = cache_get_field_content_int(0, "played_time", gMySQL);
        gPlayerAccountData[playerid][e_player_vip]          = cache_get_field_content_int(0, "vip", gMySQL);
        gPlayerAccountData[playerid][e_player_tutorial]     = cache_get_field_content_int(0, "tutorial", gMySQL);
        gPlayerAccountData[playerid][e_player_lastlogin]    = cache_get_field_content_int(0, "last_login", gMySQL);

        gPlayerAccountData[playerid][e_player_kills]        = cache_get_field_content_int(0, "kills", gMySQL);
        gPlayerAccountData[playerid][e_player_deaths]       = cache_get_field_content_int(0, "deaths", gMySQL);
        gPlayerAccountData[playerid][e_player_race_wins]    = cache_get_field_content_int(0, "race_wins", gMySQL);
        gPlayerAccountData[playerid][e_player_dm_wins]      = cache_get_field_content_int(0, "dm_wins", gMySQL);
        gPlayerAccountData[playerid][e_player_derby_wins]   = cache_get_field_content_int(0, "derby_wins", gMySQL);

        cache_get_field_content(0, "created_at", gPlayerAccountData[playerid][e_player_regdate], gMySQL, 32);
        SetPlayerPoint(playerid, cache_get_field_content_int(0, "score", gMySQL));

        SetSpawnInfo(playerid, 255, gPlayerAccountData[playerid][e_player_skin], 1119.9399, -1618.7476, 20.5210, 91.8327, 0, 0, 0, 0, 0, 0);
        TogglePlayerSpectating(playerid, false);

        if(gPlayerAccountData[playerid][e_player_tutorial])
            ShowPlayerLobby(playerid);
        else
            SendPlayerToTutorial(playerid);

        // Other data
        SetPlayerDriftPoints(playerid, cache_get_field_content_int(0, "drift_points", gMySQL));

        // Load player preferences
        SetPlayerColor(playerid,            cache_get_field_content_int(0, "color", gMySQL));
        TogglePlayerAutoRepair(playerid,    cache_get_field_content_int(0, "auto_repair", gMySQL));
        TogglePlayerGoto(playerid,          cache_get_field_content_int(0, "goto", gMySQL));
        TogglePlayerNameTags(playerid,      cache_get_field_content_int(0, "name_tags", gMySQL));
        TogglePlayerDrift(playerid,         cache_get_field_content_int(0, "drift", gMySQL));
        TogglePlayerDriftCounter(playerid,  cache_get_field_content_int(0, "drift_counter", gMySQL));
        SetPlayerFightingStyle(playerid,    cache_get_field_content_int(0, "fight_style", gMySQL));
        SetPlayerLogged(playerid, true);
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_LOGIN:
        {
            if(!response)
                return Kick(playerid);

            if(!strcmp(gPlayerAccountData[playerid][e_player_password], inputtext) && !isnull(gPlayerAccountData[playerid][e_player_password]) && !isnull(inputtext))
            {
                PlayConfirmSound(playerid);
                LoadPlayerAccount(playerid);
                SendClientMessage(playerid, 0x88AA62FF, "Connected.");
            }
            else
            {
                ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Access-> Incorrect password", "Incorrect password!\nTry again:", "Access", "X"),
                PlayErrorSound(playerid);
            }
            return -2;
        }
        case DIALOG_REGISTER:
        {
            if(!response)
                Kick(playerid);
            else if(strlen(inputtext) < 6)
                ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Register-> very short password", "Try again:", "Register", "X"),
                PlayErrorSound(playerid);
            else if(strlen(inputtext) > MAX_PLAYER_PASSWORD-1)
                ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Register-> very long password", "Try again:", "Register", "X"),
                PlayErrorSound(playerid);
            else
            {
                PlayConfirmSound(playerid);
                SetPlayerLogged(playerid, true);
                SendClientMessage(playerid, 0x88AA62FF, "Registered.");

                new playerIP[16], playerName[MAX_PLAYER_NAME];
                GetPlayerName(playerid, playerName, sizeof(playerName));
                GetPlayerIp(playerid, playerIP, sizeof(playerIP));

                new query[128];
                mysql_format(gMySQL, query, sizeof(query), "INSERT INTO `users` (`username`, `password`, `ip`, `created_at`) VALUES ('%e', '%e', '%s', now())", playerName, inputtext, playerIP);
            	mysql_tquery(gMySQL, query, "OnAccountRegister", "i", playerid);
            }
            return -2;
        }
        case DIALOG_BANNED:
        {
            Kick(playerid);
            return -2;
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

GetPlayerDatabaseID(playerid)
{
    return gPlayerAccountData[playerid][e_player_database_id];
}

GetPlayerBankCash(playerid)
{
    return gPlayerAccountData[playerid][e_player_bank];
}

SetPlayerBankCash(playerid, value)
{
    gPlayerAccountData[playerid][e_player_bank] = value;
}

GetPlayerCash(playerid)
{
    return gPlayerAccountData[playerid][e_player_money];
}

SetPlayerCash(playerid, value)
{
    ResetPlayerMoney(playerid);
    gPlayerAccountData[playerid][e_player_money] = value;
    GivePlayerMoney(playerid, value);
}

GivePlayerCash(playerid, value)
{
    ResetPlayerMoney(playerid);
    gPlayerAccountData[playerid][e_player_money] += value;
    GivePlayerMoney(playerid, gPlayerAccountData[playerid][e_player_money]);
}

SetPlayerPoint(playerid, score)
{
    SetPlayerScore(playerid, score);
    gPlayerAccountData[playerid][e_player_score] = score;
}

GetPlayerPoint(playerid)
{
    return gPlayerAccountData[playerid][e_player_score];
}

GetPlayerPlayedTime(playerid)
{
    return gPlayerAccountData[playerid][e_player_played_time];
}

SetPlayerPlayedTime(playerid, value)
{
    gPlayerAccountData[playerid][e_player_played_time] = value;
}

GetPlayerAdminLevel(playerid)
{
    return gPlayerAccountData[playerid][e_player_admin];
}

SetPlayerAdminLevel(playerid, value)
{
    gPlayerAccountData[playerid][e_player_admin] = value;
}

IsPlayerMuted(playerid)
{
    return gPlayerAccountData[playerid][e_player_muted];
}

TogglePlayerMute(playerid, bool:value)
{
    gPlayerAccountData[playerid][e_player_muted] = value;
}

IsPlayerVIP(playerid)
{
    return (gPlayerAccountData[playerid][e_player_vip] > gettime()) ? true : false;
}

SetPlayerVIP(playerid, value)
{
    gPlayerAccountData[playerid][e_player_vip] = value;
}

GetPlayerVIP(playerid)
{
    return gPlayerAccountData[playerid][e_player_vip];
}

GetPlayerWarning(playerid)
{
    return gPlayerAccountData[playerid][e_player_warning];
}

SetPlayerWarning(playerid, value)
{
    gPlayerAccountData[playerid][e_player_warning] = value;
}

GetPlayerGender(playerid)
{
    return gPlayerAccountData[playerid][e_player_gender];
}

SetPlayerGender(playerid, value)
{
    gPlayerAccountData[playerid][e_player_gender] = value;
}

GetPlayerLastLogin(playerid)
{
    return gPlayerAccountData[playerid][e_player_lastlogin];
}

SetPlayerEmail(playerid, email[])
{
    format(gPlayerAccountData[playerid][e_player_email], 64, email);
}

GetPlayerEmail(playerid)
{
    new email[MAX_PLAYER_PASSWORD];
    strcat(email, gPlayerAccountData[playerid][e_player_email]);
    return email;
}

SetPlayerAge(playerid, age)
{
    gPlayerAccountData[playerid][e_player_age] = age;
}

GetPlayerSaveSkin(playerid)
{
    return gPlayerAccountData[playerid][e_player_skin];
}

GetPlayerAge(playerid)
{
    return gPlayerAccountData[playerid][e_player_age];
}

GetPlayerPassword(playerid)
{
    new password[MAX_PLAYER_PASSWORD];
    strcat(password, gPlayerAccountData[playerid][e_player_password]);
    return password;
}

SetPlayerTutorial(playerid, value)
{
    gPlayerAccountData[playerid][e_player_tutorial] = value;
}

GetPlayerPlayedTimeStamp(playerid)
{
	new playedTime[42];
	if(GetPlayerPlayedTime(playerid) < 86400)
		format(playedTime, sizeof(playedTime), "%02dh %02dm %02ds", (GetPlayerPlayedTime(playerid) / 3600), (GetPlayerPlayedTime(playerid) - (3600 * (GetPlayerPlayedTime(playerid) / 3600))) / 60, (GetPlayerPlayedTime(playerid) % 60));
	else
		 format(playedTime, sizeof(playedTime), "%02dd %02dh %02dm %02ds", GetPlayerPlayedTime(playerid) / 86400, (GetPlayerPlayedTime(playerid) - (86400 * (GetPlayerPlayedTime(playerid) / 86400))) / 3600, (GetPlayerPlayedTime(playerid) - (3600 * (GetPlayerPlayedTime(playerid) / 3600))) / 60, (GetPlayerPlayedTime(playerid) % 60));
	return playedTime;
}

SetPlayerPassword(playerid, password[], update=true)
{
    format(gPlayerAccountData[playerid][e_player_password], MAX_PLAYER_PASSWORD, password);

    if(update)
    {
        new query[128];
    	mysql_format(gMySQL, query, sizeof(query), "UPDATE `users` SET `password`='%s' WHERE `id`=%d", gPlayerAccountData[playerid][e_player_password], gPlayerAccountData[playerid][e_player_database_id]);
    	mysql_pquery(gMySQL, query);
    }
}

ChangePlayerName(playerid, name[])
{
    new query[57 + MAX_PLAYER_NAME + 1];
    mysql_format(gMySQL, query, sizeof(query),"SELECT * FROM `users` WHERE `username` = '%e' LIMIT 1", name);
    mysql_tquery(gMySQL, query, "OnNameCheck", "is", playerid, name);
    return 1;
}

//------------------------------------------------------------------------------

GetPlayerKill(playerid)
{
    return gPlayerAccountData[playerid][e_player_kills];
}

SetPlayerKill(playerid, kills)
{
    gPlayerAccountData[playerid][e_player_kills] = kills;
}

GetPlayerDeath(playerid)
{
    return gPlayerAccountData[playerid][e_player_deaths];
}

SetPlayerDeath(playerid, deaths)
{
    gPlayerAccountData[playerid][e_player_deaths] = deaths;
}

GetPlayerDeathmatchWins(playerid)
{
    return gPlayerAccountData[playerid][e_player_dm_wins];
}

SetPlayerDeathmatchWins(playerid, wins)
{
    gPlayerAccountData[playerid][e_player_dm_wins] = wins;
}

GetPlayerRaceWins(playerid)
{
    return gPlayerAccountData[playerid][e_player_race_wins];
}

SetPlayerRaceWins(playerid, wins)
{
    gPlayerAccountData[playerid][e_player_race_wins] = wins;
}

GetPlayerDerbyWins(playerid)
{
    return gPlayerAccountData[playerid][e_player_derby_wins];
}

SetPlayerDerbyWins(playerid, wins)
{
    gPlayerAccountData[playerid][e_player_derby_wins] = wins;
}

//------------------------------------------------------------------------------
