/*[ function_library.c ]*********************************************/
/*	�ėp�֐��W														*/
/*------------------------------------------------------------------*/
/*	���	�^�P�]�[												*/
/*	�쐬��	2002/02/15												*/
/*	MAIL	syu@world.interq.or.jp									*/
/*	URL		http://www.interq.or.jp/black/kiku/takezo/				*/
/*																	*/
/*	Copyright (c) 2002 �^�P�]�[, �c�F�����C�_�}�X�B���ӂƁB			*/
/*											All Rights Reserved.	*/
/*-[�X�V����]-------------------------------------------------------*/
/*	2002/02/22	�R�s�[����`�͈͎w��v���[���T�C�Y�ύX�R�s�[�֐���	*/
/*				�쐬, �v���[���T�C�Y�ύX�R�s�[�֐����C��			*/
/*	2002/02/20	�v���[���T�C�Y�ύX�R�s�[�֐����쐬					*/
/*	2002/02/18	���l�摜�\���֐����쐬								*/
/*	2002/02/16	�t�@�C�����݃`�F�b�N�֐����쐬						*/
/*	2002/02/15	�z�񏉊����֐�, �X�N���[���V���b�g�ۑ��֐�,			*/
/*				��`�̈�X�N���[���V���b�g�ۑ��֐����쐬			*/
/*-[����]-----------------------------------------------------------*/
/*	YGS2K��p�BYGS2001�ł͎g���Ȃ���B								*/
/********************************************************************/

/*[ DLL�̃C���|�[�g ]************************************************/
/*
import "lib/dir.dll"	// �f�B���N�g���E���C�u����
 */
/*[ �O���t�@�C���̃C���N���[�h ]*************************************/

/*[ �O���[�o���ϐ���` ]*********************************************/

/*[ InitialyzeArray ]************************************************/
/*	�z�񏉊����֐�													*/
/*-[����]-----------------------------------------------------------*/
/*	*ARRAY		(io)	�z��̃|�C���^								*/
/*	size		(i )	�z��										*/
/*	value		(i )	�����l										*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
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
/*	�X�N���[���V���b�g�ۑ��֐�										*/
/*-[����]-----------------------------------------------------------*/
/*	filename	(i )	�ۑ�����t�@�C����							*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
/********************************************************************/
void SaveScreenShot( filename )
{
	// �Z�J���_���v���[������o�b�N�A�b�v�v���[���ɓ]��
	EnableBackupPlane();
	SnapToBackupPlane();
	halt;
	// �o�b�N�A�b�v�v���[����ۑ�
	SaveBackupPlane( filename );
	// �o�b�N�A�b�v�v���[���̎g�p�I��
	DisableBackupPlane();

	return;
}

/*[ SaveScreenShotRect ]*********************************************/
/*	��`�̈�X�N���[���V���b�g�ۑ��֐�								*/
/*-[����]-----------------------------------------------------------*/
/*	filename		(i )	�ۑ�����t�@�C����						*/
/*	wx, wy			(i )	�X�N���[���T�C�Y��, �c					*/
/*	plane			(i )	��`�ۑ��Ɉꎞ�I�Ɏg�p����v���[���ԍ�	*/
/*	x, y, sx, sy	(i )	�ۑ������`�͈͂��w��					*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
/********************************************************************/
void SaveScreenShotRect( filename, wx, wy, plane, x, y, sx, sy )
{
	// �Z�J���_���v���[������o�b�N�A�b�v�v���[���ɓ]��
	EnableBackupPlane();
	SnapToBackupPlane();
	halt;
	// �w��v���[���Ƀo�b�N�A�b�v�v���[������]��
	CreateSurface( plane, wx, wy );
	SwapToSecondary( plane );
	BltFromBackupPlane();
	SwapToSecondary( plane );
	// �w��v���[���̋�`�͈͂�ۑ�
	SaveBitmap( filename, plane, x, y, sx, sy );
	// �v���[���̉���ƃo�b�N�A�b�v�v���[���̎g�p�I��
	ReleaseBitmap( plane );
	DisableBackupPlane();

	return;
}

/*[ SearchFile ]*****************************************************/
/*	�t�@�C�����݃`�F�b�N�֐�										*/
/*-[����]-----------------------------------------------------------*/
/*	Path	(i )	�����Ώۃp�X									*/
/*	File	(i )	�����Ώۃt�@�C����								*/
/*-[�߂�l]---------------------------------------------------------*/
/*	0	�w��t�@�C���͑��݂��Ȃ�									*/
/*	1	�w��t�@�C�������݂���										*/
/********************************************************************/
long SearchFile( Path, File )
{
	long result[64];

	// �����Ώۃp�X�A�t�@�C������ݒ�
	EnableDirListup( 1 );
	SetFindPath( Path );
	SetFindFile( File );

	// ����
	if ( FindFile( &result ) )
	{
		return( 0 );	// ������Ȃ�����
	}
	else
	{
		return( 1 );	// ��������
	}
}

