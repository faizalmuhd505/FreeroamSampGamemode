/*
 * 
 *     include
 *     ZadMinO_K
 * 
 */

#if defined _ZAdminO5_included
	#endinput
#endif
#define _ZAdminO5_included

//===( include )===//
#include <a_samp>
#include <zDini>
#include <sscanf2>
#include <streamer>
//===( define )===//
#define CarpetaCuentas        "ZadminO5/Usuarios/%s.sav"
#define crearteles            "ZadminO5/Config/CreadorCmdsTeles.ini"
#define ConfigCuentas         "ZadminO5/Config/Config.cfg"
#define rRaceCuentas          "ZadminO5/Carreras/%s.RRACE"
#define rRaceCuentas2         "ZadminO5/Carreras/NombresCarreras/NombresCarreras.txt"
#define AkaCuentas            "ZadminO5/Config/aka.txt"
#define antibots              "ZadminO5/Config/AntiBots.txt"
#define antinombrecrash       "ZadminO5/Config/AntiNombreCrashLog.txt"
#define antinombrespam        "ZadminO5/Config/AntiNombreSpamLog.txt"
#define reporteslog           "ZadminO5/Config/Reportes.txt"
#define nombreprohividolog    "ZadminO5/Config/NombresProhividos.cfg"
#define kicklogs              "ZadminO5/Logs/Kickeados.ini"
#define banlogs               "ZadminO5/Logs/Baneados.ini"
#define cmdlogs               "ZadminO5/Logs/Comandos.ini"
#define chatlogs              "ZadminO5/Logs/Chat.ini"
#define chatadminlogs         "ZadminO5/Logs/ChatAdmin.ini"
#define chatviplogs           "ZadminO5/Logs/ChatVip.ini"
#define ZAV                   "5"
#define noadmins              800
#define novips                801
#define Comando(%1,%2,%3) if ((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (Comando_%1(playerid, "")))||(((%3)[(%2) + 1] == 32) && (Comando_%1(playerid, (%3)[(%2) + 2]))))) return 1
#define ZComando(%1,%2,%3) if(strcmp(%2,%1,%3)== 0)
#define DATABASENAME	"IpToCountry.db.db"
new Text:Textdraw0;
#if !defined IGNORE_VEHICLE_DELETION
new bool:gDialogCreated[ MAX_VEHICLES ] = { false, ... };
#endif
//===( forward )===//
forward AdminChat(color,const string[]);
forward VipChat(color,const string[]);
forward tvdios(playerid);
forward KickLog(string[]);
forward BanLog(string[]);
forward CmdLog(string[]);
forward ChatLog(string[]);
forward ChatAdminLog(string[]);
forward ChatVipLog(string[]);
forward AntiBotsLog(string[]);
forward AntiNombreCrashLog(string[]);
forward AntiNombreSpamLog(string[]);
forward ReportesLog(string[]);
forward ShowInformationTxt(playerid);
forward VolverCarcel(playerid);
forward Liberar(playerid);
forward PrintAdvertencia(const string[]);
forward CreadorDeTeleCompletos(string[]);
forward AutoKick(playerid);
forward JugadoresConectados();
forward JugadoresEnVehiculo();
forward JugadoresEnCarcel();
forward JugadoresCongelados();
forward JugadoresSilenciados();
forward JugadoresBloqueados();
forward AdministradoresConectados();
forward VipsConectados();
forward Conteo4();
forward Conteo3();
forward Conteo2();
forward Conteo1();
forward ConteoYa();
static bool:OnFly[MAX_PLAYERS];
forward bool:ActivarModoVolador(playerid);
forward Fly(playerid);
forward bool:DesactivarModoVolador(playerid);
forward static SetPlayerLookAt(playerid,Float:x,Float:y);
forward ActivarModoVoladorTodos();
forward DesactivarModoVoladorTodos();
//==============================================================================
IsInvalidSkin(skinid)
{
#define MAX_BAD_SKINS 22
new InSkin[MAX_BAD_SKINS] = {
0, 3, 4, 5, 6, 8, 42, 65, 74, 86,
119, 149, 208, 273, 289};
for (new i = 0; i < MAX_BAD_SKINS; i++) {
if (skinid == InSkin[i]) return true;
}
return 0;
}
//==============================================================================
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
//==============================================================================
stock strrest(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}
	new offset = index;
	new result[128];
	while ((index < length) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}
