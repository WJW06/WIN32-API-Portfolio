#pragma once
#include "OBJECT.h"
//#include "WEAPON.h"

class BIOLOGY :
	public OBJECT
{
public:
	BIOLOGY();
	virtual ~BIOLOGY();
public:
	SURFACEINFO sfMove[16];
	SURFACEINFO	sfShoot[16];
	SURFACEINFO sfHit[16];
	int			nAni;
protected:
	//STRING	stName;
	int		nHp;
	int		nStr;
	float	fAS;
	float	fASMax;
	int     nRange;
	float	fSpeed;
	short   nMoveTime;
	bool	bIsShootMove;
	short	nHitTime;
	bool	bIsHit;
	int		nBiologyType;
	//bool	bIsFire;
	//WEAPON	UsedWeapon;
	//bool	bIsUsedWeapon;
	enum	Biology_Type
	{
		None_Biology = -1,
		Type_Player,
		Type_Monster,
		Type_Npc
	 };
public:
	void	operator=(const BIOLOGY& _Biology);
	//char* GetName() { return stName.GetBuffer(); }
	int		GetHp() { return nHp; }
	int		GetStr() { return nStr; }
	float	GetAS() { return fAS; }
	float	GetASMax() { return fASMax; }
	int		GetRange() { return nRange; }
	float	GetSpeed() { return fSpeed; }
	short	GetMoveTime() { return nMoveTime; }
	bool	GetIsShootMove() { return bIsShootMove; }
	short	GetHitTime() { return nHitTime; }
	bool	GetIsHit() { return bIsHit; }
	int		GetBiologyType() { return nBiologyType; }
	//bool	GetIsFire() { return bIsFire; }
	//WEAPON* GetUsedWeapon() { return &UsedWeapon; }
	//bool	GetIsUsedWeapon() { return bIsUsedWeapon; }

	//void	SetName(char* _Name) { stName = STRING(_Name); }
	void	SetHp(int _Hp) { nHp = _Hp; }
	void	SetStr(int _Str) { nStr = _Str; }
	void	SetAS(float _AS) { fAS = _AS; }
	void	SetASMax(float _ASMax) { fASMax = _ASMax; }
	void	SetRange(int _Range) { nRange = _Range; }
	void	SetSpeed(float _Speed) { fSpeed = _Speed; }
	void	SetMoveTime(short _MoveTime) { nMoveTime = _MoveTime; }
	void	SetIsShootMove(bool _IsShootMove) { bIsShootMove = _IsShootMove; }
	void	SetHitTime(short _HitTime) { nHitTime = _HitTime; }
	void	SetIsHit(bool _IsHit) { bIsHit = _IsHit; }
	void	SetBiologyType(int _Type) { nBiologyType = _Type; }
	//void	SetIsFire(int _IsFire) { bIsFire = _IsFire; }
	//void	SetUsedWeapon(WEAPON& _Weapon) { UsedWeapon = _Weapon; }
	//void	SetIsUsedWeapon(bool _IsUsedWeapon) { bIsUsedWeapon = _IsUsedWeapon; }
	
	void	HpUp(int _Hp) { nHp += _Hp; }
	void	StrUp(int _Str) { nStr += _Str; }
	void	ASUp(float _AS) { fAS += _AS; }
	void	ASMaxUp(float _ASMax) { fASMax += _ASMax; }
	void	RangeUp(int _Range) { nRange += _Range; }
	void	SpeedUp(float _Speed) { fSpeed += _Speed; }
	void	MoveTimeUp(short _MoveTime) { nMoveTime += _MoveTime; }
	void	HitTimeUp(short _HitTime) { nHitTime += _HitTime; }

	void	MoveAction(int nDMove);
	void	HitCount();
	void	SAttackAction(HWND hWnd, int nDMove, BIOLOGY* _Biology1, BIOLOGY* _Biology2);
	void	LAttackAction(HWND hWnd, int nDMove, int nDShoot, int _Str);
	void	MoveTimer();
	void	FireTimer();
	void	ShootBullet(HWND hWnd, int nDShoot, int _Str);
};