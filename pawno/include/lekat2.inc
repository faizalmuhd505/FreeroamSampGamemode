//Player Attachments system by Excel
//==============================================================================
#include <a_samp>
#include <mSelection>
#include <sscanf2>
#include <dini>
#include <zcmd>
//==============================================================================
#define DIALOG_ATTACH_INDEX             13500
#define DIALOG_ATTACH_INDEX_SELECTION   DIALOG_ATTACH_INDEX+1
#define DIALOG_ATTACH_EDITREPLACE       DIALOG_ATTACH_INDEX+2
#define DIALOG_ATTACH_MODEL_SELECTION   DIALOG_ATTACH_INDEX+3
#define DIALOG_ATTACH_BONE_SELECTION    DIALOG_ATTACH_INDEX+4
#define DIALOG_ATTACH_OBJECT_SELECTION  DIALOG_ATTACH_INDEX+5
#define DIALOG_ATTACH_OBJECT2_SELECTION DIALOG_ATTACH_INDEX+6
//==============================================================================
#define MAX_OSLOTS  MAX_PLAYER_ATTACHED_OBJECTS
//==============================================================================
#define 	COL_WHITE       "{FFFFFF}"
#define 	COL_BLACK       "{0E0101}"
#define 	COL_GREY        "{C3C3C3}"
#define 	COL_GREEN       "{6EF83C}"
#define 	COL_RED         "{F81414}"
#define 	COL_YELLOW      "{F3FF02}"
#define 	COL_ORANGE      "{FFAF00}"
#define 	COL_LIME        "{B7FF00}"
#define 	COL_CYAN        "{00FFEE}"
#define 	COL_BLUE        "{0049FF}"
#define 	COL_MAGENTA     "{F300FF}"
#define 	COL_VIOLET      "{B700FF}"
#define 	COL_PINK        "{FF00EA}"
#define 	COL_MARONE      "{A90202}"
//==============================================================================
new AttachmentObjectsList[] = {
18632,
18633,
18634,
18635,
18636,
18637,
18638,
18639,
18640,
18975,
19136,
19274,
18641,
18642,
18643,
18644,
18645,
18865,
18866,
18867,
18868,
18869,
18870,
18871,
18872,
18873,
18874,
18875,
18890,
18891,
18892,
18893,
18894,
18895,
18896,
18897,
18898,
18899,
18900,
18901,
18902,
18903,
18904,
18905,
18906,
18907,
18908,
18909,
18910,
18911,
18912,
18913,
18914,
18915,
18916,
18917,
18918,
18919,
18920,
18921,
18922,
18923,
18924,
18925,
18926,
18927,
18928,
18929,
18930,
18931,
18932,
18933,
18934,
18935,
18936,
18937,
18938,
18939,
18940,
18941,
18942,
18943,
18944,
18945,
18946,
18947,
18948,
18949,
18950,
18951,
18952,
18953,
18954,
18955,
18956,
18957,
18958,
18959,
18960,
18961,
18962,
18963,
18964,
18965,
18966,
18967,
18968,
18969,
18970,
18971,
18972,
18973,
18974,
18976,
18977,
18978,
18979,
19006,
19007,
19008,
19009,
19010,
19011,
19012,
19013,
19014,
19015,
19016,
19017,
19018,
19019,
19020,
19021,
19022,
19023,
19024,
19025,
19026,
19027,
19028,
19029,
19030,
19031,
19032,
19033,
19034,
19035,
19036,
19037,
19038,
19039,
19040,
19041,
19042,
19043,
19044,
19045,
19046,
19047,
19048,
19049,
19050,
19051,
19052,
19053,
19085,
19086,
19090,
19091,
19092,
19093,
19094,
19095,
19096,
19097,
19098,
19099,
19100,
19101,
19102,
19103,
19104,
19105,
19106,
19107,
19108,
19109,
19110,
19111,
19112,
19113,
19114,
19115,
19116,
19117,
19118,
19119,
19120,
19137,
19138,
19139,
19140,
19141,
19142,
19160,
19161,
19162,
19163,
19317,
19318,
19319,
19330,
19331,
19346,
19347,
19348,
19349,
19350,
19351,
19352,
19487,
19488,
19513,
19515,
331,
333,
334,
335,
336,
337,
338,
339,
341,
321,
322,
323,
324,
325,
326,
343,
346,
347,
348,
349,
350,
351,
352,
353,
355,
356,
372,
357,
358,
361,
363,
364,
365,
366,
367,
368,
369,
371
};
//==============================================================================
new AttachmentBones[][24] = {
{"Spine"},
{"Head"},
{"Left upper arm"},
{"Right upper arm"},
{"Left hand"},
{"Right hand"},
{"Left thigh"},
{"Right thigh"},
{"Left foot"},
{"Right foot"},
{"Right calf"},
{"Left calf"},
{"Left forearm"},
{"Right forearm"},
{"Left clavicle"},
{"Right clavicle"},
{"Neck"},
{"Jaw"}
};
//==============================================================================
CMD:lekat2(playerid,params[])
{
	new string[128];
	new dialog[500];
	for(new x;x<MAX_OSLOTS;x++)
	{
        if(IsPlayerAttachedObjectSlotUsed(playerid, x))
		{	format(string, sizeof(string), ""COL_WHITE"Slot:%d :: "COL_GREEN"Used Slot\n", x);    }
		else format(string, sizeof(string), ""COL_WHITE"Slot:%d\n", x);
		strcat(dialog,string);
   	}
   	ShowPlayerDialog(playerid, DIALOG_ATTACH_INDEX_SELECTION, DIALOG_STYLE_LIST,"Player Objects/Attachment: (Select Slot)", dialog, "Select", "Close(X)");
	return 1;
}
CMD:att(playerid,params[])
{
	return cmd_lekat2(playerid,params);
}
CMD:attachments(playerid,params[])
{
	return cmd_lekat2(playerid,params);
}
//==============================================================================
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_ATTACH_INDEX_SELECTION:
        {
            if(response)
            {
                if(IsPlayerAttachedObjectSlotUsed(playerid, listitem))
                {
                    ShowPlayerDialog(playerid, DIALOG_ATTACH_EDITREPLACE, DIALOG_STYLE_MSGBOX, \
                    "Player Objects/Attachment: (Delete/Edit)", ""COL_WHITE"Do you wish to edit the attachment in that slot, or delete it?", "Edit(!)", "Delete(X)");
                }
                else
                {
					ShowPlayerDialog(playerid,DIALOG_ATTACH_OBJECT_SELECTION,DIALOG_STYLE_LIST,"Player Objects/Attachment: (Select Object Path)","Path:1 :: "COL_GREY"Player Objects Menu\n"COL_WHITE"Path:2 :: "COL_GREY"Custom Object","Next(>>)","Back(<<)");
     			}
                SetPVarInt(playerid, "AttachmentIndexSel", listitem);
            }
            return 1;
        }
        case DIALOG_ATTACH_OBJECT_SELECTION:
        {
            if(!response)
            {
                cmd_lekat2(playerid,"");
            }
            if(response)
            {
            	if(listitem==0) ShowModelSelectionMenuEx(playerid, AttachmentObjectsList, 228+38, "Player Objects", DIALOG_ATTACH_MODEL_SELECTION, 0.0, 0.0, 0.0, 1.0, 0x00000099, 0x000000EE, 0xACCBF1FF);
            	if(listitem==1) ShowPlayerDialog(playerid,DIALOG_ATTACH_OBJECT2_SELECTION,DIALOG_STYLE_INPUT,"Player Objects/Attachment: (Insert objectid)",""COL_WHITE"Put your custom objectid below, You can also take help from ''http://wiki.sa-mp.com''.","Edit","Back(<<)");
			}
		}
        case DIALOG_ATTACH_OBJECT2_SELECTION:
        {
            if(!response)
            {   ShowPlayerDialog(playerid,DIALOG_ATTACH_OBJECT_SELECTION,DIALOG_STYLE_LIST,"Player Objects/Attachment: (Select Object Path)","Path:1 :: "COL_GREY"Player Objects Menu\n"COL_WHITE"Path:2 :: "COL_GREY"Custom Object","Next(>>)","Back(<<)");    }
			if(response)
			{
				if(!strlen(inputtext))return SendClientMessage(playerid,-1,"PLAYER: You can't leave the coloumn blank."),ShowPlayerDialog(playerid,DIALOG_ATTACH_OBJECT2_SELECTION,DIALOG_STYLE_INPUT,"Player Objects/Attachment: (Insert objectid)",""COL_WHITE"Put your custom objectid below, You can also take help from ''http://wiki.sa-mp.com''.","Edit","Back(<<)");
				if(!IsNumeric(inputtext)) return SendClientMessage(playerid,-1,"PLAYER: You can't fill a object name, only object id's allowed."),ShowPlayerDialog(playerid,DIALOG_ATTACH_OBJECT2_SELECTION,DIALOG_STYLE_INPUT,"Player Objects/Attachment: (Insert objectid)",""COL_WHITE"Put your custom objectid below, You can also take help from ''http://wiki.sa-mp.com''.","Edit","Back(<<)");
				new obj;
			    if(!sscanf(inputtext, "i", obj))
				{
					if(GetPVarInt(playerid, "AttachmentUsed") == 1) EditAttachedObject(playerid, obj);
				    else
				    {
					    SetPVarInt(playerid, "AttachmentModelSel", obj);
					    new string[256+1];
					    new dialog[500];
					    for(new x;x<sizeof(AttachmentBones);x++)
					    {
					     	format(string, sizeof(string), "Bone:%s\n", AttachmentBones[x]);
					     	strcat(dialog,string);
					    }
						ShowPlayerDialog(playerid, DIALOG_ATTACH_BONE_SELECTION, DIALOG_STYLE_LIST, \
					 	"{FF0000}Attachment Modification - Bone Selection", dialog, "Select", "Cancel");
				    }
				}
			}
        }
        case DIALOG_ATTACH_EDITREPLACE:
        {
            if(response) EditAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));
            else
			{
			    RemovePlayerAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));
            	new file[128];
			    new name[24];
			    new x=GetPVarInt(playerid, "AttachmentIndexSel");
			    new f1[15],f2[15],f3[15],f4[15],f5[15],f6[15],f7[15],f8[15],f9[15],f10[15],f11[15];
			    GetPlayerName(playerid,name,24);
			    format(file,sizeof(file), "Leaders/%s.ini",name);
			    if(!dini_Exists(file)) return 1;
			    format(f1,15,"O_Model_%d",x);
			    format(f2,15,"O_Bone_%d",x);
				format(f3,15,"O_OffX_%d",x);
			    format(f4,15,"O_OffY_%d",x);
			    format(f5,15,"O_OffZ_%d",x);
			    format(f6,15,"O_RotX_%d",x);
			    format(f7,15,"O_RotY_%d",x);
			    format(f8,15,"O_RotZ_%d",x);
			    format(f9,15,"O_ScaleX_%d",x);
			    format(f10,15,"O_ScaleY_%d",x);
			    format(f11,15,"O_ScaleZ_%d",x);
			    dini_Unset(file,f1);
			    dini_Unset(file,f2);
			    dini_Unset(file,f3);
			    dini_Unset(file,f4);
			    dini_Unset(file,f5);
			    dini_Unset(file,f6);
			    dini_Unset(file,f7);
			    dini_Unset(file,f8);
			    dini_Unset(file,f9);
			    dini_Unset(file,f10);
			    dini_Unset(file,f11);
				DeletePVar(playerid, "AttachmentIndexSel");
            }
			return 1;
        }
        case DIALOG_ATTACH_BONE_SELECTION:
        {
            if(response)
            {
                SetPlayerAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"), GetPVarInt(playerid, "AttachmentModelSel"), listitem+1);
                EditAttachedObject(playerid, GetPVarInt(playerid, "AttachmentIndexSel"));
                SendClientMessage(playerid, 0xFFFFFFFF, "PLAYER: You can also hold SPAWN and use MOUSE to view from either sides.");
            }
            DeletePVar(playerid, "AttachmentIndexSel");
            DeletePVar(playerid, "AttachmentModelSel");
            return 1;
        }
    }
    return 0;
}
//==============================================================================
public OnPlayerEditAttachedObject( playerid, response, index, modelid, boneid,
                                   Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,
                                   Float:fRotX, Float:fRotY, Float:fRotZ,
                                   Float:fScaleX, Float:fScaleY, Float:fScaleZ )
{
    /*new debug_string[256+1];
	format(debug_string,256,"SetPlayerAttachedObject(playerid,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f)",
        index,modelid,boneid,fOffsetX,fOffsetY,fOffsetZ,fRotX,fRotY,fRotZ,fScaleX,fScaleY,fScaleZ);*/

    SetPlayerAttachedObject(playerid,index,modelid,boneid,fOffsetX,fOffsetY,fOffsetZ,fRotX,fRotY,fRotZ,fScaleX,fScaleY,fScaleZ);
    SendClientMessage(playerid, 0xFFFFFFFF, "PLAYER: You have finished editing attachments, it has been saved to your database.");

    new file[128];
    new name[24];
    new f1[15],f2[15],f3[15],f4[15],f5[15],f6[15],f7[15],f8[15],f9[15],f10[15],f11[15];
    GetPlayerName(playerid,name,24);
    format(file,sizeof(file), "Leaders/%s.ini",name);
    if(!dini_Exists(file)) return 1;
    format(f1,15,"O_Model_%d",index);
    format(f2,15,"O_Bone_%d",index);
	format(f3,15,"O_OffX_%d",index);
    format(f4,15,"O_OffY_%d",index);
    format(f5,15,"O_OffZ_%d",index);
    format(f6,15,"O_RotX_%d",index);
    format(f7,15,"O_RotY_%d",index);
    format(f8,15,"O_RotZ_%d",index);
    format(f9,15,"O_ScaleX_%d",index);
    format(f10,15,"O_ScaleY_%d",index);
    format(f11,15,"O_ScaleZ_%d",index);
    dini_IntSet(file,f1,modelid);
    dini_IntSet(file,f2,boneid);
    dini_FloatSet(file,f3,fOffsetX);
    dini_FloatSet(file,f4,fOffsetY);
    dini_FloatSet(file,f5,fOffsetZ);
    dini_FloatSet(file,f6,fRotX);
    dini_FloatSet(file,f7,fRotY);
    dini_FloatSet(file,f8,fRotZ);
    dini_FloatSet(file,f9,fScaleX);
    dini_FloatSet(file,f10,fScaleY);
    dini_FloatSet(file,f11,fScaleZ);
    return 1;
}
//==============================================================================
public OnPlayerConnect(playerid)
{
    new file[128];
    new name[24];
    new f1[15],f2[15],f3[15],f4[15],f5[15],f6[15],f7[15],f8[15],f9[15],f10[15],f11[15];
    GetPlayerName(playerid,name,24);
    format(file,sizeof(file), "Leaders/%s.ini",name);
	if(!dini_Exists(file))
	{
	    dini_Create(file);
		for(new x;x<MAX_OSLOTS;x++)
		{
		    if(IsPlayerAttachedObjectSlotUsed(playerid, x))
		    {
			    format(f1,15,"O_Model_%d",x);
			    format(f2,15,"O_Bone_%d",x);
				format(f3,15,"O_OffX_%d",x);
			    format(f4,15,"O_OffY_%d",x);
			    format(f5,15,"O_OffZ_%d",x);
			    format(f6,15,"O_RotX_%d",x);
			    format(f7,15,"O_RotY_%d",x);
			    format(f8,15,"O_RotZ_%d",x);
			    format(f9,15,"O_ScaleX_%d",x);
			    format(f10,15,"O_ScaleY_%d",x);
			    format(f11,15,"O_ScaleZ_%d",x);
			    dini_IntSet(file,f1,0);
			    dini_IntSet(file,f2,0);
			    dini_FloatSet(file,f3,0.0);
			    dini_FloatSet(file,f4,0.0);
			    dini_FloatSet(file,f5,0.0);
			    dini_FloatSet(file,f6,0.0);
			    dini_FloatSet(file,f7,0.0);
			    dini_FloatSet(file,f8,0.0);
			    dini_FloatSet(file,f9,0.0);
			    dini_FloatSet(file,f10,0.0);
			    dini_FloatSet(file,f11,0.0);
			}
	 	}
	}
}
//==============================================================================
public OnPlayerSpawn(playerid)
{
    new file[128];
    new name[24];
    new f1[15],f2[15],f3[15],f4[15],f5[15],f6[15],f7[15],f8[15],f9[15],f10[15],f11[15];
    GetPlayerName(playerid,name,24);
    format(file,sizeof(file), "Leaders/%s.ini",name);
    if(!dini_Exists(file)) return 1;
    for(new x;x<MAX_OSLOTS;x++)
	{
	    format(f1,15,"O_Model_%d",x);
		format(f2,15,"O_Bone_%d",x);
		format(f3,15,"O_OffX_%d",x);
  		format(f4,15,"O_OffY_%d",x);
		format(f5,15,"O_OffZ_%d",x);
		format(f6,15,"O_RotX_%d",x);
		format(f7,15,"O_RotY_%d",x);
		format(f8,15,"O_RotZ_%d",x);
		format(f9,15,"O_ScaleX_%d",x);
		format(f10,15,"O_ScaleY_%d",x);
		format(f11,15,"O_ScaleZ_%d",x);
	    if(dini_Int(file,f1)!=0)
	    {
	        SetPlayerAttachedObject(playerid,x,dini_Int(file,f1),dini_Int(file,f2),dini_Float(file,f3),dini_Float(file,f4),dini_Float(file,f5),dini_Float(file,f6),dini_Float(file,f7),dini_Float(file,f8),dini_Float(file,f9),dini_Float(file,f10),dini_Float(file,f11));
		}
	}
	return 1;
}
//==============================================================================
public OnPlayerModelSelectionEx(playerid, response, extraid, modelid)
{
	if(extraid==DIALOG_ATTACH_MODEL_SELECTION)
	{
	    if(!response)
     	{   ShowPlayerDialog(playerid,DIALOG_ATTACH_OBJECT_SELECTION,DIALOG_STYLE_LIST,"Player Objects/Attachment: (Select Object Path)","Path:1 :: "COL_GREY"Player Objects Menu\n"COL_WHITE"Path:2 :: "COL_GREY"Custom Object","Next(>>)","Back(<<)");    }
	    if(response)
	    {
		    if(GetPVarInt(playerid, "AttachmentUsed") == 1) EditAttachedObject(playerid, modelid);
		    else
		    {
			    SetPVarInt(playerid, "AttachmentModelSel", modelid);
                new string[256+1];
				new dialog[500];
				for(new x;x<sizeof(AttachmentBones);x++)
    			{
					format(string, sizeof(string), "Bone:%s\n", AttachmentBones[x]);
					strcat(dialog,string);
				}
				ShowPlayerDialog(playerid, DIALOG_ATTACH_BONE_SELECTION, DIALOG_STYLE_LIST, \
				"{FF0000}Attachment Modification - Bone Selection", dialog, "Select", "Cancel");
		    }//else DeletePVar(playerid, "AttachmentIndexSel");
		}
 	}
	return 1;
}
//==============================================================================
stock IsNumeric(string[])
{
	for (new i = 0, j = strlen(string); i < j; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}
//==============================================================================
