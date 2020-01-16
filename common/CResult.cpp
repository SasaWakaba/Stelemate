#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "Game_Object.h"
#include "input.h"

#include "Scene.h"
#include "manager.h"



#include "CTitle.h"
#include "CGame.h"
#include "CResult.h"


#include "MeshField.h"

#include "polygon.h"

#include "CFade.h"

#include "camera.h"
#include "CSkyBox.h"

bool CResult::bChange;


void CResult::Init()
{


	AddGameObject<CCamera>(0)->SetAt(XMFLOAT3(0.0f, 0.0f, 0.0f));
	AddGameObject<CSkyBox>(0)->SetNight(true);
	bChange = false;
	CFade::EndFade();
}

void CResult::UnInit()
{
	CScene::UnInit();
}

void CResult::Update()
{
	CScene::Update();
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		Change();
	}

	if (bChange)
	{
		if (CFade::startFin())
		{
			CManager::SetScene<CTitle>();
		}
	}
}