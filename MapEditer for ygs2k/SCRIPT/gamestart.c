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
/*	2002/04/26		リトライＸＹ座標の表示桁数が２桁だったのを		*/
/*					足りないので３桁に修正							*/
/*	2002/04/25		データ保存処理を修正							*/
/*	2002/04/24		付加情報の設定でダイアログ未入力の場合に値が	*/
/*					変になるのを修正								*/
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
import "lib/file.dll"
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

long MDATA[7600];	// マップデータ配列
long MDATA2[7600];	// マップデータ配列
long IDATA[7600];	// アイテムデータ配列
long EDATA[7600];	// 敵データ配列
long ORG_M[7600];	// マップデータ更新比較用
long ORG_M2[7600];	// マップデータ更新比較用
long ORG_I[7600];	// アイテムデータ更新比較用
long ORG_E[7600];	// 敵データ更新比較用

long map_data_size   = 7600;	// バッファサイズ 確保したサイズを指定する

long EDIT_LAYER = 0;	// 編集レイヤ		0	:	マップ
						//					1	:	アイテム
						//					2	:	敵

long map_width     = 20 * 5;			// マップ幅 デフォルト=20
long map_height    = 15 * 5;			// マップ高さ デフォルト=15
long map_offset_x  = 0;	 				// マップ表示オフセットx
long map_offset_y  = ( 15 * 5 ) - 15 ;	// マップ表示オフセットy
long map_offset_mouse_x  = 0;	 				// マップ表示オフセットx
long map_offset_mouse_y  = ( 15 * 5 ) - 15 ;	// マップ表示オフセットy

long map_info_offset = ( 20 * 5 ) * ( 15 * 5 );    // マップ情報の開始位置 (map_width * map_height)以上とする
								// デフォルト=320

long DISP_LAYER[4] = { 1, 1, 1, 1 };	// レイヤ表示／非表示

long SEL_CHIP[4] = { 0, 0, 0, 0 };	// 現在選択されているマップチップ

long MAP_LOADED[4]  = { 0, 0, 0, 0 };	// マップ、アイテム、敵データ読み込み済みフラグ
long CHIP_LOADED[4] = { 0, 0, 0, 0 };	// マップ、アイテム、敵チップ読み込み済みフラグ

long STAGE_NO = 0;	// ステージ番号
long GAMEN_NO = 0;	// 画面番号
long ORG_STAGE_NO = -1;
long ORG_GAMEN_NO = -1;

long chip_x, chip_y;

long test[1024];

