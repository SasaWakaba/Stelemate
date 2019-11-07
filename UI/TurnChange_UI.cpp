#include "../common/main.h"
#include "../common/Game_Object.h"
#include "../common/texture.h"
#include "../common/polygon.h"

#include "TurnChange_UI.h"

void CTurnChangeUI::Initialize()
{
	m_bDrawPL = false;
	m_bDrawEne = false;

	pos = 0.0f;
	m_Count = 0;

	m_Polygon[0] = new CPolygon();
	m_Polygon[0]->Initialize();
	m_Polygon[0]->Load("asset/texture/PlayerPhase.png");

	m_Polygon[1] = new CPolygon();
	m_Polygon[1]->Initialize();
	m_Polygon[1]->Load("asset/texture/EnemyPhase.png");
}

void CTurnChangeUI::Finalize()
{
	for (int i = 0; i < 2; i++)
	{
		m_Polygon[i]->Finalize();
		delete m_Polygon[i];
	}
}

void CTurnChangeUI::Update()
{
	if (m_bDrawEne || m_bDrawPL)
	{

		if (m_Count < 120) {
			pos = -TURNCHANGE_UI_WIDTH + (sin(-PI / 2 + PI / 120 * m_Count) + 1) / 2 * (SCREEN_WIDTH / 2 + TURNCHANGE_UI_WIDTH);
			m_Count += 2;
		}
		else if (m_Count < 240)
		{
			pos = (SCREEN_WIDTH + TURNCHANGE_UI_WIDTH) - (sin(-PI / 2 + PI / 120 * m_Count) + 1) / 2 * (SCREEN_WIDTH / 2 + TURNCHANGE_UI_WIDTH);
			m_Count += 2;
		}
		else
		{
			m_bDrawEne = false;
			m_bDrawPL = false;
		}
	}
}

void CTurnChangeUI::Draw()
{
	if (m_bDrawPL)
	{
		m_Polygon[0]->Draw(pos, SCREEN_HEIGHT / 2, 0.0f, 0.0f, TURNCHANGE_UI_WIDTH, TURNCHANGE_UI_HEIGHT, TURNCHANGE_UI_WIDTH, TURNCHANGE_UI_HEIGHT);
	}
	if (m_bDrawEne)
	{
		m_Polygon[1]->Draw(pos, SCREEN_HEIGHT / 2, 0.0f, 0.0f, TURNCHANGE_UI_WIDTH, TURNCHANGE_UI_HEIGHT, TURNCHANGE_UI_WIDTH, TURNCHANGE_UI_HEIGHT);
	}
}