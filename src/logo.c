#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "define.h"
#include "function.h"
#include "util_snd.h"
#include "extern.h"
#include "logo.h" 


// �֐��v���g�^�C�v
void logo_main( void );
void logo_init( void );
void logo_relese( void );
void logo_keys( void );
void logo_drow( void );
void logo_init_save_data( void );

// �ϐ��錾
static int scene_exit;
static int demo;
static int demo2;


//----------------------------------------------------------------------
// ���C���֐�
void logo_main( void )
{
	int exit_code;
	
	exit_code = 0;
	
	logo_init( );		// ������
	
	while( scene_exit )
	{
//		KeyInput( );	// �L�[����
		
		logo_keys( );		// �L�[����
		logo_drow( );		// �`��
		
		halt( );
//		SDL_Flip( g_screen );	// �`��
		FPSWait( );		// �҂�

		exit_code = system_keys( );  //
		if ( exit_code == 0 )
		{
			scene_exit = 0;
		}
	}
	
	logo_relese( );		// �I��
}

void logo_init( void )
{
	scene_exit = 1;
	demo = 0;
	demo2 = 0;
	
	LoadBitmap("image/a_logo.bmp",2,true);		//�v���[���i���o�[�P�Ƀ^�C�g����ʔw�i��ǂݍ���
	LoadBitmap("image/al_256.bmp",3,false);		//�v���[���i���o�[�P�Ƀ^�C�g����ʔw�i��ǂݍ���

	soundStopBgm(EN_BGM_GAME01);
}

void logo_relese( void )
{
	int i;
	
	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		ReleaseBitmap( i );
	}
	soundStopBgm(EN_BGM_GAME01);

}


void logo_keys( void )
{
	//	�㉺�L�[�ɉ����Ĉړ�
	if (IsPushKey(gameflag[0]))
	{
	}
	if (IsPushKey(gameflag[1]))
	{
	}
	if (IsPushKey(gameflag[2]))
	{
	}
	if (IsPushKey(gameflag[3]))
	{
	}

	//	�X�y�[�X�L�[���������
	if ( ( IsPushKey(gameflag[4]) ) || ( IsPushKey(gameflag[5]) ) || ( demo2 >= 2 ) )
	{
		if ( demo2 >= 2 )
		{
			gameflag[40] = 0;					/* �^�C�g�� */
			g_scene = EN_SN_TITLE;
			scene_exit=0;
			return;
		}
		else 
		{
			demo2++;
		}
	}

}

void logo_drow( void )
{
	//�w�i�N���A
	ClearSecondary();

	demo++;
	
	switch( demo2 )
	{
	case 0:
		Blt( 3, 0, 0 );		/* 320 * 240 */
		if ( demo >= ( 60 * 3 ) )
		{
			demo = 0;
			demo2++;
		}
		break;
	case 1:
		Blt( 2, 0, 0 );		/* 320 * 240 */
		if ( demo >= ( 60 * 3 ) )
		{
			demo = 0;
			demo2 = 2;
		}
		break;
	default:
		break;
	}
	
	
	//�L�[���͌���
	KeyInput();				

}


