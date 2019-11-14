#ifndef CSCORE_H_
#define CSCORE_H_

class CNumber;

class CScore
{
private:
	CNumber* m_Num;
	int m_Digit;
	int m_CounterStopValue;
	int m_Wight;
	int m_Height;
public:
	void Initialize(int digit, int w, int h);
	void Finalize(void);
	void Draw(float x, float y, int score);
};



#endif // !SCORE_H_
