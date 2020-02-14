#ifndef CENEMY_PATTERN_END_H_
#define CENEMY_PATTERN_END_H_

class CCharcterBase;

class CEnemyPatternEnd : public CEnemyPattern
{
public:
	virtual ~CEnemyPatternEnd() {}
	virtual void Update(CEnemyAI* pEnemy, Vector2_3D* cursol) override;
};



#endif // !CENEMY_PATTERN_NORMAL_H_
