#include "../common/main.h"
#include "../common/renderer.h"
#include "../GameSystem/WorldManager.h"
#include "../common/input.h"
#include "../common/polygon.h"
#include "../common/CDrawText.h"
#include "../common/Game_Object.h"
#include "../common/number.h"
#include "../Charcter/CPlayerManager.h"
#include "../Charcter/CJob.h"

#include "../common/Scene.h"
#include "../GameSystem/CPreparation.h"
#include "Employment_UI.h"

#include "Preparation_UI.h"

#define FRAME_H ((float)SCREEN_HEIGHT * 0.194f)
#define FRAME_W ((float)FRAME_H * 1.72f)

#define FRAME_GAP ((float)SCREEN_HEIGHT * 0.028f)

#define SUBFRAME_W (FRAME_W * 0.95f)
#define SUBFRAME_H (FRAME_H * 0.9f)


#define TEXT_SIZE_BIG (90.0f)
#define TEXT_SIZE_SMALL (70.0f)

static float pos = 1.0f;
static float star = 0;

CPreparationUI::CPreparationUI()
{
	m_Text[0] = new CDrawText();
	m_Text[1] = new CDrawText();

	m_Text[0]->Set((int)TEXT_SIZE_BIG);
	m_Text[1]->Set((int)TEXT_SIZE_SMALL);
}

CPreparationUI::~CPreparationUI()
{
	m_Text[0]->UnSet();
	delete m_Text[0];
	m_Text[1]->UnSet();
	delete m_Text[1];
}

void CPreparationUI::Initialize()
{
	for (int i = 0; i < maxTex; i++)
	{
		m_Texture[i] = new CPolygon();
		m_Texture[i]->Initialize();
	}

	m_Number = new CNumber();
	m_Number->Initialize();

	m_Emp = new CEmploymentUI();
	m_Emp->Initialize();

	m_Texture[0]->Load("asset/texture/select.png");
	m_Texture[1]->Load("asset/texture/PreparationUI000.png");
	m_Texture[2]->Load("asset/texture/PreparationUI001.png");
	m_Texture[3]->Load("asset/texture/PreparationUI002.png");
	m_Texture[4]->Load("asset/texture/PreparationUI003.png");
	m_Texture[5]->Load("asset/texture/PreparationUI004.png");
	m_Texture[6]->Load("asset/texture/PreparationUI005.png");

	m_Texture[7]->Load("asset/texture/titleUI008.png");

	m_Cursol = Arrangement;
	frame = 0;
	pos = 1.0f;
	star = 0;
}

void CPreparationUI::Finalize()
{
	for (int i = 0; i < maxTex; i++)
	{
		m_Texture[i]->Finalize();
		delete m_Texture[i];
	}
	m_Number->Finalize();
	delete m_Number;

	m_Emp->Finalize();
	delete m_Emp;
}

void CPreparationUI::Update()
{
	if (m_Emp->GetPhase() == 0)
	{
		if (CInput::GetKeyTrigger('W'))
		{
			if (m_Cursol > 0)
			{
				m_Cursol = (SelectPre)(m_Cursol - 1);
			}
		}

		if (CInput::GetKeyTrigger('S'))
		{
			if (m_Cursol < 3)
			{
				m_Cursol = (SelectPre)(m_Cursol + 1);
			}
		}

		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			switch (m_Cursol)
			{
			case CPreparationUI::Start:
				if (WorldManager::GetParty().size() > 0)
				{
					CPreparation::Change();
				}
				break;
			case CPreparationUI::Arrangement:
				break;
			case CPreparationUI::Employment:
				m_Emp->StartEmp();
				break;
			case CPreparationUI::Strengthen:

				break;
			}
		}
	}
	m_Emp->Update(frame);
	frame++;
}

