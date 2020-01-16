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
#include "../common/ModelAnimation.h"
#include "../common/CDrawText.h"
#include "../common/CCircleShadow.h"

#include "CSystemBattle.h"

#define DATA_WIDTH (SCREEN_WIDTH / 3)
#define DATA_HEIGHT (SCREEN_HEIGHT / 10)

#define TEXT_SIZE (65)

bool CSystemBattle::bBattle = false;
PanelState* CSystemBattle::m_Char_A;
PanelState* CSystemBattle::m_Char_B;

float CSystemBattle::X = 0.0f;
int CSystemBattle::Fase;
int CSystemBattle::CreateFrame;
int CSystemBattle::Frame;
XMFLOAT4 CSystemBattle::view;
XMFLOAT3 CSystemBattle::charaPos[2];

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

		charaPos[0] = XMFLOAT3(-5.0f, 92.5f, 0.0f);
		charaPos[1] = XMFLOAT3(5.0f, 92.5f, 0.0f);
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

	m_Position = { 0.0f, 90.0f, 0.0f };

	for (int i = 0; i < UI_MAX; i++)
	{
		m_Polygon[i] = new CPolygon();
		m_Polygon[i]->Initialize();
	}

	m_Polygon[0]->Load("asset/texture/BattleUI000.png");
	m_Polygon[1]->Load("asset/texture/BattleUI001.png");
	m_Polygon[2]->Load("asset/texture/BattleUI002.png");
	m_Polygon[3]->Load("asset/texture/BattleUI003.png");
	m_Polygon[4]->Load("asset/texture/BattleUI004.png");
	m_Polygon[5]->Load("asset/texture/BattleUI005.png");

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

	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		Model[i] = new CModelAnimation();
	}
	Model[0]->Load("asset/model/Rook_A/Rook.obj");
	Model[1]->Load("asset/model/Rook_B/RookB.obj");

	Rand = new CBattleRand();
	Rand->Initialize();

	sky = new CSkyBox();
	sky->Initialize();

	text = new CDrawText();
	text->Set(TEXT_SIZE);
	shadow = new CCircleShadow();
	shadow->Initialize();


	Frame = 0;
}

