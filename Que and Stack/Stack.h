#pragma once
#include "charnode.h"
#include "initializer_list"

class Stack
{
public:
	Stack()
		:m_top_(nullptr)	{}
	
	Stack(std::initializer_list<char> list)
		:m_top_(nullptr)
	{
		for (const auto &element : list)
		{
			Push(element);
		}
	}

void Push(const char ch)
{
		m_top_ = new ADS101::CharNode(ch, m_top_);
	}
void Pop()
	{
		if (m_top_)
		{
			auto *current = m_top_;		
			m_top_ = m_top_->hentNeste();
			delete current;
		}
	}
char Top() const
	{
		return m_top_->hentData();
	}
size_t Size() const
	{
		return m_top_->hentAntall();
	}
bool Empty() const
	{
		return Size() < 1;
	}
private:
	ADS101::CharNode* m_top_;
};