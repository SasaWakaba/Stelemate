#include "main.h"

#include <vector>
#include <map>
#include <iostream>
#include "renderer.h"

#include "texture.h"
#include "shader.h"

#include "ModelAnimation.h"
#include "TextureManager.h"

void CModelAnimation::Update(int Animation1, int Animation2, float blend, int Frame)
{
	aiAnimation* animation1 = m_Scene[Animation1]->mAnimations[0];
	aiAnimation* animation2 = m_Scene[Animation2]->mAnimations[0];
	for (int c = 0; c < animation1->mNumChannels; c++)
	{

		aiNodeAnim* nodeAnim1 = animation1->mChannels[c];
		aiNodeAnim* nodeAnim2 = animation2->mChannels[c];

		int f = Frame % nodeAnim1->mNumRotationKeys;

		 aiQuaternion::Interpolate(m_NodeRotation[nodeAnim1->mNodeName.C_Str()], nodeAnim1->mRotationKeys[f].mValue, nodeAnim2->mRotationKeys[f].mValue, blend); //球面線形補間 aiQuaternion::Interpolate;

		f = Frame % nodeAnim1->mNumPositionKeys;
		m_NodePosition[nodeAnim1->mNodeName.C_Str()] = (nodeAnim1->mPositionKeys[f].mValue * blend) + (nodeAnim2->mPositionKeys[f].mValue * (1.0f - blend)); //線形補間;
	}
}

void CModelAnimation::Update(int Animation, int Frame)
{
	aiAnimation* animation = m_Scene[Animation]->mAnimations[0];
	for (int c = 0; c < animation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = animation->mChannels[c];
		int f = Frame % nodeAnim->mNumRotationKeys;
		m_NodeRotation[nodeAnim->mNodeName.C_Str()] = nodeAnim->mRotationKeys[f].mValue;

		f = Frame % nodeAnim->mNumPositionKeys;
		m_NodePosition[nodeAnim->mNodeName.C_Str()] = nodeAnim->mPositionKeys[f].mValue;

	}
}

void CModelAnimation::Draw(XMMATRIX world)
{
	DrawMesh(m_Scene[0]->mRootNode, world);
}

void CModelAnimation::DrawMesh(aiNode* node, XMMATRIX matrix)
{
	if (m_bInstance)
	{
		CRenderer::SetCustomShader(m_InstanceVShader, m_InstanceVLayout, m_InstancePShader);
	}

	XMMATRIX world;

	//aiMatrix4x4 mtxTransform = node->mTransformation;
	//aiTransposeMatrix4(&mtxTransform);
	//world *= XMLoadFloat4x4((XMFLOAT4X4*)&mtxTransform);

	aiQuaternion aiQuat = m_NodeRotation[node->mName.C_Str()];
	XMVECTOR quat = XMLoadFloat4(&XMFLOAT4(aiQuat.x, aiQuat.y, aiQuat.z, aiQuat.w));
	world = XMMatrixRotationQuaternion(quat);
	aiVector3D aiVec = m_NodePosition[node->mName.C_Str()];
	XMVECTOR vec = XMLoadFloat3(&XMFLOAT3(aiVec.x, aiVec.y, aiVec.z));
	world *= XMMatrixTranslation(aiVec.x, aiVec.y, aiVec.z);

	world *= matrix;


	
	// マトリクス設定
	CRenderer::SetWorldMatrix(&world);
	for (int n = 0; n < node->mNumMeshes; n++)
	{
		unsigned int m = node->mMeshes[n];
		aiMesh* mesh = m_Scene[0]->mMeshes[m];

		const aiMaterial* material = m_Scene[0]->mMaterials[mesh->mMaterialIndex];
		aiString path;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

		if (m_TextureIdMap[path.data] != nullptr)
		{
			CRenderer::SetTexture(m_TextureIdMap[path.data]);
		}

		CRenderer::SetVertexBuffers(m_mesh[m].vertexBuffer);
		CRenderer::SetIndexBuffer(m_mesh[m].indexBuffer);
		CRenderer::SetMaterial(m_material[0]);
		if (!m_bInstance)
		{
			CRenderer::DrawIndexed(m_mesh[m].IndexNum, 0, 0);
		}
		else
		{
			CRenderer::GetDeviceContext()->UpdateSubresource(MoveBuffer, 0, NULL, &InstanseSpace, 0, 0);
			CRenderer::GetDeviceContext()->VSSetConstantBuffers(5, 1, &MoveBuffer);
			CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			CRenderer::GetDeviceContext()->DrawIndexedInstanced(m_mesh[m].IndexNum, InstanseSpace.Move.z, m, 0, 0);
		}
	}

	for (int n = 0; n < node->mNumChildren; n++)
	{
		DrawMesh(node->mChildren[n], world);
	}


	if (m_bInstance)
	{
		CRenderer::SetDefaultShader();
	}
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);
}

