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

// �֐��v���g�^�C�v
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
// �ϐ��錾
static long scene_exit;
static long sn = 0;									/* ��ʗp�ϐ������ς��邱�Ƃɂ���ĕ`��֐����̏�����ς���		*/

static long enm1_parameter[10 * 20] = 
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0���g�p */
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
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20���g�p */
};

static long enm2_parameter[10 * 20] = 
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0���g�p */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20���g�p */
};

static long enm3_parameter[10 * 20] = 
{
/*   HP   �� �U�� ���� ���� */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0���g�p */
	  1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20���g�p */
};

static long enm4_parameter[10 * 20] = 
{
/*   HP */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 0���g�p */
	  7,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 1�{�X */
	  7,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 2 */
	 30,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 3 */
	 27,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 4 */
     42,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 5 */
     30,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 6 */
      1,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 7 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 8 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 	/* 9 */
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0 	/* 20���g�p */
};

static long item_data[3] = { 32, 50, 20 };			/* �A�C�e���̏��@�T�C�Y�A�ő�z�u���A1�f�[�^�o�b�t�@�� */
static long enm_data[3] = { 0, 30, 30 };			/* �G�̏��@�\���A�ő�z�u���A1�f�[�^�o�b�t�@�� */
static long MapInfo[10] = 
{
	20 * 5									/* 0:�}�b�v��x�T�C�Y */
,	15 * 5									/* 1:�}�b�v��y�T�C�Y */
,	( 20 * 5 ) * 32							/* 2:�}�b�v��x�\���T�C�Y */
,	( 15 * 5 ) * 32							/* 3:�}�b�v��y�\���T�C�Y */
,   20										/* 4:�w�b�_�f�[�^���̃f�[�^�� */
};
static long char_size[10] = 
{
	32										/* char_size[0] ���� */
,	32										/* char_size[1] ���� */
,	10										/* char_size[2] ���肵�Ȃ������i������h�b�g�ŃJ�E���g�j */
,	( 32 - 10 )								/* char_size[3] ���肵�Ȃ����E�i������h�b�g�ŃJ�E���g�j */
,	8										/* char_size[4] �A�j���[�V�����p�^�[���� */
};

static long player[50];									/* �v���C���[�p�o�b�t�@ */
											/* player[0] X */
											/* player[1] Y */
											/* player[2] ��� */
											/* player[3] ���� */
											/* player[4] BMP���̕\���ʒuX */
											/* player[5] BMP���̕\���ʒuY */
											/* player[6] �͂ݒ��̈ړ��␳X */
											/* player[7] �͂ݒ��̈ړ��␳Y */
											/* player[8] ����HP */
											/* player[9] �G��͂�ł��� */
											/* player[10] �A�j���[�V�����t���[���J�E���^ */
											/* player[11] �A�j���[�V�����J�E���^ */
											/* player[12] �A�j���[�V�����t���[���w�� */
											/* player[13] �W�����v�t���[���J�E���^ */
											/* player[14] �W�����v�J�E���^ */
											/* player[15] �~�X�̏ꍇ��X */
											/* player[16] �~�X�̏ꍇ��Y */
											/* player[17] ���G���� */
											/* player[18] ���n���[�V�����p�J�E���^ */
											/* player[19] ��]�\�� */
											/* player[20] �}�b�v�̉�]�p�x */
											/* player[21] �}�b�v�̉�]�p�x�ڕW */
											/* player[22] ��]���͂̃E�G�C�g */
											/* player[23] ��]�p�x���� */
											/* player[24] secret item get �\������  */
											/* player[25] �{�^���������ăW�����v�����t���O */
											/* player[26] �����ԗ��������t���O�i���n�t�F�N�g�p�j */
											/* player[27] �͂񂾂Ƃ��ɓ��͂���Ă����L�[ */
											/* player[28] �ړ������[�V���� */
											/* player[29] ���΂ː�����ђ� */
											/* player[30] lastone�\�� */
											/* player[31] �J�b�g�C���̕\�� */
											/* player[32] �J�b�g�C���̎�� */
											/* player[33] �A�C�e�������������̈ړ��� */
											/* player[34]  */
											/* player[35]  */
											/* player[36]  */
											/* player[37]  */
											/* player[38]  */
static long dp_x;									/* �v���C���[�̕\���ʒu�i��ʓ��̑��΍��W�j */
static long dp_y;									/* �v���C���[�̕\���ʒu�i��ʓ��̑��΍��W�j */
static long dp_x2 = 80;								/* �v���C���[�̕\���ʒu�i��ʓ��̑��΍��W�j */
static long demo[10];
static uint32_t map1[10200];								/* ( MapInfo[0] * MapInfo[1] ) + MapInfo[4] �w�i�p�o�b�t�@ ���C���[1 */
static uint32_t map2[10200];							 	/* MapInfo[0] * MapInfo[1] �w�i�p�o�b�t�@ ���C���[2 */
static uint32_t mapfile[10200];							/* MapInfo[0] * MapInfo[1] �w�i�p�o�b�t�@ ���C���[2 */
static long map_data[20];							/* �w�b�_��� */
static long bak_cnt = 0;							/* �w�i�A�j���[�V�����p�J�E���^ */
static long bak_alldrow = 0;						/* �w�i�̕`����N���b�v���邩 */
static long d_x = 0;								/* �w�i�\���ʒu */
static long d_y = 0;								/* �w�i�\���ʒu */
static long kamera = 0;
//static long disp_data[60];							/* �Z�[�u�ꗗ */
static long next_px = 0;							/* ��ʐ؂�ւ����̃L�����ړ��΍� */
static long next_py = 0;

static long map_rot_info = 0;							/* �}�b�v�̌��� */
#ifdef GP2X
static const long atk_rr1 =30;						/* �r�̉�]���x */
#else
static const long atk_rr1 =5;						/* �r�̉�]���x */
#endif 
//long atk_rr = 360 / 32;						/* �r�̉�]���x */

static long stage = 0;								/* �X�e�[�W�ԍ� */
static long secretitemget = 0;						/* �B���A�C�e���̎擾 */
static uint32_t target_save[1024];

static long pshot[10 * 10];							/* �v���C���[�U���p��� */
static long pshotf[10 * 40];						/* �v���C���[�U���p��� */
static long pshotf2[10 * 80];						/* �v���C���[�U���p��� */
static long pmshot[20 * 40];						/* �v���C���[�U���p��� */
static long pjumpf[100];							/* �v���C���[�U���p��� */
static long item[20 * 50];							/* �A�C�e���p�o�b�t�@ */
static long item_wk[5*100];							/* �n�� ���̑��̃}�b�v��� */
//static long enemy[40 * 20];								/* �G���															*/
static long enemy[30 * 30];							/* enm_data[1] * enm_data[2] �G���	*/

static long mgc_e[10 * 20] ;						/* MGC�\�����														*/
static long p_ef[1000] ;							/* �ėp�o�b�t�@�i���Փ��j														*/
//static long life_a[5];								/* HP�A�j���[�V�����p */
static long kane[200];								/* �A�C�e���p�o�b�t�@ */

static long Jump_counts = 0;
static long snack_count = 0;
static long all_snack_count = 0;
static long save_data[512];							/* �ۑ���� */
static long test[5];
static long rayer[5];								/* �w�i�X�N���[���� */
static long play_time[5];
/* ���v���C�Q�O�� */
static uint32_t replay[60 * 60 * 10];	/* �t���[�����b���� */
static long replay_time = 1;
static long replay_time_MAX = 60 * 60 * 10;	/* �ő厞�� */
static long replay_load_key[10];
static long replay_file_name = 0;
static long replay_save_flag = 0;				/* �ۑ����s���� 1:���Ȃ� */
static long rrkey[5];								/* ���̓L�[���� */

//static long event_buff[100];
/* event_buff[0]	�����p����޳�\�� */
/* event_buff[1]	��\�� */
/* event_buff[2]	�����͑҂� */
/* event_buff[3]	wait */
/* event_buff[4]	���s�C�x���g�o�b�t�@�|�C���^ */
/* event_buff[5]	��\�� */
/* event_buff[7]	i */
/* event_buff[8]	player[2] */
/* event_buff[9]	player[3] */
/* event_buff[10]	��ʍX�V */
/* event_buff[11]	��ʉ��o */

/* TextLayer( 10 )�Ͳ���ĂŎg�p�i�Œ�j */
/* �v���[��80�`90�Ͳ���ĂŎg�p */
/* wav30�Ͳ���ĂŎg�p */
//static long file_handle = 0	;
static long one_event = 0;							/* �d�Ȃ��Ĕ�������C�x���g�̑O��d�Ȃ��Ă������̃t���O */
//static long start_plyer_disp = 1;					/* �J�n���ɕ\�����邩�t���O */
//static long start_effct_disp = 0;					/* �J�n���Ɍ��ʂ�\�����邩�t���O */


//----------------------------------------------------------------------
// ���C���֐�
void act_main( void )
{
	long exit_code;
	
	exit_code = 0;

	act_init( );		// ������
	
	while( scene_exit )
	{
//		KeyInput( );	// �L�[����
		
//		act_keys( );		// �L�[����
		act_drow( );		// �`��
		
		FPSWait( );		// �҂�

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	act_relese( );		// �I��
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
	bak_cnt = 0;							/* �w�i�A�j���[�V�����p�J�E���^ */
	bak_alldrow = 0;						/* �w�i�̕`����N���b�v���邩 */
	d_x = 0;								/* �w�i�\���ʒu */
	d_y = 0;								/* �w�i�\���ʒu */
	next_px = 0;							/* ��ʐ؂�ւ����̃L�����ړ��΍� */
	next_py = 0;
	stage = 0;								/* �X�e�[�W�ԍ� */
	Jump_counts = 0;
	snack_count = 0;
	all_snack_count = 0;
	replay_time = 1;
	replay_time_MAX = 60 * 60 * 10;	/* �ő厞�� */
	replay_save_flag = 0;				/* �ۑ����s���� 1:���Ȃ� */
	one_event = 0;							/* �d�Ȃ��Ĕ�������C�x���g�̑O��d�Ȃ��Ă������̃t���O */
	map_rot_info = 0;							/* �}�b�v�̌��� */
	secretitemget = 0;						/* �B���A�C�e���̎擾 */

//#if false
	memset( player, 0, sizeof( player ) );									/* �v���C���[�p�o�b�t�@ */
	memset( demo, 0, sizeof( demo ) );
	memset( map1, 0, sizeof( map1 ) );								/* �w�i�p�o�b�t�@ ���C���[1 */
	memset( map2, 0, sizeof( map2 ) );								/* �w�i�p�o�b�t�@ ���C���[2 */
	memset( map_data, 0, sizeof( map_data ) );
	memset( pshot, 0, sizeof( pshot ) );							/* �v���C���[�U���p��� */
	memset( pshotf, 0, sizeof( pshotf ) );						/* �v���C���[�U���p��� */
	memset( pshotf2, 0, sizeof( pshotf2 ) );						/* �v���C���[�U���p��� */
	memset( pmshot, 0, sizeof( pmshot ) );						/* �v���C���[�U���p��� */
	memset( pjumpf, 0, sizeof( pjumpf ) );							/* �v���C���[�U���p��� */
	memset( item, 0, sizeof( item ) );							/* �A�C�e���p�o�b�t�@ */
	memset( item_wk, 0, sizeof( item_wk ) );							/* �n�� ���̑��̃}�b�v��� */
	memset( enemy, 0, sizeof( enemy ) );								/* �G���															*/
	memset( mgc_e, 0, sizeof( mgc_e ) ) ;						/* MGC�\�����														*/
	memset( p_ef, 0, sizeof( p_ef ) ) ;							/* �ėp�o�b�t�@�i���Փ��j														*/
	memset( kane, 0, sizeof( kane ) );								/* �A�C�e���p�o�b�t�@ */
	memset( save_data, 0, sizeof( save_data ) );							/* �ۑ���� */
	memset( test, 0, sizeof( test ) );
	memset( rayer, 0, sizeof( rayer ) );								/* �w�i�X�N���[���� */
	memset( play_time, 0, sizeof( play_time ) );
	memset( replay, 0, sizeof( replay ) );	/* �t���[�����b���� */
	memset( replay_load_key, 0, sizeof( replay_load_key ) );
	memset( rrkey, 0, sizeof( rrkey ) );								/* ���̓L�[���� */
	memset( string, 0, sizeof( string ) );								/* ���̓L�[���� */
	memset( target_save, 0, sizeof( target_save ) );
//#endif

	/* ������擾��� */
	ResetGameFlag2();				/* �t�@�C���Ȃ� */
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
	
//	player[6] = save_data[8];	/* �X�L�� */
//	player[7] = save_data[7];	/* �n�[�g�̂����珊���� */
	player[8] = 1;	/* HP */
	stage = save_data[2];
	d_num = save_data[3]; 	/* ��� */
//	player[3] = save_data[4];	/* ���� */
	gameflag[120] = d_num;


	player[20] = 0;
	player[21] = 0;
	player[22] = 1;


	/* ���C���[�P */
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", ( int )stage , ( int )1, ( int )d_num );
	if ( 0 == LoadFile( string, map1, sizeof( map1 ) ) )
	{
		// File loaded OK
	}
	else 
	{
		/* �t�@�C�����Ȃ� */
		if ( gameflag[132] == 1 )	/* ���v���C */
		{
			g_scene = EN_SN_TITLE;	/* �^�C�g���� */
		}
		else 
		{
//			gameflag[40] = 5;	/* �G���f�B���O�� */
			g_scene = EN_SN_ENDING;	/* �^�C�g���� */
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
			if ( LoadBitmap(string,110 + i , 0 ) != 0 )					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
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
	if ( gameflag[128] != 0 )	//�}�b�v�r���[
	{
		item_set( 1, player[0], player[1], 0, d_num );
	}
	
	/* ���C���[�Q */
	ResetGameFlag2( );
	sprintf(string,"data/%d/%d_%d.map", ( int )stage , ( int )2, ( int )d_num );
	LoadFile( string, map2, sizeof( map2 ) );

	/* �A�C�e���z�u */
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
						//�L�����N�^�[
					}
					else 
					{ 
						item_set( mapfile[x + ( y * MapInfo[0] )], x * 32, ( ( MapInfo[1] - 1 - y ) * 32 ), x + ( y * MapInfo[0] ), d_num );
					}
				}
			}
		}
	}


	
	ResetGameFlag2();				/* �t�@�C���Ȃ� */
	sprintf( string,"data/%d/e%d_%d.map", ( int )stage , ( int )1, ( int )d_num );
	LoadFile( string, mapfile, sizeof( mapfile ) );

	/* �G�z�u */
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
	
	player[14] = 10;	/* �W�����v�J�E���^ */
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
			/* �t�@�C�����ǂ߂Ȃ����� */
			g_scene = EN_SN_TITLE;	/* �^�C�g���� */
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

	if ( gameflag[127] == 1 )	//�g�[�^���A�^�b�N
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
			if ( gameflag[137] > gameflag[135] )	//�g�[�^���A�^�b�N �N���A����
			{
				gameflag[137] = gameflag[135];
			}
			if ( gameflag[138] > gameflag[136] )	//�g�[�^���A�^�b�N �N���A�W�����v
			{
				gameflag[138] = gameflag[136];
			}
		}
	}


	sprintf(string,"image/player/ri%d.bmp", ( int )gameflag[122] );
	LoadBitmap(string,1,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/player/mgc1.bmp",2,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/player/atk1.bmp",3,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/player/atk2.bmp",4,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	LoadBitmap("image/player/atkf.bmp",5,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/player/cutin.bmp",6,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	sprintf(string,"image/map/map%d_1.bmp", ( int )stage );
	LoadBitmap(string,10,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	sprintf(string,"image/map/map%d_2.bmp", ( int )stage );
	LoadBitmap(string,11,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	sprintf(string,"image/map/item%d.bmp", ( int )stage );
	LoadBitmap(string,12,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���


	LoadBitmap("image/sys/map_f0.bmp",15,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/map_f1.bmp",16,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/map_f2.bmp",17,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/fonts2.bmp",18,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/sc.bmp",19,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	LoadBitmap("image/sys/p_data.bmp",20,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/skill.bmp",21,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/hp.bmp",22,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/hp2.bmp",23,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	
	LoadBitmap("image/sys/pause.bmp",24,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	/* 25�`30�̓C�x���g�Ŏg�p */

	/* 31�͉�ʌ��ʂŎg�p */
	
	LoadBitmap("image/enm/e32.bmp",40,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/enm/e48.bmp",41,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/enm/e64.bmp",42,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	
	LoadBitmap("image/enm/e_shot.bmp",50,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	LoadBitmap("image/player/font_d.bmp",51,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/player/hp.bmp",52,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	

	LoadBitmap("image/sys/menu.bmp",60,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/title/scl.bmp",61,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/window_item.bmp",62,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	LoadBitmap("image/player/arm.bmp",65,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/player/arm2.bmp",66,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/input.bmp",67,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/new.bmp",68,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/new2.bmp",69,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/mini_map.bmp",70,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/stagestart.bmp",71,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/bak/0.bmp",72,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/new3.bmp",73,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/scor.bmp",74,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/houkou.bmp",75,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	LoadBitmap("image/sys/waku.bmp",109,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/color.bmp",127,false);

	CreateSurface( 125, 640, 640 );
	SetPalette(127, 125);	// �p���b�g�̐ݒ�
	SetColorKey(125, true );	// �J���[�L�[�̐ݒ�
/*
	SaveBmp( -1, "bmp1.bmp" );
	SaveBmp( 125, "bmp125.bmp" );
	SaveBmp( 127, "bmp127.bmp" );
*/

	CreateSurface( 124, 640 * 5, 480 * 5 );
	SetPalette(127, 124);	// �p���b�g�̐ݒ�
	
	if ( gameflag[128] != 0 )	//�}�b�v�r���[
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
		replay_input_save( );		/* ���v���C�f�[�^�ۑ� */
	}
	else 
	{
		replay_input_load( );		/* ���v���C�f�[�^�Đ� */
	}
	replay_time++;
	if ( replay_time > replay_time_MAX )
	{
		replay_time = replay_time_MAX;	/* �ő厞�Ԃ��z�����A�ۑ����Ȃ� */
		replay_save_flag = 1;			/* �ۑ����Ȃ� */
	}

	for ( i = 0; i < 5; i++ )
	{
		rrkey[i] = 0;						/* ���̓L�[���� */
	}

	player[17]--;			/* ���G���� */
	if ( player[17] <= 0 )
	{
		player[17] = 0;
	}
	if ( player[9] == 0 )
	{
		jmp( );
	}
	
	
	if ( ( item_up( ) != -1 ) && ( player[14] == 10 ) )	/* �A�C�e���̏�ɏ���Ă��� */
	{
		player[1] = item_up( ); 
	}
	
	player[19] = 0;	// ��]�\���t���O

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
		
		if ( player[9] == 1 )	//��]��
		{
		}
		else
		{
			if ( ( ( IsPressKey( gameflag[2] ) ) && ( gameflag[132] == 0 ) )		// ��
		  || ( ( replay_load_key[0] == 1 ) && ( gameflag[132] == 1 ) ) )
			{
				
				player[3] = 1;	/* ���� */
				if ( player[2] == 0 )
				{
					player[10] = 0;	/* �A�j���[�V�����Ԋu�t���[���ݒ� */
					player[11] = 0;	/* �A�j���[�V�����J�E���^ */
					player[2] = 1;	/* ���� */
				}
				else if ( player[2] == 1 )
				{
					player[0] = player[0] - 2;	/* �L�����N�^�[�ړ� */
				}
				else if ( player[2] == 21 )
				{
					player[0] = player[0] - 2;	/* �L�����N�^�[�ړ� */
				}

			}
			else if ( ( ( IsPressKey( gameflag[3] ) ) && ( gameflag[132] == 0 ) )	// �E
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

		
		
		if ( player[28] != 0 )	/* �ړ��� */
		{
			player[0] = player[0] + player[28];
		}
		player[28] = 0;
		
		if ( player[29] > 0 )	/* �ړ��� */
		{
			player[0] = player[0] + ( player[29] * 1 );
			player[29] = player[29] - 1;
		}
		else if ( player[29] < 0 )
		{
			player[0] = player[0] + ( player[29] * 1 );
			player[29] = player[29] + 1;
		}
		
		/* �O��̈ʒu����ړ����� */
		if ( old_x > player[0] )
		{
			idou_l( );	/* ���ړ��̕ǔ��� */
		}
		else if ( old_x < player[0] )
		{
			idou_r( );	/* �E�ړ��̕ǔ��� */
		}
		player[33] = ( player[0] - old_x );
		
		
		if ( ( ( IsPressKey( gameflag[0] ) ) && ( gameflag[132] == 0 ) )
		  || ( ( replay_load_key[2] == 1 ) && ( gameflag[132] == 1 ) ) )
		{
			/* �����A���� */
//			if ( ( player[2] == 0 ) || ( player[2] == 1 ) )
//			{
//				item_event( );
//			}
		}
		else if ( ( ( IsPressKey( gameflag[1] ) ) && ( gameflag[132] == 0 ) )
		  || ( ( replay_load_key[3] == 1 ) && ( gameflag[132] == 1 ) ) )
		{
		}
		
		
		//	�X�y�[�X�L�[���������
		if ( ( ( IsPressKey( gameflag[4] ) )  && ( gameflag[132] == 0 ) ) 		/* �ړ����x�ቺ */
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
					player[2] = 2;		// ����

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

		kakudosa = ( player[21] - player[20] );		// ��]���I������
		if ( kakudosa == 0 )		// �����Ȃ��ꍇ�͉񂳂Ȃ�
		{
			if ( player[9] == 1 )
			{
				Jump_counts++;
				soundPlaySe( EN_SE_ATK1 );
				rotmap( player[21] );	// ��]
				
				player[10] = 0;
				player[11] = 0;
				player[2] = 0;		// ƭ����

				player[14] = 0;		// ����
				player[13] = 0;
				
				player[1] = player[1] + 8;	// �����蔻�肪�����`�Ȃ̂ŕ�������

				sn = 1;
				player[9] = 0;
				
				switch( player[21] )
				{
				case 90:
					map_rot_info = map_rot_info - 1;							/* �}�b�v�̌��� */
					break;
				case 180:
					map_rot_info = map_rot_info + 2;							/* �}�b�v�̌��� */
					break;
				case 270:
					map_rot_info = map_rot_info + 1;							/* �}�b�v�̌��� */
					break;
				default:
					break;
				}
				if ( map_rot_info < 0 )	// ������
				{
					map_rot_info = map_rot_info + 4;
				}
				if ( map_rot_info > 3 )	// ������
				{
					map_rot_info = map_rot_info - 4;
				}

			}
		}
		else 
		{
			if ( kakudosa == 0 )		// �����Ȃ��ꍇ�͉񂳂Ȃ�
			{
			}
			else if ( kakudosa < 0 ) // �ڕW�p�x�ɑ΂��Č��ݒn�̓v���X
			{
				if ( -180 > kakudosa )  // 180�x�����Ă���ꍇ�͋t��]
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
			else if ( kakudosa > 0 ) // �ڕW�p�x�ɑ΂��Č��ݒn�̓}�C�i�X
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
			// 360�x���z�����ꍇ��0�x�ɃI�t�Z�b�g
			if ( player[20] < 0 )
			{
				player[20] = player[20] + 360;
			}
			if ( player[20] >= 360 )
			{
				player[20] = player[20] - 360;
			}
		}
		
		//B���������
		if ( ( ( ( IsPushKey( gameflag[5] ) ) || ( IsPushKey( gameflag[0] ) && ( gameflag[133] == 1 ) ) ) && ( gameflag[132] == 0 ) )
		  || ( ( replay_load_key[6] == 1 ) && ( gameflag[132] == 1 ) ) )
		{
			if ( player[9] == 0 )	// ����ł��Ȃ�
			{
				if ( ( player[2] != 11 ) && ( player[2] != 31 ) && ( player[14] == 10 ) )	/* �n��ōU���A�_���[�W����Ȃ� */
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
						/* �A�C�e���ɏ���Ă��Ȃ��ꍇ�͂��������g���C�ʒu */
						if ( item_up( ) == -1 )
						{
							player[15] = player[0];
							player[16] = player[1];
						}
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	/* �� */
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
				if ( ( player[14] > 0 ) && ( player[25] == 1 ) )	/* �r���ŗ��� */
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
	
	/* 12�{�^���@���@�b�������ꂽ */
	if ( IsPushKey( gameflag[6] ) )
	{
		if ( sn != 5 )	//��]���ł͂Ȃ�
		{ 
			sn = 4;
			demo[0] = 0;
			demo[1] = 0;
		}
	}
	
	/* �X�L���V���[�g�J�b�g�E�B���h�E */
	if ( IsPushKey( gameflag[7] ) )
	{
	}



	if ( player[0] < 0 )	/* ��ʍ��[���� */
	{
		player[0] = 0;
		/*
		�C�x���g����save_data[9]��ݒ肷�邱�ƂŁA�ꎞ�I�ɃX�N���[���s�Ƃ���B
		�{�X��ȂǂɎg�p
		*/
		if ( save_data[9] == 1 )	/* �X�N���[���s�� */
		{
		}
		/* �A�C�e���ɏ���Ă���ꍇ�̓X�N���[�����Ȃ� */
/*
		else if ( ( stage == 7 ) && ( item_up( ) != -1 ) )
		{
		}
*/
		else 
		{
			if ( player[1] <= 460 )					/* �L�����N�^�[���������ʓ� */
			{
				if ( map_data[4] == 1 )			/* �X�N���[����񂠂� */
				{
					wait_scl( 2, map_data[5] );	/* �X�N���[�� */
				}
				else if ( map_data[4] == 2 )	/* �X�e�[�W�ړ���񂠂� */
				{
					end_scl( map_data[5] );		/* �X�e�[�W�ړ� */
				}
			}
		}
	}
	if ( player[0] > ( MapInfo[2] - char_size[0] ) )	/* ��ʉE�[���� */
	{
		player[0] =  MapInfo[2] - char_size[0];
		if ( save_data[9] == 1 )	/* �X�N���[���s�� */
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
	if ( player[1] <= 0 )	/* ��ʉ� */
	{
		if ( save_data[9] == 1 )	/* �X�N���[���s�� */
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
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )	/* ��ʏ� */
	{
		if ( save_data[9] == 1 )	/* �X�N���[���s�� */
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
	if ( player[2] == 0 )	/* �j���[�g���� */
	{
		player[12] = 10;
	}
	if ( player[2] == 1 )	/* ���� */
	{
		player[12] = 10;
	}
	if ( player[2] == 2 )	/* ���� */
	{
		player[12] = 5;
	}
	if ( player[2] == 11 )	/* �U�� */
	{
		player[12] = 2;
	}
	if ( player[2] == 21 )	/* �� */
	{
		player[12] = 5;
	}
	if ( player[2] == 31 )	/* ���� */
	{
		player[12] = 10;
	}
	if ( player[2] == 33 )	/* �N���A */
	{
		player[12] = 10;
	}
	if ( player[2] == 61 )	/* ����� */
	{
		player[12] = 10;
	}
}


/* �������̏ꍇ�̓W�����v�͑��� */
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
	/* �������� */

	if ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 319 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 319 ) 
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 419 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 419 )  
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 318 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 318 )    
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 418 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 418 )  
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 719 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 719 )
	  || ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] == 718 ) || ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] == 718 ) )
	{
//		player[14] = player[14] + 1; 		/* �W�����v�t���O */
//		if ( player[14] >= 9 )
//		{
//			player[14] = 9;
//		}
	}
	else 
	{
	}
}

/* �W�����v�x�ʒu�v�Z */
void jmp( )
{
	long y1;
	long px ;
	long px1 ;
	long px2 ;
	long py ;
	long py3 ;
	
	/* �W�����v�t���[���J�E���g */
	player[13]++;
	if ( player[13] >= 10 )
	{
		player[13] = 0;
	}
	
	if ( player[2] == 41 )	/* �͂����� */
	{
		player[18] = 0;			/* ���݂���W�����v */
		player[28] = 0;			/* ������Ă��� */

		player[14] = 10;
		return;
	}
	
	/* ����̈ʒu */
	px = ( player[0] + ( char_size[0] / 2 ) ) / 32;
	px1 = ( player[0] + char_size[2] ) / 32;
	px2 = ( player[0] + char_size[3] ) / 32;
//		py = ( 16 - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );
	py = ( MapInfo[1] - ( ( player[1] + ( char_size[1] - 5 ) ) / 32 ) );
	
	if ( player[14] == 10 ) 	/* �n�� */
	{
		
		/* 100 �` 200�͒n�� */
		/* �������n�ʂł͂Ȃ� */
		if ( ( ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) ) 
		  && ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) ) 
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) )
		  && ( !( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		  && ( !( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) ) )
		  || ( ( ( player[1] ) % 32 ) != 0 ) )
		{
			if ( item_up( ) != -1 )	/* �A�C�e���̏�ɏ���Ă��� */
			{
				player[1] = item_up( ); 
				player[14] = 10;
				return;
			}
			
			/* �������Ȃ�󒆏�Ԃֈڍs */
			if ( ( player[2] == 0 )
			  || ( player[2] == 1 ) )
			{
				player[10] = 0;
				player[11] = 0;
				player[2] = 21;		/* �� */
			}
			player[14] = -1;			/* �����J�n */
			player[13] = 0;
			
			if ( player[2] == 31 )	/* �_���[�W�� */
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
		/* �������Ȃ�󒆏�Ԃֈڍs */
		if ( ( player[2] == 0 )
		  || ( player[2] == 1 ) )
		{
			player[10] = 0;
			player[11] = 0;
			player[2] = 21;		/* �� */
		}
		player[22] = 0;					/* ���J�E���^ */
	}

	/* 10�t���[����1��Y���W�v�Z */
	if ( player[13] == 0 )	
	{
		player[14] = player[14] - 2;	/* �W�����v�͌��� */

		/* ���_�t�߂�-1�����J�n�Ƃ��� */
		if ( ( player[14] <= 2 ) && ( player[14] > -2 ) )
		{
			player[14] = -1;
		}

		if ( player[14] < -4 )	/* �ő�������ݒ� */
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
	
	/* �������蓙�̔w�i�ɂ���ė������x���ς��ꍇ�͔��肷�� */
	/* ����̈ʒu */
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
		if ( player[14] > 0 ) /* �㏸�� */
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

		player[1] = player[1] - ( y1 / 20 );	/* Y�ړ� */
	}


	/* �����A�㏸�\���� */
	/* ��ʊO�̏ꍇ�͍s��Ȃ� */ 
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		return;
	}
	py3 = ( MapInfo[1] - ( ( player[1] + char_size[1] + 32 ) / 32 ) );

	/* ���� */
	if ( player[14] <= 0 )													/* ��蒆�͔��肵�Ȃ� */
	{
		/* �n�ʔ��� */
		if ( ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * MapInfo[0] ) ] <= 219 ) ) 
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 119 ) ) 
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * MapInfo[0] ) ] <= 619 ) ) )
		{
			/* ���n */
			if ( player[8] > 0 )	/* HP������ꍇ�͌��ʉ���炷 */
			{ 
				soundPlaySe( EN_SE_LANDING );
				se_wav( 9 );
			}
			if ( ( player[2] != 31 ) && ( player[2] != 32 ) )	/* �_���[�W������Ȃ� */
			{
				player[2] = 0;							/* ������Ԃ� */
				player[11] = 0;							/* �A�j���[�V�����J�E���^�N���A */
			}
			player[1] = ( ( MapInfo[1] - py ) * 32 ); 		/* ���n�����}�X��Y���W�ɍ��킹�� */
			player[14] = 10;								/* �W�����v�͂�n��ɐݒ� */

			player[18] = 0;			/* ���݂���W�����v */
			player[28] = 0;			/* ������Ă��� */

			p_jump_f_set( player[0], player[1] );
		}
		else 
		{
			if ( item_up( ) != -1 )						/* �A�C�e���̏�ɏ���Ă��� */
			{
				soundPlaySe( EN_SE_LANDING );
				se_wav( 9 );
				if ( ( player[2] != 31 ) && ( player[2] != 32 ) )	/* �_���[�W������Ȃ� */
				{
					player[2] = 0;							/* ���n */
					player[11] = 0;							/* �A�j���[�V�����J�E���^�N���A */
				}
				player[1] = item_up( ); 
				player[14] = 10;

				player[18] = 0;			/* ���݂���W�����v */
				player[28] = 0;			/* ������Ă��� */

				p_jump_f_set( player[0], player[1] );
			}
		}
	}
	else		/* �㏸�� */
	{
		/* �n�ʔ��� */
		if ( ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px1 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 100 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 119 ) )
		  || ( ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] >= 200 ) && ( map1[ px2 + ( ( py3 ) * MapInfo[0] ) ] <= 219 ) ) )
		{
			/* �����Ԃ����� */
			player[13] = 0;
			player[14] = -3;		/* ���� */
		}
		else 
		{
			if ( item_up2( ) != -1 )	/* �A�C�e���ɓ����Ԃ��� */
			{
				player[1] = item_up2( ); 
				player[13] = 0;
				player[14] = -3;
			}
		}
	}
	/* ��ʊO�A���ɍs���� */
	if ( player[1] <= -14 )
	{
		if ( map_data[2] == 0 )		/* �X�N���[�����Ȃ��ꍇ�̓_���[�W */
		{
			if ( player[8] > 0 )			/* HP������ */
			{ 
				if ( player[17] == 0 )	/* ���G���Ԃ����� */
				{
					player[17] = 120;	/* ���G���� */
					player[8] = player[8] - 1;/* �_���[�W */
					se_wav( 1 );	/* �_���[�W���ʉ� */
				}
				if ( player[8] > 0 )		/* HP������ */
				{ 
					player[0] = player[15];	/* ���g���C�ʒu�Ɉړ� */
					player[1] = player[16];
					wait_scl2( save_data[3] ,player[0], player[1] );	/* �Ó]�߂� */
					
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

/* �������ւ̈ړ����� */
void idou_l( )
{
	long px ;
	long py1 ;
	long py2 ;
	long bx ;
	long by ;

	long i;


	/* ����̈ʒu */
	/* player[29]���o�l������ѕ␳ */
	px = ( player[0] + char_size[2] + player[29] ) / 32;
	py1 = ( MapInfo[1] - ( ( player[1] + 32 + ( char_size[1] / 2 )  ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + 32 + 5 ) / 32 ) ); 						/* �����T�h�b�g�����ꏊ�𔻒肷�� */
	/* ��ʊO�͈�ԏ�Ŕ��� */ 
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		py1 = 0;
		py2 = 0;
	}

	/* 502�͂�����@501�͂����� */
	/* �ǂɖ��܂����ꍇ�͕ǍۂɈړ� */
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
			/* �v���C���[�Ƃ̓����蔻�� */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0]  + player[29] + char_size[3] ) )	/* ���@�Ƃ̂����蔻�� */
				&& ( (player[0] + player[29] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + char_size[1] - 5 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
			{
				if (
				     ( by == 6 ) /* �ړ��s�A�C�e�� */
				   )
				{
					//�X�C�b�`�u���b�N�̏ꍇ�͖��܂�
//					player[0] = item[( i * item_data[2] ) + 1 ] + item_data[0] - char_size[2];
					px = ( player[0] + 16 ) / 32;
					player[0] = px * 32 - char_size[2];

					player[29] = 0;
					player[19] = 1;	//
				}
				if (
				     ( by == 3 ) /* �ړ��s�A�C�e�� */
				   )
				{
					//�ړ��u���b�N�̏ꍇ�͒[�Ɉʒu�C��
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
/* �����̍��E�Ɉړ��\���H */
void idou_r( )
{
	long px ;
	long py1 ;
	long py2 ;
	long bx ;
	long by ;

	long i;

	/* ����̈ʒu */
	/* player[29]���o�l������ѕ␳ */
	px = ( player[0] + char_size[3] + player[29] ) / 32;
	py1 = ( MapInfo[1] - ( ( player[1] + 32 + ( char_size[1] / 2 ) ) / 32 ) );
	py2 = ( MapInfo[1] - ( ( player[1] + 32 + 5 ) / 32 ) ); /* �����T�h�b�g�����ꏊ�𔻒肷�� */
	/* ��ʊO�͈�ԏ�Ŕ��� */ 
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )
	{
		py1 = 0;
		py2 = 0;
	}

	/* 502�͂�����@501�͂����� */
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
			/* �v���C���[�Ƃ̓����蔻�� */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + player[29] + char_size[3] ) )	/* ���@�Ƃ̂����蔻�� */
				&& ( (player[0] + player[29] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + 32 ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + char_size[1] - 5 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) ) )
			{
				if (
				     ( by == 6 ) /* �ړ��s�A�C�e�� */
				   )
				{
					//�X�C�b�`�u���b�N�̏ꍇ�͖��܂�
//					player[0] = item[( i * item_data[2] ) + 1 ] - char_size[3];
					px = ( player[0] + 16 ) / 32;
					player[0] = px * 32 + 9;

					player[29] = 0;
					player[19] = 2;
				}
				if (
				     ( by == 3 ) /* �ړ��s�A�C�e�� */
				   )
				{
					//�ړ��u���b�N�̏ꍇ�͒[�Ɉʒu�C��
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
	//�ϐ��錾
	//-------------------------------------------------------------

	//�w�i�N���A
//	ClearSecondary();

	switch( sn )							/* sn�ɂ���ĕ`�悷����̂�ς��� */
	{
	case 0:		//�J�n�f��
		bg_disp();
		bakdisp1( );
		bakdisp2( );
		item_disp( );
		item_line( );
		enm_disp( );
		playerdisp( );
		snack_counter_disp( ); // ����J�E���^
		mapdisp( );
		stage_start( );
		debugdisp( );
		//-----------------------------------------------------------------------------------
		break;
	case 1 :		//�A�N�V����
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
		snack_counter_disp( ); // ����J�E���^
		mapdisp( );
		debugdisp( );		/* �f�o�b�O��� */
		stage_endj( );
		//-----------------------------------------------------------------------------------
		break;
	case 2 :		//�N���A�f��
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
		snack_counter_disp( ); // ����J�E���^
		mapdisp( );
		stage_claer( );
		playerdisp( );
		debugdisp( );
		//-----------------------------------------------------------------------------------
		break;
	case 3 :		//�Q�[���I�[�o�[
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
		snack_counter_disp( ); // ����J�E���^
		mapdisp( );
		stage_end( );
		debugdisp( );
		//-----------------------------------------------------------------------------------
		break;
	case 4 :		//�A�C�e��
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
		snack_counter_disp( ); // ����J�E���^
		mapdisp( );
		window_disp( );
		debugdisp( );
		//-----------------------------------------------------------------------------------
		break;
	case 5 :		//��]
		//-----------------------------------------------------------------------------------
		act_keys( );
		bg_disp();
		bak_rot( );
//		minimap_disp( );
		snack_counter_disp( ); // ����J�E���^
		mapdisp( );
		debugdisp( );		/* �f�o�b�O��� */
		break;
	case 6 :		//�}�b�v�r���[
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
		snack_counter_disp( ); // ����J�E���^
		mapdisp( );
		debugdisp( );		/* �f�o�b�O��� */
		stage_endj( );
		break;
	default :	//	�ǂ̏����ɂ������Ȃ��ꍇ
		
		ClearSecondary();
		/* ��ʐ؂�ւ����̕\���΍� */
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

	//��ʂ̕`��
	halt( );
//	SDL_Flip( g_screen );	// �`��
	//�L�[���͌���
	KeyInput();				
	
}

/* �ꎞ�t�@�C���ۑ� */
void save_file_w( )
{
	long i;

	SaveGameFlag("save/config");

	
	ResetGameFlag2( );
//	save_data[7] = player[7];	/* �n�[�g�̂����珊���� */
	save_data[5] = player[8];	/* HP */
	save_data[2] = stage;
	
	save_data[0] = player[0];	/* �w */
	save_data[1] = player[1];	/* �x */
	save_data[4] = player[3];	/* ���� */
//	save_data[8] = player[6];	/* �X�L�� */

	for ( i = 0; i < 512; i++ )
	{
		gameflag2[i] = save_data[i];
	}
	SaveGameFlag2( "save/work.sav");
	
	/* �A�C�e���擾��� */
	ResetGameFlag2();				
	for ( i = 0; i < 500; i++ )
	{
		gameflag2[i] = item_wk[i];
	}
	SaveGameFlag2("save/item_wk.sav");

}


/**********************************/
/* �v���C���[�̏�Ԍ��菈��       */
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
		/* 8�p�^�[����1�p�^�[���ڂɖ߂� */
		if ( player[11] >= char_size[4] )
		{
			player[11] = 0;
			if ( player[2] == 21 )	/* �� */
			{
				player[11] = ( char_size[4] - 1 - 3 );		/* 5�ɖ߂� */
			}
			if ( player[2] == 11 )	/* �U���I�� */
			{
				player[2] = 0;
				if ( player[14] != 10 )	/* �� */
				{
					player[2] = 21;
				}
			}
			if ( player[2] == 31 )	/* �_���[�W */
			{
				player[2] = 0;
				if ( player[14] != 10 )	/* �� */
				{
					player[2] = 21;
				}
			}
			if ( player[2] == 32 )	/* �_�E���Q�[���I�[�o�[ */
			{
				player[2] = 32;
				player[11] = ( char_size[4] - 1 );		/* �ŏI�p�^�[���̂܂� */
			}
			if ( player[2] == 33 )	/* �N���A */
			{
				player[2] = 33;
				player[11] = ( char_size[4] - 1 - 3 );		/* 5�ɖ߂� */
			}
		}
	}
	fram_set( );
	
	/* ��ʑ��΍��W�ł̕\���ʒu */
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
	if ( player[18] > 0 )	/* ���n���[�V�����\�� */
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

	
	if ( player[2] == 1 )		/* ���� */
	{
		player[4] = 0;
		player[5] = 1;
	}
	if ( player[2] == 2 )		/* ���� */
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
		if ( player[14] < 0 )	/* �����Ă� */
		{
			player[5] = 7;
		}
	}
	if ( player[2] == 31 )	/* �_���[�W */
	{
		player[4] = 0;
		player[5] = 5;

	}
	if ( player[2] == 32 )	/* �Q�[���I�[�o�[ */
	{
		player[4] = 0;
		player[5] = 5;

	}
	if ( player[2] == 33 )	/* �N���A */
	{
		player[4] = 0;
		player[5] = 8;

	}
	
	if ( gameflag[128] == 0 )	//�}�b�v�r���[�ł͂Ȃ�
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
//�w�i�\��
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
	
	//��ʔw�i����ʑS�̂ɓ]��
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

	/* �w�i�A�j���[�V����ON */
	Blt( 112, 0, 0 );						/* �w�i�X�N���[�����o */
//	Blt( 110, 0 - rayer[0] - d_x, 0 - d_y );				/* �w�i�X�N���[�����o */
//	Blt( 110, 640 - rayer[0] - d_x, 0 - d_y );				/* �w�i�X�N���[�����o */
//	Blt( 111, 0 - rayer[1] - d_x, 0 - d_y );				/* �w�i�X�N���[�����o */
//	Blt( 111, 640 - rayer[1] - d_x, 0 - d_y );				/* �w�i�X�N���[�����o */
//	Blt( 112, 0 - rayer[2] - d_x, 0 - d_y );				/* �w�i�X�N���[�����o */
//	Blt( 112, 640 - rayer[2] - d_x, 0 - d_y );				/* �w�i�X�N���[�����o */
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
	
	/* stage13,14,17�͑��d�X�N���[�� */
	/* �n�ʕ\�� */
	for ( x = 0; x < MapInfo[1]; x++ )
	{
		for ( y = 0; y < MapInfo[1]; y++ )
		{

			if ( ( ( ( d_x - 32 ) <= ( x * 32 ) ) 
			  && ( ( d_y - 32 ) <= ( y * 32 ) )
			  && ( ( d_x + 320 + 32 ) >= ( x * 32 ) )
			  && ( ( d_y + 240 + 32 ) >= ( y * 32 ) ) )
			  || ( bak_alldrow == 1 )	 					/* �w�i�̕`����N���b�v���邩 */
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
			  || ( bak_alldrow == 1 )	 					/* �w�i�̕`����N���b�v���邩 */
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

	bak_alldrow = 1;						/* �w�i�̕`����N���b�v���邩 */

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

	bak_alldrow = 0;						/* �w�i�̕`����N���b�v���邩 */

	d_x = bak_d_x;
	d_y = bak_d_y;

//	SaveBmp( 125, "temp.bmp" );

}
void bak_rot( void )
{
	BltRectRotZoom( 125, 160, 120, 0, 0, 640, 640, player[20], 1, 0 );
}



/* �v�`�h�s���X�N���[�� */
void wait_scl( long type, long d_num )
{
/*  
	0:��	1:��	2:��	3:�E
	��݂��ރt�@�C���m�n
*/
	long i;
	long x;
	long y;

	se_wav( 14 );
	screen_BackupPlane( );

	/* �o�b�t�@�N���A */
	for ( i = 0; i < 100; i++ )
	{
		p_ef[i * 5] = 0;						/* ���� */
	}
	for ( i = 0; i < 40; i++ )
	{
		pmshot[i * 20 + 2] = 0;						/* ���� */
	}
	for ( i = 0; i < 10; i++ )
	{
		pshot[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 40; i++ )
	{
		pshotf[i * 10 + 0] = 0 ;	
	}
	/* �o�b�t�@�N���A */
	for ( i = 0; i < 50; i++ )
	{
		item[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 20; i++ )
	{
		enemy[i * 20 + 0] = 0 ;					/* ���݂��ĂȂ� */
	}
	for ( i = 0; i < 20; i++ )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* ���݂��ĂȂ� */
	}
	for ( i = 0; i < 20; i++ )
	{
		kane[i * 10 + 0] = 0 ;					/* ���݂��ĂȂ� */
	}

	/* ����ʃo�b�t�@�ǂݍ��� */
/*
	for ( i = 0 ; i < 2 ; i++ )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	�o�b�N�A�b�v�v���[�������Blt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	�o�b�N�A�b�v�v���[���̎g�p�I��

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
			LoadBitmap(string,110 + i , 0 );					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
		}
		else 
		{
			ReleaseBitmap(110 + i);
		}
	}
	
	
	
	/* ���C���[�Q */
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


	/* �A�C�e���z�u */
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

	ResetGameFlag2();				/* �t�@�C���Ȃ� */
	sprintf( string,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( string );	/* �G�z�u */
	/* �G�z�u */
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
	
	/* ��X�N���[�� */
	if ( type == 0 )
	{
		player[1] = 0;
	}
	/* ���X�N���[�� */
	if ( type == 1 )
	{
		player[1] = ( 480 - 32 - 16 );
	}
	/* ���X�N���[�� */
	if ( type == 3 )
	{
		player[0] = 0;
	}
	/* ���X�N���[�� */
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
			BltFromBackupPlane();		//	�o�b�N�A�b�v�v���[�������Blt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	�o�b�N�A�b�v�v���[���̎g�p�I��
*/
	/* ���g���C�ꏊ�ݒ� */
	player[15] = player[0];
	player[16] = player[1];

	player[9] = 0;			/* �͂�ł���G�͏����� */

}

/* �v�`�h�s���X�N���[�� */
void wait_scl2( long d_num ,long init_x, long init_y )
{
/*  
	0:��	1:��	2:��	3:�E
	��݂��ރt�@�C���m�n
*/
	long i;
	long x;
	long y;

//	se_wav( 14 );
//	screen_BackupPlane( );

	/* �o�b�t�@�N���A */
	for ( i = 0; i < 100; i++ )
	{
		p_ef[i * 5] = 0;						/* ���� */
	}
	for ( i = 0; i < 40; i++ )
	{
		pmshot[i * 20 + 2] = 0;						/* ���� */
	}
	for ( i = 0; i < 10; i++ )
	{
		pshot[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 40; i++ )
	{
		pshotf[i * 10 + 0] = 0 ;	
	}
	/* �o�b�t�@�N���A */
	for ( i = 0; i < 50; i++ )
	{
		item[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 20; i++ )
	{
		enemy[i * 20 + 0] = 0 ;					/* ���݂��ĂȂ� */
	}
	for ( i = 0; i < 20; i++ )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* ���݂��ĂȂ� */
	}
	for ( i = 0; i < 20; i++ )
	{
		kane[i * 10 + 0] = 0 ;					/* ���݂��ĂȂ� */
	}

	/* ����ʃo�b�t�@�ǂݍ��� */
/*
	for ( i = 0 ; i < 2 ; i++ )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	�o�b�N�A�b�v�v���[�������Blt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	�o�b�N�A�b�v�v���[���̎g�p�I��

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
			LoadBitmap(string,110 + i , 0 );					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
		}
		else 
		{
			ReleaseBitmap(110 + i);
		}
	}
	
	
	
	/* ���C���[�Q */
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


	/* �A�C�e���z�u */
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

	ResetGameFlag2();				/* �t�@�C���Ȃ� */
	sprintf( string,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( string );	/* �G�z�u */
	/* �G�z�u */
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
			BltFromBackupPlane();		//	�o�b�N�A�b�v�v���[�������Blt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
//	DisableBackupPlane();	//	�o�b�N�A�b�v�v���[���̎g�p�I��
//	screen_BackupPlane( );
*/
	/* ���g���C�ꏊ�ݒ� */
	player[15] = player[0];
	player[16] = player[1];


}

/* �v�`�h�s���X�N���[��(reload��p�A�G�̍Ĕz�u���s��Ȃ�) */
void wait_scl3( )
{
/*  
	0:��	1:��	2:��	3:�E
	��݂��ރt�@�C���m�n
*/
	long i;
	long x;
	long y;
	long d_num;
	
	d_num = save_data[3];

//	se_wav( 14 );
//	screen_BackupPlane( );

	/* �o�b�t�@�N���A */
	for ( i = 0; i < 100; i++ )
	{
		p_ef[i * 10] = 0;						/* ���� */
	}
	for ( i = 0; i < 40; i++ )
	{
		pmshot[i * 20 + 2] = 0;						/* ���� */
	}
	for ( i = 0; i < 10; i++ )
	{
		pshot[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 40; i++ )
	{
		pshotf[i * 10 + 0] = 0 ;	
	}
	/* �o�b�t�@�N���A */
	for ( i = 0; i < 50; i++ )
	{
		item[i * 10 + 0] = 0 ;	
	}
	for ( i = 0; i < 20; i++ )
	{
		if ( enemy[0 + ( i * 20 )] == 1 )					/* ���݂��ĂȂ� */
		{
			enemy[1 + ( i * 20 )] = enemy[14 + ( i * 20 )] ;					/* ���݂��ĂȂ� */
			enemy[2 + ( i * 20 )] = enemy[15 + ( i * 20 )] ;					/* ���݂��ĂȂ� */
		}
	}
	for ( i = 0; i < 20; i++ )
	{
		mgc_e[i * 10 + 0] = 0 ;					/* ���݂��ĂȂ� */
	}

	/* ����ʃo�b�t�@�ǂݍ��� */
/*
	for ( i = 0 ; i < 2 ; i++ )
	{
		for ( j = 0 ; j < 2; j++ )
		{
			BltFromBackupPlane();		//	�o�b�N�A�b�v�v���[�������Blt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	�o�b�N�A�b�v�v���[���̎g�p�I��

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
			LoadBitmap(string,110 + i , 0 );					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
		}
		else 
		{
			ReleaseBitmap(110 + i);
		}
	}
	
	
	
	/* ���C���[�Q */
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


	/* �A�C�e���z�u */
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

	ResetGameFlag2();				/* �t�@�C���Ȃ� */
	sprintf( string,"data/%d/e%d_%d.map", (int)stage , (int)1, (int)d_num );
	LoadGameFlag2( string );	/* �G�z�u */
	/* �G�z�u */
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
			BltFromBackupPlane();		//	�o�b�N�A�b�v�v���[�������Blt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
*/
//	DisableBackupPlane();	//	�o�b�N�A�b�v�v���[���̎g�p�I��
//	screen_BackupPlane( );

	/* ���g���C�ꏊ�ݒ� */
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
	case 0:		// �ړ�����
	case 360:		// �ړ�����
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
	case 0:			// �ړ�����
	case 360:		// �ړ�����
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
	// �v���C���[�̍��W��ϊ�
	rotchange( player[0] + ( char_size[0] / 2 ), player[1] + ( char_size[1] / 2 ), rot, &wx, &wy );

	player[0] = wx - ( char_size[0] / 2 ) - 1;	//�ǂɖ��܂��Ă��܂����ߕ␳
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
			case 2:	// �����
			case 3:
			case 4:
				if ( item[7 + ( i * item_data[2] )] >= 0 )
				{
					k = item[7 + ( i * item_data[2] )];	// �x�_�̎擾
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
			/* �G�̃T�C�Y�擾 */
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
			if ( enemy[3 + ( i * enm_data[2] )] == 4 )	/* 4�{�X */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 5 )	/* 5�{�X */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 6 )	/* 6�{�X */
			{
				size = 32;
			}
			rotchange( enemy[( i * enm_data[2] ) + 1 ] + ( size / 2 ), enemy[( i * enm_data[2] ) + 2 ] + ( size / 2 ), rot, &wx, &wy );
			enemy[( i * enm_data[2] ) + 1 ] = wx - ( size / 2 );
			enemy[( i * enm_data[2] ) + 2 ] = wy - ( size / 2 );
		}
	}
	//�p�[�e�B�N���̈ړ�
	for ( i = 0; i < 80; i++ )
	{
		if ( pshotf2[i * 10 + 2] != 0 )
		{
			rotchange( ( pshotf2[i * 10 + 5] >> 16 ) + 16, ( pshotf2[i * 10 + 6] >> 16 ) + 16, rot, &wx, &wy );
			pshotf2[i * 10 + 5] = ( wx ) << 16 ;	/* �����ʒu�̐ݒ� */
			pshotf2[i * 10 + 6] = ( wy ) << 16 ;
		}
	}
	
#ifdef GP2X
	replay_time = replay_time + 15;
#endif 

}

void rotchangemap( long x1, long y1, long deg, long *x2, long *y2 )
{
	long rad; // ��]�p�x(���W�A��)

	rad = 360 - deg;

	long cx = MapInfo[1] / 2; // �}�b�v�̒��S���W(X)
	long cy = MapInfo[1] / 2; // �}�b�v�̒��S���W(Y)

	long dx = x1 - cx; // ���S����̋���(X)
	long dy = y1 - cy; // ���S����̋���(Y)

	long tmpX = dx*funcCos(rad) - dy*funcSin(rad); // ��]
	long tmpY = dx*funcSin(rad) + dy*funcCos(rad); 
	
	tmpX = tmpX + ( 1 << 15 );
	tmpY = tmpY + ( 1 << 15 );

	*x2 = ( cx + ( tmpX >> 16 ) ); // ���̍��W�ɃI�t�Z�b�g����
	*y2 = ( cy + ( tmpY >> 16 ) );

}

void rotchange( long x1, long y1, long deg, long *x2, long *y2 )
{
	long rad; // ��]�p�x(���W�A��)

	rad = deg;

	long cx = MapInfo[3] / 2; // �}�b�v�̒��S���W(X)
	long cy = MapInfo[3] / 2; // �}�b�v�̒��S���W(Y)

	long dx = x1 - cx; // ���S����̋���(X)
	long dy = y1 - cy; // ���S����̋���(Y)

	long tmpX = dx*funcCos(rad) - dy*funcSin(rad); // ��]
	long tmpY = dx*funcSin(rad) + dy*funcCos(rad); 
	
	tmpX = tmpX + ( 1 << 15 );
	tmpY = tmpY + ( 1 << 15 );

	*x2 = ( cx + ( tmpX >> 16 ) ); // ���̍��W�ɃI�t�Z�b�g����
	*y2 = ( cy + ( tmpY >> 16 ) );

}

//-----------------------------------------------------------------------------------
// ����J�E���^�[�\��
void snack_counter_disp()
{
	long px;
	long py;
	long x;
	long dx;
	long dy;
	long i;
	long old_count;
	// ����J�E���g
	
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
		//last one�̕\��
		player[30] = 180;
	}
	if ( ( old_count != snack_count ) && ( snack_count == 0 ) )
	{
		//last one�̕\��
		player[30] = 0;
	}
	// ����
	px = 10;
	py = 18;
	// �����T�C�Y
	dx = 10;
	dy = 8;
	// 'rest' �c�肨���
	x = 0;
	BltRect( 18, 105, 2, 0, 72, 100, 8 );	/* replay */
	// �c��̐�
//	x = x + dx * 2;
//	px = px + rand(3)-1; // �Ԃ�Ԃ�
//	py = py + rand(3)-1; // �Ԃ�Ԃ�
//	BltNumericImage2( count, 2, 140 + rand(3)-1, 2 + rand(3)-1, 18, 0, 0, 10, 8 );
	BltNumericImage2( snack_count, 2, 155, 2, 18, 0, 0, 10, 8 );
}

//-----------------------------------------------------------------------------------
//�~�j�}�b�v�̕\��
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
	// ����
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
	// �v���C���[
	x = px + 0      + ((player[0] / 32 + 0) * size);
	y = py + height - ((player[1] / 32 + 1) * size);
	BltRect( 127, x, y, 127, 191, size, size );
	// �����
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
//���\��
void mapdisp()
{
	int stage_hosei;
	
	stage_hosei = 0;
	if ( stage == 2 )
	{
		stage_hosei = 50;
	}

	long wk;
	/* �v���C���[��ԕ\�� */
//	Blt( 20, 0, 0 );	/* �g */
	if ( gameflag[128] != 0 )	//�}�b�v�r���[
	{
		BltRect( 18, 10, 15, 0, 136, 100, 8 * 3 );	/* mapviwe */
	}
	if ( gameflag[132] == 1 )
	{
		if ( stage != 0 )
		{
			BltRect( 18, 10, 15, 0, 32, 100, 8 );	/* replay */
		}
		/* �L�[���� */
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
		if ( gameflag[127] == 1 )	//�g�[�^���A�^�b�N
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

		if ( gameflag[127] == 1 )	//�g�[�^���A�^�b�N
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

		BltNumericImage( play_time[0], 2, 110, 230, 18, 0, 0, 10, 8 );	/* ���� */
		BltNumericImage( play_time[1], 2, 80, 230, 18, 0, 0, 10, 8 );	/* ���� */
		BltNumericImage( play_time[2], 2, 50, 230, 18, 0, 0, 10, 8 );	/* ���� */

		if ( gameflag[127] == 1 )	//�g�[�^���A�^�b�N
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

	// �����̕\��
	BltRect( 75, 280, 122, 0 + ( map_rot_info * 32 ), 0, 32, 32 );	/*  */

	//�����i�̕\��
	BltRect( 6, 240, 240 - 96, 0, 64 , 96, 96 );	/*  */
	if ( ( sn == 1 ) || ( sn == 5 ) || ( sn == 4 ) )
	{
		if ( snack_count != all_snack_count )
		{
			BltRect( 6, 240 + 32, 240 - 96 + 32, 0 + ( ( ( save_data[3] - 1 ) % 10 ) * 32 ), 160 + ( ( ( save_data[3] - 1 ) / 10 ) * 32 ) , 32 - ( ( snack_count * 100 ) / ( ( all_snack_count * 100 ) / 32 ) ), 32 );	/*  */
		}
	}

	//�J�b�g�C���̕\��
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

//	BltRect( 22, 24, 10, 0, 0, 16 * save_data[6], 12 );			/* �ő�g�o */
//	BltRect( 23, 24, 10, 0, life_a[1] * 12 , 16 * player[8], 12 );	/* ���݂g�o */
//	/* hp�A�j���[�V���� */
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
/* bgm�Đ� */
/* �X�e�[�W�̊J�n�ɌĂ� */
void bgm_midi( long BgmWavNo )
{

	
}


//-----------------------------------------------------------------------------------
/* se�Đ� */
void se_wav(long SeWavNo)
{
	
}



//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//�J�n
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
			BltFromBackupPlane();		//	�o�b�N�A�b�v�v���[�������Blt
			Blt( 15 + i , 0, 0 );
			halt;
		}
	}
	DisableBackupPlane();	//	�o�b�N�A�b�v�v���[���̎g�p�I��
*/

	KeyInput( );	// �L�[����
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
	
	if ( player[8] <= 0 )		/* ���C�t�O */
	{

		player[2] = 32;	/* �_�E�����[�V���� */
		player[10] = 0;	/* �_�E�����[�V���� */
		player[11] = 0;	/* �_�E�����[�V���� */
		
		
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
	
	if ( gameflag[127] == 0 )	//�g�[�^���A�^�b�N
	{
		if ( ( gameflag[300 + save_data[3] + stage_hosei] > Jump_counts ) )
		{
			if ( gameflag[132] == 0 )
			{
				// �V�L�^
				Blt( 69, 0, 0 );
				newrecode = 1;
			}
		}
		if ( ( gameflag[200 + save_data[3] + stage_hosei] > play_time[4] ) )
		{
			if ( gameflag[132] == 0 )
			{
				// �V�L�^
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
		//�ڕW�^�C��
		if ( target_save[200 + save_data[3] + stage_hosei] >= play_time[4] )
		{
			BltRect( 61, 20, 138, 0, 128 , 20, 20 );
		}
		//�ڕW��]
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
			BltRect( 18, 190, 170, 0, 176, 200, 8 );	/* �^�C�� */
			BltRect( 61, 20, 170, 0, 128 , 20, 20 );
		}
		else 
		{
			BltRect( 18, 190, 170, 0, 168, 200, 8 );	/* �^�C�� */
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
	//�����i�̎擾1
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
			if ( gameflag[127] == 1 )	//�g�[�^���A�^�b�N
			{
				gameflag[135] = play_time[4];
			}
			else 
			{
				replay_file_save_w( );
				if ( gameflag[200 + save_data[3] + stage_hosei] > play_time[4] )
				{
					gameflag[200 + save_data[3] + stage_hosei] = play_time[4];	/* �X�R�A�ۑ� */
				
					replay_file_save( 0 );
				}

				if ( gameflag[300 + save_data[3] + stage_hosei] > Jump_counts )
				{
					gameflag[300 + save_data[3] + stage_hosei] = Jump_counts;	/* �X�R�A�ۑ� */
				
					replay_file_save( 1 );
				}
				
				if ( secretitemget == 1 )
				{
					gameflag[400 + save_data[3] + stage_hosei] = 1;
				}
			}
			
			if ( gameflag[129] != 0 )	//�X�e�[�W�Z���N�g����J�n
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
					if ( gameflag[127] == 0 )	//�g�[�^���A�^�b�N�ł͂Ȃ�
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
			if ( gameflag[129] != 0 )	//�X�e�[�W�Z���N�g����J�n
			{
				gameflag[40] = 1;
				g_scene = EN_SN_STAGESELECT;
			}
			else 
			{
				save_data[3]++;
			}
			if ( ( gameflag[124] == 1 ) || ( stage == 0 ) )	/* ���v���C�n�m�d */
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
		if ( player[8] <= 0 )		/* ���C�t�O */
		{
			gameflag[136]++;
			if ( gameflag[136] > 999 )	/* �~�X�J�E���g */
			{
				gameflag[136] = 999;
			}
		}
		if ( gameflag[127] == 1 )	//�g�[�^���A�^�b�N
		{
			play_time[4] = 1000000 + ( play_time[2] * 10000 ) + ( play_time[1] * 100 ) + ( play_time[0] );
			gameflag[135] = play_time[4];
		}
		gameflag[71] = 1;
		sn = 10;
	}
}

/* �}�b�v�̒[�ɐG��ăX�e�[�W�ړ� */
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
			pshot[( i * 10 ) + 3 ] = houkou;	/* ���E */
			pshot[( i * 10 ) + 4 ] = muki;	/* ���� */
			pshot[( i * 10 ) + 5 ] = 0;
			pshot[( i * 10 ) + 6 ] = 0;
			pshot[( i * 10 ) + 7 ] = type;
			pshot[( i * 10 ) + 8 ] = 0;		/* �����蔻����WX */
			pshot[( i * 10 ) + 9 ] = 0;		/* �����蔻����WX */
			
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
			/* �ʒu�␳ */	
			pshot[( i * 10 ) + 1 ] = player[0];
			pshot[( i * 10 ) + 2 ] = player[1];
			
			if ( pshot[( i * 10 ) + 3 ] == 0 )
			{
				if ( pshot[( i * 10 ) + 4 ] == 0 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] + 16;
					pshot[( i * 10 ) + 8 ] = 0;		/* �����蔻����WX */
					pshot[( i * 10 ) + 9 ] = 0;		/* �����蔻����WX */
				}
				if ( pshot[( i * 10 ) + 4 ] == 1 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] + 10;
					pshot[( i * 10 ) + 8 ] = 0;		/* �����蔻����WX */
					pshot[( i * 10 ) + 9 ] = 0;		/* �����蔻����WX */
				}
				if ( pshot[( i * 10 ) + 4 ] == 2 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] - 16;
					pshot[( i * 10 ) + 8 ] = 0;		/* �����蔻����WX */
					pshot[( i * 10 ) + 9 ] = 0;		/* �����蔻����WX */
				}
				if ( pshot[( i * 10 ) + 4 ] == 3 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] + 5;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
					pshot[( i * 10 ) + 8 ] = 0;		/* �����蔻����WX */
					pshot[( i * 10 ) + 9 ] = 0;		/* �����蔻����WX */
				}
				if ( pshot[( i * 10 ) + 4 ] == 4 )
				{
					pshot[( i * 10 ) + 1 ] = player[0] - 16;
					pshot[( i * 10 ) + 2 ] = player[1] - 43;
					pshot[( i * 10 ) + 8 ] = 0;		/* �����蔻����WX */
					pshot[( i * 10 ) + 9 ] = 0;		/* �����蔻����WX */
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
	
	/* �����ʒuX */
	/* �����ʒuY */

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
				pshotf2[ii * 10 + 0] = funcSin( rg ) * k;		/* �e��x */
				pshotf2[ii * 10 + 1] = funcCos( rg ) * k;		/* �e��y */
				pshotf2[ii * 10 + 2] = 1;				/* ���� */									
				pshotf2[ii * 10 + 3] = 1;				/* ���� */
				pshotf2[ii * 10 + 4] = 0 ;			/* ������܂ł̃t���[���� */
				pshotf2[ii * 10 + 5] = ( x ) << 16 ;	/* �����ʒu�̐ݒ� */
				pshotf2[ii * 10 + 6] = ( y ) << 16 ;
				pshotf2[ii * 10 + 7] = 0 ;			/* ������܂ł̃t���[���� */
				pshotf2[ii * 10 + 8] = 10 ; 			/* ������܂ł̃t���[���� */
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
				pshotf2[ii * 10 + 5] = pshotf2[ii * 10 + 0] + pshotf2[ii * 10 + 5];		/* �e��x */
				pshotf2[ii * 10 + 6] = pshotf2[ii * 10 + 1] + pshotf2[ii * 10 + 6];		/* �e��x */
				pshotf2[ii * 10 + 3] = 1;				/* ���� */
				pshotf2[ii * 10 + 7]++ ;			/* ������܂ł̃t���[���� */
				if ( pshotf2[ii * 10 + 7] >= pshotf2[ii * 10 + 8] )
				{
					pshotf2[ii * 10 + 7] = 0;
					pshotf2[ii * 10 + 4] = pshotf2[ii * 10 + 4] + 1 ;			/* ������܂ł̃t���[���� */
					if ( pshotf2[ii * 10 + 4] >= 2 )
					{
						pshotf2[ii * 10 + 2] = 0;				/* ���ݖ��� */									
					}
				}
			}
			else
			{
				BltRect( 5, ( pshotf2[ii * 10 + 5] >> 16 ) - d_x, ( 0 - ( pshotf2[ii * 10 + 6] >> 16 ) ) + MapInfo[3] - 32 - d_y, pshotf2[ii * 10 + 4] * 32, 32, 32, 32 );
				pshotf2[ii * 10 + 5] = pshotf2[ii * 10 + 0] + pshotf2[ii * 10 + 5];		/* �e��x */
				pshotf2[ii * 10 + 6] = pshotf2[ii * 10 + 1] + pshotf2[ii * 10 + 6];		/* �e��x */
				pshotf2[ii * 10 + 3] = 1;				/* ���� */
				pshotf2[ii * 10 + 7]++ ;			/* ������܂ł̃t���[���� */
				if ( pshotf2[ii * 10 + 7] >= pshotf2[ii * 10 + 8] )
				{
					pshotf2[ii * 10 + 7] = 0;
					pshotf2[ii * 10 + 4] = pshotf2[ii * 10 + 4] + 1 ;			/* ������܂ł̃t���[���� */
					if ( pshotf2[ii * 10 + 4] >= 4 )
					{
						pshotf2[ii * 10 + 2] = 0;				/* ���ݖ��� */									
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
		//�X�C�b�`�̕`�揇�͑O
		for ( i = 0; i < item_data[1]; i++ )
		{
			if ( item[( i * item_data[2] ) + 0 ] == 0 )
			{
				item[( i * item_data[2] ) + 0 ] = 1;
				item[( i * item_data[2] ) + 1 ] = x;
				item[( i * item_data[2] ) + 2 ] = y;
				item[( i * item_data[2] ) + 3 ] = type;
				item[( i * item_data[2] ) + 4 ] = 0;	// �x�_����̑��ΈʒuX
				item[( i * item_data[2] ) + 5 ] = 0;	// �x�_����̑��ΈʒuY
				item[( i * item_data[2] ) + 6 ] = 0;	/* �ړ��J�E���^ */
				item[( i * item_data[2] ) + 7 ] = -1;	/* �x�_�̃|�C���^ */
				item[( i * item_data[2] ) + 8 ] = 0;	/* �ړ���X */
				item[( i * item_data[2] ) + 9 ] = 0;	/* �ړ���Y */
				item[( i * item_data[2] ) + 10 ] = -1;	/* �G�̃|�C���^ */
				

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
				item[( i * item_data[2] ) + 4 ] = 0;	// �x�_����̑��ΈʒuX
				item[( i * item_data[2] ) + 5 ] = 0;	// �x�_����̑��ΈʒuY
				item[( i * item_data[2] ) + 6 ] = 0;	/* �ړ��J�E���^ */
				item[( i * item_data[2] ) + 7 ] = -1;	/* �x�_�̃|�C���^ */
				item[( i * item_data[2] ) + 8 ] = 0;	/* �ړ���X */
				item[( i * item_data[2] ) + 9 ] = 0;	/* �ړ���Y */
				item[( i * item_data[2] ) + 10 ] = -1;	/* �G�̃|�C���^ */
				

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
			  || ( bak_alldrow == 1 )	 					/* �w�i�̕`����N���b�v���邩 */
			   )
			{

				BltRect( 12 , item[1 + ( i * item_data[2] )] - d_x, ( 0 - item[2 + ( i * item_data[2] )] ) + MapInfo[3] - item_data[0] - d_y, item_data[0] * bx, by * item_data[0], item_data[0], item_data[0] );
			}
			/* �v���C���[�Ƃ̓����蔻�� */
			if ( ( ( (item[1 + ( i * item_data[2] )] + 0 ) <= (player[0] + char_size[3] ) )	/* ���@�Ƃ̂����蔻�� */
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
					//������u���b�N
					//�L�����N�^�[���n�ʂɂ���
					if ( player[33] > 0 ) 
					{
						if ( ( player[14] == 10 ) && ( item[( i * item_data[2] ) + 4 ] == 10 ) )
						{
							/* �ǂ���Ȃ������� */
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
						/* �ǂ���Ȃ������� */
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
			if ( ( ( (item[1 + ( i * item_data[2] )] + 5 ) <= (player[0] + char_size[3] ) )	/* ���@�Ƃ̂����蔻�� */
				&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] - 5 ) )
				&& ( (item[2 + ( i * item_data[2] )]  + 5 ) < (player[1] + ( char_size[1] - 10 ) ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] - 5 ) ) )
				&& ( sn == 1 ) )
			{
				//�n�ʂɂ���
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
						//��]��
						soundPlaySe( EN_SE_PAWA );
						sn = 5;
						player[20] = 0;
						player[21] = 0;
						player[22] = 0;

						player[10] = 0;
						player[11] = 0;
						player[4] = 0;
						player[5] = 3;
						player[2] = 2;		// ����

						bak_make( );


						player[22] = 10;
						player[20] = player[21];
						//����Ă���A�C�e���ɂ���ĉ�]����������
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
					//��o�l
					soundPlaySe( EN_SE_JUMP );
					/* �A�C�e���ɏ���Ă��Ȃ��ꍇ�͂��������g���C�ʒu */
					if ( player[2] != 31 )
					{
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	/* �� */
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
					//���o�l
					soundPlaySe( EN_SE_JUMP );
					/* �A�C�e���ɏ���Ă��Ȃ��ꍇ�͂��������g���C�ʒu */
/*
					if ( player[2] != 31 )
					{
						player[10] = 0;
						player[11] = 0;
						player[2] = 21;	// �� 
					}
*/
					if ( ( by == 10 ) && ( bx == 4 ) )
					{
						player[29] = 20;	// ���o�l�ӂ���ї�
					}
					else 
					{
						player[29] = -20;	// ���o�l�ӂ���ї�
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
				case 2:	// �����
				case 3:
				case 4:
					if ( item[( i * item_data[2] ) + 7 ] >= 0 )	// �x�_�����݂���
					{
						if ( item[6 + ( i * item_data[2] )] > 0 )
						{
							/* �v���C���[�Ƃ̓����蔻�� */
							if ( ( ( (item[1 + ( i * item_data[2] )] + item[( i * item_data[2] ) + 8 ] ) <= (player[0] + char_size[3] ) )	/* ���@�Ƃ̂����蔻�� */
								&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] + item[( i * item_data[2] ) + 8 ] ) )
								&& ( (item[2 + ( i * item_data[2] )]  + item[( i * item_data[2] ) + 9 ] ) < (player[1] + ( char_size[1] ) ) )
								&& ( (player[1] ) < ( item[2 + ( i * item_data[2] )] + item_data[0] + item[( i * item_data[2] ) + 9 ] ) ) )
								&& ( by == 3 )
							   )
							{
								//�ړ��I��
//								item[6 + ( i * item_data[2] )] = -1;
							}
							else 
							{
								item[( i * item_data[2] ) + 1 ] = item[( i * item_data[2] ) + 1 ] + item[( i * item_data[2] ) + 8 ] ;
								item[( i * item_data[2] ) + 2 ] = item[( i * item_data[2] ) + 2 ] + item[( i * item_data[2] ) + 9 ] ;
								item[( i * item_data[2] ) + 6 ]--;
							}
							
							if ( item[6 + ( i * item_data[2] )] == 1 )	// �ړ��t���[��������~�̏ꍇ
							{
								k = item[7 + ( i * item_data[2] )];	// �x�_�̎擾
								item[( i * item_data[2] ) + 1 ] = ( item[( k * item_data[2] ) + 1 ] + item[4 + ( i * item_data[2] )] ) ;
								item[( i * item_data[2] ) + 2 ] = ( item[( k * item_data[2] ) + 2 ] + item[5 + ( i * item_data[2] )] ) ;
								item[( i * item_data[2] ) + 6 ] = 0;
							}
							if ( item[( i * item_data[2] ) + 10 ] >= 0 )	// �G�̃|�C���^�����݂���
							{
								k = item[10 + ( i * item_data[2] )];	// �x�_�̎擾
								enemy[1 +( k * enm_data[2] )] = item[1 + ( i * item_data[2] )];
								enemy[2 +( k * enm_data[2] )] = item[2 + ( i * item_data[2] )];
							}
						}
					}
					else 
					{
						if ( item[( i * item_data[2] ) + 7 ] == -1 )		// ���񌟍�
						{
							//�x�_������
							item[( i * item_data[2] ) + 7 ] = -2;	//����
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
											// �x�_����̑��Έʒu��ۑ�
											item[( i * item_data[2] ) + 4 ] = item[( i * item_data[2] ) + 1 ] - item[( ii * item_data[2] ) + 1 ];	/* ����p�o�b�t�@ */
											item[( i * item_data[2] ) + 5 ] = item[( i * item_data[2] ) + 2 ] - item[( ii * item_data[2] ) + 2 ];	/* ����p�o�b�t�@ */
											item[( i * item_data[2] ) + 7 ] = ii;
										}
										break;
									default:
										break;
									}
									if ( item[( i * item_data[2] ) + 7 ] != -2 )
									{
										// �x�_����������
										break;
									}
								}
							}
						}
						if ( by == 4 )	// �G�ړ��A�C�e��
						{
							if ( item[( i * item_data[2] ) + 10 ] == -1 )		// ���񌟍�
							{
								//�x�_������
								item[( i * item_data[2] ) + 10 ] = -2;	//����
								for ( ii = 0; ii < enm_data[1]; ii++ )
								{
									if ( enemy[0 +( ii * enm_data[2] )] == 1 )
									{
										//�������W�ɓG������ꍇ�|�C���^�̎擾
										if ( 
										     ( enemy[1 +( ii * enm_data[2] )] == item[( i * item_data[2] ) + 1 ] )
										  && ( enemy[2 +( ii * enm_data[2] )] == item[( i * item_data[2] ) + 2 ] )
										   )
										{
											item[( i * item_data[2] ) + 10 ] = ii;	/* ����p�o�b�t�@ */
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
						if ( gameflag[128] == 0 )	//�}�b�v�r���[�ł͂Ȃ�
						{
							//��
							item_jmp( i );
						}
					}
					break;
				case 5:
					// �X�C�b�`
					k = 0;
					if ( ( ( (item[1 + ( i * item_data[2] )] + 0 ) <= (player[0] + char_size[3] ) )	/* ���@�Ƃ̂����蔻�� */
						&& ( (player[0] + char_size[2] ) < (item[1 + ( i * item_data[2] )] + item_data[0] - 0 ) )
						&& ( (item[2 + ( i * item_data[2] )]  + 0 ) < (player[1] + ( char_size[1] - 10 ) ) )
						&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + item_data[0] - 0 ) ) )
						&& ( sn == 1 ) )
					{
						// �X�C�b�`�������Ă���
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
									//�����������ē����蔻����s��
									if ( ( ( (item[1 + ( i  * item_data[2] )] ) < ( item[1 + ( ii * item_data[2] )] + item_data[0] ) )	/* ���@�Ƃ̂����蔻�� */
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
						// �X�C�b�`�������Ă���
						if ( item[4 + ( i * item_data[2] )] == 0 )
						{
							//�O�񂪉�����Ă��Ȃ�����
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
					//�X�C�b�`�ŏ�����u���b�N
					//�X�C�b�`�������Ă��Ȃ�
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
									//�X�C�b�`�������Ă���
									item[3 + ( i * item_data[2] )] = 700 + bx;
								}
							}
						}
					}
/*
					if ( item[( i * item_data[2] ) + 7 ] >= 0 )	// �x�_�����݂���
					{
						k = item[7 + ( i * item_data[2] )];	// �X�C�b�`�̏�Ԃ�����
						if ( item[4 + ( k * item_data[2] )] != 0 )
						{
							//�X�C�b�`�������Ă���
							item[3 + ( i * item_data[2] )] = 700 + bx;
						}
						else 
						{
							//�X�C�b�`�������Ă��Ȃ�
							item[3 + ( i * item_data[2] )] = 600 + bx;
						}
					}
					else 
					{
						if ( item[( i * item_data[2] ) + 7 ] == -1 )		// ���񌟍�
						{
							//�X�C�b�`������
							item[( i * item_data[2] ) + 7 ] = -2;	//����
							for ( ii = 0; ii < item_data[1]; ii++ )
							{
								if ( item[( ii * item_data[2] ) + 0 ] != 0 )
								{
									bx2 = item[( ii * item_data[2] ) + 3 ] % 100;
									by2 = item[( ii * item_data[2] ) + 3 ] / 100;
									if ( ( by2 == 5 ) && ( bx2 == bx ) )
									{
										// �X�C�b�`����̑��Έʒu��ۑ�
										item[( i * item_data[2] ) + 7 ] = ii;
									}
									if ( item[( i * item_data[2] ) + 7 ] != -2 )
									{
										// �X�C�b�`����������
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
/* �A�C�e���̂x���W�v�Z */
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
		/* �n�ʔ��� */
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
			if ( item_up_Isitem( i ) != -1 )	/* �A�C�e���̏�ɏ���Ă��� */
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
		/* �n�ʔ��� */
	}
	
	/* ��ʒ[�ŗ�����̂�h�~ */
	if ( ( item[( i * item_data[2] ) + 1 ] < 0 ) || ( item[( i * item_data[2] ) + 1 ] > ( MapInfo[2] - 32 ) ) )
	{
		item[( i * item_data[2] ) + 4 ]  = 0;
	}
	/* ����̈ʒu */
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

	if ( item[( i * item_data[2] ) + 4 ]  <= 0 ) 													/* ��蒆�͔��肵�Ȃ� */
	{
		/* �n�ʔ��� */
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
			if ( item_up_Isitem( i ) != -1 )	/* �A�C�e���̏�ɏ���Ă��� */
			{
				item[( i * item_data[2] ) + 2 ] = item_up_Isitem( i ); 
				item[( i * item_data[2] ) + 4 ] = 10;
				return;
			}
		}
	}
	else		/* �㏸�� */
	{
		/* �n�ʔ��� */
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

// �A�C�e�����m�ɐ���
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
	harfsize = item_data[0] / 2;	// ����
	
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			by = item[( i * item_data[2] ) + 3 ] / 100;
			switch ( by )
			{
			case 2:	// �����
			case 3:
			case 4:
				if ( item[7 + ( i * item_data[2] )] >= 0 )
				{
					k = item[7 + ( i * item_data[2] )];	// �x�_�̎擾
					x1 = ( ( item[1 + ( i * item_data[2] )] + harfsize ) - d_x ) << 16;
					y1 = ( ( 0 - item[2 + ( i * item_data[2] )] ) + MapInfo[3] - item_data[0] - d_y + harfsize - 1 ) << 16;
					x2 = ( ( item[1 + ( k * item_data[2] )] + harfsize ) - d_x ) << 16;
					y2 = ( ( 0 - item[2 + ( k * item_data[2] )] ) + MapInfo[3] - item_data[0] - d_y + harfsize - 1 ) << 16;
					// ���̕`��
					drawGRPline( x1, y1, x2, y2, SDL_MapRGB(g_screen->format,255,255,255) );
				}
				break;
			default:
				break;
			}
		}
	}
}
//�A�C�e���̗������Ɏg�p
//�i���s�A�C�e���������ɂ���ꍇ�́A���W��Ԃ�
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
			//�����͔��肵�Ȃ�
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			
			if (
			     ( by == 2 ) 
			  || ( by == 3 ) 
			  || ( by == 6 ) 
			  || ( ( by == 10 ) && ( bx == 7 ) ) 
			   )
			{
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( px + item_data[0] - 5 ) )	/* ���@�Ƃ̂����蔻�� */
					&& ( (px + 5) < (item[1 + ( i * item_data[2] )] + item_data[0] ) )
					&& ( (item[2 + ( i * item_data[2] )] + 27 ) < (py + 10 ) )
					&& ( (py - 1) < ( item[2 + ( i * item_data[2] )] + item_data[0] ) ) ) )
				{
					return( item[2 + ( i * item_data[2] )] + 32 );
				}
			}
		}
	}
	if ( ( ( (player[0] + 10  ) < ( px + item_data[0] ) )	/* ���@�Ƃ̂����蔻�� */
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
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* ���@�Ƃ̂����蔻�� */
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
				if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* ���@�Ƃ̂����蔻�� */
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

/* �A�C�e���ɏd�Ȃ��ďオ�����ꂽ���̃C�x���g */
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
			
			/* �v���C���[�Ƃ̓����蔻�� */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < (player[0] + 22 ) )	/* ���@�Ƃ̂����蔻�� */
				&& ( (player[0] + 10 ) < (item[1 + ( i * item_data[2] )] + 32 ) )
				&& ( (item[2 + ( i * item_data[2] )] ) < (player[1] + 32 ) )
				&& ( (player[1] + 5 ) < ( item[2 + ( i * item_data[2] )] + 32 ) ) )
				&& ( player[14] == 10 ) )
			{
				r_f = 1;
				player[18] = 0;	/* ���n���[�V�����Ƃق����炩���A�j���[�V�����̉��� */

			}

			if ( ( r_f == 1 ) && ( item[( i * item_data[2] ) + 7 ] == 0 ) )
			{
				if ( ( item[( i * 10 ) + 3 ] >= 100 ) && ( item[( i * 10 ) + 3 ] <= 220 ) ) /* �Ŕ� */
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


//�G�쐬
/* �}�b�v�t�@�C�����琶������ꍇ */
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
//			if ( size >= 4 )	/* �{�X */
//			{
//				sprintf(string,"image/enm/boss%d.bmp", syu );
//				LoadBitmap(string[0],39 + size,true);								//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
//				syu = 1;
//			}
			enemy[4 + ( i * enm_data[2] )] = syu;
//			enemy[5 + ( i * enm_data[2] )] = e_hp( type ) ;
			enemy[5 + ( i * enm_data[2] )] = 1 ;
			enemy[6 + ( i * enm_data[2] )] = 0;				/* ����J�E���^ */
			enemy[7 + ( i * enm_data[2] )] = 0;				/* �ʒu�␳ */
			enemy[8 + ( i * enm_data[2] )] = 0;				/* �\���p�^�[�� */
			enemy[9 + ( i * enm_data[2] )] = 0;				/* ���� */
			enemy[10+ ( i * enm_data[2] )] = 0;				/* �\���x */
			enemy[11+ ( i * enm_data[2] )] = type;			/* ��� */
			enemy[12+ ( i * enm_data[2] )] = 0;				/* �W�����v�t���[���J�E���^ */
			enemy[13+ ( i * enm_data[2] )] = 0;				/* �W�����v�J�E���^ */
			enemy[14+ ( i * enm_data[2] )] = x;				/* �Ĕz�u���X */
			enemy[15+ ( i * enm_data[2] )] = y;				/* �Ĕz�u���Y */
			enemy[16+ ( i * enm_data[2] )] = 0;				/* ���G���� */
			enemy[17+ ( i * enm_data[2] )] = 0;	/* �_���[�W */
			enemy[18+ ( i * enm_data[2] )] = 1;				/* �Ĕz�u���s���� */
			enemy[19+ ( i * enm_data[2] )] = 0;/* Gold */
			enemy[20+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[21+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[22+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[23+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[24+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[25+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[26+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[27+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[28+ ( i * enm_data[2] )] = 0;				/* �ړ���X */
			enemy[29+ ( i * enm_data[2] )] = 0;				/* �ړ���Y */

			if ( size != 4 )
			{
				all_snack_count++;
			}
			/* �z�u���ɃC�x���g���s�������ꍇ�͂����̔��f����ǉ����� */
//			if ( size >= 4 )	/* �{�X */
//			{
//				init_event_set_enm( enemy[11+ ( i * enm_data[2] )] , i );	/* �z�u���̃C�x���g�����s */
//			}
			break;
		}
	}
}

//�G�쐬
/* �G����G�����������ꍇ */
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
//			if ( size >= 4 )	/* �{�X */
//			{
//				sprintf(string,"image/enm/boss%d.bmp", syu );
//				LoadBitmap(string[0],39 + size,true);								//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
//				syu = 1;
//			}
			enemy[4 + ( i * enm_data[2] )] = syu;
//			enemy[5 + ( i * enm_data[2] )] = e_hp( type ) ;
			enemy[5 + ( i * enm_data[2] )] = 1 ;
			enemy[6 + ( i * enm_data[2] )] = 0;				/* ����J�E���^ */
			enemy[7 + ( i * enm_data[2] )] = 0;				/* �ʒu�␳ */
			enemy[8 + ( i * enm_data[2] )] = 0;				/* �\���p�^�[�� */
			enemy[9 + ( i * enm_data[2] )] = muki;			/* ���� */
			enemy[10+ ( i * enm_data[2] )] = 0;				/* �\���x */
			enemy[11+ ( i * enm_data[2] )] = type;			/* ��� */
			enemy[12+ ( i * enm_data[2] )] = 0;				/* �W�����v�t���[���J�E���^ */
			enemy[13+ ( i * enm_data[2] )] = 0;				/* �W�����v�J�E���^ */
			enemy[14+ ( i * enm_data[2] )] = x;				/* �Ĕz�u���X */
			enemy[15+ ( i * enm_data[2] )] = y;				/* �Ĕz�u���Y */
			enemy[16+ ( i * enm_data[2] )] = 0;				/* ���G���� */
			enemy[17+ ( i * enm_data[2] )] = 0;	/* �_���[�W */
			enemy[18+ ( i * enm_data[2] )] = 0;				/* �Ĕz�u���s���� */
			enemy[19+ ( i * enm_data[2] )] = 0;/* Gold */
			enemy[20+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[21+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[22+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[23+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[24+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[25+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[26+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[27+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[28+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */
			enemy[29+ ( i * enm_data[2] )] = 0;				/* ����p�o�b�t�@ */


//			if ( size >= 4 )	/* �{�X */
//			{
//				init_event_set_enm( enemy[11+ ( i * enm_data[2] )] , i );
//			}
			break;
		}
	}
}


/* �G�̂g�o��ݒ�ie_set�Ŏg����j */
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
	p_h = 32;	/* �v���C���[�̓����蔻�� */
	all = 1;
	size = 0;
	akt_size2 = 0;
	
	for ( i = 0; i < enm_data[1]; i++ )
	{
		if ( enemy[0 +( i * enm_data[2] )] == 1 )
		{
			if ( enemy[3 + ( i * enm_data[2] )] != 4 )	/* 4�{�X */
			{
				isclaer = 1;
			}
			all = 0;
			/* ���G���Ԃ����݂���ꍇ�̓J�E���g */
			if ( enemy[16 + ( i * enm_data[2] )] > 0 )
			{
				enemy[16 + ( i * enm_data[2] )]--;
			}

			/* �G�̃T�C�Y�擾 */
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
			if ( enemy[3 + ( i * enm_data[2] )] == 4 )	/* 4�{�X */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 5 )	/* 5�{�X */
			{
				size = 32;
			}
			if ( enemy[3 + ( i * enm_data[2] )] == 6 )	/* 6�{�X */
			{
				size = 32;
			}
			
			/* �{�X�̃T�C�Y�␳ */
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
			
			/* ��ʓ��̓G�����`�悷�� */
			disp_x_j = enemy[1 + ( i * enm_data[2] )];
			disp_y_j = ( 0 - enemy[2 + ( i * enm_data[2] )] ) + MapInfo[3];

			if ( ( ( ( d_x - size ) <= ( disp_x_j ) ) 
			  && ( ( d_y - size ) <= ( disp_y_j  ) )
			  && ( ( d_x + 320 + size ) >= ( disp_x_j ) )
			  && ( ( d_y + 240 + size ) >= ( disp_y_j ) ) )
			  || ( bak_alldrow == 1 )	 					/* �w�i�̕`����N���b�v���邩 */
			   )
			{ 

				if ( enemy[6 + ( i * enm_data[2] )] > 0 )	/* ���� */
				{
					if ( ( ( enemy[16 + ( i * enm_data[2] )] % 2 ) == 0 ) || ( sn != 1 ) )
					{
//						if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* �{�X�̂Ƃ��͕\�����@���Ⴄ */
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
//						if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* �{�X�̂Ƃ��͕\�����@���Ⴄ */
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
							if ( enemy[3 + ( i * enm_data[2] )] == 4 )	//�B���A�C�e��
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
			
			/* ��ʓ��̓G�����`�悷�� */
			if ( ( ( d_x - 320 - 64 ) <= ( disp_x_j ) ) 
			  && ( ( d_y - 240 - 64 ) <= ( disp_y_j  ) )
			  && ( ( d_x + 640 + 64 ) >= ( disp_x_j ) )
			  && ( ( d_y + 480 + 64 ) >= ( disp_y_j ) ) )
			{
				e_move( i );	/* �G�L������ޕʓ��� */
			}
				
			/* �{�X�͉�ʊO�ֈړ����Ȃ� */
#if false
			if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* 5�{�X */
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
			/* ��ʊO�ֈړ������ꍇ�͏��� */
			if ( ( enemy[1 + ( i * enm_data[2] )] >= ( MapInfo[2] + size ) ) 
			  || ( enemy[1 + ( i * enm_data[2] )] <= ( 0 - size ) )
			  || ( enemy[2 + ( i * enm_data[2] )] <= ( 0 - size ) )
			  || ( enemy[2 + ( i * enm_data[2] )] >= ( MapInfo[3] + size ) ) )
			{
//				/* ��ʊO�̏ꍇ�ɍĔz�u���s�� */
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

			/* �v���C���[�Ƃ̓����蔻�� */
			if ( ( ( (enemy[1 + i * enm_data[2]] + size_hosei_x ) < (player[0] + char_size[3] ) )	/* ���@�Ƃ̂����蔻�� */
				&& ( (player[0] + char_size[2] ) < (enemy[1 + i * enm_data[2]] + size - size_hosei_x ) )
				&& ( (enemy[2 + i * enm_data[2]] + size_hosei_y ) < (player[1] + p_h) )
				&& ( (player[1] + 5 ) < ( enemy[2 + i * enm_data[2]] + size - size_hosei_y - 10 ) ) ) 
				&& ( player[17] == 0 ) 					/* ���G���Ԃ����� */
				&& ( enemy[6 + i * enm_data[2]] == 0 ) )			/* �G�̖��G���Ԃ��Ȃ� */
			{
				if ( gameflag[128] == 0 )	//�}�b�v�r���[�ł͂Ȃ�
				{
					if ( enemy[3 + ( i * enm_data[2] )] == 4 )
					{
						if ( snack_count == 1 )
						{
							enemy[0 + i * enm_data[2]] = 0;		/* ���� */
							soundPlaySe( EN_SE_L1 );
							p_shot_f2_set( ( enemy[1 + i * enm_data[2]] ) , ( enemy[2 + i * enm_data[2]] ), 0 );
							p_shot_f_set( 160 ,120, enemy[11 + i * enm_data[2]] );
							player[24] = 180;
							player[31] = 70; //�J�b�g�C��
							player[32] = ( rand( ) % 3 ); //�J�b�g�C��
							secretitemget = 1;						/* �B���A�C�e���̎擾 */
						}
					}
					else 
					{
						enemy[0 + i * enm_data[2]] = 0;		/* ���� */
						soundPlaySe( EN_SE_L1 );
						p_shot_f2_set( ( enemy[1 + i * enm_data[2]] ) , ( enemy[2 + i * enm_data[2]] ), 0 );
						p_shot_f_set( 160 ,120, enemy[11 + i * enm_data[2]] );
						player[31] = 70; //�J�b�g�C��
						player[32] = ( rand( ) % 3 ); //�J�b�g�C��
					}
				}
			}

			/* �|���Ȃ����ʂȓG�i�j���j */

//			if (
//			     ( ( enemy[11 + i * enm_data[2]] == 406 ) && ( ( enemy[8+ ( i * enm_data[2] )] == 1 ) || ( enemy[8+ ( i * enm_data[2] )] == 2 ) ) )		/* 6�{�X */
//			   )
//			{
//			}
//			else 
			{
				/* �G�ƃI�u�W�F�N�g�̓����蔻�� */
				for ( k = 0; k < 40 ; k++ )
				{
					/* �I�u�W�F�N�g�̃T�C�Y */
					size2 = 32;
					/* �v���C���[�̒e�Ƃ̓����蔻�� */
					if ( ( ( ( enemy[1 + i * enm_data[2]] + size_hosei_x ) < ( ( pmshot[5 + k * 20] >> 16 ) + size2 ) )
						&& ( ( ( pmshot[5 + k * 20] >> 16 ) + akt_size2 ) < ( enemy[1 + i * enm_data[2]] + size - size_hosei_x  ) )
						&& ( ( enemy[2 + i * enm_data[2]] + size_hosei_y ) < ( ( pmshot[6 + k * 20] >> 16 ) + size2 ) )
						&& ( ( ( pmshot[6 + k * 20] >> 16 ) + akt_size2 ) < ( enemy[2 + i * enm_data[2]] + size - size_hosei_y - 10  ) ) ) 
						&& ( pmshot[2 + k * 20] == 1 ) )
					{
						/* ���G���Ԃ����݂��Ȃ� */
						if ( enemy[16 + ( i * enm_data[2] )] == 0 )
						{
							/* �U���������Ȃ����ʂȓG */
#if false
							if (
							     ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( enemy[ 9 + ( i * enm_data[2] )] == 1 ) && ( pmshot[3 + k * 20] == 2 ) )	/* �R�T�N�� */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( enemy[ 9 + ( i * enm_data[2] )] == 0 ) && ( pmshot[3 + k * 20] == 3 ) )	/* �R�T�N�� */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 114 ) && ( pmshot[3 + k * 20] == 1 ) )	/* �R�T�N�� */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 112 ) && ( enemy[8 + ( i * enm_data[2] )] == 0 ) )	/* �A�[�� */
							  || ( ( enemy[11 + ( i * enm_data[2] )] == 112 ) && ( enemy[8 + ( i * enm_data[2] )] == 1 ) )	/* �A�[�� */
							   )
							{
								pmshot[2 + k * 20] = 0;		/* �e���� */
								se_wav( 2 );
								/* ���U���̏ꍇ�̓W�����v */
								if ( pmshot[3 + k * 20] == 1 )
								{
									/* �͂˂� */
									player[10] = 0;			/* �A�j���[�V�����t���[���J�E���^�̃N���A */
									player[11] = 0;			/* �A�j���[�V�����J�E���^�̃N���A */
									player[2] = 21;			/* �󒆏�� */

									player[14] = 5;			/* �W�����v�͂̐ݒ�A����ɂ���č������ς�� 1�`9 */
									player[13] = 0;			/* �W�����v�t���[���J�E���^�̃N���A */
			//						player[25] = 1;			/* �{�^���������ăW�����v�����t���O */
								}
							}
							else 
							{
								/* �U���q�b�g���ʂ̕\����z�u */
								p_shot_f_set( ( pmshot[5 + k * 20] >> 16 ) , ( pmshot[6 + k * 20] >> 16 ), 0 );

								/* �GHP������ */
								enemy[5 + ( i * enm_data[2] )] = enemy[5 + ( i * enm_data[2] )] - 1;

								/* �����ݒ� */
								if ( enemy[3 + ( i * enm_data[2] )] < 4 )	/* 4�{�X�͕ς��Ȃ� */
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

//								pmshot[2 + k * 20] = 0;				/* �e���� */
								if ( enemy[5 + ( i * enm_data[2] )] <= 0 )		/* �|���� */
								{

									/* �|�����ۂ̃C�x���g�����s */
									/* �{�X�ȊO�ł��s���ꍇ�͂����̔��f����ǉ� */
									if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* 4�{�X */
									{
										enemy[16 + ( i * enm_data[2] )] = 59;	/* ���G���Ԃ̐ݒ� */
//										boss_dead( enemy[1 + ( i * enm_data[2] )], enemy[2 + ( i * enm_data[2] )], i );
//										event_set_enm( enemy[11 + ( i * enm_data[2] )] , i );
#if false
										for ( l = 0; l < enm_data[1]; l++ )
										{
											enemy[5 + ( l * enm_data[2] )] = 0;
											enemy[6 + ( l * enm_data[2] )] = 60;		/* ���� */
											enemy[16 + ( l * enm_data[2] )] = 60;
										}
#endif
									}
									
									p_shot_f2_set( ( pmshot[5 + k * 20] >> 16 ) - 4, ( pmshot[6 + k * 20] >> 16 ) + 4, 0 );
									enemy[6 + ( i * enm_data[2] )] = 30;		/* �_���[�W���炢���[�V�����\���t���[���� */
									enemy[16 + ( i * enm_data[2] )] = 60;	/* ���G���Ԃ̐ݒ� */
									se_wav( 5 );
								}
								else 
								{
									/* �|���ĂȂ� */
									/* ���G���Ԑݒ� */
									enemy[6 + ( i * enm_data[2] )] = 30;		/* �̂����莞�� */
									enemy[7 + ( i * enm_data[2] )] = 6;		/* �ʒu�␳ */
									enemy[16 + ( i * enm_data[2] )] = 60;	/* ���G���� */
									se_wav( 4 );
									if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* �{�X�̂Ƃ��͂̂����肪�Ȃ� */
									{
										enemy[6 + ( i * enm_data[2] )] = 0;		/* �̂����莞�� */
										enemy[7 + ( i * enm_data[2] )] = 0;		/* �ʒu�␳ */
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
				enemy[7 + ( i * enm_data[2] )]--;					/* �ړ��␳ */
				/* �ǂɖ��܂�Ȃ��悤�ɔ��� */
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
			
			/* �_���[�W���炢���[�V���� */
			if ( enemy[6 + ( i * enm_data[2] )] > 0 )
			{
				enemy[6 + ( i * enm_data[2] )]--;					/* ������܂ŃJ�E���^ */
				if ( enemy[6 + ( i * enm_data[2] )] == 0 )
				{
					if ( enemy[5 + ( i * enm_data[2] )] <= 0 )		/* HP�������ꍇ */
					{
						if ( enemy[3 + ( i * enm_data[2] )] >= 4 )	/* �{�X */
						{
							se_wav( 18 );				/* �{�X��|�������ʉ� */

						}
						else 
						{
#if false
							if ( Rand( 5 ) == 0 )	/* ���C�t�o�� */
							{
								se_wav( 7 );
								kane_set( enemy[1 + ( i * enm_data[2] )] + ( ( size / 2 ) - 16 ), enemy[2 + ( i * enm_data[2] )] , 0, enemy[19+ ( i * enm_data[2] )] );
							}
							else 
							{
								se_wav( 7 );
								kane_set( enemy[1 + ( i * enm_data[2] )] + ( ( size / 2 ) - 16 ), enemy[2 + ( i * enm_data[2] )] , 1, enemy[19+ ( i * enm_data[2] )] );
							}
							/* ��ʊO�̏ꍇ�ɍĔz�u���s�� */
							if ( enemy[18 + ( i * enm_data[2] )] == 1 )
							{
								set_enmreset_tbl( enemy[14 + ( i * enm_data[2] )], enemy[15 + ( i * enm_data[2] )], enemy[11 + ( i * enm_data[2] )] );
							}
#endif
						}
						enemy[0 + ( i * enm_data[2] )] = 0;		/* ���� */
						
					}
				}
			}
		}
	}
	
//	if ( ( isclaer == 0 ) && ( sn == 1 ) )
	if ( ( isclaer == 0 ) )	/* �~�X���ĂƂ��Ă��N���A */
	{
		/* �S���Ƃ��� */
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
	if ( enemy[5 + ( i * enm_data[2] )] <= 0 )	/* �|���� */
	{
		return;
	}
	
	enemy[8 + ( i * enm_data[2] )] = map_rot_info;		/* �A�j���[�V�����p�^�[�� */
	enemy[9 + ( i * enm_data[2] )] = 0;		/* �A�j���[�V�����p�^�[�� */
	enemy[14 + ( i * enm_data[2] )] = 0;

}

/* �{�X��|�������o */
void boss_dead( long x, long y )
{
/*	
	long i;
	long xx;
	long yy;
	for ( i = 0; i < 100; i++ ) 
	{
//		BltFromBackupPlane();		//	�o�b�N�A�b�v�v���[�������Blt
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
/* �G�V���b�g���� */
void e_shot_set( long type , long i , long x, long y )
{
	long ii;
	long j;
	long rg;
	long mx;
	long my;
	
	/* �����ʒuX */
	/* �����ʒuY */
	for ( ii = 0; ii < 20; ii++ )
	{
		if ( mgc_e[ii * 10 + 0] == 0 )					/* ���݂��ĂȂ� */
		{

			for ( j = 0 ; j <= 9 ;j++ )
			{
				mgc_e[ii * 10 + j] = 0;
			}
			if ( type == 1061 )							/* ���h�J�� */
			{
				mx = ( ( 32 / 2 ) - 5 ) + player[0] - x;
				my = ( ( 32 / 2 ) - 5 ) + player[1] - y;
				rg = funcTan2( mx, my );
				rg = ( 90 );
				mgc_e[ii * 10 + 1] = x << 16;		/* X */
				mgc_e[ii * 10 + 2] = y << 16;		/* Y */
				mgc_e[ii * 10 + 3] = 0;		/* �A�j���[�V�����J�E���^ */
				mgc_e[ii * 10 + 4] = funcSin( rg ) * 4;		/* �ړ����� */
				mgc_e[ii * 10 + 5] = funcCos( rg ) * 4;	/* �ړ����� */
				mgc_e[ii * 10 + 6] = 6;		/* �_���[�W */
				mgc_e[ii * 10 + 7] = 2;		/* ���� */
				mgc_e[ii * 10 + 9] = type;					/* �^�C�vplayer[10] */
			}

			mgc_e[ii * 10 + 0] = 1;					/* ���݂��� */
			break;
		}
	}

}
/* �V���b�g�ړ� */
void e_shot_disp( )
{
	long i;
	long p_h;
	long size ;
	
	p_h = 22;	/* �v���C���[�̓����蔻�� */
	size = 0;
	
	/* �����ʒuX */
	/* �����ʒuY */
	for ( i = 0; i < 20; i++ )
	{
		if ( mgc_e[i * 10 + 0] == 1 )					/* ���݂��Ă��� */
		{
			if ( mgc_e[i * 10 + 9] == 4010 ) 	/* �P�{�X */
			{
				size = 32;
				BltRect( 50, ( mgc_e[i * 10 + 1] >> 16 ) - d_x , ( 0 - ( mgc_e[i * 10 + 2] >> 16 ) ) + 480 - 32 - d_y, mgc_e[i * 10 + 3] * 32, 0 , 32, 32 );
				mgc_e[i * 10 + 1] = mgc_e[i * 10 + 1] + mgc_e[i * 10 + 4];		/* X */
				mgc_e[i * 10 + 2] = mgc_e[i * 10 + 2] + mgc_e[i * 10 + 5];		/* Y */
				mgc_e[i * 10 + 3]++;					/* �A�j���[�V�����J�E���^ */
				if ( mgc_e[i * 10 + 3] >= 4 )
				{
					mgc_e[i * 10 + 3] = 0;
				}
			}
			
			/* �v���C���[�Ƃ̓����蔻�� */
			if ( ( ( ( ( mgc_e[1 + i * 10] >> 16 ) ) < (player[0] + 22 ) )	/* ���@�Ƃ̂����蔻�� */
				&& ( (player[0] + 10 ) < ( ( mgc_e[1 + i * 10] >> 16 ) + size ) )
				&& ( ( ( mgc_e[2 + i * 10] >> 16 ) ) < (player[1] + p_h) )
				&& ( (player[1] + 5  ) < ( ( mgc_e[2 + i * 10] >> 16 ) + size ) ) ) 
				&& ( player[17] == 0 ) )
			{
				player[10] = 0;
				player[11] = 0;
				player[12] = 4;
				player[13] = 0;
				player[2] = 31;	/* �_���[�W */
				player[17] = 120;	/* ���G���� */
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

/* �G�p�W�����v */
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
	/* ��ʊO�ł͍s��Ȃ� */
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
		/* ����̈ʒu */
		px = ( enemy[1 + ( i * 20 )] + 32 ) / 32;
		px1 = ( enemy[1 + ( i * 20 )] + size ) / 32;
		px2 = ( enemy[1 + ( i * 20 )] + size ) / 32;
		py = ( 16 - ( ( enemy[2 + ( i * 20 )] + 28 ) / 32 ) );
		/* 100 �` 200�͒n�� */
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
		/* �n�ʔ��� */
	}


	/* ��ʒ[�ŗ�����̂�h�~ */
	e10 = enemy[13 + ( i * 20 )];
	if (  enemy[1+ ( i * 20 )] > ( 630 - size - size ) )
	{
		if ( enemy[13+ ( i * 20 )] < 0 )	/* ���� */
		{
			e10 = 0;
		}
	}


	/* ����̈ʒu */
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

	if ( enemy[13 + ( i * 20 )] <= 0 )													/* ��蒆�͔��肵�Ȃ� */
	{
		/* �n�ʔ��� */
		if ( ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 119 ) )
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 200 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 219 ) ) 
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) )
		{
			enemy[2 + ( i * 20 )] = ( ( 16 - py ) * 32 ) - 16; 
			enemy[13 + ( i * 20 )] = 10;
		}
	}
	else		/* �㏸�� */
	{
		if ( enemy[1+ ( i * 20 )] < ( 630 - size - size ) )
		{
			px = ( enemy[1 + ( i * 20 )] + size ) / 32;
			py = ( 16 - ( ( enemy[2 + ( i * 20 )] - ( y1 / 25 ) + 16 + 48  ) / 32 ) );

			/* �n�ʔ��� */
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


/* �ړ���̍��W�̃}�X��Ԃ� */
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
	
	/* �A�C�e���Ƃ̂����蔻�� */
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( item[( i * item_data[2] ) + 0 ] == 1 )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			/* �v���C���[�Ƃ̓����蔻�� */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( x ) )	/* ���@�Ƃ̂����蔻�� */
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
	
	/* �A�C�e���Ƃ̂����蔻�� */
	for ( i = 0; i < item_data[1]; i++ )
	{
		if ( ( item[( i * item_data[2] ) + 0 ] == 1 ) && ( item_index != i ) )
		{
			bx = item[3 + ( i * item_data[2] )] % 100 ;
			by = item[3 + ( i * item_data[2] )] / 100 ;
			/* �v���C���[�Ƃ̓����蔻�� */
			if ( ( ( (item[1 + ( i * item_data[2] )]  ) < ( x ) )	/* ���@�Ƃ̂����蔻�� */
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
			/* �Ƃ��� */
			if ( ( ( (kane[1 + ( i * 10 )]  ) < (player[0] + 10 ) )	/* ���@�Ƃ̂����蔻�� */
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
/* �W�����v�x�ʒu�v�Z */
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
		/* �n�ʔ��� */
	}
	
	/* ��ʒ[�ŗ�����̂�h�~ */
	if ( ( kane[1 + ( i * 10 )] < 0 ) || ( kane[1 + ( i * 10 )] > 610 ) )
	{
		kane[6 + ( i * 10 )] = 0;
	}
	/* ����̈ʒu */
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

	if ( kane[6 + ( i * 10 )] <= 0 ) 													/* ��蒆�͔��肵�Ȃ� */
	{
		/* �n�ʔ��� */
		if ( ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 299 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 100 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 299 ) ) 
		  || ( ( map1[ px1 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px1 + ( ( py ) * 20 ) ] <= 619 ) )
		  || ( ( map1[ px2 + ( ( py ) * 20 ) ] >= 600 ) && ( map1[ px2 + ( ( py ) * 20 ) ] <= 619 ) ) )
		{
			kane[2 + ( i * 10 )] = ( ( 16 - py ) * 32 ) - 16; 
			kane[6 + ( i * 10 )] = 10;
		}
	}
	else		/* �㏸�� */
	{
		/* �n�ʔ��� */
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

/* ���j���[�̕\�� */
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

/* ���j���[�ł̃L�[���� */
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
	//	�X�y�[�X�L�[���������
	if ( IsPushOKKey( ) ) 
	{
		if ( demo[0] == 0 )
		{
			if ( player[9] != 0 ) //��]��
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
			if ( gameflag[129] != 0 )	//�X�e�[�W�Z���N�g����J�n
			{
				g_scene = EN_SN_STAGESELECT;
			}
			else 
			{
				g_scene = EN_SN_TITLE;	/* �^�C�g���� */
			}
//			gameflag[40] = 1;
			sn = 10;
		}
	}
	//B���������
	if ( IsPushCancelKey( ) )
	{
		if ( player[9] != 0 ) //��]��
		{
			sn = 5;
		}
		else 
		{
			sn = 1;
		}
	}

}


/* �}�b�v�r���[�ł̃L�[���� */
void mapviwe_keys( void )
{
	if ( IsPressKey( gameflag[0] ) )	//��@
	{
		player[1] = player[1] + 2;
	}
	if ( IsPressKey( gameflag[1] ) )	//���@
	{
		player[1] = player[1] - 2;
	}
	if ( IsPressKey( gameflag[2] ) )	//���@
	{
		player[0] = player[0] - 2;
	}
	if ( IsPressKey( gameflag[3] ) )	//�E�@
	{
		player[0] = player[0] + 2;
	}

	if ( player[0] < 0 )	/* ��ʍ��[���� */
	{
		player[0] = 0;
	}
	if ( player[0] > ( MapInfo[2] - char_size[0] ) )	/* ��ʉE�[���� */
	{
		player[0] =  MapInfo[2] - char_size[0];
	}
	if ( player[1] <= 0 )	/* ��ʉ� */
	{
		player[1] = 0;
	}
	if ( player[1] >= ( MapInfo[3] - char_size[1] ) )	/* ��ʏ� */
	{
		player[1] = ( MapInfo[3] - char_size[1] );
	}

	//	�X�y�[�X�L�[���������
	if ( IsPushOKKey( ) ) 
	{
		g_scene = EN_SN_TITLE;	/* �^�C�g���� */
//		gameflag[40] = 1;
		sn = 10;
	}
	//B���������
	if ( IsPushCancelKey( ) )
	{
		g_scene = EN_SN_TITLE;	/* �^�C�g���� */
//		gameflag[40] = 1;
		sn = 10;
	}

}

/* ��Βl��Ԃ� */
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

/* ���@���� */
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
 
	/* �����ʒuX */
	/* �����ʒuY */

	max = 1;
	for ( i = 0; i < max; i++ )
	{

		k = 5;

		for ( ii = 0; ii < 40; ii++ )
		{
			if ( pmshot[ii * 20 + 2] == 0 )
			{
				pmshot[ii * 20 + 0] = funcSin( rg ) * k;			/* �e��x */
				pmshot[ii * 20 + 1] = funcCos( rg ) * k;			/* �e��y */
				pmshot[ii * 20 + 2] = 1;						/* ���� */
				pmshot[ii * 20 + 3] = 0;						/* ��� */
				pmshot[ii * 20 + 4] = 0 ;						/*  */
				pmshot[ii * 20 + 5] = ( player[0] ) << 16 ;			/* �����ʒu�̐ݒ� */
				pmshot[ii * 20 + 6] = ( player[1] ) << 16 ;
				pmshot[ii * 20 + 7] = muki;						/* ���� */
				
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

			pmshot[ii * 20 + 5] = pmshot[ii * 20 + 0] + pmshot[ii * 20 + 5];		/* �e��x */
			pmshot[ii * 20 + 6] = pmshot[ii * 20 + 1] + pmshot[ii * 20 + 6];		/* �e��x */
			
			if ( ( ( pmshot[ii * 20 + 5] >> 16 ) > 640 ) || ( ( pmshot[ii * 20 + 5] >> 16 ) < -32 ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* ���ݖ��� */
			}
			if ( ( ( pmshot[ii * 20 + 6] >> 16 ) > 480 ) || ( ( pmshot[ii * 20 + 6] >> 16 ) < -32 ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* ���ݖ��� */
			}
			
			if ( ( ( map1_item_j( ( pmshot[ii * 20 + 5] >> 16 ) + 16 , ( pmshot[ii * 20 + 6] >> 16 ) + 16 ) >= 100 )
			    && ( map1_item_j( ( pmshot[ii * 20 + 5] >> 16 ) + 16 , ( pmshot[ii * 20 + 6] >> 16 ) + 16 ) <= 220 ) ) )
			{
				pmshot[ii * 20 + 2] = 0;				/* ���ݖ��� */
				p_shot_f2_set( ( pmshot[5 + ii * 20] >> 16 ) + 15, ( pmshot[6 + ii * 20] >> 16 ) + 15, 0 );
				if ( pmshot[3 + ii * 20] == 2 )	/* �X�L���N���b�V���V���b�g */
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
	
	/* �L�[�����͊�{�I��player[2]������Ԃ̎��ɃL�[����ꂽ��ǂ��Ȃ���L�q���Ă��� */
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
	
	//	�X�y�[�X�L�[���������
	if ( IsPressKey( gameflag[4] ) )
	{
		input_keys = input_keys + 10000;
	}
	
	//B���������
	if ( IsPressKey( gameflag[5] ) )
	{
		input_keys = input_keys + 100000;
	}
	
	//B���������
	if ( ( IsPushKey( gameflag[5] ) ) || ( IsPushKey( gameflag[0] ) && ( gameflag[133] == 1 ) ) )
	{
		input_keys = input_keys + 1000000;
	}
	/* 12�{�^���@���@�b�������ꂽ */
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
	// ���̕`��
}







