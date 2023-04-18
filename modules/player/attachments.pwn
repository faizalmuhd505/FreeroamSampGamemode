/*******************************************************************************
* Name DO ARQUIVO :		modules/player/attachments.pwn
*
* DESCRIÇÃO :
*	   Permite que os jogadores anexem objetos em si mesmo.
*
* NOTAS :
*	   -
*/

#include <YSI\y_hooks>

//------------------------------------------------------------------------------

#define MAX_PLAYER_ATTACHED_ITEMS	10

//------------------------------------------------------------------------------

forward OnLoadPlayerAttachments(playerid);
forward OnInsertAttachmentOnDatabase(playerid, index);

//------------------------------------------------------------------------------

static gPickupID;
static gPlayerTickCount[MAX_PLAYERS];
static gIsDialogVisible[MAX_PLAYERS];

//------------------------------------------------------------------------------

enum
{
    LIST_GLASSES,
    LIST_HATS,
	LIST_BANDANA,
	LIST_CAP,
	LIST_HELMETS,
	LIST_MASKS
}

static attachments_category[][] =
{
    "Glasses",
    "Hat",
	"Bandana",
	"Boné",
	"Helmets",
	"Masks"
};

static attachments_data[][][] =
{
    /*
		preço, modelo, categoria, descrição
	*/

	// Glasses
    {50,	19006, 	LIST_GLASSES,	"Common red"},
    {50,	19007, 	LIST_GLASSES,	"Common yellow"},
    {50,	19008, 	LIST_GLASSES,	"Green green"},
    {50,	19009, 	LIST_GLASSES,	"Common blue"},
    {50,	19010, 	LIST_GLASSES,	"Common purple "},
    {150,	19011,	LIST_GLASSES,	"Psychedelic"},
    {75,	19012,	LIST_GLASSES,	"Common black "},
    {100,	19013, 	LIST_GLASSES,	"Personalized Black "},
    {150,	19014, 	LIST_GLASSES,	"Chess"},
    {200,	19015, 	LIST_GLASSES,	"Transparent black "},
    {250,	19016, 	LIST_GLASSES,	"X-ray"},
    {300,	19017, 	LIST_GLASSES,	"Yellow"},
    {300,	19018, 	LIST_GLASSES,	"Orange"},
    {300,	19019, 	LIST_GLASSES,	"Red"},
    {300,	19020, 	LIST_GLASSES,	"Azul"},
    {300,	19021, 	LIST_GLASSES,	"Green"},
    {600,	19022, 	LIST_GLASSES,	"Black Aviator "},
    {500,	19023, 	LIST_GLASSES,	"Blue Aviator "},
    {500,	19024, 	LIST_GLASSES,	"Purple aviator "},
    {500,	19025, 	LIST_GLASSES,	"Lilas aviator "},
    {500,	19026, 	LIST_GLASSES,	"Aviator rose "},
    {500,	19027, 	LIST_GLASSES,	"Aviator Orange "},
    {500,	19028, 	LIST_GLASSES,	"Aviator yellow "},
    {500,	19029, 	LIST_GLASSES,	"Aviator green "},
    {400,	19030, 	LIST_GLASSES,	"Intellectual brown "},
    {400,	19031, 	LIST_GLASSES,	"Intellectual yellow "},
    {400,	19032, 	LIST_GLASSES,	"Intellectual red "},
    {800,	19033, 	LIST_GLASSES,	"Blind Black "},
    {650,	19034, 	LIST_GLASSES,	"Black Chess "},
    {1200,	19035, 	LIST_GLASSES,	"Personalized Blue "},
    {2000,	19138, 	LIST_GLASSES,	"Black police "},
    {2000,	19139, 	LIST_GLASSES,	"Police red "},
    {2000,	19140, 	LIST_GLASSES,	"Police blue "},

	// Hats
	{400,	18947, 	LIST_HATS,		"Black Fedora "},
    {400,	18948, 	LIST_HATS,		"Blue Fedora "},
    {400,	18949, 	LIST_HATS,		"Green Fedora "},
    {400,	18950, 	LIST_HATS,		"Red Fedora "},
    {400,	18951, 	LIST_HATS,		"Yellow fedora "},
    {350,	18967, 	LIST_HATS,		"Black bucket "},
    {350,	18969, 	LIST_HATS,		"Orange bucket "},
    {500,	18968, 	LIST_HATS,		"Gray and blue bucket "},

	// Bandanas
	{120,	18891,	LIST_BANDANA,	"Blue Bandana "},
	{120,	18892,	LIST_BANDANA,	"Red Bandana "},
	{100,	18893,	LIST_BANDANA,	"White and pink bandana "},
	{100,	18894,	LIST_BANDANA,	"Orange and gray bandana "},
	{500,	18895,	LIST_BANDANA,	"Bandana Skull "},
	{450,	18896,	LIST_BANDANA,	"Black Bandana "},
	{300,	18897,	LIST_BANDANA,	"Blue Bandana "},
	{300,	18898,	LIST_BANDANA,	"Green bandana "},
	{300,	18899,	LIST_BANDANA,	"Bandana Rosa "},
	{300,	18900,	LIST_BANDANA,	"Colorful bandana "},
	{400,	18901,	LIST_BANDANA,	"Tiger Bandana "},
	{300,	18902,	LIST_BANDANA,	"Bandana Cheese "},
	{200,	18903,	LIST_BANDANA,	"Bandana purple "},
	{350,	18904,	LIST_BANDANA,	"Personalized bandana "},
	{300,	18905,	LIST_BANDANA,	"Bandana Madeira"},
	{250,	18906,	LIST_BANDANA,	"Orange bandana (front) "},
	{250,	18907,	LIST_BANDANA,	"Colorful bandana (front) "},
	{250,	18908,	LIST_BANDANA,	"Personalized bandana (front) "},
	{250,	18909,	LIST_BANDANA,	"Blue Bandana (front) "},
	{500,	18910,	LIST_BANDANA,	"Bandana Fogo (front) "},

	// Caps
	{500,	18939,	LIST_CAP,		"Personalized cap "},
	{150,	18940,	LIST_CAP,		"Black cap"},
	{150,	18942,	LIST_CAP,		"Blue cap "},
	{250,	18943,	LIST_CAP,		"Grove Street Cap "},
	{500,	18926,	LIST_CAP,		"EXERCISE CAP "},
	{450,	18927,	LIST_CAP,		"Sea cap "},
	{300,	18928,	LIST_CAP,		"Colored cap "},
	{300,	18929,	LIST_CAP,		"Boné Psicodelico"},
	{300,	18930,	LIST_CAP,		"Fire cap "},
	{300,	18932,	LIST_CAP,		"Orange cap "},
	{300,	18933,	LIST_CAP,		"Ball cap "},
	{200,	18934,	LIST_CAP,		"Wine cap "},
	{200,	18935,	LIST_CAP,		"Cheese cap "},
	{200,	19093,	LIST_CAP,		"Gray Dude Cap "},
	{200,	19160,	LIST_CAP,		"Yellow dude cap "},
	{1000,	19161,	LIST_CAP,		"Black police cap "},
	{1000,	19162,	LIST_CAP,		"Blue police cap "},

	// Helmets
	{600,	18645,	LIST_HELMETS,	"Fire helmet "},
	{1200,	18976,	LIST_HELMETS,	"Motocross helmet"},
	{800,	18977,	LIST_HELMETS,	"Red helmet "},
	{1000,	18978,	LIST_HELMETS,	"White helmet "},
	{800,	18979,	LIST_HELMETS,	"Pink helmet "},
	{3500,	19200,	LIST_HELMETS,	"Police helmet "},

	// Masks
	{1200,	18911,	LIST_MASKS,		"Skull Mask "},
	{600,	18912,	LIST_MASKS,		"Black mask "},
	{300,	18913,	LIST_MASKS,		"Green mask "},
	{600,	18914,	LIST_MASKS,		"Mask army "},
	{300,	18915,	LIST_MASKS,		"Colorful mask "},
	{300,	18916,	LIST_MASKS,		"Mascara mascara "},
	{1200,	18917,	LIST_MASKS,		"Personalized mask "},
	{300,	18918,	LIST_MASKS,		"Psychedelic mask "},
	{300,	18919,	LIST_MASKS,		"Ball mask "},
	{300,	18920,	LIST_MASKS,		"Brown mask "},
	{1200,	19036,	LIST_MASKS,		"White Hockey Mask "},
	{600,	19037,	LIST_MASKS,		"Red Hockey Mask "},
	{600,	19038,	LIST_MASKS,		"Green Hockey Mask "},
	{800,	18974,	LIST_MASKS,		"Zorro mask "},
	{600,	19163,	LIST_MASKS,		"Mascara Gimp"}
};

