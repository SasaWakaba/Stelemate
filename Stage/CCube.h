#ifndef CCUBE_H_
#define CCUBE_H_

#include "../common/main.h"
#include "../common/texture.h"

class CCube
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
public:
	void Initialize();
	void Finalize();
	void Draw(XMMATRIX* world, CTexture* tex);
};

#endif // !CCUBE_H_
