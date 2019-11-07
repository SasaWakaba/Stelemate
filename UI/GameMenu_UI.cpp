#include "../common/main.h"
#include "../common/Game_Object.h"
#include "../common/texture.h"
#include "../common/polygon.h"
#include "../common/input.h"

#include "GameMenu_UI.h"


void CGameMenu_UI::Initialize()
{
	m_Polygon[0] = new CPolygon();
	m_Polygon[0]->Initialize();
	m_Polygon[0]->Load("asset/texture/Attack.png");

	m_Polygon[1] = new CPolygon();
	m_Polygon[1]->Initialize();
	m_Polygon[1]->Load("asset/texture/Heal.png");

	m_Polygon[2] = new CPolygon();
	m_Polygon[2]->Initialize();
	m_Polygon[2]->Load("asset/texture/Stay.png");

	m_Polygon[3] = new CPolygon();
	m_Polygon[3]->Initialize();
	m_Polygon[3]->Load("asset/texture/select.png");

	m_Polygon[4] = new CPolygon();
	m_Polygon[4]->Initialize();
	m_Polygon[4]->Load("asset/texture/selectWindow.png");

	for (int i = 0; i < NUM_UI; i++)
	{
		m_Pos[i].x = 0.0f;
		m_Pos[i].y = 0.0f;
	}

	m_bDraw = false;

}

void CGameMenu_UI::Finalize()
{
	for (int i = 0; i < NUM_UI; i++)
	{
		m_Polygon[i]->Finalize();
		delete m_Polygon[i];
	}
}

void CGameMenu_UI::Update()
{
	if (m_bDraw)
	{
		for (int i = 0; i < NUM_UI; i++)
		{
			m_Pos[i].x = SCREEN_WIDTH / 6 * 5;
		}
		float Defolt_Y = -150.0f + (sin(-PI / 2 + PI / 120 * m_Count) + 1) / 2 * (SCREEN_HEIGHT / 2 + 100.0f);

		float menu_size = GAMEMENU_UI_HEIGHT * m_DrawCnt + m_DrawCnt * 5.0f;

		if (m_Atk)
		{
			m_Pos[0].y = Defolt_Y + (menu_size / m_DrawCnt * 1) - (menu_size / 2);
		}
		
		if (m_Heal)
		{
			if (m_Atk)
			{
				m_Pos[1].y = Defolt_Y + (menu_size / m_DrawCnt * 2) - (menu_size / 2);
			}
			else
			{
				m_Pos[1].y = Defolt_Y + (menu_size / m_DrawCnt * 1) - (menu_size / 2);
			}
		}

		if (m_Stay)
		{
			switch (m_DrawCnt)
			{
			case 0:
				break;
			case 1:
				m_Pos[2].y = Defolt_Y + (menu_size / m_DrawCnt * 1) - (menu_size / 2);
				break;
			case 2:
				m_Pos[2].y = Defolt_Y + (menu_size / m_DrawCnt * 2) - (menu_size / 2);
				break;
			case 3:
				m_Pos[2].y = Defolt_Y + (menu_size / m_DrawCnt * 3) - (menu_size / 2);
				break;
			}
		}

		if (m_Count < 120) {
			m_Count += 2;
		}
		else
		{
			if (CInput::GetKeyTrigger('S'))
			{
				switch (m_MenuPos)
				{
				case 0:
					if (!m_Heal)
					{
						m_MenuPos += 2;
					}
					else
					{
						m_MenuPos++;
					}
					break;
				case 2:
					break;
				default:
					m_MenuPos++;
					break;
				}
			}
			if (CInput::GetKeyTrigger('W'))
			{
				switch (m_MenuPos)
				{
				case 0:
					break;
				case 1:
					if (!m_Atk)
					{
						break;
					}
					else
					{
						m_MenuPos--;
					}
					break;
				case 2:
					if (!m_Heal)
					{
						if (m_Atk)
						{
							m_MenuPos -= 2;
						}
					}
					else 
					{
						m_MenuPos--;
					}
					break;
				default:
					m_MenuPos--;
					break;
				}
			}
		}
	}
}

void CGameMenu_UI::Draw()
{
	if (m_bDraw)
	{

		if (m_Atk)
		{
			m_Polygon[0]->Draw(m_Pos[0].x, m_Pos[0].y, 0.0f, 0.0f, GAMEMENU_UI_WIDTH, GAMEMENU_UI_HEIGHT, GAMEMENU_UI_WIDTH, GAMEMENU_UI_HEIGHT);
		}
		if (m_Heal)
		{
			m_Polygon[1]->Draw(m_Pos[1].x, m_Pos[1].y, 0.0f, 0.0f, GAMEMENU_UI_WIDTH, GAMEMENU_UI_HEIGHT, GAMEMENU_UI_WIDTH, GAMEMENU_UI_HEIGHT);
		}
		if (m_Stay)
		{
			m_Polygon[2]->Draw(m_Pos[2].x, m_Pos[2].y, 0.0f, 0.0f, GAMEMENU_UI_WIDTH, GAMEMENU_UI_HEIGHT, GAMEMENU_UI_WIDTH, GAMEMENU_UI_HEIGHT);
		}

		m_Polygon[4]->Draw(m_Pos[m_MenuPos].x, m_Pos[m_MenuPos].y, 0.0f, 0.0f, 165.0f, 90.0f, 165.0f, 90.0f);
		m_Polygon[3]->Draw(m_Pos[m_MenuPos].x - 100.0f, m_Pos[m_MenuPos].y - 30.0f, 0.0f, 0.0f, 90.0f, 90.0f, 90.0f, 90.0f);
	}
}

void CGameMenu_UI::Set(bool atk, bool heal, bool stay)
{
	if (!m_bDraw)
	{
		m_Count = 0;
		if (!atk)
		{
			if (!heal)
			{
				m_MenuPos = 2;
			}
			else
			{
				m_MenuPos = 1;
			}
		}
		else
		{
			m_MenuPos = 0;
		}
		if (atk)  m_DrawCnt++;
		if (heal) m_DrawCnt++;
		if (stay) m_DrawCnt++;
		m_Atk	= atk;
		m_Heal	= heal;
		m_Stay	= stay;
		m_bDraw = true;
	}
}

void CGameMenu_UI::reset()
{
	m_Count = 0;
	m_MenuPos = 0;
	m_DrawCnt = 0;

	m_Atk	= false;
	m_Heal	= false;
	m_Stay	= false;
	m_bDraw = false;

	for (int i = 0; i < NUM_UI; i++)
	{
		m_Pos[i].x = 0.0f;
		m_Pos[i].y = 0.0f;
	}
}