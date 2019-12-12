#include "../common/main.h"
#include "../common/MeshField.h"
#include "../common/ModelAnimation.h"


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
					m_StageMap[z * m_Xnum + x].Charcter->Initialize();
					m_StageMap[z * m_Xnum + x].Charcter->SetLocation(XMFLOAT3((x * SPACE_SIZE) - (SPACE_SIZE * m_Xnum / 2), 0.0f, (z * SPACE_SIZE) - (SPACE_SIZE * m_Znum / 2)));
				}
			}
		}
	}
	m_Meshfield = new CMeshField();
	m_Meshfield->Initialize(m_Xnum * SPACE_SIZE * 3, m_Znum * SPACE_SIZE * 2, m_Xnum * 3, m_Znum * 2);

	m_Model[0] = new CModelAnimation();
	m_Model[0]->Load("asset/model/wooden watch tower2.fbx");

	m_Model[1] = new CModelAnimation();
	m_Model[1]->Load("asset/model/forest/treeplan1.fbx");
}

void CStage::Finalize()
{
	for (int z = 0; z < m_Znum; z++)
	{
		for (int x = 0; x < m_Xnum; x++)
		{
			if (m_StageMap[z * m_Xnum + x].bChar)
			{
				m_StageMap[z * m_Xnum + x].Charcter->Finalize();
				delete m_StageMap[z * m_Xnum + x].Charcter;
				m_StageMap[z * m_Xnum + x].Charcter = nullptr;
				m_StageMap[z * m_Xnum + x].bChar = false;
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

	m_Model[0]->UnLoad();
	delete m_Model[0];
	m_Model[1]->UnLoad();
	delete m_Model[1];
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
	for (CStagePanel* panel : m_StagePanel)
	{
		panel->Draw();
	}

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

	m_Meshfield->SetRotation(XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_Meshfield->SetPosition(XMFLOAT3(SPACE_SIZE * m_Xnum - SPACE_SIZE / 2, 0.0f, SPACE_SIZE * m_Znum * 1.5f - SPACE_SIZE /2));
	m_Meshfield->Draw();
	m_Meshfield->SetPosition(XMFLOAT3(-(SPACE_SIZE * m_Xnum + SPACE_SIZE / 2), 0.0f, -(SPACE_SIZE * m_Znum * 1.5f + SPACE_SIZE / 2)));
	m_Meshfield->Draw();

	m_Meshfield->SetRotation(XMFLOAT3(0.0f, XMConvertToRadians(90.0f), 0.0f));
	m_Meshfield->SetPosition(XMFLOAT3(-(SPACE_SIZE * m_Znum * 1.5f + SPACE_SIZE / 2), 0.0f, SPACE_SIZE * m_Xnum - SPACE_SIZE / 2));
	m_Meshfield->Draw();
	m_Meshfield->SetPosition(XMFLOAT3(SPACE_SIZE * m_Znum * 1.5f - SPACE_SIZE / 2, 0.0f, -(SPACE_SIZE * m_Xnum - SPACE_SIZE / 2)));
	m_Meshfield->Draw();

	XMMATRIX world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
	world *= XMMatrixTranslation(-(SPACE_SIZE * (m_Xnum + 4) / 2), 0.0f, -(SPACE_SIZE * (m_Znum + 4) / 2));
	m_Model[0]->Draw(world);

	world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
	world *= XMMatrixTranslation((SPACE_SIZE * (m_Xnum + 4) / 2), 0.0f, (SPACE_SIZE * (m_Znum + 4) / 2));
	m_Model[0]->Draw(world);

	for (int z = 0; z < 1; z++)
	{
		for (int x = 1; x < (m_Xnum + 4); x++)
		{
			world = XMMatrixScaling(0.05f, 0.05f, 0.05f);
			world *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
			world *= XMMatrixTranslation((x * SPACE_SIZE) -(SPACE_SIZE * (m_Xnum + 4) / 2), 0.0f, (z * SPACE_SIZE) -(SPACE_SIZE * (m_Znum + 4) / 2));
			m_Model[1]->Draw(world);
		}
	}

}