#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "act.h" 
#include "include/dconv.h" 
#include "include/general.h" 

// 関数プロトタイプ
void act_main( void );
void act_init( void );
void act_relese( void );
void act_keys( void );
void fram_set( );
void jmp_st( );
void jmp( );
void idou_l( );
void idou_r( );
void cleaer_ankr( long ankr_flag );
void act_drow( void );
void save_file_w( );
void save_file( );
void clear_save_file( );
void playerdisp( );
void bg_disp();
void bakdisp1();
void bakdisp2( );
void bak_make( void );
void bak_rot( void );
void wait_scl( long type, long d_num );
void wait_scl2( long d_num ,long init_x, long init_y );
void wait_scl3( );
void snack_counter_disp();
void minimap_disp( void );
void mapdisp();
void bgm_midi( long BgmWavNo );
void se_wav(long SeWavNo);
void stage_start( );
void stage_endj( );
void stage_claer( );
void stage_end( );
void end_scl( long s_num );
void p_shot_set( long type , long muki, long houkou );
void p_shot_disp( );
void p_shot_f_set( long x, long y , long type );
void p_shot_f_disp( );
void p_shot_f2_set( long x, long y , long muki );
void p_shot_f2_disp( );
void item_set( long type, long x, long y, long iti, long g_num );
long item_sonzai( long map1, long map2 );
void item_disp( );
void item_jmp( int i );
void item_line( void );
long item_up_Isitem( long item_index );
long item_up( );
long item_up2( );
long item_event( );
void init_event_set_enm( long event_no , long b_num );
void init_event_set( long event_no , long b_num );
void event_set( long event_no , long b_num );
void event_set_enm( long event_no , long b_num );
void event_disp( );
void event_save( );
void load_save_file( );
void event_kaihuku( );
void event_return( );
void event_warp( );
void enm_set( long type, long x, long y );
void enm_set2( long type, long x, long y ,long muki );
long e_hp( long type );
void enm_disp();
void e_move( long i );
void boss_dead( long x, long y );
void e_shot_set( long type , long i , long x, long y );
void e_shot_disp( );
void enmjmp( long i );
long map1_item_j( long x, long y );
long map1_item_j_Isitem( long x, long y, long item_index );
void kane_set( long x, long y );
void kane_disp(  );
void k_jmp( long i );
void p_jump_f_set( long x, long y );
void p_jump_f_disp( );
void screen_BackupPlane( );
void window_disp( );
void window_keys( );
long labs( long para );
void p_mgc_set( long muki , long p3 );
void p_mgc_disp( );
void BlendExBltRectW( long plane_no, long x, long y, long sx, long sy, long hx, long hy, long func, long blend );
void BlendExBltW( long plane_no, long x, long y, long func, long blend );
void BlendExBltFastW( long plane_no, long x, long y, long func, long blend );
void replay_input_save( void );
void replay_input_load( void );
void replay_file_save_w( void );
void replay_file_save( long type );
long replay_file_load( void );
long GetKyori( long i1, long i2 );
void rotmap( long rot );
void rotchangemap( long x1, long y1, long deg, long *x2, long *y2 );
void rotchange( long x1, long y1, long deg, long *x2, long *y2 );
void debugdisp( void );
void mapviwe_keys( void );

char string[1024];
// 変数宣言
static long scene_exit;
static long sn = 0;									/* 場面用変数これを変えることによって描画関数内の処理を変える		*/

static long enm1_parameter[10 * 20] = 
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0未使用 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 10 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 11 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 12 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20未使用 */
};

static long enm2_parameter[10 * 20] = 
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0未使用 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20未使用 */
};

static long enm3_parameter[10 * 20] = 
{
/*   HP   金 攻撃 属性 相性 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0未使用 */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20未使用 */
};

static long enm4_parameter[10 * 20] = 
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0未使用 */
	  7,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1ボス */
	  7,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	 30,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	 27,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
     42,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
     30,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
      1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20未使用 */
};

static long item_data[3] = { 32, 50, 20 };			/* アイテムの情報　サイズ、最大配置個数、1データバッファ数 */
static long enm_data[3] = { 0, 30, 30 };			/* 敵の情報　予備、最大配置個数、1データバッファ数 */
static long MapInfo[10] = 
{
	20 * 5									/* 0:マップのxサイズ */
,	15 * 5									/* 1:マップのyサイズ */
,	( 20 * 5 ) * 32							/* 2:マップのx表示サイズ */
,	( 15 * 5 ) * 32							/* 3:マップのy表示サイズ */
,   20										/* 4:ヘッダデータ部のデータ数 */
};
static long char_size[10] = 
{
	32										/* char_size[0] 横幅 */
,	32										/* char_size[1] 高さ */
,	10										/* char_size[2] 判定しない幅左（左からドットでカウント） */
,	( 32 - 10 )								/* char_size[3] 判定しない幅右（左からドットでカウント） */
,	8										/* char_size[4] アニメーションパターン数 */
};

static long player[50];									/* プレイヤー用バッファ */
											/* player[0] X */
											/* player[1] Y */
											/* player[2] 状態 */
											/* player[3] 向き */
											/* player[4] BMP内の表示位置X */
											/* player[5] BMP内の表示位置Y */
											/* player[6] 掴み中の移動補正X */
											/* player[7] 掴み中の移動補正Y */
											/* player[8] 現在HP */
											/* player[9] 敵を掴んでいる */
											/* player[10] アニメーションフレームカウンタ */
											/* player[11] アニメーションカウンタ */
											/* player[12] アニメーションフレーム指定 */
											/* player[13] ジャンプフレームカウンタ */
											/* player[14] ジャンプカウンタ */
											/* player[15] ミスの場合のX */
											/* player[16] ミスの場合のY */
											/* player[17] 無敵時間 */
											/* player[18] 着地モーション用カウンタ */
											/* player[19] 回転可能か */
											/* player[20] マップの回転角度 */
											/* player[21] マップの回転角度目標 */
											/* player[22] 回転入力のウエイト */
											/* player[23] 回転角度差分 */
											/* player[24] secret item get 表示時間  */
											/* player[25] ボタンをおしてジャンプしたフラグ */
											/* player[26] 長時間落下したフラグ（着地フェクト用） */
											/* player[27] 掴んだときに入力されていたキー */
											/* player[28] 移動床モーション */
											/* player[29] 横ばね吹き飛び中 */
											/* player[30] lastone表示 */
											/* player[31] カットインの表示 */
											/* player[32] カットインの種類 */
											/* player[33] アイテムを押した時の移動量 */
											/* player[34]  */
											/* player[35]  */
											/* player[36]  */
											/* player[37]  */
											/* player[38]  */
static long dp_x;									/* プレイヤーの表示位置（画面内の相対座標） */
static long dp_y;									/* プレイヤーの表示位置（画面内の相対座標） */
static long dp_x2 = 80;								/* プレイヤーの表示位置（画面内の相対座標） */
static long demo[10];
static uint32_t map1[10200];								/* ( MapInfo[0] * MapInfo[1] ) + MapInfo[4] 背景用バッファ レイヤー1 */
static uint32_t map2[10200];							 	/* MapInfo[0] * MapInfo[1] 背景用バッファ レイヤー2 */
static uint32_t mapfile[10200];							/* MapInfo[0] * MapInfo[1] 背景用バッファ レイヤー2 */
static long map_data[20];							/* ヘッダ情報 */
static long bak_cnt = 0;							/* 背景アニメーション用カウンタ */
static long bak_alldrow = 0;						/* 背景の描画をクリップするか */
static long d_x = 0;								/* 背景表示位置 */
static long d_y = 0;								/* 背景表示位置 */
static long kamera = 0;
//static long disp_data[60];							/* セーブ一覧 */
static long next_px = 0;							/* 画面切り替え時のキャラ移動対策 */
static long next_py = 0;

static long map_rot_info = 0;							/* マップの向き */
#ifdef GP2X
static const long atk_rr1 =30;						/* 腕の回転速度 */
#else
static const long atk_rr1 =5;						/* 腕の回転速度 */
#endif 
//long atk_rr = 360 / 32;						/* 腕の回転速度 */

static long stage = 0;								/* ステージ番号 */
static long secretitemget = 0;						/* 隠しアイテムの取得 */
static uint32_t target_save[1024];

static long pshot[10 * 10];							/* プレイヤー攻撃用情報 */
static long pshotf[10 * 40];						/* プレイヤー攻撃用情報 */
static long pshotf2[10 * 80];						/* プレイヤー攻撃用情報 */
static long pmshot[20 * 40];						/* プレイヤー攻撃用情報 */
static long pjumpf[100];							/* プレイヤー攻撃用情報 */
static long item[20 * 50];							/* アイテム用バッファ */
static long item_wk[5*100];							/* 地面 その他のマップ情報 */
//static long enemy[40 * 20];								/* 敵情報															*/
static long enemy[30 * 30];							/* enm_data[1] * enm_data[2] 敵情報	*/

static long mgc_e[10 * 20] ;						/* MGC表示情報														*/
static long p_ef[1000] ;							/* 汎用バッファ（足跡等）														*/
//static long life_a[5];								/* HPアニメーション用 */
static long kane[200];								/* アイテム用バッファ */

static long Jump_counts = 0;
static long snack_count = 0;
static long all_snack_count = 0;
static long save_data[512];							/* 保存情報 */
static long test[5];
static long rayer[5];								/* 背景スクロール量 */
static long play_time[5];
/* リプレイ２０分 */
static uint32_t replay[60 * 60 * 10];	/* フレーム＊秒＊分 */
static long replay_time = 1;
static long replay_time_MAX = 60 * 60 * 10;	/* 最大時間 */
static long replay_load_key[10];
static long replay_file_name = 0;
static long replay_save_flag = 0;				/* 保存を行うか 1:しない */
static long rrkey[5];								/* 入力キー方向 */

//static long event_buff[100];
/* event_buff[0]	文字用ｳｨﾝﾄﾞｳ表示 */
/* event_buff[1]	顔表示 */
/* event_buff[2]	ｷｰ入力待ち */
/* event_buff[3]	wait */
/* event_buff[4]	実行イベントバッファポインタ */
/* event_buff[5]	顔表示 */
/* event_buff[7]	i */
/* event_buff[8]	player[2] */
/* event_buff[9]	player[3] */
/* event_buff[10]	画面更新 */
/* event_buff[11]	画面演出 */

/* TextLayer( 10 )はｲﾍﾞﾝﾄで使用（固定） */
/* プレーン80～90はｲﾍﾞﾝﾄで使用 */
/* wav30はｲﾍﾞﾝﾄで使用 */
//static long file_handle = 0	;
static long one_event = 0;							/* 重なって発生するイベントの前回重なっていたかのフラグ */
//static long start_plyer_disp = 1;					/* 開始時に表示するかフラグ */
//static long start_effct_disp = 0;					/* 開始時に効果を表示するかフラグ */


//----------------------------------------------------------------------
// メイン関数
void act_main( void )
{
	long exit_code;
	
	exit_code = 0;

	act_init( );		// 初期化
	
	while( scene_exit )
	{
//		KeyInput( );	// キー入力
		
//		act_keys( );		// キー処理
		act_drow( );		// 描画
		
		FPSWait( );		// 待ち

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	act_relese( );		// 終了
}

void act_init( void )
{
	long i;
	long x;
	long y;
	long wk;
	long d_num;

	scene_exit = 1;
	sn = 0;
	bak_cnt = 0;							/* 背景アニメーション用カウンタ */
	bak_alldrow = 0;						/* 背景の描画をクリップするか */
	d_x = 0;								/* 背景表示位置 */
	d_y = 0;								/* 背景表示位置 */
	next_px = 0;							/* 画面切り替え時のキャラ移動対策 */
	next_py = 0;
	stage = 0;								/* ステージ番号 */
	Jump_counts = 0;
	snack_count = 0;
	all_snack_count = 0;
	replay_time = 1;
	replay_time_MAX = 60 * 60 * 10;	/* 最大時間 */
	replay_save_flag = 0;				/* 保存を行うか 1:しない */
	one_event = 0;							/* 重なって発生するイベントの前回重なっていたかのフラグ */
	map_rot_info = 0;							/* マップの向き */
	secretitemget = 0;						/* 隠しアイテムの取得 */

//#if false
	memset( player, 0, sizeof( player ) );									/* プレイヤー用バッファ */
	memset( demo, 0, sizeof( demo ) );
	memset( map1, 0, sizeof( map1 ) );								/* 背景用バッファ レイヤー1 */
	memset( map2, 0, sizeof( map2 ) );								/* 背景用バッファ レイヤー2 */
	memset( map_data, 0, sizeof( map_data ) );
	memset( pshot, 0, sizeof( pshot ) );							/* プレイヤー攻撃用情報 */
	memset( pshotf, 0, sizeof( pshotf ) );						/* プレイヤー攻撃用情報 */
	memset( pshotf2, 0, sizeof( pshotf2 ) );						/* プレイヤー攻撃用情報 */
	memset( pmshot, 0, sizeof( pmshot ) );						/* プレイヤー攻撃用情報 */
	memset( pjumpf, 0, sizeof( pjumpf ) );							/* プレイヤー攻撃用情報 */
	memset( item, 0, sizeof( item ) );							/* アイテム用バッファ */
	memset( item_wk, 0, sizeof( item_wk ) );							/* 地面 その他のマップ情報 */
	memset( enemy, 0, sizeof( enemy ) );								/* 敵情報															*/
	memset( mgc_e, 0, sizeof( mgc_e ) ) ;						/* MGC表示情報														*/
	memset( p_ef, 0, sizeof( p_ef ) ) ;							/* 汎用バッファ（足跡等）														*/
	memset( kane, 0, sizeof( kane ) );								/* アイテム用バッファ */
	memset( save_data, 0, sizeof( save_data ) );							/* 保存情報 */
	memset( test, 0, sizeof( test ) );
	memset( rayer, 0, sizeof( rayer ) );								/* 背景スクロール量 */
	memset( play_time, 0, sizeof( play_time ) );
	memset( replay, 0, sizeof( replay ) );	/* フレーム＊秒＊分 */
	memset( replay_load_key, 0, sizeof( replay_load_key ) );
	memset( rrkey, 0, sizeof( rrkey ) );								/* 入力キー方向 */
	memset( string, 0, sizeof( string ) );								/* 入力キー方向 */
	memset( target_save, 0, sizeof( target_save ) );
//#endif

	/* かけら取得情報 */
	ResetGameFlag2();				/* ファイルなし */
//	LoadGameFlag2("save/item_wk.sav");
	for ( i = 0; i <= 500; i++ )
	{
		item_wk[i] = gameflag2[i];
	}
	
	ResetGameFlag2( );
	LoadGameFlag2( "save/work.sav");
	for ( i = 0; i < 512; i++ )
	{
		save_data[i] = gameflag2[i];
	}
	
	LoadFile( "data/target", &target_save[0], sizeof( target_save ) );
	
//	player[6] = save_data[8];	/* スキル */
//	player[7] = save_data[7];	/* ハートのかけら所持個数 */
	player[8] = 1;	/* HP */
	stage = save_data[2];
	d_num = save_data[3]; 	/* 画面 */
//	player[3] = save_data[4];	/* 向き */
	gameflag[120] = d_num;


	player[20] = 0;
	player[21] = 0;
	player[22] = 1;


	/* レイヤー１ */
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", ( int )stage , ( int )1, ( int )d_num );
	if ( 0 == LoadFile( string, map1, sizeof( map1 ) ) )
	{
		// File loaded OK
	}
	else 
	{
		/* ファイルがない */
		if ( gameflag[132] == 1 )	/* リプレイ */
		{
			g_scene = EN_SN_TITLE;	/* タイトルへ */
		}
		else 
		{
//			gameflag[40] = 5;	/* エンディングへ */
			g_scene = EN_SN_ENDING;	/* タイトルへ */
		}
		sn = 10;
	}
	for ( i = 0 ; i <= 20 ; i++ )
	{
		map_data[i] = map1[i + ( MapInfo[0] * MapInfo[1] )];
	}
	
	for ( i = 0 ; i < 5 ; i++ )
	{
		if ( map_data[11 + i] != 0 )
		{
			sprintf(string,"image/bak/%d_256.bmp", ( int )map_data[11 + i] );
//			sprintf(string,"image/bak/%d.bmp", ( long )map_data[11 + i] );
			if ( LoadBitmap(string,110 + i , 0 ) != 0 )					//プレーンナンバー２にシステム用ＢＭＰを読み込む
			{
				ReleaseBitmap(110 + i);
			}
		}
	}

//	if ( gameflag[70] == 1 )
//	{
//		gameflag[70] = 0;
//		player[0] = save_data[0];	/* X */
//		player[1] = save_data[1];	/* Y */
//	}
//	else 
//	{
		player[0] = map_data[9] * 32;
		player[1] = ( map_data[10] * 32 );
//	}
	if ( gameflag[128] != 0 )	//マップビュー
	{
		item_set( 1, player[0], player[1], 0, d_num );
	}
	
	/* レイヤー２ */
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", ( int )stage , ( int )2, ( int )d_num );
	LoadFile( string, map2, sizeof( map2 ) );

	/* アイテム配置 */
	ResetGameFlag2( );
	sprintf(string,"data/%d/i%d_%d.map", ( int )stage , ( int )1, ( int )d_num );
//	SetConstParam( "MessageBox", "" , string );
	LoadFile( string, mapfile, sizeof( mapfile ) );
	{
		for ( x = 0; x < MapInfo[0] ; x++ )
		{
			for ( y = 0; y < MapInfo[1] ; y++ )
			{
				if ( mapfile[x + ( y * MapInfo[0] )] != 0 )
				{
					if ( mapfile[x + ( y * MapInfo[0] )] == 1 )
					{
						//キャラクター
					}
					else 
					{ 
						item_set( mapfile[x + ( y * MapInfo[0] )], x * 32, ( ( MapInfo[1] - 1 - y ) * 32 ), x + ( y * MapInfo[0] ), d_num );
					}
				}
			}
		}
	}


	
	ResetGameFlag2();				/* ファイルなし */
	sprintf( string,"data/%d/e%d_%d.map", ( int )stage , ( int )1, ( int )d_num );
	LoadFile( string, mapfile, sizeof( mapfile ) );

	/* 敵配置 */
	for ( x = 0; x < MapInfo[0] ; x++ )
	{
		for ( y = 0; y < MapInfo[1] ; y++ )
		{
			if ( mapfile[x + ( y * MapInfo[0] )] != 0 )
			{
				enm_set( mapfile[x + ( y * MapInfo[0] )], x * 32, ( ( MapInfo[1] - 1 - y ) * 32 ) );
			}
		}
	}
	
	player[14] = 10;	/* ジャンプカウンタ */
	player[15] = player[0];
	player[16] = player[1];
	player[2] = 0;
	
	/* for test start */
//	player[7] = 9;
/*
	save_data[40] = 1;
	save_data[41] = 1;
	save_data[42] = 1;
	save_data[43] = 1;
*/
	/* for test end */
	
//	bak_make( );

	if ( gameflag[132] == 1 )
	{
		if ( 1 != replay_file_load( ) )
		{
			/* ファイルが読めなかった */
			g_scene = EN_SN_TITLE;	/* タイトルへ */
//			gameflag[40] = 1;
			sn = 10;
			return;
		}
	}
	else 
	{
	}


	soundSetVolumeMasterBgm( 100 );
	if ( gameflag[70] == 1 )
	{
		if (
		     ( ( save_data[3] >  0 ) && ( save_data[3] <= 10 ) ) 
		   )
		{
			soundPlayBgm( EN_BGM_GAME02 );
		}
		if (
		     ( ( save_data[3] > 10 ) && ( save_data[3] <= 20 ) ) 
		   )
		{
			soundPlayBgm( EN_BGM_GAME03 );
		}
		if (
		     ( ( save_data[3] > 20 ) && ( save_data[3] <= 30 ) )
		   )
		{
			soundPlayBgm( EN_BGM_GAME04 );
		}
		if (
		     ( ( save_data[3] > 30 ) && ( save_data[3] <= 40 ) )
		   )
		{
			soundPlayBgm( EN_BGM_GAME05 );
		}
		if (
		     ( ( save_data[3] > 40 ) && ( save_data[3] <= 50 ) )
		   )
		{
			soundPlayBgm( EN_BGM_GAME06 );
		}
	}
	else 
	{
		if ( gameflag[71] == 0 )
		{
			if (
			     ( ( save_data[3] ==  1 ) ) 
			   )
			{
				soundPlayBgm( EN_BGM_GAME02 );
			}
			if (
			     ( ( save_data[3] == 11 ) ) 
			   )
			{
				soundPlayBgm( EN_BGM_GAME03 );
			}
			if (
			     ( ( save_data[3] == 21 ) ) 
			   )
			{
				soundPlayBgm( EN_BGM_GAME04 );
			}
			if (
			     ( ( save_data[3] == 31 ) )
			   )
			{
				soundPlayBgm( EN_BGM_GAME05 );
			}
			if (
			     ( ( save_data[3] == 41 ) )
			   )
			{
				soundPlayBgm( EN_BGM_GAME06 );
			}
		}
	}
	
	gameflag[71] = 0;
	gameflag[70] = 0;

	if ( gameflag[127] == 1 )	//トータルアタック
	{
//		sprintf( string[0],"%d", gameflag[135] );
//		MidStr(string[0],6,2,string[1]);
		wk = get2keta( gameflag[135] , 1 );
		play_time[0] = play_time[0] + wk;
		if ( play_time[0] >= 60 )
		{
			play_time[0] = play_time[0] - 60;
			play_time[1]++; 
		}
//		sprintf( string[0],"%d", gameflag[135] );
//		MidStr(string[0],4,2,string[1]);
		wk = get2keta( gameflag[135] , 100 );
		play_time[1] = play_time[1] + wk;
		if ( play_time[1] >= 60 )
		{
			play_time[1] = play_time[1] - 60;
			play_time[2]++; 
		}
		
//		sprintf( string[0],"%d", gameflag[135] );
//		MidStr(string[0],2,2,string[1]);
		wk = get2keta( gameflag[135] , 10000 );
		play_time[2] = play_time[2] + wk;
		if ( play_time[2] >= 999 )
		{
			play_time[2] = 999;
			play_time[1] = 59;
			play_time[0] = 59;
		}
		
		if ( gameflag[40] == 5 )
		{
			if ( gameflag[137] > gameflag[135] )	//トータルアタック クリア時間
			{
				gameflag[137] = gameflag[135];
			}
			if ( gameflag[138] > gameflag[136] )	//トータルアタック クリアジャンプ
			{
				gameflag[138] = gameflag[136];
			}
		}
	}


	sprintf(string,"image/player/ri%d.bmp", ( int )gameflag[122] );
	LoadBitmap(string,1,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/player/mgc1.bmp",2,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/player/atk1.bmp",3,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/player/atk2.bmp",4,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む

	LoadBitmap("image/player/atkf.bmp",5,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/player/cutin.bmp",6,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む

	sprintf(string,"image/map/map%d_1.bmp", ( int )stage );
	LoadBitmap(string,10,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	sprintf(string,"image/map/map%d_2.bmp", ( int )stage );
	LoadBitmap(string,11,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	sprintf(string,"image/map/item%d.bmp", ( int )stage );
	LoadBitmap(string,12,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む


	LoadBitmap("image/sys/map_f0.bmp",15,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/map_f1.bmp",16,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/map_f2.bmp",17,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/fonts2.bmp",18,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/sc.bmp",19,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む

	LoadBitmap("image/sys/p_data.bmp",20,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/skill.bmp",21,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/hp.bmp",22,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/hp2.bmp",23,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	
	LoadBitmap("image/sys/pause.bmp",24,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む

	/* 25～30はイベントで使用 */

	/* 31は画面効果で使用 */
	
	LoadBitmap("image/enm/e32.bmp",40,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/enm/e48.bmp",41,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/enm/e64.bmp",42,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	
	LoadBitmap("image/enm/e_shot.bmp",50,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む

	LoadBitmap("image/player/font_d.bmp",51,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/player/hp.bmp",52,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	

	LoadBitmap("image/sys/menu.bmp",60,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/title/scl.bmp",61,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/window_item.bmp",62,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む

	LoadBitmap("image/player/arm.bmp",65,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/player/arm2.bmp",66,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/input.bmp",67,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/new.bmp",68,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/new2.bmp",69,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/mini_map.bmp",70,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/stagestart.bmp",71,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/bak/0.bmp",72,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/new3.bmp",73,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/scor.bmp",74,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/sys/houkou.bmp",75,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む

	LoadBitmap("image/sys/waku.bmp",109,true);					//プレーンナンバー２にシステム用ＢＭＰを読み込む
	LoadBitmap("image/color.bmp",127,false);

	CreateSurface( 125, 640, 640 );
	SetPalette(127, 125);	// パレットの設定
	SetColorKey(125, true );	// カラーキーの設定
/*
	SaveBmp( -1, "bmp1.bmp" );
	SaveBmp( 125, "bmp125.bmp" );
	SaveBmp( 127, "bmp127.bmp" );
*/

	CreateSurface( 124, 640 * 5, 480 * 5 );
	SetPalette(127, 124);	// パレットの設定
	
	if ( gameflag[128] != 0 )	//マップビュー
	{
		sn = 6;
	}

}

void act_relese( void )
{
	long i;
	
	save_file_w( );

	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		ReleaseBitmap( i );
	}
//	soundStopBgm(EN_BGM_GAME01);

}


void act_keys( void )
{
	long i;
	long old_x;
	long houkou;
	long kakudosa;
	
	houkou = 0;
	kakudosa = 0;
	
	if ( ( sn == 1 ) || ( sn == 5 ) )
	{
		play_time[0] = play_time[0] + 1;
		if ( play_time[0] >= 60 )
		{
			play_time[0] = 0;
			play_time[1] = play_time[1] + 1;
			if ( play_time[1] >= 60 )
			{
				play_time[1] = 0;
				play_time[2] = play_time[2] + 1;
				if ( play_time[2] >= 60 )
				{
					if ( play_time[2] >= 10 )
					{
						play_time[2] = 10;
					}
				}
			}
		}
	}
	if ( gameflag[132] == 0 )
	{
		replay_input_save( );		/* リプレイデータ保存 */
	}
	else 
	{
		replay_input_load( );		/* リプレイデータ再生 */
	}
	replay_time++;
	if ( replay_time > replay_time_MAX )
	{
		replay_time = replay_time_MAX;	/* 最大時間を越えた、保存しない */
		replay_save_flag = 1;			/* 保存しない */
	}

	for ( i = 0; i < 5; i++ )
	{
		rrkey[i] = 0;						/* 入力キー方向 */
	}

	player[17]--;			/* 無敵時間 */
	if ( player[17] <= 0 )
	{
		player[17] = 0;
	}
	if ( player[9] == 0 )
	{
		jmp( );
	}
	
	
	if ( ( item_up( ) != -1 ) && ( player[14] == 10 ) )	/* アイテムの上に乗っている */
	{
		player[1] = item_up( ); 
	}
	
	player[19] = 0;	// 回転可能かフラグ

	if ( player[2] == 31 )
	{
		if ( player[3] == 1 ) 
		{
//			player[0] = player[0] + 3;
//			idou_r( );
		}
		else 
		{
//			player[0] = player[0] - 3;
//			idou_l( );
		}
	}
	else 
	{
		old_x = player[0];
		
		if ( player[9] == 1 )	//回転中
		{
		}
		else
		{
			if ( ( ( IsPressKey( gameflag[2] ) ) && ( gameflag[132] == 0 ) )		// 左
		  || ( ( replay_load_key[0] == 1 ) && ( gameflag[132] == 1 ) ) )
			{
				
				player[3] = 1;	/* 向き */
				if ( player[2] == 0 )
				{
					player[10] = 0;	/* アニメーション間隔フレーム設定 */
					player[11] = 0;	/* アニメーションカウンタ */
					player[2] = 1;	/* 歩き */
				}
				else if ( player[2] == 1 )
				{
					player[0] = player[0] - 2;	/* キャラクター移動 */
				}
				else if ( player[2] == 21 )
				{
					player[0] = player[0] - 2;	/* キャラクター移動 */
				}

			}
			else if ( ( ( IsPressKey( gameflag[3] ) ) && ( gameflag[132] == 0 ) )	// 右
		  || ( ( replay_load_key[1] == 1 ) && ( gameflag[132] == 1 ) ) )
			{
				player[3] = 0;
				if ( player[2] == 0 )
				{
					player[10] = 0;
					player[11] = 0;
					player[2] = 1;
				}
				else if ( player[2] == 1 )
				{
					player[0] = player[0] + 2;
				}
				else if ( player[2] == 21 )
				{
					player[0] = player[0] + 2;
				}
			}
			else 
			{
				if ( player[2] == 1 )
				{
					player[10] = 0;
					player[11] = 0;
					player[2] = 0;
				}
			}
		}	

		
		
		if ( player[28] != 0 )	/* 移動床 */
		{
			player[0] = player[0] + player[28];
		}
		player[28] = 0;
		
		if ( player[29] > 0 )	/* 移動床 */
		{
			player[0] = player[0] + ( player[29] * 1 );
			player[29] = player[29] - 1;
		}
		else if ( player[29] < 0 )
		{
			player[0] = player[0] + ( player[29] * 1 );
			player[29] = player[29] + 1;
		}
		
		/* 前回の位置から移動した */
		if ( old_x > player[0] )
		{
			idou_l( );	/* 左移動の壁判定 */
		}
		else if ( old_x < player[0] )
		{
			idou_r( );	/* 右移動の壁判定 */
		}
		player[33] = ( player[0] - old_x );
		
		
		if ( ( ( IsPressKey( gameflag[0] ) ) && ( gameflag[132] == 0 ) )
		  || ( ( replay_load_key[2] == 1 ) && ( gameflag[132] == 1 ) ) )
		{
			/* 立ち、歩き */
//			if ( ( player[2] == 0 ) || ( player[2] == 1 ) )
//			{
//				item_event( );
//			}
		}
		else if ( ( ( IsPressKey( gameflag[1] ) ) && ( gameflag[132] == 0 ) )
		  || ( ( replay_load_key[3] == 1 ) && ( gameflag[132] == 1 ) ) )
		{
		}
		
		
		//	スペースキーが押される
		if ( ( ( IsPressKey( gameflag[4] ) )  && ( gameflag[132] == 0 ) ) 		/* 移動速度低下 */
		  || ( ( replay_load_key[4] == 1 ) && ( gameflag[132] == 1 ) ) )
		{
			if ( player[19] != 0 )	//
			{
				if ( player[9] == 0 )
				{
					soundPlaySe( EN_SE_PAWA );
					sn = 5;
					player[20] = 0;
					player[21] = 0;
					player[22] = 0;

					player[10] = 0;
					player[11] = 0;
					player[4] = 0;
					player[5] = 3;
					player[2] = 2;		// つかみ

					bak_make( );


					if ( player[19] == 1 )	//
					{
						player[22] = 10;
						player[20] = player[21];
						player[21] = player[21] + 90;
					}
					if ( player[19] == 2 )	//
					{
						player[22] = 10;
						player[20] = player[21];
						player[21] = player[21] - 90;
					}
					if ( player[21] < 0 )
					{
						player[21] = player[21] + 360;
					}
					if ( player[21] >= 360 )
					{
						player[21] = player[21] - 360;
					}

				}
				player[9] = 1;
			}
		}

		kakudosa = ( player[21] - player[20] );		// 回転が終了した
		if ( kakudosa == 0 )		// 差がない場合は回さない
		{
			if ( player[9] == 1 )
			{
				Jump_counts++;
				soundPlaySe( EN_SE_ATK1 );
				rotmap( player[21] );	// 回転
				
				player[10] = 0;
				player[11] = 0;
				player[2] = 0;		// ﾆｭｰﾄﾗﾙ

				player[14] = 0;		// 落下
				player[13] = 0;
				
				player[1] = player[1] + 8;	// あたり判定が長方形なので浮かせる

				sn = 1;
				player[9] = 0;
				
				switch( player[21] )
				{
				case 90:
					map_rot_info = map_rot_info - 1;							/* マップの向き */
					break;
				case 180:
					map_rot_info = map_rot_info + 2;							/* マップの向き */
					break;
				case 270:
					map_rot_info = map_rot_info + 1;							/* マップの向き */
					break;
				default:
					break;
				}
				if ( map_rot_info < 0 )	// 超えた
				{
					map_rot_info = map_rot_info + 4;
				}
				if ( map_rot_info > 3 )	// 超えた
				{
					map_rot_info = map_rot_info - 4;
				}

			}
		}
		else 
		{
			if ( kakudosa == 0 )		// 差がない場合は回さない
			{
			}
			else if ( kakudosa < 0 ) // 目標角度に対して現在地はプラス
			{
				if ( -180 > kakudosa )  // 180度超えている場合は逆回転
				{
					player[20] = player[20] + atk_rr1;
					houkou = 1;
				}
				else 
				{
					player[20] = player[20] - atk_rr1;
					houkou = 0;
				}
			}
			else if ( kakudosa > 0 ) // 目標角度に対して現在地はマイナス
			{
				if ( 180 < kakudosa )
				{
					player[20] = player[20] - atk_rr1;
					houkou = 0;
				}
				else 
				{
					player[20] = player[20] + atk_rr1;
					houkou = 1;
				}
			}
			// 360度を越えた場合は0度にオフセット
			if ( player[20] < 0 )
			{
				player[20] = player[20] + 360;
			}
			if ( player[20] >= 360 )
			{
				player[20] = player[20] - 360;
			}
		}
		
		//Bが押される
		if ( ( ( ( IsPushKey( gameflag[5] ) ) || ( IsPushKey( gameflag[0] ) && ( gameflag[133] == 1 ) ) ) && ( gameflag[132] == 0 ) )
		  || ( ( replay_load_key[6] == 1 ) && ( gameflag[132] == 1 ) ) )
		{
			if ( player[9] == 0 )	// つかんでいない
			{
				if ( ( player[2] != 11 ) && ( player[2] != 31 ) && ( player[14] == 10 ) )	/* 地上で攻撃、ダメージじゃない */
				{
					if (
						   ( ( ( map1_item_j( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ) ) >= 100 )
						    && ( map1_item_j( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ) ) <= 119 ) )
						  || ( ( map1_item_j( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ) ) >= 200 )
						    && ( map1_item_j( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ) ) <= 219 ) ) )
					   )
					{
					}
					else 
					{
						soundPlaySe( EN_SE_JUMP );
						/* アイテムに乗っていない場合はそこがリトライ位置 */
						if ( item_up( ) == -1 )
						{
							player[15] = player[0];
							player[16] = player[1];
						}
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	/* 空中 */
						player[14] = 5;
						player[13] = 0;
						player[25] = 1;
						jmp_st( );
					}
				}
			}
		}
		if ( ( ( IsPressKey( gameflag[5] ) ) && ( gameflag[132] == 0 ) )
		  || ( ( replay_load_key[5] == 1 ) && ( gameflag[132] == 1 ) ) )
		{
		}
		else 
		{
			if ( player[14] == 10 )
			{
			}
			else 
			{
				if ( ( player[14] > 0 ) && ( player[25] == 1 ) )	/* 途中で落下 */
				{
//					player[14] = -1;
				}
			}
			player[25] = 0;
		}
		
		
	}
	if ( Jump_counts > 99 )
	{
		Jump_counts = 99;
	}
	
	/* 12ボタン　か　Ｃが押された */
	if ( IsPushKey( gameflag[6] ) )
	{
		if ( sn != 5 )	//回転中ではない
		{ 
			sn = 4;
			demo[0] = 0;
			demo[1] = 0;
		}
	}
	
	/* スキルショートカットウィンドウ */
	if ( IsPushKey( gameflag[7] ) )
	{
	}



	if ( player[0] < 0 )	/* 画面左端判定 */
	{
		player[0] = 0;
		/*
		イベント中にsave_data[9]を設定することで、一時的にスクロール不可とする。
		ボス戦などに使用
		*/
		if ( save_data[9] == 1 )	/* スクロール不可 */
		{
		}
		/* アイテムに乗っている場合はスクロールしない */
/*
		else if ( ( stage == 7 ) && ( item_up( ) != -1 ) )
		{
		}
*/
		else 
		{
			if ( player[1] <= 460 )					/* キャラクター上方向が画面内 */
			{
				if ( map_data[4] == 1 )			/* スクロール情報あり */
				{
					wait_scl( 2, map_data[5] );	/* スクロール */
				}
				else if ( map_data[4] == 2 )	/* ステージ移動情報あり */
				{
					end_scl( map_data[5] );		/* ステージ移動 */
				}
			}
		}
	}
	if ( player[0] > ( MapInfo[2] - char_size[0] ) )	/* 画面右端判定 */
	{
		player[0] =  MapInfo[2] - char_size[0];
		if ( save_data[9] == 1 )	/* スクロール不可 */
		{
		}
/*
		else if ( ( stage == 7 ) && ( item_up( ) != -1 ) )
		{
		}
*/
		else 
		{
			if ( player[1] <= ( MapInfo[1] ) )
			{
				if ( map_data[6] == 1 )
				{
					wait_scl( 3, map_data[7] );
				}
				else if ( map_data[6] == 2 )
				{
					end_scl( map_data[7] );
				}
			}
		}
	}
	if ( player[1] <= 0 )	/* 画面下 */
	{
		if ( save_data[9] == 1 )	/* スクロール不可 */
		{
		}
		else 
		{
			if ( map_data[2] == 1 )
			{
				wait_scl( 1, map_data[3] );
			}
			else if ( map_data[2] == 2 )
			{
				end_scl( map_data[3] );
			}
		}
	}
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )	/* 画面上 */
	{
		if ( save_data[9] == 1 )	/* スクロール不可 */
		{
		}
		else 
		{
			if ( map_data[0] == 1 )
			{
				wait_scl( 0 , map_data[1] );
			}
			else if ( map_data[0] == 2 )
			{
				end_scl( map_data[1] );
			}
		}
	}

}

void fram_set( )
{
	if ( player[2] == 0 )	/* ニュートラル */
	{
		player[12] = 10;
	}
	if ( player[2] == 1 )	/* 歩き */
	{
		player[12] = 10;
	}
	if ( player[2] == 2 )	/* つかみ */
	{
		player[12] = 5;
	}
	if ( player[2] == 11 )	/* 攻撃 */
	{
		player[12] = 2;
	}
	if ( player[2] == 21 )	/* 空中 */
	{
		player[12] = 5;
	}
	if ( player[2] == 31 )	/* やられ */
	{
		player[12] = 10;
	}
	if ( player[2] == 33 )	/* クリア */
	{
		player[12] = 10;
	}
	if ( player[2] == 61 )	/* 上向き */
	{
		player[12] = 10;
	}
}


/* すい中の場合はジャンプ力増加 */
void jmp_st( )
{
	long px1 ;
	long px2 ;
	long py ;
	long py2 ;

	px1 = ( player[0] + char_size[2] ) / 32;
	px2 = ( player[0] + char_size[3] ) / 32;
	py = ( MapInfo[1] - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + char_size[1] + ( char_size[1] - 5 ) ) / 32 ) );
	/* 水中判定 */

	if ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 319 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 319 ) 
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 419 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 419 )  
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 318 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 318 )    
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 418 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 418 )  
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 719 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 719 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 718 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 718 ) )
	{
//		player[14] = player[14] + 1; 		/* ジャンプフラグ */
//		if ( player[14] >= 9 )
//		{
//			player[14] = 9;
//		}
	}
	else 
	{
	}
}

