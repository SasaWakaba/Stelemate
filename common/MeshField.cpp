#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "Game_Object.h"
#include "MeshField.h"



static float g_Primitive;

XMFLOAT3 crossVec(XMFLOAT3 a, XMFLOAT3 b) 
{
	XMFLOAT3 n;
	n.x = a.y*b.z - a.z*b.y;
	n.y = a.z*b.x - a.x*b.z;
	n.z = a.x*b.y - a.y*b.x;
	return n;
}

float dotVec(XMFLOAT3 a, XMFLOAT3 b)
{
	float n;
	n = a.x*b.x + a.y*b.y + a.z*b.z;
	return n;
}

XMFLOAT3 minusVec(XMFLOAT3 a, XMFLOAT3 b)
{
	XMFLOAT3 n;
	n.x = a.x - b.x;
	n.y = a.y - b.y;
	n.z = a.z - b.z;
	return n;
}

XMFLOAT3 addVec(XMFLOAT3 a, XMFLOAT3 b)
{
	XMFLOAT3 n;
	n.x = a.x + b.x;
	n.y = a.y + b.y;
	n.z = a.z + b.z;
	return n;
}

XMFLOAT3 XVec(XMFLOAT3 a, float b)
{
	XMFLOAT3 n;
	n.x = a.x*b;
	n.y = a.y*b;
	n.z = a.z*b;
	return n;
}


void CMeshField::Initialize(float gridSizeX, float gridSizeZ, float gridX, float gridZ)
{
	m_GridSizeX = gridSizeX;
	m_GridSizeZ = gridSizeZ;
	m_GridX = gridX;
	m_GridZ = gridZ;


	g_Primitive = (gridX * 2.0f) * gridZ + (gridZ - 1) * 4.0f + 2;
	//=======================================================
	//テクスチャ読み込み
	//=======================================================
	m_Texture = new CTexture();
	m_Texture->LoadTex("asset/texture/forest.jpg");


	//=======================================================
	//頂点バッファ生成
	//=======================================================
	VERTEX_3D* vertex;
	vertex = new VERTEX_3D[(gridX + 1) * (gridZ + 1)];

	int cnt = 0;
	int z = (gridZ + 1);
	int x = 0;
	for (int i = 0; i < (gridX + 1) * (gridZ + 1); i++)
	{
		vertex[cnt].Position = XMFLOAT3(gridSizeX / gridX * x - (gridSizeX / 2), 0.0f, gridSizeZ / gridZ * (z - 1) - (gridSizeZ / 2));
		vertex[cnt].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[cnt].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[cnt].TexCoord = XMFLOAT2(x, z);
		cnt++;
		x++;
		if (x == gridX + 1)
		{
			x = 0;
			z--;
		}
	}

	//=======================================================
	//頂点バッファ生成
	//=======================================================
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * ((gridX + 1) * (gridZ + 1));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);



	//=====================================================
	//インデックスバッファ
	//=====================================================
	
	Index = new unsigned short[(2 + gridX * 2.0f) * gridZ + (gridZ - 1) * 2.0f];
	z = 1;
	x = 0;
	cnt = 0;
	float max = (2 + gridX * 2.0f) * gridZ + (gridZ - 1) * 2.0f;

	int d = 2 + (gridX + 1) * (gridZ + 1) / 2 + (gridZ - 1);

	for (int i = 0; i < gridX * gridZ + gridZ; i++)
	{
		Index[cnt] = x + (gridX + 1);
		cnt++;
		Index[cnt] = x;
		cnt++;
		x++;

		if (x == (gridX + 1) * z && cnt < max - 1)
		{
			Index[cnt] = x - 1;
			cnt++;
			Index[cnt] = x + (gridX + 1);
			cnt++;
			z++;
		}
	}


	D3D11_BUFFER_DESC ib;
	ib.ByteWidth = sizeof(unsigned short) * ((2 + gridX * 2.0f) * gridZ + (gridZ - 1) * 2.0f);
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

	
}

void CMeshField::Finalize()
{
	delete[] vertex;
	delete[] Index;
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}

void CMeshField::Update()
{

}

void CMeshField::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CRenderer::SetTexture(m_Texture);	//テクスチャ設定

	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);					//拡大・縮小
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);	//回転
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);				//移動
	CRenderer::SetWorldMatrix(&world);

	

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定
	CRenderer::GetDeviceContext()->DrawIndexed(g_Primitive, 0, 0);	//ポリゴン描画
}

