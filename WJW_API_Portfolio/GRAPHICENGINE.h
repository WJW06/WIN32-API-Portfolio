#pragma once
#ifndef __GRAPHICENGINE_H__
#define __GRAPHICENGINE_H__

#include <windows.h>

typedef struct SURFACEINFOtag
{
	int			nWidth;
	int			nHeight;
	int			nCentralX;		// 중심좌표 X
	int			nCentralY;		// 중심좌표 Y
	COLORREF	crColorKey;		// 컬러키
	DWORD		dwDelayTime;	// 지연시간 (ms)

	HDC			dcSurface;		// 비트맵이 적재되있는 표면 DC
	HBITMAP		hBmp;			// 비트맵 핸들
	HBITMAP		hOldBmp;		// 이전 비트맵 핸들 ( dc 해제시 참조 )
} SURFACEINFO;

typedef struct BIN_SURFACEINFOtag
{
	int			nWidth;
	int			nHeight;
	int			nCentralX;		// 중심좌표 X
	int			nCentralY;		// 중심좌표 Y
	COLORREF	crColorKey;		// 컬러키
	DWORD		dwDelayTime;	// 지연시간 (ms)

	BYTE* pSurface;		// 표면의 주소
} BIN_SURFACEINFO;

BOOL GeCreateBackBuffer(HDC hdc, int nWidth, int nHeight, int nBPP, SURFACEINFO* psInfo);
void GeSetImgSurface(SURFACEINFO* psfInfo);
HBITMAP GeBmpFile2BmpHandle(char* pstrFilename);
void GeLoadSurface(HDC hdc, SURFACEINFO* psInfo);
void GeSetSprSurface(SURFACEINFO* psfInfo, COLORREF crColorKey);

BOOL GePutImage(HDC dcDst, int x, int y, SURFACEINFO* psInfo);
BOOL GePutSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo);
BOOL GeReduPutSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo, int nReductionRate);
BOOL GeCompleteBlt(HDC hdc, SURFACEINFO* psInfo);

void GeReleaseSurface(SURFACEINFO* psInfo);

HBITMAP MakeDDBFromDIB(HDC hdc, char* Path);

#endif