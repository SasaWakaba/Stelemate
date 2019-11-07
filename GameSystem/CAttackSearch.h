#ifndef CATTACK_SEARCH_H_
#define CATTACK_SEARCH_H_

#include "../common/main.h"
#include "../Stage/CStage.h"
#include <vector>

#include "../common/texture.h"
#include "C3DPolygon.h"

#include "../Charcter/CCharcterBase.h"

class CAttackSearch
{
private:
	int m_X;
	int m_Z;

	PanelState* m_StageMap;

	C3DPolygon* m_Polygon;

	CTexture* m_Atk;

	std::vector<Vector2_3D> m_AtkArea;

	bool bDraw;

public:
	void Initialize(int numX, int numZ, PanelState* Map);
	void Finalize();
	void Draw();

	std::vector<Vector2_3D> Search(Vector2_3D pos, Weapontype Atk);

	void Reset() { m_AtkArea.clear(); }

	void SetDraw(bool bEnable) { bDraw = bEnable; }

	void Add(Vector2_3D pos)
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
};


#endif // !CATTACK_SEARCH_H_