//==============================================================================
stock TeleportPlayer(playerid, Float:x,Float:y,Float:z)
{
	new cartype = GetPlayerVehicleID(playerid);
	new State=GetPlayerState(playerid);
	if(State!=PLAYER_STATE_DRIVER)
	{
		SetPlayerPos(playerid,x,y,z);
	}
	else if(IsPlayerInVehicle(playerid, cartype) == 1)
	{
		SetVehiclePos(cartype,x,y,z);
	}
	else
	{
		SetPlayerPos(playerid,x,y,z);
	}
}
//==============================================================================
stock IsNumeric(string[])
{
	for(new i = 0; i < strlen(string); i++) if(string[i] > '9' || string[i] < '0') return false;
	return true;
}
//==============================================================================
stock ServerNombre()
{
new gString[256];
GetServerVarAsString("hostname", gString, sizeof(gString));
return gString;
}
//==============================================================================
stock VozFantasma(const Voz[]) {
for(new i = 0; i < MAX_PLAYERS; i++) {
new Str[256];
format(Str, sizeof(Str), "http://audio1.spanishdict.com/audio?lang=es&voice=Ximena&speed=25&text=%s", Voz);
PlayAudioStreamForPlayer(i, Str, 0, 0, 0, 0, 0); }
return 1; }
//==============================================================================
CreatePlayerVehicle( playerid, modelid )
{
	new
	    vehicle,
		Float:x,
		Float:y,
		Float:z,
		Float:angle;

	if ( GetPlayerState( playerid ) == PLAYER_STATE_DRIVER )
	{
	    vehicle = GetPlayerVehicleID( playerid );
	    GetVehiclePos( vehicle, x, y, z );
	    GetVehicleZAngle( vehicle, angle );
	    DestroyVehicle( vehicle );
	}
	else
	{
		GetPlayerPos( playerid, x, y, z );
		GetPlayerFacingAngle( playerid, angle );
	}
	vehicle = CreateVehicle( modelid, x, y, ( z + 1 ), angle, -1, -1,-1 );
	LinkVehicleToInterior( vehicle, GetPlayerInterior( playerid ) );
	#if !defined IGNORE_VIRTUAL_WORLDS
		SetVehicleVirtualWorld( vehicle, GetPlayerVirtualWorld( playerid ) );
	#endif
	#if !defined IGNORE_WARP_INTO_VEHICLE
		PutPlayerInVehicle( playerid, vehicle, 0 );
	#endif
	#if !defined IGNORE_VEHICLE_DELETION
		gDialogCreated[ vehicle ] = true;
	#endif
	return 1;
}
//==============================================================================
CrearVehiculo(playerid,modelid,color1,color2)
{
	new
	    vehicle,
		Float:x,
		Float:y,
		Float:z,
		Float:angle;

	if ( GetPlayerState( playerid ) == PLAYER_STATE_DRIVER )
	{
	    vehicle = GetPlayerVehicleID( playerid );
	    GetVehiclePos( vehicle, x, y, z );
	    GetVehicleZAngle( vehicle, angle );
	    DestroyVehicle( vehicle );
	}
	else
	{
		GetPlayerPos( playerid, x, y, z );
		GetPlayerFacingAngle( playerid, angle );
	}
	vehicle = CreateVehicle( modelid, x, y, ( z + 1 ), angle, color1, color2, -1 );
	LinkVehicleToInterior( vehicle, GetPlayerInterior( playerid ) ); AddVehicleComponent(vehicle,1073);
	#if !defined IGNORE_VIRTUAL_WORLDS
		SetVehicleVirtualWorld( vehicle, GetPlayerVirtualWorld( playerid ) );
	#endif
	#if !defined IGNORE_WARP_INTO_VEHICLE
		PutPlayerInVehicle( playerid, vehicle, 0 );
	#endif
	#if !defined IGNORE_VEHICLE_DELETION
		gDialogCreated[ vehicle ] = true;
	#endif
	return 1;
}
//==============================================================================
stock NickSpam(SPAM[])
{
new SSPAM;
new CUENTAP,CUENTAN,CUENTAGB;
for(SSPAM = 0; SSPAM < strlen(SPAM); SSPAM ++)
{
if(SPAM[SSPAM] == '.') CUENTAP ++;
if(SPAM[SSPAM] == '0' || SPAM[SSPAM] == '1' || SPAM[SSPAM] == '2' || SPAM[SSPAM] == '3' || SPAM[SSPAM] == '4' || SPAM[SSPAM] == '5' || SPAM[SSPAM] == '6' || SPAM[SSPAM] == '7' || SPAM[SSPAM] == '8' || SPAM[SSPAM] == '9') CUENTAN ++; //Cuenta los Numeros
if(SPAM[SSPAM] == '_') CUENTAGB ++;
}
if(CUENTAP >= 3 && CUENTAN >= 7) return 1;
if(CUENTAGB >= 1 && CUENTAN >= 7) return 1;
if((strfind(SPAM, ".com", true) != -1 || strfind(SPAM, ".com.ar", true) != -1 || strfind(SPAM, ".org", true) != -1 || strfind(SPAM, ".net", true) != -1 || strfind(SPAM, ".es", true) != -1 || strfind(SPAM, ".tk", true) != -1) && CUENTAN >= 4 ) return 1;
return 0;
}
//==============================================================================
stock GetNumberOfPlayersOnThisIP(test_ip[])
{
	new against_ip[32+1];
	new x = 0;
	new ip_count = 0;
	for(x=0; x<MAX_PLAYERS; x++) {
		if(IsPlayerConnected(x)) {
		    GetPlayerIp(x,against_ip,32);
		    if(!strcmp(against_ip,test_ip)) ip_count++;
		}
	}
	return ip_count;
}
//////////////////////
stock CambioNombre(nickname[],newnick[]) {
new oldfname[256];
new newfname[256];
format(oldfname,sizeof(oldfname),CarpetaCuentas,nickname);
format(newfname,sizeof(newfname),CarpetaCuentas,newnick);
return frenametextfile(oldfname,newfname);
}
stock frenametextfile(oldname[],newname[]) {
    if (!fexist(oldname)) return false;
    fremove(newname);
    if (!fcopytextfile(oldname,newname)) return false;
    fremove(oldname);
    return true;
}
stock fcopytextfile(oldname[],newname[]) {
	new File:ohnd,File:nhnd;
	if (!fexist(oldname)) return false;
	ohnd=fopen(oldname,io_read);
	nhnd=fopen(newname,io_write);
	new tmpres[256];
	while (fread(ohnd,tmpres)) {
		StripNewLine(tmpres);
		format(tmpres,sizeof(tmpres),"%s\r\n",tmpres);
		fwrite(nhnd,tmpres);
	}
	fclose(ohnd);
	fclose(nhnd);
	return true;
}
stock StripNewLine(str2[])
{
	new len = strlen(str2);
	if (str2[0]==0) return ;
	if ((str2[len - 1] == '\n') || (str2[len - 1] == '\r')) {
		str2[len - 1] = 0;
		if (str2[0]==0) return ;
		if ((str2[len - 2] == '\n') || (str2[len - 2] == '\r')) str2[len - 2] = 0;
	}
}
// funciones el español
stock DarPuntaje(playerid,puntaje) { return SetPlayerScore(playerid,puntaje+GetPlayerScore(playerid)); }
stock DarDinero(playerid,dinero) { return GivePlayerMoney(playerid,dinero); }
//////////////////////
stock IpToCountry_db(IpInfo[])
{
	new
		DB:database,
		DBResult:result,
		query[256];
	
	database = db_open(DATABASENAME);
	if(database)
	{
		if(strcmp("127.0.0.1", IpInfo, true) == 0)
		{
			query = "Localhost";
		} else {
			new
				IPsplit[4][10];
			if(sscanf(IpInfo, "p<.>s[10]s[10]s[10]s[10]", IPsplit[0], IPsplit[1], IPsplit[2], IPsplit[3])) { query = "Invalida IP"; }
			else {
				format(query, sizeof query, "\
				SELECT `Country`\
				FROM `countrydetected`\
				WHERE `Ip_From` <= ((16777216*%d) + (65536*%d) + (256*%d) + %d)\
				AND `Ip_to` >= ((16777216*%d) + (65536*%d) + (256*%d) + %d) LIMIT 1",
				strval(IPsplit[0]), strval(IPsplit[1]), strval(IPsplit[2]), strval(IPsplit[3]),
				strval(IPsplit[0]), strval(IPsplit[1]), strval(IPsplit[2]), strval(IPsplit[3]));
				
				result = db_query(database, query);
				if(!db_get_field_assoc(result, "Country", query, sizeof query))
				{
					query = "Desconocido";
				}
				db_free_result(result);
			}
		}
		db_close(database);
	} else query = "Failed. Not Open "DATABASENAME"";
	return query;
}
//////////////////////////////////////////////////////////////////////////////
stock IsValidWeapon(weaponid)
{
    if (weaponid > 0 && weaponid < 19 || weaponid > 21 && weaponid < 47) return 1;
    return 0;
}
////////////////////
public ActivarModoVoladorTodos()
{
for(new i = 0; i < MAX_PLAYERS; i++) if(IsPlayerConnected(i)) ActivarModoVolador(i);
return 1;
}
public DesactivarModoVoladorTodos()
{
for(new i = 0; i < MAX_PLAYERS; i++) if(IsPlayerConnected(i)) DesactivarModoVolador(i);
return 1;
}


