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

	//// ������ ����
	fp = fopen(pstrFilename, "rb");

	//// BITMAPFILEHEADER 	
	fread(&BitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	//// BITMAPINFO�� ũ�⸦ ���ϰ� �Ҵ�, �д´�
	dwSize = BitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);	// 40 bytes
	//dwSize = sizeof(BITMAPINFO);									// 44 bytes
	pBitmapInfo = (BITMAPINFO*)malloc(dwSize);
	fread(pBitmapInfo, dwSize, 1, fp);

	//// DIB ������ ����� ���� �޸𸮸� �Ҵ��Ѵ�.
	hBit = CreateDIBSection(NULL,				// HDC, DIB_PAL_COLORS�� ��츸 ���
		pBitmapInfo,		// BITMAPINFO ������
		DIB_RGB_COLORS,	// ���� ��� �÷���
		&pBitmap,			// �޸� ��巡��
		NULL,				// ���� ���� ��ü �ڵ�
		0);				// ���� ���� ��ü�� ��Ʈ ������

	//// �̹��� �����͸� �о���δ�.
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

	//// ������ ����
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

	//// DDB�� ��ȯ�Ѵ�.
	hBit = CreateDIBitmap(hdc,						// hdc
		iheader,					// BITMAPINFOHEADER ���
		CBM_INIT,					// 0 �Ǵ� CBM_INIT ( �ʱ�ȭ )
		lpMemBlock + fh->bfOffBits,	// ������ ��巡��
		ih,							// BITMAPINFO ���
		DIB_RGB_COLORS);

	free(lpMemBlock);

	return hBit;
}