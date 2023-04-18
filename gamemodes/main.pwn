/*******************************************************************************
* NOME DO ARQUIVO :		main.pwn
*
*DESCRIPTION : 
 * Includes all modules, libraries and gamemode settings
*
* GRADES : 
 * This file should not be used to handle gamemode information, 
 * Just serve as a bridge for the modules to connect.
*
*/

// NECESSÁRIO estar no topo
#include a_samp
#undef MAX_PLAYERS
#define MAX_PLAYERS 50

//------------------------------------------------------------------------------

// Versão do script
#define SCRIPT_VERSION_MAJOR							0
#define SCRIPT_VERSION_MINOR							1
#define SCRIPT_VERSION_PATCH							0
#define SCRIPT_VERSION_NAME								"Freeroam/DM/Stunt/Derby"

// Banco de Dados
#define MySQL_HOST                                      "maple.db.ashhost.in"
#define MySQL_USER                                      "u768_s36AidHHq4wdwsdawdwdawdwd"
#define MySQL_DB                                        "s768_LegacyFreeroam"
#define MySQL_PASS                                      "wdasdwasdwasdwasdwaswdd"
new gMySQL;

//------------------------------------------------------------------------------

// Amount of buildings (inputs and outputs) the server can load
#define MAX_BUILDINGS									32

// Number of vehicles that players can create
#define MAX_CREATED_VEHICLE_PER_PLAYER					1

// Interval between the random messages of the server in milliseconds
#define ADVERTISE_INTERVAL								300000

// Interval between the name of the random server in milliseconds
#define UPDATE_HOSTNAME_INTERVAL						15000

// Maximum Player Password Size
#define MAX_PLAYER_PASSWORD								32

// Maximum quantity of races that the server can load
#define MAX_RACES										64

// Maximum amount of checkpoints that the race may have
#define MAX_RACE_CHECKPOINTS							32

// Maximum quantity of runners in racing
#define MAX_RACE_PLAYERS								10

// How many seconds the race will take to start after the minimum limit of players is reached
#define RACE_COUNT_DOWN									30

// How many seconds the derby will take to start after the minimum limit of players is hit
#define DERBY_COUNT_DOWN								30

// Quantos segundos o evento irá levar para iniciar após ser criado
#define EVENT_COUNT_DOWN								60

//Maximum Derby amount on the server 
#define MAX_DERBY										32

// How many seconds the DM will take to start after the limit of players is reached
#define DEATHMATCH_COUNT_DOWN							30

// Maximum amount of deathmatches that the server can load
#define MAX_DEATHMATCHES								64

// Maximum quantity of players on Deathmatch
#define MAX_DEATHMATCH_PLAYERS							30

// Maximum size of map names
// Recommended to use few characters to avoid exceeding the limit of dialog
#define MAX_RACE_NAME									34
#define MAX_DEATHMATCH_NAME								34

// Minimum quantity of players to start the game modes
#define MINIMUM_PLAYERS_TO_START_RACE					2
#define MINIMUM_PLAYERS_TO_START_DM						2
#define MINIMUM_PLAYERS_TO_START_DERBY					2

// Invalid ID constants
#define INVALID_RACE_ID									-1
#define INVALID_DEATHMATCH_ID							-1
#define INVALID_DERBY_ID								-1

// Address for the PHP script to send email
#define MAILER_URL "http://localhost/mailer.php"

//------------------------------------------------------------------------------

// Libraries
#include streamer
#include next-ac
#include sscanf2
#include a_mysql
#include YSI\y_hooks
#include YSI\y_timers
#include YSI\y_iterate
#include YSI\y_commands
#include YSI\y_va
#include mSelection
#include md-sort
#include mailer
#include drift
#include utils

//------------------------------------------------------------------------------

hook OnGameModeInit()
{
	print("\n\n============================================================\n");
	print("Initializing...\n");
	SetGameModeText(SCRIPT_VERSION_NAME " " #SCRIPT_VERSION_MAJOR "." #SCRIPT_VERSION_MINOR "." #SCRIPT_VERSION_PATCH);

	// Conexão com o banco de dados MySQL
	mysql_log(LOG_ERROR | LOG_WARNING | LOG_DEBUG); // Usado para debug, comentar quando for para produção
	gMySQL = mysql_connect(MySQL_HOST, MySQL_USER, MySQL_DB, MySQL_PASS);
	if(mysql_errno(gMySQL) != 0)
	{
		print("ERROR: Could not connect to database!");
		return -1; // Parar inicialização se não foir possível conectar ao banco de dados.
	}
	else
		printf("[mysql] connected to database %s at %s successfully!", MySQL_DB, MySQL_HOST);

	// Configurações do Gamemode
	
	ShowNameTags(1);
	UsePlayerPedAnims();
	DisableInteriorEnterExits();
	SetNameTagDrawDistance(40.0);
	EnableStuntBonusForAll(false);
	AddPlayerClass(299, 1119.9399, -1618.7476, 20.5210, 91.8327, 0, 0, 0, 0, 0, 0);
	SetTimer("LoopHostName", 5000, true);
	return 1;
}

hook LoopHostName()
{
	SendRconCommand("hostname LEGACY FREEROAM [MY]");
	return 1;
}

//------------------------------------------------------------------------------

// Modulos
/* Definições */
#include "../modules/def/dialog.pwn"
#include "../modules/def/colors.pwn"
#include "../modules/def/messages.pwn"
#include "../modules/def/ranks.pwn"

/* Visual */
#include "../modules/visual/logo.pwn"
#include "../modules/visual/authentication.pwn"
#include "../modules/visual/lobby.pwn"
#include "../modules/visual/deathmatch.pwn"
#include "../modules/visual/tutorial.pwn"

/* Data */
#include "../modules/data/player.pwn"
#include "../modules/data/building.pwn"
#include "../modules/data/ranking.pwn"

/* Player */
#include "../modules/player/commands.pwn"
#include "../modules/player/attachments.pwn"
#include "../modules/player/changeskin.pwn"

/* Admin */
#include "../modules/admin/commands.pwn"

/* Core */
#include "../modules/core/timers.pwn"
#include "../modules/core/advertisements.pwn"

/* Gameplay */
#include "../modules/gameplay/bank.pwn"
#include "../modules/gameplay/chat.pwn"
#include "../modules/gameplay/colors.pwn"
#include "../modules/gameplay/tuning.pwn"
#include "../modules/gameplay/derby.pwn"
#include "../modules/gameplay/races.pwn"
#include "../modules/gameplay/deathmatch.pwn"
#include "../modules/gameplay/drift.pwn"
#include "../modules/gameplay/events.pwn"
#include "../modules/gameplay/anticheat.pwn"
#include "../modules/gameplay/animations.pwn"
#include "../modules/gameplay/pause.pwn"
#include "../modules/gameplay/npc.pwn"
#include "../modules/gameplay/vehiclename.pwn"
#include "../modules/gameplay/interior.pwn"
#include "../modules/gameplay/tutorial.pwn"

//------------------------------------------------------------------------------

main()
{
	printf("\n\n%s %d.%d.%d initialiazed.\n", SCRIPT_VERSION_NAME, SCRIPT_VERSION_MAJOR, SCRIPT_VERSION_MINOR, SCRIPT_VERSION_PATCH);
	print("============================================================\n");
}
