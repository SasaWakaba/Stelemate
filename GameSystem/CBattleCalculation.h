#ifndef CBATTLE_CALCUlATION_H_
#define CBATTLE_CALCULATION_H_

class CCharcterBase;
//typedef STATUS;
enum JOBCLASS;


class CBattleCalculation
{
private:
	//Í + íU 
	int AttackPower(int attack, int weponAttack) { return attack + weponAttack; }

	////Z~1.5{K^~0.5 + í½
	//static int Hit(int dex, int luk, int weaponHit) { return (dex * 1.5f) + (luk * 0.5f) + weaponHit; }

	////¬³~1.5{K^~0.5
	//static int Avoidance(int speed, int luk) { return (speed * 1.5f) + (luk * 0.5f); }

	////(Z+K^) / 2 + íKE
	//static int Critical(int dex, int luk, int weaponCri) { return (dex + luk) / 2 + weaponCri; }

	////¬³ - (íd³ - (Í / 5))
	//static int AttackSpeed(int speed, int attack, int weaponWeight) { return speed - (weaponWeight - (attack / 5)); }

	////«â³
	//static float Advantage(JOBCLASS atkjob, JOBCLASS defjob);
public:

	//HPÆÚ®ÍÈOÌXe[^XÌv
	static int AllPower(STATUS status);

	//Í + (íU ~ÁUâ³ ~ Løâ³) - hä
	static int Damage(CCharcterBase* atk, CCharcterBase* def);

	//Í + (@U ~ÁUâ³ ~ Løâ³) - h
	static int DamageMagic(CCharcterBase* atk, CCharcterBase* def);
};


#endif // CBATTLE_CALCUlATION_H_
