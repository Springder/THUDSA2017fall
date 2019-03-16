#pragma once

#include "binnode.h" //����������ڵ���
#include "release.h"

using namespace std;
int max(int a, int b)
{
	return a > b ? a : b;
}
template <typename T> class BinTree { //������ģ����
protected:
   int _size; BinNodePosi(T) _root; //��ģ�����ڵ�
public:
   BinTree() : _size ( 0 ), _root ( NULL ) { } //���캯��
   ~BinTree() { /*if ( 0 < _size ) remove ( _root );*/ } //��������
   int size() const { return _size; } //��ģ
   bool empty() const { return !_root; } //�п�
   BinNodePosi(T) getroot() const { return _root; } //����
   BinNodePosi(T) insertAsRoot ( T const& e ); //������ڵ�
   BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e��Ϊx�����ӣ�ԭ�ޣ�����
   BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e��Ϊx���Һ��ӣ�ԭ�ޣ�����

   BinNodePosi(T) insertAsRoot(T const& e, int ln, int rn, bool isEx); //������ڵ㣨����Ϊ��Ҷ�ڵ����ͣ�
   BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e, int ln, int rn, bool isEx); //e��Ϊx�����ӣ�ԭ�ޣ����루����Ϊ��Ҷ�ڵ����ͣ�
   BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e, int ln, int rn, bool isEx); //e��Ϊx���Һ��ӣ�ԭ�ޣ����루����Ϊ��Ҷ�ڵ����ͣ�

   BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S); //T��Ϊx����������
   BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S); //T��Ϊx����������
   int remove(BinNodePosi(T) x); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
   bool operator< ( BinTree<T> const& t ) //�Ƚ������������в��䣩
   { return _root && t._root && lt ( _root, t._root ); }
   bool operator== ( BinTree<T> const& t ) //�е���
   { return _root && t._root && ( _root == t._root ); }
}; //BinTree


template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot ( T const& e )
{ _size = 1; return _root = new BinNode<T> ( e ); } //��e�������ڵ����յĶ�����

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC ( BinNodePosi(T) x, T const& e )
{ 
	_size++; 
	return x->lc = new BinNode<T> (e); } //e����Ϊx������

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC ( BinNodePosi(T) x, T const& e )
{ _size++; return x->rc= new BinNode<T>(e); } //e����Ϊx���Һ���

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e, int ln, int rn, bool isEx) //����
{
	_size = 1;
	return _root = new BinNode<T>(e, ln, rn, isEx);
} //��e�������ڵ����յĶ�����

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e, int ln, int rn, bool isEx)//����
{
	_size++;
	x->lc = new BinNode<T>(e, ln, rn, isEx);
	return x->lc;
} //e����Ϊx������

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e, int ln, int rn, bool isEx)//����
{
	_size++; 
	x->rc = new BinNode<T>(e, ln, rn, isEx);
	return x->rc;
} //e����Ϊx���Һ���



template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
int BinTree<T>::remove(BinNodePosi(T) x) { //assert: xΪ�������еĺϷ�λ��
	//FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	int n = removeAt(x); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}
template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNodePosi(T) x) { //assert: xΪ�������еĺϷ�λ��
	if (!x) return 0; //�ݹ��������
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
	release(x->data); release(x); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
}

template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) { //x->lc == NULL
	if (x->lc = S->_root) x->lc->parent = x; //����
	_size += S->_size;  //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S) { //x->rc == NULL
	if (x->rc = S->_root) x->rc->parent = x; //����
	_size += S->_size; //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

