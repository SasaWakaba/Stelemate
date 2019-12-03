#include "../common/main.h"
#include "../common/math.h"
#include "../Charcter/CCharcterBase.h"
#include "../Stage/CStage.h"
#include "../GameSystem/CMoveSearch.h"
#include <list>

#include "WorldManager.h"

GameMode WorldManager::Gamemode;
int WorldManager::NowStage;
int WorldManager::ClearTurn;
int WorldManager::ClearTurnAll;
int WorldManager::SoldierPoint;
int WorldManager::turn;

StageState WorldManager::StageStateAll[5];
EnemyMove WorldManager::enemyAction;
CMoveSearch* WorldManager::moveArea;

void WorldManager::SetGameMode(GameMode mode) { Gamemode = mode; }
void WorldManager::AddTurn() { ClearTurn++; }
void WorldManager::AddSoldierPoint(int add){ SoldierPoint += add; }
void WorldManager::UseSoldierPoint(int use) { SoldierPoint -= use; }

void WorldManager::StageStart(int stageNum)
{
	NowStage = stageNum;
	ClearTurn = 0;
}

void WorldManager::SetStageState(PanelState* stage, int x, int z, int stageNum)
{
	StageStateAll[stageNum].Stage = stage;
	StageStateAll[stageNum].numX = x;
	StageStateAll[stageNum].numZ = z;
}
