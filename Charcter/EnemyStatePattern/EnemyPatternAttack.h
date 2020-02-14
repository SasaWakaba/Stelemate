#ifndef CENEMY_PATTERN_ATTACK_H_
#define CENEMY_PATTERN_ATTACK_H_

class CCharcterBase;

class CEnemyPatternAttack : public CEnemyPattern
{
public:
	virtual ~CEnemyPatternAttack() {}
	virtual void Update(CEnemyAI* pEnemy, Vector2_3D* cursol) override;

	Vector2_3D HPLower(std::vector<Vector2_3D> max, StageInfo* stage);
};



#endif // !CENEMY_PATTERN_ATTACK_H_
