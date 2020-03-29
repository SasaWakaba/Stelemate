#include "../common/main.h"
#include "../common/renderer.h"

#include "CCharcterBase.h"
#include "../common/model.h"
#include "../common/ModelAnimation.h"
#include "../common/ModelManager.h"
#include "CCharacterData.h"
#include "CWeaponData.h"

#include "CJob.h"

void CSwordsman::Initialize()
{
	m_Model[0] = new CModelAnimation();
	m_Model[0]->Load("asset/model/Character/Swordman/swordman_Idle.fbx");
	m_Model[0]->LoadAnim("asset/model/Character/Swordman/swordman_run.fbx");

	m_Model[1] = new CModelAnimation();
	m_Model[1]->Load("asset/model/Character/Enemy/swordman_Idle.fbx");
	m_Model[1]->LoadAnim("asset/model/Character/Enemy/swordman_run.fbx");
	m_Status = CCharacterData::m_CharData["Œ•Žm"];
	nowHP = m_Status.HP;
	Level = 1;
	m_Weapon = &CWeaponData::m_WeaponData["“S‚ÌŒ•"];
	frame = 0;
}

void CSwordsman::Finalize()
{
	m_Model[0]->UnLoad();
	delete m_Model[0];
	m_Model[1]->UnLoad();
	delete m_Model[1];
}

void CSwordsman::Update()
{
	CCharcterBase::Update();
	if (bMoveLocation)
	{
		if (bAlly)
		{
			m_Model[0]->Update(1, frame);
		}
		else
		{
			m_Model[1]->Update(1, frame);
		}
	}
	else
	{
		if (bAlly)
		{
			m_Model[0]->Update(0, frame);
		}
		else
		{
			m_Model[1]->Update(0, frame);
		}
	}
	frame++;
}
void CSwordsman::Draw()
{
	XMMATRIX world;
	world = XMMatrixScaling(0.25f, 0.25f, 0.25f);

	if (bAlly)
	{
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(m_Rotation.y), 0.0f);
		world *= XMMatrixTranslation(m_Location.x, m_Location.y, m_Location.z);
		m_Model[0]->Draw(world);
	}
	else
	{
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(m_Rotation.y), 0.0f);
		world *= XMMatrixTranslation(m_Location.x, m_Location.y, m_Location.z);
		m_Model[1]->Draw(world);
	}
}

void CLancer::Initialize()
{
	m_Model[0] = new CModelAnimation();
	m_Model[0]->Load("asset/model/Character/Lancer/Lancer_idle.fbx");
	m_Model[0]->LoadAnim("asset/model/Character/Lancer/Lancer_run.fbx");

	m_Model[1] = new CModelAnimation();
	m_Model[1]->Load("asset/model/Character/Enemy/Lancer_idle.fbx");
	m_Model[1]->LoadAnim("asset/model/Character/Enemy/Lancer_run.fbx");

	m_Status = CCharacterData::m_CharData["‘„•º"];
	nowHP = m_Status.HP;
	Level = 1;
	m_Weapon = &CWeaponData::m_WeaponData["“S‚Ì‘„"];
	frame = 0;
}

void CLancer::Finalize()
{
	m_Model[0]->UnLoad();
	delete m_Model[0];
	m_Model[1]->UnLoad();
	delete m_Model[1];
}
void CLancer::Update()
{
	CCharcterBase::Update();
	if (bMoveLocation)
	{
		if (bAlly)
		{
			m_Model[0]->Update(1, frame);
		}
		else
		{
			m_Model[1]->Update(1, frame);
		}
	}
	else
	{
		if (bAlly)
		{
			m_Model[0]->Update(0, frame);
		}
		else
		{
			m_Model[1]->Update(0, frame);
		}
	}
	frame++;
}

void CLancer::Draw()
{
	XMMATRIX world;
	world = XMMatrixScaling(0.25f, 0.25f, 0.25f);
	world *= XMMatrixRotationRollPitchYaw(0.0f, m_Rotation.y, 0.0f);
	world *= XMMatrixTranslation(m_Location.x, m_Location.y, m_Location.z);
	if (bAlly)
	{
		m_Model[0]->Draw(world);
	}
	else
	{
		m_Model[1]->Draw(world);
	}
}


void CArcher::Initialize() 
{
	m_Model[0] = new CModelAnimation();
	m_Model[0]->Load("asset/model/Character/Archer/Archer_idle.fbx");
	m_Model[0]->LoadAnim("asset/model/Character/Archer/Archer_run.fbx");

	m_Model[1] = new CModelAnimation();
	m_Model[1]->Load("asset/model/Character/Enemy/Archer_idle.fbx");
	m_Model[1]->LoadAnim("asset/model/Character/Enemy/Archer_run.fbx");
	m_Status = CCharacterData::m_CharData["‹|Žg‚¢"];
	nowHP = m_Status.HP;
	Level = 1;
	m_Weapon = &CWeaponData::m_WeaponData["“S‚Ì‹|"];
	frame = 0;
}

void CArcher::Finalize() 
{
	m_Model[0]->UnLoad();
	delete m_Model[0];
	m_Model[1]->UnLoad();
	delete m_Model[1];
}

void CArcher::Update() 
{
	CCharcterBase::Update();
	if (bMoveLocation)
	{
		if (bAlly)
		{
			m_Model[0]->Update(1, frame);
		}
		else
		{
			m_Model[1]->Update(1, frame);
		}
	}
	else
	{
		if (bAlly)
		{
			m_Model[0]->Update(0, frame);
		}
		else
		{
			m_Model[1]->Update(0, frame);
		}
	}
	frame++;
}

void CArcher::Draw() 
{
	XMMATRIX world;
	world = XMMatrixScaling(0.25f, 0.25f, 0.25f);
	world *= XMMatrixRotationRollPitchYaw(0.0f, m_Rotation.y, 0.0f);
	world *= XMMatrixTranslation(m_Location.x, m_Location.y, m_Location.z);
	if (bAlly)
	{
		m_Model[0]->Draw(world);
	}
	else
	{
		m_Model[1]->Draw(world);
	}
}