//------------------------------------------------------------------------------

enum e_attachment_data
{
    e_attachment_db,

    e_attachment_index,
    e_attachment_model,
    e_attachment_bone,

    Float:e_attachment_x,
    Float:e_attachment_y,
    Float:e_attachment_z,

    Float:e_attachment_rx,
    Float:e_attachment_ry,
    Float:e_attachment_rz,

    Float:e_attachment_sx,
    Float:e_attachment_sy,
    Float:e_attachment_sz,

    e_attachment_col_1,
    e_attachment_col_2
}
static gPlayerAttachmentData[MAX_PLAYERS][MAX_PLAYER_ATTACHED_ITEMS][e_attachment_data];
static bool:gPlayerAlreadySpawned[MAX_PLAYERS];
static bool:gIsPlayerEditing[MAX_PLAYERS];
static gPlayerSelectedIndex[MAX_PLAYERS];
static gPlayerSelectedCategory[MAX_PLAYERS];

//------------------------------------------------------------------------------

ResetPlayerAttachments(playerid)
{
    for (new i = 0; i < MAX_PLAYER_ATTACHED_ITEMS; i++)
    {
        gPlayerAttachmentData[playerid][i][e_attachment_db] = 0;
        gPlayerAttachmentData[playerid][i][e_attachment_model] = 0;
        RemovePlayerAttachedObject(playerid, gPlayerAttachmentData[playerid][i][e_attachment_index]);
    }
}

