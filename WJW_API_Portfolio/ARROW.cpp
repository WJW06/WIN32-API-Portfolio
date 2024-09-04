#include "ARROW.h"

ARROW::ARROW()
{
    fSpeed = 8.f;
    nBulletType = Type_Arrow;
	nReductionRate = 4;
}

ARROW::~ARROW()
{
}

void ARROW::CreateBasicArrowSurface(HDC dcScreen, SURFACEINFO* sfArrowInfo, COLORREF crColorKey)
{
    char strName[25];
    for (int i = 0; i < 4; ++i)
    {
        GeSetSprSurface(&sfArrowInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/Arrow%d.bmp", i + 1);
        sfArrowInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfArrowInfo[i]);
    }
}