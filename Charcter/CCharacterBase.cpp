#include "../common/main.h"
#include "CCharacterData.h"
#include "CWeaponData.h"

#include "CCharcterBase.h"

XMFLOAT3 CCharcterBase::GetLocation() { return m_Location; }

void CCharcterBase::SetLocation(XMFLOAT3 pos) { m_Location = pos; }

STATUS* CCharcterBase::GetStatus() { return &m_Status; }

void CCharcterBase::SetDestroy() { bDead = true; }

void CCharcterBase::SetTurnMove(bool bEnable) { bTurnMove = bEnable; }

bool CCharcterBase::GetTurnMove() { return bTurnMove; }

void CCharcterBase::SetAlly(bool bEnable) { bAlly = bEnable; if(!bAlly)m_Rotation.y = 180.0f; }

void CCharcterBase::SetRotation(XMFLOAT3 rot) { m_Rotation = rot; }

bool CCharcterBase::GetAlly() { return bAlly; }

void CCharcterBase::SetWeapon(WeaponStatus* weapon) { m_Weapon = weapon; }

WeaponStatus* CCharcterBase::GetWeapon() { return m_Weapon; }

void CCharcterBase::SetName(std::string name) { this->name = name; }

std::string CCharcterBase::GetName() { return name; }

bool CCharcterBase::Destroy()
{
	if (bDead)
	{
		Finalize();
		delete this;
		return true;
	}
	else
	{
		return false;
	}
}

void CCharcterBase::Update()
{
	if (bMoveLocation)
	{
		if (cnt < 15)
		{
			m_Location.x += m_MoveLocation.x / 15.0f;
			m_Location.y += m_MoveLocation.y / 15.0f;
			m_Location.z += m_MoveLocation.z / 15.0f;
			cnt++;
		}
		else
		{
			bMoveLocation = false;
		}
	}
}

void CCharcterBase::MoveLocation(XMFLOAT3 pos)
{
	m_MoveLocation = XMFLOAT3(pos.x - m_Location.x, pos.y - m_Location.y, pos.z - m_Location.z);
	m_Rotation.y = atan2f(pos.z - m_Location.z, pos.x - m_Location.x);
	if (m_Rotation.y < 0)
	{
		m_Rotation.y = m_Rotation.y + 2 * PI;
	}
	m_Rotation.y = m_Rotation.y * 360 / (2 * PI);
	m_Rotation.y -= 90.0f;
	m_Rotation.y *= -1.0f;
	bMoveLocation = true;
	cnt = 0;
}