long AUTO_LOAD = 0;	/* 1 = OFF */

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
	int k;
	int file_handle;
	
	/********************************/
	/*	初期処理					*/
	/********************************/

	// FPS設定
	SetFPS( 60 );
	FPSLayerOn( 500, 350 );

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
	CreateSurface( 36, 320, 240 );	// マップ

	// LOAD, SAVEボタンの読み込み
	LoadBitmap("sysdat/load.bmp", 4, 0 );
	LoadBitmap("sysdat/save.bmp", 5, 0 );
	LoadBitmap("sysdat/clear.bmp", 9, 0 );
	LoadBitmap("sysdat/auto.bmp", 50, 0 );		/* add  */
	LoadBitmap("sysdat/auto2.bmp", 51, 0 );

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
	LoadBitmap("sysdat/bak_layer.bmp", 29, 0 );

	LoadBitmap("sysdat/arrow.bmp", 52, 0 );
	LoadBitmap("sysdat/arrow2.bmp", 53, 0 );
	LoadBitmap("sysdat/offset_xy.bmp", 54, 0 );
	LoadBitmap("sysdat/clear2.bmp", 55, 0 );
	LoadBitmap("sysdat/arrow3.bmp", 56, 0 );

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
		/* 2003.11.22 start */
		if ( ( MOUSE_X > 246 ) && ( MOUSE_X < 306 ) &&
			 ( MOUSE_Y >  4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // autoのロードがクリックされた
			if ( AUTO_LOAD == 1 )
			{
				AUTO_LOAD = 0;
			}
			else 
			{
				AUTO_LOAD = 1;
			}
		}
		/* 2003.11.22 end */
		/* 2007.12.02 start */
		/* マウスの座標を表示 */
		if ( ( MOUSE_X      >  5 ) && ( MOUSE_X  < 325 ) &&
			 ( MOUSE_Y      > 25 ) && ( MOUSE_Y  < 265 ) )
		{
			i = ( MOUSE_Y - 25 ) / 16;
			j = ( MOUSE_X -  5 ) / 16;
			map_offset_mouse_x  = j + map_offset_x;	// マップ表示オフセットx
			map_offset_mouse_y  = map_height - (i+map_offset_y)-1 ;	// マップ表示オフセットy
		}
		/* 2007.12.02 end */

		
		if ( ( MOUSE_X > 60 ) && ( MOUSE_X < 120 ) &&
			 ( MOUSE_Y >  4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // マップのロードがクリックされた
			MouseLayerOff();
			if ( AUTO_LOAD == 1 )
			{
				if ( EDIT_LAYER == 0 )
				{
					strcpy( string[1], "マップデータ(n_n.map)=*.map" );
					strcpy( string[2], "%d\\%d_%d.map" );
					strcpy( string[3], "マップ画像(*.bmp)=*.bmp" );
				}
				else if ( EDIT_LAYER == 1 )
				{
					strcpy( string[1], "アイテムデータ(*.map)=*.map" );
					strcpy( string[2], "%d\\i%d_%d.map" );
					strcpy( string[3], "アイテム画像(*.bmp)=*.bmp" );
				}
				else if ( EDIT_LAYER == 2 )
				{
					strcpy( string[1], "敵データ(*.map)=*.map" );
					strcpy( string[2], "%d\\e%d_%d.map" );
					strcpy( string[3], "敵画像(*.bmp)=*.bmp" );
				}
				else
				{
					strcpy( string[1], "マップデータ(n_n.map)=*.map" );
					strcpy( string[2], "%d\\%d_%d.map" );
					strcpy( string[3], "マップ画像(*.bmp)=*.bmp" );
				}
				if ( GetOpenFileName( string[1], ".", string[0] ) == 0 )
				{
					k = 0;
					for( i = StrLen( string[0] ); i > 0; i-- )
					{
						if ( CharAt( string[0], i ) == '\\' )
						{
							k++;
							if ( k == 2 )
							{
								RightStr( string[0], StrLen( string[0] ) - i - 1, string[10] );
	//							SetConstParam( "MessageBox", string[10] );
								break;
							}
						}
					}
					if ( IsPatMatch( string[10], string[2], &STAGE_NO, &k , &GAMEN_NO ) )
					{
						if ( EDIT_LAYER == 0 )
						{
							ORG_GAMEN_NO = GAMEN_NO;
							ORG_STAGE_NO = STAGE_NO;
							LoadFile( string[0], &ORG_M, 4*map_data_size );
							LoadFile( string[0], &MDATA, 4*map_data_size );
						}
						else if ( EDIT_LAYER == 1 )
						{
							LoadFile( string[0], &ORG_I, 4*map_data_size );
							LoadFile( string[0], &IDATA, 4*map_data_size );
						}
						else if ( EDIT_LAYER == 2 )
						{
							LoadFile( string[0], &ORG_E, 4*map_data_size );
							LoadFile( string[0], &EDATA, 4*map_data_size );
						}
						else
						{
							LoadFile( string[0], &ORG_M2, 4*map_data_size );
							LoadFile( string[0], &MDATA2, 4*map_data_size );
						}
						MAP_LOADED[EDIT_LAYER] = 1;
//						map_offset_x  = 0;	//マップ表示オフセットx
//						map_offset_y  = 0;	//マップ表示オフセットy

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
						SetConstParam( "MessageBox", "ガビーン！", "マップファイルじゃないよ" );
					}
				}
			}
			else 
			{
				EDIT_LAYER = 0;
				if ( EDIT_LAYER == 0 )
				{
					strcpy( string[1], "マップデータ(n_n.map)=*.map" );
					strcpy( string[2], "%d\\%d_%d.map" );
					strcpy( string[3], "マップ画像(*.bmp)=*.bmp" );
				}
/*
				else if ( EDIT_LAYER == 1 )
				{
					strcpy( string[1], "アイテムデータ(*.map)=*.map" );
					strcpy( string[2], "%d\\i%d_%d.map" );
					strcpy( string[3], "アイテム画像(*.bmp)=*.bmp" );
				}
				else if ( EDIT_LAYER == 2 )
				{
					strcpy( string[1], "敵データ(*.map)=*.map" );
					strcpy( string[2], "%d\\e%d_%d.map" );
					strcpy( string[3], "敵画像(*.bmp)=*.bmp" );
				}
				else
				{
					strcpy( string[1], "マップデータ(n_n.map)=*.map" );
					strcpy( string[2], "%d\\%d_%d.map" );
					strcpy( string[3], "マップ画像(*.bmp)=*.bmp" );
				}
*/
				if ( GetOpenFileName( string[1], ".", string[0] ) == 0 )
				{
					
					k = 0;
					for( i = StrLen( string[0] ); i > 0; i-- )
					{
						if ( CharAt( string[0], i ) == '\\' )
						{
							k++;
							if ( k == 2 )
							{
								RightStr( string[0], StrLen( string[0] ) - i - 1, string[10] );
								LeftStr( string[0], i + 1, string[4] );	//	str1の左からn文字をstr2に入れる(最後に\0を付加)
//								SetConstParam( "MessageBox", string[4] );
								break;
							}
						}
					}
					
					if ( IsPatMatch( string[10], string[2], &STAGE_NO, &k , &GAMEN_NO ) )
					{
						for( k = 0; k < map_data_size; k++ )
						{
							MDATA2[k] = 0;
							IDATA[k] = 0;
							EDATA[k] = 0;
							ORG_M2[k] = 0;
							ORG_I[k] = 0;
							ORG_E[k] = 0;
						}
						for ( k = 0; k < 4; k++ )
						{
							EDIT_LAYER = k;
							if ( EDIT_LAYER == 0 )
							{
								ORG_GAMEN_NO = GAMEN_NO;
								ORG_STAGE_NO = STAGE_NO;
								
								sprintf(string[0],"%s%d/1_%d.map", string[4], STAGE_NO, GAMEN_NO );
								
								LoadFile( string[0], &ORG_M, 4*map_data_size );
								LoadFile( string[0], &MDATA, 4*map_data_size );
							}
							else if ( EDIT_LAYER == 1 )
							{
								sprintf(string[0],"%s%d/i1_%d.map", string[4], STAGE_NO, GAMEN_NO );
								LoadFile( string[0], &ORG_I, 4*map_data_size );
								LoadFile( string[0], &IDATA, 4*map_data_size );
							}
							else if ( EDIT_LAYER == 2 )
							{
								sprintf(string[0],"%s%d/e1_%d.map", string[4], STAGE_NO, GAMEN_NO );
								LoadFile( string[0], &ORG_E, 4*map_data_size );
								LoadFile( string[0], &EDATA, 4*map_data_size );
							}
							else
							{
								sprintf(string[0],"%s%d/2_%d.map", string[4], STAGE_NO, GAMEN_NO );
								LoadFile( string[0], &ORG_M2, 4*map_data_size );
								LoadFile( string[0], &MDATA2, 4*map_data_size );
							}
//							map_offset_x  = 0;	//マップ表示オフセットx
//							map_offset_y  = 0;	//マップ表示オフセットy
							MAP_LOADED[EDIT_LAYER] = 1;
/*
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
*/
								CreateLayerImage();
//							}
						}
					}
					else
					{
						SetConstParam( "MessageBox", "ガビーン！", "マップファイルじゃないよ" );
					}
				}
			}
			EDIT_LAYER = 0;
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
				for( i = 0; i < map_data_size; i++ )
				{
					MDATA[i] = 0;
					MDATA2[i] = 0;
					IDATA[i] = 0;
					EDATA[i] = 0;
					ORG_M2[i] = 0;
					ORG_M[i] = 0;
					ORG_I[i] = 0;
					ORG_E[i] = 0;
				}
				j = EDIT_LAYER;
				for( EDIT_LAYER = 0; EDIT_LAYER < 4; EDIT_LAYER++ )
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

		/* 2003.11.22 start */
		if ( ( MOUSE_X > 584 ) && ( MOUSE_X < 644 ) &&
			 ( MOUSE_Y >   4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // マップチップ定義のロードがクリックされた
			MouseLayerOff();
			strcpy( string[1], "マップ定義(*.txt)=*.txt" );
			if ( GetOpenFileName( string[1], ".", string[0] ) == 0 )
			{
				file_handle = OpenFile( string[0], "R" );
				if ( file_handle == 0 )
				{
					return;
				}
				else 
				{
					loop
					{
						if ( ReadLine( file_handle, string[0] ) != 0 )
						{
							break;
						}
						else
						{
							i = -1;
							if ( IsPatMatch( string[0], "map1bmp:%s", string[1] ) != 0 )
							{
								i = 0;
//								SetConstParam( "MessageBox", "TEST", string[1] );
							}
							else if ( IsPatMatch( string[0], "ibmp:%s", string[1] ) != 0 )
							{
								i = 1;
							}
							else if ( IsPatMatch( string[0], "ebmp:%s", string[1] ) != 0 )
							{
								i = 2;
							}
							else if ( IsPatMatch( string[0], "map2bmp:%s", string[1] ) != 0 )
							{
								i = 3;
							}
							if ( i != -1 )
							{
								EDIT_LAYER = i;
								LoadBitmap( string[1], 10, 0 );
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
						}
					}
					CloseFile( file_handle );	//	ファイルをクローズする。
					file_handle = 0;
					EDIT_LAYER = 0;
				}
			}
			MouseLayerOn( 0, 1, 1 );
		}
		/* 2003.11.22 end */
		
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
			else if ( EDIT_LAYER == 2 )
			{
				strcpy( string[1], "敵画像(*.bmp)=*.bmp" );
			}
			else
			{
				strcpy( string[1], "マップ2像(*.bmp)=*.bmp" );
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
//			 ( MOUSE_Y      >  25 ) && ( MOUSE_Y < 345  ) &&
			 ( MOUSE_Y      >  25 ) && ( MOUSE_Y < 505  ) &&
			 ( ( MOUSE_BUTTON ==  2 ) || ( MOUSE_BUTTON == 12 ) ) && ( CHIP_LOADED[EDIT_LAYER] ) )
		{ // マップチップがクリックされた
			i = ( MOUSE_Y -  25 ) / 16;
			j = ( MOUSE_X - 335 ) / 16;
			if ( ( i < 20 ) && ( j < 20 ) )
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
				MDATA[(i+map_offset_y) * map_width + j + map_offset_x] = SEL_CHIP[EDIT_LAYER];
			}
			else if ( EDIT_LAYER == 1 )
			{
				IDATA[(i+map_offset_y) * map_width + j + map_offset_x] = SEL_CHIP[EDIT_LAYER];
			}
			else if ( EDIT_LAYER == 2 )
			{
				EDATA[(i+map_offset_y) * map_width + j + map_offset_x] = SEL_CHIP[EDIT_LAYER];
			}
			else 
			{
				MDATA2[(i+map_offset_y) * map_width + j + map_offset_x] = SEL_CHIP[EDIT_LAYER];
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
				SEL_CHIP[EDIT_LAYER] = MDATA[(i+map_offset_y) * map_width + j + map_offset_x];
			}
			else if ( EDIT_LAYER == 1 )
			{
				SEL_CHIP[EDIT_LAYER] = IDATA[(i+map_offset_y) * map_width + j + map_offset_x];
			}
			else if ( EDIT_LAYER == 2 )
			{
				SEL_CHIP[EDIT_LAYER] = EDATA[(i+map_offset_y) * map_width + j + map_offset_x];
			}
			else 
			{
				SEL_CHIP[EDIT_LAYER] = MDATA2[(i+map_offset_y) * map_width + j + map_offset_x];
			}
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 270 ) && ( MOUSE_Y  < 286 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // STAGEが左クリックされた
			MouseLayerOff();
			GetEditBox("STAGE番号を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				STAGE_NO = ValLong( string[0] );
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 270 ) && ( MOUSE_Y  < 286 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 画面番号が左クリックされた
			MouseLayerOff();
			GetEditBox("画面番号を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				GAMEN_NO = ValLong( string[0] );
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 290 ) && ( MOUSE_Y  < 306 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 上スクロールが左クリックされた
			MouseLayerOff();
			GetEditBox("スクロール種別[ 0:不可, 1:通常, 2:Wait ] を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset] = ValLong( string[0] );
			}
			GetEditBox("スクロール先画面番号を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+1] = ValLong( string[0] );
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 290 ) && ( MOUSE_Y  < 306 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 下スクロールが左クリックされた
			MouseLayerOff();
			GetEditBox("スクロール種別[ 0:不可, 1:通常, 2:Wait ] を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+2] = ValLong( string[0] );
			}
			GetEditBox("スクロール先画面番号を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+3] = ValLong( string[0] );
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 310 ) && ( MOUSE_Y  < 326 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 左スクロールが左クリックされた
			MouseLayerOff();
			GetEditBox("スクロール種別[ 0:不可, 1:通常, 2:Wait ] を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+4] = ValLong( string[0] );
			}
			GetEditBox("スクロール先画面番号を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+5] = ValLong( string[0] );
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 310 ) && ( MOUSE_Y  < 326 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 右スクロールが左クリックされた
			MouseLayerOff();
			GetEditBox("スクロール種別[ 0:不可, 1:通常, 2:Wait ] を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+6] = ValLong( string[0] );
			}
			GetEditBox("スクロール先画面番号を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+7] = ValLong( string[0] );
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 330 ) && ( MOUSE_Y  < 346 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // リトライ画面が左クリックされた
			MouseLayerOff();
			GetEditBox("リトライ画面番号 を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+8] = ValLong( string[0] );
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 330 ) && ( MOUSE_Y  < 346 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // リトライ座標が左クリックされた
			MouseLayerOff();
			GetEditBox("リトライ時のＸ座標を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+9] = ValLong( string[0] );
			}
			GetEditBox("リトライ時のＹ座標を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+10] = ValLong( string[0] );
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 244 ) && ( MOUSE_X  < 264 ) &&
			 ( MOUSE_Y      > 286 ) && ( MOUSE_Y  < 366 ) &&
//			 ( MOUSE_Y      > 286 ) && ( MOUSE_Y  < 350 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // レイヤ表示／非表示が左クリックされた
			i = ( MOUSE_Y - 286 ) / 16;
			DISP_LAYER[i] = - DISP_LAYER[i];
		}

		if ( ( MOUSE_X      > 264 ) && ( MOUSE_X  < 324 ) &&
			 ( MOUSE_Y      > 286 ) && ( MOUSE_Y  < 350 ) &&
//			 ( MOUSE_Y      > 286 ) && ( MOUSE_Y  < 350 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // 編集対象レイヤが左クリックされた
			i = ( MOUSE_Y - 286 ) / 16;
			EDIT_LAYER = i;
		}

		/* レイヤーが左クリックされた */
		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 350 ) && ( MOUSE_Y  < 366 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // リトライ画面が左クリックされた
			MouseLayerOff();
			GetEditBox("１番手前背景ＢＭＰファイル番号 を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+11] = ValLong( string[0] );
			}
			GetEditBox("２番目中背景ＢＭＰファイル番号 を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+12] = ValLong( string[0] );
			}
			GetEditBox("３番奥固定背景ＢＭＰファイル番号 を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+13] = ValLong( string[0] );
			}
/*
			GetEditBox("４番奥固定背景ＢＭＰファイル番号 を半角数字で入力", string[0] );
			if ( StrLen( string[0] ) != 0 )
			{
				MDATA[map_info_offset+14] = ValLong( string[0] );
			}
*/
			MouseLayerOn( 0, 1, 1 );
		}


		/* ↑矢印がクリックされた */
		if(  ( MOUSE_X      > 275 ) && ( MOUSE_X  < 293 ) &&
			 ( MOUSE_Y      > 355 ) && ( MOUSE_Y  < 370 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_y--;
			if( map_offset_y < 0 )
				map_offset_y = 0;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click UP");
			InnerLog(map_offset_y);
			*/
		}

		/* ↓矢印がクリックされた */
		if(  ( MOUSE_X      > 275 ) && ( MOUSE_X  < 293 ) &&
			 ( MOUSE_Y      > 388 ) && ( MOUSE_Y  < 405 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_y++;
			if( map_offset_y > map_height - 15 )
				map_offset_y = map_height - 15;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click DOWN");
			InnerLog(map_offset_y);
			*/
		}

		/* ←矢印がクリックされた */
		if(  ( MOUSE_X      > 260 ) && ( MOUSE_X  < 274 ) &&
			 ( MOUSE_Y      > 373 ) && ( MOUSE_Y  < 388 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_x--;
			if( map_offset_x < 0 )
				map_offset_x = 0;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click LEFT");
			InnerLog(map_offset_x);
			*/
		}

		/* →矢印がクリックされた */
		if(  ( MOUSE_X      > 293 ) && ( MOUSE_X  < 310 ) &&
			 ( MOUSE_Y      > 373 ) && ( MOUSE_Y  < 388 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_x++;
			if( map_offset_x > map_width - 20 )
				map_offset_x = map_width - 20;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click RIGHT");
			InnerLog(map_offset_x);
			*/
		}
		
		/* ↑矢印がクリックされた */
		if(  ( MOUSE_X      > 335 ) && ( MOUSE_X  < 353 ) &&
			 ( MOUSE_Y      > 355 ) && ( MOUSE_Y  < 370 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_y = map_offset_y - 15;
			if( map_offset_y < 0 )
				map_offset_y = 0;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click UP");
			InnerLog(map_offset_y);
			*/
		}

		/* ↓矢印がクリックされた */
		if(  ( MOUSE_X      > 335 ) && ( MOUSE_X  < 353 ) &&
			 ( MOUSE_Y      > 388 ) && ( MOUSE_Y  < 405 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_y = map_offset_y + 15;
			if( map_offset_y > map_height - 15 )
				map_offset_y = map_height - 15;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click DOWN");
			InnerLog(map_offset_y);
			*/
		}

		/* ←矢印がクリックされた */
		if(  ( MOUSE_X      > 320 ) && ( MOUSE_X  < 334 ) &&
			 ( MOUSE_Y      > 373 ) && ( MOUSE_Y  < 388 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_x = map_offset_x - 20;
			if( map_offset_x < 0 )
				map_offset_x = 0;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click LEFT");
			InnerLog(map_offset_x);
			*/
		}

		/* →矢印がクリックされた */
		if(  ( MOUSE_X      > 353 ) && ( MOUSE_X  < 370 ) &&
			 ( MOUSE_Y      > 373 ) && ( MOUSE_Y  < 388 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_x = map_offset_x + 20;
			if( map_offset_x > map_width - 20 )
				map_offset_x = map_width - 20;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click RIGHT");
			InnerLog(map_offset_x);
			*/
		}
		
		/* ↑矢印がクリックされた */
		if(  ( MOUSE_X      > 395 ) && ( MOUSE_X  < 413 ) &&
			 ( MOUSE_Y      > 355 ) && ( MOUSE_Y  < 370 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_y = map_offset_y - 7;
			if( map_offset_y < 0 )
				map_offset_y = 0;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click UP");
			InnerLog(map_offset_y);
			*/
		}

		/* ↓矢印がクリックされた */
		if(  ( MOUSE_X      > 395 ) && ( MOUSE_X  < 413 ) &&
			 ( MOUSE_Y      > 388 ) && ( MOUSE_Y  < 405 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_y = map_offset_y + 7;
			if( map_offset_y > map_height - 15 )
				map_offset_y = map_height - 15;
			CreateAllLayerImage();
/*			
			InnerLogMes("Click DOWN");
			InnerLog(map_offset_y);
*/			
		}

		/* ←矢印がクリックされた */
		if(  ( MOUSE_X      > 380 ) && ( MOUSE_X  < 394 ) &&
			 ( MOUSE_Y      > 373 ) && ( MOUSE_Y  < 388 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_x = map_offset_x - 10;
			if( map_offset_x < 0 )
				map_offset_x = 0;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click LEFT");
			InnerLog(map_offset_x);
			*/
		}

		/* →矢印がクリックされた */
		if(  ( MOUSE_X      > 413 ) && ( MOUSE_X  < 430 ) &&
			 ( MOUSE_Y      > 373 ) && ( MOUSE_Y  < 388 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			map_offset_x = map_offset_x + 10;
			if( map_offset_x > map_width - 20 )
				map_offset_x = map_width - 20;
			CreateAllLayerImage();
			/*
			InnerLogMes("Click RIGHT");
			InnerLog(map_offset_x);
			*/
		}
		
		/* 黒壁クリア */
		if(  ( MOUSE_X      > 5 ) && ( MOUSE_X  < 65 ) &&
			 ( MOUSE_Y      > 390 ) && ( MOUSE_Y  < 406 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{
			MouseLayerOff();
			if ( SetConstParam( "YesNo", "確認", "マップレイヤー１を黒い壁でクリアします。" ) )
			{
				for( i = 0; i < ( map_width * map_height ) ; i++ )
				{
					MDATA[i] = 119;
					ORG_M[i] = 119;
				}
				j = EDIT_LAYER;
				for( EDIT_LAYER = 0; EDIT_LAYER < 4; EDIT_LAYER++ )
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

		/***** 描画処理 *****/

		// 説明
		TextLayerOff( 0 );
		TextLayerOn( 0, 4, 4 );
		TextOut( 0, "マップ" );
		TextLayerOff( 1 );
		TextLayerOn( 1, 334, 4 );
		TextOut( 1, "マップチップ" );
		TextLayerOn( 2, 494, 4 );
		TextOut( 2, "マップ定義" );

		// LOAD & SAVE
		BltFast( 4, 60,  4 );
		BltFast( 5, 122, 4 );
		BltFast( 9, 184, 4 );
		BltFast( 50 + AUTO_LOAD,246, 4 );	//add auto
		BltFast( 4, 434, 4 );
		BltFast( 4, 580, 4 );

		// STAGE番号、画面番号
		BltFast( 21, 5, 270 );
		BltNumericImage( STAGE_NO, 2, 67, 270, 7, 0, 0, 8, 16 );
		BltFast( 22, 110, 270 );
		BltNumericImage( GAMEN_NO, 2, 172, 270, 7, 0, 0, 8, 16 );

		// スクロール設定
		BltFast( 23,   5, 290 );
		BltNumericImage( MDATA[map_info_offset], 2, 67, 290, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[map_info_offset+1], 2, 87, 290, 7, 0, 0, 8, 16 );
		BltFast( 24, 110, 290 );
		BltNumericImage( MDATA[map_info_offset+2], 2, 172, 290, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[map_info_offset+3], 2, 192, 290, 7, 0, 0, 8, 16 );
		BltFast( 25,   5, 310 );
		BltNumericImage( MDATA[map_info_offset+4], 2, 67, 310, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[map_info_offset+5], 2, 87, 310, 7, 0, 0, 8, 16 );
		BltFast( 26, 110, 310 );
		BltNumericImage( MDATA[map_info_offset+6], 2, 172, 310, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[map_info_offset+7], 2, 192, 310, 7, 0, 0, 8, 16 );

		// リトライ画面設定
		BltFast( 27,   5, 330 );
		BltNumericImage( MDATA[map_info_offset+8], 2, 67, 330, 7, 0, 0, 8, 16 );
		BltFast( 28, 110, 330 );
		BltNumericImage( MDATA[map_info_offset+9], 3, 172, 330, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[map_info_offset+10], 3, 202, 330, 7, 0, 0, 8, 16 );
		
		/* レイヤー */
		BltFast( 29,   5, 350 );
		BltNumericImage( MDATA[map_info_offset+11], 2, 67, 350, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[map_info_offset+12], 2, 87, 350, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[map_info_offset+13], 2, 107, 350, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[map_info_offset+14], 2, 127, 350, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[map_info_offset+15], 2, 147, 350, 7, 0, 0, 8, 16 );

		// 矢印
		BltFast( 52, 260, 355 );
		BltFast( 53, 320, 355 );
		BltFast( 56, 380, 355 );
		/* 表示座標 */
		BltFast( 54, 5, 370 );
		BltNumericImage( map_offset_x, 3, 67, 370, 7, 0, 0, 8, 16 );
		BltNumericImage( map_height - map_offset_y - 15, 3, 97, 370, 7, 0, 0, 8, 16 );
		BltNumericImage( map_offset_mouse_x, 3, 157, 370, 7, 0, 0, 8, 16 );
		BltNumericImage( map_offset_mouse_y, 3, 187, 370, 7, 0, 0, 8, 16 );
		/* 黒壁クリア */
		BltFast( 55, 5, 390 );
		
		// レイヤー
		BltFastRect( 8, 244, 270, 0, 0, 80, 16 );
		for( i = 0; i < 4; i++ )
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
		for( i = 0; i < 4; i++ )
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
	for( i = 0; i < map_data_size; i++ )
	{
		if ( ( MDATA[i] != ORG_M[i] ) || ( MDATA2[i] != ORG_M2[i] ) || ( IDATA[i] != ORG_I[i] ) || ( EDATA[i] != ORG_E[i] ) )
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
	long x,y,i;

	SwapToSecondary( 33 + EDIT_LAYER );
	for( y = 0; y < 15; y++ )
	{
		for( x = 0 ; x<20 ; x++ )
		{
			i=(x+map_offset_x) + (y+map_offset_y)*map_width;
			if ( EDIT_LAYER == 0 )
			{
				if ( MDATA[i] >= 0 )
				{
					BltFastRect( 11 + EDIT_LAYER, x * 16, y * 16,
								 MDATA[i] % 100 * 16, MDATA[i] / 100 * 16, 16, 16 );
				}
			}
			else if ( EDIT_LAYER == 1 )
			{
				if ( IDATA[i] >= 0 )
				{
					BltFastRect( 11 + EDIT_LAYER, x * 16, y * 16,
								 IDATA[i] % 100 * 16, IDATA[i] / 100 * 16, 16, 16 );
				}
			}
			else if ( EDIT_LAYER == 2 )
			{
				if ( EDATA[i] >= 0 )
				{
					BltFastRect( 11 + EDIT_LAYER, x * 16, y * 16,
								 EDATA[i] % 100 * 16, EDATA[i] / 100 * 16, 16, 16 );
				}
			}
			else 
			{
				if ( MDATA2[i] >= 0 )
				{
					BltFastRect( 11 + EDIT_LAYER, x * 16, y * 16,
								 MDATA2[i] % 100 * 16, MDATA2[i] / 100 * 16, 16, 16 );
				}
			}
		}
	}
	SwapToSecondary( 33 + EDIT_LAYER );

	return;
}

void CreateAllLayerImage()
{
	long i, j;
	i = EDIT_LAYER;

	for( j=0 ; j<=3 ; j++ )
	{
		EDIT_LAYER = j;
		CreateLayerImage();
	}
	EDIT_LAYER = i;

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

	GetCurrentDirectory( string[1] ); 	//現在のパスを取得
	GetParentDir( string[1] );			//一つ上のパスを取得
//	GetParentDir( string[1] );

	// MM/DATA/n/下に保存
//	strcat( string[1], "" );
//	SetConstParam( "MessageBox", "test", string[1] );
	if ( !SearchFile( string[1], "data" ) )
	{
		strcat( string[1], "data\\" );
		MakeDir( string[1] );
	}
	else
	{
		strcat( string[1], "data\\" );
	}
	sprintf( string[2], "%d", STAGE_NO );
	if ( !SearchFile( string[1], string[2] ) )
	{
		strcat( string[1], string[2] );
		strcat( string[1], "\\" );
		MakeDir( string[1] );
	}
	else
	{
		strcat( string[1], string[2] );
		strcat( string[1], "\\" );
	}
/*
	if ( SearchFile( string[1], "RotatGear" ) )
	{	// 親フォルダが"MM"
		// MM/DATA/n/下に保存
		strcat( string[1], "RotatGear\\" );
		if ( !SearchFile( string[1], "data" ) )
		{
			strcat( string[1], "data\\" );
			MakeDir( string[1] );
		}
		else
		{
			strcat( string[1], "data\\" );
		}
		sprintf( string[2], "%d", STAGE_NO );
		if ( !SearchFile( string[1], string[2] ) )
		{
			strcat( string[1], string[2] );
			strcat( string[1], "\\" );
			MakeDir( string[1] );
		}
		else
		{
			strcat( string[1], string[2] );
			strcat( string[1], "\\" );
		}
	}
	else
	{	// 親フォルダが"MM"以外
		// ./savedata/n/下に保存
		GetCurrentDirectory( string[1] );
		if ( !SearchFile( string[1], "savedata" ) )
		{
			strcat( string[1], "savedata\\" );
			MakeDir( string[1] );
		}
		else
		{
			strcat( string[1], "savedata\\" );
		}
		sprintf( string[2], "%d", STAGE_NO );
		if ( !SearchFile( string[1], string[2] ) )
		{
			strcat( string[1], string[2] );
			strcat( string[1], "\\" );
			MakeDir( string[1] );
		}
		else
		{
			strcat( string[1], string[2] );
			strcat( string[1], "\\" );
		}
	}
*/
	// マップデータ更新判定
	for( i = 0; i < map_data_size; i++ )
	{
		if ( ( MDATA[i] != ORG_M[i]     ) ||
			 ( STAGE_NO != ORG_STAGE_NO ) ||
			 ( GAMEN_NO != ORG_GAMEN_NO ) )
		{
			sprintf( string[0], "%s%d_%d.map", string[1], 1, GAMEN_NO );
			SaveFile( string[0], &MDATA, 4*map_data_size );
			LoadFile( string[0], &ORG_M, 4*map_data_size );

			sprintf( string[0], "%s%d_%d.map", string[1], 2, GAMEN_NO );
			SaveFile( string[0], &MDATA2, 4*map_data_size );
			LoadFile( string[0], &ORG_M2, 4*map_data_size );
			break;
		}
	}
	// マップデータ更新判定
	for( i = 0; i < map_data_size; i++ )
	{
		if ( ( MDATA2[i] != ORG_M2[i]   ) ||
			 ( STAGE_NO != ORG_STAGE_NO ) ||
			 ( GAMEN_NO != ORG_GAMEN_NO ) )
		{
			sprintf( string[0], "%s%d_%d.map", string[1], 2, GAMEN_NO );
			SaveFile( string[0], &MDATA2, 4*map_data_size );
			LoadFile( string[0], &ORG_M2, 4*map_data_size );
			break;
		}
	}
	// アイテムデータ更新判定
	for( i = 0; i < map_data_size; i++ )
	{
		if ( ( IDATA[i] != ORG_I[i]                                                                 ) ||
			 ( ( IDATA[i] > 0 ) && ( ( STAGE_NO != ORG_STAGE_NO ) || ( GAMEN_NO != ORG_GAMEN_NO ) ) ) )
		{
			sprintf( string[0], "%si%d_%d.map", string[1], 1, GAMEN_NO );
			SaveFile( string[0], &IDATA, 4*map_data_size );
			LoadFile( string[0], &ORG_I, 4*map_data_size );
			break;
		}
	}
	// 敵データ更新判定
	for( i = 0; i < map_data_size; i++ )
	{
		if ( ( EDATA[i] != ORG_E[i]                                                                 ) ||
			 ( ( EDATA[i] > 0 ) && ( ( STAGE_NO != ORG_STAGE_NO ) || ( GAMEN_NO != ORG_GAMEN_NO ) ) ) )
		{
			sprintf( string[0], "%se%d_%d.map", string[1], 1, GAMEN_NO );
			SaveFile( string[0], &EDATA, 4*map_data_size );
			LoadFile( string[0], &ORG_E, 4*map_data_size );
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
