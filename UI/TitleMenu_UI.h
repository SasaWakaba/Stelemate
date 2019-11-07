#ifndef CTITLE_MENU_H_
#define CTITLE_MENU_H_

#include "../common/main.h"
#include "../common/Game_Object.h"
#include "../common/texture.h"
#include "../common/polygon.h"

#define TITLELOGO_WIDTH (1024.0f)
#define TITLELOGO_HEIGHT (512.0f)

class CModelLoader;

class CTitleMenu:public CGameObject
{
private:

	enum TitleTexture
	{
		Title_Logo,
		PressSpace,
		Menu_0,
		Menu_1,
		Menu_2,
		Menu_3,
	};

	CModelLoader*	m_Model;
	CPolygon*		m_Polygon[6];

	//PRESS========
	float PressAlpha;

	float TitleAlpha;

	UI_POS m_PosTitle;

	bool bDown;

	bool PressWait;

	bool bPressSpace;

	int m_Count;
	//=============

	//SELECT=======
	float SelectEffect;

	UI_POS m_PosSelect[3];

	int SelectNum;
	//=============
	int Frame;




public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !CTITLE_MENU_H_
