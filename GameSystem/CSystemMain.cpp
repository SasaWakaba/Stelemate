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



void CSystemMain::Initialize(int x, int z, PanelState* Map)
{
	m_X = x;
	m_Z = z;

	m_Cursor = new C3DPolygon();
	m_Cursor->Initialize();

	m_CursorLocation.x = 0;
	m_CursorLocation.z = 0;

	m_StageMap = Map;

	m_bSelect = false;

	m_bMenu = false;

	m_bBattle = false;

	m_Yazirushi = new CBillboard();
	m_Yazirushi->Initialize();
	
	m_Yazirushi->Load("asset/texture/tns.png");

	m_Arrow = new CArrowsLine();
	m_Arrow->Initialize();

	m_MoveSerch = new CMoveSearch();
	m_MoveSerch->Initialize(m_X, m_Z, m_StageMap);

	m_AttackSearch = new CAttackSearch();
	m_AttackSearch->Initialize(m_X, m_Z, m_StageMap);

	CCamera::SetAt(XMFLOAT3((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.5f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2)));

	turn = 0;

	m_Enemy = new CEnemyAI();
	m_Enemy->Initialize(m_X, m_Z, m_StageMap);

	m_Frame = 0;
	m_FrameEnemy = 0;
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

	CPanelState::SetPanel(m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].PanelPattarn);
	CCharacterState::SetPanel(&m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x]);

	CScene* sceneC;
	sceneC = CManager::GetScene();

	CTurnChangeUI* ChangeUI = sceneC->GetGameObject<CTurnChangeUI>(4);

	switch (turn)
	{
	case Player:
		TurnPlayer();
		break;
	case Enemy:
		TurnEnemy();
		break;
	case TurnChangePlayer:
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
		}
		break;
	case TurnChangeEnemy:
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


	m_Frame++;
}

void CSystemMain::Draw()
{

	XMMATRIX world;

	//カーソルのあるパネル
	world = XMMatrixTranslation((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.5f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2));
	m_Cursor->Draw(world);

	//移動できる範囲の描画
	m_MoveSerch->Draw();

	m_AttackSearch->Draw();

	//移動の矢印の描画
	if (m_bSelect)
	{
		m_Arrow->Draw(m_X, m_Z);
	}

	//カーソルの描画
	world = XMMatrixTranslation((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 3.0f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2));
	m_Yazirushi->Draw(world);
}


