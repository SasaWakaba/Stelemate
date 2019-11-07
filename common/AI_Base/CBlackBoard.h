#ifndef CBLACKBOARD_H_
#define CBLACKBOARD_H_

class CBlackBoard
{
public:
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
};

#endif // !CBLACKBOARD_H_
