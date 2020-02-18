#include "CStagePanel.h"
#include "CStageData.h"
#include "../common/texture.h"
#include "../common/Billboard.h"
#include "../common/input.h"
#include "../common/inputController.h"
#include "../GameSystem/WorldManager.h"
#include "../common/Scene.h"
#include "../common/manager.h"
#include "../GameSystem/CSubCamera.h"
#include "CStageManager.h"
#include "CStageSetting.h"
#include "../GameSystem/C3DPolygon.h"
#include "../common/TextureManager.h"
#include <map>

#include "../Charcter/CJob.h"


void CStageSetting::Edit() { edit = true; frame = 0; }
bool CStageSetting::GetEdit() { return edit; }
StageInfo* CStageSetting::GetSettingStage() { return pStage; }

void CStageSetting::Initialize(int stageNum)
{
	pStage = GetStageData(stageNum);
	{
		StageEnemy ene = GetStageEnemy(stageNum);
		for (int i = 0; i < ene.SwordmanNum; i++)
		{
			CCharcterBase* enemy;
			enemy = new CSwordsman();
			enemy->Initialize();
			enemy->SetAlly(false);

			int z = pStage->StageZnum - 1;
			int x = pStage->StageXnum - 1;
			while (1)
			{
				if (pStage->stage[z * pStage->StageZnum + x].bChar == false)
				{
					enemy->SetLocation(XMFLOAT3((x * SPACE_SIZE) - (SPACE_SIZE * pStage->StageXnum / 2), 0.0f, (z * SPACE_SIZE) - (SPACE_SIZE * pStage->StageZnum / 2)));

					pStage->stage[z * pStage->StageZnum + x].Charcter = enemy;
					pStage->stage[z * pStage->StageZnum + x].bChar = true;
					break;
				}
				else
				{
					x--;
					if (x < 0)
					{
						x = pStage->StageXnum - 1;
						z--;
					}
				}
			}
		}

		if (WorldManager::GetParty().size() > 0)
		{
			for (auto pl : WorldManager::GetParty())
			{
				pStage->stage[pl.second->PosZ * pStage->StageXnum + pl.second->PosX].bChar = true;
				pStage->stage[pl.second->PosZ * pStage->StageXnum + pl.second->PosX].Charcter = pl.second->m_Character;
			}
		}
	}

	edit = false;

	camera = new CSubCamera();
	camera->Initialize();
	camera->SetViewPos(SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, SCREEN_WIDTH / 5 * 4, SCREEN_HEIGHT / 5 * 4);
	camera->SetAt(XMFLOAT3(0.0f, 0.0f, 0.0f));

	camera->SetEye(XMFLOAT3(0.0f, 10.0f, -10.0f));

	m_3DPolygon = new C3DPolygon();
	m_3DPolygon->Initialize();


	m_StagePanel[0] = new CStagePanel(1, XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_StagePanel[0]->Initialize();

	m_StagePanel[1] = new CStagePanel(2, XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_StagePanel[1]->Initialize();

	m_Texture[0] = CTextureManager::LoadTexture("asset/texture/Move.png");
	m_Texture[1] = CTextureManager::LoadTexture("asset/texture/Atk.png");

	m_CursorLocation.x = 0;
	m_CursorLocation.z = 0;
	frame = 0;

	m_Yazirushi = new CBillboard();
	m_Yazirushi->Initialize();

	m_Yazirushi->Load("asset/texture/select_circle.png");
}

void CStageSetting::Finalize()
{
	camera->Finalize();
	delete camera;

	m_3DPolygon->Finalize();
	delete m_3DPolygon;

	m_Yazirushi->Finalize();
	delete m_Yazirushi;

	for (CStagePanel* panel : m_StagePanel)
	{
		panel->Finalize();
		delete panel;
	}

	SetStageData(pStage);
}

StageInfo* CStageSetting::GetStageData(int stageNum)
{
	std::string stage = "stage" + std::to_string(stageNum);
	return CStageData::m_StageData[stage];
}

StageEnemy CStageSetting::GetStageEnemy(int stageNum)
{
	std::string stage = "stage" + std::to_string(stageNum);
	return CStageData::m_StageEnemy[stage];
}

void CStageSetting::SetStageData(StageInfo* stage)
{
	WorldManager::SetStageState(stage);
}

void CStageSetting::Update()
{
	if (edit)
	{
		//上入力
		if (CInput::GetKeyTrigger('W') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_UP))
		{
			if ((m_CursorLocation.z + 1) < 2)
			{
				m_CursorLocation.z++;
			}

		}
		//下入力
		if (CInput::GetKeyTrigger('S') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			if ((m_CursorLocation.z - 1) >= 0)
			{
				m_CursorLocation.z--;
			}
		}
		//左入力
		if (CInput::GetKeyTrigger('A') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			if ((m_CursorLocation.x - 1) >= 0)
			{
				m_CursorLocation.x--;
			}
		}
		//右入力
		if (CInput::GetKeyTrigger('D') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_RIGHT))
		{
			if ((m_CursorLocation.x + 1) < pStage->StageXnum)
			{
				m_CursorLocation.x++;
			}
		}

		if (CInput::GetKeyTrigger('Q') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_B))
		{
			if (select != true)
			{
				edit = false;
			}
			else
			{
				select = false;
			}
		}

		if (CInput::GetKeyTrigger(VK_SPACE) || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_A))
		{
			if (frame > 10)
			{
				if (select != true)
				{
					if (pStage->stage[m_CursorLocation.z * pStage->StageXnum + m_CursorLocation.x].bChar && pStage->stage[m_CursorLocation.z * pStage->StageXnum + m_CursorLocation.x].Charcter->GetAlly())
					{
						selectPos = m_CursorLocation;
						select = true;
					}
				}
				else
				{
					if (selectPos == m_CursorLocation)
					{
						select = false;
					}
					else if (pStage->stage[m_CursorLocation.z * pStage->StageXnum + m_CursorLocation.x].bChar == false)
					{
						pStage->stage[m_CursorLocation.z * pStage->StageXnum + m_CursorLocation.x].bChar = true;
						pStage->stage[m_CursorLocation.z * pStage->StageXnum + m_CursorLocation.x].Charcter = pStage->stage[selectPos.z * pStage->StageXnum + selectPos.x].Charcter;
						pStage->stage[m_CursorLocation.z * pStage->StageXnum + m_CursorLocation.x].Charcter->SetLocation(XMFLOAT3((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * pStage->StageXnum / 2), 0.0f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * pStage->StageZnum / 2)));
						pStage->stage[selectPos.z * pStage->StageXnum + selectPos.x].Charcter = nullptr;
						pStage->stage[selectPos.z * pStage->StageXnum + selectPos.x].bChar = false;

						
						WorldManager::GetParty()[pStage->stage[m_CursorLocation.z * pStage->StageXnum + m_CursorLocation.x].Charcter->GetName()]->PosX = m_CursorLocation.x;
						WorldManager::GetParty()[pStage->stage[m_CursorLocation.z * pStage->StageXnum + m_CursorLocation.x].Charcter->GetName()]->PosZ = m_CursorLocation.z;
						select = false;
					}
				}
			}
		}
		frame++;
	}

	if (WorldManager::GetParty().size() > 0)
	{
		for (auto pl : WorldManager::GetParty())
		{
			pStage->stage[pl.second->PosZ * pStage->StageXnum + pl.second->PosX].bChar = true;
			pStage->stage[pl.second->PosZ * pStage->StageXnum + pl.second->PosX].Charcter = pl.second->m_Character;
		}
	}


	for (int z = 0; z < pStage->StageZnum; z++)
	{
		for (int x = 0; x < pStage->StageXnum; x++)
		{
			if (pStage->stage[z * pStage->StageXnum + x].bChar)
			{
				pStage->stage[z * pStage->StageXnum + x].Charcter->Update();
				if (pStage->stage[z * pStage->StageXnum + x].Charcter->Destroy())
				{
					pStage->stage[z * pStage->StageXnum + x].bChar = false;
				}
			}
		}
	}
}

