#pragma once
#include "BULLET.h"

class ARROW :
	public BULLET
{
public:
	ARROW();
	virtual ~ARROW();
public:
	void	CreateBasicArrowSurface(HDC dcScreen, SURFACEINFO* sfArrowInfo, COLORREF crColorKey);
};

