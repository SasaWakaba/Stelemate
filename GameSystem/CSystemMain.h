#ifndef CSYSTEM_MAIN_H_
#define CSYSTEM_MAIN_H_

#include <vector>
#include "../common/main.h"
#include "../Stage/CStage.h"
#include "../Audio/audio_clip.h"

#include "CMoveSearch.h"
#include "CAttackSearch.h"


class CCursor;
class CBillboard;
class CCharcterBase;
class C3DPolygon;
class CArrowsLine;
class CEnemyAI;




class CSystemMain
{
private:
	//�J�[�\���̓񎟌����W(����)
	Vector2_3D					m_CursorLocation;
	//�J�[�\���̓񎟌����W(�ЂƂO)
	Vector2_3D					m_CursorOld;
	//�I�𒆂̃L�����̓񎟌����W
	Vector2_3D					m_SelectLocation;
	//�X�e�[�W�̃f�[�^
	PanelState*					m_StageMap;
	//�I�𒆂̃p�l��
	PanelState*					m_SelectPanel;
	//�I�𒆂̃L�����̃f�[�^
	CCharcterBase*				m_SelectChar;
	//���̃r���{�[�h
	CBillboard*					m_Yazirushi;
	//�J�[�\���̃|���S��
	C3DPolygon*					m_Cursor;
	//���艹
	CAudioClip*					m_Ok;
	//�ړ����
	CArrowsLine*				m_Arrow;
	//�ړ��͈͌v�Z
	CMoveSearch*				m_MoveSerch;
	//�ړ��\�͈�
	std::vector<Vector2_3D>		m_MoveArea;
	//�U���\�͈͌v�Z
	CAttackSearch*				m_AttackSearch;
	//�U���\�͈�
	std::vector<Vector2_3D>		m_AtkArea;

	CEnemyAI*					m_Enemy;


	//�X�e�[�W�̏c�Ɖ��̍ő�T�C�Y
	int m_X, m_Z;

	int m_Frame;

	int m_FrameEnemy;
	//�I�𒆂��ۂ�
	bool m_bSelect;
	//���j���[�\�������ۂ�
	bool m_bMenu;
	//�퓬�����ۂ�
	bool m_bBattle;


	enum Turn
	{
		Player,
		Enemy,
		TurnChangePlayer,
		TurnChangeEnemy
	};
	int turn;
	void TurnPlayer();
	void TurnEnemy();

public:
	CSystemMain():m_SelectChar(nullptr), m_Cursor(nullptr), m_StageMap(nullptr), m_SelectPanel(nullptr){
		m_Ok = new CAudioClip();
		m_Ok->Load("asset/audio/decision.wav");
	}

	void Initialize(int x, int z, PanelState* Map);
	void Finalize();
	void Update();
	void Draw();
};

#endif // !CSYSTEM_MAIN_H_
