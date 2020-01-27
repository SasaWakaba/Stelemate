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

	void Add(Vector2_3D pos);
};


#endif // !CMOVE_SEARCH_H_
