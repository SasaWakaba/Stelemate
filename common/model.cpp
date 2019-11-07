

#include "main.h"
#include "renderer.h"
#include "Game_Object.h"
#include <vector>
#include <map>




#include "model.h"
#include "texture.h"
#include "input.h"


static int g_NumIndex;
static int g_NumVertex;

std::map<std::string, CTexture*> g_TextureIdMap;

void CModel::Draw(XMMATRIX world)
{
	// マトリクス設定
	CRenderer::SetWorldMatrix(&world);

	// 頂点バッファ設定
	CRenderer::SetVertexBuffers( m_VertexBuffer );

	// インデックスバッファ設定
	CRenderer::SetIndexBuffer( m_IndexBuffer );

	for( unsigned short i = 0; i < m_SubsetNum; i++ )
	{
		// マテリアル設定
		CRenderer::SetMaterial( m_SubsetArray[i].Material.Material );

		// テクスチャ設定
		CRenderer::SetTexture( m_SubsetArray[i].Material.Texture );

		// ポリゴン描画
		CRenderer::DrawIndexed( m_SubsetArray[i].IndexNum, m_SubsetArray[i].StartIndex, 0 );
	}



}




void CModel::Load( const char *FileName )
{



	MODEL model;
	LoadObj( FileName, &model );



	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( VERTEX_3D ) * model.VertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory( &sd, sizeof(sd) );
		sd.pSysMem = model.VertexArray;

		CRenderer::GetDevice()->CreateBuffer( &bd, &sd, &m_VertexBuffer );
	}


	// インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( unsigned short ) * model.IndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory( &sd, sizeof(sd) );
		sd.pSysMem = model.IndexArray;

		CRenderer::GetDevice()->CreateBuffer( &bd, &sd, &m_IndexBuffer );
	}

	// サブセット設定
	{
		m_SubsetArray = new DX11_SUBSET[ model.SubsetNum ];
		m_SubsetNum = model.SubsetNum;

		for( unsigned short i = 0; i < model.SubsetNum; i++ )
		{
			m_SubsetArray[i].StartIndex = model.SubsetArray[i].StartIndex;
			m_SubsetArray[i].IndexNum = model.SubsetArray[i].IndexNum;

			m_SubsetArray[i].Material.Material = model.SubsetArray[i].Material.Material;

			m_SubsetArray[i].Material.Texture = new CTexture();
			m_SubsetArray[i].Material.Texture->Load( model.SubsetArray[i].Material.TextureName );

		}
	}

	delete[] model.VertexArray;
	delete[] model.IndexArray;
	delete[] model.SubsetArray;

}


void CModel::Unload()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();

	for (unsigned int i = 0; i < m_SubsetNum; i++)
	{
		m_SubsetArray[i].Material.Texture->Unload();
		delete m_SubsetArray[i].Material.Texture;
	}

	delete[] m_SubsetArray;

}





