#ifndef CFADE_H_
#define CFADE_H_

//#include "main.h"
//#include "Game_Object.h"
//#include "polygon.h"

class CPolygon;

class CFade
{
private:
	static CPolygon* m_Polygon[2];
	static bool bFadeStart;
	static bool bFadeEnd;
	static float m_pos[2];
	static int frame;

	static bool startfin;

public:
	static void Initialize();
	static void Finalize();
	static void Update();
	static void Draw();

	static void StartFade();
	static void EndFade();

	static bool startFin();
};


#endif // !CFADE_H_
