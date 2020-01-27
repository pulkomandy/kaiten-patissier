/*[ gamestart.c ]****************************************************/
/*	ＭＭ　マップエディター　ｆｏｒ　ｙｇｓ２ｋ						*/
/*------------------------------------------------------------------*/
/*	作者	タケゾー												*/
/*	作成日	2002/04/19												*/
/*	MAIL	syu@world.interq.or.jp									*/
/*	URL		http://www.interq.or.jp/black/kiku/takezo/				*/
/*																	*/
/*	Copyright (c) 2002 タケゾー All Rights Reserved.				*/
/*-[更新履歴]-------------------------------------------------------*/
/*	2002/04/23		データ保存処理を以下の様に変更					*/
/*						親フォルダが「MM」の場合					*/
/*							「/MM/DATA/stage_no/」に保存			*/
/*						親フォルダが「MM」以外の場合				*/
/*							「./savedata/stage_no/」に保存			*/
/*						フォルダが存在しない場合は自動生成される	*/
/*	2002/04/22		マップ、マップチップ読み込み時に透過色を設定	*/
/*					するように修正									*/
/*					アイテム、敵の配置に対応						*/
/*	2002/04/19		作った。										*/
/********************************************************************/

/*[ DLLのインポート ]************************************************/
import "lib/dir.dll"
import "lib/string.dll"
import "lib/patmatch.dll"
import "lib/FileDialog.dll"
import "lib/EditDialog.dll"
import "lib/tkzfile.dll"

/*[ 外部ファイルのインクルード ]*************************************/
include "script/function_library.c"

/*[ グローバル変数定義 ]*********************************************/
// マウス関連
long MOUSE_X;
long MOUSE_Y;
long MOUSE_BUTTON = 0;	//  0			:	入力なし,
						//  1(Push)		:	右クリック,  2:左クリック,  3:同時クリック,  4:右ダブルクリック
						// 11(Press)	:	右クリック, 12:左クリック, 13:同時クリック, 14:右ダブルクリック

long MDATA[1024];	// マップデータ配列
long IDATA[1024];	// アイテムデータ配列
long EDATA[1024];	// 敵データ配列
long ORG_M[1024];	// マップデータ更新比較用
long ORG_I[1024];	// アイテムデータ更新比較用
long ORG_E[1024];	// 敵データ更新比較用

long EDIT_LAYER = 0;	// 編集レイヤ		0	:	マップ
						//					1	:	アイテム
						//					2	:	敵

long DISP_LAYER[3] = { 1, 1, 1 };	// レイヤ表示／非表示

long SEL_CHIP[3] = { 0, 0, 0 };	// 現在選択されているマップチップ

long MAP_LOADED[3]  = { 0, 0, 0 };	// マップ、アイテム、敵データ読み込み済みフラグ
long CHIP_LOADED[3] = { 0, 0, 0 };	// マップ、アイテム、敵チップ読み込み済みフラグ

long STAGE_NO = 0;	// ステージ番号
long GAMEN_NO = 0;	// 画面番号
long ORG_STAGE_NO = -1;
long ORG_GAMEN_NO = -1;

long chip_x, chip_y;

