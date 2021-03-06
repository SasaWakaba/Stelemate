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
#include "../common/TextureManager.h"
#include "../common/ModelManager.h"
#include "WorldManager.h"

#include "CSystemBattle.h"

#define DATA_WIDTH (SCREEN_WIDTH / 3)
#define DATA_HEIGHT (SCREEN_HEIGHT / 10)

#define Quarticout(t, b, c, d) ((c) * (1 - powf((1.0f - (t) / (d)), 4.0f)) + (b))
#define ease_out(t, b, c, d) ((c) * (-(powf(2.0f, (-10.0f * (t) / (d)))) + 1) + (b))

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
float	CSystemBattle::charaRot[2];

int decideJob(CCharcterBase* chara)
{
	switch (chara->m_JobClass)
	{
	case Swordman:
		if (chara->GetAlly())
		{
			return 0;
		}
		else
		{
			return 1;
		}
		break;
	case Lancer:
		if (chara->GetAlly())
		{
			return 2;
		}
		else
		{
			return 3;
		}
	case Archer:
		if (chara->GetAlly())
		{
			return 4;
		}
		else
		{
			return 5;
		}
	case Sorcerer:
		if (chara->GetAlly())
		{
			return 6;
		}
		else
		{
			return 7;
		}
		break;
	case Healer:
		if (chara->GetAlly())
		{
			return 8;
		}
		else
		{
			return 9;
		}
		break;
	}
	return -1;
}

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
		charaRot[0] = 90.0f;
		charaRot[1] = -90.0f;
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

	tex[0] = CTextureManager::LoadTexture("asset/texture/grass01.jpg");
	tex[1] = CTextureManager::LoadTexture("asset/texture/forest.jpg");

	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		Model[i] = new CModelAnimation();
	}
	Model[0] = CModelManager::LoadModel("asset/model/Character/Swordman/swordman_Idle.fbx");
	CModelManager::LoadAnim(Model[0], "asset/model/Character/Swordman/swordman_run.fbx");
	CModelManager::LoadAnim(Model[0], "asset/model/Character/Swordman/swordman_Attack.fbx");

	Model[1] = CModelManager::LoadModel("asset/model/Character/Enemy/swordman_Idle.fbx");
	CModelManager::LoadAnim(Model[1], "asset/model/Character/Enemy/swordman_run.fbx");
	CModelManager::LoadAnim(Model[1], "asset/model/Character/Enemy/swordman_Attack.fbx");

	Model[2] = CModelManager::LoadModel("asset/model/Character/Lancer/Lancer_Idle.fbx");
	CModelManager::LoadAnim(Model[2], "asset/model/Character/Lancer/Lancer_run.fbx");
	CModelManager::LoadAnim(Model[2], "asset/model/Character/Lancer/Lancer_Attack.fbx");

	Model[3] = CModelManager::LoadModel("asset/model/Character/Enemy/Lancer_Idle.fbx");
	CModelManager::LoadAnim(Model[3], "asset/model/Character/Enemy/Lancer_run.fbx");
	CModelManager::LoadAnim(Model[3], "asset/model/Character/Enemy/Lancer_Attack.fbx");

	Model[4] = CModelManager::LoadModel("asset/model/Character/Archer/Archer_Idle.fbx");
	CModelManager::LoadAnim(Model[4], "asset/model/Character/Archer/Archer_run.fbx");
	CModelManager::LoadAnim(Model[4], "asset/model/Character/Archer/Archer_Attack.fbx");

	Model[5] = CModelManager::LoadModel("asset/model/Character/Enemy/Archer_Idle.fbx");
	CModelManager::LoadAnim(Model[5], "asset/model/Character/Enemy/Archer_run.fbx");
	CModelManager::LoadAnim(Model[5], "asset/model/Character/Enemy/Archer_Attack.fbx");


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

	sky->Finalize();
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
			{
				if (X < SCREEN_WIDTH)
				{
					int age = (int)((Frame - CreateFrame) * 2.0f);
					X = (sin(-PI / 2 + PI / 120 * age) + 1) / 2 * SCREEN_WIDTH;
				}
				else if (view.x > SCREEN_WIDTH / 6)
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
				camera->SetViewPos((int)view.x, (int)view.y, (int)view.z, (int)view.w);
				Model[decideJob(m_Char_A->Charcter)]->Update(0, Frame);
				Model[decideJob(m_Char_B->Charcter)]->Update(0, Frame);
				break;
			}
			case MoveCamera:
				//if (AnimFrame > 10)
				//{
				//	Damage();
				//	bBattle = false;
				//}
				//AnimFrame++;
				break;

			case MoveCharA:
			{
				if (charaPos[0].x < 2.0f && m_Char_A->Charcter->m_JobClass != Archer)
				{
					int age = (Frame - CreateFrame);
					charaPos[0].x = Quarticout(1.0f / 30.0f * age, -5.0f,7.0f, 1);
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
					else if (m_Char_B->Charcter->nowHP - Damage_A < 0)
					{
						Damage_A = m_Char_B->Charcter->nowHP;
					}
					DamageCount = 0;
					Fase = AttackA;
					CreateFrame = Frame;
				}
				else
				{
					Fase = End;
				}
				Model[decideJob(m_Char_A->Charcter)]->Update(1, Frame);
				Model[decideJob(m_Char_B->Charcter)]->Update(0, Frame);
				break;
			}
			case AttackA:
			{
				int age = Frame - CreateFrame;
				if (age < 60)
				{
					Model[decideJob(m_Char_A->Charcter)]->Update(2, age);
					Model[decideJob(m_Char_B->Charcter)]->Update(0, Frame);
				}
				else if (charaPos[0].x > -5.0f && m_Char_A->Charcter->m_JobClass != Archer)
				{
					age = age - 60;
					charaPos[0].x = Quarticout(1.0f / 30.0f * age, 2.0f, -7.0f, 1);
					charaRot[0] = -90.0f;
					Model[decideJob(m_Char_A->Charcter)]->Update(1, Frame);
					Model[decideJob(m_Char_B->Charcter)]->Update(0, Frame);
					if (DamageCount < Damage_A)
					{
						DamageCount += 0.2f;
					}
					else
					{
						DamageCount = Damage_A;
					}
				}
				else
				{
					charaRot[0] = 90.0f;
					Model[decideJob(m_Char_A->Charcter)]->Update(0, Frame);
					Model[decideJob(m_Char_B->Charcter)]->Update(0, Frame);
					if (DamageCount < Damage_A)
					{
						DamageCount += 0.2f;
					}
					else
					{
						DamageCount = Damage_A;
					}
				}


				if (DamageCount == Damage_A && charaRot[0] == 90.0f)
				{
					m_Char_B->Charcter->nowHP -= Damage_A;
					if (m_Char_B->Charcter->nowHP > 0 && m_Char_A->Charcter->m_JobClass != Archer)
					{
						Fase = MoveCharB;
						CreateFrame = Frame;
					}
					else if(m_Char_B->Charcter->nowHP <= 0)
					{
						if (m_Char_A->Charcter->GetAlly())
						{
							WorldManager::LevelUpMember(m_Char_A->Charcter->GetName().c_str(), m_Char_B->Charcter->Level);
						}

						if (m_Char_B->Charcter->GetAlly())
						{
							if (WorldManager::GetGameMode() == Classic)
							{
								WorldManager::GetParty()[m_Char_B->Charcter->GetName()] = nullptr;
								m_Char_B->Charcter->SetDestroy();
							}
							else
							{
								m_Char_B->bChar = false;
								//m_Char_B->Charcter = nullptr;
							}
							WorldManager::AddDeadCount();
						}
						else
						{
							m_Char_B->Charcter->SetDestroy();
							WorldManager::AddSubjugation();
						}
						Fase = End;
					}
					else
					{
						Fase = End;
					}
				}
				break;
			}
			case MoveCharB:
			{
				if (charaPos[1].x > -2.0f && m_Char_B->Charcter->m_JobClass != Archer)
				{
					int age = (Frame - CreateFrame);
					charaPos[1].x = Quarticout(1.0f / 30.0f * age, 5.0f, -7.0f, 1);
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
					else if (m_Char_A->Charcter->nowHP - Damage_B < 0)
					{
						Damage_B = m_Char_A->Charcter->nowHP;
					}

					DamageCount = 0;
					Fase = AttackB;
					CreateFrame = Frame;
				}

				Model[decideJob(m_Char_A->Charcter)]->Update(0, Frame);
				Model[decideJob(m_Char_B->Charcter)]->Update(1, Frame);
				break;
			}
			case AttackB:
			{
				int age = Frame - CreateFrame;
				if (age < 60)
				{
					Model[decideJob(m_Char_A->Charcter)]->Update(0, Frame);
					Model[decideJob(m_Char_B->Charcter)]->Update(2, age);
				}
				else if (charaPos[1].x < 5.0f  && m_Char_B->Charcter->m_JobClass != Archer)
				{
					age = age - 60;
					charaPos[1].x = Quarticout(1.0f / 30.0f * age, -2.0f, 7.0f, 1);
					charaRot[1] = 90.0f;
					Model[decideJob(m_Char_A->Charcter)]->Update(0, Frame);
					Model[decideJob(m_Char_B->Charcter)]->Update(1, Frame);
					if (DamageCount < Damage_B)
					{
						DamageCount += 0.2f;
					}
					else
					{
						DamageCount = Damage_B;
					}
				}
				else
				{
					charaRot[1] = -90.0f;
					Model[decideJob(m_Char_A->Charcter)]->Update(0, Frame);
					Model[decideJob(m_Char_B->Charcter)]->Update(0, Frame);
					if (DamageCount < Damage_B)
					{
						DamageCount += 0.2f;
					}
					else
					{
						DamageCount = Damage_B;
					}
				}


				if (DamageCount == Damage_B && charaRot[1] == -90.0f)
				{
					m_Char_A->Charcter->nowHP -= Damage_B;
					if (m_Char_A->Charcter->nowHP <= 0)
					{
						if (m_Char_B->Charcter->GetAlly())
						{
							WorldManager::LevelUpMember(m_Char_B->Charcter->GetName().c_str(), m_Char_A->Charcter->Level);
						}


						if (m_Char_A->Charcter->GetAlly())
						{
							if (WorldManager::GetGameMode() == Classic)
							{
								WorldManager::GetParty()[m_Char_A->Charcter->GetName()] = nullptr;
								m_Char_A->Charcter->SetDestroy();
							}
							else
							{
								m_Char_A->bChar = false;
								//m_Char_A->Charcter = nullptr;
							}
							WorldManager::AddDeadCount();
						}
						else
						{
							m_Char_A->Charcter->SetDestroy();
							WorldManager::AddSubjugation();
						}

						Fase = End;
					}
					else
					{
						Fase = End;
					}
				}
				break;
			}
			case End:
			{
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
					int age = (Frame - CreateFrame) * 2;
					X = X + (sin(-PI / 2 + PI / 120 * age) + 1) / 2 * -SCREEN_WIDTH;
				}
				else
				{
					bBattle = false;
					m_Char_A = nullptr;
					m_Char_B = nullptr;
					X = 0.0f;
				}
				camera->SetViewPos((int)view.x, (int)view.y, (int)view.z, (int)view.w);
				break;
			}
		}
		sky->Update();
	}
	else
	{
		bMove = false;
	}
	Frame++;
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
			//��
			world = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
			sky->Draw(world);

			//�n�ʂP
			world = XMMatrixScaling(5.0f, 5.0f, 5.0f);					//�g��E�k��
			world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);	//��]
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

			//�n�ʂQ
			world = XMMatrixScaling(5.0f, 5.0f, 5.0f);					//�g��E�k��
			world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);	//��]
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
		//�L�����N�^�[
		{
			world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
			world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(charaRot[0]), 0.0f);
			world *= XMMatrixTranslation(charaPos[0].x, charaPos[0].y, charaPos[0].z);
			switch (m_Char_A->Charcter->m_JobClass)
			{
			case Swordman:
				if (m_Char_A->Charcter->GetAlly())
				{
					Model[0]->Draw(world);
				}
				else
				{
					Model[1]->Draw(world);
				}
				break;
			case Lancer:
				if (m_Char_A->Charcter->GetAlly())
				{
					Model[2]->Draw(world);
				}
				else
				{
					Model[3]->Draw(world);
				}
				break;
			case Archer:
				if (m_Char_A->Charcter->GetAlly())
				{
					Model[4]->Draw(world);
				}
				else
				{
					Model[5]->Draw(world);
				}
			case Sorcerer:
				break;
			}
			world = XMMatrixScaling(3.0f, 3.0f, 3.0f);
			world *= XMMatrixTranslation(charaPos[0].x, 92.5f + 0.01f, charaPos[0].z);
			shadow->Draw(world);

			world = XMMatrixScaling(0.5f, 0.5f, 0.5f);
			world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(charaRot[1]), 0.0f);
			world *= XMMatrixTranslation(charaPos[1].x, charaPos[1].y, charaPos[1].z);
			switch (m_Char_B->Charcter->m_JobClass)
			{
			case Swordman:
				if (m_Char_B->Charcter->GetAlly())
				{
					Model[0]->Draw(world);
				}
				else
				{
					Model[1]->Draw(world);
				}
				break;
			case Lancer:
				if (m_Char_B->Charcter->GetAlly())
				{
					Model[2]->Draw(world);
				}
				else
				{
					Model[3]->Draw(world);
				}
				break;
			case Archer:
				if (m_Char_B->Charcter->GetAlly())
				{
					Model[4]->Draw(world);
				}
				else
				{
					Model[5]->Draw(world);
				}
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
			if (Fase == AttackB)
			{
				Bar = DATA_WIDTH * 0.84f / m_Char_A->Charcter->GetStatus()->HP * m_Char_A->Charcter->nowHP - (DATA_WIDTH * 0.84f / m_Char_A->Charcter->GetStatus()->HP) * DamageCount;
			}
			else
			{
				Bar = DATA_WIDTH * 0.84f / m_Char_A->Charcter->GetStatus()->HP * m_Char_A->Charcter->nowHP;
			}
			m_Polygon[3]->Draw((BasePos.x - DATA_WIDTH * 0.06f) - (DATA_WIDTH * 0.84f - Bar) / 2, BasePos.y, 0, 0, Bar, DATA_HEIGHT / 2, DATA_WIDTH * 0.84f, DATA_HEIGHT / 2, color);

			m_Polygon[4]->Draw(BasePos.x, BasePos.y, 0, 0, DATA_WIDTH, DATA_HEIGHT, DATA_WIDTH, DATA_HEIGHT);
			m_Polygon[5]->Draw(BasePos.x - (DATA_WIDTH / 2), BasePos.y, 0, 0, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 7);
			color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
			if (m_Char_A->Charcter->nowHP >= 10)
			{
				text->DrawEng((int)(BasePos.x - (DATA_WIDTH / 2) - TEXT_SIZE / 2), (int)(BasePos.y - TEXT_SIZE * 0.625f), (int)TEXT_SIZE, (int)(TEXT_SIZE / 3 * 2), std::to_string(m_Char_A->Charcter->nowHP), color);
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

			if (Fase == AttackA)
			{
				Bar = DATA_WIDTH * 0.84f / m_Char_B->Charcter->GetStatus()->HP * m_Char_B->Charcter->nowHP - (DATA_WIDTH * 0.84f / m_Char_B->Charcter->GetStatus()->HP) * DamageCount;
			}
			else
			{
				Bar = DATA_WIDTH * 0.84f / m_Char_B->Charcter->GetStatus()->HP * m_Char_B->Charcter->nowHP;
			}
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