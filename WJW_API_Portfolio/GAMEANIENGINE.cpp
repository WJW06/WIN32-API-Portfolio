#include "GAMEANIENGIN.h"
#include "MONSTERENGINE.h"
#include "COLLIDER.h"
#include "HEART.h"

int nBgX, nBgY, nMvX, nMvY, nPrevBgX, nPrevBgY;

extern SURFACEINFO      g_sfBack;
extern SURFACEINFO      g_sfBG;
extern char             BGFileName[50];

extern int     nGameState;
extern enum Game_State
{
    State_Waiting,
    State_Playing,
    State_End
};
extern bool     bButtonType;

SURFACEINFO     sfStartButton;
SURFACEINFO     sfExitButton;

extern int nStage;

extern PLAYER*          pPlayer;
extern BULLET*          pBullet;
extern list<BULLET*>    pBulletList;
extern list<BULLET*>::iterator  pBLIter;

extern MONSTER*         pMonster;
extern list<MONSTER*>   pMonsterList;
extern list<MONSTER*>::iterator pMLIter;

SURFACEINFO sfGameOver;
SURFACEINFO sfReStartButton;

void GIInit(HDC hdc)
{
    GeCreateBackBuffer(hdc, MaxClientWidth, MaxClientHeight, 32, &g_sfBack);

    GeSetImgSurface(&g_sfBG);
    g_sfBG.hBmp = GeBmpFile2BmpHandle(BGFileName);
    GeLoadSurface(hdc, &g_sfBG);

    MakeStartButtonSurface(hdc, &sfStartButton, RGB(237, 28, 36));
    MakeExitButtonSurface(hdc, &sfExitButton, RGB(153, 217, 234));

    MakePlayerSurface(hdc, pPlayer->sfMove, RGB(255, 0, 128));
    MakePlayerShootSurface(hdc, pPlayer->sfShoot, RGB(255, 0, 128));
    MakePlayerHitSurface(hdc, pPlayer->sfHit, RGB(255, 0, 128));
    MakeHeartSurface(hdc, pPlayer->GetHeart()->sfHeart, RGB(63, 72, 204));

    MakeGameOverSurface(hdc, &sfGameOver, RGB(0, 162, 232));
    MakeReStartButtonSurface(hdc, &sfReStartButton, RGB(237, 28, 36));

    nBgX = -175;
    nBgY = -144;
    pPlayer->SetRealWidth(pPlayer->sfMove[pPlayer->nAni].nWidth / pPlayer->nReductionRate * 2);
    pPlayer->SetRealHeight(pPlayer->sfMove[pPlayer->nAni].nHeight / pPlayer->nReductionRate * 2 + 7);
}


void WaitingAMLoop(HWND hWnd)
{
    HDC     hdc;
    HPEN    NewPen, OldPen;

    GePutImage(g_sfBack.dcSurface, nBgX, nBgY, &g_sfBG);
    GePutSprite(g_sfBack.dcSurface, 800, 300, &sfStartButton);
    GeReduPutSprite(g_sfBack.dcSurface, 845, 400, &sfExitButton, 2);


    hdc = GetDC(hWnd);

    if (bButtonType)
    {
        NewPen = CreatePen(PS_SOLID, 2, RGB(0, 128, 0));
        OldPen = (HPEN)SelectObject(hdc, NewPen);
        MoveToEx(hdc,800,300,NULL);
        LineTo(hdc, 800 + sfStartButton.nWidth, 300);
        MoveToEx(hdc, 800, 300, NULL);
        LineTo(hdc, 800, 300 + sfStartButton.nHeight);
        MoveToEx(hdc, 800 + sfStartButton.nWidth, 300, NULL);
        LineTo(hdc, 800 + sfStartButton.nWidth, 300 + sfStartButton.nHeight);
        MoveToEx(hdc, 800, 300 + sfStartButton.nHeight, NULL);
        LineTo(hdc, 800 + sfStartButton.nWidth, 300 + sfStartButton.nHeight);
    }
    else
    {
        NewPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        OldPen = (HPEN)SelectObject(hdc, NewPen);
        MoveToEx(hdc, 845, 400, NULL);
        LineTo(hdc, 845 + (sfExitButton.nWidth / 2), 400);
        MoveToEx(hdc, 845, 400, NULL);
        LineTo(hdc, 845, 400 + (sfExitButton.nHeight / 2));
        MoveToEx(hdc, 845 + (sfExitButton.nWidth / 2), 400, NULL);
        LineTo(hdc, 845 + (sfExitButton.nWidth / 2), 400 + (sfExitButton.nHeight / 2));
        MoveToEx(hdc, 845, 400 + (sfExitButton.nHeight / 2), NULL);
        LineTo(hdc, 845 + (sfExitButton.nWidth / 2), 400 + (sfExitButton.nHeight / 2));
    }

    SelectObject(hdc, OldPen);
    DeleteObject(NewPen);
    GeCompleteBlt(hdc, &g_sfBack);
    ReleaseDC(hWnd, hdc);
}

