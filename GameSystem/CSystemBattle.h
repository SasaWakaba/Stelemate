#ifndef CSYSTEM_BATTLE_H_
#define CSYSTEM_BATTLE_H_


#define BATTLE_TEXTURE_WIDTH (960)
#define BATTLE_TEXTURE_HEIGHT (420)

#include "../Stage/CStage.h"
class CPolygon;
class CSubCamera;
class CBattleRand;
class CTexture;
class CSkyBox;

class CSystemBattle:public CGameObject
{
private:
	enum
	{
		BackSet = 0,
		MoveCamera,
		MoveCharA,
		AttackA,
		MoveCharB,
		AttackB,
		End,
	};

	static PanelState *m_Char_A;
	static PanelState *m_Char_B;

	static bool bBattle;

	static float X;

	CPolygon*	m_Polygon[3];

	CSubCamera*	camera;

	bool bMove;

	int AnimFrame;

	CBattleRand* Rand;
	CTexture*	tex[2];

	static XMFLOAT4 view;
	static int Fase;
	static int CreateFrame;

	static int Frame;

	CSkyBox* sky;

public:


	static bool Battle(PanelState* pA, PanelState* pB);
	static bool BattleEnd() { return bBattle; }

	void Initialize();
	void Finalize();
	void Draw();
	void Update();

	void Damage();
};

#endif // !CSYSTEM_BATTLE