//モデル読込////////////////////////////////////////////
void CModel::LoadObj( const char *FileName, MODEL *Model )
{

	XMFLOAT3	*positionArray;
	XMFLOAT3	*normalArray;
	XMFLOAT2	*texcoordArray;

	unsigned short	positionNum = 0;
	unsigned short	normalNum = 0;
	unsigned short	texcoordNum = 0;
	unsigned short	vertexNum = 0;
	unsigned short	indexNum = 0;
	unsigned short	in = 0;
	unsigned short	subsetNum = 0;

	MODEL_MATERIAL	*materialArray = nullptr;
	unsigned short	materialNum = 0;

	char str[256];
	char *s;
	char c;


	FILE *file;
	file = fopen( FileName, "rt" );
	assert(file);



	//要素数カウント
	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "v" ) == 0 )
		{
			positionNum++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			normalNum++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			texcoordNum++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			subsetNum++;
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			in = 0;

			do
			{
				fscanf( file, "%s", str );
				vertexNum++;
				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c!= '\r' );

			//四角は三角に分割
			if( in == 4 )
				in = 6;

			indexNum += in;
		}
	}


	//メモリ確保
	positionArray = new XMFLOAT3[ positionNum ];
	normalArray = new XMFLOAT3[ normalNum ];
	texcoordArray = new XMFLOAT2[ texcoordNum ];


	Model->VertexArray = new VERTEX_3D[ vertexNum ];
	Model->VertexNum = vertexNum;

	Model->IndexArray = new unsigned short[ indexNum ];
	Model->IndexNum = indexNum;

	Model->SubsetArray = new SUBSET[ subsetNum ];
	Model->SubsetNum = subsetNum;




	//要素読込
	XMFLOAT3 *position = positionArray;
	XMFLOAT3 *normal = normalArray;
	XMFLOAT2 *texcoord = texcoordArray;

	unsigned short vc = 0;
	unsigned short ic = 0;
	unsigned short sc = 0;


	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "mtllib" ) == 0 )
		{
			//マテリアルファイル
			fscanf( file, "%s", str );

			char path[256];
			strcpy( path, "asset/" );
			strcat( path, str );

			LoadMaterial( path, &materialArray, &materialNum );
		}
		else if( strcmp( str, "o" ) == 0 )
		{
			//オブジェクト名
			fscanf( file, "%s", str );
		}
		else if( strcmp( str, "v" ) == 0 )
		{
			//頂点座標
			fscanf( file, "%f", &position->x );
			fscanf( file, "%f", &position->y );
			fscanf( file, "%f", &position->z );
			//position->x *= SCALE_MODEL;
			//position->y *= SCALE_MODEL;
			//position->z *= SCALE_MODEL;
			position++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			//法線
			fscanf( file, "%f", &normal->x );
			fscanf( file, "%f", &normal->y );
			fscanf( file, "%f", &normal->z );
			normal++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			//テクスチャ座標
			fscanf( file, "%f", &texcoord->x );
			fscanf( file, "%f", &texcoord->y );
			//texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			//マテリアル
			fscanf( file, "%s", str );

			if( sc != 0 )
				Model->SubsetArray[ sc - 1 ].IndexNum = ic - Model->SubsetArray[ sc - 1 ].StartIndex;

			Model->SubsetArray[ sc ].StartIndex = ic;


			for( unsigned short i = 0; i < materialNum; i++ )
			{
				if( strcmp( str, materialArray[i].Name ) == 0 )
				{
					Model->SubsetArray[ sc ].Material.Material = materialArray[i].Material;
					strcpy( Model->SubsetArray[ sc ].Material.TextureName, materialArray[i].TextureName );
					strcpy( Model->SubsetArray[ sc ].Material.Name, materialArray[i].Name );

					break;
				}
			}

			sc++;
			
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			//面
			in = 0;

			do
			{
				fscanf( file, "%s", str );

				s = strtok( str, "/" );	
				Model->VertexArray[vc].Position = positionArray[ atoi( s ) - 1 ];
				if( s[ strlen( s ) + 1 ] != '/' )
				{
					//テクスチャ座標が存在しない場合もある
					s = strtok( NULL, "/" );
					Model->VertexArray[vc].TexCoord = texcoordArray[ atoi( s ) - 1 ];
				}
				s = strtok( NULL, "/" );	
				Model->VertexArray[vc].Normal = normalArray[ atoi( s ) - 1 ];

				Model->VertexArray[vc].Diffuse = XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );

				Model->IndexArray[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c != '\r' );

			//四角は三角に分割
			if( in == 4 )
			{
				Model->IndexArray[ic] = vc - 4;
				ic++;
				Model->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}


	if( sc != 0 )
		Model->SubsetArray[ sc - 1 ].IndexNum = ic - Model->SubsetArray[ sc - 1 ].StartIndex;


	fclose(file);


	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}




