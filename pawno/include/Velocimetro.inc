/*  Creador de Velocimetro v0.2.1
Script creado para Extreme Latin Role Play por enigma513
Este script puede ser editado, distribuido siempre y cuando se conserven los creditos

Es mi primer include, por ahora le saque las funciones de kilometraje, gasolina, cuadro de info, seran agregadas en proximas versiones

Creditos:
Script: enigma513
foreach: Y_Less
TextDraw Editor: Zamaroht
GetSpeed, IsABike: No estoy seguro de quien es.

Idea: Me motive al mirar que irinel habia hecho un buen velocimetro

Test:
Oscar
*/
//native FijarVelocimetro(Float:CentroX, Float:CentroY, Float:RadioCircunf, Float:MaxVeloc, Float:MaxAngulo, color_letra, MaxPuntos);
//native DestruirVelocimetro();
//native AddExtTDSpeedo(Text:TextID);
//native AddDigitalVelocimetro(playerid, PlayerText:TextID);

/*
CentroX         	Es la pos en X del centro de la circunferencia, del punto de donde saldria la aguja del velocimetro
CentroY             Es la pos en X del centro de la circunferencia, del punto de donde saldria la aguja del velocimetro
RadioCircunf        Es el radio de la circunferencia, que tan alejados estaran los numeros
MaxVeloc            Maxima velocidad registrada
MaxAngulo           Maximo Angulo, es para la posicion de los numeros en el velocimetro, se pueden usar valores como 90 o 180
color_letra         Es el color de los numeros
MaxPuntos           El maximo de puntos que tendra la aguja (maximo 10)
*/

#if defined _Vel_Ext_included
	#endinput
#endif
#define _Vel_Ext_included

#include <a_samp>
#include <foreach>
#include <float>

#define FUNCION:%0(%1) 	forward %0(%1); \
						public %0(%1)

//-----------------------------------Configurar------------------------------------------//
#define VEL_TIMER 			200//Cada cuanto se actualizara el velocimetro
#define Vel_Intervalo 		10 //Tu velocidad maxima entre este numero, te dara la separacion
#define MAX_TEXT_SLOTS 		11 //Para puntos ( VelocimetroX[Vel_MaxPuntos] )
#define MAX_TEXT_ANADIDOS 	10 //Para agregar TD externos
//---------------------------------------------------------------------------------------//


#define Vel_Frecuencia 		Vel_Intervalo+1

new Text:TextVelAg[Vel_Frecuencia];
new VelocTimer, VelocimetroShowing[MAX_PLAYERS] = { 0, ...};

enum anadinfo
{
	Anad_Creado,
	Text: Anad_ID
};
new TextAnadidos[MAX_TEXT_ANADIDOS][anadinfo];

enum DigInfo
{
	bool: Dig_Creado,
	PlayerText: Dig_ID
};
new TextDigital[MAX_PLAYERS][DigInfo];

enum tdinfo
{
    PlayerText: Text_ID,
    Text_Creado,
    Text_Tipo
};
new TextCreado[MAX_PLAYERS][MAX_TEXT_SLOTS][tdinfo];

enum velinfo
{
	bool: Vel_Creado,
    Float:Vel_CentroX,
	Float:Vel_CentroY,
	Float:Vel_Radio,
	Float:Vel_MaxVeloc,
	Float:Vel_MaxAngulo,
	Vel_color_fondo,
	Float:Vel_PosFondoX,
	Float:Vel_PosFondoY,
	Float:Vel_FondoTextSizeX,
	Float:Vel_FondoTextSizeY,
	Vel_color_letra,
	Vel_MaxPuntos,
	Float:Vel_Factor
};
new VelocimetroX[velinfo];

new Iterator:TextSlot[MAX_PLAYERS]<MAX_TEXT_SLOTS>;

public OnFilterScriptInit()
{
    Itter_Init(TextSlot);
	return CallLocalFunction("VelExt_OnFilterScriptInit", "");
}
#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit VelExt_OnFilterScriptInit
forward VelExt_OnFilterScriptInit();

