#ifndef CSTAGEMANAGER_H_
#define CSTAGEMANAGER_H_

#include <list>
#include "../common/main.h"
#include "../common/Game_Object.h"
#include "../GameSystem/CSystemMain.h"

#include "CStage.h"

class CStageManager:public CGameObject
{
private:
	std::list<CStage*> m_Stage;

	std::list<CSystemMain*> m_MainSys;
	unsigned short StageNum;
public:
	CStageManager(){}
	~CStageManager() {}

	void Initialize();
	void Finalize()
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
	void Update();
	void Draw();

	void SetStageNum(int n){ StageNum = n; }

	//static int GetStageNum(int n) { return StageNum; }
	
	CStage* AddStage(PanelState* stagestate, int x, int z)
	{
		CStage* stage = new CStage(x, z, stagestate);
		stage->Initialize();
		m_Stage.push_back(stage);
		return stage;
	}

	CSystemMain* AddMainSystem(PanelState* stagestate, int x, int z)
	{
		CSystemMain* system = new CSystemMain();
		system->Initialize(x, z, stagestate);
		m_MainSys.push_back(system);
		return system;
	}
};

#endif // !CSTAGEMANAGER_H_
