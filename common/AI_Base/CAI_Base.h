#ifndef CAI_BASE_H_
#define CAI_BASE_H_

#include "CBlackBoard.h"
#include "CTask.h"

class CAiBase
{
protected:
	CBlackBoard*	m_BlackBoard;
	CTask*			m_Root;
public:
	CAiBase(CBlackBoard* blackboard):m_BlackBoard(blackboard){}
	virtual ~CAiBase(){}

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
};

#endif // CAI_BASE_H_
