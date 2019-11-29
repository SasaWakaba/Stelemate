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

typedef struct
{
	PanelState* Stage;
	int			numX;
	int			numZ;
}StageState;

class WorldManager
{
private:
	//ゲームモード
	static GameMode Gamemode;

	//プレイヤーのユニットデータ
	static std::map<std::string, std::list<PlayerData*>> PlayerParty;

	//ステージデータ
	static StageState	StageStateAll[5];

	//今のステージ
	static int NowStage;

	//クリアにかかったターン数
	static int ClearTurn;

	//合計クリアターン数
	static int ClearTurnAll;

	//雇用や強化に使用するポイント,SP
	static int SoldierPoint;

	//現在のターン：プレイヤーorエネミー
	static int turn;

	//エネミーの行動
	static EnemyMove enemyAction;

public:
	//ゲームモード設定
	static void SetGameMode(GameMode mode);

	//ステージ開始
	static void StageStart(int stageNum);

	//ステージ情報格納
	static void SetStageState(PanelState* stage, int x, int z, int stageNum);

	//ターン経過
	static void AddTurn();

	//SP加算
	static void AddSoldierPoint(int add);
	//SP使用
	static void UseSoldierPoint(int use);

	//デバッグ用情報取得関数
	static GameMode GetGameMode() { return Gamemode; }
	static int GetNowStageNum() { return NowStage; }
	static StageState GetNowStage() { return StageStateAll[NowStage]; }
	static int GetTurn() { return ClearTurn; }
	static void SetTurn(int Nowturn) { turn = Nowturn; }
	static int GetActionTurn() { return turn; }
	static void SetEnemyAction(EnemyMove move) { enemyAction = move; }
	static EnemyMove GetEnemyAction() { return enemyAction; }

};

#endif // !WORLD_MANAGER_H_
