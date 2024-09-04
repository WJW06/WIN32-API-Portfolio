#include <iostream>
#include <conio.h>
#include "PLAYER.h"
#include "COLLIDER.h"
#include "HEART.h"
//#include "ENGIN.h"

using namespace std;

bool PLAYER::bCheckNum = true;

PLAYER::PLAYER()
{
	if (bCheckNum)
	{
		char Name[40];
		cin >> Name;
		InitPlayerState(Name);
		CreateCollider();
	}
}

PLAYER::~PLAYER()
{
	bCheckNum = true;
}

void PLAYER::CreateHeart()
{
	pHeart = new HEART;
	pHeart->SetHp(&nHp);
	pHeart->SetMaxHp(5);
}

void PLAYER::InitPlayerState(char* _Name)
{
	nAni = 0;
	nReductionRate = 3;
	nHp = 5;
	CreateHeart();
	nStr = 2;
	fASMax = 3.f;
	nRange = 6;
	fSpeed = 3.f;
	nLevel = 1;
	nScore = 0;
	nBiologyType = Type_Player;
	nExp = 0;
	nMaxExp = 4;
	//iItemNum = 0;
	//iOrnamentNum = 0;
	bCheckNum = false;
}

//void PLAYER::TakeItemState(EQUIPMENT* _Item)
//{
//	nHp += _Item->GetHealth();
//	nDef += _Item->GetDefense();
//	nStr += _Item->GetStrength();
//	nSpeed += _Item->GetSpeed();
//	nLuck += _Item->GetLuck();
//}

void PLAYER::LevelUp()
{
	nExp -= nMaxExp;
	nLevel += 1;
	nMaxExp = nMaxExp * 3 / 2;
	if (nLevel % 5 == 0)
	{
		nStr += 1;
		fSpeed += 0.1f;
	}
}


//void PLAYER::AddItem(EQUIPMENT* _Item)
//{
//	if (iItemNum >= 10)
//	{
//		int CheckKey = DeleteItemNum();
//		if (CheckKey == -1)
//		{
//			delete _Item;
//			_Item = NULL;
//			return;
//		}
//	}
//	if (CheckUsedEquipment(_Item) == false)
//	{
//		pItemSlot[iItemNum++] = _Item;
//	}
//}
//
//int PLAYER::DeleteItemNum()
//{
//	int ChoiceNum, CheckKey;
//	ChoiceNum = ChoiceItemNum();
//	while (1)
//	{
//		cout << "네 : 1 / 아니요(새로 얻은 아이템이 사라집니다.) : 2\n";
//		CheckKey = _getch();
//		if (SystemEngin::ReCheckKey()) continue;
//		switch (CheckKey)
//		{
//		case 49:
//			cout << pItemSlot[ChoiceNum]->GetName() << " 아이템을 버리셨습니다.\n\n";
//			delete pItemSlot[ChoiceNum];
//			pItemSlot[ChoiceNum] = NULL;
//			--iItemNum;
//			return ChoiceNum;
//		case 50:
//			cout << "새 아이템을 버리셨습니다.\n\n";
//			return -1;
//		default:
//			cout << "번호를 잘못 누르셨습니다.\n\n";
//			break;
//		}
//	}
//	cout << "Enter <<" << endl << endl;
//	getchar();
//}
//
//int PLAYER::ChoiceItemNum()
//{
//	int ChoiceNum;
//	cout << "어떤 아이템을 선택하시겠습니까?\n\n";
//	for (int i = 0; i < 10; ++i)
//		cout << i + 1 << ". " << pItemSlot[i]->GetName() << endl;
//	while (1)
//	{
//		cout << endl << "번호 : ";
//		cin >> ChoiceNum;
//		if (ChoiceNum < 1 || ChoiceNum > 10) cout << "\n다시 입력해주세요.\n";
//	}
//	return ChoiceNum - 1;
//}
//
//void PLAYER::AddOrnament(EQUIPMENT* _Ornament)
//{
//	if (iOrnamentNum >= 5)
//	{
//		int CheckKey = DeleteOrnamentNum();
//		if (CheckKey == -1)
//		{
//			delete _Ornament;
//			_Ornament = NULL;
//			return;
//		}
//	}
//	ORNAMENT* pOrnament = dynamic_cast<ORNAMENT*>(_Ornament);
//	if (pOrnament == NULL)
//	{
//		cout << "Dynamic 캐스팅 실패!\n";
//		return;
//	}
//	if (GetIsUsedWeapon() == true)
//	{
//		if (GetUsedWeapon()->GetIsUsedOrnament() == false) GetUsedWeapon()->AddOrnament(pOrnament);
//		else pOrnamentList[iOrnamentNum++] = pOrnament;
//	}
//	else pOrnamentList[iOrnamentNum++] = pOrnament;
//}
//
//int PLAYER::DeleteOrnamentNum()
//{
//	int ChoiceNum, CheckKey;
//	ChoiceNum = ChoiceOrnamentNum();
//	cout << "정말 이 장식품을 선택하시겠습니까?\n\n";
//	while (1)
//	{
//		cout << "네 : 1 / 아니요(새로 얻은 장식품이 사라집니다.) : 2\n";
//		CheckKey = _getch();
//		if (SystemEngin::ReCheckKey()) continue;
//		switch (CheckKey)
//		{
//		case 49:
//			cout << pOrnamentList[ChoiceNum]->GetName() << " 장식품을 버리셨습니다.\n\n";
//			delete pOrnamentList[ChoiceNum];
//			pOrnamentList[ChoiceNum] = NULL;
//			--iOrnamentNum;
//			return ChoiceNum;
//		case 50:
//			cout << "새 장식품을 버리셨습니다.\n\n";
//			return -1;
//		default:
//			cout << "번호를 잘못 누르셨습니다.\n\n";
//			break;
//		}
//	}
//	cout << "Enter <<\n\n";
//	getchar();
//}
//
//int PLAYER::ChoiceOrnamentNum()
//{
//	int ChoiceNum;
//	cout << "어떤 장식품을 선택하시겠습니까?\n\n";
//	for (int i = 0; i < 5; ++i)
//		cout << i + 1 << ". " << pOrnamentList[i]->GetName() << endl;
//	while (1)
//	{
//		cout << endl << "번호 : ";
//		cin >> ChoiceNum;
//		if (ChoiceNum < 1 || ChoiceNum > 5) cout << "\n다시 입력해주세요.\n";
//	}
//	return ChoiceNum - 1;
//}


