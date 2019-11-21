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



void WorldManager::SetGameMode(GameMode mode) { Gamemode = mode; }
void WorldManager::AddTurn() { ClearTurn++; }

void WorldManager::StageStart(int stageNum)
{
	NowStage = stageNum;
	ClearTurn = 0;
}