/* ジャンプＹ位置計算 */
void jmp( )
{
	long y1;
	long px ;
	long px1 ;
	long px2 ;
	long py ;
	long py3 ;
	
	/* ジャンプフレームカウント */
	player[13]++;
	if ( player[13] >= 10 )
	{
		player[13] = 0;
	}
	
	if ( player[2] == 41 )	/* はしご中 */
	{
		player[18] = 0;			/* つかみからジャンプ */
		player[28] = 0;			/* 流されている */

		player[14] = 10;
		return;
	}
	
	/* 今回の位置 */
	px = ( player[0] + ( char_size[0] / 2 ) ) / 32;
	px1 = ( player[0] + char_size[2] ) / 32;
	px2 = ( player[0] + char_size[3] ) / 32;
//		py = ( 16 - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );
	py = ( MapInfo[1] - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );
	
	if ( player[14] == 10 ) 	/* 地上 */
	{
		
		/* 100 ～ 200は地面 */
		/* 足元が地面ではない */
		if ( ( ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) ) 
		  && ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) ) 
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) )
		  && ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) ) )
		  || ( ( ( player[1] ) % 32 ) != 0 ) )
		{
			if ( item_up( ) != -1 )	/* アイテムの上に乗っている */
			{
				player[1] = item_up( ); 
				player[14] = 10;
				return;
			}
			
			/* 歩き中なら空中状態へ移行 */
			if ( ( player[2] == 0 )
			  || ( player[2] == 1 ) )
			{
				player[10] = 0;
				player[11] = 0;
				player[2] = 21;		/* 空中 */
			}
			player[14] = -1;			/* 落下開始 */
			player[13] = 0;
			
			if ( player[2] == 31 )	/* ダメージ中 */
			{
			}
		}
		else
		{
			return;
		}
	}
	else 
	{
		/* 歩き中なら空中状態へ移行 */
		if ( ( player[2] == 0 )
		  || ( player[2] == 1 ) )
		{
			player[10] = 0;
			player[11] = 0;
			player[2] = 21;		/* 空中 */
		}
		player[22] = 0;					/* 盾カウンタ */
	}

	/* 10フレームに1回Y座標計算 */
	if ( player[13] == 0 )	
	{
		player[14] = player[14] - 2;	/* ジャンプ力減少 */

		/* 頂点付近は-1落下開始とする */
		if ( ( player[14] <= 2 ) && ( player[14] > -2 ) )
		{
			player[14] = -1;
		}

		if ( player[14] < -4 )	/* 最速落下を設定 */
		{
			player[14] = -4;
		}
	
		if ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 319 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 319 ) 
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 419 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 419 )  
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 318 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 318 )    
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 418 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 418 )  
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 719 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 719 )
		  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 718 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 718 ) )
		{
		}
	}
	
	/* 水中判定等の背景によって落下速度が変わる場合は判定する */
	/* 今回の位置 */
	y1 = ( ( 0 - player[14] ) * ( 0 - player[14] ) * ( 0 - player[14] ) );
	px1 = ( player[0] + char_size[2] ) / 32;
	px2 = ( player[0] + char_size[3] ) / 32;
	py = ( MapInfo[1] - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );

	if ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 319 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 319 ) 
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 419 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 419 )  
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 318 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 318 )    
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 418 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 418 )  
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 719 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 719 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 718 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 718 ) )
	{
		if ( player[14] > 0 ) /* 上昇中 */
		{
			player[1] = player[1] - ( y1 / 15 );
		}
		else 
		{
			player[1] = player[1] - ( y1 / 50 );
		}
	}
	else 
	{

		player[1] = player[1] - ( y1 / 20 );	/* Y移動 */
	}


	/* 落下、上昇可能判定 */
	/* 画面外の場合は行わない */ 
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		return;
	}
	py3 = ( MapInfo[1] - ( ( player[1] + char_size[1] + 32 ) / 32 ) );

	/* 落下 */
	if ( player[14] <= 0 )													/* 上り中は判定しない */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) 
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) 
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		{
			/* 着地 */
			if ( player[8] > 0 )	/* HPがある場合は効果音を鳴らす */
			{ 
				soundPlaySe( EN_SE_LANDING );
				se_wav( 9 );
			}
			if ( ( player[2] != 31 ) && ( player[2] != 32 ) )	/* ダメージ中じゃない */
			{
				player[2] = 0;							/* 立ち状態へ */
				player[11] = 0;							/* アニメーションカウンタクリア */
			}
			player[1] = ( ( MapInfo[1] - py ) * 32 ); 		/* 着地したマスのY座標に合わせる */
			player[14] = 10;								/* ジャンプ力を地上に設定 */

			player[18] = 0;			/* つかみからジャンプ */
			player[28] = 0;			/* 流されている */

			p_jump_f_set( player[0], player[1] );
		}
		else 
		{
			if ( item_up( ) != -1 )						/* アイテムの上に乗っている */
			{
				soundPlaySe( EN_SE_LANDING );
				se_wav( 9 );
				if ( ( player[2] != 31 ) && ( player[2] != 32 ) )	/* ダメージ中じゃない */
				{
					player[2] = 0;							/* 着地 */
					player[11] = 0;							/* アニメーションカウンタクリア */
				}
				player[1] = item_up( ); 
				player[14] = 10;

				player[18] = 0;			/* つかみからジャンプ */
				player[28] = 0;			/* 流されている */

				p_jump_f_set( player[0], player[1] );
			}
		}
	}
	else		/* 上昇中 */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) ) )
		{
			/* 頭がぶつかった */
			player[13] = 0;
			player[14] = -3;		/* 落下 */
		}
		else 
		{
			if ( item_up2( ) != -1 )	/* アイテムに頭がぶつかる */
			{
				player[1] = item_up2( ); 
				player[13] = 0;
				player[14] = -3;
			}
		}
	}
	/* 画面外、下に行った */
	if ( player[1] <= -14 )
	{
		if ( map_data[2] == 0 )		/* スクロールしない場合はダメージ */
		{
			if ( player[8] > 0 )			/* HPがある */
			{ 
				if ( player[17] == 0 )	/* 無敵時間が無い */
				{
					player[17] = 120;	/* 無敵時間 */
					player[8] = player[8] - 1;/* ダメージ */
					se_wav( 1 );	/* ダメージ効果音 */
				}
				if ( player[8] > 0 )		/* HPがある */
				{ 
					player[0] = player[15];	/* リトライ位置に移動 */
					player[1] = player[16];
					wait_scl2( save_data[3] ,player[0], player[1] );	/* 暗転戻り */
					
//					player[13] = 0;
//					player[14] = 6;
				}
				else 
				{
					player[1] = -14;
				}
			}
			else
			{
				player[1] = -14;
			}
		}
	}

}

