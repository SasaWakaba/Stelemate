#include <vector>

#include "../common/main.h"
#include "../common/input.h"
#include "../common/texture.h"
#include "../common/Billboard.h"
#include "../Stage/CStage.h"
#include "../Charcter/CCharcterBase.h"
#include "../UI/GameMenu_UI.h"
#include "../common/Scene.h"
#include "../common/CGame.h"
#include "../common/manager.h"
#include "../common/camera.h"
#include "../common/math.h"
#include "CCursor.h"
#include "CSystemMain.h"
#include "C3DPolygon.h"
#include "ArrowsLine.h"
#include "CMoveSearch.h"
#include "CAttackSearch.h"
#include "CSystemBattle.h"
#include "../UI/PanelState_UI.h"
#include "../UI/CharacterState.h"
#include "CEnemyAI.h"

#include "../UI/TurnChange_UI.h"
#include "../UI/BattleSimu_UI.h"
#include "WorldManager.h"



void CSystemMain::Initialize(int x, int z, PanelState* Map)
{
	//フィールドのX最大数
	m_X = x;
	//フィールドのZ最大数
	m_Z = z;

	//カーソル(地面)の初期化
	m_Cursor = new C3DPolygon();
	m_Cursor->Initialize();
	//カーソル位置の初期化
	m_CursorLocation.x = 0;
	m_CursorLocation.z = 0;
	//ステージの保存
	m_StageMap = Map;

	//選択フラグ初期化
	m_bSelect = false;
	//メニュー表示フラグ初期化
	m_bMenu = false;
	//バトル中フラグ初期化
	m_bBattle = false;
	//カーソル(矢印)の初期化
	m_Yazirushi = new CBillboard();
	m_Yazirushi->Initialize();
	
	m_Yazirushi->Load("asset/texture/tns.png");

	//移動矢印初期化
	m_Arrow = new CArrowsLine();
	m_Arrow->Initialize();

	//移動範囲計測の初期化
	m_MoveSerch = new CMoveSearch();
	m_MoveSerch->Initialize(m_X, m_Z, m_StageMap);
	//攻撃範囲計測の初期化
	m_AttackSearch = new CAttackSearch();
	m_AttackSearch->Initialize(m_X, m_Z, m_StageMap);
	//カメラ位置初期化
	CCamera::SetAt(XMFLOAT3((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.5f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2)));
	//ターン初期化
	turn = TurnChangePlayer;
	//エネミーのAI初期化
	m_Enemy = new CEnemyAI();
	m_Enemy->Initialize(m_X, m_Z, m_StageMap);
	//フレーム
	m_Frame = 0;
	m_FrameEnemy = 0;

	m_EnemyMoving = wait;
	PlayerSelection = NotSelect;

	WorldManager::SetEnemyAction(m_EnemyMoving);

	CCharcterBase* SelectEnemy = nullptr;
	Vector2_3D SelectEnemyPos = {0, 0};


	//===============
	m_StageMap[0].Charcter->GetStatus()->HP = 99;
	m_StageMap[0].Charcter->nowHP = 99;
}

void CSystemMain::Finalize()
{
	m_Enemy->Finalize();
	delete m_Enemy;

	m_AttackSearch->Finalize();
	delete m_AttackSearch;

	m_MoveSerch->Finalize();
	delete m_MoveSerch;

	m_Arrow->Finalize();
	delete m_Arrow;

	m_Ok->Unload();
	delete m_Ok;

	m_Yazirushi->Finalize();
	delete m_Yazirushi;


	m_Cursor->Finalize();
	delete m_Cursor;
}

