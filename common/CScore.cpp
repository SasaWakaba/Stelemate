#include "../common/main.h"
#include "number.h"
#include "CScore.h"

#define SCORE_WIDTH (50)
#define SCORE_HEIGHT (50)


void CScore::Initialize(int digit)
{
	m_Num = new CNumber();
	m_Num->Initialize();

	m_Digit = digit;

	m_CounterStopValue = 1;
	for (int i = 0; i < digit; i++)
	{
		m_CounterStopValue *= 10;
	}
	m_CounterStopValue--;
}

void CScore::Finalize(void)
{
	m_Num->Finalize();
	delete m_Num;
}

void CScore::Draw(float x, float y, int score, bool bZero, bool bLeft)
{
	//ƒJƒ“ƒXƒgˆ—
	if (score > m_CounterStopValue)
	{
		score = m_CounterStopValue;
	}
	for (int i = m_Digit - 1; i >= 0; i--)
	{
		m_Num->Draw(x + SCORE_WIDTH * i, y, SCORE_WIDTH, SCORE_HEIGHT, score % 10);
		score /= 10;
	}
}