/* 左方向への移動判定 */
void idou_l( )
{
	long px ;
	long py1 ;
	long py2 ;
	long bx ;
	long by ;

	long i;


	/* 今回の位置 */
	/* player[29]横バネ吹き飛び補正 */
	px = ( player[0] + char_size[2] + player[29] ) / 32;
	py1 = ( MapInfo[1] - ( ( player[1] + 32 + ( char_size[1] / 2 )  ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + 32 + 5 ) / 32 ) ); 						/* 足より５ドット高い場所を判定する */
	/* 画面外は一番上で判定 */ 
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		py1 = 0;
		py2 = 0;
	}

	/* 502はしご上　501はしご中 */
	/* 壁に埋まった場合は壁際に移動 */
	if ( ( ( map1[ px + ( ( py1 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px + ( ( py1 ) * MapInfo[0] ) ] <= 299 ) )
	  || ( ( map1[ px + ( ( py2 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px + ( ( py2 ) * MapInfo[0] ) ] <= 299 ) ) )
	{
		px = ( player[0] + 16 ) / 32;
		player[0] = px * 32 - char_size[2];
		player[29] = 0;
		
		player[19] = 1;	//
	}
	else 
	{
	
	}
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[( i * item_data[2] ) + 3 ] % 100;
			by = item[( i * item_data[2] ) + 3 ] / 100;
			/* プレイヤーとの当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0]  + player[29] + char_size[3] ) )	/* 自機とのあたり判定 */
				&& ( (player[0] + player[29] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + char_size[1] - 5 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
			{
				if (
				     ( by == 6 ) /* 移動不可アイテム */
				   )
				{
					//スイッチブロックの場合は埋まる
//					player[0] = item[( i * item_data[2] ) + 1 ] + item_data[0] - char_size[2];
					px = ( player[0] + 16 ) / 32;
					player[0] = px * 32 - char_size[2];

					player[29] = 0;
					player[19] = 1;	//
				}
				if (
				     ( by == 3 ) /* 移動不可アイテム */
				   )
				{
					//移動ブロックの場合は端に位置修正
					player[0] = item[( i * item_data[2] ) + 1 ] + item_data[0] - char_size[2];
//					px = ( player[0] + 16 ) / 32;
//					player[0] = px * 32 - char_size[2];

					player[29] = 0;
					player[19] = 1;	//
				}
			}
		}
	}

}
/* 自分の左右に移動可能か？ */
void idou_r( )
{
	long px ;
	long py1 ;
	long py2 ;
	long bx ;
	long by ;

	long i;

	/* 今回の位置 */
	/* player[29]横バネ吹き飛び補正 */
	px = ( player[0] + char_size[3] + player[29] ) / 32;
	py1 = ( MapInfo[1] - ( ( player[1] + 32 + ( char_size[1] / 2 ) ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + 32 + 5 ) / 32 ) ); /* 足より５ドット高い場所を判定する */
	/* 画面外は一番上で判定 */ 
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		py1 = 0;
		py2 = 0;
	}

	/* 502はしご上　501はしご中 */
	if ( ( ( map1[ px + ( ( py1 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px + ( ( py1 ) * MapInfo[0] ) ] <= 299 ) )
	  || ( ( map1[ px + ( ( py2 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px + ( ( py2 ) * MapInfo[0] ) ] <= 299 ) ) )
	{
		px = ( player[0] + 16 ) / 32;
		player[0] = px * 32 + 9;
		player[29] = 0;

		player[19] = 2;
	}
	else 
	{
	}
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[( i * item_data[2] ) + 3 ] % 100;
			by = item[( i * item_data[2] ) + 3 ] / 100;
			/* プレイヤーとの当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + player[29] + char_size[3] ) )	/* 自機とのあたり判定 */
				&& ( (player[0] + player[29] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + 32 ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + char_size[1] - 5 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) ) )
			{
				if (
				     ( by == 6 ) /* 移動不可アイテム */
				   )
				{
					//スイッチブロックの場合は埋まる
//					player[0] = item[( i * item_data[2] ) + 1 ] - char_size[3];
					px = ( player[0] + 16 ) / 32;
					player[0] = px * 32 + 9;

					player[29] = 0;
					player[19] = 2;
				}
				if (
				     ( by == 3 ) /* 移動不可アイテム */
				   )
				{
					//移動ブロックの場合は端に位置修正
					player[0] = item[( i * item_data[2] ) + 1 ] - char_size[3];
//					px = ( player[0] + 16 ) / 32;
//					player[0] = px * 32 + 9;

					player[29] = 0;
					player[19] = 2;
				}
			}
		}

	}

}

void cleaer_ankr( long ankr_flag )
{
}

void act_drow( void )
{
	//-------------------------------------------------------------
	//変数宣言
	//-------------------------------------------------------------

	//背景クリア
//	ClearSecondary();

	switch( sn )							/* snによって描画するものを変える */
	{
	case 0:		//開始デモ
		bg_disp();
		bakdisp1( );
		bakdisp2( );
		item_disp( );
		item_line( );
		enm_disp( );
		playerdisp( );
		snack_counter_disp( ); // おやつカウンタ
		mapdisp( );
		stage_start( );
		debugdisp( );
		//-----------------------------------------------------------------------------------
		break;
	case 1 :		//アクション
		act_keys( );
		bg_disp();
		bakdisp1( );
		bakdisp2( );
		item_disp( );
		item_line( );
		kane_disp( );
		enm_disp( );
		e_shot_disp( );
		playerdisp( );
		p_jump_f_disp( );
		p_shot_disp( );
		p_mgc_disp( );
		p_shot_f2_disp( );
		p_shot_f_disp( );
//		minimap_disp( );
		snack_counter_disp( ); // おやつカウンタ
		mapdisp( );
		debugdisp( );		/* デバッグ情報 */
		stage_endj( );
		//-----------------------------------------------------------------------------------
		break;
	case 2 :		//クリアデモ
		bg_disp();
		bakdisp1( );
		bakdisp2( );
		item_disp( );
		item_line( );
//		enm_disp( );
//		e_shot_disp( );
//		jmp( );
//		p_shot_disp( );
//		p_mgc_disp( );
		p_shot_f2_disp( );
//		minimap_disp( );
		snack_counter_disp( ); // おやつカウンタ
		mapdisp( );
		stage_claer( );
		playerdisp( );
		debugdisp( );
		//-----------------------------------------------------------------------------------
		break;
	case 3 :		//ゲームオーバー
		bg_disp();
		bakdisp1( );
		bakdisp2( );
		item_disp( );
		item_line( );
		enm_disp( );
		e_shot_disp( );
		jmp( );
		playerdisp( );
		p_shot_disp( );
		p_mgc_disp( );
		p_shot_f2_disp( );
//		minimap_disp( );
		snack_counter_disp( ); // おやつカウンタ
		mapdisp( );
		stage_end( );
		debugdisp( );
		//-----------------------------------------------------------------------------------
		break;
	case 4 :		//アイテム
		window_keys( );
		bg_disp();
		bakdisp1( );
		bakdisp2( );
		item_disp( );
		item_line( );
		kane_disp( );
		enm_disp( );
		e_shot_disp( );
		playerdisp( );
		p_jump_f_disp( );
		p_shot_disp( );
		p_mgc_disp( );
		p_shot_f2_disp( );
		p_shot_f_disp( );
//		minimap_disp( );
		snack_counter_disp( ); // おやつカウンタ
		mapdisp( );
		window_disp( );
		debugdisp( );
		//-----------------------------------------------------------------------------------
		break;
	case 5 :		//回転
		//-----------------------------------------------------------------------------------
		act_keys( );
		bg_disp();
		bak_rot( );
//		minimap_disp( );
		snack_counter_disp( ); // おやつカウンタ
		mapdisp( );
		debugdisp( );		/* デバッグ情報 */
		break;
	case 6 :		//マップビュー
		//-----------------------------------------------------------------------------------
		mapviwe_keys( );
		bg_disp();
		bakdisp1( );
		bakdisp2( );
		item_disp( );
		item_line( );
		kane_disp( );
		enm_disp( );
		e_shot_disp( );
		playerdisp( );
		p_jump_f_disp( );
		p_shot_disp( );
		p_mgc_disp( );
		p_shot_f2_disp( );
		p_shot_f_disp( );
//		minimap_disp( );
		snack_counter_disp( ); // おやつカウンタ
		mapdisp( );
		debugdisp( );		/* デバッグ情報 */
		stage_endj( );
		break;
	default :	//	どの条件にも満たない場合
		
		ClearSecondary();
		/* 画面切り替え時の表示対策 */
		player[0] = next_px;
		player[1] = next_py;
		
		scene_exit = 0;
		return;
		break;
	}

//	if ( gameflag[61] == 0 )
//	{
//		Blt( 109 , -160, -120 );
//	}

	//画面の描画
	halt( );
//	SDL_Flip( g_screen );	// 描画
	//キー入力検査
	KeyInput();				
	
}

/* 一時ファイル保存 */
void save_file_w( )
{
	long i;

	SaveGameFlag("save/config");

	
	ResetGameFlag2( );
//	save_data[7] = player[7];	/* ハートのかけら所持個数 */
	save_data[5] = player[8];	/* HP */
	save_data[2] = stage;
	
	save_data[0] = player[0];	/* Ｘ */
	save_data[1] = player[1];	/* Ｙ */
	save_data[4] = player[3];	/* 向き */
//	save_data[8] = player[6];	/* スキル */

	for ( i = 0; i < 512; i++ )
	{
		gameflag2[i] = save_data[i];
	}
	SaveGameFlag2( "save/work.sav");
	
	/* アイテム取得情報 */
	ResetGameFlag2();				
	for ( i = 0; i < 500; i++ )
	{
		gameflag2[i] = item_wk[i];
	}
	SaveGameFlag2("save/item_wk.sav");

}


/**********************************/
/* プレイヤーの状態決定処理       */
/**********************************/

void playerdisp( )
{
	long arm_muki;
	
	arm_muki = 0;
	
	player[10]++;
	if ( player[10] >= player[12] )
	{
		player[10] = 0;
		
		player[11]++;
		/* 8パターンで1パターン目に戻る */
		if ( player[11] >= char_size[4] )
		{
			player[11] = 0;
			if ( player[2] == 21 )	/* 空中 */
			{
				player[11] = ( char_size[4] - 1 - 3 );		/* 5に戻す */
			}
			if ( player[2] == 11 )	/* 攻撃終了 */
			{
				player[2] = 0;
				if ( player[14] != 10 )	/* 空中 */
				{
					player[2] = 21;
				}
			}
			if ( player[2] == 31 )	/* ダメージ */
			{
				player[2] = 0;
				if ( player[14] != 10 )	/* 空中 */
				{
					player[2] = 21;
				}
			}
			if ( player[2] == 32 )	/* ダウンゲームオーバー */
			{
				player[2] = 32;
				player[11] = ( char_size[4] - 1 );		/* 最終パターンのまま */
			}
			if ( player[2] == 33 )	/* クリア */
			{
				player[2] = 33;
				player[11] = ( char_size[4] - 1 - 3 );		/* 5に戻す */
			}
		}
	}
	fram_set( );
	
	/* 画面相対座標での表示位置 */
	if ( player[3] == 1 )
	{
		if ( kamera < 0 )
		{
			kamera = 0;
		}
		kamera = kamera + 1;
		if ( kamera > 20 )
		{
			kamera = 20;
		}
		dp_x2 = dp_x2 + ( kamera / 6 );
		if ( dp_x2 > 200 )
		{
			dp_x2 = 200;
		}
	}
	else 
	{
		if ( kamera > 0 )
		{
			kamera = 0;
		}
		kamera = kamera - 1;
		if ( kamera < -20 )
		{
			kamera = -20;
		}
		dp_x2 = dp_x2 + ( kamera / 6 );
		if ( dp_x2 < 80 )
		{
			dp_x2 = 80;
		}
	}
	dp_x2 = 160;
/*	
	if ( player[0] < dp_x2 )
	{
		dp_x = player[0];
	}
	else if ( player[0] >= ( MapInfo[2] - ( 320 - dp_x2 ) ) )
	{
		dp_x = player[0] - ( MapInfo[2] - 320 );
	}
	else 
	{
		dp_x = dp_x2;
	}
*/	
	dp_x = dp_x2 - 16;
//	dp_x = 160 - 16;
/*
	if ( player[1] < 100 )
	{
		dp_y = player[1];
	}
	else if ( player[1] >= ( MapInfo[3] - 140 ) )
	{
		dp_y = player[1] - ( MapInfo[3] - 240 );
	}
	else 
	{
		dp_y = 100;
	}
*/	
	dp_y = 120 - 16;
//	dp_y = ( 120 - 16 );
	
	if ( player[2] == 0 )
	{
		player[4] = 0;
		player[5] = 0;
	}
	if ( player[18] > 0 )	/* 着地モーション表示 */
	{
		player[18]--;
	}
	if ( player[2] != 0 )
	{
		player[18] = 0;
	}
	else 
	{
	}

	
	if ( player[2] == 1 )		/* 歩き */
	{
		player[4] = 0;
		player[5] = 1;
	}
	if ( player[2] == 2 )		/* つかみ */
	{
		player[4] = 0;
		player[5] = 3;
	}
	if ( player[2] == 11 )
	{
		player[4] = 0;
		player[5] = 3;
	}
	if ( player[2] == 21 )
	{
		player[4] = 0;
		player[5] = 2;
		if ( player[14] < 0 )	/* 落ちてる */
		{
			player[5] = 7;
		}
	}
	if ( player[2] == 31 )	/* ダメージ */
	{
		player[4] = 0;
		player[5] = 5;

	}
	if ( player[2] == 32 )	/* ゲームオーバー */
	{
		player[4] = 0;
		player[5] = 5;

	}
	if ( player[2] == 33 )	/* クリア */
	{
		player[4] = 0;
		player[5] = 8;

	}
	
	if ( gameflag[128] == 0 )	//マップビューではない
	{
		if ( ( player[17] % 2 ) == 0 )
		{
			BltRect( 1, 
			         dp_x, 
			         240 - dp_y - char_size[1],
			         ( player[11] * char_size[0] ) + ( player[4] * ( char_size[0] * char_size[4] ) ), 
			         ( player[5] * ( char_size[1] * 2 ) ) + ( player[3] * char_size[1] ), 
			         char_size[0], 
			         char_size[1] );
		}
		if ( player[30] > 0 )
		{
			player[30]--;
			BltRect( 18, dp_x - 30, 240 - dp_y + 4, 0, 160, 100, 8 );	/* last one */
		}
		if ( player[24] > 0 )
		{
			player[24]--;
			BltRect( 18, dp_x - 30, 240 - dp_y + 4 + 10, 0, 184, 200, 16 );	/* secret item get */
		}
		
		
		switch ( player[19] )
		{
		case 1:
			BltRect( 5, 
			         dp_x - 32, 
			         240 - dp_y - char_size[1],
			         0, 
			         80, 
			         32, 
			         32 );
			break;
		case 2:
			BltRect( 5, 
			         dp_x + 32, 
			         240 - dp_y - char_size[1],
			         32, 
			         80, 
			         32, 
			         32 );
			break;
		default:
			break;
		}
	}
}
//-------------------------------------------------------------
//背景表示
void bg_disp()
{
	long x;
	long y;
	long b_x;
	long b_y;
	long i;

	x = 0;
	y = 0;
	b_x = 0;
	b_y = 0;
	i = 0;

	if ( gameflag[67] == 1 )
	{
		rayer[0] = rayer[0] + 1;
		if ( rayer[0] > 640 )
		{
			rayer[0] = rayer[0] - 640;
		}
		rayer[1] = rayer[1] + 2;
		if ( rayer[1] > 640 )
		{
			rayer[1] = rayer[1] - 640;
		}
		rayer[2] = rayer[2] + 4;
		if ( rayer[2] > 640 )
		{
			rayer[2] = rayer[2] - 640;
		}
	}
	
	//画面背景を画面全体に転送
	bak_cnt = bak_cnt + 1;
	if ( bak_cnt >= 40 )
	{
		bak_cnt = 0;
	}

/*
	if ( player[0] < dp_x2 )
	{
		d_x = 0;
	}
	else if ( player[0] >= ( MapInfo[2] - ( 320 - dp_x2 ) ) )
	{
		d_x = ( MapInfo[2] - 320 );
	}
	else 
	{
		d_x = player[0] - dp_x2 ;
	}
*/
	d_x = player[0] - dp_x2 + 16 ;
/*
	if ( player[1] < ( 100 ) )
	{
		d_y = ( MapInfo[3] - 240 );
	}
	else if ( player[1] >= ( MapInfo[3] - 140 ) )
	{
		d_y = 0 ;
	}
	else 
	{
		d_y = ( MapInfo[3] - 240 ) + 100 - player[1];
	}
*/	
	d_y = ( MapInfo[3] - 240 ) + ( 120 - 16 ) - player[1];
//	d_y = ( 360 - 16 ) - player[1];

	/* 背景アニメーションON */
	Blt( 112, 0, 0 );						/* 背景スクロール演出 */
//	Blt( 110, 0 - rayer[0] - d_x, 0 - d_y );				/* 背景スクロール演出 */
//	Blt( 110, 640 - rayer[0] - d_x, 0 - d_y );				/* 背景スクロール演出 */
//	Blt( 111, 0 - rayer[1] - d_x, 0 - d_y );				/* 背景スクロール演出 */
//	Blt( 111, 640 - rayer[1] - d_x, 0 - d_y );				/* 背景スクロール演出 */
//	Blt( 112, 0 - rayer[2] - d_x, 0 - d_y );				/* 背景スクロール演出 */
//	Blt( 112, 640 - rayer[2] - d_x, 0 - d_y );				/* 背景スクロール演出 */
}
void bakdisp1()
{
	long x;
	long y;
	long b_x;
	long b_y;
	long i;

	x = 0;
	y = 0;
	b_x = 0;
	b_y = 0;
	i = 0;
	
	/* stage13,14,17は多重スクロール */
	/* 地面表示 */
	for ( x = 0; x < MapInfo[1]; x++ )
	{
		for ( y = 0; y < MapInfo[1]; y++ )
		{

			if ( ( ( ( d_x - 32 ) <= ( x * 32 ) ) 
			  && ( ( d_y - 32 ) <= ( y * 32 ) )
			  && ( ( d_x + 320 + 32 ) >= ( x * 32 ) )
			  && ( ( d_y + 240 + 32 ) >= ( y * 32 ) ) )
			  || ( bak_alldrow == 1 )	 					/* 背景の描画をクリップするか */
			   )
			{
				b_y = map1[ x + ( y * MapInfo[0] ) ] / 100;
				b_x = map1[ x + ( y * MapInfo[0] ) ] % 100;
				if ( ( map1[ x + ( y * MapInfo[0] ) ] >= 100 ) && ( map1[ x + ( y * MapInfo[0] ) ] <= 219 ) )
				{
					BltRect( 10, ( x * 32 ) - d_x , ( y * 32 ) - d_y , 0 * 32 , 0 * 32 ,32, 32 );
				}
				else 
				{	
					if ( b_y == 1 )
					{
						BltRect( 10, ( x * 32 )  - d_x , ( y * 32 )  - d_y , b_x * 32 , ( 5 + map_rot_info ) * 32 ,32, 32 );
					}
					if ( b_y == 3 )
					{
						BltRect( 10, ( x * 32 )  - d_x , ( y * 32 )  - d_y , b_x * 32 , ( 9 + map_rot_info ) * 32 ,32, 32 );
					}
				}
			}
		}
	}

}
void bakdisp2( )
{
	long i;
	long x;
	long y;
	long b_x;
	long b_y;
	
	i = bak_cnt / 10;
	
	for ( x = 0; x < MapInfo[1]; x++ )
	{
		for ( y = 0; y < MapInfo[1]; y++ )
		{

			if ( ( ( ( d_x - 32 ) <= ( x * 32 ) ) 
			  && ( ( d_y - 32 ) <= ( y * 32 ) )
			  && ( ( d_x + 320 + 32 ) >= ( x * 32 ) )
			  && ( ( d_y + 240 + 32 ) >= ( y * 32 ) ) )
			  || ( bak_alldrow == 1 )	 					/* 背景の描画をクリップするか */
			   )
			{

				if ( ( map1[ x + ( y * MapInfo[0] ) ] >= 100 ) && ( map1[ x + ( y * MapInfo[0] ) ] <= 219 ) )
				{
					b_y = map1[ x + ( y * MapInfo[0] ) ] / 100;
					b_x = map1[ x + ( y * MapInfo[0] ) ] % 100;
					if ( b_y == 1 )
					{
						BltRect( 10, ( x * 32 )  - d_x , ( y * 32 )  - d_y , ( b_x + ( ( map_data[13] - 1) * 2 ) ) * 32 , ( 5 + map_rot_info ) * 32 ,32, 32 );
					}
					if ( b_y == 3 )
					{
						BltRect( 10, ( x * 32 )  - d_x , ( y * 32 )  - d_y , b_x * 32 , ( 9 + map_rot_info ) * 32 ,32, 32 );
					}
					
					b_y = map2[ x + ( y * MapInfo[0] ) ] / 100;
					b_x = map2[ x + ( y * MapInfo[0] ) ] % 100;
					if ( b_y == 1 )
					{
						BltRect( 11, ( x * 32 )  - d_x , ( y * 32 )  - d_y , b_x * 32 , ( 5 + map_rot_info ) * 32 ,32, 32 );
					}
					if ( b_y == 3 )
					{
						BltRect( 11, ( x * 32 )  - d_x , ( y * 32 )  - d_y , b_x * 32 , ( 9 + map_rot_info ) * 32 ,32, 32 );
					}
				}
				else  
				{
					b_y = map2[ x + ( y * MapInfo[0] ) ] / 100;
					b_x = map2[ x + ( y * MapInfo[0] ) ] % 100;
					if ( b_y == 1 )
					{
						BltRect( 11, ( x * 32 )  - d_x , ( y * 32 )  - d_y , b_x * 32 , ( 5 + map_rot_info ) * 32 ,32, 32 );
					}
					if ( b_y == 3 )
					{
						BltRect( 11, ( x * 32 )  - d_x , ( y * 32 )  - d_y , b_x * 32 , ( 9 + map_rot_info ) * 32 ,32, 32 );
					}
				}
			}
		}
	}
}

void bak_make( void )
{

	long bak_d_x;
	long bak_d_y;
	

	SwapToSecondary( 125 );

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 640;
	rect.h = 640;
	SDL_FillRect(g_screen, &rect, SDL_MapRGBA(g_screen->format,16,99,62,255));

	bak_d_x = d_x;
	bak_d_y = d_y;
	
	d_x = d_x - 160 ;
	d_y = d_y - 200;

	bak_alldrow = 1;						/* 背景の描画をクリップするか */

	bakdisp1( );
	bakdisp2( );
	item_disp( );
	item_line( );
	kane_disp( );
	enm_disp( );
	e_shot_disp( );
	BltRect( 1, 320 - 16, 288 + 16 , ( player[11] * 32 ) + ( player[4] * 320 ), ( player[5] * 64 ) + ( player[3] * 32 ), 32, 32 );
	p_jump_f_disp( );
	p_shot_disp( );
	p_mgc_disp( );
	p_shot_f2_disp( );
	p_shot_f_disp( );
	
	SwapToSecondary( 125 );

	bak_alldrow = 0;						/* 背景の描画をクリップするか */

	d_x = bak_d_x;
	d_y = bak_d_y;

//	SaveBmp( 125, "temp.bmp" );

}
void bak_rot( void )
{
	BltRectRotZoom( 125, 160, 120, 0, 0, 640, 640, player[20], 1, 0 );
}



/* ＷＡＩＴつきスクロール */
void wait_scl( long type, long d_num )
{
/*  
	0:上	1:下	2:左	3:右
	よみこむファイルＮＯ
*/
	long i;
	long x;
	long y;

	se_wav( 14 );
	screen_BackupPlane( );

	/* バッファクリア */
	for ( i = 0; i < 100; i++ )
	{
		p_ef[i * 5] = 0;						/* 存在 */
	}
	for ( i = 0; i < 40; i++ )
	{
		pmshot[i * 20 + 2] = 0;						/* 存在 */
	}
	for ( i = 0; i < 10; i++ )
	{
		pshot[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 40; i++ )
	{
		pshotf[i * 10 + 0] = 0 ;	
	}
	/* バッファクリア */
	for ( i = 0; i < 50; i++ )
	{
		item[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 20; i++ )
	{
		enemy[i * 20 + 0] = 0 ;					/* 存在してない */
	}
	for ( i = 0; i < 20; i++ )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* 存在してない */
	}
	for ( i = 0; i < 20; i++ )
	{
		kane[i * 10 + 0] = 0 ;					/* 存在してない */
	}

	/* 次画面バッファ読み込み */
/*
	for ( i = 0 ; i < 2 ; i++ )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	バックアッププレーンからのBlt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	バックアッププレーンの使用終了

	for ( j = 0 ; j < 2; j++ )
	{
		ClearSecondary();
		halt;
	}
*/	
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2(string);
	{
		for ( i = 0; i <= 319; i++ )
		{
			map1[i] = gameflag2[i];
		}
	}
	for ( i = 0 ; i <= 20 ; i++ )
	{
		map_data[i] = gameflag2[i + 320];
	}
	
	for ( i = 0 ; i < 5 ; i++ )
	{
		sprintf(string,"image/bak/%d.bmp", (int)map_data[11 + i] );
		
		if ( ( i == 0 ) || ( map_data[11 + i] != 0 ) )
		{
			LoadBitmap(string,110 + i , 0 );					//プレーンナンバー２にシステム用ＢＭＰを読み込む
		}
		else 
		{
			ReleaseBitmap(110 + i);
		}
	}
	
	
	
	/* レイヤー２ */
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", (int)stage , (int)2, (int)d_num );
	if ( LoadGameFlag2(string) == 0 )
	{
		for ( i = 0; i <= 319; i++ )
		{
			map2[i] = gameflag2[i];
		}
	}
//	bak_make();


	/* アイテム配置 */
	ResetGameFlag2( );
	sprintf(string,"data/%d/i%d_%d.map", (int)stage , (int)1, (int)d_num );
	if ( LoadGameFlag2(string) == 0 )
	{
		for ( x = 0; x <= 19 ; x++ )
		{
			for ( y = 0; y <= 16 ; y++ )
			{
				if ( gameflag2[x + ( y * 20 )] != 0 )
				{
					item_set( gameflag2[x + ( y * 20 )], x * 32, ( ( 14 - y ) * 32 ) + 16, x + ( y * 20 ), d_num );
				}
			}
		}
	}

	ResetGameFlag2();				/* ファイルなし */
	sprintf( string,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( string );	/* 敵配置 */
	/* 敵配置 */
	for ( x = 0; x <= 19 ; x++ )
	{
		for ( y = 0; y <= 16 ; y++ )
		{
			if ( gameflag2[x + ( y * 20 )] != 0 )
			{
				enm_set( gameflag2[x + ( y * 20 )], x * 32, ( ( 14 - y ) * 32 ) + 16 );
			}
		}
	}
	
	save_data[3] = d_num;
	
	/* 上スクロール */
	if ( type == 0 )
	{
		player[1] = 0;
	}
	/* 下スクロール */
	if ( type == 1 )
	{
		player[1] = ( 480 - 32 - 16 );
	}
	/* 横スクロール */
	if ( type == 3 )
	{
		player[0] = 0;
	}
	/* 横スクロール */
	if ( type == 2 )
	{
		player[0] = ( 640 - 32 );
	}


/*
	screen_BackupPlane( );

	for ( i = 2 ; i >= 0 ; i-- )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	バックアッププレーンからのBlt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	バックアッププレーンの使用終了
*/
	/* リトライ場所設定 */
	player[15] = player[0];
	player[16] = player[1];

	player[9] = 0;			/* 掴んでいる敵は消える */

}

/* ＷＡＩＴつきスクロール */
void wait_scl2( long d_num ,long init_x, long init_y )
{
/*  
	0:上	1:下	2:左	3:右
	よみこむファイルＮＯ
*/
	long i;
	long x;
	long y;

//	se_wav( 14 );
//	screen_BackupPlane( );

	/* バッファクリア */
	for ( i = 0; i < 100; i++ )
	{
		p_ef[i * 5] = 0;						/* 存在 */
	}
	for ( i = 0; i < 40; i++ )
	{
		pmshot[i * 20 + 2] = 0;						/* 存在 */
	}
	for ( i = 0; i < 10; i++ )
	{
		pshot[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 40; i++ )
	{
		pshotf[i * 10 + 0] = 0 ;	
	}
	/* バッファクリア */
	for ( i = 0; i < 50; i++ )
	{
		item[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 20; i++ )
	{
		enemy[i * 20 + 0] = 0 ;					/* 存在してない */
	}
	for ( i = 0; i < 20; i++ )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* 存在してない */
	}
	for ( i = 0; i < 20; i++ )
	{
		kane[i * 10 + 0] = 0 ;					/* 存在してない */
	}

	/* 次画面バッファ読み込み */
/*
	for ( i = 0 ; i < 2 ; i++ )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	バックアッププレーンからのBlt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	バックアッププレーンの使用終了

	for ( j = 0 ; j < 2; j++ )
	{
		ClearSecondary();
		halt;
	}
*/	
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2(string);
	{
		for ( i = 0; i <= 319; i++ )
		{
			map1[i] = gameflag2[i];
		}
	}
	for ( i = 0 ; i <= 20 ; i++ )
	{
		map_data[i] = gameflag2[i + 320];
	}
	
	for ( i = 0 ; i < 5 ; i++ )
	{
		sprintf(string,"image/bak/%d.bmp", (int)map_data[11 + i] );
		
		if ( ( i == 0 ) || ( map_data[11 + i] != 0 ) )
		{
			LoadBitmap(string,110 + i , 0 );					//プレーンナンバー２にシステム用ＢＭＰを読み込む
		}
		else 
		{
			ReleaseBitmap(110 + i);
		}
	}
	
	
	
	/* レイヤー２ */
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", (int)stage , (int)2, (int)d_num );
	if ( LoadGameFlag2(string) == 0 )
	{
		for ( i = 0; i <= 319; i++ )
		{
			map2[i] = gameflag2[i];
		}
	}
//	bak_make();


	/* アイテム配置 */
	ResetGameFlag2( );
	sprintf(string,"data/%d/i%d_%d.map", (int)stage , (int)1, (int)d_num );
	if ( LoadGameFlag2(string) == 0 )
	{
		for ( x = 0; x <= 19 ; x++ )
		{
			for ( y = 0; y <= 16 ; y++ )
			{
				if ( gameflag2[x + ( y * 20 )] != 0 )
				{
					item_set( gameflag2[x + ( y * 20 )], x * 32, ( ( 14 - y ) * 32 ) + 16, x + ( y * 20 ), d_num );
				}
			}
		}
	}

	ResetGameFlag2();				/* ファイルなし */
	sprintf( string,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( string );	/* 敵配置 */
	/* 敵配置 */
	for ( x = 0; x <= 19 ; x++ )
	{
		for ( y = 0; y <= 16 ; y++ )
		{
			if ( gameflag2[x + ( y * 20 )] != 0 )
			{
				enm_set( gameflag2[x + ( y * 20 )], x * 32, ( ( 14 - y ) * 32 ) + 16 );
			}
		}
	}
	
	save_data[3] = d_num;
	
	player[0] = init_x;
	player[1] = init_y;
/*	
	screen_BackupPlane( );

	for ( i = 2 ; i >= 0 ; i-- )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	バックアッププレーンからのBlt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
//	DisableBackupPlane();	//	バックアッププレーンの使用終了
//	screen_BackupPlane( );
*/
	/* リトライ場所設定 */
	player[15] = player[0];
	player[16] = player[1];


}

/* ＷＡＩＴつきスクロール(reload専用、敵の再配置を行わない) */
void wait_scl3( )
{
/*  
	0:上	1:下	2:左	3:右
	よみこむファイルＮＯ
*/
	long i;
	long x;
	long y;
	long d_num;
	
	d_num = save_data[3];

//	se_wav( 14 );
//	screen_BackupPlane( );

	/* バッファクリア */
	for ( i = 0; i < 100; i++ )
	{
		p_ef[i * 10] = 0;						/* 存在 */
	}
	for ( i = 0; i < 40; i++ )
	{
		pmshot[i * 20 + 2] = 0;						/* 存在 */
	}
	for ( i = 0; i < 10; i++ )
	{
		pshot[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 40; i++ )
	{
		pshotf[i * 10 + 0] = 0 ;	
	}
	/* バッファクリア */
	for ( i = 0; i < 50; i++ )
	{
		item[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 20; i++ )
	{
		if ( enemy[0 + ( i * 20 )] == 1 )					/* 存在してない */
		{
			enemy[1 + ( i * 20 )] = enemy[14 + ( i * 20 )] ;					/* 存在してない */
			enemy[2 + ( i * 20 )] = enemy[15 + ( i * 20 )] ;					/* 存在してない */
		}
	}
	for ( i = 0; i < 20; i++ )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* 存在してない */
	}

	/* 次画面バッファ読み込み */
/*
	for ( i = 0 ; i < 2 ; i++ )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	バックアッププレーンからのBlt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	バックアッププレーンの使用終了

	for ( j = 0 ; j < 2; j++ )
	{
		ClearSecondary();
		halt;
	}
*/	
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2(string);
	{
		for ( i = 0; i <= 319; i++ )
		{
			map1[i] = gameflag2[i];
		}
	}
	for ( i = 0 ; i <= 20 ; i++ )
	{
		map_data[i] = gameflag2[i + 320];
	}
	
	for ( i = 0 ; i < 5 ; i++ )
	{
		sprintf(string,"image/bak/%d.bmp", (int)map_data[11 + i] );
		
		if ( ( i == 0 ) || ( map_data[11 + i] != 0 ) )
		{
			LoadBitmap(string,110 + i , 0 );					//プレーンナンバー２にシステム用ＢＭＰを読み込む
		}
		else 
		{
			ReleaseBitmap(110 + i);
		}
	}
	
	
	
	/* レイヤー２ */
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", (int)stage , (int)2, (int)d_num );
	if ( LoadGameFlag2(string) == 0 )
	{
		for ( i = 0; i <= 319; i++ )
		{
			map2[i] = gameflag2[i];
		}
	}
//	bak_make();


	/* アイテム配置 */
	ResetGameFlag2( );
	sprintf(string,"data/%d/i%d_%d.map", (int)stage , (int)1, (int)d_num );
	if ( LoadGameFlag2(string) == 0 )
	{
		for ( x = 0; x <= 19 ; x++ )
		{
			for ( y = 0; y <= 16 ; y++ )
			{
				if ( gameflag2[x + ( y * 20 )] != 0 )
				{
					item_set( gameflag2[x + ( y * 20 )], x * 32, ( ( 14 - y ) * 32 ) + 16, x + ( y * 20 ), d_num );
				}
			}
		}
	}

	ResetGameFlag2();				/* ファイルなし */
	sprintf( string,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( string );	/* 敵配置 */
	/* 敵配置 */
	for ( x = 0; x <= 19 ; x++ )
	{
		for ( y = 0; y <= 16 ; y++ )
		{
			if ( gameflag2[x + ( y * 20 )] != 0 )
			{
//				enm_set( gameflag2[x + ( y * 20 )], x * 32, ( ( 14 - y ) * 32 ) + 16 );
			}
		}
	}
	
//	save_data[7] = d_num;
	
/*
	player[0] = init_x;
	player[1] = init_y;
*/	
/*
	screen_BackupPlane( );

	for ( i = 2 ; i >= 0 ; i-- )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	バックアッププレーンからのBlt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
*/
//	DisableBackupPlane();	//	バックアッププレーンの使用終了
//	screen_BackupPlane( );

	/* リトライ場所設定 */
	player[15] = player[0];
	player[16] = player[1];


}

void rotmap( long rot )
{
	long i;
	long size;
	long x;
	long y;
	long wx;
	long wy;
	long k;
	long by;
	long bx;
/*
	long bak_d_x;
	long bak_d_y;
	bak_d_x = d_x;
	bak_d_y = d_y;
	
	d_x = 0 ;
	d_y = 0;
*/
	k = 0;
	wx = 0;
	wy = 0;
	by = 0;
	bx = 0;
	
	x = 0;
	y = 0;
/*
	switch( rot )
	{
	case 0:		// 移動無し
	case 360:		// 移動無し
		break;
	case 90:
		memcpy( mapfile, map1, sizeof( map1 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				map1[ ( y ) + ( ( MapInfo[1] - x - 1 ) * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}
		memcpy( mapfile, map2, sizeof( map2 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				map2[ ( y ) + ( ( MapInfo[1] - x - 1 ) * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}
		break;
	case 180:
		memcpy( mapfile, map1, sizeof( map1 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				map1[ ( MapInfo[1] - x - 1 ) + ( ( MapInfo[1] - y - 1) * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}
		memcpy( mapfile, map2, sizeof( map2 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				map2[ ( MapInfo[1] - x - 1 ) + ( ( MapInfo[1] - y - 1) * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}
		break;
	case 270:
		memcpy( mapfile, map1, sizeof( map1 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				map1[ ( ( MapInfo[1] - y - 1 ) ) + ( ( x ) * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}
		memcpy( mapfile, map2, sizeof( map2 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				map2[ ( ( MapInfo[1] - y - 1 ) ) + ( ( x ) * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}
		break;
	}
*/
	switch( rot )
	{
	case 0:			// 移動無し
	case 360:		// 移動無し
		break;
	default:
//		memset( mapfile, map2, sizeof( map2 ) );
		memcpy( mapfile, map1, sizeof( map1 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				rotchangemap( x, y, rot , &wx, &wy );
				map1[ wx + ( wy * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}

		memcpy( mapfile, map2, sizeof( map2 ) );
		for ( x = 0; x < MapInfo[1]; x++ )
		{
			for ( y = 0; y < MapInfo[1]; y++ )
			{
				rotchangemap( x, y, rot , &wx, &wy );
				map2[ wx + ( wy * MapInfo[0] ) ] = mapfile[ ( x ) + ( y * MapInfo[0] ) ];
			}
		}
	
		break;
	}

/*	
	SwapToSecondary( 124 );
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 2400;
	rect.h = 2400;
	SDL_FillRect(g_screen, &rect, SDL_MapRGBA(g_screen->format,16,99,62,255));
	
	bakdisp1( );
	bakdisp2( );
	SwapToSecondary( 124 );
	SaveBmp( 124, "temp.bmp" );
	d_x = bak_d_x;
	d_y = bak_d_y;
*/
	wx = 0;
	wy = 0;
	// プレイヤーの座標を変換
	rotchange( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ), rot, &wx, &wy );

	player[0] = wx - ( char_size[0] / 2 ) - 1;	//壁に埋まってしまうため補正
	player[1] = wy - ( char_size[1] / 2 );

	
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			rotchange( item[( i * item_data[2] ) + 1 ] + ( item_data[0] / 2 ), item[( i * item_data[2] ) + 2 ] + ( item_data[0] / 2 ), rot, &wx, &wy );
			item[( i * item_data[2] ) + 1 ] = wx - ( item_data[0] / 2 );
			item[( i * item_data[2] ) + 2 ] = wy - ( item_data[0] / 2 );
			
		}
	}
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			by = item[( i * item_data[2] ) + 3 ] / 100;
			bx = item[( i * item_data[2] ) + 3 ] % 100;
			switch ( by )
			{
			case 2:	// 上方向
			case 3:
			case 4:
				if ( item[7 + ( i * item_data[2] )] >= 0 )
				{
					k = item[7 + ( i * item_data[2] )];	// 支点の取得
					item[6 + ( i * item_data[2] )] = 12;
					item[8 + ( i * item_data[2] )] = ( ( item[( k * item_data[2] ) + 1 ] + item[4 + ( i * item_data[2] )] ) - item[( i * item_data[2] ) + 1 ] ) / 10;
					item[9 + ( i * item_data[2] )] = ( ( item[( k * item_data[2] ) + 2 ] + item[5 + ( i * item_data[2] )] ) - item[( i * item_data[2] ) + 2 ] ) / 10;
				}
				break;
			case 10:
				switch( bx )
				{
				case 3:
				case 4:
				case 5:
				case 6:
					if ( rot == 270 )
					{
						item[( i * item_data[2] ) + 3 ] = item[( i * item_data[2] ) + 3 ] + 1;
					}
					else 
					{
						item[( i * item_data[2] ) + 3 ] = item[( i * item_data[2] ) + 3 ] - 1;
					}
					if ( item[( i * item_data[2] ) + 3 ] > 1006 )
					{
						item[( i * item_data[2] ) + 3 ] = item[( i * item_data[2] ) + 3 ] - 4;
					}
					if ( item[( i * item_data[2] ) + 3 ] < 1003 )
					{
						item[( i * item_data[2] ) + 3 ] = item[( i * item_data[2] ) + 3 ] + 4;
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	for ( i = 0; i < enm_data[1]; i++ )
	{
		if ( enemy[0 +( i * enm_data[2] )] == 1 )
		{
			size = 32;
			/* 敵のサイズ取得 */
			if ( enemy[3 + ( i * enm_data[2] )] == 1 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 2 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 3 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 4 )	/* 4ボス */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 5 )	/* 5ボス */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 6 )	/* 6ボス */
			{
				size = 32;
			}
			rotchange( enemy[( i * enm_data[2] ) + 1 ] + ( size / 2 ), enemy[( i * enm_data[2] ) + 2 ] + ( size / 2 ), rot, &wx, &wy );
			enemy[( i * enm_data[2] ) + 1 ] = wx - ( size / 2 );
			enemy[( i * enm_data[2] ) + 2 ] = wy - ( size / 2 );
		}
	}
	//パーティクルの移動
	for ( i = 0; i < 80; i++ )
	{
		if ( pshotf2[i * 10 + 2] != 0 )
		{
			rotchange( ( pshotf2[i * 10 + 5] >> 16 ) + 16, ( pshotf2[i * 10 + 6] >> 16 ) + 16, rot, &wx, &wy );
			pshotf2[i * 10 + 5] = ( wx ) << 16 ;	/* 初期位置の設定 */
			pshotf2[i * 10 + 6] = ( wy ) << 16 ;
		}
	}
	
#ifdef GP2X
	replay_time = replay_time + 15;
#endif 

}

void rotchangemap( long x1, long y1, long deg, long *x2, long *y2 )
{
	long rad; // 回転角度(ラジアン)

	rad = 360 - deg;

	long cx = MapInfo[1] / 2; // マップの中心座標(X)
	long cy = MapInfo[1] / 2; // マップの中心座標(Y)

	long dx = x1 - cx; // 中心からの距離(X)
	long dy = y1 - cy; // 中心からの距離(Y)

	long tmpX = dx*funcCos(rad) - dy*funcSin(rad); // 回転
	long tmpY = dx*funcSin(rad) + dy*funcCos(rad); 
	
	tmpX = tmpX + ( 1 << 15 );
	tmpY = tmpY + ( 1 << 15 );

	*x2 = ( cx + ( tmpX >> 16 ) ); // 元の座標にオフセットする
	*y2 = ( cy + ( tmpY >> 16 ) );

}

void rotchange( long x1, long y1, long deg, long *x2, long *y2 )
{
	long rad; // 回転角度(ラジアン)

	rad = deg;

	long cx = MapInfo[3] / 2; // マップの中心座標(X)
	long cy = MapInfo[3] / 2; // マップの中心座標(Y)

	long dx = x1 - cx; // 中心からの距離(X)
	long dy = y1 - cy; // 中心からの距離(Y)

	long tmpX = dx*funcCos(rad) - dy*funcSin(rad); // 回転
	long tmpY = dx*funcSin(rad) + dy*funcCos(rad); 
	
	tmpX = tmpX + ( 1 << 15 );
	tmpY = tmpY + ( 1 << 15 );

	*x2 = ( cx + ( tmpX >> 16 ) ); // 元の座標にオフセットする
	*y2 = ( cy + ( tmpY >> 16 ) );

}

//-----------------------------------------------------------------------------------
// おやつカウンター表示
void snack_counter_disp()
{
	long px;
	long py;
	long x;
	long dx;
	long dy;
	long i;
	long old_count;
	// おやつカウント
	
	old_count = snack_count;
	snack_count = 0;

	for(i = 0; i < enm_data[1]; i++)
	{
		if ( ( enemy[0 +( i * enm_data[2] )] == 1 ) && ( enemy[3 +( i * enm_data[2] )] != 4 ) )
		{
			snack_count++;
		}
	}
	
	if ( ( old_count != snack_count ) && ( snack_count == 1 ) )
	{
		//last oneの表示
		player[30] = 180;
	}
	if ( ( old_count != snack_count ) && ( snack_count == 0 ) )
	{
		//last oneの表示
		player[30] = 0;
	}
	// 左上
	px = 10;
	py = 18;
	// 文字サイズ
	dx = 10;
	dy = 8;
	// 'rest' 残りおやつ
	x = 0;
	BltRect( 18, 105, 2, 0, 72, 100, 8 );	/* replay */
	// 残りの数
//	x = x + dx * 2;
//	px = px + rand(3)-1; // ぶるぶる
//	py = py + rand(3)-1; // ぶるぶる
//	BltNumericImage2( count, 2, 140 + rand(3)-1, 2 + rand(3)-1, 18, 0, 0, 10, 8 );
	BltNumericImage2( snack_count, 2, 155, 2, 18, 0, 0, 10, 8 );
}

//-----------------------------------------------------------------------------------
//ミニマップの表示
void minimap_disp( void )
{
	long px;
	long py;
	long size;
	long width;
	long height;
	long i;
	long x;
	long y;
	// 左上
	px   = 2;
	py   = 12;
	size = 1;
	width  = size*MapInfo[1];
	height = size*MapInfo[1];

	if ( gameflag[132] == 0 )
	{
		return;
	}
	
	
	// 20 x 15
//	BlendExBltFastW( 70, px, py, 0, 100 );
	Blt( 70, px, py );
	// プレイヤー
	x = px + 0      + ((player[0] / 32 + 0) * size);
	y = py + height - ((player[1] / 32 + 1) * size);
	BltRect( 127, x, y, 127, 191, size, size );
	// おやつ
	for( i = 0; i < enm_data[1]; i++)
	{
		if ( enemy[0 +( i * enm_data[2] )] == 1 )
		{
			x = px + 0      + ((enemy[1 +( i * enm_data[2])] / 32 + 0) * size);
			y = py + height - ((enemy[2 +( i * enm_data[2])] / 32 + 1) * size);
			BltRect( 127, x, y, 127, 127, size, size );
		}

	}
}

//-----------------------------------------------------------------------------------
//情報表示
void mapdisp()
{
	int stage_hosei;
	
	stage_hosei = 0;
	if ( stage == 2 )
	{
		stage_hosei = 50;
	}

	long wk;
	/* プレイヤー状態表示 */
//	Blt( 20, 0, 0 );	/* 枠 */
	if ( gameflag[128] != 0 )	//マップビュー
	{
		BltRect( 18, 10, 15, 0, 136, 100, 8 * 3 );	/* mapviwe */
	}
	if ( gameflag[132] == 1 )
	{
		if ( stage != 0 )
		{
			BltRect( 18, 10, 15, 0, 32, 100, 8 );	/* replay */
		}
		/* キー入力 */
		if ( replay_load_key[0] == 1 )  /* l */
		{
			if ( replay_load_key[2] == 1 )  /* up */
			{
				BltRect( 67, 10, 150, 256, 0, 64, 64 );	/* l */
			}
			else if ( replay_load_key[3] == 1 )  /* down */
			{
				BltRect( 67, 10, 150, 192, 64, 64, 64 );	/* l */
			}
			else 
			{
				BltRect( 67, 10, 150, 128, 64, 64, 64 );	/* l */
			}
		}
		else if ( replay_load_key[1] == 1 )  /* r */
		{
			if ( replay_load_key[2] == 1 )  /* up */
			{
				BltRect( 67, 10, 150, 192, 0, 64, 64 );	/* r */
			}
			else if ( replay_load_key[3] == 1 )  /* down */
			{
				BltRect( 67, 10, 150, 256, 64, 64, 64 );	/* r */
			}
			else 
			{
				BltRect( 67, 10, 150, 64, 64, 64, 64 );	/* r */
			}
		}
		else 
		{
			if ( replay_load_key[2] == 1 )  /* up */
			{
				BltRect( 67, 10, 150, 64, 0, 64, 64 );	/* r */
			}
			else if ( replay_load_key[3] == 1 )  /* down */
			{
				BltRect( 67, 10, 150, 128, 0, 64, 64 );	/* r */
			}
			else 
			{
				BltRect( 67, 10, 150, 0, 0, 64, 64 );	/* r */
			}
		}
		if ( replay_load_key[4] == 1 )  /* 1 */
		{
			BltRect( 67, 90, 190, 32, 128, 32, 32 );	/* off */
		}
		else 
		{
			BltRect( 67, 90, 190, 0, 128, 32, 32 );	/* on */
		}
		if ( replay_load_key[5] == 1 )  /* 2 */
		{
			BltRect( 67, 130, 190, 32, 128, 32, 32 );	/* off */
		}
		else 
		{
			BltRect( 67, 130, 190, 0, 128, 32, 32 );	/* on */
		}
	}

	if ( stage != 0 )
	{	
		if ( gameflag[127] == 1 )	//トータルアタック
		{
			BltRect( 18, 5, 220, 0, 128, 100, 8 );	/* rank */
		}
		else if ( stage == 2 )
		{
			BltRect( 18, 5, 220, 0, 112, 100, 8 );	/* rank */
		}
		else 
		{
			if ( ( save_data[3] >= 1 ) && ( save_data[3] <= 10 ) )
			{
				BltRect( 18, 5, 220, 0, 88, 100, 8 );	/* rank */
			}
			if ( ( save_data[3] >= 11 ) && ( save_data[3] <= 30 ) )
			{
				BltRect( 18, 5, 220, 0, 96, 100, 8 );	/* rank */
			}
			if ( ( save_data[3] >= 31 ) && ( save_data[3] <= 50 ) )
			{
				BltRect( 18, 5, 220, 0, 104, 100, 8 );	/* rank */
			}
		}

		BltRect( 18, 10, 2, 0, 40, 100, 8 );	/*  */
		BltNumericImage2( save_data[3], 2, 70, 2, 18, 0, 0, 10, 8 );	/* d_num */

		if ( gameflag[127] == 1 )	//トータルアタック
		{
			BltRect( 18, 180, 2, 0, 120, 100, 8 );	/*  */
			BltNumericImage2( gameflag[136], 3, 250, 2, 18, 0, 0, 10, 8 );	/* miss count */
		}
		else 
		{
			BltRect( 18, 190, 2, 0, 80, 100, 8 );	/*  */
			BltNumericImage2( Jump_counts, 2, 280, 2, 18, 0, 0, 10, 8 );	/* Jump_counts */
		}
		
		BltRect( 18, 50, 230, 0, 8, 100, 8 );	/*  */
		BltRect( 18, 5, 230, 0, 16, 100, 8 );	/*  */
		
		BltRect( 18, 200, 230 , 0, 8, 100, 8 );	/*  */
		BltRect( 18, 155, 230 , 0, 24, 100, 8 );	/*  */

		BltNumericImage( play_time[0], 2, 110, 230, 18, 0, 0, 10, 8 );	/* 時間 */
		BltNumericImage( play_time[1], 2, 80, 230, 18, 0, 0, 10, 8 );	/* 時間 */
		BltNumericImage( play_time[2], 2, 50, 230, 18, 0, 0, 10, 8 );	/* 時間 */

		if ( gameflag[127] == 1 )	//トータルアタック
		{
	//		sprintf( string,"%d", gameflag[200 + save_data[3]] );
	//		MidStr(string,6,2,string[1]);
			wk = get2keta( gameflag[137] , 1 );
			BltNumericImage( wk, 2, 260, 230, 18, 0, 0, 10, 8 );	
	//		sprintf( string,"%d", gameflag[200 + save_data[3]] );
	//		MidStr(string,4,2,string[1]);
			wk = get2keta( gameflag[137] , 100 );
			BltNumericImage( wk, 2, 230, 230, 18, 0, 0, 10, 8 );	
	//		sprintf( string,"%d", gameflag[200 + save_data[3]] );
	//		MidStr(string,2,2,string[1]);
			wk = get2keta( gameflag[137] , 10000 );
			BltNumericImage( wk, 2, 200, 230, 18, 0, 0, 10, 8 );	
		}
		else 
		{
			wk = get2keta( gameflag[200 + save_data[3] + stage_hosei] , 1 );
			BltNumericImage( wk, 2, 260, 230, 18, 0, 0, 10, 8 );	
			wk = get2keta( gameflag[200 + save_data[3] + stage_hosei] , 100 );
			BltNumericImage( wk, 2, 230, 230, 18, 0, 0, 10, 8 );	
			wk = get2keta( gameflag[200 + save_data[3] + stage_hosei] , 10000 );
			BltNumericImage( wk, 2, 200, 230, 18, 0, 0, 10, 8 );	
		}
	}
	else 
	{
		BltRect( 18, 190, 2, 0, 80, 100, 8 );	/*  */
		BltNumericImage2( Jump_counts, 2, 280, 2, 18, 0, 0, 10, 8 );	/* Jump_counts */
	}

	// 方向の表示
	BltRect( 75, 280, 122, 0 + ( map_rot_info * 32 ), 0, 32, 32 );	/*  */

	//完成品の表示
	BltRect( 6, 240, 240 - 96, 0, 64 , 96, 96 );	/*  */
	if ( ( sn == 1 ) || ( sn == 5 ) || ( sn == 4 ) )
	{
		if ( snack_count != all_snack_count )
		{
			BltRect( 6, 240 + 32, 240 - 96 + 32, 0 + ( ( ( save_data[3] - 1 ) % 10 ) * 32 ), 160 + ( ( ( save_data[3] - 1 ) / 10 ) * 32 ) , 32 - ( ( snack_count * 100 ) / ( ( all_snack_count * 100 ) / 32 ) ), 32 );	/*  */
		}
	}

	//カットインの表示
	if ( player[31] > 0 )
	{
		wk = player[31];
		if ( wk < 60 )
		{
			wk = 0;
		}
		else 
		{
			wk = wk - 60;
		}
		BltRect( 6, ( 320 - 64 ) + ( wk * wk ), 240 - 64 - 20, 0 + ( player[32] * 64 ), 0 , 64, 64 );	/*  */
		player[31]--;
	}

//	BltRect( 22, 24, 10, 0, 0, 16 * save_data[6], 12 );			/* 最大ＨＰ */
//	BltRect( 23, 24, 10, 0, life_a[1] * 12 , 16 * player[8], 12 );	/* 現在ＨＰ */
//	/* hpアニメーション */
//	life_a[0]++;
//	if ( life_a[0] >= 10 )
//	{
//		life_a[0] = 0;
//		life_a[1]++;
//		if ( life_a[1] >= 4 )
//		{
//			life_a[1] = 0;
//		}
//	}
	 

}


//-----------------------------------------------------------------------------------
/* bgm再生 */
/* ステージの開始に呼ぶ */
void bgm_midi( long BgmWavNo )
{

	
}


//-----------------------------------------------------------------------------------
/* se再生 */
void se_wav(long SeWavNo)
{
	
}



//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//開始
void stage_start( )
{
	int x = 0;
	int y = 0;
	int rec = 0;
	int rec2 = 0;
/*
	long i;
	long j;
	screen_BackupPlane( );

	for ( i = 2 ; i >= 0 ; i-- )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	バックアッププレーンからのBlt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	バックアッププレーンの使用終了
*/

	KeyInput( );	// キー入力
	demo[0]++;
	
	rec = 32 - ( demo[0] * 2 );
	if ( rec < 0 )
	{
		rec = 0;
	}
	rec2 = demo[0];
	if ( rec2 > 16 )
	{
		rec2 = 16;
	}
	
	for ( x = 0; x < 10; x++ )
	{
		for ( y = 0; y < 8; y++ )
		{
			BltRect( 72, ( x * 32 ) + rec2, ( y * 32 ) + rec2, 0, 0, rec, rec );
		}
	}
	// stage start
	BltRect( 71, 90, 80, 0, 0, 200, 32 );
	if ( demo[0] >= 120 )
	{
		// go
		BltRect( 71, 150, 140, 0, 64, 200, 32 );
	}
	else if ( demo[0] >= 60 )
	{
		// ready
		BltRect( 71, 130, 140, 0, 32, 200, 32 );
	}
	
	if (
	     ( demo[0] >= 180 ) 
	  || ( ( g_DebugStageProduction != 0 ) && ( demo[0] >= 2 ) )
	  || ( ( gameflag[134] != 0 ) && ( demo[0] >= 2 ) )
	   )
	{
		demo[0] = 0;
		sn = 1;
	}

}

void stage_endj( )
{
	
	if ( player[8] <= 0 )		/* ライフ０ */
	{

		player[2] = 32;	/* ダウンモーション */
		player[10] = 0;	/* ダウンモーション */
		player[11] = 0;	/* ダウンモーション */
		
		
//		ReleaseMIDI();
//		gameflag[40] = 6;
		sn = 3;
		demo[0] = 0;
	}
}

void stage_claer( )
{
	int stage_hosei;
	int rec = 0;
	int rec2 = 0;
	int x = 0;
	int y = 0;
	int newrecode = 0;
	int fead = 0;
	int wk = 0;
	
	stage_hosei = 0;
	if ( stage == 2 )
	{
		stage_hosei = 50;
	}
	
	
	if ( demo[0] == 0 )
	{
		demo[1] = 62;
//		demo[2] = 126;
		demo[2] = 148;
	}
	demo[0]++;
	
	
	play_time[4] = 1000000 + ( play_time[2] * 10000 ) + ( play_time[1] * 100 ) + ( play_time[0] );

	fead = demo[0] - 140;
	if ( fead < 0 )
	{
		fead = 0;
	}
	rec = ( fead * 2 );
	if ( rec > 32 )
	{
		rec = 32;
	}
	rec2 = 16 - fead;
	if ( rec2 < 0 )
	{
		rec2 = 0;
	}
	
	for ( x = 0; x < 10; x++ )
	{
		for ( y = 0; y < 8; y++ )
		{
			BltRect( 72, ( x * 32 ) + rec2, ( y * 32 ) + rec2, 0, 0, rec, rec );
		}
	}
	
	if ( gameflag[127] == 0 )	//トータルアタック
	{
		if ( ( gameflag[300 + save_data[3] + stage_hosei] > Jump_counts ) )
		{
			if ( gameflag[132] == 0 )
			{
				// 新記録
				Blt( 69, 0, 0 );
				newrecode = 1;
			}
		}
		if ( ( gameflag[200 + save_data[3] + stage_hosei] > play_time[4] ) )
		{
			if ( gameflag[132] == 0 )
			{
				// 新記録
				Blt( 68, 0, 0 );
				newrecode = 1;
			}
		}
	}
	if ( newrecode == 0 )
	{
		// stage clear
		Blt( 73, 0, 0 );
		BltRect( 71, 90, 180, 0, 96, 200, 32 );
		if ( demo[0] == 1 )
		{
			soundSetVolumeMasterBgm( 10 );
			soundPlaySe( EN_SE_CL21 + ( ( save_data[3] - 1 ) / 10 ) );
		}
	}
	else 
	{
		if ( demo[0] == 1 )
		{
			soundSetVolumeMasterBgm( 10 );
			soundPlaySe( EN_SE_CL1 + ( ( save_data[3] - 1 ) / 10 ) );
		}
	}
	
	if ( stage != 0 )
	{
		Blt( 74, 0, 0 );
		//目標タイム
		if ( target_save[200 + save_data[3] + stage_hosei] >= play_time[4] )
		{
			BltRect( 61, 20, 138, 0, 128 , 20, 20 );
		}
		//目標回転
		if ( target_save[300 + save_data[3] + stage_hosei] >= Jump_counts )
		{
			BltRect( 61, 20, 154, 0, 128 , 20, 20 );
		}
		// best
		wk = get2keta( target_save[200 + save_data[3] + stage_hosei], 1 );
		BltNumericImage( wk, 2, 250, 146, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( target_save[200 + save_data[3] + stage_hosei], 100 );
		BltNumericImage( wk, 2, 220, 146, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( target_save[200 + save_data[3] + stage_hosei], 10000 );
		BltNumericImage( wk, 2, 190, 146, 18, 0, 0, 10, 8 );	/*  */
		BltNumericImage2( target_save[300 + save_data[3] + stage_hosei], 2, 190, 162, 18, 0, 0, 10, 8 );	/* Jump_counts */
		// now
		wk = get2keta( play_time[4], 1 );
		BltNumericImage( wk, 2, 250, 138, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( play_time[4], 100 );
		BltNumericImage( wk, 2, 220, 138, 18, 0, 0, 10, 8 );	/*  */
		wk = get2keta( play_time[4], 10000 );
		BltNumericImage( wk, 2, 190, 138, 18, 0, 0, 10, 8 );	/*  */
		BltNumericImage2( Jump_counts, 2, 190, 154, 18, 0, 0, 10, 8 );	/* Jump_counts */
		if ( secretitemget == 1 )
		{
			BltRect( 18, 190, 170, 0, 176, 200, 8 );	/* タイム */
			BltRect( 61, 20, 170, 0, 128 , 20, 20 );
		}
		else 
		{
			BltRect( 18, 190, 170, 0, 168, 200, 8 );	/* タイム */
		}
		
		BltRect( 18, 200, 230 , 0, 8, 100, 8 );	/*  */
		BltRect( 18, 155, 230 , 0, 24, 100, 8 );	/*  */

		wk = get2keta( gameflag[200 + save_data[3] + stage_hosei] , 1 );
		BltNumericImage( wk, 2, 260, 230, 18, 0, 0, 10, 8 );	
		wk = get2keta( gameflag[200 + save_data[3] + stage_hosei] , 100 );
		BltNumericImage( wk, 2, 230, 230, 18, 0, 0, 10, 8 );	
		wk = get2keta( gameflag[200 + save_data[3] + stage_hosei] , 10000 );
		BltNumericImage( wk, 2, 200, 230, 18, 0, 0, 10, 8 );	
		
		
		
	}
	//完成品の取得1
	if ( demo[2] > 0 )
	{
		demo[2] = demo[2] - 1;
		if ( demo[2] <= 0 )
		{
//			soundPlaySe( EN_SE_CL1 );
		}
		demo[1] = demo[1] + 3;
		if ( demo[1] > 360 )
		{
			demo[1] = demo[1] - 360;
		} 
		x = 160 + ( ( funcSin( demo[1] ) * ( demo[2] ) ) >> 16 );
		y = 120 + ( ( funcCos( demo[1] ) * ( demo[2] ) ) >> 16 );
		BltRect( 6, x - 16, y - 16, 0 + ( ( ( save_data[3] - 1 ) % 10 ) * 32 ), 160 + ( ( ( save_data[3] - 1 ) / 10 ) * 32 ), 32, 32 );	/*  */
		p_shot_f2_set( x, y , 2 + ( rand( ) % 3 ) );
		p_shot_f2_set( x, y , 2 + ( rand( ) % 3 ) );
	}
	else 
	{
		BltRect( 6, 110, 104, 0 + ( ( ( save_data[3] - 1 ) % 10 ) * 32 ), 160 + ( ( ( save_data[3] - 1 ) / 10 ) * 32 ), 32, 32 );	/*  */
	}
	if ( demo[0] >= ( 60 * 3 ) )
	{
		demo[0] = ( 60 * 3 );
		BltRect( 18, 180, 114, 0, 144, 100, 8 * 2 );	/* 1 key to exit  */
	}
	
	if ( ( ( demo[0] >= ( 60 * 3 ) ) && ( IsPushOKKey( ) ) )|| ( ( g_DebugStageProduction != 0 ) && ( demo[0] >= 2 ) ) )
	{
		if ( gameflag[132] == 0 )
		{
			if ( gameflag[127] == 1 )	//トータルアタック
			{
				gameflag[135] = play_time[4];
			}
			else 
			{
				replay_file_save_w( );
				if ( gameflag[200 + save_data[3] + stage_hosei] > play_time[4] )
				{
					gameflag[200 + save_data[3] + stage_hosei] = play_time[4];	/* スコア保存 */
				
					replay_file_save( 0 );
				}

				if ( gameflag[300 + save_data[3] + stage_hosei] > Jump_counts )
				{
					gameflag[300 + save_data[3] + stage_hosei] = Jump_counts;	/* スコア保存 */
				
					replay_file_save( 1 );
				}
				
				if ( secretitemget == 1 )
				{
					gameflag[400 + save_data[3] + stage_hosei] = 1;
				}
			}
			
			if ( gameflag[129] != 0 )	//ステージセレクトから開始
			{
				gameflag[40] = 1;
				g_scene = EN_SN_STAGESELECT;
			}
			else 
			{
				save_data[3]++;
				gameflag[120] = save_data[3];
				if ( 
				     ( save_data[3] == 1 )
				  || ( save_data[3] == 11 )
				  || ( save_data[3] == 21 )
				  || ( save_data[3] == 31 )
				  || ( save_data[3] == 41 )
				   )
				{
					if ( gameflag[127] == 0 )	//トータルアタックではない
					{
						g_scene = EN_SN_DEMO;
					}
				}
			}
			if ( gameflag[121] < save_data[3] )
			{
				gameflag[121] = save_data[3];
			}
		}
		else 
		{
//			replay_file_save_w( );
			if ( gameflag[129] != 0 )	//ステージセレクトから開始
			{
				gameflag[40] = 1;
				g_scene = EN_SN_STAGESELECT;
			}
			else 
			{
				save_data[3]++;
			}
			if ( ( gameflag[124] == 1 ) || ( stage == 0 ) )	/* リプレイＯＮＥ */
			{
				gameflag[40] = 1;
				g_scene = EN_SN_TITLE;
			}
		}
		sn = 10;
	}
//	if ( player[14] == 10 )
//	{
		if ( player[2] != 33 )
		{
			player[10] = 0 ;
			player[11] = 0 ;
			player[2] = 33 ;
		}
//	}
	
}

void stage_end( )
{
	demo[0]++;
	if ( demo[0] > 60 )
	{
		if ( player[8] <= 0 )		/* ライフ０ */
		{
			gameflag[136]++;
			if ( gameflag[136] > 999 )	/* ミスカウント */
			{
				gameflag[136] = 999;
			}
		}
		if ( gameflag[127] == 1 )	//トータルアタック
		{
			play_time[4] = 1000000 + ( play_time[2] * 10000 ) + ( play_time[1] * 100 ) + ( play_time[0] );
			gameflag[135] = play_time[4];
		}
		gameflag[71] = 1;
		sn = 10;
	}
}

/* マップの端に触れてステージ移動 */
void end_scl( long s_num )
{
}



void p_shot_set( long type , long muki, long houkou )
{
	long i;
		
	for ( i = 0; i < 10; i++ )
	{
		if ( pshot[( i * 10 ) + 0 ] == 0 )
		{
			pshot[( i * 10 ) + 0 ] = 1;
			pshot[( i * 10 ) + 1 ] = player[0];
			pshot[( i * 10 ) + 2 ] = player[1];
			pshot[( i * 10 ) + 3 ] = houkou;	/* 左右 */
			pshot[( i * 10 ) + 4 ] = muki;	/* 方向 */
			pshot[( i * 10 ) + 5 ] = 0;
			pshot[( i * 10 ) + 6 ] = 0;
			pshot[( i * 10 ) + 7 ] = type;
			pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
			pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
			
			break;
		}
	}
}

void p_shot_disp( )
{
	long i;
	
	for ( i = 0; i < 10; i++ )
	{
		if ( pshot[( i * 10 ) + 0 ] == 1 )
		{
			/* 位置補正 */	
			pshot[( i * 10 ) + 1 ] = player[0];
			pshot[( i * 10 ) + 2 ] = player[1];
			
			if ( pshot[( i * 10 ) + 3 ] == 0 )
			{
				if ( pshot[( i * 10 ) + 4 ] == 0 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] + 16;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 1 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] + 10;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 2 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] - 16;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 3 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
				if ( pshot[( i * 10 ) + 4 ] == 4 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
					pshot[( i * 10 ) + 8 ] = 0;		/* あたり判定座標X */
					pshot[( i * 10 ) + 9 ] = 0;		/* あたり判定座標X */
				}
			}
			else if ( pshot[( i * 10 ) + 3 ] == 1 )
			{
				if ( pshot[( i * 10 ) + 4 ] == 0 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] + 16;
				}
				if ( pshot[( i * 10 ) + 4 ] == 1 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 37;
					pshot[( i * 10 ) + 2 ] = player[1] + 10;
				}
				if ( pshot[( i * 10 ) + 4 ] == 2 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 37;
					pshot[( i * 10 ) + 2 ] = player[1] - 16;
				}
				if ( pshot[( i * 10 ) + 4 ] == 3 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 37;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
				}
				if ( pshot[( i * 10 ) + 4 ] == 4 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
				}
			}


			BltRect( 3, pshot[( i * 10 ) + 1 ] - d_x, 480 - pshot[( i * 10 ) + 2 ] - 64 - d_y , pshot[( i * 10 ) + 6 ] * 64, pshot[( i * 10 ) + 3 ] * 256, 64, 64 );
//			BlendExBltRectW( 3, pshot[( i * 10 ) + 1 ] - d_x, 480 - pshot[( i * 10 ) + 2 ] - 64 - d_y, ( pshot[( i * 10 ) + 6 ] * 64 ) + ( pshot[( i * 10 ) + 3 ] * 256 ), pshot[( i * 10 ) + 4 ] * 64, 64 , 64 ,0 , 180 );	
			
			
			pshot[( i * 10 ) + 5 ]++;
			if ( pshot[( i * 10 ) + 5 ] >= 4 )
			{
				pshot[( i * 10 ) + 5 ] = 0;
				pshot[( i * 10 ) + 6 ]++;
				if ( pshot[( i * 10 ) + 6 ] >= 4 )
				{
					pshot[( i * 10 ) + 6 ] = 0;
					pshot[( i * 10 ) + 0 ] = 0;
				}
			}
		}
	}
}

void p_shot_f_set( long x, long y , long type )
{
	long i;
	
	for ( i = 0; i < 40; i++ )
	{
		if ( pshotf[( i * 10 ) + 0 ] == 0 )
		{
			pshotf[( i * 10 ) + 0 ] = 1;
			pshotf[( i * 10 ) + 1 ] = x;
			pshotf[( i * 10 ) + 2 ] = y;
			pshotf[( i * 10 ) + 5 ] = 120 / 10;
			pshotf[( i * 10 ) + 6 ] = 70 / 10;
			pshotf[( i * 10 ) + 7 ] = type;
			pshotf[( i * 10 ) + 8 ] = 0;
			break;
		}
	}
}
void p_shot_f_disp( )
{
	long i;
	
	for ( i = 0; i < 40; i++ )
	{
		if ( pshotf[( i * 10 ) + 0 ] == 1 )
		{
//			BltRect( 5, pshotf[( i * 10 ) + 1 ] - d_x, 480 - pshotf[( i * 10 ) + 2 ] - 32 - d_y , pshotf[( i * 10 ) + 6 ] * 32, pshotf[( i * 10 ) + 7 ] * 32, 32, 32 );
			pshotf[( i * 10 ) + 1 ] = pshotf[( i * 10 ) + 1 ] + pshotf[( i * 10 ) + 5 ];
			pshotf[( i * 10 ) + 2 ] = pshotf[( i * 10 ) + 2 ] + pshotf[( i * 10 ) + 6 ];
			BltRect( 40  ,
			         pshotf[( i * 10 ) + 1 ] - 16,
			         pshotf[( i * 10 ) + 2 ] - 16,
			         ( ( ( pshotf[( i * 10 ) + 7 ] / 100 ) - 1 ) * 128 ) ,
			         32 * ( pshotf[( i * 10 ) + 7 ] % 100 ),
			         32,
			         32 );
//			BlendExBltRectW( 5, pshotf[( i * 10 ) + 1 ] - d_x, 480 - pshotf[( i * 10 ) + 2 ] - 32 - d_y , pshotf[( i * 10 ) + 6 ] * 32, pshotf[( i * 10 ) + 7 ] * 32, 32, 32 , 0 ,  ( 200 - ( pshotf[( i * 10 ) + 6 ] * 10 ) ) );
			
			pshotf[( i * 10 ) + 8 ]++;
			if ( pshotf[( i * 10 ) + 8 ] >= 10 )
			{
				pshotf[( i * 10 ) + 0 ] = 0;
			}
		}
	}
}
void p_shot_f2_set( long x, long y , long muki )
{
	long i;
	long k; 
	long ii;
	long rg;
	long max;
	
	/* 発生位置X */
	/* 発生位置Y */

	if ( 
	     ( muki == 2 )
	  || ( muki == 3 )
	  || ( muki == 4 )
	   )
	{
		max = 1;
	}
	else 
	{
		max = 10;
	}
	
	for ( i = 0; i < max; i++ )
	{
		rg = ( ( rand( ) % 360 ) );
		
		k = ( rand( ) % 5 ) + 1;

		for ( ii = 0; ii < 80; ii++ )
		{
			if ( pshotf2[ii * 10 + 2] == 0 )
			{
				pshotf2[ii * 10 + 0] = funcSin( rg ) * k;		/* 弾速x */
				pshotf2[ii * 10 + 1] = funcCos( rg ) * k;		/* 弾速y */
				pshotf2[ii * 10 + 2] = 1;				/* 存在 */									
				pshotf2[ii * 10 + 3] = 1;				/* 方向 */
				pshotf2[ii * 10 + 4] = 0 ;			/* 消えるまでのフレーム数 */
				pshotf2[ii * 10 + 5] = ( x ) << 16 ;	/* 初期位置の設定 */
				pshotf2[ii * 10 + 6] = ( y ) << 16 ;
				pshotf2[ii * 10 + 7] = 0 ;			/* 消えるまでのフレーム数 */
				pshotf2[ii * 10 + 8] = 10 ; 			/* 消えるまでのフレーム数 */
				pshotf2[ii * 10 + 9] = muki ; 			/* type */
				break;
			}
		}
	}
}
void p_shot_f2_disp( )
{
	long ii;

	for ( ii = 0; ii < 80; ii++ )
	{
		if ( pshotf2[ii * 10 + 2] == 1 )
		{
			if (
			     ( pshotf2[ii * 10 + 9] == 2 )
			  || ( pshotf2[ii * 10 + 9] == 3 )
			  || ( pshotf2[ii * 10 + 9] == 4 )
			   )
			{
				BltRect( 5, ( pshotf2[ii * 10 + 5] >> 16 ), ( pshotf2[ii * 10 + 6] >> 16 ) - 32, pshotf2[ii * 10 + 4] * 32, 128 + ( ( pshotf2[ii * 10 + 9] - 2 ) * 32 ) , 32, 32 );
				pshotf2[ii * 10 + 5] = pshotf2[ii * 10 + 0] + pshotf2[ii * 10 + 5];		/* 弾速x */
				pshotf2[ii * 10 + 6] = pshotf2[ii * 10 + 1] + pshotf2[ii * 10 + 6];		/* 弾速x */
				pshotf2[ii * 10 + 3] = 1;				/* 方向 */
				pshotf2[ii * 10 + 7]++ ;			/* 消えるまでのフレーム数 */
				if ( pshotf2[ii * 10 + 7] >= pshotf2[ii * 10 + 8] )
				{
					pshotf2[ii * 10 + 7] = 0;
					pshotf2[ii * 10 + 4] = pshotf2[ii * 10 + 4] + 1 ;			/* 消えるまでのフレーム数 */
					if ( pshotf2[ii * 10 + 4] >= 2 )
					{
						pshotf2[ii * 10 + 2] = 0;				/* 存在無し */									
					}
				}
			}
			else
			{
				BltRect( 5, ( pshotf2[ii * 10 + 5] >> 16 ) - d_x, ( 0 - ( pshotf2[ii * 10 + 6] >> 16 ) ) + MapInfo[3] - 32 - d_y, pshotf2[ii * 10 + 4] * 32, 32, 32, 32 );
				pshotf2[ii * 10 + 5] = pshotf2[ii * 10 + 0] + pshotf2[ii * 10 + 5];		/* 弾速x */
				pshotf2[ii * 10 + 6] = pshotf2[ii * 10 + 1] + pshotf2[ii * 10 + 6];		/* 弾速x */
				pshotf2[ii * 10 + 3] = 1;				/* 方向 */
				pshotf2[ii * 10 + 7]++ ;			/* 消えるまでのフレーム数 */
				if ( pshotf2[ii * 10 + 7] >= pshotf2[ii * 10 + 8] )
				{
					pshotf2[ii * 10 + 7] = 0;
					pshotf2[ii * 10 + 4] = pshotf2[ii * 10 + 4] + 1 ;			/* 消えるまでのフレーム数 */
					if ( pshotf2[ii * 10 + 4] >= 4 )
					{
						pshotf2[ii * 10 + 2] = 0;				/* 存在無し */									
					}
				}
			}
//			BlendExBltRectW( 5, ( pshotf2[ii * 10 + 5] >> 16 ) - d_x, 480 - ( pshotf2[ii * 10 + 6] >> 16 ) - 4 - d_y, ( pshotf2[ii * 10 + 4] * 4 ) , 32, 4, 4 , 1 , ( 255 - ( pshotf2[ii * 10 + 4] * 20 ) ) );
		}
	}

}


void item_set( long type, long x, long y, long iti, long g_num )
{
	long i;
	long bx;
	long by;

	i = 0;
	bx = 0;
	by = 0;
/*
	
	if ( iti != 0 )
	{
		if ( 0 == item_sonzai( iti, g_num ) )
		{
			return;
		} 
	}	
	if ( iti < 0 )
	{
		return;
	}
*/
	by = type / 100;
	if ( by == 5 )
	{
		//スイッチの描画順は前
		for ( i = 0; i < item_data[1]; i++ )
		{
			if ( item[( i * item_data[2] ) + 0 ] == 0 )
			{
				item[( i * item_data[2] ) + 0 ] = 1;
				item[( i * item_data[2] ) + 1 ] = x;
				item[( i * item_data[2] ) + 2 ] = y;
				item[( i * item_data[2] ) + 3 ] = type;
				item[( i * item_data[2] ) + 4 ] = 0;	// 支点からの相対位置X
				item[( i * item_data[2] ) + 5 ] = 0;	// 支点からの相対位置Y
				item[( i * item_data[2] ) + 6 ] = 0;	/* 移動カウンタ */
				item[( i * item_data[2] ) + 7 ] = -1;	/* 支点のポインタ */
				item[( i * item_data[2] ) + 8 ] = 0;	/* 移動量X */
				item[( i * item_data[2] ) + 9 ] = 0;	/* 移動量Y */
				item[( i * item_data[2] ) + 10 ] = -1;	/* 敵のポインタ */
				

				break;
			}
		}
	}
	else 
	{
		for ( i = ( item_data[1] - 1 ); i > 0; i-- )
		{
			if ( item[( i * item_data[2] ) + 0 ] == 0 )
			{
				item[( i * item_data[2] ) + 0 ] = 1;
				item[( i * item_data[2] ) + 1 ] = x;
				item[( i * item_data[2] ) + 2 ] = y;
				item[( i * item_data[2] ) + 3 ] = type;
				item[( i * item_data[2] ) + 4 ] = 0;	// 支点からの相対位置X
				item[( i * item_data[2] ) + 5 ] = 0;	// 支点からの相対位置Y
				item[( i * item_data[2] ) + 6 ] = 0;	/* 移動カウンタ */
				item[( i * item_data[2] ) + 7 ] = -1;	/* 支点のポインタ */
				item[( i * item_data[2] ) + 8 ] = 0;	/* 移動量X */
				item[( i * item_data[2] ) + 9 ] = 0;	/* 移動量Y */
				item[( i * item_data[2] ) + 10 ] = -1;	/* 敵のポインタ */
				

				break;
			}
		}
	}
		
}
long item_sonzai( long map1, long map2 )
{
	long i;
	long rc;

	rc = 1;
	for ( i = 0; i < 100; i++ )
	{
		if ( item_wk[0 + ( i * 5 )] == 1 )
		{
			if ( ( item_wk[1 + ( i * 5 )] == map1 )
			  && ( item_wk[2 + ( i * 5 )] == map2 )
			  && ( item_wk[3 + ( i * 5 )] == stage ) )
			{
				rc = 0;
				break;
			}
		}
	}
	return( rc );

}


void item_disp( )
{
	long i;
	long k;
	long bx;
	long by;
	long k_f;
	long wbx;
	long disp_x_j;
	long disp_y_j;
	long ii;
	long bx2;
	long by2;
	
	ii = 0;
	bx2 = 0;
	by2 = 0;
	wbx = 0;
	k_f = 0;
	disp_x_j = 0;
	disp_y_j = 0;
	
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			
			disp_x_j = item[1 + ( i * item_data[2] )];
			disp_y_j = ( 0 - item[2 + ( i * item_data[2] )] ) + MapInfo[3];
			if ( ( ( ( d_x - item_data[0] ) <= ( disp_x_j ) ) 
			  && ( ( d_y - item_data[0] ) <= ( disp_y_j  ) )
			  && ( ( d_x + 320 + item_data[0] ) >= ( disp_x_j ) )
			  && ( ( d_y + 240 + item_data[0] ) >= ( disp_y_j ) ) )
			  || ( bak_alldrow == 1 )	 					/* 背景の描画をクリップするか */
			   )
			{

				BltRect( 12 , item[1 + ( i * item_data[2] )] - d_x, ( 0 - item[2 + ( i * item_data[2] )] ) + MapInfo[3] - item_data[0] - d_y, item_data[0] * bx, by * item_data[0], item_data[0], item_data[0] );
			}
			/* プレイヤーとの当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )] + 0 ) <= (player[0] + char_size[3] ) )	/* 自機とのあたり判定 */
				&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] - 0 ) )
				&& ( (item[2 + ( i * item_data[2] )]  + 0 ) < (player[1] + ( char_size[1] - 10 ) ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] - 0 ) ) )
				&& ( sn == 1 ) )
			{
				k_f = 1;
				if (
				     ( ( by == 10 ) && ( bx == 7 ) )
				   )
				{
					//押せるブロック
					//キャラクターが地面にいる
					if ( player[33] > 0 ) 
					{
						if ( ( player[14] == 10 ) && ( item[( i * item_data[2] ) + 4 ] == 10 ) )
						{
							/* 壁じゃなかったら */
							if (
								   ( ( ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + item_data[0] + player[33], item[2 + ( i * item_data[2] )] + 16, i ) >= 100 )
								    && ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + item_data[0] + player[33], item[2 + ( i * item_data[2] )] + 16, i ) <= 119 ) )
								  || ( ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + item_data[0] + player[33], item[2 + ( i * item_data[2] )] + 16, i ) >= 200 )
								    && ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + item_data[0] + player[33], item[2 + ( i * item_data[2] )] + 16, i ) <= 219 ) ) )
							   )
							{
								player[0] = item[1 + ( i * item_data[2] )] - ( char_size[3] );
								player[29] = 0;
							}
							else 
							{
								if ( item[8 + ( i * item_data[2] )] >= 0 )
								{
									item[( i * item_data[2] ) + 1 ] = item[( i * item_data[2] ) + 1 ] + player[33] ;
									player[29] = 0;
								}
							}
						}
						else 
						{
							player[0] = item[1 + ( i * item_data[2] )] - ( char_size[3] );
							player[29] = 0;
						}
					}
					else if ( player[33] < 0 ) 
					{
						/* 壁じゃなかったら */
						if ( ( player[14] == 10 ) && ( item[( i * item_data[2] ) + 4 ] == 10 ) )
						{
							if (
								   ( ( ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + player[33] , item[2 + ( i * item_data[2] )] + 16, i ) >= 100 )
								    && ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + player[33] , item[2 + ( i * item_data[2] )] + 16, i ) <= 119 ) )
								  || ( ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + player[33] , item[2 + ( i * item_data[2] )] + 16, i ) >= 200 )
								    && ( map1_item_j_Isitem( item[1 + ( i * item_data[2] )] + player[33] , item[2 + ( i * item_data[2] )] + 16, i ) <= 219 ) ) )
							   )
							{
								player[0] = item[1 + ( i * item_data[2] )] + item_data[0] - char_size[2];
								player[29] = 0;
							}
							else 
							{
								if ( item[8 + ( i * item_data[2] )] >= 0 )
								{
									item[( i * item_data[2] ) + 1 ] = item[( i * item_data[2] ) + 1 ] + player[33] ;
									player[29] = 0;
								}
							}
						}
						else 
						{
							player[0] = item[1 + ( i * item_data[2] )] + item_data[0] - char_size[2];
							player[29] = 0;
						}
					}
				}
				
			}
			if ( ( ( (item[1 + ( i * item_data[2] )] + 5 ) <= (player[0] + char_size[3] ) )	/* 自機とのあたり判定 */
				&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] - 5 ) )
				&& ( (item[2 + ( i * item_data[2] )]  + 5 ) < (player[1] + ( char_size[1] - 10 ) ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] - 5 ) ) )
				&& ( sn == 1 ) )
			{
				//地面にいる
//				if ( player[14] == 10 )
//				{
				if ( one_event == 0 )
				{
					one_event = 1;
					if (
					     ( ( by == 10 ) && ( bx == 1 ) )
					  || ( ( by == 10 ) && ( bx == 2 ) )
					   )
					{
						//回転床
						soundPlaySe( EN_SE_PAWA );
						sn = 5;
						player[20] = 0;
						player[21] = 0;
						player[22] = 0;

						player[10] = 0;
						player[11] = 0;
						player[4] = 0;
						player[5] = 3;
						player[2] = 2;		// つかみ

						bak_make( );


						player[22] = 10;
						player[20] = player[21];
						//乗っているアイテムによって回転方向を決定
						if ( ( by == 10 ) && ( bx == 1 ) )
						{
							player[21] = player[21] - 90;
						}
						if ( ( by == 10 ) && ( bx == 2 ) )
						{
							player[21] = player[21] + 90;
						}
						
						if ( player[21] < 0 )
						{
							player[21] = player[21] + 360;
						}
						if ( player[21] >= 360 )
						{
							player[21] = player[21] - 360;
						}
						player[9] = 1;
					}
				}
				if ( ( by == 10 ) && ( bx == 3 ) )
				{
					//上バネ
					soundPlaySe( EN_SE_JUMP );
					/* アイテムに乗っていない場合はそこがリトライ位置 */
					if ( player[2] != 31 )
					{
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	/* 空中 */
					}
					player[14] = 7;
					player[13] = 0;
					player[25] = 1;
					jmp_st( );
				}
				if ( 
				     ( ( by == 10 ) && ( bx == 4 ) )
				  || ( ( by == 10 ) && ( bx == 6 ) )
				   )
				{
					//横バネ
					soundPlaySe( EN_SE_JUMP );
					/* アイテムに乗っていない場合はそこがリトライ位置 */
/*
					if ( player[2] != 31 )
					{
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	// 空中 
					}
*/
					if ( ( by == 10 ) && ( bx == 4 ) )
					{
						player[29] = 20;	// 横バネふき飛び力
					}
					else 
					{
						player[29] = -20;	// 横バネふき飛び力
					}
//					jmp_st( );
				}
			}
			
			if ( 
			     ( sn == 1 )
			  || ( sn == 6 )
			   )
			{
				switch ( by )
				{
				case 2:	// 上方向
				case 3:
				case 4:
					if ( item[( i * item_data[2] ) + 7 ] >= 0 )	// 支点が存在する
					{
						if ( item[6 + ( i * item_data[2] )] > 0 )
						{
							/* プレイヤーとの当たり判定 */
							if ( ( ( (item[1 + ( i * item_data[2] )] + item[( i * item_data[2] ) + 8 ] ) <= (player[0] + char_size[3] ) )	/* 自機とのあたり判定 */
								&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] + item[( i * item_data[2] ) + 8 ] ) )
								&& ( (item[2 + ( i * item_data[2] )]  + item[( i * item_data[2] ) + 9 ] ) < (player[1] + ( char_size[1] ) ) )
								&& ( (player[1] ) < ( item[2 + ( i * item_data[2] )] + item_data[0] + item[( i * item_data[2] ) + 9 ] ) ) )
								&& ( by == 3 )
							   )
							{
								//移動終了
//								item[6 + ( i * item_data[2] )] = -1;
							}
							else 
							{
								item[( i * item_data[2] ) + 1 ] = item[( i * item_data[2] ) + 1 ] + item[( i * item_data[2] ) + 8 ] ;
								item[( i * item_data[2] ) + 2 ] = item[( i * item_data[2] ) + 2 ] + item[( i * item_data[2] ) + 9 ] ;
								item[( i * item_data[2] ) + 6 ]--;
							}
							
							if ( item[6 + ( i * item_data[2] )] == 1 )	// 移動フレーム数が停止の場合
							{
								k = item[7 + ( i * item_data[2] )];	// 支点の取得
								item[( i * item_data[2] ) + 1 ] = ( item[( k * item_data[2] ) + 1 ] + item[4 + ( i * item_data[2] )] ) ;
								item[( i * item_data[2] ) + 2 ] = ( item[( k * item_data[2] ) + 2 ] + item[5 + ( i * item_data[2] )] ) ;
								item[( i * item_data[2] ) + 6 ] = 0;
							}
							if ( item[( i * item_data[2] ) + 10 ] >= 0 )	// 敵のポインタが存在する
							{
								k = item[10 + ( i * item_data[2] )];	// 支点の取得
								enemy[1 +( k * enm_data[2] )] = item[1 + ( i * item_data[2] )];
								enemy[2 +( k * enm_data[2] )] = item[2 + ( i * item_data[2] )];
							}
						}
					}
					else 
					{
						if ( item[( i * item_data[2] ) + 7 ] == -1 )		// 初回検索
						{
							//支点を検索
							item[( i * item_data[2] ) + 7 ] = -2;	//無し
							for ( ii = 0; ii < item_data[1]; ii++ )
							{
								if ( item[( ii * item_data[2] ) + 0 ] != 0 )
								{
									bx2 = item[( ii * item_data[2] ) + 3 ] % 100;
									by2 = item[( ii * item_data[2] ) + 3 ] / 100;
									switch( by )
									{
									case 2:
									case 3:
									case 4:
										if ( ( by2 == 1 ) && ( bx2 == bx ) )
										{
											// 支点からの相対位置を保存
											item[( i * item_data[2] ) + 4 ] = item[( i * item_data[2] ) + 1 ] - item[( ii * item_data[2] ) + 1 ];	/* 動作用バッファ */
											item[( i * item_data[2] ) + 5 ] = item[( i * item_data[2] ) + 2 ] - item[( ii * item_data[2] ) + 2 ];	/* 動作用バッファ */
											item[( i * item_data[2] ) + 7 ] = ii;
										}
										break;
									default:
										break;
									}
									if ( item[( i * item_data[2] ) + 7 ] != -2 )
									{
										// 支点が見つかった
										break;
									}
								}
							}
						}
						if ( by == 4 )	// 敵移動アイテム
						{
							if ( item[( i * item_data[2] ) + 10 ] == -1 )		// 初回検索
							{
								//支点を検索
								item[( i * item_data[2] ) + 10 ] = -2;	//無し
								for ( ii = 0; ii < enm_data[1]; ii++ )
								{
									if ( enemy[0 +( ii * enm_data[2] )] == 1 )
									{
										//同じ座標に敵がいる場合ポインタの取得
										if ( 
										     ( enemy[1 +( ii * enm_data[2] )] == item[( i * item_data[2] ) + 1 ] )
										  && ( enemy[2 +( ii * enm_data[2] )] == item[( i * item_data[2] ) + 2 ] )
										   )
										{
											item[( i * item_data[2] ) + 10 ] = ii;	/* 動作用バッファ */
										}
									}
								}
							}
						}
					}
					break;
				case 10:
					if ( bx == 7 )
					{
						if ( gameflag[128] == 0 )	//マップビューではない
						{
							//箱
							item_jmp( i );
						}
					}
					break;
				case 5:
					// スイッチ
					k = 0;
					if ( ( ( (item[1 + ( i * item_data[2] )] + 0 ) <= (player[0] + char_size[3] ) )	/* 自機とのあたり判定 */
						&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] - 0 ) )
						&& ( (item[2 + ( i * item_data[2] )]  + 0 ) < (player[1] + ( char_size[1] - 10 ) ) )
						&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] - 0 ) ) )
						&& ( sn == 1 ) )
					{
						// スイッチが入っている
						k = 1;
					}
					else 
					{
						for ( ii = 0; ii < item_data[1]; ii++ )
						{
							if ( item[( ii * item_data[2] ) + 0 ] != 0 )
							{
								bx2 = item[( ii * item_data[2] ) + 3 ] % 100;
								by2 = item[( ii * item_data[2] ) + 3 ] / 100;
								if ( 
								     ( ( by2 == 10 ) && ( bx2 == 7 ) )
								  || ( by2 == 2 )
								  || ( by2 == 3 )
								  || ( by2 == 4 )
								   )
								{
									//箱を検索して当たり判定を行う
									if ( ( ( (item[1 + ( i  * item_data[2] )] ) < ( item[1 + ( ii * item_data[2] )] + item_data[0] ) )	/* 自機とのあたり判定 */
										&& ( (item[1 + ( ii * item_data[2] )] ) < ( item[1 + ( i  * item_data[2] )] + item_data[0] ) )
										&& ( (item[2 + ( i  * item_data[2] )] ) < ( item[2 + ( ii * item_data[2] )] + item_data[0] ) )
										&& ( (item[2 + ( ii * item_data[2] )] ) < ( item[2 + ( i  * item_data[2] )] + item_data[0] ) ) ) )
									{
										k = 1;
									}
								}
							}
						}
					}
					if ( k == 1 )
					{
						// スイッチが入っている
						if ( item[4 + ( i * item_data[2] )] == 0 )
						{
							//前回が押されていなかった
							soundPlaySe( EN_SE_SW );
						}
						item[4 + ( i * item_data[2] )] = 1;
					}
					else 
					{
						item[4 + ( i * item_data[2] )] = 0;
					}
					break;
				case 6:
				case 7:
					//スイッチで消えるブロック
					//スイッチが入っていない
					item[3 + ( i * item_data[2] )] = 600 + bx;
					for ( ii = 0; ii < item_data[1]; ii++ )
					{
						if ( item[( ii * item_data[2] ) + 0 ] != 0 )
						{
							bx2 = item[( ii * item_data[2] ) + 3 ] % 100;
							by2 = item[( ii * item_data[2] ) + 3 ] / 100;
							if ( ( by2 == 5 ) && ( bx2 == bx ) )
							{
								if ( item[( ii * item_data[2] ) + 4 ] != 0 )
								{
									//スイッチが入っている
									item[3 + ( i * item_data[2] )] = 700 + bx;
								}
							}
						}
					}
