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
	//�R���|�W�b�g(����)�̃^�C�v�FSequence or Selector
	CompositeType				m_Type;
	//�ێ����Ă�f�R���[�^�\(����)
	std::vector<CDecorator*>	m_Decorator;
	//�ێ����Ă�^�X�N(����)
	std::vector<CTask*>			m_Task;

public:
	//�R���|�W�b�g(����)�̃^�C�v���w��
	CComposite(CBlackBoard* bb, CompositeType type):CTask(bb),m_Type(type){}
	~CComposite()
	{

		m_Decorator.clear();
		m_Task.clear();
	}

	bool Task()
	{
		//�f�R���[�^�\�����݂��邩�H
		if (m_Decorator.size() != 0)
		{
			for (CDecorator* dec : m_Decorator)
			{
				//�ێ����Ă�f�R���[�^�\��true�Ȃ�ʉ�
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
