#include "../common/main.h"
#include "../GameSystem/WorldManager.h"
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include "../Charcter/CCharcterBase.h"
#include "CStageData.h"

std::map<std::string, StageInfo*> CStageData::m_StageData;
std::map<std::string, StageEnemy> CStageData::m_StageEnemy;

void CStageData::Load(const char* filename)
{
	std::ifstream file(filename);

	if (!file)
	{
		std::cout << "Error! File can not be opened" << std::endl;
		return;
	}
	std::string str = "";
	std::string name = "";

	std::getline(file, str);

	{
		std::stringstream data(str);
		getline(data, name, ',');
		m_StageData[name] = new StageInfo();
		std::string num = "";
		std::vector<unsigned short> enenum;
		while (getline(data, num, ','))
		{
			unsigned short numE;
			std::stringstream n(num);
			n >> numE;

			enenum.push_back(numE);
		}
		m_StageData[name]->StageXnum = enenum[0];
		m_StageData[name]->StageZnum = enenum[1];
		StageEnemy ene;
		ene.SwordmanNum = enenum[2];
		ene.ArcherNum = enenum[3];
		ene.SorcererNum = enenum[4];
		ene.HealerNum = enenum[5];
		ene.LancerNum = enenum[6];
		ene.EnemyNum = ene.SwordmanNum + ene.ArcherNum + ene.SorcererNum + ene.HealerNum + ene.LancerNum;

		m_StageEnemy[name] = ene;
	}




	std::list<unsigned short> map;
	while (std::getline(file, str))
	{
		std::stringstream data(str);
		std::string tmp = "";
		while (getline(data, tmp, ','))
		{
			unsigned short num;
			std::stringstream n(tmp);
			n >> num;
			map.push_back(num);
		}
	}
	std::list<unsigned short>::iterator mapPos = map.begin();
	m_StageData[name]->stage = new PanelState[map.size()];
	for (int i = 0; i < map.size(); i++)
	{
		m_StageData[name]->stage[i].PanelPattarn = *mapPos;
		m_StageData[name]->stage[i].bChar = false;
		m_StageData[name]->stage[i].Charcter = nullptr;
		++mapPos;
	}
}

void CStageData::Initialize()
{
	Load("Data/StageData1.csv");
}

void CStageData::Finalize()
{
	m_StageData.clear();
}