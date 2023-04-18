/*
	Dialogs Include (dialogs.inc)
	* New dialog functions and NEW Model-Preview dialog, now within SAMP "ShowPlayerDialog", a new style!
  	* Just add a new style: DIALOG_STYLE_PREVMODEL

 	Author: (creator)
	* Gammix
	* Y_Less - ceildiv macro, and connection check suggest

	(c) Copyright 2015
  	* This file is provided as is (no warranties).
*/
//native PlayerTextDrawSetPreviewModel(playerid, PlayerText:text, modelindex);
//native PlayerTextDrawSetPreviewRot(playerid, PlayerText:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0);
/*
FUNCTIONS:
native ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[] = "", infosize = sizeof(info));
native HidePlayerDialog(playerid);
native GetPlayerDialogID(playerid);
native GetPlayerDialogStyle(playerid);
native SetupPreviewModelDialog(playerid, Float:mx, Float:my, Float:mz, Float:mzoom = 1.0, mbgcolor = 0x4A5A6BFF, hovercolor = 0x8B0000FF, selectcolor = 0x8B0000FF);

CALLBACKS:
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
*/

#if !defined INVALID_DIALOG_ID
	#define INVALID_DIALOG_ID 	-1//make sure the INVALID_DIALOG_ID is '-1' only!
#endif

#define MAX_DIALOG_MODELS 		400//maximum number of listitems a PREVIEW MODEL Dialog can have

#define DIALOG_STYLE_PREVMODEL 	10//the new dialog style id, you may change if not suitable or for future usage! This may effect HidePlayerDialog.

#define MODELS_PER_LINE 		(6)//Max models that can be displayed in a line

#define MODELS_PER_PAGE 		((MODELS_PER_LINE) * 3)//Max models that can be displayed in a page

// Dialog Textdraws
static PlayerText:gPlayerButtonsTD[MAX_PLAYERS][2];
static PlayerText:gPlayerHeaderTD[MAX_PLAYERS];
static PlayerText:gPlayerPageTD[MAX_PLAYERS];
static PlayerText:gPlayerModelTD[MAX_PLAYERS][MODELS_PER_PAGE];
//
static Text:gBackgroundTD;
static Text:gContentBoxTD[2];
static Text:gButtonsTD[14];
//
static gPlayerList[MAX_PLAYERS][MAX_DIALOG_MODELS];
static gPlayerTotalModels[MAX_PLAYERS];
//
enum DialogEnum
{
	bool:E_DIALOG_CANCEL,
	E_DIALOG_PAGE,
	E_DIALOG_SELECTED_ITEM,
	E_DIALOG_CLICK_TICK,
	Float:E_MODEL_X,
	Float:E_MODEL_Y,
	Float:E_MODEL_Z,
	Float:E_MODEL_ZOOM,
	E_MODEL_BACKGROUND_COLOR,
	E_MODEL_HOVER_COLOR,
	E_MODEL_SELECT_COLOR
}
static gPlayerDialog[MAX_PLAYERS][DialogEnum];
//

// Internal functions
#define ceildiv(%0,%1) (((%0)-1)/(%1)+1)//thansk to Y_Less
static Dialog_TotalPages(playerid)
{
	if(! IsPlayerConnected(playerid)) return false;
	return ceildiv(gPlayerTotalModels[playerid], MODELS_PER_PAGE);
}

static Dialog_CancelSelectTextDraw(playerid)
{
	gPlayerDialog[playerid][E_DIALOG_CANCEL] = true;
	return CancelSelectTextDraw(playerid);
}

