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
	CAiBase(CBlackBoard* blackboard, CTask* root):m_BlackBoard(blackboard), m_Root(root){}
	virtual ~CAiBase(){}

	virtual void Play() = 0;
};

#endif // CAI_BASE_H_
