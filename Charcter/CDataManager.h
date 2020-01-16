#ifndef CDATA_MANAGER_H_
#define CDATA_MANAGER_H_

#include "CCharacterData.h"
#include "CWeaponData.h"
#include "../common/CDrawText.h"
#include "../Stage/CStageData.h"

class CDataManager
{
public:
	static void Load()
	{
		CCharacterData::Initialize();
		CWeaponData::Initialize();
		CDrawText::Initialize();
		CStageData::Initialize();
	}
	static void Unload()
	{
		CCharacterData::Finalize();
		CWeaponData::Finalize();
		CDrawText::Finalize();
		CStageData::Finalize();
	}
};

#endif // CDATA_MANAGER_H_
