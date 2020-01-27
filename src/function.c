#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "SDL.h"
#include "SDL_mixer.h"
#include "define.h"
#include "function.h"
#include "extern.h"
#include "util_snd.h"
#include "include/general.h"
#include "include/dconv.h"
#include "SDL_rotozoom.h"

void FunctionInit( void );
void ResetGameFlag( void );
void ResetGameFlag2( void );
int LoadGameFlag( char *fn );
int SaveGameFlag( char *fn );
int LoadGameFlag2( char *fn );
int SaveGameFlag2( char *fn );
int SaveFile( char *fn, long *buff, long size );
int LoadFile( char *fn, long *buff, long size );
long GetConfig( char* fn, char* cParam );
long LogFileWrite( char* fn, char* cParam );

long LoadBitmap( char *fname , int bmpindex, int flag );
void ReleaseBitmap( int bmpindex );
void BltRect(int bmpindex, int srcX, int srcY, int dstX, int dstY, int width, int height);
void Blt( int bmpindex, int dstX, int dstY );
void SetColorKey(int bmpindex, int flag );
void SetColorKeyPos(int bank, Uint32 color);
void ClearSecondary( void );
void BltNumericImage( long value, long length, long x, long y, long plane, long num_stpos_x, long num_stpos_y, long num_width, long num_height );
void BltNumericImage2( long value, long length, long x, long y, long plane, long num_stpos_x, long num_stpos_y, long num_width, long num_height );
long get2keta( long val, long st );
void SetGscreenPalette( SDL_Surface *surface );
void SetPalette(int getbmpindex, int setbmpindex);
void BltRectRotZoom( int bmpindex, int dstX, int dstY, int srcX, int srcY, int width, int height, double angle, double zoom, int smooth);
void CreateSurface( int bmpindex, int size_x, int size_y  );
void SwapToSecondary( int bmpindex );
void SaveBmp( int bmpindex, char *fn );
void drawGRPline(f32 x1, f32 y1, f32 x2, f32 y2, Uint32 color);
void pointSDLsurface( f32 px, f32 py, Uint32 color);
inline void putSDLpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void BltGSreface( int rr );
void halt( void );

int IsPushKey( int keycode );
int IsPressKey( int keycode );
void KeyInit( void );
void KeyInput( void );
int initPAD(void);
void closePAD(void);
int getPAD(void);
int IsPushOKKey( void );
int IsPushCancelKey( void );

void FPSWait( void );
int system_keys( void );
int Set_Volume( int vol );

void soundInitBuffer(void);
void soundRelease(void);
void soundLoadBuffer(Sint32 num, Uint8 *fname, int loop);

long funcSin( long rdo );
long funcCos( long rdo );
long funcTan2( long posX, long posY );

// キー取得用
static int key_eventPress[GP2X_BUTTON_MAX];
static int key_eventPress_old[GP2X_BUTTON_MAX];
static int key_eventPush[GP2X_BUTTON_MAX];
int	pad_type;
int	pads;
int	trgs;
int	reps;

SDL_Joystick *joys;
Uint8 *keys;

//static int pads_old;
static int rep_cnt;
// 画像表示用
static SDL_Surface* bitmap[BMPBUFF_MAX];
static SDL_Surface* g_surface_bakup;
// 定時処理用
static long prvTickCount;
static long nowTick;
//static int frame;
#ifdef GP2X
//static const int INTERVAL_BASE = 8;
static const int INTERVAL_BASE = 16;
#else
static const int INTERVAL_BASE = 16;
#endif
SDL_Event event;

// 音楽再生
static long sound_vol;

void FunctionInit( void )
{
	int i;
	
	prvTickCount = 0;
	
	for ( i = 0; i < BMPBUFF_MAX; i++ )
	{
		bitmap[i] = NULL;
	}
	KeyInit( );
	soundInitBuffer();

}

