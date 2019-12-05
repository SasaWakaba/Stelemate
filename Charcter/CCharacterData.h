#ifndef CCARACTER_DATA_H_
#define CCARACTER_DATA_H_
#include <map>

#define MAX_STATUS (9)

typedef enum
{
	Sword = 0,
	Lance,
	Bow,
	Magic,
	Wand,
}Weapontype;

enum JOBCLASS
{
	Swordman,
	Lancer,
	Archer,
	Sorcerer
};

typedef struct
{
	int HP;				//�q�b�g�|�C���g�A�̗�
	int Attack;			//�U����
	int Speed;			//���x
	int Defense;		//�h���
	int MagicDefense;	//���@�h���
	int Dexterity;		//�r�q��
	int Luck;			//�^

	int MovePoint;		//�s����
	Weapontype type;	//����^�C�v

}STATUS;

class CCharacterData
{
public:
	static std::map<std::string, STATUS> m_CharData;

	static void Initialize();
	static void Finalize();
};

#endif // !CCARACTER_DATA_H_
