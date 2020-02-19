#include "../common/main.h"
#include "../common/renderer.h"
#include "../common/texture.h"
#include "../common/TextureManager.h"
#include "CCube.h"
#include "CStagePanel.h"

#include "../common/model.h"
#include "../common/ModelAnimation.h"
#include "../common/ModelManager.h"

void CStagePanel::Initialize()
{
	switch (m_PanelPattarn)
	{
	case 1:
		m_Texture = CTextureManager::LoadTexture("asset/texture/grass01.jpg");
		break;
	case 2:
		m_Texture = CTextureManager::LoadTexture("asset/texture/forest.jpg");

		m_Model = CModelManager::LoadModel("asset/model/forest/treeplan1.fbx");
		break;
	}
	
	cube = new CCube();
	cube->Initialize();
}

void CStagePanel::Finalize()
{
	cube->Finalize();
	delete cube;
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
		CRenderer::SetAlphaTestEnable(true);
		world = XMMatrixScaling(0.03f, 0.03f, 0.03f);
		world *= XMMatrixRotationRollPitchYaw(90.0f, 0.0f, 0.0f);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y + 0.5f, m_Position.z);
		m_Model->Draw(world);
		CRenderer::SetAlphaTestEnable(false);
	}
}