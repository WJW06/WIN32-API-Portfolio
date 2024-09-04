#include <math.h>
#include "BULLET.h"
#include "BIOLOGY.h"
#include "COLLIDER.h"

#define TopBullet			0
#define RightBullet         1
#define BottomBullet        2
#define LeftBullet          3
#define TopRightBullet		4
#define TopLeftBullet		5
#define BottomRightBullet	6
#define BottomLeftBullet	7

BULLET::BULLET() :
	nHp(1),
	nAni(0),
	nStr(0),
	fSpeed(0.f),
	fTheta(0.f),
	nBulletType(None)
{
	CreateCollider();
}

BULLET::~BULLET()
{
}

void BULLET::BulletUpdate()
{
	pPosition.x += fSpeed * cosf(fTheta);
	pPosition.y -= fSpeed * sinf(fTheta);
}

void BULLET::CheckConflict(BIOLOGY* _Biology)
{
	if ((((pCollider->GetxFinalPos() >= _Biology->GetCollider()->GetxFinalPos()) && (pCollider->GetxFinalPos() <= _Biology->GetCollider()->GetWidth()))
		|| ((pCollider->GetWidth() >= _Biology->GetCollider()->GetxFinalPos()) && (pCollider->GetWidth() <= _Biology->GetCollider()->GetWidth())))
		&& (((pCollider->GetyFinalPos() >= _Biology->GetCollider()->GetyFinalPos()) && (pCollider->GetyFinalPos() <= _Biology->GetCollider()->GetHeight()))
		|| ((pCollider->GetHeight() >= _Biology->GetCollider()->GetyFinalPos()) && (pCollider->GetHeight() <= _Biology->GetCollider()->GetHeight()))))
	{
		switch (nAni)
		{
		case TopBullet:
			_Biology->ChangeyPosition(-(nStr * (int)fSpeed));
			break;
		case RightBullet:
			_Biology->ChangexPosition(-(nStr * (int)fSpeed));
			break;
		case BottomBullet:
			_Biology->ChangeyPosition(nStr * (int)fSpeed);
			break;
		case LeftBullet:
			_Biology->ChangexPosition(-(nStr * (int)fSpeed));
			break;
		case TopRightBullet:
			_Biology->ChangexPosition(-(nStr * (int)fSpeed));
			_Biology->ChangeyPosition(-(nStr * (int)fSpeed));
			break;
		case TopLeftBullet:
			_Biology->ChangexPosition(-(nStr * (int)fSpeed));
			_Biology->ChangeyPosition(-(nStr * (int)fSpeed));
			break;
		case BottomRightBullet:
			_Biology->ChangexPosition(-(nStr * (int)fSpeed));
			_Biology->ChangeyPosition(nStr * (int)fSpeed);
			break;
		case BottomLeftBullet :
			_Biology->ChangexPosition(-(nStr * (int)fSpeed));
			_Biology->ChangeyPosition(nStr * (int)fSpeed);
			break;
		}
		_Biology->HpUp(-nStr);
		_Biology->HitCount();
		--nHp;
	}
}

void BULLET::SetPlayerDirection()
{
	return;
}

double BULLET::GetDistance()
{
	return 0;
}

POINT BULLET::GetDirection()
{
	return POINT();
}