void AMLoop(HWND hWnd)
{
    HDC hdc;
    switch (nGameState)
    {
    case State_Waiting:
        WaitingAMLoop(hWnd);
        break;
    case State_Playing:
    {
        if (pPlayer->GetHp() <= 0)
        {
            for (pMLIter = pMonsterList.begin(); pMLIter != pMonsterList.end();)
                pMLIter = pMonsterList.erase(pMLIter);
            for (pBLIter = pBulletList.begin(); pBLIter != pBulletList.end();)
                pBLIter = pBulletList.erase(pBLIter);
            nGameState = State_End;
        }
        nPrevBgX = nBgX;
        nPrevBgY = nBgY;

        if (pPlayer->GetxPosition() < -nBgX)
        {
            nMvX = pPlayer->GetxPosition() + nBgX;
            nBgX -= nMvX;
            pPlayer->ChangexPosition(-nMvX);
        }
        if (pPlayer->GetyPosition() < -nBgY)
        {
            nMvY = pPlayer->GetyPosition() + nBgY;
            nBgY -= nMvY;
            pPlayer->ChangeyPosition(-nMvY);
        }
        if (pPlayer->GetxPosition() + pPlayer->GetRealWidth() + nBgX > (MaxClientWidth / 6 * 4))
        {
            nMvX = (MaxClientWidth / 6 * 4) - (pPlayer->GetRealWidth() + pPlayer->GetxPosition() + nBgX);
            nBgX += nMvX;
            pPlayer->ChangexPosition(nMvX);
        }
        if (pPlayer->GetyPosition() + pPlayer->GetRealHeight() + nBgY > (MaxClientHeight / 6 * 4))
        {
            nMvY = (MaxClientHeight / 6 * 4) - (pPlayer->GetRealHeight() + pPlayer->GetyPosition() + nBgY);
            nBgY += nMvY;
            pPlayer->ChangeyPosition(nMvY);
        }

        if (nBgX > 0) nBgX = 0;
        if (nBgY > 0) nBgY = 0;

        GePutImage(g_sfBack.dcSurface, nBgX, nBgY, &g_sfBG);

        if (!pPlayer->GetIsHit())
        {
            if (pPlayer->GetIsShootMove())   GeReduPutSprite(g_sfBack.dcSurface, pPlayer->GetxPosition(), pPlayer->GetyPosition(), &pPlayer->sfShoot[pPlayer->nAni], 2);
            else                             GeReduPutSprite(g_sfBack.dcSurface, pPlayer->GetxPosition(), pPlayer->GetyPosition(), &pPlayer->sfMove[pPlayer->nAni], 2);
        }
        else
        {
            GeReduPutSprite(g_sfBack.dcSurface, pPlayer->GetxPosition(), pPlayer->GetyPosition(), &pPlayer->sfHit[pPlayer->nAni], 2);
            pPlayer->MoveTimer();
            pPlayer->HitTimeUp(1);
            if (pPlayer->GetHitTime() >= 40)
            {
                pPlayer->nAni -= 4;
                pPlayer->SetIsHit(false);
            }
        }

        for (int i = 0; i < pPlayer->GetHp(); ++i)
        {
            GePutSprite(g_sfBack.dcSurface, 850 + (30 * i), 30, &pPlayer->GetHeart()->sfHeart[0]);
        }
        if (pPlayer->GetHp() < pPlayer->GetHeart()->GetMaxHp())
        {
            for (int i = pPlayer->GetHeart()->GetMaxHp(); i - pPlayer->GetHp() > 0; --i)
                GePutSprite(g_sfBack.dcSurface, 850 + (30 * (i - 1)), 30, &pPlayer->GetHeart()->sfHeart[1]);
        }

        pBLIter = pBulletList.begin();
        for (int i = 0; i < pBulletList.size(); ++i)
        {
            GeReduPutSprite(g_sfBack.dcSurface, pBLIter._Ptr->_Myval->GetxPosition(), pBLIter._Ptr->_Myval->GetyPosition(), &pBLIter._Ptr->_Myval->sfMoveBullet[pBLIter._Ptr->_Myval->nAni], 4);
            ++pBLIter;
        }


        if (pMonsterList.size())
        {
            pMLIter = pMonsterList.begin();
            for (int i = 0; i < pMonsterList.size(); ++i)
            {
                if (nPrevBgX > nBgX) pMLIter._Ptr->_Myval->ChangexPosition(nMvX);
                if (nPrevBgX < nBgX) pMLIter._Ptr->_Myval->ChangexPosition(-nMvX);
                if (nPrevBgY > nBgY) pMLIter._Ptr->_Myval->ChangeyPosition(nMvY);
                if (nPrevBgY < nBgY) pMLIter._Ptr->_Myval->ChangeyPosition(-nMvY);
                if (pMLIter._Ptr->_Myval->GetIsShootMove())   GeReduPutSprite(g_sfBack.dcSurface, pMLIter._Ptr->_Myval->GetxPosition(), pMLIter._Ptr->_Myval->GetyPosition(), &pMLIter._Ptr->_Myval->sfShoot[pMLIter._Ptr->_Myval->nAni], 2);
                else                                          GeReduPutSprite(g_sfBack.dcSurface, pMLIter._Ptr->_Myval->GetxPosition(), pMLIter._Ptr->_Myval->GetyPosition(), &pMLIter._Ptr->_Myval->sfMove[pMLIter._Ptr->_Myval->nAni], 2);
                ++pMLIter;
            }
        }

        hdc = GetDC(hWnd);
        GeCompleteBlt(hdc, &g_sfBack);
        ReleaseDC(hWnd, hdc);
        ShowPlayerState(hWnd);

        Sleep(1000 / 144);
    }
        break;
    case State_End:
        DeathAMLoop(hWnd);
        break;
    }
}

