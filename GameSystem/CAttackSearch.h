#ifndef CATTACK_SEARCH_H_
#define CATTACK_SEARCH_H_

#include "../common/main.h"
#include "../Stage/CStage.h"

class C3DPolygon;
class CTexture;

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

	void Add(Vector2_3D pos);
};


#endif // !CATTACK_SEARCH_H_