/*[ main ]***********************************************************/
/*	メイン関数														*/
/*-[引数]-----------------------------------------------------------*/
/*	無し															*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void main()
{
	long i,j;

	/********************************/
	/*	初期処理					*/
	/********************************/

	// FPS設定
	SetFPS( 60 );
	FPSLayerOn( 5, 350 );

	// マウスカーソル読み込み
	LoadBitmap( "sysdat/mouse.bmp", 0, 0 );
	SetColorKeyPos( 0, 0, 0 );
	MouseLayerOn( 0, 1, 1 );

	// マップ、マップチップ背景
	LoadBitmap( "sysdat/background.bmp", 2, 0 );
	CreateSurface( 1, 322, 242 );
	SwapToSecondary( 1 );
	BltFastRect( 2, 0, 0, 0, 0, 322, 242 );
	SwapToSecondary( 1 );

	// マス目（１マス）の読み込み
	LoadBitmap( "sysdat/masu.bmp", 3, 0 );
	SetColorKeyPos( 3, 0, 0 );

	// マップ、マップチップ用マス目の作成
	CreateSurface( 31, 320, 240 );
	SwapToSecondary( 31 );
	for( i = 0; i < 20; i++ )
	{
		for( j = 0; j < 15; j++ )
		{
			BltFast( 3, ( i * 16 ), ( j * 16 ) );
		}
	}
	SwapToSecondary( 31 );
	SetColorKeyPos( 31, 0, 0 );
	CreateSurface( 32, 320, 320 );
	SwapToSecondary( 32 );
	for( i = 0; i < 20; i++ )
	{
		for( j = 0; j < 20; j++ )
		{
			BltFast( 3, ( i * 16 ), ( j * 16 ) );
		}
	}
	SwapToSecondary( 32 );
	SetColorKeyPos( 32, 0, 0 );
	CreateSurface( 33, 320, 240 );	// マップ
	CreateSurface( 34, 320, 240 );	// アイテム
	CreateSurface( 35, 320, 240 );	// 敵

	// LOAD, SAVEボタンの読み込み
	LoadBitmap("sysdat/load.bmp", 4, 0 );
	LoadBitmap("sysdat/save.bmp", 5, 0 );
	LoadBitmap("sysdat/clear.bmp", 9, 0 );

	// マップチップ選択カーソル読み込み
	LoadBitmap("sysdat/select_chip.bmp", 6, 0 );
	SetColorKeyPos( 6, 4, 4 );

	// 数字画像読み込み
	LoadBitmap("sysdat/num.bmp", 7, 0 );
	SetColorKeyPos( 7, 0, 0 );

	// レイヤー
	LoadBitmap("sysdat/layer.bmp", 8, 0 );

	// マップ設定の各ボタン読み込み
	LoadBitmap("sysdat/stage.bmp", 21, 0 );
	LoadBitmap("sysdat/gamen.bmp", 22, 0 );
	LoadBitmap("sysdat/up_scroll.bmp", 23, 0 );
	LoadBitmap("sysdat/dn_scroll.bmp", 24, 0 );
	LoadBitmap("sysdat/l_scroll.bmp", 25, 0 );
	LoadBitmap("sysdat/r_scroll.bmp", 26, 0 );
	LoadBitmap("sysdat/retry.bmp", 27, 0 );
	LoadBitmap("sysdat/retry_xy.bmp", 28, 0 );

	/********************************/
	/*	主処理						*/
	/********************************/

	loop
	{
		ClearSecondary();
		SUB_GetMouseInfo();		// マウス入力情報の取得
		KeyInput();				// キーボード入力

		/***** キーボード入力判定 *****/

		if ( IsPushEscKey() )
		{	// ESCキーが押されたら終了しまっせ！
			break;
		}

		/***** マウス入力判定 *****/

		if ( ( MOUSE_X > 60 ) && ( MOUSE_X < 120 ) &&
			 ( MOUSE_Y >  4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // マップのロードがクリックされた
			MouseLayerOff();
			if ( EDIT_LAYER == 0 )
			{
				strcpy( string[1], "マップデータ(n_n.map)=*.map" );
				strcpy( string[2], "%d_%d.map" );
				strcpy( string[3], "マップ画像(*.bmp)=*.bmp" );
			}
			else if ( EDIT_LAYER == 1 )
			{
				strcpy( string[1], "アイテムデータ(*.map)=*.map" );
				strcpy( string[2], "i%d_%d.map" );
				strcpy( string[3], "アイテム画像(*.bmp)=*.bmp" );
			}
			else
			{
				strcpy( string[1], "敵データ(*.map)=*.map" );
				strcpy( string[2], "e%d_%d.map" );
				strcpy( string[3], "敵画像(*.bmp)=*.bmp" );
			}
			if ( GetOpenFileName( string[1], ".", string[0] ) == 0 )
			{
				for( i = StrLen( string[0] ); i > 0; i-- )
				{
					if ( CharAt( string[0], i ) == '\\' )
					{
						RightStr( string[0], StrLen( string[0] ) - i - 1, string[10] );
						break;
					}
				}
				if ( IsPatMatch( string[10], string[2], &STAGE_NO, &GAMEN_NO ) )
				{
					ORG_STAGE_NO = STAGE_NO;
					ORG_GAMEN_NO = GAMEN_NO;
					if ( EDIT_LAYER == 0 )
					{
						LoadFile( string[0], &ORG_M, 4*1024 );
						LoadFile( string[0], &MDATA, 4*1024 );
					}
					else if ( EDIT_LAYER == 1 )
					{
						LoadFile( string[0], &ORG_I, 4*1024 );
						LoadFile( string[0], &IDATA, 4*1024 );
					}
					else
					{
						LoadFile( string[0], &ORG_E, 4*1024 );
						LoadFile( string[0], &EDATA, 4*1024 );
					}
					MAP_LOADED[EDIT_LAYER] = 1;
					if ( !CHIP_LOADED[EDIT_LAYER] )
					{
						if ( GetOpenFileName( string[3], ".", string[0] ) == 0 )
						{
							LoadBitmap( string[0], 10, 0 );
							GetPlaneSize( 10, &chip_x, &chip_y );
							PlaneResizeCopyFromRect( 11 + EDIT_LAYER, 10, 1, 50, 50, 0, 0, chip_x, chip_y, 0 );
							CHIP_LOADED[EDIT_LAYER] = 1;
							SwapToSecondary( 33 + EDIT_LAYER );
							for( i = 0; i < 15; i++ )
							{
								for( j = 0; j < 20; j++ )
								{
									BltFastRect( 11 + EDIT_LAYER, j * 16, i * 16, 0, 0, 16, 16 );
								}
							}
							SwapToSecondary( 33 + EDIT_LAYER );
							SetColorKeyPos( 33 + EDIT_LAYER, 0, 0 );
							CreateLayerImage();
						}
					}
					else
					{
						CreateLayerImage();
					}
				}
				else
				{
					SetConstParam( "MessageBox", "ガビーン！", "ＭＭ用のマップファイルじゃないよ" );
				}
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X > 122 ) && ( MOUSE_X < 182 ) &&
			 ( MOUSE_Y >   4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // マップのセーブがクリックされた
			MapDataSave();
			MouseLayerOff();
			SetConstParam( "MessageBox", "セーブしました。", "セーブしました。" );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X > 184 ) && ( MOUSE_X < 244 ) &&
			 ( MOUSE_Y >   4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // マップのクリアがクリックされた
			MouseLayerOff();
			if ( SetConstParam( "YesNo", "確認", "全てクリアしてよいかね？" ) )
			{
				STAGE_NO = 0;
				GAMEN_NO = 0;
				for( i = 0; i < 1024; i++ )
				{
					MDATA[i] = 0;
					IDATA[i] = 0;
					EDATA[i] = 0;
					ORG_M[i] = 0;
					ORG_I[i] = 0;
					ORG_E[i] = 0;
				}
				j = EDIT_LAYER;
				for( EDIT_LAYER = 0; EDIT_LAYER < 3; EDIT_LAYER++ )
				{
					if ( CHIP_LOADED[EDIT_LAYER] == 1 )
					{
						CreateLayerImage();
					}
				}
				EDIT_LAYER = j;
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X > 434 ) && ( MOUSE_X < 494 ) &&
			 ( MOUSE_Y >   4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // マップチップのロードがクリックされた
			MouseLayerOff();
			if ( EDIT_LAYER == 0 )
			{
				strcpy( string[1], "マップ画像(*.bmp)=*.bmp" );
			}
			else if ( EDIT_LAYER == 1 )
			{
				strcpy( string[1], "アイテム画像(*.bmp)=*.bmp" );
			}
			else
			{
				strcpy( string[1], "敵画像(*.bmp)=*.bmp" );
			}
			if ( GetOpenFileName( string[1], ".", string[0] ) == 0 )
			{
				LoadBitmap( string[0], 10, 0 );
				GetPlaneSize( 10, &chip_x, &chip_y );
				PlaneResizeCopyFromRect( 11 + EDIT_LAYER, 10, 1, 50, 50, 0, 0, chip_x, chip_y, 0 );
				CHIP_LOADED[EDIT_LAYER] = 1;
				SwapToSecondary( 33 + EDIT_LAYER );
				for( i = 0; i < 15; i++ )
				{
					for( j = 0; j < 20; j++ )
					{
						BltFastRect( 11 + EDIT_LAYER, j * 16, i * 16, 0, 0, 16, 16 );
					}
				}
				SwapToSecondary( 33 + EDIT_LAYER );
				SetColorKeyPos( 33 + EDIT_LAYER, 0, 0 );
				if ( MAP_LOADED[EDIT_LAYER] )
				{
					CreateLayerImage();
				}
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 335 ) && ( MOUSE_X < 655  ) &&
			 ( MOUSE_Y      >  25 ) && ( MOUSE_Y < 345  ) &&
			 ( ( MOUSE_BUTTON ==  2 ) || ( MOUSE_BUTTON == 12 ) ) && ( CHIP_LOADED[EDIT_LAYER] ) )
		{ // マップチップがクリックされた
			i = ( MOUSE_Y -  25 ) / 16;
			j = ( MOUSE_X - 335 ) / 16;
			if ( ( i < 8 ) && ( j < 20 ) )
			{
				SEL_CHIP[EDIT_LAYER] = i * 100 + j;
			}
		}

		if ( ( MOUSE_X      >  5 ) && ( MOUSE_X  < 325 ) &&
			 ( MOUSE_Y      > 25 ) && ( MOUSE_Y  < 265 ) &&
			 ( ( MOUSE_BUTTON ==  2 ) || ( MOUSE_BUTTON == 12 ) ) && ( SEL_CHIP[EDIT_LAYER] >= 0 ) )
		{ // マップが左クリックされた
			i = ( MOUSE_Y - 25 ) / 16;
			j = ( MOUSE_X -  5 ) / 16;
			if ( EDIT_LAYER == 0 )
			{
				MDATA[20 + (i*20) + j] = SEL_CHIP[EDIT_LAYER];
			}
			else if ( EDIT_LAYER == 1 )
			{
				IDATA[20 + (i*20) + j] = SEL_CHIP[EDIT_LAYER];
			}
			else
			{
				EDATA[20 + (i*20) + j] = SEL_CHIP[EDIT_LAYER];
			}
			SwapToSecondary( 33 + EDIT_LAYER );
			BltFastRect( 11 + EDIT_LAYER, j * 16, i * 16,
						 SEL_CHIP[EDIT_LAYER] % 100 * 16, SEL_CHIP[EDIT_LAYER] / 100 * 16, 16, 16 );
			SwapToSecondary( 33 + EDIT_LAYER );
		}

		if ( ( MOUSE_X      >  5 ) && ( MOUSE_X  < 325 ) &&
			 ( MOUSE_Y      > 25 ) && ( MOUSE_Y  < 265 ) &&
			 ( ( MOUSE_BUTTON == 1 ) || ( MOUSE_BUTTON == 11 ) ) )
		{ // マップが右クリックされた
			i = ( MOUSE_Y - 25 ) / 16;
			j = ( MOUSE_X -  5 ) / 16;
			if ( EDIT_LAYER == 0 )
			{
				SEL_CHIP[EDIT_LAYER] = MDATA[20 + (i*20) + j];
			}
			else if ( EDIT_LAYER == 1 )
			{
				SEL_CHIP[EDIT_LAYER] = IDATA[20 + (i*20) + j];
			}
			else
			{
				SEL_CHIP[EDIT_LAYER] = EDATA[20 + (i*20) + j];
			}
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 270 ) && ( MOUSE_Y  < 286 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // STAGEが左クリックされた
			MouseLayerOff();
			GetEditBox("STAGE番号を半角数字で入力", string[0] );
			STAGE_NO = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 270 ) && ( MOUSE_Y  < 286 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 画面番号が左クリックされた
			MouseLayerOff();
			GetEditBox("画面番号を半角数字で入力", string[0] );
			GAMEN_NO = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 290 ) && ( MOUSE_Y  < 306 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 上スクロールが左クリックされた
			MouseLayerOff();
			GetEditBox("スクロール種別[ 0:不可, 1:通常, 2:Wait ] を半角数字で入力", string[0] );
			MDATA[320] = ValLong( string[0] );
			GetEditBox("スクロール先画面番号を半角数字で入力", string[0] );
			MDATA[321] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 290 ) && ( MOUSE_Y  < 306 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 下スクロールが左クリックされた
			MouseLayerOff();
			GetEditBox("スクロール種別[ 0:不可, 1:通常, 2:Wait ] を半角数字で入力", string[0] );
			MDATA[322] = ValLong( string[0] );
			GetEditBox("スクロール先画面番号を半角数字で入力", string[0] );
			MDATA[323] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 310 ) && ( MOUSE_Y  < 326 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 左スクロールが左クリックされた
			MouseLayerOff();
			GetEditBox("スクロール種別[ 0:不可, 1:通常, 2:Wait ] を半角数字で入力", string[0] );
			MDATA[324] = ValLong( string[0] );
			GetEditBox("スクロール先画面番号を半角数字で入力", string[0] );
			MDATA[325] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 310 ) && ( MOUSE_Y  < 326 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 右スクロールが左クリックされた
			MouseLayerOff();
			GetEditBox("スクロール種別[ 0:不可, 1:通常, 2:Wait ] を半角数字で入力", string[0] );
			MDATA[326] = ValLong( string[0] );
			GetEditBox("スクロール先画面番号を半角数字で入力", string[0] );
			MDATA[327] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 330 ) && ( MOUSE_Y  < 346 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // リトライ画面が左クリックされた
			MouseLayerOff();
			GetEditBox("リトライ画面番号 を半角数字で入力", string[0] );
			MDATA[328] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 330 ) && ( MOUSE_Y  < 346 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // リトライ座標が左クリックされた
			MouseLayerOff();
			GetEditBox("リトライ時のＸ座標を半角数字で入力", string[0] );
			MDATA[329] = ValLong( string[0] );
			GetEditBox("リトライ時のＹ座標を半角数字で入力", string[0] );
			MDATA[330] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 244 ) && ( MOUSE_X  < 264 ) &&
			 ( MOUSE_Y      > 286 ) && ( MOUSE_Y  < 350 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // レイヤ表示／非表示が左クリックされた
			i = ( MOUSE_Y - 286 ) / 16;
			DISP_LAYER[i] = - DISP_LAYER[i];
		}

		if ( ( MOUSE_X      > 264 ) && ( MOUSE_X  < 324 ) &&
			 ( MOUSE_Y      > 286 ) && ( MOUSE_Y  < 350 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 編集対象レイヤが左クリックされた
			i = ( MOUSE_Y - 286 ) / 16;
			EDIT_LAYER = i;
		}

		/***** 描画処理 *****/

		// 説明
		TextLayerOff( 0 );
		TextLayerOn( 0, 4, 4 );
		TextOut( 0, "マップ" );
		TextLayerOff( 1 );
		TextLayerOn( 1, 334, 4 );
		TextOut( 1, "マップチップ" );

		// LOAD & SAVE
		BltFast( 4, 60,  4 );
		BltFast( 5, 122, 4 );
		BltFast( 9, 184, 4 );
		BltFast( 4, 434, 4 );

		// STAGE番号、画面番号
		BltFast( 21, 5, 270 );
		BltNumericImage( STAGE_NO, 2, 67, 270, 7, 0, 0, 8, 16 );
		BltFast( 22, 110, 270 );
		BltNumericImage( GAMEN_NO, 2, 172, 270, 7, 0, 0, 8, 16 );

		// スクロール設定
		BltFast( 23,   5, 290 );
		BltNumericImage( MDATA[320], 2, 67, 290, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[321], 2, 87, 290, 7, 0, 0, 8, 16 );
		BltFast( 24, 110, 290 );
		BltNumericImage( MDATA[322], 2, 172, 290, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[323], 2, 192, 290, 7, 0, 0, 8, 16 );
		BltFast( 25,   5, 310 );
		BltNumericImage( MDATA[324], 2, 67, 310, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[325], 2, 87, 310, 7, 0, 0, 8, 16 );
		BltFast( 26, 110, 310 );
		BltNumericImage( MDATA[326], 2, 172, 310, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[327], 2, 192, 310, 7, 0, 0, 8, 16 );

		// リトライ画面設定
		BltFast( 27,   5, 330 );
		BltNumericImage( MDATA[328], 2, 67, 330, 7, 0, 0, 8, 16 );
		BltFast( 28, 110, 330 );
		BltNumericImage( MDATA[329], 2, 172, 330, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[330], 2, 192, 330, 7, 0, 0, 8, 16 );

		// レイヤー
		BltFastRect( 8, 244, 270, 0, 0, 80, 16 );
		for( i = 0; i < 3; i++ )
		{
			if ( DISP_LAYER[i] > 0 )
			{
				BltFastRect( 8, 244, 286 + ( i * 16 ), 80, 0, 20, 16 );
			}
			else
			{
				BltFastRect( 8, 244, 286 + ( i * 16 ), 100, 0, 20, 16 );
			}
			if ( i == EDIT_LAYER )
			{
				BltFastRect( 8, 264, 286 + ( i * 16 ), 0, 16 + ( i * 16 ), 60, 16 );
			}
			else
			{
				BltFastRect( 8, 264, 286 + ( i * 16 ), 60, 16 + ( i * 16 ), 60, 16 );
			}
		}

		// マップ、マップチップ背景描画
		BltFast( 1, 4, 24 );
		BltFast( 2, 334, 24 );

		if ( CHIP_LOADED[EDIT_LAYER] )
		{
			BltFast( 11 + EDIT_LAYER, 335, 25 );
		}

		// マップの描画
		for( i = 0; i < 3; i++ )
		{
			if ( DISP_LAYER[i] > 0 )
			{
				Blt( 33 + i, 5, 25 );
			}
		}

		// マップ、マップチップマス目描画
		Blt( 31,   5, 25 );
		Blt( 32, 335, 25 );

		// マップチップ選択カーソル描画
		if ( ( SEL_CHIP[EDIT_LAYER] >= 0 ) &&
			 ( CHIP_LOADED[EDIT_LAYER]   ) )
		{
			i = SEL_CHIP[EDIT_LAYER] / 100;
			j = SEL_CHIP[EDIT_LAYER] % 100;
			Blt( 6, j * 16 + 335, i * 16 + 25 );
		}

		halt;
	}

	/********************************/
	/*	終了処理					*/
	/********************************/

	MouseLayerOff();

	/***** 保存確認判定 *****/
	for( i = 0; i < 1024; i++ )
	{
		if ( ( MDATA[i] != ORG_M[i] ) || ( IDATA[i] != ORG_I[i] ) || ( EDATA[i] != ORG_E[i] ) )
		{
			if ( SetConstParam( "YesNo", "確認", "データを保存して終了しますか？" ) )
			{
				MapDataSave();
			}
			break;
		}
	}

	/***** メモリ解放 *****/
	ReleaseBitmap(  0 );
	ReleaseBitmap(  1 );
	ReleaseBitmap(  2 );
	ReleaseBitmap(  3 );
	ReleaseBitmap(  4 );
	ReleaseBitmap(  5 );
	ReleaseBitmap(  6 );
	ReleaseBitmap(  7 );
	ReleaseBitmap(  8 );
	ReleaseBitmap(  9 );
	ReleaseBitmap( 10 );
	ReleaseBitmap( 11 );
	ReleaseBitmap( 12 );
	ReleaseBitmap( 13 );
	ReleaseBitmap( 21 );
	ReleaseBitmap( 22 );
	ReleaseBitmap( 23 );
	ReleaseBitmap( 24 );
	ReleaseBitmap( 25 );
	ReleaseBitmap( 26 );
	ReleaseBitmap( 27 );
	ReleaseBitmap( 28 );
	ReleaseBitmap( 31 );
	ReleaseBitmap( 32 );
	ReleaseBitmap( 33 );
	TextLayerOff( 0 );
	TextLayerOff( 1 );
	FPSLayerOff();

	Quit();
}

/*[ SUB_GetMouseInfo ]***********************************************/
/*	マウス情報の取得関数											*/
/*-[引数]-----------------------------------------------------------*/
/*	無し															*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void SUB_GetMouseInfo()
{
	long b;

	// マウス情報の取得
	GetMouseInfo( &MOUSE_X, &MOUSE_Y, &b );

	// ボタン入力の判定
	if ( b == 0 )
	{
		MOUSE_BUTTON = 0;
	}
	else if ( b == MOUSE_BUTTON )
	{
		MOUSE_BUTTON = b + 10;
	}
	else if ( b + 10 == MOUSE_BUTTON )
	{
	}
	else
	{
		MOUSE_BUTTON = b;
	}

	return;
}

/*[ CreateLayerImage ]***********************************************/
/*	配置データ、チップ画像読み込み時のレイヤイメージ作成関数		*/
/*-[引数]-----------------------------------------------------------*/
/*	無し															*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void CreateLayerImage()
{
	long i;

	SwapToSecondary( 33 + EDIT_LAYER );
	for( i = 20; i < 320; i++ )
	{
		if ( EDIT_LAYER == 0 )
		{
			if ( MDATA[i] >= 0 )
			{
				BltFastRect( 11 + EDIT_LAYER, ( i - 20 ) % 20 * 16, ( i - 20 ) / 20 * 16,
							 MDATA[i] % 100 * 16, MDATA[i] / 100 * 16, 16, 16 );
			}
		}
		else if ( EDIT_LAYER == 1 )
		{
			if ( IDATA[i] >= 0 )
			{
				BltFastRect( 11 + EDIT_LAYER, ( i - 20 ) % 20 * 16, ( i - 20 ) / 20 * 16,
							 IDATA[i] % 100 * 16, IDATA[i] / 100 * 16, 16, 16 );
			}
		}
		else
		{
			if ( EDATA[i] >= 0 )
			{
				BltFastRect( 11 + EDIT_LAYER, ( i - 20 ) % 20 * 16, ( i - 20 ) / 20 * 16,
							 EDATA[i] % 100 * 16, EDATA[i] / 100 * 16, 16, 16 );
			}
		}
	}
	SwapToSecondary( 33 + EDIT_LAYER );

	return;
}

/*[ MapDataSave ]****************************************************/
/*	マップ、アイテム、敵データ保存関数								*/
/*-[引数]-----------------------------------------------------------*/
/*	無し															*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void MapDataSave()
{
	long i;

	if ( SearchFile( "../../", "mm" ) )
	{	// 親フォルダが"MM"
		// MM/DATA/n/下に保存
		if ( !SearchFile( "../", "data" ) )
		{
//			MakeDir( "../data" );
		}
		sprintf( string[1], "%d", STAGE_NO );
		if ( !SearchFile( "../data/", string[1] ) )
		{
			sprintf( string[1], "../data/%d/", STAGE_NO );
//			MakeDir( string[1] );
		}
		sprintf( string[1], "../data/%d/", STAGE_NO );
	}
	else
	{	// 親フォルダが"MM"以外
		// ./savedata/n/下に保存
		if ( !SearchFile( "./", "savedata" ) )
		{
//			MakeDir( "./savedata" );
		}
		sprintf( string[1], "%d", STAGE_NO );
		if ( !SearchFile( "./savedata/", string[1] ) )
		{
			sprintf( string[1], "./savedata/%d/", STAGE_NO );
//			MakeDir( string[1] );
		}
		sprintf( string[1], "./savedata/%d/", STAGE_NO );
	}
	sprintf( string[1], "../data/%d/", STAGE_NO );
	// マップデータ更新判定
	for( i = 0; i < 1024; i++ )
	{
		if ( ( MDATA[i] != ORG_M[i]     ) ||
			 ( STAGE_NO != ORG_STAGE_NO ) ||
			 ( GAMEN_NO != ORG_GAMEN_NO ) )
		{
			sprintf( string[0], "%s%d_%d.map", string[1], STAGE_NO, GAMEN_NO );
			SaveFile( string[0], &MDATA, 4*1024 );
			LoadFile( string[0], &ORG_M, 4*1024 );
			break;
		}
	}
	// アイテムデータ更新判定
	for( i = 0; i < 1024; i++ )
	{
		if ( ( IDATA[i] != ORG_I[i]                                                                 ) ||
			 ( ( IDATA[i] > 0 ) && ( ( STAGE_NO != ORG_STAGE_NO ) || ( GAMEN_NO != ORG_GAMEN_NO ) ) ) )
		{
			sprintf( string[0], "%si%d_%d.map", string[1], STAGE_NO, GAMEN_NO );
			SaveFile( string[0], &IDATA, 4*1024 );
			LoadFile( string[0], &ORG_I, 4*1024 );
			break;
		}
	}
	// 敵データ更新判定
	for( i = 0; i < 1024; i++ )
	{
		if ( ( EDATA[i] != ORG_E[i]                                                                 ) ||
			 ( ( EDATA[i] > 0 ) && ( ( STAGE_NO != ORG_STAGE_NO ) || ( GAMEN_NO != ORG_GAMEN_NO ) ) ) )
		{
			sprintf( string[0], "%se%d_%d.map", string[1], STAGE_NO, GAMEN_NO );
			SaveFile( string[0], &EDATA, 4*1024 );
			LoadFile( string[0], &ORG_E, 4*1024 );
			break;
		}
	}
	if ( ( STAGE_NO != ORG_STAGE_NO ) ||
		 ( GAMEN_NO != ORG_GAMEN_NO ) )
	{
		ORG_STAGE_NO = STAGE_NO;
		ORG_GAMEN_NO = GAMEN_NO;
	}

	return;
}
