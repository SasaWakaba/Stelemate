#ifndef CBATTLE_CALCUlATION_H_
#define CBATTLE_CALCULATION_H_

struct STATUS;

class CBattleCalculation
{
public:
	//HPと移動力以外のステータスの合計
	static int AllPower(STATUS status);

	//力 + 武器攻撃 
	int AttackPower(int attack, int weponAttack);

	//技 + 武器命中
	int Hit(int dex, int weponHit);

	//(技+幸運) / 2 + 武器必殺
	int Critical(int dex, int luk, int weponCri);

	//速さ - (武器重さ - (力 / 5))
	int AttackSpeed(int speed, int attack, int weponWeit);


};


#endif // CBATTLE_CALCUlATION_H_
