#pragma once
#include "BIOLOGY.h"

class PLAYER;

enum Monster_Type
{
    None_Monster = -1,
    Type_Zombie,
    Type_Cake,
    //MoreAdd
    Type_MonsterEnd
};

class MONSTER :
    public BIOLOGY
{
public:
    MONSTER();
    virtual ~MONSTER();
protected:
    int     nGivingExp;
    int     nGivingScore;
    int     nMType;
    bool    bIsAttackMonster;
    bool    bIsLongRange;
public:
    int     GetGivingExp() { return nGivingExp; }
    int     GetGivingScore() { return nGivingScore; }
    int     GetMType() { return nMType; }
    bool    GetIsAttack() { return bIsAttackMonster; }
    bool    GetIsLongRange() { return bIsLongRange; }

    void    SetGivingExp(int _GivingExp) { nGivingExp = _GivingExp; }
    void    SetGivingScore(int _GivingScore) { nGivingScore = _GivingScore; }
    void    SetMType(int _MType) { nMType = _MType; }
    void    SetIsAttack(bool _IsAttack) { bIsAttackMonster = _IsAttack; }
    void    SetIsLongRange(bool _IsLongRange) { bIsLongRange = _IsLongRange; }

    void    InitMonster();
    void    AfterDeath(PLAYER* _Player);

    void    NavigationAI(HWND hWnd, PLAYER* _Player);
    void    BumpIntoMFM(MONSTER* _Monster);
};