bool:ActivarModoVolador(playerid)
{
	if(OnFly[playerid])
        return false;
    OnFly[playerid] = true;
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid,x,y,z);
	SetPlayerPos(playerid,x,y,z+5.0);
	ApplyAnimation(playerid,"PARACHUTE","PARA_steerR",6.1,1,1,1,1,0,1);
	Fly(playerid);
	GameTextForPlayer(playerid,"~y~Modo Vuelo~n~~r~Clic Izq ~w~- Subes~n~~r~Clic Derecho ~w~- Bajas~n~ ~r~Espacio ~w~- Rapido~n~~r~Alt Izq ~w~- Lento",10000,3);
	return true;
}

public Fly(playerid) {
	if(!IsPlayerConnected(playerid)) return 1; new k, ud,lr; GetPlayerKeys(playerid,k,ud,lr);
	new Float:v_x,Float:v_y,Float:v_z, Float:x,Float:y,Float:z; if(ud < 0) { GetPlayerCameraFrontVector(playerid,x,y,z); v_x = x+0.1; v_y = y+0.1; }
	if(k & 128) v_z = -0.2; else if(k & KEY_FIRE) v_z = 0.2; if(k & KEY_WALK) { v_x /=5.0; v_y /=5.0; v_z /=5.0; }
	if(k & KEY_SPRINT) { v_x *=4.0; v_y *=4.0; v_z *=4.0; }
	if(v_z == 0.0) v_z = 0.025; SetPlayerVelocity(playerid,v_x,v_y,v_z);
	if(v_x == 0 && v_y == 0) { if(GetPlayerAnimationIndex(playerid) == 959) ApplyAnimation(playerid,"PARACHUTE","PARA_steerR",6.1,1,1,1,1,0,1); } else { GetPlayerCameraFrontVector(playerid,v_x,v_y,v_z); GetPlayerCameraPos(playerid,x,y,z); SetPlayerLookAt(playerid,v_x*500.0+x,v_y*500.0+y); if(GetPlayerAnimationIndex(playerid) != 959) ApplyAnimation(playerid,"PARACHUTE","FALL_SkyDive_Accel",6.1,1,1,1,1,0,1); }
	if(OnFly[playerid]) SetTimerEx("Fly",100,0,"i",playerid); return 1; }
