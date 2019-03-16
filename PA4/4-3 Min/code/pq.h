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
#define  ProperParent(PQ, n, i) /*���ӣ����ࣩ�����еĴ���*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���

template <typename T> struct PQ { //���ȼ�����PQģ����
	virtual void insert(T) = 0; //���ձȽ���ȷ�������ȼ�����������
	virtual T getMax() = 0; //ȡ�����ȼ���ߵĴ���
	virtual T delMax() = 0; //ɾ�����ȼ���ߵĴ���
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
	T getMax(); //��ȡ���ȼ���ߵĴ���
	T delMax(); //ɾ�����ȼ���ߵĴ���
	void swap(T &i, T &j) 
	{
		T temp = i;
		i = j;
		j = temp;
	}
	bool lt(T i, T j) { return i <= j; }
}; //PQ_ComplHeap

template <typename T> void PQ_ComplHeap<T>::insert(T e) { //������������ȫ�������
	Vector<T>::insert(e); //���Ƚ��´�����������ĩβ
	percolateUp(this->_size - 1); //�ٶԸô���ʵʩ���˵���
}

template <typename T> T PQ_ComplHeap<T>::getMax() 
{ 
	return this->_elem[0]; 
} //ȡ���ȼ���ߵĴ���

template <typename T> T PQ_ComplHeap<T>::delMax() { //ɾ���ǿ���ȫ����������ȼ���ߵĴ���
	T maxElem = this->_elem[0]; this->_elem[0] = this->_elem[--this->_size]; //ժ���Ѷ����״���������֮��ĩ����
	percolateDown(this->_size, 0); //���¶Ѷ�ʵʩ����
	return maxElem; //���ش�ǰ���ݵ�������
}

//�������еĵ�i������ʵʩ���˲�����i < this->_size
template <typename T> Rank PQ_ComplHeap<T>::percolateUp(Rank i) {
	while (ParentValid(i)) { //ֻҪi�и��ף���δ�ִ�Ѷ�������
		Rank j = Parent(i); //��i֮������j
		if (lt(this->_elem[i], this->_elem[j])) break; //һ����ǰ���Ӳ������������������
		swap(this->_elem[i], this->_elem[j]); i = j; //���򣬸��ӽ���λ�ã�������������һ��
	} //while
	return i; //�����������յִ��λ��
}

//������ǰn�������еĵ�i��ʵʩ���ˣ�i < n
template <typename T> Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i) {
	Rank j; //i���䣨���������������У���Ϊ����
	while (i != (j = ProperParent(this->_elem, n, i))) //ֻҪi��j����
	{
		swap(this->_elem[i], this->_elem[j]); i = j;
	} //���߻�λ�������������½����i
	return i; //�������˵ִ��λ�ã���i��j��
}

template <typename T> void PQ_ComplHeap<T>::heapify(Rank n) { //Floyd�����㷨��O(n)ʱ��
	for (int i = LastInternal(n); InHeap(n, i); i--) //�Ե׶��ϣ�����
		/*DSA*/ {
		percolateDown(n, i); //���˸��ڲ��ڵ�
		/*DSA*/for (int k = 0; k < n; k++) {
			/*DSA*/  int kk = k; while (i < kk) kk = (kk - 1) / 2;
			///*DSA*/  i == kk ? print(this->_elem[k]) : print("    ");
			/*DSA*/
		}; /*printf("\n");*/
		/*DSA*/
	}
}