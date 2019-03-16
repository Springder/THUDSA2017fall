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
   virtual int updateHeight ( BinNodePosi(T) x ); //���½ڵ�x�ĸ߶�
   void updateHeightAbove ( BinNodePosi(T) x ); //���½ڵ�x�������ȵĸ߶�
public:
   BinTree() : _size ( 0 ), _root ( NULL ) { } //���캯��
   ~BinTree() { if ( 0 < _size ) remove ( _root ); } //��������
   int size() const { return _size; } //��ģ
   bool empty() const { return !_root; } //�п�
   BinNodePosi(T) getroot() const { return _root; } //����
   BinNodePosi(T) insertAsRoot ( T const& e ); //������ڵ�
   BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e��Ϊx�����ӣ�ԭ�ޣ�����
   BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e��Ϊx���Һ��ӣ�ԭ�ޣ�����
   int remove(BinNodePosi(T) x); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
   bool operator< ( BinTree<T> const& t ) //�Ƚ������������в��䣩
   { return _root && t._root && lt ( _root, t._root ); }
   bool operator== ( BinTree<T> const& t ) //�е���
   { return _root && t._root && ( _root == t._root ); }
}; //BinTree

template <typename T> int BinTree<T>::updateHeight ( BinNodePosi(T) x ) //���½ڵ�x�߶�
{ return x->height = 1 + max ( stature ( x->lc ), stature ( x->rc ) ); } //���������������

template <typename T> void BinTree<T>::updateHeightAbove ( BinNodePosi(T) x ) //���¸߶�
{ while ( x ) { updateHeight ( x ); x = x->parent; } } //��x�����������������ȡ����Ż�


template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot ( T const& e )
{ _size = 1; return _root = new BinNode<T> ( e ); } //��e�������ڵ����յĶ�����

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC ( BinNodePosi(T) x, T const& e )
{ _size++; x->insertAsLC ( e ); updateHeightAbove ( x ); return x->lc; } //e����Ϊx������

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC ( BinNodePosi(T) x, T const& e )
{ _size++; x->insertAsRC ( e ); updateHeightAbove ( x ); return x->rc; } //e����Ϊx���Һ���


template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
int BinTree<T>::remove(BinNodePosi(T) x) { //assert: xΪ�������еĺϷ�λ��
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //�������ȸ߶�
	int n = removeAt(x); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}
template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNodePosi(T) x) { //assert: xΪ�������еĺϷ�λ��
	if (!x) return 0; //�ݹ��������
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
	release(x->data); release(x); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
}