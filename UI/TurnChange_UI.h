#ifndef CTURN_CHANGE_UI_
#define CTURN_CHANGE_UI_


#include "../common/main.h"
#include "../common/Game_Object.h"
class CPolygon;

#define TURNCHANGE_UI_WIDTH (600.0f)
#define TURNCHANGE_UI_HEIGHT (200.0f)

class CTurnChangeUI:public CGameObject
{
private:
	CPolygon *m_Polygon[2];

	float pos;

	int m_Count;

	bool m_bDrawPL;
	bool m_bDrawEne;
public:

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	bool GetEndPL() { return m_bDrawPL; }
	bool GetEndEne() { return m_bDrawEne; }

	void ChangePlayer()
	{
		if (!m_bDrawPL)
		{
			m_Count = 0;
			m_bDrawPL = true;
		}
	}
	void ChangeEnemy()
	{
		if (!m_bDrawEne)
		{
			m_Count = 0;
			m_bDrawEne = true;
		}
	}
};


#endif // !CTURN_CHANGE_UI_
