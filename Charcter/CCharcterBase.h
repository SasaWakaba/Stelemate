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

	//描画場所取得
	XMFLOAT3 GetLocation() { return m_Location; }

	//描画場所設定
	void SetLocation(XMFLOAT3 pos) { m_Location = pos; }

	//描画場所移動開始
	void MoveLocation(XMFLOAT3 pos) 
	{
		m_MoveLocation = XMFLOAT3(pos.x - m_Location.x, pos.y - m_Location.y, pos.z - m_Location.z);
		bMoveLocation = true;
		cnt = 0;
	}

	//ステータス取得
	STATUS* GetStatus() { return &m_Status; }

	//死亡セット
	void SetDestroy() { bDead = true; }

	//ターン行動設定
	void SetTurnMove(bool bEnable) { bTurnMove = bEnable; }

	bool GetTurnMove() { return bTurnMove; }

	//味方ユニットか否か設定
	void SetAlly(bool bEnable) { bAlly = bEnable; }

	//味方ユニットか否か取得
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

	//武器設定
	void SetWeapon(WeaponStatus* weapon) { m_Weapon = weapon; }

	//武器取得
	WeaponStatus* GetWeapon() { return m_Weapon; }
};


#endif // !CCHARCTER_H_
