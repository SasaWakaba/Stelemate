#ifndef CJOB_H_
#define CJOB_H_

#include "../common/main.h"
#include "CCharcterBase.h"
#include "../common/model.h"
#include "../common/ModelAnimation.h"
#include "CCharacterData.h"

class CSwordsman :public CCharcterBase
{
private:
	XMFLOAT3 m_LocationOld;
	CModelAnimation* m_Model[2];
public:
	CSwordsman():CCharcterBase(Swordman){}
	~CSwordsman(){}
	void Initialize()
	{
		m_Model[0] = new CModelAnimation();
		m_Model[0]->Load("asset/model/Rook_A/Rook.obj");
		m_Model[1] = new CModelAnimation();
		m_Model[1]->Load("asset/model/Rook_B/RookB.obj");

		m_Status = CCharacterData::m_CharData["Swordsman"];
	}
	void Finalize() 
	{
		m_Model[0]->UnLoad();
		delete m_Model[0];
		m_Model[1]->UnLoad();
		delete m_Model[1];
	}

	void Draw() 
	{
		XMMATRIX world;
		world = XMMatrixScaling(0.25f, 0.25f, 0.25f);
		world *= XMMatrixRotationRollPitchYaw((PI/180) * 90.0f, 0.0f, 0.0f);
		world *= XMMatrixTranslation(m_Location.x, m_Location.y, m_Location.z);
		if (bAlly)
		{
			m_Model[0]->Draw(world);
		}
		else
		{
			m_Model[1]->Draw(world);
		}
	}

};


#endif // !CJOB_H_
