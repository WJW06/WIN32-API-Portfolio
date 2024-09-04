#include "MONSTER.h"
#include "PLAYER.h"
#include "COLLIDER.h"

#define RightMove   0
#define LeftMove    4
#define BehindMove  8
#define FrontMove   12

#define TopBullet			0
#define RightBullet         1
#define BottomBullet        2
#define LeftBullet          3

extern int nStage;

MONSTER::MONSTER()
{
	InitMonster();
	CreateCollider();
}

MONSTER::~MONSTER()
{
}

void MONSTER::InitMonster()
{
	nHp += 1 * (nStage - 1);
	fSpeed = 1.5f + (0.1f * nStage);
	nGivingExp = 0;
	nGivingScore = 0;
	nMType = None_Monster;
	bIsAttackMonster = true;
	bIsLongRange = false;
	nBiologyType = Type_Monster;
}

void MONSTER::AfterDeath(PLAYER* _Player)
{
	_Player->ExpUp(nGivingExp);
	_Player->ScoreUp(nGivingScore);
}

void MONSTER::NavigationAI(HWND hWnd, PLAYER* _Player)
{
	int MonsterxPos, MonsteryPos, MonsterxDistance, MonsteryDistance;
	MonsterxPos = pCollider->GetxFinalPos() + (GetRealWidth() / 2);
	MonsteryPos = pCollider->GetyFinalPos() + (GetRealHeight() / 2);
	MonsterxDistance = (GetRealWidth() / 2) * GetRange();
	MonsteryDistance = (GetRealWidth() / 4) * GetRange();

	if (((_Player->GetCollider()->GetWidth() >= pCollider->GetxFinalPos() - MonsteryDistance) && (_Player->GetCollider()->GetxFinalPos() <= pCollider->GetWidth() + MonsterxDistance))
		&& ((_Player->GetCollider()->GetHeight() >= pCollider->GetyFinalPos() - MonsteryDistance) && (_Player->GetCollider()->GetyFinalPos() <= pCollider->GetHeight() + MonsteryDistance)))
	{
		if (GetAS() >= GetASMax())
		{
			if (!GetIsLongRange())
			{
				if (_Player->GetxPosition() > GetxPosition())	SAttackAction(hWnd, RightMove, _Player, this);
				else											SAttackAction(hWnd, LeftMove, _Player, this);
			}
			else
			{
				if (_Player->GetxPosition() > GetxPosition())		LAttackAction(hWnd, RightMove, RightBullet, nStr);
				else if (_Player->GetxPosition() < GetxPosition())	LAttackAction(hWnd, LeftMove, LeftBullet, nStr);
				if (_Player->GetyPosition() > GetyPosition())
				{
					if (nAni >= RightMove && nAni < RightMove + 4)	LAttackAction(hWnd, RightMove, BottomBullet, nStr);
					else											LAttackAction(hWnd, LeftMove, BottomBullet, nStr);
				}
				else if (_Player->GetyPosition() < GetyPosition())
				{
					if (nAni >= RightMove && nAni < RightMove + 4)	LAttackAction(hWnd, RightMove, TopBullet, nStr);
					else											LAttackAction(hWnd, LeftMove, TopBullet, nStr);
				}
			}
		}
		return;
	}
	if (_Player->GetCollider()->GetWidth() < pCollider->GetxFinalPos() - MonsteryDistance)
	{
		ChangexPosition(-GetSpeed());
		MoveAction(LeftMove);
	}
	if (_Player->GetCollider()->GetxFinalPos() > pCollider->GetWidth() + MonsterxDistance)
	{
		ChangexPosition(GetSpeed());
		MoveAction(RightMove);
	}
	if (_Player->GetCollider()->GetHeight() < pCollider->GetyFinalPos() - MonsteryDistance)
	{
		ChangeyPosition(-GetSpeed());
		if (!(_Player->GetCollider()->GetWidth() < pCollider->GetxFinalPos() - MonsteryDistance)
			&& !(_Player->GetCollider()->GetxFinalPos() > pCollider->GetWidth() + MonsterxDistance))
		{
			if (nAni >= LeftMove && nAni < LeftMove + 4)	MoveAction(LeftMove);
			else											MoveAction(RightMove);
		}
	}
	if (_Player->GetCollider()->GetyFinalPos() > pCollider->GetHeight() + MonsteryDistance)
	{
		ChangeyPosition(GetSpeed());
		if (!(_Player->GetCollider()->GetWidth() < pCollider->GetxFinalPos() - MonsteryDistance)
			&& !(_Player->GetCollider()->GetxFinalPos() > pCollider->GetWidth() + MonsterxDistance))
		{
			if (nAni >= LeftMove && nAni < LeftMove + 4)	MoveAction(LeftMove);
			else											MoveAction(RightMove);
		}
	}
}

void MONSTER::BumpIntoMFM(MONSTER* _Monster)
{

	if ((_Monster->GetCollider()->GetWidth() >= pCollider->GetxFinalPos()) && (_Monster->GetCollider()->GetWidth() <= pCollider->GetWidth()))
	{
		if ((_Monster->GetCollider()->GetHeight() >= pCollider->GetyFinalPos()) && (_Monster->GetCollider()->GetHeight() <= pCollider->GetHeight())
			|| (_Monster->GetCollider()->GetyFinalPos() >= pCollider->GetyFinalPos()) && (_Monster->GetCollider()->GetyFinalPos() <= pCollider->GetHeight()))
			_Monster->ChangexPosition((pCollider->GetxFinalPos() - _Monster->GetCollider()->GetWidth()));
	}
	else if ((_Monster->GetCollider()->GetxFinalPos() >= pCollider->GetxFinalPos()) && (_Monster->GetCollider()->GetxFinalPos() <= pCollider->GetWidth()))
	{
		if ((_Monster->GetCollider()->GetHeight() >= pCollider->GetyFinalPos()) && (_Monster->GetCollider()->GetHeight() <= pCollider->GetHeight())
			|| (_Monster->GetCollider()->GetyFinalPos() >= pCollider->GetyFinalPos()) && (_Monster->GetCollider()->GetyFinalPos() <= pCollider->GetHeight()))
			_Monster->ChangexPosition((pCollider->GetWidth() - _Monster->GetCollider()->GetxFinalPos()));
	}
}

