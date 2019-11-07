#include "../common/main.h"
#include "../common/texture.h"
#include "CCube.h"
#include "CStagePanel.h"

#include "../common/model.h"
#include "../mesh/ModelLoader.h"

void CStagePanel::Initialize()
{
	switch (m_PanelPattarn)
	{
	case 1:
		m_Texture = new CTexture();
		m_Texture->LoadTex("asset/texture/grass01.jpg");
		break;
	case 2:
		m_Texture = new CTexture();
		m_Texture->LoadTex("asset/texture/forest.jpg");

		m_Model = new CModelLoader();
		m_Model->Load("asset/model/forest.obj");
		break;
	}
	
	cube = new CCube();
	cube->Initialize();
}

void CStagePanel::Finalize()
{
	m_Texture->Unload();
	delete m_Texture;
	cube->Finalize();
	delete cube;

	if (m_Model != nullptr)
	{
		m_Model->Close();
		delete m_Model;
	}
}

void CStagePanel::Draw()
{
	XMMATRIX world;
	world = XMMatrixScaling(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE);											//Šg‘åEk¬
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);							//‰ñ“]
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);				//ˆÚ“®
	cube->Draw(&world, m_Texture);

	if (m_PanelPattarn == 2)
	{
		world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
		world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y + 0.5f, m_Position.z);
		//m_Model->Draw(&world);
	}
}