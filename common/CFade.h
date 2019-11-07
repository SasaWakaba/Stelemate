#ifndef CFADE_H_
#define CFADE_H_

#include "main.h"
#include "Game_Object.h"
#include "polygon.h"

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

	static void StartFade() { 
	bFadeStart = true;	
	m_pos[0] = -SCREEN_WIDTH;
	m_pos[1] = 0.0f;
	frame = 0;
	startfin = false;
	}
	static void EndFade() {
		if (bFadeStart)
		{
			bFadeEnd = true;
			bFadeStart = false;
		}
		else
		{
			bFadeEnd = true;
			bFadeStart = false;
			m_pos[0] = SCREEN_WIDTH / 2;
		}
	}

	static bool startFin() { return startfin; }
};


#endif // !CFADE_H_
