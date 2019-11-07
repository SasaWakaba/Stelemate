#include "../common/main.h"
#include "../common/texture.h"
#include "../common/polygon.h"

#include "BattleSimu_UI.h"

#define TEX_WIDTH (100.0f)
#define TEX_HEIGHT (100.0f)

void CBattleSimu::Initialize()
{
	for (int i = 0; i < 4; i++)
	{
		m_Texture[i] = new CPolygon();
		m_Texture[i]->Initialize();
	}
	m_Texture[0]->Load("asset/texture/Status_HP000.png");
	m_Texture[1]->Load("asset/texture/Status_HP001.png");
	m_Texture[2]->Load("asset/texture/Status_HP002.png");
	m_Texture[3]->Load("asset/texture/Status_HP003.png");


	m_Pos.x = SCREEN_WIDTH / 5;
	m_Pos.z = SCREEN_HEIGHT / 2;

	bDraw = false;
}

void CBattleSimu::Finalize()
{
	for (int i = 0; i < 4; i++)
	{
		m_Texture[i]->Finalize();
		delete m_Texture[i];
	}
}

void CBattleSimu::Update()
{

}

void CBattleSimu::Draw()
{
	if (bDraw)
	{
		VertexColor_4 color{
			XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
			XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f),
			XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
			XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f),
		};

		float x = TEX_WIDTH * 1.5f;
		float y = TEX_HEIGHT / 2;
		m_Texture[1]->Draw(m_Pos.x - x, m_Pos.z, 0.0f, 0.0f, x * 2, y, x * 2, y);
		m_Texture[3]->Draw(m_Pos.x + x, m_Pos.z, 0.0f, 0.0f, x * 2, y, x * 2, y);

		x = TEX_WIDTH + (TEX_WIDTH / 13);
		y = TEX_HEIGHT / 3;
		m_Texture[0]->Draw(m_Pos.x - x, m_Pos.z, 0.0f, 0.0f, x * 2, y, x * 2, y, color);
		m_Texture[0]->Draw(m_Pos.x + x, m_Pos.z, 0.0f, 0.0f, x * 2, y, x * 2, y);
		m_Texture[2]->Draw(m_Pos.x, m_Pos.z, 0.0f, 0.0f, TEX_WIDTH, TEX_HEIGHT, TEX_WIDTH, TEX_HEIGHT);
	}
}