#ifndef CBATTLE_CALCUlATION_H_
#define CBATTLE_CALCULATION_H_

struct STATUS;

class CBattleCalculation
{
public:
	//HP�ƈړ��͈ȊO�̃X�e�[�^�X�̍��v
	static int AllPower(STATUS status);

	//�� + ����U�� 
	int AttackPower(int attack, int weponAttack);

	//�Z + ���햽��
	int Hit(int dex, int weponHit);

	//(�Z+�K�^) / 2 + ����K�E
	int Critical(int dex, int luk, int weponCri);

	//���� - (����d�� - (�� / 5))
	int AttackSpeed(int speed, int attack, int weponWeit);


};


#endif // CBATTLE_CALCUlATION_H_
