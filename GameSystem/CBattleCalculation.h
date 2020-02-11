#ifndef CBATTLE_CALCUlATION_H_
#define CBATTLE_CALCULATION_H_

class CCharcterBase;
//typedef STATUS;
enum JOBCLASS;


class CBattleCalculation
{
private:
	//—Í + •ŠíUŒ‚ 
	int AttackPower(int attack, int weponAttack) { return attack + weponAttack; }

	////‹Z~1.5{K‰^~0.5 + •Ší–½’†
	//static int Hit(int dex, int luk, int weaponHit) { return (dex * 1.5f) + (luk * 0.5f) + weaponHit; }

	////‘¬‚³~1.5{K‰^~0.5
	//static int Avoidance(int speed, int luk) { return (speed * 1.5f) + (luk * 0.5f); }

	////(‹Z+K‰^) / 2 + •Ší•KE
	//static int Critical(int dex, int luk, int weaponCri) { return (dex + luk) / 2 + weaponCri; }

	////‘¬‚³ - (•Šíd‚³ - (—Í / 5))
	//static int AttackSpeed(int speed, int attack, int weaponWeight) { return speed - (weaponWeight - (attack / 5)); }

	////‘Š«•â³
	//static float Advantage(JOBCLASS atkjob, JOBCLASS defjob);
public:

	//HP‚ÆˆÚ“®—ÍˆÈŠO‚ÌƒXƒe[ƒ^ƒX‚Ì‡Œv
	static int AllPower(STATUS status);

	//—Í + (•ŠíUŒ‚ ~“ÁU•â³ ~ —LŒø•â³) - –hŒä
	static int Damage(CCharcterBase* atk, CCharcterBase* def);

	//–‚—Í + (–‚–@UŒ‚ ~“ÁU•â³ ~ —LŒø•â³) - –‚–h
	static int DamageMagic(CCharcterBase* atk, CCharcterBase* def);
};


#endif // CBATTLE_CALCUlATION_H_
