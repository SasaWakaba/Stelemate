#include "main.h"
#include "renderer.h"
#include "Game_Object.h"
#include "model.h"
#include "texture.h"
#include "CSkyBox.h"
#include "input.h"

#include "camera.h"


#include "Scene.h"
#include "manager.h"

#define BOXPOS (0.998f)

//static VERTEX_3D vertex[] = {
//	//上
//	{XMFLOAT3(-1.0f, 1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f, 0)},
//	{XMFLOAT3( 1.0f, 1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 2.0f, 0.0f)},
//	{XMFLOAT3(-1.0f, 1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f)},
//	{XMFLOAT3( 1.0f, 1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f)},
//	//左
//	{XMFLOAT3(-1.0f,  1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f / 3.0f)},
//	{XMFLOAT3(-1.0f,  1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f)},
//	{XMFLOAT3(-1.0f, -1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f / 3.0f * 2.0f)},
//	{XMFLOAT3(-1.0f, -1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f * 2.0f)},
//	//正面
//	{XMFLOAT3(-1.0f,  1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f)},
//	{XMFLOAT3( 1.0f,  1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f)},
//	{XMFLOAT3(-1.0f, -1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f * 2.0f)},
//	{XMFLOAT3( 1.0f, -1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f * 2.0f)},
//	//右
//	{XMFLOAT3( 1.0f,  1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f)		},
//	{XMFLOAT3( 1.0f,  1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 3.0f, 1.0f / 3.0f)		},
//	{XMFLOAT3( 1.0f, -1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f * 2.0f)},
//	{XMFLOAT3( 1.0f, -1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 3.0f, 1.0f / 3.0f * 2.0f)},
//	//後ろ
//	{XMFLOAT3( 1.0f,  1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 3.0f, 1.0f / 3.0f)		},
//	{XMFLOAT3(-1.0f,  1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f / 3.0f)						},
//	{XMFLOAT3( 1.0f, -1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 3.0f, 1.0f / 3.0f * 2.0f)},
//	{XMFLOAT3(-1.0f, -1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f / 3.0f * 2.0f)				},
//	//下
//	{XMFLOAT3(-1.0f, -1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f * 2.0f)		},
//	{XMFLOAT3( 1.0f, -1.0f,  1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f * 2.0f)},
//	{XMFLOAT3(-1.0f, -1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f, 1.0f)						},
//	{XMFLOAT3( 1.0f, -1.0f, -1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f)				}
//};

