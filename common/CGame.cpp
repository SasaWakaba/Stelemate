#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "Game_Object.h"
#include "input.h"

#include "camera.h"
#include "model.h"
#include "polygon.h"
#include "Field.h"
#include "Wall.h"
#include "MeshField.h"


#include "CSkyBox.h"
#include "../UI/GameMenu_UI.h"
#include "../GameSystem/CSystemBattle.h"
#include "../UI/PanelState_UI.h"
#include "../UI/TurnChange_UI.h"
#include "../UI/BattleSimu_UI.h"
#include "../UI/CharacterState.h"


#include "../Audio/audio_clip.h"

#include "Scene.h"
#include "manager.h"
#include "CResult.h"


#include "CFade.h"
#include "../GameSystem/CSubCamera.h"

#include "CGame.h"



//CRI ADX2
//Wwise
bool CGame::bChange;

void CGame::Change()
{
	if (!bChange)
	{
		bChange = true;
		CFade::StartFade();
	}
}

void CGame::Init()
{

	bChange = false;
	m_BGM = new CAudioClip();
	m_BGM->Load("asset/audio/tw040.wav");
	//m_BGM->Play(true);



	AddGameObject<CCamera>(0);



	//AddGameObject<CPolygon>(4);

	AddGameObject<CSkyBox>(0);
	AddGameObject<CStageManager>(0)->SetStageNum(0);



	AddGameObject<CPanelState>(3);
	AddGameObject<CCharacterState>(3);

	AddGameObject<CGameMenu_UI>(4);


	AddGameObject<CTurnChangeUI>(4);
	AddGameObject<CBattleSimu>(4);

	AddGameObject<CSystemBattle>(4);
	
	//AddGameObject<CSubCamera>(4);
	////AddGameObject<CSkyBox>(4)->SetNight(true);
	
	CFade::EndFade();
	//CRenderer::SetDepthEnable(false);
	//AddGameObject<CSubCamera>(4)->SetViewPos(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH / 6 * 5, SCREEN_HEIGHT / 6 * 5);
	//AddGameObject<CWall>(4);
	//CRenderer::SetDepthEnable(true);
}

void CGame::UnInit()
{
	
	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;
	CScene::UnInit();
}

void CGame::Update()
{
	CScene::Update();

	if (bChange)
	{
		if (CFade::startFin())
		{
			CManager::SetScene<CResult>();
		}
	}

}