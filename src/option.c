#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "option.h" 


// 関数プロトタイプ
void option_main( void );
void option_init( void );
void option_relese( void );
void option_keys( void );
void option_drow( void );
void option_init_save_data( void );
void option_kane_set( int x, int y );
void option_kane_disp( void );
void option_k_jmp( int i );


// 変数宣言
static int scene_exit;

static int mode;		//現在選択されている項目	０：ＧＡＭＥＳＴＡＲＴ　１：ＯＰＴＩＯＮ　２：ＥＸＩＴ
static int ag = 0;
static int selct[15];
static int bak_scl[64];
static int bak_count[64];
static int a[2] = {0,0};
static int b[2] = {0,0};
static int tolal_time[5];
static int tolal_time2[5];
static int tolal_time3[5];
static char string[1024];

//----------------------------------------------------------------------
// メイン関数
void option_main( void )
{
	int exit_code;
	
	exit_code = 0;
	
	option_init( );		// 初期化
	
	while( scene_exit )
	{
//		KeyInput( );	// キー入力
		
		option_keys( );		// キー処理
		option_drow( );		// 描画
		
		halt( );
//		SDL_Flip( g_screen );	// 描画
		FPSWait( );		// 待ち

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	option_relese( );		// 終了
}

void option_init( void )
{
	int i;
	int wk;
	
	scene_exit = 1;

	mode = 0;		//現在選択されている項目	０：ＧＡＭＥＳＴＡＲＴ　１：ＯＰＴＩＯＮ　２：ＥＸＩＴ
	ag = 0;
	memset( selct, 0, sizeof( selct ) );
	memset( bak_scl, 0, sizeof( bak_scl ) );
	memset( bak_count, 0, sizeof( bak_count ) );
	memset( a, 0, sizeof( a ) );
	memset( b, 0, sizeof( b ) );
	memset( tolal_time, 0, sizeof( tolal_time ) );
	memset( tolal_time2, 0, sizeof( tolal_time2 ) );
	memset( tolal_time3, 0, sizeof( tolal_time3 ) );
	memset( string, 0, sizeof( string ) );


//	LoadBitmap("image/title/tria1.bmp",1,1);				//プレーンナンバー２にシステム用ＢＭＰを読み込む

	LoadBitmap("image/title/title2.bmp",2,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/scl.bmp",3,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/title5.bmp",4,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/potion_bak.bmp",5, false );		//プレーンナンバー１にタイトル画面背景を読み込む
	LoadBitmap("image/sys/fonts2.bmp",6,true);				//プレーンナンバー２にシステム用ＢＭＰを読み込む

	if ( gameflag[126] == 1 )
	{
		LoadBitmap("image/title/option2.bmp",7,1);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	}
	else 
	{
		LoadBitmap("image/title/option1.bmp",7,1);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	}
	
	LoadBitmap("image/title/lvel.bmp",8,1);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/on_off.bmp",9,1);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/title_mask.bmp",11,1);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/none.bmp",12,1);				//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/sima.bmp",13,1);				//プレーンナンバー２にシステム用ＢＭＰを読み込む

	LoadBitmap("image/sys/waku.bmp",109,0);					//プレーンナンバー２にシステム用ＢＭＰを読み込む

//	bgm_midi( );

	tolal_time[0] = 0;
	tolal_time[1] = 0;
	tolal_time[2] = 0;
	for ( i = 1; i <= 50; i++ )
	{
//		sprintf( string[0],"%d", gameflag[200 + i] );
//		MidStr(string[0],6,2,string[1]);
		wk = get2keta( gameflag[200 + i], 1 );
		tolal_time[0] = tolal_time[0] + wk;
		if ( tolal_time[0] >= 60 )
		{
			tolal_time[0] = tolal_time[0] - 60;
			tolal_time[1]++; 
		}
//		sprintf( string[0],"%d", gameflag[200 + i] );
//		MidStr(string[0],4,2,string[1]);
		wk = get2keta( gameflag[200 + i], 100 );
		tolal_time[1] = tolal_time[1] + wk;
		if ( tolal_time[1] >= 60 )
		{
			tolal_time[1] = tolal_time[1] - 60;
			tolal_time[2]++; 
		}
		
//		sprintf( string[0],"%d", gameflag[200 + i] );
//		MidStr(string[0],2,2,string[1]);
		wk = get2keta( gameflag[200 + i], 10000 );
		tolal_time[2] = tolal_time[2] + wk;
		if ( tolal_time[2] >= 999 )
		{
			tolal_time[2] = 999;
			tolal_time[1] = 59;
			tolal_time[0] = 59;
		}
		
		/* スコア */
//		sprintf( string[0],"%d", gameflag[250 + i] );
//		MidStr(string[0],6,2,string[1]);
		wk = get2keta( gameflag[250 + i], 1 );
		tolal_time2[0] = tolal_time2[0] + wk;
		if ( tolal_time2[0] >= 60 )
		{
			tolal_time2[0] = tolal_time2[0] - 60;
			tolal_time2[1]++; 
		}
//		sprintf( string[0],"%d", gameflag[250 + i] );
//		MidStr(string[0],4,2,string[1]);
		wk = get2keta( gameflag[250 + i], 100 );
		tolal_time2[1] = tolal_time2[1] + wk;
		if ( tolal_time2[1] >= 60 )
		{
			tolal_time2[1] = tolal_time2[1] - 60;
			tolal_time2[2]++; 
		}
		
//		sprintf( string[0],"%d", gameflag[250 + i] );
//		MidStr(string[0],2,2,string[1]);
		wk = get2keta( gameflag[250 + i], 10000 );
		tolal_time2[2] = tolal_time2[2] + wk;
		if ( tolal_time2[2] >= 999 )
		{
			tolal_time2[2] = 999;
			tolal_time2[1] = 59;
			tolal_time2[0] = 59;
		}
	}

	tolal_time[3] = 0;
	for ( i = 1; i <= 50; i++ )
	{
		tolal_time[3] = tolal_time[3] + gameflag[300 + i];
		tolal_time2[3] = tolal_time2[3] + gameflag[350 + i];
	}



	/* スコア */
	tolal_time3[0] = 0;
	tolal_time3[1] = 0;
	tolal_time3[2] = 0;
	tolal_time3[3] = 0;

//	sprintf( string[0],"%d", gameflag[137] );
//	MidStr(string[0],6,2,string[1]);
	wk = get2keta( gameflag[137], 1 );
	tolal_time3[0] = wk;
//	if ( tolal_time3[0] >= 60 )
//	{
//		tolal_time3[0] = tolal_time3[0] - 60;
//		tolal_time3[1]++; 
//	}
//	sprintf( string[0],"%d", gameflag[137] );
//	MidStr(string[0],4,2,string[1]);
	wk = get2keta( gameflag[137], 100 );
	tolal_time3[1] = wk;
//	if ( tolal_time3[1] >= 60 )
//	{
//		tolal_time3[1] = tolal_time3[1] - 60;
//		tolal_time3[2]++; 
//	}
	
//	sprintf( string[0],"%d", gameflag[137] );
//	MidStr(string[0],2,2,string[1]);
	wk = get2keta( gameflag[137], 10000 );
	tolal_time3[2] = wk;
//	if ( tolal_time3[2] >= 999 )
//	{
//		tolal_time3[2] = 999;
//		tolal_time3[1] = 59;
//		tolal_time3[0] = 59;
//	}

	tolal_time3[3] = gameflag[138];

//	selct[4] = gameflag[67];	//背景アニメーションＯＮ0／ＯＦＦ1
	selct[2] = gameflag[133];	//上キーの使用
	selct[3] = gameflag[134];	//開始演出のスキップ
	selct[4] = gameflag[131];	//言語

}

