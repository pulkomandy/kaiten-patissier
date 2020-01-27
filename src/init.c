#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <unistd.h>

#include "define.h"
#include "extern.h"
#include "function.h"
#include "util_snd.h"

#include "scene.h"

#ifdef GP2X
#include <unistd.h>
#endif

//#define MacOS

void main_init( void );
void main_init_config( void );
void ExitProgram(void);
int main(int argc, char *argv[]);


int main(int argc, char *argv[])
{
	SDL_Rect rect;
	Uint32 flags;
	SDL_Surface* tmp;
	char AppPath[1024];
	char AppPathw[1024];
	char *char_work;
	int strlen;

	/* 初期化 */
	memset( &AppPath[0], '\0', sizeof( AppPath ) );
	memset( &AppPathw[0], '\0', sizeof( AppPath ) );
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
		
#ifdef GP2X
#else
	#ifdef MacOS
		if ( argc > 0 )	// 起動に引数がある場合
		{
			strcpy( &AppPath[0], argv[0] );
	//		strcat( &AppPath[0], "/Contents/Recources/" );
			char_work = strrchr( &AppPath[0], '/' );
//			char_work = strrchr( &AppPath[0], '\\' );
			strlen = char_work - &AppPath[0];
			
			strncpy( &AppPathw[0], &AppPath[0], strlen );
			chdir( &AppPathw[0] );
//			LogFileWrite( "testlog.txt", &AppPathw[0] );
		}
	#else
	#endif
#endif	
	
	main_init_config( );	// 環境ファイルの読み込み

	/* 初期化画面サイズ */
#ifdef GP2X
	gameflag[61] = 1;	//画面倍率
	flags = SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWPALETTE;
#else
	gameflag[61] = 1;	//画面倍率
	flags = SDL_SWSURFACE;
	if ( argc > 1 )	// 起動に引数がある場合
	{
		while( *++argv != NULL )
		{ 
			if( **argv == '-' )
			{
				switch( *(*argv+1) )
				{
				case 'f':  /* -l オプション処理 */
					flags = SDL_FULLSCREEN  | SDL_SWSURFACE;
				case 'r':  /* -r オプション処理 */
					gameflag[61] = 2;	//画面倍率
				}
			}
			else
			{
				break;
			}
		}
//		if ( ( char * )argv[1] == "f" )
//		{
//			flags = SDL_FULLSCREEN  | SDL_SWSURFACE;
//		}
//		if ( ( char * )argv[2] == '2' )
//		{
//			gameflag[61] = 2;	//画面倍率
//		}
//		LogFileWrite( "testlog.txt", &( char * )argv[1] );
	}
#endif

//	g_screen = SDL_SetVideoMode(DISPLY_WIDTH, DISPLY_HEIGHT, 16, SDL_SWSURFACE);
//	g_screen = SDL_SetVideoMode(DISPLY_WIDTH, DISPLY_HEIGHT, 8, flags);
	g_screen = SDL_SetVideoMode(DISPLY_WIDTH * gameflag[61], DISPLY_HEIGHT * gameflag[61], 8, flags);
	rect.x = 0;
	rect.y = 0;
	rect.w = DISPLY_WIDTH;
	rect.h = DISPLY_HEIGHT;
//	SDL_SetClipRect( g_screen, &rect );
	
	tmp = SDL_LoadBMP("image/color.bmp");		//プレーンナンバー１にタイトル画面背景を読み込む
	SetGscreenPalette( tmp );
	SDL_FreeSurface(tmp);
	
	if (!g_screen)
	{
		fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
		return 1;
	}
	SDL_WM_SetCaption("RotateGear", "");
	
	SDL_ShowCursor(SDL_DISABLE);
	FunctionInit( );
//	soundInitBuffer();
	/* グローバル変数の初期化 */
	main_init( );


		
	scenemanager( );
	
	ExitProgram( );
	return 0;
}


