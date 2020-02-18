#include "../common/main.h"
#include "../common/input.h"
#include "../common/inputController.h"
#include "../common/Game_Object.h"
#include "../common/texture.h"
#include "../common/polygon.h"
#include "../common/CDrawText.h"
#include "../common/number.h"
#include "../common/manager.h"
#include <iostream>

#include "../GameSystem/WorldManager.h"
#include "../common/Scene.h"
#include "../common/CResult.h"
#include "Result_UI.h"

#define backOut(t, b, c, d) ((c) * (1 - (powf((1 - (t) / (d)), 3.0f) - (1 - (t) / (d)) * sinf(PI * (1 - (t) / (d))))) + (b))
#define quinticOut(t, b, c, d) ((c) * (1 - powf((1 - (t) / (d)), 5)) + (b))
#define elastic_out(t, b, c, d) ((c) * (1 - powf(2, (-10.0f * (t) / (d))) * sinf(13 * (PI / 2) * ((t) / (d) + 1)) + (b)))


#define NUMBER_SIZE (150.0f)
#define TEXT_SIZE (70.0f)

static float alpha = 1.0f;

void CResultUI::Initialize()
{
	for (int i = 0; i < RESULT_UI_NUM; i++)
	{
		m_Texture[i] = new CPolygon();
		m_Texture[i]->Initialize();
	}
	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	CRenderer::SetClearColor(color);
	m_Texture[0]->Load("asset/texture/ResultUI000.png");
	m_Texture[1]->Load("asset/texture/ResultUI001.png");
	m_Texture[2]->Load("asset/texture/ResultUI002.png");
	m_Texture[3]->Load("asset/texture/ResultUI003.png");
	m_Texture[4]->Load("asset/texture/ResultUI004.png");
	m_Texture[5]->Load("asset/texture/ResultUI005.png");
	m_Texture[6]->Load("asset/texture/ResultUI006.png");
	m_Texture[7]->Load("asset/texture/ResultUI007.png");

	m_Texture[8]->Load("asset/texture/titleUI005.png");
	m_Texture[9]->Load("asset/texture/titleUI006.png");
	m_Texture[10]->Load("asset/texture/black.png");
	m_Texture[11]->Load("asset/texture/titleUI007.png");

	ResultTitlePos = { -SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2 };
	UIbasePos = { SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2 };

	SelectPos[0] = { -SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3};
	SelectPos[1] = { -SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3 * 2 };


	number = new CNumber();
	number->Initialize();

	textAlpha[0] = 0.0f;
	textAlpha[1] = 0.0f;

	m_Text[0] = new CDrawText();
	m_Text[0]->Set(NUMBER_SIZE * 0.5f);
	m_Text[1] = new CDrawText();
	m_Text[1]->Set(TEXT_SIZE);

	for (int i = 0; i < 4; i++)
	{
		NumScale[i] = 0.0f;
	}
	frame = 0;
	Phase = 0;
	selectEnd = 0;

	alpha = 0.8f;
}

void CResultUI::Finalize()
{
	for (int i = 0; i < RESULT_UI_NUM; i++)
	{
		m_Texture[i]->Finalize();
		delete m_Texture[i];
	}
	m_Text[0]->UnSet();
	delete m_Text[0];
	m_Text[1]->UnSet();
	delete m_Text[1];
	number->Finalize();
}

