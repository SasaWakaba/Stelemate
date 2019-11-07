#ifndef MESH_H_
#define MESH_H_

#include "../common/main.h"
#include "../common/texture.h"
#include "../common/renderer.h"


#include <fstream>
#include <sstream>
using namespace std;


struct VERTEX {
	FLOAT X, Y, Z;
	XMFLOAT2 texcoord;
};

struct Texture {
	std::string type;
	std::string path;
	ID3D11ShaderResourceView *texture;
};

class Mesh 
{
public:
	vector<VERTEX_3D> vertices;
	vector<UINT> indices;
	vector<CTexture*> textures;
	vector<MATERIAL> materials;
	const XMMATRIX* m_Trans;
	

	Mesh(vector<VERTEX_3D> vertices, vector<UINT> indices, vector<CTexture*> textures, vector<MATERIAL> materials, const XMMATRIX* mtxTrans)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		this->materials = materials;
		this->m_Trans = mtxTrans;
		this->setupMesh();
	}

	void Draw(const XMMATRIX* mtxWorld)
	{
		//**************************
		// マトリクス設定
		//**************************
		XMMATRIX World;
		World =  *m_Trans * *mtxWorld;
		World = *mtxWorld;
		CRenderer::SetWorldMatrix(&World);


		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		

		CRenderer::SetTexture(textures[0]);

		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

		CRenderer::GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		CRenderer::SetMaterial(materials[0]);

		CRenderer::DrawIndexed(indices.size(), 0, 0);
	}

	void Close()
	{
		VertexBuffer->Release();
		IndexBuffer->Release();
	}
private:
	/*  Render data  */
	ID3D11Buffer *VertexBuffer, *IndexBuffer;

	/*  Functions    */
	// Initializes all the buffer objects/arrays
	bool setupMesh()
	{
		HRESULT hr;

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(VERTEX_3D) * vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &vertices[0];

		hr = CRenderer::GetDevice()->CreateBuffer(&vbd, &initData, &VertexBuffer);
		if (FAILED(hr))
			return false;

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * indices.size();
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;

		initData.pSysMem = &indices[0];

		hr = CRenderer::GetDevice()->CreateBuffer(&ibd, &initData, &IndexBuffer);
		if (FAILED(hr))
			return false;

		return true;
	}
};

#endif // !MESH_H_
