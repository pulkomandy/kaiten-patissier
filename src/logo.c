#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "logo.h" 


// 関数プロトタイプ
void logo_main( void );
void logo_init( void );
void logo_relese( void );
void logo_keys( void );
void logo_drow( void );
void logo_init_save_data( void );

// 変数宣言
static int scene_exit;
static int demo;
static int demo2;


//----------------------------------------------------------------------
// メイン関数
void logo_main( void )
{
	int exit_code;
	
	exit_code = 0;
	
	logo_init( );		// 初期化
	
	while( scene_exit )
	{
//		KeyInput( );	// キー入力
		
		logo_keys( );		// キー処理
		logo_drow( );		// 描画
		
		halt( );
//		SDL_Flip( g_screen );	// 描画
		FPSWait( );		// 待ち

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	logo_relese( );		// 終了
}

void logo_init( void )
{
	scene_exit = 1;
	demo = 0;
	demo2 = 0;
	
	LoadBitmap("image/a_logo.bmp",2,true);		//プレーンナンバー１にタイトル画面背景を読み込む
	LoadBitmap("image/al_256.bmp",3,false);		//プレーンナンバー１にタイトル画面背景を読み込む

	soundStopBgm(EN_BGM_GAME01);
}

void logo_relese( void )
{
	int i;
	
	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		ReleaseBitmap( i );
	}
	soundStopBgm(EN_BGM_GAME01);

}


void logo_keys( void )
{
	//	上下キーに応じて移動
	if (IsPushKey(gameflag[0]))
	{
	}
	if (IsPushKey(gameflag[1]))
	{
	}
	if (IsPushKey(gameflag[2]))
	{
	}
	if (IsPushKey(gameflag[3]))
	{
	}

	//	スペースキーが押される
	if ( ( IsPushKey(gameflag[4]) ) || ( IsPushKey(gameflag[5]) ) || ( demo2 >= 2 ) )
	{
		if ( demo2 >= 2 )
		{
			gameflag[40] = 0;					/* タイトル */
			g_scene = EN_SN_TITLE;
			scene_exit=0;
			return;
		}
		else 
		{
			demo2++;
		}
	}

}

void logo_drow( void )
{
	//背景クリア
	ClearSecondary();

	demo++;
	
	switch( demo2 )
	{
	case 0:
		Blt( 3, 0, 0 );		/* 320 * 240 */
		if ( demo >= ( 60 * 3 ) )
		{
			demo = 0;
			demo2++;
		}
		break;
	case 1:
		Blt( 2, 0, 0 );		/* 320 * 240 */
		if ( demo >= ( 60 * 3 ) )
		{
			demo = 0;
			demo2 = 2;
		}
		break;
	default:
		break;
	}
	
	
	//キー入力検査
	KeyInput();				

}


