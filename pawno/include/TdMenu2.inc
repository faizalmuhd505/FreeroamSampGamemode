
//        - Credits to CrazyBob for Idea -        //


#include a_samp

/*Natives
native CreateTdMenu(menuid,menutitle[],Rows);
native AddTdMenuItem(menuid,row,menutext[],menuprices);
native ShowTdMenu(playerid,menuid);
native HideTdMenu(playerid,menuid);
native DestroyTdMenu(menuid);
*/

#define MAX_TD_MENUS  100
#define MAX_TITLE_LEN 20
#define MAX_ROWS      16 // " no 0" 1 -15 //

enum MInfo
{
bool:UsedMenu,
mRows,
}
new Text:MenuTd0[MAX_TD_MENUS][1];
new Text:MenuTd1[MAX_TD_MENUS][1];
new Text:MenuTd2[MAX_TD_MENUS][1];
new Text:MenuTd3[MAX_TD_MENUS][16];
new Text:MenuTd4[MAX_TD_MENUS][16];
new Text:MenuTd5[MAX_TD_MENUS][1];
new Text:MenuTd6[MAX_TD_MENUS][1];

new TdMenuTimerActive;
new CurrentPlayerMenu[MAX_PLAYERS];
new MenuInfo[MAX_TD_MENUS][MInfo];
new MenuShown[MAX_PLAYERS][MAX_TD_MENUS];
new PlayerDeth[MAX_PLAYERS];
new Menu_Price[MAX_TD_MENUS][MAX_ROWS];
new Menu_Text[MAX_TD_MENUS][MAX_ROWS][700];
new Float:BoxSizeY;
new Float:PressY;

forward OnPlayerTdMenuUsed(playerid,menuid,row);

 

stock CreateTdMenu(menuid,menutitle[],Rows)
{
if(strlen(menutitle) > MAX_TITLE_LEN) return print("[ERROR]:Title Len Must be 20");
if(Rows >= 16) return print("[ERROR]:Max Rows 15"); DestroyTdMenu(menuid);

if(Rows == 1) {BoxSizeY = 11.000018 , PressY = 197.000000;}
if(Rows == 2) {BoxSizeY = 12.100018 , PressY = 207.000000;}
if(Rows == 3) {BoxSizeY = 13.200018 , PressY = 217.000000;}
if(Rows == 4) {BoxSizeY = 14.300019 , PressY = 227.000000;}
if(Rows == 5) {BoxSizeY = 15.400019 , PressY = 237.000000;}
if(Rows == 6) {BoxSizeY = 16.500020 , PressY = 247.000000;}
if(Rows == 7) {BoxSizeY = 17.800022 , PressY = 257.000000;}
if(Rows == 8) {BoxSizeY = 19.000022 , PressY = 268.000000;}
if(Rows == 9) {BoxSizeY = 20.000022 , PressY = 277.000000;}
if(Rows == 10) {BoxSizeY = 21.200023 , PressY = 287.000000;}
if(Rows == 11) {BoxSizeY = 22.300024 , PressY = 297.000000;}
if(Rows == 12) {BoxSizeY = 23.500024 , PressY = 307.000000;}
if(Rows == 13) {BoxSizeY = 24.500024 , PressY = 317.000000;}
if(Rows == 14) {BoxSizeY = 25.500024 , PressY = 327.000000;}
if(Rows == 15) {BoxSizeY = 26.500024 , PressY = 337.000000;}

if(Rows >= 1)
{
MenuTd0[menuid][0]  = TextDrawCreate(21.000000, 112.000000, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0] , 255);
TextDrawFont(MenuTd0[menuid][0] , 1);
TextDrawLetterSize(MenuTd0[menuid][0] , 0.000000, BoxSizeY);
TextDrawColor(MenuTd0[menuid][0] , -1);
TextDrawSetOutline(MenuTd0[menuid][0] , 0);
TextDrawSetProportional(MenuTd0[menuid][0] , 1);
TextDrawSetShadow(MenuTd0[menuid][0] , 1);
TextDrawUseBox(MenuTd0[menuid][0] , 1);
TextDrawBoxColor(MenuTd0[menuid][0] , 118);
TextDrawTextSize(MenuTd0[menuid][0] , 230.000000, 11.000000);
TextDrawSetSelectable(MenuTd0[menuid][0] , 0);

MenuTd1[menuid][0]  = TextDrawCreate(124.000000, 130.000000,menutitle);
TextDrawAlignment(MenuTd1[menuid][0] , 2);
TextDrawBackgroundColor(MenuTd1[menuid][0] , 255);
TextDrawFont(MenuTd1[menuid][0] , 1);
TextDrawLetterSize(MenuTd1[menuid][0] , 0.500000, 1.000000);
TextDrawColor(MenuTd1[menuid][0] , -1);
TextDrawSetOutline(MenuTd1[menuid][0] , 1);
TextDrawSetProportional(MenuTd1[menuid][0] , 1);
TextDrawSetSelectable(MenuTd1[menuid][0] , 0);

MenuTd2[menuid][0]  = TextDrawCreate(123.000000, PressY, "Press ~y~F6 ~b~[T]~w~And Select Number~n~~w~Press ~y~LMB ~w~To Close This Box");
TextDrawAlignment(MenuTd2[menuid][0] , 2);
TextDrawBackgroundColor(MenuTd2[menuid][0] , 255);
TextDrawFont(MenuTd2[menuid][0] , 1);
TextDrawLetterSize(MenuTd2[menuid][0] , 0.209997, 0.799996);
TextDrawColor(MenuTd2[menuid][0] , -1);
TextDrawSetOutline(MenuTd2[menuid][0] , 1);
TextDrawSetProportional(MenuTd2[menuid][0] , 1);
TextDrawSetSelectable(MenuTd2[menuid][0] , 0);

MenuTd5[menuid][0]  = TextDrawCreate(123.000000, 151.000000, "");
TextDrawAlignment(MenuTd5[menuid][0] , 2);
TextDrawBackgroundColor(MenuTd5[menuid][0] , 255);
TextDrawFont(MenuTd5[menuid][0] , 1);
TextDrawLetterSize(MenuTd5[menuid][0] , 0.209998, 0.799996);
TextDrawColor(MenuTd5[menuid][0] , -1);
TextDrawSetOutline(MenuTd5[menuid][0] , 1);
TextDrawSetProportional(MenuTd5[menuid][0] , 1);
TextDrawSetSelectable(MenuTd5[menuid][0] , 0);

MenuTd6[menuid][0]  = TextDrawCreate(121.000000, 162.000000, "");
TextDrawAlignment(MenuTd6[menuid][0] , 2);
TextDrawBackgroundColor(MenuTd6[menuid][0] , 255);
TextDrawFont(MenuTd6[menuid][0] , 1);
TextDrawLetterSize(MenuTd6[menuid][0] , 0.209998, 0.799996);
TextDrawColor(MenuTd6[menuid][0] , -1);
TextDrawSetOutline(MenuTd6[menuid][0] , 1);
TextDrawSetProportional(MenuTd6[menuid][0] , 1);
TextDrawSetSelectable(MenuTd6[menuid][0] , 0);

MenuTd3[menuid][1] = TextDrawCreate(26.000000, 176.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][1], 255);
TextDrawFont(MenuTd3[menuid][1], 1);
TextDrawLetterSize(MenuTd3[menuid][1], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][1], -1);
TextDrawSetOutline(MenuTd3[menuid][1], 1);
TextDrawSetProportional(MenuTd3[menuid][1], 1);
TextDrawSetSelectable(MenuTd3[menuid][1], 0);

