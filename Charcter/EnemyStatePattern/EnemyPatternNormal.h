#ifndef CENEMY_PATTERN_NORMAL_H_
#define CENEMY_PATTERN_NORMAL_H_

class CCharcterBase;

class CEnemyPatternNormal : public CEnemyPattern
{
private:
	CCharcterBase*				MoveEnemy;
	Vector2_3D					SelectEnemyPos;
public:
	virtual ~CEnemyPatternNormal() {}
	virtual void Update(CEnemyAI* pEnemy, Vector2_3D* cursol) override;

	std::vector<Vector2_3D> Move(CEnemyAI* pEnemy, Vector2_3D pos, CCharcterBase* Move);
	EnemyMove Select(CEnemyAI* pEnemy, Vector2_3D pos, Weapontype Atk);

	Vector2_3D NearLocation(std::vector<Vector2_3D> max, Vector2_3D pos);
};



#endif // !CENEMY_PATTERN_NORMAL_H_