/*[ BltNumericImage ]************************************************/
/*	���l�摜�\���֐�												*/
/*-[����]-----------------------------------------------------------*/
/*	value			(i )	�摜�\�����鐔�l						*/
/*	length			(i )	�\�����錅���i�����ȏ�͕\������Ȃ��j	*/
/*	x				(i )	�摜��\������ʒu�����W				*/
/*	y				(i )	�摜��\������ʒu�����W				*/
/*	plane			(i )	���l�摜���ǂݍ��܂�Ă���v���[���ԍ�	*/
/*	num_stpos_x		(i )	�v���[�����ł̐��l�摜�̊J�n�ʒu�����W	*/
/*	num_stpos_y		(i )	�v���[�����ł̐��l�摜�̊J�n�ʒu�����W	*/
/*	num_width		(i )	���l�摜�P�����̕��i�h�b�g���j			*/
/*	num_height		(i )	���l�摜�P�����̍����i�h�b�g���j		*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
/********************************************************************/
void BltNumericImage( value, length, x, y, plane, num_stpos_x, num_stpos_y, num_width, num_height )
{
	long blt_num;	// �P���̐��l���i�[����
	long i;			// ��������for���[�v�Ŏg�p
	long dv;		// ����Z�Ŏg�p����l

	// value �����̒l�̏ꍇ�A���̒l�ɒu��������
	if ( value < 0 )
	{
		value = value * -1;
	}

	// �ŏ��̊���Z�Ŏg�p����l�����߂�
	dv = 1;
	for( i = 1; i < length; i++ )
	{
		dv = dv * 10;
	}

	// �w�肳�ꂽ�������̐����摜��]������
	for( i = 0; i < length; i++ )
	{
		// �\�����鐔�������߂�
		blt_num = value / dv;
		value = value - blt_num * dv;
		if ( blt_num > 9 )
		{	// �\���������P���̐��l�ɂȂ�Ȃ���΁A�P���ɂ���B
			blt_num = blt_num % 10;
		}
		// �����摜�]��
		BltRect( plane, x + (num_width * i), y, num_stpos_x + (num_width * blt_num), num_stpos_y, num_width, num_height );
		// ����Z�Ŏg�p����l��10�Ŋ���
		dv = dv / 10;
	}

	return;
}

/*[ PlaneResizeCopy ]************************************************/
/*	�v���[���T�C�Y�ύX�R�s�[�֐�									*/
/*-[����]-----------------------------------------------------------*/
/*	to_plane_no		(i )	�R�s�[��v���[���ԍ�					*/
/*	from_plane_no	(i )	�R�s�[���v���[���ԍ�					*/
/*	func			(i )	�R�s�[�T�C�Y�ݒ�						*/
/*								0:�T�C�Y�w��						*/
/*								1:�{���w��i���Ŏw��j				*/
/*	to_x			(i )	�R�s�[�T�C�Y����						*/
/*	to_y			(i )	�R�s�[�T�C�Y����						*/
/*	color_key		(i )	���߃L�[								*/
/*								0:����								*/
/*								1:�L��								*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
/********************************************************************/
void PlaneResizeCopy( to_plane_no, from_plane_no, func, to_x, to_y, color_key )
{
	long to_plane_x, to_plane_y, from_plane_x, from_plane_y;
	long resize_x, resize_y;

	// �g��k���������߂�
	GetPlaneSize( from_plane_no, &from_plane_x, &from_plane_y );
	if ( func == 0 )
	{	// �T�C�Y�w��
		to_plane_x = to_x;
		to_plane_y = to_y;
		resize_x   = 65536 * (to_plane_x * 100 / from_plane_x) / 100;
		resize_y   = 65536 * (to_plane_y * 100 / from_plane_y) / 100;
	}
	else
	{	// �{���w��
		to_plane_x = from_plane_x * to_x / 100;
		to_plane_y = from_plane_y * to_y / 100;
		resize_x   = 65536 * to_x / 100;
		resize_y   = 65536 * to_y / 100;
	}

	// �v���[���摜���R�s�[
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
/*	�R�s�[����`�͈͎w��v���[���T�C�Y�ύX�R�s�[�֐�				*/
/*-[����]-----------------------------------------------------------*/
/*	to_plane_no		(i )	�R�s�[��v���[���ԍ�					*/
/*	from_plane_no	(i )	�R�s�[���v���[���ԍ�					*/
/*	func			(i )	�R�s�[�T�C�Y�ݒ�						*/
/*								0:�T�C�Y�w��						*/
/*								1:�{���w��i���Ŏw��j				*/
/*	to_x			(i )	�R�s�[�T�C�Y����						*/
/*	to_y			(i )	�R�s�[�T�C�Y����						*/
/*  from_sx			(i )	�R�s�[���v���[���]�������W����			*/
/*	from_sy			(i )	�R�s�[���v���[���]�������W����			*/
/*	from_hx			(i )	�R�s�[���v���[���]����`�T�C�Y����		*/
/*	from_hy			(i )	�R�s�[���v���[���]����`�T�C�Y����		*/
/*	color_key		(i )	���߃L�[								*/
/*								0:����								*/
/*								1:�L��								*/
/*-[�߂�l]---------------------------------------------------------*/
/*	����															*/
/********************************************************************/
void PlaneResizeCopyFromRect( to_plane_no, from_plane_no, func, to_x, to_y,
							  from_sx, from_sy, from_hx, from_hy, color_key )
{
	long to_plane_x, to_plane_y;
	long resize_x, resize_y;

	// �g��k���������߂�
	if ( func == 0 )
	{	// �T�C�Y�w��
		to_plane_x = to_x;
		to_plane_y = to_y;
		resize_x   = 65536 * (to_plane_x * 100 / from_hx) / 100;
		resize_y   = 65536 * (to_plane_y * 100 / from_hy) / 100;
	}
	else
	{	// �{���w��
		to_plane_x = from_hx * to_x / 100;
		to_plane_y = from_hy * to_y / 100;
		resize_x   = 65536 * to_x / 100;
		resize_y   = 65536 * to_y / 100;
	}

	// �v���[���摜���R�s�[
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

