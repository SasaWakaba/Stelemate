#ifndef ENEMY_PATTERN_H_
#define ENEMY_PATTERN_H_

class CEnemyAI;

class CEnemyPattern
{
public:
	virtual ~CEnemyPattern() {}
	virtual void Update(CEnemyAI* pEnemy, Vector2_3D* cursol) = 0;
};

class CEnemyPatternNone : public CEnemyPattern
{
public:
	virtual ~CEnemyPatternNone() {}
	virtual void Update(CEnemyAI* pEnemy, Vector2_3D* cursol) override {}
};

#endif // !ENEMY_PATTERN_H_