void CSystemBattle::Finalize()
{
	for (int i = 0; i < UI_MAX; i++)
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
	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		Model[i]->UnLoad();
		delete Model[i];
	}
	delete sky;
	text->UnSet();
	delete text;
	shadow->Finalize();
	delete 	shadow;
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
					Fase = MoveCharA;
					CreateFrame = Frame;
				}
				camera->SetViewPos(view.x, view.y, view.z, view.w);
				break;
			case MoveCamera:
				//if (AnimFrame > 10)
				//{
				//	Damage();
				//	bBattle = false;
				//}
				//AnimFrame++;
				break;

			case MoveCharA:
				if (charaPos[0].x < 3.0f)
				{
					int r = (Frame - CreateFrame) * 4.0f;
					charaPos[0].x = -1.0f + cosf(XMConvertToRadians(180 - r)) * 4.0f;
					charaPos[0].y = 92.5f + sinf(XMConvertToRadians(180 - r)) * 4.0f;
				}
				else if (m_Char_B->Charcter->nowHP > 0)
				{
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
					DamageCount = 0;
					Fase = AttackA;
				}
				else
				{
					Fase = End;
				}
				break;

			case AttackA:
				if (charaPos[0].x > -5.0f)
				{
					charaPos[0].x -= 0.5f;
				}

				if (Frame % 5 == 0)
				{
					if (DamageCount < Damage_A)
					{
						DamageCount++;
						m_Char_B->Charcter->nowHP--;
					}
					else
					{
						if (m_Char_B->Charcter->nowHP > 0)
						{
							Fase = MoveCharB;
							CreateFrame = Frame;
						}
						else
						{
							m_Char_B->Charcter->SetDestroy();
							Fase = End;
						}
					}
				}
				break;

			case MoveCharB:
				if (charaPos[1].x > -3.0f)
				{
					int r = (Frame - CreateFrame) * 4.0f;
					charaPos[1].x = 1.0f + cosf(XMConvertToRadians(0 + r)) * 4.0f;
					charaPos[1].y = 92.5f + sinf(XMConvertToRadians(0 + r)) * 4.0f;
				}
				else if (m_Char_A->Charcter->nowHP > 0)
				{
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
					DamageCount = 0;
					Fase = AttackB;
				}
				break;
			case AttackB:
				if (charaPos[1].x < 5.0f)
				{
					charaPos[1].x += 0.5f;
				}
				if (Frame % 5 == 0)
				{
					if (DamageCount < Damage_B)
					{
						DamageCount++;
						m_Char_A->Charcter->nowHP--;
					}
					else
					{
						if (m_Char_A->Charcter->nowHP <= 0)
						{
							m_Char_A->Charcter->SetDestroy();
							Fase = End;
						}
						else
						{
							Fase = End;
						}
					}
				}
				break;
			case End:
				if (view.x < SCREEN_WIDTH / 2)
				{
					view.x += ((SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 6)) / 15;
					view.y += ((SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 6)) / 15;
					view.z += ((SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 6 * 5)) / 15;
					view.w += ((SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 6 * 5)) / 15;
					CreateFrame = Frame;
				}
				else if (X > 0)
				{
					int age = (Frame - CreateFrame) * 2.0f;
					X = X + (sin(-PI / 2 + PI / 120 * age) + 1) / 2 * -SCREEN_WIDTH;
				}
				else
				{
					bBattle = false;
					m_Char_A = nullptr;
					m_Char_B = nullptr;
					X = 0.0f;
				}
				camera->SetViewPos(view.x, view.y, view.z, view.w);
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

		{
			//‹ó
			world = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
			sky->Draw(world);

			//’n–Ê‚P
			world = XMMatrixScaling(5.0f, 5.0f, 5.0f);					//Šg‘åEk¬
			world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);	//‰ñ“]
			world *= XMMatrixTranslation(m_Position.x - 5.0f, m_Position.y, m_Position.z);

			switch (m_Char_A->PanelPattarn)
			{
			case 1:
				Rand->Draw(world, tex[0]);
				break;
			case 2:
				Rand->Draw(world, tex[1]);
				break;
			}

			//’n–Ê‚Q
			world = XMMatrixScaling(5.0f, 5.0f, 5.0f);					//Šg‘åEk¬
			world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);	//‰ñ“]
			world *= XMMatrixTranslation(m_Position.x + 5.0f, m_Position.y, m_Position.z);

			switch (m_Char_B->PanelPattarn)
			{
			case 1:
				Rand->Draw(world, tex[0]);
				break;
			case 2:
				Rand->Draw(world, tex[1]);
				break;
			}
		}
		//ƒLƒƒƒ‰ƒNƒ^[
		{
			switch (m_Char_A->Charcter->m_JobClass)
			{
			case Swordman:
				if (m_Char_A->Charcter->GetAlly())
				{
					world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
					world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90.0f), 0.0f);
					world *= XMMatrixTranslation(charaPos[0].x, charaPos[0].y, charaPos[0].z);
					Model[0]->Draw(world);
				}
				else
				{
					world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
					world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(-90.0f), 0.0f);
					world *= XMMatrixTranslation(charaPos[0].x, charaPos[0].y, charaPos[0].z);
					Model[1]->Draw(world);
				}
				break;
			case Lancer:
			case Archer:
			case Sorcerer:
				break;
			}
			world = XMMatrixScaling(3.0f, 3.0f, 3.0f);
			world *= XMMatrixTranslation(charaPos[0].x, 92.5f + 0.01f, charaPos[0].z);
			shadow->Draw(world);

			switch (m_Char_B->Charcter->m_JobClass)
			{
			case Swordman:
				if (m_Char_B->Charcter->GetAlly())
				{
					world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
					world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(-90.0f), 0.0f);
					world *= XMMatrixTranslation(charaPos[1].x, charaPos[1].y, charaPos[1].z);
					Model[0]->Draw(world);
				}
				else
				{
					world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
					world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90.0f), 0.0f);
					world *= XMMatrixTranslation(charaPos[1].x, charaPos[1].y, charaPos[1].z);
					Model[1]->Draw(world);
				}
				break;
			case Lancer:
			case Archer:
			case Sorcerer:
				break;
			}
			world = XMMatrixScaling(3.0f, 3.0f, 3.0f);
			world *= XMMatrixTranslation(charaPos[1].x, 92.5f + 0.01f, charaPos[1].z);
			shadow->Draw(world);
		}

		//UI
		{
			camera->SetViewPos(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			camera->Draw();
			XMFLOAT2 BasePos;
			BasePos.x = -(DATA_WIDTH / 2) + X / 8 * 3;
			BasePos.y = SCREEN_HEIGHT / 7 * 6;
			m_Polygon[2]->Draw(BasePos.x, BasePos.y, 0, 0, DATA_WIDTH, DATA_HEIGHT, DATA_WIDTH, DATA_HEIGHT);

			VertexColor_4 color;
			if (m_Char_A->Charcter->GetAlly())
			{
				color.a = color.c = { 0.0f, 0.0f, 0.1f, 1.0f };
				color.b = color.d = { 0.0f, 0.0f, 0.8f, 1.0f };
			}
			else
			{
				color.a = color.c = { 0.1f, 0.0f, 0.0f, 1.0f };
				color.b = color.d = { 0.8f, 0.0f, 0.0f, 1.0f };
			}
			float Bar;
			Bar = DATA_WIDTH * 0.84f / m_Char_A->Charcter->GetStatus()->HP * m_Char_A->Charcter->nowHP;
			m_Polygon[3]->Draw((BasePos.x - DATA_WIDTH * 0.06f) - (DATA_WIDTH * 0.84f - Bar) / 2, BasePos.y, 0, 0, Bar, DATA_HEIGHT / 2, DATA_WIDTH * 0.84f, DATA_HEIGHT / 2, color);

			m_Polygon[4]->Draw(BasePos.x, BasePos.y, 0, 0, DATA_WIDTH, DATA_HEIGHT, DATA_WIDTH, DATA_HEIGHT);
			m_Polygon[5]->Draw(BasePos.x - (DATA_WIDTH / 2), BasePos.y, 0, 0, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 7);
			color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
			if (m_Char_A->Charcter->nowHP >= 10)
			{
				text->DrawEng(BasePos.x - (DATA_WIDTH / 2) - TEXT_SIZE / 2, BasePos.y - TEXT_SIZE * 0.625f, TEXT_SIZE, TEXT_SIZE / 3 * 2, std::to_string(m_Char_A->Charcter->nowHP), color);
			}
			else if (m_Char_A->Charcter->nowHP > 0)
			{
				text->DrawEng(BasePos.x - (DATA_WIDTH / 2), BasePos.y - TEXT_SIZE * 0.625f, TEXT_SIZE, TEXT_SIZE / 3 * 2, std::to_string(m_Char_A->Charcter->nowHP), color);
			}
			else
			{
				text->DrawEng(BasePos.x - (DATA_WIDTH / 2), BasePos.y - TEXT_SIZE * 0.625f, TEXT_SIZE, TEXT_SIZE / 3 * 2, std::to_string(0), color);
			}


			BasePos.x = SCREEN_WIDTH + (DATA_WIDTH / 2) - X / 8 * 3;

			m_Polygon[2]->Draw(BasePos.x, BasePos.y, 0, 0, DATA_WIDTH, DATA_HEIGHT, DATA_WIDTH, DATA_HEIGHT);

			if (m_Char_B->Charcter->GetAlly())
			{
				color.a = color.c = { 0.0f, 0.0f, 0.1f, 1.0f };
				color.b = color.d = { 0.0f, 0.0f, 0.8f, 1.0f };
			}
			else
			{
				color.a = color.c = { 0.1f, 0.0f, 0.0f, 1.0f };
				color.b = color.d = { 0.8f, 0.0f, 0.0f, 1.0f };
			}
			Bar = DATA_WIDTH * 0.84f / m_Char_B->Charcter->GetStatus()->HP * m_Char_B->Charcter->nowHP;
			m_Polygon[3]->Draw((BasePos.x - DATA_WIDTH * 0.06f) - (DATA_WIDTH * 0.84f - Bar) / 2, BasePos.y, 0, 0, Bar, DATA_HEIGHT / 2, DATA_WIDTH * 0.84f, DATA_HEIGHT / 2, color);

			m_Polygon[4]->Draw(BasePos.x, BasePos.y, 0, 0, DATA_WIDTH, DATA_HEIGHT, DATA_WIDTH, DATA_HEIGHT);
			m_Polygon[5]->Draw(BasePos.x - (DATA_WIDTH / 2), BasePos.y, 0, 0, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 7);
			color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
			if (m_Char_B->Charcter->nowHP >= 10)
			{
				text->DrawEng(BasePos.x - (DATA_WIDTH / 2) - TEXT_SIZE / 2, BasePos.y - TEXT_SIZE*0.625f, TEXT_SIZE, TEXT_SIZE / 3 * 2, std::to_string(m_Char_B->Charcter->nowHP), color);
			}
			else if (m_Char_B->Charcter->nowHP > 0)
			{
				text->DrawEng(BasePos.x - (DATA_WIDTH / 2), BasePos.y - TEXT_SIZE * 0.625f, TEXT_SIZE, TEXT_SIZE / 3 * 2, std::to_string(m_Char_B->Charcter->nowHP), color);
			}
			else
			{
				text->DrawEng(BasePos.x - (DATA_WIDTH / 2), BasePos.y - TEXT_SIZE * 0.625f, TEXT_SIZE, TEXT_SIZE / 3 * 2, std::to_string(0), color);
			}
			camera->SetViewPos(view.x, view.y, view.z, view.w);
		}
	}
}


void CSystemBattle::Damage()
{
	if (m_Char_B->Charcter->nowHP > 0)
	{
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