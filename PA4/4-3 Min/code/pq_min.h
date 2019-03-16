#pragma once
#include "vector.h"

#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //�ж�PQ[i]�Ƿ�Ϸ�
#define  Parent(i)         ( ( i - 1 ) >> 1 ) //PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define  LastInternal(n)   Parent( n - 1 ) //���һ���ڲ��ڵ㣨��ĩ�ڵ�ĸ��ף�
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]������
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]���Һ���
#define  ParentValid(i)    ( 0 < i ) //�ж�PQ[i]�Ƿ��и���
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //�ж�PQ[i]�Ƿ�����������
#define  Bigger(PQ, i, j)  ( lt( PQ[i], PQ[j] ) ? j : i ) //ȡ���ߣ���ʱǰ�����ȣ�
#define less(PQ, i, j) (gt (PQ[i], PQ[j]) ? j : i) //ȡС��
#define  ProperParent(PQ, n, i) /*���ӣ����ࣩ�����еĴ���*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���

#define ProperParent_min(PQ, n, i) /*���ӣ����ࣩ�����е�С��*/ \
(RChildValid(n, i) ? less(PQ, less(PQ, i, LChild(i)), RChild(i)) : \
(LChildValid(n, i) ? less(PQ, i, LChild(i)) : i \
	) \
	) //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)
template <typename T> struct PQ { //���ȼ�����PQģ����
	virtual void insert(T) = 0; //���ձȽ���ȷ�������ȼ�����������
	virtual T getMin() = 0; //ȡ�����ȼ���С�Ĵ���
	virtual T delMin() = 0; //ɾ�����ȼ���С�Ĵ���
};

template <typename T> class PQ_ComplHeap : public PQ<T>, public Vector<T> { //��ȫ�����
	/*DSA*/friend class UniPrint; //��ʾ���ʹ�ã����򲻱���������
protected:
	Rank percolateDown(Rank n, Rank i); //����
	Rank percolateUp(Rank i); //����
	void heapify(Rank n); //Floyd�����㷨
public:
	PQ_ComplHeap() { } //Ĭ�Ϲ���
	PQ_ComplHeap(T* A, Rank n) { this->copyFrom(A, 0, n); heapify(n); } //��������
	void insert(T); //���ձȽ���ȷ�������ȼ����򣬲������
	T getMin(); //��ȡ���ȼ���С�Ĵ���
	T delMin(); //ɾ�����ȼ���С�Ĵ���
	void swap(T &i, T &j)
	{
		T temp = i;
		i = j;
		j = temp;
	}
	bool lt(T i, T j) { return i <= j; }
	bool gt(T i, T j) { return i >= j; }
	T getMaxRank(); //��ȡ���ֵ��rank���Ӻ������
	T replaceMax(T e, Rank i); //�滻���ֵ��Ȼ������
	T getElem(Rank i);
}; //PQ_ComplHeap

template <typename T> void PQ_ComplHeap<T>::insert(T e) { //������������ȫ�������
	Vector<T>::insert(e); //���Ƚ��´�����������ĩβ
	percolateUp(this->_size - 1); //�ٶԸô���ʵʩ���˵���
}

template <typename T> T PQ_ComplHeap<T>::getMin()
{
	return this->_elem[0];
} //ȡ���ȼ���ߵĴ���

template <typename T> T PQ_ComplHeap<T>::delMin() { //ɾ���ǿ���ȫ����������ȼ���С�Ĵ���
	T minElem = this->_elem[0]; this->_elem[0] = this->_elem[--this->_size]; //ժ���Ѷ����״���������֮��ĩ����
	percolateDown(this->_size, 0); //���¶Ѷ�ʵʩ����
	return minElem; //���ش�ǰ���ݵ���С����
}

//�������еĵ�i������ʵʩ���˲�����i < this->_size
template <typename T> Rank PQ_ComplHeap<T>::percolateUp(Rank i) {
	while (ParentValid(i)) { //ֻҪi�и��ף���δ�ִ�Ѷ�������
		Rank j = Parent(i); //��i֮������j
		if (gt(this->_elem[i], this->_elem[j])) break; //һ����ǰ���Ӳ������������������
		swap(this->_elem[i], this->_elem[j]); i = j; //���򣬸��ӽ���λ�ã�������������һ��
	} //while
	return i; //�����������յִ��λ��
}

//������ǰn�������еĵ�i��ʵʩ���ˣ�i < n
template <typename T> Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i) {
	Rank j; //i���䣨���������������У���Ϊ����
	while (i != (j = ProperParent_min(this->_elem, n, i))) //ֻҪi��j����
	{
		swap(this->_elem[i], this->_elem[j]); i = j;
	} //���߻�λ�������������½����i
	return i; //�������˵ִ��λ�ã���i��j��
}

template <typename T> void PQ_ComplHeap<T>::heapify(Rank n) { //Floyd�����㷨��O(n)ʱ��
	for (int i = LastInternal(n); InHeap(n, i); i--) //�Ե׶��ϣ�����
	{
		percolateDown(n, i); //���˸��ڲ��ڵ�
		for (int k = 0; k < n; k++) 
		{
			int kk = k; while (i < kk) kk = (kk - 1) / 2;
		};
	}
}

template <typename T> T PQ_ComplHeap<T>::getMaxRank()
{
	int maxElem = INT_MIN;
	int maxElemRank = this->_size;
	int cursorRank = this->_size;
	while (! LChildValid(this->_size, cursorRank))//û�к��ӵ�ʱ��
	{
		if (this->_elem[cursorRank] > maxElem)
		{
			maxElem = this->_elem[cursorRank];
			maxElemRank = cursorRank;
		}
		cursorRank--;
	}
	return maxElemRank;
} 

template <typename T> T PQ_ComplHeap<T>::replaceMax(T e, Rank i)
{
	int maxElem = this->_elem[i];
	this->_elem[i] = e;
	percolateUp(i);
	return maxElem;
}

template<typename T>
inline T PQ_ComplHeap<T>::getElem(Rank i) { return this->_elem[i]; }