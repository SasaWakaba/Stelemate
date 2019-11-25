
#include "../common/CGame.h"
#include "../common/manager.h"
#include "../common/CFade.h"
#include "../common/Scene.h"
#include "CPreparation.h"


//CRI ADX2
//Wwise
bool CPreparation::bChange;

void CPreparation::Init()
{

	bChange = false;
	m_BGM = new CAudioClip();
	m_BGM->Load("asset/audio/tw040.wav");
	m_BGM->Play(true);

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