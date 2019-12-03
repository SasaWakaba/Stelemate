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
#include "particle.h"
#include "CFade.h"

bool CTitle::bChange;

void CTitle::Init()
{
	bChange = false;

	AddGameObject<CCamera>(0)->SetAt(XMFLOAT3(0.0f, 0.0f, 0.0f));
	//AddGameObject<CSkyBox>(0)->SetNight(true);

	CParticle* particleTest = AddGameObject<CParticle>(0);
	particleTest->CreateInstance(25);
	XMFLOAT3* movement = new XMFLOAT3[particleTest->GetInstanceCount()];
	int* startFrame = new int[particleTest->GetInstanceCount()];
	for (int i = 0; i < particleTest->GetInstanceCount(); i++) {
		movement[i].x = cos((i - 1))*0.05f; //何番目のインスタンスがこういうｘ動きする
		movement[i].y = 0.05f;               //何番目のインスタンスがこういうｙ動きする
		movement[i].z = sin((i - 1))*0.05f; //何番目のインスタンスがこういうｚ動きする
		startFrame[i] = 0 - i * 2;
	}
	particleTest->SetMaxFrame(60);
	particleTest->SetStartFrame(startFrame);
	particleTest->SetMovement(movement);

	//AddGameObject<CTitleMenu>(1);

	CFade::EndFade();

	// メモリリーク検出
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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