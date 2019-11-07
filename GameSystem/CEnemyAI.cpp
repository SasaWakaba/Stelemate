#include "../common/main.h"
#include "../Stage/CStage.h"
#include <vector>


#include "../common/texture.h"
#include "C3DPolygon.h"

#include "../Charcter/CCharcterBase.h"

#include "CAttackSearch.h"
#include "CMoveSearch.h"

#include "CEnemyAI.h"


void CEnemyAI::Initialize(int numX, int numZ, PanelState* Map)
{
	m_X = numX;
	m_Z = numZ;

	m_StageMap = Map;

	m_AtkSearch = new CAttackSearch();
	m_AtkSearch->Initialize(m_X, m_Z, Map);

	m_MoveSearch = new CMoveSearch();
	m_MoveSearch->Initialize(m_X, m_Z, Map);


}

void CEnemyAI::Finalize()
{
	m_AtkSearch->Finalize();
	delete m_AtkSearch;

	m_MoveSearch->Finalize();
	delete m_MoveSearch;
}

std::vector<Vector2_3D> CEnemyAI::Move(Vector2_3D pos, int Move)
{
	Reset();

	std::vector<Vector2_3D> Area;
	Area = m_MoveSearch->Search(pos, Move);

	std::vector<Vector2_3D> PL;
	for (int z = 0; z < m_Z; z++)
	{
		for (int x = 0; x < m_X; x++)
		{
			if (m_StageMap[z * m_Z + x].bChar)
			{
				if (m_StageMap[z * m_Z + x].Charcter->GetAlly())
				{
					Vector2_3D add = { x,z };
					PL.push_back(add);
				}
			}
		}
	}
	
	Vector2_3D Near = NearLocation(PL, pos);;
	int length_near = abs((pos.x - Near.x)) + abs((pos.z - Near.z));

	PL.clear();

	/*for (Vector2_3D plPos : PL)
	{
		if (length_near != -1)
		{
			int length = abs((pos.x - plPos.x)) + abs((pos.z - plPos.z));
			if (length_near > length)
			{
				Near = plPos;
				length_near = length;
			}
		}
		else
		{
			Near = plPos;
			length_near = abs((pos.x - plPos.x)) + abs((pos.z - plPos.z));
		}
	}*/

	if (length_near != 1)
	{
		Vector2_3D Moving = pos;
		for (int i = Move; i > 0;)
		{
			for (Vector2_3D movePos : Area)
			{
				if (Moving.z == movePos.z)
				{
					if (Moving.x + 1 == movePos.x)
					{
						PL.push_back(movePos);
					}
					if (Moving.x - 1 == movePos.x)
					{
						PL.push_back(movePos);
					}
				}
				else if (Moving.x == movePos.x)
				{
					if (Moving.z + 1 == movePos.z)
					{
						PL.push_back(movePos);
					}
					if (Moving.z - 1 == movePos.z)
					{
						PL.push_back(movePos);
					}
				}
			}
			Moving = NearLocation(PL, Near);
			Add(Moving);
			if (Moving.x == Near.x)
			{
				if (Moving.z == Near.z + 1)
				{
					i = 0;
				}
				else if (Moving.z == Near.z - 1)
				{
					i = 0;
				}
				else
				{
					i--;
				}
			}
			else if (Moving.z == Near.z)
			{
				if (Moving.x == Near.x + 1)
				{
					i = 0;
				}
				else if (Moving.x == Near.x - 1)
				{
					i = 0;
				}
				else
				{
					i--;
				}
			}
			else
			{
				i--;
			}
		}
	}

	




	return m_SearchArea;
}

