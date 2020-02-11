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

	std::string		name;
public:
	JOBCLASS		m_JobClass;
	int				nowHP = 0;
	int				Level;


	CCharcterBase(JOBCLASS job):m_JobClass(job){}
	virtual ~CCharcterBase() {}

	virtual void Initialize() {}
	virtual void Finalize() {}
	virtual void Update();
	virtual void Draw() {}

	//描画場所取得
	XMFLOAT3 GetLocation();

	//描画場所設定
	void SetLocation(XMFLOAT3 pos);

	//描画場所移動開始
	void MoveLocation(XMFLOAT3 pos);

	//ステータス取得
	STATUS* GetStatus();

	//死亡セット
	void SetDestroy();

	//ターン行動設定
	void SetTurnMove(bool bEnable);

	bool GetTurnMove();

	//味方ユニットか否か設定
	void SetAlly(bool bEnable);

	//味方ユニットか否か取得
	bool GetAlly();

	bool Destroy();

	//武器設定
	void SetWeapon(WeaponStatus* weapon);

	//武器取得
	WeaponStatus* GetWeapon();

	//名前設定(プレイヤー用)
	void SetName(std::string name);

	//名前取得(プレイヤー用)
	std::string GetName();
};


#endif // !CCHARCTER_H_
