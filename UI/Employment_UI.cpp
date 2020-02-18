#include "../common/main.h"
#include "../common/math.h"
#include "../common/renderer.h"
#include "../GameSystem/WorldManager.h"
#include "../common/input.h"
#include "../common/inputController.h"
#include "../common/polygon.h"
#include "../common/CDrawText.h"
#include "../common/Game_Object.h"
#include "../common/number.h"
#include "../Charcter/CPlayerManager.h"
#include "../Charcter/CCharacterData.h"
#include "../Charcter/CJob.h"
#include "../Stage/CStageData.h"

#include <iostream>

#include "Employment_UI.h"

#define ease_out(t, b, c, d) ((c) * (-(powf(2.0f, (-10.0f * (t) / (d)))) + 1) + (b))

#define elastic_out(t, b, c, d) ((c) * (1 - powf(2, (-10.0f * (t) / (d))) * sinf(13 * (PI / 2) * ((t) / (d) + 1)) + (b)))

#define TEXT_SIZE_BIG (90.0f)
#define TEXT_SIZE_SMALL (70.0f)
#define TEXT_SIZE_ENG (50.0f)

#define TEXTURE_WID (800.0f)
#define TEXTURE_WID_2 (530.0f)
#define TEXTURE_HEI (546.875f)
#define TEXTURE_HEI_2 (700.0f)

#define ICON_SIZE (64.0f)

static float pos = 1.0f;
static float uvc = 0.0f;

CEmploymentUI::CEmploymentUI()
{
	m_Text[0] = new CDrawText();
	m_Text[1] = new CDrawText();
	m_Text[2] = new CDrawText();

	m_Text[0]->Set((int)TEXT_SIZE_BIG);
	m_Text[1]->Set((int)TEXT_SIZE_SMALL);
	m_Text[2]->Set((int)TEXT_SIZE_ENG);
}
CEmploymentUI::~CEmploymentUI()
{
	m_Text[0]->UnSet();
	delete m_Text[0];
	m_Text[1]->UnSet();
	delete m_Text[1];
	m_Text[2]->UnSet();
	delete m_Text[2];
}

void CEmploymentUI::StartEmp() {
	Phase = 1;
	selectJob = 0;
	StartFrame = Frame;
}

void CEmploymentUI::Initialize()
{
	for (int i = 0; i < maxTex; i++)
	{
		m_Texture[i] = new CPolygon();
		m_Texture[i]->Initialize();
		m_TexPos[i] = SCREEN_HEIGHT + SCREEN_HEIGHT / 2;
	}

	for (int i = 0; i < 5; i++)
	{
		m_Icon[i] = new CPolygon();
		m_Icon[i]->Initialize();
		std::string path = "asset/texture/Icon00" + std::to_string(i) + ".png";
		m_Icon[i]->Load(path.c_str());
	}


	m_Number = new CNumber();
	m_Number->Initialize();

	m_Texture[0]->Load("asset/texture/select.png");
	m_Texture[1]->Load("asset/texture/PreparationUI006.png");
	m_Texture[2]->Load("asset/texture/PreparationUI007.png");
	m_Texture[3]->Load("asset/texture/PreparationUI002.png");

	m_Texture[4]->Load("asset/texture/PreparationUI008.png");

	m_AddData = nullptr;
	pos = 1.0f;
	Frame = 0;
	Phase = 0;
	selectJob = 0;
	uvc = 0.0f;

	for (int i = 0; i < 7; i++)
	{
		m_JudgeScale[i] = 0.0f;
	}
}

void CEmploymentUI::Finalize()
{
	for (int i = 0; i < maxTex; i++)
	{
		m_Texture[i]->Finalize();
		delete m_Texture[i];
	}

	for (int i = 0; i < 5; i++)
	{
		m_Icon[i]->Finalize();
		delete m_Icon[i];
	}
	m_Number->Finalize();
	delete m_Number;
}