void CSystemMain::Update()
{
	if (m_CursorOld.x != m_CursorLocation.x || m_CursorOld.z != m_CursorLocation.z)
	{
		CCamera::Move(XMFLOAT3((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.5f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2)));
	}
	//前のカーソル位置の保存
	m_CursorOld = m_CursorLocation;

	//ステージパネルの情報UIの更新
	if (PlayerSelection != BattleSelect && !m_bBattle)
	{
		CPanelState::SetDraw(true);
		CPanelState::SetPanel(m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].PanelPattarn);
		CCharacterState::SetPanel(&m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x]);
	}
	else
	{
		CPanelState::SetDraw(false);
		CCharacterState::SetPanel(nullptr);
	}

	CScene* scene;
	scene = CManager::GetScene();

	CTurnChangeUI* ChangeUI = scene->GetGameObject<CTurnChangeUI>(4);

	WorldManager::SetTurn(turn);

	switch (turn)
	{
	case Player:
		TurnPlayer();
		break;
	case Enemy:
		TurnEnemy();
		break;
	case TurnChangePlayer:
		m_bBattle = false;
		for (int z = 0; z < m_Z; z++)
		{
			for (int x = 0; x < m_X; x++)
			{
				if (m_StageMap[z * m_X + x].bChar)
				{
					if (m_StageMap[z * m_X + x].Charcter->GetAlly())
					{
						m_CursorLocation = {x, z};
					}
				}
			}
		}
		if (!ChangeUI->GetEndPL())
		{
			for (int z = 0; z < m_Z; z++)
			{
				for (int x = 0; x < m_X; x++)
				{
					if (m_StageMap[z * m_X + x].bChar)
					{
						if (m_StageMap[z * m_X + x].Charcter->GetAlly())
						{
							m_StageMap[z * m_X + x].Charcter->SetTurnMove(false);
						}
					}
				}
			}
			turn = Player;
			WorldManager::AddTurn();
		}
		break;
	case TurnChangeEnemy:
		m_bBattle = false;
		for (int z = 0; z < m_Z; z++)
		{
			for (int x = 0; x < m_X; x++)
			{
				if (m_StageMap[z * m_X + x].bChar)
				{
					if (!m_StageMap[z * m_X + x].Charcter->GetAlly())
					{
						m_CursorLocation = { x, z };
					}
				}
			}
		}

		if (!ChangeUI->GetEndEne())
		{
			for (int z = 0; z < m_Z; z++)
			{
				for (int x = 0; x < m_X; x++)
				{
					if (m_StageMap[z * m_X + x].bChar)
					{
						if (!m_StageMap[z * m_X + x].Charcter->GetAlly())
						{
							m_StageMap[z * m_X + x].Charcter->SetTurnMove(false);
						}
					}
				}
			}
			m_FrameEnemy = m_Frame;
			turn = Enemy;
		}
		break;
	}

	//敵が全滅したらクリア============================================
	int eneCnt = 0;
	for (int z = 0; z < m_Z; z++)
	{
		for (int x = 0; x < m_X; x++)
		{
			if (m_StageMap[z * m_X + x].bChar)
			{
				if (!m_StageMap[z * m_X + x].Charcter->GetAlly())
				{
					eneCnt++;

				}
			}
		}
	}

	if (eneCnt == 0)
	{
		CGame::Change();
	}
	//============================================================

	//味方が全滅したらゲームオーバー============================================
	int preCnt = 0;
	for (int z = 0; z < m_Z; z++)
	{
		for (int x = 0; x < m_X; x++)
		{
			if (m_StageMap[z * m_X + x].bChar)
			{
				if (m_StageMap[z * m_X + x].Charcter->GetAlly())
				{
					preCnt++;

				}
			}
		}
	}

	if (preCnt == 0)
	{
		CGame::Change();
	}
	//============================================================

	m_Frame++;
}

void CSystemMain::Draw()
{
	if (!m_bBattle)
	{
		XMMATRIX world;

		//カーソルのあるパネル
		world = XMMatrixTranslation((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.5f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2));
		m_Cursor->Draw(world);

		//移動できる範囲の描画
		m_MoveSerch->Draw();

		m_AttackSearch->Draw();

		//移動の矢印の描画
		if (PlayerSelection == Select)
		{
			m_Arrow->Draw(m_X, m_Z);
		}

		//カーソルの描画
		world = XMMatrixTranslation((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 3.5f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2));
		m_Yazirushi->Draw(world);
	}
}


