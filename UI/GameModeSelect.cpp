#include "../common/main.h"
#include "../common/input.h"
#include "../common/texture.h"
#include "../common/polygon.h"
#include "../common/CDrawText.h"
#include "../GameSystem/WorldManager.h"
#include "../common/Scene.h"
#include "../common/CTitle.h"

#include "GameModeSelect.h"

#define SELECT_W (800)
#define SELECT_H (160)
#define ENCLOSUE (SELECT_H * 0.1f)

#define ICON_SIZE (100)

#define TEXT_BIG_SIZE (70)
#define TEXT_SMALL_SIZE (30)


CGameModeSelect::CGameModeSelect()
{
	for (int i = 0; i < 5; i++)
	{
		m_Texture[i] = new CPolygon();
		m_Texture[i]->Initialize();
	}
	m_Texture[0]->Load("asset/texture/select.png");
	m_Texture[1]->Load("asset/texture/titleUI005.png");
	m_Texture[2]->Load("asset/texture/titleUI006.png");
	m_Texture[3]->Load("asset/texture/titleUI007.png");
	m_Texture[4]->Load("asset/texture/titleUI008.png");

	m_Text[0] = new CDrawText();
	m_Text[1] = new CDrawText();

	m_Text[0]->Set(TEXT_BIG_SIZE);
	m_Text[1]->Set(TEXT_SMALL_SIZE);

	m_select = Casual;
	frame = 0;
}

CGameModeSelect::~CGameModeSelect()
{
	for (int i = 0; i < 5; i++)
	{
		m_Texture[i]->Finalize();
		delete m_Texture[i];
	}

	m_Text[0]->UnSet();
	delete m_Text[0];
	m_Text[1]->UnSet();
	delete m_Text[1];
}

void CGameModeSelect::Update()
{
	if (CInput::GetKeyTrigger('W'))
	{
		m_select = Casual;
	}

	if (CInput::GetKeyTrigger('S'))
	{
		m_select = Classic;
	}

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		WorldManager::SetGameMode(m_select);
		CTitle::Change();
	}
	frame++;
}

void CGameModeSelect::Draw()
{
	VertexColor_4 color;
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	float PosX = SCREEN_WIDTH / 2;
	float AposY = SCREEN_HEIGHT / 3;
	float BposY = SCREEN_HEIGHT / 3 * 2;

	m_Texture[1]->Draw(PosX, AposY, 0, 0, SELECT_W, SELECT_H, SELECT_W, SELECT_H, color);
	m_Texture[2]->Draw(PosX, BposY, 0, 0, SELECT_W, SELECT_H, SELECT_W, SELECT_H, color);
	m_Texture[4]->Draw(PosX, SCREEN_HEIGHT - 75, 0, 0, 1300, 90, 1300, 90, color);

	float TextWidth = TEXT_BIG_SIZE - TEXT_BIG_SIZE / 3;
	float TextPosX = PosX - SELECT_W / 2 + TEXT_BIG_SIZE / 2;

	color.setAll(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	std::string text = "カジュアル";
	m_Text[0]->DrawJpn(TextPosX, AposY - SELECT_H / 2 + TEXT_BIG_SIZE / 2, TEXT_BIG_SIZE, TextWidth, text, color);
	text = "クラシック";
	m_Text[0]->DrawJpn(TextPosX, BposY - SELECT_H / 2 + TEXT_BIG_SIZE / 2, TEXT_BIG_SIZE, TextWidth, text, color);

	text = "失った仲間は戦闘終了後に復活";
	m_Text[1]->DrawJpn(PosX - TEXT_SMALL_SIZE * 2, AposY - TEXT_SMALL_SIZE, TEXT_SMALL_SIZE, TEXT_SMALL_SIZE, text, color);
	text = "お手軽なモード";
	m_Text[1]->DrawJpn(PosX, AposY, TEXT_SMALL_SIZE, TEXT_SMALL_SIZE, text, color);
	text = "モードを選択してください";
	m_Text[1]->DrawJpn(PosX - (TEXT_SMALL_SIZE - TEXT_SMALL_SIZE / 4) * 6, SCREEN_HEIGHT - 75, TEXT_SMALL_SIZE, TEXT_SMALL_SIZE - TEXT_SMALL_SIZE / 4, text, color);

	text = "失った仲間は戻らない";
	m_Text[1]->DrawJpn(PosX, BposY - TEXT_SMALL_SIZE, TEXT_SMALL_SIZE, TEXT_SMALL_SIZE, text, color);
	text = "じっくり考えるモード";
	m_Text[1]->DrawJpn(PosX, BposY, TEXT_SMALL_SIZE, TEXT_SMALL_SIZE, text, color);


	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	text = "カジュアル";
	m_Text[0]->DrawJpn(TextPosX - 3, AposY - SELECT_H / 2 + TEXT_BIG_SIZE / 2 - 3, TEXT_BIG_SIZE, TextWidth, text, color);
	text = "クラシック";
	m_Text[0]->DrawJpn(TextPosX - 3, BposY - SELECT_H / 2 + TEXT_BIG_SIZE / 2 - 3, TEXT_BIG_SIZE, TextWidth, text, color);

	//選択肢の囲いと矢印
	{
		static float alpha = 1.0f;
		if (frame % 60 < 30)
		{
			alpha -= 0.5f / 30;
		}
		else
		{
			alpha += 0.5f / 30;
		}
		color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, alpha));
		switch (m_select)
		{
		case Casual:
			m_Texture[3]->Draw(PosX, AposY, 0, 0, SELECT_W + ENCLOSUE, SELECT_H + ENCLOSUE, SELECT_W + ENCLOSUE, SELECT_H + ENCLOSUE, color);
			m_Texture[0]->Draw(PosX - SELECT_W / 2 - ICON_SIZE / 3, AposY - ICON_SIZE / 2 + 30 * alpha, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			break;
		case Classic:
			m_Texture[3]->Draw(PosX, BposY, 0, 0, SELECT_W + ENCLOSUE, SELECT_H + ENCLOSUE, SELECT_W + ENCLOSUE, SELECT_H + ENCLOSUE, color);
			m_Texture[0]->Draw(PosX - SELECT_W / 2 - ICON_SIZE / 3, BposY - ICON_SIZE / 2 + 30 * alpha, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			break;
		}
	}
}