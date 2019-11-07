#pragma once

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#pragma comment (lib, "assimp.lib")

// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
};

// 描画サブセット構造体
struct SUBSET
{
	unsigned short	StartIndex;
	unsigned short	IndexNum;
	MODEL_MATERIAL	Material;
};

// モデル構造体
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned short	VertexNum;
	unsigned short	*IndexArray;
	unsigned short	IndexNum;
	SUBSET			*SubsetArray;
	unsigned short	SubsetNum;
};



class CModel
{
private:
	XMFLOAT3					m_Position;
	XMFLOAT3					m_Rotation;
	XMFLOAT3					m_Scale;


	ID3D11Buffer*	m_VertexBuffer = NULL;
	ID3D11Buffer*	m_IndexBuffer = NULL;

	DX11_SUBSET*	m_SubsetArray = NULL;
	unsigned short	m_SubsetNum;

	void LoadObj( const char *FileName, MODEL *Model );
	void LoadModel(const aiScene* scene, const aiNode* node, VERTEX_3D* vertex, WORD* index);
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned short *MaterialNum );

public:
	//void Initialize();
	//void Finalize();
	//void Update();
	void Draw(XMMATRIX world);

	void DrawAssimp(XMMATRIX world);

	void Load( const char *FileName );
	void Load();
	void Unload();

};