#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "main.h"

class CGameObject
{
protected:
	XMFLOAT3					m_Position;
	XMFLOAT3					m_Rotation;
	XMFLOAT3					m_Scale;

	bool						m_Destroy = false;
public:
	CGameObject(){}
	virtual ~CGameObject(){}
	
	virtual void Initialize(){}
	virtual void Finalize(){}
	virtual void Update(){}
	virtual void Draw(){}

	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			Finalize();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	XMFLOAT3 GetPosition() { return m_Position; }

};

#endif // !GAME_OBJECT_H_