void ResetGameFlag( void )
{
	memset( &gameflag[0], 0, sizeof( gameflag ) );
}
int LoadGameFlag( char *fn )
{
	int rc = 0;
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	int size;
	
	/* (2)ファイルのオープン */
	/*  ここで、ファイルポインタを取得する */
	if ( ( fp = fopen( fn, "rb" ) ) == NULL )
	{
//		printf("file open error!!\n");
		rc = -1;	/* (3)エラーの場合は通常、異常終了する */
	}
	else 
	{
		/* (4)ファイルの読み（書き）*/
		size = fread( &gameflag[0], 1, sizeof( gameflag ), fp );  /* 5000バイト分読み込む */
		fclose( fp );	/* (5)ファイルのクローズ */
#ifdef GP2X
		sync( );
#endif
	}
	
	return ( rc );
}
int SaveGameFlag( char *fn )
{
	int rc = 0;
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	int size;
	
	/* (2)ファイルのオープン */
	/*  ここで、ファイルポインタを取得する */
	if ( ( fp = fopen( fn, "wb" ) ) == NULL )
	{
//		printf("file open error!!\n");
		rc = -1;	/* (3)エラーの場合は通常、異常終了する */
	}
	else 
	{
		/* (4)ファイルの読み（書き）*/
		size = fwrite( &gameflag[0], 1, sizeof( gameflag ), fp );  /* 5000バイト分読み込む */
		fclose( fp );	/* (5)ファイルのクローズ */
#ifdef GP2X
		sync( );
#endif
	}
	
	return ( rc );
}
void ResetGameFlag2( void )
{
	memset( &gameflag2[0], 0, sizeof( gameflag ) );
}
int LoadGameFlag2( char *fn )
{
	int rc = 0;
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	int size;
	
	/* (2)ファイルのオープン */
	/*  ここで、ファイルポインタを取得する */
	if ( ( fp = fopen( fn, "rb" ) ) == NULL )
	{
//		printf("file open error!!\n");
		rc = -1;	/* (3)エラーの場合は通常、異常終了する */
	}
	else 
	{
		/* (4)ファイルの読み（書き）*/
		size = fread( &gameflag2[0], 1, sizeof( gameflag ), fp );  /* 5000バイト分読み込む */
		fclose( fp );	/* (5)ファイルのクローズ */
#ifdef GP2X
		sync( );
#endif
	}
	
	return ( rc );
}
int SaveGameFlag2( char *fn )
{
	int rc = 0;
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	int size;
	
	/* (2)ファイルのオープン */
	/*  ここで、ファイルポインタを取得する */
	if ( ( fp = fopen( fn, "wb" ) ) == NULL )
	{
//		printf("file open error!!\n");
		rc = -1;	/* (3)エラーの場合は通常、異常終了する */
	}
	else 
	{
		/* (4)ファイルの読み（書き）*/
		size = fwrite( &gameflag2[0], 1, sizeof( gameflag ), fp );  /* 5000バイト分読み込む */
		fclose( fp );	/* (5)ファイルのクローズ */
#ifdef GP2X
		sync( );
#endif
	}
	
	return ( rc );
}
int SaveFile( char *fn, long *buff, long size )
{
	int rc = 0;
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	
	/* (2)ファイルのオープン */
	/*  ここで、ファイルポインタを取得する */
	if ( ( fp = fopen( fn, "wb" ) ) == NULL )
	{
//		printf("file open error!!\n");
		rc = -1;	/* (3)エラーの場合は通常、異常終了する */
	}
	else 
	{
		/* (4)ファイルの読み（書き）*/
		size = fwrite( buff, 1, size, fp );  /* 5000バイト分読み込む */
		fclose( fp );	/* (5)ファイルのクローズ */
#ifdef GP2X
		sync( );
#endif
	}
	
	return ( rc );
}
int LoadFile( char *fn, long *buff, long size )
{
	int rc = 0;
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	
	/* (2)ファイルのオープン */
	/*  ここで、ファイルポインタを取得する */
	if ( ( fp = fopen( fn, "rb" ) ) == NULL )
	{
//		printf("file open error!!\n");
		rc = -1;	/* (3)エラーの場合は通常、異常終了する */
	}
	else 
	{
		/* (4)ファイルの読み（書き）*/
		size = fread( buff, 1, size, fp );  /* 5000バイト分読み込む */
		fclose( fp );	/* (5)ファイルのクローズ */
#ifdef GP2X
		sync( );
#endif
	}
	
	return ( rc );
}

long GetConfig( char* fn, char* cParam )
{
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	char *sp;
	char s[256];
	char s2[256];
	memset( s, '\0', sizeof( s ) );
	long rc;
	
	rc = 0;
	/* (2)ファイルのオープン */
	/*  ここで、ファイルポインタを取得する */
	if ( ( fp = fopen( fn, "r" ) ) == NULL )
	{
		rc = 0;	/* (3)エラーの場合は通常、異常終了する */
	}
	else 
	{
		/* (4)ファイルの読み（書き）*/
		while ( fgets( s, 256, fp ) != NULL) 
		{
			/* ここではfgets()により１行単位で読み出し */
			if ( strstr( s, cParam ) != NULL )
			{
				sp = NULL;
				//文字列が存在する
				sp = strstr( s, "=" );
				if ( sp != NULL )
				{
					sp++;
					memset( s2, '\0', sizeof( s ) );
					if ( ! ( ( *sp >= '0' && *sp <= '9' ) || ( *sp =='-' ) ) )
					{
						return 0;	//	だめびゃん...
					}
					while ( *sp >= '0' && *sp <= '9' )
					{
						rc = rc * 10 + ( *sp - '0' );
						sp++;
					}
				}
				break;
			}
			memset( s, '\0', sizeof( s ) );
		}
#ifdef GP2X
		sync( );
#endif
	}
	return( rc );
}

long LogFileWrite( char* fn, char* cParam )
{
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	long rc;
	
	rc = 0;
	/* (2)ファイルのオープン */
	/*  ここで、ファイルポインタを取得する */
	if ( ( fp = fopen( fn, "w" ) ) == NULL )
	{
		rc = 0;	/* (3)エラーの場合は通常、異常終了する */
	}
	else 
	{
		fputs( cParam, fp);
#ifdef GP2X
		sync( );
#endif
	}
	return( rc );
}

long LoadBitmap( char *fname , int bmpindex, int flag )
{
	long rc;
	SDL_Surface* tmp;

	rc = 0;
	
	ReleaseBitmap( bmpindex );


	tmp = SDL_LoadBMP( fname );
	if(tmp)
	{
		if(flag != 0)
		{
			// パレット０番が透過色
			SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, SDL_MapRGBA(g_screen->format,0,0,0,0) );
		}
		bitmap[bmpindex] = SDL_DisplayFormat(tmp);
//		bitmap[bmpindex] = tmp;
		SDL_FreeSurface(tmp);
	}
	else 
	{
		rc = -1;
	}

