#ifndef CPREPARATION_H_
#define CPREPARATION_H_

#include "../common/CFade.h"

class CPreparation : public CScene
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

#endif // !CPREPARATION_H_