//------------------------------------------------------------------------------

ResetPlayerAttachment(playerid, slotid)
{
    gPlayerAttachmentData[playerid][slotid][e_attachment_db] = 0;
    gPlayerAttachmentData[playerid][slotid][e_attachment_model] = 0;
    RemovePlayerAttachedObject(playerid, gPlayerAttachmentData[playerid][slotid][e_attachment_index]);
}

//------------------------------------------------------------------------------

SavePlayerAttachments(playerid)
{
    new query[222];
    for (new i = 0; i < MAX_PLAYER_ATTACHED_ITEMS; i++)
    {
        if(gPlayerAttachmentData[playerid][i][e_attachment_db] == 0)
            continue;

    	mysql_format(gMySQL, query, sizeof(query),
        "UPDATE `attachments` SET `Index`=%d, `Model`=%d, `Bone`=%d,\
        `X`=%f, `Y`=%f, `Z`=%f,\
        `RX`=%f, `RY`=%f, `RZ`=%f,\
        `SX`=%f, `SY`=%f, `SZ`=%f \
        WHERE `ID`=%d",
    	gPlayerAttachmentData[playerid][i][e_attachment_index], gPlayerAttachmentData[playerid][i][e_attachment_model], gPlayerAttachmentData[playerid][i][e_attachment_bone],
        gPlayerAttachmentData[playerid][i][e_attachment_x], gPlayerAttachmentData[playerid][i][e_attachment_y], gPlayerAttachmentData[playerid][i][e_attachment_z],
        gPlayerAttachmentData[playerid][i][e_attachment_rx], gPlayerAttachmentData[playerid][i][e_attachment_ry], gPlayerAttachmentData[playerid][i][e_attachment_rz],
        gPlayerAttachmentData[playerid][i][e_attachment_sx], gPlayerAttachmentData[playerid][i][e_attachment_sy], gPlayerAttachmentData[playerid][i][e_attachment_sz],
        gPlayerAttachmentData[playerid][i][e_attachment_db]);
    	mysql_tquery(gMySQL, query);
    }
}

