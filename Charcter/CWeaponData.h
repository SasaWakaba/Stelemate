#ifndef CWEAPON_DATA_H_
#define CWEAPON_DATA_H_
#include <map>
#define MAX_WEAPON_STATUS (5)

#include "CCharacterData.h"

typedef struct 
{
	std::string name;
	int Attack;
	int Hit;
	int Cri;
	int Weight;
	Weapontype WeaponType;
}WeaponStatus;

class CWeaponData
{
public:
	static std::map<std::string, WeaponStatus> m_WeaponData;

	static void Initialize();
	static void Finalize();
};

#endif // CWEAPON_DATA_H_