MenuTd4[menuid][1] = TextDrawCreate(224.000000, 176.000000, "");
TextDrawAlignment(MenuTd4[menuid][1], 3);
TextDrawBackgroundColor(MenuTd4[menuid][1], 255);
TextDrawFont(MenuTd4[menuid][1], 1);
TextDrawLetterSize(MenuTd4[menuid][1], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][1], -1);
TextDrawSetOutline(MenuTd4[menuid][1], 1);
TextDrawSetProportional(MenuTd4[menuid][1], 1);
TextDrawSetSelectable(MenuTd4[menuid][1], 0);
}
else print("[ERROR]:Min Rows 1"); DestroyTdMenu(menuid);

if(Rows >= 2)
{

MenuTd3[menuid][2] = TextDrawCreate(26.000000, 186.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][2], 255);
TextDrawFont(MenuTd3[menuid][2], 1);
TextDrawLetterSize(MenuTd3[menuid][2], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][2], -1);
TextDrawSetOutline(MenuTd3[menuid][2], 1);
TextDrawSetProportional(MenuTd3[menuid][2], 1);
TextDrawSetSelectable(MenuTd3[menuid][2], 0);

MenuTd4[menuid][2] = TextDrawCreate(224.000000, 186.000000, "");
TextDrawAlignment(MenuTd4[menuid][2], 3);
TextDrawBackgroundColor(MenuTd4[menuid][2], 255);
TextDrawFont(MenuTd4[menuid][2], 1);
TextDrawLetterSize(MenuTd4[menuid][2], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][2], -1);
TextDrawSetOutline(MenuTd4[menuid][2], 1);
TextDrawSetProportional(MenuTd4[menuid][2], 1);
TextDrawSetSelectable(MenuTd4[menuid][2], 0);
}

if(Rows >= 3)
{
MenuTd3[menuid][3] = TextDrawCreate(26.000000, 196.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][3], 255);
TextDrawFont(MenuTd3[menuid][3], 1);
TextDrawLetterSize(MenuTd3[menuid][3], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][3], -1);
TextDrawSetOutline(MenuTd3[menuid][3], 1);
TextDrawSetProportional(MenuTd3[menuid][3], 1);
TextDrawSetSelectable(MenuTd3[menuid][3], 0);

MenuTd4[menuid][3] = TextDrawCreate(224.000000, 196.000000, "");
TextDrawAlignment(MenuTd4[menuid][3], 3);
TextDrawBackgroundColor(MenuTd4[menuid][3], 255);
TextDrawFont(MenuTd4[menuid][3], 1);
TextDrawLetterSize(MenuTd4[menuid][3], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][3], -1);
TextDrawSetOutline(MenuTd4[menuid][3], 1);
TextDrawSetProportional(MenuTd4[menuid][3], 1);
TextDrawSetSelectable(MenuTd4[menuid][3], 0);
}

if(Rows >= 4)
{
MenuTd3[menuid][4] = TextDrawCreate(26.000000, 206.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][4], 255);
TextDrawFont(MenuTd3[menuid][4], 1);
TextDrawLetterSize(MenuTd3[menuid][4], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][4], -1);
TextDrawSetOutline(MenuTd3[menuid][4], 1);
TextDrawSetProportional(MenuTd3[menuid][4], 1);
TextDrawSetSelectable(MenuTd3[menuid][4], 0);

