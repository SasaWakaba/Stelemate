#include "../common/main.h"
#include <fstream>
#include <sstream>
#include <map>
#include "../Charcter/CCharcterBase.h"
#include "CStageData.h"

std::map<int, StageInfo*> CStageData::m_StageData;

void CStageData::Load(int stageNum, const char* filename)
{
	std::ifstream file(filename);

	if (!file)
	{
		std::cout << "Error! File can not be opened" << std::endl;
		return;
	}
	std::string str = "";
	//std::getline(file, str); //ˆês–Ú‚Í–³Ž‹
	int i = 0;
	int z = 0;
	while (std::getline(file, str))
	{
		std::stringstream data(str);
		std::string tmp = "";
		int x = 0;
		while (getline(data, tmp, ','))
		{
			std::stringstream n(tmp);
			n >> m_StageData[stageNum]->stage[i].PanelPattarn;
			m_StageData[stageNum]->stage[i].bChar = false;
			m_StageData[stageNum]->stage[i].Charcter = nullptr;
			i++;
			x++;
		}
		m_StageData[stageNum]->StageXnum = x;
		z++;
	}
	m_StageData[stageNum]->StageZnum = z;
}

void CStageData::Initialize()
{
	Load(1, "../Data/StageData1.csv");
}

void CStageData::Finalize()
{
	m_StageData.clear();
}