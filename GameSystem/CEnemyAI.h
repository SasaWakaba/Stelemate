#ifndef CENEMY_AI_H_
#define CENEMY_AI_H_

#include "../common/main.h"
#include "../Stage/CStage.h"
#include <vector>


#include "../common/texture.h"
#include "C3DPolygon.h"

#include "../Charcter/CCharcterBase.h"
#include "../common/math.h"

class CMoveSearch;
class CAttackSearch;



class CEnemyAI
{
private:

	int m_X;
	int m_Z;

	PanelState* m_StageMap;

	
	std::vector<Vector2_3D> m_SearchArea;

	CMoveSearch*	m_MoveSearch;
	CAttackSearch*	m_AtkSearch;

	bool Add(Vector2_3D pos)
	{
		if (m_SearchArea.size() != 0)
		{
			bool re = false;
			for (int i = 0; i < m_SearchArea.size(); i++)
			{
				if (m_SearchArea[i].x == pos.x && m_SearchArea[i].z == pos.z)
				{
					re = true;
					break;
				}
			}


			if (!re)
			{
				m_SearchArea.push_back(pos);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			m_SearchArea.push_back(pos);
			return true;
		}
	}


	Vector2_3D NearLocation(std::vector<Vector2_3D> max, Vector2_3D pos)
	{
		Vector2_3D Near;
		int length_near = -1;
		for (Vector2_3D plPos : max)
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
		}

		return Near;
	}

public:
	void Initialize(int numX, int numZ, PanelState* Map);
	void Finalize();

	std::vector<Vector2_3D> Move(Vector2_3D pos, int Move);

	EnemyMove Select(Vector2_3D pos, Weapontype Atk);

	void Reset() { m_SearchArea.clear(); }

};



#endif // !CENEMY_AI_H_
