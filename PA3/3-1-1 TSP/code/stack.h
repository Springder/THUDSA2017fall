#pragma once
#include "list.h" //���б�Ϊ���࣬������ջģ����
#include "release.h"
template <typename T> class Stack : public List<T> { //���б����/ĩ����Ϊջ��/��
public: //size()��empty()�Լ��������Žӿڣ�����ֱ������
	void push(T const& e) { this->insertAsLast(e); } //��ջ����Ч�ڽ���Ԫ����Ϊ�б����Ԫ�ز���
	T pop() { return this->remove(this->last()); } //��ջ����Ч��ɾ���б����Ԫ��
	T& top() { return this->last()->data; } //ȡ����ֱ�ӷ����б����Ԫ��
	void print();
};
template<typename T>
inline void Stack<T>::print()
{
	ListNodePosi(T) cursor = this->last();
	for (int i = 0; i < this->getsize(); i++)
	{
		printf("%d ", cursor->data);
		cursor = cursor->pred;
	}
	printf("\n");
}

