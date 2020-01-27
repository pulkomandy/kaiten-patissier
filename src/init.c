#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <unistd.h>

#include "define.h"
#include "extern.h"
#include "function.h"
#include "util_snd.h"

#include "scene.h"

#ifdef GP2X
#include <unistd.h>
#endif

//#define MacOS

void main_init( void );
void main_init_config( void );
void ExitProgram(void);
int main(int argc, char *argv[]);


int main(int argc, char *argv[])
{
	SDL_Rect rect;
	Uint32 flags;
	SDL_Surface* tmp;
	char AppPath[1024];
	char AppPathw[1024];
	char *char_work;
	int strlen;

	/* ������ */
	memset( &AppPath[0], '\0', sizeof( AppPath ) );
	memset( &AppPathw[0], '\0', sizeof( AppPath ) );
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
		
#ifdef GP2X
#else
	#ifdef MacOS
		if ( argc > 0 )	// �N���Ɉ���������ꍇ
		{
			strcpy( &AppPath[0], argv[0] );
	//		strcat( &AppPath[0], "/Contents/Recources/" );
			char_work = strrchr( &AppPath[0], '/' );
//			char_work = strrchr( &AppPath[0], '\\' );
			strlen = char_work - &AppPath[0];
			
			strncpy( &AppPathw[0], &AppPath[0], strlen );
			chdir( &AppPathw[0] );
//			LogFileWrite( "testlog.txt", &AppPathw[0] );
		}
	#else
	#endif
#endif	
	
	main_init_config( );	// ���t�@�C���̓ǂݍ���

	/* ��������ʃT�C�Y */
#ifdef GP2X
	gameflag[61] = 1;	//��ʔ{��
	flags = SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWPALETTE;
#else
	gameflag[61] = 1;	//��ʔ{��
	flags = SDL_SWSURFACE;
	if ( argc > 1 )	// �N���Ɉ���������ꍇ
	{
		while( *++argv != NULL )
		{ 
			if( **argv == '-' )
			{
				switch( *(*argv+1) )
				{
				case 'f':  /* -l �I�v�V�������� */
					flags = SDL_FULLSCREEN  | SDL_SWSURFACE;
				case 'r':  /* -r �I�v�V�������� */
					gameflag[61] = 2;	//��ʔ{��
				}
			}
			else
			{
				break;
			}
		}
//		if ( ( char * )argv[1] == "f" )
//		{
//			flags = SDL_FULLSCREEN  | SDL_SWSURFACE;
//		}
//		if ( ( char * )argv[2] == '2' )
//		{
//			gameflag[61] = 2;	//��ʔ{��
//		}
//		LogFileWrite( "testlog.txt", &( char * )argv[1] );
	}
#endif

//	g_screen = SDL_SetVideoMode(DISPLY_WIDTH, DISPLY_HEIGHT, 16, SDL_SWSURFACE);
//	g_screen = SDL_SetVideoMode(DISPLY_WIDTH, DISPLY_HEIGHT, 8, flags);
	g_screen = SDL_SetVideoMode(DISPLY_WIDTH * gameflag[61], DISPLY_HEIGHT * gameflag[61], 8, flags);
	rect.x = 0;
	rect.y = 0;
	rect.w = DISPLY_WIDTH;
	rect.h = DISPLY_HEIGHT;
//	SDL_SetClipRect( g_screen, &rect );
	
	tmp = SDL_LoadBMP("image/color.bmp");		//�v���[���i���o�[�P�Ƀ^�C�g����ʔw�i��ǂݍ���
	SetGscreenPalette( tmp );
	SDL_FreeSurface(tmp);
	
	if (!g_screen)
	{
		fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
		return 1;
	}
	SDL_WM_SetCaption("RotateGear", "");
	
	SDL_ShowCursor(SDL_DISABLE);
	FunctionInit( );
//	soundInitBuffer();
	/* �O���[�o���ϐ��̏����� */
	main_init( );


		
	scenemanager( );
	
	ExitProgram( );
	return 0;
}


