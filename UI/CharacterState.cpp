#include "../common/main.h"
#include "../common/renderer.h"
#include "../common/Game_Object.h"
#include "../common/texture.h"
#include "../common/polygon.h"
#include "../Stage/CStage.h"

#include "../common/CDrawText.h"
#include "../common/CScore.h"
#include "CharacterState.h"

#define STATUS_WINDOW_WIDTH (768 / 3 * 2)
#define STATUS_WINDOW_HEIGHT (160 / 3 * 2)

#define GAP_WINDOW_Y (SCREEN_HEIGHT / 15)
#define GAP_WINDOW_X (SCREEN_WIDTH / 25)

PanelState* CCharacterState::m_PanelState;

void CCharacterState::Initialize()
{
	m_StateNum = new CScore();
	m_StateNum->Initialize(2, 30, 30);

	m_CharacterState[0] = new CPolygon();
	m_CharacterState[0]->Initialize();
	m_CharacterState[0]->Load("asset/texture/DataStatus000.png");

	m_PanelState = nullptr;
}

void CCharacterState::Finalize()
{
	m_StateNum->Finalize();
	delete m_StateNum;

	for (int i = 0; i < STATE_TEX_NUM; i++)
	{
		m_CharacterState[i]->Finalize();
		delete m_CharacterState[i];
	}
}

void CCharacterState::Update()
{

}

void CCharacterState::Draw()
{
	if (m_PanelState != nullptr)
	{
		if (m_PanelState->bChar)
		{
			VertexColor_4 color{
			XMFLOAT4(1.0f,1.0f,1.0f,1.0f),
			XMFLOAT4(1.0f,1.0f,1.0f,1.0f),
			XMFLOAT4(1.0f,1.0f,1.0f,1.0f),
			XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
			};

			float x = STATUS_WINDOW_WIDTH / 2 + GAP_WINDOW_X;
			float y = SCREEN_HEIGHT - ((STATUS_WINDOW_HEIGHT / 2) + GAP_WINDOW_Y);

			m_CharacterState[0]->Draw(x, y, 0, 0, STATUS_WINDOW_WIDTH, STATUS_WINDOW_HEIGHT, STATUS_WINDOW_WIDTH, STATUS_WINDOW_HEIGHT);

			m_StateNum->Draw(-STATUS_WINDOW_WIDTH / 4 + x, -10 + y, m_PanelState->Charcter->GetStatus()->HP);
			m_StateNum->Draw(x, -10 + y, m_PanelState->Charcter->nowHP);
			m_StateNum->Draw(STATUS_WINDOW_WIDTH / 5 - 15 + x, -10 + y, m_PanelState->Charcter->GetStatus()->HP);

			CDrawText::Draw(-STATUS_WINDOW_WIDTH / 3.5 + x, y - 5, 30, m_PanelState->Charcter->GetWeapon()->name);
		}
	}
}