MenuTd4[menuid][4] = TextDrawCreate(224.000000, 206.000000, "");
TextDrawAlignment(MenuTd4[menuid][4], 3);
TextDrawBackgroundColor(MenuTd4[menuid][4], 255);
TextDrawFont(MenuTd4[menuid][4], 1);
TextDrawLetterSize(MenuTd4[menuid][4], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][4], -1);
TextDrawSetOutline(MenuTd4[menuid][4], 1);
TextDrawSetProportional(MenuTd4[menuid][4], 1);
TextDrawSetSelectable(MenuTd4[menuid][4], 0);
}

if(Rows >= 5)
{
MenuTd3[menuid][5] = TextDrawCreate(26.000000, 216.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][5], 255);
TextDrawFont(MenuTd3[menuid][5], 1);
TextDrawLetterSize(MenuTd3[menuid][5], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][5], -1);
TextDrawSetOutline(MenuTd3[menuid][5], 1);
TextDrawSetProportional(MenuTd3[menuid][5], 1);
TextDrawSetSelectable(MenuTd3[menuid][5], 0);

MenuTd4[menuid][5] = TextDrawCreate(224.000000, 216.000000, "");
TextDrawAlignment(MenuTd4[menuid][5], 3);
TextDrawBackgroundColor(MenuTd4[menuid][5], 255);
TextDrawFont(MenuTd4[menuid][5], 1);
TextDrawLetterSize(MenuTd4[menuid][5], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][5], -1);
TextDrawSetOutline(MenuTd4[menuid][5], 1);
TextDrawSetProportional(MenuTd4[menuid][5], 1);
TextDrawSetSelectable(MenuTd4[menuid][5], 0);
}

if(Rows >= 6)
{
MenuTd3[menuid][6] = TextDrawCreate(26.000000, 226.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][6], 255);
TextDrawFont(MenuTd3[menuid][6], 1);
TextDrawLetterSize(MenuTd3[menuid][6], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][6], -1);
TextDrawSetOutline(MenuTd3[menuid][6], 1);
TextDrawSetProportional(MenuTd3[menuid][6], 1);
TextDrawSetSelectable(MenuTd3[menuid][6], 0);

MenuTd4[menuid][6] = TextDrawCreate(224.000000, 226.000000, "");
TextDrawAlignment(MenuTd4[menuid][6], 3);
TextDrawBackgroundColor(MenuTd4[menuid][6], 255);
TextDrawFont(MenuTd4[menuid][6], 1);
TextDrawLetterSize(MenuTd4[menuid][6], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][6], -1);
TextDrawSetOutline(MenuTd4[menuid][6], 1);
TextDrawSetProportional(MenuTd4[menuid][6], 1);
TextDrawSetSelectable(MenuTd4[menuid][6], 0);
}

if(Rows >= 7)
{
MenuTd3[menuid][7] = TextDrawCreate(26.000000, 236.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][7], 255);
TextDrawFont(MenuTd3[menuid][7], 1);
TextDrawLetterSize(MenuTd3[menuid][7], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][7], -1);
TextDrawSetOutline(MenuTd3[menuid][7], 1);
TextDrawSetProportional(MenuTd3[menuid][7], 1);
TextDrawSetSelectable(MenuTd3[menuid][7], 0);

MenuTd4[menuid][7] = TextDrawCreate(224.000000, 236.000000, "");
TextDrawAlignment(MenuTd4[menuid][7], 3);
TextDrawBackgroundColor(MenuTd4[menuid][7], 255);
TextDrawFont(MenuTd4[menuid][7], 1);
TextDrawLetterSize(MenuTd4[menuid][7], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][7], -1);
TextDrawSetOutline(MenuTd4[menuid][7], 1);
TextDrawSetProportional(MenuTd4[menuid][7], 1);
TextDrawSetSelectable(MenuTd4[menuid][7], 0);
}

if(Rows >= 8)
{
MenuTd3[menuid][8] = TextDrawCreate(26.000000, 246.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][8], 255);
TextDrawFont(MenuTd3[menuid][8], 1);
TextDrawLetterSize(MenuTd3[menuid][8], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][8], -1);
TextDrawSetOutline(MenuTd3[menuid][8], 1);
TextDrawSetProportional(MenuTd3[menuid][8], 1);
TextDrawSetSelectable(MenuTd3[menuid][8], 0);

MenuTd4[menuid][8] = TextDrawCreate(224.000000, 246.000000, "");
TextDrawAlignment(MenuTd4[menuid][8], 3);
TextDrawBackgroundColor(MenuTd4[menuid][8], 255);
TextDrawFont(MenuTd4[menuid][8], 1);
TextDrawLetterSize(MenuTd4[menuid][8], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][8], -1);
TextDrawSetOutline(MenuTd4[menuid][8], 1);
TextDrawSetProportional(MenuTd4[menuid][8], 1);
TextDrawSetSelectable(MenuTd4[menuid][8], 0);
}

if(Rows >= 9)
{
MenuTd3[menuid][9] = TextDrawCreate(26.000000, 256.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][9], 255);
TextDrawFont(MenuTd3[menuid][9], 1);
TextDrawLetterSize(MenuTd3[menuid][9], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][9], -1);
TextDrawSetOutline(MenuTd3[menuid][9], 1);
TextDrawSetProportional(MenuTd3[menuid][9], 1);
TextDrawSetSelectable(MenuTd3[menuid][9], 0);

