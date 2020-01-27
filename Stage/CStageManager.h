#ifndef CSTAGEMANAGER_H_
#define CSTAGEMANAGER_H_

//#include <list>
//#include "../common/main.h"
//#include "../common/Game_Object.h"
//#include "../GameSystem/CSystemMain.h"
//
#include "CStage.h"

class CStage;
class CSystemMain;

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
	void Finalize();
	void Update();
	void Draw();

	void SetStageNum(int n){ StageNum = n; }

	//static int GetStageNum(int n) { return StageNum; }
	
	CStage* AddStage(PanelState* stagestate, int x, int z);

	CSystemMain* AddMainSystem(PanelState* stagestate, int x, int z);
};

#endif // !CSTAGEMANAGER_H_
