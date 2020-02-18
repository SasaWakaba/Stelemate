#include "../common/main.h"
#include "../common/input.h"
#include "../common/inputController.h"
#include "../common/Game_Object.h"
#include "../common/texture.h"
#include "../common/polygon.h"
#include "../common/model.h"

#include "../common/Scene.h"
#include "../common/CTitle.h"
#include "../Audio/audio_clip.h"
#include "GameModeSelect.h"

#include "TitleMenu_UI.h"


void CTitleMenu::Initialize()
{
	m_Polygon[Title_Logo] = new CPolygon();
	m_Polygon[Title_Logo]->Initialize();
	m_Polygon[Title_Logo]->Load("asset/texture/title.png");

	m_Polygon[PressSpace] = new CPolygon();
	m_Polygon[PressSpace]->Initialize();
	m_Polygon[PressSpace]->Load("asset/texture/titleUI000.png");

	m_Polygon[Menu_0] = new CPolygon();
	m_Polygon[Menu_0]->Initialize();
	m_Polygon[Menu_0]->Load("asset/texture/titleUI001.png");

	m_Polygon[Menu_1] = new CPolygon();
	m_Polygon[Menu_1]->Initialize();
	m_Polygon[Menu_1]->Load("asset/texture/titleUI002_0.png");

	m_Polygon[Menu_2] = new CPolygon();
	m_Polygon[Menu_2]->Initialize();
	m_Polygon[Menu_2]->Load("asset/texture/titleUI003.png");

	m_Polygon[Menu_3] = new CPolygon();
	m_Polygon[Menu_3]->Initialize();
	m_Polygon[Menu_3]->Load("asset/texture/titleUI004.png");

	m_Polygon[6] = new CPolygon();
	m_Polygon[6]->Initialize();
	m_Polygon[6]->Load("asset/texture/black.png");

	select = Title;

	m_Ok = new CAudioClip();
	m_Ok->Load("asset/audio/decision.wav");
	//PRESS=============================
	PressAlpha = 1.0f;
	TitleAlpha = 0.0f;
	Frame = 0;
	bDown = false;
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
	m_Count = 0;
	m_PosTitle.x = SCREEN_WIDTH / 2;
	m_PosTitle.y = 0.0f;
	PressWait = false;
	//==================================

	SelectEffect = 0.0f;

	SelectNum = 0;
	m_PosSelect[0].y = SCREEN_HEIGHT / 2;
	m_PosSelect[0].x = SCREEN_WIDTH - 150.0f;

	m_PosSelect[1].y = SCREEN_HEIGHT / 2 + 70.0f;
	m_PosSelect[1].x = SCREEN_WIDTH - 100.0f;

	m_PosSelect[2].y = SCREEN_HEIGHT / 2 + 140.0f;
	m_PosSelect[2].x = SCREEN_WIDTH - 75.0f;

	ModeSelect = new CGameModeSelect();

}

void CTitleMenu::Finalize()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_Polygon[i] != nullptr)
		{
			m_Polygon[i]->Finalize();
			delete m_Polygon[i];
		}
	}
	m_Ok->Unload();
	delete m_Ok;

}