void CModelAnimation::Load(const char* Filename)
{
	m_Scene[0] = aiImportFile(Filename, aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);
	m_SceneNum = 1;
	m_mesh = new MESH[m_Scene[0]->mNumMeshes];
	m_MeshNum = m_Scene[0]->mNumMeshes;

	{
		//std::map<std::string, CTexture*> m_TextureIdMap;
		const std::string modelPath = Filename;
		size_t pos = modelPath.find_last_of("\\/");
		std::string basePath = modelPath.substr(0, pos + 1);

		m_material = new MATERIAL[m_Scene[0]->mNumMaterials];
		//m_Texture = nullptr;
		for (unsigned int m = 0; m < m_Scene[0]->mNumMaterials; m++)
		{
			aiString path;
			if (m_Scene[0]->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				if (path.data[0] == '*')
				{
					int id = atoi(&path.data[1]);
					CTexture* tex;
					tex = new CTexture();
					tex->LoatTextureFromMemory((const unsigned char*)m_Scene[0]->mTextures[id]->pcData, m_Scene[0]->mTextures[id]->mWidth);
					m_TextureIdMap[path.data] = tex;
					//m_TextureIdMap[path.data]->LoatTextureFromMemory((const unsigned char*)m_Scene->mTextures[id]->pcData, m_Scene->mTextures[id]->mWidth);
					//m_Texture = m_TextureIdMap[path.data];
					//delete tex;
				}
				else
				{
					std::string fileloc = basePath + path.data;
					CTexture* tex;
					tex = CTextureManager::LoadTexture(fileloc.c_str());
					m_TextureIdMap[path.data] = tex;
					//m_TextureIdMap[path.data]->LoadTex(fileloc.c_str());
					//m_Texture = m_TextureIdMap[path.data];
					//delete tex;
				}
			}
			else
			{
				m_TextureIdMap[path.data] = 0;
			}

			aiColor4D diffuse, ambient, specular, emissive;
			aiGetMaterialColor(m_Scene[0]->mMaterials[m], AI_MATKEY_COLOR_DIFFUSE, &diffuse);
			aiGetMaterialColor(m_Scene[0]->mMaterials[m], AI_MATKEY_COLOR_AMBIENT, &ambient);
			aiGetMaterialColor(m_Scene[0]->mMaterials[m], AI_MATKEY_COLOR_SPECULAR, &specular);
			aiGetMaterialColor(m_Scene[0]->mMaterials[m], AI_MATKEY_COLOR_EMISSIVE, &emissive);

			m_material[m].Diffuse = COLOR(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
			m_material[m].Ambient = COLOR(ambient.r, ambient.g, ambient.b, ambient.a);
			m_material[m].Specular = COLOR(specular.r, specular.g, specular.b, specular.a);
			m_material[m].Emission = COLOR(emissive.r, emissive.g, emissive.b, emissive.a);

		}
	}

	for (int m = 0; m < m_MeshNum; m++)
	{
		aiMesh* mesh = m_Scene[0]->mMeshes[m];
		VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];

		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			vertex[i].Position = XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			vertex[i].Normal = XMFLOAT3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			vertex[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			if (mesh->mTextureCoords[0])
			{
				vertex[i].TexCoord = XMFLOAT2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			}
		}

		// 頂点バッファ生成
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(VERTEX_3D) * mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;

			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_mesh[m].vertexBuffer);
		}
		delete[] vertex;


		unsigned short* index;
		index = new unsigned short[mesh->mNumFaces * 3];
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			index[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
			index[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			index[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}
		m_mesh[m].IndexNum = mesh->mNumFaces * 3;



		// インデックスバッファ生成
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned short) * m_mesh[m].IndexNum;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = &index[0];

			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_mesh[m].indexBuffer);
		}

		delete index;
	}

	if (m_bInstance)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		CShader::LoadVertexShader("Instance_VS.cso", &m_InstanceVShader, &m_InstanceVLayout, layout, ARRAYSIZE(layout));
		CShader::LoadPixelShader("pixelShader.cso", &m_InstancePShader);

		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = sizeof(float);
		hBufferDesc.ByteWidth = sizeof(Instaced);
		CRenderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, &MoveBuffer);
		CRenderer::GetDeviceContext()->UpdateSubresource(MoveBuffer, 0, NULL, &InstanseSpace, 0, 0);
		CRenderer::GetDeviceContext()->VSSetConstantBuffers(5, 1, &MoveBuffer);
	}
}

void CModelAnimation::UnLoad()
{
	for (int i = 0; i < m_MeshNum; i++)
	{
		m_mesh[i].indexBuffer->Release();
		m_mesh[i].vertexBuffer->Release();
	}
	delete[] m_mesh;
	delete m_material;
	for (int i = 0; i < m_SceneNum; i++)
	{
		aiReleaseImport(m_Scene[i]);
	}
	m_TextureIdMap.clear();
}