//	bitmap[bmpindex] = SDL_LoadBMP( fname );
	if(bitmap[bmpindex])
	{
		if(flag != 0)
		{
			SDL_Surface *surface;
		    Uint8 bpp;
			SDL_Palette *pal;
			Uint8 r;
			Uint8 g;
			Uint8 b;

			surface = bitmap[bmpindex];
		    if(surface){
			    bpp = surface->format->BytesPerPixel;
				if(bpp <= 1){
					pal = surface->format->palette;
					if(pal){
						r = pal->colors->r;
						g = pal->colors->g;
						b = pal->colors->b;
						// パレット０番が透過色
						SDL_SetColorKey(bitmap[bmpindex], SDL_SRCCOLORKEY, SDL_MapRGBA(g_screen->format,r,g,b,0) );
					}
				}
			}
		}
	}
	else 
	{
		rc = -1;
	}


	return ( rc );
}
void SetColorKey(int bmpindex, int flag )
{
	if(flag != 0)
	{
		SDL_Surface *surface;
	    Uint8 bpp;
		SDL_Palette *pal;
		Uint8 r;
		Uint8 g;
		Uint8 b;

		surface = bitmap[bmpindex];
	    if(surface){
		    bpp = surface->format->BytesPerPixel;
			if(bpp <= 1){
				pal = surface->format->palette;
				if(pal){
					r = pal->colors->r;
					g = pal->colors->g;
					b = pal->colors->b;
					// パレット０番が透過色
					SDL_SetColorKey(bitmap[bmpindex], SDL_SRCCOLORKEY, SDL_MapRGBA(g_screen->format,r,g,b,0) );
				}
			}
		}
	}
	else 
	{
		SDL_SetColorKey(bitmap[bmpindex], 0, SDL_MapRGBA(g_screen->format,0,0,0,0) );
	}
}
// 未使用
void SetColorKeyPos(int bmpindex, Uint32 color)
{
//	SDL_GetRGBA(Uint32 pixel, SDL_PixelFormat *fmt, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);
	SDL_SetColorKey(bitmap[bmpindex], SDL_SRCCOLORKEY, color);
}
// BMPの開放
void ReleaseBitmap( int bmpindex )
{
	if ( bitmap[bmpindex] != NULL )
	{
		SDL_FreeSurface(bitmap[bmpindex]);
		bitmap[bmpindex] = NULL;
	}
}
// ＢＭＰ範囲指定表示
void BltRect( int bmpindex, int dstX, int dstY, int srcX, int srcY, int width, int height)
{
	SDL_Rect srcRect;
	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = width;
	srcRect.h = height;

	SDL_Rect dstRect;
	dstRect.x = dstX;
	dstRect.y = dstY;
	dstRect.w = width;
	dstRect.h = height;

	if(bitmap[bmpindex])
	{
		SDL_BlitSurface(bitmap[bmpindex], &srcRect, g_screen, &dstRect);
	}
}
// ＢＭＰ範囲指定表示
void Blt( int bmpindex, int dstX, int dstY )
{
	SDL_Rect dstRect;
	dstRect.x = dstX;
	dstRect.y = dstY;
	dstRect.w = 0;
	dstRect.h = 0;

	if(bitmap[bmpindex])
	{
		SDL_BlitSurface(bitmap[bmpindex], NULL, g_screen, &dstRect);
	}
}
void SetGscreenPalette( SDL_Surface *surface )
{
//	SDL_Surface *surface;
    Uint8 bpp;
	SDL_Palette *pal;

//	surface = bitmap[bmpindex];
    if(surface){
	    bpp = surface->format->BytesPerPixel;
		if(bpp <= 1){
			pal = surface->format->palette;
			if(pal){
				SDL_SetPalette(g_screen, SDL_LOGPAL|SDL_PHYSPAL, pal->colors, 0, 256);
			}
		}
	}
}
void SetPalette(int getbmpindex, int setbmpindex)
{
	SDL_Surface *surface;
    Uint8 bpp;
	SDL_Palette *pal;

	surface = bitmap[getbmpindex];
    if(surface){
	    bpp = surface->format->BytesPerPixel;
		if(bpp <= 8){
			pal = surface->format->palette;
			if(pal){
				SDL_SetPalette(bitmap[setbmpindex], SDL_LOGPAL|SDL_PHYSPAL, pal->colors, 0, 256);
			}
		}
	}
}
void SaveBmp( int bmpindex, char *fn )
{
	if ( bmpindex >= 0 )
	{
		SDL_SaveBMP(bitmap[bmpindex], fn);
	}
	else 
	{
		SDL_SaveBMP(g_screen, fn);
	}
}
void CreateSurface( int bmpindex, int size_x, int size_y  )
{
	SDL_Surface* tmp;
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

	ReleaseBitmap( bmpindex );
	tmp = SDL_CreateRGBSurface( SDL_SWSURFACE, size_x, size_y, 0, rmask, gmask, bmask, amask );
	if(tmp)
	{
		bitmap[bmpindex] = SDL_DisplayFormat(tmp);
		SDL_FreeSurface(tmp);
	}
}

