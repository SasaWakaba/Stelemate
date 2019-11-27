#include "../common/main.h"
#include "../common/renderer.h"
#include "../common/input.h"
#include "../common/polygon.h"
#include "../common/CDrawText.h"
#include "../common/Game_Object.h"

#include "../common/Scene.h"
#include "../GameSystem/CPreparation.h"
#include "Preparation_UI.h"

#define FRAME_W (360)
#define FRAME_H (210)

#define SUBFRAME_W (400)
#define SUBFRAME_H (145)

#define CURSOR_W (345)
#define CURSOR_H (183.6f)

#define TEXT_SIZE_BIG (90)
#define TEXT_SIZE_SMALL (50)
CPreparationUI::CPreparationUI()
{
	m_Text[0] = new CDrawText();
	m_Text[1] = new CDrawText();

	m_Text[0]->Set(TEXT_SIZE_BIG);
	m_Text[1]->Set(TEXT_SIZE_SMALL);
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
	m_Texture[0]->Load("asset/texture/select.png");
	m_Texture[1]->Load("asset/texture/PreparationUI000.png");
	m_Texture[2]->Load("asset/texture/PreparationUI001.png");
	m_Texture[3]->Load("asset/texture/PreparationUI002.png");
	m_Texture[4]->Load("asset/texture/PreparationUI003.png");

	m_Cursol = Arrangement;
	frame = 0;
}

void CPreparationUI::Finalize()
{
	for (int i = 0; i < maxTex; i++)
	{
		m_Texture[i]->Finalize();
		delete m_Texture[i];
	}
}

void CPreparationUI::Update()
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
			CPreparation::Change();
			break;
		case CPreparationUI::Arrangement:
			
			break;
		case CPreparationUI::Employment:
			
			break;
		case CPreparationUI::Strengthen:
			
			break;
		}
	}
	frame++;
}

void CPreparationUI::Draw()
{
	//背景
	m_Texture[1]->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

	int frameX = SCREEN_WIDTH - FRAME_W / 2;
	static int star = 0;
	VertexColor_4 color;
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));
	
	switch (m_Cursol)
	{
	case CPreparationUI::Start:
		m_Texture[3]->Draw(frameX, SCREEN_HEIGHT / 8, star, 0, CURSOR_W, CURSOR_H, CURSOR_W, CURSOR_H, color);
		break;
	case CPreparationUI::Arrangement:
		//m_Texture[3]->Draw(frameX, SCREEN_HEIGHT / 5 * 2, star, 0, CURSOR_W, CURSOR_H, CURSOR_W, CURSOR_H, color);
		break;
	case CPreparationUI::Employment:
		//m_Texture[3]->Draw(frameX, SCREEN_HEIGHT / 5 * 3, star, 0, CURSOR_W, CURSOR_H, CURSOR_W, CURSOR_H, color);
		break;
	case CPreparationUI::Strengthen:
		//m_Texture[3]->Draw(frameX, SCREEN_HEIGHT / 5 * 4, star, 0, CURSOR_W, CURSOR_H, CURSOR_W, CURSOR_H, color);
		break;
	}
	star++;
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	m_Texture[2]->Draw(frameX, SCREEN_HEIGHT / 8, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);


	m_Texture[4]->Draw(frameX, SCREEN_HEIGHT / 5 * 2, 0, 0, SUBFRAME_W, SUBFRAME_H, SUBFRAME_W, SUBFRAME_H, color);
	m_Texture[4]->Draw(frameX, SCREEN_HEIGHT / 5 * 3, 0, 0, SUBFRAME_W, SUBFRAME_H, SUBFRAME_W, SUBFRAME_H, color);
	m_Texture[4]->Draw(frameX, SCREEN_HEIGHT / 5 * 4, 0, 0, SUBFRAME_W, SUBFRAME_H, SUBFRAME_W, SUBFRAME_H, color);


	float textX = frameX - TEXT_SIZE_BIG / 3 * 2;
	float textY = TEXT_SIZE_BIG / 5 * 3;

	std::string text = "戦闘開始";
	m_Text[0]->DrawJpn(textX - TEXT_SIZE_BIG / 3 *2, SCREEN_HEIGHT / 8 - textY, TEXT_SIZE_BIG, TEXT_SIZE_BIG / 3 * 2, text, color);

	color.setAll(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	text = "配置";
	m_Text[0]->DrawJpn(textX, SCREEN_HEIGHT / 5 * 2 - textY, TEXT_SIZE_BIG, TEXT_SIZE_BIG / 3 * 2, text, color);
	text = "雇用";
	m_Text[0]->DrawJpn(textX, SCREEN_HEIGHT / 5 * 3 - textY, TEXT_SIZE_BIG, TEXT_SIZE_BIG / 3 * 2, text, color);
	text = "強化";
	m_Text[0]->DrawJpn(textX, SCREEN_HEIGHT / 5 * 4 - textY, TEXT_SIZE_BIG, TEXT_SIZE_BIG / 3 * 2, text, color);
	
	color.setAll(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	text = "Stage1";
	m_Text[1]->DrawJpn(0, 0, TEXT_SIZE_SMALL, TEXT_SIZE_SMALL / 2, text, color);

	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	int cursor = 125;
	static float pos = 1.0f;
	if (frame % 60 < 30)
	{
		pos -= 0.5f / 30;
	}
	else
	{
		pos += 0.5f / 30;
	}
	switch (m_Cursol)
	{
	case CPreparationUI::Start:
		m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, SCREEN_HEIGHT / 8 - cursor / 3 * pos, 0, 0, cursor, cursor, cursor, cursor, color);
		break;
	case CPreparationUI::Arrangement:
		m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, SCREEN_HEIGHT / 5 * 2 - cursor / 3 * pos, 0, 0, cursor, cursor, cursor, cursor, color);
		break;
	case CPreparationUI::Employment:
		m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, SCREEN_HEIGHT / 5 * 3 - cursor / 3 * pos, 0, 0, cursor, cursor, cursor, cursor, color);
		break;
	case CPreparationUI::Strengthen:
		m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, SCREEN_HEIGHT / 5 * 4 - cursor / 3 * pos, 0, 0, cursor, cursor, cursor, cursor, color);
		break;
	}
}