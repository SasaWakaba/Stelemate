#include "main.h"
#include "renderer.h"
#include <map>
#include <string>
#include "texture.h"
#include "TextureManager.h"

std::map<std::string, CTexture*> CTextureManager::m_Textures;

void CTextureManager::Initialize()
{
	m_Textures.clear();
}

void CTextureManager::Finalize()
{
	for (auto tex : m_Textures)
	{
		tex.second->Unload();
		delete tex.second;
	}
	m_Textures.clear();
}

CTexture* CTextureManager::LoadTexture(const char* filename)
{
	if (m_Textures[filename] == nullptr)
	{
		m_Textures[filename] = new CTexture();
		m_Textures[filename]->LoadTex(filename);
		return m_Textures[filename];
	}
	else
	{
		return m_Textures[filename];
	}

	return nullptr;
}