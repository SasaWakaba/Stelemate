#ifndef CDECORATOR_H_
#define CDECORATOR_H_

class CBlackBoard;

class CDecorator
{
protected:
	CBlackBoard* m_BlackBoard;
public:
	CDecorator(CBlackBoard* bb) :m_BlackBoard(bb) {}

	virtual bool Decorator() = 0;
};



#endif // !CDECORATOR_H_
