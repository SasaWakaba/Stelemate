#include <vector>
#include <iterator>
#include "../common/main.h"
#include "../common/texture.h"

#include "C3DPolygon.h"

#include "ArrowsLine.h"

void CArrowsLine::Initialize()
{
	m_Arrows = new CTexture();
	m_Arrows->LoadTex("asset/texture/line_a.png");

	m_Line = new CTexture();
	m_Line->LoadTex("asset/texture/line_b.png");

	m_Curve = new CTexture();
	m_Curve->LoadTex("asset/texture/line_c.png");

	m_Polygon = new C3DPolygon();
	m_Polygon->Initialize();
}

void CArrowsLine::Finalize()
{
	Reset();
	m_Arrows->Unload();
	delete m_Arrows;
	m_Line->Unload();
	delete m_Line;
	m_Curve->Unload();
	delete m_Curve;

	delete m_Polygon;
}

void CArrowsLine::Draw(int x, int z)
{
	VertexColor_4 color{
		XMFLOAT4(1.0f, 1.0f, 1.0f, 0.51f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 0.51f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 0.51f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 0.51f)
	};
	XMMATRIX world;
	for (int i = 0; i < m_ArrowsLine.size(); i++)
	{
		world = XMMatrixTranslation((m_ArrowsLine[i].x * SPACE_SIZE) - (SPACE_SIZE * x / 2), 0.6f, (m_ArrowsLine[i].z * SPACE_SIZE) - (SPACE_SIZE * z / 2));

		if (i + 1 != m_ArrowsLine.size())
		{
			if (i - 1 >= 0)
			{
				//�ЂƂO�ƈ�オX���ɒ���
				if (m_ArrowsLine[i - 1].x == m_ArrowsLine[i + 1].x)
				{
					m_Polygon->Draw(m_Line, world, color);
				}
				//�ЂƂO�ƈ�オZ���ɒ���
				if (m_ArrowsLine[i - 1].z == m_ArrowsLine[i + 1].z)
				{
					world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * 90.0f, 0.0f)* world;
					m_Polygon->Draw(m_Line, world, color);
				}

				//�ЂƂO���E
				if (m_ArrowsLine[i].x < m_ArrowsLine[i - 1].x)
				{
					//��オ��
					if (m_ArrowsLine[i].z < m_ArrowsLine[i + 1].z)
					{
						m_Polygon->Draw(m_Curve, world, color);
					}
					//��オ��
					if (m_ArrowsLine[i].z > m_ArrowsLine[i + 1].z)
					{
						world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * 90.0f, 0.0f) * world;
						m_Polygon->Draw(m_Curve, world, color);
					}
				}
				//�ЂƂO����
				if (m_ArrowsLine[i].x > m_ArrowsLine[i - 1].x)
				{
					//��オ��
					if (m_ArrowsLine[i].z < m_ArrowsLine[i + 1].z)
					{
						world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * -90.0f, 0.0f) * world;
						m_Polygon->Draw(m_Curve, world, color);
					}
					//��オ��
					if (m_ArrowsLine[i].z > m_ArrowsLine[i + 1].z)
					{
						world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * -180.0f, 0.0f) * world;
						m_Polygon->Draw(m_Curve, world, color);
					}
				}
				//�ЂƂO����
				if (m_ArrowsLine[i].z < m_ArrowsLine[i - 1].z)
				{
					//��オ�E
					if (m_ArrowsLine[i].x < m_ArrowsLine[i + 1].x)
					{
						m_Polygon->Draw(m_Curve, world, color);
					}
					//��オ��
					if (m_ArrowsLine[i].x > m_ArrowsLine[i + 1].x)
					{
						world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * -90.0f, 0.0f) * world;
						m_Polygon->Draw(m_Curve, world, color);
					}
				}
				//�ЂƂO����
				if (m_ArrowsLine[i].z > m_ArrowsLine[i - 1].z)
				{
					//��オ�E
					if (m_ArrowsLine[i].x < m_ArrowsLine[i + 1].x)
					{
						world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * 90.0f, 0.0f) * world;
						m_Polygon->Draw(m_Curve, world, color);
					}
					//��オ��
					if (m_ArrowsLine[i].x > m_ArrowsLine[i + 1].x)
					{
						world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * -180.0f, 0.0f) * world;
						m_Polygon->Draw(m_Curve, world, color);
					}
				}
			}
			else
			{
				//���J�n�n�_
				//�����E����
				if (m_ArrowsLine[i].x < m_ArrowsLine[i + 1].x || m_ArrowsLine[i].x > m_ArrowsLine[i + 1].x)
				{
					world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * 90.0f, 0.0f) * world;
					m_Polygon->Draw(m_Line, world, color);
				}
				//�����ォ��
				if (m_ArrowsLine[i].z < m_ArrowsLine[i + 1].z || m_ArrowsLine[i].z > m_ArrowsLine[i + 1].z)
				{
					m_Polygon->Draw(m_Line, world, color);
				}
			}
		}
		else
		{
			//���I���n�_
			//��O������
			if (i - 1 >= 0)
			{
				//��O����
				if (m_ArrowsLine[i].z < m_ArrowsLine[i - 1].z)
				{
					m_Polygon->Draw(m_Arrows, world, color);
				}
				//��O����
				if (m_ArrowsLine[i].z > m_ArrowsLine[i - 1].z)
				{
					world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * 180.0f, 0.0f) * world;
					m_Polygon->Draw(m_Arrows, world, color);
				}
				//��O���E
				if (m_ArrowsLine[i].x < m_ArrowsLine[i - 1].x)
				{
					world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * 90.0f, 0.0f) * world;
					m_Polygon->Draw(m_Arrows, world, color);
				}
				//��O����
				if (m_ArrowsLine[i].x > m_ArrowsLine[i - 1].x)
				{
					world = XMMatrixRotationRollPitchYaw(0.0f, (PI / 180) * -90.0f, 0.0f) * world;
					m_Polygon->Draw(m_Arrows, world, color);
				}
			}
			else
			{
				m_Polygon->Draw(m_Arrows, world, color);
			}
		}
	}
}