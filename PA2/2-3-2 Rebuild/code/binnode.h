#pragma once

#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p) ? (p)->height : -1) //�ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��
/******************************************************************************************
 * BinNode״̬�����ʵ��ж�
 ******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //����ӵ��һ������
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //ͬʱӵ����������
#define IsLeaf(x) ( ! HasChild(x) )

/******************************************************************************************
 * ��BinNode�����ض���ϵ�Ľڵ㼰ָ��
 ******************************************************************************************/
#define sibling(p) /*�ֵ�*/ \
   ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )

#define uncle(x) /*����*/ \
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )

#define FromParentTo(x) /*���Ը��׵�����*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )
   
   
template <typename T> struct BinNode { //�������ڵ�ģ����
// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
   T data; //��ֵ
   BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //���ڵ㼰���Һ���
   int height; //�߶ȣ�ͨ�ã� 
// ���캯��
   BinNode() :
      parent ( NULL ), lc ( NULL ), rc ( NULL ), height ( 0 ) { }
   BinNode ( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
             int h = 0) :
      data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ) { }
// �����ӿ�
   BinNodePosi(T) insertAsLC ( T const& ); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
   BinNodePosi(T) insertAsRC ( T const& ); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
};

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC ( T const& e )
{ return lc = new BinNode ( e, this ); } //��e��Ϊ��ǰ�ڵ�����Ӳ��������

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC ( T const& e )
{ return rc = new BinNode ( e, this ); } //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������

