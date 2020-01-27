#include <vector>
#include "../common/main.h"
#include "../Stage/CStage.h"
#include "../common/texture.h"
#include "C3DPolygon.h"
#include "../Charcter/CCharcterBase.h"

#include "CAttackSearch.h"

void CAttackSearch::Add(Vector2_3D pos)
{
	if (m_AtkArea.size() != 0)
	{
		bool re = false;
		for (int i = 0; i < m_AtkArea.size(); i++)
		{
			if (m_AtkArea[i].x == pos.x && m_AtkArea[i].z == pos.z)
			{
				re = true;
				break;
			}
		}

		if (!re)
		{
			m_AtkArea.push_back(pos);
		}
	}
	else
	{
		m_AtkArea.push_back(pos);
	}
}

void CAttackSearch::Initialize(int numX, int numZ, PanelState* Map)
{
	m_X = numX;
	m_Z = numZ;
	m_StageMap = Map;

	m_Atk = new CTexture();
	m_Atk->LoadTex("asset/texture/Atk.png");

	m_Polygon = new C3DPolygon();
	m_Polygon->Initialize();

	bDraw = false;
}

void CAttackSearch::Finalize()
{
	m_Atk->Unload();
	delete m_Atk;
	
	m_Polygon->Finalize();
	delete m_Polygon;

	m_AtkArea.clear();
}

void CAttackSearch::Draw()
{
	if (bDraw)
	{
		XMMATRIX world;
		VertexColor_4 color = {
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
		};
		for (Vector2_3D pos : m_AtkArea)
		{
			world = XMMatrixTranslation((pos.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.4f, (pos.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2));
			m_Polygon->Draw(m_Atk, world, color);
		}
	}
}

std::vector<Vector2_3D> CAttackSearch::Search(Vector2_3D pos, Weapontype Atk)
{
	Reset();
	Vector2_3D add;
	switch (Atk)
	{
	case Sword:
		if (pos.x + 1 < m_X)
		{
			add = { pos.x + 1, pos.z };
			Add(add);
		}
		if (pos.x - 1 >= 0)
		{
			add = { pos.x - 1, pos.z };
			Add(add);
		}
		if (pos.z + 1 < m_Z)
		{
			add = { pos.x, pos.z + 1 };
			Add(add);
		}
		if (pos.z - 1 >= 0)
		{
			add = { pos.x, pos.z - 1 };
			Add(add);
		}
		break;
	case Magic:
		if (pos.x + 2 < m_X)
		{
			add = { pos.x + 2, pos.z };
			Add(add);
		}
		if (pos.x - 2 >= 0)
		{
			add = { pos.x - 2, pos.z };
			Add(add);
		}
		if (pos.z + 2 < m_Z)
		{
			add = { pos.x, pos.z + 2 };
			Add(add);
		}
		if (pos.z - 2 >= 0)
		{
			add = { pos.x, pos.z - 2 };
			Add(add);
		}

		if (pos.x + 1 < m_X)
		{
			if (pos.z + 1 < m_Z)
			{
				add = { pos.x + 1, pos.z + 1 };
				Add(add);
			}
			if (pos.z - 1 >= 0)
			{
				add = { pos.x + 1, pos.z - 1 };
				Add(add);
			}
		}
		if (pos.x - 1 >= 0)
		{
			if (pos.z + 1 < m_Z)
			{
				add = { pos.x - 1, pos.z + 1 };
				Add(add);
			}
			if (pos.z - 1 >= 0)
			{
				add = { pos.x - 1, pos.z - 1 };
				Add(add);
			}
		}
		break;
	}

	return m_AtkArea;
}