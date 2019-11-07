#ifndef CARROWS_LINE_H_
#define CARROWS_LINE_H_

#include <vector>
#include "../common/main.h"
#include "../common/texture.h"

#include "C3DPolygon.h"

//typedef struct
//{
//	Vector2_3D start;
//	Vector2_3D End;
//
//	Vector2_3D* Line;
//	int nPanel;
//}Arrows;


class CArrowsLine
{
private:
	CTexture* m_Arrows;
	CTexture* m_Line;
	CTexture* m_Curve;

	C3DPolygon* m_Polygon;

	std::vector<Vector2_3D> m_ArrowsLine;

public:
	void Add(Vector2_3D pos) 
	{ 
		if (m_ArrowsLine.size() != 0)
		{
			int copy = 0;
			for (int i = 0; i < m_ArrowsLine.size(); i++)
			{
				if (m_ArrowsLine[i].x == pos.x && m_ArrowsLine[i].z == pos.z)
				{
					copy = m_ArrowsLine.size() - i;
					break;
				}
			}

			if (copy == 0)
			{
				m_ArrowsLine.push_back(pos);
			}
			else
			{
				for (int i = 0; i < copy; i++)
				{
					Delete();
				}
				m_ArrowsLine.push_back(pos);
			}
			
		}
		else
		{
			m_ArrowsLine.push_back(pos);
		}
	}

	void Delete() { m_ArrowsLine.pop_back(); }

	void Reset() { m_ArrowsLine.clear(); }

	void Initialize();
	void Finalize();
	void Draw(int x, int z);
};


#endif // !CARROWS_LINE_H_
