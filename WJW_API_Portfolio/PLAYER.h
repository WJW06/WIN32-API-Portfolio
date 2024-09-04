#pragma once
#include "BIOLOGY.h"
//#include "EQUIPMENT.h"
//#include "ARMOR.h"
//#include "ORNAMENT.h"

class HEART;

class PLAYER :
	public BIOLOGY
{
public:
	PLAYER();
	virtual ~PLAYER();
private:
	HEART*		pHeart;
	int			nLevel;
	int			nScore;
	int			nExp;
	int			nMaxExp;
	//ARMOR		UsedArmor[6];
	//EQUIPMENT* pItemSlot[10];
	//ORNAMENT* pOrnamentList[5];
	//int			iItemNum;
	//int			iOrnamentNum;
	//int			nCoin;
	static bool	bCheckNum;
public:
	HEART*		GetHeart() { return pHeart; }
	int			GetLevel() { return nLevel; }
	int			GetScore() { return nScore; }
	int			GetExp() { return nExp; }
	int			GetMaxExp() { return nMaxExp; }
	//EQUIPMENT* GetItem(int _ItemNum) { return pItemSlot[_ItemNum]; }
	//ORNAMENT* GetOrnament(int _OrnamentNum) { return pOrnamentList[_OrnamentNum]; }
	//int			GetCoin() { return nCoin; }
	//bool		GetCheckNum() { return bCheckNum; }

	void		SetLevel(int _Level) { nLevel = _Level; }
	void		SetScore(int _Score) { nScore = _Score; }
	void		SetExp(int _Exp) { nExp = _Exp; }
	void		SetMaxExp(int _MaxExp) { nMaxExp = _MaxExp; }
	//void		SetCoin(int _Coin) { nCoin = _Coin; }
	//void		SetCheckNum(bool _CheckNum) { bCheckNum = _CheckNum; }

	void		CreateHeart();
	void		InitPlayerState(char* _Name);
	//void		TakeItemState(EQUIPMENT* _Item);
	void		LevelUp();
	void		ScoreUp(int _Score) { nScore += _Score; }
	void		ExpUp(int _Exp) { nExp += _Exp; }
	//void		AddCoin(int _AddCoin) { nCoin += _AddCoin; }
	//void		AddItem(EQUIPMENT* _Item);
	//int			DeleteItemNum();
	//int			ChoiceItemNum();
	//void		AddOrnament(EQUIPMENT* _Ornament);
	//int			DeleteOrnamentNum();
	//int			ChoiceOrnamentNum();
	//bool		CheckUsedEquipment(EQUIPMENT* _Item);
	//bool		CheckUsedWeapon(EQUIPMENT* _Weapon);
	//bool		CheckArmorType(EQUIPMENT* _Armor);
	//bool		CheckOrnament(EQUIPMENT* _Ornament);
	//void	ItemMaxSay(int _ItemNum);
};

