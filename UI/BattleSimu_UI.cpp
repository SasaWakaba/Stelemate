#include "../common/main.h"
#include "../common/math.h"
#include "../common/texture.h"
#include "../common/polygon.h"
#include "../common/CDrawText.h"
#include "../Charcter/CCharacterData.h"
#include "../Charcter/CCharcterBase.h"
#include "../common/CScore.h"

#include "BattleSimu_UI.h"

#define TEX_WIDTH (600.0f)
#define TEX_HEIGHT (600.0f)

#define TEXT_BIG (TEX_WIDTH * 0.1f)
#define TEXT_SMALL (TEXT_BIG * 0.6f)
static float alpha = 0.8f;

void CBattleSimu::Initialize()
{
	for (int i = 0; i < MAX_TEXNUM; i++)
	{
		m_Texture[i] = new CPolygon();
		m_Texture[i]->Initialize();
	}
	m_Texture[0]->Load("asset/texture/Status_HP000.png");
	m_Texture[1]->Load("asset/texture/Status_HP001.png");
	m_Texture[2]->Load("asset/texture/Status_HP002.png");
	m_Texture[3]->Load("asset/texture/Status_HP003.png");
	m_Texture[4]->Load("asset/texture/Status_Back000.png");
	m_Texture[5]->Load("asset/texture/Icon000.png");
	m_Texture[6]->Load("asset/texture/Icon001.png");
	m_Texture[7]->Load("asset/texture/Icon002.png");
	m_Texture[8]->Load("asset/texture/Icon003.png");
	m_Texture[9]->Load("asset/texture/Icon004.png");

	m_Text[0] = new CDrawText();
	m_Text[1] = new CDrawText();

	m_Text[0]->Set(TEXT_BIG);
	m_Text[1]->Set(TEXT_SMALL);

	m_Pos.x = SCREEN_WIDTH / 4.5f;
	m_Pos.y = SCREEN_HEIGHT / 2;

	m_Char[0] = nullptr;
	m_Char[1] = nullptr;

	m_Number = new CScore();
	m_Number->Initialize(2, TEXT_SMALL, TEXT_SMALL);

	bDraw = false;
	frame = 0;

	alpha = 0.8f;
}

void CBattleSimu::Finalize()
{
	for (int i = 0; i < MAX_TEXNUM; i++)
	{
		m_Texture[i]->Finalize();
		delete m_Texture[i];
	}

	m_Text[0]->UnSet();
	m_Text[1]->UnSet();
}

void CBattleSimu::Update()
{
	frame++;
}

