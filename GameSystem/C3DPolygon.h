#ifndef C3DPOLYGON_H_
#define C3DPOLYGON_H_

#include "../common/main.h"

class C3DPolygon
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw(XMMATRIX world);

	void Draw(CTexture* tex, XMMATRIX world, VertexColor_4 color);
};


#endif // !C3DPOLYGON_H_

