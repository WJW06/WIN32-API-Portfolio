#pragma once

#define MaxClientWidth 1050
#define MaxClientHeight 864

#define RightMove   0
#define LeftMove    4
#define BehindMove  8
#define FrontMove   12

//#define MaxArrow            100
#define TopBullet			0
#define RightBullet         1
#define BottomBullet        2
#define LeftBullet          3
#define TopRightBullet		4
#define TopLeftBullet		5
#define BottomRightBullet	6
#define BottomLeftBullet	7

#define PI 3.1415926535f

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

#include <list>
#include "GRAPHICENGINE.h"
#include "PLAYER.h"
#include "ARROW.h"
#include "MONSTER.h"

using namespace std;