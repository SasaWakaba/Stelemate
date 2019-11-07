
#ifndef MESH_FIELD_H_
#define MESH_FIELD_H_



class CMeshField :public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	CTexture* m_Texture = NULL;

	VERTEX_3D* vertex;
	unsigned short* Index;

	float m_GridSizeX;
	float m_GridSizeZ;
	float m_GridX;
	float m_GridZ;

public:
	void Initialize(float gridSizeX, float gridSizeZ, float gridX, float gridZ);
	void Initialize(float gridSizeX, float gridSizeZ, float gridX, float gridZ, float y[11][11]);
	void Finalize();
	void Update();
	void Draw();


	float GetHeight(XMFLOAT3 position);
};

#endif