#ifndef CSYSTEM_BATTLE_H_
#define CSYSTEM_BATTLE_H_


#include "../Stage/CStage.h"

#define CHARACTER_MAX (4)
#define UI_MAX (7)

class CPolygon;
class CSubCamera;
class CBattleRand;
class CTexture;
class CSkyBox;
class CModelAnimation;
class CDrawText;
class CCircleShadow;

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

	CPolygon*	m_Polygon[UI_MAX];

	CSubCamera*	camera;

	bool bMove;

	int AnimFrame;

	CBattleRand* Rand;
	CTexture*	tex[2];

	static XMFLOAT4 view;
	static int Fase;
	static int CreateFrame;

	static int Frame;

	static XMFLOAT3 charaPos[2];
	static float	charaRot[2];

	CSkyBox* sky;

	CModelAnimation* Model[CHARACTER_MAX];

	int Damage_A = 0;
	int Damage_B = 0;
	float DamageCount = 0;
	CDrawText* text;
	CCircleShadow* shadow;

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