//マテリアル読み込み///////////////////////////////////////////////////////////////////
void CModel::LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned short *MaterialNum )
{
	char str[256];

	FILE *file;
	file = fopen( FileName, "rt" );
	if( file == NULL )
	{
		assert(false);
		return;
	}

	MODEL_MATERIAL *materialArray;
	unsigned short materialNum = 0;

	//要素数カウント
	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;


		if( strcmp( str, "newmtl" ) == 0 )
		{
			materialNum++;
		}
	}


	//メモリ確保
	materialArray = new MODEL_MATERIAL[ materialNum ];


	//要素読込
	int mc = -1;

	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;


		if( strcmp( str, "newmtl" ) == 0 )
		{
			//マテリアル名
			mc++;
			fscanf( file, "%s", materialArray[ mc ].Name );
			strcpy( materialArray[ mc ].TextureName, "" );
		}
		else if( strcmp( str, "Ka" ) == 0 )
		{
			//アンビエント
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.b );
			materialArray[ mc ].Material.Ambient.a = 1.0f;
		}
		else if( strcmp( str, "Kd" ) == 0 )
		{
			//ディフューズ
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.b );
			materialArray[ mc ].Material.Diffuse.a = 1.0f;
		}
		else if( strcmp( str, "Ks" ) == 0 )
		{
			//スペキュラ
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.b );
			materialArray[ mc ].Material.Specular.a = 1.0f;
		}
		else if( strcmp( str, "Ns" ) == 0 )
		{
			//スペキュラ強度
			fscanf( file, "%f", &materialArray[ mc ].Material.Shininess );
		}
		else if( strcmp( str, "d" ) == 0 )
		{
			//アルファ
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.a );
		}
		else if( strcmp( str, "map_Kd" ) == 0 )
		{
			//テクスチャ
			fscanf( file, "%s", str );

			char path[256];
			strcpy( path, "asset/" );
			strcat( path, str );

			strcat( materialArray[ mc ].TextureName, path );
		}
	}

	fclose(file);
	*MaterialArray = materialArray;
	*MaterialNum = materialNum;
}



void CModel::Load()
{

	g_NumIndex = 0;
	g_NumVertex = 0;
	const aiScene* m_Scene;

	const std::string modelPath = "asset/dog.x";
	m_Scene = aiImportFile(modelPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality || aiProcess_MakeLeftHanded || aiProcess_FlipUVs);


	for (int i = 0; i < m_Scene->mNumMeshes; i++)
	{
		g_NumVertex += m_Scene->mMeshes[i]->mNumVertices;
		for (int j = 0; j < m_Scene->mMeshes[i]->mNumFaces; j++)
		{
			g_NumIndex += m_Scene->mMeshes[i]->mFaces[j].mNumIndices;
		}
	}
	
	//=======================================================
	//頂点バッファ生成
	//=======================================================
	VERTEX_3D* vertex;
	vertex = new VERTEX_3D[g_NumVertex];

	//=====================================================
	//インデックスバッファ
	//=====================================================
	WORD* Index;
	Index = new WORD[g_NumIndex];

	g_NumIndex = 0;
	g_NumVertex = 0;


	LoadModel(m_Scene, m_Scene->mRootNode, vertex, Index);


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * g_NumVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	delete[] vertex;



	D3D11_BUFFER_DESC ib;
	ib.ByteWidth = sizeof(WORD) * g_NumIndex;
	ib.Usage = D3D11_USAGE_DEFAULT;
	ib.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ib.CPUAccessFlags = 0;
	ib.MiscFlags = 0;
	ib.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA ir;
	ir.pSysMem = Index;
	ir.SysMemPitch = 0;
	ir.SysMemSlicePitch = 0;

	CRenderer::GetDevice()->CreateBuffer(&ib, &ir, &m_IndexBuffer);

	delete[] Index;
	
	
}

