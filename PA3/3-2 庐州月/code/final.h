#pragma once
#include <iostream>
#define INT_MAX 2147483647
#define INT_MIN (-2147483647 - 1)
using namespace std;
#define BinNodePosi(T) BinNode<T>*
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define stature(p) ((p) ? (p)->height : -1) //�ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��
#define HeightUpdated(x) /*�߶ȸ��³�������*/ ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define EQUAL(e, v)  (!(v) || (e) == (v)->data) //�ڵ�v��������ͨ���ڱ����Ĺؼ������e
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //����ƽ������
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //ƽ������
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVLƽ������
#define FromParentTo(x) /*���Ը��׵�����*/ \
	( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*���*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*�Ҹ�*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*�ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������*/ \
   ) \
   ) \
)

inline int max(int a, int b) {
	return (a > b) ? a : b;
}

template<class T>
class BinNode {
public:
	T data;
	int height;
	int num;
	BinNodePosi(T) parent, *lc, *rc;
	BinNode() :data(NULL), height(0), num(0), parent(NULL), lc(NULL), rc(NULL) {}
	BinNode(T e, BinNodePosi(T) parent = NULL) : data(e), height(0), num(0), parent(parent), lc(NULL), rc(NULL) {}

	//int size() {
	//	int s = 1; //���뱾��
	//	if (lc) s += lc->size(); //�ݹ������������ģ
	//	if (rc) s += rc->size(); //�ݹ������������ģ
	//	return s;
	//}

	BinNodePosi(T) succ()  //ȡ��ǰ�ڵ��ֱ�Ӻ��
	{
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
};

template<class T>
inline int getHeight(BinNodePosi(T) bn) { return (bn == NULL) ? -1 : bn->height; }

template<class T>
class AVL {
public:
	BinNodePosi(T) _root, *_hot;
	int _size;

	AVL() :_root(NULL), _hot(NULL), _size(0) {}
	//~AVL(): { if (0 < _size) remove(_root); }
	//����vΪ���ģ�AVL��SPLAY��rbTree�ȣ�BST�����в��ҹؼ���e
	static BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot) 
	{
		if (EQUAL(e, v)) return v; hot = v; //�˻���������������ڵ�v������
		while (1) { //һ��أ��������ϵ�
			BinNodePosi(T) & c = (e < hot->data) ? hot->lc : hot->rc; //ȷ�����뷽��
			if (EQUAL(e, c)) return c; hot = c; //���з��أ���������һ��
		} //hotʼ��ָ�����һ��ʧ�ܽڵ�
	} //����ʱ������ֵָ�����нڵ㣨������ͨ���ڱ�����hotָ���丸�ף��˻�ʱΪ��ʼֵNULL��

	BinNodePosi(T) & search(T e)
	{
		return searchIn(_root, e, _hot = NULL);
	}

	int updateHeight(BinNodePosi(T) x) //���½ڵ�x�߶�
	{
		return x->height = 1 + max(stature(x->lc), stature(x->rc));
	}