//------------------------------------------------------------------------------

DeletePlayerAttachment(playerid, slotid)
{
	if(!gPlayerAttachmentData[playerid][slotid][e_attachment_db])
		return 1;

	ResetPlayerAttachment(playerid, slotid);

	new query[50];
	mysql_format(gMySQL, query, sizeof(query), "DELETE FROM `attachments` WHERE `ID` = %d", gPlayerAttachmentData[playerid][slotid][e_attachment_db]);
	mysql_tquery(gMySQL, query);
	return 1;
}

//------------------------------------------------------------------------------

GivePlayerAttachments(playerid)
{
    for (new i = 0; i < MAX_PLAYER_ATTACHED_ITEMS; i++)
    {
        if(gPlayerAttachmentData[playerid][i][e_attachment_db] == 0)
            continue;

        new index = gPlayerAttachmentData[playerid][i][e_attachment_index];
        new modelid = gPlayerAttachmentData[playerid][i][e_attachment_model];
        new bone = gPlayerAttachmentData[playerid][i][e_attachment_bone];

        new Float:x = gPlayerAttachmentData[playerid][i][e_attachment_x];
        new Float:y = gPlayerAttachmentData[playerid][i][e_attachment_y];
        new Float:z = gPlayerAttachmentData[playerid][i][e_attachment_z];

        new Float:rx = gPlayerAttachmentData[playerid][i][e_attachment_rx];
        new Float:ry = gPlayerAttachmentData[playerid][i][e_attachment_ry];
        new Float:rz = gPlayerAttachmentData[playerid][i][e_attachment_rz];

        new Float:sx = gPlayerAttachmentData[playerid][i][e_attachment_sx];
        new Float:sy = gPlayerAttachmentData[playerid][i][e_attachment_sy];
        new Float:sz = gPlayerAttachmentData[playerid][i][e_attachment_sz];

        SetPlayerAttachedObject(playerid, index, modelid, bone, x, y, z, rx, ry, rz, sx, sy, sz);
    }
}

//------------------------------------------------------------------------------

LoadPlayerAttachments(playerid)
{
	new query[52];
	mysql_format(gMySQL, query, sizeof(query), "SELECT * FROM `attachments` WHERE `user_id` = %i", GetPlayerDatabaseID(playerid));
	mysql_tquery(gMySQL, query, "OnLoadPlayerAttachments", "i", playerid);
}

//------------------------------------------------------------------------------

