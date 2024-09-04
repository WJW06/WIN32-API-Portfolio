#include <math.h>
#include "MONSTERBULLET.h"
#include "PLAYER.h"

extern PLAYER* pPlayer;

MONSTERBULLET::MONSTERBULLET()
{
	fSpeed = 4.f;
	nBulletType = Type_MonsterBullet;
	nReductionRate = 2;
}

MONSTERBULLET::~MONSTERBULLET()
{
}

void MONSTERBULLET::CreateBasicMonsterBulletSurface(HDC dcScreen, SURFACEINFO* sfMonsterBulletInfo, COLORREF crColorKey)
{
    char strName[35];
    for (int i = 0; i < 4; ++i)
    {
        GeSetSprSurface(&sfMonsterBulletInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/MonsterBullet%d.bmp", i + 1);
        sfMonsterBulletInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfMonsterBulletInfo[i]);
    }
}

void MONSTERBULLET::SetPlayerDirection()
{
    int nDistance;
    ptDirection.x = pPlayer->GetxPosition();
    ptDirection.y = pPlayer->GetyPosition();
    if (ptDirection.x <= pPosition.x)
    {
        nDistance = pPosition.x - ptDirection.x;
        if (ptDirection.y <= pPosition.y)   lfDistance = sqrt(pow(nDistance, 2) + pow(pPosition.y - ptDirection.y, 2));
        else                                lfDistance = sqrt(pow(nDistance, 2) + -pow(pPosition.y - ptDirection.y, 2));
    }
    else
    {
        nDistance = ptDirection.x - pPosition.x;
        if (ptDirection.y <= pPosition.y)   lfDistance = sqrt(pow(nDistance, 2) + pow(pPosition.y - ptDirection.y, 2));
        else                                lfDistance = sqrt(pow(nDistance, 2) + -pow(pPosition.y - ptDirection.y, 2));
    }
    fTheta = nDistance / lfDistance;
}
