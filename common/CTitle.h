#ifndef CTITLE_H_
#define CTITLE_H_

#include "CFade.h"
class CAudioClip;

class CTitle :public CScene
{
private:
	static bool bChange;
	CAudioClip* m_BGM;
public:

	void Init();
	void UnInit();
	void Update();

	static void Change() { bChange = true; CFade::StartFade(); }
};

#endif // !CTITLE_H_
