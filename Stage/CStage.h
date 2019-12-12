#ifndef CSTAGE_H_
#define CSTAGE_H_


#include "../common/main.h"
#include <list>
#include "../Charcter/CCharcterBase.h"



class CStagePanel;
class CMeshField;
class CModelAnimation;


typedef struct
{
	unsigned short PanelPattarn;
	CCharcterBase* Charcter;
	bool bChar;
}PanelState;


class CStage
{
private:
	PanelState* m_StageMap;
	CStagePanel* m_StagePanel[2];
	CMeshField* m_Meshfield;
	int m_Xnum;
	int m_Znum;
	CModelAnimation* m_Model[2];
public:
	CStage(int nX, int nZ, PanelState* stage) :m_StageMap(stage) {
		m_Xnum = nX;
		m_Znum = nZ;
	}
	~CStage() {}

	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !CSTAGEMANAGER_H_