/*
					if ( item[( i * item_data[2] ) + 7 ] >= 0 )	// 支点が存在する
					{
						k = item[7 + ( i * item_data[2] )];	// スイッチの状態を検索
						if ( item[4 + ( k * item_data[2] )] != 0 )
						{
							//スイッチが入っている
							item[3 + ( i * item_data[2] )] = 700 + bx;
						}
						else 
						{
							//スイッチが入っていない
							item[3 + ( i * item_data[2] )] = 600 + bx;
						}
					}
					else 
					{
						if ( item[( i * item_data[2] ) + 7 ] == -1 )		// 初回検索
						{
							//スイッチを検索
							item[( i * item_data[2] ) + 7 ] = -2;	//無し
							for ( ii = 0; ii < item_data[1]; ii++ )
							{
								if ( item[( ii * item_data[2] ) + 0 ] != 0 )
								{
									bx2 = item[( ii * item_data[2] ) + 3 ] % 100;
									by2 = item[( ii * item_data[2] ) + 3 ] / 100;
									if ( ( by2 == 5 ) && ( bx2 == bx ) )
									{
										// スイッチからの相対位置を保存
										item[( i * item_data[2] ) + 7 ] = ii;
									}
									if ( item[( i * item_data[2] ) + 7 ] != -2 )
									{
										// スイッチが見つかった
										break;
									}
								}
							}
						}
						
					}
*/
					break;
				default:
					break;
				}
			}
		}
	}
	if ( ( k_f == 0 ) && ( sn == 1 ) )
	{
		one_event = 0;
	}
}
/* アイテムのＹ座標計算 */
void item_jmp( int i )
{
	int y1;
	int px1 ;
	int px2 ;
	int py ;
	int py2 ;
	int py3 ;

	test[1] = 0;
	px1 = ( item[( i * item_data[2] ) + 1 ] + 5 ) / 32;
	px2 = ( item[( i * item_data[2] ) + 1 ] + ( 32 - 5 ) ) / 32;
	py = ( MapInfo[1] - ( ( item[( i * item_data[2] ) + 2 ] + 28 ) / 32 ) );

	item[( i * item_data[2] ) + 5 ]++;
	if ( item[( i * item_data[2] ) + 5 ] >= 10 )
	{
		item[( i * item_data[2] ) + 5 ] = 0;
	}

	if ( item[( i * item_data[2] ) + 4 ] == 10 ) 
	{
		/* 地面判定 */
		if ( ( ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 299 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 299 ) ) 
		  || ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		  && ( ( ( item[( i * item_data[2] ) + 2 ] ) % 32 ) == 0 ) )
		{
			return;
		}
		else 
		{
			if ( item_up_Isitem( i ) != -1 )	/* アイテムの上に乗っている */
			{
				item[( i * item_data[2] ) + 2 ] = item_up_Isitem( i ); 
				item[( i * item_data[2] ) + 4 ] = 10;
				return;
			}
			item[( i * item_data[2] ) + 4 ]  = -1;
			item[( i * item_data[2] ) + 5 ]  = 0;
		}
	}
	

	if ( item[( i * item_data[2] ) + 5 ] == 0 )
	{
		item[( i * item_data[2] ) + 4 ]  = item[( i * item_data[2] ) + 4 ]  - 3;
		if ( ( item[( i * item_data[2] ) + 4 ]  <= 2 ) && ( item[( i * item_data[2] ) + 4 ]  > -2 ) )
		{
			item[( i * item_data[2] ) + 4 ]  = -1;
		}
		if ( item[( i * item_data[2] ) + 4 ]  < -4 )
		{
			item[( i * item_data[2] ) + 4 ]  = -4;
		}
		/* 地面判定 */
	}
	
	/* 画面端で落ちるのを防止 */
	if ( ( item[( i * item_data[2] ) + 1 ] < 0 ) || ( item[( i * item_data[2] ) + 1 ] > ( MapInfo[2] - 32 ) ) )
	{
		item[( i * item_data[2] ) + 4 ]  = 0;
	}
	/* 今回の位置 */
	y1 = ( ( 0 - item[( i * item_data[2] ) + 4 ]  ) * ( 0 - item[( i * item_data[2] ) + 4 ]  ) * ( 0 - item[( i * item_data[2] ) + 4 ]  ) );

	px1 = ( item[( i * item_data[2] ) + 1 ] + 16 ) / 32;
	px2 = ( item[( i * item_data[2] ) + 1 ] + 16 ) / 32;
	py = ( MapInfo[1] - ( ( item[( i * item_data[2] ) + 2 ] + 28 ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( item[( i * item_data[2] ) + 2 ] + 49 + 48 ) / 32 ) );
	item[( i * item_data[2] ) + 2 ] = item[( i * item_data[2] ) + 2 ] - ( y1 / 20 );
	py3 = ( MapInfo[1] - ( ( item[( i * item_data[2] ) + 2 ] + 32 + 32 + 16 ) / 32 ) );

	if ( item[( i * item_data[2] ) + 2 ] > MapInfo[3] ) 
	{
		return;
	}

	if ( item[( i * item_data[2] ) + 4 ]  <= 0 ) 													/* 上り中は判定しない */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 299 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 299 ) ) 
		  || ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		{
			item[( i * item_data[2] ) + 2 ] = ( ( MapInfo[1] - py ) * 32 ); 
			item[( i * item_data[2] ) + 4 ]  = 10;
		}
		else
		{
			if ( item_up_Isitem( i ) != -1 )	/* アイテムの上に乗っている */
			{
				item[( i * item_data[2] ) + 2 ] = item_up_Isitem( i ); 
				item[( i * item_data[2] ) + 4 ] = 10;
				return;
			}
		}
	}
	else		/* 上昇中 */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) ) )
		{
			item[( i * item_data[2] ) + 4 ]  = -1;
		}
	}
	if ( item[( i * item_data[2] ) + 2 ] <= -14 )
	{
		item[( i * item_data[2] ) + 0 ] = 0;
	}
	
}

