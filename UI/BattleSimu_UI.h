#ifndef CBATTLE_SIMU_H_
#define CBATTLE_SIMU_H_

#include "../common/Game_Object.h"

#define MAX_TEXNUM (10)
class CPolygon;
class CDrawText;
class CScore;

class CBattleSimu:public CGameObject
{
private:
	XMFLOAT2		m_Pos;
	CPolygon*		m_Texture[MAX_TEXNUM];
	CDrawText*		m_Text[2];
	CScore*			m_Number;
	CCharcterBase*	m_Char[2];

	bool			bDraw;
	int				frame;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void SetDraw(bool benable) { bDraw = benable; }
	void SetChar(CCharcterBase* A, CCharcterBase* B) { m_Char[0] = A; m_Char[1] = B; }
};

#endif // !CBATTLE_SIMU_H_
