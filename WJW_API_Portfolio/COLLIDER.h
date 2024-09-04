#pragma once
#include <Windows.h>

class OBJECT;

class COLLIDER
{
public:
	COLLIDER();
	~COLLIDER();
private:
	OBJECT* pObject;
	POINT	pOffsetPos;
	POINT	pFinalPos;
	int		nWidth;
	int		nHeight;
	int		nId;
	static int nNextID;
	bool	bIsCollision;
public:
	POINT	GetOffsetPos() { return pOffsetPos; }
	int		GetxOffsetPos() { return pOffsetPos.x; }
	int		GetyOffsetPos() { return pOffsetPos.y; }
	POINT	GetFinalPos() { return pFinalPos; }
	int		GetxFinalPos() { return pFinalPos.x; }
	int		GetyFinalPos() { return pFinalPos.y; }
	int		GetWidth() { return nWidth; }
	int		GetHeight() { return nHeight; }
	bool	GetIsCollision() { return bIsCollision; }

	void	SetOffsetPos(POINT _OffsetPos)	{ pOffsetPos = _OffsetPos; }
	void	SetxOffsetPos(int _xOffsetPos)	{ pOffsetPos.x = _xOffsetPos; }
	void	SetyOffsetPos(int _yOffsetPos)	{ pOffsetPos.y = _yOffsetPos; }
	void	SetFinalPos(POINT _FinalPos)	{ pFinalPos = _FinalPos; }
	void	SetxFinalPos(int _xFinalPos)	{ pFinalPos.x = _xFinalPos; }
	void	SetyFinalPos(int _yFinalPos)	{ pFinalPos.y = _yFinalPos; }
	void	SetWidth(int _Width) { nWidth = _Width; }
	void	SetHeight(int _Height) { nHeight = _Height; }
	void	SetId(int _Id) { nId = _Id; }
	void	OnCollision() { bIsCollision = true; }
	void	OffCollision() { bIsCollision = false; }

	void	Update();
	void	Render();

	friend class OBJECT;
};

