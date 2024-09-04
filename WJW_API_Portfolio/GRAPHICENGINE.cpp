#include <stdio.h>
#include "GRAPHICENGINE.h"

BOOL GeCreateBackBuffer(HDC hdc, int nWidth, int nHeight, int nBPP, SURFACEINFO* psInfo)
{
	psInfo->dcSurface = CreateCompatibleDC(hdc);
	psInfo->hBmp = CreateCompatibleBitmap(hdc, nWidth, nHeight);
	psInfo->hOldBmp = (HBITMAP)SelectObject(psInfo->dcSurface, psInfo->hBmp);
	PatBlt(psInfo->dcSurface, 0, 0, nWidth, nHeight, PATCOPY);
	psInfo->nWidth = nWidth;
	psInfo->nHeight = nHeight;

	return TRUE;
}

void GeSetImgSurface(SURFACEINFO* psfInfo)
{
	memset(psfInfo, 0, sizeof(SURFACEINFO));
}

HBITMAP GeBmpFile2BmpHandle(char* pstrFilename)
{
	FILE* fp;
	DWORD dwSize;
	BITMAPFILEHEADER BitmapFileHeader;
	BITMAPINFO* pBitmapInfo;
	HBITMAP hBit;
	void* pBitmap;

	//// 파일을 연다
	fp = fopen(pstrFilename, "rb");

	//// BITMAPFILEHEADER 	
	fread(&BitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	//// BITMAPINFO의 크기를 구하고 할당, 읽는다
	dwSize = BitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);	// 40 bytes
	//dwSize = sizeof(BITMAPINFO);									// 44 bytes
	pBitmapInfo = (BITMAPINFO*)malloc(dwSize);
	fread(pBitmapInfo, dwSize, 1, fp);

	//// DIB 섹션을 만들고 버퍼 메모리를 할당한다.
	hBit = CreateDIBSection(NULL,				// HDC, DIB_PAL_COLORS인 경우만 사용
		pBitmapInfo,		// BITMAPINFO 포인터
		DIB_RGB_COLORS,	// 색상 사용 플래그
		&pBitmap,			// 메모리 어드래스
		NULL,				// 파일 매핑 개체 핸들
		0);				// 파일 매핑 개체의 비트 오프셋

	//// 이미지 데이터를 읽어들인다.
	int nImageSize = BitmapFileHeader.bfSize - BitmapFileHeader.bfOffBits;
	fread(pBitmap, nImageSize, 1, fp);

	////
	free(pBitmapInfo);

	////
	fclose(fp);

	return hBit;
}

void GeLoadSurface(HDC hdc, SURFACEINFO* psInfo)
{
	BITMAP  bit;

	psInfo->dcSurface = CreateCompatibleDC(hdc);
	psInfo->hOldBmp = (HBITMAP)SelectObject(psInfo->dcSurface, psInfo->hBmp);

	GetObject(psInfo->hBmp, sizeof(BITMAP), &bit);
	psInfo->nWidth = bit.bmWidth;
	psInfo->nHeight = bit.bmHeight;
}

void GeSetSprSurface(SURFACEINFO* psfInfo, COLORREF crColorKey)
{
	memset(psfInfo, 0, sizeof(SURFACEINFO));
	psfInfo->crColorKey = crColorKey;
}

BOOL GePutImage(HDC dcDst, int x, int y, SURFACEINFO* psInfo)
{
	if (psInfo)
		return BitBlt(dcDst, x, y, psInfo->nWidth, psInfo->nHeight, psInfo->dcSurface, 0, 0, SRCCOPY);
	else return FALSE;
}

BOOL GePutSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo)
{
	return TransparentBlt(dcDst, x, y, psInfo->nWidth, psInfo->nHeight,
		psInfo->dcSurface, 0, 0, psInfo->nWidth, psInfo->nHeight, psInfo->crColorKey);
}

BOOL GeReduPutSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo, int nReductionRate)
{
	return TransparentBlt(dcDst, x, y, psInfo->nWidth / nReductionRate, psInfo->nHeight / nReductionRate,
		psInfo->dcSurface, 0, 0, psInfo->nWidth, psInfo->nHeight, psInfo->crColorKey);
}

BOOL GeCompleteBlt(HDC hdc, SURFACEINFO* psInfo)
{
	BitBlt(hdc, 0, 0, psInfo->nWidth, psInfo->nHeight, psInfo->dcSurface, 0, 0, SRCCOPY);
	return TRUE;
}

void GeReleaseSurface(SURFACEINFO* psInfo)
{
	SelectObject(psInfo->dcSurface, psInfo->hOldBmp);
	DeleteDC(psInfo->dcSurface);
	DeleteObject(psInfo->hBmp);
}

HBITMAP MakeDDBFromDIB(HDC hdc, char* Path)
{
	HANDLE  hFile;
	DWORD   FileSize, dwRead;
	HBITMAP hBit;
	BITMAPFILEHEADER* fh;
	BITMAPINFO* ih;
	BITMAPINFOHEADER* iheader;
	LPBYTE			 lpMemBlock;

	//// 파일을 연다
	hFile = CreateFile(Path, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return NULL;
	}

	FileSize = GetFileSize(hFile, NULL);

	lpMemBlock = (LPBYTE)malloc(FileSize);
	fh = (BITMAPFILEHEADER*)lpMemBlock;
	ReadFile(hFile, lpMemBlock, FileSize, &dwRead, NULL);
	CloseHandle(hFile);

	ih = (BITMAPINFO*)(lpMemBlock + sizeof(BITMAPFILEHEADER));
	iheader = (BITMAPINFOHEADER*)(lpMemBlock + sizeof(BITMAPFILEHEADER));

	//// DDB로 변환한다.
	hBit = CreateDIBitmap(hdc,						// hdc
		iheader,					// BITMAPINFOHEADER 헤더
		CBM_INIT,					// 0 또는 CBM_INIT ( 초기화 )
		lpMemBlock + fh->bfOffBits,	// 래스터 어드래스
		ih,							// BITMAPINFO 헤더
		DIB_RGB_COLORS);

	free(lpMemBlock);

	return hBit;
}