#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "stageselect.h" 


// �֐��v���g�^�C�v
void stageselect_main( void );
void stageselect_init( void );
void stageselect_relese( void );
void stageselect_keys( void );
void stageselect_drow( void );
void stageselect_init_save_data( void );

// �a�l�o�p�萔

// �ϐ��錾
static int scene_exit;

static int mode;		//���ݑI������Ă��鍀��	�O�F�f�`�l�d�r�s�`�q�s�@�P�F�n�o�s�h�n�m�@�Q�F�d�w�h�s
static int a[2] = {0,0};
static int csl[2] = {0,0};

//static char string[1024];

static long target_save[1024];

//----------------------------------------------------------------------
// ���C���֐�
void stageselect_main( void )
{
	int exit_code;
	
	exit_code = 0;
	
	stageselect_init( );		// ������
	
	while( scene_exit )
	{
//		KeyInput( );	// �L�[����
		
		stageselect_keys( );		// �L�[����
		stageselect_drow( );		// �`��
		
		halt( );	// �`��
//		SDL_Flip( g_screen );	// �`��
		FPSWait( );		// �҂�

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	stageselect_relese( );		// �I��
}

void stageselect_init( void )
{
	scene_exit = 1;

	mode = 0;		//���ݑI������Ă��鍀��	�O�F�f�`�l�d�r�s�`�q�s�@�P�F�n�o�s�h�n�m�@�Q�F�d�w�h�s
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

	LoadBitmap("image/title/title_natuki.bmp",1,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	LoadBitmap("image/title/stageselect.bmp",2,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/title/scl.bmp",3,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
//	LoadBitmap("image/bak/1_256.bmp",5, false );		//�v���[���i���o�[�P�Ƀ^�C�g����ʔw�i��ǂݍ���
//	LoadBitmap("image/bak/1.bmp",5, false );		//�v���[���i���o�[�P�Ƀ^�C�g����ʔw�i��ǂݍ���
	LoadBitmap("image/title/potion_bak.bmp",5, false );		//�v���[���i���o�[�P�Ƀ^�C�g����ʔw�i��ǂݍ���
	LoadBitmap("image/player/cutin.bmp",6,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	if ( gameflag[126] == 0 )
	{
		LoadBitmap("image/title/title5.bmp",7,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	}
	else 
	{
		LoadBitmap("image/title/title5_ura.bmp",7,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	}

	LoadBitmap("image/title/title3.bmp",10,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/fonts2.bmp",18,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/sys/waku.bmp",109,true);					//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���


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

	//	����L�[��������
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
			
			gameflag[127] = 0;	//�g�[�^���A�^�b�N
			gameflag[123] = -1;	//���v���C�I�����̃X�e�[�W
			gameflag[132] =  0;		//���v���C
			gameflag[70] = 1;
			gameflag[128] = 0;	//�}�b�v�r���[
			gameflag[129] = 1;	//�X�e�[�W�Z���N�g����J�n
			SaveGameFlag2( "save/work.sav");

			ResetGameFlag2( );
			SaveGameFlag2( "save/item_wk.sav");

			gameflag[40] = 4;
			g_scene = EN_SN_ACT;
			scene_exit=0;
			return;
		}
	}
	//	�L�����Z���L�[��������
	if ( IsPushCancelKey( ) )
	{
		g_scene = EN_SN_TITLE;
		scene_exit=0;
	}
	/* 12�{�^���@���@�b�������ꂽ */
/*
	if ( IsPushKey( gameflag[6] ) )	// �X�L���`�F���W
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
	//�ϐ��錾
	//-------------------------------------------------------------

	//�w�i�N���A
	ClearSecondary();


	//�^�C�g����ʂ̓]��
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
	
	//�����
	tergetnam = 0;
	for ( x = 0; x < 5; x++ )
	{
		for ( y = 0; y < 10; y++ )
		{
			stage_no = ( ( x ) * 10 ) + ( y + 1 );
			//�g���t�B�[�̕\��
			//�^�C��
			tergetnam = 0;
			if ( target_save[200 + stage_no + stage_hosei] >= gameflag[200 + stage_no + stage_hosei] )
			{
				tergetnam++;
			}
			//��]
			if ( target_save[300 + stage_no + stage_hosei] >= gameflag[300 + stage_no + stage_hosei] )
			{
				tergetnam++;
			}
			//�B��
			if ( gameflag[400 + stage_no + stage_hosei] != 0 )
			{
				tergetnam++;
			}
			BltRect( 3, 15 + ( x * 64 ) , 32 + ( y * 8 ), 0, 96 + ( tergetnam * 7 ) , 41 , 7 );	/* �B���x */
		}
	}
	
	Blt( 2, 0, 0 );
	if ( csl[0] == 10 )
	{
		// exit
		BltRect( 3, 0 + ( 2 * 64 ) , 32 + ( 10 * 8 ), ( a[1] / 10 ) * 16, 0 , 16 , 16 );	/* �J�[�\�� */
	}
	else 
	{
		BltNumericImage( csl[1] + 1, 1, 174, 135, 18, 0, 0, 10, 8 );	/*  */
		BltNumericImage( csl[0] + 1 + ( csl[1] * 10 ), 2, 192, 135, 18, 0, 0, 10, 8 );	/*  */
		
		BltRect( 3, 0 + ( csl[1] * 64 ) , 28 + ( csl[0] * 8 ), ( a[1] / 10 ) * 16, 0 , 16 , 16 );	/* �J�[�\�� */
		
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
		
		//�g���t�B�[�̕\��
		//�^�C��
		if ( target_save[200 + stage_no + stage_hosei] >= gameflag[200 + stage_no + stage_hosei] )
		{
			BltRect( 3, 0, 138, 0, 64, 32, 32 );	/* �^�C�� */
			BltRect( 3, 0 + 5, 138 + 4, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J�[�\�� */
			BltRect( 3, 0 + 20, 138 + 14, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J�[�\�� */
		}
		else 
		{
			BltRect( 3, 0, 138, 0, 32, 32, 32 );	/* �y�� */
		}
		//��]
		if ( target_save[300 + stage_no + stage_hosei] >= gameflag[300 + stage_no + stage_hosei] )
		{
			BltRect( 3, 0, 170, 32, 64, 32, 32 );	/* �^�C�� */
			BltRect( 3, 0 + 5, 170 + 4, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J�[�\�� */
			BltRect( 3, 0 + 20, 170 + 14, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J�[�\�� */
		}
		else 
		{
			BltRect( 3, 0, 170, 0, 32, 32, 32 );	/* �y�� */
		}
		//�B��
		if ( gameflag[400 + stage_no + stage_hosei] != 0 )
		{
			BltRect( 18, 190, 214, 0, 176, 200, 8 );	/* �^�C�� */
			BltRect( 3, 0, 202, 64, 64, 32, 32 );	/* �^�C�� */
			BltRect( 3, 0 + 5, 202 + 4, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J�[�\�� */
			BltRect( 3, 0 + 20, 202 + 14, 32 + ( ( ( a[0] / 10 ) % 2 ) * 5 ), 37 , 5 , 7 );	/* �J�[�\�� */
		}
		else 
		{
			BltRect( 18, 190, 214, 0, 168, 200, 8 );	/* �^�C�� */
			BltRect( 3, 0, 202, 0, 32, 32, 32 );	/* �y�� */
		}
		
	}
		
//	if ( gameflag[61] == 0 )
//	{
//		Blt( 109 , -160, -120 );
//	}
	
	//�L�[���͌���
	KeyInput();				

}


/***************************************************************************/
// NAME      = init_save_data
// FUNCTION  = �Z�[�u�t�@�C���̏����l��ݒ�
// NOTES     = 
// DATE      = 
// AUTHER    = koizumi
// HISTORY   =
// PARAMETER = �Ȃ�
// RETURN    = �Ȃ�
/***************************************************************************/
void stageselect_init_save_data( void )
{
	gameflag2[0]	= 8 * 32;	/* �w */
	gameflag2[1]	= ( 2 * 32 ) - 16;	/* �x */
	if ( gameflag[126] == 1 )
	{
		gameflag2[2]	= 2;	/* �X�e�[�W */
	}
	else 
	{
		gameflag2[2]	= 1;	/* �X�e�[�W */
	}
	gameflag[120] = ( ( csl[1] ) * 10 ) + ( csl[0] + 1 );
	gameflag2[3]	= gameflag[120];	/* ��ʂm�� */
	gameflag2[4]	= 0;	/* ���� */
	gameflag2[5]	= 3;	/* ���݂g�o */
	gameflag2[6]	= 3;	/* �ő�g�o */
	gameflag2[7]	= 0;	/* �n�[�g�̂����珊���� */
	gameflag2[8]	= 0;	/* ���ݐݒ�X�L�� */
	gameflag2[9]	= 0;	/* �e���|�[�^�g�p�s�A�X�N���[���s�t���O */
	gameflag2[10]	= 0;	/* �e���|�[�^�g�p�s�t���O */

	gameflag2[20]	= 0; 	/* �� */
	gameflag2[21]	= 0; 	/* �� */
	gameflag2[22]	= 0; 	/* �b */
	
	gameflag2[30]	= 0;	/* �e���|�[�^�[�g�p */
	gameflag2[31]	= 0;	/* �e���|�[�^�[�X�e�[�W */
	gameflag2[32]	= 0;	/* �e���|�[�^�[��ʂm�� */
	gameflag2[33]	= 0;	/* �e���|�[�^�[�w */
	gameflag2[34]	= 0;	/* �e���|�[�^�[�x */

	gameflag2[40]	= 0;	/* �擾�X�L���P */
	gameflag2[41]	= 0;	/* �擾�X�L���Q */
	gameflag2[42]	= 0;	/* �擾�X�L���R */
	gameflag2[43]	= 0;	/* �擾�X�L���S */

	
	/* �C�j�V�����C�Y���K�v�ȏꍇ�͂����ɋL�q���� */
//	gameflag2[100]	= ;	/* �C�x���g�t���O[100]�`[199] */

	/* 100�`399�C�x���g�p�t���O */
	
}



