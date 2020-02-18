#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "Game_Object.h"
#include "../GameSystem/WorldManager.h"
#include "../Audio/audio_clip.h"
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
#include "particle.h"
#include "CFade.h"
#include "../GameSystem/CSubCamera.h"
#include "../UI/TitleBackground.h"

bool CTitle::bChange;

void CTitle::Init()
{
	WorldManager::Initialize();
	bChange = false;
	m_BGM = new CAudioClip();
	m_BGM->Load("asset/audio/titleBGM.wav");
	m_BGM->Play(true);

	AddGameObject<CCamera>(0)->SetAt(XMFLOAT3(0.0f, 0.0f, 0.0f));
	AddGameObject<CSkyBox>(0)->SetNight(true);
	AddGameObject<CTitleBackground>(0);
	//CParticle* particleTest = AddGameObject<CParticle>(1);
	//particleTest->CreateInstance(50);
	//XMFLOAT3* movement = new XMFLOAT3[particleTest->GetInstanceCount()];
	//int* startFrame = new int[particleTest->GetInstanceCount()];
	//for (int i = 0; i < particleTest->GetInstanceCount(); i++) {
	//	movement[i].x = cosf((float)(i - 1))*0.05f; //何番目のインスタンスがこういうｘ動きする
	//	movement[i].y = -0.1f;               //何番目のインスタンスがこういうｙ動きする
	//	movement[i].z = 0; //何番目のインスタンスがこういうｚ動きする
	//	startFrame[i] = 0 - i * 2;
	//}
	//particleTest->SetMaxFrame(360);
	//particleTest->SetStartFrame(startFrame);
	//particleTest->SetMovement(movement);

	AddGameObject<CTitleMenu>(2);



	CFade::EndFade();
}

void CTitle::UnInit()
{
	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;
	CScene::UnInit();
}

void CTitle::Update()
{
	CScene::Update();
	if (bChange)
	{
		if (CFade::startFin())
		{
			CManager::SetScene<CPreparation>();
		}
	}

}