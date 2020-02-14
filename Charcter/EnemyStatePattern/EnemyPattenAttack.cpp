
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
#include "EnemyPatternAttack.h"

void CEnemyPatternAttack::Update(CEnemyAI* pEnemy, Vector2_3D* cursol)
{
	StageInfo* stage = pEnemy->GetStageInfo();
	std::vector<Vector2_3D> PL;
	if (!pEnemy->GetBattle())
	{
		if (!pEnemy->GetBattle())
		{
			for (Vector2_3D pos : pEnemy->GetAttackSearch(*cursol, pEnemy->GetMoveEnemy()->GetWeapon()->WeaponType))
			{
				if (stage->stage[pos.z * stage->StageXnum + pos.x].bChar)
				{
					if (stage->stage[pos.z * stage->StageXnum + pos.x].Charcter->GetAlly())
					{
						PL.push_back(pos);
					}
				}
			}
		}
		if (PL.size() > 1)
		{
			Vector2_3D selectPL = HPLower(PL, stage);
			CSystemBattle::Battle(&stage->stage[cursol->z * stage->StageXnum + cursol->x], &stage->stage[selectPL.z * stage->StageXnum + selectPL.x]);
			pEnemy->SetBattle(true);
		}
		else
		{
			CSystemBattle::Battle(&stage->stage[cursol->z * stage->StageXnum + cursol->x], &stage->stage[PL[0].z * stage->StageXnum + PL[0].x]);
			pEnemy->SetBattle(true);
		}
	}

	if (pEnemy->GetBattle())
	{
		if (!CSystemBattle::BattleEnd())
		{
			pEnemy->SetMove(end);
			pEnemy->SetBattle(false);
			if (pEnemy->GetMoveEnemy()->nowHP <= 0)
			{
				stage->stage[pEnemy->GetMoveEnemyPos().z * stage->StageXnum + pEnemy->GetMoveEnemyPos().x].bChar = false;
				stage->stage[pEnemy->GetMoveEnemyPos().z * stage->StageXnum + pEnemy->GetMoveEnemyPos().x].Charcter = nullptr;
			}
		}
	}
	else
	{
		pEnemy->SetMove(end);
	}
}

Vector2_3D CEnemyPatternAttack::HPLower(std::vector<Vector2_3D> max, StageInfo* stage)
{
	Vector2_3D Lower;
	int HP = -1;
	for (Vector2_3D pos : max)
	{
		if(HP != -1)
		{
			if (HP > stage->stage[pos.z * stage->StageXnum + pos.x].Charcter->nowHP)
			{
				Lower = pos;
				HP = stage->stage[pos.z * stage->StageXnum + pos.x].Charcter->nowHP;
			}
		}
		else
		{
			Lower = pos;
			HP = stage->stage[pos.z * stage->StageXnum + pos.x].Charcter->nowHP;
		}
	}

	return Lower;
}