void main_init( void )
{
	g_scene = EN_SN_LOGO;

	
	// �Q�[�����̎g�p���鉹�̓ǂݍ���
	soundLoadBuffer(EN_BGM_GAME01, (Uint8 *)"sound/bgm/01.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME02, (Uint8 *)"sound/bgm/02.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME03, (Uint8 *)"sound/bgm/03.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME04, (Uint8 *)"sound/bgm/04.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME05, (Uint8 *)"sound/bgm/05.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME06, (Uint8 *)"sound/bgm/06.ogg", -1);
	soundLoadBuffer(EN_BGM_GAME07, (Uint8 *)"sound/bgm/07.ogg", 0);
	
	soundLoadBufferSE(EN_SE_ATK1   , (Uint8 *)"sound/se/atk1.wav" );
	soundLoadBufferSE(EN_SE_DAMEGE , (Uint8 *)"sound/se/damage.wav" );
	soundLoadBufferSE(EN_SE_L1     , (Uint8 *)"sound/se/l1.wav" );
	soundLoadBufferSE(EN_SE_LANDING, (Uint8 *)"sound/se/landing.wav" );
	soundLoadBufferSE(EN_SE_MSG    , (Uint8 *)"sound/se/msg.wav" );
	soundLoadBufferSE(EN_SE_SELECT , (Uint8 *)"sound/se/select.wav" );
	soundLoadBufferSE(EN_SE_SW     , (Uint8 *)"sound/se/sw.wav" );
	soundLoadBufferSE(EN_SE_JUMP   , (Uint8 *)"sound/se/jump.wav" );
	soundLoadBufferSE(EN_SE_PAWA   , (Uint8 *)"sound/se/puwa.wav" );
	soundLoadBufferSE(EN_SE_CL1   , (Uint8 *)"sound/se/se01.wav" );
	soundLoadBufferSE(EN_SE_CL2   , (Uint8 *)"sound/se/se02.wav" );
	soundLoadBufferSE(EN_SE_CL3   , (Uint8 *)"sound/se/se03.wav" );
	soundLoadBufferSE(EN_SE_CL4   , (Uint8 *)"sound/se/se04.wav" );
	soundLoadBufferSE(EN_SE_CL5   , (Uint8 *)"sound/se/se05.wav" );
	soundLoadBufferSE(EN_SE_CL21   , (Uint8 *)"sound/se/se06.wav" );
	soundLoadBufferSE(EN_SE_CL22   , (Uint8 *)"sound/se/se07.wav" );
	soundLoadBufferSE(EN_SE_CL23   , (Uint8 *)"sound/se/se08.wav" );
	soundLoadBufferSE(EN_SE_CL24   , (Uint8 *)"sound/se/se09.wav" );
	soundLoadBufferSE(EN_SE_CL25   , (Uint8 *)"sound/se/se10.wav" );

	Set_Volume( gameflag[60] );

}

void ExitProgram(void)
{

	soundStopBgm(0);
	soundStopSeAll();
	soundRelease();

	SaveGameFlag("save/config");
	
	closePAD();
//	closeSDL();
	SDL_Quit();

#ifdef GP2X
	chdir("/usr/gp2x");
	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
}


void main_init_config( void )
{
	int i;
	i = 0;
	
	if ( ! ( LoadGameFlag("save/config") == 0 ) )
	{
		/* �t�@�C�������݂��Ȃ��ꍇ�̏����l�ݒ� */
		ResetGameFlag();
#ifdef GP2X
		gameflag[0]=GP2X_BUTTON_UP;		//��	Up
		gameflag[1]=GP2X_BUTTON_DOWN;	//��	Down
		gameflag[2]=GP2X_BUTTON_LEFT;	//��	Left
		gameflag[3]=GP2X_BUTTON_RIGHT;	//�E	Right
		gameflag[4]=GP2X_BUTTON_X;	//�`	Z
		gameflag[5]=GP2X_BUTTON_B;	//�a	X
		gameflag[6]=GP2X_BUTTON_Y;	//�b	C
		gameflag[7]=GP2X_BUTTON_A;	//�c	S
		gameflag[8]=GP2X_BUTTON_L;	//�c	S
		gameflag[9]=GP2X_BUTTON_R;	//�c	S
		gameflag[10]=GP2X_BUTTON_START;	//�c	S
		gameflag[11]=GP2X_BUTTON_SELECT;	//�c	S
#else 
		gameflag[0]=GP2X_BUTTON_UP;		//��	Up
		gameflag[1]=GP2X_BUTTON_DOWN;	//��	Down
		gameflag[2]=GP2X_BUTTON_LEFT;	//��	Left
		gameflag[3]=GP2X_BUTTON_RIGHT;	//�E	Right
		gameflag[4]=GP2X_BUTTON_A;	//�`	Z
		gameflag[5]=GP2X_BUTTON_X;	//�a	X
		gameflag[6]=GP2X_BUTTON_Y;	//�b	C
		gameflag[7]=GP2X_BUTTON_B;	//�c	S
		gameflag[8]=GP2X_BUTTON_L;	//�c	S
		gameflag[9]=GP2X_BUTTON_R;	//�c	S
		gameflag[10]=GP2X_BUTTON_START;	//�c	S
		gameflag[11]=GP2X_BUTTON_SELECT;	//�c	S
		gameflag[61] = 2;	//��ʔ{��
#endif
		
		gameflag[60] = 128;	//����

		gameflag[70] = 1;	//�^�C�g����ʂ��痈��
		gameflag[71] = 1;	//���g���C��I������


		gameflag[100] = 0;	//�N���A�t���O
		
		gameflag[107] = 0;	//play time s
		gameflag[108] = 0;	//play time s
		gameflag[109] = 0;	//play time m
		gameflag[110] = 0;	//play time h
		gameflag[111] = 59;	//CLEAR time s
		gameflag[112] = 59;	//CLEAR time m
		gameflag[113] = 99;	//CLEAR time h
		
		
		gameflag[120] = 1;	//�X�e�[�W�Z���N�g
		gameflag[121] = 1;	//���B�X�e�[�W
		gameflag[122] = 0;	//�L�����Z���N�g
		gameflag[123] = -1;	//���v���C�I�����̃X�e�[�W
		gameflag[124] = 0;	//���v���C�`�k�k�A�n�m�d
		gameflag[125] = 0;	//���v���Cjamp
		gameflag[126] = 0;	//����
		gameflag[127] = 0;	//�g�[�^���A�^�b�N
		gameflag[128] = 0;	//�}�b�v�r���[
		gameflag[129] = 0;	//�X�e�[�W�Z���N�g����J�n
		
		gameflag[131] = 0;	//����
		gameflag[132] = 0;	//���v���C
		gameflag[133] = 1;	//up key use
		gameflag[134] = 0;	//�J�n���o�̗L��

		gameflag[135] = 0;	//�g�[�^���A�^�b�N ����					[130]>[135]
		gameflag[136] = 0;	//�g�[�^���A�^�b�N �~�X				[131]>[136]
		gameflag[137] = 1595959;	//�g�[�^���A�^�b�N �N���A����	[132]>[137]
		gameflag[138] = 999;	//�g�[�^���A�^�b�N �N���A�~�X	[133]>[138]
		
		for ( i = 0; i <= 99; i++ )
		{
			gameflag[200 + i] = 1105959;
		}
		for ( i = 0; i <= 99; i++ )
		{
			gameflag[300 + i] = 99;
		}
		for ( i = 0; i <= 99; i++ )
		{
			gameflag[400 + i] = 0;
		}
	}
// for debug start
/*
		for ( i = 0; i <= 99; i++ )
		{
			gameflag[400 + i] = 1;
		}
*/
// for debug end
	gameflag[121] = 50;	//���B�X�e�[�W
//	gameflag[100] = 1;	//���B�X�e�[�W
	
	g_DebugDisp 				= GetConfig( CONFIGFILE_NAME , "DebugDisp" );
	g_DebugStageProduction 		= GetConfig( CONFIGFILE_NAME , "DebugStageProduction" );
}