void CStageSetting::Draw()
{
	CRenderer::DepthReset();
	camera->SetViewPos(SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, SCREEN_WIDTH / 5 * 4, SCREEN_HEIGHT / 5 * 4);
	camera->Draw();



	for (int z = 0; z < pStage->StageZnum; z++)
	{
		for (int x = 0; x < pStage->StageXnum; x++)
		{
			if (pStage->stage[z * pStage->StageXnum + x].PanelPattarn == 1)
			{
				m_StagePanel[0]->SetPosition(XMFLOAT3((x * SPACE_SIZE) - (SPACE_SIZE * pStage->StageXnum / 2), -0.5f, (z * SPACE_SIZE) - (SPACE_SIZE * pStage->StageZnum / 2)));
				m_StagePanel[0]->Draw();
			}

			if (pStage->stage[z * pStage->StageXnum + x].PanelPattarn == 2)
			{
				m_StagePanel[1]->SetPosition(XMFLOAT3((x * SPACE_SIZE) - (SPACE_SIZE * pStage->StageXnum / 2), -0.5f, (z * SPACE_SIZE) - (SPACE_SIZE * pStage->StageZnum / 2)));
				m_StagePanel[1]->Draw();
			}

			if (pStage->stage[z * pStage->StageXnum + x].bChar)
			{
				pStage->stage[z * pStage->StageXnum + x].Charcter->Draw();
			}
		}
	}

	VertexColor_4 color;
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));
	for (int z = 0; z < 2; z++)
	{
		for (int x = 0; x < pStage->StageXnum; x++)
		{
			XMMATRIX matrix = XMMatrixTranslation((x * SPACE_SIZE) - (SPACE_SIZE * pStage->StageXnum / 2), 0.4f, (z * SPACE_SIZE) - (SPACE_SIZE * pStage->StageZnum / 2));
			m_3DPolygon->Draw(m_Texture[0], matrix, color);
			//matrix = XMMatrixTranslation(((pStage->StageXnum - 1 - x) * SPACE_SIZE) - (SPACE_SIZE * pStage->StageXnum / 2), 0.4f, ((pStage->StageZnum - 1 - z) * SPACE_SIZE) - (SPACE_SIZE * pStage->StageZnum / 2));
			//m_3DPolygon->Draw(m_Texture[1], matrix, color);
		}
	}

	//if (Frame % 60 < 30)
	//{
	//	cGap += 0.3f / 30.0f;
	//}
	//else
	//{
	//	cGap -= 0.3f / 30.0f;
	//}

	XMMATRIX world;
	if (edit)
	{
		VertexColor_4 color;

		if (select)
		{
			color.setAll(XMFLOAT4(1.0f, 0.5f, 0.0f, 0.8f));
			world = XMMatrixTranslation((selectPos.x * SPACE_SIZE) - (SPACE_SIZE * pStage->StageXnum / 2), 2.5f, (selectPos.z * SPACE_SIZE) - (SPACE_SIZE * pStage->StageZnum / 2));
			m_Yazirushi->Draw(world, color);
		}

		color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.8f));
		//カーソルの描画
		world = XMMatrixTranslation((m_CursorLocation.x * SPACE_SIZE) - (SPACE_SIZE * pStage->StageXnum / 2), 3.5f, (m_CursorLocation.z * SPACE_SIZE) - (SPACE_SIZE * pStage->StageZnum / 2));
		m_Yazirushi->Draw(world, color);
	}


	camera->SetViewPos(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->Draw();
}