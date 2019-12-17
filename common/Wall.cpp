#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "Game_Object.h"
#include "Wall.h"




void CBattleRand::Initialize()
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(-1.0f, 0.5f, 1.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.1f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 0.5f, 1.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.1f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, 0.5f, -1.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.1f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, 0.5f, -1.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.1f, 0.0f);
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
	m_Texture->LoadTex("asset/texture/Icon000.png");
}

void CBattleRand::Finalize()
{
	m_VertexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}

void CBattleRand::Update()
{

}

void CBattleRand::Draw(XMMATRIX world, CTexture* tex)
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //���_�o�b�t�@�ݒ�
	CRenderer::SetTexture(tex);	//�e�N�X�`���ݒ�

	//XMMATRIX world;
	//world = XMMatrixScaling(5.0f, 5.0f, 5.0f);					//�g��E�k��
	//world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);	//��]
	//world *= XMMatrixTranslation(0.0f, 90.0f, 0.0f);				//�ړ�
	CRenderer::SetWorldMatrix(&world);

	CRenderer::SetAlphaTestEnable(true);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->Draw(4, 0);		//�|���S���`��

	CRenderer::SetAlphaTestEnable(false);
	//
	//world = XMMatrixScaling(1.0f, 1.0f, 1.0f);					//�g��E�k��
	//world *= XMMatrixRotationRollPitchYaw(0.0f, 1.5f, 0.0f);	//��]
	//world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);				//�ړ�
	//CRenderer::SetWorldMatrix(&world);
	//
	//CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//�g�|���W�ݒ�
	//CRenderer::GetDeviceContext()->Draw(4, 0);		//�|���S���`��
}