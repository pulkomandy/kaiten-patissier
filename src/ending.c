#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "ending.h" 


// 関数プロトタイプ
void ending_main( void );
void ending_init( void );
void ending_relese( void );
void ending_keys( void );
void ending_drow( void );
void ending_init_save_data( void );


// 変数宣言
static int scene_exit;
static int demo[10];
static int end_type;
static long target_save[1024];

static char string[1024];

//----------------------------------------------------------------------
// メイン関数
void ending_main( void )
{
	int exit_code;
	
	exit_code = 0;
	
	ending_init( );		// 初期化
	
	while( scene_exit )
	{
//		KeyInput( );	// キー入力
		
		ending_keys( );		// キー処理
		ending_drow( );		// 描画
		
		halt( );
//		SDL_Flip( g_screen );	// 描画
		FPSWait( );		// 待ち

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	ending_relese( );		// 終了
}

void ending_init( void )
{
	int stage_hosei;
	int x;
	int y;
	int stage_no;
	int tergetnam;
	//-----------------------------------------------------------------------------------
	tergetnam = 0;
	stage_hosei = 0;
	end_type = 0;

	if ( gameflag[126] == 1 )
	{
		stage_hosei = 50;
	}
	scene_exit = 1;
	memset( target_save, 0, sizeof( target_save ) );
	memset( demo, 0, sizeof( demo ) );

	LoadBitmap("image/bak/1_256.bmp",1,false);		//プレーンナンバー１にタイトル画面背景を読み込む
	sprintf(string, "image/end%d/%d.bmp", ( int )gameflag[131] , ( int )1 );
	LoadBitmap(string,2,true);		//プレーンナンバー１にタイトル画面背景を読み込む
	sprintf(string, "image/end%d/%d.bmp", ( int )gameflag[131] , ( int )2 );
	LoadBitmap(string,3,true);		//プレーンナンバー１にタイトル画面背景を読み込む
	sprintf(string, "image/end%d/%d.bmp", ( int )gameflag[131] , ( int )3 );
	LoadBitmap(string,4,true);		//プレーンナンバー１にタイトル画面背景を読み込む
	sprintf(string, "image/end%d/%d.bmp", ( int )gameflag[131] , ( int )4 );
	LoadBitmap(string,5,true);		//プレーンナンバー１にタイトル画面背景を読み込む
	sprintf(string, "image/end%d/%d.bmp", ( int )gameflag[131] , ( int )5 );
	LoadBitmap(string,6,true);		//プレーンナンバー１にタイトル画面背景を読み込む

	LoadBitmap("image/end0/end1.bmp",10,true);		//プレーンナンバー１にタイトル画面背景を読み込む
	LoadBitmap("image/end0/end2.bmp",11,true);		//プレーンナンバー１にタイトル画面背景を読み込む

	LoadBitmap("image/sys/waku.bmp",109,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	soundPlayBgm( EN_BGM_GAME07 );

	LoadFile( "save/target", &target_save[0], sizeof( target_save ) );
	tergetnam = 0;
	for ( x = 0; x < 5; x++ )
	{
		for ( y = 0; y < 10; y++ )
		{
			stage_no = ( ( x ) * 10 ) + ( y + 1 );
			//トロフィーの表示
			//タイム
			if ( target_save[200 + stage_no + stage_hosei] >= gameflag[200 + stage_no + stage_hosei] )
			{
//				tergetnam++;
			}
			//回転
			if ( target_save[300 + stage_no + stage_hosei] >= gameflag[300 + stage_no + stage_hosei] )
			{
//				tergetnam++;
			}
			//隠し
			if ( gameflag[400 + stage_no + stage_hosei] != 0 )
			{
				tergetnam++;
			}
		}
	}
	if ( tergetnam == 50 )
	{
		end_type = 1;
	}
	gameflag[100] = 0;


}

void ending_relese( void )
{
	int i;
	
	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		ReleaseBitmap( i );
	}
	soundStopBgm(EN_BGM_GAME01);

}


void ending_keys( void )
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
	if ( 
	     ( ( IsPushKey(gameflag[4]) ) || ( IsPushKey(gameflag[5]) ) )
	  && ( gameflag[100] == 1 )
	   )
	{
		gameflag[40] = 0;					/* タイトル */
		g_scene = EN_SN_TITLE;
		scene_exit=0;
		return;
	}
	if ( 
	     ( ( IsPushKey(gameflag[4]) ) || ( IsPushKey(gameflag[5]) ) )
	  && ( gameflag[100] == 0 )
	   )
	{
		demo[0] = 0;
		demo[1]++;
	}
	

}

void ending_drow( void )
{
	
	demo[0]++;
	if ( end_type == 0 )
	{
		//エンディング１
		switch( demo[1] )
		{
		case 0:
			Blt( 10 , 0, 0 );
			Blt( 2 , 0, 0 );
			if ( demo[0] > ( ( 60 * 12 ) + 40 ) )
			{
				demo[0] = 0;
				demo[1]++;
			}
			break;
		case 1:
			Blt( 10 , 0, 0 );
			Blt( 5 , 0, 0 );
			if ( demo[0] > ( ( 60 * 12 ) + 30 ) )
			{
				demo[0] = 0;
				demo[1]++;
			}
			break;
		case 2:
			Blt( 10 , 0, 0 );
			Blt( 6 , 0, 0 );
			demo[0] = 0;
			demo[1] = 2;
			gameflag[100] = 1;
			break;
		default:
			demo[1] = 2;
			gameflag[100] = 1;
			break;
		}
	}
	else 
	{
		//エンディング２
		switch( demo[1] )
		{
		case 0:
			Blt( 11 , 0, 0 );
			Blt( 3 , 0, 0 );
			if ( demo[0] > ( ( 60 * 12 ) + 40 ) )
			{
				demo[0] = 0;
				demo[1]++;
			}
			break;
		case 1:
			Blt( 11 , 0, 0 );
			Blt( 4 , 0, 0 );
			if ( demo[0] > ( ( 60 * 12 ) + 30 ) )
			{
				demo[0] = 0;
				demo[1]++;
			}
			break;
		case 2:
			Blt( 11 , 0, 0 );
			Blt( 5 , 0, 0 );
			if ( demo[0] > ( ( 60 * 12 ) + 30 ) )
			{
				demo[0] = 0;
				demo[1]++;
			}
			break;
		case 3:
			Blt( 11 , 0, 0 );
			Blt( 6 , 0, 0 );
			demo[0] = 0;
			demo[1] = 3;
			gameflag[100] = 1;
			break;
		default:
			demo[1] = 3;
			gameflag[100] = 1;
			break;
		}
	}
	
	//キー入力検査
	KeyInput();				

}


