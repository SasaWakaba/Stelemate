#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "texture.h"
#include "Game_Object.h"
#include "Billboard.h"
#include "Scene.h"
#include "manager.h"
#include "camera.h"
#include "TextureManager.h"

XMMATRIX ExtractOffset(const XMMATRIX& mWorld);
XMMATRIX ExtractScaling(const XMMATRIX& mWorld);


void CBillboard::Initialize()
{
	//m_Texture = new CTexture();

	VERTEX_3D vertex[4];
	vertex[0].Position =	XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertex[0].Normal =		XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse =		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord =	XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position =	XMFLOAT3(0.5f, 0.5f, 0.0f);
	vertex[1].Normal =		XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse =		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord =	XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position =	XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex[2].Normal =		XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse =		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord =	XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position =	XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertex[3].Normal =		XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse =		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord =	XMFLOAT2(1.0f, 1.0f);

	//=======================================================
	//頂点バッファ生成
	//=======================================================
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void CBillboard::Finalize()
{
	m_VertexBuffer->Release();
	//m_Texture->Unload();
	delete m_Texture;
}

void CBillboard::Draw(XMMATRIX world)
{
	XMMATRIX* view = CRenderer::GetViewMatrix();


	XMMATRIX mOffset = ExtractOffset(*view);
	XMMATRIX mScaling = ExtractScaling(*view);
	XMMATRIX MatrixWorld;
	XMVECTOR det;
	MatrixWorld = XMMatrixInverse(&det, mScaling) * (*view) * XMMatrixInverse(&det, mOffset);
	MatrixWorld = XMMatrixInverse(&det, MatrixWorld) * world;

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::SetTexture(m_Texture);	//テクスチャ設定


	CRenderer::SetWorldMatrix(&MatrixWorld);


	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定
	CRenderer::GetDeviceContext()->Draw(4, 0);		//ポリゴン描画
	
}

void CBillboard::Draw(XMMATRIX world, VertexColor_4 color)
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = color.a;
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(0.5f, 0.5f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = color.b;
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = color.c;
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = color.d;
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_MAPPED_SUBRESOURCE msr;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	memcpy(msr.pData, vertex, sizeof(VERTEX_3D) * 4); // 
	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	XMMATRIX* view = CRenderer::GetViewMatrix();


	XMMATRIX mOffset = ExtractOffset(*view);
	XMMATRIX mScaling = ExtractScaling(*view);
	XMMATRIX MatrixWorld;
	XMVECTOR det;
	MatrixWorld = XMMatrixInverse(&det, mScaling) * (*view) * XMMatrixInverse(&det, mOffset);
	MatrixWorld = XMMatrixInverse(&det, MatrixWorld) * world;

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::SetTexture(m_Texture);	//テクスチャ設定


	CRenderer::SetWorldMatrix(&MatrixWorld);


	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定
	CRenderer::GetDeviceContext()->Draw(4, 0);		//ポリゴン描画
}

void CBillboard::Load(const char* filename)
{
	m_Texture = CTextureManager::LoadTexture(filename);
}

XMMATRIX ExtractOffset(const XMMATRIX& mWorld) {
	return XMMatrixTranslation(mWorld.r[3].m128_f32[0], mWorld.r[3].m128_f32[1], mWorld.r[3].m128_f32[2]);
}

XMMATRIX ExtractScaling(const XMMATRIX& mWorld) {
	return XMMatrixScaling(
		XMVector3Length(XMVECTOR{ mWorld.r[0].m128_f32[0],mWorld.r[0].m128_f32[1],mWorld.r[0].m128_f32[2] }).m128_f32[0],
		XMVector3Length(XMVECTOR{ mWorld.r[1].m128_f32[0],mWorld.r[1].m128_f32[1],mWorld.r[1].m128_f32[2] }).m128_f32[0],
		XMVector3Length(XMVECTOR{ mWorld.r[2].m128_f32[0],mWorld.r[2].m128_f32[1],mWorld.r[2].m128_f32[2] }).m128_f32[0]
	);
}