void SwapToSecondary( int bmpindex )
{
	if ( g_surface_bakup != NULL )
	{
		g_screen = g_surface_bakup;
		g_surface_bakup = NULL;
	}
	else 
	{
		g_surface_bakup = g_screen;
		g_screen = bitmap[bmpindex];
	}
} 
// ＢＭＰ範囲指定表示
void BltRectRotZoom( int bmpindex, int dstX, int dstY, int srcX, int srcY, int width, int height, double angle, double zoom, int smooth)
{

	SDL_Surface *temp_Surface;
	
	temp_Surface = rotozoomSurface(bitmap[bmpindex], angle, zoom, smooth);
	SDL_Surface *surface;
    Uint8 bpp;
	SDL_Palette *pal;
	Uint8 r;
	Uint8 g;
	Uint8 b;

	surface = bitmap[bmpindex];
    if(surface){
	    bpp = surface->format->BytesPerPixel;
		if(bpp <= 8){
			pal = surface->format->palette;
			if(pal){
				SDL_SetPalette(temp_Surface, SDL_LOGPAL|SDL_PHYSPAL, pal->colors, 0, 256);
				r = pal->colors->r;
				g = pal->colors->g;
				b = pal->colors->b;
				// パレット０番が透過色
				SDL_SetColorKey(temp_Surface, SDL_SRCCOLORKEY, SDL_MapRGBA(g_screen->format,r,g,b,0) );
			}
		}
	}
	
//	SDL_SaveBMP(SDL_DisplayFormat(temp_Surface), "tempbmp.bmp");
	
	
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = temp_Surface->w;
	srcRect.h = temp_Surface->h;

	SDL_Rect dstRect;
	dstRect.x = dstX - ( temp_Surface->w / 2 );
	dstRect.y = dstY - ( temp_Surface->h / 2 );
	dstRect.w = temp_Surface->w;
	dstRect.h = temp_Surface->h;

	SDL_BlitSurface( temp_Surface , &srcRect, g_screen, &dstRect);
	SDL_FreeSurface(temp_Surface);
}


// 背景のクリア
void ClearSecondary( void )
{
	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = DISPLY_WIDTH;
	rect.h = DISPLY_HEIGHT;
	
	
	SDL_FillRect(g_screen, &rect, SDL_MapRGBA(g_screen->format,0,0,0,255));
}

// ラインの描画
void drawGRPline(f32 x1, f32 y1, f32 x2, f32 y2, Uint32 color)
{
	f32 x, y, dx, dy, s, step;
	int i, j;

	dx = abs((x2 >> 16) - (x1 >> 16)) * WP;
	dy = abs((y2 >> 16) - (y1 >> 16)) * WP;

	x = x1;
	y = y1;
/*
	if(x >= DISPLY_WIDTH_WP) x -= DISPLY_WIDTH_WP;
	if(x <  0) x += DISPLY_WIDTH_WP;
	if(y >= DISPLY_HEIGHT_WP) y -= DISPLY_HEIGHT_WP;
	if(y <  0) y += DISPLY_HEIGHT_WP;
*/
	if(dx > dy){
		if(x1 > x2){
			step = (y1 > y2) ? +1 * WP : -1 * WP;
			s = x1;
			x1 = x2;
			x2 = s;
			y1 = y2;
		}else{
			step = (y1 < y2) ? +1 * WP : -1 * WP;
		}
		pointSDLsurface( x, y, color);
		s = dx / 2 * WP;
		i = x1 >> 16;
		j = x2 >> 16;
		while(++i <= j){
			x1 += 1 * WP;
//			if(x1 >= DISPLY_WIDTH_WP) x1 -= DISPLY_WIDTH_WP;
//			if(x1 <  0) x1 += DISPLY_WIDTH_WP;
			s -= dy;
			if(s < 0){
				s += dx;
				y1 += step;
			}
//			if(y1 >= DISPLY_HEIGHT_WP) y1 -= DISPLY_HEIGHT_WP;
//			if(y1 <  0) y1 += DISPLY_HEIGHT_WP;
			pointSDLsurface( x1 + WP, y1,      color);
			pointSDLsurface( x1 + WP, y1 + WP, color);
			pointSDLsurface( x1 + WP, y1 - WP, color);

			pointSDLsurface( x1,      y1,      color);
			pointSDLsurface( x1,      y1 + WP, color);
			pointSDLsurface( x1,      y1 - WP, color);

			pointSDLsurface( x1 - WP, y1,      color);
			pointSDLsurface( x1 - WP, y1 + WP, color);
			pointSDLsurface( x1 - WP, y1 - WP, color);
		}
	}else{
		if(y1 > y2){
			step = (x1 > x2) ? +1 * WP : -1 * WP;
			s = y1;
			y1 = y2;
			y2 = s;
			x1 = x2;
		}else{
			step = (x1 < x2)? +1 * WP : -1 * WP;
		}
		pointSDLsurface( x, y, color);
		s = dy / 2 * WP;
		i = y1 >> 16;
		j = y2 >> 16;
		while(++i <= j){
			y1 += 1 * WP;
//			if(y1 >= DISPLY_HEIGHT_WP) y1 -= DISPLY_HEIGHT_WP;
//			if(y1 <  0) y1 += DISPLY_HEIGHT_WP;
			s -= dx;
			if(s < 0){
				s += dy;
				x1 += step;
			}
//			if(x1 >= DISPLY_WIDTH_WP) x1 -= DISPLY_WIDTH_WP;
//			if(x1 <  0) x1 += DISPLY_WIDTH_WP;
			pointSDLsurface( x1 + WP, y1,      color);
			pointSDLsurface( x1 + WP, y1 + WP, color);
			pointSDLsurface( x1 + WP, y1 - WP, color);

			pointSDLsurface( x1,      y1,      color);
			pointSDLsurface( x1,      y1 + WP, color);
			pointSDLsurface( x1,      y1 - WP, color);

			pointSDLsurface( x1 - WP, y1,      color);
			pointSDLsurface( x1 - WP, y1 + WP, color);
			pointSDLsurface( x1 - WP, y1 - WP, color);
		}
	}
}
void pointSDLsurface( f32 px, f32 py, Uint32 color)
{
	if ( px < 0 || px >= ( DISPLY_WIDTH_WP ) || py < 0 || py >= ( DISPLY_HEIGHT_WP ) ){
		return;
	}

	putSDLpixel(g_screen, px, py, color);
}