void CSystemMain::TurnPlayer()
{
	switch (PlayerSelection)
	{
	case NotSelect:
	//選択カーソル移動
	{
		//上入力
		if (CInput::GetKeyTrigger('W'))
		{
			if ((m_CursorLocation.z + 1) < m_Z)
			{
				m_CursorLocation.z++;
			}

		}
		//下入力
		if (CInput::GetKeyTrigger('S'))
		{
			if ((m_CursorLocation.z - 1) >= 0)
			{
				m_CursorLocation.z--;
			}
		}
		//左入力
		if (CInput::GetKeyTrigger('A'))
		{
			if ((m_CursorLocation.x - 1) >= 0)
			{
				m_CursorLocation.x--;
			}
		}
		//右入力
		if (CInput::GetKeyTrigger('D'))
		{
			if ((m_CursorLocation.x + 1) < m_X)
			{
				m_CursorLocation.x++;
			}
		}
	}

	//移動できる範囲の計算
	{
		if (m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar)
		{
			int move;
			if (m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter->GetAlly())
			{
				move = m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter->GetStatus()->MovePoint;
				m_MoveSerch->Search(m_CursorLocation, move);
				m_MoveSerch->SetDraw(true);
			}
			else
			{
				m_MoveSerch->SetDraw(false);
				m_MoveSerch->Reset();
			}
		}
		else
		{
			m_MoveSerch->SetDraw(false);
			m_MoveSerch->Reset();
		}
	}

	//決定キー入力
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		m_Ok->Play(false);
		if (m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar && m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter->GetAlly())
		{
			m_SelectChar = m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter;
			m_SelectPanel = &m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x];
			m_SelectLocation = m_CursorLocation;
			m_Arrow->Add(m_CursorLocation);
			PlayerSelection = Select;
		}
	}
		break;

	case Select:
	//選択カーソル移動
	{
		//上入力
		if (CInput::GetKeyTrigger('W'))
		{
			if ((m_CursorLocation.z + 1) < m_Z)
			{
				for (Vector2_3D pos : m_MoveArea)
				{
					if ((m_CursorLocation.z + 1) == pos.z && m_CursorLocation.x == pos.x)
					{
						m_CursorLocation.z++;
						break;
					}
					else if ((m_CursorLocation.z + 1) == m_SelectLocation.z && m_CursorLocation.x == m_SelectLocation.x)
					{
						m_CursorLocation.z++;
						break;
					}
				}
			}
		}
		//下入力
		if (CInput::GetKeyTrigger('S'))
		{
			if ((m_CursorLocation.z - 1) >= 0)
			{
				for (Vector2_3D pos : m_MoveArea)
				{
					if ((m_CursorLocation.z - 1) == pos.z && m_CursorLocation.x == pos.x)
					{
						m_CursorLocation.z--;
						break;
					}
					else if ((m_CursorLocation.z - 1) == m_SelectLocation.z && m_CursorLocation.x == m_SelectLocation.x)
					{
						m_CursorLocation.z--;
						break;
					}
				}
			}
		}
		//左入力
		if (CInput::GetKeyTrigger('A'))
		{
			if ((m_CursorLocation.x - 1) >= 0)
			{
				for (Vector2_3D pos : m_MoveArea)
				{
					if ((m_CursorLocation.x - 1) == pos.x && m_CursorLocation.z == pos.z)
					{
						m_CursorLocation.x--;
						break;
					}
					else if ((m_CursorLocation.x - 1) == m_SelectLocation.x && m_CursorLocation.z == m_SelectLocation.z)
					{
						m_CursorLocation.x--;
						break;
					}
				}
			}
		}
		//右入力
		if (CInput::GetKeyTrigger('D'))
		{
			if ((m_CursorLocation.x + 1) >= 0)
			{
				for (Vector2_3D pos : m_MoveArea)
				{
					if ((m_CursorLocation.x + 1) == pos.x && m_CursorLocation.z == pos.z)
					{
						m_CursorLocation.x++;
						break;
					}
					else if ((m_CursorLocation.x + 1) == m_SelectLocation.x && m_CursorLocation.z == m_SelectLocation.z)
					{
						m_CursorLocation.x++;
						break;
					}
				}
			}
		}
	}
	//キャラ選択中の移動矢印の判断
	if (m_CursorOld.x != m_CursorLocation.x || m_CursorOld.z != m_CursorLocation.z)
	{
		m_Arrow->Add(m_CursorLocation);
	}
	//移動できる範囲の計算
	{
		int move;
		move = m_SelectChar->GetStatus()->MovePoint;
		m_MoveArea = m_MoveSerch->Search(m_SelectLocation, move);
		m_MoveSerch->SetDraw(true);
	}

	//決定キー入力
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		m_Ok->Play(false);
		CGameMenu_UI* UI;
		if (!m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar || m_SelectLocation == m_CursorLocation)
		{
			m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar = true;
			m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter = m_SelectChar;
			m_SelectChar->MoveLocation(XMFLOAT3((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.0f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2)));

			CScene* scene;
			scene = CManager::GetScene();

			UI = scene->GetGameObject<CGameMenu_UI>(4);

			m_AtkArea = m_AttackSearch->Search(m_CursorLocation, m_SelectChar->GetStatus()->type);

			if (m_SelectLocation != m_CursorLocation)
			{
				m_SelectPanel->bChar = false;
				m_SelectPanel->Charcter = nullptr;
			}
			m_SelectPanel = &m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x];

			bool attack = false;
			for (Vector2_3D pos : m_AtkArea)
			{
				if (m_StageMap[pos.z * m_X + pos.x].bChar)
				{
					attack = true;
					break;
				}
			}

			if (attack)
			{
				m_AttackSearch->SetDraw(true);
			}
			else
			{
				m_AttackSearch->SetDraw(false);
				m_AttackSearch->Reset();
			}

			UI->Set(attack, false, true);
			m_MoveSerch->SetDraw(false);
			m_MoveSerch->Reset();

			m_Arrow->Reset();
			m_SelectMovedLocation = m_CursorLocation;
			PlayerSelection = Manu;
		}
	}

	//キャンセルキー入力
	if (CInput::GetKeyTrigger('Q'))
	{
		m_MoveSerch->SetDraw(false);
		m_MoveSerch->Reset();

		m_SelectChar = nullptr;
		m_SelectPanel = nullptr;

		m_Arrow->Reset();
		PlayerSelection = NotSelect;
	}

		break;
	case Manu:
		//移動できる範囲の計算
		m_MoveSerch->SetDraw(false);
		m_MoveSerch->Reset();

		//決定キー入力
		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			m_Ok->Play(false);
			CGameMenu_UI* UI;
			UI = CManager::GetScene()->GetGameObject<CGameMenu_UI>(4);

			if (UI->Ready())
			{
				switch (UI->OK())
				{
				case 0:
					for (Vector2_3D pos : m_AtkArea)
					{
						if (m_StageMap[pos.z * m_X + pos.x].bChar)
						{
							m_CursorLocation = pos;
							break;
						}
					}
					PlayerSelection = BattleSelect;
					break;
				case 2:
					PlayerSelection = Fin;
					break;
				}
				UI->reset();
			}
		}

		//キャンセルキー入力
		if (CInput::GetKeyTrigger('Q'))
		{
			CGameMenu_UI* UI;
			m_StageMap[m_SelectLocation.z * m_X + m_SelectLocation.x].bChar = true;
			m_StageMap[m_SelectLocation.z * m_X + m_SelectLocation.x].Charcter = m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter;
			m_StageMap[m_SelectLocation.z * m_X + m_SelectLocation.x].Charcter->MoveLocation(XMFLOAT3((m_SelectLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.0f, (m_SelectLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2)));

			if (m_SelectLocation != m_CursorLocation)
			{
				m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar = false;
				m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter = nullptr;
			}

			CScene* scene;
			scene = CManager::GetScene();

			UI = scene->GetGameObject<CGameMenu_UI>(4);

			UI->reset();
			m_AttackSearch->Reset();
			m_SelectChar = nullptr;
			PlayerSelection = NotSelect;
		}
		break;
	case BattleSelect:
	//選択カーソル移動
	{
		//上入力
		if (CInput::GetKeyTrigger('W'))
		{
			if (m_AtkArea.size() > 1)
			{
				for (Vector2_3D pos : m_AtkArea)
				{
					if (m_StageMap[pos.z * m_X + pos.x].bChar)
					{
						if (m_CursorLocation.z < pos.z)
						{
							m_CursorLocation = pos;
							break;
						}
					}
				}
			}
		}
		//下入力
		if (CInput::GetKeyTrigger('S'))
		{
			if (m_AtkArea.size() > 1)
			{
				for (Vector2_3D pos : m_AtkArea)
				{
					if (m_StageMap[pos.z * m_X + pos.x].bChar)
					{
						if (m_CursorLocation.z > pos.z)
						{
							m_CursorLocation = pos;
							break;
						}
					}
				}
			}
		}
		//左入力
		if (CInput::GetKeyTrigger('A'))
		{
			if (m_AtkArea.size() > 1)
			{
				for (Vector2_3D pos : m_AtkArea)
				{
					if (m_StageMap[pos.z * m_X + pos.x].bChar)
					{
						if (m_CursorLocation.x > pos.x)
						{
							m_CursorLocation = pos;
							break;
						}
					}
				}
			}
		}
		//右入力
		if (CInput::GetKeyTrigger('D'))
		{
			if (m_AtkArea.size() > 1)
			{
				for (Vector2_3D pos : m_AtkArea)
				{
					if (m_StageMap[pos.z * m_X + pos.x].bChar)
					{
						if (m_CursorLocation.x < pos.x)
						{
							m_CursorLocation = pos;
							break;
						}
					}
				}
			}
		}
	}

	if(!m_bBattle)
	{
		CBattleSimu* simu = CManager::GetScene()->GetGameObject<CBattleSimu>(4);
		simu->SetDraw(true);
		simu->SetChar(m_SelectChar, m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter);
	}

	//決定キー入力
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		m_Ok->Play(false);
		CGameMenu_UI* UI;
		if (!m_bBattle)
		{
			for (Vector2_3D pos : m_AtkArea)
			{
				if (m_StageMap[pos.z * m_X + pos.x].bChar)
				{
					CSystemBattle::Battle(m_SelectPanel, &m_StageMap[pos.z * m_X + pos.x]);
					m_bBattle = true;
					m_AttackSearch->Reset();
					CBattleSimu* simu = CManager::GetScene()->GetGameObject<CBattleSimu>(4);
					simu->SetDraw(false);
					break;
				}
			}
		}
	}

	//キャンセルキー入力
	if (CInput::GetKeyTrigger('Q'))
	{
		m_AtkArea = m_AttackSearch->Search(m_SelectMovedLocation, m_SelectChar->GetStatus()->type);
		CGameMenu_UI* UI;
		UI = CManager::GetScene()->GetGameObject<CGameMenu_UI>(4);
		bool attack = false;
		for (Vector2_3D pos : m_AtkArea)
		{
			if (m_StageMap[pos.z * m_X + pos.x].bChar)
			{
				attack = true;
				break;
			}
		}

		if (attack)
		{
			m_AttackSearch->SetDraw(true);
		}
		else
		{
			m_AttackSearch->SetDraw(false);
			m_AttackSearch->Reset();
		}

		UI->Set(attack, false, true);
		m_CursorLocation = m_SelectMovedLocation;
		CBattleSimu* simu = CManager::GetScene()->GetGameObject<CBattleSimu>(4);
		simu->SetDraw(false);
		PlayerSelection = Manu;
	}
		break;
	case HealSelect:
		break;
	case Fin:
		m_SelectChar->SetTurnMove(true);
		m_SelectChar = nullptr;
		PlayerSelection = NotSelect;
		m_SelectPanel = nullptr;
		break;
	}

	if (m_bBattle)
	{
		if (!CSystemBattle::BattleEnd())
		{
			m_bBattle = false;
			PlayerSelection = Fin;
		}
	}

	//行動終了判定
	{
		int notMove = 0;
		for (int z = 0; z < m_Z; z++)
		{
			for (int x = 0; x < m_X; x++)
			{
				if (m_StageMap[z * m_X + x].bChar)
				{
					if (m_StageMap[z * m_X + x].Charcter->GetAlly())
					{
						if (!m_StageMap[z * m_X + x].Charcter->GetTurnMove())
						{
							notMove++;
						}
					}
				}
			}
		}

		if (notMove == 0)
		{
			CScene* sceneC;
			sceneC = CManager::GetScene();

			CTurnChangeUI* ChangeUI = sceneC->GetGameObject<CTurnChangeUI>(4);
			ChangeUI->ChangeEnemy();
			turn = TurnChangeEnemy;
			m_MoveSerch->SetDraw(false);
			m_MoveSerch->Reset();
			m_AttackSearch->SetDraw(false);
			m_AttackSearch->Reset();
		}
	}
}