void DeathAMLoop(HWND hWnd)
{
    HDC     hdc;
    HPEN    NewPen, OldPen;
    int     i = 0, RSBx, RSBy, EBx, EBy;
    char    strState[1000];

    RSBx = MaxClientWidth / 3;
    RSBy = MaxClientHeight / 3 * 2 - 80;
    EBx = MaxClientWidth / 3 + 110;
    EBy = MaxClientHeight / 3 * 2 + 50;

    GePutImage(g_sfBack.dcSurface, nBgX, nBgY, &g_sfBG);
    GePutSprite(g_sfBack.dcSurface, MaxClientWidth / 4, MaxClientHeight / 4 - 100, &sfGameOver);
    GePutSprite(g_sfBack.dcSurface, RSBx, RSBy, &sfReStartButton);
    GeReduPutSprite(g_sfBack.dcSurface, EBx, EBy, &sfExitButton, 2);

    SetBkMode(g_sfBack.dcSurface, TRANSPARENT);

    if (bButtonType)
    {
        NewPen = CreatePen(PS_SOLID, 2, RGB(153, 4, 255));
        OldPen = (HPEN)SelectObject(g_sfBack.dcSurface, NewPen);
        MoveToEx(g_sfBack.dcSurface, RSBx, RSBy, NULL);
        LineTo(g_sfBack.dcSurface, RSBx + sfReStartButton.nWidth, RSBy);
        MoveToEx(g_sfBack.dcSurface, RSBx, RSBy, NULL);
        LineTo(g_sfBack.dcSurface, RSBx, RSBy + sfReStartButton.nHeight);
        MoveToEx(g_sfBack.dcSurface, RSBx + sfReStartButton.nWidth, RSBy, NULL);
        LineTo(g_sfBack.dcSurface, RSBx + sfReStartButton.nWidth, RSBy + sfReStartButton.nHeight);
        MoveToEx(g_sfBack.dcSurface, RSBx, RSBy + sfReStartButton.nHeight, NULL);
        LineTo(g_sfBack.dcSurface, RSBx + sfReStartButton.nWidth, RSBy + sfReStartButton.nHeight);
    }
    else
    {   
        NewPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        OldPen = (HPEN)SelectObject(g_sfBack.dcSurface, NewPen);
        MoveToEx(g_sfBack.dcSurface, EBx, EBy, NULL);
        LineTo(g_sfBack.dcSurface, EBx + (sfExitButton.nWidth / 2), EBy);
        MoveToEx(g_sfBack.dcSurface, EBx, EBy, NULL);
        LineTo(g_sfBack.dcSurface, EBx, EBy + (sfExitButton.nHeight / 2));
        MoveToEx(g_sfBack.dcSurface, EBx + (sfExitButton.nWidth / 2), EBy, NULL);
        LineTo(g_sfBack.dcSurface, EBx + (sfExitButton.nWidth / 2), EBy + (sfExitButton.nHeight / 2));
        MoveToEx(g_sfBack.dcSurface, EBx, EBy + (sfExitButton.nHeight / 2), NULL);
        LineTo(g_sfBack.dcSurface, EBx + (sfExitButton.nWidth / 2), EBy + (sfExitButton.nHeight / 2));
    }

    wsprintf(strState, "Stage : %d", nStage);
    TextOut(g_sfBack.dcSurface, MaxClientWidth / 7 * 3 + (i++ * 100), MaxClientHeight / 5 * 3 - 100, strState, strlen(strState));

    wsprintf(strState, "Score : %d", pPlayer->GetScore());
    TextOut(g_sfBack.dcSurface, MaxClientWidth / 7 * 3 + (i++ * 100), MaxClientHeight / 5 * 3 - 100, strState, strlen(strState));

    SelectObject(g_sfBack.dcSurface, OldPen);
    DeleteObject(NewPen);
    hdc = GetDC(hWnd);
    GeCompleteBlt(hdc, &g_sfBack);
    ReleaseDC(hWnd, hdc);
}

