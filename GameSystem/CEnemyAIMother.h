#ifndef CENEMY_AI_MOTHER_H_
#define CENEMY_AI_MOTHER_H_

#include "../common/AI_Base/CBlackBoard.h"
#include "../common/AI_Base/CTask.h"
#include "../common/AI_Base/CDecorator.h"
#include "../common/AI_Base/CComposite.h"
#include "../common/AI_Base/CAI_Base.h"

#include "../common/main.h"
#include "../Stage/CStage.h"
#include <vector>







class CMoveSearch;
class CAttackSearch;

class CMotherBlackBoard :public CBlackBoard
{
public:
	//ÉfÅ[É^=======================================
	int m_X;
	int m_Z;

	PanelState* m_StageMap;

	CMoveSearch*	m_MoveSearch;
	CAttackSearch*	m_AtkSearch;

	std::vector<Vector2_3D> m_SearchArea;

	//============================================


	void Initialize(int numX, int numZ, PanelState* Map);
	void Update();
};

class CMotherAI :public CAiBase
{
public:
	CMotherAI(int numX, int numZ, PanelState* Map);
	~CMotherAI() {}

	static void Play();
};

class CEnemyAIMother
{
private:
	static CMotherBlackBoard*	m_BlackBoard;
public:
	static void initialize(int numX, int numZ, PanelState* Map);

	static std::vector<Vector2_3D> SerchPlayer(Vector2_3D pos, int Move);
};


#endif // CENEMY_AI_MOTHER_H_