MenuTd4[menuid][9] = TextDrawCreate(224.000000, 256.000000, "");
TextDrawAlignment(MenuTd4[menuid][9], 3);
TextDrawBackgroundColor(MenuTd4[menuid][9], 255);
TextDrawFont(MenuTd4[menuid][9], 1);
TextDrawLetterSize(MenuTd4[menuid][9], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][9], -1);
TextDrawSetOutline(MenuTd4[menuid][9], 1);
TextDrawSetProportional(MenuTd4[menuid][9], 1);
TextDrawSetSelectable(MenuTd4[menuid][9], 0);
}

if(Rows >= 10)
{
MenuTd3[menuid][10] = TextDrawCreate(25.000000, 266.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][10], 255);
TextDrawFont(MenuTd3[menuid][10], 1);
TextDrawLetterSize(MenuTd3[menuid][10], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][10], -1);
TextDrawSetOutline(MenuTd3[menuid][10], 1);
TextDrawSetProportional(MenuTd3[menuid][10], 1);
TextDrawSetSelectable(MenuTd3[menuid][10], 0);

MenuTd4[menuid][10] = TextDrawCreate(224.000000, 266.000000, "");
TextDrawAlignment(MenuTd4[menuid][10], 3);
TextDrawBackgroundColor(MenuTd4[menuid][10], 255);
TextDrawFont(MenuTd4[menuid][10], 1);
TextDrawLetterSize(MenuTd4[menuid][10], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][10], -1);
TextDrawSetOutline(MenuTd4[menuid][10], 1);
TextDrawSetProportional(MenuTd4[menuid][10], 1);
TextDrawSetSelectable(MenuTd4[menuid][10], 0);
}

if(Rows >= 11)
{
MenuTd3[menuid][11] = TextDrawCreate(26.000000, 276.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][11], 255);
TextDrawFont(MenuTd3[menuid][11], 1);
TextDrawLetterSize(MenuTd3[menuid][11], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][11], -1);
TextDrawSetOutline(MenuTd3[menuid][11], 1);
TextDrawSetProportional(MenuTd3[menuid][11], 1);
TextDrawSetSelectable(MenuTd3[menuid][11], 0);

MenuTd4[menuid][11] = TextDrawCreate(224.000000, 276.000000, "");
TextDrawAlignment(MenuTd4[menuid][11], 3);
TextDrawBackgroundColor(MenuTd4[menuid][11], 255);
TextDrawFont(MenuTd4[menuid][11], 1);
TextDrawLetterSize(MenuTd4[menuid][11], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][11], -1);
TextDrawSetOutline(MenuTd4[menuid][11], 1);
TextDrawSetProportional(MenuTd4[menuid][11], 1);
TextDrawSetSelectable(MenuTd4[menuid][11], 0);
}

if(Rows >= 12)
{
MenuTd3[menuid][12] = TextDrawCreate(25.000000, 286.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][12], 255);
TextDrawFont(MenuTd3[menuid][12], 1);
TextDrawLetterSize(MenuTd3[menuid][12], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][12], -1);
TextDrawSetOutline(MenuTd3[menuid][12], 1);
TextDrawSetProportional(MenuTd3[menuid][12], 1);
TextDrawSetSelectable(MenuTd3[menuid][12], 0);

MenuTd4[menuid][12] = TextDrawCreate(224.000000, 286.000000, "");
TextDrawAlignment(MenuTd4[menuid][12], 3);
TextDrawBackgroundColor(MenuTd4[menuid][12], 255);
TextDrawFont(MenuTd4[menuid][12], 1);
TextDrawLetterSize(MenuTd4[menuid][12], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][12], -1);
TextDrawSetOutline(MenuTd4[menuid][12], 1);
TextDrawSetProportional(MenuTd4[menuid][12], 1);
TextDrawSetSelectable(MenuTd4[menuid][12], 0);
}

if(Rows >= 13)
{
MenuTd3[menuid][13] = TextDrawCreate(25.000000, 296.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][13], 255);
TextDrawFont(MenuTd3[menuid][13], 1);
TextDrawLetterSize(MenuTd3[menuid][13], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][13], -1);
TextDrawSetOutline(MenuTd3[menuid][13], 1);
TextDrawSetProportional(MenuTd3[menuid][13], 1);
TextDrawSetSelectable(MenuTd3[menuid][13], 0);

MenuTd4[menuid][13] = TextDrawCreate(224.000000, 296.000000, "");
TextDrawAlignment(MenuTd4[menuid][13], 3);
TextDrawBackgroundColor(MenuTd4[menuid][13], 255);
TextDrawFont(MenuTd4[menuid][13], 1);
TextDrawLetterSize(MenuTd4[menuid][13], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][13], -1);
TextDrawSetOutline(MenuTd4[menuid][13], 1);
TextDrawSetProportional(MenuTd4[menuid][13], 1);
TextDrawSetSelectable(MenuTd4[menuid][13], 0);
}

if(Rows >= 14)
{
MenuTd3[menuid][14] = TextDrawCreate(25.000000, 306.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][14], 255);
TextDrawFont(MenuTd3[menuid][14], 1);
TextDrawLetterSize(MenuTd3[menuid][14], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][14], -1);
TextDrawSetOutline(MenuTd3[menuid][14], 1);
TextDrawSetProportional(MenuTd3[menuid][14], 1);
TextDrawSetSelectable(MenuTd3[menuid][14], 0);