void GIDestroyAll()
{
    for (int i = 0; i < 16; ++i)
        GeReleaseSurface(&pPlayer->sfMove[i]);
    for (int i = pBulletList.size(); i > 0; --i)
        pBulletList.pop_back();
    GeReleaseSurface(&g_sfBG);
    GeReleaseSurface(&g_sfBack);
}

void ShowDistance(HWND hWnd, OBJECT* _Object)
{
    HDC hdc = GetDC(hWnd);
    HPEN NewPen, OldPen;
    NewPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    OldPen = (HPEN)SelectObject(hdc, NewPen);
    MoveToEx(hdc, _Object->GetCollider()->GetxFinalPos(), _Object->GetCollider()->GetyFinalPos(), NULL);
    LineTo(hdc, _Object->GetCollider()->GetxFinalPos(), _Object->GetCollider()->GetHeight());
    MoveToEx(hdc, _Object->GetCollider()->GetxFinalPos(), _Object->GetCollider()->GetyFinalPos(), NULL);
    LineTo(hdc, _Object->GetCollider()->GetWidth(), _Object->GetCollider()->GetyFinalPos());
    MoveToEx(hdc, _Object->GetCollider()->GetWidth(), _Object->GetCollider()->GetyFinalPos(), NULL);
    LineTo(hdc, _Object->GetCollider()->GetWidth(), _Object->GetCollider()->GetHeight());
    MoveToEx(hdc, _Object->GetCollider()->GetxFinalPos(), _Object->GetCollider()->GetHeight(), NULL);
    LineTo(hdc, _Object->GetCollider()->GetWidth(), _Object->GetCollider()->GetHeight());
    SelectObject(hdc, OldPen);
    DeleteObject(NewPen);
    ReleaseDC(hWnd, hdc);
}

void ShowPlayerState(HWND hWnd)
{
    HDC     hdc;
    int     i = 1;
    char    strState[1000];

    SetBkMode(g_sfBack.dcSurface, TRANSPARENT);

    wsprintf(strState, "Stage : %d", nStage);
    TextOut(g_sfBack.dcSurface, 30, 30, strState, strlen(strState));

    wsprintf(strState, "Score : %d", pPlayer->GetScore());
    TextOut(g_sfBack.dcSurface, 30 + (100 * i++), 30, strState, strlen(strState));
    
    hdc = GetDC(hWnd);
    GeCompleteBlt(hdc, &g_sfBack);
    ReleaseDC(hWnd, hdc);
}

