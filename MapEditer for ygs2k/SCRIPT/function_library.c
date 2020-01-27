/*[ function_library.c ]*********************************************/
/*	汎用関数集														*/
/*------------------------------------------------------------------*/
/*	作者	タケゾー												*/
/*	作成日	2002/02/15												*/
/*	MAIL	syu@world.interq.or.jp									*/
/*	URL		http://www.interq.or.jp/black/kiku/takezo/				*/
/*																	*/
/*	Copyright (c) 2002 タケゾー, ツェムライダマスィそふと。			*/
/*											All Rights Reserved.	*/
/*-[更新履歴]-------------------------------------------------------*/
/*	2002/02/22	コピー元矩形範囲指定プレーンサイズ変更コピー関数を	*/
/*				作成, プレーンサイズ変更コピー関数を修正			*/
/*	2002/02/20	プレーンサイズ変更コピー関数を作成					*/
/*	2002/02/18	数値画像表示関数を作成								*/
/*	2002/02/16	ファイル存在チェック関数を作成						*/
/*	2002/02/15	配列初期化関数, スクリーンショット保存関数,			*/
/*				矩形領域スクリーンショット保存関数を作成			*/
/*-[注意]-----------------------------------------------------------*/
/*	YGS2K専用。YGS2001では使えないよ。								*/
/********************************************************************/

/*[ DLLのインポート ]************************************************/
/*
import "lib/dir.dll"	// ディレクトリ・ライブラリ
 */
/*[ 外部ファイルのインクルード ]*************************************/

/*[ グローバル変数定義 ]*********************************************/

/*[ InitialyzeArray ]************************************************/
/*	配列初期化関数													*/
/*-[引数]-----------------------------------------------------------*/
/*	*ARRAY		(io)	配列のポインタ								*/
/*	size		(i )	配列数										*/
/*	value		(i )	初期値										*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void InitialyzeArray( *ARRAY, size, value )
{
	long i;

	for( i = 0; i < size; i++ )
	{
		ARRAY[i] = value;
	}

	return;
}

/*[ SaveScreenShot ]*************************************************/
/*	スクリーンショット保存関数										*/
/*-[引数]-----------------------------------------------------------*/
/*	filename	(i )	保存するファイル名							*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void SaveScreenShot( filename )
{
	// セカンダリプレーンからバックアッププレーンに転送
	EnableBackupPlane();
	SnapToBackupPlane();
	halt;
	// バックアッププレーンを保存
	SaveBackupPlane( filename );
	// バックアッププレーンの使用終了
	DisableBackupPlane();

	return;
}

/*[ SaveScreenShotRect ]*********************************************/
/*	矩形領域スクリーンショット保存関数								*/
/*-[引数]-----------------------------------------------------------*/
/*	filename		(i )	保存するファイル名						*/
/*	wx, wy			(i )	スクリーンサイズ横, 縦					*/
/*	plane			(i )	矩形保存に一時的に使用するプレーン番号	*/
/*	x, y, sx, sy	(i )	保存する矩形範囲を指定					*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void SaveScreenShotRect( filename, wx, wy, plane, x, y, sx, sy )
{
	// セカンダリプレーンからバックアッププレーンに転送
	EnableBackupPlane();
	SnapToBackupPlane();
	halt;
	// 指定プレーンにバックアッププレーンから転送
	CreateSurface( plane, wx, wy );
	SwapToSecondary( plane );
	BltFromBackupPlane();
	SwapToSecondary( plane );
	// 指定プレーンの矩形範囲を保存
	SaveBitmap( filename, plane, x, y, sx, sy );
	// プレーンの解放とバックアッププレーンの使用終了
	ReleaseBitmap( plane );
	DisableBackupPlane();

	return;
}

/*[ SearchFile ]*****************************************************/
/*	ファイル存在チェック関数										*/
/*-[引数]-----------------------------------------------------------*/
/*	Path	(i )	検索対象パス									*/
/*	File	(i )	検索対象ファイル名								*/
/*-[戻り値]---------------------------------------------------------*/
/*	0	指定ファイルは存在しない									*/
/*	1	指定ファイルが存在した										*/
/********************************************************************/
long SearchFile( Path, File )
{
	long result[64];

	// 検索対象パス、ファイル名を設定
	EnableDirListup( 1 );
	SetFindPath( Path );
	SetFindFile( File );

	// 検索
	if ( FindFile( &result ) )
	{
		return( 0 );	// 見つからなかった
	}
	else
	{
		return( 1 );	// 見つかった
	}
}