static Text:Dialog_TextDrawAdd(Float:posX, Float:posY, string[], bgcolor, font, Float:lettersizeX, Float:lettersizeY, textcolor, allign = 0, outline = 1, bool:proportional = true, shadow = 1, bool:usebox = false, boxcolor = 0, Float:textsizeX = -1.0, Float:textsizeY = -1.0, model = 0, Float:rotX = 0.0, Float:rotY = 0.0, Float:rotZ = 0.0, Float:zoom = 1.0)
{
	static Text:gTextDraw;
    gTextDraw = TextDrawCreate(posX, posY, string);
	TextDrawBackgroundColor(gTextDraw, bgcolor);
	TextDrawFont(gTextDraw, font);
	TextDrawLetterSize(gTextDraw, lettersizeX, lettersizeY);
	TextDrawColor(gTextDraw, textcolor);
	TextDrawAlignment(gTextDraw, allign);
	TextDrawSetOutline(gTextDraw, outline);
	TextDrawSetProportional(gTextDraw, proportional);
	TextDrawSetShadow(gTextDraw, shadow);
	TextDrawUseBox(gTextDraw, usebox);
	if(usebox) TextDrawBoxColor(gTextDraw, boxcolor);
	if(textsizeX != -1.0 && textsizeY != -1.0) TextDrawTextSize(gTextDraw, textsizeX, textsizeY);
	if(font == 5)
	{
		TextDrawSetPreviewModel(gTextDraw, model);
		TextDrawSetPreviewRot(gTextDraw, rotX, rotY, rotZ, zoom);
	}
	return gTextDraw;
}

static PlayerText:Dialog_PlayerTextDrawAdd(playerid, Float:posX, Float:posY, string[], bgcolor, font, Float:lettersizeX, Float:lettersizeY, textcolor, allign = 0, outline = 1, bool:proportional = true, shadow = 1, bool:usebox = false, boxcolor = 0, Float:textsizeX = -1.0, Float:textsizeY = -1.0, model = 0, Float:rotX = 0.0, Float:rotY = 0.0, Float:rotZ = 0.0, Float:zoom = 1.0, selectable = 0)
{
	static PlayerText:gTextDraw;
    gTextDraw = CreatePlayerTextDraw(playerid, posX, posY, string);
	PlayerTextDrawBackgroundColor(playerid, gTextDraw, bgcolor);
	PlayerTextDrawFont(playerid, gTextDraw, font);
	PlayerTextDrawLetterSize(playerid, gTextDraw, lettersizeX, lettersizeY);
	PlayerTextDrawColor(playerid, gTextDraw, textcolor);
 	PlayerTextDrawAlignment(playerid, gTextDraw, allign);
	PlayerTextDrawSetOutline(playerid, gTextDraw, outline);
	PlayerTextDrawSetProportional(playerid, gTextDraw, proportional);
	PlayerTextDrawSetShadow(playerid, gTextDraw, shadow);
	PlayerTextDrawUseBox(playerid, gTextDraw, usebox);
	if(usebox) PlayerTextDrawBoxColor(playerid, gTextDraw, boxcolor);
	if(textsizeX != -1.0 && textsizeY != -1.0) PlayerTextDrawTextSize(playerid, gTextDraw, textsizeX, textsizeY);
	if(font == 5)
	{
		PlayerTextDrawSetPreviewModel(playerid, gTextDraw, model);
		PlayerTextDrawSetPreviewRot(playerid, gTextDraw, rotX, rotY, rotZ, zoom);
	}
	PlayerTextDrawSetSelectable(playerid, gTextDraw, selectable);
	return gTextDraw;
}

static Dialog_isnumeric(str[])
{
	new ch, i;
	while ((ch = str[i++])) if (!('0' <= ch <= '9')) return false;
	return true;
}

static Dialog_CreateGlobalTD()
{
   	gBackgroundTD 	 = Dialog_TextDrawAdd(132.000000, 	123.000000, "BACKGROUND", 	255, 1, 0.000000, 25.000000, -1, 	0, false, true, 0, true, 150, 	500.000000, 0.000000);
    gContentBoxTD[0] = Dialog_TextDrawAdd(137.000000, 	131.000000, "BOX", 			255, 1, 0.000000, 20.900007, -156, 	0, false, true, 0, true, -156, 	493.000000, 0.000000);
    gContentBoxTD[1] = Dialog_TextDrawAdd(138.000000, 	132.000000, "BOX", 			255, 1, 0.000000, 20.700010, -1, 	0, false, true, 0, true, 230, 	492.000000, 0.000000);
	return true;
}

static Dialog_DestroyGlobalTD()
{
	TextDrawHideForAll(gBackgroundTD);
	TextDrawDestroy(gBackgroundTD);
	TextDrawHideForAll(gContentBoxTD[0]);
	TextDrawDestroy(gContentBoxTD[0]);
	TextDrawHideForAll(gContentBoxTD[1]);
	TextDrawDestroy(gContentBoxTD[1]);
	return true;
}

