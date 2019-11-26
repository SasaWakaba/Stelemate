#ifndef CSUB_CAMERA_H_
#define CSUB_CAMERA_H_


class CSubCamera :public CGameObject
{
private:
	XMMATRIX	m_ViewMatrix;
	RECT m_Viewport;

	XMFLOAT3 m_Eye;					//�J�������W
	XMFLOAT3 m_at;					//���Ă�ꏊ(�����_)
	XMFLOAT3 m_CameraFront;			//�J�����̐��ʁA�����P
	XMFLOAT3 m_CameraRight;			//�J�����̉E���A�����P
	XMFLOAT3 m_CameraUp;			//�J�����̏�A�����P
	float m_Length;					//���Ă�ꏊ�܂ł̒���



public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void SetViewPos(int x, int y, int w, int h);
};
#endif // !CSUB_CAMERA_H_