#ifndef CCHARACTER_STATE_UI_H_
#define CCHARACTER_STATE_UI_H_

#include "../common/main.h"
#include "../common/Game_Object.h"
#include "../Stage/CStage.h"


#define STATE_TEX_NUM (1)

class CTexture;
class CPolygon;
class CScore;

class CCharacterState :public CGameObject
{
private:
	CPolygon* m_CharacterState[STATE_TEX_NUM];

	CScore*	m_StateNum;

	static PanelState* m_PanelState;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	static void SetPanel(PanelState* panel) { m_PanelState = panel; }
};


#endif // !CPANEL_STATE_UI_H_
