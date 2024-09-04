#include "PLAYERENGINE.h"

extern int  nGameState;
extern enum Game_State
{
    State_Waiting,
    State_Playing,
    State_End
};
bool    bButtonType = true;

extern list<BULLET*>    pBulletList;

void KeyProc(HWND hWnd, PLAYER* _Player)
{
    switch (nGameState)
    {
    case State_Waiting:
        StartMenuKey(hWnd);
        break;
    case State_Playing:
        MoveKey(hWnd, _Player);
        if (_Player->GetxPosition() < 0) _Player->SetxPosition(0);
        if (_Player->GetyPosition() < 0) _Player->SetyPosition(0);
        if (_Player->GetxPosition() > MaxClientWidth - _Player->GetRealWidth()) _Player->SetxPosition(MaxClientWidth - _Player->GetRealWidth());
        if (_Player->GetyPosition() > MaxClientHeight - _Player->GetRealHeight()) _Player->SetyPosition(MaxClientHeight - _Player->GetRealHeight());
        if (pBulletList.size() < 1000)
        {
            FireKey(hWnd, _Player);
        }
        break;
    case State_End:
        ReStartMenuKey(hWnd);
        break;
    }
}

void StartMenuKey(HWND hWnd)
{
    if (bButtonType)
    {
        if (GetKeyState(VK_SPACE) & 0x80)
            nGameState = State_Playing;
        if (GetKeyState(VK_RETURN) & 0x80)
            nGameState = State_Playing;
        if (GetKeyState('S') & 0x80)
            bButtonType = false;
        if (GetKeyState(VK_DOWN) & 0x80)
            bButtonType = false;
    }
    if (!bButtonType)
    {
        if (GetKeyState(VK_SPACE) & 0x80)
            SendMessage(hWnd, WM_DESTROY, NULL, NULL);
        if (GetKeyState(VK_RETURN) & 0x80)
            SendMessage(hWnd, WM_DESTROY, NULL, NULL);
        if (GetKeyState('W') & 0x80)
            bButtonType = true;
        if (GetKeyState(VK_UP) & 0x80)
            bButtonType = true;
    }
}

void MoveKey(HWND hWnd, PLAYER* _Player)
{
    if (_Player->GetIsShootMove()) return;
    if (GetKeyState('S') & 0x80)
    {
        _Player->ChangeyPosition(_Player->GetSpeed());
        _Player->MoveAction(FrontMove);
    }
    if (GetKeyState('W') & 0x80)
    {
        _Player->ChangeyPosition(-_Player->GetSpeed());
        if (GetKeyState('S') & 0x80) return;
        _Player->MoveAction(BehindMove);
    }
    if (GetKeyState('D') & 0x80)
    {
        _Player->ChangexPosition(_Player->GetSpeed());
        if (GetKeyState('W') & 0x80) return;
        if (GetKeyState('S') & 0x80) return;
        _Player->MoveAction(RightMove);
    }
    if (GetKeyState('A') & 0x80)
    {
        _Player->ChangexPosition(-_Player->GetSpeed());
        if (GetKeyState('W') & 0x80) return;
        if (GetKeyState('S') & 0x80) return;
        if (GetKeyState('D') & 0x80) return;
        _Player->MoveAction(LeftMove);
    }
}

void FireKey(HWND hWnd, PLAYER* _Player)
{
    if (_Player->GetAS() >= _Player->GetASMax())
    {
        if (GetKeyState(VK_RIGHT) & 0x80)
        {
            _Player->LAttackAction(hWnd, RightMove, RightBullet, _Player->GetStr());
            if (GetKeyState(VK_LEFT) & 0x80) return;
            if (GetKeyState(VK_UP) & 0x80) return;
            if (GetKeyState(VK_DOWN) & 0x80) return;
        }
        if (GetKeyState(VK_LEFT) & 0x80)
        {
            _Player->LAttackAction(hWnd, LeftMove, LeftBullet, _Player->GetStr());
            if (GetKeyState(VK_RIGHT) & 0x80) return;
            if (GetKeyState(VK_UP) & 0x80) return;
            if (GetKeyState(VK_DOWN) & 0x80) return;
        }
        if (GetKeyState(VK_DOWN) & 0x80)
        {
            _Player->LAttackAction(hWnd, FrontMove, BottomBullet, _Player->GetStr());
            if (GetKeyState(VK_LEFT) & 0x80) return;
            if (GetKeyState(VK_RIGHT) & 0x80) return;
            if (GetKeyState(VK_UP) & 0x80) return;
        }
        if (GetKeyState(VK_UP) & 0x80)
        {
            _Player->LAttackAction(hWnd, BehindMove, TopBullet, _Player->GetStr());
            if (GetKeyState(VK_LEFT) & 0x80) return;
            if (GetKeyState(VK_RIGHT) & 0x80) return;
            if (GetKeyState(VK_DOWN) & 0x80) return;
        }
        if (GetKeyState(VK_SPACE) & 0x80) _Player->SetIsShootMove(false);
    }
}

void ReStartMenuKey(HWND hWnd)
{
    if (bButtonType)
    {
        if (GetKeyState(VK_SPACE) & 0x80)
            SendMessage(hWnd, WM_CREATE, NULL, NULL);
        if (GetKeyState(VK_RETURN) & 0x80)
            SendMessage(hWnd, WM_CREATE, NULL, NULL);
        if (GetKeyState('S') & 0x80)
            bButtonType = false;
        if (GetKeyState(VK_DOWN) & 0x80)
            bButtonType = false;
    }
    if (!bButtonType)
    {
        if (GetKeyState(VK_SPACE) & 0x80)
            SendMessage(hWnd, WM_DESTROY, NULL, NULL);
        if (GetKeyState(VK_RETURN) & 0x80)
            SendMessage(hWnd, WM_DESTROY, NULL, NULL);
        if (GetKeyState('W') & 0x80)
            bButtonType = true;
        if (GetKeyState(VK_UP) & 0x80)
            bButtonType = true;
    }
}
