#pragma once
#include "BULLET.h"
class MONSTERBULLET :
    public BULLET
{
public:
    MONSTERBULLET();
    virtual ~MONSTERBULLET();
private:
    POINT   ptDirection;
    double  lfDistance;
public:
    POINT   GetDirection() { return ptDirection; }
    double  GetDistance() { return lfDistance; }
    void    SetDirection(POINT _Direction) { ptDirection = _Direction; }

    void	CreateBasicMonsterBulletSurface(HDC dcScreen, SURFACEINFO* sfMonsterBulletInfo, COLORREF crColorKey);
    void    SetPlayerDirection();
};