void CBattleSimu::Draw()
{
	if (bDraw)
	{

		if (frame % 60 < 30)
		{
			alpha -= 0.5f / 30;
		}
		else
		{
			alpha += 0.5f / 30;
		}
		VertexColor_4 color{
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		};


		if (m_Char[0] != nullptr && m_Char[1] != nullptr)
		{

			STATUS* pl = m_Char[0]->GetStatus();
			STATUS* ene = m_Char[1]->GetStatus();
			float BarY = m_Pos.y - TEX_HEIGHT * 0.125f;
			int plDamage;
			int eneDamage;
			{
				switch (pl->type)
				{
				case Sword:
				case Lance:
				case Bow:
					plDamage = pl->Attack + (m_Char[0]->GetWeapon()->Attack * myMath::Advantage(m_Char[0]->m_JobClass, m_Char[1]->m_JobClass)) - ene->Defense;
					break;
				case Magic:
				case Wand:
					break;
				}
				switch (ene->type)
				{
				case Sword:
				case Lance:
				case Bow:
					eneDamage = ene->Attack + (m_Char[1]->GetWeapon()->Attack * myMath::Advantage(m_Char[1]->m_JobClass, m_Char[0]->m_JobClass)) - pl->Defense;
					break;
				case Magic:
				case Wand:
					break;
				}

				if (m_Char[1]->nowHP - plDamage < 0)
				{
					plDamage = m_Char[1]->nowHP;
				}
				if (m_Char[0]->nowHP - eneDamage < 0)
				{
					eneDamage = m_Char[0]->nowHP;
				}

			}

			//HPƒo[‚Ìƒx[ƒX
			m_Texture[1]->Draw(m_Pos.x, BarY, 0, 0, TEX_WIDTH, TEX_HEIGHT * 0.09f, TEX_WIDTH, TEX_HEIGHT * 0.09f);

			//ƒ_ƒ[ƒWŽó‚¯‚é‘O‚ÌHP•`‰æ
			color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, alpha));
			float plBarX = (m_Pos.x - ((TEX_WIDTH * 0.72f) * 0.29f)) + (TEX_WIDTH * 0.3f) / pl->HP * (pl->HP - m_Char[0]->nowHP) / 2;
			float eneBarX = (m_Pos.x + ((TEX_WIDTH * 0.72f) * 0.29f)) - (TEX_WIDTH * 0.3f) / ene->HP * (ene->HP - m_Char[1]->nowHP) / 2;
			m_Texture[0]->Draw(plBarX, BarY, 0, 0, TEX_WIDTH * 0.3f / pl->HP * m_Char[0]->nowHP, TEX_HEIGHT * 0.04f, TEX_WIDTH * 0.3f, TEX_HEIGHT * 0.04f, color);
			m_Texture[0]->Draw(eneBarX, BarY, 0, 0, TEX_WIDTH * 0.3f / ene->HP * m_Char[1]->nowHP, TEX_HEIGHT * 0.04f, TEX_WIDTH * 0.3f, TEX_HEIGHT * 0.04f, color);

			//ƒ_ƒ[ƒWŽó‚¯‚½Œã‚ÌHP•`‰æ
			color.a = color.c = { 0.0f, 0.0f, 0.8f, 1.0f };
			color.b = color.d = { 0.0f, 0.0f, 0.1f, 1.0f };

			plBarX = (m_Pos.x - ((TEX_WIDTH * 0.72f) * 0.29f)) + (TEX_WIDTH * 0.3f) / pl->HP * (pl->HP - (m_Char[0]->nowHP - eneDamage)) / 2;
			eneBarX = (m_Pos.x + ((TEX_WIDTH * 0.72f) * 0.29f)) - (TEX_WIDTH * 0.3f) / ene->HP * (ene->HP - (m_Char[1]->nowHP - plDamage)) / 2;
			m_Texture[0]->Draw(plBarX, BarY, 0, 0, TEX_WIDTH * 0.3f  / pl->HP * (m_Char[0]->nowHP - eneDamage), TEX_HEIGHT * 0.04f, TEX_WIDTH * 0.3f, TEX_HEIGHT * 0.04f, color);
			color.a = color.c = { 0.1f, 0.0f, 0.0f, 1.0f };
			color.b = color.d = { 0.8f, 0.0f, 0.0f, 1.0f };
			m_Texture[0]->Draw(eneBarX, BarY, 0, 0, TEX_WIDTH * 0.3f / ene->HP * (m_Char[1]->nowHP - plDamage), TEX_HEIGHT * 0.04f, TEX_WIDTH * 0.3f, TEX_HEIGHT * 0.04f, color);

			m_Texture[2]->Draw(m_Pos.x, BarY, 0, 0, TEX_WIDTH * 0.72f, TEX_HEIGHT * 0.044f, TEX_WIDTH * 0.72f, TEX_HEIGHT * 0.044f);
		
			m_Texture[4]->Draw(m_Pos.x, m_Pos.y, 0, 0, TEX_WIDTH, TEX_HEIGHT, TEX_WIDTH, TEX_HEIGHT);

			{
				color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
				switch (m_Char[0]->m_JobClass)
				{
				case Swordman:
					m_Text[0]->DrawJpn(m_Pos.x - TEX_WIDTH / 4.8f, m_Pos.y - TEX_HEIGHT / 2.2f, TEXT_BIG, TEXT_BIG / 1.5f, (std::string)"Œ•Žm", color);
					m_Texture[5]->Draw(m_Pos.x - TEX_WIDTH / 4.8f - TEXT_SMALL * 2.5f, m_Pos.y - TEX_HEIGHT / 3.4f, 0, 0, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f);
					break;
				case Lancer:
					m_Text[0]->DrawJpn(m_Pos.x - TEX_WIDTH / 4.8f, m_Pos.y - TEX_HEIGHT / 2.2f, TEXT_BIG, TEXT_BIG / 1.5f, (std::string)"‘„•º", color);
					m_Texture[9]->Draw(m_Pos.x - TEX_WIDTH / 4.8f - TEXT_SMALL * 2.5f, m_Pos.y - TEX_HEIGHT / 3.4f, 0, 0, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f);
					break;
				case Archer:
					m_Text[0]->DrawJpn(m_Pos.x - TEX_WIDTH / 4.8f, m_Pos.y - TEX_HEIGHT / 2.2f, TEXT_BIG, TEXT_BIG / 1.5f, (std::string)"‹|Žm", color);
					m_Texture[6]->Draw(m_Pos.x - TEX_WIDTH / 4.8f - TEXT_SMALL * 2.5f, m_Pos.y - TEX_HEIGHT / 3.4f, 0, 0, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f);
					break;
				case Sorcerer:
					m_Text[0]->DrawJpn(m_Pos.x - TEX_WIDTH / 4.8f, m_Pos.y - TEX_HEIGHT / 2.2f, TEXT_BIG, TEXT_BIG / 1.5f, (std::string)"–‚pŽt", color);
					m_Texture[8]->Draw(m_Pos.x - TEX_WIDTH / 4.8f - TEXT_SMALL * 2.5f, m_Pos.y - TEX_HEIGHT / 3.4f, 0, 0, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f);
					break;
				}
				m_Text[1]->DrawJpn(m_Pos.x - TEX_WIDTH / 4.8f - TEXT_SMALL * 1.5f, m_Pos.y - TEX_HEIGHT / 3.0f, TEXT_SMALL, TEXT_SMALL / 1.2f, m_Char[0]->GetWeapon()->name, color);
				m_Text[1]->DrawEng(m_Pos.x + TEX_WIDTH / 4.8f - TEXT_SMALL * 2.0f, m_Pos.y - TEX_HEIGHT / 3.0f, TEXT_SMALL, TEXT_SMALL / 1.2f, std::to_string(m_Char[0]->GetWeapon()->Attack), color);
			}
			{
				switch (m_Char[1]->m_JobClass)
				{
				case Swordman:
					m_Text[0]->DrawJpn(m_Pos.x + TEX_WIDTH / 10.5f, m_Pos.y + TEX_HEIGHT / 3.7f, TEXT_BIG, TEXT_BIG / 1.5f, (std::string)"Œ•Žm", color);
					m_Texture[5]->Draw(m_Pos.x + TEX_WIDTH / 4.8f - TEXT_SMALL * 5.5f, m_Pos.y + TEX_HEIGHT / 2.3f, 0, 0, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f);
					break;
				case Lancer:
					m_Text[0]->DrawJpn(m_Pos.x + TEX_WIDTH / 10.5f, m_Pos.y + TEX_HEIGHT / 3.7f, TEXT_BIG, TEXT_BIG / 1.5f, (std::string)"‘„•º", color);
					m_Texture[9]->Draw(m_Pos.x + TEX_WIDTH / 4.8f - TEXT_SMALL * 5.5f, m_Pos.y + TEX_HEIGHT / 2.3f, 0, 0, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f);
					break;
				case Archer:
					m_Text[0]->DrawJpn(m_Pos.x + TEX_WIDTH / 10.5f, m_Pos.y + TEX_HEIGHT / 3.7f, TEXT_BIG, TEXT_BIG / 1.5f, (std::string)"‹|Žm", color);
					m_Texture[6]->Draw(m_Pos.x + TEX_WIDTH / 4.8f - TEXT_SMALL * 5.5f, m_Pos.y + TEX_HEIGHT / 2.3f, 0, 0, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f);
					break;
				case Sorcerer:
					m_Text[0]->DrawJpn(m_Pos.x + TEX_WIDTH / 10.5f, m_Pos.y + TEX_HEIGHT / 3.7f, TEXT_BIG, TEXT_BIG / 1.5f, (std::string)"–‚pŽt", color);
					m_Texture[8]->Draw(m_Pos.x + TEX_WIDTH / 4.8f - TEXT_SMALL * 5.5f, m_Pos.y + TEX_HEIGHT / 2.3f, 0, 0, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f, TEXT_SMALL * 1.25f);
					break;
				}
				m_Text[1]->DrawJpn(m_Pos.x + TEX_WIDTH / 4.8f - TEXT_SMALL * 4.5f, m_Pos.y + TEX_HEIGHT / 2.5f, TEXT_SMALL, TEXT_SMALL / 1.2f, m_Char[1]->GetWeapon()->name, color);
				m_Text[1]->DrawEng(m_Pos.x + TEX_WIDTH / 3.0f, m_Pos.y + TEX_HEIGHT / 2.5f, TEXT_SMALL, TEXT_SMALL / 1.2f, std::to_string(m_Char[1]->GetWeapon()->Attack), color);
			}

			m_Texture[3]->Draw(plBarX - (TEX_WIDTH * 0.3f / pl->HP * (m_Char[0]->nowHP - eneDamage) / 2), BarY - TEXT_SMALL * 1.2f, 0, 0, TEXT_SMALL * 2.0f, TEXT_SMALL * 2.32f, TEXT_SMALL * 2.0f, TEXT_SMALL *2.32f);
			m_Texture[3]->Draw(eneBarX + (TEX_WIDTH * 0.3f / ene->HP * (m_Char[1]->nowHP - plDamage) / 2), BarY - TEXT_SMALL * 1.2f, 0, 0, TEXT_SMALL * 2.0f, TEXT_SMALL * 2.32f, TEXT_SMALL * 2.0f, TEXT_SMALL *2.32f);

			m_Number->Draw(plBarX - (TEX_WIDTH * 0.3f / pl->HP * (m_Char[0]->nowHP - eneDamage) / 2) - TEXT_SMALL / 3, BarY - TEXT_SMALL * 1.4f, m_Char[0]->nowHP - plDamage);
			m_Number->Draw(eneBarX + (TEX_WIDTH * 0.3f / ene->HP * (m_Char[1]->nowHP - plDamage) / 2) - TEXT_SMALL / 3, BarY - TEXT_SMALL * 1.4f, m_Char[1]->nowHP - eneDamage);

			m_Number->Draw(m_Pos.x - TEX_WIDTH / 2.4f, BarY, m_Char[0]->nowHP);
			m_Number->Draw(m_Pos.x + TEX_WIDTH / 2.6f, BarY, m_Char[1]->nowHP);

			//•KŽE
			m_Number->Draw(m_Pos.x - TEXT_SMALL * 3.5f, m_Pos.y + TEXT_SMALL * 3.2f, myMath::Critical(pl->Dexterity, pl->Luck, m_Char[0]->GetWeapon()->Cri) - ene->Luck);
			m_Number->Draw(m_Pos.x + TEXT_SMALL * 3.0f, m_Pos.y + TEXT_SMALL * 3.2f, myMath::Critical(ene->Dexterity, ene->Luck, m_Char[1]->GetWeapon()->Cri) - ene->Luck);

			//–½’†
			m_Number->Draw(m_Pos.x - TEXT_SMALL * 3.5f, m_Pos.y + TEXT_SMALL * 1.75f, myMath::Hit(pl->Dexterity, pl->Luck, m_Char[0]->GetWeapon()->Hit) - myMath::Avoidance(ene->Speed, ene->Luck));
			m_Number->Draw(m_Pos.x + TEXT_SMALL * 3.0f, m_Pos.y + TEXT_SMALL * 1.75f, myMath::Hit(ene->Dexterity, ene->Luck, m_Char[1]->GetWeapon()->Hit) - myMath::Avoidance(pl->Speed, pl->Luck));

			//ˆÐ—Í
			m_Number->Draw(m_Pos.x - TEXT_SMALL * 3.5f, m_Pos.y + TEXT_SMALL * 0.25f, plDamage);
			m_Number->Draw(m_Pos.x + TEXT_SMALL * 3.0f, m_Pos.y + TEXT_SMALL * 0.25f, eneDamage);

		}
	}
}