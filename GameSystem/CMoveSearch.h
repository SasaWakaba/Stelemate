#ifndef CMOVE_SEARCH_H_
#define CMOVE_SEARCH_H_

#include "../common/main.h"
#include "../Stage/CStage.h"

class C3DPolygon;
class CTexture;

class CMoveSearch
{
private:
	int m_X;
	int m_Z;

	PanelState* m_StageMap;

	C3DPolygon* m_Polygon;

	CTexture* m_Move[2];

	std::vector<Vector2_3D> m_MoveArea;

	bool bDraw;

	bool PL;

	void ReSearch(Vector2_3D pos, int Move, Vector2_3D posOld);
	void ReSearchLance(Vector2_3D pos, int Move, Vector2_3D posOld);

public:
	void Initialize(int numX, int numZ, PanelState* Map);
	void Finalize();
	void Draw();

	std::vector<Vector2_3D> Search(Vector2_3D pos, CCharcterBase* Move);

	void Reset() { m_MoveArea.clear(); }

	void SetDraw(bool bEnable, bool pl) { bDraw = bEnable; PL = pl; }

	void Add(Vector2_3D pos);
};


#endif // !CMOVE_SEARCH_H_
