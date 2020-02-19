#include "../common/main.h"
#include "../common/Game_Object.h"
#include "../common/texture.h"
#include "../GameSystem/CSystemMain.h"
#include <list>

#include "CStage.h"

#include "../Charcter/CCharcterBase.h"
#include "../Charcter/CJob.h"
#include "../Charcter/CPlayerManager.h"
#include "../GameSystem/WorldManager.h"
#include "CStageData.h"

#include "CStageManager.h"



void CStageManager::Initialize()
{

	if (WorldManager::GetStageInfo().size() != 0)
	{
		for (auto stage : WorldManager::GetStageInfo())
		{
			AddStage(stage->stage, stage->StageXnum, stage->StageZnum);
			AddMainSystem(stage->stage, stage->StageXnum, stage->StageZnum);
		}
	}
	SetStageNum(WorldManager::GetNowStageNum());

	//WorldManager::SetStageState(CStageData::m_StageData["stage1"]);
}

void CStageManager::Finalize()
{
	for (CStage* stage : m_Stage)
	{
		stage->Finalize();
		delete stage;
	}
	m_Stage.clear();

	for (CSystemMain* sys : m_MainSys)
	{
		sys->Finalize();
		delete sys;
	}
	m_MainSys.clear();
}

void CStageManager::Update()
{
	int cnt = 0;
	for (CStage* stage : m_Stage)
	{
		if (cnt == StageNum)
		{
			stage->Update();
		}
		cnt++;
	}
	cnt = 0;
	for (CSystemMain* sys : m_MainSys)
	{
		if (cnt == StageNum)
		{
			sys->Update();
		}
		cnt++;
	}
}

void CStageManager::Draw()
{
	int cnt = 0;
	for (CStage* stage : m_Stage)
	{
		if (cnt == StageNum)
		{
			stage->Draw();
		}
		cnt++;
	}

	cnt = 0;
	for (CSystemMain* sys : m_MainSys)
	{
		if (cnt == StageNum)
		{
			sys->Draw();
		}
		cnt++;
	}
}

CStage* CStageManager::AddStage(PanelState* stagestate, int x, int z)
{
	CStage* stage = new CStage(x, z, stagestate);
	stage->Initialize();
	m_Stage.push_back(stage);
	return stage;
}

CSystemMain* CStageManager::AddMainSystem(PanelState* stagestate, int x, int z)
{
	CSystemMain* system = new CSystemMain();
	system->Initialize(x, z, stagestate);
	m_MainSys.push_back(system);
	return system;
}