// アイテム同士に線を
void item_line( void )
{
	int i;
	int by;
	int k;
	int harfsize;
	int x1;
	int y1;
	int x2;
	int y2;
	
	k = 0;
	i = 0;
	by = 0;
	harfsize = item_data[0] / 2;	// 半分
	
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			by = item[( i * item_data[2] ) + 3 ] / 100;
			switch ( by )
			{
			case 2:	// 上方向
			case 3:
			case 4:
				if ( item[7 + ( i * item_data[2] )] >= 0 )
				{
					k = item[7 + ( i * item_data[2] )];	// 支点の取得
					x1 = ( ( item[1 + ( i * item_data[2] )] + harfsize ) - d_x ) << 16;
					y1 = ( ( 0 - item[2 + ( i * item_data[2] )] ) + MapInfo[3] - item_data[0] - d_y + harfsize - 1 ) << 16;
					x2 = ( ( item[1 + ( k * item_data[2] )] + harfsize ) - d_x ) << 16;
					y2 = ( ( 0 - item[2 + ( k * item_data[2] )] ) + MapInfo[3] - item_data[0] - d_y + harfsize - 1 ) << 16;
					// 線の描画
					drawGRPline( x1, y1, x2, y2, SDL_MapRGB(g_screen->format,255,255,255) );
				}
				break;
			default:
				break;
			}
		}
	}
}
//アイテムの落下時に使用
//進入不可アイテムが足元にある場合は、座標を返す
long item_up_Isitem( long item_index )
{
	long i;
	long bx;
	long by;
	long px;
	long py;
	
	px = item[1 + ( item_index * item_data[2] )];
	py = item[2 + ( item_index * item_data[2] )];
	
	for ( i = 0; i < item_data[1]; i++ )
	{
//		if ( ( item[( i * item_data[2] ) + 0 ] == 1 ) && ( item_index != i ) )
		if ( ( item[( i * item_data[2] ) + 0 ] == 1 ) )
		{
			//自分は判定しない
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			
			if (
			     ( by == 2 ) 
			  || ( by == 3 ) 
			  || ( by == 6 ) 
			  || ( ( by == 10 ) && ( bx == 7 ) ) 
			   )
			{
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( px + item_data[0] - 5 ) )	/* 自機とのあたり判定 */
					&& ( (px + 5) < (item[1 + ( i * item_data[2] )] + item_data[0] ) )
					&& ( (item[2 + ( i * item_data[2] )] + 27 ) < (py + 10 ) )
					&& ( (py - 1) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
				{
					return( item[2 + ( i * item_data[2] )] + 32 );
				}
			}
		}
	}
	if ( ( ( (player[0] + 10  ) < ( px + item_data[0] ) )	/* 自機とのあたり判定 */
		&& ( (px ) < (player[0] + 22 ) )
		&& ( (player[1] + 27 ) < (py + 10 ) )
		&& ( (py - 1) < ( player[1] + 32 ) ) ) )
	{
		return( player[1] + 32 );
	}

	return( -1 );
}

