#include <iostream>
//#include "Bitmap.h"
#define Posi(T) ListNode<T>*
typedef int Rank;
template <typename T>
struct ListNode
{
	T data;
	Posi(T) pred;
	Posi(T) succ;
	ListNode() {}
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
		:data(e), pred(p), succ(s) {}
	Posi(T) insertAsPred(T const& e);
	Posi(T) insertAsSucc(T const& e);
};
template <typename T> //��e������ǰ�ڵ�֮ǰ�����ڵ�ǰ�ڵ������б������ڱ�ͷ�ڵ�header��
Posi(T) ListNode<T>::insertAsPred(T const& e) {
	Posi(T) x = new ListNode(e, pred, this); //�����½ڵ�
	pred->succ = x; pred = x; //������������
	return x; //�����½ڵ��λ��
}

template <typename T> //��e���浱ǰ�ڵ�֮������ڵ�ǰ�ڵ������б������ڱ�β�ڵ�trailer��
Posi(T) ListNode<T>::insertAsSucc(T const& e) {
	Posi(T) x = new ListNode(e, this, succ); //�����½ڵ�
	succ->pred = x; succ = x; //������������
	return x; //�����½ڵ��λ��
}


template <typename T> class List {
private:
	int _size;
	Posi(T) header;
	Posi(T) trailer;
protected:
	void init();
	int clear();

public:
	List() { init(); } //Ĭ��
	T remove(Posi(T) p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	~List();
	Rank size() const { return _size; } //��ģ
	Posi(T) first() const { return header->succ; }
	Posi(T) last() const { return trailer->pred; }
	Posi(T) insertAsFirst(T const& e);
	Posi(T) insertAsLast(T const& e);
	Posi(T) insertA(Posi(T) p, T const& e);
	Posi(T) insertB(Posi(T) p, T const& e);
	Posi(T) insertm(T const& e, Rank m, Posi(T) p); // ��m������
	//T& operater[](Rank r) const;
	void printlist() const;
	void inverseprint(Posi(T) p) const;
};
template <typename T> void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}
template <typename T> int List<T>::clear() { //����б�
	int oldSize = _size;
	while (0 < _size) 
		remove(header->succ); //����ɾ���׽ڵ㣬ֱ���б���
	return oldSize;
}
template <typename T> Posi(T) List<T>::insertAsFirst(T const& e)
{
	_size++; return header->insertAsSucc(e);
};//e�����׽ڵ����

template <typename T> Posi(T) List<T>::insertAsLast(T const& e)
{
	_size++; return trailer->insertAsPred(e);
} //e����ĩ�ڵ����

template <typename T> Posi(T) List<T>::insertA(Posi(T) p, T const& e)
{
	_size++; return p->insertAsSucc(e);
} //e����p�ĺ�̲��루After��

template <typename T> Posi(T) List<T>::insertB(Posi(T) p, T const& e)
{
	_size++; return p->insertAsPred(e);
} //e����p��ǰ�����루Before)

template <typename T> Posi(T) List<T>::insertm(T const& e, Rank m, Posi(T) p)
{
	//printf("%d insertm\n", e);
	// �������������û���˼���1����ʱ
	if (_size == 0) p = insertAsFirst(e); //��Ϊ�׽ڵ�
	else if (_size == 1) p = insertAsLast(e); //��Ϊĩ�ڵ�
	else
	{
		//printf("��ǰ�ڵ�data=%d\n", p->data);
		int walked = 1; //���߹�����
		while (walked < m)
		{
			//printf("walked=%d p=%d\n", walked, p->data);
			if (p->succ->succ == NULL)//��ĩ�ڵ㷵�ؿ�ͷ�����Ѿ��߹����� + 1
			{
				//printf("�ص�first\n");
				p = first();
			}
			else
			{
				//printf("����\n");
				p = p->succ;//���ϸ��ڵ㿪ʼ��
			}
			walked++;
		}
		return insertA(p, e);
	}
	return p;
}

template <typename T> T List<T>::remove(Posi(T) p) { //ɾ���Ϸ��ڵ�p����������ֵ
	T e = p->data; //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
	p->pred->succ = p->succ; p->succ->pred = p->pred; //��̡�ǰ��
	delete p; _size--; //�ͷŽڵ㣬���¹�ģ
	return e; //���ر��ݵ���ֵ
}

template<typename T>
List<T>::~List()
{
	clear(); delete header; delete trailer;
}

template<typename T>
void List<T>::printlist() const
{
	printf("��ӡlist\n");
	Posi(T) sp = first(); //���׽ڵ����
	int i = 0;
	while (i<_size)
	{
		printf("%d ", sp->data);
		sp = sp->succ;
		i++;
	}
	printf("\n");
}
template<typename T>
void List<T>::inverseprint(Posi(T) p) const
{
	int count = 0;
	while (p->pred != NULL) //��ͷ�ڵ㣬����������ӡ
	{
		printf("%d ", p->data);
		p = p->pred;
		count++;
	}
	//��ӡ���p��Ϊ�׽ڵ�
	p = last(); //��ĩβ��ʼ
	while (count < _size)
	{
		printf("%d ", p->data);
		count++;
		p = p->pred;
	}
}
int main()
{
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int n, m;
	if (scanf("%d %d", &n, &m) == EOF)
		return 0;
	List<int> listman;
	int num;
	Posi(int) p = NULL;
	for (int i = 0; i < n; i++)
	{
		if (scanf("%d", &num) == EOF)
			return 0;
		p = listman.insertm(num, m, p);
		//listman.printlist();
	}
	//printf("�����ӡǰ��data=%d ", p->data);
	listman.inverseprint(p);
	return 0;
}