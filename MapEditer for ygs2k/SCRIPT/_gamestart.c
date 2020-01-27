/*[ gamestart.c ]****************************************************/
/*	�l�l�@�}�b�v�G�f�B�^�[�@�������@�������Q��						*/
/*------------------------------------------------------------------*/
/*	���	�^�P�]�[												*/
/*	�쐬��	2002/04/19												*/
/*	MAIL	syu@world.interq.or.jp									*/
/*	URL		http://www.interq.or.jp/black/kiku/takezo/				*/
/*																	*/
/*	Copyright (c) 2002 �^�P�]�[ All Rights Reserved.				*/
/*-[�X�V����]-------------------------------------------------------*/
/*	2002/04/23		�f�[�^�ۑ��������ȉ��̗l�ɕύX					*/
/*						�e�t�H���_���uMM�v�̏ꍇ					*/
/*							�u/MM/DATA/stage_no/�v�ɕۑ�			*/
/*						�e�t�H���_���uMM�v�ȊO�̏ꍇ				*/
/*							�u./savedata/stage_no/�v�ɕۑ�			*/
/*						�t�H���_�����݂��Ȃ��ꍇ�͎������������	*/
/*	2002/04/22		�}�b�v�A�}�b�v�`�b�v�ǂݍ��ݎ��ɓ��ߐF��ݒ�	*/
/*					����悤�ɏC��									*/
/*					�A�C�e���A�G�̔z�u�ɑΉ�						*/
/*	2002/04/19		������B										*/
/********************************************************************/

/*[ DLL�̃C���|�[�g ]************************************************/
import "lib/dir.dll"
import "lib/string.dll"
import "lib/patmatch.dll"
import "lib/FileDialog.dll"
import "lib/EditDialog.dll"
import "lib/tkzfile.dll"

/*[ �O���t�@�C���̃C���N���[�h ]*************************************/
include "script/function_library.c"

/*[ �O���[�o���ϐ���` ]*********************************************/
// �}�E�X�֘A
long MOUSE_X;
long MOUSE_Y;
long MOUSE_BUTTON = 0;	//  0			:	���͂Ȃ�,
						//  1(Push)		:	�E�N���b�N,  2:���N���b�N,  3:�����N���b�N,  4:�E�_�u���N���b�N
						// 11(Press)	:	�E�N���b�N, 12:���N���b�N, 13:�����N���b�N, 14:�E�_�u���N���b�N

long MDATA[1024];	// �}�b�v�f�[�^�z��
long IDATA[1024];	// �A�C�e���f�[�^�z��
long EDATA[1024];	// �G�f�[�^�z��
long ORG_M[1024];	// �}�b�v�f�[�^�X�V��r�p
long ORG_I[1024];	// �A�C�e���f�[�^�X�V��r�p
long ORG_E[1024];	// �G�f�[�^�X�V��r�p

long EDIT_LAYER = 0;	// �ҏW���C��		0	:	�}�b�v
						//					1	:	�A�C�e��
						//					2	:	�G

long DISP_LAYER[3] = { 1, 1, 1 };	// ���C���\���^��\��

long SEL_CHIP[3] = { 0, 0, 0 };	// ���ݑI������Ă���}�b�v�`�b�v

long MAP_LOADED[3]  = { 0, 0, 0 };	// �}�b�v�A�A�C�e���A�G�f�[�^�ǂݍ��ݍς݃t���O
long CHIP_LOADED[3] = { 0, 0, 0 };	// �}�b�v�A�A�C�e���A�G�`�b�v�ǂݍ��ݍς݃t���O

long STAGE_NO = 0;	// �X�e�[�W�ԍ�
long GAMEN_NO = 0;	// ��ʔԍ�
long ORG_STAGE_NO = -1;
long ORG_GAMEN_NO = -1;

long chip_x, chip_y;

