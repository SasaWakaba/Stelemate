#ifndef CBATTLE_CALCUlATION_H_
#define CBATTLE_CALCULATION_H_

class CCharcterBase;
//typedef STATUS;
enum JOBCLASS;


class CBattleCalculation
{
private:
	//�� + ����U�� 
	int AttackPower(int attack, int weponAttack) { return attack + weponAttack; }

	////�Z�~1.5�{�K�^�~0.5 + ���햽��
	//static int Hit(int dex, int luk, int weaponHit) { return (dex * 1.5f) + (luk * 0.5f) + weaponHit; }

	////�����~1.5�{�K�^�~0.5
	//static int Avoidance(int speed, int luk) { return (speed * 1.5f) + (luk * 0.5f); }

	////(�Z+�K�^) / 2 + ����K�E
	//static int Critical(int dex, int luk, int weaponCri) { return (dex + luk) / 2 + weaponCri; }

	////���� - (����d�� - (�� / 5))
	//static int AttackSpeed(int speed, int attack, int weaponWeight) { return speed - (weaponWeight - (attack / 5)); }

	////�����␳
	//static float Advantage(JOBCLASS atkjob, JOBCLASS defjob);
public:

	//HP�ƈړ��͈ȊO�̃X�e�[�^�X�̍��v
	static int AllPower(STATUS status);

	//�� + (����U�� �~���U�␳ �~ �L���␳) - �h��
	static int Damage(CCharcterBase* atk, CCharcterBase* def);

	//���� + (���@�U�� �~���U�␳ �~ �L���␳) - ���h
	static int DamageMagic(CCharcterBase* atk, CCharcterBase* def);
};


#endif // CBATTLE_CALCUlATION_H_
