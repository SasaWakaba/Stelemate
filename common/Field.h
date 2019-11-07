#ifndef FIELD_H_
#define FIELD_H_


class CField :public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

#endif