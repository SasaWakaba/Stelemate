



#include "Scene.h"

#include "../Audio/audio_clip.h"

#include "../DebugUi/DebugUI.h"

#include "manager.h"

#include "CTitle.h"
#include "CGame.h"
#include "CResult.h"

#include "CFade.h"



CScene* CManager::m_scene = nullptr;

void CManager::Init()
{

	CRenderer::Init();
	CInput::Init();
	
	CFade::Initialize();

	SetScene<CTitle>();

	CAudioClip::Init();


}

void CManager::UnInit()
{

	CFade::Finalize();
	

	m_scene->UnInit();

	CAudioClip::Uninit();

	CRenderer::Uninit();

}

void CManager::Update()
{
	CFade::Update();

	if (GetDebugWindow())
	{
		CDebugUI::Update();
	}

	CInput::Update();

	m_scene->Update();
}

void CManager::Draw()
{

	CRenderer::Begin();

	m_scene->Draw();

	CFade::Draw();
	if (GetDebugWindow())
	{
		CDebugUI::Draw();
	}


	CRenderer::End();

}

CScene* CManager::GetScene(void)
{
	return m_scene; 
}