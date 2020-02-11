#ifndef WORLD_MANAGER_H_
#define WORLD_MANAGER_H_

#include "../common/main.h"
#include "../common/math.h"
#include "../Charcter/CCharcterBase.h"
#include "../Stage/CStage.h"
#include "../Charcter/CPlayerManager.h"
#include "../Stage/CStageData.h"
#include <list>


class CPlayerManager;

enum GameMode
{
	Casual = 0,
	Classic,
};

class CMoveSearch;

class WorldManager
{
private:
	//ゲームモード
	static GameMode Gamemode;

	//プレイヤーのユニットデータ
	static CPlayerManager* PlayerParty;

	//ステージデータ
	static std::vector<StageInfo*>	StageStateAll;

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

	static CMoveSearch* moveArea;

public:
	static void Initialize();
	static void Finalize();

	//ゲームモード設定
	static void SetGameMode(GameMode mode);

	//ステージ開始
	static void StageStart(int stageNum);

	//ステージ情報格納
	static void SetStageState(StageInfo* stage);

	//ステージ情報取得
	static std::vector<StageInfo*> GetStageInfo() { return StageStateAll; }

	//レベルアップ(プレイヤー)
	static int LevelUpMember(const char* characterName, int EnemyLevel) { return PlayerParty->CharacterGetExperience(characterName, EnemyLevel); }

	//ターン経過
	static void AddTurn();

	//SP加算
	static void AddSoldierPoint(int add);
	//SP使用
	static void UseSoldierPoint(int use);
	//SP取得
	static int GetSoldierPoint();

	//雇用
	static STATUS* PlayerAdd(const char* characterName, PlayerData* menber);
	static std::map<std::string, PlayerData*> GetParty();

	//デバッグ用情報取得関数
	static GameMode GetGameMode() { return Gamemode; }
	static int GetNowStageNum() { return NowStage; }
	static StageInfo GetNowStage() { return *StageStateAll[NowStage]; }
	static int GetTurn() { return ClearTurn; }
	static void SetTurn(int Nowturn) { turn = Nowturn; }
	static int GetActionTurn() { return turn; }
	static void SetEnemyAction(EnemyMove move) { enemyAction = move; }
	static EnemyMove GetEnemyAction() { return enemyAction; }
	static void SetMoveSearch(CMoveSearch* area) { moveArea = area; }

};

#endif // !WORLD_MANAGER_H_
