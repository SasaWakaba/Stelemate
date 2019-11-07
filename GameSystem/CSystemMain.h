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
	//カーソルの二次元座標(現在)
	Vector2_3D					m_CursorLocation;
	//カーソルの二次元座標(ひとつ前)
	Vector2_3D					m_CursorOld;
	//選択中のキャラの二次元座標
	Vector2_3D					m_SelectLocation;
	//ステージのデータ
	PanelState*					m_StageMap;
	//選択中のパネル
	PanelState*					m_SelectPanel;
	//選択中のキャラのデータ
	CCharcterBase*				m_SelectChar;
	//矢印のビルボード
	CBillboard*					m_Yazirushi;
	//カーソルのポリゴン
	C3DPolygon*					m_Cursor;
	//決定音
	CAudioClip*					m_Ok;
	//移動矢印
	CArrowsLine*				m_Arrow;
	//移動範囲計算
	CMoveSearch*				m_MoveSerch;
	//移動可能範囲
	std::vector<Vector2_3D>		m_MoveArea;
	//攻撃可能範囲計算
	CAttackSearch*				m_AttackSearch;
	//攻撃可能範囲
	std::vector<Vector2_3D>		m_AtkArea;

	CEnemyAI*					m_Enemy;


	//ステージの縦と横の最大サイズ
	int m_X, m_Z;

	int m_Frame;

	int m_FrameEnemy;
	//選択中か否か
	bool m_bSelect;
	//メニュー表示中か否か
	bool m_bMenu;
	//戦闘中か否か
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
