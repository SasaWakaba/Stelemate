#include <vector>
#include "../common/main.h"
#include "../Stage/CStage.h"
#include "../common/texture.h"
#include "C3DPolygon.h"
#include "../common/TextureManager.h"
#include "CMoveSearch.h"


void CMoveSearch::Add(Vector2_3D pos)
{
	if (m_MoveArea.size() != 0)
	{
		bool re = false;
		for (unsigned int i = 0; i < m_MoveArea.size(); i++)
		{
			if (m_MoveArea[i].x == pos.x && m_MoveArea[i].z == pos.z)
			{
				re = true;
				break;
			}
		}

		if (!re)
		{
			m_MoveArea.push_back(pos);
		}
	}
	else
	{
		m_MoveArea.push_back(pos);
	}
}

void CMoveSearch::Initialize(int numX, int numZ, PanelState* Map)
{
	m_X = numX;
	m_Z = numZ;
	m_StageMap = Map;

	m_Move[0] = CTextureManager::LoadTexture("asset/texture/Move.png");

	m_Move[1] = CTextureManager::LoadTexture("asset/texture/MoveEne.png");

	m_Polygon = new C3DPolygon();
	m_Polygon->Initialize();

	bDraw = false;
	PL = true;
}

void CMoveSearch::Finalize()
{
	m_Polygon->Finalize();
	delete m_Polygon;
}

void CMoveSearch::Draw()
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
		for (Vector2_3D pos : m_MoveArea)
		{
			world = XMMatrixTranslation((pos.x * SPACE_SIZE) - (SPACE_SIZE * m_X / 2), 0.4f, (pos.z * SPACE_SIZE) - (SPACE_SIZE * m_Z / 2));
			if (PL)
			{
				m_Polygon->Draw(m_Move[0], world, color);
			}
			else
			{
				m_Polygon->Draw(m_Move[1], world, color);
			}
		}
	}
}

std::vector<Vector2_3D> CMoveSearch::Search(Vector2_3D pos, CCharcterBase* Move)
{
	Reset();
	Add(pos);
	if (Move->m_JobClass != Lancer)
	{
		ReSearch(pos, Move->GetStatus()->MovePoint, pos);
	}
	else
	{
		ReSearchLance(pos, Move->GetStatus()->MovePoint, pos);
	}
	return m_MoveArea;
}

void CMoveSearch::ReSearch(Vector2_3D pos, int Move, Vector2_3D posOld)
{
	int old = posOld.z * m_X + posOld.x;
	int Right;
	int Left;
	int Up;
	int Down;

	if (pos.x + 1 >= m_X)
	{
		Right = old;
	}
	else
	{
		Right = pos.z * m_X + pos.x + 1;
	}
	if (pos.x - 1 < 0)
	{
		Left = old;
	}
	else
	{
		Left = pos.z * m_X + pos.x - 1;
	}
	if (pos.z + 1 >= m_Z)
	{
		Up = old;
	}
	else
	{
		Up = (pos.z + 1) * m_X + pos.x;
	}
	if (pos.z - 1 < 0)
	{
		Down = old;
	}
	else
	{
		Down = (pos.z - 1) * m_X + pos.x;
	}

	//‰E‚ð’Tõ
	if (Right != old)
	{
		if (!m_StageMap[Right].bChar)
		{
			if (Move >= (int)m_StageMap[Right].PanelPattarn)
			{
				Vector2_3D add = { pos.x + 1, pos.z };
				Add(add);

				ReSearch(add, Move - (int)m_StageMap[Right].PanelPattarn, pos);
			}
		}
	}

	//¶‚ð’Tõ
	if (Left != old)
	{
		if (!m_StageMap[Left].bChar)
		{
			if (Move >= (int)m_StageMap[Left].PanelPattarn)
			{
				Vector2_3D add = { pos.x - 1, pos.z };
				Add(add);

				ReSearch(add, Move - (int)m_StageMap[Left].PanelPattarn, pos);
			}
		}
	}

	//ã‚ð’Tõ
	if (Up != old)
	{
		if (!m_StageMap[Up].bChar)
		{
			if (Move >= (int)m_StageMap[Up].PanelPattarn)
			{
				Vector2_3D add = { pos.x, pos.z + 1 };
				Add(add);

				ReSearch(add, Move - (int)m_StageMap[Up].PanelPattarn, pos);
			}
		}
	}

	//‰º‚ð’Tõ
	if (Down != old)
	{
		if (!m_StageMap[Down].bChar)
		{
			if (Move >= (int)m_StageMap[Down].PanelPattarn)
			{
				Vector2_3D add = { pos.x, pos.z - 1 };
				Add(add);

				ReSearch(add, Move - (int)m_StageMap[Down].PanelPattarn, pos);
			}
		}
	}

}

void CMoveSearch::ReSearchLance(Vector2_3D pos, int Move, Vector2_3D posOld)
{
	int old = posOld.z * m_X + posOld.x;
	int Right;
	int Left;
	int Up;
	int Down;

	if (pos.x + 1 >= m_X)
	{
		Right = old;
	}
	else
	{
		Right = pos.z * m_X + pos.x + 1;
	}
	if (pos.x - 1 < 0)
	{
		Left = old;
	}
	else
	{
		Left = pos.z * m_X + pos.x - 1;
	}
	if (pos.z + 1 >= m_Z)
	{
		Up = old;
	}
	else
	{
		Up = (pos.z + 1) * m_X + pos.x;
	}
	if (pos.z - 1 < 0)
	{
		Down = old;
	}
	else
	{
		Down = (pos.z - 1) * m_X + pos.x;
	}

	//‰E‚ð’Tõ
	if (Right != old)
	{
		if (!m_StageMap[Right].bChar)
		{
			if (Move >= (int)m_StageMap[Right].PanelPattarn || (int)m_StageMap[Right].PanelPattarn == 2)
			{
				Vector2_3D add = { pos.x + 1, pos.z };
				Add(add);
			}
		}
	}

	//¶‚ð’Tõ
	if (Left != old)
	{
		if (!m_StageMap[Left].bChar)
		{
			if (Move >= (int)m_StageMap[Left].PanelPattarn || (int)m_StageMap[Left].PanelPattarn == 2)
			{
				Vector2_3D add = { pos.x - 1, pos.z };
				Add(add);
			}
		}
	}

	//ã‚ð’Tõ
	if (Up != old)
	{
		if (!m_StageMap[Up].bChar)
		{
			if (Move >= (int)m_StageMap[Up].PanelPattarn || (int)m_StageMap[Up].PanelPattarn == 2)
			{
				Vector2_3D add = { pos.x, pos.z + 1 };
				Add(add);
			}
		}
	}

	//‰º‚ð’Tõ
	if (Down != old)
	{
		if (!m_StageMap[Down].bChar)
		{
			if (Move >= (int)m_StageMap[Down].PanelPattarn || (int)m_StageMap[Down].PanelPattarn == 2)
			{
				Vector2_3D add = { pos.x, pos.z - 1 };
				Add(add);
			}
		}
	}

}