inline void putSDLpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + (y >> 16) * surface->pitch + (x >> 16) * bpp;

    switch(bpp){
	    case 1:
	        *p = pixel;
	        break;
	    case 2:
	        *(Uint16 *)p = pixel;
	        break;
	    case 3:
	        if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
	            p[0] = (pixel >> 16) & 0xff;
	            p[1] = (pixel >> 8) & 0xff;
	            p[2] = pixel & 0xff;
	        }else{
	            p[0] = pixel & 0xff;
	            p[1] = (pixel >> 8) & 0xff;
	            p[2] = (pixel >> 16) & 0xff;
	        }
	        break;
	    case 4:
	        *(Uint32 *)p = pixel;
	        break;
    }
}

void KeyInit( void )
{
	int i;
	
	/* initialize */
/*
	SDL_Init(SDL_INIT_JOYSTICK|SDL_INIT_VIDEO);
	SDL_JoystickOpen(0);
*/
	sound_vol = 128;
	 
	for ( i = 0; i < GP2X_BUTTON_MAX; i++ )
	{
		key_eventPress[i] = 0;
		key_eventPress_old[i] = 0;
		key_eventPush[i] = 0;
	}

	initPAD( );
}
int initPAD(void)
{
	if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0){
		return 0;
    }

	if(SDL_NumJoysticks() > 0){
		joys = SDL_JoystickOpen(0);
		SDL_JoystickEventState(SDL_ENABLE);
	}else{
		joys = NULL;
	}

	pad_type = 0;
	trgs = 0;
	reps = 0;

	rep_cnt = 0;

	return 1;
}
void closePAD(void)
{
	if(SDL_JoystickOpened(0)){
		SDL_JoystickClose(joys);
	}
}

