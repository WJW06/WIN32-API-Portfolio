#include "MONSTERENGINE.h"
#include "COLLIDER.h"

extern HDC hdc;

extern int nStage;

extern PLAYER*			pPlayer;
extern MONSTER*			pMonster;
extern list<MONSTER*>	pMonsterList;

void RandomSpawnMonster(int nRandomType)
{
	if (nStage <= 2) nRandomType = 0;
	switch (nRandomType)
	{
	case Type_Zombie:
		pMonster = new ZOMBIE;
		MakeZombieSurface(hdc, pMonster->sfMove, RGB(0, 64, 128));
		MakeZombieAttackSurface(hdc, pMonster->sfShoot, RGB(0, 64, 128));
		pMonster->GetCollider()->SetxOffsetPos(5);
		break;
	case Type_Cake:
		pMonster = new CAKE;
		MakeCakeSurface(hdc, pMonster->sfMove, RGB(255, 255, 0));
		MakeCakeAttackSurface(hdc, pMonster->sfShoot, RGB(255, 255, 0));
		break;
	}
	if (!pMonster) return;
	pMonster->SetRealWidth(pMonster->sfMove[pMonster->nAni].nWidth);
	pMonster->SetRealHeight(pMonster->sfMove[pMonster->nAni].nHeight);
	pMonster->SetxPosition(rand() % (MaxClientWidth * 2) - (MaxClientWidth / 2));
	pMonster->SetyPosition(rand() % (MaxClientHeight * 2) - (MaxClientHeight / 2));
	//if (Monster.GetIsLongRange())
	//{
	//	if (Monster.GetxPosition() > (MaxClientWidth + 355) - (Monster.sfMove[Monster.nAni].nWidth / Monster.nReductionRate * Monster.GetRange()))
	//		Monster.ChangexPosition(Monster.sfMove[Monster.nAni].nWidth / Monster.nReductionRate * Monster.GetRange());
	//	if (Monster.GetyPosition() > (MaxClientHeight + 288) - (Monster.sfMove[Monster.nAni].nHeight / Monster.nReductionRate * Monster.GetRange()))
	//		Monster.ChangeyPosition(Monster.sfMove[Monster.nAni].nHeight / Monster.nReductionRate * Monster.GetRange());
	//}
	pMonster->SetMType(nRandomType);
	pMonsterList.push_back(pMonster);
}
