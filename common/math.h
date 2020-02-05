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

// 2
#define quadIn(t) ((t) * (t))
#define quadOut(t) (-(t) * ((t) - 2))
#define quadInOut(t) ((t) <= 0.5) ? (t) * (t) * 2 : 1 - ((t) - 1) * ((t) - 1) * 2)

// 3
#define cubeIn(t) ((t) * (t) * (t))
#define cubeOut(t) (1 + ((t) - 1) * ((t) - 1) * ((t) - 1))
#define cubeInOut(t) ((t) <= 0.5 ? ((t) * (t) * (t) * 4) : 1 + (((t) - 1) * ((t) - 1) * ((t) - 1) * 4))

// 4
#define quartIn(t) ((t) * (t) * (t) * (t))
#define quartOut(t) ( 1 - ((t) - 1) * ((t) - 1) * ((t) - 1) * ((t) - 1))
#define quartInOut(t) (((t) <= 0.5) ? ((t) * (t) * (t) * (t) * 8) : do{(t) = (t) * 2 - 2; ((1 - (t) * (t) * (t) * (t)) / 2 + 0.5); }while(0))

// 5
#define quintIn(t) ((t) * (t) * (t) * (t) * (t))
#define quintOut(t) (do{(t) = (t) - 1; ((t) * (t) * (t) * (t) * (t) + 1;)}while(0))
#define quintInOut(t) (do{(t) *= 2; ((t) < 1) ? ((t) * (t) * (t) * (t) * (t)) / 2 : (t) -= 2; (((t) * (t) * (t) * (t) * (t) + 2) / 2); } while(0))

// smooth
#define smoothStepInOut(t) ((t) * (t) * ((t) * -2 + 3))
#define smoothStepIn(t) (2 * smoothStepInOut((t) / 2))
#define smoothStepOut(t) (2 * smoothStepInOut((t) / 2 + 0.5) - 1)

// smoother
#define smootherStepInOut(t) ((t) * (t) * (t) * ((t) * ((t) * 6 - 15) + 10))
#define smootherStepIn(t) (2 * smootherStepInOut((t) / 2))
#define smootherStepOut(t) (2 * smootherStepInOut((t) / 2 + 0.5) - 1)

// sin
#define sineIn(t) (-cosf(PI / 2 * t) + 1)
#define sineOut(t) (sinf(PI / 2 * t))
#define sineInOut(t) (-cosf(PI * t) / 2 + 0.5f)

// bounce
#define bounceIn(t) ((t) = 1 - (t);\
	(t) < 1 / 2.75f ? (1 - 7.5625f * (t) * (t)) : \
	(t) < 2 / 2.75f ? (1 - (7.5625f * ((t) - 1.5f / 2.75f) * ((t) - 1.5f / 2.75f) + 0.75f)) : \
	(t) < 2.5f / 2.75f : (1 - (7.5625f * ((t) - 2.25f / 2.75f) * ((t) - 2.25f / 2.75f) + 0.9375f)) : \
	(1 - (7.5625f * ((t) - 2.625f / 2.75f) * ((t) - 2.625f / 2.75f) + 0.984375f)))

#define bounceOut(t) (((t) < 1 / 2.75f) ? (7.5625f * (t) * (t)) : \
	((t) < 2 / 2.75f) ? (7.5625f * ((t) - 1.5f / 2.75f) * ((t) - 1.5f / 2.75f) + 0.75f) : \
	((t) < 2.5f / 2.75f) ? (7.5625f * ((t) - 2.25f / 2.75f) * ((t) - 2.25f / 2.75f) + 0.9375f) : \
	(7.5625f * (t - 2.625f / 2.75f) * ((t) - 2.625f / 2.75f) + 0.984375f))

#define bounceInOut(t) (((t) < 0.5f) ? (t) = 1 - (t) * 2 ; \
	((t) < 1 / 2.75f) ? ((1 - 7.5625f * (t) * (t)) / 2) : \
	((t) < 2 / 2.75f) ? ((1 - (7.5625f * ((t) - 1.5f / 2.75f) * ((t) - 1.5f / 2.75f) + .75)) / 2) : \
	((t) < 2.5f / 2.75f) ? ((1 - (7.5625 * ((t) - 2.25f / 2.75f) * ((t) - 2.25f / 2.75f) + 0.9375f)) / 2) : \
	((1 - (7.5625 * (t - B6) * (t - B6) + 0.984375f)) / 2) : \
	\
	(t) = (t) * 2 - 1; \
	((t) < 1 / 2.75f) ? ((7.5625f * (t) * (t)) / 2 + 0.5f) : \
	((t) < 2 / 2.75f) ? ((7.5625f * ((t) - 1.5f / 2.75f) * ((t) - 1.5f / 2.75f) + 0.75f) / 2 + 0.5f) : \
	((t) < 2.5f / 2.75f) ? ((7.5625f * ((t) - 2.25f / 2.75f) * ((t) - 2.25f / 2.75f) + 0.9375f) / 2 + 0.5f) : \
	((7.5625f * (t - 2.625f / 2.75f) * ((t) - 2.625f / 2.75f) + 0.984375f) / 2 + 0.5f)R)

// circ
#define circIn(t) (-(sqrtf(1 - (t) * (t)) - (t)))
#define circOut(t) (sqrtf(1 - ((t) - 1) * ((t) - 1)))
#define circInOut(t) (t) <= 0.5f ? ((sqrtf(1 - (t) * (t) * 4) - 1) / -2 :  (sqrtf(1 - ((t) * 2 - 2) * ((t) * 2 - 2)) + 1) / 2)

// expo
#define expoIn(t) (powf(2, 10 * ((t) - 1)))
#define	expoOut(t) (-powf(2, -10 * (t)) + 1)
#define expoInOut(t) ((t) < 0.5f ? powf(2, 10 * ((t) * 2 - 1)) / 2 : (-powf(2, -10 * ((t) * 2 - 1)) + 2) / 2)



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
		return -1.0f;
	}
};

#endif // !MYMATH_H_
