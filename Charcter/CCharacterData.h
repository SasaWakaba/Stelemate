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
	int HP;				//ヒットポイント、体力
	int Attack;			//攻撃力
	int Speed;			//速度
	int Defense;		//防御力
	int MagicDefense;	//魔法防御力
	int Dexterity;		//俊敏さ
	int Luck;			//運

	int MovePoint;		//行動力
	Weapontype type;	//武器タイプ

}STATUS;

class CCharacterData
{
public:
	static std::map<std::string, STATUS> m_CharData;

	static void Initialize();
	static void Finalize();
};

#endif // !CCARACTER_DATA_H_
