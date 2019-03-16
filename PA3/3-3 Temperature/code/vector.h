/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once
#include "release.h"
#include "DataHead.h"
typedef int Rank; //��
#define DEFAULT_CAPACITY  8 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����
template <typename T> class Vector { //����ģ����
protected:
   Rank _size; int _capacity;  T* _elem; //��ģ��������������
   void copyFrom ( T const* A, Rank lo, Rank hi ); //������������A[lo, hi)
   void expand(); //�ռ䲻��ʱ����
   void shrink(); //װ�����ӹ�Сʱѹ��
public:
// ���캯��
   Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
   { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c
   Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //�������帴��
   Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //����
   Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //�������帴��
   Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //����
// ��������
   ~Vector() { delete[] _elem; } //�ͷ��ڲ��ռ�
// ֻ�����ʽӿ�
   Rank size() const { return _size; } //��ģ
   bool empty() const { return !_size; } //�п�
   T& operator[] (Rank r) const { return _elem[r]; } //�����±������������������������ʽ���ø�Ԫ��
   Vector<T> & operator= (Vector<T> const& x);//���ظ�ֵ���������Ա�ֱ�ӿ�¡����
// ��д���ʽӿ�
   T remove ( Rank r ); //ɾ����Ϊr��Ԫ��
   int remove ( Rank lo, Rank hi ); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
   Rank insert ( Rank r, T const& e ); //����Ԫ��
   Rank insert ( T const& e ) { return insert ( _size, e ); } //Ĭ����ΪĩԪ�ز���
// ����
   void print() { for (int i = 0;i < _size;i++) printf("%d ", _elem[i]); printf("\n"); }
   void printy() { for (int i = 0;i < _size;i++) printf("%d ", TP[_elem[i]].y); printf("\n"); }

}; //Vector

template <typename T> //Ԫ������
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //����������A[lo, hi)Ϊ������������
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0; //����ռ䣬��ģ����
	while (lo < hi) //A[lo, hi)�ڵ�Ԫ����һ
		_elem[_size++] = A[lo++]; //������_elem[0, hi - lo)
}

template <typename T> void Vector<T>::expand() { //�����ռ䲻��ʱ����
	if (_size < _capacity) return; //��δ��Աʱ����������
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //��������С����
	T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //�����ӱ�
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i]; //����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='��
							   /*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
	delete[] oldElem; //�ͷ�ԭ�ռ�
}

template <typename T> void Vector<T>::shrink() { //װ�����ӹ�Сʱѹ��������ռ�ռ�
	if (_capacity < DEFAULT_CAPACITY << 1) return; //����������DEFAULT_CAPACITY����
	if (_size << 2 > _capacity) return; //��25%Ϊ��
	T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; //��������
	for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //����ԭ��������
	delete[] oldElem; //�ͷ�ԭ�ռ�
}

template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V) { //����
	if (_elem) delete[] _elem; //�ͷ�ԭ������
	copyFrom(V._elem, 0, V.size()); //���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}

template <typename T> T Vector<T>::remove(Rank r) { //ɾ����������Ϊr��Ԫ�أ�0 <= r < size
	T e = _elem[r]; //���ݱ�ɾ��Ԫ��
	remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
	return e; //���ر�ɾ��Ԫ��
}

template <typename T> int Vector<T>::remove(Rank lo, Rank hi) { //ɾ������[lo, hi)
	if (lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����������remove(0, 0)
	while (hi < _size) _elem[lo++] = _elem[hi++]; //[hi, _size)˳��ǰ��hi - lo����Ԫ
	_size = lo; //���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)����
	shrink(); //���б�Ҫ��������
	return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
}

template <typename T> //��e��Ϊ��ΪrԪ�ز���
Rank Vector<T>::insert(Rank r, T const& e) { //assert: 0 <= r <= size
	expand(); //���б�Ҫ������
	for (int i = _size; i > r; i--) _elem[i] = _elem[i - 1]; //�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
	_elem[r] = e; _size++; //������Ԫ�ز���������
	return r; //������
}
