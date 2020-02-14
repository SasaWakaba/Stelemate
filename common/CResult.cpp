#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "Game_Object.h"
#include "input.h"
#include "../GameSystem/WorldManager.h"

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
#include "../UI/Result_UI.h"

bool CResult::bChange;
int CResult::Select;

void CResult::Init()
{
	AddGameObject<CResultUI>(0);
	bChange = false;
	CFade::EndFade();
}

void CResult::UnInit()
{
	CScene::UnInit();
}

void CResult::Change(int select) 
{
	bChange = true; 
	CFade::StartFade();
	Select = select;
}

void CResult::Update()
{
	CScene::Update();
	//if (CInput::GetKeyTrigger(VK_SPACE))
	//{
	//	Change();
	//}

	if (bChange)
	{
		if (CFade::startFin())
		{
			if (Select == 0)
			{
				CManager::SetScene<CPreparation>();
			}
			else
			{
				WorldManager::Finalize();
				CManager::SetScene<CTitle>();
			}
		}
	}
}