MenuTd4[menuid][14] = TextDrawCreate(224.000000, 306.000000, "");
TextDrawAlignment(MenuTd4[menuid][14], 3);
TextDrawBackgroundColor(MenuTd4[menuid][14], 255);
TextDrawFont(MenuTd4[menuid][14], 1);
TextDrawLetterSize(MenuTd4[menuid][14], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][14], -1);
TextDrawSetOutline(MenuTd4[menuid][14], 1);
TextDrawSetProportional(MenuTd4[menuid][14], 1);
TextDrawSetSelectable(MenuTd4[menuid][14], 0);
}

if(Rows >= 15)
{
MenuTd3[menuid][15] = TextDrawCreate(25.000000, 316.000000, "");
TextDrawBackgroundColor(MenuTd3[menuid][15], 255);
TextDrawFont(MenuTd3[menuid][15], 1);
TextDrawLetterSize(MenuTd3[menuid][15], 0.209996, 0.799996);
TextDrawColor(MenuTd3[menuid][15], -1);
TextDrawSetOutline(MenuTd3[menuid][15], 1);
TextDrawSetProportional(MenuTd3[menuid][15], 1);
TextDrawSetSelectable(MenuTd3[menuid][15], 0);

MenuTd4[menuid][15] = TextDrawCreate(224.000000, 316.000000, "");
TextDrawAlignment(MenuTd4[menuid][15], 3);
TextDrawBackgroundColor(MenuTd4[menuid][15], 255);
TextDrawFont(MenuTd4[menuid][15], 1);
TextDrawLetterSize(MenuTd4[menuid][15], 0.209996, 0.799996);
TextDrawColor(MenuTd4[menuid][15], -1);
TextDrawSetOutline(MenuTd4[menuid][15], 1);
TextDrawSetProportional(MenuTd4[menuid][15], 1);
TextDrawSetSelectable(MenuTd4[menuid][15], 0);
}
MenuInfo[menuid][mRows] = Rows;
MenuInfo[menuid][UsedMenu] = true;
if(TdMenuTimerActive != 1)
{
SetTimer("TdMenuTimer",50,1);
TdMenuTimerActive = 1;
}
printf("[TdMenu]: Menu %d Created",menuid);
return 1;
}

stock CreateTdMenuInPut(menuid,menutitle[])
{
//if(strlen(menutitle) > MAX_TITLE_LEN+3) return print("[ERROR]:Title Len Must be 20");

MenuTd0[menuid][0] = TextDrawCreate(21.000000, 112.000000, "____________");
TextDrawBackgroundColor(MenuTd0[menuid][0], 255);
TextDrawFont(MenuTd0[menuid][0], 1);
TextDrawLetterSize(MenuTd0[menuid][0], 0.000000, 9.400020);
TextDrawColor(MenuTd0[menuid][0], -1);
TextDrawSetOutline(MenuTd0[menuid][0], 0);
TextDrawSetProportional(MenuTd0[menuid][0], 1);
TextDrawSetShadow(MenuTd0[menuid][0], 1);
TextDrawUseBox(MenuTd0[menuid][0], 1);
TextDrawBoxColor(MenuTd0[menuid][0], 118);
TextDrawTextSize(MenuTd0[menuid][0], 230.000000, 11.000000);
TextDrawSetSelectable(MenuTd0[menuid][0], 0);

MenuTd1[menuid][0] = TextDrawCreate(124.000000, 130.000000, menutitle);
TextDrawAlignment(MenuTd1[menuid][0], 2);
TextDrawBackgroundColor(MenuTd1[menuid][0], 255);
TextDrawFont(MenuTd1[menuid][0], 1);
TextDrawLetterSize(MenuTd1[menuid][0], 0.500000, 1.000000);
TextDrawColor(MenuTd1[menuid][0], -1);
TextDrawSetOutline(MenuTd1[menuid][0], 1);
TextDrawSetProportional(MenuTd1[menuid][0], 1);
TextDrawSetSelectable(MenuTd1[menuid][0], 0);

MenuTd2[menuid][0] = TextDrawCreate(123.000000, 183.000000, "Prees ~y~F6 ~b~[T]~w~And Select Number~n~~w~Press ~y~LMB ~w~To Exit");
TextDrawAlignment(MenuTd2[menuid][0], 2);
TextDrawBackgroundColor(MenuTd2[menuid][0], 255);
TextDrawFont(MenuTd2[menuid][0], 1);
TextDrawLetterSize(MenuTd2[menuid][0], 0.209996, 0.799996);
TextDrawColor(MenuTd2[menuid][0], -1);
TextDrawSetOutline(MenuTd2[menuid][0], 1);
TextDrawSetProportional(MenuTd2[menuid][0], 1);
TextDrawSetSelectable(MenuTd2[menuid][0], 0);

MenuTd5[menuid][0] = TextDrawCreate(123.000000, 151.000000, "");
TextDrawAlignment(MenuTd5[menuid][0], 2);
TextDrawBackgroundColor(MenuTd5[menuid][0], 255);
TextDrawFont(MenuTd5[menuid][0], 1);
TextDrawLetterSize(MenuTd5[menuid][0], 0.209998, 0.799996);
TextDrawColor(MenuTd5[menuid][0], -1);
TextDrawSetOutline(MenuTd5[menuid][0], 1);
TextDrawSetProportional(MenuTd5[menuid][0], 1);
TextDrawSetSelectable(MenuTd5[menuid][0], 0);

MenuTd6[menuid][0] = TextDrawCreate(121.000000, 162.000000, "");
TextDrawAlignment(MenuTd6[menuid][0], 2);
TextDrawBackgroundColor(MenuTd6[menuid][0], 255);
TextDrawFont(MenuTd6[menuid][0], 1);
TextDrawLetterSize(MenuTd6[menuid][0], 0.209997, 0.799996);
TextDrawColor(MenuTd6[menuid][0], -1);
TextDrawSetOutline(MenuTd6[menuid][0], 1);
TextDrawSetProportional(MenuTd6[menuid][0], 1);
TextDrawSetSelectable(MenuTd6[menuid][0], 0);
MenuInfo[menuid][UsedMenu] = true;
MenuInfo[menuid][mRows] = 0;
if(TdMenuTimerActive != 1)
{
SetTimer("TdMenuTimer",50,1);
TdMenuTimerActive = 1;
}
printf("[TdMenu]: Menu %d Created",menuid);
return 1;
}
stock AddTdMenuInfoRowText(menuid,row,Infotext[])
{
if(MenuInfo[menuid][UsedMenu] == true)
{

if(row == 1)
{
TextDrawSetString(MenuTd5[menuid][0],Infotext);
}

if(row == 2)
{
TextDrawSetString(MenuTd6[menuid][0],Infotext);
}

}
}

