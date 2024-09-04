#pragma once
#include <windows.h>
#include "GRAPHICENGINE.h"

class COLLIDER;

class OBJECT
{
public:
	OBJECT();
	virtual ~OBJECT();
public:
	int		nReductionRate;
protected:
	POINT		pPosition;
	int			nRealWidth;
	int			nRealHeight;
	COLLIDER*	pCollider;
public:
	POINT		GetPosition()	{ return pPosition; }
	int			GetxPosition()	{ return pPosition.x; }
	int			GetyPosition()	{ return pPosition.y; }
	int			GetRealWidth()	{ return  nRealWidth; }
	int			GetRealHeight() { return nRealHeight; }
	COLLIDER*	GetCollider()	{ return pCollider; }

	void	SetPosition(POINT _Position) { pPosition = _Position; }
	void	SetxPosition(int _x) { pPosition.x = _x; }
	void	SetyPosition(int _y) { pPosition.y = _y; }
	void	SetRealWidth(int _RealWidth) { nRealWidth = _RealWidth; }
	void	SetRealHeight(int _RealHeight) { nRealHeight = _RealHeight; }

	void	ChangexPosition(int _x) { pPosition.x += _x; }
	void	ChangeyPosition(int _y) { pPosition.y += _y; }
	void	ChangeRealWidth(int _RealWidth) { nRealWidth += _RealWidth; }
	void	ChangeRealHeight(int _RealHeight) { nRealHeight += _RealHeight; }

	void	CreateCollider();
	virtual void Update() final;
};

