#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "demo.h" 


// �֐��v���g�^�C�v
void demo_main( void );
void demo_init( void );
void demo_relese( void );
void demo_keys( void );
void demo_drow( void );


// �ϐ��錾
static int scene_exit;


static char string[1024];
//----------------------------------------------------------------------
// ���C���֐�
void demo_main( void )
{
	int exit_code;
	
	exit_code = 0;
	
	demo_init( );		// ������
	
	while( scene_exit )
	{
//		KeyInput( );	// �L�[����
		
		demo_keys( );		// �L�[����
		demo_drow( );		// �`��
		
		halt( );
//		SDL_Flip( g_screen );	// �`��
		FPSWait( );		// �҂�

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	demo_relese( );		// �I��
}

void demo_init( void )
{
	scene_exit = 1;

	sprintf(string,"image/demo%d/demo%d.bmp", ( int )gameflag[131] , ( int )1 );
	LoadBitmap(string,1,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	sprintf(string,"image/demo%d/demo%d.bmp", ( int )gameflag[131] , ( int )2 );
	LoadBitmap(string,2,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	sprintf(string,"image/demo%d/demo%d.bmp", ( int )gameflag[131] , ( int )3 );
	LoadBitmap(string,3,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	sprintf(string,"image/demo%d/demo%d.bmp", ( int )gameflag[131] , ( int )4 );
	LoadBitmap(string,4,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	sprintf(string,"image/demo%d/demo%d.bmp", ( int )gameflag[131] , ( int )5 );
	LoadBitmap(string,5,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	LoadBitmap("image/bak/1_256.bmp",11,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/bak/2_256.bmp",12,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/bak/3_256.bmp",13,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/bak/4_256.bmp",14,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���
	LoadBitmap("image/bak/5_256.bmp",15,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	LoadBitmap("image/demo0/mesh.bmp",20,true);				//�v���[���i���o�[�Q�ɃV�X�e���p�a�l�o��ǂݍ���

	if ( gameflag[70] == 0 )
	{
		if ( ( gameflag[120] > 0 ) && ( gameflag[120] <= 10 ) )
		{
			soundPlayBgm( EN_BGM_GAME01 );
		}
		if ( ( gameflag[120] > 10 ) && ( gameflag[120] <= 20 ) )
		{
			soundPlayBgm( EN_BGM_GAME01 );
		}
		if ( ( gameflag[120] > 20 ) && ( gameflag[120] <= 30 ) )
		{
			soundPlayBgm( EN_BGM_GAME01 );
		}
		if ( ( gameflag[120] > 30 ) && ( gameflag[120] <= 40 ) )
		{
			soundPlayBgm( EN_BGM_GAME01 );
		}
		if ( ( gameflag[120] > 40 ) && ( gameflag[120] <= 50 ) )
		{
			soundPlayBgm( EN_BGM_GAME01 );
		}
	}
//	soundPlayBgm( EN_BGM_GAME01 );

}

void demo_relese( void )
{
	int i;
	
	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		ReleaseBitmap( i );
	}
	soundStopBgm(EN_BGM_GAME01);

}


void demo_keys( void )
{
	if ( IsPushKey( gameflag[0] ) )
	{
//		soundPlaySe( EN_SE_SELECT );
	}
	else if ( IsPushKey( gameflag[1] ) )
	{
//		soundPlaySe( EN_SE_SELECT );
	}
	if ( IsPushKey( gameflag[2] ) )
	{
	}

	//	����L�[��������
	if ( IsPushOKKey( ) )
	{
		g_scene = EN_SN_ACT;
		scene_exit=0;
	}
	//	�L�����Z���L�[��������
	if ( IsPushCancelKey( ) )
	{
		g_scene = EN_SN_ACT;
		scene_exit=0;
	}
}

void demo_drow( void )
{
	//-------------------------------------------------------------
	//�ϐ��錾
	//-------------------------------------------------------------
	
	//�w�i�N���A
	ClearSecondary();
	
	if ( ( gameflag[120] > 0 ) && ( gameflag[120] <= 10 ) )
	{
		Blt( 11, 0, 0 );
		Blt( 20, 0, 0 );
		Blt( 1, 0, 0 );
	}
	if ( ( gameflag[120] > 10 ) && ( gameflag[120] <= 20 ) )
	{
		Blt( 12, 0, 0 );
		Blt( 20, 0, 0 );
		Blt( 2, 0, 0 );
	}
	if ( ( gameflag[120] > 20 ) && ( gameflag[120] <= 30 ) )
	{
		Blt( 13, 0, 0 );
		Blt( 20, 0, 0 );
		Blt( 3, 0, 0 );
	}
	if ( ( gameflag[120] > 30 ) && ( gameflag[120] <= 40 ) )
	{
		Blt( 14, 0, 0 );
		Blt( 20, 0, 0 );
		Blt( 4, 0, 0 );
	}
	if ( ( gameflag[120] > 40 ) && ( gameflag[120] <= 50 ) )
	{
		Blt( 15, 0, 0 );
		Blt( 20, 0, 0 );
		Blt( 5, 0, 0 );
	}
	
	//�L�[���͌���
	KeyInput();				

}

