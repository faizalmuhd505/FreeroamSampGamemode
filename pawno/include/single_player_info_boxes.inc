/*
	Single-Player Info Boxes
	Copyright (C) 2015 Kevin @ Reloaded Zone

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#if defined _spib_included
	#endinput
#endif

#define _spib_included

// ** VARIABLES

// *** PER-PLAYER VARIABLES

// **** TIMERS

static tmInfoBox[MAX_PLAYERS];

// **** TEXTDRAWS

static PlayerText:ptInfoBox[MAX_PLAYERS];

// ** CALLBACKS

public OnPlayerConnect(playerid)
{
	ptInfoBox[playerid] = CreatePlayerTextDraw(playerid, 38.000000, 150.000000, "");
	PlayerTextDrawBackgroundColor(playerid, ptInfoBox[playerid], 255);
	PlayerTextDrawFont(playerid, ptInfoBox[playerid], 1);
	PlayerTextDrawLetterSize(playerid, ptInfoBox[playerid], 0.2, 0.999);
	PlayerTextDrawColor(playerid, ptInfoBox[playerid], -1);
	PlayerTextDrawSetOutline(playerid, ptInfoBox[playerid], 1);
	PlayerTextDrawSetProportional(playerid, ptInfoBox[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ptInfoBox[playerid], 0);
	PlayerTextDrawUseBox(playerid, ptInfoBox[playerid], 1);
	PlayerTextDrawBoxColor(playerid, ptInfoBox[playerid], 255);
	PlayerTextDrawTextSize(playerid, ptInfoBox[playerid], 219.000000, 30.000000);
	PlayerTextDrawSetSelectable(playerid, ptInfoBox[playerid], 0);

	#if defined spib_OnPlayerConnect
		return spib_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect spib_OnPlayerConnect

#if defined spib_OnPlayerConnect
	forward spib_OnPlayerConnect(playerid);
#endif

// ** FUNCTIONS

stock ShowInfoBox(playerid, box_color, shown_for, text[])
{
	PlayerTextDrawBoxColor(playerid, ptInfoBox[playerid], box_color);
	PlayerTextDrawSetString(playerid, ptInfoBox[playerid], text);
	PlayerTextDrawShow(playerid, ptInfoBox[playerid]);

	tmInfoBox[playerid] = SetTimerEx("HideInfoBox", (1000 * shown_for), false, "i", playerid);
	KillTimer(tmInfoBox[playerid]);
	return 1;
}

forward HideInfoBox(playerid);
public HideInfoBox(playerid)
{
	PlayerTextDrawHide(playerid, ptInfoBox[playerid]);
	return 1;
}