stock AddTdMenuItem(menuid,row,menutext[],Itemprices = 0)
{
if(MenuInfo[menuid][UsedMenu] == true)
{
if(Itemprices > 0)
{
Menu_Price[menuid][row] = Itemprices;
if(row > MenuInfo[menuid][mRows]) return 1;
if(row == 1)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~1 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][1],Str1);
TextDrawSetString(MenuTd4[menuid][1],Str);
Menu_Text[menuid][row] = Str1;
}
if(row == 2)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~2 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][2],Str1);
TextDrawSetString(MenuTd4[menuid][2],Str);
}
if(row == 3)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~3 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][3],Str1);
TextDrawSetString(MenuTd4[menuid][3],Str);
}
if(row == 4)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~4 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][4],Str1);
TextDrawSetString(MenuTd4[menuid][4],Str);
}
if(row == 5)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~5 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][5],Str1);
TextDrawSetString(MenuTd4[menuid][5],Str);
}
if(row == 6)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~6 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][6],Str1);
TextDrawSetString(MenuTd4[menuid][6],Str);
}
if(row == 7)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~7 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][7],Str1);
TextDrawSetString(MenuTd4[menuid][7],Str);
}
if(row == 8)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~8 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][8],Str1);
TextDrawSetString(MenuTd4[menuid][8],Str);
}
if(row == 9)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~9 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][9],Str1);
TextDrawSetString(MenuTd4[menuid][9],Str);
}
if(row == 10)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~10 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][10],Str1);
TextDrawSetString(MenuTd4[menuid][10],Str);
}
if(row == 11)
{
new Str[512];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~11 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][11],Str1);
TextDrawSetString(MenuTd4[menuid][11],Str);
}
if(row == 12)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~12 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][12],Str1);
TextDrawSetString(MenuTd4[menuid][12],Str);
}
if(row == 13)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~13 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][13],Str1);
TextDrawSetString(MenuTd4[menuid][13],Str);
}
if(row == 14)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~14 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][14],Str1);
TextDrawSetString(MenuTd4[menuid][14],Str);
}
if(row == 15)
{
new Str[256];
format(Str,sizeof(Str),"~g~$%d",Itemprices);
new Str1[700];
format(Str1,sizeof(Str1),"~y~15 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][15],Str1);
TextDrawSetString(MenuTd4[menuid][15],Str);
}
}
else
{
if(row == 1)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~1 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][1],Str1);
TextDrawSetString(MenuTd4[menuid][1],"");
}
if(row == 2)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~2 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][2],Str1);
TextDrawSetString(MenuTd4[menuid][2],"");
}
if(row == 3)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~3 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][3],Str1);
TextDrawSetString(MenuTd4[menuid][3],"");
}
if(row == 4)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~4 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][4],Str1);
TextDrawSetString(MenuTd4[menuid][4],"");
}
if(row == 5)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~5 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][5],Str1);
TextDrawSetString(MenuTd4[menuid][5],"");
}
if(row == 6)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~6 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][6],Str1);
TextDrawSetString(MenuTd4[menuid][6],"");
}
if(row == 7)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~7 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][7],Str1);
TextDrawSetString(MenuTd4[menuid][7],"");
}
if(row == 8)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~8 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][8],Str1);
TextDrawSetString(MenuTd4[menuid][8],"");
}
if(row == 9)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~9 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][9],Str1);
TextDrawSetString(MenuTd4[menuid][9],"");
}
if(row == 10)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~10 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][10],Str1);
TextDrawSetString(MenuTd4[menuid][10],"");
}
if(row == 11)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~11 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][11],Str1);
TextDrawSetString(MenuTd4[menuid][11],"");
}
if(row == 12)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~12 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][12],Str1);
TextDrawSetString(MenuTd4[menuid][12],"");
}
if(row == 13)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~13 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][13],Str1);
TextDrawSetString(MenuTd4[menuid][13],"");
}
if(row == 14)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~14 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][14],Str1);
TextDrawSetString(MenuTd4[menuid][14],"");
}
if(row == 15)
{
new Str1[700];
format(Str1,sizeof(Str1),"~y~15 ~w~ - %s",menutext);
TextDrawSetString(MenuTd3[menuid][15],Str1);
TextDrawSetString(MenuTd4[menuid][15],"");
}
}
new Str_1[700];
format(Str_1,sizeof(Str_1),"%s",menutext);
Menu_Text[menuid][row] = Str_1;
}
return 1;
}