public OnLoadPlayerAttachments(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields, gMySQL);
	if(rows)
	{
        for (new i = 0; i < rows; i++)
        {
            gPlayerAttachmentData[playerid][i][e_attachment_db] = cache_get_field_content_int(i, "ID");

            gPlayerAttachmentData[playerid][i][e_attachment_index] = cache_get_field_content_int(i, "Index");
            gPlayerAttachmentData[playerid][i][e_attachment_model] = cache_get_field_content_int(i, "Model");
            gPlayerAttachmentData[playerid][i][e_attachment_bone] = cache_get_field_content_int(i, "Bone");

            gPlayerAttachmentData[playerid][i][e_attachment_x] = cache_get_field_content_float(i, "X");
            gPlayerAttachmentData[playerid][i][e_attachment_y] = cache_get_field_content_float(i, "Y");
            gPlayerAttachmentData[playerid][i][e_attachment_z] = cache_get_field_content_float(i, "Z");

            gPlayerAttachmentData[playerid][i][e_attachment_rx] = cache_get_field_content_float(i, "RX");
            gPlayerAttachmentData[playerid][i][e_attachment_ry] = cache_get_field_content_float(i, "RY");
            gPlayerAttachmentData[playerid][i][e_attachment_rz] = cache_get_field_content_float(i, "RZ");

            gPlayerAttachmentData[playerid][i][e_attachment_sx] = cache_get_field_content_float(i, "SX");
            gPlayerAttachmentData[playerid][i][e_attachment_sy] = cache_get_field_content_float(i, "SY");
            gPlayerAttachmentData[playerid][i][e_attachment_sz] = cache_get_field_content_float(i, "SZ");

            gPlayerAttachmentData[playerid][i][e_attachment_col_1] = cache_get_field_content_int(i, "Col1");
            gPlayerAttachmentData[playerid][i][e_attachment_col_2] = cache_get_field_content_int(i, "Col2");
        }
        GivePlayerAttachments(playerid);
	}
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerSpawn(playerid)
{
	if(IsPlayerNPC(playerid))
		return 1;

    if(!gPlayerAlreadySpawned[playerid])
    {
        LoadPlayerAttachments(playerid);
        gPlayerAlreadySpawned[playerid] = true;
    }
	else
		GivePlayerAttachments(playerid);
	return 1;
}

//------------------------------------------------------------------------------

hook OnGameModeInit()
{
    mysql_tquery(gMySQL,
	"CREATE TABLE IF NOT EXISTS `attachments` (`ID` int(11) NOT NULL AUTO_INCREMENT, `user_id` INT(11),\
	`Index` INT(11), `Model` INT(11), `Bone` INT(11),\
    `X` FLOAT, `Y` FLOAT, `Z` FLOAT,\
    `RX` FLOAT, `RY` FLOAT, `RZ` FLOAT,\
    `SX` FLOAT, `SY` FLOAT, `SZ` FLOAT,\
    `Col1` INT(11), `Col2` INT(11),\
	PRIMARY KEY (ID), KEY (ID)) ENGINE = InnoDB DEFAULT CHARSET = latin1 AUTO_INCREMENT = 1;");
    gPickupID = CreateDynamicPickup(18645, 1, 206.3237, -100.5559, 1005.2578, 0, 15);
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
    if(pickupid == gPickupID && !gIsDialogVisible[playerid] && gPlayerTickCount[playerid] < GetTickCount())
    {
        CallRemoteFunction("OnPlayerCommandText", "is", playerid, "/selectattachment");
        gIsDialogVisible[playerid] = true;
    }
}

//------------------------------------------------------------------------------

hook OnPlayerDisconnect(playerid, reason)
{
	SavePlayerAttachments(playerid);
    ResetPlayerAttachments(playerid);
    gIsDialogVisible[playerid] = false;
    gIsPlayerEditing[playerid] = false;
	gPlayerAlreadySpawned[playerid] = false;
    return 1;
}

//------------------------------------------------------------------------------

