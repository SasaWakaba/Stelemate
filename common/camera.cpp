
#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "Billboard.h"



XMFLOAT3 CCamera::m_at;
int CCamera::cnt;
XMFLOAT3 CCamera::MoveLength;
bool CCamera::bMove;

void CCamera::Initialize()
{

	m_Position = XMFLOAT3( 5.0f, 5.0f, -10.0f );
	m_Rotation = XMFLOAT3( 0.5f, -0.6f, 0.0f );

	m_Length = 10.0f;

	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;

	m_at =			XMFLOAT3(0.0f, 0.0f,  0.0f);

	m_Eye =			XMFLOAT3(m_at.x, m_at.y + m_Length, m_at.z - m_Length);

	m_CameraFront = XMFLOAT3(m_at.x - m_Eye.x, m_at.y - m_Eye.y, m_at.z - m_Eye.z);
	m_CameraRight =	XMFLOAT3(-1.0f, 0.0f, 0.0f);

	XMVECTOR Vecfront = XMLoadFloat3(&m_CameraFront);
	XMVECTOR VecRight = XMLoadFloat3(&m_CameraRight);
	XMVECTOR VecUp = XMLoadFloat3(&m_CameraUp);

	Vecfront = XMVector3Normalize(Vecfront);

	VecUp = XMVector3Cross(VecRight, Vecfront);

	VecUp = XMVector3Normalize(VecUp);

	VecRight = XMVector3Cross(Vecfront, VecUp);

	VecRight = XMVector3Normalize(VecRight);


	XMStoreFloat3(&m_CameraFront, Vecfront);
	XMStoreFloat3(&m_CameraRight, VecRight);
	XMStoreFloat3(&m_CameraUp, VecUp);
	

}


void CCamera::Finalize()
{

}


void CCamera::Update()
{
	if (!bMove)
	{
		if (m_Position.x != m_at.x || m_Position.y != m_at.y || m_Position.z != m_at.z)
		{
			m_Eye = XMFLOAT3(m_at.x, m_at.y + m_Length, m_at.z - m_Length);
		}
	}
	else
	{
		if (cnt < 15)
		{
			m_at.x += MoveLength.x / 15.0f;
			m_at.y += MoveLength.y / 15.0f;
			m_at.z += MoveLength.z / 15.0f;
			m_Eye = XMFLOAT3(m_at.x, m_at.y + m_Length, m_at.z - m_Length);
			cnt++;
		}
		else
		{
			bMove = false;
		}
	}

	m_Position = m_at;
}



void CCamera::Draw()
{

	
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;



	// ビューポート設定
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);


	// ビューマトリクス設定

	m_ViewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_Eye), XMLoadFloat3(&m_at), XMLoadFloat3(&m_CameraUp));

	CRenderer::SetViewMatrix(&m_ViewMatrix);



	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);



}

XMMATRIX* CCamera::GetView()
{
	return &m_ViewMatrix;
}