void KeyInput( void )
{
	int i;
#ifdef GP2X
	int pad = 0;

	keys = SDL_GetKeyState(NULL);

	if(joys){
		if(SDL_JoystickGetButton(joys,  0)) pad |= PAD_UP;
		if(SDL_JoystickGetButton(joys,  1)) pad |= PAD_UP | PAD_LEFT;
		if(SDL_JoystickGetButton(joys,  2)) pad |= PAD_LEFT;
		if(SDL_JoystickGetButton(joys,  3)) pad |= PAD_DOWN | PAD_LEFT;
		if(SDL_JoystickGetButton(joys,  4)) pad |= PAD_DOWN;
		if(SDL_JoystickGetButton(joys,  5)) pad |= PAD_DOWN | PAD_RIGHT;
		if(SDL_JoystickGetButton(joys,  6)) pad |= PAD_RIGHT;
		if(SDL_JoystickGetButton(joys,  7)) pad |= PAD_UP | PAD_RIGHT;
		if(SDL_JoystickGetButton(joys, 12)) pad |= PAD_BUTTON1;
		if(SDL_JoystickGetButton(joys, 15)) pad |= PAD_BUTTON2;
		if(SDL_JoystickGetButton(joys, 14)) pad |= PAD_BUTTON3;
		if(SDL_JoystickGetButton(joys, 13)) pad |= PAD_BUTTON4;
		if(SDL_JoystickGetButton(joys, 11)) pad |= PAD_BUTTON5;
		if(SDL_JoystickGetButton(joys, 10)) pad |= PAD_BUTTON6;
		if(SDL_JoystickGetButton(joys, 17)) pad |= PAD_BUTTON7;
		if(SDL_JoystickGetButton(joys, 16)) pad |= PAD_BUTTON8;
		if(SDL_JoystickGetButton(joys,  9)) pad |= PAD_BUTTON9;
		if(SDL_JoystickGetButton(joys,  8)) pad |= PAD_BUTTONA;
		if(SDL_JoystickGetButton(joys, 18)) pad |= PAD_BUTTONB;
	}
#else
	int x = 0, y = 0;
	int pad = 0;

	keys = SDL_GetKeyState(NULL);

	if(joys){
		x = SDL_JoystickGetAxis(joys, 0);
		y = SDL_JoystickGetAxis(joys, 1);
	}
	if(pad_type == 0){
		if(keys[SDLK_RIGHT] == SDL_PRESSED || keys[SDLK_KP6] == SDL_PRESSED || x > JOYSTICK_AXIS){
			pad |= PAD_RIGHT;
		}
		if(keys[SDLK_LEFT] == SDL_PRESSED || keys[SDLK_KP4] == SDL_PRESSED || x < -JOYSTICK_AXIS){
			pad |= PAD_LEFT;
		}
		if(keys[SDLK_DOWN] == SDL_PRESSED || keys[SDLK_KP2] == SDL_PRESSED || y > JOYSTICK_AXIS){
			pad |= PAD_DOWN;
		}
		if(keys[SDLK_UP] == SDL_PRESSED || keys[SDLK_KP8] == SDL_PRESSED || y < -JOYSTICK_AXIS){
			pad |= PAD_UP;
		}
	}
	if(pad_type == 1){
		if(keys[SDLK_d] == SDL_PRESSED || keys[SDLK_KP6] == SDL_PRESSED || x > JOYSTICK_AXIS){
			pad |= PAD_RIGHT;
		}
		if(keys[SDLK_a] == SDL_PRESSED || keys[SDLK_KP4] == SDL_PRESSED || x < -JOYSTICK_AXIS){
			pad |= PAD_LEFT;
		}
		if(keys[SDLK_s] == SDL_PRESSED || keys[SDLK_KP2] == SDL_PRESSED || y > JOYSTICK_AXIS){
			pad |= PAD_DOWN;
		}
		if(keys[SDLK_w] == SDL_PRESSED || keys[SDLK_KP8] == SDL_PRESSED || y < -JOYSTICK_AXIS){
			pad |= PAD_UP;
		}
	}

	int	btn1 = 0, btn2 = 0, btn3 = 0, btn4 = 0, btn5 = 0, btn6 = 0, btn7 = 0, btn8 = 0, btn9 = 0, btnA = 0;

	if(joys){
		btn1 = SDL_JoystickGetButton(joys, 0);
		btn2 = SDL_JoystickGetButton(joys, 1);
		btn3 = SDL_JoystickGetButton(joys, 2);
		btn4 = SDL_JoystickGetButton(joys, 3);
		btn5 = SDL_JoystickGetButton(joys, 4);
		btn6 = SDL_JoystickGetButton(joys, 5);
		btn7 = SDL_JoystickGetButton(joys, 6);
		btn8 = SDL_JoystickGetButton(joys, 7);
		btn9 = SDL_JoystickGetButton(joys, 8);
		btnA = SDL_JoystickGetButton(joys, 9);
	}
	if(pad_type == 0){
		if(keys[SDLK_z] == SDL_PRESSED || btn1){
			pad |= PAD_BUTTON1;
		}
		if(keys[SDLK_x] == SDL_PRESSED || btn2){
			pad |= PAD_BUTTON2;
		}
		if(keys[SDLK_c] == SDL_PRESSED || btn3){
			pad |= PAD_BUTTON3;
		}
	}
	if(pad_type == 1){
		if(keys[SDLK_BACKSLASH] == SDL_PRESSED || btn1){
			pad |= PAD_BUTTON1;
		}
		if(keys[SDLK_RSHIFT] == SDL_PRESSED || btn2){
			pad |= PAD_BUTTON2;
		}
		if(keys[SDLK_p] == SDL_PRESSED || btn3){
			pad |= PAD_BUTTON3;
		}
	}
	//音量
	if(keys[SDLK_F1] == SDL_PRESSED || btn7){
		pad |= PAD_BUTTON7;
	}
	if(keys[SDLK_F2] == SDL_PRESSED || btn8){
		pad |= PAD_BUTTON8;
	}

	if(btn4){
		pad |= PAD_BUTTON4;
	}
	if(btn5){
		pad |= PAD_BUTTON5;
	}
	if(btn6){
		pad |= PAD_BUTTON6;
	}
//	if(btn7){
//		pad |= PAD_BUTTON7;
//	}
//	if(btn8){
//		pad |= PAD_BUTTON8;
//	}
	if(btn9){
		pad |= PAD_BUTTON9;
	}
	if(btnA){
		pad |= PAD_BUTTONA;
	}
	
	
#endif

	for ( i = 0; i < GP2X_BUTTON_MAX; i++ )
	{
		key_eventPress[i] = 0;
	}
	
	if ( pad & PAD_UP )
	{
		key_eventPress[GP2X_BUTTON_UP] = 1;
	}
	if ( pad & PAD_DOWN )
	{
		key_eventPress[GP2X_BUTTON_DOWN] = 1;
	}
	if ( pad & PAD_LEFT )
	{
		key_eventPress[GP2X_BUTTON_LEFT] = 1;
	}
	if ( pad & PAD_RIGHT )
	{
		key_eventPress[GP2X_BUTTON_RIGHT] = 1;
	}
	if ( pad & PAD_BUTTON1 )
	{
		key_eventPress[GP2X_BUTTON_A] = 1;
	}
	if ( pad & PAD_BUTTON2 )
	{
		key_eventPress[GP2X_BUTTON_X] = 1;
	}
	if ( pad & PAD_BUTTON3 )
	{
		key_eventPress[GP2X_BUTTON_Y] = 1;
	}
	if ( pad & PAD_BUTTON4 )
	{
		key_eventPress[GP2X_BUTTON_B] = 1;
	}
	if ( pad & PAD_BUTTON5 )
	{
		key_eventPress[GP2X_BUTTON_R] = 1;
	}
	if ( pad & PAD_BUTTON6 )
	{
		key_eventPress[GP2X_BUTTON_L] = 1;
	}
	if ( pad & PAD_BUTTON7 )
	{
		key_eventPress[GP2X_BUTTON_VOLDOWN] = 1;
	}
	if ( pad & PAD_BUTTON8 )
	{
		key_eventPress[GP2X_BUTTON_VOLUP] = 1;
	}
	if ( pad & PAD_BUTTON9 )
	{
		key_eventPress[GP2X_BUTTON_SELECT] = 1;
	}
	if ( pad & PAD_BUTTONA )
	{
		key_eventPress[GP2X_BUTTON_START] = 1;
	}
	if ( pad & PAD_BUTTONB )
	{
		key_eventPress[GP2X_BUTTON_CLICK] = 1;
	}
#ifndef GP2X
	if ( keys[SDLK_ESCAPE] )	// 終了
	{
		key_eventPress[GP2X_BUTTON_EXIT] = 1;
	}
#endif
	for ( i = 0; i < GP2X_BUTTON_MAX; i++ )
	{
		if ( ( key_eventPress_old[i] == 0 ) && ( key_eventPress[i] != 0 ) )
		{
			key_eventPush[i] = 1;
		}
		else 
		{
			key_eventPush[i] = 0;
		}
		key_eventPress_old[i] = key_eventPress[i];
		
	}
}