hook OnPlayerEditAttachedObj(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
    if(gIsPlayerEditing[playerid])
    {
        for (new i = 0; i < MAX_PLAYER_ATTACHED_ITEMS; i++)
        {
            if(index != gPlayerAttachmentData[playerid][i][e_attachment_index])
                continue;

            if(response)
            {
                gPlayerAttachmentData[playerid][i][e_attachment_x] = fOffsetX;
                gPlayerAttachmentData[playerid][i][e_attachment_y] = fOffsetY;
                gPlayerAttachmentData[playerid][i][e_attachment_z] = fOffsetZ;

                gPlayerAttachmentData[playerid][i][e_attachment_rx] = fRotX;
                gPlayerAttachmentData[playerid][i][e_attachment_ry] = fRotY;
                gPlayerAttachmentData[playerid][i][e_attachment_rz] = fRotZ;

                gPlayerAttachmentData[playerid][i][e_attachment_sx] = fScaleX;
                gPlayerAttachmentData[playerid][i][e_attachment_sy] = fScaleY;
                gPlayerAttachmentData[playerid][i][e_attachment_sz] = fScaleZ;

				SetPlayerAttachedObject(playerid, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
				SendClientMessage(playerid, 0xFFFFFFFF, "* {CCFF00}Accessory{ffffff} saved.");
            }
            else
            {
                new Float:x = gPlayerAttachmentData[playerid][i][e_attachment_x];
                new Float:y = gPlayerAttachmentData[playerid][i][e_attachment_y];
                new Float:z = gPlayerAttachmentData[playerid][i][e_attachment_z];

                new Float:rx = gPlayerAttachmentData[playerid][i][e_attachment_rx];
                new Float:ry = gPlayerAttachmentData[playerid][i][e_attachment_ry];
                new Float:rz = gPlayerAttachmentData[playerid][i][e_attachment_rz];

                new Float:sx = gPlayerAttachmentData[playerid][i][e_attachment_sx];
                new Float:sy = gPlayerAttachmentData[playerid][i][e_attachment_sy];
                new Float:sz = gPlayerAttachmentData[playerid][i][e_attachment_sz];

                SetPlayerAttachedObject(playerid, index, modelid, boneid, x, y, z, rx, ry, rz, sx, sy, sz);
				SendClientMessage(playerid, 0xFFFFFFFF, "* You canceled the edition of {CCFF00}accessory{ffffff}.");
            }
            break;
        }
        gIsPlayerEditing[playerid] = false;
    }
    return 1;
}

//------------------------------------------------------------------------------

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_ATTACHMENTS_CATEGORY)
    {
		gPlayerSelectedCategory[playerid] = listitem;
        if(!response)
        {
            PlayCancelSound(playerid);
            return -2;
        }

        new caption[32], buffer[64], info[1024];
        strcat(info, "Name\tPrice");
        for(new i = 0; i < sizeof(attachments_data); i++)
        {
			if(listitem == attachments_data[i][2][0])
			{
				format(buffer, sizeof(buffer), "\n%s\t$%d", attachments_data[i][3], attachments_data[i][0]);
            	strcat(info, buffer);
			}
        }
        format(caption, sizeof(caption), "Accessories->%s", attachments_category[listitem]);
        ShowPlayerDialog(playerid, DIALOG_ATTACHMENTS_CATEGORY + (listitem+1), DIALOG_STYLE_TABLIST_HEADERS, caption, info, "Select", "X");
        PlaySelectSound(playerid);
        return -2;
    }
    else if(dialogid == DIALOG_ATTACHMENTS_BONE)
    {
        new i = gPlayerSelectedIndex[playerid];
        gIsPlayerEditing[playerid] = true;
		gPlayerAttachmentData[playerid][i][e_attachment_bone] = (listitem + 1);
		SetPlayerAttachedObject(playerid, i, gPlayerAttachmentData[playerid][i][e_attachment_model], (listitem + 1));
        EditAttachedObject(playerid, i);
        PlaySelectSound(playerid);
        return -2;
    }
    else if(dialogid == DIALOG_ATTACHMENTS_REMOVE)
	{
		if(!response)
		{
			PlayCancelSound(playerid);
			return -2;
		}
		SendClientMessage(playerid, 0xFFFFFFFF, "* You removed the {CCFF00}accessory{ffffff}.");
		DeletePlayerAttachment(playerid, listitem);
	}
    else if(dialogid == DIALOG_ATTACHMENTS_EDIT)
	{
		if(!response)
		{
			PlayCancelSound(playerid);
			return -2;
		}
		gPlayerSelectedIndex[playerid] = listitem;
		ShowPlayerDialog(playerid, DIALOG_ATTACHMENTS_BONE, DIALOG_STYLE_TABLIST, "Which bone you want to attach the accessory?",
        "1\tPimple\n2\tHead\n3\tUpper left arm\n4\tRight upper arm\n5\tLeft hand\n6\tRight hand\n7\tLeft thigh\n8\tRight thigh\n9\tLeft foot\n10\tRight foot\n11\tRight Calfa\n12\tLeft CALF\n13\tLower left arm\n14\tRight -hand man\n15\tLeft shoulder\n16\tRight shoulder\n17\tNeck\n18\tJaw",
        "Edit", "");
	}
    else if(dialogid >= (DIALOG_ATTACHMENTS_CATEGORY+1) && dialogid <= (DIALOG_ATTACHMENTS_CATEGORY+sizeof(attachments_category)))
    {
        if(!response)
        {
            new info[128];
            for(new i = 0; i < sizeof(attachments_category); i++)
            {
                if(i > 0) strcat(info, "\n");
                strcat(info, attachments_category[i]);
            }
            ShowPlayerDialog(playerid, DIALOG_ATTACHMENTS_CATEGORY, DIALOG_STYLE_LIST, "Accessories", info, "Select", "X");
            PlayCancelSound(playerid);
            return -2;
        }

        new free_index = -1;
        for (new i = 0; i < MAX_PLAYER_ATTACHED_ITEMS; i++)
        {
            if(gPlayerAttachmentData[playerid][i][e_attachment_db] == 0)
            {
                free_index = i;
                break;
            }
        }

		new category = 0, sc = gPlayerSelectedCategory[playerid];
		for (new i = 0; i < sizeof(attachments_data); i++)
		{
			if(attachments_data[i][2][0] == sc)
				break;
			category++;
		}

        if(free_index == -1)
        {
            SendClientMessage(playerid, COLOR_ERROR, "* You cannot load more accessories.");
            PlayErrorSound(playerid);
            return -2;
        }
		else if(GetPlayerCash(playerid) < attachments_data[(listitem+category)][0][0])
		{
			SendClientMessage(playerid, COLOR_ERROR, "* You do not have enough money.");
            PlayErrorSound(playerid);
            return -2;
		}

		GivePlayerCash(playerid, -attachments_data[(listitem+category)][0][0]);

        gPlayerAttachmentData[playerid][free_index][e_attachment_model] = attachments_data[(listitem+category)][1][0];
        gPlayerAttachmentData[playerid][free_index][e_attachment_index] = free_index;
        gPlayerSelectedIndex[playerid] = free_index;

        ShowPlayerDialog(playerid, DIALOG_ATTACHMENTS_BONE, DIALOG_STYLE_TABLIST, "Which bone you want to attach the accessory?",
        "1\tPimple\n2\tHead\n3\tUpper left arm\n4\tRight upper arm\n5\tLeft hand\n6\tRight hand\n7\tLeft thigh\n8\tRight thigh\n9\tLeft foot\n10\tRight foot\n11\tRight Calfa\n12\tLeft CALF\n13\tLower left arm\n14\tRight -hand man\n15\tLeft shoulder\n16\tRight shoulder\n17\tNeck\n18\tJaw",
        "Edit", "");

		SendClientMessage(playerid, 0xFFFFFFFF, "* Você comprou um {CCFF00}acessório{ffffff}! (/ajudaacessorio)");

        gIsDialogVisible[playerid] = false;
        gPlayerTickCount[playerid] = GetTickCount() + 2500;
        SetPlayerPos(playerid, 217.4102, -98.5851, 1005.2578);
        SetPlayerFacingAngle(playerid, 270.5558);
        SetCameraBehindPlayer(playerid);

		new query[220];
        mysql_format(gMySQL, query, sizeof(query), "INSERT INTO `attachments` (`user_id`, `Index`, `Model`, `Bone`, `X`, `Y`, `Z`, `RX`, `RY`, `RZ`, `SX`, `SY`, `SZ`, `Col1`, `Col2`) VALUES (%d, %d, %d, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0)", GetPlayerDatabaseID(playerid), free_index, attachments_data[(listitem+category)][1]);
    	mysql_tquery(gMySQL, query, "OnInsertAttachmentOnDatabase", "ii", playerid, free_index);
        return -2;
    }
    return 1;
}