void CEmploymentUI::Update(int frame)
{
	Frame = frame;
	int age = Frame - StartFrame;
	switch (Phase)
	{
	case notDraw:
		break;
	case moveSelect:
		m_TexPos[0] = ease_out((age * (1.0f / 30)), SCREEN_HEIGHT + SCREEN_HEIGHT / 2, -SCREEN_HEIGHT, 1);
		if (age == 30)
		{
			Phase++;
		}
		break;
	case Select:
		if (CInput::GetKeyTrigger('W') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_UP))
		{
			if (selectJob > 0)
			{
				selectJob--;
			}
		}

		if (CInput::GetKeyTrigger('S') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			if (selectJob < 5)
			{
				selectJob++;
			}
		}

		if (CInput::GetKeyTrigger(VK_SPACE) || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_A))
		{
			switch (selectJob)
			{
			case Swordman:
				if (0 < WorldManager::GetSoldierPoint())
				{
					PlayerData* member;
					member = new PlayerData();
					member->m_Character = new CSwordsman();
					member->m_Character->Initialize();
					member->m_Character->SetAlly(true);
					member->m_Exp = 0;
					member->m_NextExp = FIRST_LEVELUP;
					member->m_Character->SetName(std::string("Œ•Žm"));

					
					member->PosX = 0;
					member->PosZ = 0;
					while (1)
					{
						if (m_stage->stage[member->PosZ * m_stage->StageZnum + member->PosX].bChar != true)
						{
							break;
						}
						else
						{
							if (member->PosX > m_stage->StageXnum - 1)
							{
								member->PosX = 0;
								member->PosZ++;
							}
							else
							{
								member->PosX++;
							}
						}
					}
					member->m_Character->SetLocation(XMFLOAT3((member->PosX * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageXnum / 2), 0.0f, (member->PosZ * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageZnum / 2)));

					m_AddStatus = WorldManager::PlayerAdd(member->m_Character->GetName().c_str(), member);
					WorldManager::UseSoldierPoint(1);
					Phase = moveEmp;
					StartFrame = Frame;
					m_AddData = member;
				}
				break;
			case Archer:
				if (2 < WorldManager::GetSoldierPoint())
				{
					PlayerData* member;
					member = new PlayerData();
					member->m_Character = new CArcher();
					member->m_Character->Initialize();
					member->m_Character->SetAlly(true);
					member->m_Exp = 0;
					member->m_NextExp = FIRST_LEVELUP;
					member->m_Character->SetName(std::string("‹|Žg‚¢"));


					member->PosX = 0;
					member->PosZ = 0;
					while (1)
					{
						if (m_stage->stage[member->PosZ * m_stage->StageZnum + member->PosX].bChar != true)
						{
							break;
						}
						else
						{
							if (member->PosX > m_stage->StageXnum - 1)
							{
								member->PosX = 0;
								member->PosZ++;
							}
							else
							{
								member->PosX++;
							}
						}
					}
					member->m_Character->SetLocation(XMFLOAT3((member->PosX * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageXnum / 2), 0.0f, (member->PosZ * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageZnum / 2)));

					m_AddStatus = WorldManager::PlayerAdd(member->m_Character->GetName().c_str(), member);
					WorldManager::UseSoldierPoint(2);
					Phase = moveEmp;
					StartFrame = Frame;
					m_AddData = member;
				}
				break;
			case Sorcerer:
				if (2 < WorldManager::GetSoldierPoint())
				{
					PlayerData* member;
					member = new PlayerData();
					member->m_Character = new CSorcerer();
					member->m_Character->Initialize();
					member->m_Character->SetAlly(true);
					member->m_Exp = 0;
					member->m_NextExp = FIRST_LEVELUP;
					member->m_Character->SetName(std::string("–‚pŽt"));


					member->PosX = 0;
					member->PosZ = 0;
					while (1)
					{
						if (m_stage->stage[member->PosZ * m_stage->StageZnum + member->PosX].bChar != true)
						{
							break;
						}
						else
						{
							if (member->PosX > m_stage->StageXnum - 1)
							{
								member->PosX = 0;
								member->PosZ++;
							}
							else
							{
								member->PosX++;
							}
						}
					}
					member->m_Character->SetLocation(XMFLOAT3((member->PosX * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageXnum / 2), 0.0f, (member->PosZ * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageZnum / 2)));

					m_AddStatus = WorldManager::PlayerAdd(member->m_Character->GetName().c_str(), member);
					WorldManager::UseSoldierPoint(2);
					Phase = moveEmp;
					StartFrame = Frame;
					m_AddData = member;
				}
				break;
			case Healer:
				if (2 < WorldManager::GetSoldierPoint())
				{
					PlayerData* member;
					member = new PlayerData();
					member->m_Character = new CHealer();
					member->m_Character->Initialize();
					member->m_Character->SetAlly(true);
					member->m_Exp = 0;
					member->m_NextExp = FIRST_LEVELUP;
					member->m_Character->SetName(std::string("C“¹Žm"));


					member->PosX = 0;
					member->PosZ = 0;
					while (1)
					{
						if (m_stage->stage[member->PosZ * m_stage->StageZnum + member->PosX].bChar != true)
						{
							break;
						}
						else
						{
							if (member->PosX > m_stage->StageXnum - 1)
							{
								member->PosX = 0;
								member->PosZ++;
							}
							else
							{
								member->PosX++;
							}
						}
					}
					member->m_Character->SetLocation(XMFLOAT3((member->PosX * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageXnum / 2), 0.0f, (member->PosZ * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageZnum / 2)));

					m_AddStatus = WorldManager::PlayerAdd(member->m_Character->GetName().c_str(), member);
					WorldManager::UseSoldierPoint(2);
					Phase = moveEmp;
					StartFrame = Frame;
					m_AddData = member;
				}
				break;
			case Lancer:
				if (3 < WorldManager::GetSoldierPoint())
				{
					PlayerData* member;
					member = new PlayerData();
					member->m_Character = new CLancer();
					member->m_Character->Initialize();
					member->m_Character->SetAlly(true);
					member->m_Exp = 0;
					member->m_NextExp = FIRST_LEVELUP;
					member->m_Character->SetName(std::string("‘„•º"));


					member->PosX = 0;
					member->PosZ = 0;
					while (1)
					{
						if (m_stage->stage[member->PosZ * m_stage->StageZnum + member->PosX].bChar != true)
						{
							break;
						}
						else
						{
							if (member->PosX > m_stage->StageXnum - 1)
							{
								member->PosX = 0;
								member->PosZ++;
							}
							else
							{
								member->PosX++;
							}
						}
					}
					member->m_Character->SetLocation(XMFLOAT3((member->PosX * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageXnum / 2), 0.0f, (member->PosZ * SPACE_SIZE) - (SPACE_SIZE * m_stage->StageZnum / 2)));

					m_AddStatus = WorldManager::PlayerAdd(member->m_Character->GetName().c_str(), member);
					WorldManager::UseSoldierPoint(3);
					Phase = moveEmp;
					StartFrame = Frame;
					m_AddData = member;
				}
				break;
			case 5:
				Phase = backSelect;
				StartFrame = Frame;
				break;
			}
		}
		if (CInput::GetKeyTrigger('Q') || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_B))
		{
			Phase = backSelect;
			StartFrame = Frame;
		}
		break;
	case backSelect:
		m_TexPos[0] = ease_out((age * (1.0f / 30)), SCREEN_HEIGHT / 2, SCREEN_HEIGHT, 1);
		if (age == 30)
		{
			Phase = end;
		}
		break;
	case moveEmp:
		m_TexPos[0] = ease_out((age * (1.0f / 30)), SCREEN_HEIGHT / 2, -SCREEN_HEIGHT, 1);
		m_TexPos[2] = ease_out((age * (1.0f / 30)), SCREEN_HEIGHT + SCREEN_HEIGHT / 2, -SCREEN_HEIGHT, 1);
		if (age == 30)
		{
			Phase++;
			StartFrame = Frame;
		}
		break;
	case Emp:

		for (int i = 0; i < 7; i++)
		{
			m_JudgeScale[i] = elastic_out(age * (1.0f / 40), 0.0f, 1.0f, 1);
			age -= 10;
			if (age < 0) age = 0;
		}

		if (CInput::GetKeyTrigger(VK_SPACE) || CInputController::GetKeyTrigger(XINPUT_GAMEPAD_A))
		{
			Phase = backEmp;
			StartFrame = Frame;
			for (int i = 0; i < 7; i++)
			{
				m_JudgeScale[i] = 0.0f;
			}
		}
		break;
	case backEmp:
		m_TexPos[2] = ease_out((age * (1.0f / 30)), SCREEN_HEIGHT / 2, -SCREEN_HEIGHT, 1);
		if (age == 30)
		{
			Phase = end;
		}
		break;
	case end:
		Phase = notDraw;
		break;
	}

	switch (selectJob)
	{
	case Swordman:
		m_TexPos[1] = m_TexPos[0] - TEXTURE_HEI_2 / 9 * 2;
		break;
	case Archer:
		m_TexPos[1] = m_TexPos[0] - TEXTURE_HEI_2 / 9;
		break;
	case Sorcerer:
		m_TexPos[1] = m_TexPos[0];
		break;
	case Healer:
		m_TexPos[1] = m_TexPos[0] + TEXTURE_HEI_2 / 9;
		break;
	case Lancer:
		m_TexPos[1] = m_TexPos[0] + TEXTURE_HEI_2 / 9 * 2;
		break;
	case 5:
		m_TexPos[1] = m_TexPos[0] + TEXTURE_HEI_2 / 9 * 3.2f;
	}

	if (Frame % 120 > 60)
	{
		if (uvc < 0.7f)
		{
			uvc += 1.0f / 120;
		}
	}
	else
	{
		if (uvc > 0.3f)
		{
			uvc -= 1.0f / 120;
		}
	}
	if (Frame % 60 < 30)
	{
		pos -= 0.5f / 30;
	}
	else
	{
		pos += 0.5f / 30;
	}
}

