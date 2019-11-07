#ifndef CMOVE_SEARCH_H_
#define CMOVE_SEARCH_H_

#include "../common/main.h"
#include "../Stage/CStage.h"
#include <vector>

#include "../common/texture.h"
#include "C3DPolygon.h"

class CMoveSearch
{
private:
	int m_X;
	int m_Z;

	PanelState* m_StageMap;

	C3DPolygon* m_Polygon;

	CTexture* m_Move;

	std::vector<Vector2_3D> m_MoveArea;

	bool bDraw;

	void ReSearch(Vector2_3D pos, int Move, Vector2_3D posOld);

public:
	void Initialize(int numX, int numZ, PanelState* Map);
	void Finalize();
	void Draw();

	std::vector<Vector2_3D> Search(Vector2_3D pos, int Move);

	void Reset() { m_MoveArea.clear(); }

	void SetDraw(bool bEnable) { bDraw = bEnable; }

	void Add(Vector2_3D pos)
	{
		if (m_MoveArea.size() != 0)
		{
			bool re = false;
			for (int i = 0; i < m_MoveArea.size(); i++)
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
};


#endif // !CMOVE_SEARCH_H_
