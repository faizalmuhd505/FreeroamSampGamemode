/*******************************************************************************
* NOME DO ARQUIVO :		modules/visual/authentication.pwn
*
* DESCRIÇÃO :
*	   Script responsável por mostrar e ocultar a UI de autenticação.
*
* NOTAS :
*	   -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

static PlayerText:loginTextDraw[MAX_PLAYERS][8];
static Text:registerTextDraw[9];
static Text:backgroundTextDraw[7];

static bool:isTextDrawVisible[MAX_PLAYERS];
static bool:isDialogVisible[MAX_PLAYERS];
static bool:isPlayerRegistered[MAX_PLAYERS];

static gPlayerRecoverCode[MAX_PLAYERS][64];

//------------------------------------------------------------------------------

ShowPlayerAuthentication(playerid, bool:login)
{
    PlayAudioStreamForPlayer(playerid, "https://dl.dropboxusercontent.com/u/88802402/lfintro.mp3");
    ClearPlayerScreen(playerid);

    if(login)
    {
        ShowPlayerLoginTextDraw(playerid);
    }
    else
    {
        ShowPlayerRegisterTextDraw(playerid);
    }
}

//------------------------------------------------------------------------------

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(isTextDrawVisible[playerid])
    {
        if(clickedid == Text:INVALID_TEXT_DRAW)
        {
             if(!isDialogVisible[playerid])
             {
                 SelectTextDraw(playerid, 0x74c624ff);
             }
        }
        else if(clickedid == registerTextDraw[2])
        {
            isDialogVisible[playerid] = true;
            ShowPlayerDialog(playerid, DIALOG_REGISTER_GENDER, DIALOG_STYLE_MSGBOX, "Registration: Sex", "Enter your sex", "Man", "Woman");
            CancelSelectTextDraw(playerid);
        }
        else if(clickedid == registerTextDraw[3])
        {
            isDialogVisible[playerid] = true;
            ShowPlayerDialog(playerid, DIALOG_REGISTER_PASSWORD, DIALOG_STYLE_PASSWORD, "Registration: password", "Enter your password", "Save", "X");
            CancelSelectTextDraw(playerid);
        }
        else if(clickedid == registerTextDraw[4])
        {
            new output[290];
            for(new i = 10; i < 100; i++)
            {
                new string[6];
                format(string, sizeof(string), "%i\n", i);
                strcat(output, string);
            }
            isDialogVisible[playerid] = true;
            ShowPlayerDialog(playerid, DIALOG_REGISTER_AGE, DIALOG_STYLE_LIST, "Registration: Age", output, "Save", "X");
            CancelSelectTextDraw(playerid);
        }
        else if(clickedid == registerTextDraw[5])
        {
            isDialogVisible[playerid] = true;
            ShowPlayerDialog(playerid, DIALOG_REGISTER_EMAIL, DIALOG_STYLE_INPUT, "Registration: Email", "Enter your email", "Save", "X");
            CancelSelectTextDraw(playerid);
        }
        else if(clickedid == registerTextDraw[6])
        {
            if(strlen(GetPlayerPassword(playerid)) < 4 || strlen(GetPlayerEmail(playerid)) < 4 || GetPlayerAge(playerid) < 10 || GetPlayerGender(playerid) == -1)
            {
                ShowPlayerRegisterTextDrawErr(playerid);
                PlayErrorSound(playerid);
            }
            else
            {
                StopAudioStreamForPlayer(playerid);
                PlayConfirmSound(playerid);
                SetPlayerLogged(playerid, true);
                SendClientMessage(playerid, 0x88AA62FF, "Registered.");
                HidePlayerRegisterTextDraw(playerid);

                new playerIP[16], playerName[MAX_PLAYER_NAME];
                GetPlayerName(playerid, playerName, sizeof(playerName));
                GetPlayerIp(playerid, playerIP, sizeof(playerIP));

                new query[300];
                mysql_format(gMySQL, query, sizeof(query), "INSERT INTO `users` (`username`, `email`, `password`, `gender`, `age`, `ip`, `created_at`) VALUES ('%e', '%e', '%e', %d, %d, '%s', now())", playerName, GetPlayerEmail(playerid), GetPlayerPassword(playerid), GetPlayerGender(playerid), GetPlayerAge(playerid), playerIP);
                mysql_tquery(gMySQL, query, "OnAccountRegister", "i", playerid);
            }
        }
        else if(clickedid == registerTextDraw[7])
        {
            Kick(playerid);
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
    if(isTextDrawVisible[playerid])
    {
        if(playertextid == loginTextDraw[playerid][3])
        {
            new info[104];
            format(info, sizeof(info), "Welcome back, %s!\n\nYou already have an account.\nEnter your password to access.", GetPlayerNamef(playerid));
            ShowPlayerDialog(playerid, DIALOG_LOGIN_PASSWORD, DIALOG_STYLE_PASSWORD, "Access", info, "Access", "X");
        }
        else if(playertextid == loginTextDraw[playerid][4])
        {
            PlaySelectSound(playerid);
            ShowPlayerDialog(playerid, DIALOG_FORUM, DIALOG_STYLE_MSGBOX, "{ffffff}Our Discord",
            "{ffffff}https://discord.me/projectlegacy ", "Okey", "");
        }
        else if(playertextid == loginTextDraw[playerid][5])
        {
            ShowPlayerCredits(playerid);
        }
        else if(playertextid == loginTextDraw[playerid][7])
        {
            new output[148];
            PlaySelectSound(playerid);
            if(strlen(gPlayerRecoverCode[playerid]) < 2)
            {
                strcat(gPlayerRecoverCode[playerid], GenerateKey());
                format(output, sizeof(output), "Code: %s.", gPlayerRecoverCode[playerid]);
                SendMail(GetPlayerEmail(playerid), "https://discord.me/projectlegacy", "Freeroam", "Recover Password", output);

            }
            format(output, sizeof(output), "We send a code to your email (%s).\nEnter the code below to reset your password:", GetPlayerEmail(playerid));
            ShowPlayerDialog(playerid, DIALOG_RESETPASS_CODE, DIALOG_STYLE_INPUT, "Password", output, "Send", "X");
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch (dialogid)
    {
        case DIALOG_RESETPASS_PASS:
        {
            if(!response)
            {
                PlayErrorSound(playerid);
                ShowPlayerDialog(playerid, DIALOG_RESETPASS_PASS, DIALOG_STYLE_INPUT, "Reset Password", "{00ff00}Correct Code!\n\n{ffffff}Enter your new password:", "Save", "");
            }
            else if(strlen(inputtext) > MAX_PLAYER_PASSWORD - 1)
            {
                PlayErrorSound(playerid);
                ShowPlayerDialog(playerid, DIALOG_RESETPASS_PASS, DIALOG_STYLE_INPUT, "Reset Password", "{ff0000}Very long password!\n\n{ffffff}Enter your new password:", "Save", "");
            }
            else if(strlen(inputtext) < 4)
            {
                PlayErrorSound(playerid);
                ShowPlayerDialog(playerid, DIALOG_RESETPASS_PASS, DIALOG_STYLE_INPUT, "Reset Password", "{ff0000}Very short password!\n\n{ffffff}Enter your new password:", "Save", "");
            }
            else
            {
                SetPlayerPassword(playerid, inputtext);
                SendClientMessage(playerid, COLOR_SUCCESS, "* Your password has been changed successfully!");
                SendClientMessage(playerid, COLOR_SUB_TITLE, "* You can log in now.");
            }
        }
        case DIALOG_RESETPASS_CODE:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
            }
            else
            {
                if(!strcmp(gPlayerRecoverCode[playerid], inputtext) && strlen(inputtext) > 1)
                {
                    PlaySelectSound(playerid);
                    ShowPlayerDialog(playerid, DIALOG_RESETPASS_PASS, DIALOG_STYLE_INPUT, "Password", "{00ff00}Correct code!\n\n{ffffff}Enter your new passworda:", "Save", "");
                }
                else
                {
                    new output[188];
                    PlayErrorSound(playerid);
                    format(output, sizeof(output), "We send a code to your email(%s).\nEnter the code below to reset your password:\n\n{ff0000}INCORRECT CODE!", GetPlayerEmail(playerid));
                    ShowPlayerDialog(playerid, DIALOG_RESETPASS_CODE, DIALOG_STYLE_INPUT, "Password", output, "Send", "X");
                }
            }
        }
        case DIALOG_LOGIN_PASSWORD:
        {
            if(!response)
            {
                PlayCancelSound(playerid);
                return 1;
            }

            new password[MAX_PLAYER_PASSWORD];
            format(password, sizeof(password), GetPlayerPassword(playerid));
            if(!strcmp(password, inputtext) && !isnull(password) && !isnull(inputtext))
            {
                StopAudioStreamForPlayer(playerid);
                HidePlayerLoginTextDraw(playerid);
                PlayConfirmSound(playerid);
                LoadPlayerAccount(playerid);
                SendClientMessage(playerid, 0x88AA62FF, "Connected.");
            }
            else
            {
                ShowPlayerDialog(playerid, DIALOG_LOGIN_PASSWORD, DIALOG_STYLE_INPUT, "Access-> Incorrect password", "Incorrect password!\nTry again:", "Access", "X"),
                PlayErrorSound(playerid);
            }
            return -2;
        }
        case DIALOG_REGISTER_GENDER:
        {
            if(!response)
            {
                SetPlayerGender(playerid, 1);
                PlayConfirmSound(playerid);
            }
            else
            {
                SetPlayerGender(playerid, 0);
                PlayConfirmSound(playerid);
            }
            isDialogVisible[playerid] = false;
            SelectTextDraw(playerid, 0x74c624ff);
        }
        case DIALOG_REGISTER_PASSWORD:
        {
            if(!response)
                PlayCancelSound(playerid);
            else if(strlen(inputtext) < 4)
            {
                PlayErrorSound(playerid);
                ShowPlayerDialog(playerid, DIALOG_REGISTER_PASSWORD, DIALOG_STYLE_PASSWORD, "Registration: password", "Enter your password\n{ff0000}Very short password!", "Save", "X");
            }
            else if(strlen(inputtext) > MAX_PLAYER_PASSWORD-1)
            {
                PlayErrorSound(playerid);
                ShowPlayerDialog(playerid, DIALOG_REGISTER_PASSWORD, DIALOG_STYLE_PASSWORD, "Registration: password", "Enter your password\n{ff0000}Very long password!", "Save", "X");
            }
            else
            {
                SetPlayerPassword(playerid, inputtext, false);
                PlayConfirmSound(playerid);
            }
            isDialogVisible[playerid] = false;
            SelectTextDraw(playerid, 0x74c624ff);
        }
        case DIALOG_REGISTER_AGE:
        {
            if(!response)
                PlayCancelSound(playerid);
            else
            {
                SetPlayerAge(playerid, (listitem + 10));
                PlayConfirmSound(playerid);
            }
            isDialogVisible[playerid] = false;
            SelectTextDraw(playerid, 0x74c624ff);
        }
        case DIALOG_REGISTER_EMAIL:
        {
            if(!response)
                PlayCancelSound(playerid);
            else if(strlen(inputtext) < 4)
            {
                PlayErrorSound(playerid);
                ShowPlayerDialog(playerid, DIALOG_REGISTER_EMAIL, DIALOG_STYLE_INPUT, "Registration: Email", "Enter your email \n {ff0000} Invalid email!", "Save", "X");
            }
            else
            {
                new query[128];
                mysql_format(gMySQL, query, sizeof(query),"SELECT * FROM `users` WHERE `email` = '%e' LIMIT 1", inputtext);
                mysql_tquery(gMySQL, query, "OnEmailCheck", "is", playerid, inputtext);
            }
            isDialogVisible[playerid] = false;
            SelectTextDraw(playerid, 0x74c624ff);
        }
        case DIALOG_CREDITS:
        {
            PlayCancelSound(playerid);
        }
        case DIALOG_FORUM:
        {
            PlayCancelSound(playerid);
        }
    }
    return 1;
}

//------------------------------------------------------------------------------

ShowPlayerLoginTextDraw(playerid)
{
    if(isTextDrawVisible[playerid])
    {
        for(new i = 0; i < sizeof(loginTextDraw[]); i++)
        {
            PlayerTextDrawShow(playerid, loginTextDraw[playerid][i]);
        }
        return 1;
    }

    loginTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 197.000000, 80.000000, "   Login");
    PlayerTextDrawBackgroundColor(playerid, loginTextDraw[playerid][0], 255);
    PlayerTextDrawFont(playerid, loginTextDraw[playerid][0], 3);
    PlayerTextDrawLetterSize(playerid, loginTextDraw[playerid][0], 0.540000, 1.699998);
    PlayerTextDrawColor(playerid, loginTextDraw[playerid][0], -1);
    PlayerTextDrawSetOutline(playerid, loginTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, loginTextDraw[playerid][0], 1);
    PlayerTextDrawUseBox(playerid, loginTextDraw[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, loginTextDraw[playerid][0], 255);
    PlayerTextDrawTextSize(playerid, loginTextDraw[playerid][0], 299.000000, 0.000000);
    PlayerTextDrawSetSelectable(playerid, loginTextDraw[playerid][0], 0);

    new playerName[64];
    format(playerName, sizeof(playerName), "Nick: ~w~%s", GetPlayerNamef(playerid));
    loginTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 220.000000, 138.000000, playerName);
    PlayerTextDrawBackgroundColor(playerid, loginTextDraw[playerid][1], 255);
    PlayerTextDrawFont(playerid, loginTextDraw[playerid][1], 2);
    PlayerTextDrawLetterSize(playerid, loginTextDraw[playerid][1], 0.260000, 1.899999);
    PlayerTextDrawColor(playerid, loginTextDraw[playerid][1], 0x74c624ff);
    PlayerTextDrawSetOutline(playerid, loginTextDraw[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, loginTextDraw[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, loginTextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, loginTextDraw[playerid][1], 0);

    new playerID[64];
    format(playerID, sizeof(playerID), "ID: ~w~%d", playerid);
    loginTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 220.000000, 170.000000, playerID);
    PlayerTextDrawBackgroundColor(playerid, loginTextDraw[playerid][2], 255);
    PlayerTextDrawFont(playerid, loginTextDraw[playerid][2], 2);
    PlayerTextDrawLetterSize(playerid, loginTextDraw[playerid][2], 0.389999, 1.899999);
    PlayerTextDrawColor(playerid, loginTextDraw[playerid][2], 0x74c624ff);
    PlayerTextDrawSetOutline(playerid, loginTextDraw[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, loginTextDraw[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, loginTextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, loginTextDraw[playerid][2], 0);

    loginTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 235.000000, 248.000000, "      TO PLAY");
    PlayerTextDrawBackgroundColor(playerid, loginTextDraw[playerid][3], 255);
    PlayerTextDrawFont(playerid, loginTextDraw[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, loginTextDraw[playerid][3], 0.500000, 1.499999);
    PlayerTextDrawColor(playerid, loginTextDraw[playerid][3], -1);
    PlayerTextDrawSetOutline(playerid, loginTextDraw[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, loginTextDraw[playerid][3], 1);
    PlayerTextDrawUseBox(playerid, loginTextDraw[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, loginTextDraw[playerid][3], 102);
    PlayerTextDrawTextSize(playerid, loginTextDraw[playerid][3], 403.000000, 10.000000);
    PlayerTextDrawSetSelectable(playerid, loginTextDraw[playerid][3], true);

    loginTextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 235.000000, 292.000000, "      FORUM");
    PlayerTextDrawBackgroundColor(playerid, loginTextDraw[playerid][4], 255);
    PlayerTextDrawFont(playerid, loginTextDraw[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, loginTextDraw[playerid][4], 0.500000, 1.499999);
    PlayerTextDrawColor(playerid, loginTextDraw[playerid][4], -1);
    PlayerTextDrawSetOutline(playerid, loginTextDraw[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, loginTextDraw[playerid][4], 1);
    PlayerTextDrawUseBox(playerid, loginTextDraw[playerid][4], 1);
    PlayerTextDrawBoxColor(playerid, loginTextDraw[playerid][4], 102);
    PlayerTextDrawTextSize(playerid, loginTextDraw[playerid][4], 403.000000, 10.000000);
    PlayerTextDrawSetSelectable(playerid, loginTextDraw[playerid][4], true);

    loginTextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 235.000000, 337.000000, "     Credits");
    PlayerTextDrawBackgroundColor(playerid, loginTextDraw[playerid][5], 255);
    PlayerTextDrawFont(playerid, loginTextDraw[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, loginTextDraw[playerid][5], 0.500000, 1.499999);
    PlayerTextDrawColor(playerid, loginTextDraw[playerid][5], -1);
    PlayerTextDrawSetOutline(playerid, loginTextDraw[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, loginTextDraw[playerid][5], 1);
    PlayerTextDrawUseBox(playerid, loginTextDraw[playerid][5], 1);
    PlayerTextDrawBoxColor(playerid, loginTextDraw[playerid][5], 102);
    PlayerTextDrawTextSize(playerid, loginTextDraw[playerid][5], 403.000000, 10.000000);
    PlayerTextDrawSetSelectable(playerid, loginTextDraw[playerid][5], true);

    loginTextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 343.000000, 110.000000, "skin");
    PlayerTextDrawBackgroundColor(playerid, loginTextDraw[playerid][6], 0);
    PlayerTextDrawFont(playerid, loginTextDraw[playerid][6], 5);
    PlayerTextDrawLetterSize(playerid, loginTextDraw[playerid][6], 0.479999, 10.600000);
    PlayerTextDrawColor(playerid, loginTextDraw[playerid][6], -1);
    PlayerTextDrawSetOutline(playerid, loginTextDraw[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, loginTextDraw[playerid][6], 1);
    PlayerTextDrawUseBox(playerid, loginTextDraw[playerid][6], 1);
    PlayerTextDrawBoxColor(playerid, loginTextDraw[playerid][6], 255);
    PlayerTextDrawTextSize(playerid, loginTextDraw[playerid][6], 99.000000, 120.000000);
    PlayerTextDrawSetPreviewModel(playerid, loginTextDraw[playerid][6], GetPlayerSaveSkin(playerid));
    PlayerTextDrawSetPreviewRot(playerid, loginTextDraw[playerid][6], 1.000000, 1.000000, 1.000000, 1.000000);
    PlayerTextDrawSetSelectable(playerid, loginTextDraw[playerid][6], 0);

    loginTextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 235.000000, 382.000000, " RECOVER PASSWORD");
    PlayerTextDrawBackgroundColor(playerid, loginTextDraw[playerid][7], 255);
    PlayerTextDrawFont(playerid, loginTextDraw[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, loginTextDraw[playerid][7], 0.500000, 1.499999);
    PlayerTextDrawColor(playerid, loginTextDraw[playerid][7], -1);
    PlayerTextDrawSetOutline(playerid, loginTextDraw[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, loginTextDraw[playerid][7], 1);
    PlayerTextDrawUseBox(playerid, loginTextDraw[playerid][7], 1);
    PlayerTextDrawBoxColor(playerid, loginTextDraw[playerid][7], 102);
    PlayerTextDrawTextSize(playerid, loginTextDraw[playerid][7], 403.000000, 10.000000);
    PlayerTextDrawSetSelectable(playerid, loginTextDraw[playerid][7], true);

    for(new i = 0; i < sizeof(backgroundTextDraw); i++)
        TextDrawShowForPlayer(playerid, backgroundTextDraw[i]);

    for(new i = 0; i < sizeof(loginTextDraw[]); i++)
        PlayerTextDrawShow(playerid, loginTextDraw[playerid][i]);

    SelectTextDraw(playerid, 0x74c624ff);
    isTextDrawVisible[playerid] = true;
    return 1;
}

//------------------------------------------------------------------------------

HidePlayerLoginTextDraw(playerid)
{
    if(!isTextDrawVisible[playerid])
        return 1;

    for(new i = 0; i < sizeof(backgroundTextDraw); i++)
        TextDrawHideForPlayer(playerid, backgroundTextDraw[i]);

    for(new i = 0; i < sizeof(loginTextDraw[]); i++)
    {
        PlayerTextDrawHide(playerid, loginTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, loginTextDraw[playerid][i]);
    }

    isTextDrawVisible[playerid] = false;
    CancelSelectTextDraw(playerid);
    return 1;
}

//------------------------------------------------------------------------------

ShowPlayerRegisterTextDraw(playerid)
{
    for(new i = 0; i < sizeof(backgroundTextDraw); i++)
        TextDrawShowForPlayer(playerid, backgroundTextDraw[i]);

    for(new i = 0; i < (sizeof(registerTextDraw) - 1); i++)
        TextDrawShowForPlayer(playerid, registerTextDraw[i]);

    isTextDrawVisible[playerid] = true;
    SelectTextDraw(playerid, 0x74c624ff);
}

//------------------------------------------------------------------------------

HidePlayerRegisterTextDraw(playerid)
{
    for(new i = 0; i < sizeof(backgroundTextDraw); i++)
        TextDrawHideForPlayer(playerid, backgroundTextDraw[i]);

    for(new i = 0; i < sizeof(registerTextDraw); i++)
        TextDrawHideForPlayer(playerid, registerTextDraw[i]);

    isTextDrawVisible[playerid] = false;
    CancelSelectTextDraw(playerid);
}

//------------------------------------------------------------------------------

ShowPlayerRegisterTextDrawErr(playerid)
{
    TextDrawShowForPlayer(playerid, registerTextDraw[8]);
}

//------------------------------------------------------------------------------

hook OnPlayerConnect(playerid)
{
    SendClientMessageToAllf(0xb5ff00ff, "* %s connected to the server.", GetPlayerNamef(playerid));
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerDisconnect(playerid, reason)
{
    isDialogVisible[playerid]       = false;
    isTextDrawVisible[playerid]     = false;
    isPlayerRegistered[playerid]    = false;
    gPlayerRecoverCode[playerid][0] = '\0';

    new szDisconnectReason[3][] =
    {
        "Timeout/Crash",
        "Own account",
        "Kick/Ban"
    };
    SendClientMessageToAllf(0xb5ff00ff, "* %s disconnected from the server. (%s)", GetPlayerNamef(playerid), szDisconnectReason[reason]);
    return 1;
}

//------------------------------------------------------------------------------

hook OnGameModeInit()
{
    backgroundTextDraw[0] = TextDrawCreate(197.000000, 2.000000, "#"); // box total
    TextDrawBackgroundColor(backgroundTextDraw[0], 255);
    TextDrawFont(backgroundTextDraw[0], 2);
    TextDrawLetterSize(backgroundTextDraw[0], 0.500000, 49.499992);
    TextDrawColor(backgroundTextDraw[0], -1);
    TextDrawSetOutline(backgroundTextDraw[0], 0);
    TextDrawSetProportional(backgroundTextDraw[0], 1);
    TextDrawSetShadow(backgroundTextDraw[0], 1);
    TextDrawUseBox(backgroundTextDraw[0], 1);
    TextDrawBoxColor(backgroundTextDraw[0], 136);
    TextDrawTextSize(backgroundTextDraw[0], 442.000000, -21.000000);
    TextDrawSetSelectable(backgroundTextDraw[0], 0);

    backgroundTextDraw[1] = TextDrawCreate(230.000000, 13.000000, "~g~~h~L~w~egacy ~g~~h~F~w~reeroam"); // logo
    TextDrawBackgroundColor(backgroundTextDraw[1], 255);
    TextDrawFont(backgroundTextDraw[1], 1);
    TextDrawLetterSize(backgroundTextDraw[1], 0.600000, 2.900000);
    TextDrawColor(backgroundTextDraw[1], -1);
    TextDrawSetOutline(backgroundTextDraw[1], 0);
    TextDrawSetProportional(backgroundTextDraw[1], 1);
    TextDrawSetShadow(backgroundTextDraw[1], 1);
    TextDrawSetSelectable(backgroundTextDraw[1], 0);

    backgroundTextDraw[2] = TextDrawCreate(250.000000, 38.000000, "~w~-"); // linha embaixo do logo
    TextDrawBackgroundColor(backgroundTextDraw[2], 255);
    TextDrawFont(backgroundTextDraw[2], 1);
    TextDrawLetterSize(backgroundTextDraw[2], 9.510000, 1.000000);
    TextDrawColor(backgroundTextDraw[2], -1);
    TextDrawSetOutline(backgroundTextDraw[2], 0);
    TextDrawSetProportional(backgroundTextDraw[2], 1);
    TextDrawSetShadow(backgroundTextDraw[2], 1);
    TextDrawSetSelectable(backgroundTextDraw[2], 0);

    backgroundTextDraw[3] = TextDrawCreate(197.000000, 97.000000, "#"); // barra de cima
    TextDrawBackgroundColor(backgroundTextDraw[3], 255);
    TextDrawFont(backgroundTextDraw[3], 2);
    TextDrawLetterSize(backgroundTextDraw[3], 0.610000, 0.199999);
    TextDrawColor(backgroundTextDraw[3], -1);
    TextDrawSetOutline(backgroundTextDraw[3], 0);
    TextDrawSetProportional(backgroundTextDraw[3], 1);
    TextDrawSetShadow(backgroundTextDraw[3], 1);
    TextDrawUseBox(backgroundTextDraw[3], 1);
    TextDrawBoxColor(backgroundTextDraw[3], 255);
    TextDrawTextSize(backgroundTextDraw[3], 442.000000, -20.000000);
    TextDrawSetSelectable(backgroundTextDraw[3], 0);

    backgroundTextDraw[4] = TextDrawCreate(240.000000, 415.000000, "We wish a good game !");
    TextDrawBackgroundColor(backgroundTextDraw[4], 255);
    TextDrawFont(backgroundTextDraw[4], 2);
    TextDrawLetterSize(backgroundTextDraw[4], 0.290000, 1.000000);
    TextDrawColor(backgroundTextDraw[4], -1);
    TextDrawSetOutline(backgroundTextDraw[4], 1);
    TextDrawSetProportional(backgroundTextDraw[4], 1);
    TextDrawSetSelectable(backgroundTextDraw[4], 0);

    backgroundTextDraw[5] = TextDrawCreate(193.000000, 2.000000, "#"); // barra esquerda
    TextDrawBackgroundColor(backgroundTextDraw[5], 255);
    TextDrawFont(backgroundTextDraw[5], 2);
    TextDrawLetterSize(backgroundTextDraw[5], 0.610000, 51.099998);
    TextDrawColor(backgroundTextDraw[5], -1);
    TextDrawSetOutline(backgroundTextDraw[5], 0);
    TextDrawSetProportional(backgroundTextDraw[5], 1);
    TextDrawSetShadow(backgroundTextDraw[5], 1);
    TextDrawUseBox(backgroundTextDraw[5], 1);
    TextDrawBoxColor(backgroundTextDraw[5], 255);
    TextDrawTextSize(backgroundTextDraw[5], 194.000000, -20.000000);
    TextDrawSetSelectable(backgroundTextDraw[5], 0);

    backgroundTextDraw[6] = TextDrawCreate(446.000000, 2.000000, "#"); // barra direita
    TextDrawBackgroundColor(backgroundTextDraw[6], 255);
    TextDrawFont(backgroundTextDraw[6], 2);
    TextDrawLetterSize(backgroundTextDraw[6], 0.610000, 51.099998);
    TextDrawColor(backgroundTextDraw[6], -1);
    TextDrawSetOutline(backgroundTextDraw[6], 0);
    TextDrawSetProportional(backgroundTextDraw[6], 1);
    TextDrawSetShadow(backgroundTextDraw[6], 1);
    TextDrawUseBox(backgroundTextDraw[6], 1);
    TextDrawBoxColor(backgroundTextDraw[6], 255);
    TextDrawTextSize(backgroundTextDraw[6], 438.000000, -20.000000);
    TextDrawSetSelectable(backgroundTextDraw[6], 0);

    registerTextDraw[0] = TextDrawCreate(197.000000, 80.000000, "  Record");
    TextDrawBackgroundColor(registerTextDraw[0], 255);
    TextDrawFont(registerTextDraw[0], 3);
    TextDrawLetterSize(registerTextDraw[0], 0.540000, 1.699998);
    TextDrawColor(registerTextDraw[0], -1);
    TextDrawSetOutline(registerTextDraw[0], 1);
    TextDrawSetProportional(registerTextDraw[0], 1);
    TextDrawUseBox(registerTextDraw[0], 1);
    TextDrawBoxColor(registerTextDraw[0], 255);
    TextDrawTextSize(registerTextDraw[0], 314.000000, 0.000000);
    TextDrawSetSelectable(registerTextDraw[0], 0);

    registerTextDraw[1] = TextDrawCreate(197.000000, 332.000000, "#"); // barra de baixo
    TextDrawBackgroundColor(registerTextDraw[1], 255);
    TextDrawFont(registerTextDraw[1], 2);
    TextDrawLetterSize(registerTextDraw[1], 0.610000, 0.199999);
    TextDrawColor(registerTextDraw[1], -1);
    TextDrawSetOutline(registerTextDraw[1], 0);
    TextDrawSetProportional(registerTextDraw[1], 1);
    TextDrawSetShadow(registerTextDraw[1], 1);
    TextDrawUseBox(registerTextDraw[1], 1);
    TextDrawBoxColor(registerTextDraw[1], 255);
    TextDrawTextSize(registerTextDraw[1], 442.000000, -20.000000);
    TextDrawSetSelectable(registerTextDraw[1], 0);

    registerTextDraw[2] = TextDrawCreate(235.000000, 139.000000, "       SEX");
    TextDrawBackgroundColor(registerTextDraw[2], 255);
    TextDrawFont(registerTextDraw[2], 1);
    TextDrawLetterSize(registerTextDraw[2], 0.500000, 1.499999);
    TextDrawColor(registerTextDraw[2], -1);
    TextDrawSetOutline(registerTextDraw[2], 1);
    TextDrawSetProportional(registerTextDraw[2], 1);
    TextDrawUseBox(registerTextDraw[2], 1);
    TextDrawBoxColor(registerTextDraw[2], 102);
    TextDrawTextSize(registerTextDraw[2], 403.000000, 10.000000);
    TextDrawSetSelectable(registerTextDraw[2], true);

    registerTextDraw[3] = TextDrawCreate(235.000000, 184.000000, "       PASSWORD");
    TextDrawBackgroundColor(registerTextDraw[3], 255);
    TextDrawFont(registerTextDraw[3], 1);
    TextDrawLetterSize(registerTextDraw[3], 0.500000, 1.499999);
    TextDrawColor(registerTextDraw[3], -1);
    TextDrawSetOutline(registerTextDraw[3], 1);
    TextDrawSetProportional(registerTextDraw[3], 1);
    TextDrawUseBox(registerTextDraw[3], 1);
    TextDrawBoxColor(registerTextDraw[3], 102);
    TextDrawTextSize(registerTextDraw[3], 403.000000, 10.000000);
    TextDrawSetSelectable(registerTextDraw[3], true);

    registerTextDraw[4] = TextDrawCreate(235.000000, 230.000000, "       AGE");
    TextDrawBackgroundColor(registerTextDraw[4], 255);
    TextDrawFont(registerTextDraw[4], 1);
    TextDrawLetterSize(registerTextDraw[4], 0.500000, 1.499999);
    TextDrawColor(registerTextDraw[4], -1);
    TextDrawSetOutline(registerTextDraw[4], 1);
    TextDrawSetProportional(registerTextDraw[4], 1);
    TextDrawUseBox(registerTextDraw[4], 1);
    TextDrawBoxColor(registerTextDraw[4], 102);
    TextDrawTextSize(registerTextDraw[4], 403.000000, 10.000000);
    TextDrawSetSelectable(registerTextDraw[4], true);

    registerTextDraw[5] = TextDrawCreate(235.000000, 276.000000, "       EMAIL");
    TextDrawBackgroundColor(registerTextDraw[5], 255);
    TextDrawFont(registerTextDraw[5], 1);
    TextDrawLetterSize(registerTextDraw[5], 0.500000, 1.499999);
    TextDrawColor(registerTextDraw[5], -1);
    TextDrawSetOutline(registerTextDraw[5], 1);
    TextDrawSetProportional(registerTextDraw[5], 1);
    TextDrawUseBox(registerTextDraw[5], 1);
    TextDrawBoxColor(registerTextDraw[5], 102);
    TextDrawTextSize(registerTextDraw[5], 403.000000, 10.000000);
    TextDrawSetSelectable(registerTextDraw[5], true);

    registerTextDraw[6] = TextDrawCreate(197.000000, 332.000000, "  Start");
    TextDrawBackgroundColor(registerTextDraw[6], 255);
    TextDrawFont(registerTextDraw[6], 3);
    TextDrawLetterSize(registerTextDraw[6], 0.540000, 1.699998);
    TextDrawColor(registerTextDraw[6], -1);
    TextDrawSetOutline(registerTextDraw[6], 1);
    TextDrawSetProportional(registerTextDraw[6], 1);
    TextDrawUseBox(registerTextDraw[6], 1);
    TextDrawBoxColor(registerTextDraw[6], 255);
    TextDrawTextSize(registerTextDraw[6], 287.000000, 10.000000);
    TextDrawSetSelectable(registerTextDraw[6], true);

    registerTextDraw[7] = TextDrawCreate(326.000000, 332.000000, "  Cancel");
    TextDrawBackgroundColor(registerTextDraw[7], 255);
    TextDrawFont(registerTextDraw[7], 3);
    TextDrawLetterSize(registerTextDraw[7], 0.540000, 1.699998);
    TextDrawColor(registerTextDraw[7], -1);
    TextDrawSetOutline(registerTextDraw[7], 1);
    TextDrawSetProportional(registerTextDraw[7], 1);
    TextDrawUseBox(registerTextDraw[7], 1);
    TextDrawBoxColor(registerTextDraw[7], 255);
    TextDrawTextSize(registerTextDraw[7], 442.000000, 10.000000);
    TextDrawSetSelectable(registerTextDraw[7], true);

    registerTextDraw[8] = TextDrawCreate(210.000000, 309.000000, "Please complete all data !");
    TextDrawBackgroundColor(registerTextDraw[8], 255);
    TextDrawFont(registerTextDraw[8], 2);
    TextDrawLetterSize(registerTextDraw[8], 0.250000, 1.000000);
    TextDrawColor(registerTextDraw[8], -16776961);
    TextDrawSetOutline(registerTextDraw[8], 1);
    TextDrawSetProportional(registerTextDraw[8], 1);
    TextDrawSetSelectable(registerTextDraw[8], 0);
    return 1;
}
