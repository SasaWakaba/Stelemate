#include "../common/main.h"
#include "../common/math.h"
#include "../common/renderer.h"
#include "../GameSystem/WorldManager.h"
#include "../common/input.h"
#include "../common/polygon.h"
#include "../common/CDrawText.h"
#include "../common/Game_Object.h"
#include "../common/number.h"
#include "../Charcter/CPlayerManager.h"
#include "../Charcter/CCharacterData.h"
#include "../Charcter/CJob.h"

#include <iostream>

#include "Employment_UI.h"

#define ease_out(t, b, c, d) ((c) * (-(powf(2.0f, (-10.0f * (t) / (d)))) + 1) + (b))

#define elastic_out(t, b, c, d) ((c) * (1 - powf(2, (-10.0f * (t) / (d))) * sinf(13 * (PI / 2) * ((t) / (d) + 1)) + (b))

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

	m_AddData = nullptr;
	pos = 1.0f;
	Frame = 0;
	Phase = 0;
	selectJob = 0;
	uvc = 0.0f;
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
		m_TexPos[0] = ease_out((age * (1.0f / 60)), SCREEN_HEIGHT + SCREEN_HEIGHT / 2, -SCREEN_HEIGHT, 1);
		if (age == 60)
		{
			Phase++;
		}
		break;
	case Select:
		if (CInput::GetKeyTrigger('W'))
		{
			if (selectJob > 0)
			{
				selectJob--;
			}
		}

		if (CInput::GetKeyTrigger('S'))
		{
			if (selectJob < 5)
			{
				selectJob++;
			}
		}

		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			switch (selectJob)
			{
			case Swordman:
				if (0 < WorldManager::GetSoldierPoint())
				{
					PlayerData* member;
					member = new PlayerData();
					member->m_Character = new CSwordsman();
					member->m_Character->SetAlly(true);
					member->m_Exp = 0;
					member->m_NextExp = FIRST_LEVELUP;
					member->name = "swordsman";
					member->PosX = 0 + WorldManager::GetParty().size();
					member->PosZ = 0;

					WorldManager::PlayerAdd(member->name.c_str(), member);
					WorldManager::UseSoldierPoint(1);
					Phase = moveEmp;
					StartFrame = Frame;
					m_AddData = member;
				}
				break;
			case Archer:
				break;
			case Sorcerer:
				break;
			case Healer:
				break;
			case Lancer:
				break;
			case 5:
				Phase = backSelect;
				StartFrame = Frame;
				break;
			}
		}
		break;
	case backSelect:
		m_TexPos[0] = ease_out((age * (1.0f / 60)), SCREEN_HEIGHT / 2, SCREEN_HEIGHT, 1);
		if (age == 60)
		{
			Phase = end;
		}
		break;
	case moveEmp:
		m_TexPos[0] = ease_out((age * (1.0f / 60)), SCREEN_HEIGHT / 2, -SCREEN_HEIGHT, 1);
		m_TexPos[2] = ease_out((age * (1.0f / 60)), SCREEN_HEIGHT + SCREEN_HEIGHT / 2, -SCREEN_HEIGHT, 1);
		if (age == 60)
		{
			Phase++;
		}
		break;
	case Emp:
		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			Phase = backEmp;
			StartFrame = Frame;
		}
		break;
	case backEmp:
		m_TexPos[2] = ease_out((age * (1.0f / 60)), SCREEN_HEIGHT / 2, -SCREEN_HEIGHT, 1);
		if (age == 60)
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
			//�e�N�X�`��
			m_Texture[2]->Draw(texX, m_TexPos[0], 0, 0, TEXTURE_WID_2, TEXTURE_HEI_2, TEXTURE_WID_2, TEXTURE_HEI_2);
			color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, uvc));
			m_Texture[3]->Draw(texX, m_TexPos[1], 0, 0, ICON_SIZE * 7, ICON_SIZE, ICON_SIZE * 7, ICON_SIZE, color);

			m_Icon[0]->Draw(iconX, m_TexPos[0] - TEXTURE_HEI_2 / 9 * 2, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			m_Icon[1]->Draw(iconX, m_TexPos[0] - TEXTURE_HEI_2 / 9, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			m_Icon[2]->Draw(iconX, m_TexPos[0], 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			m_Icon[3]->Draw(iconX, m_TexPos[0] + TEXTURE_HEI_2 / 9, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
			m_Icon[4]->Draw(iconX, m_TexPos[0] + TEXTURE_HEI_2 / 9 * 2, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);

			m_Texture[0]->Draw(texX - ICON_SIZE * 4.0f, m_TexPos[1] - ICON_SIZE * 2 / 3 * pos, 0, 0, ICON_SIZE * 2, ICON_SIZE * 2, ICON_SIZE * 2, ICON_SIZE * 2);

			//�e�L�X�g
			text = "����I��";
			color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
			m_Text[0]->DrawJpn(texX - ((TEXT_SIZE_BIG / 3 * 2) * 4 / 2), m_TexPos[0] - TEXTURE_HEI_2 / 2.9f - textY, TEXT_SIZE_BIG, (int)TEXT_SIZE_BIG / 3 * 2, text, color);
			textY = TEXT_SIZE_SMALL / 5 * 3;
			color.setAll(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
			text = "���m";
			m_Text[1]->DrawJpn(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 2 / 2), m_TexPos[0] - TEXTURE_HEI_2 / 9 * 2 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			text = "�|�g��";
			m_Text[1]->DrawJpn(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 3 / 2), m_TexPos[0] - TEXTURE_HEI_2 / 9 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			text = "�����m";
			m_Text[1]->DrawJpn(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 3 / 2), m_TexPos[0] - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			text = "�C���m";
			m_Text[1]->DrawJpn(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 3 / 2), m_TexPos[0] + TEXTURE_HEI_2 / 9 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			text = "����";
			m_Text[1]->DrawJpn(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 2 / 2), m_TexPos[0] + TEXTURE_HEI_2 / 9 * 2 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			text = "��߂�";
			m_Text[1]->DrawJpn(texX - ((TEXT_SIZE_SMALL / 3 * 2) * 3 / 2), m_TexPos[0] + TEXTURE_HEI_2 / 9 * 3.2f - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);

			color.setAll(XMFLOAT4(0.35f, 0.35f, 0.35f, 1.0f));
			textY = TEXT_SIZE_ENG / 2;
			textX = texX + (TEXT_SIZE_ENG / 3 * 2) * 3;
			text = "SP:1";
			m_Text[2]->DrawEng(textX, m_TexPos[0] - TEXTURE_HEI_2 / 9 * 2 - textY, TEXT_SIZE_ENG, (int)TEXT_SIZE_ENG / 3 * 2, text, color);
			text = "SP:2";
			m_Text[2]->DrawEng(textX, m_TexPos[0] - TEXTURE_HEI_2 / 9 - textY, TEXT_SIZE_ENG, (int)TEXT_SIZE_ENG / 3 * 2, text, color);
			m_Text[2]->DrawEng(textX, m_TexPos[0] - textY, TEXT_SIZE_ENG, (int)TEXT_SIZE_ENG / 3 * 2, text, color);
			m_Text[2]->DrawEng(textX, m_TexPos[0] + TEXTURE_HEI_2 / 9 - textY, TEXT_SIZE_ENG, (int)TEXT_SIZE_ENG / 3 * 2, text, color);
			text = "SP:3";
			m_Text[2]->DrawEng(textX, m_TexPos[0] + TEXTURE_HEI_2 / 9 * 2 - textY, TEXT_SIZE_ENG, (int)TEXT_SIZE_ENG / 3 * 2, text, color);
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
				text = "���m";
				m_Text[0]->DrawJpn(texX - ((TEXT_SIZE_BIG / 3 * 2) * 2 / 2), iconY - textY, (int)TEXT_SIZE_BIG, (int)TEXT_SIZE_BIG / 3 * 2, text, color);
				break;
			case Archer:
				m_Icon[1]->Draw(iconX, iconY, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
				text = "�|�g��";
				m_Text[0]->DrawJpn(texX - ((TEXT_SIZE_BIG / 3 * 2) * 3 / 2), iconY - textY, (int)TEXT_SIZE_BIG, (int)TEXT_SIZE_BIG / 3 * 2, text, color);
				break;
			case Sorcerer:
				m_Icon[2]->Draw(iconX, iconY, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
				text = "�����m";
				m_Text[0]->DrawJpn(texX - ((TEXT_SIZE_BIG / 3 * 2) * 3 / 2), iconY - textY, (int)TEXT_SIZE_BIG, (int)TEXT_SIZE_BIG / 3 * 2, text, color);
				break;
			case Healer:
				m_Icon[3]->Draw(iconX, iconY, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
				text = "�C���m";
				m_Text[0]->DrawJpn(texX - ((TEXT_SIZE_BIG / 3 * 2) * 3 / 2), iconY - textY, (int)TEXT_SIZE_BIG, (int)TEXT_SIZE_BIG / 3 * 2, text, color);
				break;
			case Lancer:
				m_Icon[4]->Draw(iconX, iconY, 0, 0, ICON_SIZE, ICON_SIZE, ICON_SIZE, ICON_SIZE);
				text = "����";
				m_Text[0]->DrawJpn(texX - ((TEXT_SIZE_BIG / 3 * 2) * 2 / 2), iconY - textY, (int)TEXT_SIZE_BIG, (int)TEXT_SIZE_BIG / 3 * 2, text, color);
				break;
			}
			textX = texX - (TEXTURE_WID / 5 * 2) - ((TEXT_SIZE_SMALL / 3 * 2) / 2);
			textY = TEXT_SIZE_SMALL / 5 * 3;
			text = "HP";
			m_Text[1]->DrawEng(textX, m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 3 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			if (m_AddData->m_Character->GetStatus()->type == Sword || m_AddData->m_Character->GetStatus()->type == Lance || m_AddData->m_Character->GetStatus()->type == Bow)
			{
				text = "��";
			}
			else
			{
				text = "����";
			}
			m_Text[1]->DrawJpn(textX, m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 4 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			text = "�K�^";
			m_Text[1]->DrawJpn(textX, m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 5 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			text = "�Z";
			m_Text[1]->DrawJpn(textX, m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 6 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);

			textX = texX;
			text = "�h��";
			m_Text[1]->DrawJpn(textX, m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 3 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			text = "���h";
			m_Text[1]->DrawJpn(textX, m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 4 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);
			text = "����";
			m_Text[1]->DrawJpn(textX, m_TexPos[2] - (TEXTURE_HEI / 2) + TEXTURE_HEI / 7 * 5 - textY, TEXT_SIZE_SMALL, (int)TEXT_SIZE_SMALL / 3 * 2, text, color);

		}
		break;
	}
}