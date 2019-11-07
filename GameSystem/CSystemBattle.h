#ifndef CSYSTEM_BATTLE_H_
#define CSYSTEM_BATTLE_H_

#include "../common/Game_Object.h"
#include "../Charcter/CCharcterBase.h"
#include "../common/polygon.h"

#define BATTLE_TEXTURE_WIDTH (960)
#define BATTLE_TEXTURE_HEIGHT (420)



class CSystemBattle:public CGameObject
{
private:
	static CCharcterBase *m_Char_A;
	static CCharcterBase *m_Char_B;

	static bool bBattle;

	static float X;

	CPolygon*	m_Polygon[3];

	bool bMove;

	int AnimFrame;

public:


	static bool Battle(CCharcterBase* pA, CCharcterBase* pB);
	static bool BattleEnd() { return bBattle; }

	void Initialize();
	void Finalize();
	void Draw();
	void Update();

	void Damage();
};

#endif // !CSYSTEM_BATTLE
