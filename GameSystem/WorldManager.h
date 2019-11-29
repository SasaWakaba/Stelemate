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
	//�Q�[�����[�h
	static GameMode Gamemode;

	//�v���C���[�̃��j�b�g�f�[�^
	static std::map<std::string, std::list<PlayerData*>> PlayerParty;

	//�X�e�[�W�f�[�^
	static StageState	StageStateAll[5];

	//���̃X�e�[�W
	static int NowStage;

	//�N���A�ɂ��������^�[����
	static int ClearTurn;

	//���v�N���A�^�[����
	static int ClearTurnAll;

	//�ٗp�⋭���Ɏg�p����|�C���g,SP
	static int SoldierPoint;

	//���݂̃^�[���F�v���C���[or�G�l�~�[
	static int turn;

	//�G�l�~�[�̍s��
	static EnemyMove enemyAction;

public:
	//�Q�[�����[�h�ݒ�
	static void SetGameMode(GameMode mode);

	//�X�e�[�W�J�n
	static void StageStart(int stageNum);

	//�X�e�[�W���i�[
	static void SetStageState(PanelState* stage, int x, int z, int stageNum);

	//�^�[���o��
	static void AddTurn();

	//SP���Z
	static void AddSoldierPoint(int add);
	//SP�g�p
	static void UseSoldierPoint(int use);

	//�f�o�b�O�p���擾�֐�
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
