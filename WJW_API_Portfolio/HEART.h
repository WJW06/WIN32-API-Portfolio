#pragma once
#include "OBJECT.h"

class HEART :
    public OBJECT
{
public:
    HEART();
    virtual ~HEART();
public:
    SURFACEINFO sfHeart[2];
protected:
    int*    pHp;
    int     nMaxHp;
public:
    int* GetHp() { return pHp; }
    int GetMaxHp() { return nMaxHp; }

    void SetHp(int* _Hp) { pHp = _Hp; }
    void SetMaxHp(int _MaxHp) { nMaxHp = _MaxHp; }

    void MaxHpUp(int _MaxHp) { nMaxHp += _MaxHp; }
};

