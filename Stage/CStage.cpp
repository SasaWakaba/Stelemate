#include "../common/main.h"




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
				//CStagePanel* panel;
				//panel = new CStagePanel(m_StageMap[z * m_Xnum + x].PanelPattarn, XMFLOAT3((x * SPACE_SIZE) - (SPACE_SIZE * m_Xnum/2), -0.5f, (z * SPACE_SIZE) - (SPACE_SIZE * m_Znum/2)));
				//panel->Initialize();
				//m_StagePanel.push_back(panel);
				if (m_StageMap[z * m_Xnum + x].bChar)
				{
					m_StageMap[z * m_Xnum + x].Charcter->Initialize();
					m_StageMap[z * m_Xnum + x].Charcter->SetLocation(XMFLOAT3((x * SPACE_SIZE) - (SPACE_SIZE * m_Xnum / 2), 1.0f, (z * SPACE_SIZE) - (SPACE_SIZE * m_Znum / 2)));
				}
			}
		}
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
}