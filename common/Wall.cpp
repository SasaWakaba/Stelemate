#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "Game_Object.h"
#include "Wall.h"




void CWall::Initialize()
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(-1.0f, 2.0f, 1.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 2.0f, 1.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, 0.0f, 1.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, 0.0f, 1.0f);
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


	//=======================================================
	//テクスチャ読み込み
	//=======================================================
	m_Texture = new CTexture();
	m_Texture->Load("asset/hoshi.tga");
}

void CWall::Finalize()
{
	m_VertexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}

void CWall::Update()
{

}

void CWall::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::SetTexture(m_Texture);	//テクスチャ設定

	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);					//拡大・縮小
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);	//回転
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);				//移動
	CRenderer::SetWorldMatrix(&world);


	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定
	CRenderer::GetDeviceContext()->Draw(4, 0);		//ポリゴン描画

	
	//
	//world = XMMatrixScaling(1.0f, 1.0f, 1.0f);					//拡大・縮小
	//world *= XMMatrixRotationRollPitchYaw(0.0f, 1.5f, 0.0f);	//回転
	//world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);				//移動
	//CRenderer::SetWorldMatrix(&world);
	//
	//CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定
	//CRenderer::GetDeviceContext()->Draw(4, 0);		//ポリゴン描画
}