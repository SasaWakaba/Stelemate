#ifndef WORLD_MANAGER_H_
#define WORLD_MANAGER_H_

#include "../common/main.h"
#include "../common/math.h"
#include "../Charcter/CCharcterBase.h"
#include "../Stage/CStage.h"
#include <list>

typedef struct
{
	CCharcterBase*	m_Character;
	int				m_Exp;
}PlayerData;

enum GameMode
{
	Casual = 0,
	Classic,
};

class WorldManager
{
private:
	//ゲームモード
	static GameMode Gamemode;

	//プレイヤーのユニットデータ
	static std::map<std::string, std::list<PlayerData*>> PlayerParty;

	//ステージデータ
	static PanelState*	Stage[5];

	//今のステージ
	static int NowStage;

	//クリアにかかったターン数
	static int ClearTurn;

	//合計クリアターン数
	static int ClearTurnAll;

public:


	static void StageStart(int stageNum) 
	{ 
		NowStage = stageNum; 
		ClearTurn = 0;
	}

	//ターン経過
	static void AddTurn() { ClearTurn++; }
};

#endif // !WORLD_MANAGER_H_
