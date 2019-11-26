#include "../common/main.h"
#include "../common/input.h"
#include "../common/polygon.h"
#include "../common/CDrawText.h"
#include "../common/Game_Object.h"
#include "Preparation_UI.h"

#define FRAME_W (300)
#define FRAME_H (175)

#define CURSOR_W (287.5f)
#define CURSOR_H (153)

#define TEXT_SIZE_BIG (125)
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
		if (m_Cursol < maxTex - 1)
		{
			m_Cursol = (SelectPre)(m_Cursol + 1);
		}
	}

	if (CInput::GetKeyTrigger(VK_SPACE))
	{

	}
	frame++;
}

void CPreparationUI::Draw()
{
	//”wŒi
	m_Texture[1]->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

	int frameX = SCREEN_WIDTH - FRAME_W / 2;
	static int star = 0;
	VertexColor_4 color;
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));

	switch (m_Cursol)
	{
	case CPreparationUI::Start:
		m_Texture[3]->Draw(frameX, SCREEN_HEIGHT / 5, star, 0, CURSOR_W, CURSOR_H, CURSOR_W, CURSOR_H, color);
		break;
	case CPreparationUI::Arrangement:
		m_Texture[3]->Draw(frameX, SCREEN_HEIGHT / 5 * 2, star, 0, CURSOR_W, CURSOR_H, CURSOR_W, CURSOR_H, color);
		break;
	case CPreparationUI::Employment:
		m_Texture[3]->Draw(frameX, SCREEN_HEIGHT / 5 * 3, star, 0, CURSOR_W, CURSOR_H, CURSOR_W, CURSOR_H, color);
		break;
	case CPreparationUI::Strengthen:
		m_Texture[3]->Draw(frameX, SCREEN_HEIGHT / 5 * 4, star, 0, CURSOR_W, CURSOR_H, CURSOR_W, CURSOR_H, color);
		break;
	}
	star++;
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	m_Texture[2]->Draw(frameX, SCREEN_HEIGHT / 5, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);
	m_Texture[2]->Draw(frameX, SCREEN_HEIGHT / 5 * 2, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);
	m_Texture[2]->Draw(frameX, SCREEN_HEIGHT / 5 * 3, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);
	m_Texture[2]->Draw(frameX, SCREEN_HEIGHT / 5 * 4, 0, 0, FRAME_W, FRAME_H, FRAME_W, FRAME_H, color);


	float textX = frameX - TEXT_SIZE_BIG / 3 * 2;
	float textY = TEXT_SIZE_BIG / 5 * 3;

	std::string text = "oŒ‚";
	m_Text[0]->DrawJpn(textX, SCREEN_HEIGHT / 5 - textY, TEXT_SIZE_BIG, TEXT_SIZE_BIG / 3 * 2, text, color);
	text = "”z’u";
	m_Text[0]->DrawJpn(textX, SCREEN_HEIGHT / 5 * 2 - textY, TEXT_SIZE_BIG, TEXT_SIZE_BIG / 3 * 2, text, color);
	text = "ŒÙ—p";
	m_Text[0]->DrawJpn(textX, SCREEN_HEIGHT / 5 * 3 - textY, TEXT_SIZE_BIG, TEXT_SIZE_BIG / 3 * 2, text, color);
	text = "‹­‰»";
	m_Text[0]->DrawJpn(textX, SCREEN_HEIGHT / 5 * 4 - textY, TEXT_SIZE_BIG, TEXT_SIZE_BIG / 3 * 2, text, color);
	
	//m_Text[1]->DrawJpn(frameX, SCREEN_HEIGHT / 5, TEXT_SIZE_SMALL, TEXT_SIZE_SMALL / 2, text, color);


	int cursor = 150;
	switch (m_Cursol)
	{
	case CPreparationUI::Start:
		m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, SCREEN_HEIGHT / 5 - cursor / 3, 0, 0, cursor, cursor, cursor, cursor, color);
		break;
	case CPreparationUI::Arrangement:
		m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, SCREEN_HEIGHT / 5 * 2 - cursor / 3, 0, 0, cursor, cursor, cursor, cursor, color);
		break;
	case CPreparationUI::Employment:
		m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, SCREEN_HEIGHT / 5 * 3 - cursor / 3, 0, 0, cursor, cursor, cursor, cursor, color);
		break;
	case CPreparationUI::Strengthen:
		m_Texture[0]->Draw(frameX - FRAME_W / 2 - cursor / 3, SCREEN_HEIGHT / 5 * 4 - cursor / 3, 0, 0, cursor, cursor, cursor, cursor, color);
		break;
	}
}