long item_up( )
{
	long i;
	long bx;
	long by;
	
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			
			if (
			     ( by == 2 ) 
			  || ( by == 3 ) 
			  || ( by == 6 ) 
			  || ( ( by == 10 ) && ( bx == 7 ) ) 
			   )
			{
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* 自機とのあたり判定 */
					&& ( (player[0] + 10 ) < (item[1 + ( i * item_data[2] )] + 32 ) )
					&& ( (item[2 + ( i * item_data[2] )] + 27 ) < (player[1] + 10 ) )
					&& ( (player[1] - 1 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) ) )
				{
					return( item[2 + ( i * item_data[2] )] + 32 );
				}
			}
		}
	}
	return( -1 );
}
long item_up2( )
{
	long i;
	long bx;
	long by;
	
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			
			if (
			     ( by == 3 )
			  || ( by == 6 )
			  || ( ( by == 10 ) && ( bx == 7 ) ) 
			   )
			{
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* 自機とのあたり判定 */
					&& ( (player[0] + 10 ) < (item[1 + ( i * item_data[2] )] + 32 ) )
					&& ( (item[2 + ( i * item_data[2] )] + 0 ) < (player[1] + 33 ) )
					&& ( (player[1] + 20 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) ) )
				{
					return( item[2 + ( i * item_data[2] )] - 32 );
				}
			}
		}
	}
	return( -1 );
}

/* アイテムに重なって上が押された時のイベント */
long item_event( )
{
	long i;
	long rc;
	long r_f;
	
	rc = 0;
	
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			r_f = 0;
			
			/* プレイヤーとの当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* 自機とのあたり判定 */
				&& ( (player[0] + 10 ) < (item[1 + ( i * item_data[2] )] + 32 ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + 32 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) )
				&& ( player[14] == 10 ) )
			{
				r_f = 1;
				player[18] = 0;	/* 着地モーションとほったらかしアニメーションの解除 */

			}

			if ( ( r_f == 1 ) && ( item[( i * item_data[2] ) + 7 ] == 0 ) )
			{
				if ( ( item[( i * 10 ) + 3 ] >= 100 ) && ( item[( i * 10 ) + 3 ] <= 220 ) ) /* 看板 */
				{
					rc = 1;
//					event_set( item[( i * 10 ) + 3 ] , i );
				}
				break;
			}
			
		}
	}
	return( rc );
}


