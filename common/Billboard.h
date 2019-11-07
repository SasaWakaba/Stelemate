#ifndef BILLBOARD_H_
#define BILLBOARD_H_


class CBillboard
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;
	int m_MaxTexture;
public:
	void Initialize();
	void Finalize();
	void Update(){}
	void Draw(XMMATRIX world);

	void Load(const char* filename);

};



#endif // !BILLBOARD_H_
