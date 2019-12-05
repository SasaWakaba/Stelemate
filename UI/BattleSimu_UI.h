#ifndef CBATTLE_SIMU_H_
#define CBATTLE_SIMU_H_

#include "../common/Game_Object.h"

#define MAX_TEXNUM (5)
class CPolygon;
class CDrawText;
class CScore;
class CCharacterBase;

class CBattleSimu:public CGameObject
{
private:
	XMFLOAT2		m_Pos;
	CPolygon*		m_Texture[MAX_TEXNUM];
	CDrawText*		m_Text[2];
	CScore*			m_Number;
	CCharacterBase*	m_Char[2];

	bool			bDraw;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !CBATTLE_SIMU_H_