void CPreparationUI::Draw()
{
	float enclosureY = FRAME_H / 2 + FRAME_GAP / 6;
	float enclosureAddY = FRAME_H + FRAME_GAP / 6;

	float frameX = (SCREEN_WIDTH - FRAME_W / 2);



	VertexColor_4 color;

	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));

	float textX = frameX - TEXT_SIZE_BIG / 3 * 2;
	float textY = TEXT_SIZE_BIG / 5 * 3;

	//背景
	m_Texture[1]->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

	m_Texture[7]->Draw(SCREEN_WIDTH / 3, SCREEN_HEIGHT - (SCREEN_HEIGHT * 1.11f * 0.1f), 0, 0, SCREEN_HEIGHT * 1.11f, SCREEN_HEIGHT * 1.11f * 0.1f, SCREEN_HEIGHT * 1.11f, SCREEN_HEIGHT * 1.11f * 0.1f);

	//カーソル後ろの紫
	switch (m_Cursol)
	{
	case CPreparationUI::Start:
		m_Texture[3]->Draw(frameX, enclosureY, star, 0, SUBFRAME_W, SUBFRAME_H, SUBFRAME_W, SUBFRAME_H, color);
		break;
	case CPreparationUI::Arrangement:
		m_Texture[3]->Draw(frameX, enclosureY + enclosureAddY * 2, star, 0, SUBFRAME_W, SUBFRAME_H, SUBFRAME_W, SUBFRAME_H, color);
		break;
	case CPreparationUI::Employment:
		m_Texture[3]->Draw(frameX, enclosureY + enclosureAddY * 3, star, 0, SUBFRAME_W, SUBFRAME_H, SUBFRAME_W, SUBFRAME_H, color);
		break;
	case CPreparationUI::Strengthen:
		m_Texture[3]->Draw(frameX, enclosureY + enclosureAddY * 4, star, 0, SUBFRAME_W, SUBFRAME_H, SUBFRAME_W, SUBFRAME_H, color);
		break;
	}
	star+=2;

	//メニューの枠
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	m_Texture[2]->Draw(frameX, enclosureY, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);

	m_Texture[4]->Draw(frameX, enclosureY + enclosureAddY, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);

	m_Texture[2]->Draw(frameX, enclosureY + enclosureAddY * 2, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);

	m_Texture[2]->Draw(frameX, enclosureY + enclosureAddY * 3, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);

	m_Texture[2]->Draw(frameX, enclosureY + enclosureAddY * 4, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);


	m_Texture[6]->Draw(frameX - SCREEN_HEIGHT / 4 - SCREEN_HEIGHT / 16, SCREEN_HEIGHT / 2, 0, star, SCREEN_HEIGHT / 8, SCREEN_HEIGHT, SCREEN_HEIGHT / 8, SCREEN_HEIGHT * 4);

	m_Texture[5]->Draw(frameX - SCREEN_HEIGHT / 4, SCREEN_HEIGHT / 2, 0, 0, SCREEN_HEIGHT / 4, SCREEN_HEIGHT, SCREEN_HEIGHT / 4, SCREEN_HEIGHT);



	//メニュー文字
	color.setAll(XMFLOAT4(0.662f, 0.647f, 0.615f, 1.0f));

	std::string text = "戦闘開始";
	m_Text[0]->DrawJpn((int)(textX - TEXT_SIZE_BIG / 3 *2), (int)(enclosureY - textY), (int)TEXT_SIZE_BIG, (int)TEXT_SIZE_BIG / 3 * 2, text, color);

	text = "配置";
	m_Text[0]->DrawJpn((int)textX, (int)(enclosureY + enclosureAddY * 2 - textY), (int)TEXT_SIZE_BIG, (int)(TEXT_SIZE_BIG / 3 * 2), text, color);
	text = "雇用";
	m_Text[0]->DrawJpn((int)textX, (int)(enclosureY + enclosureAddY * 3 - textY), (int)TEXT_SIZE_BIG, (int)(TEXT_SIZE_BIG / 3 * 2), text, color);
	text = "強化";
	m_Text[0]->DrawJpn((int)textX, (int)(enclosureY + enclosureAddY * 4 - textY), (int)TEXT_SIZE_BIG, (int)(TEXT_SIZE_BIG / 3 * 2), text, color);
	
	
	text = std::string("Day") + std::to_string(WorldManager::GetNowStageNum() + 1);
	m_Text[1]->DrawEng((int)(frameX - (TEXT_SIZE_SMALL / 2 * (text.size() - 1)) / 2), (int)(enclosureY + enclosureAddY - FRAME_H / 2), (int)TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 2, text, color);


	m_Number->Draw((int)(frameX + FRAME_W / 4), (int)(enclosureY + enclosureAddY + FRAME_H / 4), TEXT_SIZE_SMALL, TEXT_SIZE_SMALL, WorldManager::GetSoldierPoint(), color);


	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	float cursor = 125.0f;

	if (frame % 60 < 30)
	{
		pos -= 0.5f / 30;
	}
	else
	{
		pos += 0.5f / 30;
	}

	if (m_Emp->GetPhase() == 0)
	{
		//カーソル羽ペン
		switch (m_Cursol)
		{
		case CPreparationUI::Start:
			m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, enclosureY - cursor / 3 * pos, 0, 0, cursor, cursor, cursor, cursor, color);
			break;
		case CPreparationUI::Arrangement:
			m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, enclosureY + enclosureAddY * 2 - cursor / 3 * pos, 0, 0, cursor, cursor, cursor, cursor, color);
			break;
		case CPreparationUI::Employment:
			m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, enclosureY + enclosureAddY * 3 - cursor / 3 * pos, 0, 0, cursor, cursor, cursor, cursor, color);
			break;
		case CPreparationUI::Strengthen:
			m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, enclosureY + enclosureAddY * 4 - cursor / 3 * pos, 0, 0, cursor, cursor, cursor, cursor, color);
			break;
		}
	}

	m_Emp->Draw();
}