/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

typedef int Rank; //��

#define ListNodePosi(T) ListNode<T>* //�б�ڵ�λ��

template <typename T> struct ListNode { //�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
// ��Ա
   T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //��ֵ��ǰ�������
// ���캯��
   ListNode() {} //���header��trailer�Ĺ���
   ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
      : data ( e ), pred ( p ), succ ( s ) {} //Ĭ�Ϲ�����
// �����ӿ�
   ListNodePosi(T) insertAsPred ( T const& e ); //������ǰ�ڵ�֮ǰ�����½ڵ�
   ListNodePosi(T) insertAsSucc ( T const& e ); //���浱ǰ�ڵ�֮������½ڵ�
};

template <typename T> //��e���浱ǰ�ڵ�֮������ڵ�ǰ�ڵ������б������ڱ�β�ڵ�trailer��
ListNodePosi(T) ListNode<T>::insertAsSucc ( T const& e ) {
   ListNodePosi(T) x = new ListNode ( e, this, succ ); //�����½ڵ�
   succ->pred = x; succ = x; //������������
   return x; //�����½ڵ��λ��
}

template <typename T> //��e������ǰ�ڵ�֮ǰ�����ڵ�ǰ�ڵ������б������ڱ�ͷ�ڵ�header��
ListNodePosi(T) ListNode<T>::insertAsPred ( T const& e ) {
   ListNodePosi(T) x = new ListNode ( e, pred, this ); //�����½ڵ�
   pred->succ = x; pred = x; //������������
   return x; //�����½ڵ��λ��
}

template <typename T> class List { //�б�ģ����

private:
   int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //��ģ��ͷ�ڱ���β�ڱ�

protected:
   void init(); //�б���ʱ�ĳ�ʼ��
   int clear(); //������нڵ�
public:
// ���캯��
   List() { init(); } //Ĭ��
// ��������
   ~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
// ֻ�����ʽӿ�
   Rank size() const { return _size; } //��ģ
   bool empty() const { return _size <= 0; } //�п�
   ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
   ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
   bool valid ( ListNodePosi(T) p ) //�ж�λ��p�Ƿ����Ϸ�
   { return p && ( trailer != p ) && ( header != p ); } //��ͷ��β�ڵ��ͬ��NULL

// ��д���ʽӿ�
   ListNodePosi(T) insertAsFirst ( T const& e ); //��e�����׽ڵ����
   ListNodePosi(T) insertAsLast ( T const& e ); //��e����ĩ�ڵ����
   T remove ( ListNodePosi(T) p ); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
   void push(T const& e) { insertAsLast(e); } //��ջ����Ч�ڽ���Ԫ����Ϊ�б����Ԫ�ز���
   T pop() { return remove(last()); } //��ջ����Ч��ɾ���б����Ԫ��
   T& top() { return last()->data; } //ȡ����ֱ�ӷ����б����Ԫ��
}; //List

template <typename T> void List<T>::init() { //�б��ʼ�����ڴ����б����ʱͳһ����
   header = new ListNode<T>; //����ͷ�ڱ��ڵ�
   trailer = new ListNode<T>; //����β�ڱ��ڵ�
   header->succ = trailer; header->pred = NULL;
   trailer->pred = header; trailer->succ = NULL;
   _size = 0; //��¼��ģ
}
template <typename T> int List<T>::clear() { //����б�
   int oldSize = _size;
   while ( 0 < _size ) remove ( header->succ ); //����ɾ���׽ڵ㣬ֱ���б���
   return oldSize;
}
template <typename T> List<T>::~List() //�б�������
{ clear(); delete header; delete trailer; } //����б��ͷ�ͷ��β�ڱ��ڵ�

template <typename T> ListNodePosi(T) List<T>::insertAsFirst ( T const& e )
{  _size++; return header->insertAsSucc ( e );  } //e�����׽ڵ����

template <typename T> ListNodePosi(T) List<T>::insertAsLast ( T const& e )
{  _size++; return trailer->insertAsPred ( e );  } //e����ĩ�ڵ����

template <typename T> T List<T>::remove ( ListNodePosi(T) p ) { //ɾ���Ϸ��ڵ�p����������ֵ
   T e = p->data; //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
   p->pred->succ = p->succ; p->succ->pred = p->pred; //��̡�ǰ��
   delete p; _size--; //�ͷŽڵ㣬���¹�ģ
   return e; //���ر��ݵ���ֵ
}