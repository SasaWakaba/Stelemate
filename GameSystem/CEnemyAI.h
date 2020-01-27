#ifndef CENEMY_AI_H_
#define CENEMY_AI_H_

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

	bool Add(Vector2_3D pos);


	Vector2_3D NearLocation(std::vector<Vector2_3D> max, Vector2_3D pos);

public:
	void Initialize(int numX, int numZ, PanelState* Map);
	void Finalize();

	std::vector<Vector2_3D> Move(Vector2_3D pos, int Move);

	EnemyMove Select(Vector2_3D pos, Weapontype Atk);

	void Reset() { m_SearchArea.clear(); }

};



#endif // !CENEMY_AI_H_
