#include  "../common/main.h"
#include "../common/renderer.h"
#include "../common/texture.h"
#include "../common/polygon.h"
#include "../common/Game_Object.h"
#include "TitleBackground.h"

void CTitleBackground::Initialize()
{
	for (int i = 0; i < 5; i++)
	{
		texture[i] = new CPolygon();
		texture[i]->Initialize();
	}

	texture[0]->Load("asset/texture/ResultUI005.png");
	texture[1]->Load("asset/texture/ResultUI006.png");
	texture[2]->Load("asset/texture/ResultUI007.png");

	texture[3]->Load("asset/texture/TitleUI009.png");
	texture[4]->Load("asset/texture/TitleUI010.png");
	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	CRenderer::SetClearColor(color);
	frame = 0;
}
void CTitleBackground::Finalize()
{
	for (int i = 0; i < 5; i++)
	{
		texture[i]->Finalize();
		delete texture[i];
	}
}
void CTitleBackground::Update()
{
	frame++;
}
void CTitleBackground::Draw()
{
	VertexColor_4 color;
	color.setAll(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	//texture[0]->Draw(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, XMConvertToRadians(-frame * 0.1f), color);
	//texture[1]->Draw(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, XMConvertToRadians(frame / 3 * 0.1f), color);

	texture[4]->Draw(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, XMConvertToRadians(frame / 2 * 0.1f), color);
	texture[2]->Draw(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH*0.6f, SCREEN_WIDTH*0.6f, SCREEN_WIDTH*0.6f, SCREEN_WIDTH*0.6f, color);
	texture[3]->Draw(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, SCREEN_WIDTH*0.8f, XMConvertToRadians(-frame / 2 * 0.1f), color);
}