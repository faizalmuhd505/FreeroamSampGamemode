/*******************************************************************************
* NOME DO ARQUIVO :        modules/def/dialog.pwn
*
* DESCRIÇÃO :
*       Organizar os ID de dialogo para que não aja mais de um dialogo com
*       mesmo id.
*
* NOTAS :
*       -
*/

enum
{
    DIALOG_LOGIN,
    DIALOG_REGISTER,
    DIALOG_BANNED,
    DIALOG_COLORS,
    DIALOG_CREDITS,
    DIALOG_FORUM,

    DIALOG_COMMAND_LIST,
    DIALOG_COMMAND_LIST_PLAYER,
    DIALOG_COMMAND_LIST_VEHICLE,
    DIALOG_COMMAND_LIST_TELEPORT,
    DIALOG_COMMAND_LIST_GENERAL,
    DIALOG_COMMAND_LIST_ANIMS,

    DIALOG_ADMIN_COMMANDS,
    DIALOG_INFO_PLAYER,
    DIALOG_PLAYERS_IP,

    DIALOG_SURVEY,

    DIALOG_TUNING,
    DIALOG_TUNING_PAINTJOB,
    DIALOG_TUNING_COLOR,
    DIALOG_TUNING_EXHAUST,
    DIALOG_TUNING_FBUMP,
    DIALOG_TUNING_RBUMP,
    DIALOG_TUNING_ROOF,
    DIALOG_TUNING_SPOILER,
    DIALOG_TUNING_SKIRT,
    DIALOG_TUNING_BULLBAR,
    DIALOG_TUNING_WHEEL,
    DIALOG_TUNING_NITRO,
    DIALOG_TUNING_HOOD,
    DIALOG_TUNING_VENT,
    DIALOG_TUNING_LIGHT,
    DIALOG_VEHICLE_LIST,
    DIALOG_FIGHTING_LIST,

    DIALOG_LOGIN_PASSWORD,

    DIALOG_REGISTER_GENDER,
    DIALOG_REGISTER_PASSWORD,
    DIALOG_REGISTER_AGE,
    DIALOG_REGISTER_EMAIL,

    DIALOG_RACE_CREATOR,
    DIALOG_RACE_CREATOR_PRIZE,
    DIALOG_RACE_PRIZE_VALUE,
    DIALOG_RACE_CREATOR_CONFIG,
    DIALOG_RACE_CONFIG_CP_TYPE,
    DIALOG_RACE_CONFIG_CP_SIZE,
    DIALOG_RACE_CONFIG_CP_NAME,
    DIALOG_RACE_CONFIG_VMODEL,

    DIALOG_DM_CREATOR,
    DIALOG_DM_CREATOR_PRIZE,
    DIALOG_DM_PRIZE_VALUE,
    DIALOG_DM_CREATOR_WEAPON,
    DIALOG_DM_CREATOR_WEAPON_ID,
    DIALOG_DM_CREATOR_CONFIG,
    DIALOG_DM_CRT_CONFIG_NAME,
    DIALOG_DM_CRT_CONFIG_POINTS,

    DIALOG_RACE,
    DIALOG_RACE_LEADERBOARD,
    DIALOG_RACE_DELETE,

    DIALOG_DERBY,
    DIALOG_DERBY_LEADERBOARD,

    DIALOG_EVENT_CREATOR,
    DIALOG_EVENT_CREATOR_WEAPON,
    DIALOG_EVENT_CR_WP_SLOT_0,
    DIALOG_EVENT_CR_WP_SLOT_1,
    DIALOG_EVENT_CR_WP_SLOT_2,
    DIALOG_EVENT_CR_WP_SLOT_3,
    DIALOG_EVENT_CR_WP_SLOT_4,
    DIALOG_EVENT_CR_WP_SLOT_5,
    DIALOG_EVENT_CR_WP_SLOT_6,
    DIALOG_EVENT_CR_WP_SLOT_7,
    DIALOG_EVENT_CR_WP_SLOT_8,
    DIALOG_EVENT_CR_WP_SLOT_9,
    DIALOG_EVENT_CR_WP_SLOT_10,

    DIALOG_EVENT_CREATOR_SPAWN,
    DIALOG_EVENT_CREATOR_PRIZE,

    DIALOG_SPAWN_HELPER,
    DIALOG_ADMIN_REPORT,

    DIALOG_ATTACHMENTS_CATEGORY,
	DIALOG_ATTACHMENTS_GLASSES,
	DIALOG_ATTACHMENTS_HATS,
	DIALOG_ATTACHMENTS_BANDANA,
	DIALOG_ATTACHMENTS_CAP,
	DIALOG_ATTACHMENTS_HELMETS,
	DIALOG_ATTACHMENTS_MASKS,
	DIALOG_ATTACHMENTS_EDIT,
	DIALOG_ATTACHMENTS_BONE,
	DIALOG_ATTACHMENTS_REMOVE,

    DIALOG_GENERATE_VIP_KEY,
    DIALOG_GEN_VIP_KEY_DAYS,
    DIALOG_GEN_VIP_KEY_TYPE,

    DIALOG_RULES,
    DIALOG_BAR,

    DIALOG_DEATHMATCH,
    DIALOG_DEATHMATCH_LEADERBOARD,
    DIALOG_DEATHMATCH_DELETE,

    DIALOG_INTERIOR_LIST,

    DIALOG_RANKING,
    DIALOG_RANKING_SCORE,
    DIALOG_RANKING_KILLS,
    DIALOG_RANKING_RACES,
    DIALOG_RANKING_DERBY,
    DIALOG_RANKING_DM,
    DIALOG_RANKING_PLAYED,

    DIALOG_RESETPASS_CODE,
    DIALOG_RESETPASS_PASS
}