stock GetItemPrice(playerid,menuid,row)
{
if(Menu_Price[menuid][row] == 0)
{
new _str_[256];
format(_str_,sizeof(_str_),"~y~%d ~w~ - %s",row,Menu_Text[menuid][row]);
TextDrawSetString(MenuTd3[menuid][row],_str_);

TextDrawSetString(MenuTd4[menuid][row]," ");
return 1;
}

if(Menu_Price[menuid][row] > GetPlayerMoney(playerid))
{
new _str_[256];
format(_str_,sizeof(_str_),"~y~%d ~w~ - ~r~%s",row,Menu_Text[menuid][row]);
TextDrawSetString(MenuTd3[menuid][row],_str_);

format(_str_,sizeof(_str_),"~r~$%d",Menu_Price[menuid][row]);
TextDrawSetString(MenuTd4[menuid][row],_str_);
}
else if(Menu_Price[menuid][row] < GetPlayerMoney(playerid))
{
new _str_[256];
format(_str_,sizeof(_str_),"~y~%d ~w~ - %s",row,Menu_Text[menuid][row]);
TextDrawSetString(MenuTd3[menuid][row],_str_);

format(_str_,sizeof(_str_),"~g~$%d",Menu_Price[menuid][row]);
TextDrawSetString(MenuTd4[menuid][row],_str_);
}
return 1;
}

