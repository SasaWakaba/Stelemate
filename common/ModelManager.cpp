#include "main.h"
#include "renderer.h"
#include <map>
#include <string>
#include "ModelAnimation.h"
#include "ModelManager.h"

std::map<std::string, CModelAnimation*> CModelManager::m_Models;
std::map<std::string, CModelAnimation*> CModelManager::m_ModelAnims;

void CModelManager::Initialize()
{
	m_Models.clear();
}
void CModelManager::Finalize()
{
	for (auto model : m_Models)
	{
		model.second->UnLoad();
		delete model.second;
	}
	m_Models.clear();
}
CModelAnimation* CModelManager::LoadModel(const char* filename)
{
	if (m_Models[filename] == nullptr)
	{
		m_Models[filename] = new CModelAnimation();
		m_Models[filename]->Load(filename);
		return m_Models[filename];
	}
	else
	{
		return m_Models[filename];
	}

	return nullptr;
}

void CModelManager::LoadAnim(CModelAnimation* model, const char* filename)
{
	if (m_ModelAnims[filename] == nullptr)
	{
		model->LoadAnim(filename);
		m_ModelAnims[filename] = model;
	}
}