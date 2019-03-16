#pragma once
#include "list.h" //���б�Ϊ���࣬������ջģ����
template <typename T> class Queue : public List<T> {
public:
	void enqueue(T const & e) { this->insertAsLast(e); }
	T dequeue() { return this->remove(this->first()); }
	T & front() { return this->first()->data; }
	T & behind() { return this->last()->data; }
	//void print();
};
//template<typename T>
//inline void Queue<T>::print()
//{
//	printf("print queue: ");
//	ListNodePosi(T) x = first();
//	for (int i = 0; i < this->size(); i++)
//	{
//		printf("%d", x->data);
//		x = x->succ;
//	}
//	printf("\n");
//}