int IsPushKey( int keycode )
{
	int rc = 0;
	
	if ( key_eventPush[keycode] == 1 )
	{
		rc = 1;
	}

	return( rc );
}

int IsPressKey( int keycode )
{
	int rc = 0;
	
	if ( key_eventPress[keycode] == 1 )
	{
		rc = 1;
	}

	return( rc );
}

int IsPushOKKey( void )
{
	int rc = 0;
#ifdef GP2X
	if ( key_eventPush[GP2X_BUTTON_B] == 1 )
#else
	if ( key_eventPush[GP2X_BUTTON_A] == 1 )
#endif
	{
		rc = 1;
	}

	return( rc );
}
int IsPushCancelKey( void )
{
	int rc = 0;
	
#ifdef GP2X
	if ( key_eventPush[GP2X_BUTTON_X] == 1 )
#else
	if ( key_eventPush[GP2X_BUTTON_X] == 1 )
#endif
	{
		rc = 1;
	}

	return( rc );
}

void FPSWait( void )
{
	int interval = INTERVAL_BASE;
	Uint32 leftTick;

	//サウンドの制御
	soundPlayCtrl( );

	SDL_PollEvent(&event);
/*
	nowTick = SDL_GetTicks();
	frame = (nowTick - prvTickCount) / interval;
	if(frame <= 0){
#ifdef GP2X
		wait(prvTickCount + interval - nowTick);
#else
		SDL_Delay(prvTickCount + interval - nowTick);
#endif
	}
	prvTickCount = SDL_GetTicks();
*/

	if(prvTickCount == 0) prvTickCount = SDL_GetTicks();
	
	while (true)
	{
	 	nowTick = SDL_GetTicks();
 		leftTick = prvTickCount + interval - nowTick;
 		if(leftTick < 1 || leftTick > 9999)
 		{
			break;
		}
#ifdef GP2X
 	 	wait(1);
#else
		SDL_Delay(1);
#endif
	}
	prvTickCount = nowTick;

	gameflag[107] = gameflag[107] + 1;
	if ( gameflag[107] >= 60 )
	{
		gameflag[107] = 0;
		gameflag[108] = gameflag[108] + 1;
		if ( gameflag[108] >= 60 )
		{
			gameflag[108] = 0;
			gameflag[109] = gameflag[109] + 1;
			if ( gameflag[109] >= 60 )
			{
				gameflag[109] = 0;
				gameflag[110] = gameflag[110] + 1;
				if ( gameflag[110] >= 999 )
				{
					gameflag[110] = 999;
				}
			}
		}
	}

}