void MakeStartButtonSurface(HDC dcScreen, SURFACEINFO* sfStartButtonInfo, COLORREF crColorKey)
{
    char strName[25];

    GeSetSprSurface(&sfStartButtonInfo[0], crColorKey);
    wsprintf(strName, "BmpImg/StartButton.bmp");
    sfStartButtonInfo[0].hBmp = MakeDDBFromDIB(dcScreen, strName);
    GeLoadSurface(dcScreen, &sfStartButtonInfo[0]);

}

void MakeExitButtonSurface(HDC dcScreen, SURFACEINFO* sfExitButtonInfo, COLORREF crColorKey)
{
    char strName[25];

    GeSetSprSurface(&sfExitButtonInfo[0], crColorKey);
    wsprintf(strName, "BmpImg/ExitButton.bmp");
    sfExitButtonInfo[0].hBmp = MakeDDBFromDIB(dcScreen, strName);
    GeLoadSurface(dcScreen, &sfExitButtonInfo[0]);
}

void MakePlayerSurface(HDC dcScreen, SURFACEINFO* sfPlayerInfo, COLORREF crColorKey)
{
    int i, j = 0;
    char strName[30];
    for (i = 0; i < 4; i++)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerRight%d.bmp", ++j);
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (j = 0; i < 8; i++)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerLeft%d.bmp", ++j);
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (j = 0; i < 12; i++)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerBehind%d.bmp", ++j);
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (j = 0; i < 16; i++)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerFront%d.bmp", ++j);
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
}

void MakePlayerShootSurface(HDC dcScreen, SURFACEINFO* sfPlayerInfo, COLORREF crColorKey)
{
    int i, j = 0;
    char strName[35];
    for (i = 0; i < 4; ++i)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerRightShoot%d.bmp", ++j);
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (j = 0; i < 8; ++i)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerLeftShoot%d.bmp", ++j);
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (j = 0; i < 12; ++i)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerBehindShoot%d.bmp", ++j);
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (j = 0; i < 16; ++i)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerFrontShoot%d.bmp", ++j);
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
}

void MakePlayerHitSurface(HDC dcScreen, SURFACEINFO* sfPlayerInfo, COLORREF crColorKey)
{
    int i;
    char strName[35];
    for (i = 0; i < 4; i += 2)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerRightHit.bmp");
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (; i < 8; i += 2)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerLeftHit.bmp");
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (; i < 12; i += 2)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerBehindHit.bmp");
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (; i < 16; i += 2)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/PlayerFrontHit.bmp");
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
    for (i = 1; i < 16; i += 2)
    {
        GeSetSprSurface(&sfPlayerInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/BlankPlayer.bmp");
        sfPlayerInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfPlayerInfo[i]);
    }
}

void MakeZombieSurface(HDC dcScreen, SURFACEINFO* sfZombieInfo, COLORREF crColorKey)
{
    int i, j = 0;
    char strName[30];
    for (i = 0; i < 4; ++i)
    {
        GeSetSprSurface(&sfZombieInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/ZombieRight%d.bmp", ++j);
        sfZombieInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfZombieInfo[i]);
    }
    for (j = 0; i < 8; ++i)
    {
        GeSetSprSurface(&sfZombieInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/ZombieLeft%d.bmp", ++j);
        sfZombieInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfZombieInfo[i]);
    }
    for (j = 0; i < 12; ++i)
    {
        GeSetSprSurface(&sfZombieInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/ZombieRight%d.bmp", ++j);
        sfZombieInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfZombieInfo[i]);
    }
    for (j = 0; i < 16; ++i)
    {
        GeSetSprSurface(&sfZombieInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/ZombieLeft%d.bmp", ++j);
        sfZombieInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfZombieInfo[i]);
    }
}

void MakeZombieAttackSurface(HDC dcScreen, SURFACEINFO* sfZombieInfo, COLORREF crColorKey)
{
    int i, j = 0;
    char strName[35];
    for (i = 0; i < 4; ++i)
    {
        GeSetSprSurface(&sfZombieInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/ZombieRightAttack%d.bmp", ++j);
        sfZombieInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfZombieInfo[i]);
    }
    for (j = 0; i < 8; ++i)
    {
        GeSetSprSurface(&sfZombieInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/ZombieLeftAttack%d.bmp", ++j);
        sfZombieInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfZombieInfo[i]);
    }
    for (j = 0; i < 12; ++i)
    {
        GeSetSprSurface(&sfZombieInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/ZombieRightAttack%d.bmp", ++j);
        sfZombieInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfZombieInfo[i]);
    }
    for (j = 0; i < 16; ++i)
    {
        GeSetSprSurface(&sfZombieInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/ZombieLeftAttack%d.bmp", ++j);
        sfZombieInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfZombieInfo[i]);
    }
}

