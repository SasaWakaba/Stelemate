#include "ModelLoader.h"
#include "../common/renderer.h"
#include "../common/texture.h"

bool CModelLoader::Load(std::string filename)
{
	Assimp::Importer importer;

	

	const aiScene* pScene = importer.ReadFile(filename,
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded);

	if (pScene == NULL)
		return false;


	const std::string modelPath = filename;
	size_t pos = modelPath.find_last_of("\\/");
	std::string basePath = modelPath.substr(0, pos + 1);

	for (unsigned int m = 0; m < pScene->mNumMaterials; m++)
	{
		aiString path;
		if (pScene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			if (!m_TextureIdMap[path.data])
			{
				std::string fileloc = basePath + path.data;
				m_TextureIdMap[path.data] = new CTexture;

				m_TextureIdMap[path.data]->LoadTex(fileloc.c_str());
			}
		}
	}


	processNode(pScene->mRootNode, pScene);

	return true;
}

void CModelLoader::Draw(const XMMATRIX* mtxWorld)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(mtxWorld);
	}
}

Mesh CModelLoader::processMesh(aiMesh * mesh, const aiScene * scene, const XMMATRIX* mtxTrans)
{
	// Data to fill
	vector<VERTEX_3D> vertices;
	vector<UINT> indices;
	vector<CTexture*> textures;
	vector<MATERIAL> vec_material;


	// Walk through each of the mesh's vertices
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		VERTEX_3D vertex;

		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;


		if (mesh->HasNormals()) //法線の有無
		{
			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.TexCoord.y = (float)mesh->mTextureCoords[0][i].y;
		}
		vertex.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		CTexture* tex;
		tex = new CTexture;
		aiString path;
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			textures.push_back(m_TextureIdMap[path.data]);
		}

		aiColor4D diffuse, ambient, specular, emissive;
		MATERIAL l_Material;
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emissive);
		l_Material.Ambient.a = ambient.a;
		l_Material.Ambient.b = ambient.b;
		l_Material.Ambient.g = ambient.g;
		l_Material.Ambient.r = ambient.r;

		l_Material.Diffuse.a = diffuse.a;
		l_Material.Diffuse.b = diffuse.b;
		l_Material.Diffuse.g = diffuse.g;
		l_Material.Diffuse.r = diffuse.r;

		l_Material.Specular.a = specular.a;
		l_Material.Specular.b = specular.b;
		l_Material.Specular.g = specular.g;
		l_Material.Specular.r = specular.r;
		
		l_Material.Emission.a = emissive.a;
		l_Material.Emission.b = emissive.b;
		l_Material.Emission.g = emissive.g;
		l_Material.Emission.r = emissive.r;

		vec_material.push_back(l_Material);
	}

	return Mesh(vertices, indices, textures, vec_material, mtxTrans);
}



void CModelLoader::Close()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Close();
	}
}

void CModelLoader::processNode(aiNode * node, const aiScene * scene)
{
	//行列をDX11用に変換
	aiMatrix4x4 matrix = node->mTransformation;
	XMMATRIX mtxTrans = XMMATRIX(
		matrix.a1, matrix.a2, matrix.a3, matrix.a4,
		matrix.b1, matrix.b2, matrix.b3, matrix.b4,
		matrix.c1, matrix.c2, matrix.c3, matrix.c4,
		matrix.d1, matrix.d2, matrix.d3, matrix.d4
	);
	
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(this->processMesh(mesh, scene, &mtxTrans));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}