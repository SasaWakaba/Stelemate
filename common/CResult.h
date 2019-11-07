#ifndef CRESULT_H_
#define CRESULT_H_

#include "CFade.h"

class CResult :public CScene
{
private:
	static bool bChange;
public:
	void Init();
	void UnInit();
	void Update();

	static void Change() { bChange = true; CFade::StartFade(); }
};



#endif // !CRESULT
