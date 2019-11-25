#include "../common/main.h"
#include "../common/math.h"
#include "../Charcter/CCharcterBase.h"
#include "../Stage/CStage.h"
#include <list>

#include "WorldManager.h"

GameMode WorldManager::Gamemode;
int WorldManager::NowStage;
int WorldManager::ClearTurn;
int WorldManager::ClearTurnAll;
int WorldManager::SoldierPoint;


void WorldManager::SetGameMode(GameMode mode) { Gamemode = mode; }
void WorldManager::AddTurn() { ClearTurn++; }
void WorldManager::AddSoldierPoint(int add){ SoldierPoint += add; }
void WorldManager::UseSoldierPoint(int use) { SoldierPoint -= use; }

void WorldManager::StageStart(int stageNum)
{
	NowStage = stageNum;
	ClearTurn = 0;
}
