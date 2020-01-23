#include "../common/main.h"
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include "../Charcter/CCharcterBase.h"
#include "CStageData.h"

std::map<std::string, StageInfo*> CStageData::m_StageData;

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
	getline(std::stringstream(str), name, ',');

	m_StageData[name] = new StageInfo();

	std::list<unsigned short> map;
	int z = 0;
	while (std::getline(file, str))
	{
		std::stringstream data(str);
		std::string tmp = "";
		int x = 0;
		while (getline(data, tmp, ','))
		{
			unsigned short num;
			std::stringstream n(tmp);
			n >> num;
			map.push_back(num);
			x++;
		}
		m_StageData[name]->StageXnum = x;
		z++;
	}
	m_StageData[name]->StageZnum = z;
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