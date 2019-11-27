#include "../common/main.h"
#include "../common/Game_Object.h"
#include "../Charcter/CCharcterBase.h"
#include "../common/polygon.h"
#include "../Charcter/CCharacterData.h"
#include "CBattleCalculation.h"

#include "CSystemBattle.h"

bool CSystemBattle::bBattle = false;
CCharcterBase* CSystemBattle::m_Char_A;
CCharcterBase* CSystemBattle::m_Char_B;

float CSystemBattle::X = 0.0f;

bool CSystemBattle::Battle(CCharcterBase* pA, CCharcterBase* pB)
{
	if (!bBattle)
	{
		m_Char_A = pA;
		m_Char_B = pB;
		bBattle = true;
		X = 0.0f;
		return true;
	}
	else
	{
		return false;
	}
}

void CSystemBattle::Initialize()
{
	bBattle = false;
	m_Char_A = nullptr;
	m_Char_B = nullptr;
	bMove = false;

	AnimFrame = 0;

	m_Polygon[0] = new CPolygon();
	m_Polygon[0]->Initialize();
	m_Polygon[0]->Load("asset/texture/Battle_sky.png");

	m_Polygon[1] = new CPolygon();
	m_Polygon[1]->Initialize();
	m_Polygon[1]->Load("asset/texture/Battle_rand.png");

	m_Polygon[2] = new CPolygon();
	m_Polygon[2]->Initialize();
	m_Polygon[2]->Load("asset/texture/Battle_grass.png");
}

void CSystemBattle::Finalize()
{
	for (int i = 0; i < 3; i++)
	{
		m_Polygon[i]->Finalize();
		delete m_Polygon[i];
	}
}

void CSystemBattle::Update()
{
	if (bBattle)
	{
		if (X < (SCREEN_WIDTH / 10) && bMove == false)
		{
			X++;
		}
		else if(bMove == false)
		{
			bMove = true;
		}

		if (bMove)
		{
			if (AnimFrame > 10)
			{
				Damage();
				bBattle = false;
			}
			AnimFrame++;
		}
	}
	else
	{
		bMove = false;
	}
}

void CSystemBattle::Draw()
{
	if (bBattle)
	{
		m_Polygon[0]->Draw((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2, 0.0f, 0.0f, BATTLE_TEXTURE_WIDTH, BATTLE_TEXTURE_HEIGHT, BATTLE_TEXTURE_WIDTH, BATTLE_TEXTURE_HEIGHT);
		m_Polygon[1]->Draw((SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 10) + X, SCREEN_HEIGHT / 2, 0.0f, 0.0f, BATTLE_TEXTURE_WIDTH, BATTLE_TEXTURE_HEIGHT, BATTLE_TEXTURE_WIDTH, BATTLE_TEXTURE_HEIGHT);
		m_Polygon[2]->Draw(SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 10) - X, SCREEN_HEIGHT / 2, 0.0f, 0.0f, BATTLE_TEXTURE_WIDTH, BATTLE_TEXTURE_HEIGHT, BATTLE_TEXTURE_WIDTH, BATTLE_TEXTURE_HEIGHT);
	}
}


void CSystemBattle::Damage()
{
	if (m_Char_B->nowHP > 0)
	{
		int Damage_A = 0;
		switch (m_Char_A->GetStatus()->type)
		{
		case Sword:
		case Lance:
		case Bow:
			Damage_A = CBattleCalculation::Damage(m_Char_A, m_Char_B);
			break;

		case Magic:
		case Wand:
			Damage_A = CBattleCalculation::DamageMagic(m_Char_A, m_Char_B);
			break;
		}

		if (Damage_A <= 0)
		{
			Damage_A = 0;
		}

		m_Char_B->nowHP -= Damage_A;

		if (m_Char_B->nowHP > 0)
		{
			int Damage_B = 0;
			switch (m_Char_B->GetStatus()->type)
			{
			case Sword:
			case Lance:
			case Bow:
				Damage_B = CBattleCalculation::Damage(m_Char_B, m_Char_A);
				break;

			case Magic:
			case Wand:
				Damage_B = CBattleCalculation::DamageMagic(m_Char_B, m_Char_A);
				break;
			}
			if (Damage_B <= 0)
			{
				Damage_B = 0;
			}

			m_Char_A->nowHP -= Damage_B;

			if (m_Char_A->nowHP <= 0)
			{
				m_Char_A->SetDestroy();
			}
		}
		else
		{
			m_Char_B->SetDestroy();
		}

	}
	else
	{
		bBattle = false;
		m_Char_A = nullptr;
		m_Char_B = nullptr;
		X = 0.0f;
	}
}