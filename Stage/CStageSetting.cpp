#include "CStagePanel.h"
#include "CStageData.h"
#include "../GameSystem/WorldManager.h"
#include "CStageSetting.h"

void CStageSetting::Initialize()
{
	pStage = nullptr;
	StageXnum = 0;
	StageZnum = 0;
}

void CStageSetting::Finalize()
{

}

StageInfo* CStageSetting::GetStageData(int stageNum)
{
	std::string stage = "stage" + std::to_string(stageNum);
	return CStageData::m_StageData[stage];
}

void CStageSetting::SetStageData(CStagePanel* stage)
{

}