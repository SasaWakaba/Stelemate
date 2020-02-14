#ifndef CENEMY_PATTERN_WAIT_H_
#define CENEMY_PATTERN_WAIT_H_

class CCharcterBase;

class CEnemyPatternWait : public CEnemyPattern
{
public:
	virtual ~CEnemyPatternWait() {}
	virtual void Update(CEnemyAI* pEnemy, Vector2_3D* cursol) override;

	float NearLength(std::vector<Vector2_3D> max, Vector2_3D pos);
};



#endif // !CENEMY_PATTERN_NORMAL_H_
