#ifndef MYMATH_H_
#define MYMATH_H_

#include "main.h"
#define MAX_LEVEL (40)

enum EnemyMove
{
	wait = 0,
	move,
	attack,
	heal,
	end,
};

enum PlayerMove
{
	NotSelect = 0,
	Select,
	Manu,
	BattleSelect,
	HealSelect,
	Fin,
};



#endif // !MYMATH_H_