static Dialog_CreateGlobalButtonsTD()
{
    gButtonsTD[0] = Dialog_TextDrawAdd(200.000000, 329.000000, "BUTTON1", 			255, 1, 0.000000, 1.300007, -1, 	0, false, true, 0, true, 	-156, 	256.000000, 	27.000000);
	gButtonsTD[1] = Dialog_TextDrawAdd(197.000000, 328.000000, "LD_OTB2:butnA", 	255, 4, 0.000000, 1.300008, 255, 	0, false, true, 0, true, 	255, 	63.000000, 		18.000000, 0, 0.0, 0.0, 0.0, 1);
	TextDrawSetSelectable(gButtonsTD[1], 1);//i have to do this seperately, idk why its not set to selectable when in the funcion Dialog_TextDrawAdd. Though it works in the case of player texts!
    gButtonsTD[2] = Dialog_TextDrawAdd(194.000000, 322.000000, "(          )", 	255, 1, 0.389999, 2.299999, -131, 	0, false, true, 0, false);

    gButtonsTD[3] = Dialog_TextDrawAdd(284.000000, 329.000000, "BUTTON2", 			255, 1, 0.000000, 1.300007, -1, 	0, false, true, 0, true, 	-156, 	340.000000, 	27.000000);
    gButtonsTD[4] = Dialog_TextDrawAdd(280.000000, 328.000000, "LD_OTB2:butnA", 	255, 4, 0.000000, 1.300008, 255, 	0, false, true, 0, true, 	255, 	65.000000, 		18.000000, 0, 0.0, 0.0, 0.0, 1);
    TextDrawSetSelectable(gButtonsTD[4], 1);
	gButtonsTD[5] = Dialog_TextDrawAdd(278.000000, 322.000000, "(          )", 	255, 1, 0.389999, 2.299999, -131, 	0, false, true, 0, false);

    gButtonsTD[6] = Dialog_TextDrawAdd(371.000000, 329.000000, "BUTTON3", 			255, 1, 0.000000, 1.300007, -1, 	0, false, true, 0, true, 	-156, 	386.000000, 	27.000000);
    gButtonsTD[7] = Dialog_TextDrawAdd(367.000000, 328.000000, "LD_OTB2:butnA", 	255, 4, 0.000000, 1.300008, 255, 	0, false, true, 0, true, 	255, 	23.000000, 		18.000000, 0, 0.0, 0.0, 0.0, 1);
    TextDrawSetSelectable(gButtonsTD[7], 1);
	gButtonsTD[8] = Dialog_TextDrawAdd(365.000000, 322.000000, "(   )", 			255, 1, 0.389999, 2.299999, -131, 	0, false, true, 0, false);
    gButtonsTD[9] = Dialog_TextDrawAdd(378.000000, 328.000000, "<", 				0, 	 1, 0.269999, 1.299999, -56, 	2, false, true, 0, false);

    gButtonsTD[10] = Dialog_TextDrawAdd(402.000000, 329.000000, "BUTTON4",			255, 1, 0.000000, 1.300007, -1, 	0, false, true, 0, true, 	-156,	417.000000, 	27.000000);
    gButtonsTD[11] = Dialog_TextDrawAdd(399.000000, 328.000000, "LD_OTB2:butnA", 	255, 4, 0.000000, 1.300008, 255, 	0, false, true, 0, true, 	255, 	21.000000, 		18.000000, 0, 0.0, 0.0, 0.0, 1);
    TextDrawSetSelectable(gButtonsTD[11], 1);
	gButtonsTD[12] = Dialog_TextDrawAdd(396.000000, 322.000000, "(   )", 			255, 1, 0.389999, 2.299999, -131, 	0, false, true, 0, false);
    gButtonsTD[13] = Dialog_TextDrawAdd(410.000000, 328.000000, ">", 				0,   1, 0.269999, 1.299999, -56, 	2, false, true, 0, false);
	return true;
}

static Dialog_DestroyGlobalButtonsTD()
{
	for(new i; i != 14;i++)
	{
		TextDrawHideForAll(gButtonsTD[i]);
		TextDrawDestroy(gButtonsTD[i]);
	}
	return true;
}