stock ShowTdMenu(playerid,menuid)
{
if(IsPlayerConnected(playerid))
{
for(new m;m<MAX_TD_MENUS;m++)
{
if(MenuShown[playerid][m] == 1)
{
TextDrawHideForPlayer(playerid,MenuTd0[m][0]);
TextDrawHideForPlayer(playerid,MenuTd1[m][0]);
TextDrawHideForPlayer(playerid,MenuTd2[m][0]);
TextDrawHideForPlayer(playerid,MenuTd5[m][0]);
TextDrawHideForPlayer(playerid,MenuTd6[m][0]);
for(new m11;m11<16;m11++)
{
TextDrawHideForPlayer(playerid,MenuTd3[m][m11]);
TextDrawHideForPlayer(playerid,MenuTd4[m][m11]);
}
MenuShown[playerid][m] = false;
}
}

switch(MenuInfo[menuid][mRows])
{
case 0:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
}
case 1:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
GetItemPrice(playerid,menuid,1);
}
case 2:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
}
case 3:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
}
case 4:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
}
case 5:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
}
case 6:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
}
case 7:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
GetItemPrice(playerid,menuid,7);
}
case 8:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
GetItemPrice(playerid,menuid,7);
GetItemPrice(playerid,menuid,8);
}
case 9:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
GetItemPrice(playerid,menuid,7);
GetItemPrice(playerid,menuid,8);
GetItemPrice(playerid,menuid,9);
}
case 10:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
GetItemPrice(playerid,menuid,7);
GetItemPrice(playerid,menuid,8);
GetItemPrice(playerid,menuid,9);
GetItemPrice(playerid,menuid,10);
}
case 11:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
GetItemPrice(playerid,menuid,7);
GetItemPrice(playerid,menuid,8);
GetItemPrice(playerid,menuid,9);
GetItemPrice(playerid,menuid,10);
GetItemPrice(playerid,menuid,11);
}
case 12:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][12]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
GetItemPrice(playerid,menuid,7);
GetItemPrice(playerid,menuid,8);
GetItemPrice(playerid,menuid,9);
GetItemPrice(playerid,menuid,10);
GetItemPrice(playerid,menuid,11);
GetItemPrice(playerid,menuid,12);
}
case 13:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][13]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
GetItemPrice(playerid,menuid,7);
GetItemPrice(playerid,menuid,8);
GetItemPrice(playerid,menuid,9);
GetItemPrice(playerid,menuid,10);
GetItemPrice(playerid,menuid,11);
GetItemPrice(playerid,menuid,12);
GetItemPrice(playerid,menuid,13);
}
case 14:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][14]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][14]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
GetItemPrice(playerid,menuid,7);
GetItemPrice(playerid,menuid,8);
GetItemPrice(playerid,menuid,9);
GetItemPrice(playerid,menuid,10);
GetItemPrice(playerid,menuid,11);
GetItemPrice(playerid,menuid,12);
GetItemPrice(playerid,menuid,13);
GetItemPrice(playerid,menuid,14);
}
case 15:
{
TextDrawShowForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd6[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][1]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][2]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][3]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][4]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][5]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][6]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][7]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][8]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][9]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][10]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][11]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][12]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][13]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][14]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][14]);
TextDrawShowForPlayer(playerid,MenuTd3[menuid][15]);
TextDrawShowForPlayer(playerid,MenuTd4[menuid][15]);
GetItemPrice(playerid,menuid,1);
GetItemPrice(playerid,menuid,2);
GetItemPrice(playerid,menuid,3);
GetItemPrice(playerid,menuid,4);
GetItemPrice(playerid,menuid,5);
GetItemPrice(playerid,menuid,6);
GetItemPrice(playerid,menuid,7);
GetItemPrice(playerid,menuid,8);
GetItemPrice(playerid,menuid,9);
GetItemPrice(playerid,menuid,10);
GetItemPrice(playerid,menuid,11);
GetItemPrice(playerid,menuid,12);
GetItemPrice(playerid,menuid,13);
GetItemPrice(playerid,menuid,14);
GetItemPrice(playerid,menuid,15);
}
}
MenuShown[playerid][menuid] = true;
CurrentPlayerMenu[playerid] = menuid;
}
}
stock HideCurrentTdMenu(playerid)
{ 
new menuid = CurrentPlayerMenu[playerid];
if(MenuShown[playerid][menuid] == 1)
{
TextDrawHideForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd6[menuid][0]);
for(new m;m<16;m++)
{
TextDrawHideForPlayer(playerid,MenuTd3[menuid][m]);
TextDrawHideForPlayer(playerid,MenuTd4[menuid][m]);
}
MenuShown[playerid][menuid] = false;
CurrentPlayerMenu[playerid] = -1;
}
}
stock HideTdMenu(playerid,menuid)
{
if(MenuShown[playerid][menuid] == 1)
{
TextDrawHideForPlayer(playerid,MenuTd0[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd1[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd2[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd5[menuid][0]);
TextDrawHideForPlayer(playerid,MenuTd6[menuid][0]);
for(new m;m<16;m++)
{
TextDrawHideForPlayer(playerid,MenuTd3[menuid][m]);
TextDrawHideForPlayer(playerid,MenuTd4[menuid][m]);
}
MenuShown[playerid][menuid] = false;
CurrentPlayerMenu[playerid] = -1;
}
}
stock DestroyTdMenu(menuid)
{
if(MenuInfo[menuid][UsedMenu] == true)
{
for(new i;i<MAX_PLAYERS;i++)
{
TextDrawHideForPlayer(i,MenuTd0[menuid][0]);
TextDrawHideForPlayer(i,MenuTd1[menuid][0]);
TextDrawHideForPlayer(i,MenuTd2[menuid][0]);
TextDrawHideForPlayer(i,MenuTd5[menuid][0]);
TextDrawHideForPlayer(i,MenuTd6[menuid][0]);
for(new mi;mi<16;mi++)
{
TextDrawHideForPlayer(i,MenuTd3[menuid][mi]);
TextDrawHideForPlayer(i,MenuTd4[menuid][mi]);
}
}
}
}
#define TEXT:(%1,%2) if(MenuInfo[CurrentPlayerMenu[playerid]][mRows] == %2) if(strcmp(#%1, text, true, 10) == 0)
forward Menu(mid,playerid,value[]); 

stock GetPlayerTdMenu(playerid)
{
if(MenuShown[playerid][CurrentPlayerMenu[playerid]] == 0) return 1;
return CurrentPlayerMenu[playerid];
}

IsNumeric(const string[])
{
	for (new i = 0, j = strlen(string); i < j; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}

public OnPlayerText(playerid, text[])
{
new tex = strval(text);
if(MenuShown[playerid][CurrentPlayerMenu[playerid]] == 1) 
{
if(MenuInfo[CurrentPlayerMenu[playerid]][mRows] == 0)
{
CallLocalFunction("Menu", "iis", CurrentPlayerMenu[playerid],playerid, text);
}
else
{
if(IsNumeric(text))
{
CallLocalFunction("OnPlayerTdMenuUsed", "iii", playerid, CurrentPlayerMenu[playerid],tex);
}
}
return 0;
}
if (funcidx("m_OnPlayerText") != -1) return CallLocalFunction("m_OnPlayerText", "is", playerid, text);
return 1;
}

#if defined _ALS_OnPlayerText
    #undef OnPlayerText
#else
    #define _ALS_OnPlayerText
#endif
#define OnPlayerText m_OnPlayerText
forward m_OnPlayerText(playerid, text[]);

forward	TdMenuTimer();

public TdMenuTimer()
{
	for(new i;i<MAX_PLAYERS;i++)
	{
	new keys, updown, leftright;
	GetPlayerKeys(i, keys, updown, leftright);
	if(keys == KEY_FIRE)
	{
	HideTdMenu(i,CurrentPlayerMenu[i]);
	}
	if(!IsPlayerConnected(i))
	{
	HideTdMenu(i,CurrentPlayerMenu[i]);
	}
	if(PlayerDeth[i] == 1)
	{
	HideTdMenu(i,CurrentPlayerMenu[i]);
	}
	}
}
/*
stock isNumeric(const string[])
{
  new length=strlen(string);
  if (length==0) return false;
  for (new i = 0; i < length; i++)
    {
      if (
            (string[i] > '9' || string[i] < '0' && string[i]!='-' && string[i]!='+') // Not a number,'+' or '-'
             || (string[i]=='-' && i!=0)                                             // A '-' but not at first.
             || (string[i]=='+' && i!=0)                                             // A '+' but not at first.
         ) return false;
    }
  if (length==1 && (string[0]=='-' || string[0]=='+')) return false;
  return true;
}

stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}
*/