	BinNodePosi(T) connect34(
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
	{
		//*DSA*/print(a); print(b); print(c); printf("\n");
		a->lc = T0; if (T0) T0->parent = a;
		a->rc = T1; if (T1) T1->parent = a; updateHeight(a);
		c->lc = T2; if (T2) T2->parent = c;
		c->rc = T3; if (T3) T3->parent = c; updateHeight(c);
		b->lc = a; a->parent = b;
		b->rc = c; c->parent = b; updateHeight(b);
		return b; //�������µĸ��ڵ�
	}

	BinNodePosi(T) rotateAt(BinNodePosi(T) v)  //vΪ�ǿ��ﱲ�ڵ�
	{
		if (!v) { exit(-1); }
		BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; //��v��p��g���λ�÷��������
		if (IsLChild(*p)) /* zig */
			if (IsLChild(*v)) { /* zig-zig */ //*DSA*/printf("\tzIg-zIg: ");
				p->parent = g->parent; //��������
				return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
			}
			else { /* zig-zag */  //*DSA*/printf("\tzIg-zAg: ");
				v->parent = g->parent; //��������
				return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
			}
		else  /* zag */
			if (IsRChild(*v)) { /* zag-zag */ //*DSA*/printf("\tzAg-zAg: ");
				p->parent = g->parent; //��������
				return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
			}
			else { /* zag-zig */  //*DSA*/printf("\tzAg-zIg: ");
				v->parent = g->parent; //��������
				return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
			}
	}

	void updateHeightAbove(BinNodePosi(T) x) { //���¸߶�
		while (x) {
			updateHeight(x);
			x = x->parent;
		}
	}

	BinNodePosi(T) insert(const T& e) //���ؼ���e����AVL����
	{ 
		BinNodePosi(T) & x = search(e);
		if (x) { //���x���ڣ���ô���ִ���+1
			x->num++;
			return x;
		}
		BinNodePosi(T) xx = x = new BinNode<T>(e, _hot);
		_size++; //�����½ڵ�x
				 // ��ʱ��x�ĸ���_hot�����ߣ������游�п���ʧ��
		for (BinNodePosi(T) g = _hot; g; g = g->parent) { //��x֮���������ϣ�������������g
			if (!AvlBalanced(*g)) { //һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬��������
				BinNodePosi(T)& h = FromParentTo(*g);
				h = rotateAt(tallerChild(tallerChild(g))); //���½���ԭ��
				break; //g����󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ����漴����
			}
			else //����g��Ȼƽ�⣩��ֻ��򵥵�
				updateHeight(g); //������߶ȣ�ע�⣺����gδʧ�⣬�߶���������ӣ�
		} //����ֻ��һ�ε�����������������������ȫ���߶ȱ�Ȼ��ԭ
		return xx; //�����½ڵ�λ��
	} //����e�Ƿ������ԭ���У�����AVL::insert(e)->data == e

	BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot) 
	{
		BinNodePosi(T) w = x; //ʵ�ʱ�ժ���Ľڵ㣬��ֵͬx
		BinNodePosi(T) succ = NULL; //ʵ�ʱ�ɾ���ڵ�Ľ�����
		if (!HasLChild(*x)) //��*x��������Ϊ�գ����
			succ = x = x->rc; //ֱ�ӽ�*x�滻Ϊ��������
		else if (!HasRChild(*x)) //��������Ϊ�գ����
			succ = x = x->lc; //�ԳƵش�����ע�⣺��ʱsucc != NULL
		else { //���������������ڣ���ѡ��x��ֱ�Ӻ����Ϊʵ�ʱ�ժ���ڵ㣬Ϊ����Ҫ
			w = w->succ(); //�����������У��ҵ�*x��ֱ�Ӻ��*w
			swap(x->data, w->data); //����*x��*w������Ԫ��
			swap(x->num, w->num);
			BinNodePosi(T) u = w->parent;
			((u == x) ? u->rc : u->lc) = succ = w->rc; //����ڵ�*w
		}
		hot = w->parent; //��¼ʵ�ʱ�ɾ���ڵ�ĸ���
		if (succ) succ->parent = hot; //������ɾ���ڵ�Ľ�������hot����
		return succ; //�ͷű�ժ���ڵ㣬���ؽ�����
	}

	bool remove(T e) //ɾ������д��
	{ 
		_hot = NULL;
		BinNodePosi(T)& x = search(e); if (!x) return false; //ȷ��Ŀ����ڣ�����_hot�����ã�
		if (x->num != 0) { //������ϴ�����Ϊ0����ô���ϴ���-1����
			x->num--;
			return true;
		}
		//������ϴ���Ϊ0����Ҫɾȥ�ò���
		removeAt(x, _hot); _size--; //�Ȱ�BST����ɾ��֮���˺�ԭ�ڵ�֮��_hot�������Ⱦ�����ʧ�⣩
		for (BinNodePosi(T) g = _hot; g; g = g->parent) { //��_hot�������ϣ�������������g
			if (!AvlBalanced(*g)) { //һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬��������������
				BinNodePosi(T)& h = FromParentTo(*g);
				g = rotateAt(tallerChild(tallerChild(g))); //ԭ����
				h = g;
			}
			updateHeight(g); //��������߶ȣ�ע�⣺����gδʧ�⣬�߶�����ܽ��ͣ�
		} //��������Omega(logn)�ε������������Ƿ�����������ȫ���߶Ⱦ����ܽ���
		return true; //ɾ���ɹ�
	}

	T take(T const e) //ȡ�����ڵ���Ŀ��ֵ����Сֵ
	{    
		if (!_root) return 0; //������ڵ�Ϊ�գ�����0.��Ȼ��Ŀ���Ѿ�˵��ÿ��ʯ�ž����ҵ������Ĳ��ϣ������Ѱ��ĳ��ʯ�ŵĲ���ʱ���������ܿա�
		if (_root->data == e) {//�ڸ��ڵ��ҵ�
			remove(e);
			return e;
		}

		T re = INT_MAX; //re���ڴ�Ŵ���Ŀ��ֵ����Сֵ����ʼ��Ϊ�������
		_hot = _root;
		while (1) {
			BinNodePosi(T) c = (e < _hot->data) ? _hot->lc : _hot->rc; //ȷ�����뷽��
			if (e <= _hot->data && re >= _hot->data)
				re = _hot->data; //��hot����re
			if (!c)
				break; 
			else if (e == c->data) 
			{
				re = e;
				break;
			}
			_hot = c;
		}
		remove(re);
		return re;
	}
};