static Dialog_Update(playerid, selected = 0)
{
	new Float:BASE_X = 140.0;
	new Float:BASE_Y = 132.0;
	new bgcolor = 0;
	new switch_line = 0;
	new current_items = ((gPlayerDialog[playerid][E_DIALOG_PAGE]) * MODELS_PER_PAGE);

    //destroy model player:textdraws

	for(new i; i != MODELS_PER_PAGE; i++)
	{
	    if(gPlayerModelTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
	   		PlayerTextDrawHide(playerid, gPlayerModelTD[playerid][i]);
			PlayerTextDrawDestroy(playerid, gPlayerModelTD[playerid][i]);
			gPlayerModelTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	for(new i; i != MODELS_PER_PAGE; i++)
	{
	    if(current_items >= (gPlayerTotalModels[playerid])) break;

	    if(i == selected)
		{
			gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM] = current_items;
			bgcolor = gPlayerDialog[playerid][E_MODEL_SELECT_COLOR];
	    }
		else bgcolor = gPlayerDialog[playerid][E_MODEL_BACKGROUND_COLOR];

		gPlayerModelTD[playerid][i] = Dialog_PlayerTextDrawAdd(playerid, BASE_X, BASE_Y, "model", bgcolor, 5, 0.500000, 1.000000, -1, 0, 0, true, 0, true, 0, 56.000000, 61.000000, gPlayerList[playerid][current_items], gPlayerDialog[playerid][E_MODEL_X], gPlayerDialog[playerid][E_MODEL_Y], gPlayerDialog[playerid][E_MODEL_Z], gPlayerDialog[playerid][E_MODEL_ZOOM], true);
		PlayerTextDrawShow(playerid, gPlayerModelTD[playerid][i]);

		BASE_X += 57.0;
		switch_line += 1;
		if(switch_line == MODELS_PER_LINE)
		{
			switch_line = 0;
			BASE_Y += 62.0;
			BASE_X = 140.0;
		}
		current_items += 1;
	}
	return true;
}

static Dialog_UpdatePage(playerid)
{
	new string[10];
	if(GetPlayerDialogStyle(playerid) == DIALOG_STYLE_PREVMODEL)
	{
		format(string, sizeof(string), "%d/%d", (gPlayerDialog[playerid][E_DIALOG_PAGE] + 1), Dialog_TotalPages(playerid));
		PlayerTextDrawSetString(playerid, gPlayerPageTD[playerid], string);
	}
	return true;
}

// Handling Callbacks
//Note: if you use this in a filterscript, please define "FILTERSCRIPT" in your script
#if defined FILTERSCRIPT// if used in a filterscript

	public OnFilterScriptInit()
	{
		Dialog_CreateGlobalTD();
		Dialog_CreateGlobalButtonsTD();

        #if defined Dialog_OnFilterScriptInit
        	return Dialog_OnFilterScriptInit();
	    #else
	    	return 1;
	    #endif
	}
	#if defined _ALS_OnFilterScriptInit
	    #undef OnFilterScriptInit
	#else
	    #define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit Dialog_OnFilterScriptInit
	#if defined Dialog_OnFilterScriptInit
	    forward Dialog_OnFilterScriptInit();
	#endif

	public OnFilterScriptExit()
	{
		Dialog_DestroyGlobalTD();
		Dialog_DestroyGlobalButtonsTD();

	    #if defined Dialog_OnFilterScriptExit
        	return Dialog_OnFilterScriptExit();
	    #else
	    	return 1;
	    #endif
	}
	#if defined _ALS_OnFilterScriptExit
	    #undef OnFilterScriptExit
	#else
	    #define _ALS_OnFilterScriptExit
	#endif
	#define OnFilterScriptExit Dialog_OnFilterScriptExit
	#if defined Dialog_OnFilterScriptExit
	    forward Dialog_OnFilterScriptExit();
	#endif

#else// if used in a gamemode

	public OnGameModeInit()
	{
		Dialog_CreateGlobalTD();
		Dialog_CreateGlobalButtonsTD();

	    #if defined Dialog_OnGameModeInit
        	return Dialog_OnGameModeInit();
	    #else
	    	return 1;
	    #endif
	}
	#if defined _ALS_OnGameModeInit
	    #undef OnGameModeInit
	#else
	    #define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit Dialog_OnGameModeInit
	#if defined Dialog_OnGameModeInit
	    forward Dialog_OnGameModeInit();
	#endif

	public OnGameModeExit()
	{
		Dialog_DestroyGlobalTD();
		Dialog_DestroyGlobalButtonsTD();

	    #if defined Dialog_OnGameModeExit
        	return Dialog_OnGameModeExit();
	    #else
	    	return 1;
	    #endif
	}
	#if defined _ALS_OnGameModeExit
	    #undef OnGameModeExit
	#else
	    #define _ALS_OnGameModeExit
	#endif
	#define OnGameModeExit Dialog_OnGameModeExit
	#if defined Dialog_OnGameModeExit
	    forward Dialog_OnGameModeExit();
	#endif

#endif

public OnPlayerConnect(playerid)
{
	for(new i; i != 2; i++) gPlayerButtonsTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;

	gPlayerHeaderTD[playerid] = PlayerText:INVALID_TEXT_DRAW;
	gPlayerPageTD[playerid] = PlayerText:INVALID_TEXT_DRAW;

	for(new i; i != MODELS_PER_PAGE; i++) gPlayerModelTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;

	SetPVarInt(playerid, "Dialog_ID", INVALID_DIALOG_ID);
	SetPVarInt(playerid, "Dialog_TYPE", -1);
	gPlayerDialog[playerid][E_DIALOG_PAGE] = 0;
	gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM] = 0;
	gPlayerDialog[playerid][E_DIALOG_CLICK_TICK] = 0;

	SetupPreviewModelDialog(playerid, 0.0, 0.0, 0.0);

	gPlayerDialog[playerid][E_DIALOG_CANCEL] = false;

	#if defined Dialog_OnPlayerConnect
       	return Dialog_OnPlayerConnect(playerid);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Dialog_OnPlayerConnect
#if defined Dialog_OnPlayerConnect
    forward Dialog_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	gPlayerPageTD[playerid] = PlayerText:INVALID_TEXT_DRAW;
	gPlayerHeaderTD[playerid] = PlayerText:INVALID_TEXT_DRAW;
	for(new i; i != 2; i++) gPlayerButtonsTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	for(new i; i != MODELS_PER_PAGE; i++) gPlayerModelTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;

    #if defined Dialog_OnPlayerDisconnect
		return Dialog_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect Dialog_OnPlayerDisconnect
#if defined Dialog_OnPlayerDisconnect
	forward Dialog_OnPlayerDisconnect(playerid, reason);
#endif

#define BUTTON_1 		gButtonsTD[1]//button 1, clickable TD; gives you response = 0
#define BUTTON_2 		gButtonsTD[4]//button 2, clickable TD; gives you response = 1
#define BUTTON_PREVIOUS gButtonsTD[7]//button <, clickable TD; gives you previous page
#define BUTTON_NEXT 	gButtonsTD[11]//button >, clickable TD; gives you next page

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(! gPlayerDialog[playerid][E_DIALOG_CANCEL])
	{
	    if(GetPlayerDialogStyle(playerid) == DIALOG_STYLE_PREVMODEL)
	    {
			new model[15] = "-1";
	   		if(Dialog_isnumeric(gPlayerList[playerid][gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM]]))
	  		{
			   	format(model, sizeof(model), "%d", gPlayerList[playerid][gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM]]);
			}

	        if(gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM] < 0) gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM] = 0;

			if(clickedid == Text:INVALID_TEXT_DRAW)//if pressed ESC key
			{
				if(! CallLocalFunction("OnDialogResponse", "dddds", playerid, GetPVarInt(playerid, "Dialog_ID"), 0, gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM], model))
				{
	   				CallRemoteFunction("OnDialogResponse", "dddds", playerid, GetPVarInt(playerid, "Dialog_ID"), 0, gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM], model);
				}
				return 1;
			}

			if(clickedid == BUTTON_1)//if clicked 'BUTTON1'
			{
				if(! CallLocalFunction("OnDialogResponse", "dddds", playerid, GetPVarInt(playerid, "Dialog_ID"), 1, gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM], model))
				{
				    CallRemoteFunction("OnDialogResponse", "dddds", playerid, GetPVarInt(playerid, "Dialog_ID"), 1, gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM], model);
				}
				return 1;
			}

		 	if(clickedid == BUTTON_2)//if clicked 'BUTTON2'
			{
			    if(! CallLocalFunction("OnDialogResponse", "dddds", playerid, GetPVarInt(playerid, "Dialog_ID"), 0, gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM], model))
				{
				    CallRemoteFunction("OnDialogResponse", "dddds", playerid, GetPVarInt(playerid, "Dialog_ID"), 0, gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM], model);
				}
				return 1;
			}

			if(clickedid == BUTTON_NEXT)//if clicked '>' - next page
			{
			   	if(gPlayerDialog[playerid][E_DIALOG_PAGE] < (Dialog_TotalPages(playerid) - 1))
		 		{
					gPlayerDialog[playerid][E_DIALOG_PAGE] += 1;
					Dialog_Update(playerid);
					Dialog_UpdatePage(playerid);
				}
				else
				{
					PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				}
			}

		 	if(clickedid == BUTTON_PREVIOUS)//if clicked '<' - previous page
			{
				if(gPlayerDialog[playerid][E_DIALOG_PAGE] > 0)
				{
			    	gPlayerDialog[playerid][E_DIALOG_PAGE] -= 1;
			    	Dialog_Update(playerid);
					Dialog_UpdatePage(playerid);
				}
				else
				{
				    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
				}
			}
		}
	}
	gPlayerDialog[playerid][E_DIALOG_CANCEL] = false;

    #if defined Dialog_OnPlayerClickTextDraw
       	return Dialog_OnPlayerClickTextDraw(playerid, Text:clickedid);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
    #undef OnPlayerClickTextDraw
