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
	int				m_NextExp;
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

	//雇用や強化に使用するポイント,SP
	static int SoldierPoint;

public:
	//ゲームモード設定
	static void SetGameMode(GameMode mode);

	//ステージ開始
	static void StageStart(int stageNum);

	//ターン経過
	static void AddTurn();

	//SP加算
	static void AddSoldierPoint(int add);
	//SP使用
	static void UseSoldierPoint(int use);
};

#endif // !WORLD_MANAGER_H_
