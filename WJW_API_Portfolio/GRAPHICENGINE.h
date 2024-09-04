#pragma once
#ifndef __GRAPHICENGINE_H__
#define __GRAPHICENGINE_H__

#include <windows.h>

typedef struct SURFACEINFOtag
{
	int			nWidth;
	int			nHeight;
	int			nCentralX;		// �߽���ǥ X
	int			nCentralY;		// �߽���ǥ Y
	COLORREF	crColorKey;		// �÷�Ű
	DWORD		dwDelayTime;	// �����ð� (ms)

	HDC			dcSurface;		// ��Ʈ���� ������ִ� ǥ�� DC
	HBITMAP		hBmp;			// ��Ʈ�� �ڵ�
	HBITMAP		hOldBmp;		// ���� ��Ʈ�� �ڵ� ( dc ������ ���� )
} SURFACEINFO;

typedef struct BIN_SURFACEINFOtag
{
	int			nWidth;
	int			nHeight;
	int			nCentralX;		// �߽���ǥ X
	int			nCentralY;		// �߽���ǥ Y
	COLORREF	crColorKey;		// �÷�Ű
	DWORD		dwDelayTime;	// �����ð� (ms)

	BYTE* pSurface;		// ǥ���� �ּ�
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