//敵作成
/* マップファイルから生成する場合 */
void enm_set( long type, long x, long y )
{	
	int i;
	int size;
	int syu;
	int j;


	for ( i = 0; i < enm_data[1]; i++ )
	{
		if ( enemy[0 + ( i * enm_data[2] )] == 0 )
		{
			for ( j = 0; j < enm_data[2] ; j++ )
			{
				enemy[j + ( i * enm_data[2] )] = 0;
			}
			
			
			enemy[0 + ( i * enm_data[2] )] = 1;
			enemy[1 + ( i * enm_data[2] )] = x;
			enemy[2 + ( i * enm_data[2] )] = y;
			size = type / 100;
			syu = type % 100;
			enemy[3 + ( i * enm_data[2] )] = size;
//			if ( size >= 4 )	/* ボス */
//			{
//				sprintf(string,"image/enm/boss%d.bmp", syu );
//				LoadBitmap(string[0],39 + size,true);								//プレーンナンバー２にシステム用ＢＭＰを読み込む
//				syu = 1;
//			}
			enemy[4 + ( i * enm_data[2] )] = syu;
//			enemy[5 + ( i * enm_data[2] )] = e_hp( type ) ;
			enemy[5 + ( i * enm_data[2] )] = 1 ;
			enemy[6 + ( i * enm_data[2] )] = 0;				/* やられカウンタ */
			enemy[7 + ( i * enm_data[2] )] = 0;				/* 位置補正 */
			enemy[8 + ( i * enm_data[2] )] = 0;				/* 表示パターン */
			enemy[9 + ( i * enm_data[2] )] = 0;				/* 向き */
			enemy[10+ ( i * enm_data[2] )] = 0;				/* 表示Ｙ */
			enemy[11+ ( i * enm_data[2] )] = type;			/* 種類 */
			enemy[12+ ( i * enm_data[2] )] = 0;				/* ジャンプフレームカウンタ */
			enemy[13+ ( i * enm_data[2] )] = 0;				/* ジャンプカウンタ */
			enemy[14+ ( i * enm_data[2] )] = x;				/* 再配置情報X */
			enemy[15+ ( i * enm_data[2] )] = y;				/* 再配置情報Y */
			enemy[16+ ( i * enm_data[2] )] = 0;				/* 無敵時間 */
			enemy[17+ ( i * enm_data[2] )] = 0;	/* ダメージ */
			enemy[18+ ( i * enm_data[2] )] = 1;				/* 再配置を行うか */
			enemy[19+ ( i * enm_data[2] )] = 0;/* Gold */
			enemy[20+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[21+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[22+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[23+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[24+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[25+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[26+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[27+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[28+ ( i * enm_data[2] )] = 0;				/* 移動量X */
			enemy[29+ ( i * enm_data[2] )] = 0;				/* 移動量Y */

			if ( size != 4 )
			{
				all_snack_count++;
			}
			/* 配置時にイベントを行いたい場合はここの判断文を追加する */
//			if ( size >= 4 )	/* ボス */
//			{
//				init_event_set_enm( enemy[11+ ( i * enm_data[2] )] , i );	/* 配置時のイベントを実行 */
//			}
			break;
		}
	}
}

//敵作成
/* 敵から敵が生成される場合 */
void enm_set2( long type, long x, long y ,long muki )
{	
	int i;
	int size;
	int syu;
	int j;

	for ( i = 0; i < enm_data[1]; i++ )
	{
		if ( enemy[0 + ( i * enm_data[2] )] == 0 )
		{
			for ( j = 0; j < enm_data[2] ; j++ )
			{
				enemy[j + ( i * enm_data[2] )] = 0;
			}
			
			
			enemy[0 + ( i * enm_data[2] )] = 1;
			enemy[1 + ( i * enm_data[2] )] = x;
			enemy[2 + ( i * enm_data[2] )] = y;
			size = type / 100;
			syu = type % 100;
			enemy[3 + ( i * enm_data[2] )] = size;
//			if ( size >= 4 )	/* ボス */
//			{
//				sprintf(string,"image/enm/boss%d.bmp", syu );
//				LoadBitmap(string[0],39 + size,true);								//プレーンナンバー２にシステム用ＢＭＰを読み込む
//				syu = 1;
//			}
			enemy[4 + ( i * enm_data[2] )] = syu;
//			enemy[5 + ( i * enm_data[2] )] = e_hp( type ) ;
			enemy[5 + ( i * enm_data[2] )] = 1 ;
			enemy[6 + ( i * enm_data[2] )] = 0;				/* やられカウンタ */
			enemy[7 + ( i * enm_data[2] )] = 0;				/* 位置補正 */
			enemy[8 + ( i * enm_data[2] )] = 0;				/* 表示パターン */
			enemy[9 + ( i * enm_data[2] )] = muki;			/* 向き */
			enemy[10+ ( i * enm_data[2] )] = 0;				/* 表示Ｙ */
			enemy[11+ ( i * enm_data[2] )] = type;			/* 種類 */
			enemy[12+ ( i * enm_data[2] )] = 0;				/* ジャンプフレームカウンタ */
			enemy[13+ ( i * enm_data[2] )] = 0;				/* ジャンプカウンタ */
			enemy[14+ ( i * enm_data[2] )] = x;				/* 再配置情報X */
			enemy[15+ ( i * enm_data[2] )] = y;				/* 再配置情報Y */
			enemy[16+ ( i * enm_data[2] )] = 0;				/* 無敵時間 */
			enemy[17+ ( i * enm_data[2] )] = 0;	/* ダメージ */
			enemy[18+ ( i * enm_data[2] )] = 0;				/* 再配置を行うか */
			enemy[19+ ( i * enm_data[2] )] = 0;/* Gold */
			enemy[20+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[21+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[22+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[23+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[24+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[25+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[26+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[27+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[28+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */
			enemy[29+ ( i * enm_data[2] )] = 0;				/* 動作用バッファ */


//			if ( size >= 4 )	/* ボス */
//			{
//				init_event_set_enm( enemy[11+ ( i * enm_data[2] )] , i );
//			}
			break;
		}
	}
}


/* 敵のＨＰを設定（e_setで使われる） */
long e_hp( long type )
{
	long rc;
	rc = 1;
	if ( ( type / 100 ) == 1 )	/* 32 */
	{
		rc = enm1_parameter[ 10 * ( type - 100 ) + 0 ];
	}
	if ( ( type / 100 ) == 2 )	/* 48 */
	{
		rc = enm2_parameter[ 10 * ( type - 200 ) + 0 ];
	}
	if ( ( type / 100 ) == 3 )	/* 64 */
	{
		rc = enm3_parameter[ 10 * ( type - 300 ) + 0 ];
	}
	if ( ( type / 100 ) == 4 )	/* 128 */
	{
		rc = enm4_parameter[ 10 * ( type - 400 ) + 0 ];
	}
	return ( rc );
}

void enm_disp()
{	
	long i;
	long k;
	long size ;
	long size2;
	long akt_size2;
	long p_h;
	long all;
	long size_hosei_x;
	long size_hosei_y;
	long isclaer;
	long is_tukami;
	long disp_x_j;
	long disp_y_j;

	disp_x_j = 0;
	disp_y_j = 0;
	
	is_tukami = 0;
	isclaer = 0; 
	size_hosei_x = 0;
	size_hosei_y = 0;
	p_h = 32;	/* プレイヤーの当たり判定 */
	all = 1;
	size = 0;
	akt_size2 = 0;
	
	for ( i = 0; i < enm_data[1]; i++ )
	{
		if ( enemy[0 +( i * enm_data[2] )] == 1 )
		{
			if ( enemy[3 + ( i * enm_data[2] )] != 4 )	/* 4ボス */
			{
				isclaer = 1;
			}
			all = 0;
			/* 無敵時間が存在する場合はカウント */
			if ( enemy[16 + ( i * enm_data[2] )] > 0 )
			{
				enemy[16 + ( i * enm_data[2] )]--;
			}

			/* 敵のサイズ取得 */
			if ( enemy[3 + ( i * enm_data[2] )] == 1 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 2 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 3 )
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 4 )	/* 4ボス */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 5 )	/* 5ボス */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 6 )	/* 6ボス */
			{
				size = 32;
			}
			
			/* ボスのサイズ補正 */
//			if ( ( enemy[11+ ( i * enm_data[2] )] == 401 ) || ( enemy[11+ ( i * enm_data[2] )] == 501 ) )
//			{
//				size_hosei_x = 5;
//				size_hosei_y = 10;
//			} 
//			else 
//			{
				size_hosei_x = 5;
				size_hosei_y = 10;
//			}
			
			/* 画面内の敵だけ描画する */
			disp_x_j = enemy[1 + ( i * enm_data[2] )];
			disp_y_j = ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3];

			if ( ( ( ( d_x - size ) <= ( disp_x_j ) ) 
			  && ( ( d_y - size ) <= ( disp_y_j  ) )
			  && ( ( d_x + 320 + size ) >= ( disp_x_j ) )
			  && ( ( d_y + 240 + size ) >= ( disp_y_j ) ) )
			  || ( bak_alldrow == 1 )	 					/* 背景の描画をクリップするか */
			   )
			{ 

				if ( enemy[6 + ( i * enm_data[2] )] > 0 )	/* やられ */
				{
					if ( ( ( enemy[16 + ( i * enm_data[2] )] % 2 ) == 0 ) || ( sn != 1 ) )
					{
//						if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* ボスのときは表示方法が違う */
//						{
//							BltRect( 39 + enemy[3 + ( i * enm_data[2] )] , enemy[1 + ( i * enm_data[2] )]  - d_x, ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3] - size  - d_y, ( size * 4 ) , size + ( size * enemy[9 + ( i * enm_data[2] )] ), size, size );
//						}
//						else 
//						{
							BltRect( 39 + enemy[3 + ( i * enm_data[2] )],
							        enemy[1 + ( i * enm_data[2] )]  - d_x,
							        ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3] - size  - d_y,
							        ( size * 8 ) + ( enemy[9 + ( i * enm_data[2])] *  size ),
							        size * ( enemy[4 + ( i * enm_data[2] )] + enemy[10+ ( i * enm_data[2] )] ),
							        size,
							        size );
//						}
					}
				}
				else 
				{
						
					if ( ( ( enemy[16 + ( i * enm_data[2] )] % 2 ) == 0 ) || ( sn != 1 ) )
					{
//						if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* ボスのときは表示方法が違う */
//						{
//							BltRect( 39 + enemy[3 + ( i * enm_data[2] )] ,
//							         enemy[1 + ( i * enm_data[2] )]  - d_x,
//							         ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3] - size  - d_y,
//							         ( size * enemy[8 + ( i * enm_data[2] )] ) ,
//							         size * ( enemy[4 + ( i * enm_data[2] )] + enemy[10+ ( i * enm_data[2] )] ) + ( enemy[9 + ( i * enm_data[2] )] * size ),
//							         size,
//							         size );
//						}
//						else 
//						{
//							BltRect( 39 + enemy[3 + ( i * enm_data[2] )] ,
							if ( enemy[3 + ( i * enm_data[2] )] == 4 )	//隠しアイテム
							{
								if ( snack_count == 1 )
								{
									BltRect( 40  ,
									         enemy[1 + ( i * enm_data[2] )]  - d_x,
									         ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3] - size  - d_y,
									         ( size * enemy[8 + ( i * enm_data[2] )] ) + ( enemy[9 + ( i * enm_data[2] )] * ( size * 4 ) ) + ( ( enemy[3 + ( i * enm_data[2] )] - 1 ) * 128 ) ,
									         size * ( enemy[4 + ( i * enm_data[2] )] + enemy[10+ ( i * enm_data[2] )] ),
									         size,
									         size );
								}
							}
							else 
							{
								BltRect( 40  ,
								         enemy[1 + ( i * enm_data[2] )]  - d_x,
								         ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3] - size  - d_y,
								         ( size * enemy[8 + ( i * enm_data[2] )] ) + ( enemy[9 + ( i * enm_data[2] )] * ( size * 4 ) ) + ( ( enemy[3 + ( i * enm_data[2] )] - 1 ) * 128 ) ,
								         size * ( enemy[4 + ( i * enm_data[2] )] + enemy[10+ ( i * enm_data[2] )] ),
								         size,
								         size );
							}
//						} 
					}
				}
			}
			
			/* 画面内の敵だけ描画する */
			if ( ( ( d_x - 320 - 64 ) <= ( disp_x_j ) ) 
			  && ( ( d_y - 240 - 64 ) <= ( disp_y_j  ) )
			  && ( ( d_x + 640 + 64 ) >= ( disp_x_j ) )
			  && ( ( d_y + 480 + 64 ) >= ( disp_y_j ) ) )
			{
				e_move( i );	/* 敵キャラ種類別動作 */
			}
				
			/* ボスは画面外へ移動しない */
#if false
			if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* 5ボス */
			{
				if ( enemy[i * enm_data[2] + 1] > ( MapInfo[2] - size ) )
				{
					enemy[i * enm_data[2] + 1] = ( MapInfo[2] - size );
				}
				if ( enemy[i * enm_data[2] + 1] < 1 )
				{
					enemy[i * enm_data[2] + 1] = 1;
				}
			}
#endif			
			/* 画面外へ移動した場合は消去 */
			if ( ( enemy[1 + ( i * enm_data[2] )] >= ( MapInfo[2] + size ) ) 
			  || ( enemy[1 + ( i * enm_data[2] )] <= ( 0 - size ) )
			  || ( enemy[2 + ( i * enm_data[2] )] <= ( 0 - size ) )
			  || ( enemy[2 + ( i * enm_data[2] )] >= ( MapInfo[3] + size ) ) )
			{
//				/* 画面外の場合に再配置を行う */
//				if ( enemy[18 + ( i * enm_data[2] )] == 1 )
//				{
//					set_enmreset_tbl( enemy[14 + ( i * enm_data[2] )], enemy[15 + ( i * enm_data[2] )], enemy[11 + ( i * enm_data[2] )] );
//				}
//				enemy[0 + ( i * enm_data[2] )] = 0;
			}
/*
			if ( sn != 1 )
			{
				return;
			}
*/

			/* プレイヤーとの当たり判定 */
			if ( ( ( (enemy[1 + i * enm_data[2]] + size_hosei_x ) < (player[0] + char_size[3] ) )	/* 自機とのあたり判定 */
				&& ( (player[0] + char_size[2] ) < (enemy[1 + i * enm_data[2]] + size - size_hosei_x ) )
				&& ( (enemy[2 + i * enm_data[2]] + size_hosei_y ) < (player[1] + p_h) )
				&& ( (player[1] + 5 ) < ( enemy[2 + i * enm_data[2]] + size - size_hosei_y - 10 ) ) ) 
				&& ( player[17] == 0 ) 					/* 無敵時間が無い */
				&& ( enemy[6 + i * enm_data[2]] == 0 ) )			/* 敵の無敵時間がない */
			{
				if ( gameflag[128] == 0 )	//マップビューではない
				{
					if ( enemy[3 + ( i * enm_data[2] )] == 4 )
					{
						if ( snack_count == 1 )
						{
							enemy[0 + i * enm_data[2]] = 0;		/* 消去 */
							soundPlaySe( EN_SE_L1 );
							p_shot_f2_set( ( enemy[1 + i * enm_data[2]] ) , ( enemy[2 + i * enm_data[2]] ), 0 );
							p_shot_f_set( 160 ,120, enemy[11 + i * enm_data[2]] );
							player[24] = 180;
							player[31] = 70; //カットイン
							player[32] = ( rand( ) % 3 ); //カットイン
							secretitemget = 1;						/* 隠しアイテムの取得 */
						}
					}
					else 
					{
						enemy[0 + i * enm_data[2]] = 0;		/* 消去 */
						soundPlaySe( EN_SE_L1 );
						p_shot_f2_set( ( enemy[1 + i * enm_data[2]] ) , ( enemy[2 + i * enm_data[2]] ), 0 );
						p_shot_f_set( 160 ,120, enemy[11 + i * enm_data[2]] );
						player[31] = 70; //カットイン
						player[32] = ( rand( ) % 3 ); //カットイン
					}
				}
			}

			/* 倒せない特別な敵（針等） */

//			if (
//			     ( ( enemy[11 + i * enm_data[2]] == 406 ) && ( ( enemy[8+ ( i * enm_data[2] )] == 1 ) || ( enemy[8+ ( i * enm_data[2] )] == 2 ) ) )		/* 6ボス */
//			   )
//			{
//			}
//			else 
			{
				/* 敵とオブジェクトの当たり判定 */
				for ( k = 0; k < 40 ; k++ )
				{
					/* オブジェクトのサイズ */
					size2 = 32;
					/* プレイヤーの弾との当たり判定 */
					if ( ( ( ( enemy[1 + i * enm_data[2]] + size_hosei_x ) < ( ( pmshot[5 + k * 20] >> 16 ) + size2 ) )
						&& ( ( ( pmshot[5 + k * 20] >> 16 ) + akt_size2 ) < ( enemy[1 + i * enm_data[2]] + size - size_hosei_x  ) )
						&& ( ( enemy[2 + i * enm_data[2]] + size_hosei_y ) < ( ( pmshot[6 + k * 20] >> 16 ) + size2 ) )
						&& ( ( ( pmshot[6 + k * 20] >> 16 ) + akt_size2 ) < ( enemy[2 + i * enm_data[2]] + size - size_hosei_y - 10  ) ) ) 
						&& ( pmshot[2 + k * 20] == 1 ) )
					{
						/* 無敵時間が存在しない */
						if ( enemy[16 + ( i * enm_data[2] )] == 0 )
						{
							/* 攻撃が効かない特別な敵 */
#if false
							if (
							     ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( enemy[ 9 + ( i * enm_data[2] )] == 1 ) && ( pmshot[3 + k * 20] == 2 ) )	/* コサクン */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( enemy[ 9 + ( i * enm_data[2] )] == 0 ) && ( pmshot[3 + k * 20] == 3 ) )	/* コサクン */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( pmshot[3 + k * 20] == 1 ) )	/* コサクン */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 112 ) && ( enemy[8 + ( i * enm_data[2] )] == 0 ) )	/* アーン */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 112 ) && ( enemy[8 + ( i * enm_data[2] )] == 1 ) )	/* アーン */
							   )
							{
								pmshot[2 + k * 20] = 0;		/* 弾消去 */
								se_wav( 2 );
								/* 下攻撃の場合はジャンプ */
								if ( pmshot[3 + k * 20] == 1 )
								{
									/* はねる */
									player[10] = 0;			/* アニメーションフレームカウンタのクリア */
									player[11] = 0;			/* アニメーションカウンタのクリア */
									player[2] = 21;			/* 空中状態 */

									player[14] = 5;			/* ジャンプ力の設定、これによって高さが変わる 1～9 */
									player[13] = 0;			/* ジャンプフレームカウンタのクリア */
			//						player[25] = 1;			/* ボタンを押してジャンプしたフラグ */
								}
							}
							else 
							{
								/* 攻撃ヒット効果の表示を配置 */
								p_shot_f_set( ( pmshot[5 + k * 20] >> 16 ) , ( pmshot[6 + k * 20] >> 16 ), 0 );

								/* 敵HPを減少 */
								enemy[5 + ( i * enm_data[2] )] = enemy[5 + ( i * enm_data[2] )] - 1;

								/* 向き設定 */
								if ( enemy[3 + ( i * enm_data[2] )] < 4 )	/* 4ボスは変わらない */
								{
									if ( pmshot[10 + k * 20] == 1 )
									{
										enemy[9 + ( i * enm_data[2] )] = 0;
									}
									else 
									{
										enemy[9 + ( i * enm_data[2] )] = 1;
									}
								}

//								pmshot[2 + k * 20] = 0;				/* 弾消去 */
								if ( enemy[5 + ( i * enm_data[2] )] <= 0 )		/* 倒した */
								{

									/* 倒した際のイベントを実行 */
									/* ボス以外でも行う場合はここの判断文を追加 */
									if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* 4ボス */
									{
										enemy[16 + ( i * enm_data[2] )] = 59;	/* 無敵時間の設定 */
//										boss_dead( enemy[1 + ( i * enm_data[2] )], enemy[2 + ( i * enm_data[2] )], i );
//										event_set_enm( enemy[11 + ( i * enm_data[2] )] , i );
#if false
										for ( l = 0; l < enm_data[1]; l++ )
										{
											enemy[5 + ( l * enm_data[2] )] = 0;
											enemy[6 + ( l * enm_data[2] )] = 60;		/* 消去 */
											enemy[16 + ( l * enm_data[2] )] = 60;
										}
#endif
									}
									
									p_shot_f2_set( ( pmshot[5 + k * 20] >> 16 ) - 4, ( pmshot[6 + k * 20] >> 16 ) + 4, 0 );
									enemy[6 + ( i * enm_data[2] )] = 30;		/* ダメージくらいモーション表示フレーム数 */
									enemy[16 + ( i * enm_data[2] )] = 60;	/* 無敵時間の設定 */
									se_wav( 5 );
								}
								else 
								{
									/* 倒してない */
									/* 無敵時間設定 */
									enemy[6 + ( i * enm_data[2] )] = 30;		/* のけぞり時間 */
									enemy[7 + ( i * enm_data[2] )] = 6;		/* 位置補正 */
									enemy[16 + ( i * enm_data[2] )] = 60;	/* 無敵時間 */
									se_wav( 4 );
									if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* ボスのときはのけぞりがない */
									{
										enemy[6 + ( i * enm_data[2] )] = 0;		/* のけぞり時間 */
										enemy[7 + ( i * enm_data[2] )] = 0;		/* 位置補正 */
									}
								}
							}
#endif
						}
					}
				}
			}
			
			if ( enemy[7 + ( i * enm_data[2] )] > 0 )
			{
				enemy[7 + ( i * enm_data[2] )]--;					/* 移動補正 */
				/* 壁に埋まらないように判定 */
				if ( enemy[9 + ( i * enm_data[2] )] == 0 )
				{
					if ( ( ( map1_item_j( enemy[1 + ( i * enm_data[2] )] - 4 , enemy[2 + ( i * enm_data[2] )] + 2 ) >= 100 )
					    && ( map1_item_j( enemy[1 + ( i * enm_data[2] )] - 4 , enemy[2 + ( i * enm_data[2] )] + 2 ) <= 119 ) )
					  || ( ( map1_item_j( enemy[1 + ( i * enm_data[2] )] - 4 , enemy[2 + ( i * enm_data[2] )] + 2 ) >= 200 )
					    && ( map1_item_j( enemy[1 + ( i * enm_data[2] )] - 4 , enemy[2 + ( i * enm_data[2] )] + 2 ) <= 219 ) ) )
					{
					}
					else 
					{
						enemy[1 + ( i * enm_data[2] )] = enemy[1 + ( i * enm_data[2] )] - ( enemy[7 + ( i * enm_data[2] )] * enemy[7 + ( i * enm_data[2] )] );
					}
				}
				else 
				{
					if ( ( ( map1_item_j( enemy[1 + ( i * enm_data[2] )] + size + 4, enemy[2 + ( i * enm_data[2] )] + 2 ) >= 100 )
					    && ( map1_item_j( enemy[1 + ( i * enm_data[2] )] + size + 4, enemy[2 + ( i * enm_data[2] )] + 2 ) <= 119 ) )
					  || ( ( map1_item_j( enemy[1 + ( i * enm_data[2] )] + size + 4, enemy[2 + ( i * enm_data[2] )] + 2 ) >= 200 )
					    && ( map1_item_j( enemy[1 + ( i * enm_data[2] )] + size + 4, enemy[2 + ( i * enm_data[2] )] + 2 ) <= 219 ) ) )
					{
					}
					else 
					{
						enemy[1 + ( i * enm_data[2] )] = enemy[1 + ( i * enm_data[2] )] + ( enemy[7 + ( i * enm_data[2] )] * enemy[7 + ( i * enm_data[2] )] );
					}
				}
			}
			
			/* ダメージくらいモーション */
			if ( enemy[6 + ( i * enm_data[2] )] > 0 )
			{
				enemy[6 + ( i * enm_data[2] )]--;					/* 消えるまでカウンタ */
				if ( enemy[6 + ( i * enm_data[2] )] == 0 )
				{
					if ( enemy[5 + ( i * enm_data[2] )] <= 0 )		/* HPが無い場合 */
					{
						if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* ボス */
						{
							se_wav( 18 );				/* ボスを倒した効果音 */

						}
						else 
						{
#if false
							if ( Rand( 5 ) == 0 )	/* ライフ出現 */
							{
								se_wav( 7 );
								kane_set( enemy[1 + ( i * enm_data[2] )] + ( ( size / 2 ) - 16 ), enemy[2 + ( i * enm_data[2] )] , 0, enemy[19+ ( i * enm_data[2] )] );
							}
							else 
							{
								se_wav( 7 );
								kane_set( enemy[1 + ( i * enm_data[2] )] + ( ( size / 2 ) - 16 ), enemy[2 + ( i * enm_data[2] )] , 1, enemy[19+ ( i * enm_data[2] )] );
							}
							/* 画面外の場合に再配置を行う */
							if ( enemy[18 + ( i * enm_data[2] )] == 1 )
							{
								set_enmreset_tbl( enemy[14 + ( i * enm_data[2] )], enemy[15 + ( i * enm_data[2] )], enemy[11 + ( i * enm_data[2] )] );
							}
#endif
						}
						enemy[0 + ( i * enm_data[2] )] = 0;		/* 消去 */
						
					}
				}
			}
		}
	}
	
//	if ( ( isclaer == 0 ) && ( sn == 1 ) )
	if ( ( isclaer == 0 ) )	/* ミスしてとってもクリア */
	{
		/* 全部とった */
//		player[14] = 0;
//		player[9] = 0;

		sn = 2;
		demo[0] = 0;
	} 
}

void e_move( long i )
{
	
	if ( enemy[6 + ( i * enm_data[2] )] > 0 )
	{
		return;
	}
	if ( enemy[5 + ( i * enm_data[2] )] <= 0 )	/* 倒した */
	{
		return;
	}
	
	enemy[8 + ( i * enm_data[2] )] = map_rot_info;		/* アニメーションパターン */
	enemy[9 + ( i * enm_data[2] )] = 0;		/* アニメーションパターン */
	enemy[14 + ( i * enm_data[2] )] = 0;

}

/* ボスを倒した演出 */
void boss_dead( long x, long y )
{
/*	
	long i;
	long xx;
	long yy;
	for ( i = 0; i < 100; i++ ) 
	{
//		BltFromBackupPlane();		//	バックアッププレーンからのBlt
		if ( ( i % 10 ) == 0 )
		{
			xx = ( rand( ) % 96 );
			yy = ( rand( ) % 96 );
			se_wav( 24 + ( rand( ) % 3 ) );
			p_shot_f_set( x + xx, y + yy, 0 );
			p_shot_f2_set(  x + xx + 15, y + yy + 15, 0 );
		}
		p_shot_f_disp( );
		p_shot_f2_disp( );
		halt;
	}
*/
}

//-----------------------------------------------------------------------------------
/* 敵ショット生成 */
void e_shot_set( long type , long i , long x, long y )
{
	long ii;
	long j;
	long rg;
	long mx;
	long my;
	
	/* 発生位置X */
	/* 発生位置Y */
	for ( ii = 0; ii < 20; ii++ )
	{
		if ( mgc_e[ii * 10 + 0] == 0 )					/* 存在してない */
		{

			for ( j = 0 ; j <= 9 ;j++ )
			{
				mgc_e[ii * 10 + j] = 0;
			}
			if ( type == 1061 )							/* ヤドカリ */
			{
				mx = ( ( 32 / 2 ) - 5 ) + player[0] - x;
				my = ( ( 32 / 2 ) - 5 ) + player[1] - y;
				rg = funcTan2( mx, my );
				rg = ( 90 );
				mgc_e[ii * 10 + 1] = x << 16;		/* X */
				mgc_e[ii * 10 + 2] = y << 16;		/* Y */
				mgc_e[ii * 10 + 3] = 0;		/* アニメーションカウンタ */
				mgc_e[ii * 10 + 4] = funcSin( rg ) * 4;		/* 移動方向 */
				mgc_e[ii * 10 + 5] = funcCos( rg ) * 4;	/* 移動方向 */
				mgc_e[ii * 10 + 6] = 6;		/* ダメージ */
				mgc_e[ii * 10 + 7] = 2;		/* 属性 */
				mgc_e[ii * 10 + 9] = type;					/* タイプplayer[10] */
			}

			mgc_e[ii * 10 + 0] = 1;					/* 存在あり */
			break;
		}
	}

}
/* ショット移動 */
void e_shot_disp( )
{
	long i;
	long p_h;
	long size ;
	
	p_h = 22;	/* プレイヤーの当たり判定 */
	size = 0;
	
	/* 発生位置X */
	/* 発生位置Y */
	for ( i = 0; i < 20; i++ )
	{
		if ( mgc_e[i * 10 + 0] == 1 )					/* 存在している */
		{
			if ( mgc_e[i * 10 + 9] == 4010 ) 	/* １ボス */
			{
				size = 32;
				BltRect( 50, ( mgc_e[i * 10 + 1] >> 16 ) - d_x , ( 0 - ( mgc_e[i * 10 + 2] >> 16 ) ) + 480 - 32 - d_y, mgc_e[i * 10 + 3] * 32, 0 , 32, 32 );
				mgc_e[i * 10 + 1] = mgc_e[i * 10 + 1] + mgc_e[i * 10 + 4];		/* X */
				mgc_e[i * 10 + 2] = mgc_e[i * 10 + 2] + mgc_e[i * 10 + 5];		/* Y */
				mgc_e[i * 10 + 3]++;					/* アニメーションカウンタ */
				if ( mgc_e[i * 10 + 3] >= 4 )
				{
					mgc_e[i * 10 + 3] = 0;
				}
			}
			
			/* プレイヤーとの当たり判定 */
			if ( ( ( ( ( mgc_e[1 + i * 10] >> 16 ) ) < (player[0] + 22 ) )	/* 自機とのあたり判定 */
				&& ( (player[0] + 10 ) < ( ( mgc_e[1 + i * 10] >> 16 ) + size ) )
				&& ( ( ( mgc_e[2 + i * 10] >> 16 ) ) < (player[1] + p_h) )
				&& ( (player[1] + 5  ) < ( ( mgc_e[2 + i * 10] >> 16 ) + size ) ) ) 
				&& ( player[17] == 0 ) )
			{
				player[10] = 0;
				player[11] = 0;
				player[12] = 4;
				player[13] = 0;
				player[2] = 31;	/* ダメージ */
				player[17] = 120;	/* 無敵時間 */
				player[8] = player[8] - 1;
				
				se_wav( 1 );
			}


			if ( ( ( mgc_e[i * 10 + 1] >> 16 ) >= 640 ) || ( ( mgc_e[i * 10 + 1] >> 16 ) <= 0 ) || ( ( mgc_e[i * 10 + 2] >> 16 ) <= -100 )|| ( ( mgc_e[i * 10 + 2] >> 16 ) >= 480 ))
			{
				mgc_e[i * 10 + 0] = 0;
			}
		}
	}
}

/* 敵用ジャンプ */
void enmjmp( long i )
{
	long y1;
	long px ;
	long px1 ;
	long px2 ;
	long py ;
	long py2 ;

	long size;
	long e10;
	/* 画面外では行わない */
/*
	if ( enemy[1 + ( i * 20 )] > 460 )
	{
		return;
	}
*/
	if ( enemy[3 + ( i * 20 )] == 1 )
	{
		size = 16;
	}
	else if ( enemy[3 + ( i * 20 )] == 2 )
	{
		size = 24;
	}
	else
	{
		size = 16;
	}

	if ( enemy[13 + ( i * 20 )] == 10 ) 
	{
		/* 今回の位置 */
		px = ( enemy[1 + ( i * 20 )] + 32 ) / 32;
		px1 = ( enemy[1 + ( i * 20 )] + size ) / 32;
		px2 = ( enemy[1 + ( i * 20 )] + size ) / 32;
		py = ( 16 - ( ( enemy[2 + ( i * 20 )] + 28 ) / 32 ) );
		/* 100 ～ 200は地面 */
		if ( ( !( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 119 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 119 ) ) ) 
		  && ( !( ( map1[ px1 + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 219 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 219 ) ) ) 
		  && ( !( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) ) )
		{
			enemy[13+ ( i * 20 )] = 0;
			enemy[12+ ( i * 20 )] = 0;
		}
		else 
		{
			return;
		}
	}

	enemy[12 + ( i * 20 )]++;
	if ( enemy[12+ ( i * 20 )] >= 10 )
	{
		enemy[12+ ( i * 20 )] = 0;
		
		enemy[13 + ( i * 20 )] = enemy[13 + ( i * 20 )] - 3;
//		if ( player[5] == 0 )
//		{
//			player[5] = -3;
//		}
		if ( ( enemy[13 + ( i * 20 )] <= 2 ) && ( enemy[13 + ( i * 20 )] > -2 ) )
		{
			enemy[13 + ( i * 20 )] = -3;
		}
		if ( enemy[13 + ( i * 20 )] < -8 )
		{
			enemy[13 + ( i * 20 )] = -8;
		}
		/* 地面判定 */
	}


	/* 画面端で落ちるのを防止 */
	e10 = enemy[13 + ( i * 20 )];
	if (  enemy[1+ ( i * 20 )] > ( 630 - size - size ) )
	{
		if ( enemy[13+ ( i * 20 )] < 0 )	/* 落下 */
		{
			e10 = 0;
		}
	}


	/* 今回の位置 */
	y1 = ( ( 0 - e10 ) * ( 0 - e10 ) * ( 0 - e10 ) );
//	player[1] = player[1] - ( y1 / 30 );


	enemy[2 + ( i * 20 )] = enemy[2 + ( i * 20 )] - ( y1 / 25 );
	px1 = ( enemy[1 + ( i * 20 )] + size ) / 32;
	px2 = ( enemy[1 + ( i * 20 )] + size ) / 32;
	py = ( 16 - ( ( enemy[2 + ( i * 20 )] + 28 ) / 32 ) );
	py2 = ( 16 - ( ( enemy[2 + ( i * 20 )] + 49 + 48 ) / 32 ) );
//	py = ( 16 - ( ( player[1] ) / 32 ) );

	if ( enemy[2 + ( i * 20 )] > 480 ) 
	{
		return;
	}

	if ( enemy[13 + ( i * 20 )] <= 0 )													/* 上り中は判定しない */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 219 ) ) 
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) )
		{
			enemy[2 + ( i * 20 )] = ( ( 16 - py ) * 32 ) - 16; 
			enemy[13 + ( i * 20 )] = 10;
		}
	}
	else		/* 上昇中 */
	{
		if ( enemy[1+ ( i * 20 )] < ( 630 - size - size ) )
		{
			px = ( enemy[1 + ( i * 20 )] + size ) / 32;
			py = ( 16 - ( ( enemy[2 + ( i * 20 )] - ( y1 / 25 ) + 16 + 48  ) / 32 ) );

			/* 地面判定 */
			if ( ( ( map1[ px + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px + ( ( py ) * 20 ) ] <= 119 ) )
			  || ( ( map1[ px + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px + ( ( py ) * 20 ) ] <= 219 ) ) )
			{
				enemy[13+ ( i * 20 )] = -3;
				enemy[12+ ( i * 20 )] = 0;
			}
		}

	}
	if ( enemy[2 + ( i * 20 )] <= -14 )
	{
		enemy[0 + ( i * 20 )] = 0;
	}

}


