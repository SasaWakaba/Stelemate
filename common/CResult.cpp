#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "Game_Object.h"
#include "input.h"
#include "../GameSystem/WorldManager.h"

#include "Scene.h"
#include "manager.h"


#include "../Audio/audio_clip.h"
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

	m_BGM = new CAudioClip();
	m_BGM->Load("asset/audio/resultBGM.wav");
	m_BGM->Play(true);
	CFade::EndFade();
}

void CResult::UnInit()
{
	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;
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