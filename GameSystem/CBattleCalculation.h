#ifndef CBATTLE_CALCUlATION_H_
#define CBATTLE_CALCULATION_H_

struct STATUS;

class CBattleCalculation
{
public:
	//HPÆÚ®ÍÈOÌXe[^XÌv
	static int AllPower(STATUS status);

	//Í + íU 
	int AttackPower(int attack, int weponAttack);

	//Z + í½
	int Hit(int dex, int weponHit);

	//(Z+K^) / 2 + íKE
	int Critical(int dex, int luk, int weponCri);

	//¬³ - (íd³ - (Í / 5))
	int AttackSpeed(int speed, int attack, int weponWeit);


};


#endif // CBATTLE_CALCUlATION_H_
