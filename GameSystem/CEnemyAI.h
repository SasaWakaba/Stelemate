#ifndef CENEMY_AI_H_
#define CENEMY_AI_H_

#include "../common/math.h"

class CMoveSearch;
class CAttackSearch;
class CEnemyPattern;

class CEnemyAI
{
private:

	StageInfo* m_StageMap;

	CEnemyPattern* m_pEnemyPattern;
	

	std::vector<Vector2_3D> m_SearchArea;

	CMoveSearch*	m_MoveSearch;
	CAttackSearch*	m_AtkSearch;


	EnemyMove					m_EnemyMoving;

	CCharcterBase*				MoveEnemy;
	Vector2_3D					SelectEnemyPos;

	bool bBattle;

public:
	void Initialize(int numX, int numZ, PanelState* Map);
	void Update(Vector2_3D* cursol);
	void Finalize();

	Vector2_3D NearLocation(std::vector<Vector2_3D> max, Vector2_3D pos);

	bool Add(Vector2_3D pos);

	void Reset() { m_SearchArea.clear(); }


	void ChangeEnemyPattern(CEnemyPattern* pattern);

	//エネミーステートパターン用取得関数
	StageInfo* GetStageInfo();
	std::vector<Vector2_3D> GetMoveSearch(Vector2_3D pos, int move);
	std::vector<Vector2_3D> GetAttackSearch(Vector2_3D pos, Weapontype Atk);
	std::vector<Vector2_3D> GetSerchArea();
	CCharcterBase* GetMoveEnemy();
	Vector2_3D	   GetMoveEnemyPos();
	void SetMoveEnemy(CCharcterBase* ene);
	void SetMoveEnemyPos(Vector2_3D pos);
	void ResetMove();
	void ResetAttack();
	EnemyMove GetMove();
	void SetMove(EnemyMove move);

	bool GetBattle();
	void SetBattle(bool bEneble);
};



#endif // !CENEMY_AI_H_
