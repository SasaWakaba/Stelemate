#ifndef MYMATH_H_
#define MYMATH_H_

#include "main.h"
#include "../Charcter/CCharacterData.h"
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

#define ADVANTAGEOUS (1.2f)
#define DISADVANTAGE (0.8f)

class myMath
{
public:
	static int Hit(int dex, int luk, int weaponHit) { return (int)((dex * 1.5f) + (luk * 0.5f) + weaponHit); }
	static int Avoidance(int speed, int luk) { return (int)((speed * 1.5f) + (luk * 0.5f)); }
	static int Critical(int dex, int luk, int weaponCri) { return (int)((dex + luk) / 2 + weaponCri); }
	static int AttackSpeed(int speed, int attack, int weaponWeight) { return (int)(speed - (weaponWeight - (attack / 5))); }
	static float Advantage(JOBCLASS atkjob, JOBCLASS defjob)
{
	if (atkjob == Swordman)
	{
		switch (defjob)
		{
		case Swordman:
			return 1.0f;
			break;
		case Lancer:
			return DISADVANTAGE;
			break;
		case Archer:
			return ADVANTAGEOUS;
			break;
		case Sorcerer:
			return 1.0f;
			break;
		}
	}
	else if (atkjob == Lancer)
	{
		switch (defjob)
		{
		case Swordman:
			return ADVANTAGEOUS;
			break;
		case Lancer:
			return 1.0f;
			break;
		case Archer:
			return DISADVANTAGE;
			break;
		case Sorcerer:
			return ADVANTAGEOUS;
			break;
		}
	}
	else if (atkjob == Archer)
	{
		switch (defjob)
		{
		case Swordman:
			return DISADVANTAGE;
			break;
		case Lancer:
			return ADVANTAGEOUS;
			break;
		case Archer:
			return 1.0f;
			break;
		case Sorcerer:
			return 1.0f;
			break;
		}
	}
	else if (atkjob == Sorcerer)
	{
		switch (defjob)
		{
		case Swordman:
			return 1.0f;
			break;
		case Lancer:
			return DISADVANTAGE;
			break;
		case Archer:
			return ADVANTAGEOUS;
			break;
		case Sorcerer:
			return 1.0f;
			break;
		}
	}
	else
	{
		return -1.0f;
	}
}
};

#endif // !MYMATH_H_
