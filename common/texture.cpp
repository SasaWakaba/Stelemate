
#define STB_IMAGE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

#include "../include/stb_image.h"

#include "main.h"
#include "renderer.h"

#include "texture.h"


void CTexture::Load(const char *FileName)
{


	unsigned char	header[18];
	unsigned char	*image;
	unsigned int	width, height;
	unsigned char	depth;
	unsigned int	bpp;
	unsigned int	size;



	// ヘッダ読み込み
	FILE* file;
	file = fopen(FileName, "rb");
	assert(file);

	fread(header, sizeof(header), 1, file);


	// 画像サイズ取得
	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];
	depth = header[16];

	if (depth == 32)
		bpp = 4;
	else if (depth == 24)
		bpp = 3;
	else
		bpp = 0;

	if (bpp != 4) {
		assert(false);
	}

	size = width * height * bpp;

	// メモリ確保
	image = (unsigned char*)new unsigned char[size];

	// 画像読み込み
	fread(image, size, 1, file);

	// R<->B
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			unsigned char c;
			c = image[(y * width + x) * bpp + 0];
			image[(y * width + x) * bpp + 0] = image[(y * width + x) * bpp + 2];
			image[(y * width + x) * bpp + 2] = c;
		}
	}

	fclose(file);


	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = image;
	initData.SysMemPitch = width * 4;
	initData.SysMemSlicePitch = size;

	auto hr = CRenderer::GetDevice()->CreateTexture2D(&desc, &initData, &m_Texture);
	if (FAILED(hr)) {
		assert(false);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &m_ShaderResourceView);
	if (FAILED(hr))
	{
		assert(false);
	}


	delete image;
}


void CTexture::Unload()
{
	if (m_Texture != nullptr)
	{
		m_Texture->Release();
		m_ShaderResourceView->Release();
	}
}



void CTexture::LoadTex(const char *FileName)
{
	unsigned int texture;
	unsigned char* pixels;
	int width;
	int height;
	int bpp;
	unsigned int	size;

	// ファイルを読み込み、画像データを取り出す
	//   最後の引数でピクセルあたりのバイト数を強制できる
	pixels = stbi_load(FileName, &width, &height, &bpp, 4);

	size = width * height * bpp;

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = pixels;
	initData.SysMemPitch = width * 4;
	initData.SysMemSlicePitch = size;

	auto hr = CRenderer::GetDevice()->CreateTexture2D(&desc, &initData, &m_Texture);
	if (FAILED(hr)) {
		assert(false);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &m_ShaderResourceView);
	if (FAILED(hr))
	{
		assert(false);
	}

	stbi_image_free(pixels);
}

void CTexture::LoatTextureFromMemory(const unsigned char* file, unsigned int w)
{
	unsigned int texture;
	unsigned char* pixels;
	int width;
	int height;
	int bpp;
	unsigned int	size;

	// ファイルを読み込み、画像データを取り出す
	//   最後の引数でピクセルあたりのバイト数を強制できる
	pixels = stbi_load_from_memory(file, w, &width, &height, &bpp, 4);

	size = width * height * bpp;

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = pixels;
	initData.SysMemPitch = width * 4;
	initData.SysMemSlicePitch = size;

	auto hr = CRenderer::GetDevice()->CreateTexture2D(&desc, &initData, &m_Texture);
	if (FAILED(hr)) {
		assert(false);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &m_ShaderResourceView);
	if (FAILED(hr))
	{
		assert(false);
	}

	stbi_image_free(pixels);
}

void CTexture::SetData(const TCHAR* name, ID3D11Texture2D* tex2D)
{
	if (m_ShaderResourceView != nullptr)
	{
		m_ShaderResourceView->Release();
	}
	HRESULT hr;

	//StrCpy(this->name, name);
	m_Texture = tex2D;

	// テクスチャ情報を取得する
	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	// ShaderResourceViewの情報を作成する
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	// ShaderResourceViewを作成する
	hr = CRenderer::GetDevice()->CreateShaderResourceView(tex2D, &srvDesc, &m_ShaderResourceView);

	// シェーダ用にサンプラを作成する
	//D3D11_SAMPLER_DESC samDesc;
	//ZeroMemory(&samDesc, sizeof(samDesc));
	//samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//samDesc.MaxAnisotropy = 1;
	//samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	//samDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//hr = CRenderer::GetDevice()->CreateSamplerState(&samDesc, &samplerState);
}