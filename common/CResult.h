#ifndef CRESULT_H_
#define CRESULT_H_

#include "CFade.h"
class CAudioClip;

class CResult :public CScene
{
private:
	static bool bChange;
	static int Select;
	CAudioClip* m_BGM;
public:
	void Init();
	void UnInit();
	void Update();

	static void Change(int select);
};



#endif // !CRESULT