void CTitleMenu::Update()
{
	//É^ÉCÉgÉãç~Ç¡ÇƒÇ≠ÇÈÇ‚Ç¬
	{
		if (TitleAlpha < 1.0f && !bDown)
		{
			TitleAlpha += 1.0f / 120.0f;
		}
		else
		{
			TitleAlpha = 1.0f;
			bDown = true;
		}
		float Defolt_Y = 0.0f + (sin(-PI / 2 + PI / 120 * m_Count) + 1) / 2 * (SCREEN_HEIGHT / 3);
		m_PosTitle.y = Defolt_Y;

		if (m_Count < 120) {
			m_Count++;
		}
	}


	if (bDown)
	{
		switch (select)
		{
		case CTitleMenu::Title:
			{
				if (!PressWait)
				{
					if (PressAlpha > 0.0f)
					{
						PressAlpha -= 1.0f / 30.0f;
					}
					else
					{
						PressWait = true;
					}
				}
				else
				{
					if (PressAlpha < 1.0f)
					{
						PressAlpha += 1.0f / 30.0f;
					}
					else
					{
						PressWait = false;
					}
				}
			}
			if (CInput::GetKeyTrigger(VK_SPACE) || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_A))
			{
				m_Ok->Play(false);
				select = Select;
			}
			break;

		case CTitleMenu::Select:
			if (CInput::GetKeyTrigger(VK_SPACE) || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_A))
			{
				m_Ok->Play(false);
				switch (SelectNum)
				{
				case 0:
					//CTitle::Change();
					select = Mode;
					break;

				case 1:
					break;

				case 2:
					EndGaming();
					break;
				}
			}
			if (CInput::GetKeyTrigger('W')|| CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_UP))
			{
				if (SelectNum > 0)
				{
					SelectNum-=2;
				}
			}

			if (CInput::GetKeyTrigger('S') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_DOWN))
			{
				if (SelectNum < 2)
				{
					SelectNum+=2;
				}
			}

			switch (SelectNum)
			{
			case 0:
				m_PosSelect[0].y = SCREEN_HEIGHT / 2;
				m_PosSelect[0].x = SCREEN_WIDTH - 150.0f;
				m_PosSelect[2].y = SCREEN_HEIGHT / 2 + 70.0f;
				m_PosSelect[2].x = SCREEN_WIDTH - 75.0f;

				//m_PosSelect[1].y = SCREEN_HEIGHT / 2 + 70.0f;
				//m_PosSelect[1].x = SCREEN_WIDTH - 50.0f;

				//m_PosSelect[2].y = SCREEN_HEIGHT / 2 + 140.0f;
				//m_PosSelect[2].x = SCREEN_WIDTH - 75.0f;
				break;
			case 1:
				m_PosSelect[0].y = SCREEN_HEIGHT / 2 - 70.0f;
				m_PosSelect[0].x = SCREEN_WIDTH - 100.0f;

				m_PosSelect[1].y = SCREEN_HEIGHT / 2;
				m_PosSelect[1].x = SCREEN_WIDTH - 100.0f;

				m_PosSelect[2].y = SCREEN_HEIGHT / 2 + 70.0f;
				m_PosSelect[2].x = SCREEN_WIDTH - 75.0f;
				break;
			case 2:
				//m_PosSelect[0].y = SCREEN_HEIGHT / 2 - 140.0f;
				//m_PosSelect[0].x = SCREEN_WIDTH - 100.0f;

				//m_PosSelect[1].y = SCREEN_HEIGHT / 2 - 70.0f;
				//m_PosSelect[1].x = SCREEN_WIDTH - 50.0f;

				m_PosSelect[0].y = SCREEN_HEIGHT / 2 - 70.0f;
				m_PosSelect[0].x = SCREEN_WIDTH - 100.0f;
				m_PosSelect[2].y = SCREEN_HEIGHT / 2;
				m_PosSelect[2].x = SCREEN_WIDTH - 150.0f;
				break;
			}
			SelectEffect += 1.0f;
			break;

		case CTitleMenu::Mode:
			ModeSelect->Update();
			if (CInput::GetKeyTrigger('Q') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_B))
			{
				select = Select;
			}
			break;
		default:
			break;
		}
	}

	//Frame++;
}

void CTitleMenu::Draw()
{
	VertexColor_4 color;
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.3f));
	m_Polygon[6]->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, color);
	switch (select)
	{
	case CTitleMenu::Title:
		VertexColor_4 colorLogo;
		colorLogo.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, TitleAlpha));

		m_Polygon[Title_Logo]->Draw(m_PosTitle.x, m_PosTitle.y, 0.0f, 0.0f, TITLELOGO_WIDTH, TITLELOGO_HEIGHT, TITLELOGO_WIDTH, TITLELOGO_HEIGHT, colorLogo);

		if (bDown)
		{
			VertexColor_4 colorPress;
			colorPress.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, PressAlpha));
			m_Polygon[PressSpace]->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5 * 4, 0.0f, 0.0f, 600.0f, 70.0f, 600.0f, 70.0f, colorPress);
		}

		break;

	case CTitleMenu::Select:
	{
		VertexColor_4 colorSelect;
		colorSelect.a = colorSelect.c = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
		colorSelect.b = colorSelect.d = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		m_Polygon[Menu_3]->Draw(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT / 2, 0.0f + SelectEffect, 0.0f, 300.0f, 35.0f, 300.0f, 35.0f, colorSelect);

		VertexColor_4 colorMenu;
		colorMenu.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		m_Polygon[Menu_0]->Draw(m_PosSelect[0].x, m_PosSelect[0].y, 0.0f, 0.0f, 200.0f, 35.0f, 200.0f, 35.0f);
		m_Polygon[Menu_2]->Draw(m_PosSelect[2].x, m_PosSelect[2].y, 0.0f, 0.0f, 150.0f, 35.0f, 150.0f, 35.0f);
		//m_Polygon[Menu_1]->Draw(m_PosSelect[1].x, m_PosSelect[1].y, 0.0f, 0.0f, 100.0f, 35.0f, 100.0f, 35.0f);
		//m_Polygon[Menu_2]->Draw(m_PosSelect[2].x, m_PosSelect[2].y, 0.0f, 0.0f, 150.0f, 35.0f, 150.0f, 35.0f);

		break;
	}
	case CTitleMenu::Mode:
	{
		ModeSelect->Draw();
		break;
	}
	}
}