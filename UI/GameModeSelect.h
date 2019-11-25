#ifndef CGAME_MODE_SELECT_H_
#define CGAME_MODE_SELECT_H_

#include "../GameSystem/WorldManager.h"

class CPolygon;
class CDrawText;

class CGameModeSelect
{
private:
	CPolygon*	m_Texture[5];
	CDrawText*	m_Text[2];

	GameMode m_select;

	int frame;
public:
	CGameModeSelect();
	~CGameModeSelect();

	void Update();
	void Draw();

};

#endif // !CGAME_MODE_SELECT_H_
