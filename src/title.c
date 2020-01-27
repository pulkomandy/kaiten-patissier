#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "title.h" 


// 関数プロトタイプ
void title_main( void );
void title_init( void );
void title_relese( void );
void title_keys( void );
void title_drow( void );
void title_init_save_data( void );
void title_kane_set( int x, int y );
void title_kane_disp( void );
void title_k_jmp( int i );
int replay_file_find( void );
int replay_file_find2( void );

// ＢＭＰ用定数
enum
{
	EN_TITLE_NONE = 0,
	EN_TITLE_image1,
	EN_TITLE_image2,
	EN_TITLE_image3,
	EN_TITLE_image4,
	EN_TITLE_image5,
	EN_TITLE_image6,
};

// 変数宣言
static int scene_exit;

static int mode;		//現在選択されている項目	０：ＧＡＭＥＳＴＡＲＴ　１：ＯＰＴＩＯＮ　２：ＥＸＩＴ
static int a[2] = {0,0};
static int b[2] = {0,0};
static int caslanm ;
static int kane[200];								/* アイテム用バッファ */
static int uracount = 0;

static int title_no = 0;
static char string[1024];
//----------------------------------------------------------------------
// メイン関数
void title_main( void )
{
	int exit_code;
	
	exit_code = 0;
	
	title_init( );		// 初期化
	
	while( scene_exit )
	{
//		KeyInput( );	// キー入力
		
		title_keys( );		// キー処理
		title_drow( );		// 描画
		
		halt( );	// 描画
//		SDL_Flip( g_screen );	// 描画
		FPSWait( );		// 待ち

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	title_relese( );		// 終了
}

void title_init( void )
{
	scene_exit = 1;

	title_no = 0;
	mode = 0;		//現在選択されている項目	０：ＧＡＭＥＳＴＡＲＴ　１：ＯＰＴＩＯＮ　２：ＥＸＩＴ
	memset( kane, 0, sizeof( kane ) );
	uracount = 0;
	title_no = 0;
	caslanm = 0;

	LoadBitmap("image/title/title_pipi.bmp",1,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む

	LoadBitmap("image/title/title2.bmp",2,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/scl.bmp",3,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/bak/1_256.bmp",5, false );		//プレーンナンバー１にタイトル画面背景を読み込む
//	LoadBitmap("image/bak/1.bmp",5, false );		//プレーンナンバー１にタイトル画面背景を読み込む

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

	a[0] = 100;
	a[1] = 200;
	title_kane_set( 0, 300 );
	
	if ( gameflag[123] != -1 )
	{
		gameflag[120] = gameflag[123];	//リプレイ選択時のステージ
	}
	
	if ( gameflag[120] > 50 )
	{
		gameflag[120] = 50;
	}
/*
	for ( i = 0; i < 32 ; i++ )
	{
		bak_scl[i] = Rand( 320 );
	}
*/
                                                
	soundPlayBgm( EN_BGM_GAME01 );

}

void title_relese( void )
{
	int i;
	
	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		ReleaseBitmap( i );
	}
//	soundStopBgm(EN_BGM_GAME01);

}


void title_keys( void )
{
	if ( IsPushKey( gameflag[0] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		mode--;
		if ( mode == -1 )
		{
			mode = 6;
		}
	}
	else if ( IsPushKey( gameflag[1] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		mode++;
		if ( mode == 7 )
		{
			mode = 0;
		}
	}
	if ( IsPushKey( gameflag[2] ) )
	{
		if ( ( mode == 0 ) || ( mode == 1 ) )
		{
			soundPlaySe( EN_SE_SELECT );
			gameflag[120]--;
			if ( gameflag[120] < 1 )
			{
				gameflag[120] = gameflag[121];
				if ( gameflag[120] > 50 )
				{
					gameflag[120] = 50;
				}
			}
		}
		if ( mode == 2 )
		{
			 
			soundPlaySe( EN_SE_SELECT );
			gameflag[124]--;
			if ( gameflag[124] < 0 )
			{
				gameflag[124] = 1;
			}
		}
	}
	else if ( IsPushKey( gameflag[3] ) )
	{
		if ( ( mode == 0 ) || ( mode == 1 ) )
		{
			soundPlaySe( EN_SE_SELECT );
			gameflag[120]++;
			if ( ( gameflag[120] > gameflag[121] ) || ( gameflag[120] > 50 ) )
			{
				gameflag[120] = 1;
			}
		}
		if ( mode == 2 )
		{
			 
			soundPlaySe( EN_SE_SELECT );
			gameflag[124]++;
			if ( gameflag[124] > 1 )
			{
				gameflag[124] = 0;
			}
		}
	}
	if ( IsPressKey( gameflag[2] ) )
	{
		b[0]++;
		if ( ( mode == 0 ) || ( mode == 1 ) )
		{
			if ( b[0] >= 12 )
			{
				b[0] = 0;
				soundPlaySe( EN_SE_SELECT );
				gameflag[120]--;
				if ( gameflag[120] < 1 )
				{
					gameflag[120] = gameflag[121];
					if ( gameflag[120] > 50 )
					{
						gameflag[120] = 50;
					}
				}
			}
		}
	}
	else if ( IsPressKey( gameflag[3] ) )
	{
		b[0]++;
		if ( ( mode == 0 ) || ( mode == 1 ) )
		{
			if ( b[0] >= 12 )
			{
				b[0] = 0;
				soundPlaySe( EN_SE_SELECT );
				gameflag[120]++;
				if ( ( gameflag[120] > gameflag[121] ) || ( gameflag[120] > 50 ) )
				{
					gameflag[120] = 1;
				}
			}
		}
	}
	else 
	{
		b[0] = 0;
	}

	//	決定キーを押した
	if ( IsPushOKKey( ) )
	{
		if ( mode == 6 )	/* Exit */
		{
			gameflag[123] = -1;	//リプレイ選択時のステージ
			gameflag[40] = 10;						/* モードによって変える */
			g_scene = EN_SN_EXIT;
			scene_exit=0;
		}
		else if ( mode == 5 )	/* option */
		{
			gameflag[123] = -1;	//リプレイ選択時のステージ
			gameflag[40] = 3;
			g_scene = EN_SN_OPTION;
			scene_exit=0;
		}
		else if ( mode == 4 )	/* demo */
		{
			ResetGameFlag2( );
			
			title_init_save_data( );
			
			gameflag[125] = 0;	/* replay nomal */
			gameflag[123] = gameflag[120];	//リプレイ選択時のステージ
			gameflag[132] =  1;		//リプレイ
			gameflag2[3]	= 1;	/* 画面Ｎｏ */
			gameflag2[2]	= 0;	/* ステージ */
			gameflag[70] = 1;
			gameflag[128] = 0;	//マップビュー
			gameflag[129] = 0;	//ステージセレクトから開始
			SaveGameFlag2( "save/work.sav");

			ResetGameFlag2( );
			SaveGameFlag2( "save/item_wk.sav");

			gameflag[40] = 4;
			g_scene = EN_SN_ACT;
			scene_exit=0;
		}
		else if ( mode == 3 )	/* stage select */
		{
			gameflag[70] = 1;
			g_scene = EN_SN_STAGESELECT;
			scene_exit=0;
		}
		else if ( mode == 2 )	/* replay */
		{
			if ( replay_file_find( ) == 1 )
			{
				ResetGameFlag2( );
				
				title_init_save_data( );
				
				gameflag[127] = 0;	//トータルアタック
				gameflag[125] = 0;	/* replay nomal */
				gameflag[123] = gameflag[120];	//リプレイ選択時のステージ
				gameflag[132] =  1;		//リプレイ
				gameflag[70] = 1;
				gameflag[128] = 0;	//マップビュー
				gameflag[129] = 0;	//ステージセレクトから開始
				SaveGameFlag2( "save/work.sav");

				ResetGameFlag2( );
				SaveGameFlag2( "save/item_wk.sav");

				gameflag[40] = 4;
				g_scene = EN_SN_ACT;
				scene_exit=0;
				return;
			}
			else 
			{
				soundPlaySe( EN_SE_MSG );
			}
		}
		else if ( mode == 1 )	/* map viwe */
		{
			ResetGameFlag2( );
			
			title_init_save_data( );
			
			gameflag[127] = 0;	//トータルアタック
			gameflag[123] = -1;	//リプレイ選択時のステージ
			gameflag[132] =  0;		//リプレイ
			gameflag[70] = 1;
			gameflag[128] = 1;	//マップビュー
			gameflag[129] = 0;	//ステージセレクトから開始
			SaveGameFlag2( "save/work.sav");

			ResetGameFlag2( );
			SaveGameFlag2( "save/item_wk.sav");

			gameflag[40] = 4;
			g_scene = EN_SN_ACT;
			scene_exit=0;
			return;
		}
		else if ( mode == 0 )	/* new */
		{
			ResetGameFlag2( );
			
			title_init_save_data( );
			
			gameflag[127] = 0;	//トータルアタック
			gameflag[123] = -1;	//リプレイ選択時のステージ
			gameflag[132] =  0;		//リプレイ
			gameflag[70] = 1;
			gameflag[128] = 0;	//マップビュー
			gameflag[129] = 0;	//ステージセレクトから開始
			SaveGameFlag2( "save/work.sav");

			ResetGameFlag2( );
			SaveGameFlag2( "save/item_wk.sav");

			gameflag[40] = 4;
			g_scene = EN_SN_ACT;
			scene_exit=0;
			if ( 
			     ( gameflag[120] == 1 )
			  || ( gameflag[120] == 11 )
			  || ( gameflag[120] == 21 )
			  || ( gameflag[120] == 31 )
			  || ( gameflag[120] == 41 )
			   )
			{
				g_scene = EN_SN_DEMO;
			}
			return;
		}
	}
	//	キャンセルキーを押した
	if ( IsPushCancelKey( ) )
	{
		if ( mode == 0 )	/* 裏面 */
		{
/*
			if ( gameflag[100] == 1 )
			{
				uracount++;
				if ( uracount >= 16 )
				{
					if ( gameflag[126] == 0 )
					{
						gameflag[126] = 1;
						LoadBitmap("image/title/title5_ura.bmp",7,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
					}
					else 
					{
						gameflag[126] = 0;
						LoadBitmap("image/title/title5.bmp",7,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
					}
					uracount = 0;
				}
			}
*/
		}
		if ( mode == 2 )	/* replay jamp */
		{
			if ( replay_file_find2( ) == 1 )
			{
				ResetGameFlag2( );
				
				title_init_save_data( );
				
				gameflag[127] = 0;	//トータルアタック
				gameflag[125] = 1;	/* replay jamp */
				gameflag[123] = gameflag[120];	//リプレイ選択時のステージ
				gameflag[132] =  1;		//リプレイ
				gameflag[129] = 0;	//ステージセレクトから開始
				gameflag[70] = 1;
				SaveGameFlag2( "save/work.sav");

				ResetGameFlag2( );
				SaveGameFlag2( "save/item_wk.sav");

				gameflag[40] = 4;
				g_scene = EN_SN_ACT;
				scene_exit=0;
			}
			else 
			{
				soundPlaySe( EN_SE_MSG );
			}
		}
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

void title_drow( void )
{
	//-------------------------------------------------------------
	//変数宣言
	int stage_hosei;
	int wk;
	//-------------------------------------------------------------
	
	stage_hosei = 0;
	if ( gameflag[126] == 1 )
	{
		stage_hosei = 50;
	}

	//背景クリア
	ClearSecondary();


	//タイトル画面の転送
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	
	if ( title_no == 0 )
	{
		Blt( 5, 0, 0 );
		
		Blt( 1, 110 - a[0], 0 + a[1] );
		
		a[0] = a[0] - 10;
		if ( a[0] < 0 )
		{
			a[0] = 0;
		}
		a[1] = a[1] - 20;
		if ( a[1] < 0 )
		{
			a[1] = 0;
		}
		
		Blt( 2, 0 - 80, 0 );
//		Blt( 7, 0, 0 );
//		BltRect( 7, 0, 0 - ( c[0] * c[0] * c[0] ), 0, 64, 192, 96 );
		title_kane_disp(  );
		
		caslanm++;
		if ( caslanm >= 40 )
		{
			caslanm = 0;
		}
		BltRect( 3, 96 - 80, 112 + ( mode * 16 ), ( caslanm / 10 ) * 16, 0 , 16 , 16 );	/* カーソル */
		BltNumericImage2( gameflag[120], 2, 262 - 80 - 32, 136 - 16, 18, 0, 0, 10, 8 );	/* ステージ */
		BltRect( 18, 262 - 80 - 32, 168 - 16, 0, 56 + ( gameflag[124] * 8 ), 100, 8 );	/* リプレイタイプ */
		
		BltRect( 18, 5, 230 , 0, 24, 100, 8 );	/*  */
		BltRect( 18, 50, 230 , 0, 8, 100, 8 );	/*  */

		wk = get2keta( gameflag[200 + gameflag[120] + stage_hosei], 1 );
		BltNumericImage( wk, 2, 110, 230, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( gameflag[200 + gameflag[120] + stage_hosei], 100 );
		BltNumericImage( wk, 2, 80, 230, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( gameflag[200 + gameflag[120] + stage_hosei], 10000 );
		BltNumericImage( wk, 2, 50, 230, 18, 0, 0, 10, 8 );	/*  */
			
		BltRect( 18, 150, 230, 0, 80, 100, 8 );	/*  */
		BltNumericImage2( gameflag[300 + gameflag[120] + stage_hosei], 2, 240, 230, 18, 0, 0, 10, 8 );	/* Jump_counts */

//		BltRect( 18, 90, 230, 0, 8, 100, 8 );	/*  */
//		BltRect( 18, 5, 230, 0, 48, 100, 8 );	/*  */
//		BltNumericImage( gameflag[108], 2, 150, 230, 18, 0, 0, 10, 8 );	/* 時間 */
//		BltNumericImage( gameflag[109], 2, 120, 230, 18, 0, 0, 10, 8 );	/* 時間 */
//		BltNumericImage( gameflag[110], 2, 90, 230, 18, 0, 0, 10, 8 );	/* 時間 */

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
void title_init_save_data( void )
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

/***************************************************************************/
// NAME      = kane_set
// FUNCTION  = タイトル文字の生成
// NOTES     = 
// DATE      = 
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = x：初期位置
//             y：初期位置
// RETURN    = なし
/***************************************************************************/
void title_kane_set( int x, int y )
{
	int i;
	
	for ( i = 0; i < 20; i++ )
	{
		if ( kane[0 + ( i * 10 )] == 0 )
		{
			kane[0 + ( i * 10 )] = 1;
			kane[1 + ( i * 10 )] = x;
			kane[2 + ( i * 10 )] = y;
			kane[4 + ( i * 10 )] = 0;
			kane[3 + ( i * 10 )] = 0;
			kane[5 + ( i * 10 )] = 0;
			kane[6 + ( i * 10 )] = 0;
			kane[7 + ( i * 10 )] = 0;
			kane[8 + ( i * 10 )] = 0;
			kane[9 + ( i * 10 )] = 6;
			break;
		}
	}
}


/***************************************************************************/
// NAME      = kane_disp
// FUNCTION  = タイトル文字の表示
// NOTES     = 
// DATE      = 
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = なし
// RETURN    = なし
/***************************************************************************/
void title_kane_disp( void )
{
	int i;
	
	for ( i = 0; i < 20; i++ )
	{
		if ( kane[0 + ( i * 10 )] == 1 )
		{
			BltRect( 7, kane[1 + ( i * 10 )], ( 0 - kane[2 + ( i * 10 )] ) + 240 - 96, 0, 64, 300, 96 );

			title_k_jmp( i );
		}
	}
}


/***************************************************************************/
// NAME      = k_jmp
// FUNCTION  = タイトル文字のY表示位置計算
// NOTES     = 
// DATE      = 
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = i：バッファ番号
// RETURN    = なし
/***************************************************************************/
void title_k_jmp( int i )
{
	int y1;



	if ( kane[6 + ( i * 10 )] == 10 ) 
	{
		if ( kane[9 + ( i * 10 )] > 0 )
		{ 
			kane[6 + ( i * 10 )] = kane[9 + ( i * 10 )];
			kane[9 + ( i * 10 )] = kane[9 + ( i * 10 )] - 1;
		}
		return;
	}

	kane[5 + ( i * 10 )]++;
	if ( kane[5 + ( i * 10 )] >= 10 )
	{
		kane[5 + ( i * 10 )] = 0;
	} 
	
	if ( kane[5 + ( i * 10 )] == 0 )
	{
		kane[6 + ( i * 10 )] = kane[6 + ( i * 10 )] - 3;
		if ( ( kane[6 + ( i * 10 )] <= 2 ) && ( kane[6 + ( i * 10 )] > -2 ) )
		{
			kane[6 + ( i * 10 )] = -3;
		}
		if ( kane[6 + ( i * 10 )] < -8 )
		{
			kane[6 + ( i * 10 )] = -8;
		}
		/* 地面判定 */
	}
	
	/* 今回の位置 */
	y1 = ( ( 0 - kane[6 + ( i * 10 )] ) * ( 0 - kane[6 + ( i * 10 )] ) * ( 0 - kane[6 + ( i * 10 )] ) );
	kane[2 + ( i * 10 )] = kane[2 + ( i * 10 )] - ( y1 / 25 );

	if ( kane[2 + ( i * 10 )] < 140 ) 
	{
		kane[6 + ( i * 10 )] = 10;
	}
}



/***************************************************************************/
// NAME      = replay_file_find
// FUNCTION  = リプレイファイルの検索
// NOTES     = 
// DATE      = 
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = なし
// RETURN    = ファイルの有無
/***************************************************************************/
int replay_file_find( void )
{
	long i;
	int file_j;
	int stage;
	
	stage = 1;
	if ( gameflag[126] == 1 )
	{
		stage = 2;	/* 裏ステージ */
	}
	else 
	{
	}
	
	file_j = 1;
	
	sprintf( string, "replay/%d/replay_data_%d.dat", ( int )stage, ( int )gameflag[120] );
	if ( LoadFile( string, &i, 1 ) )
	{
		file_j = 0;
	}
	
	return( file_j );
} 


/***************************************************************************/
// NAME      = replay_file_find2
// FUNCTION  = 最短ジャンプリプレイファイルの検索
// NOTES     = 
// DATE      = 
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = なし
// RETURN    = ファイルの有無
/***************************************************************************/
int replay_file_find2( void )
{
	long i;
	int file_j;
	int stage;
	
	stage = 1;
	if ( gameflag[126] == 1 )
	{
		stage = 2;	/* 裏ステージ */
	}
	else 
	{
	}
	
	file_j = 1;
	sprintf( string, "replay/%d/replay_data_j%d.dat", ( int )stage, ( int )gameflag[120] );
	if ( LoadFile( string, &i, 1 ) )
	{
		file_j = 0;
	}
	
	return( file_j );
} 




