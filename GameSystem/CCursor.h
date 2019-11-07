#ifndef CCURSOR_H_
#define CCURSOR_H_

#include "../common/main.h"
#include "../common/texture.h"


class CCursor
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;

	CTexture* m_Texture;
public:
	void Initialize();
	void Finalize();
	void Draw(XMMATRIX* world);
};

#endif // !CCURSOR_H_
