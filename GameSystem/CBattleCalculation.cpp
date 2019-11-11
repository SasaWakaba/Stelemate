#include "../common/main.h"
#include "../Charcter/CCharcterBase.h"
#include "../Charcter/CCharacterData.h"

#include "CBattleCalculation.h"
#include <random>

int CBattleCalculation::AllPower(STATUS status)
{
	int Power;
	Power = status.Attack + status.Defense + status.Dexterity + status.Luck + status.MagicDefense + status.Speed;
	return Power;
}

int CBattleCalculation::Damage(CCharcterBase* atk, CCharcterBase* def)
{
	int hitnum = Hit(atk->GetStatus()->Dexterity, atk->GetStatus()->Luck, 1) - Avoidance(def->GetStatus()->Speed, def->GetStatus()->Luck);
	if (hitnum <= 0)
	{
		return -1;
	}
	else if (hitnum < 100)
	{
		std::mt19937 mtRand(0);
		std::uniform_int_distribution<uint32_t> get_rand(0, 100);


	}

	int damage = atk->GetStatus()->Attack + (/*‚±‚±‚É•ŠíUŒ‚—Í**/Advantage(atk->m_JobClass, def->m_JobClass)) - def->GetStatus()->Defense;

	return damage;
}

int CBattleCalculation::DamageMagic(CCharcterBase* atk, CCharcterBase* def)
{
	int damage = 0;

	return damage;
}

float CBattleCalculation::Advantage(JOBCLASS atkjob, JOBCLASS defjob)
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
	else if(atkjob == Lancer)
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