void CResultUI::Update()
{
	int age = frame - StartFrame;
	switch (Phase)
	{
		case BackSet:
		case Heading:
			if (frame < 60)
			{
				UIbasePos.y = backOut(1.0f / 60.0f * frame, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT, 1.0f);
			}
			else
			{
				UIbasePos.y = SCREEN_HEIGHT / 2;
				if (textAlpha[0] < 1.0f)
				{
					textAlpha[0] = quinticOut(1.0f / 60.0f * (frame - 60), 0.0f, 1.0f, 1);
				}
				if (textAlpha[1] < 1.0f)
				{
					textAlpha[1] = quinticOut(1.0f / 60.0f * (frame - 90), 0.0f, 1.0f, 1);
				}
			}

			if (frame == 30)
			{
				Phase++;
				StartFrame = frame;
				age = frame - StartFrame;
			}

			if (Phase == Heading)
			{
				ResultTitlePos.x = quinticOut(1.0f / 60.0f * age, -SCREEN_WIDTH / 2, SCREEN_WIDTH, 1);
				ResultTitlePos.y = quinticOut(1.0f / 60.0f * age, -SCREEN_HEIGHT / 5, SCREEN_HEIGHT / 5 + SCREEN_HEIGHT / 5, 1);
				
				if (age > 60)
				{
					ResultTitlePos.x = SCREEN_WIDTH / 2;
					ResultTitlePos.y = SCREEN_HEIGHT / 5;
					if (textAlpha[1] == 1.0f)
					{
						StartFrame = frame;
						Phase++;
					}
				}
			}
			break;
		case Number:
			for (int i = 0; i < 4; i++)
			{
				NumScale[i] = elastic_out(age * (1.0f / 60), 0.0f, 1.0f, 1);
				age -= 10;
				if (age < 0) age = 0;
			}

			if (NumScale[3] == 1.0f)
			{
				//決定キー入力
				if (CInput::GetKeyTrigger(VK_SPACE) || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_A))
				{
					Phase++;
					StartFrame = frame;
					age = frame - StartFrame;
					if (WorldManager::GetParty().size() == 0 || WorldManager::GetParty().size() - WorldManager::GetResult()->DeadCount == 0)
					{
						SelectPos[1].y = SCREEN_HEIGHT / 2;
						selectEnd = 1;
					}
				}
			}
			break;
		case select:
			for (int i = 0; i < 2; i++)
			{
				SelectPos[i].x = quinticOut(1.0f / 60.0f * age, -SCREEN_WIDTH / 2, SCREEN_WIDTH, 1);
				if (SelectPos[i].x > SCREEN_WIDTH / 2)
				{
					SelectPos[i].x = SCREEN_WIDTH / 2;
				}
				age -= 10;
				if (age < 0) age = 0;
			}
			//決定キー入力
			if (CInput::GetKeyTrigger(VK_SPACE) || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_A))
			{
				Phase = end;
				CResult::Change(selectEnd);
				if (selectEnd == 0)
				{
					WorldManager::AddSoldierPoint(WorldManager::GetResult()->SubjugationCount - WorldManager::GetResult()->DeadCount);
					WorldManager::SetNowStageNum(WorldManager::GetNowStageNum() + 1);
				}
			}

			if (WorldManager::GetParty().size() - WorldManager::GetResult()->DeadCount != 0)
			{
				if (CInput::GetKeyTrigger('W') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_UP))
				{
					selectEnd = 0;
				}
				if (CInput::GetKeyTrigger('S') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_DOWN))
				{
					selectEnd = 1;
				}
			}
			break;
		case end:
			break;
	}
	frame++;
}

