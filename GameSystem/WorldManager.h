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
	//�Q�[�����[�h
	static GameMode Gamemode;

	//�v���C���[�̃��j�b�g�f�[�^
	static std::map<std::string, std::list<PlayerData*>> PlayerParty;

	//�X�e�[�W�f�[�^
	static PanelState*	Stage[5];

	//���̃X�e�[�W
	static int NowStage;

	//�N���A�ɂ��������^�[����
	static int ClearTurn;

	//���v�N���A�^�[����
	static int ClearTurnAll;

public:
	static void SetGameMode(GameMode mode);

	static void StageStart(int stageNum);

	//�^�[���o��
	static void AddTurn();
};

#endif // !WORLD_MANAGER_H_
