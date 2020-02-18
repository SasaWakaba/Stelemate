



#include "Scene.h"

#include "../Audio/audio_clip.h"

#include "../DebugUi/DebugUI.h"
#include "inputController.h"
#include "manager.h"

#include "CTitle.h"
#include "CGame.h"
#include "CResult.h"

#include "CFade.h"
#include "TextureManager.h"


CScene* CManager::m_scene = nullptr;

void CManager::Init()
{

	CRenderer::Init();
	CInput::Init();
	CInputController::Init();
	CAudioClip::Init();
	CTextureManager::Initialize();
	CFade::Initialize();

	SetScene<CTitle>();



}

void CManager::UnInit()
{

	CFade::Finalize();
	CTextureManager::Finalize();

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
	CInputController::Update();
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