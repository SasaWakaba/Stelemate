#pragma once

#include "main.h"
#include "renderer.h"




class CTexture
{

public:

	void Load( const char *FileName );
	void Unload();

	ID3D11ShaderResourceView* GetShaderResourceView(){ return m_ShaderResourceView; }

	void LoadTex(const char *FileName);
	void LoatTextureFromMemory(const unsigned char* file, unsigned int w);

	void SetData(const TCHAR* name, ID3D11Texture2D* tex2D);

private:

	ID3D11Texture2D*			m_Texture = nullptr;
	ID3D11ShaderResourceView*	m_ShaderResourceView;

};