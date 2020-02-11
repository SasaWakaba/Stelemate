
#include "../common/CGame.h"
#include "../common/manager.h"
#include "../common/CFade.h"
#include "../common/Scene.h"
#include "../Audio/audio_clip.h"
#include "CPreparation.h"
#include "../UI/Preparation_UI.h"


//CRI ADX2
//Wwise
bool CPreparation::bChange;

void CPreparation::Change()
{
	if (!bChange)
	{
		bChange = true;
		CFade::StartFade();
	}
}

void CPreparation::Init()
{

	bChange = false;
	m_BGM = new CAudioClip();
	m_BGM->Load("asset/audio/tw040.wav");
	//m_BGM->Play(true);

	AddGameObject<CPreparationUI>(1);

	CFade::EndFade();
}

void CPreparation::UnInit()
{

	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;
	CScene::UnInit();
}

void CPreparation::Update()
{
	CScene::Update();

	if (bChange)
	{
		if (CFade::startFin())
		{
			CManager::SetScene<CGame>();
		}
	}

}