#else
    #define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw Dialog_OnPlayerClickTextDraw
#if defined Dialog_OnPlayerClickTextDraw
    forward Dialog_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(! gPlayerDialog[playerid][E_DIALOG_CANCEL])
	{
		if(GetPlayerDialogStyle(playerid) == DIALOG_STYLE_PREVMODEL)
	 	{
		 	//clicks on a model
			for(new x = 0; x < MODELS_PER_PAGE; x++)
			{
			    //double click
			    if((GetTickCount() - gPlayerDialog[playerid][E_DIALOG_CLICK_TICK]) < 200)
			    {
			    	if(playertextid == gPlayerModelTD[playerid][x])
					{
						new model[15] = "-1";
				   		if(Dialog_isnumeric(gPlayerList[playerid][gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM]]))
				  		{
						   	format(model, sizeof(model), "%d", gPlayerList[playerid][gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM]]);
						}

				        if(gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM] < 0) gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM] = 0;

						if(! CallLocalFunction("OnDialogResponse", "dddds", playerid, GetPVarInt(playerid, "Dialog_ID"), 1, gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM], model))
						{
							CallRemoteFunction("OnDialogResponse", "dddds", playerid, GetPVarInt(playerid, "Dialog_ID"), 1, gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM], model);
						}
						return 1;
					}
			    }
			    //single click (just highlight the listitem)
			    else
			    {
			    	if(playertextid == gPlayerModelTD[playerid][x])
					{
					    gPlayerDialog[playerid][E_DIALOG_CLICK_TICK] = GetTickCount();
						return Dialog_Update(playerid, x);
					}
				}
			}
		}
	}
	gPlayerDialog[playerid][E_DIALOG_CANCEL] = false;

    #if defined Dialog_OnPlayerClickPlayerTD
       	return Dialog_OnPlayerClickPlayerTD(playerid, PlayerText:playertextid);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnPlayerClickPlayerTD
    #undef OnPlayerClickPlayerTextDraw
