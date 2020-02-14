#include "../common/main.h"
#include "../Stage/CStage.h"
#include <vector>


#include "../common/texture.h"
#include "C3DPolygon.h"

#include "../Charcter/CCharcterBase.h"

#include "CAttackSearch.h"
#include "CMoveSearch.h"
#include "WorldManager.h"

#include "../Charcter/EnemyStatePattern/EnemyPttern.h"
#include "../Charcter/EnemyStatePattern/EnemyPatternNormal.h"

#include "../common/math.h"
#include "CEnemyAI.h"


StageInfo* CEnemyAI::GetStageInfo() { return m_StageMap; }
EnemyMove CEnemyAI::GetMove() { return m_EnemyMoving; }
bool CEnemyAI::GetBattle() { return bBattle; }
void CEnemyAI::SetBattle(bool bEneble) { bBattle = bEneble; }
std::vector<Vector2_3D> CEnemyAI::GetSerchArea() { return m_SearchArea; }
void CEnemyAI::ResetMove() { m_MoveSearch->Reset(); }
void CEnemyAI::ResetAttack() { m_AtkSearch->Reset(); }
void CEnemyAI::SetMove(EnemyMove move) { m_EnemyMoving = move; }
std::vector<Vector2_3D> CEnemyAI::GetMoveSearch(Vector2_3D pos, int move) { return m_MoveSearch->Search(pos, move); }
std::vector<Vector2_3D> CEnemyAI::GetAttackSearch(Vector2_3D pos, Weapontype Atk) { return m_AtkSearch->Search(pos, Atk); }
CCharcterBase* CEnemyAI::GetMoveEnemy() { return MoveEnemy; }
Vector2_3D	   CEnemyAI::GetMoveEnemyPos() { return SelectEnemyPos; }

void CEnemyAI::SetMoveEnemy(CCharcterBase* ene) { MoveEnemy = ene; }
void CEnemyAI::SetMoveEnemyPos(Vector2_3D pos) { SelectEnemyPos = pos; }


void CEnemyAI::ChangeEnemyPattern(CEnemyPattern* pattern)
{
	delete m_pEnemyPattern;
	m_pEnemyPattern = pattern;
}

bool CEnemyAI::Add(Vector2_3D pos)
{
	if (m_SearchArea.size() != 0)
	{
		bool re = false;
		for (unsigned int i = 0; i < m_SearchArea.size(); i++)
		{
			if (m_SearchArea[i].x == pos.x && m_SearchArea[i].z == pos.z)
			{
				re = true;
				break;
			}
		}


		if (!re)
		{
			m_SearchArea.push_back(pos);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		m_SearchArea.push_back(pos);
		return true;
	}
}


Vector2_3D CEnemyAI::NearLocation(std::vector<Vector2_3D> max, Vector2_3D pos)
{
	Vector2_3D Near;
	int length_near = -1;
	for (Vector2_3D plPos : max)
	{
		if (length_near != -1)
		{
			int length = abs((pos.x - plPos.x)) + abs((pos.z - plPos.z));
			if (length_near > length)
			{
				Near = plPos;
				length_near = length;
			}
		}
		else
		{
			Near = plPos;
			length_near = abs((pos.x - plPos.x)) + abs((pos.z - plPos.z));
		}
	}

	return Near;
}


void CEnemyAI::Initialize(int numX, int numZ, PanelState* Map)
{
	m_pEnemyPattern = new CEnemyPatternNormal();
	m_StageMap = new StageInfo();
	m_StageMap->stage = Map;
	m_StageMap->StageXnum = numX;
	m_StageMap->StageZnum = numZ;

	m_AtkSearch = new CAttackSearch();
	m_AtkSearch->Initialize(numX, numZ, Map);

	m_MoveSearch = new CMoveSearch();
	m_MoveSearch->Initialize(numX, numZ, Map);

	bBattle = false;
}

void CEnemyAI::Finalize()
{
	delete m_pEnemyPattern;
	m_StageMap->stage = nullptr;
	delete m_StageMap;
	m_AtkSearch->Finalize();
	delete m_AtkSearch;

	m_MoveSearch->Finalize();
	delete m_MoveSearch;
}

void CEnemyAI::Update(Vector2_3D* cursol)
{
	m_pEnemyPattern->Update(this, cursol);
	WorldManager::SetEnemyAction(m_EnemyMoving);
}