void main_init( void )
{
	g_scene = EN_SN_LOGO;

	
	// ゲーム中の使用する音の読み込み
	soundLoadBuffer(EN_BGM_GAME01, (Uint8 *)"sound/bgm/01.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME02, (Uint8 *)"sound/bgm/02.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME03, (Uint8 *)"sound/bgm/03.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME04, (Uint8 *)"sound/bgm/04.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME05, (Uint8 *)"sound/bgm/05.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME06, (Uint8 *)"sound/bgm/06.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME07, (Uint8 *)"sound/bgm/07.ogg", 0);
	
	soundLoadBufferSE(EN_SE_ATK1   , (Uint8 *)"sound/se/atk1.wav" );
	soundLoadBufferSE(EN_SE_DAMEGE , (Uint8 *)"sound/se/damage.wav" );
	soundLoadBufferSE(EN_SE_L1     , (Uint8 *)"sound/se/l1.wav" );
	soundLoadBufferSE(EN_SE_LANDING, (Uint8 *)"sound/se/landing.wav" );
	soundLoadBufferSE(EN_SE_MSG    , (Uint8 *)"sound/se/msg.wav" );
	soundLoadBufferSE(EN_SE_SELECT , (Uint8 *)"sound/se/select.wav" );
	soundLoadBufferSE(EN_SE_SW     , (Uint8 *)"sound/se/sw.wav" );
	soundLoadBufferSE(EN_SE_JUMP   , (Uint8 *)"sound/se/jump.wav" );
	soundLoadBufferSE(EN_SE_PAWA   , (Uint8 *)"sound/se/puwa.wav" );
	soundLoadBufferSE(EN_SE_CL1   , (Uint8 *)"sound/se/se01.wav" );
	soundLoadBufferSE(EN_SE_CL2   , (Uint8 *)"sound/se/se02.wav" );
	soundLoadBufferSE(EN_SE_CL3   , (Uint8 *)"sound/se/se03.wav" );
	soundLoadBufferSE(EN_SE_CL4   , (Uint8 *)"sound/se/se04.wav" );
	soundLoadBufferSE(EN_SE_CL5   , (Uint8 *)"sound/se/se05.wav" );
	soundLoadBufferSE(EN_SE_CL21   , (Uint8 *)"sound/se/se06.wav" );
	soundLoadBufferSE(EN_SE_CL22   , (Uint8 *)"sound/se/se07.wav" );
	soundLoadBufferSE(EN_SE_CL23   , (Uint8 *)"sound/se/se08.wav" );
	soundLoadBufferSE(EN_SE_CL24   , (Uint8 *)"sound/se/se09.wav" );
	soundLoadBufferSE(EN_SE_CL25   , (Uint8 *)"sound/se/se10.wav" );

	Set_Volume( gameflag[60] );

}

void ExitProgram(void)
{

	soundStopBgm(0);
	soundStopSeAll();
	soundRelease();

	SaveGameFlag("save/config");
	
	closePAD();
//	closeSDL();
	SDL_Quit();

#ifdef GP2X
	chdir("/usr/gp2x");
	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
}


