#include "../common/main.h"
#include "../common/texture.h"
#include <list>

#include "CStage.h"
#include "CStageManager.h"

#include "../Charcter/CCharcterBase.h"
#include "../Charcter/CJob.h"
#include "../GameSystem/WorldManager.h"
#include "CStageData.h"

PanelState stage0[] = {
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},
};


PanelState stage1[] = {
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},{2, nullptr, false},{2, nullptr, false},{2, nullptr, false},{2, nullptr, false},
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},{2, nullptr, false},{2, nullptr, false},
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},{2, nullptr, false},
	{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},{2, nullptr, false},{2, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},
	{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{1, nullptr, false},{2, nullptr, false},
};

void CStageManager::Initialize()
{
	PanelState* stage0 = CStageData::m_StageData["stage1"]->stage;


	CCharcterBase* man;
	CCharcterBase* cat;
	CCharcterBase* cat2;
	man = new CSwordsman();
	man->SetAlly(true);
	cat = new CSwordsman();
	cat->SetAlly(false);
	cat2 = new CSwordsman();
	cat2->SetAlly(false);
	stage0[0].bChar = true;
	stage0[0].Charcter = man;

	stage0[63].bChar = true;
	stage0[63].Charcter = cat;
	stage0[57].bChar = true;
	stage0[57].Charcter = cat2;

	AddStage(stage0, 8, 8);
	AddMainSystem(stage0, 8, 8);

	WorldManager::SetStageState(stage0, 8, 8, 0);
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