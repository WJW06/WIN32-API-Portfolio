#include <list>
#include "BIOLOGY.h"
#include "BULLET.h"
#include "BULLET_LIST.h"
#include "TIMERENGINE.h"
#include "COLLIDER.h"

#define RightMove   0
#define LeftMove    4
#define BehindMove  8
#define FrontMove   12

#define TopBullet			0
#define RightBullet         1
#define BottomBullet        2
#define LeftBullet          3

using namespace std;

extern BULLET*		pBullet;
extern list<BULLET*>  pBulletList;

BIOLOGY::BIOLOGY() :
	//stName{ NULL,0 },
	nHp(0),
	nStr(0),
	fAS(0.f),
	fASMax(1.5f),
	nRange(0),
	fSpeed(0.f),
	nMoveTime(0),
	bIsShootMove(false),
	nHitTime(0),
	bIsHit(false),
	nBiologyType(None)
	/*bIsFire(false)*/
	//bIsUsedWeapon(false)
{
}

BIOLOGY::~BIOLOGY()
{
}

void BIOLOGY::operator=(const BIOLOGY& _Biology)
{
	if (this == &_Biology) return;
	//stName = _Biology.stName;
	nReductionRate = _Biology.nReductionRate;
	nHp = _Biology.nHp;
	nStr = _Biology.nStr;
	fAS = _Biology.fAS;
	fASMax = _Biology.fASMax;
	nRange = _Biology.nRange;
	fSpeed = _Biology.fSpeed;
	nBiologyType = _Biology.nBiologyType;
	bIsShootMove = _Biology.bIsShootMove;
}

void BIOLOGY::MoveAction(int nDMove)
{
	if (GetIsShootMove()) SetIsShootMove(false);
	if (nAni < nDMove || nAni >= nDMove + 4) nAni = nDMove;
	MoveTimer();
	if (nAni >= 4 + nDMove) nAni = nDMove;
}

void BIOLOGY::HitCount()
{
	if (!bIsHit)
	{
		if (nAni >= RightMove && nAni < RightMove + 4)
			nAni = RightMove;
		if (nAni >= LeftMove && nAni < LeftMove + 4)
			nAni = LeftMove;
		if (nAni >= BehindMove && nAni < BehindMove + 4)
			nAni = BehindMove;
		if (nAni >= FrontMove && nAni < FrontMove + 4)
			nAni = FrontMove;
		nHitTime = 0;
		bIsHit = true;
	}
}

void BIOLOGY::SAttackAction(HWND hWnd, int nDMove, BIOLOGY* _Biology1, BIOLOGY* _Biology2)
{
	if (!GetIsShootMove())
	{
		nAni = nDMove;
		SetIsShootMove(true);
		SetAS(0);
	}
	if (nAni < nDMove || nAni > nDMove + 3)
	{
		nAni = nDMove;
		SetIsShootMove(false);
		return;
	}
	FireTimer();
	if (nAni >= 3 + nDMove)
	{
		nAni = nDMove;
		_Biology1->HpUp(-_Biology2->GetStr());
		_Biology1->HitCount();
		SetAS(0);
		SetIsShootMove(false);
	}
}

void BIOLOGY::LAttackAction(HWND hWnd, int nDMove, int nDShoot, int _Str)
{
	if (!GetIsShootMove())
	{
		nAni = nDMove;
		SetIsShootMove(true);
		SetAS(0);
	}
	if (nAni < nDMove || nAni > nDMove + 3)
	{
		nAni = nDMove;
		SetIsShootMove(false);
		return;
	}
	FireTimer();
	if (nAni >= 3 + nDMove)
	{
		ShootBullet(hWnd, nDShoot, _Str);
		nAni = nDMove;
		SetAS(0);
		SetIsShootMove(false);
	}
}

void BIOLOGY::MoveTimer()
{
	MoveTimeUp(1);
	if (GetMoveTime() >= 10)
	{
		nAni++;
		SetMoveTime(0);
	}
}

void BIOLOGY::FireTimer()
{
	nAni++;
	SetAS(0);
}

void BIOLOGY::ShootBullet(HWND hWnd, int _DShoot, int _Str)
{
	HDC hdc = GetDC(hWnd);
	BULLET* pBullet = nullptr;
	switch (GetBiologyType())
	{
	case Type_Player:
	{
		ARROW* pArrow = new ARROW;
		pArrow->CreateBasicArrowSurface(hdc, pArrow->sfMoveBullet, RGB(255, 0, 128));
		pBullet = pArrow;
	}
		break;
	case Type_Monster:
	{
		MONSTERBULLET* pMonsterBullet = new MONSTERBULLET;
		pMonsterBullet->CreateBasicMonsterBulletSurface(hdc, pMonsterBullet->sfMoveBullet, RGB(255, 255, 255));
		pBullet = pMonsterBullet;
	}
		break;
	}
	pBullet->SetStr(_Str);
	if (pBullet != nullptr)
	{
		switch (_DShoot)
		{
		case RightBullet:
			pBullet->SetxPosition(GetxPosition() + (GetRealWidth() / 2));
			pBullet->SetyPosition(GetyPosition() + (GetRealHeight() / 3));
			if (pBullet->GetBulletType() == Type_Arrow)
			{
				pBullet->GetCollider()->SetyOffsetPos(4);
				pBullet->GetCollider()->SetxOffsetPos(20);
			}
			break;
		case LeftBullet:
			pBullet->SetxPosition(GetxPosition() - (GetRealWidth() / 2));
			pBullet->SetyPosition(GetyPosition() + (GetRealHeight() / 3));
			if (pBullet->GetBulletType() == Type_Arrow)
			{
				pBullet->GetCollider()->SetxOffsetPos(12);
				pBullet->GetCollider()->SetyOffsetPos(4);
			}
			break;
		case TopBullet:
			pBullet->SetxPosition(GetxPosition() + (GetRealWidth() / 3));
			pBullet->SetyPosition(GetyPosition() - (GetRealHeight() / 4));
			if (pBullet->GetBulletType() == Type_Arrow)
				pBullet->GetCollider()->SetxOffsetPos(4);
			break;
		case BottomBullet:
			pBullet->SetxPosition(GetxPosition() + (GetRealWidth() / 3));
			pBullet->SetyPosition(GetyPosition() + (GetRealHeight() / 2));
			if (pBullet->GetBulletType() == Type_Arrow)
			{
				pBullet->GetCollider()->SetxOffsetPos(4);
				pBullet->GetCollider()->SetyOffsetPos(20);
			}
			break;
		}
		if (_DShoot == RightBullet || _DShoot == LeftBullet)
		{
			pBullet->SetRealHeight(pBullet->sfMoveBullet[pBullet->nAni].nWidth / pBullet->nReductionRate);
			pBullet->SetRealWidth(pBullet->sfMoveBullet[pBullet->nAni].nHeight / pBullet->nReductionRate);
		}
		else
		{
			pBullet->SetRealWidth(pBullet->sfMoveBullet[pBullet->nAni].nWidth / pBullet->nReductionRate);
			pBullet->SetRealHeight(pBullet->sfMoveBullet[pBullet->nAni].nHeight / pBullet->nReductionRate);
		}
		pBullet->nAni = _DShoot;
		if (pBullet->GetBulletType() == Type_MonsterBullet) pBullet->SetPlayerDirection();
		pBulletList.push_back(pBullet);
	}
	ReleaseDC(hWnd, hdc);
}