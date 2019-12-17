#ifndef CCIRCLE_SHADOW_H_
#define CCIRCLE_SHADOW_H_

#include "Game_Object.h"

class CCircleShadow :public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw(XMMATRIX world);
};

#endif