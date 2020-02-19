#include "../common/main.h"
#include "../common/MeshField.h"
#include "../common/ModelAnimation.h"
#include "../common/CCircleShadow.h"
#include "../common/ModelManager.h"

#include "CStagePanel.h"
#include "CStage.h"



void CStage::Initialize()
{

	m_StagePanel[0] = new CStagePanel(1, XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_StagePanel[0]->Initialize();

	m_StagePanel[1] = new CStagePanel(2, XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_StagePanel[1]->Initialize();

	for (int z = 0; z < m_Znum; z++)
	{
		for (int x = 0; x < m_Xnum; x++)
		{
			if (m_StageMap[z * m_Xnum + x].PanelPattarn != 0)
			{
				if (m_StageMap[z * m_Xnum + x].bChar)
				{
					/*m_StageMap[z * m_Xnum + x].Charcter->Initialize();*/
					m_StageMap[z * m_Xnum + x].Charcter->SetLocation(XMFLOAT3((x * SPACE_SIZE) - (SPACE_SIZE * m_Xnum / 2), 0.0f, (z * SPACE_SIZE) - (SPACE_SIZE * m_Znum / 2)));
				}
			}
		}
	}
	m_Meshfield = new CMeshField();
	m_Meshfield->Initialize(m_Xnum * SPACE_SIZE * 3, m_Znum * SPACE_SIZE * 2, m_Xnum * 3, m_Znum * 2);

	m_Model[0] = CModelManager::LoadModel("asset/model/wooden watch tower2.fbx");

	m_Model[1] = CModelManager::LoadModel("asset/model/forest/treeplan1.fbx");

	m_Model[2] = new CModelAnimation();
	m_Model[2]->InstanceEnable(true, XMFLOAT4(5, 5, 40, 0.0f));
	m_Model[2]->Load("asset/model/forest/treeplan1.fbx");

	m_Shadow = new CCircleShadow();
	m_Shadow->Initialize();

	XMMATRIX world;
	for (int x = 1; x < (m_Xnum + 4); x++)
	{
		world = XMMatrixScaling(0.05f, 0.05f, 0.05f);
		world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(rand() % 360), 0.0f);
		world *= XMMatrixTranslation(- (SPACE_SIZE * (m_Znum + 4) / 2), 0.0f, -(x * SPACE_SIZE) + (SPACE_SIZE * (m_Xnum + 4) / 2));
		m_Forest.push_back(world);

		world = XMMatrixScaling(0.05f, 0.05f, 0.05f);
		world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(rand() % 360), 0.0f);
		world *= XMMatrixTranslation((SPACE_SIZE * (m_Znum + 4) / 2) - SPACE_SIZE, 0.0f, -(x * SPACE_SIZE) + (SPACE_SIZE * (m_Xnum + 4) / 2) - SPACE_SIZE);
		m_Forest.push_back(world);

		world = XMMatrixScaling(0.05f, 0.05f, 0.05f);
		world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(rand()%360), 0.0f);
		world *= XMMatrixTranslation((x * SPACE_SIZE) - (SPACE_SIZE * (m_Xnum + 4) / 2), 0.0f,- (SPACE_SIZE * (m_Znum + 4) / 2));
		m_Forest.push_back(world);

		world = XMMatrixScaling(0.05f, 0.05f, 0.05f);
		world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(rand() % 360), 0.0f);
		world *= XMMatrixTranslation((x * SPACE_SIZE) -(SPACE_SIZE * (m_Xnum + 4) / 2) - SPACE_SIZE, 0.0f,(SPACE_SIZE * (m_Znum + 4) / 2) - SPACE_SIZE);
		m_Forest.push_back(world);
	}
}

void CStage::Finalize()
{
	for (int z = 0; z < m_Znum; z++)
	{
		for (int x = 0; x < m_Xnum; x++)
		{
			if (m_StageMap[z * m_Xnum + x].bChar)
			{
				if (!m_StageMap[z * m_Xnum + x].Charcter->GetAlly())
				{
					m_StageMap[z * m_Xnum + x].Charcter->Finalize();
					delete m_StageMap[z * m_Xnum + x].Charcter;
					m_StageMap[z * m_Xnum + x].Charcter = nullptr;
					m_StageMap[z * m_Xnum + x].bChar = false;
				}
				else
				{
					m_StageMap[z * m_Xnum + x].Charcter = nullptr;
					m_StageMap[z * m_Xnum + x].bChar = false;
				}
			}
		}
	}

	for (CStagePanel* panel : m_StagePanel)
	{
		panel->Finalize();
		delete panel;
	}

	m_Meshfield->Finalize();
	delete m_Meshfield;

	m_Model[2]->UnLoad();
	delete m_Model[2];

	m_Shadow->Finalize();
	delete m_Shadow;

	m_Forest.clear();
}

void CStage::Update()
{
	for (int z = 0; z < m_Znum; z++)
	{
		for (int x = 0; x < m_Xnum; x++)
		{
			if (m_StageMap[z * m_Xnum + x].bChar)
			{
				m_StageMap[z * m_Xnum + x].Charcter->Update();
				if (m_StageMap[z * m_Xnum + x].Charcter->Destroy())
				{
					m_StageMap[z * m_Xnum + x].bChar = false;
				}
			}
		}
	}
}

