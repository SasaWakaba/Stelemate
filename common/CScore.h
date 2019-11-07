#ifndef CSCORE_H_
#define CSCORE_H_

class CNumber;

class CScore
{
private:
	CNumber* m_Num;
	int m_Digit;
	int m_CounterStopValue;
public:
	void Initialize(int digit);
	void Finalize(void);
	void Draw(float x, float y, int score, bool bZero, bool bLeft);
};



#endif // !SCORE_H_
