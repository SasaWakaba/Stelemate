#ifndef CBATTLE_SIMU_H_
#define CBATTLE_SIMU_H_

#include "../common/Game_Object.h"
class CPolygon;

class CBattleSimu:public CGameObject
{
private:
	Vector2_3D		m_Pos;
	CPolygon*		m_Texture[4];

	bool			bDraw;
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !CBATTLE_SIMU_H_