void CSystemMain::TurnEnemy()
{
	{
		//行動していないキャラがいるか
		if (m_EnemyMoving == wait)
		{
			int notMove = 0;
			for (int z = 0; z < m_Z; z++)
			{
				for (int x = 0; x < m_X; x++)
				{
					if (m_StageMap[z * m_X + x].bChar)
					{
						if (!m_StageMap[z * m_X + x].Charcter->GetAlly())
						{
							if (!m_StageMap[z * m_X + x].Charcter->GetTurnMove())
							{
								notMove++;
							}
						}
					}
				}
			}
			//全員行動済みになったらターン終了
			if (notMove == 0)
			{
				static int cnt = 0;
				if (cnt == 30)
				{
					CScene* sceneC;
					sceneC = CManager::GetScene();

					CTurnChangeUI* ChangeUI = sceneC->GetGameObject<CTurnChangeUI>(4);
					ChangeUI->ChangePlayer();
					turn = TurnChangePlayer;
					cnt = 0;
				}
				cnt++;
			}
		}
	}
	int age = m_Frame - m_FrameEnemy;
	if (age % 15 == 0)
	{
		switch (m_EnemyMoving)
		{
		case wait:
			for (int z = 0; z < m_Z; z++)
			{
				for (int x = 0; x < m_X; x++)
				{
					if (m_StageMap[z * m_X + x].bChar)
					{
						if (!m_StageMap[z * m_X + x].Charcter->GetAlly())
						{
							if (!m_StageMap[z * m_X + x].Charcter->GetTurnMove())
							{
								SelectEnemy = m_StageMap[z * m_X + x].Charcter;
								SelectEnemyPos = { x, z };
								m_EnemyMoving = move;
								m_CursorLocation = SelectEnemyPos;

								WorldManager::SetEnemyAction(m_EnemyMoving);

								break;
							}
						}
					}
				}
			}
			break;
		case move:
			if (SelectEnemy != nullptr)
			{
				m_CursorLocation = m_Enemy->Move(SelectEnemyPos, SelectEnemy->GetStatus()->MovePoint).back();
				m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar = true;
				m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter = SelectEnemy;
				SelectEnemy->MoveLocation(XMFLOAT3((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.0f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2)));

				if (m_CursorLocation != SelectEnemyPos)
				{
					m_StageMap[SelectEnemyPos.z * m_X + SelectEnemyPos.x].bChar = false;
					m_StageMap[SelectEnemyPos.z * m_X + SelectEnemyPos.x].Charcter = nullptr;
				}

				SelectEnemyPos = m_CursorLocation;
			}
			m_EnemyMoving = m_Enemy->Select(m_CursorLocation, SelectEnemy->GetWeapon()->WeaponType);

			WorldManager::SetEnemyAction(m_EnemyMoving);

			break;
		case attack:
			if (!m_bBattle)
			{
				for (Vector2_3D pos : m_AttackSearch->Search(m_CursorLocation, SelectEnemy->GetWeapon()->WeaponType))
				{
					if (m_StageMap[pos.z * m_X + pos.x].bChar)
					{
						if (m_StageMap[pos.z * m_X + pos.x].Charcter->GetAlly())
						{
							CSystemBattle::Battle(&m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x], &m_StageMap[pos.z * m_X + pos.x]);
							m_bBattle = true;
							break;
						}
					}
				}
			}

			if (m_bBattle)
			{
				if (!CSystemBattle::BattleEnd())
				{
					m_EnemyMoving = end;
					m_bBattle = false;
					if (SelectEnemy->nowHP <= 0)
					{
						m_StageMap[SelectEnemyPos.z * m_X + SelectEnemyPos.x].bChar = false;
						m_StageMap[SelectEnemyPos.z * m_X + SelectEnemyPos.x].Charcter = nullptr;
					}
				}
			}
			else
			{
				m_EnemyMoving = end;
			}

			WorldManager::SetEnemyAction(m_EnemyMoving);

			break;
		case heal:
			for (Vector2_3D pos : m_AttackSearch->Search(m_CursorLocation, SelectEnemy->GetWeapon()->WeaponType))
			{
				if (m_StageMap[pos.z * m_X + pos.x].bChar)
				{
					if (!m_StageMap[pos.z * m_X + pos.x].Charcter->GetAlly())
					{
						//CSystemBattle::Battle(SelectEnemy, m_StageMap[pos.z * m_X + pos.x].Charcter);
						break;
					}
				}
			}

			WorldManager::SetEnemyAction(m_EnemyMoving);

			break;
		case end:
			SelectEnemy->SetTurnMove(true);
			SelectEnemy = nullptr;
			m_EnemyMoving = wait;

			WorldManager::SetEnemyAction(m_EnemyMoving);

			break;
		default:
			break;
		}
	}


}