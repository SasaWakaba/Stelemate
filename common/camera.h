#pragma once

#include "Game_Object.h"

class CCamera:public CGameObject
{
private:
	XMMATRIX	m_ViewMatrix;
	RECT m_Viewport;

	static XMFLOAT3 m_Eye;					//カメラ座標
	static XMFLOAT3 m_at;					//見てる場所(注視点)
	XMFLOAT3 m_CameraFront;			//カメラの正面、長さ１
	XMFLOAT3 m_CameraRight;			//カメラの右側、長さ１
	XMFLOAT3 m_CameraUp;			//カメラの上、長さ１
	float m_Length;					//見てる場所までの長さ

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