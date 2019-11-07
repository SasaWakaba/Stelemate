#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "Game_Object.h"
#include "polygon.h"


void CPolygon::Initialize()
{
	//=======================================================
	//テクスチャ読み込み
	//=======================================================
	m_Texture = new CTexture();
}

void CPolygon::Load(const char* filename)
{
	m_Texture->LoadTex(filename);
}

void CPolygon::Finalize()
{
	if (m_VertexBuffer != nullptr)
	{
	m_VertexBuffer->Release();
	}
	m_Texture->Unload();
	delete m_Texture;
}

void CPolygon::Update()
{
	 
}

void CPolygon::Draw()
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(X, Y, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(X + Width, Y, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(X, Y + Height, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(X + Width, Y + Height, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//=======================================================
	//頂点バッファ生成
	//=======================================================
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::SetTexture(m_Texture);	//テクスチャ設定
	CRenderer::SetWorldViewProjection2D();	//2Dマトリクス設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定
	CRenderer::GetDeviceContext()->Draw(4,0);		//ポリゴン描画
}


void CPolygon::Draw(float dx, float dy, float tx, float ty, float tw, float th, float w, float h)
{
	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = ((float)tx + tw) / w;
	float v1 = ((float)ty + th) / h;

	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(dx - (tw / 2), dy - (th / 2), 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(u0, v0);

	vertex[1].Position = XMFLOAT3(dx + (tw / 2), dy - (th / 2), 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(u1, v0);

	vertex[2].Position = XMFLOAT3(dx - (tw / 2), dy + (th / 2), 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(u0, v1);

	vertex[3].Position = XMFLOAT3(dx + (tw / 2), dy + (th / 2), 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(u1, v1);

	//=======================================================
	//頂点バッファ生成
	//=======================================================
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	CRenderer::SetDepthEnable(false);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::SetTexture(m_Texture);	//テクスチャ設定
	CRenderer::SetWorldViewProjection2D();	//2Dマトリクス設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定
	CRenderer::GetDeviceContext()->Draw(4, 0);		//ポリゴン描画

	CRenderer::SetDepthEnable(true);
}


void CPolygon::Draw(float dx, float dy, float tx, float ty, float tw, float th, float w, float h, VertexColor_4 color)
{
	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = ((float)tx + tw) / w;
	float v1 = ((float)ty + th) / h;

	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(dx - (tw / 2), dy - (th / 2), 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = color.a;
	vertex[0].TexCoord = XMFLOAT2(u0, v0);

	vertex[1].Position = XMFLOAT3(dx + (tw / 2), dy - (th / 2), 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = color.b;
	vertex[1].TexCoord = XMFLOAT2(u1, v0);

	vertex[2].Position = XMFLOAT3(dx - (tw / 2), dy + (th / 2), 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = color.c;
	vertex[2].TexCoord = XMFLOAT2(u0, v1);

	vertex[3].Position = XMFLOAT3(dx + (tw / 2), dy + (th / 2), 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = color.d;
	vertex[3].TexCoord = XMFLOAT2(u1, v1);

	//=======================================================
	//頂点バッファ生成
	//=======================================================
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	CRenderer::SetDepthEnable(false);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::SetTexture(m_Texture);	//テクスチャ設定
	CRenderer::SetWorldViewProjection2D();	//2Dマトリクス設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定
	CRenderer::GetDeviceContext()->Draw(4, 0);		//ポリゴン描画

	CRenderer::SetDepthEnable(true);
}