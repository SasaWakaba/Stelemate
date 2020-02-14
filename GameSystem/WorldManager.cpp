#include "../common/main.h"
#include "../common/math.h"
#include "../Charcter/CCharcterBase.h"
#include "../Stage/CStage.h"
#include "../GameSystem/CMoveSearch.h"
#include "../Charcter/CPlayerManager.h"
#include "../Stage/CStageData.h"
#include <list>

#include "WorldManager.h"

GameMode WorldManager::Gamemode;
int WorldManager::NowStage;
int WorldManager::ClearTurn;
int WorldManager::ClearTurnAll;
int WorldManager::SoldierPoint;
int WorldManager::turn;

std::vector<StageInfo*> WorldManager::StageStateAll;
EnemyMove WorldManager::enemyAction;
CMoveSearch* WorldManager::moveArea;
CPlayerManager* WorldManager::PlayerParty;
ResultScore WorldManager::Result;

void WorldManager::SetGameMode(GameMode mode) { Gamemode = mode; }
void WorldManager::AddTurn() { ClearTurn++; }
void WorldManager::AddSoldierPoint(int add){ SoldierPoint += add; }
void WorldManager::UseSoldierPoint(int use) { SoldierPoint -= use; }
int WorldManager::GetSoldierPoint() { return SoldierPoint; }
STATUS* WorldManager::PlayerAdd(const char* characterName, PlayerData* menber) { return PlayerParty->CharacterAdd(characterName, menber); }
std::map<std::string, PlayerData*> WorldManager::GetParty() { return PlayerParty->GetMenberData(); }

void WorldManager::AddSubjugation() { Result.SubjugationCount++; }
void WorldManager::AddDeadCount() { Result.DeadCount++; }
ResultScore* WorldManager::GetResult() { return &Result; }

void WorldManager::Initialize()
{
	PlayerParty = new CPlayerManager();
	SoldierPoint = 3;
	SetNowStageNum(0);
}
void WorldManager::Finalize()
{
	delete PlayerParty;
}

void WorldManager::StageStart()
{
	ClearTurn = 0;
	Result.DeadCount = 0;
	Result.SubjugationCount = 0;
}

void WorldManager::SetStageState(StageInfo* stage)
{
	StageStateAll.push_back(stage);
}