void CModel::LoadModel(const aiScene* scene, const aiNode* node, VERTEX_3D* vertex, WORD* index)
{

	for (int n = 0; n < node->mNumMeshes; n++)
	{
		const aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];
		const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiColor4D diffuse;
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);

		aiString path;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

		for (int l = 0; l < mesh->mNumVertices; l++)
		{
			vertex[g_NumVertex].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[g_NumVertex].Normal = XMFLOAT3(mesh->mNormals[l].x, mesh->mNormals[l].y, mesh->mNormals[l].z);
			vertex[g_NumVertex].TexCoord = XMFLOAT2(mesh->mTextureCoords[0][l].x, mesh->mTextureCoords[0][l].y);
			vertex[g_NumVertex].Position = XMFLOAT3(mesh->mVertices[l].x, mesh->mVertices[l].y, mesh->mVertices[l].z);
			g_NumVertex++;
		}
		for (int t = 0; t < mesh->mNumFaces; t++)
		{
			const aiFace* face = &mesh->mFaces[t];
			for (int i = 0; i < face->mNumIndices; i++)
			{
				index[g_NumIndex] = face->mIndices[i];
				g_NumIndex++;
			}
		}

		//for (int t = 0; t < mesh->mNumFaces; t++)
		//{
		//	const aiFace* face = &mesh->mFaces[t];
		//	for (int i = 0; i < face->mNumIndices; i++)
		//	{
		//		int index = face->mIndices[i];
		//		vertex[g_NumIndex].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		//		if (mesh->mNormals != nullptr)
		//		{
		//			vertex[g_NumIndex].Normal = XMFLOAT3(mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z);
		//		}
		//
		//		if (mesh->HasTextureCoords(0))
		//		{
		//			vertex[g_NumIndex].TexCoord = XMFLOAT2(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y);
		//		}
		//		vertex[g_NumIndex].Position = XMFLOAT3(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);
		//		g_NumIndex++;
		//	}
		//}
		//g_NumVertex += mesh->mNumVertices;
	}
	for (int n = 0; n < node->mNumChildren; n++)
	{
		LoadModel(scene, node->mChildren[n], vertex, index);
	}
	


}

void CModel::DrawAssimp(XMMATRIX world)
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //頂点バッファ設定
	CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	CRenderer::SetWorldMatrix(&world);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定
	CRenderer::GetDeviceContext()->DrawIndexed(g_NumIndex + 2, 0, 0);	//ポリゴン描画
}




