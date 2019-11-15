#include "../common/AI_Base/CBlackBoard.h"
#include "../common/AI_Base/CTask.h"
#include "../common/AI_Base/CDecorator.h"
#include "../common/AI_Base/CComposite.h"
#include "../common/AI_Base/CAI_Base.h"

#include "CAttackSearch.h"
#include "CMoveSearch.h"


#include "CEnemyAIMother.h"

CMotherBlackBoard* CEnemyAIMother::m_BlackBoard;

void CEnemyAIMother::initialize(int numX, int numZ, PanelState* Map)
{
	m_BlackBoard = new CMotherBlackBoard();
	m_BlackBoard->Initialize(numX, numZ, Map);
}

std::vector<Vector2_3D> CEnemyAIMother::SerchPlayer(Vector2_3D pos, int Move)
{
	std::vector<Vector2_3D> Area;
	Area = m_BlackBoard->m_MoveSearch->Search(pos, Move);

	std::vector<Vector2_3D> PL;
	for (int z = 0; z < m_BlackBoard->m_Z; z++)
	{
		for (int x = 0; x < m_BlackBoard->m_X; x++)
		{
			if (m_BlackBoard->m_StageMap[z * m_BlackBoard->m_Z + x].bChar)
			{
				if (m_BlackBoard->m_StageMap[z * m_BlackBoard->m_Z + x].Charcter->GetAlly())
				{
					Vector2_3D add = { x,z };
					PL.push_back(add);
				}
			}
		}
	}

	return PL;
}

void CMotherBlackBoard::Initialize(int numX, int numZ, PanelState* Map)
{
	m_X = numX;
	m_Z = numZ;

	m_StageMap = Map;

	m_AtkSearch = new CAttackSearch();
	m_AtkSearch->Initialize(m_X, m_Z, Map);

	m_MoveSearch = new CMoveSearch();
	m_MoveSearch->Initialize(m_X, m_Z, Map);
}

void CMotherBlackBoard::Update()
{

}