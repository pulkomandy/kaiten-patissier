#include "gp2x.h"

#ifndef __DEFINE
#define __DEFINE

#define WP 65536
#define WWP (WP*2)

#define true 1
#define false 0

//設定ファイルの内容
#define CONFIGFILE_NAME "debug.txt"

#define DISPLY_WIDTH (320)
#define DISPLY_HEIGHT (240)
#define DISPLY_WIDTH_WP (320*WP)
#define DISPLY_HEIGHT_WP (240*WP)

#define BMPBUFF_MAX (128)

#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_Y               (14)
#define GP2X_BUTTON_X               (15)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)
#define GP2X_BUTTON_EXIT            (19)
#define GP2X_BUTTON_MAX             (20)


#define VOL_MAX (128)

enum  
{
	EN_SN_EXIT = 0,
	EN_SN_TITLE,
	EN_SN_ACT,
	EN_SN_OPTION,
	EN_SN_ENDING,
	EN_SN_LOGO,
	EN_SN_STAGESELECT,
	EN_SN_DEMO,
} DISP_SCENE;

enum {
	EN_BGM_GAME01 = 0,
	EN_BGM_GAME02,
	EN_BGM_GAME03,
	EN_BGM_GAME04,
	EN_BGM_GAME05,
	EN_BGM_GAME06,
	EN_BGM_GAME07,

	EN_BGM_END   ,
};
enum {
	EN_SE_ATK1 = 0,
	EN_SE_DAMEGE ,
	EN_SE_L1     ,
	EN_SE_LANDING,
	EN_SE_MSG    ,
	EN_SE_SELECT ,
	EN_SE_SW     ,
	EN_SE_JUMP   ,
	EN_SE_PAWA   ,
	EN_SE_CL1   ,
	EN_SE_CL2   ,
	EN_SE_CL3   ,
	EN_SE_CL4   ,
	EN_SE_CL5   ,
	EN_SE_CL21   ,
	EN_SE_CL22   ,
	EN_SE_CL23   ,
	EN_SE_CL24   ,
	EN_SE_CL25   ,

	EN_SE_END   ,
};



#endif


