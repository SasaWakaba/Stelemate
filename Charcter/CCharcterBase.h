#ifndef CCHARCTER_BASE_H_
#define CCHARCTER_BASE_H_

#include "../common/main.h"
#include "CCharacterData.h"
#include "CWeaponData.h"


class CCharcterBase
{
protected:
	XMFLOAT3		m_Scaling;
	XMFLOAT3		m_Location;
	XMFLOAT3		m_Rotation;

	XMFLOAT3		m_MoveLocation;

	STATUS			m_Status;

	WeaponStatus*	m_Weapon = nullptr;

	int				cnt;

	bool			bDead = false;

	bool			bTurnMove = false;

	bool			bAlly;

	bool			bMoveLocation = false;
public:
	JOBCLASS		m_JobClass;
	CCharcterBase(JOBCLASS job):m_JobClass(job){}
	virtual ~CCharcterBase() {}

	virtual void Initialize() {}
	virtual void Finalize() {}
	virtual void Update() 
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
	virtual void Draw() {}

	//�`��ꏊ�擾
	XMFLOAT3 GetLocation() { return m_Location; }

	//�`��ꏊ�ݒ�
	void SetLocation(XMFLOAT3 pos) { m_Location = pos; }

	//�`��ꏊ�ړ��J�n
	void MoveLocation(XMFLOAT3 pos) 
	{
		m_MoveLocation = XMFLOAT3(pos.x - m_Location.x, pos.y - m_Location.y, pos.z - m_Location.z);
		bMoveLocation = true;
		cnt = 0;
	}

	//�X�e�[�^�X�擾
	STATUS* GetStatus() { return &m_Status; }

	//���S�Z�b�g
	void SetDestroy() { bDead = true; }

	//�^�[���s���ݒ�
	void SetTurnMove(bool bEnable) { bTurnMove = bEnable; }

	bool GetTurnMove() { return bTurnMove; }

	//�������j�b�g���ۂ��ݒ�
	void SetAlly(bool bEnable) { bAlly = bEnable; }

	//�������j�b�g���ۂ��擾
	bool GetAlly() { return bAlly; }

	bool Destroy()
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

	//����ݒ�
	void SetWeapon(WeaponStatus* weapon) { m_Weapon = weapon; }

	//����擾
	WeaponStatus* GetWeapon() { return m_Weapon; }
};


#endif // !CCHARCTER_H_