int system_keys( void )
{
	int rc;
	
	rc = 1;
#ifdef GP2X
	// 終了
//	if ( ( IsPressKey( GP2X_BUTTON_START ) ) && ( IsPressKey( GP2X_BUTTON_SELECT ) ) )
	if ( ( IsPressKey( GP2X_BUTTON_START ) ) && ( IsPressKey( GP2X_BUTTON_L ) ) && ( IsPressKey( GP2X_BUTTON_R ) ) )
#else
	if ( ( event.type == SDL_QUIT ) || ( IsPressKey( GP2X_BUTTON_EXIT ) ) )
#endif
	{
		rc = 0;
		g_scene = EN_SN_EXIT;
	}
	// 音量調整
	if ( IsPushKey( GP2X_BUTTON_VOLUP ) )
	{
		gameflag[60] = gameflag[60] + 10;
		if ( gameflag[60] > VOL_MAX )
		{
			gameflag[60] = VOL_MAX;
		}
		Set_Volume( gameflag[60] );
	}
	if ( IsPushKey( GP2X_BUTTON_VOLDOWN ) )
	{
		gameflag[60] = gameflag[60] - 10;
		if ( gameflag[60] < 0 )
		{
			gameflag[60] = 0;
		}
		Set_Volume( gameflag[60] );
	}
	
	return( rc );
}
int Set_Volume( int vol )
{
	int rc = 0;
	
	soundSetVolumeBgm( vol, 0 );
	soundSetVolumeAll( vol );
	
	return( rc );
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
void BltNumericImage( long value, long length, long x, long y, long plane, long num_stpos_x, long num_stpos_y, long num_width, long num_height )
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

/*[ BltNumericImage2 ]************************************************/
/*	数値画像表示関数（右詰め）										*/
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
void BltNumericImage2( long value, long length, long x, long y, long plane, long num_stpos_x, long num_stpos_y, long num_width, long num_height )
{
	long blt_num;	// １桁の数値を格納する
	long i;			// 桁数分のforループで使用
	long dv;		// 割り算で使用する値
	long x_hosei;	//右詰め補正値
	
	// value が負の値の場合、正の値に置き換える
	if ( value < 0 )
	{
		value = value * -1;
	}
	
	/* 2002.10.21 D.K start */
	int buf = value;
	int t = 1;
	while(true)
	{
		t++;
		buf = buf / 10;
		if ( 0 <= buf )
		{
			break;
		}
	}
	x_hosei = t;
//	scanf(string[0],"%d",value);
//	x_hosei = StrLen( string[0] );
	if ( x_hosei == 0 )
	{
		x_hosei = 1;
	}
	x_hosei = length - x_hosei;
	x_hosei = x_hosei * num_width;
//	length = StrLen( string[0] );
	x = x + x_hosei;
	/* 2002.10.21 D.K end */
	
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

long funcSin( long rdo )
{
	long ang = 0;
	long rc = 0;
	
	if ( ( rdo >= 0 ) && ( rdo < 180 ) )
	{
		ang = ( ( 65535 * rdo ) / 360 );
		rc = MOTsin( ang );
	}
	if ( ( rdo >= 180 ) && ( rdo < 360 ) )
	{
		rdo = rdo - 180;
		ang = ( ( 65535 * rdo ) / 360 );
		rc = MOTsin( ang );
		rc = rc * -1;
	}
	
	return( rc );
}
long funcCos( long rdo )
{
	long ang = 0;
	long rc = 0;
	
	if ( ( rdo >= 0 ) && ( rdo < 180 ) )
	{
		ang = ( ( 65535 * rdo ) / 360 );
		rc = MOTcos( ang );
	}
	if ( ( rdo >= 180 ) && ( rdo < 360 ) )
	{
		rdo = rdo - 180;
		ang = ( ( 65535 * rdo ) / 360 );
		rc = MOTcos( ang );
		rc = rc * -1;
	}
	
	return( rc );
}


long funcTan2( long posX, long posY )
{
	long rc = 0;
	
	rc = MOTatan( ( posX ) * 256, ( posY * -1 ) * 256 );
	
	return( rc );
}

long get2keta( long val, long st )
{
	long rc = 0;
	
	val = val / st;
	rc = val % 100;
	
	return( rc );
}

void BltGSreface( int rr )
{
	SDL_Surface *temp_Surface;
	
	temp_Surface = rotozoomSurface(g_screen, 0, rr, 0);
	SDL_Surface *surface;
    Uint8 bpp;
	SDL_Palette *pal;
	Uint8 r;
	Uint8 g;
	Uint8 b;

	surface = g_screen;
    if(surface){
	    bpp = surface->format->BytesPerPixel;
		if(bpp <= 8){
			pal = surface->format->palette;
			if(pal){
				SDL_SetPalette(temp_Surface, SDL_LOGPAL|SDL_PHYSPAL, pal->colors, 0, 256);
				r = pal->colors->r;
				g = pal->colors->g;
				b = pal->colors->b;
				// パレット０番が透過色
				SDL_SetColorKey(temp_Surface, false, SDL_MapRGBA(g_screen->format,r,g,b,0) );
			}
		}
	}
	
//	SDL_SaveBMP(SDL_DisplayFormat(temp_Surface), "tempbmp.bmp");
	
	
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = temp_Surface->w;
	srcRect.h = temp_Surface->h;

	SDL_Rect dstRect;
//	dstRect.x = 320 - ( temp_Surface->w / 2 );
//	dstRect.y = 240 - ( temp_Surface->h / 2 );
	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = temp_Surface->w;
	dstRect.h = temp_Surface->h;


	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = DISPLY_WIDTH * rr;
	rect.h = DISPLY_HEIGHT * rr;
	SDL_FillRect(g_screen, &rect, SDL_MapRGBA(g_screen->format,0,0,0,255));

	SDL_BlitSurface( temp_Surface , &srcRect, g_screen, &dstRect);
	SDL_FreeSurface(temp_Surface);

}

void halt( void )
{
	if ( gameflag[61] > 1 )
	{
		BltGSreface( gameflag[61] );	//拡大表示
	}
	SDL_Flip( g_screen );	// 描画
}