void CResultUI::Draw()
{
	float BaseW = SCREEN_WIDTH * 0.8f;
	float BaseH = BaseW * 0.6836f;
	VertexColor_4 color;
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	m_Texture[5]->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_WIDTH, XMConvertToRadians(frame * 0.1f), color);
	m_Texture[6]->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_WIDTH, XMConvertToRadians(-frame / 3 * 0.1f), color);
	m_Texture[7]->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_WIDTH, XMConvertToRadians(frame / 2 * 0.1f), color);


	m_Texture[1]->Draw(UIbasePos.x, UIbasePos.y, 0, 0, BaseW, BaseH, BaseW, BaseH);
	float rot = atan2f((SCREEN_HEIGHT / 5) - (-SCREEN_HEIGHT / 5), (SCREEN_WIDTH / 2) - (-SCREEN_WIDTH / 2));
	m_Texture[0]->Draw(ResultTitlePos.x, ResultTitlePos.y, 0, 0, SCREEN_WIDTH, SCREEN_WIDTH / 4, SCREEN_WIDTH, SCREEN_WIDTH / 4, rot, color);

	color.a = color.c = XMFLOAT4(0.0f, 0.0f, 0.0f,textAlpha[0]);
	color.b = color.d = XMFLOAT4(0.0f, 0.0f, 0.0f,textAlpha[1]);
	m_Texture[2]->Draw(UIbasePos.x - BaseW / 2 + BaseW * 0.244f,					UIbasePos.y - 20.0f,					0, 0, BaseH / 7 * 3, BaseH / 7, BaseH / 7 * 3, BaseH / 7, color);//0.244
	m_Texture[3]->Draw(UIbasePos.x - BaseW / 2 + BaseW * 0.244f + BaseH / 7,		UIbasePos.y + BaseH / 7 - 10.0f,		0, 0, BaseH / 7 * 5, BaseH / 7, BaseH / 7 * 5, BaseH / 7, color);

	if (WorldManager::GetParty().size() - WorldManager::GetResult()->DeadCount != 0)
	{
		m_Texture[4]->Draw(UIbasePos.x - BaseW / 2 + BaseW * 0.244f + BaseH / 7 / 2,	UIbasePos.y + BaseH / 7 * 2,	0, 0, BaseH / 7 * 4, BaseH / 7, BaseH / 7 * 4, BaseH / 7, color);
		m_Text[0]->DrawEng(UIbasePos.x + BaseW / 5 + NUMBER_SIZE / 2, UIbasePos.y + BaseH / 7 * 2, NUMBER_SIZE * 0.5f, NUMBER_SIZE * 0.5f / 3 * 2, "SP", color);
	}

	color.setAll(XMFLOAT4(1.0f, 0.0f, 0.0f, 0.9f));
	if (WorldManager::GetResult()->SubjugationCount > 9)
	{
		int num = WorldManager::GetResult()->SubjugationCount;
		for (int i = 0; num % 10 != 0; i++)
		{
			number->Draw(UIbasePos.x + BaseW / 5 + (NUMBER_SIZE / 3 * 2) * i, UIbasePos.y - 20.0f, NUMBER_SIZE * NumScale[0], NUMBER_SIZE * NumScale[0], num % 10, color);
			num /= 10;
		}
	}
	else
	{
		number->Draw(UIbasePos.x + BaseW / 5, UIbasePos.y - 20.0f, NUMBER_SIZE * NumScale[0], NUMBER_SIZE * NumScale[0], WorldManager::GetResult()->SubjugationCount, color);
	}

	color.setAll(XMFLOAT4(0.0f, 1.0f, 0.0f, 0.9f));
	if (WorldManager::GetParty().size() - WorldManager::GetResult()->DeadCount > 9)
	{
		int num = WorldManager::GetParty().size() - WorldManager::GetResult()->DeadCount;
		for(int i = 0;num % 10 != 0; i++)
		{
			number->Draw(UIbasePos.x + BaseW / 5 + (NUMBER_SIZE / 3 * 2) * i, UIbasePos.y + BaseH / 7 - 10.0f, NUMBER_SIZE * NumScale[1], NUMBER_SIZE * NumScale[1], num % 10, color);
			num /= 10;
		}
	}
	else
	{
		number->Draw(UIbasePos.x + BaseW / 5, UIbasePos.y + BaseH / 7 - 10.0f, NUMBER_SIZE * NumScale[1], NUMBER_SIZE * NumScale[1], WorldManager::GetParty().size() - WorldManager::GetResult()->DeadCount, color);
	}

	if (WorldManager::GetParty().size() - WorldManager::GetResult()->DeadCount != 0)
	{
		color.setAll(XMFLOAT4(0.0f, 0.0f, 1.0f, 0.9f));
		int Score = WorldManager::GetResult()->SubjugationCount - WorldManager::GetResult()->DeadCount;
		if (Score > 9)
		{
			int num = Score;
			for (int i = 0; num % 10 != 0; i++)
			{
				number->Draw(UIbasePos.x + BaseW / 5 + (NUMBER_SIZE / 3 * 2) * i, UIbasePos.y + BaseH / 7 * 2, NUMBER_SIZE * NumScale[3], NUMBER_SIZE * NumScale[3], num % 10, color);
				num /= 10;
			}
		}
		else
		{
			number->Draw(UIbasePos.x + BaseW / 5, UIbasePos.y + BaseH / 7 * 2, NUMBER_SIZE * NumScale[3], NUMBER_SIZE * NumScale[3], Score, color);
		}
	}

	if (Phase == select || Phase == end)
	{
		color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));
		m_Texture[10]->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, color);

		if (WorldManager::GetParty().size() == 0 || WorldManager::GetParty().size() - WorldManager::GetResult()->DeadCount == 0)
		{
			m_Texture[9]->Draw(SelectPos[1].x, SelectPos[1].y, 0, 0, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2 / 5, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2 / 5);
			color.setAll(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
			std::string text = "ゲームを終了してタイトルへ戻る";
			m_Text[1]->DrawJpn(SelectPos[1].x - (TEXT_SIZE / 3 * 2) * text.size() / 4, SelectPos[1].y - TEXT_SIZE / 3 * 2, TEXT_SIZE, TEXT_SIZE / 3 * 2, text, color);
		}
		else
		{
			m_Texture[8]->Draw(SelectPos[0].x, SelectPos[0].y, 0, 0, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2 / 5, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2 / 5);
			m_Texture[9]->Draw(SelectPos[1].x, SelectPos[1].y, 0, 0, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2 / 5, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2 / 5);
			std::string text = "次のステージへ進む";
			m_Text[1]->DrawJpn(SelectPos[0].x - (TEXT_SIZE / 3 * 2) * text.size() / 4, SelectPos[0].y - TEXT_SIZE / 3 * 2, TEXT_SIZE, TEXT_SIZE / 3 * 2, text, color);
			text = "ゲームを終了してタイトルへ戻る";
			m_Text[1]->DrawJpn(SelectPos[1].x - (TEXT_SIZE / 3 * 2) * text.size() / 4, SelectPos[1].y - TEXT_SIZE / 3 * 2, TEXT_SIZE, TEXT_SIZE / 3 * 2, text, color);
		}

		if (frame % 60 < 30)
		{
			alpha -= 0.5f / 30;
		}
		else
		{
			alpha += 0.5f / 30;
		}
		color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, alpha));

		if (selectEnd == 0)
		{
			m_Texture[11]->Draw(SelectPos[0].x, SelectPos[0].y, 0, 0, SCREEN_WIDTH / 2 * 1.04f, SCREEN_WIDTH / 2 / 5 * 1.2f, SCREEN_WIDTH / 2 * 1.04f, SCREEN_WIDTH / 2 / 5 * 1.2f, color);
		}
		else
		{
			m_Texture[11]->Draw(SelectPos[1].x, SelectPos[1].y, 0, 0, SCREEN_WIDTH / 2 * 1.04f, SCREEN_WIDTH / 2 / 5 * 1.2f, SCREEN_WIDTH / 2 * 1.04f, SCREEN_WIDTH / 2 / 5 * 1.2f, color);
		}
	}
}