bool:DesactivarModoVolador(playerid) { if(!OnFly[playerid]) return false; new Float:x,Float:y,Float:z; GetPlayerPos(playerid,x,y,z); SetPlayerPos(playerid,x,y,z); OnFly[playerid] = false; return true; }
static SetPlayerLookAt(playerid,Float:x,Float:y) { new Float:Px, Float:Py, Float: Pa; GetPlayerPos(playerid, Px, Py, Pa); Pa = floatabs(atan((y-Py)/(x-Px))); if (x <= Px && y >= Py) 		Pa = floatsub(180.0, Pa); else if (x < Px && y < Py) 		Pa = floatadd(Pa, 180.0); else if (x >= Px && y <= Py)	Pa = floatsub(360.0, Pa); Pa = floatsub(Pa, 90.0); if (Pa >= 360.0) Pa = floatsub(Pa, 360.0); SetPlayerFacingAngle(playerid, Pa); return; }
//==============================================================================
stock PonerZadminO5v4() {
Textdraw0 = TextDrawCreate(1.000000, 0.000000, "ZadminKelox2012");
TextDrawBackgroundColor(Textdraw0, 255);
TextDrawFont(Textdraw0, 1);
TextDrawLetterSize(Textdraw0, 0.330000, 0.899999);
TextDrawColor(Textdraw0, 1482184874);
TextDrawSetOutline(Textdraw0, 0);
TextDrawSetProportional(Textdraw0, 1);
TextDrawSetShadow(Textdraw0, 1);
for(new i; i < MAX_PLAYERS; i ++) {
if(IsPlayerConnected(i)) { TextDrawShowForPlayer(i, Textdraw0); }
} return 1; }
stock SacarZadminO5v4() { TextDrawHideForAll(Textdraw0); TextDrawDestroy(Textdraw0); return 1; }
stock ActivarZadminO5v4(playerid) { TextDrawShowForPlayer(playerid, Textdraw0); return 1; }
//==============================================================================
stock ObtenerNombreArmaID(NombreArma[]) {
if(strfind("molotov",NombreArma,true)!=-1) return 18;
for(new i = 0; i <= 46; i++) {
switch(i) {
case 0,19,20,21,44,45: continue;
default: {
new anombre[32]; GetWeaponName(i,anombre,sizeof(anombre));
if(strfind(anombre,NombreArma,true) != -1) return i;
} } } return -1; }
//==============================================================================
