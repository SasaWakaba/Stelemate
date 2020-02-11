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

	//�`��ꏊ�擾
	XMFLOAT3 GetLocation();

	//�`��ꏊ�ݒ�
	void SetLocation(XMFLOAT3 pos);

	//�`��ꏊ�ړ��J�n
	void MoveLocation(XMFLOAT3 pos);

	//�X�e�[�^�X�擾
	STATUS* GetStatus();

	//���S�Z�b�g
	void SetDestroy();

	//�^�[���s���ݒ�
	void SetTurnMove(bool bEnable);

	bool GetTurnMove();

	//�������j�b�g���ۂ��ݒ�
	void SetAlly(bool bEnable);

	//�������j�b�g���ۂ��擾
	bool GetAlly();

	bool Destroy();

	//����ݒ�
	void SetWeapon(WeaponStatus* weapon);

	//����擾
	WeaponStatus* GetWeapon();

	//���O�ݒ�(�v���C���[�p)
	void SetName(std::string name);

	//���O�擾(�v���C���[�p)
	std::string GetName();
};


#endif // !CCHARCTER_H_
