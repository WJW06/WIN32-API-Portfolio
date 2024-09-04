#pragma once
#include "OBJECT.h"

class BIOLOGY;

enum Bullet_Type {
	None = -1,
	Type_Arrow,
	Type_MonsterBullet,
	Type_BulletEnd
};

class BULLET : 
	public OBJECT
{
public:
	BULLET();
	virtual ~BULLET();
public:
	SURFACEINFO sfMoveBullet[4];
	int			nAni;
protected:
	int		nHp;
	int		nStr;
	float	fSpeed;
	float	fTheta;
	int		nBulletType;
public:
	int		GetHp() { return nHp; }
	int		GetStr() { return nStr; }
	float	GetSpeed() { return fSpeed; }
	float	GetTheta() { return fTheta; }
	int		GetBulletType() { return nBulletType; }
		
	void	SetStr(int _Str) { nStr = _Str; }
	void	SetSpeed(float _Speed) { fSpeed = _Speed; }
	void	SetTheta(float _Theta) { fTheta = _Theta; }

	void	BulletUpdate();
	void	CheckConflict(BIOLOGY* _Biology);

	virtual void	SetPlayerDirection();
	virtual double	GetDistance();
	virtual POINT	GetDirection();
};

