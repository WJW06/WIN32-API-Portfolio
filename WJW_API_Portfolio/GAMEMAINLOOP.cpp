#include <math.h>
#include "GAMEMAINLOOP.h"
#include "MONSTERENGINE.h"
#include "COLLIDER.h"

extern int nBgX, nBgY, nMvX, nMvY;

extern HDC hdc;

extern int     nGameState;
extern enum Game_State
{
    State_Waiting,
    State_Playing,
    State_End
};

int     nStage;

extern PLAYER*  pPlayer;
BULLET*         pBullet;
list<BULLET*>   pBulletList;
list<BULLET*>::iterator  pBLIter;

MONSTER*        pMonster;
list<MONSTER*>  pMonsterList;
list<MONSTER*>::iterator pMLIter;
list<MONSTER*>::iterator pMLLoopIter;
int             nMonsterSpawnTime;

void MainLoop(HWND hWnd)
{
    if (nGameState != State_Playing) return;
    nStage = pPlayer->GetScore() / 1000 + 1;

    pPlayer->Update();
    //ShowDistance(hWnd, pPlayer);
    if (pPlayer->GetExp() >= pPlayer->GetMaxExp())
        pPlayer->LevelUp();
    if (pPlayer->GetAS() <= pPlayer->GetASMax())
        pPlayer->ASUp(0.1f);

    MonsterSpawn();
    //if (nMonsterSpawnTime++ == 0)
    //{
    //    pMonster = new CAKE;
    //    MakeCakeSurface(hdc, pMonster->sfMove, RGB(255, 255, 0));
    //    MakeCakeAttackSurface(hdc, pMonster->sfShoot, RGB(255, 255, 0));
    //    pMonster->SetRealWidth(pMonster->sfMove[pMonster->nAni].nWidth);
    //    pMonster->SetRealHeight(pMonster->sfMove[pMonster->nAni].nHeight);
    //    pMonster->SetxPosition(500);
    //    pMonster->SetyPosition(200);
    //    pMonsterList.push_back(pMonster);
    //}
    //if (pMonsterList.size() == 0) nMonsterSpawnTime = 0;
    if (pMonsterList.size())
    {
        pMLIter = pMonsterList.begin();
        for (int i = 0; i < pMonsterList.size(); ++i)
        {
            if (pMLIter._Ptr->_Myval->GetAS() <= pMLIter._Ptr->_Myval->GetASMax())
                pMLIter._Ptr->_Myval->ASUp(0.1f);
            pMLIter._Ptr->_Myval->Update();
            //ShowDistance(hWnd, *pMLIter);
            pMLIter._Ptr->_Myval->NavigationAI(hWnd, pPlayer);
            if (pMonsterList.size() >= 2)
            {
                pMLLoopIter = pMonsterList.begin();
                for (int j = 0; j < pMonsterList.size(); ++j)
                {
                    if (pMLIter == pMLLoopIter) continue;
                    pMLIter._Ptr->_Myval->BumpIntoMFM(pMLLoopIter._Ptr->_Myval);
                    pMLLoopIter._Ptr->_Myval->Update();
                    ++pMLLoopIter;
                }
            }
            ++pMLIter;
        }
    }
    if (pBulletList.size())
    {
        pBLIter = pBulletList.begin();
        for (; pBLIter != pBulletList.end();)
        {
            if (pBLIter._Ptr->_Myval->GetBulletType() == Type_Arrow)
            {
                switch (pBLIter._Ptr->_Myval->nAni)
                {
                case TopBullet:
                    pBLIter._Ptr->_Myval->SetTheta(PI / 2);
                    if (pBLIter._Ptr->_Myval->GetyPosition() + pBLIter._Ptr->_Myval->GetRealHeight() - nBgY < 0)
                    {
                        pBLIter = pBulletList.erase(pBLIter);
                        if (pBulletList.size() == 0) return;
                        continue;
                    }
                    break;
                case RightBullet:
                    pBLIter._Ptr->_Myval->SetTheta(0);
                    if (pBLIter._Ptr->_Myval->GetxPosition() - pBLIter._Ptr->_Myval->GetRealWidth() + nBgX > MaxClientWidth)
                    {
                        pBLIter = pBulletList.erase(pBLIter);
                        if (pBulletList.size() == 0) return;
                        continue;
                    }
                    break;
                case BottomBullet:
                    pBLIter._Ptr->_Myval->SetTheta(-PI / 2);
                    if (pBLIter._Ptr->_Myval->GetyPosition() - pBLIter._Ptr->_Myval->GetRealHeight() + nBgY > MaxClientHeight)
                    {
                        pBLIter = pBulletList.erase(pBLIter);;
                        if (pBulletList.size() == 0) return;
                        continue;
                    }
                    break;
                case LeftBullet:
                    pBLIter._Ptr->_Myval->SetTheta(PI);
                    if (pBLIter._Ptr->_Myval->GetxPosition() + pBLIter._Ptr->_Myval->GetRealWidth() - nBgX < 0)
                    {
                        pBLIter = pBulletList.erase(pBLIter);
                        if (pBulletList.size() == 0) return;
                        continue;
                    }
                    break;
                }
            }
            //if (pBLIter._Ptr->_Myval->GetBulletType() == Type_MonsterBullet)
            //{
            //    switch (pBLIter._Ptr->_Myval->nAni)
            //    {
            //    case TopRightBullet:
            //        pBLIter._Ptr->_Myval->SetTheta();
            //        if (pBLIter._Ptr->_Myval->GetyPosition() + pBLIter._Ptr->_Myval->GetRealHeight() - nBgY < 0)
            //        {
            //            pBLIter = pBulletList.erase(pBLIter);
            //            if (pBulletList.size() == 0) return;
            //            continue;
            //        }
            //        if (pBLIter._Ptr->_Myval->GetxPosition() - pBLIter._Ptr->_Myval->GetRealWidth() + nBgX > MaxClientWidth)
            //        {
            //            pBLIter = pBulletList.erase(pBLIter);
            //            if (pBulletList.size() == 0) return;
            //            continue;
            //        }
            //        break;
            //    case TopLeftBullet:

            //        if (pBLIter._Ptr->_Myval->GetyPosition() + pBLIter._Ptr->_Myval->GetRealHeight() - nBgY < 0)
            //        {
            //            pBLIter = pBulletList.erase(pBLIter);
            //            if (pBulletList.size() == 0) return;
            //            continue;
            //        }
            //        if (pBLIter._Ptr->_Myval->GetxPosition() + pBLIter._Ptr->_Myval->GetRealWidth() - nBgX < 0)
            //        {
            //            pBLIter = pBulletList.erase(pBLIter);
            //            if (pBulletList.size() == 0) return;
            //            continue;
            //        }
            //        break;
            //    case BottomRightBullet:

            //        if (pBLIter._Ptr->_Myval->GetyPosition() - pBLIter._Ptr->_Myval->GetRealHeight() + nBgY > MaxClientHeight)
            //        {
            //            pBLIter = pBulletList.erase(pBLIter);;
            //            if (pBulletList.size() == 0) return;
            //            continue;
            //        }
            //        if (pBLIter._Ptr->_Myval->GetxPosition() - pBLIter._Ptr->_Myval->GetRealWidth() + nBgX > MaxClientWidth)
            //        {
            //            pBLIter = pBulletList.erase(pBLIter);
            //            if (pBulletList.size() == 0) return;
            //            continue;
            //        }
            //        break;
            //    case BottomLeftBullet:

            //        if (pBLIter._Ptr->_Myval->GetyPosition() - pBLIter._Ptr->_Myval->GetRealHeight() + nBgY > MaxClientHeight)
            //        {
            //            pBLIter = pBulletList.erase(pBLIter);;
            //            if (pBulletList.size() == 0) return;
            //            continue;
            //        }
            //        if (pBLIter._Ptr->_Myval->GetxPosition() + pBLIter._Ptr->_Myval->GetRealWidth() - nBgX < 0)
            //        {
            //            pBLIter = pBulletList.erase(pBLIter);
            //            if (pBulletList.size() == 0) return;
            //            continue;
            //        }
            //        break;
            //    }
            //}
            pBLIter._Ptr->_Myval->BulletUpdate();
            pBLIter._Ptr->_Myval->Update();
            //ShowDistance(hWnd, *pBLIter);
            if (pBulletList.size() >= 2)
            {
                ++pBLIter;
                continue;
            }
            if (pMonsterList.size())
            {
                pBLIter = pBulletList.begin();
                pMLIter = pMonsterList.begin();
                for (int i = 0; i < pMonsterList.size(); ++i)
                {
                    if (pBLIter._Ptr->_Myval->GetBulletType() == Type_Arrow)
                        pBLIter._Ptr->_Myval->CheckConflict(pMLIter._Ptr->_Myval);
                    if (pBLIter._Ptr->_Myval->GetBulletType() == Type_MonsterBullet)
                        pBLIter._Ptr->_Myval->CheckConflict(pPlayer);
                    if (pMLIter._Ptr->_Myval->GetHp() <= 0)
                    {
                        pMLIter._Ptr->_Myval->AfterDeath(pPlayer);
                        pMLIter = pMonsterList.erase(pMLIter);
                    }
                    else ++pMLIter;
                    if (pBLIter._Ptr->_Myval->GetHp() <= 0)
                    {
                        pBLIter = pBulletList.erase(pBLIter);
                        if (pBulletList.size() == 0) return;
                        continue;
                    }
                }
                if (pBulletList.size() == 1) return;
                ++pBLIter;
            }
            else
            {
                if (pBulletList.size() == 1) return;
                ++pBLIter;
            }
        }
    }
}

void MonsterSpawn()
{
    if (nMonsterSpawnTime++ >= 200)
    {
        RandomSpawnMonster(rand() % Type_MonsterEnd);
        nMonsterSpawnTime = 0;
    }
}
