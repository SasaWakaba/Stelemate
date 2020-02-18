
#include "main.h"
#include <Xinput.h>
#include "inputController.h"

XINPUT_STATE CInputController::State;
XINPUT_STATE CInputController::OldState;

void CInputController::Init()
{
	XInputGetState(0, &State);
	XInputGetState(0, &OldState);
}
void CInputController::Uninit()
{

}
void CInputController::Update()
{
	OldState = State;
	XInputGetState(0, &State);
	//XInputEnable(true);
}

bool CInputController::GetKeyPress(WORD KeyCode)
{
	return (State.Gamepad.wButtons & KeyCode);
}
bool CInputController::GetKeyTrigger(WORD KeyCode)
{
	return ((State.Gamepad.wButtons & KeyCode) && !(OldState.Gamepad.wButtons & KeyCode));
}