//自動生成フラクタル
void CMeshField::Initialize(float gridSizeX, float gridSizeZ, float gridX, float gridZ, float y[11][11])
{
	m_GridSizeX = gridSizeX;
	m_GridSizeZ = gridSizeZ;
	m_GridX = gridX;
	m_GridZ = gridZ;

	g_Primitive = (gridX * 2.0f) * gridZ + (gridZ - 1) * 4.0f + 2;
	//=======================================================
	//テクスチャ読み込み
	//=======================================================
	m_Texture = new CTexture();
	m_Texture->Load("asset/field004.tga");


	//=======================================================
	//頂点バッファ
	//=======================================================
	
	vertex = new VERTEX_3D[(gridX + 1) * (gridZ + 1)];

	int cnt = 0;
	int z = (gridZ + 1);
	int x = 0;
	int numz = 0;
	for (int i = 0; i < (gridX + 1) * (gridZ + 1); i++)
	{
		vertex[cnt].Position = XMFLOAT3(gridSizeX / gridX * x - (gridSizeX / 2), y[numz][x], gridSizeZ / gridZ * (z - 1) - (gridSizeZ / 2));
		vertex[cnt].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[cnt].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[cnt].TexCoord = XMFLOAT2(x, z);
		cnt++;
		x++;
		if (x == gridX + 1)
		{
			x = 0;
			z--;
			numz++;
		}
	}

	for (int i = 1; i < gridZ; i++)
	{
		for (int j = 1; j < gridX; j++)
		{
			XMFLOAT3 normal;
			XMFLOAT3 va;
			XMFLOAT3 vb;
			
			va.x = vertex[(i - 1) * ((int)gridX + 1) + j].Position.x - vertex[(i + 1) * ((int)gridX + 1) + j].Position.x;
			va.y = vertex[(i - 1) * ((int)gridX + 1) + j].Position.y - vertex[(i + 1) * ((int)gridX + 1) + j].Position.y;
			va.z = vertex[(i - 1) * ((int)gridX + 1) + j].Position.z - vertex[(i + 1) * ((int)gridX + 1) + j].Position.z;

			vb.x = vertex[i * ((int)gridX + 1) + (j+1)].Position.x - vertex[i * ((int)gridX + 1) + (j-1)].Position.x;
			vb.y = vertex[i * ((int)gridX + 1) + (j+1)].Position.y - vertex[i * ((int)gridX + 1) + (j-1)].Position.y;
			vb.z = vertex[i * ((int)gridX + 1) + (j+1)].Position.z - vertex[i * ((int)gridX + 1) + (j-1)].Position.z;

			normal = crossVec(va, vb);
			float length = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
			normal.x = normal.x / length;
			normal.y = normal.y / length;
			normal.z = normal.z / length;

			vertex[i * ((int)gridX + 1) + j].Normal = normal;
		}
	}




	//=======================================================
	//頂点バッファ生成
	//=======================================================
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * ((gridX + 1) * (gridZ + 1));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	

	//=====================================================
	//インデックスバッファ
	//=====================================================
	WORD* Index;
	Index = new WORD[(2 + gridX * 2.0f) * gridZ + (gridZ - 1) * 2.0f];
	z = 1;
	x = 0;
	cnt = 0;
	float max = (2 + gridX * 2.0f) * gridZ + (gridZ - 1) * 2.0f;

	int d = 2 + (gridX + 1) * (gridZ + 1) / 2 + (gridZ - 1);

	for (int i = 0; i < gridX * gridZ + gridZ; i++)
	{
		Index[cnt] = x + (gridX + 1);
		cnt++;
		Index[cnt] = x;
		cnt++;
		x++;

		if (x == (gridX + 1) * z && cnt < max - 1)
		{
			Index[cnt] = x - 1;
			cnt++;
			Index[cnt] = x + (gridX + 1);
			cnt++;
			z++;
		}
	}


	D3D11_BUFFER_DESC ib;
	ib.ByteWidth = sizeof(WORD) * ((2 + gridX * 2.0f) * gridZ + (gridZ - 1) * 2.0f);
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

}


float CMeshField::GetHeight(XMFLOAT3 position)
{
	int x, z;
	XMFLOAT3 p0, p1, p2, v01, v02, n, v, hp, va, vb;

	float dp0n, dvn, dpn, t;

	v = XMFLOAT3(0.0f, -10.0f, 0.0f);

	x = (position.x + m_GridSizeX / 2) / (m_GridSizeX / m_GridX);//0.1fは１ブロックのサイズ
	z = ((position.z * - 1) + m_GridSizeZ / 2) / (m_GridSizeZ / m_GridZ);

	if (x < 0 || z < 0 || x > m_GridX || z > m_GridZ)
	{
		return 0.0f;
	}

	va.x = vertex[(z + 1) * ((int)m_GridX + 1) + (x + 1)].Position.x - vertex[z * ((int)m_GridX + 1) + x].Position.x;
	va.y = vertex[(z + 1) * ((int)m_GridX + 1) + (x + 1)].Position.y - vertex[z * ((int)m_GridX + 1) + x].Position.y;
	va.z = vertex[(z + 1) * ((int)m_GridX + 1) + (x + 1)].Position.z - vertex[z * ((int)m_GridX + 1) + x].Position.z;

	vb.x = position.x - vertex[z * ((int)m_GridX + 1) + x].Position.x;
	vb.y = position.y - vertex[z * ((int)m_GridX + 1) + x].Position.y;
	vb.z = position.z - vertex[z * ((int)m_GridX + 1) + x].Position.z;

	if (va.z*vb.x - va.x*vb.z > 0.0f)
	{
		p0 = vertex[(z + 1) * ((int)m_GridX + 1) + x].Position;
		p1 = vertex[z * ((int)m_GridX + 1) + x].Position;
		p2 = vertex[(z + 1) * ((int)m_GridX + 1) + (x + 1)].Position;
	}
	else
	{
		p0 = vertex[z * ((int)m_GridX + 1) + (x + 1)].Position;
		p1 = vertex[(z + 1) * ((int)m_GridX + 1) + (x + 1)].Position;
		p2 = vertex[z * ((int)m_GridX + 1) + x].Position;
	}

	v01 = minusVec(p1, p0);
	v02 = minusVec(p2, p0);
	n = crossVec(v01, v02);

	dvn = dotVec(v, n);
	dp0n = dotVec(p0, n);
	dpn = dotVec(position, n);

	t = (dp0n - dpn) / dvn;
	hp = addVec(position, XVec(v, t));

	return hp.y;
}