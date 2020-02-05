#include "../common/main.h"
#include "../common/math.h"
#include "../Charcter/CCharcterBase.h"
#include "../Stage/CStage.h"
#include "../GameSystem/CMoveSearch.h"
#include "../Charcter/CPlayerManager.h"
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
CPlayerManager* WorldManager::PlayerParty;

void WorldManager::SetGameMode(GameMode mode) { Gamemode = mode; }
void WorldManager::AddTurn() { ClearTurn++; }
void WorldManager::AddSoldierPoint(int add){ SoldierPoint += add; }
void WorldManager::UseSoldierPoint(int use) { SoldierPoint -= use; }
int WorldManager::GetSoldierPoint() { return SoldierPoint; }
STATUS* WorldManager::PlayerAdd(const char* characterName, PlayerData* menber) { return PlayerParty->CharacterAdd(characterName, menber); }
std::map<std::string, PlayerData*> WorldManager::GetParty() { return PlayerParty->GetMenberData(); }

void WorldManager::Initialize()
{
	PlayerParty = new CPlayerManager();
	SoldierPoint = 3;
}
void WorldManager::Finalize()
{
	delete PlayerParty;
}

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
