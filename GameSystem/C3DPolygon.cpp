#include "../common/main.h"
#include "../common/renderer.h"
#include "../common/texture.h"
#include "C3DPolygon.h"




void C3DPolygon::Initialize()
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(-0.5f, 0.0f, 0.5f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(0.5f, 0.0f, 0.5f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-0.5f, 0.0f, -0.5f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.5f, 0.0f, -0.5f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//=======================================================
	//���_�o�b�t�@����
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
	//�e�N�X�`���ǂݍ���
	//=======================================================
	m_Texture = new CTexture();
	m_Texture->LoadTex("asset/texture/cursor.png");
}

void C3DPolygon::Finalize()
{
	m_VertexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}

void C3DPolygon::Update()
{

}

void C3DPolygon::Draw(XMMATRIX world)
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //���_�o�b�t�@�ݒ�
	CRenderer::SetTexture(m_Texture);	//�e�N�X�`���ݒ�

	XMMATRIX worldthis;
	worldthis = XMMatrixScaling(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE);					//�g��E�k��

	worldthis *= world;

	CRenderer::SetWorldMatrix(&worldthis);


	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->Draw(4, 0);		//�|���S���`��
}


void C3DPolygon::Draw(CTexture* tex, XMMATRIX world, VertexColor_4 color)
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(-0.5f, 0.0f, 0.5f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(color.a.x, color.a.y, color.a.z, color.a.w);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(0.5f, 0.0f, 0.5f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(color.b.x, color.b.y, color.b.z, color.b.w);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-0.5f, 0.0f, -0.5f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(color.c.x, color.c.y, color.c.z, color.c.w);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.5f, 0.0f, -0.5f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(color.d.x, color.d.y, color.d.z, color.d.w);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//=======================================================
	//���_�o�b�t�@����
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
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //���_�o�b�t�@�ݒ�
	CRenderer::SetTexture(tex);	//�e�N�X�`���ݒ�

	XMMATRIX worldthis;
	worldthis = XMMatrixScaling(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE);					//�g��E�k��

	worldthis *= world;

	CRenderer::SetWorldMatrix(&worldthis);

	
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->Draw(4, 0);		//�|���S���`��
}