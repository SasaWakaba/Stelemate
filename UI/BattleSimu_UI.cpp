#include "../common/main.h"
#include "../common/texture.h"
#include "../common/polygon.h"
#include "../common/CDrawText.h"
#include "../Charcter/CCharcterBase.h"
#include "../common/Billboard.h"

#include "BattleSimu_UI.h"

#define TEX_WIDTH (600.0f)
#define TEX_HEIGHT (600.0f)

#define TEXT_BIG (TEX_WIDTH * 0.1f)
#define TEXT_SMALL (TEXT_BIG * 0.7f)


void CBattleSimu::Initialize()
{
	for (int i = 0; i < MAX_TEXNUM; i++)
	{
		m_Texture[i] = new CPolygon();
		m_Texture[i]->Initialize();
	}
	m_Texture[0]->Load("asset/texture/Status_HP000.png");
	m_Texture[1]->Load("asset/texture/Status_HP001.png");
	m_Texture[2]->Load("asset/texture/Status_HP002.png");
	m_Texture[3]->Load("asset/texture/Status_HP003.png");
	m_Texture[4]->Load("asset/texture/Status_Back000.png");

	m_Text[0] = new CDrawText();
	m_Text[1] = new CDrawText();

	m_Text[0]->Set(TEXT_BIG);
	m_Text[1]->Set(TEXT_SMALL);

	m_Pos.x = SCREEN_WIDTH / 5;
	m_Pos.y = SCREEN_HEIGHT / 2;

	m_Char[0] = nullptr;
	m_Char[1] = nullptr;

	bDraw = false;
}

void CBattleSimu::Finalize()
{
	for (int i = 0; i < MAX_TEXNUM; i++)
	{
		m_Texture[i]->Finalize();
		delete m_Texture[i];
	}

	m_Text[0]->UnSet();
	m_Text[1]->UnSet();
}

void CBattleSimu::Update()
{

}

void CBattleSimu::Draw()
{
	if (bDraw)
	{
		VertexColor_4 color{
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		};



		float BarY = m_Pos.y - TEX_HEIGHT * 0.125f;
		m_Texture[1]->Draw(m_Pos.x, BarY, 0, 0, TEX_WIDTH, TEX_HEIGHT * 0.08f, TEX_WIDTH, TEX_HEIGHT * 0.08f);
		color.a = color.c = { 0.0f, 0.0f, 0.8f, 1.0f };
		color.b = color.d = { 0.0f, 0.0f, 0.1f, 1.0f };
		m_Texture[0]->Draw(m_Pos.x - TEX_WIDTH * 0.208f, BarY, 0, 0, TEX_WIDTH * 0.3f, TEX_HEIGHT * 0.04f, TEX_WIDTH * 0.3f, TEX_HEIGHT * 0.04f, color);
		color.a = color.c = { 0.1f, 0.0f, 0.0f, 1.0f };
		color.b = color.d = { 0.8f, 0.0f, 0.0f, 1.0f };
		m_Texture[0]->Draw(m_Pos.x + TEX_WIDTH * 0.208f, BarY, 0, 0, TEX_WIDTH * 0.3f, TEX_HEIGHT * 0.04f, TEX_WIDTH * 0.3f, TEX_HEIGHT * 0.04f, color);

		m_Texture[2]->Draw(m_Pos.x, BarY, 0, 0, TEX_WIDTH * 0.72f, TEX_HEIGHT * 0.044f, TEX_WIDTH * 0.72f, TEX_HEIGHT * 0.044f);
		
		m_Texture[4]->Draw(m_Pos.x, m_Pos.y, 0, 0, TEX_WIDTH, TEX_HEIGHT, TEX_WIDTH, TEX_HEIGHT);

		if (m_Char[0] != nullptr)
		{

		}
		if (m_Char[1] != nullptr)
		{

		}
	}
}