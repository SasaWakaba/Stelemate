#pragma once
#include "Game_Object.h"
class CParticle : public CGameObject
{
	struct PARTICLE
	{
		float x;
		float y;
		float z;
		float frame;
	};
private:
	//バファーやシェーダー
	ID3D11InputLayout* m_ParticleVLayout	= nullptr;
	ID3D11VertexShader* m_ParticleVShader	= nullptr;
	ID3D11PixelShader* m_ParticlePShader	= nullptr;
	ID3D11GeometryShader* m_ParticleGShader = nullptr;
	ID3D11Buffer* m_PositionBuffer			= nullptr;
	ID3D11Buffer* m_VertexBuffer			= nullptr;
	ID3D11Buffer* m_IndexBuffer				= nullptr;
	ID3D11Buffer* m_CameraPosBuffer			= nullptr;

	ID3D11Buffer* m_WorldBuffer = nullptr;
	ID3D11Buffer* m_ViewBuffer = nullptr;
	ID3D11Buffer* m_ProjectionBuffer = nullptr;

	//頂点データ
	VERTEX_3D* pVertex;
	//インスタンスデータ
	PARTICLE* m_instanceData = nullptr;
	int m_instanceCount;
	int m_maxFrame;
	int* m_startFrame = nullptr;
	XMFLOAT3* m_movement = nullptr;
	XMFLOAT4* m_CameraPos;
	//テクスチャ変数
	CTexture* m_Texture = nullptr;
public:


	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	//インスタンスを作成または、インスタンスの生成数を設定する関数
	void CreateInstance(int count);
	int GetInstanceCount() { return m_instanceCount; }

	//インスタンスは何フレームまで生きるのかの設定する関数
	void SetMaxFrame(int frame) { m_maxFrame = frame; }

	//n番目のインスタンスはいつのフレーム数に現れるかまたは動くのかの設定する関数
	void SetStartFrame(int* frame) {
		m_startFrame = frame;
		for (int i = 0; i < m_instanceCount; i++) {
			m_instanceData[i].frame = (float)m_startFrame[i];
		}
	}
	//n番目のインスタンスはどういう動きをするのかの設定する関数
	void SetMovement(XMFLOAT3* move) { m_movement = move; }
};