/*[ main ]***********************************************************/
/*	���C���֐�														*/
/*-[����]-----------------------------------------------------------*/
/*	����															*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
/********************************************************************/
void main()
{
	long i,j;

	/********************************/
	/*	��������					*/
	/********************************/

	// FPS�ݒ�
	SetFPS( 60 );
	FPSLayerOn( 5, 350 );

	// �}�E�X�J�[�\���ǂݍ���
	LoadBitmap( "sysdat/mouse.bmp", 0, 0 );
	SetColorKeyPos( 0, 0, 0 );
	MouseLayerOn( 0, 1, 1 );

	// �}�b�v�A�}�b�v�`�b�v�w�i
	LoadBitmap( "sysdat/background.bmp", 2, 0 );
	CreateSurface( 1, 322, 242 );
	SwapToSecondary( 1 );
	BltFastRect( 2, 0, 0, 0, 0, 322, 242 );
	SwapToSecondary( 1 );

	// �}�X�ځi�P�}�X�j�̓ǂݍ���
	LoadBitmap( "sysdat/masu.bmp", 3, 0 );
	SetColorKeyPos( 3, 0, 0 );

	// �}�b�v�A�}�b�v�`�b�v�p�}�X�ڂ̍쐬
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
	CreateSurface( 33, 320, 240 );	// �}�b�v
	CreateSurface( 34, 320, 240 );	// �A�C�e��
	CreateSurface( 35, 320, 240 );	// �G

	// LOAD, SAVE�{�^���̓ǂݍ���
	LoadBitmap("sysdat/load.bmp", 4, 0 );
	LoadBitmap("sysdat/save.bmp", 5, 0 );
	LoadBitmap("sysdat/clear.bmp", 9, 0 );

	// �}�b�v�`�b�v�I���J�[�\���ǂݍ���
	LoadBitmap("sysdat/select_chip.bmp", 6, 0 );
	SetColorKeyPos( 6, 4, 4 );

	// �����摜�ǂݍ���
	LoadBitmap("sysdat/num.bmp", 7, 0 );
	SetColorKeyPos( 7, 0, 0 );

	// ���C���[
	LoadBitmap("sysdat/layer.bmp", 8, 0 );

	// �}�b�v�ݒ�̊e�{�^���ǂݍ���
	LoadBitmap("sysdat/stage.bmp", 21, 0 );
	LoadBitmap("sysdat/gamen.bmp", 22, 0 );
	LoadBitmap("sysdat/up_scroll.bmp", 23, 0 );
	LoadBitmap("sysdat/dn_scroll.bmp", 24, 0 );
	LoadBitmap("sysdat/l_scroll.bmp", 25, 0 );
	LoadBitmap("sysdat/r_scroll.bmp", 26, 0 );
	LoadBitmap("sysdat/retry.bmp", 27, 0 );
	LoadBitmap("sysdat/retry_xy.bmp", 28, 0 );

	/********************************/
	/*	�又��						*/
	/********************************/

	loop
	{
		ClearSecondary();
		SUB_GetMouseInfo();		// �}�E�X���͏��̎擾
		KeyInput();				// �L�[�{�[�h����

		/***** �L�[�{�[�h���͔��� *****/

		if ( IsPushEscKey() )
		{	// ESC�L�[�������ꂽ��I�����܂����I
			break;
		}

		/***** �}�E�X���͔��� *****/

		if ( ( MOUSE_X > 60 ) && ( MOUSE_X < 120 ) &&
			 ( MOUSE_Y >  4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // �}�b�v�̃��[�h���N���b�N���ꂽ
			MouseLayerOff();
			if ( EDIT_LAYER == 0 )
			{
				strcpy( string[1], "�}�b�v�f�[�^(n_n.map)=*.map" );
				strcpy( string[2], "%d_%d.map" );
				strcpy( string[3], "�}�b�v�摜(*.bmp)=*.bmp" );
			}
			else if ( EDIT_LAYER == 1 )
			{
				strcpy( string[1], "�A�C�e���f�[�^(*.map)=*.map" );
				strcpy( string[2], "i%d_%d.map" );
				strcpy( string[3], "�A�C�e���摜(*.bmp)=*.bmp" );
			}
			else
			{
				strcpy( string[1], "�G�f�[�^(*.map)=*.map" );
				strcpy( string[2], "e%d_%d.map" );
				strcpy( string[3], "�G�摜(*.bmp)=*.bmp" );
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
					SetConstParam( "MessageBox", "�K�r�[���I", "�l�l�p�̃}�b�v�t�@�C������Ȃ���" );
				}
			}
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X > 122 ) && ( MOUSE_X < 182 ) &&
			 ( MOUSE_Y >   4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // �}�b�v�̃Z�[�u���N���b�N���ꂽ
			MapDataSave();
			MouseLayerOff();
			SetConstParam( "MessageBox", "�Z�[�u���܂����B", "�Z�[�u���܂����B" );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X > 184 ) && ( MOUSE_X < 244 ) &&
			 ( MOUSE_Y >   4 ) && ( MOUSE_Y <  20 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // �}�b�v�̃N���A���N���b�N���ꂽ
			MouseLayerOff();
			if ( SetConstParam( "YesNo", "�m�F", "�S�ăN���A���Ă悢���ˁH" ) )
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
		{ // �}�b�v�`�b�v�̃��[�h���N���b�N���ꂽ
			MouseLayerOff();
			if ( EDIT_LAYER == 0 )
			{
				strcpy( string[1], "�}�b�v�摜(*.bmp)=*.bmp" );
			}
			else if ( EDIT_LAYER == 1 )
			{
				strcpy( string[1], "�A�C�e���摜(*.bmp)=*.bmp" );
			}
			else
			{
				strcpy( string[1], "�G�摜(*.bmp)=*.bmp" );
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
		{ // �}�b�v�`�b�v���N���b�N���ꂽ
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
		{ // �}�b�v�����N���b�N���ꂽ
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
		{ // �}�b�v���E�N���b�N���ꂽ
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
		{ // STAGE�����N���b�N���ꂽ
			MouseLayerOff();
			GetEditBox("STAGE�ԍ��𔼊p�����œ���", string[0] );
			STAGE_NO = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 270 ) && ( MOUSE_Y  < 286 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // ��ʔԍ������N���b�N���ꂽ
			MouseLayerOff();
			GetEditBox("��ʔԍ��𔼊p�����œ���", string[0] );
			GAMEN_NO = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 290 ) && ( MOUSE_Y  < 306 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // ��X�N���[�������N���b�N���ꂽ
			MouseLayerOff();
			GetEditBox("�X�N���[�����[ 0:�s��, 1:�ʏ�, 2:Wait ] �𔼊p�����œ���", string[0] );
			MDATA[320] = ValLong( string[0] );
			GetEditBox("�X�N���[�����ʔԍ��𔼊p�����œ���", string[0] );
			MDATA[321] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 290 ) && ( MOUSE_Y  < 306 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // ���X�N���[�������N���b�N���ꂽ
			MouseLayerOff();
			GetEditBox("�X�N���[�����[ 0:�s��, 1:�ʏ�, 2:Wait ] �𔼊p�����œ���", string[0] );
			MDATA[322] = ValLong( string[0] );
			GetEditBox("�X�N���[�����ʔԍ��𔼊p�����œ���", string[0] );
			MDATA[323] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 310 ) && ( MOUSE_Y  < 326 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // ���X�N���[�������N���b�N���ꂽ
			MouseLayerOff();
			GetEditBox("�X�N���[�����[ 0:�s��, 1:�ʏ�, 2:Wait ] �𔼊p�����œ���", string[0] );
			MDATA[324] = ValLong( string[0] );
			GetEditBox("�X�N���[�����ʔԍ��𔼊p�����œ���", string[0] );
			MDATA[325] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 310 ) && ( MOUSE_Y  < 326 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // �E�X�N���[�������N���b�N���ꂽ
			MouseLayerOff();
			GetEditBox("�X�N���[�����[ 0:�s��, 1:�ʏ�, 2:Wait ] �𔼊p�����œ���", string[0] );
			MDATA[326] = ValLong( string[0] );
			GetEditBox("�X�N���[�����ʔԍ��𔼊p�����œ���", string[0] );
			MDATA[327] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      >   5 ) && ( MOUSE_X  <  65 ) &&
			 ( MOUSE_Y      > 330 ) && ( MOUSE_Y  < 346 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // ���g���C��ʂ����N���b�N���ꂽ
			MouseLayerOff();
			GetEditBox("���g���C��ʔԍ� �𔼊p�����œ���", string[0] );
			MDATA[328] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 110 ) && ( MOUSE_X  < 170 ) &&
			 ( MOUSE_Y      > 330 ) && ( MOUSE_Y  < 346 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // ���g���C���W�����N���b�N���ꂽ
			MouseLayerOff();
			GetEditBox("���g���C���̂w���W�𔼊p�����œ���", string[0] );
			MDATA[329] = ValLong( string[0] );
			GetEditBox("���g���C���̂x���W�𔼊p�����œ���", string[0] );
			MDATA[330] = ValLong( string[0] );
			MouseLayerOn( 0, 1, 1 );
		}

		if ( ( MOUSE_X      > 244 ) && ( MOUSE_X  < 264 ) &&
			 ( MOUSE_Y      > 286 ) && ( MOUSE_Y  < 350 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // ���C���\���^��\�������N���b�N���ꂽ
			i = ( MOUSE_Y - 286 ) / 16;
			DISP_LAYER[i] = - DISP_LAYER[i];
		}

		if ( ( MOUSE_X      > 264 ) && ( MOUSE_X  < 324 ) &&
			 ( MOUSE_Y      > 286 ) && ( MOUSE_Y  < 350 ) &&
			 ( MOUSE_BUTTON == 2 ) )
		{ // �ҏW�Ώۃ��C�������N���b�N���ꂽ
			i = ( MOUSE_Y - 286 ) / 16;
			EDIT_LAYER = i;
		}

		/***** �`�揈�� *****/

		// ����
		TextLayerOff( 0 );
		TextLayerOn( 0, 4, 4 );
		TextOut( 0, "�}�b�v" );
		TextLayerOff( 1 );
		TextLayerOn( 1, 334, 4 );
		TextOut( 1, "�}�b�v�`�b�v" );

		// LOAD & SAVE
		BltFast( 4, 60,  4 );
		BltFast( 5, 122, 4 );
		BltFast( 9, 184, 4 );
		BltFast( 4, 434, 4 );

		// STAGE�ԍ��A��ʔԍ�
		BltFast( 21, 5, 270 );
		BltNumericImage( STAGE_NO, 2, 67, 270, 7, 0, 0, 8, 16 );
		BltFast( 22, 110, 270 );
		BltNumericImage( GAMEN_NO, 2, 172, 270, 7, 0, 0, 8, 16 );

		// �X�N���[���ݒ�
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

		// ���g���C��ʐݒ�
		BltFast( 27,   5, 330 );
		BltNumericImage( MDATA[328], 2, 67, 330, 7, 0, 0, 8, 16 );
		BltFast( 28, 110, 330 );
		BltNumericImage( MDATA[329], 2, 172, 330, 7, 0, 0, 8, 16 );
		BltNumericImage( MDATA[330], 2, 192, 330, 7, 0, 0, 8, 16 );

		// ���C���[
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

		// �}�b�v�A�}�b�v�`�b�v�w�i�`��
		BltFast( 1, 4, 24 );
		BltFast( 2, 334, 24 );

		if ( CHIP_LOADED[EDIT_LAYER] )
		{
			BltFast( 11 + EDIT_LAYER, 335, 25 );
		}

		// �}�b�v�̕`��
		for( i = 0; i < 3; i++ )
		{
			if ( DISP_LAYER[i] > 0 )
			{
				Blt( 33 + i, 5, 25 );
			}
		}

		// �}�b�v�A�}�b�v�`�b�v�}�X�ڕ`��
		Blt( 31,   5, 25 );
		Blt( 32, 335, 25 );

		// �}�b�v�`�b�v�I���J�[�\���`��
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
	/*	�I������					*/
	/********************************/

	MouseLayerOff();

	/***** �ۑ��m�F���� *****/
	for( i = 0; i < 1024; i++ )
	{
		if ( ( MDATA[i] != ORG_M[i] ) || ( IDATA[i] != ORG_I[i] ) || ( EDATA[i] != ORG_E[i] ) )
		{
			if ( SetConstParam( "YesNo", "�m�F", "�f�[�^��ۑ����ďI�����܂����H" ) )
			{
				MapDataSave();
			}
			break;
		}
	}

	/***** ��������� *****/
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
/*	�}�E�X���̎擾�֐�											*/
/*-[����]-----------------------------------------------------------*/
/*	����															*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
/********************************************************************/
void SUB_GetMouseInfo()
{
	long b;

	// �}�E�X���̎擾
	GetMouseInfo( &MOUSE_X, &MOUSE_Y, &b );

	// �{�^�����͂̔���
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
/*	�z�u�f�[�^�A�`�b�v�摜�ǂݍ��ݎ��̃��C���C���[�W�쐬�֐�		*/
/*-[����]-----------------------------------------------------------*/
/*	����															*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
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
/*	�}�b�v�A�A�C�e���A�G�f�[�^�ۑ��֐�								*/
/*-[����]-----------------------------------------------------------*/
/*	����															*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
/********************************************************************/
void MapDataSave()
{
	long i;

	if ( SearchFile( "../../", "mm" ) )
	{	// �e�t�H���_��"MM"
		// MM/DATA/n/���ɕۑ�
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
	{	// �e�t�H���_��"MM"�ȊO
		// ./savedata/n/���ɕۑ�
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
	// �}�b�v�f�[�^�X�V����
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
	// �A�C�e���f�[�^�X�V����
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
	// �G�f�[�^�X�V����
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
