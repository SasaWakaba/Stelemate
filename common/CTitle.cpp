#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "Game_Object.h"
#include "input.h"

#include "Scene.h"
#include "manager.h"
#include "CResult.h"
#include "CGame.h"
#include "../GameSystem/CPreparation.h"
#include "CTitle.h"

#include "polygon.h"
#include "camera.h"
#include "CSkyBox.h"

#include "../UI/TitleMenu_UI.h"

#include "CFade.h"

bool CTitle::bChange;

void CTitle::Init()
{
	bChange = false;

	AddGameObject<CCamera>(0)->SetAt(XMFLOAT3(0.0f, 0.0f, 0.0f));
	AddGameObject<CSkyBox>(0)->SetNight(true);

	AddGameObject<CTitleMenu>(1);

	CFade::EndFade();

	// ÉÅÉÇÉäÉäÅ[ÉNåüèo
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void CTitle::UnInit()
{
	CScene::UnInit();
}

void CTitle::Update()
{
	CScene::Update();
	if (bChange)
	{
		if (CFade::startFin())
		{

			//CManager::SetScene<CGame>();
			CManager::SetScene<CPreparation>();
		}
	}

}