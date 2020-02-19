#ifndef CENEMY_PATTERN_MOVE_H_
#define CENEMY_PATTERN_MOVE_H_

class CCharcterBase;

class CEnemyPatternMove : public CEnemyPattern
{
public:
	virtual ~CEnemyPatternMove() {}
	virtual void Update(CEnemyAI* pEnemy, Vector2_3D* cursol) override;

	std::vector<Vector2_3D> Move(CEnemyAI* pEnemy, Vector2_3D pos, CCharcterBase* Move);
	EnemyMove Select(CEnemyAI* pEnemy, Vector2_3D pos, Weapontype Atk);
};



#endif // !CENEMY_PATTERN_MOVE_H_
