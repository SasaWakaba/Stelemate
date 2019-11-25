#ifndef MANAGER_H_
#define MANAGER_H_

#include "CGame.h"
#include "CResult.h"
#include "CTitle.h"
#include "CFade.h"

class CScene;


class CManager
{
private:
	static CScene* m_scene;
public:
	static void Init();
	static void UnInit();
	static void Update();
	static void Draw();

	static CScene* GetScene(void);


	template <typename T>
	static void SetScene()
	{
		if (m_scene != nullptr)
		{
			m_scene->UnInit();
			delete m_scene;
		}
		T* scene = new T();
		scene->Init();
		m_scene = scene;
	}


	static const char* GetNowScene()
	{
		if (typeid(*m_scene) == typeid(CGame))
		{
			return "Game";
		}
		if (typeid(*m_scene) == typeid(CResult))
		{
			return "Result";
		}
		if (typeid(*m_scene) == typeid(CTitle))
		{
			return "Title";
		}

		return "Null";
	}
};

#endif