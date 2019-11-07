#ifndef CPANEL_STATE_UI_H_
#define CPANEL_STATE_UI_H_

#include "../common/main.h"
#include "../common/Game_Object.h"

#define PANELSTATE_TEX_NUM (6)

class CTexture;
class CPolygon;

class CPanelState:public CGameObject
{
private:
	CPolygon* m_Polygon[PANELSTATE_TEX_NUM];
	static unsigned short m_PanelPattarn;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	static void SetPanel(unsigned short panel) { m_PanelPattarn = panel; }
};


#endif // !CPANEL_STATE_UI_H_
