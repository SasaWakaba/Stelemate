#ifndef CSKYBOX_H_
#define CSKYBOX_H_

class CSkyBox:public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	CTexture* m_Texture[2];

	bool bNight;
	float frame;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
	void Draw(XMMATRIX trans);

	void SetNight(bool bEnable) { bNight = bEnable; }
};

#endif // !CSKYBOX_H_