void CSystemMain::TurnPlayer()
{


	//選択カーソル移動
	{
		//上入力
		if (CInput::GetKeyTrigger('W'))
		{
			if (!m_bMenu && !m_bSelect)
			{
				if ((m_CursorLocation.z + 1) < m_Z)
				{
					m_CursorLocation.z++;
				}
			}
			else if (m_bSelect)
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
		}
		//下入力
		if (CInput::GetKeyTrigger('S'))
		{
			if (!m_bMenu && !m_bSelect)
			{
				if ((m_CursorLocation.z - 1) >= 0)
				{
					m_CursorLocation.z--;
				}
			}
			else if (m_bSelect)
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
		}
		//左入力
		if (CInput::GetKeyTrigger('A'))
		{
			if (!m_bMenu && !m_bSelect)
			{
				if ((m_CursorLocation.x - 1) >= 0)
				{
					m_CursorLocation.x--;
				}
			}
			else if (m_bSelect)
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
		}
		//右入力
		if (CInput::GetKeyTrigger('D'))
		{
			if (!m_bMenu && !m_bSelect)
			{
				if ((m_CursorLocation.x + 1) < m_X)
				{
					m_CursorLocation.x++;
				}
			}
			else if (m_bSelect)
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
	}

	//キャラ選択中の移動矢印の判断
	if (m_CursorOld.x != m_CursorLocation.x || m_CursorOld.z != m_CursorLocation.z)
	{
		if (m_bSelect)
		{
			m_Arrow->Add(m_CursorLocation);
		}
	}

	//移動できる範囲の計算
	if (m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar || m_bSelect)
	{
		int move;
		if (!m_bSelect)
		{
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
			move = m_SelectChar->GetStatus()->MovePoint;
			m_MoveArea = m_MoveSerch->Search(m_SelectLocation, move);
			m_MoveSerch->SetDraw(true);
		}
	}
	else
	{
		m_MoveSerch->SetDraw(false);
		m_MoveSerch->Reset();
	}

	//決定キー入力
	if (CInput::GetKeyTrigger('E'))
	{
		m_Ok->Play(false);
		if (!m_bSelect && !m_bMenu)
		{
			if (m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar && m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter->GetAlly())
			{
				m_SelectChar = m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter;
				m_SelectPanel = &m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x];
				m_SelectLocation = m_CursorLocation;
				m_bSelect = true;
				m_Arrow->Add(m_CursorLocation);
			}
		}
		else if (m_bSelect)
		{
			if (!m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar)
			{
				m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar = true;
				m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter = m_SelectChar;
				m_SelectChar->MoveLocation(XMFLOAT3((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 1.0f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2)));


				CScene* scene;
				scene = CManager::GetScene();

				CGameMenu_UI* UI = scene->GetGameObject<CGameMenu_UI>(4);

				m_AtkArea = m_AttackSearch->Search(m_CursorLocation, m_SelectChar->GetStatus()->type);


				m_SelectPanel->bChar = false;
				m_SelectPanel->Charcter = nullptr;
				m_SelectPanel = nullptr;

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



				m_bSelect = false;
				m_Arrow->Reset();
				m_bMenu = true;
			}
		}
		else if (m_bMenu)
		{
			CScene* scene;
			scene = CManager::GetScene();

			CGameMenu_UI* UI = scene->GetGameObject<CGameMenu_UI>(4);

			if (UI->Ready())
			{
				switch (UI->OK())
				{
				case 0:
					for (Vector2_3D pos : m_AtkArea)
					{
						if (m_StageMap[pos.z * m_X + pos.x].bChar)
						{
							CSystemBattle::Battle(m_SelectChar, m_StageMap[pos.z * m_X + pos.x].Charcter);
							m_bBattle = true;
							break;
						}
					}
					break;
				case 2:
					m_SelectChar->SetTurnMove(true);
					break;
				}

				UI->reset();
				m_AttackSearch->Reset();
				m_bMenu = false;
				m_SelectChar = nullptr;

				
			}
		}
	}





	if (CInput::GetKeyTrigger('Q'))
	{
		if (m_bSelect)
		{
			m_MoveSerch->SetDraw(false);
			m_MoveSerch->Reset();

			m_SelectChar = nullptr;
			m_SelectPanel = nullptr;

			m_bSelect = false;
			m_Arrow->Reset();
		}
		else if (m_bMenu)
		{
			m_StageMap[m_SelectLocation.z * m_X + m_SelectLocation.x].bChar = true;
			m_StageMap[m_SelectLocation.z * m_X + m_SelectLocation.x].Charcter = m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter;
			m_StageMap[m_SelectLocation.z * m_X + m_SelectLocation.x].Charcter->MoveLocation(XMFLOAT3((m_SelectLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 1.0f, (m_SelectLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2)));

			m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar = false;
			m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter = nullptr;

			CScene* scene;
			scene = CManager::GetScene();

			CGameMenu_UI* UI = scene->GetGameObject<CGameMenu_UI>(4);

			UI->reset();
			m_AttackSearch->Reset();
			m_bMenu = false;
			m_SelectChar = nullptr;
		}
	}

	if (m_bBattle)
	{
		if (!CSystemBattle::BattleEnd())
		{
			CScene* sceneC;
			sceneC = CManager::GetScene();

			CTurnChangeUI* ChangeUI = sceneC->GetGameObject<CTurnChangeUI>(4);
			ChangeUI->ChangeEnemy();
			turn = TurnChangeEnemy;
		}
	}


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
	}
}


void CSystemMain::TurnEnemy()
{
	int age = m_Frame - m_FrameEnemy;
	if (age % 30 == 0)
	{
		CCharcterBase* enemy = nullptr;
		Vector2_3D pos;
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
							enemy = m_StageMap[z * m_X + x].Charcter;
							m_StageMap[z * m_X + x].bChar = false;
							m_StageMap[z * m_X + x].Charcter = nullptr;
							pos = { x, z };
							break;
						}
					}
				}
			}
		}

		if (enemy != nullptr)
		{
			for (Vector2_3D ene : m_Enemy->Move(pos, enemy->GetStatus()->MovePoint))
			{
				m_CursorLocation = ene;
			}

			m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].bChar = true;
			m_StageMap[m_CursorLocation.z * m_X + m_CursorLocation.x].Charcter = enemy;
			enemy->MoveLocation(XMFLOAT3((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 1.0f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2)));
			enemy->SetTurnMove(true);
		}



		
	}

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