void option_relese( void )
{
	int i;
	
	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		ReleaseBitmap( i );
	}
	soundStopBgm(EN_BGM_GAME01);

}


void option_keys( void )
{
	int load_rc = 0;
	
	if ( ag == 0 )
	{
		if ( IsPushKey( gameflag[0] ) )
		{
			soundPlaySe( EN_SE_SELECT );
			mode--;
			if ( mode == 14 )
			{
				mode = 6;
			}
			if ( mode <= -1 )
			{
				mode = 15;
			}
		}
		else if ( IsPushKey( gameflag[1] ) )
		{
			soundPlaySe( EN_SE_SELECT );
			mode++;
			if ( mode == 7 )
			{
				mode = 15;
			}
			if ( mode >= 16 )
			{
				mode = 0;
			}
		}
	}
	if ( IsPushKey( gameflag[2] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		selct[mode]--;
		if ( selct[mode] < 0 )
		{
			selct[mode] = 0;
		}
		if( ( mode == 5 ) && ( ag == 1 ) )
		{
//			sprintf(string[0],"image/option/%d.bmp", selct[mode] );
			sprintf(string,"image/option/%d.bmp", selct[mode] );
			LoadBitmap( string, 10 , false );
		}
	}
	else if ( IsPushKey( gameflag[3] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		selct[mode]++;
		if ( mode == 0 )	/* BGM */
		{
			if ( selct[mode] > ( EN_BGM_END - 1 ) )
			{
				selct[mode] = ( EN_BGM_END - 1 );
			}
		}
		if ( mode == 1 )	/* SE */
		{
			if ( selct[mode] > ( EN_SE_END - 1 ) )
			{
				selct[mode] = ( EN_SE_END - 1 );
			}
		}
		if ( mode == 2 )	/* 上ジャンプ */
		{
			if ( selct[mode] > 1 )
			{
				selct[mode] = 1;
			}
		}
		if ( mode == 3 )	/* 開始演出 */
		{
			if ( selct[mode] > 1 )
			{
				selct[mode] = 1;
			}
		}
		if ( mode == 4 )	/* 言語 */
		{
			if ( selct[mode] > 1 )
			{
				selct[mode] = 1;
			}
		}
		if ( ( mode == 5 ) && ( ag == 1 ) )
		{
			if ( selct[mode] > 99 )
			{
				selct[mode] = 99;
			}
//			sprintf(string,"image/option/%d.bmp", selct[mode] );
			sprintf(string,"image/option/%d.bmp", selct[mode] );
			load_rc = LoadBitmap( string, 10 , false );
			if ( load_rc != 0 )
			{
				//ファイルの読み込みに失敗
				selct[mode]--;
				sprintf(string,"image/option/%d.bmp", selct[mode] );
				load_rc = LoadBitmap( string, 10 , false );
			}
		}
	}
	
	
	//	決定が押される
	if ( IsPushOKKey( ) )
	{
		if ( mode == 15 )	/* Exit */
		{
			gameflag[133] = selct[2];	//上キー
			gameflag[134] = selct[3];	//開始演出
			gameflag[131] = selct[4];	//言語
			SaveGameFlag("config/config.fig");

			gameflag[40] = 1;						/* モードによって変える */
			g_scene = EN_SN_TITLE;
			scene_exit=0;
		}
		else if ( mode == 6 )
		{
			if ( gameflag[100] == 1 )
			{
				gameflag[133] = selct[2];	//上キー
				gameflag[134] = selct[3];	//開始演出
				gameflag[131] = selct[4];	//言語

				gameflag[40] = 5;						/* モードによって変える */
				g_scene = EN_SN_ENDING;
				scene_exit=0;
			}
			else 
			{
				soundPlaySe( EN_SE_MSG );
			}
		}
		else if ( mode == 5 )
		{
			ag = 1;
//			sprintf(string,"image/option/%d.bmp", selct[mode] );
			sprintf(string,"image/option/%d.bmp", selct[mode] );
			LoadBitmap( string, 10 , false );
		}
		else if ( mode == 1 )	/* se test */
		{
			soundPlaySe( selct[mode] );
		}
		else if ( mode == 0 )	/* bgm test */
		{
			soundStopBgm(EN_BGM_GAME01);
			soundPlayBgm( selct[mode] );
		}
	}
	
	//	キャンセルが押される
	if ( IsPushCancelKey(  ) )
	{
		if ( mode == 13 )	/* Exit */
		{
		}
		else if ( mode == 6 )
		{
		}
		else if ( mode == 5 )
		{
			ag = 0;
		}
		else if ( mode == 4 )
		{
			selct[mode] = 0;
		}
		else if ( mode == 3 )
		{
			selct[mode] = 0;
		}
		else if ( mode == 2 )
		{
			selct[mode] = 0;
		}
		else if ( mode == 1 )	/* se test */
		{
			soundStopSeAll();					/* wavファイルの全開放 */
		}
		else if ( mode == 0 )	/* bgm test */
		{
			soundStopBgm(0);
		}
		if ( ag == 1 )
		{
			ag = 0;
		}
	}

}

void option_drow( void )
{
	//-------------------------------------------------------------
	//変数宣言
	int i;
	int x, y;
	//-------------------------------------------------------------

	//背景クリア
	ClearSecondary();


	//タイトル画面の転送
	//-----------------------------------------------------------------------------------
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
	/* ロゴ */
//	Blt( 4, 0, 0 );

	Blt( 1, 10, 90 );
	
	//-----------------------------------------------------------------------------------
	if ( ag == 0 )
	{
	
		
		Blt( 0, 0, 0 );
		
		
		Blt( 7, 0, 0 );
		BltRect( 3, 40, 52 + ( mode * 8 ) , 0 + ( a[1] / 10 ) * 16 , 0, 16, 16 );
		
		for ( i = 0; i < 2 ; i++ )
		{
			//数値の項目
			BltNumericImage( selct[i], 2, 200, 56 + ( i * 8 ), 6, 0, 0, 10, 8 );	/*  */
		}
		BltRect( 9 , 200, 56 + ( 2 * 8 ), 0, ( selct[2] ) * 8 , 200, 8 );	/* on off */
		BltRect( 9 , 200, 56 + ( 3 * 8 ), 0, ( selct[3] ) * 8 , 200, 8 );	/* on off */
		BltRect( 9 , 200, 56 + ( 4 * 8 ), 0, ( ( selct[4] ) * 8 ) + 16, 200, 8 );	/* langage */

		BltNumericImage2( gameflag[110], 3, 180, 64 + ( 7 * 8 ), 6, 0, 0, 10, 8 );			/* プレイタイム */
		BltNumericImage( gameflag[109], 2, 200 + 20 + 10, 64 + ( 7 * 8 ), 6, 0, 0, 10, 8 );	/* プレイタイム */
		BltNumericImage( gameflag[108], 2, 200 + 40 + 20, 64 + ( 7 * 8 ), 6, 0, 0, 10, 8 );	/* プレイタイム */

		BltNumericImage2( tolal_time[2], 3, 180, 64 + ( 8 * 8 ), 6, 0, 0, 10, 8 );			/* クリアタイム */
		BltNumericImage( tolal_time[1], 2, 200 + 20 + 10, 64 + ( 8 * 8 ), 6, 0, 0, 10, 8 );	/* クリアタイム */
		BltNumericImage( tolal_time[0], 2, 200 + 40 + 20, 64 + ( 8 * 8 ), 6, 0, 0, 10, 8 );	/* クリアタイム */

		BltNumericImage2( tolal_time[3], 4, 170, 64 + ( 9 * 8 ), 6, 0, 0, 10, 8 );				/* 回転回数 */

//		BltNumericImage2( tolal_time3[2], 3, 180, 64 + ( 9 * 8 ), 6, 0, 0, 10, 8 );				/*  */
//		BltNumericImage( tolal_time3[1], 2, 200 + 20 + 10, 64 + ( 9 * 8 ), 6, 0, 0, 10, 8 );	/*  */
//		BltNumericImage( tolal_time3[0], 2, 200 + 40 + 20, 64 + ( 9 * 8 ), 6, 0, 0, 10, 8 );	/*  */

//		BltNumericImage2( tolal_time3[3], 4, 170, 64 + ( 10 * 8 ), 6, 0, 0, 10, 8 );			/*  */

		if ( gameflag[126] == 1 )
		{
			BltNumericImage2( tolal_time2[2], 3, 180, 64 + ( 12 * 8 ), 6, 0, 0, 10, 8 );	/* 資金 */
			BltNumericImage( tolal_time2[1], 2, 200 + 20 + 10, 64 + ( 12 * 8 ), 6, 0, 0, 10, 8 );	/* 資金 */
			BltNumericImage( tolal_time2[0], 2, 200 + 40 + 20, 64 + ( 12 * 8 ), 6, 0, 0, 10, 8 );	/* 資金 */

			BltNumericImage2( tolal_time2[3], 4, 170, 64 + ( 13 * 8 ), 6, 0, 0, 10, 8 );	/* 資金 */
		}

	}
	else 
	{
		/* ギャラリーモード */
		/* ギャラリーモード */
		Blt( 10, 0, 0 );

		BltNumericImage( selct[mode], 2, 300, 230, 6, 0, 0, 10, 8 );	/* No. */

	}
	
	//キー入力検査
	KeyInput();				

}