void main_init_config( void )
{
	int i;
	i = 0;
	
	if ( ! ( LoadGameFlag("save/config") == 0 ) )
	{
		/* ファイルが存在しない場合の初期値設定 */
		ResetGameFlag();
#ifdef GP2X
		gameflag[0]=GP2X_BUTTON_UP;		//上	Up
		gameflag[1]=GP2X_BUTTON_DOWN;	//下	Down
		gameflag[2]=GP2X_BUTTON_LEFT;	//左	Left
		gameflag[3]=GP2X_BUTTON_RIGHT;	//右	Right
		gameflag[4]=GP2X_BUTTON_X;	//Ａ	Z
		gameflag[5]=GP2X_BUTTON_B;	//Ｂ	X
		gameflag[6]=GP2X_BUTTON_Y;	//Ｃ	C
		gameflag[7]=GP2X_BUTTON_A;	//Ｄ	S
		gameflag[8]=GP2X_BUTTON_L;	//Ｄ	S
		gameflag[9]=GP2X_BUTTON_R;	//Ｄ	S
		gameflag[10]=GP2X_BUTTON_START;	//Ｄ	S
		gameflag[11]=GP2X_BUTTON_SELECT;	//Ｄ	S
#else 
		gameflag[0]=GP2X_BUTTON_UP;		//上	Up
		gameflag[1]=GP2X_BUTTON_DOWN;	//下	Down
		gameflag[2]=GP2X_BUTTON_LEFT;	//左	Left
		gameflag[3]=GP2X_BUTTON_RIGHT;	//右	Right
		gameflag[4]=GP2X_BUTTON_A;	//Ａ	Z
		gameflag[5]=GP2X_BUTTON_X;	//Ｂ	X
		gameflag[6]=GP2X_BUTTON_Y;	//Ｃ	C
		gameflag[7]=GP2X_BUTTON_B;	//Ｄ	S
		gameflag[8]=GP2X_BUTTON_L;	//Ｄ	S
		gameflag[9]=GP2X_BUTTON_R;	//Ｄ	S
		gameflag[10]=GP2X_BUTTON_START;	//Ｄ	S
		gameflag[11]=GP2X_BUTTON_SELECT;	//Ｄ	S
		gameflag[61] = 2;	//画面倍率
#endif
		
		gameflag[60] = 128;	//音量

		gameflag[70] = 1;	//タイトル画面から来た
		gameflag[71] = 1;	//リトライを選択した


		gameflag[100] = 0;	//クリアフラグ
		
		gameflag[107] = 0;	//play time s
		gameflag[108] = 0;	//play time s
		gameflag[109] = 0;	//play time m
		gameflag[110] = 0;	//play time h
		gameflag[111] = 59;	//CLEAR time s
		gameflag[112] = 59;	//CLEAR time m
		gameflag[113] = 99;	//CLEAR time h
		
		
		gameflag[120] = 1;	//ステージセレクト
		gameflag[121] = 1;	//到達ステージ
		gameflag[122] = 0;	//キャラセレクト
		gameflag[123] = -1;	//リプレイ選択時のステージ
		gameflag[124] = 0;	//リプレイＡＬＬ、ＯＮＥ
		gameflag[125] = 0;	//リプレイjamp
		gameflag[126] = 0;	//裏面
		gameflag[127] = 0;	//トータルアタック
		gameflag[128] = 0;	//マップビュー
		gameflag[129] = 0;	//ステージセレクトから開始
		
		gameflag[131] = 0;	//言語
		gameflag[132] = 0;	//リプレイ
		gameflag[133] = 1;	//up key use
		gameflag[134] = 0;	//開始演出の有無

		gameflag[135] = 0;	//トータルアタック 時間					[130]>[135]
		gameflag[136] = 0;	//トータルアタック ミス				[131]>[136]
		gameflag[137] = 1595959;	//トータルアタック クリア時間	[132]>[137]
		gameflag[138] = 999;	//トータルアタック クリアミス	[133]>[138]
		
		for ( i = 0; i <= 99; i++ )
		{
			gameflag[200 + i] = 1105959;
		}
		for ( i = 0; i <= 99; i++ )
		{
			gameflag[300 + i] = 99;
		}
		for ( i = 0; i <= 99; i++ )
		{
			gameflag[400 + i] = 0;
		}
	}
// for debug start
/*
		for ( i = 0; i <= 99; i++ )
		{
			gameflag[400 + i] = 1;
		}
*/
// for debug end
	gameflag[121] = 50;	//到達ステージ
//	gameflag[100] = 1;	//到達ステージ
	
	g_DebugDisp 				= GetConfig( CONFIGFILE_NAME , "DebugDisp" );
	g_DebugStageProduction 		= GetConfig( CONFIGFILE_NAME , "DebugStageProduction" );
}




