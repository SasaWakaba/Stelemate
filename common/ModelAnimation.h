#ifndef CMODEL_ANIMATION_H_
#define CMODEL_ANIMATION_H_

#include "main.h"
#include <map>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>


#pragma comment (lib, "assimp.lib")

class CTexture;

struct MESH
{
	ID3D11Buffer*	vertexBuffer;
	ID3D11Buffer*	indexBuffer;
	unsigned int	IndexNum;
};


class CModelAnimation
{
private:
	MESH*			m_mesh;
	unsigned int	m_MeshNum;
	const aiScene*	m_Scene[10];

	int				m_SceneNum = 0;
	//CTexture*		m_Texture;

	MATERIAL*		m_material;

	std::map<std::string, CTexture*> m_TextureIdMap;



	std::map<std::string, aiQuaternion> m_NodeRotation;
	std::map<std::string, aiVector3D> m_NodePosition;

	bool			m_bInstance = false;
	typedef struct
	{
		XMFLOAT4 Move;
	}Instaced;

	Instaced			InstanseSpace;

	ID3D11InputLayout*  m_InstanceVLayout = nullptr;
	ID3D11VertexShader* m_InstanceVShader = nullptr;
	ID3D11PixelShader*  m_InstancePShader = nullptr;
	ID3D11Buffer* MoveBuffer = nullptr;

public:
	void Draw(XMMATRIX world);
	void DrawMesh(aiNode* node, XMMATRIX matrix);
	void InstanceEnable(bool enable, XMFLOAT4 size) { m_bInstance = enable; InstanseSpace.Move = size;}

	void Update(int Animation, int Frame);
	void Update(int Animation1, int Animation2, float blend, int Frame);

	void Load(const char* Filename);

	void LoadAnim(const char* Filename) { 
		m_Scene[m_SceneNum] = aiImportFile(Filename, aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality); 
		m_SceneNum++; 
	}
	void UnLoad();
};

#endif // !CMODEL_ANIMATION_H_