void CEmploymentUI::Draw()
{
	std::string text;
	VertexColor_4 color;

	float texX = SCREEN_WIDTH / 3;
	float iconX = texX - TEXTURE_WID_2 / 8 * 3;
	float iconY;
	float textY = TEXT_SIZE_BIG / 5 * 3;
	float textX;
	switch (Phase)
	{
	case notDraw:
		break;
	case moveSelect:
	case Select:
	case backSelect:
	case moveEmp:
	case Emp:
	case backEmp:
		if (Phase <= moveEmp)
		{
			//ƒeƒNƒXƒ`ƒƒ
			m_Texture[2]->Draw(texX, m_TexPos[0], 0, 0, TEXTURE_WID_2, TEXTURE_HEI_2, TEXTURE_WID_2, TEXTURE_HEI_2);
			color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, uvc));
			m_Texture[3]->Draw(texX, m_TexPos[1], 0, 0, ICON_SIZE * 7, ICON_SIZE, ICON_SIZE * 7, ICON_SIZE, color);

			m_Icon[0]->Draw(iconX, m_TexPos[0] - TEXTURE_HEI_2 / 9 * 2, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			m_Icon[1]->Draw(iconX, m_TexPos[0] - TEXTURE_HEI_2 / 9, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			m_Icon[2]->Draw(iconX, m_TexPos[0], 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			m_Icon[3]->Draw(iconX, m_TexPos[0] + TEXTURE_HEI_2 / 9, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			m_Icon[4]->Draw(iconX, m_TexPos[0] + TEXTURE_HEI_2 / 9 * 2, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);

			m_Texture[0]->Draw(texX - ICON_SIZE * 4.0f, m_TexPos[1] - ICON_SIZE * 2 / 3 * pos, 0, 0, ICON_SIZE * 2, ICON_SIZE * 2, ICON_SIZE * 2, ICON_SIZE * 2);

			//ƒeƒLƒXƒg
			text = "•ºŽí‘I‘ð";
			color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
			m_Text[0]->DrawJpn((int)(texX - ((TEXT_SIZE_BIG / 3 * 2) * 4 / 2)), (int)(m_TexPos[0] - TEXTURE_HEI_2 / 2.9f - textY), (int)TEXT_SIZE_BIG, (int)(TEXT_SIZE_BIG / 3 * 2), text, color);
			textY = TEXT_SIZE_SMALL / 5 * 3;
			color.setAll(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
			text = "Œ•Žm";
			m_Text[1]->DrawJpn((int)(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 2 / 2)), (int)(m_TexPos[0] - TEXTURE_HEI_2 / 9 * 2 - textY),	(int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			text = "‹|Žg‚¢";
			m_Text[1]->DrawJpn((int)(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 3 / 2)), (int)(m_TexPos[0] - TEXTURE_HEI_2 / 9 - textY),		(int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			text = "–‚“±Žm";
			m_Text[1]->DrawJpn((int)(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 3 / 2)), (int)(m_TexPos[0] - textY),							(int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			text = "C“¹Žm";
			m_Text[1]->DrawJpn((int)(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 3 / 2)), (int)(m_TexPos[0] + TEXTURE_HEI_2 / 9 - textY),		(int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			text = "‘„•º";
			m_Text[1]->DrawJpn((int)(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 2 / 2)), (int)(m_TexPos[0] + TEXTURE_HEI_2 / 9 * 2 - textY),	(int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			text = "‚â‚ß‚é";
			m_Text[1]->DrawJpn((int)(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 3 / 2)), (int)(m_TexPos[0] + TEXTURE_HEI_2 / 9 * 3.2f - textY), (int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);

			color.setAll(XMFLOAT4(0.35f, 0.35f, 0.35f, 1.0f));
			textY = TEXT_SIZE_ENG / 2;
			textX = texX + (TEXT_SIZE_ENG / 3 * 2) * 3;
			text = "SP:1";
			m_Text[2]->DrawEng((int)textX, (int)(m_TexPos[0] - TEXTURE_HEI_2 / 9 * 2 - textY), (int)TEXT_SIZE_ENG, (int)(TEXT_SIZE_ENG / 3 * 2), text, color);
			text = "SP:2";
			m_Text[2]->DrawEng((int)textX, (int)(m_TexPos[0] - TEXTURE_HEI_2 / 9 - textY),		(int)TEXT_SIZE_ENG, (int)(TEXT_SIZE_ENG / 3 * 2), text, color);
			m_Text[2]->DrawEng((int)textX, (int)(m_TexPos[0] - textY),							(int)TEXT_SIZE_ENG, (int)(TEXT_SIZE_ENG / 3 * 2), text, color);
			m_Text[2]->DrawEng((int)textX, (int)(m_TexPos[0] + TEXTURE_HEI_2 / 9 - textY),		(int)TEXT_SIZE_ENG, (int)(TEXT_SIZE_ENG / 3 * 2), text, color);
			text = "SP:3";
			m_Text[2]->DrawEng((int)textX, (int)(m_TexPos[0] + TEXTURE_HEI_2 / 9 * 2 - textY), (int)TEXT_SIZE_ENG, (int)(TEXT_SIZE_ENG / 3 * 2), text, color);
		}

		if (Phase >= moveEmp)
		{
			m_Texture[1]->Draw(texX, m_TexPos[2], 0, 0, TEXTURE_WID, TEXTURE_HEI, TEXTURE_WID, TEXTURE_HEI);
			iconX = texX - TEXTURE_WID / 8 * 3;
			iconY = m_TexPos[2] - TEXTURE_HEI / 3;
			textY = TEXT_SIZE_BIG / 5 * 3;
			color.setAll(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
			switch (m_AddData->m_Character->m_JobClass)
			{
			case Swordman:
				m_Icon[0]->Draw(iconX, iconY, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
				text = "Œ•Žm";
				m_Text[0]->DrawJpn((int)(texX - ((TEXT_SIZE_BIG / 3 * 2) * 2 / 2)), (int)(iconY - textY), (int)TEXT_SIZE_BIG, (int)(TEXT_SIZE_BIG / 3 * 2), text, color);
				break;
			case Archer:
				m_Icon[1]->Draw(iconX, iconY, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
				text = "‹|Žg‚¢";
				m_Text[0]->DrawJpn((int)(texX - ((TEXT_SIZE_BIG / 3 * 2) * 3 / 2)), (int)(iconY - textY), (int)TEXT_SIZE_BIG, (int)(TEXT_SIZE_BIG / 3 * 2), text, color);
				break;
			case Sorcerer:
				m_Icon[2]->Draw(iconX, iconY, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
				text = "–‚“±Žm";
				m_Text[0]->DrawJpn((int)(texX - ((TEXT_SIZE_BIG / 3 * 2) * 3 / 2)), (int)(iconY - textY), (int)TEXT_SIZE_BIG, (int)(TEXT_SIZE_BIG / 3 * 2), text, color);
				break;
			case Healer:
				m_Icon[3]->Draw(iconX, iconY, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
				text = "C“¹Žm";
				m_Text[0]->DrawJpn((int)(texX - ((TEXT_SIZE_BIG / 3 * 2) * 3 / 2)), (int)(iconY - textY), (int)TEXT_SIZE_BIG, (int)(TEXT_SIZE_BIG / 3 * 2), text, color);
				break;
			case Lancer:
				m_Icon[4]->Draw(iconX, iconY, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
				text = "‘„•º";
				m_Text[0]->DrawJpn((int)(texX - ((TEXT_SIZE_BIG / 3 * 2) * 2 / 2)), (int)(iconY - textY), (int)TEXT_SIZE_BIG, (int)(TEXT_SIZE_BIG / 3 * 2), text, color);
				break;
			}
			textX = texX - (TEXTURE_WID / 5 * 2) - ((TEXT_SIZE_SMALL / 3 * 2) / 2);
			textY = TEXT_SIZE_SMALL / 5 * 3;
			text = "HP";
			m_Text[1]->DrawEng((int)textX, (int)(m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 3 - textY), (int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			if (m_AddData->m_Character->GetStatus()->type == Sword || m_AddData->m_Character->GetStatus()->type == Lance || m_AddData->m_Character->GetStatus()->type == Bow)
			{
				text = "—Í";
			}
			else
			{
				text = "–‚—Í";
			}
			m_Text[1]->DrawJpn((int)textX, (int)(m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 4 - textY), (int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			text = "K‰^";
			m_Text[1]->DrawJpn((int)textX, (int)(m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 5 - textY), (int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			text = "‹Z";
			m_Text[1]->DrawJpn((int)textX, (int)(m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 6 - textY), (int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);

			textX = texX;
			text = "–hŒä";
			m_Text[1]->DrawJpn((int)textX, (int)(m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 3 - textY), (int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			text = "–‚–h";
			m_Text[1]->DrawJpn((int)textX, (int)(m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 4 - textY), (int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);
			text = "‘¬‚³";
			m_Text[1]->DrawJpn((int)textX, (int)(m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 5 - textY), (int)TEXT_SIZE_SMALL, (int)(TEXT_SIZE_SMALL / 3 * 2), text, color);

			textX = texX - (TEXTURE_WID / 5);
			float judgeY = m_TexPos[2] - (TEXTURE_HEI / 2);
			float judgeH = 55.0f;
			float judgeW = judgeH * 0.9f;
			color.setAll(XMFLOAT4(1.0f - 1.0f / 12 * m_AddStatus->HP, 1.0f / 12 * m_AddStatus->HP, 0, 1.0f));
			m_Texture[4]->Draw(textX, judgeY + TEXTURE_HEI / 7 * 3, (float)judgeW * m_JudgeScale[0] * AbilityJudge(m_AddStatus->HP),			0, judgeW * m_JudgeScale[0], judgeH * m_JudgeScale[0], judgeW * 6 * m_JudgeScale[0], judgeH * m_JudgeScale[0], color);
			color.setAll(XMFLOAT4(1.0f - 1.0f / 12 * m_AddStatus->Attack, 1.0f / 12 * m_AddStatus->Attack, 0, 1.0f));
			m_Texture[4]->Draw(textX, judgeY + TEXTURE_HEI / 7 * 4, (float)judgeW * m_JudgeScale[1] * AbilityJudge(m_AddStatus->Attack),		0, judgeW * m_JudgeScale[1], judgeH * m_JudgeScale[1], judgeW * 6 * m_JudgeScale[1], judgeH * m_JudgeScale[1], color);
			color.setAll(XMFLOAT4(1.0f - 1.0f / 12 * m_AddStatus->Luck, 1.0f / 12 * m_AddStatus->Luck, 0, 1.0f));
			m_Texture[4]->Draw(textX, judgeY + TEXTURE_HEI / 7 * 5, (float)judgeW * m_JudgeScale[2] * AbilityJudge(m_AddStatus->Luck),			0, judgeW * m_JudgeScale[2], judgeH * m_JudgeScale[2], judgeW * 6 * m_JudgeScale[2], judgeH * m_JudgeScale[2], color);
			color.setAll(XMFLOAT4(1.0f - 1.0f / 12 * m_AddStatus->Dexterity, 1.0f / 12 * m_AddStatus->Dexterity, 0, 1.0f));
			m_Texture[4]->Draw(textX, judgeY + TEXTURE_HEI / 7 * 6, (float)judgeW * m_JudgeScale[3] * AbilityJudge(m_AddStatus->Dexterity),		0, judgeW * m_JudgeScale[3], judgeH * m_JudgeScale[3], judgeW * 6 * m_JudgeScale[3], judgeH * m_JudgeScale[3], color);

			textX = texX + (TEXTURE_WID / 5);
			color.setAll(XMFLOAT4(1.0f - 1.0f / 12 * m_AddStatus->Defense, 1.0f / 12 * m_AddStatus->Defense, 0, 1.0f));
			m_Texture[4]->Draw(textX, judgeY + TEXTURE_HEI / 7 * 3, (float)judgeW * m_JudgeScale[4] * AbilityJudge(m_AddStatus->Defense),		0, judgeW * m_JudgeScale[4], judgeH * m_JudgeScale[4], judgeW * 6 * m_JudgeScale[4], judgeH * m_JudgeScale[4], color);
			color.setAll(XMFLOAT4(1.0f - 1.0f / 12 * m_AddStatus->MagicDefense, 1.0f / 12 * m_AddStatus->MagicDefense, 0, 1.0f));
			m_Texture[4]->Draw(textX, judgeY + TEXTURE_HEI / 7 * 4, (float)judgeW * m_JudgeScale[5] * AbilityJudge(m_AddStatus->MagicDefense),	0, judgeW * m_JudgeScale[5], judgeH * m_JudgeScale[5], judgeW * 6 * m_JudgeScale[5], judgeH * m_JudgeScale[5], color);
			color.setAll(XMFLOAT4(1.0f - 1.0f / 12 * m_AddStatus->Speed, 1.0f / 12 * m_AddStatus->Speed, 0, 1.0f));
			m_Texture[4]->Draw(textX, judgeY + TEXTURE_HEI / 7 * 5, (float)judgeW * m_JudgeScale[6] * AbilityJudge(m_AddStatus->Speed),			0, judgeW * m_JudgeScale[6], judgeH * m_JudgeScale[6], judgeW * 6 * m_JudgeScale[6], judgeH * m_JudgeScale[6], color);
		}
		break;
	}
}


int CEmploymentUI::AbilityJudge(int status)
{
	switch (status)
	{
	case 0:
		return 5;
		break;
	case 1:
	case 2:
	case 3:
		return 4;
		break;
	case 4:
	case 5:
	case 6:
		return 3;
		break;
	case 7:
	case 8:
	case 9:
		return 2;
		break;
	case 10:
	case 11:
		return 1;
		break;
	case 12:
		return 0;
		break;
	}
	return -1;
}