//bool PLAYER::CheckUsedEquipment(EQUIPMENT* _Item)
//{
//	switch (_Item->GetEquipmentType())
//	{
//	case 0:	// Type_Weapon
//		if (CheckUsedWeapon(_Item)) return true;
//		break;
//	case 1: // Type_Armor
//		if (CheckArmorType(_Item)) return true;
//		break;
//	case 2: // Type_Ornament
//		if (CheckOrnament(_Item)) return true;
//		break;
//	default:
//		cout << "Armor 타입 오류" << endl;
//		break;
//	}
//	return false;
//}
//
//bool PLAYER::CheckUsedWeapon(EQUIPMENT* _Weapon)
//{
//	if (GetUsedWeapon()->GetWeaponType() == -1)
//	{
//		WEAPON* Weapon = dynamic_cast<WEAPON*>(_Weapon);
//		if (Weapon == NULL)
//		{
//			cout << "Weapon 다이나믹 캐스트 실패\n";
//			return false;
//		}
//		SetUsedWeapon(*Weapon);
//		TakeItemState(_Weapon);
//		SetIsUsedWeapon(true);
//		cout << Weapon->GetName() << " 장착!\n";
//		return true;
//	}
//	return false;
//}
//
//bool PLAYER::CheckArmorType(EQUIPMENT* _Armor)
//{
//	ARMOR* Armor = dynamic_cast<ARMOR*>(_Armor);
//	if (Armor == NULL)
//	{
//		cout << "Armor 다이나믹 캐스트 실패\n";
//		return false;
//	}
//	switch (Armor->GetArmorType())
//	{
//	case 0:
//		if (UsedArmor[0].GetArmorType() == -1)
//		{
//			UsedArmor[0] = *Armor;
//			TakeItemState(_Armor);
//			cout << UsedArmor[0].GetName() << " 장착!\n";
//			return true;
//		}
//		break;
//	case 1:
//		if (UsedArmor[1].GetArmorType() == -1)
//		{
//			UsedArmor[1] = *Armor;
//			TakeItemState(_Armor);
//			cout << UsedArmor[1].GetName() << " 장착!\n";
//			return true;
//		}
//		break;
//	case 2:
//		if (UsedArmor[2].GetArmorType() == -1)
//		{
//			UsedArmor[2] = *Armor;
//			TakeItemState(_Armor);
//			cout << UsedArmor[2].GetName() << " 장착!\n";
//			return true;
//		}
//		break;
//	case 3:
//		if (UsedArmor[3].GetArmorType() == -1)
//		{
//			UsedArmor[3] = *Armor;
//			TakeItemState(_Armor);
//			cout << UsedArmor[3].GetName() << " 장착!\n";
//			return true;
//		}
//		break;
//	case 4:
//		if (UsedArmor[4].GetArmorType() == -1)
//		{
//			UsedArmor[4] = *Armor;
//			TakeItemState(_Armor);
//			cout << UsedArmor[4].GetName() << " 장착!\n";
//			return true;
//		}
//		break;
//	case 5:
//		if (UsedArmor[5].GetArmorType() == -1)
//		{
//			UsedArmor[5] = *Armor;
//			TakeItemState(_Armor);
//			cout << UsedArmor[5].GetName() << " 장착!\n";
//			return true;
//		}
//		break;
//	default:
//		cout << "Armor 타입 오류\n";
//	}
//	return false;
//}

//bool PLAYER::CheckOrnament(EQUIPMENT* _Ornament)
//{
//
//	return false;
//}

//void PLAYER::ItemMaxSay(int _ItemNum)
//{
//	cout << endl << "아이템 갯수가 최대치에 도달하여 아이템을 버리셔야 합니다." << endl;
//	int DelNum = DeleteItemNum();
//	if (DelNum)
//	{
//		cout << endl << "아이템 흭득! (아이템 공격력 : " << _ItemNum << ")" << endl << endl;
//		nItemSlot[DelNum] = _ItemNum;
//		AddStr(_ItemNum);
//	}
//}

