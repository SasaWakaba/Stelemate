#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include<Xinput.h>
#pragma comment (lib, "xinput.lib")

class CInputController
{
private:
	static XINPUT_STATE State;
	static XINPUT_STATE OldState;
public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress(WORD KeyCode);
	static bool GetKeyTrigger(WORD KeyCode);
};


#endif // !INPUT_CONTROLLER_H_
