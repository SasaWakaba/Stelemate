#ifndef GAME_MENU_UI_H_
#define GAME_MENU_UI_H_

#include "../common/main.h"
#include "../common/Game_Object.h"
class CTexture;
class CPolygon;

#define GAMEMENU_UI_WIDTH (150.0f)
#define GAMEMENU_UI_HEIGHT (75.0f)

#define NUM_UI (5)

class CGameMenu_UI:public CGameObject
{
private:
	bool m_bDraw;

	bool m_Atk;
	bool m_Heal;
	bool m_Stay;

	int m_Count;
	int m_DrawCnt;

	int m_MenuPos;

	CPolygon *m_Polygon[NUM_UI];

	UI_POS m_Pos[NUM_UI];

	int frame;

public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void Set(bool atk, bool heal, bool stay);
	void reset();

	bool Ready() { return m_Count == 120; }
	int OK() { return m_MenuPos; }
};

#endif // !GAME_MENU_UI_H_
