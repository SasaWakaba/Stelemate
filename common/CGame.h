#ifndef CGAME_H_
#define CGAME_H_

#include "Scene.h"
#include "CFade.h"
class CAudioClip;

class CGame :public CScene
{
private:
	static bool bChange;
	CAudioClip* m_BGM;
public:

	void Init();
	void UnInit();
	void Update();

	static void Change() 
	{ 
		if (!bChange)
		{
			bChange = true; 
			CFade::StartFade();
		}
	}
};



#endif // !CGAME_H_H