public OnGameModeInit()
{
    Itter_Init(TextSlot);
	return CallLocalFunction("VelExt_OnGameModeInit", "");
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit VelExt_OnGameModeInit
forward VelExt_OnGameModeInit();

public OnFilterScriptExit()
{
    DestruirVelocimetro();
    for(new i; i<MAX_PLAYERS; i++) Itter_Clear(TextSlot[i]);
	return CallLocalFunction("VelExt_OnFilterScriptExit", "");
}
#if defined _ALS_OnFilterScriptExit
    #undef OnFilterScriptExit
#else
    #define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit VelExt_OnFilterScriptExit
forward VelExt_OnFilterScriptExit();

public OnGameModeExit()
{
    DestruirVelocimetro();
	return CallLocalFunction("VelExt_OnGameModeExit", "");
}
#if defined _ALS_OnGameModeExit
    #undef OnGameModeExit
#else
    #define _ALS_OnGameModeExit
#endif
#define OnGameModeExit VelExt_OnGameModeExit
forward VelExt_OnGameModeExit();

public OnPlayerDisconnect(playerid, reason)
{
    DestruirTodoTextCreado(playerid);
    VelocimetroShowing[playerid] = 0;
	TextDigital[playerid][Dig_Creado] = false;
    return CallLocalFunction("VelExt_OnPlayerDisconnect", "");
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect VelExt_OnPlayerDisconnect
forward VelExt_OnPlayerDisconnect(playerid, reason);

FUNCION: VelocimetroUpdate()
{
    new Float: KMH;
    foreach(new i: Player)
	{
 		if(IsPlayerInAnyVehicle(i))
	 	{
	 	    if(VelocimetroShowing[i] == 0)
	    	{
	   			for(new v; v<Vel_Frecuencia; v++)
				{
					TextDrawShowForPlayer(i, TextVelAg[v]);
	 			}
	 			for(new v; v<MAX_TEXT_ANADIDOS; v++)
				{
				    if(TextAnadidos[v][Anad_Creado])
				    {
				        TextDrawShowForPlayer(i, TextAnadidos[v][Anad_ID]);
				    }
				}
 			}
 			KMH = GetSpeed(i);
			S_VelocimetroAguja(i,true,"_",KMH,1);
			VelocimetroShowing[i] = 1;
			if(TextDigital[i][Dig_Creado])
	 		{
	 		    new string[15];
	   			format(string, 15, "%0.0f km/h",KMH);
				S_VelocTexto(i,true,string);
			}
   		}
   		else
   		{
   		    if(VelocimetroShowing[i] == 1)
	    	{
	    	    for(new v; v<Vel_Frecuencia; v++)
	  			{
					TextDrawHideForPlayer(i, Text:TextVelAg[v]);
	 			}
	 			for(new v; v<MAX_TEXT_ANADIDOS; v++)
				{
				    if(TextAnadidos[v][Anad_Creado])
				    {
				        TextDrawHideForPlayer(i, Text:TextAnadidos[v][Anad_ID]);
				    }
				}
				S_VelocimetroAguja(i,false,"_",0.0,1);
				VelocimetroShowing[i] = 0;
				S_VelocTexto(i,false,"_");
	    	}
   		}
	}
	return 1;
}
FUNCION: S_VelocimetroAguja(playerid,bool: crear,string[],Float: valor, Numero)
{
    new slot = ObtenerTextPlayerId(playerid,Numero);
    if(crear)
    {
        if(TextCreado[playerid][slot][Text_Creado] == 1) PlayerTextDrawDestroy(playerid,TextCreado[playerid][slot][Text_ID]);

		if(valor > VelocimetroX[Vel_MaxVeloc])valor = VelocimetroX[Vel_MaxVeloc];
  		if(valor < 0)valor = 0.0;
		new Float: coord[2], Float: QuePuntoAg;
		QuePuntoAg = floatsub(1.0, floatmul(Numero,0.10));

		coord[0] = floatadd(floatmul(floatcos(floatmul(valor,VelocimetroX[Vel_Factor]),degrees), floatmul(VelocimetroX[Vel_Radio],-QuePuntoAg)),VelocimetroX[Vel_CentroX]);
		coord[1] = floatadd(floatmul(floatsin(floatmul(valor,VelocimetroX[Vel_Factor]),degrees), floatmul(VelocimetroX[Vel_Radio],-QuePuntoAg)),VelocimetroX[Vel_CentroY]);
		TextCreado[playerid][slot][Text_ID] = CreatePlayerTextDraw(playerid, coord[0], coord[1], ".");
		TextCreado[playerid][slot][Text_Creado] = 1;
		if(!Itter_Contains(TextSlot[playerid],slot)) Itter_Add(TextSlot[playerid],slot);
  		TextCreado[playerid][slot][Text_Tipo] = Numero;
  		PlayerTextDrawAlignment(playerid,TextCreado[playerid][slot][Text_ID], 2);
		PlayerTextDrawBackgroundColor(playerid,TextCreado[playerid][slot][Text_ID], 255);
		PlayerTextDrawFont(playerid,TextCreado[playerid][slot][Text_ID], 1);
		PlayerTextDrawLetterSize(playerid,TextCreado[playerid][slot][Text_ID], 0.500000, 1.699998);
		PlayerTextDrawColor(playerid,TextCreado[playerid][slot][Text_ID], -1);
		PlayerTextDrawSetOutline(playerid,TextCreado[playerid][slot][Text_ID], 1);
		PlayerTextDrawSetProportional(playerid,TextCreado[playerid][slot][Text_ID], 1);
		PlayerTextDrawSetShadow(playerid,TextCreado[playerid][slot][Text_ID], 1);

        PlayerTextDrawShow(playerid,TextCreado[playerid][slot][Text_ID]);
    }
    else
    {
        DestruirTextCreado(playerid,slot);
    }
    if(Numero < VelocimetroX[Vel_MaxPuntos])
	{
	    Numero++;
		S_VelocimetroAguja(playerid,crear,string,valor,Numero);
	}
    return 1;
}
FUNCION: S_VelocTexto(playerid,bool: crear,string[])
{
	if(TextDigital[playerid][Dig_Creado])
	{
	    if(crear)
	    {
	    	PlayerTextDrawSetString(playerid,TextDigital[playerid][Dig_ID],string);
	        PlayerTextDrawShow(playerid,TextDigital[playerid][Dig_ID]);
	    }
	    else
	    {
	        PlayerTextDrawHide(playerid,TextDigital[playerid][Dig_ID]);
	    }
    }
    return 1;
}
FUNCION:CargarTextdraw()
{
	new Numeros_Frecuencia = floatround(floatdiv(VelocimetroX[Vel_MaxVeloc],Vel_Intervalo));

    for(new i=0, v=0; i<= VelocimetroX[Vel_MaxVeloc] && v <= Vel_Frecuencia; i+= Numeros_Frecuencia)
    {
        new Float: coord[2],textovel[10], val;
        val = i;
		coord[0] = floatadd(floatmul(floatcos(floatmul(float(val),VelocimetroX[Vel_Factor]),degrees), -VelocimetroX[Vel_Radio]),VelocimetroX[Vel_CentroX]);
		coord[1] = floatadd(floatmul(floatsin(floatmul(float(val),VelocimetroX[Vel_Factor]),degrees), -VelocimetroX[Vel_Radio]),VelocimetroX[Vel_CentroY]);
		format(textovel,9,"%d",i);

		TextVelAg[v] = TextDrawCreate(coord[0], coord[1], textovel);
		TextDrawAlignment(TextVelAg[v], 2);
		TextDrawBackgroundColor(TextVelAg[v], 255);
		TextDrawFont(TextVelAg[v], 3);
		TextDrawLetterSize(TextVelAg[v], 0.200000, 0.799998);
		TextDrawColor(TextVelAg[v], VelocimetroX[Vel_color_letra]);
		TextDrawSetOutline(TextVelAg[v], 1);
		TextDrawSetProportional(TextVelAg[v], 1);
		TextDrawSetShadow(TextVelAg[v], 1);
		v++;
    }
    return 1;
}

stock FijarVelocimetro(Float:CentroX, Float:CentroY, Float:RadioCircunf, Float:MaxVeloc, Float:MaxAngulo, color_letra, MaxPuntos = 3)
{
	if(VelocimetroX[Vel_Creado])
	{
		DestruirVelocimetro();
	}
 	VelocimetroX[Vel_CentroX] = CentroX;
  	VelocimetroX[Vel_CentroY] = CentroY;
   	VelocimetroX[Vel_Radio] = RadioCircunf;
   	VelocimetroX[Vel_MaxVeloc] = MaxVeloc;
    VelocimetroX[Vel_MaxAngulo] = MaxAngulo;
    VelocimetroX[Vel_color_letra] = color_letra;
    if(0 > MaxPuntos > 10) VelocimetroX[Vel_MaxPuntos] = 10;
    else VelocimetroX[Vel_MaxPuntos] = MaxPuntos;
    VelocimetroX[Vel_Factor] = floatdiv(VelocimetroX[Vel_MaxAngulo],VelocimetroX[Vel_MaxVeloc]);
    VelocimetroX[Vel_Creado] = true;
	CargarTextdraw();
	VelocTimer = SetTimer("VelocimetroUpdate",VEL_TIMER,1);
	return 1;
}
stock DestruirVelocimetro()
{
    if(VelocimetroX[Vel_Creado])
	{
		KillTimer(VelocTimer);
		for(new i; i<Vel_Frecuencia;i++)
	    {
	        TextDrawDestroy(TextVelAg[i]);
	    }
	    for(new i; i<MAX_TEXT_ANADIDOS; i++)
		{
  			if(TextAnadidos[i][Anad_Creado])
	    	{
	    	    TextAnadidos[i][Anad_Creado] = 0;
      			TextDrawDestroy(TextAnadidos[i][Anad_ID]);
		    }
		}
	    VelocimetroX[Vel_Creado] = false;
	    foreach(new i: Player)
		{
			DestruirTodoTextCreado(i);
		    VelocimetroShowing[i] = 0;
		}
	}
	return 1;
}
stock AddExtTDSpeedo(Text:TextID)
{
	new slot = ObtenerAnadSlot();
	if(slot != -1)
	{
	    TextAnadidos[slot][Anad_Creado] = 1;
     	TextAnadidos[slot][Anad_ID] = TextID;
     	return 1;
    }
    else print("Incrementa el numero de MAX_TEXT_ANADIDOS");
    return 0;
}
stock AddDigitalVelocimetro(playerid, PlayerText:TextID)
{
	TextDigital[playerid][Dig_Creado] = true;
 	TextDigital[playerid][Dig_ID] = TextID;
    return 1;
}

stock GetSpeed(playerid)//gear system
{
	new Float:ST[3];
	GetVehicleVelocity(GetPlayerVehicleID(playerid),ST[0],ST[1],ST[2]);

	return floatround(1.61*floatsqroot(floatpower(floatabs(ST[0]), 2.0) + floatpower(floatabs(ST[1]), 2.0) + floatpower(floatabs(ST[2]), 2.0)) * 100.3);
}
/*stock IsABike(vehid)//randomkid88
{
    new modelid = GetVehicleModel(vehid);
    if(modelid == 509||modelid ==510||modelid ==581||modelid ==522||modelid ==521||modelid ==523||modelid ==586||modelid ==481||modelid ==462||modelid ==448||modelid ==461||modelid ==463||modelid ==468||modelid ==471) return 1;
    else return 0;
}*/

FUNCION: TextDrawSlot(playerid)
{
    new slot = Itter_Free(TextSlot[playerid]);
	if(!TextCreado[playerid][slot][Text_Creado]) return slot;
	return -1;
}
FUNCION: DestruirTextCreado(playerid,&SlotText)
{
	if(TextCreado[playerid][SlotText][Text_Creado])
	{
		PlayerTextDrawHide(playerid,TextCreado[playerid][SlotText][Text_ID]);
		PlayerTextDrawDestroy(playerid,TextCreado[playerid][SlotText][Text_ID]);
		TextCreado[playerid][SlotText][Text_ID] = PlayerText:INVALID_TEXT_DRAW;
		TextCreado[playerid][SlotText][Text_Creado] = 0;
		TextCreado[playerid][SlotText][Text_Tipo] = 0;
		Itter_SafeRemove(TextSlot[playerid],SlotText,SlotText);
		return 1;
	}
	return 0;
}
stock DestruirTodoTextCreado(playerid)
{
    foreach(new i: TextSlot[playerid])
 	{
 	    DestruirTextCreado(playerid,i);
	}
	TextDigital[playerid][Dig_Creado] = false;
	PlayerTextDrawDestroy(playerid,TextDigital[playerid][Dig_ID]);
	return 1;
}
FUNCION: ObtenerTextPlayerId(playerid,Tipo)
{
    foreach(new i: TextSlot[playerid])
 	{
      	if(TextCreado[playerid][i][Text_Creado] == 1)
	   	{
       		if(TextCreado[playerid][i][Text_Tipo] == Tipo) return i;
    	}
  	}
	return TextDrawSlot(playerid);
}
FUNCION: ObtenerAnadSlot()
{
	for(new i; i<MAX_TEXT_ANADIDOS; i++)
	{
	    if(!TextAnadidos[i][Anad_Creado])return i;
	}
	return -1;
}
