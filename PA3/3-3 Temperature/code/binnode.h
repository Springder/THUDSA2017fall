#pragma once
#include "vector.h"
#include "DataHead.h"
#define BinNodePosi(T) BinNode<T> *
template <typename T> struct BinNode { //�������ڵ�ģ����
// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
   T data; //��ֵ
   BinNodePosi(T) lc; BinNodePosi(T) rc; //���ڵ㼰���Һ���
   int left, right; //���������
   bool isExternal; //�Ƿ���Ҷ�ڵ�
   Vector<int> Y; //������ܵĴ������¶���Ϣ�������rank
   //Vector<>
// ���캯��
   BinNode() :
       lc ( NULL ), rc ( NULL ){ } //Ĭ�Ϲ��캯��
   BinNode(T e, int l, int r, bool isExternal, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL) :
	   data(e), left(l), right(r), isExternal(isExternal), lc(lc), rc(rc) { } //Ĭ�Ϲ��캯��


// �����ӿ�
   BinNodePosi(T) insertAsLC ( T const& ); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
   BinNodePosi(T) insertAsRC ( T const& ); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�

   BinNodePosi(T) insertAsLC(T const&, int, int, bool); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�(����)
   BinNodePosi(T) insertAsRC(T const&, int, int, bool); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�(����)

   BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
};

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC ( T const& e )
{ return lc = new BinNode ( e, this ); } //��e��Ϊ��ǰ�ڵ�����Ӳ��������

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC ( T const& e )
{ return rc = new BinNode ( e, this ); } //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������


template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e, int ln, int rn, bool isEx) // ����
{
	return lc = new BinNode(e, ln, rn, isEx, this);
} //��e��Ϊ��ǰ�ڵ�����Ӳ��������

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e, int ln, int rn, bool isEx) // ����
{
	return rc = new BinNode(e, ln, rn, isEx, this);
} //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������

template <typename T> BinNodePosi(T) BinNode<T>::succ() { //��λ�ڵ�v��ֱ�Ӻ��
	BinNodePosi(T) s = this; //��¼��̵���ʱ����
	if (rc) { //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
		s = rc; //��������
		while (HasLChild(*s)) s = s->lc; //�����С���Ľڵ�
	}
	else { //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
		while (IsRChild(*s)) s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
		s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
	}
	return s;
}

