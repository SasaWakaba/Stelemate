#pragma once

#include "Game_Object.h"

class CCamera:public CGameObject
{
private:
	XMMATRIX	m_ViewMatrix;
	RECT m_Viewport;

	static XMFLOAT3 m_Eye;					//�J�������W
	static XMFLOAT3 m_at;					//���Ă�ꏊ(�����_)
	XMFLOAT3 m_CameraFront;			//�J�����̐��ʁA�����P
	XMFLOAT3 m_CameraRight;			//�J�����̉E���A�����P
	XMFLOAT3 m_CameraUp;			//�J�����̏�A�����P
	float m_Length;					//���Ă�ꏊ�܂ł̒���

	static bool bMove;
	static XMFLOAT3 MoveLength;
	static int cnt;

public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	XMMATRIX* GetView();

	static void SetAt(XMFLOAT3 pos) { m_at = pos; }
	static void Move(XMFLOAT3 at) {
			MoveLength = XMFLOAT3(at.x - m_at.x, at.y - m_at.y, at.z - m_at.z);
			bMove = true;
			cnt = 0;
	}

	static XMFLOAT3 GetEye() { return m_Eye; }
};