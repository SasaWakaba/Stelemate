#ifndef CCOMPOSITE_H_
#define CCOMPOSITE_H_

#include <vector>
#include "CDecorator.h"
#include "CTask.h"

typedef enum
{
	Sequence,
	Selector,
}CompositeType;

class CComposite: public CTask
{
protected:
	//コンポジット(分岐)のタイプ：Sequence or Selector
	CompositeType				m_Type;
	//保持してるデコレータ―(条件)
	std::vector<CDecorator*>	m_Decorator;
	//保持してるタスク(処理)
	std::vector<CTask*>			m_Task;

public:
	//コンポジット(分岐)のタイプを指定
	CComposite(CBlackBoard* bb, CompositeType type):CTask(bb),m_Type(type){}
	~CComposite()
	{

		m_Decorator.clear();
		m_Task.clear();
	}

	bool Task()
	{
		//デコレータ―が存在するか？
		if (m_Decorator.size() != 0)
		{
			for (CDecorator* dec : m_Decorator)
			{
				//保持してるデコレータ―がtrueなら通過
				if (dec->Decorator() == false)
				{
					return false;
				}
			}
		}

		if (m_Type == Sequence)
		{
			for (CTask* task : m_Task)
			{
				if (task->Task() == false)
				{
					return false;
				}
			}

			return true;
		}
		else if (m_Type == Selector)
		{
			for (CTask* task : m_Task)
			{
				if (task->Task())
				{
					return true;
				}
			}

			return false;
		}
	}


	void AddDecorator(CDecorator* dec)
	{
		m_Decorator.push_back(dec);
	}

	void AddTask(CTask* task)
	{
		m_Task.push_back(task);
	}

};

#endif // CCOMPOSITE_H_
