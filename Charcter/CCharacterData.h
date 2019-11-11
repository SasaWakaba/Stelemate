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
	int HP;
	int Attack;
	int Speed;
	int Defense;
	int MagicDefense;
	int Dexterity;
	int Luck;

	int MovePoint;
	Weapontype type;

}STATUS;

class CCharacterData
{
public:
	static std::map<std::string, STATUS> m_CharData;

	static void Initialize();
	static void Finalize();
};

#endif // !CCARACTER_DATA_H_
