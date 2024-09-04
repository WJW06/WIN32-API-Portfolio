#include "ZOMBIE.h"
#include "COLLIDER.h"

ZOMBIE::ZOMBIE()
{
	nHp = 2;
	nStr = 2;
	nReductionRate = 3;
	nRange = 1;
	nGivingExp = 1;
	nGivingScore = 100;
	nMType = Type_Zombie;
}

ZOMBIE::~ZOMBIE()
{
}