#else
    #define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw Dialog_OnPlayerClickPlayerTD
#if defined Dialog_OnPlayerClickPlayerTD
    forward Dialog_OnPlayerClickPlayerTD(playerid, PlayerText:playertextid);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(GetPlayerDialogStyle(playerid) == DIALOG_STYLE_PREVMODEL)
	{
		HidePlayerDialog(playerid);
	}
	else
	{
	    SetPVarInt(playerid, "Dialog_ID", INVALID_DIALOG_ID);
		SetPVarInt(playerid, "Dialog_TYPE", -1);
		gPlayerDialog[playerid][E_DIALOG_PAGE] = 0;
		gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM] = 0;
	 	gPlayerDialog[playerid][E_DIALOG_CLICK_TICK] = GetTickCount();
	}

    #if defined Dialog_OnDialogResponse
       	return Dialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif
#define OnDialogResponse Dialog_OnDialogResponse
#if defined Dialog_OnDialogResponse
    forward Dialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

// Include functions
stock GetPlayerDialogID(playerid)
{
	if(! IsPlayerConnected(playerid)) return false;
	return GetPVarInt(playerid, "Dialog_ID");
}

stock GetPlayerDialogStyle(playerid)
{
	if(! IsPlayerConnected(playerid)) return false;
	return GetPVarInt(playerid, "Dialog_TYPE");
}

