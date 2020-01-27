#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "stageselect.h" 


// 関数プロトタイプ
void stageselect_main( void );
void stageselect_init( void );
void stageselect_relese( void );
void stageselect_keys( void );
void stageselect_drow( void );
void stageselect_init_save_data( void );

// ＢＭＰ用定数

// 変数宣言
static int scene_exit;

static int mode;		//現在選択されている項目	０：ＧＡＭＥＳＴＡＲＴ　１：ＯＰＴＩＯＮ　２：ＥＸＩＴ
static int a[2] = {0,0};
static int csl[2] = {0,0};

//static char string[1024];

static long target_save[1024];

//----------------------------------------------------------------------
// メイン関数
void stageselect_main( void )
{
	int exit_code;
	
	exit_code = 0;
	
	stageselect_init( );		// 初期化
	
	while( scene_exit )
	{
//		KeyInput( );	// キー入力
		
		stageselect_keys( );		// キー処理
		stageselect_drow( );		// 描画
		
		halt( );	// 描画
//		SDL_Flip( g_screen );	// 描画
		FPSWait( );		// 待ち

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	stageselect_relese( );		// 終了
}

void stageselect_init( void )
{
	scene_exit = 1;

	mode = 0;		//現在選択されている項目	０：ＧＡＭＥＳＴＡＲＴ　１：ＯＰＴＩＯＮ　２：ＥＸＩＴ
	memset( a, 0, sizeof( a ) );
	memset( csl, 0, sizeof( csl ) );
	memset( target_save, 0, sizeof( target_save ) );

	csl[1] = ( gameflag[120] / 10 );
	csl[0] = ( gameflag[120] % 10 ) - 1;
	if ( ( gameflag[120] % 10 ) == 0 )
	{
		csl[1] = csl[1] - 1;
		csl[0] = 9 ;
	}

	LoadBitmap("image/title/title_natuki.bmp",1,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む

	LoadBitmap("image/title/stageselect.bmp",2,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/scl.bmp",3,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
//	LoadBitmap("image/bak/1_256.bmp",5, false );		//プレーンナンバー１にタイトル画面背景を読み込む
//	LoadBitmap("image/bak/1.bmp",5, false );		//プレーンナンバー１にタイトル画面背景を読み込む
	LoadBitmap("image/title/potion_bak.bmp",5, false );		//プレーンナンバー１にタイトル画面背景を読み込む
	LoadBitmap("image/player/cutin.bmp",6,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む

	if ( gameflag[126] == 0 )
	{
		LoadBitmap("image/title/title5.bmp",7,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	}
	else 
	{
		LoadBitmap("image/title/title5_ura.bmp",7,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	}

	LoadBitmap("image/title/title3.bmp",10,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/fonts2.bmp",18,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/waku.bmp",109,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む


	LoadFile( "save/target", &target_save[0], sizeof( target_save ) );
	
	if ( gameflag[70] == 0 )
	{
		soundPlayBgm( EN_BGM_GAME01 );
	}
	gameflag[70] = 0;
}

void stageselect_relese( void )
{
	int i;
	
	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		ReleaseBitmap( i );
	}
	soundStopBgm(EN_BGM_GAME01);

}


void stageselect_keys( void )
{
	if ( IsPushKey( gameflag[0] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		csl[0]--;
		if ( csl[0] < 0 )
		{
			csl[0] = 10;
		}
	}
	else if ( IsPushKey( gameflag[1] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		csl[0]++;
		if ( csl[0] >= 11 )
		{
			csl[0] = 0;
		}
	}
	
	if ( IsPushKey( gameflag[2] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		csl[1]--;
		if ( csl[1] < 0 )
		{
			csl[1] = 4;
		}
	}
	else if ( IsPushKey( gameflag[3] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		csl[1]++;
		if ( csl[1] >= 5 )
		{
			csl[1] = 0;
		}
	}

	//	決定キーを押した
	if ( IsPushOKKey( ) )
	{
		if ( csl[0] == 10 )
		{
			//exit
			g_scene = EN_SN_TITLE;
			scene_exit=0;
		}
		else 
		{
			ResetGameFlag2( );
			
			stageselect_init_save_data( );
			
			gameflag[127] = 0;	//トータルアタック
			gameflag[123] = -1;	//リプレイ選択時のステージ
			gameflag[132] =  0;		//リプレイ
			gameflag[70] = 1;
			gameflag[128] = 0;	//マップビュー
			gameflag[129] = 1;	//ステージセレクトから開始
			SaveGameFlag2( "save/work.sav");

			ResetGameFlag2( );
			SaveGameFlag2( "save/item_wk.sav");

			gameflag[40] = 4;
			g_scene = EN_SN_ACT;
			scene_exit=0;
			return;
		}
	}
	//	キャンセルキーを押した
	if ( IsPushCancelKey( ) )
	{
		g_scene = EN_SN_TITLE;
		scene_exit=0;
	}
	/* 12ボタン　か　Ｃが押された */
/*
	if ( IsPushKey( gameflag[6] ) )	// スキンチェンジ
	{
		gameflag[122]++;
		if ( gameflag[100] == 1 )
		{
			if ( gameflag[122] > 4 )
			{
				gameflag[122] = 0;
			}
		}
		else 
		{
			if ( gameflag[122] > 2 )
			{
				gameflag[122] = 0;
			}
		}
	}
*/
}

void stageselect_drow( void )
{
	//-------------------------------------------------------------
	//変数宣言
	//-------------------------------------------------------------

	//背景クリア
	ClearSecondary();


	//タイトル画面の転送
	//-----------------------------------------------------------------------------------
	int stage_hosei;
	int x;
	int y;
	int wk;
	int stage_no;
	int tergetnam;
	//-----------------------------------------------------------------------------------
	tergetnam = 0;
	stage_hosei = 0;

	if ( gameflag[126] == 1 )
	{
		stage_hosei = 50;
	}
	
//		Blt( 5, 0, 0 );
	a[0]++;
	if ( a[0] > 100 )
	{
		a[0] = 0;
	}
	a[1]++;
	if ( a[1] >= 40 )
	{
		a[1] = 0;
	}
	for ( x = 0; x < 5; x++ )
	{
		for ( y = 0; y < 4; y++ )
		{
			Blt( 5, ( x * 100 )- a[0], ( y * 100 ) - a[0] );
		} 
	}
	
	//いろつけ
	tergetnam = 0;
	for ( x = 0; x < 5; x++ )
	{
		for ( y = 0; y < 10; y++ )
		{
			stage_no = ( ( x ) * 10 ) + ( y + 1 );
			//トロフィーの表示
			//タイム
			tergetnam = 0;
			if ( target_save[200 + stage_no + stage_hosei] >= gameflag[200 + stage_no + stage_hosei] )
			{
				tergetnam++;
			}
			//回転
			if ( target_save[300 + stage_no + stage_hosei] >= gameflag[300 + stage_no + stage_hosei] )
			{
				tergetnam++;
			}
			//隠し
			if ( gameflag[400 + stage_no + stage_hosei] != 0 )
			{
				tergetnam++;
			}
			BltRect( 3, 15 + ( x * 64 ) , 32 + ( y * 8 ), 0, 96 + ( tergetnam * 7 ) , 41 , 7 );	/* 達成度 */
		}
	}
	
	Blt( 2, 0, 0 );
	if ( csl[0] == 10 )
	{
		// exit
		BltRect( 3, 0 + ( 2 * 64 ) , 32 + ( 10 * 8 ), ( a[1] / 10 ) * 16, 0 , 16 , 16 );	/* カーソル */
	}
	else 
	{
		BltNumericImage( csl[1] + 1, 1, 174, 135, 18, 0, 0, 10, 8 );	/*  */
		BltNumericImage( csl[0] + 1 + ( csl[1] * 10 ), 2, 192, 135, 18, 0, 0, 10, 8 );	/*  */
		
		BltRect( 3, 0 + ( csl[1] * 64 ) , 28 + ( csl[0] * 8 ), ( a[1] / 10 ) * 16, 0 , 16 , 16 );	/* カーソル */
		
		stage_no = ( ( csl[1] ) * 10 ) + ( csl[0] + 1 );

		wk = get2keta( gameflag[200 + stage_no + stage_hosei], 1 );
		BltNumericImage( wk, 2, 250, 148, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( gameflag[200 + stage_no + stage_hosei], 100 );
		BltNumericImage( wk, 2, 220, 148, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( gameflag[200 + stage_no + stage_hosei], 10000 );
		BltNumericImage( wk, 2, 190, 148, 18, 0, 0, 10, 8 );	/*  */
		BltNumericImage2( gameflag[300 + stage_no + stage_hosei], 2, 190, 178, 18, 0, 0, 10, 8 );	/* Jump_counts */
		if ( gameflag[300 + stage_no + stage_hosei] != 99 )
		{
			BltRect( 6, 250, 180, 0 + ( ( ( stage_no - 1 ) % 10 ) * 32 ), 160 + ( ( ( stage_no - 1 ) / 10 ) * 32 ), 32, 32 );	/*  */
		}


		wk = get2keta( target_save[200 + stage_no + stage_hosei], 1 );
		BltNumericImage( wk, 2, 250, 156, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( target_save[200 + stage_no + stage_hosei], 100 );
		BltNumericImage( wk, 2, 220, 156, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( target_save[200 + stage_no + stage_hosei], 10000 );
		BltNumericImage( wk, 2, 190, 156, 18, 0, 0, 10, 8 );	/*  */
		BltNumericImage2( target_save[300 + stage_no + stage_hosei], 2, 190, 186, 18, 0, 0, 10, 8 );	/* Jump_counts */
		
		//トロフィーの表示
		//タイム
		if ( target_save[200 + stage_no + stage_hosei] >= gameflag[200 + stage_no + stage_hosei] )
		{
			BltRect( 3, 0, 138, 0, 64, 32, 32 );	/* タイム */
			BltRect( 3, 0 + 5, 138 + 4, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カーソル */
			BltRect( 3, 0 + 20, 138 + 14, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カーソル */
		}
		else 
		{
			BltRect( 3, 0, 138, 0, 32, 32, 32 );	/* 土台 */
		}
		//回転
		if ( target_save[300 + stage_no + stage_hosei] >= gameflag[300 + stage_no + stage_hosei] )
		{
			BltRect( 3, 0, 170, 32, 64, 32, 32 );	/* タイム */
			BltRect( 3, 0 + 5, 170 + 4, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カーソル */
			BltRect( 3, 0 + 20, 170 + 14, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カーソル */
		}
		else 
		{
			BltRect( 3, 0, 170, 0, 32, 32, 32 );	/* 土台 */
		}
		//隠し
		if ( gameflag[400 + stage_no + stage_hosei] != 0 )
		{
			BltRect( 18, 190, 214, 0, 176, 200, 8 );	/* タイム */
			BltRect( 3, 0, 202, 64, 64, 32, 32 );	/* タイム */
			BltRect( 3, 0 + 5, 202 + 4, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カーソル */
			BltRect( 3, 0 + 20, 202 + 14, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* カーソル */
		}
		else 
		{
			BltRect( 18, 190, 214, 0, 168, 200, 8 );	/* タイム */
			BltRect( 3, 0, 202, 0, 32, 32, 32 );	/* 土台 */
		}
		
	}
		
//	if ( gameflag[61] == 0 )
//	{
//		Blt( 109 , -160, -120 );
//	}
	
	//キー入力検査
	KeyInput();				

}


/***************************************************************************/
// NAME      = init_save_data
// FUNCTION  = セーブファイルの初期値を設定
// NOTES     = 
// DATE      = 
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = なし
// RETURN    = なし
/***************************************************************************/
void stageselect_init_save_data( void )
{
	gameflag2[0]	= 8 * 32;	/* Ｘ */
	gameflag2[1]	= ( 2 * 32 ) - 16;	/* Ｙ */
	if ( gameflag[126] == 1 )
	{
		gameflag2[2]	= 2;	/* ステージ */
	}
	else 
	{
		gameflag2[2]	= 1;	/* ステージ */
	}
	gameflag[120] = ( ( csl[1] ) * 10 ) + ( csl[0] + 1 );
	gameflag2[3]	= gameflag[120];	/* 画面Ｎｏ */
	gameflag2[4]	= 0;	/* 向き */
	gameflag2[5]	= 3;	/* 現在ＨＰ */
	gameflag2[6]	= 3;	/* 最大ＨＰ */
	gameflag2[7]	= 0;	/* ハートのかけら所持個数 */
	gameflag2[8]	= 0;	/* 現在設定スキル */
	gameflag2[9]	= 0;	/* テレポータ使用不可、スクロール不可フラグ */
	gameflag2[10]	= 0;	/* テレポータ使用不可フラグ */

	gameflag2[20]	= 0; 	/* 時 */
	gameflag2[21]	= 0; 	/* 分 */
	gameflag2[22]	= 0; 	/* 秒 */
	
	gameflag2[30]	= 0;	/* テレポーター使用 */
	gameflag2[31]	= 0;	/* テレポーターステージ */
	gameflag2[32]	= 0;	/* テレポーター画面Ｎｏ */
	gameflag2[33]	= 0;	/* テレポーターＸ */
	gameflag2[34]	= 0;	/* テレポーターＹ */

	gameflag2[40]	= 0;	/* 取得スキル１ */
	gameflag2[41]	= 0;	/* 取得スキル２ */
	gameflag2[42]	= 0;	/* 取得スキル３ */
	gameflag2[43]	= 0;	/* 取得スキル４ */

	
	/* イニシャライズが必要な場合はここに記述する */
//	gameflag2[100]	= ;	/* イベントフラグ[100]～[199] */

	/* 100～399イベント用フラグ */
	
}



