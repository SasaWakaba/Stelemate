#ifndef WALL_H_
#define WALL_H_

class CBattleRand:public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw(XMMATRIX world, CTexture* tex);
};

#endif