stock SetupPreviewModelDialog(playerid, Float:mx, Float:my, Float:mz, Float:mzoom = 1.0, mbgcolor = 0x00FFFF10, hovercolor = 0x8B0000FF, selectcolor = 0x8B0000FF)
{
	gPlayerDialog[playerid][E_MODEL_X] = mx;
	gPlayerDialog[playerid][E_MODEL_Y] = my;
	gPlayerDialog[playerid][E_MODEL_Z] = mz;
	gPlayerDialog[playerid][E_MODEL_ZOOM] = mzoom;
	gPlayerDialog[playerid][E_MODEL_BACKGROUND_COLOR] = mbgcolor;
	gPlayerDialog[playerid][E_MODEL_HOVER_COLOR] = hovercolor;
	gPlayerDialog[playerid][E_MODEL_SELECT_COLOR] = selectcolor;
	return true;
}

#if ! defined SetupPrevModelDialog
	#define SetupPrevModelDialog SetupPreviewModelDialog
#endif

stock HidePlayerDialog(playerid)
{
	if(! IsPlayerConnected(playerid)) return false;

	if(GetPlayerDialogID(playerid) != INVALID_DIALOG_ID)
	{
		if(GetPlayerDialogStyle(playerid) == DIALOG_STYLE_PREVMODEL)
		{
			//hide the base buttons textdraws
		    for(new i; i != 14; i++) TextDrawHideForPlayer(playerid, gButtonsTD[i]);

		    //hide dialog base textdraws
			TextDrawHideForPlayer(playerid, gBackgroundTD);
			TextDrawHideForPlayer(playerid, gContentBoxTD[0]);
			TextDrawHideForPlayer(playerid, gContentBoxTD[1]);

			//destroy dialog page player:textdraw
			PlayerTextDrawHide(playerid, gPlayerPageTD[playerid]);
		    PlayerTextDrawDestroy(playerid, gPlayerPageTD[playerid]);
		    gPlayerPageTD[playerid] = PlayerText:INVALID_TEXT_DRAW;

			//destroy dialog header player:textdraw
		    PlayerTextDrawHide(playerid, gPlayerHeaderTD[playerid]);
		    PlayerTextDrawDestroy(playerid, gPlayerHeaderTD[playerid]);
		    gPlayerHeaderTD[playerid] = PlayerText:INVALID_TEXT_DRAW;

			//destroy dialog buttons player:textdraw
			for(new i; i != 2; i++)
			{
			    PlayerTextDrawHide(playerid, gPlayerButtonsTD[playerid][i]);
			    PlayerTextDrawDestroy(playerid, gPlayerButtonsTD[playerid][i]);
			    gPlayerButtonsTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
			}

			//destroy model player:textdraws
			for(new i; i != MODELS_PER_PAGE; i++)
			{
			    if(gPlayerModelTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
				{
		    		PlayerTextDrawHide(playerid, gPlayerModelTD[playerid][i]);
					PlayerTextDrawDestroy(playerid, gPlayerModelTD[playerid][i]);
					gPlayerModelTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
				}
			}

			Dialog_CancelSelectTextDraw(playerid);
		}
		else
		{
			ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "hide", "hide", "hide", "");
		}
	}
	SetPVarInt(playerid, "Dialog_ID", INVALID_DIALOG_ID);
	SetPVarInt(playerid, "Dialog_TYPE", -1);
	gPlayerDialog[playerid][E_DIALOG_PAGE] = 0;
	gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM] = 0;
 	gPlayerDialog[playerid][E_DIALOG_CLICK_TICK] = 0;
	return true;
}

