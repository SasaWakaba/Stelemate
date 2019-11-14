#ifndef CDATA_MANAGER_H_
#define CDATA_MANAGER_H_

#include "CCharacterData.h"
#include "CWeaponData.h"
#include "../common/CDrawText.h"

class CDataManager
{
public:
	static void Load()
	{
		CCharacterData::Initialize();
		CWeaponData::Initialize();
		CDrawText::Initialize();
	}
	static void Unload()
	{
		CCharacterData::Finalize();
		CWeaponData::Finalize();
		CDrawText::Finalize();
	}
};

#endif // CDATA_MANAGER_H_