
#include "../../common/main.h"
#include "../../common/Scene.h"
#include "../../common/manager.h"
#include "../../GameSystem/CEnemyAI.h"
#include "../../GameSystem/WorldManager.h"



#include "../../common/main.h"
#include "../../Stage/CStage.h"
#include <vector>


#include "../../Charcter/CCharcterBase.h"
#include "../../GameSystem/CSystemBattle.h"
#include "../../GameSystem/CAttackSearch.h"
#include "../../GameSystem/CMoveSearch.h"

#include "EnemyPttern.h"
#include "EnemyPatternWait.h"

void CEnemyPatternWait::Update(CEnemyAI* pEnemy, Vector2_3D* cursol)
{
	StageInfo* stage = pEnemy->GetStageInfo();
	std::vector<Vector2_3D> AllEnePos;
	std::vector<Vector2_3D> AllPL;
	for (int z = 0; z < stage->StageZnum; z++)
	{
		for (int x = 0; x < stage->StageXnum; x++)
		{
			if (stage->stage[z * stage->StageXnum + x].bChar)
			{
				if (!stage->stage[z * stage->StageXnum + x].Charcter->GetAlly())
				{
					if (!stage->stage[z * stage->StageXnum + x].Charcter->GetTurnMove())
					{
						Vector2_3D pos = { x, z };
						AllEnePos.push_back(pos);
					}
				}
			}
		}
	}

	for (auto Pl : WorldManager::GetParty())
	{
		Vector2_3D pos = { Pl.second->PosX, Pl.second->PosZ };
		AllPL.push_back(pos);
	}
	Vector2_3D NearEne;
	float Near = -1.0f;
	for (int i = 0; i < AllEnePos.size(); i++)
	{
		if (Near != -1.0f)
		{
			if (Near > NearLength(AllPL, AllEnePos[i]))
			{
				NearEne = AllEnePos[i];
				Near = NearLength(AllPL, AllEnePos[i]);
			}
		}
		else
		{
			NearEne = AllEnePos[i];
			Near = NearLength(AllPL, AllEnePos[i]);
		}
	}

	pEnemy->SetMoveEnemy(stage->stage[NearEne.z * stage->StageXnum + NearEne.x].Charcter);
	pEnemy->SetMoveEnemyPos(NearEne);
	pEnemy->SetMove(move);
	*cursol = NearEne;
}

float CEnemyPatternWait::NearLength(std::vector<Vector2_3D> max, Vector2_3D pos)
{
	Vector2_3D Near;
	float length_near = -1.0f;
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

	return length_near;
}