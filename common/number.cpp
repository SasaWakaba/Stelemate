#include "../common/main.h"
#include "../common/texture.h"
#include "../common/polygon.h"
#include "number.h"

#define NUMBER_MAX (10)




void CNumber::Initialize(void)
{
	m_Polygon = new CPolygon();
	m_Polygon->Initialize();
	m_Polygon->Load("asset/texture/number.png");
}

void CNumber::Finalize(void)
{
	m_Polygon->Finalize();
	delete m_Polygon;
}

void CNumber::Draw(float x, float y, float w, float h, int n)
{
	if (n > 9 || n < 0)
	{
		return;
	}
	float dx = w * n;
	float dy = 0.0f;
	VertexColor_4 color;
	color.setAll(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	m_Polygon->Draw(x, y, dx, dy, w, h, w * 10.0f, h, color);
}

void CNumber::Draw(float x, float y, float w, float h, int n, VertexColor_4 color)
{
	if (n > 9 || n < 0)
	{
		return;
	}
	float dx = w * n;
	float dy = 0.0f;
	m_Polygon->Draw(x, y, dx, dy, w, h, w * 10.0f, h, color);
}