/* 移動後の座標のマスを返す */
long map1_item_j( long x, long y )
{
	int px ;
	int py ;
	int i;
	int rc;
	long bx;
	long by;
	
	px = ( x ) / 32;
	py = ( MapInfo[1] - 1 - ( ( y ) / 32 ) );

	if ( py <= 0 )
	{
		py = 0;
	}
	
	rc = map1[ px + ( ( py ) * MapInfo[0] ) ];
	
	/* アイテムとのあたり判定 */
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			/* プレイヤーとの当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( x ) )	/* 自機とのあたり判定 */
				&& ( ( x ) < (item[1 + ( i * item_data[2] )] + ( item_data[0] - 1 ) ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < ( y ) )
				&& ( ( y ) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
			{
				if (
//				     ( by == 2 ) 
				     ( by == 3 ) 
				  || ( by == 6 ) 
				  || ( ( by == 10 ) && ( bx == 7 ) ) 
				   )
				{
					rc = 101;
					break;
				}
			}
		}

	}


	return( rc );
	
	
	
	
}
long map1_item_j_Isitem( long x, long y, long item_index )
{
	int px ;
	int py ;
	int i;
	int rc;
	long bx;
	long by;
	
	px = ( x ) / 32;
	py = ( MapInfo[1] - 1 - ( ( y ) / 32 ) );

	if ( py <= 0 )
	{
		py = 0;
	}
	
	rc = map1[ px + ( ( py ) * MapInfo[0] ) ];
	
	/* アイテムとのあたり判定 */
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( ( item[( i * item_data[2] ) + 0 ] == 1 ) && ( item_index != i ) )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			/* プレイヤーとの当たり判定 */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( x ) )	/* 自機とのあたり判定 */
				&& ( ( x ) < (item[1 + ( i * item_data[2] )] + ( item_data[0] - 1 ) ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < ( y ) )
				&& ( ( y ) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
			{
				if (
//				     ( by == 2 ) 
				     ( by == 3 ) 
				  || ( by == 6 ) 
				  || ( ( by == 10 ) && ( bx == 7 ) ) 
				   )
				{
					rc = 101;
					break;
				}
			}
		}

	}


	return( rc );
	
	
	
	
}


void kane_set( long x, long y )
{
	long i;
	
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
			kane[6 + ( i * 10 )] = 6;
			kane[7 + ( i * 10 )] = 0;
			kane[8 + ( i * 10 )] = 0;
			kane[9 + ( i * 10 )] = 0;
			break;
		}
	}
}

void kane_disp(  )
{
	long i;
	
	for ( i = 0; i < 20; i++ )
	{
		if ( kane[0 + ( i * 10 )] == 1 )
		{
			kane[8 + ( i * 10 )]++;
			if ( kane[8 + ( i * 10 )] >= 10 )
			{
				kane[8 + ( i * 10 )] = 0;
				kane[7 + ( i * 10 )]++;
				if ( kane[7 + ( i * 10 )] >= 4 )
				{
					kane[7 + ( i * 10 )] = 0;
				}
			} 
			if ( ( ( kane[9 + ( i * 10 )] % 2 ) == 0 ) || ( kane[9 + ( i * 10 )] < 240 ) )
			{
				BltRect( 12 , kane[1 + ( i * 10 )] - d_x, ( 0 - kane[2 + ( i * 10 )] ) + 480 - 32 - d_y, 32 * 4 , 0, 32, 32 );
			}
			
			kane[9 + ( i * 10 )]++;
			if ( kane[9 + ( i * 10 )] >= 300 )
			{
				kane[0 + ( i * 10 )] = 0;
			} 
			kane[5 + ( i * 10 )]++;
			if ( kane[5 + ( i * 10 )] >= 10 )
			{
				kane[5 + ( i * 10 )] = 0;
			} 

			k_jmp( i );
			/* とった */
			if ( ( ( (kane[1 + ( i * 10 )]  ) < (player[0] + 10 ) )	/* 自機とのあたり判定 */
				&& ( (player[0] + 22 ) < (kane[1 + ( i * 10 )] + 32 ) )
				&& ( (kane[2 + ( i * 10 )] ) < (player[1] + 32 ) )
				&& ( (player[1] + 5 ) < ( kane[2 + ( i * 10 )] + 32 ) ) ) )
			{
				se_wav( 15 );
				player[8]++;
				if ( player[8] > save_data[6] )
				{
					player[8] = save_data[6];
				}
				kane[0 + ( i * 10 )] = 0;
			}
		}
	}
}
/* ジャンプＹ位置計算 */
void k_jmp( long i )
{
	long y1;
	long px1 ;
	long px2 ;
	long py ;
	long py2 ;
	long py3 ;

	if ( kane[6 + ( i * 10 )] == 10 ) 
	{
		return;
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
	
	/* 画面端で落ちるのを防止 */
	if ( ( kane[1 + ( i * 10 )] < 0 ) || ( kane[1 + ( i * 10 )] > 610 ) )
	{
		kane[6 + ( i * 10 )] = 0;
	}
	/* 今回の位置 */
	y1 = ( ( 0 - kane[6 + ( i * 10 )] ) * ( 0 - kane[6 + ( i * 10 )] ) * ( 0 - kane[6 + ( i * 10 )] ) );

	px1 = ( kane[1 + ( i * 10 )] + 16 ) / 32;
	px2 = ( kane[1 + ( i * 10 )] + 16 ) / 32;
	py = ( 16 - ( ( kane[2 + ( i * 10 )] + 28 ) / 32 ) );
	py2 = ( 16 - ( ( kane[2 + ( i * 10 )] + 49 + 48 ) / 32 ) );
	kane[2 + ( i * 10 )] = kane[2 + ( i * 10 )] - ( y1 / 25 );
	py3 = ( 16 - ( ( kane[2 + ( i * 10 )] + 32 + 32 + 16 ) / 32 ) );

	if ( kane[2 + ( i * 10 )] > 480 ) 
	{
		return;
	}

	if ( kane[6 + ( i * 10 )] <= 0 ) 													/* 上り中は判定しない */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 299 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 299 ) ) 
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) )
		{
			kane[2 + ( i * 10 )] = ( ( 16 - py ) * 32 ) - 16; 
			kane[6 + ( i * 10 )] = 10;
		}
	}
	else		/* 上昇中 */
	{
		/* 地面判定 */
		if ( ( ( map1[ px1 + ( ( py3 ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py3 ) * 20 ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py3 ) * 20 ) ] >= 200 ) && ( map1[ px1 + ( ( py3 ) * 20 ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * 20 ) ] >= 100 ) && ( map1[ px2 + ( ( py3 ) * 20 ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * 20 ) ] >= 200 ) && ( map1[ px2 + ( ( py3 ) * 20 ) ] <= 219 ) ) )
		{
			kane[6 + ( i * 10 )] = -1;
			kane[5 + ( i * 10 )] = 0;
		}
	}
	if ( kane[2 + ( i * 10 )] <= -14 )
	{
		kane[0 + ( i * 10 )] = 0;
	}

}

void p_jump_f_set( long x, long y )
{
	long i;
	
	for ( i = 0; i < 10; i++ )
	{
		if ( pjumpf[( i * 10 ) + 0 ] == 0 )
		{
			pjumpf[( i * 10 ) + 0 ] = 1;
			pjumpf[( i * 10 ) + 1 ] = x;
			pjumpf[( i * 10 ) + 2 ] = y;
			pjumpf[( i * 10 ) + 5 ] = 0;
			pjumpf[( i * 10 ) + 6 ] = 0;
			break;
		}
	}
}

void p_jump_f_disp( )
{
	long i;
	
	for ( i = 0; i < 10; i++ )
	{
		if ( pjumpf[( i * 10 ) + 0 ] == 1 )
		{
			BltRect( 5, pjumpf[( i * 10 ) + 1 ] - d_x, ( 0 - pjumpf[( i * 10 ) + 2 ] ) + MapInfo[3] - 32 - d_y , 128 + ( pjumpf[( i * 10 ) + 6 ] * 32 ), 0, 32, 32 );
			
			pjumpf[( i * 10 ) + 5 ]++;
			if ( pjumpf[( i * 10 ) + 5 ] >= 5 )
			{
				pjumpf[( i * 10 ) + 5 ] = 0;
				pjumpf[( i * 10 ) + 6 ]++;
				if ( pjumpf[( i * 10 ) + 6 ] >= 4 )
				{
					pjumpf[( i * 10 ) + 6 ] = 0;
					pjumpf[( i * 10 ) + 0 ] = 0;
				}
			}
		}
	}
}

void screen_BackupPlane( )
{
}

/* メニューの表示 */
void window_disp( )
{
	BltRect( 61, 100, 72 + ( 32 * demo[0] ), ( demo[1] / 10 ) * 16, 0 , 16, 16 );
	Blt( 60, 0, 0 );
	
	demo[1]++;
	if ( demo[1] >= 40 )
	{
		demo[1] = 0;
	}
}

/* メニューでのキー操作 */
void window_keys( )
{
	if ( IsPushKey( gameflag[0] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		demo[0]--;
		if ( demo[0] < 0 )
		{
			demo[0] = 2;
		}
	}
	else if ( IsPushKey( gameflag[1] ) )
	{
		soundPlaySe( EN_SE_SELECT );
		demo[0]++;
		if ( demo[0] > 2 )
		{
			demo[0] = 0;
		}
	}
	//	スペースキーが押される
	if ( IsPushOKKey( ) ) 
	{
		if ( demo[0] == 0 )
		{
			if ( player[9] != 0 ) //回転中
			{
				sn = 5;
			}
			else 
			{
				sn = 1;
			}
		}
		if ( demo[0] == 1 )
		{
			gameflag[71] = 1;
			sn = 10;
		}
		if ( demo[0] == 2 )
		{
			if ( gameflag[129] != 0 )	//ステージセレクトから開始
			{
				g_scene = EN_SN_STAGESELECT;
			}
			else 
			{
				g_scene = EN_SN_TITLE;	/* タイトルへ */
			}
//			gameflag[40] = 1;
			sn = 10;
		}
	}
	//Bが押される
	if ( IsPushCancelKey( ) )
	{
		if ( player[9] != 0 ) //回転中
		{
			sn = 5;
		}
		else 
		{
			sn = 1;
		}
	}

}


/* マップビューでのキー操作 */
void mapviwe_keys( void )
{
	if ( IsPressKey( gameflag[0] ) )	//上　
	{
		player[1] = player[1] + 2;
	}
	if ( IsPressKey( gameflag[1] ) )	//下　
	{
		player[1] = player[1] - 2;
	}
	if ( IsPressKey( gameflag[2] ) )	//左　
	{
		player[0] = player[0] - 2;
	}
	if ( IsPressKey( gameflag[3] ) )	//右　
	{
		player[0] = player[0] + 2;
	}

	if ( player[0] < 0 )	/* 画面左端判定 */
	{
		player[0] = 0;
	}
	if ( player[0] > ( MapInfo[2] - char_size[0] ) )	/* 画面右端判定 */
	{
		player[0] =  MapInfo[2] - char_size[0];
	}
	if ( player[1] <= 0 )	/* 画面下 */
	{
		player[1] = 0;
	}
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )	/* 画面上 */
	{
		player[1] = ( MapInfo[3] - char_size[1] );
	}

	//	スペースキーが押される
	if ( IsPushOKKey( ) ) 
	{
		g_scene = EN_SN_TITLE;	/* タイトルへ */
//		gameflag[40] = 1;
		sn = 10;
	}
	//Bが押される
	if ( IsPushCancelKey( ) )
	{
		g_scene = EN_SN_TITLE;	/* タイトルへ */
//		gameflag[40] = 1;
		sn = 10;
	}

}

/* 絶対値を返す */
long labs( long para )
{
	long rc;
	
	rc = para;
	
	if ( para < 0 )
	{
		rc = para * -1;
	}
	return( rc );
}

/* 魔法生成 */
void p_mgc_set( long muki , long p3 )
{
	long i;
	long k; 
	long ii;
	long rg;
	long max;
	
	rg = 0;
	
	if ( muki == 0 )
	{
		rg = ( 0 );
	}
	else if ( muki == 1 )
	{
		rg = ( 45 );
	}
	else if ( muki == 2 )
	{
		rg = ( 90 );
	}
	else if ( muki == 3 )
	{
		rg = ( 135 );
	}
	else if ( muki == 4 )
	{
		rg = ( 180 );
	}

	if ( p3 == 1 )
	{
		rg = rg * -1;
	}
 
	/* 発生位置X */
	/* 発生位置Y */

	max = 1;
	for ( i = 0; i < max; i++ )
	{

		k = 5;

		for ( ii = 0; ii < 40; ii++ )
		{
			if ( pmshot[ii * 20 + 2] == 0 )
			{
				pmshot[ii * 20 + 0] = funcSin( rg ) * k;			/* 弾速x */
				pmshot[ii * 20 + 1] = funcCos( rg ) * k;			/* 弾速y */
				pmshot[ii * 20 + 2] = 1;						/* 存在 */
				pmshot[ii * 20 + 3] = 0;						/* 種類 */
				pmshot[ii * 20 + 4] = 0 ;						/*  */
				pmshot[ii * 20 + 5] = ( player[0] ) << 16 ;			/* 初期位置の設定 */
				pmshot[ii * 20 + 6] = ( player[1] ) << 16 ;
				pmshot[ii * 20 + 7] = muki;						/* 方向 */
				
				pmshot[ii * 20 + 8] = 0;						/*  */
				pmshot[ii * 20 + 9] = 0 ;						/*  */
				pmshot[ii * 20 + 10] = 0 ;						/*  */
				break;
			}
		}
	}


}

void p_mgc_disp( )
{
	long ii;
	long f;
	long b;
	
	for ( ii = 0; ii < 40; ii++ )
	{
		if ( pmshot[ii * 20 + 2] == 1 )
		{
			
			f = 1;
			b = 230;
			
			
			BltRect( 4, ( pmshot[ii * 20 + 5] >> 16 ) - d_x, 480 - ( pmshot[ii * 20 + 6] >> 16 ) - 32 - d_y, 0, 96, 32, 32 );
//			BlendExBltRectW( 4, ( pmshot[ii * 20 + 5] >> 16 ) - d_x, 480 - ( pmshot[ii * 20 + 6] >> 16 ) - 32 - d_y, 0, 96, 32, 32 , f, b );

			pmshot[ii * 20 + 5] = pmshot[ii * 20 + 0] + pmshot[ii * 20 + 5];		/* 弾速x */
			pmshot[ii * 20 + 6] = pmshot[ii * 20 + 1] + pmshot[ii * 20 + 6];		/* 弾速x */
			
			if ( ( ( pmshot[ii * 20 + 5] >> 16 ) > 640 ) || ( ( pmshot[ii * 20 + 5] >> 16 ) < -32 ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* 存在無し */
			}
			if ( ( ( pmshot[ii * 20 + 6] >> 16 ) > 480 ) || ( ( pmshot[ii * 20 + 6] >> 16 ) < -32 ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* 存在無し */
			}
			
			if ( ( ( map1_item_j( ( pmshot[ii * 20 + 5] >> 16 ) + 16 , ( pmshot[ii * 20 + 6] >> 16 ) + 16 ) >= 100 )
			    && ( map1_item_j( ( pmshot[ii * 20 + 5] >> 16 ) + 16 , ( pmshot[ii * 20 + 6] >> 16 ) + 16 ) <= 220 ) ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* 存在無し */
				p_shot_f2_set( ( pmshot[5 + ii * 20] >> 16 ) + 15, ( pmshot[6 + ii * 20] >> 16 ) + 15, 0 );
				if ( pmshot[3 + ii * 20] == 2 )	/* スキルクラッシュショット */
				{
					p_shot_f_set( ( pmshot[5 + ii * 20] >> 16 ) + ( rand( ) % 32 ) - 16, ( pmshot[6 + ii * 20] >> 16 ) + ( rand( ) % 32 ) - 16, 0 );
					p_shot_f_set( ( pmshot[5 + ii * 20] >> 16 ) + ( rand( ) % 32 ) - 16, ( pmshot[6 + ii * 20] >> 16 ) + ( rand( ) % 32 ) - 16, 0 );
					p_shot_f_set( ( pmshot[5 + ii * 20] >> 16 ) + ( rand( ) % 32 ) - 16, ( pmshot[6 + ii * 20] >> 16 ) + ( rand( ) % 32 ) - 16, 0 );
				}
				else 
				{
					p_shot_f_set( ( pmshot[5 + ii * 20] >> 16 ) , ( pmshot[6 + ii * 20] >> 16 ), 0 );
				}
			}
			
			
		}
	}

}

void replay_input_save( void )
{
	long input_keys;
	input_keys = 0;
	
	/* キー処理は基本的にplayer[2]が何状態の時にキーを入れたらどうなるを記述していく */
	if ( IsPressKey( gameflag[2] ) )
	{
		input_keys = input_keys + 1;
	}
	else if ( IsPressKey( gameflag[3] ) )
	{
		input_keys = input_keys + 10;
	}
	
	if ( IsPressKey( gameflag[0] ) )
	{
		input_keys = input_keys + 100;
	}
	else if ( IsPressKey( gameflag[1] ) )
	{
		input_keys = input_keys + 1000;
	}
	
	//	スペースキーが押される
	if ( IsPressKey( gameflag[4] ) )
	{
		input_keys = input_keys + 10000;
	}
	
	//Bが押される
	if ( IsPressKey( gameflag[5] ) )
	{
		input_keys = input_keys + 100000;
	}
	
	//Bが押される
	if ( ( IsPushKey( gameflag[5] ) ) || ( IsPushKey( gameflag[0] ) && ( gameflag[133] == 1 ) ) )
	{
		input_keys = input_keys + 1000000;
	}
	/* 12ボタン　か　Ｃが押された */
//	if ( ( ( IsPushJoyKey(6) != 0 ) || ( IsPushJoyKey(12) != 0 ) || IsPushKey( gameflag[6] ) ) )
//	{
//		input_keys = input_keys + 10000000;
//	}
	
	replay[replay_time] = input_keys;
}

void replay_input_load( void )
{
	long i;
	long input_keys;
	input_keys = 0;
	
	for ( i = 0; i < 10 ; i++ )
	{
		replay_load_key[i] = 0 ;	
	}
	
	input_keys = replay[replay_time];
	
//	if ( input_keys >= 10000000 )
//	{
//		input_keys = input_keys - 10000000;
//		replay_load_key[7] = 1 ;	
//	}
	if ( input_keys >= 1000000 )
	{
		input_keys = input_keys - 1000000;
		replay_load_key[6] = 1 ;	
	}
	if ( input_keys >= 100000 )
	{
		input_keys = input_keys - 100000;
		replay_load_key[5] = 1 ;	
	}
	if ( input_keys >= 10000 )
	{
		input_keys = input_keys - 10000;
		replay_load_key[4] = 1 ;	
	}
	if ( input_keys >= 1000 )
	{
		input_keys = input_keys - 1000;
		replay_load_key[3] = 1 ;	
	}
	if ( input_keys >= 100 )
	{
		input_keys = input_keys - 100;
		replay_load_key[2] = 1 ;	
	}
	if ( input_keys >= 10 )
	{
		input_keys = input_keys - 10;
		replay_load_key[1] = 1 ;	
	}
	if ( input_keys >= 1 )
	{
		input_keys = input_keys - 1;
		replay_load_key[0] = 1 ;	
	}
}

void replay_file_save_w( void )
{

	long d_num;
	d_num = 1;
	sprintf(string,"replay/%d/replay_data_w_%d.dat", (int)stage, (int)save_data[3] );
	SaveFile( string, &replay[0], sizeof( replay ) );

}
void replay_file_save( long type )
{

	long d_num;
	d_num = replay_file_name;
	if ( type == 0 )
	{
		sprintf(string,"replay/%d/replay_data_%d.dat", (int)stage, (int)save_data[3] );
	}
	else
	{
		sprintf(string,"replay/%d/replay_data_j%d.dat", (int)stage, (int)save_data[3] );
	}
	SaveFile( string, &replay[0], sizeof( replay ) );
}

long replay_file_load( void )
{
	long rc ;
	long d_num;
	
	rc = 1;
	d_num = 1;
	
	if ( gameflag[125] == 0 )
	{
		sprintf( string, "replay/%d/replay_data_%d.dat", (int)stage, (int)save_data[3] );
	}
	else 
	{
		sprintf( string, "replay/%d/replay_data_j%d.dat", (int)stage, (int)save_data[3] );
	}
	if ( LoadFile( string, &replay[0], sizeof( replay ) ) )
	{
		rc = 0;
	}

	return( rc );
}


long GetKyori( long i1, long i2 )
{
	long rc = 0;
	
	rc = ( long )sqrt( ( i1 * i1 ) + ( i2 * i2 ) );
	
	return ( rc );
}

void debugdisp( void )
{
	if ( g_DebugDisp != 0 )
	{
		BltNumericImage( player[32], 8, 10, 10, 18, 0, 0, 10, 8 );	
		BltNumericImage( snack_count, 8, 10, 20, 18, 0, 0, 10, 8 );	
		BltNumericImage( player[20], 8, 10, 30, 18, 0, 0, 10, 8 );	
		BltNumericImage( player[21], 8, 10, 40, 18, 0, 0, 10, 8 );	
		BltNumericImage( map_rot_info, 8, 10, 50, 18, 0, 0, 10, 8 );	
		BltNumericImage( funcTan2( player[30],player[31] ), 8, 10, 60, 18, 0, 0, 10, 8 );	
		BltNumericImage( ( MOTatan(player[30] * 256,player[31] * 256) ), 8, 10, 70, 18, 0, 0, 10, 8 );	
	}
	// 線の描画
}







