#ifndef SCENE_H_
#define SCENE_H_


#include <list>
#include "main.h"
#include "renderer.h"
#include "input.h"


#include "Game_Object.h"

#include "../Stage/CStageManager.h"

class CScene
{
protected:
	std::list<CGameObject*> m_GameObject[5];
public:
	CScene(){}
	virtual ~CScene(){}


	virtual void Init() = 0;

	virtual void UnInit()
	{
		for (int i = 0; i < 5; i++)
		{
			for (CGameObject* object : m_GameObject[i])	//m_GameObject‚Ì‚È‚©‚Ìƒ|ƒCƒ“ƒ^‚ð‡”Ô‚Éobject‚É“ü‚ê‚Ä‚­‚ê‚é
			{
				object->Finalize();
				delete object;
			}
			m_GameObject[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < 5; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}
			m_GameObject[i].remove_if([](CGameObject* object) {return object->Destroy(); });
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < 5; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	void DestroyGameObject(CGameObject* gameobject)
	{
		gameobject->SetDestroy();
	}

	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* object = new T();
		object->Initialize();
		m_GameObject[Layer].push_back(object);
		return object;
	}

	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects;
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}
};

#endif // !SCENE_H_
