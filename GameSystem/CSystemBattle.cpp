#include "../common/main.h"
#include "../common/renderer.h"
#include "../common/Game_Object.h"
#include "../Charcter/CCharcterBase.h"
#include "../common/polygon.h"
#include "../Charcter/CCharacterData.h"
#include "CBattleCalculation.h"
#include "CSubCamera.h"
#include "../Stage/CCube.h"
#include "../common/CSkyBox.h"
#include "../common/Wall.h"
#include "../Stage/CStage.h"

#include "CSystemBattle.h"

bool CSystemBattle::bBattle = false;
PanelState* CSystemBattle::m_Char_A;
PanelState* CSystemBattle::m_Char_B;

float CSystemBattle::X = 0.0f;
int CSystemBattle::Fase;
int CSystemBattle::CreateFrame;
int CSystemBattle::Frame;
XMFLOAT4 CSystemBattle::view;

bool CSystemBattle::Battle(PanelState* pA, PanelState* pB)
{
	if (!bBattle)
	{
		Fase = 0;
		m_Char_A = pA;
		m_Char_B = pB;
		bBattle = true;
		X = 0.0f;
		CreateFrame = Frame;
		view = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
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

	m_Position = {0.0f, 0.0f, 0.0f};

	m_Polygon[0] = new CPolygon();
	m_Polygon[0]->Initialize();
	m_Polygon[0]->Load("asset/texture/BattleUI000.png");

	m_Polygon[1] = new CPolygon();
	m_Polygon[1]->Initialize();
	m_Polygon[1]->Load("asset/texture/BattleUI001.png");

	m_Polygon[2] = new CPolygon();
	m_Polygon[2]->Initialize();
	m_Polygon[2]->Load("asset/texture/Battle_grass.png");

	camera = new CSubCamera();
	camera->Initialize();
	camera->SetViewPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	camera->SetAt(XMFLOAT3(0.0f, 95.0f, 0.0f));

	for (int i = 0; i < 2; i++)
	{
		tex[i] = new CTexture();
	}
	tex[0]->LoadTex("asset/texture/grass01.jpg");
	tex[1]->LoadTex("asset/texture/forest.jpg");


	Rand = new CBattleRand();
	Rand->Initialize();

	sky = new CSkyBox();
	sky->Initialize();
	Frame = 0;
}

void CSystemBattle::Finalize()
{
	for (int i = 0; i < 3; i++)
	{
		m_Polygon[i]->Finalize();
		delete m_Polygon[i];
	}
	delete camera;

	for (int i = 0; i < 2; i++)
	{
		tex[i]->Unload();
		delete tex[i];
	}

	sky->Finalize();
	delete sky;
}

void CSystemBattle::Update()
{
	if (bBattle)
	{
		switch (Fase)
		{
			case BackSet:
				if (X < SCREEN_WIDTH)
				{
					int age = (Frame - CreateFrame) * 2.0f;
					X = (sin(-PI / 2 + PI / 120 * age) + 1) / 2 * SCREEN_WIDTH;
				}
				else if(view.x > SCREEN_WIDTH / 6)
				{
					view.x += ((SCREEN_WIDTH / 6) - (SCREEN_WIDTH / 2)) / 15;
					view.y += ((SCREEN_HEIGHT / 6) - (SCREEN_HEIGHT / 2)) / 15;
					view.z += ((SCREEN_WIDTH / 6 * 5) - (SCREEN_WIDTH / 2)) / 15;
					view.w += ((SCREEN_HEIGHT / 6 * 5) - (SCREEN_HEIGHT / 2)) / 15;
				}
				else
				{
					Fase = MoveCamera;
				}
				camera->SetViewPos(view.x, view.y, view.z, view.w);
				break;
			case MoveCamera:
				if (AnimFrame > 10)
				{
					Damage();
					bBattle = false;
				}
				AnimFrame++;
				break;
			case MoveCharA:

				break;
			case AttackA:
				break;
			case MoveCharB:
				break;
			case AttackB:
				break;
			case End:
				break;
		}
		Frame++;
		sky->Update();
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
		m_Polygon[0]->Draw(-(SCREEN_WIDTH / 2) + X, SCREEN_HEIGHT / 2, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
		m_Polygon[1]->Draw(SCREEN_WIDTH + (SCREEN_WIDTH / 2) - X, SCREEN_HEIGHT / 2, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

		CRenderer::DepthReset();
		camera->Draw();
		XMMATRIX world;
		world = XMMatrixTranslation(0.0f, 90.0f, 0.0f);
		sky->Draw(world);

		world = XMMatrixScaling(5.0f, 5.0f, 5.0f);					//Šg‘åEk¬
		world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);	//‰ñ“]
		world *= XMMatrixTranslation(-5.0f, 90.0f, 0.0f);	

		Rand->Draw(world, tex[0]);

		world = XMMatrixScaling(5.0f, 5.0f, 5.0f);					//Šg‘åEk¬
		world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);	//‰ñ“]
		world *= XMMatrixTranslation(5.0f, 90.0f, 0.0f);

		Rand->Draw(world, tex[1]);
	}
}


void CSystemBattle::Damage()
{
	if (m_Char_B->Charcter->nowHP > 0)
	{
		int Damage_A = 0;
		switch (m_Char_A->Charcter->GetStatus()->type)
		{
		case Sword:
		case Lance:
		case Bow:
			Damage_A = CBattleCalculation::Damage(m_Char_A->Charcter, m_Char_B->Charcter);
			break;

		case Magic:
		case Wand:
			Damage_A = CBattleCalculation::DamageMagic(m_Char_A->Charcter, m_Char_B->Charcter);
			break;
		}

		if (Damage_A <= 0)
		{
			Damage_A = 0;
		}

		m_Char_B->Charcter->nowHP -= Damage_A;

		if (m_Char_B->Charcter->nowHP > 0)
		{
			int Damage_B = 0;
			switch (m_Char_B->Charcter->GetStatus()->type)
			{
			case Sword:
			case Lance:
			case Bow:
				Damage_B = CBattleCalculation::Damage(m_Char_B->Charcter, m_Char_A->Charcter);
				break;

			case Magic:
			case Wand:
				Damage_B = CBattleCalculation::DamageMagic(m_Char_B->Charcter, m_Char_A->Charcter);
				break;
			}
			if (Damage_B <= 0)
			{
				Damage_B = 0;
			}

			m_Char_A->Charcter->nowHP -= Damage_B;

			if (m_Char_A->Charcter->nowHP <= 0)
			{
				m_Char_A->Charcter->SetDestroy();
			}
		}
		else
		{
			m_Char_B->Charcter->SetDestroy();
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