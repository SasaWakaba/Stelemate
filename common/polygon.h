#ifndef POLYGON_H_
#define POLYGON_H_

#include "Game_Object.h"
class CTexture;


class CPolygon:public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture = NULL;

	float X, Y, Width, Height;
public:
	CPolygon():X(0),Y(0),Width(200.0f), Height(200.0f){}
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void Load(const char* filename);
	void SetPosition(float x, float y, float width, float height){ X = x; Y = y; Width = width; Height = height; }

	void Draw(float dx, float dy, float tx, float ty, float tw, float th, float w, float h);

	void Draw(float dx, float dy, float tx, float ty, float tw, float th, float w, float h, VertexColor_4 color);
};

#endif