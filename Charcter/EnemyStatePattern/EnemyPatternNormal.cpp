
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
#include "EnemyPatternNormal.h"




void CEnemyPatternNormal::Update(CEnemyAI* pEnemy, Vector2_3D* cursol)
{
	StageInfo* stage = pEnemy->GetStageInfo();

	switch (pEnemy->GetMove())
	{
	case wait:
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
							MoveEnemy = stage->stage[z * stage->StageXnum + x].Charcter;
							SelectEnemyPos = { x, z };
							pEnemy->SetMove(move);
							*cursol = SelectEnemyPos;
							break;
						}
					}
				}
			}
		}
		break;
	case move:
		if (MoveEnemy != nullptr)
		{
			*cursol = Move(pEnemy, SelectEnemyPos, MoveEnemy).back();
			stage->stage[cursol->z * stage->StageXnum + cursol->x].bChar = true;
			stage->stage[cursol->z * stage->StageXnum + cursol->x].Charcter = MoveEnemy;
			MoveEnemy->MoveLocation(XMFLOAT3((cursol->x * SPACE_SIZE) - (SPACE_SIZE * stage->StageXnum / 2), 0.0f, (cursol->z * SPACE_SIZE) - (SPACE_SIZE * stage->StageZnum / 2)));

			if (*cursol != SelectEnemyPos)
			{
				stage->stage[SelectEnemyPos.z * stage->StageXnum + SelectEnemyPos.x].bChar = false;
				stage->stage[SelectEnemyPos.z * stage->StageXnum + SelectEnemyPos.x].Charcter = nullptr;
			}

			SelectEnemyPos = *cursol;
		}
		pEnemy->SetMove(Select(pEnemy, *cursol, MoveEnemy->GetWeapon()->WeaponType));

		break;
	case attack:
		if (!pEnemy->GetBattle())
		{
			for (Vector2_3D pos : pEnemy->GetAttackSearch(*cursol, MoveEnemy->GetWeapon()->WeaponType))
			{
				if (stage->stage[pos.z * stage->StageXnum + pos.x].bChar)
				{
					if (stage->stage[pos.z * stage->StageXnum + pos.x].Charcter->GetAlly())
					{
						CSystemBattle::Battle(&stage->stage[cursol->z * stage->StageXnum + cursol->x], &stage->stage[pos.z * stage->StageXnum + pos.x]);
						pEnemy->SetBattle(true);
						break;
					}
				}
			}
		}

		if (pEnemy->GetBattle())
		{
			if (!CSystemBattle::BattleEnd())
			{
				pEnemy->SetMove(end);
				pEnemy->SetBattle(false);
				if (MoveEnemy->nowHP <= 0)
				{
					stage->stage[SelectEnemyPos.z * stage->StageXnum + SelectEnemyPos.x].bChar = false;
					stage->stage[SelectEnemyPos.z * stage->StageXnum + SelectEnemyPos.x].Charcter = nullptr;
				}
			}
		}
		else
		{
			pEnemy->SetMove(end);
		}

		break;
	case heal:
		for (Vector2_3D pos : pEnemy->GetAttackSearch(*cursol, MoveEnemy->GetWeapon()->WeaponType))
		{
			if (stage->stage[pos.z * stage->StageXnum + pos.x].bChar)
			{
				if (!stage->stage[pos.z * stage->StageXnum + pos.x].Charcter->GetAlly())
				{
					//CSystemBattle::Battle(SelectEnemy, m_StageMap[pos.z * m_X + pos.x].Charcter);
					break;
				}
			}
		}
		break;
	case end:
		MoveEnemy->SetTurnMove(true);
		MoveEnemy = nullptr;
		pEnemy->SetMove(wait);
		break;
	default:
		break;
	}
}

std::vector<Vector2_3D> CEnemyPatternNormal::Move(CEnemyAI* pEnemy, Vector2_3D pos, CCharcterBase* Move)
{
	pEnemy->Reset();
	pEnemy->ResetMove();
	std::vector<Vector2_3D> Area;
	Area = pEnemy->GetMoveSearch(pos, Move);
	StageInfo* stage = pEnemy->GetStageInfo();

	std::vector<Vector2_3D> PL;
	for (int z = 0; z < stage->StageZnum; z++)
	{
		for (int x = 0; x < stage->StageXnum; x++)
		{
			if (stage->stage[z * stage->StageZnum + x].bChar)
			{
				if (stage->stage[z * stage->StageZnum + x].Charcter->GetAlly())
				{
					Vector2_3D add = { x,z };
					PL.push_back(add);
				}
			}
		}
	}

	Vector2_3D Near = pEnemy->NearLocation(PL, pos);
	int length_near = abs((pos.x - Near.x)) + abs((pos.z - Near.z));

	PL.clear();



	if (length_near != 1)
	{
		Vector2_3D Moving = pos;
		for (int i = Move->GetStatus()->MovePoint; i > 0;)
		{
			for (Vector2_3D movePos : Area)
			{
				if (Moving.z == movePos.z)
				{
					if (Moving.x + 1 == movePos.x)
					{
						PL.push_back(movePos);
					}
					if (Moving.x - 1 == movePos.x)
					{
						PL.push_back(movePos);
					}
				}
				else if (Moving.x == movePos.x)
				{
					if (Moving.z + 1 == movePos.z)
					{
						PL.push_back(movePos);
					}
					if (Moving.z - 1 == movePos.z)
					{
						PL.push_back(movePos);
					}
				}
			}
			Moving = pEnemy->NearLocation(PL, Near);
			pEnemy->Add(Moving);
			if (Moving.x == Near.x)
			{
				if (Moving.z == Near.z + 1)
				{
					i = 0;
				}
				else if (Moving.z == Near.z - 1)
				{
					i = 0;
				}
				else
				{
					i--;
				}
			}
			else if (Moving.z == Near.z)
			{
				if (Moving.x == Near.x + 1)
				{
					i = 0;
				}
				else if (Moving.x == Near.x - 1)
				{
					i = 0;
				}
				else
				{
					i--;
				}
			}
			else
			{
				i--;
			}
		}
	}
	else
	{
		pEnemy->Add(pos);
	}



	return pEnemy->GetSerchArea();
}


EnemyMove CEnemyPatternNormal::Select(CEnemyAI* pEnemy, Vector2_3D pos, Weapontype Atk)
{
	StageInfo* stage = pEnemy->GetStageInfo();
	switch (Atk)
	{
	case Sword:
	case Lance:
	case Bow:
	case Magic:
		for (Vector2_3D pl : pEnemy->GetAttackSearch(pos, Atk))
		{
			PanelState panel = stage->stage[pl.z * stage->StageZnum + pl.x];
			if (panel.bChar)
			{
				if (panel.Charcter->GetAlly())
				{
					return attack;
					break;
				}
			}
		}
		break;
	case Wand:
		for (Vector2_3D pl : pEnemy->GetAttackSearch(pos, Atk))
		{
			PanelState panel = stage->stage[pl.z * stage->StageZnum + pl.x];
			if (panel.bChar)
			{
				if (!panel.Charcter->GetAlly())
				{
					if (panel.Charcter->nowHP < panel.Charcter->GetStatus()->HP)
						return heal;
					break;
				}
			}
		}
		break;
	default:
		break;
	}

	return end;
}