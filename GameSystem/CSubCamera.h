#ifndef CSUB_CAMERA_H_
#define CSUB_CAMERA_H_


class CSubCamera :public CGameObject
{
private:
	XMMATRIX	m_ViewMatrix;
	RECT m_Viewport;

	XMFLOAT3 m_Eye;					//カメラ座標
	XMFLOAT3 m_at;					//見てる場所(注視点)
	XMFLOAT3 m_CameraFront;			//カメラの正面、長さ１
	XMFLOAT3 m_CameraRight;			//カメラの右側、長さ１
	XMFLOAT3 m_CameraUp;			//カメラの上、長さ１
	float m_Length;					//見てる場所までの長さ



public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void SetViewPos(int x, int y, int w, int h);
};
#endif // !CSUB_CAMERA_H_