stock Dialog_Show(playerid, dialogid, style, caption[], info[], button1[], button2[] = "", infosize = sizeof(info))
{
	if(! IsPlayerConnected(playerid)) return false;

	SetPVarInt(playerid, "Dialog_ID", dialogid);
	SetPVarInt(playerid, "Dialog_TYPE", style);
 	gPlayerDialog[playerid][E_DIALOG_CLICK_TICK] = 0;

	if(dialogid == INVALID_DIALOG_ID) return HidePlayerDialog(playerid);

	switch(style)
	{
		case DIALOG_STYLE_PREVMODEL:
		{
			if(infosize > MAX_DIALOG_MODELS)
			{
				print("WARNING: Max dialog models limit reached, please increase \"MAX_DIALOG_MODELS\" to increase the index from <dialogs.inc>.");
				printf("WARNING: Accessing only %i listitems but found %i listitems from array, need an increase of %i.", MAX_DIALOG_MODELS, infosize, (infosize - MAX_DIALOG_MODELS));
				infosize = MAX_DIALOG_MODELS;
			}

			if(infosize > 0)
			{
				for(new i = 0; i < infosize; i++)
				{
					gPlayerList[playerid][i] = info[i];
				}
				gPlayerDialog[playerid][E_DIALOG_PAGE] = 0;
				gPlayerTotalModels[playerid] = infosize;
				gPlayerDialog[playerid][E_DIALOG_SELECTED_ITEM] = 0;

				//Show the dialog base textdraws
                TextDrawShowForPlayer(playerid, gBackgroundTD);
				TextDrawShowForPlayer(playerid, gContentBoxTD[0]);
				TextDrawShowForPlayer(playerid, gContentBoxTD[1]);

				Dialog_Update(playerid, 0);

				//Show the buttons base textdraws
                for(new i = 0; i != 14; i++) TextDrawShowForPlayer(playerid, gButtonsTD[i]);

				//Creating the header player:textdraw
				if(gPlayerHeaderTD[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, gPlayerHeaderTD[playerid]);
				gPlayerHeaderTD[playerid] = Dialog_PlayerTextDrawAdd(playerid, 132.000000, 112.000000, caption, 255, 1, 0.270000, 1.100000, -1, 0, false, true, 0, true, 255, 500.000000, 0.000000);
			    PlayerTextDrawShow(playerid, gPlayerHeaderTD[playerid]);

			    //Creating the button 1 player:textdraw
				if(gPlayerButtonsTD[playerid][0] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, gPlayerButtonsTD[playerid][0]);
				gPlayerButtonsTD[playerid][0] = Dialog_PlayerTextDrawAdd(playerid, 229.000000, 328.000000, button1, 0, 1, 0.269999, 1.299999, -56, 2, false, true, 0);
			    PlayerTextDrawShow(playerid, gPlayerButtonsTD[playerid][0]);

			    //Creating the button 2 player:textdraw
				if(gPlayerButtonsTD[playerid][1] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, gPlayerButtonsTD[playerid][1]);
				gPlayerButtonsTD[playerid][1] = Dialog_PlayerTextDrawAdd(playerid, 313.000000, 328.000000, button2, 0, 1, 0.269999, 1.299999, -56, 2, false, true, 0);
			    PlayerTextDrawShow(playerid, gPlayerButtonsTD[playerid][1]);

				//Creating the page player:textdraw
				new string[10];
				format(string, sizeof(string), "1/%d", Dialog_TotalPages(playerid));
				if(gPlayerPageTD[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, gPlayerPageTD[playerid]);
				gPlayerPageTD[playerid] = Dialog_PlayerTextDrawAdd(playerid, 500.000000, 112.000000, string, 255, 1, 0.270000, 1.100000, -1, 3, false, true);
			    PlayerTextDrawShow(playerid, gPlayerPageTD[playerid]);

				return SelectTextDraw(playerid, gPlayerDialog[playerid][E_MODEL_HOVER_COLOR]);
			}
		}
		default:
		{
		    if(GetPlayerDialogStyle(playerid) == DIALOG_STYLE_PREVMODEL) HidePlayerDialog(playerid);

			return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
		}
	}
	return false;
}

// Hook ShowPlayerDialog now!
#if defined _ALS_ShowPlayerDialog
    #undef ShowPlayerDialog
#else
    #define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog Dialog_Show
//