//void countModel(const aiScene* Scene,
//	const aiNode* node,
//	unsigned short	positionNum,
//	unsigned short	normalNum,
//	unsigned short	texcoordNum,
//	unsigned short	vertexNum,
//	unsigned short	indexNum,
//	unsigned short	in,
//	unsigned short	subsetNum)
//{
//	//要素数カウント
//	for (int n = 0; n < node->mNumMeshes; n++)
//	{
//		const aiMesh* mesh = Scene->mMeshes[node->mMeshes[n]];
//		for (int t = 0; t < mesh->mNumFaces; t++)
//		{
//			in = 0;
//			const aiFace* face = &mesh->mFaces[t];
//			for (int i = 0; i < face->mNumIndices; i++)
//			{
//				int index = face->mIndices[i];
//				if (mesh->mNormals != nullptr)
//				{
//					normalNum++;
//				}
//				if (mesh->HasTextureCoords(0))
//				{
//					texcoordNum++;
//				}
//				vertexNum++;
//				positionNum++;
//				in++;
//			}
//			//四角は三角に分割
//			if (in == 4)
//				in = 6;
//			indexNum += in;
//		}
//	}
//	for (int n = 0; n < node->mNumChildren; n++)
//	{
//		subsetNum++;
//		countModel(Scene, node->mChildren[n], positionNum, normalNum, texcoordNum, vertexNum, indexNum, in, subsetNum);
//	}
//}
//
////マテリアル読み込み///////////////////////////////////////////////////////////////////
//void LoadMaterial(const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned short *MaterialNum)
//{
//	char str[256];
//
//	FILE *file;
//	file = fopen(FileName, "rt");
//	if (file == NULL)
//	{
//		assert(false);
//		return;
//	}
//
//	MODEL_MATERIAL *materialArray;
//	unsigned short materialNum = 0;
//
//	//要素数カウント
//	while (true)
//	{
//		fscanf(file, "%s", str);
//
//		if (feof(file) != 0)
//			break;
//
//
//		if (strcmp(str, "newmtl") == 0)
//		{
//			materialNum++;
//		}
//	}
//
//
//	//メモリ確保
//	materialArray = new MODEL_MATERIAL[materialNum];
//
//
//	//要素読込
//	int mc = -1;
//
//	fseek(file, 0, SEEK_SET);
//
//	while (true)
//	{
//		fscanf(file, "%s", str);
//
//		if (feof(file) != 0)
//			break;
//
//
//		if (strcmp(str, "newmtl") == 0)
//		{
//			//マテリアル名
//			mc++;
//			fscanf(file, "%s", materialArray[mc].Name);
//			strcpy(materialArray[mc].TextureName, "");
//		}
//		else if (strcmp(str, "Ka") == 0)
//		{
//			//アンビエント
//			fscanf(file, "%f", &materialArray[mc].Material.Ambient.r);
//			fscanf(file, "%f", &materialArray[mc].Material.Ambient.g);
//			fscanf(file, "%f", &materialArray[mc].Material.Ambient.b);
//			materialArray[mc].Material.Ambient.a = 1.0f;
//		}
//		else if (strcmp(str, "Kd") == 0)
//		{
//			//ディフューズ
//			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.r);
//			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.g);
//			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.b);
//			materialArray[mc].Material.Diffuse.a = 1.0f;
//		}
//		else if (strcmp(str, "Ks") == 0)
//		{
//			//スペキュラ
//			fscanf(file, "%f", &materialArray[mc].Material.Specular.r);
//			fscanf(file, "%f", &materialArray[mc].Material.Specular.g);
//			fscanf(file, "%f", &materialArray[mc].Material.Specular.b);
//			materialArray[mc].Material.Specular.a = 1.0f;
//		}
//		else if (strcmp(str, "Ns") == 0)
//		{
//			//スペキュラ強度
//			fscanf(file, "%f", &materialArray[mc].Material.Shininess);
//		}
//		else if (strcmp(str, "d") == 0)
//		{
//			//アルファ
//			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.a);
//		}
//		else if (strcmp(str, "map_Kd") == 0)
//		{
//			//テクスチャ
//			fscanf(file, "%s", str);
//
//			char path[256];
//			strcpy(path, "asset/");
//			strcat(path, str);
//
//			strcat(materialArray[mc].TextureName, path);
//		}
//	}
//
//	fclose(file);
//	*MaterialArray = materialArray;
//	*MaterialNum = materialNum;
//}
//
//void Load(const char *FileName, MODEL *Model)
//{
//	XMFLOAT3	*positionArray;
//	XMFLOAT3	*normalArray;
//	XMFLOAT2	*texcoordArray;
//
//	unsigned short	positionNum = 0;
//	unsigned short	normalNum = 0;
//	unsigned short	texcoordNum = 0;
//	unsigned short	vertexNum = 0;
//	unsigned short	indexNum = 0;
//	unsigned short	in = 0;
//	unsigned short	subsetNum = 0;
//
//	MODEL_MATERIAL	*materialArray = nullptr;
//	unsigned short	materialNum = 0;
//
//	char str[256];
//	char *s;
//	char c;
//
//
//	const aiScene* m_Scene;
//	const std::string modelPath = "asset/dog.x";
//	m_Scene = aiImportFile(modelPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality || aiProcess_MakeLeftHanded || aiProcess_FlipUVs);
//
//	size_t pos = modelPath.find_last_of("\\/");
//	std::string basePath = modelPath.substr(0, pos + 1);
//	const aiNode* node = m_Scene->mRootNode;
//
//	for (unsigned int m = 0; m < m_Scene->mNumMaterials; m++)
//	{
//		aiString path;
//		if (m_Scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
//		{
//			std::string fileloc = basePath + path.data;
//			g_TextureIdMap[path.data]->LoadTex(fileloc.c_str());
//		}
//		else
//		{
//			g_TextureIdMap[path.data] = 0;
//		}
//	}
//
//	countModel(m_Scene, m_Scene->mRootNode, positionNum, normalNum, texcoordNum, vertexNum, indexNum, in, subsetNum);
//
//	//メモリ確保
//	positionArray = new XMFLOAT3[positionNum];
//	normalArray = new XMFLOAT3[normalNum];
//	texcoordArray = new XMFLOAT2[texcoordNum];
//
//
//	Model->VertexArray = new VERTEX_3D[vertexNum];
//	Model->VertexNum = vertexNum;
//
//	Model->IndexArray = new unsigned short[indexNum];
//	Model->IndexNum = indexNum;
//
//	Model->SubsetArray = new SUBSET[subsetNum];
//	Model->SubsetNum = subsetNum;
//
//	//要素読込
//	XMFLOAT3 *position = positionArray;
//	XMFLOAT3 *normal = normalArray;
//	XMFLOAT2 *texcoord = texcoordArray;
//
//	unsigned short vc = 0;
//	unsigned short ic = 0;
//	unsigned short sc = 0;
//
//	for (int n = 0; n < node->mNumMeshes; n++)
//	{
//		const aiMesh* mesh = m_Scene->mMeshes[node->mMeshes[n]];
//		for (int t = 0; t < mesh->mNumFaces; t++)
//		{
//			in = 0;
//			const aiFace* face = &mesh->mFaces[t];
//			const aiMaterial* material = m_Scene->mMaterials[mesh->mMaterialIndex];
//			aiColor4D diffuse;
//			aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
//			for (int i = 0; i < face->mNumIndices; i++)
//			{
//				int index = face->mIndices[i];
//				if (mesh->mNormals != nullptr)
//				{
//					//法線
//					normal->x = mesh->mNormals[index].x;
//					normal->y = mesh->mNormals[index].y;
//					normal->z = mesh->mNormals[index].z;
//					normal++;
//				}
//				if (mesh->HasTextureCoords(0))
//				{
//					//テクスチャ座標
//					texcoord->x = mesh->mTextureCoords[0][index].x;
//					texcoord->y = mesh->mTextureCoords[0][index].y;
//					//texcoord->y = 1.0f - texcoord->y;
//					texcoord++;
//				}
//				vertexNum++;
//				{
//					//頂点座標
//					position->x = mesh->mVertices[index].x;
//					position->y = mesh->mVertices[index].y;
//					position->z = mesh->mVertices[index].z;
//					//position->x *= SCALE_MODEL;
//					//position->y *= SCALE_MODEL;
//					//position->z *= SCALE_MODEL;
//					position++;
//				}
//				in++;
//			}
//			//四角は三角に分割
//			if (in == 4)
//				in = 6;
//			indexNum += in;
//		}
//	}
//
//	while (true)
//	{
//		fscanf(file, "%s", str);
//
//		if (feof(file) != 0)
//			break;
//
//		if (strcmp(str, "mtllib") == 0)
//		{
//			//マテリアルファイル
//			fscanf(file, "%s", str);
//
//			char path[256];
//			strcpy(path, "asset/");
//			strcat(path, str);
//
//			LoadMaterial(path, &materialArray, &materialNum);
//		}
//		else if (strcmp(str, "o") == 0)
//		{
//			//オブジェクト名
//			fscanf(file, "%s", str);
//		}
//		else if (strcmp(str, "usemtl") == 0)
//		{
//			//マテリアル
//			fscanf(file, "%s", str);
//
//			if (sc != 0)
//				Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;
//
//			Model->SubsetArray[sc].StartIndex = ic;
//
//
//			for (unsigned short i = 0; i < materialNum; i++)
//			{
//				if (strcmp(str, materialArray[i].Name) == 0)
//				{
//					Model->SubsetArray[sc].Material.Material = materialArray[i].Material;
//					strcpy(Model->SubsetArray[sc].Material.TextureName, materialArray[i].TextureName);
//					strcpy(Model->SubsetArray[sc].Material.Name, materialArray[i].Name);
//
//					break;
//				}
//			}
//
//			sc++;
//
//		}
//		else if (strcmp(str, "f") == 0)
//		{
//			//面
//			in = 0;
//
//			do
//			{
//				fscanf(file, "%s", str);
//
//				s = strtok(str, "/");
//				Model->VertexArray[vc].Position = positionArray[atoi(s) - 1];
//				if (s[strlen(s) + 1] != '/')
//				{
//					//テクスチャ座標が存在しない場合もある
//					s = strtok(NULL, "/");
//					Model->VertexArray[vc].TexCoord = texcoordArray[atoi(s) - 1];
//				}
//				s = strtok(NULL, "/");
//				Model->VertexArray[vc].Normal = normalArray[atoi(s) - 1];
//
//				Model->VertexArray[vc].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//
//				Model->IndexArray[ic] = vc;
//				ic++;
//				vc++;
//
//				in++;
//				c = fgetc(file);
//			} while (c != '\n' && c != '\r');
//
//			//四角は三角に分割
//			if (in == 4)
//			{
//				Model->IndexArray[ic] = vc - 4;
//				ic++;
//				Model->IndexArray[ic] = vc - 2;
//				ic++;
//			}
//		}
//	}
//}