/*[ BltNumericImage ]************************************************/
/*	数値画像表示関数												*/
/*-[引数]-----------------------------------------------------------*/
/*	value			(i )	画像表示する数値						*/
/*	length			(i )	表示する桁数（桁数以上は表示されない）	*/
/*	x				(i )	画像を表示する位置ｘ座標				*/
/*	y				(i )	画像を表示する位置ｙ座標				*/
/*	plane			(i )	数値画像が読み込まれているプレーン番号	*/
/*	num_stpos_x		(i )	プレーン内での数値画像の開始位置ｘ座標	*/
/*	num_stpos_y		(i )	プレーン内での数値画像の開始位置ｙ座標	*/
/*	num_width		(i )	数値画像１文字の幅（ドット数）			*/
/*	num_height		(i )	数値画像１文字の高さ（ドット数）		*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void BltNumericImage( value, length, x, y, plane, num_stpos_x, num_stpos_y, num_width, num_height )
{
	long blt_num;	// １桁の数値を格納する
	long i;			// 桁数分のforループで使用
	long dv;		// 割り算で使用する値

	// value が負の値の場合、正の値に置き換える
	if ( value < 0 )
	{
		value = value * -1;
	}

	// 最初の割り算で使用する値を求める
	dv = 1;
	for( i = 1; i < length; i++ )
	{
		dv = dv * 10;
	}

	// 指定された桁数分の数字画像を転送する
	for( i = 0; i < length; i++ )
	{
		// 表示する数字を求める
		blt_num = value / dv;
		value = value - blt_num * dv;
		if ( blt_num > 9 )
		{	// 表示したい１桁の数値にならなければ、１桁にする。
			blt_num = blt_num % 10;
		}
		// 数字画像転送
		BltRect( plane, x + (num_width * i), y, num_stpos_x + (num_width * blt_num), num_stpos_y, num_width, num_height );
		// 割り算で使用する値を10で割る
		dv = dv / 10;
	}

	return;
}

/*[ PlaneResizeCopy ]************************************************/
/*	プレーンサイズ変更コピー関数									*/
/*-[引数]-----------------------------------------------------------*/
/*	to_plane_no		(i )	コピー先プレーン番号					*/
/*	from_plane_no	(i )	コピー元プレーン番号					*/
/*	func			(i )	コピーサイズ設定						*/
/*								0:サイズ指定						*/
/*								1:倍率指定（％で指定）				*/
/*	to_x			(i )	コピーサイズｘ軸						*/
/*	to_y			(i )	コピーサイズｙ軸						*/
/*	color_key		(i )	透過キー								*/
/*								0:無効								*/
/*								1:有効								*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void PlaneResizeCopy( to_plane_no, from_plane_no, func, to_x, to_y, color_key )
{
	long to_plane_x, to_plane_y, from_plane_x, from_plane_y;
	long resize_x, resize_y;

	// 拡大縮小率を求める
	GetPlaneSize( from_plane_no, &from_plane_x, &from_plane_y );
	if ( func == 0 )
	{	// サイズ指定
		to_plane_x = to_x;
		to_plane_y = to_y;
		resize_x   = 65536 * (to_plane_x * 100 / from_plane_x) / 100;
		resize_y   = 65536 * (to_plane_y * 100 / from_plane_y) / 100;
	}
	else
	{	// 倍率指定
		to_plane_x = from_plane_x * to_x / 100;
		to_plane_y = from_plane_y * to_y / 100;
		resize_x   = 65536 * to_x / 100;
		resize_y   = 65536 * to_y / 100;
	}

	// プレーン画像をコピー
	CreateSurface( to_plane_no, to_plane_x, to_plane_y );
	SwapToSecondary( to_plane_no );
	if ( color_key )
	{
		BltR( from_plane_no, 0, 0, resize_x, resize_y );
	}
	else
	{
		BltFastR( from_plane_no, 0, 0, resize_x, resize_y );
	}
	SwapToSecondary( to_plane_no );

	return;
}

/*[ PlaneResizeCopyFromRect ]****************************************/
/*	コピー元矩形範囲指定プレーンサイズ変更コピー関数				*/
/*-[引数]-----------------------------------------------------------*/
/*	to_plane_no		(i )	コピー先プレーン番号					*/
/*	from_plane_no	(i )	コピー元プレーン番号					*/
/*	func			(i )	コピーサイズ設定						*/
/*								0:サイズ指定						*/
/*								1:倍率指定（％で指定）				*/
/*	to_x			(i )	コピーサイズｘ軸						*/
/*	to_y			(i )	コピーサイズｙ軸						*/
/*  from_sx			(i )	コピー元プレーン転送元座標ｘ軸			*/
/*	from_sy			(i )	コピー元プレーン転送元座標ｙ軸			*/
/*	from_hx			(i )	コピー元プレーン転送矩形サイズｘ軸		*/
/*	from_hy			(i )	コピー元プレーン転送矩形サイズｙ軸		*/
/*	color_key		(i )	透過キー								*/
/*								0:無効								*/
/*								1:有効								*/
/*-[戻り値]---------------------------------------------------------*/
/*	無し															*/
/********************************************************************/
void PlaneResizeCopyFromRect( to_plane_no, from_plane_no, func, to_x, to_y,
							  from_sx, from_sy, from_hx, from_hy, color_key )
{
	long to_plane_x, to_plane_y;
	long resize_x, resize_y;

	// 拡大縮小率を求める
	if ( func == 0 )
	{	// サイズ指定
		to_plane_x = to_x;
		to_plane_y = to_y;
		resize_x   = 65536 * (to_plane_x * 100 / from_hx) / 100;
		resize_y   = 65536 * (to_plane_y * 100 / from_hy) / 100;
	}
	else
	{	// 倍率指定
		to_plane_x = from_hx * to_x / 100;
		to_plane_y = from_hy * to_y / 100;
		resize_x   = 65536 * to_x / 100;
		resize_y   = 65536 * to_y / 100;
	}

	// プレーン画像をコピー
	CreateSurface( to_plane_no, to_plane_x, to_plane_y );
	SwapToSecondary( to_plane_no );
	if ( color_key )
	{
		BltRectR( from_plane_no, 0, 0, from_sx, from_sy, from_hx, from_hy, resize_x, resize_y );
	}
	else
	{
		BltFastRectR( from_plane_no, 0, 0, from_sx, from_sy, from_hx, from_hy, resize_x, resize_y );
	}
	SwapToSecondary( to_plane_no );

	return;
}

