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



#include "../Audio/audio_clip.h"

#include "Scene.h"
#include "manager.h"
#include "CResult.h"
#include "CGame.h"


#include "CFade.h"


//CRI ADX2
//Wwise
bool CGame::bChange;

void CGame::Init()
{

	bChange = false;
	m_BGM = new CAudioClip();
	m_BGM->Load("asset/audio/tw040.wav");
	m_BGM->Play(true);



	AddGameObject<CCamera>(0);



	//AddGameObject<CPolygon>(4);

	AddGameObject<CSkyBox>(0);
	AddGameObject<CStageManager>(0)->SetStageNum(0);

	AddGameObject<CPanelState>(3);

	AddGameObject<CGameMenu_UI>(4);

	AddGameObject<CSystemBattle>(4);

	AddGameObject<CTurnChangeUI>(4);
	AddGameObject<CBattleSimu>(4);

	CFade::EndFade();


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