void CStage::Draw()
{
	//for (CStagePanel* panel : m_StagePanel)
	//{
	//	panel->Draw();
	//}

	XMMATRIX world;

	for (int z = 0; z < m_Znum; z++)
	{
		for (int x = 0; x < m_Xnum; x++)
		{
			if (m_StageMap[z * m_Xnum + x].PanelPattarn == 1)
			{
				m_StagePanel[0]->SetPosition(XMFLOAT3((x * SPACE_SIZE) - (SPACE_SIZE * m_Xnum / 2), -0.5f, (z * SPACE_SIZE) - (SPACE_SIZE * m_Znum / 2)));
				m_StagePanel[0]->Draw();
			}

			if (m_StageMap[z * m_Xnum + x].PanelPattarn == 2)
			{
				m_StagePanel[1]->SetPosition(XMFLOAT3((x * SPACE_SIZE) - (SPACE_SIZE * m_Xnum / 2), -0.5f, (z * SPACE_SIZE) - (SPACE_SIZE * m_Znum / 2)));
				m_StagePanel[1]->Draw();
			}
			
			if (m_StageMap[z * m_Xnum + x].bChar)
			{
				m_StageMap[z * m_Xnum + x].Charcter->Draw();
			}
		}
	}

	//”ÕŠO
	{
		m_Meshfield->SetRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
		m_Meshfield->SetPosition(XMFLOAT3(SPACE_SIZE * m_Xnum - SPACE_SIZE / 2, 0.0f, SPACE_SIZE * m_Znum * 1.5f - SPACE_SIZE / 2));
		m_Meshfield->Draw();
		m_Meshfield->SetPosition(XMFLOAT3(-(SPACE_SIZE * m_Xnum + SPACE_SIZE / 2), 0.0f, -(SPACE_SIZE * m_Znum * 1.5f + SPACE_SIZE / 2)));
		m_Meshfield->Draw();

		m_Meshfield->SetRotation(XMFLOAT3(0.0f, XMConvertToRadians(90.0f), 0.0f));
		m_Meshfield->SetPosition(XMFLOAT3(-(SPACE_SIZE * m_Znum * 1.5f + SPACE_SIZE / 2), 0.0f, SPACE_SIZE * m_Xnum - SPACE_SIZE / 2));
		m_Meshfield->Draw();
		m_Meshfield->SetPosition(XMFLOAT3(SPACE_SIZE * m_Znum * 1.5f - SPACE_SIZE / 2, 0.0f, -(SPACE_SIZE * m_Xnum - SPACE_SIZE / 2)));
		m_Meshfield->Draw();

		for (int z = 0; z < m_Znum; z++)
		{
			for (int x = 0; x < m_Xnum; x++)
			{
				if (m_StageMap[z * m_Xnum + x].PanelPattarn == 2)
				{
					world = XMMatrixScaling(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE);
					world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
					world *= XMMatrixTranslation((x * SPACE_SIZE) - (SPACE_SIZE * m_Xnum / 2), -0.49f + SPACE_SIZE / 2, (z * SPACE_SIZE) - (SPACE_SIZE * m_Znum / 2));
					m_Shadow->Draw(world);
				}
				if (m_StageMap[z * m_Xnum + x].bChar)
				{
					world = XMMatrixScaling(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE);
					world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
					world *= XMMatrixTranslation(m_StageMap[z * m_Xnum + x].Charcter->GetLocation().x, -0.49f + SPACE_SIZE / 2, m_StageMap[z * m_Xnum + x].Charcter->GetLocation().z);
					m_Shadow->Draw(world);
				}
			}
		}



		world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
		world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		world *= XMMatrixTranslation(-(SPACE_SIZE * (m_Xnum + 4) / 2), 0.0f, -(SPACE_SIZE * (m_Znum + 4) / 2));
		m_Model[0]->Draw(world);

		world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
		world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		world *= XMMatrixTranslation((SPACE_SIZE * (m_Xnum + 4) / 2) - SPACE_SIZE, 0.0f, (SPACE_SIZE * (m_Znum + 4) / 2) - SPACE_SIZE);
		m_Model[0]->Draw(world);

		for (XMMATRIX pos : m_Forest)
		{
			CRenderer::SetAlphaTestEnable(true);
			m_Model[1]->Draw(pos);
			CRenderer::SetAlphaTestEnable(false);
			XMMATRIX sh;
			sh = XMMatrixScaling(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE);
			sh *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
			sh *= XMMatrixTranslation(pos.r[3].m128_f32[0], 0.01f, pos.r[3].m128_f32[2]);
			m_Shadow->Draw(sh);
		}

		//world = XMMatrixScaling(0.05f, 0.05f, 0.05f);
		//world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		//world *= XMMatrixTranslation((SPACE_SIZE * (m_Xnum + 4) / 2) + SPACE_SIZE, 0.0f, -(SPACE_SIZE * (m_Znum + 4) / 2));
		//m_Model[2]->Draw(world);

		//world = XMMatrixScaling(0.05f, 0.05f, 0.05f);
		//world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		//world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90.0f), 0.0f);
		//world *= XMMatrixTranslation(-(SPACE_SIZE * (m_Xnum + 4)) + SPACE_SIZE, 0.0f, -(SPACE_SIZE * (m_Znum + 4) / 2) - SPACE_SIZE);
		//m_Model[2]->Draw(world);

		//world = XMMatrixScaling(0.05f, 0.05f, 0.05f);
		//world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		//world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90.0f), 0.0f);
		//world *= XMMatrixTranslation(-(SPACE_SIZE * (m_Xnum + 4)) , 0.0f, (SPACE_SIZE * (m_Znum + 4)) + SPACE_SIZE * 4);
		//m_Model[2]->Draw(world);
	}
}