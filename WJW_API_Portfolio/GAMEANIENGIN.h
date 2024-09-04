#pragma once
#include "framework.h"

void    GIInit(HDC hdc);
void	WaitingAMLoop(HWND hWnd);
void    AMLoop(HWND hWnd);
void	DeathAMLoop(HWND hWnd);
void    GIDestroyAll();
//void	ShowDistance(HWND hWnd, OBJECT* _Object);
void	ShowPlayerState(HWND hWnd);
void	MakeStartButtonSurface(HDC dcScreen, SURFACEINFO* sfStartButtonInfo, COLORREF crColorKey);
void	MakeExitButtonSurface(HDC dcScreen, SURFACEINFO* sfExitButtonInfo, COLORREF crColorKey);
void    MakePlayerSurface(HDC dcScreen, SURFACEINFO* sfPlayerInfo, COLORREF crColorKey);
void    MakePlayerShootSurface(HDC dcScreen, SURFACEINFO* sfPlayerInfo, COLORREF crColorKey);
void	MakePlayerHitSurface(HDC dcScreen, SURFACEINFO* sfPlayerInfo, COLORREF crColorKey);

void	MakeZombieSurface(HDC dcScreen, SURFACEINFO* sfZombieInfo, COLORREF crColorKey);
void	MakeZombieAttackSurface(HDC dcScreen, SURFACEINFO* sfZombieInfo, COLORREF crColorKey);
void	MakeCakeSurface(HDC dcScreen, SURFACEINFO* sfCakeInfo, COLORREF crColorKey);
void	MakeCakeAttackSurface(HDC dcScreen, SURFACEINFO* sfCakeInfo, COLORREF crColorKey);

void	MakeHeartSurface(HDC dcScreen, SURFACEINFO* sfArrowInfo, COLORREF crColorKey);
void	MakeGameOverSurface(HDC dcScreen, SURFACEINFO* sfGameOverInfo, COLORREF crColorKey);
void	MakeReStartButtonSurface(HDC dcScreen, SURFACEINFO* sfReStartButtonInfo, COLORREF crColorKey);