void MakeCakeSurface(HDC dcScreen, SURFACEINFO* sfCakeInfo, COLORREF crColorKey)
{
    int i, j = 0;
    char strName[30];
    for (i = 0; i < 4; ++i)
    {
        GeSetSprSurface(&sfCakeInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/CakeRight%d.bmp", ++j);
        sfCakeInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfCakeInfo[i]);
    }
    for (j = 0; i < 8; ++i)
    {
        GeSetSprSurface(&sfCakeInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/CakeLeft%d.bmp", ++j);
        sfCakeInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfCakeInfo[i]);
    }
    for (j = 0; i < 12; ++i)
    {
        GeSetSprSurface(&sfCakeInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/CakeRight%d.bmp", ++j);
        sfCakeInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfCakeInfo[i]);
    }
    for (j = 0; i < 16; ++i)
    {
        GeSetSprSurface(&sfCakeInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/CakeLeft%d.bmp", ++j);
        sfCakeInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfCakeInfo[i]);
    }
}

void MakeCakeAttackSurface(HDC dcScreen, SURFACEINFO* sfCakeInfo, COLORREF crColorKey)
{
    int i, j = 0;
    char strName[35];
    for (i = 0; i < 4; ++i)
    {
        GeSetSprSurface(&sfCakeInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/CakeRightAttack%d.bmp", ++j);
        sfCakeInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfCakeInfo[i]);
    }
    for (j = 0; i < 8; ++i)
    {
        GeSetSprSurface(&sfCakeInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/CakeLeftAttack%d.bmp", ++j);
        sfCakeInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfCakeInfo[i]);
    }
    for (j = 0; i < 12; ++i)
    {
        GeSetSprSurface(&sfCakeInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/CakeRightAttack%d.bmp", ++j);
        sfCakeInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfCakeInfo[i]);
    }
    for (j = 0; i < 16; ++i)
    {
        GeSetSprSurface(&sfCakeInfo[i], crColorKey);
        wsprintf(strName, "BmpImg/CakeLeftAttack%d.bmp", ++j);
        sfCakeInfo[i].hBmp = MakeDDBFromDIB(dcScreen, strName);
        GeLoadSurface(dcScreen, &sfCakeInfo[i]);
    }
}

void MakeHeartSurface(HDC dcScreen, SURFACEINFO* sfHeartInfo, COLORREF crColorKey)
{
    char strName[25];
    GeSetSprSurface(&sfHeartInfo[0], crColorKey);
    wsprintf(strName, "BmpImg/Heart.bmp");
    sfHeartInfo[0].hBmp = MakeDDBFromDIB(dcScreen, strName);
    GeLoadSurface(dcScreen, &sfHeartInfo[0]);

    GeSetSprSurface(&sfHeartInfo[1], crColorKey);
    wsprintf(strName, "BmpImg/EmptyHeart.bmp");
    sfHeartInfo[1].hBmp = MakeDDBFromDIB(dcScreen, strName);
    GeLoadSurface(dcScreen, &sfHeartInfo[1]);
}

void MakeGameOverSurface(HDC dcScreen, SURFACEINFO* sfGameOverInfo, COLORREF crColorKey)
{
    char strName[20];

    GeSetSprSurface(&sfGameOverInfo[0], crColorKey);
    wsprintf(strName, "BmpImg/GameOver.bmp");
    sfGameOverInfo[0].hBmp = MakeDDBFromDIB(dcScreen, strName);
    GeLoadSurface(dcScreen, &sfGameOverInfo[0]);
}

void MakeReStartButtonSurface(HDC dcScreen, SURFACEINFO* sfReStartButtonInfo, COLORREF crColorKey)
{
    char strName[25];

    GeSetSprSurface(&sfReStartButtonInfo[0], crColorKey);
    wsprintf(strName, "BmpImg/ReStartButton.bmp");
    sfReStartButtonInfo[0].hBmp = MakeDDBFromDIB(dcScreen, strName);
    GeLoadSurface(dcScreen, &sfReStartButtonInfo[0]);
}