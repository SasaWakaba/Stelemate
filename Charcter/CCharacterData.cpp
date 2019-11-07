#include "../common/main.h"
#include <fstream>
#include <sstream>
#include <map>
#include "CCharcterBase.h"

#include "CCharacterData.h"

std::map<std::string, STATUS> CCharacterData::m_CharData;

void CCharacterData::Initialize()
{
	std::ifstream file("Data/CharacterData.csv");

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
		STATUS status;
		int num[MAX_STATUS];

		getline(data, name, ',');
		
		for (int i = 0; getline(data, tmp, ','); i++)
		{
			std::stringstream n(tmp);
			n >> num[i];
		}

		m_CharData[name].HP = num[0];
		m_CharData[name].Attack = num[1];
		m_CharData[name].Speed = num[2];
		m_CharData[name].Defense = num[3];
		m_CharData[name].MagicDefense = num[4];
		m_CharData[name].MovePoint = num[5];
		m_CharData[name].type = (Weapontype)num[6];	
	}
}

void CCharacterData::Finalize()
{
	m_CharData.clear();
}