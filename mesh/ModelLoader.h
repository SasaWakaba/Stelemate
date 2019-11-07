#ifndef MPDEL_LOADER_H_
#define MODEL_LOADER_H_


#include "../common/main.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "../common/texture.h"
#include <map>

#pragma comment (lib, "assimp.lib")


class CModelLoader
{
public:
	CModelLoader(){}
	~CModelLoader(){}

	bool Load(std::string filename);
	void Draw(const XMMATRIX* mtxWorld);

	void Close();
private:

	std::vector<Mesh> meshes;
	std::map<std::string, CTexture*> m_TextureIdMap;
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene, const XMMATRIX* mtxTrans);
};



#endif // !MPDEL_LOADER_H_
