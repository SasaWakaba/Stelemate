#include "../common/main.h"
#include <fstream>
#include <sstream>
#include <map>
#include "CWeaponData.h"


std::map<std::string, WeaponStatus> CWeaponData::m_WeaponData;

void CWeaponData::Initialize()
{
	std::ifstream file("Data/WeaponData.csv");

	if (!file)
	{
		std::cout << "Error! File can not be opened" << std::endl;
		return;
	}
	std::string str = "";
	std::getline(file, str); //ˆês–Ú‚Í–³Ž‹

	while (std::getline(file, str))
	{
		std::stringstream data(str);
		std::string name = "";
		std::string tmp = "";
		int num[MAX_WEAPON_STATUS];

		getline(data, name, ',');

		for (int i = 0; getline(data, tmp, ','); i++)
		{
			std::stringstream n(tmp);
			n >> num[i];
		}

		m_WeaponData[name].name = name;
		m_WeaponData[name].Attack = num[0];
		m_WeaponData[name].Hit = num[1];
		m_WeaponData[name].Cri = num[2];
		m_WeaponData[name].Weight = num[3];
		m_WeaponData[name].WeaponType = (Weapontype)num[4];
	}
}

void CWeaponData::Finalize()
{
	m_WeaponData.clear();
}