//------------------------------------------------------------------------------

public OnInsertAttachmentOnDatabase(playerid, index)
{
    gPlayerAttachmentData[playerid][index][e_attachment_db] = cache_insert_id();
    return 1;
}

//------------------------------------------------------------------------------

YCMD:ajudaacessorio(playerid, params[], help)
{
	SendClientMessage(playerid, COLOR_TITLE, "----------------------------- ACCESSORY COMMANDS -----------------------------");
	SendClientMessage(playerid, COLOR_SUB_TITLE, "* /selectattachment - /editattach - /removeattach");
	SendClientMessage(playerid, COLOR_TITLE, "----------------------------- ACCESSORY COMMANDS -----------------------------");
	return 1;
}

//------------------------------------------------------------------------------

YCMD:selectattachment(playerid, params[], help)
{
    new info[128];
    for(new i = 0; i < sizeof(attachments_category); i++)
    {
        if(i > 0) strcat(info, "\n");
        strcat(info, attachments_category[i]);
    }
	PlaySelectSound(playerid);
    ShowPlayerDialog(playerid, DIALOG_ATTACHMENTS_CATEGORY, DIALOG_STYLE_LIST, "Accessories", info, "Select", "X");
    return 1;
}

//------------------------------------------------------------------------------

YCMD:editattach(playerid, params[], help)
{
    new items = 0, info[158];
    for (new i = 0; i < MAX_PLAYER_ATTACHED_ITEMS; i++)
    {
        if(gPlayerAttachmentData[playerid][i][e_attachment_db] != 0)
        {
            items++;

            for (new j = 0; j < sizeof(attachments_data); j++)
            {
                if(gPlayerAttachmentData[playerid][i][e_attachment_model] == attachments_data[j][1][0])
                {
                    if(i > 0) strcat(info, "\n");
                    strcat(info, attachments_data[j][3]);
					break;
                }
            }
        }
		else
		{
			if(i > 0) strcat(info, "\n");
			strcat(info, "None");
		}
    }

    if(items == 0)
        return SendClientMessage(playerid, COLOR_ERROR, "* You have no accessory.");

	PlaySelectSound(playerid);
    ShowPlayerDialog(playerid, DIALOG_ATTACHMENTS_EDIT, DIALOG_STYLE_LIST, "Edit Accessories", info, "Edit", "X");
    return 1;
}

//------------------------------------------------------------------------------

YCMD:removeattach(playerid, params[], help)
{
	new items = 0, info[158];
	for (new i = 0; i < MAX_PLAYER_ATTACHED_ITEMS; i++)
	{
		if(gPlayerAttachmentData[playerid][i][e_attachment_db] != 0)
		{
			items++;

			for (new j = 0; j < sizeof(attachments_data); j++)
			{
				if(gPlayerAttachmentData[playerid][i][e_attachment_model] == attachments_data[j][1][0])
				{
					if(i > 0) strcat(info, "\n");
					strcat(info, attachments_data[j][3]);
					break;
				}
			}
		}
		else
		{
			if(i > 0) strcat(info, "\n");
			strcat(info, "None");
		}
	}

	if(items == 0)
		return SendClientMessage(playerid, COLOR_ERROR, "* You have no accessory.");
	PlaySelectSound(playerid);
    ShowPlayerDialog(playerid, DIALOG_ATTACHMENTS_REMOVE, DIALOG_STYLE_LIST, "To remove Accessories", info, "Delete", "X");
	return 1;
}