void CSkyBox::Initialize()
{
	m_Texture[0] = new CTexture();
	m_Texture[0]->LoadTex("asset/texture/SkyBox.png");

	m_Texture[1] = new CTexture();
	m_Texture[1]->LoadTex("asset/texture/SkyBox001.png");

	bNight = false;
	
	//=======================================================
	//頂点バッファ生成
	//=======================================================
	VERTEX_3D* vertex;
	vertex = new VERTEX_3D[24];
	for (int cnt = 0; cnt < 24; cnt++)
	{
		vertex[cnt].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[cnt].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{
		vertex[0].Position = XMFLOAT3(-1.0f, BOXPOS, -1.0f);
		vertex[0].TexCoord = XMFLOAT2(1.0f / 4.0f, 0.0f);
		vertex[1].Position = XMFLOAT3(1.0f, BOXPOS, -1.0f);
		vertex[1].TexCoord = XMFLOAT2(1.0f / 4.0f * 2.0f, 0.0f);
		vertex[2].Position = XMFLOAT3(-1.0f, BOXPOS, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f);
		vertex[3].Position = XMFLOAT3(1.0f, BOXPOS, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f);

		vertex[4].Position = XMFLOAT3(-BOXPOS, 1.0f, -1.0f);
		vertex[4].TexCoord = XMFLOAT2(0.0f, 1.0f / 3.0f);
		vertex[5].Position = XMFLOAT3(-BOXPOS, 1.0f, 1.0f);
		vertex[5].TexCoord = XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f);
		vertex[6].Position = XMFLOAT3(-BOXPOS, -1.0f, -1.0f);
		vertex[6].TexCoord = XMFLOAT2(0.0f, 1.0f / 3.0f * 2.0f);
		vertex[7].Position = XMFLOAT3(-BOXPOS, -1.0f, 1.0f);
		vertex[7].TexCoord = XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f * 2.0f);

		vertex[8].Position = XMFLOAT3(-1.0f, 1.0f, BOXPOS);
		vertex[8].TexCoord = XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f);
		vertex[9].Position = XMFLOAT3(1.0f, 1.0f, BOXPOS);
		vertex[9].TexCoord = XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f);
		vertex[10].Position = XMFLOAT3(-1.0f, -1.0f, BOXPOS);
		vertex[10].TexCoord = XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f * 2.0f);
		vertex[11].Position = XMFLOAT3(1.0f, -1.0f, BOXPOS);
		vertex[11].TexCoord = XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f * 2.0f);

		vertex[12].Position = XMFLOAT3(BOXPOS, 1.0f, 1.0f);
		vertex[12].TexCoord = XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f);
		vertex[13].Position = XMFLOAT3(BOXPOS, 1.0f, -1.0f);
		vertex[13].TexCoord = XMFLOAT2(1.0f / 4.0f * 3.0f, 1.0f / 3.0f);
		vertex[14].Position = XMFLOAT3(BOXPOS, -1.0f, 1.0f);
		vertex[14].TexCoord = XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f * 2.0f);
		vertex[15].Position = XMFLOAT3(BOXPOS, -1.0f, -1.0f);
		vertex[15].TexCoord = XMFLOAT2(1.0f / 4.0f * 3.0f, 1.0f / 3.0f * 2.0f);

		vertex[16].Position = XMFLOAT3(1.0f, 1.0f, -BOXPOS);
		vertex[16].TexCoord = XMFLOAT2(1.0f / 4.0f * 3.0f, 1.0f / 3.0f);
		vertex[17].Position = XMFLOAT3(-1.0f, 1.0f, -BOXPOS);
		vertex[17].TexCoord = XMFLOAT2(1.0f, 1.0f / 3.0f);
		vertex[18].Position = XMFLOAT3(1.0f, -1.0f, -BOXPOS);
		vertex[18].TexCoord = XMFLOAT2(1.0f / 4.0f * 3.0f, 1.0f / 3.0f * 2.0f);
		vertex[19].Position = XMFLOAT3(-1.0f, -1.0f, -BOXPOS);
		vertex[19].TexCoord = XMFLOAT2(1.0f, 1.0f / 3.0f * 2.0f);

		vertex[20].Position = XMFLOAT3(-1.0f, -BOXPOS, 1.0f);
		vertex[20].TexCoord = XMFLOAT2(1.0f / 4.0f, 1.0f / 3.0f * 2.0f);
		vertex[21].Position = XMFLOAT3(1.0f, -BOXPOS, 1.0f);
		vertex[21].TexCoord = XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f / 3.0f * 2.0f);
		vertex[22].Position = XMFLOAT3(-1.0f, -BOXPOS, -1.0f);
		vertex[22].TexCoord = XMFLOAT2(1.0f / 4.0f, 1.0f);
		vertex[23].Position = XMFLOAT3(1.0f, -BOXPOS, -1.0f);
		vertex[23].TexCoord = XMFLOAT2(1.0f / 4.0f * 2.0f, 1.0f);
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	delete[] vertex;


	//=====================================================
	//インデックスバッファ
	//=====================================================
	WORD* Index;
	Index = new WORD[36];

	for (int i = 0; i < 6; i++)
	{
		Index[i * 6] = i * 4;
		Index[i * 6 + 1] = i * 4 + 1;
		Index[i * 6 + 2] = i * 4 + 2;
		Index[i * 6 + 3] = i * 4 + 1;
		Index[i * 6 + 4] = i * 4 + 3;
		Index[i * 6 + 5] = i * 4 + 2;
	}

	D3D11_BUFFER_DESC ib;
	ib.ByteWidth = sizeof(WORD) * 36;
	ib.Usage = D3D11_USAGE_DEFAULT;
	ib.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ib.CPUAccessFlags = 0;
	ib.MiscFlags = 0;
	ib.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA ir;
	ir.pSysMem = Index;
	ir.SysMemPitch = 0;
	ir.SysMemSlicePitch = 0;

	CRenderer::GetDevice()->CreateBuffer(&ib, &ir, &m_IndexBuffer);

	delete[] Index;

	frame = 0.0f;
}

void CSkyBox::Finalize()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture[0]->Unload();
	delete m_Texture[0];
	m_Texture[1]->Unload();
	delete m_Texture[1];
}

void CSkyBox::Update()
{
	CCamera* camera;
	camera = CManager::GetScene()->GetGameObject<CCamera>(0);
	m_Position = camera->GetPosition();

	frame += 0.05f;
}

void CSkyBox::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	if (bNight)
	{
		CRenderer::SetTexture(m_Texture[1]);	//テクスチャ設定
	}
	else
	{
		CRenderer::SetTexture(m_Texture[0]);	//テクスチャ設定
	}


	XMMATRIX world;
	world = XMMatrixScaling(500.0f, 500.0f, 500.0f);					//拡大・縮小
	world *= XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * frame, 0.0f);	//回転
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);				//移動
	CRenderer::SetWorldMatrix(&world);



	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//トポロジ設定
	CRenderer::GetDeviceContext()->DrawIndexed(36, 0, 0);	//ポリゴン描画
}


void CSkyBox::Draw(XMMATRIX trans)
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	if (bNight)
	{
		CRenderer::SetTexture(m_Texture[1]);	//テクスチャ設定
	}
	else
	{
		CRenderer::SetTexture(m_Texture[0]);	//テクスチャ設定
	}


	XMMATRIX world;
	world = XMMatrixScaling(100.0f, 100.0f, 100.0f);					//拡大・縮小
	world *= XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * frame, 0.0f);	//回転
	world *= trans;				//移動
	CRenderer::SetWorldMatrix(&world);



	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//トポロジ設定
	CRenderer::GetDeviceContext()->DrawIndexed(36, 0, 0);	//ポリゴン描画
}