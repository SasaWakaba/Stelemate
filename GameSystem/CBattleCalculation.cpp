#include "../common/main.h"
#include "../common/math.h"
#include "../Charcter/CCharcterBase.h"
#include "../Charcter/CCharacterData.h"

#include "CBattleCalculation.h"
#include <random>

//命中と必殺の判定乱数
int Random()
{
	std::mt19937 mtRand(0);
	std::uniform_int_distribution<uint32_t> get_rand(0, 100);

	return get_rand(mtRand);
}

//総ステータス
int CBattleCalculation::AllPower(STATUS status)
{
	int Power;
	Power = status.Attack + status.Defense + status.Dexterity + status.Luck + status.MagicDefense + status.Speed;
	return Power;
}

int CBattleCalculation::Damage(CCharcterBase* atk, CCharcterBase* def)
{
	STATUS* atkStatus = atk->GetStatus();
	STATUS* defStatus = def->GetStatus();
	//命中率
	int hitnum = myMath::Hit(atkStatus->Dexterity, atkStatus->Luck, atk->GetWeapon()->Hit) - myMath::Avoidance(defStatus->Speed, defStatus->Luck);

	//0以下ならミス
	if (hitnum <= 0)
	{
		return -1;
	}
	else if (hitnum < 100)//100以下なら判定
	{
		if (Random() > hitnum)//判定失敗したらミス
		{
			return -1;
		}
	}

	
	int attacknum = 1;
	//連撃判定
	if (myMath::AttackSpeed(atkStatus->Speed, atkStatus->Attack, atk->GetWeapon()->Weight)
		- myMath::AttackSpeed(defStatus->Speed, defStatus->Attack, def->GetWeapon()->Weight) >= 4)
	{
		attacknum = 2;
	}

	int damage = 0;
	for (int i = 0; i < attacknum; i++)
	{
		int dam = (int)(atkStatus->Attack + (atk->GetWeapon()->Attack * myMath::Advantage(atk->m_JobClass, def->m_JobClass)) - defStatus->Defense);
		if (myMath::Critical(atkStatus->Dexterity, atkStatus->Luck, atk->GetWeapon()->Cri) - defStatus->Luck > Random())
		{
			dam *= 2;
		}
		damage += dam;
	}

	return damage;
}

int CBattleCalculation::DamageMagic(CCharcterBase* atk, CCharcterBase* def)
{
	STATUS* atkStatus = atk->GetStatus();
	STATUS* defStatus = def->GetStatus();
	int hitnum = myMath::Hit(atkStatus->Dexterity, atkStatus->Luck, atk->GetWeapon()->Hit) - myMath::Avoidance(defStatus->Speed, defStatus->Luck);
	if (hitnum <= 0)
	{
		return -1;
	}
	else if (hitnum < 100)
	{
		if (Random() > hitnum)
		{
			return -1;
		}
	}

	int attacknum = 1;
	if (myMath::AttackSpeed(atkStatus->Speed, atkStatus->Attack, atk->GetWeapon()->Weight)
		- myMath::AttackSpeed(defStatus->Speed, defStatus->Attack, def->GetWeapon()->Weight) >= 4)
	{
		attacknum = 2;
	}

	int damage = 0;
	for (int i = 0; i < attacknum; i++)
	{
		int dam = (int)(atkStatus->Attack + (atk->GetWeapon()->Attack * myMath::Advantage(atk->m_JobClass, def->m_JobClass)) - defStatus->MagicDefense);
		if (myMath::Critical(atkStatus->Dexterity, atkStatus->Luck, atk->GetWeapon()->Cri) - defStatus->Luck > Random())
		{
			dam *= 2;
		}
		damage += dam;
	}

	return damage;
}

//float CBattleCalculation::Advantage(JOBCLASS atkjob, JOBCLASS defjob)
//{
//	if (atkjob == Swordman)
//	{
//		switch (defjob)
//		{
//		case Swordman:
//			return 1.0f;
//			break;
//		case Lancer:
//			return DISADVANTAGE;
//			break;
//		case Archer:
//			return ADVANTAGEOUS;
//			break;
//		case Sorcerer:
//			return 1.0f;
//			break;
//		}
//	}
//	else if(atkjob == Lancer)
//	{
//		switch (defjob)
//		{
//		case Swordman:
//			return ADVANTAGEOUS;
//			break;
//		case Lancer:
//			return 1.0f;
//			break;
//		case Archer:
//			return DISADVANTAGE;
//			break;
//		case Sorcerer:
//			return ADVANTAGEOUS;
//			break;
//		}
//	}
//	else if (atkjob == Archer)
//	{
//		switch (defjob)
//		{
//		case Swordman:
//			return DISADVANTAGE;
//			break;
//		case Lancer:
//			return ADVANTAGEOUS;
//			break;
//		case Archer:
//			return 1.0f;
//			break;
//		case Sorcerer:
//			return 1.0f;
//			break;
//		}
//	}
//	else if (atkjob == Sorcerer)
//	{
//		switch (defjob)
//		{
//		case Swordman:
//			return 1.0f;
//			break;
//		case Lancer:
//			return DISADVANTAGE;
//			break;
//		case Archer:
//			return ADVANTAGEOUS;
//			break;
//		case Sorcerer:
//			return 1.0f;
//			break;
//		}
//	}
//	else
//	{
//		return -1.0f;
//	}
//}