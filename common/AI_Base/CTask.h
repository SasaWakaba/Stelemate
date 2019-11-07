#ifndef CTASK_H_
#define CTASK_H_

class CBlackBoard;

class CTask
{
protected:
	CBlackBoard* m_BlackBoard;
public:
	CTask(CBlackBoard* bb):m_BlackBoard(bb){}

	virtual bool Task() = 0;
};


#endif // !CTASK_H_
