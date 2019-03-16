#pragma once
#include <iostream>
#include "vector.h"
#include "bintree.h"
#include "DataHead.h"
#include "stack.h"


struct rangeStack //�ڵݹ黮���������ʱ���õ���ջ
{
	BinNodePosi(int) x;
	int left, right;
	rangeStack(BinNodePosi(int) x = NULL) : x(x), left(NULL), right(NULL) {}
	rangeStack(BinNodePosi(int) x, int left, int right) : x(x), left(left), right(right) {}
};

//struct rangeStack
//{
//	int left, right;
//	rangeStack() : left(NULL), right(NULL) {}
//	rangeStack(int left, int right) : left(left), right(right) {}
//};


void quicksort_x(int left, int right, struct data *a) //����x��С�����������(�ж������ڽṹ����ʵ�֣�
{
	int i, j;
	struct data t, temp;
	if (left>right)
		return;
	temp = a[left]; //temp�д�ľ��ǻ�׼�� 
	i = left;
	j = right;
	while (i != j)
	{
		//˳�����Ҫ��Ҫ�ȴ��ұ߿�ʼ�� 
		while (a[j].x >= temp.x && i < j) j--;
		//�����ұߵ� 
		while (temp.x >= a[i].x && i<j) i++;
		//�����������������е�λ�� 
		if (i < j) { t = a[i]; a[i] = a[j]; a[j] = t; }
	}
	//���ս���׼����λ 
	a[left] = a[i];
	a[i] = temp;
	quicksort_x(left, i - 1, a);//����������ߵģ�������һ���ݹ�Ĺ��� 
	quicksort_x(i + 1, right, a);//���������ұߵ� ��������һ���ݹ�Ĺ��� 
}

void quickSort(int left, int right, Vector<int> &a) //����TP�����yֵ��С�����������
{
	int i, j;
	int t, temp;
	if (left>right)
		return;
	temp = a[left]; //temp�д�ľ��ǻ�׼�� 
	i = left;
	j = right;
	while (i != j)
	{
		//˳�����Ҫ��Ҫ�ȴ��ұ߿�ʼ�� 
		while (TP[a[j]].y >= TP[temp].y && i < j) j--;
		//�����ұߵ� 
		while (TP[temp].y >= TP[a[i]].y && i<j) i++;
		//�����������������е�λ�� 
		if (i < j) { t = a[i]; a[i] = a[j]; a[j] = t; }
	}
	//���ս���׼����λ 
	a[left] = a[i];
	a[i] = temp;
	quickSort(left, i - 1, a);//����������ߵģ�������һ���ݹ�Ĺ��� 
	quickSort(i + 1, right, a);//���������ұߵ� ��������һ���ݹ�Ĺ��� 
}

void findSameX(int left, int right, Vector<int> &X, Vector<int> &begin, Vector<int> &end, struct data* a)
{
	int i = 0;
	int x = a[left].x;
	X.insert(x);
	begin.insert(left);
	while (i >= left && i <= right)
	{
		if (a[i].x > x)
		{
			x = a[i].x;
			X.insert(x);
			begin.insert(i);
			if (i > left)
				end.insert(i - 1);
		}
		i++;
	}
	end.insert(right);
}

void quicksort_y(int left, int right, struct data *a) //����y��С�����������(�ж������ڽṹ����ʵ�֣�
{
	int i, j;
	struct data t, temp;
	if (left>right)
		return;
	temp = a[left]; //temp�д�ľ��ǻ�׼�� 
	i = left;
	j = right;
	while (i != j)
	{
		//˳�����Ҫ��Ҫ�ȴ��ұ߿�ʼ�� 
		while (a[j].y >= temp.y && i < j) j--;
		//�����ұߵ� 
		while (temp.y >= a[i].y && i<j) i++;
		//�����������������е�λ�� 
		if (i < j) { t = a[i]; a[i] = a[j]; a[j] = t; }
	}
	//���ս���׼����λ 
	a[left] = a[i];
	a[i] = temp;
	quicksort_y(left, i - 1, a);//����������ߵģ�������һ���ݹ�Ĺ��� 
	quicksort_y(i + 1, right, a);//���������ұߵ� ��������һ���ݹ�Ĺ��� 
}




void rangeBuild(BinTree<int> &tr, BinNodePosi(int) &x, int left, int right, struct data *TP, Vector<int> &X, Vector<int> &begin, Vector<int> &end, Stack<rangeStack> &S)
//��ע�⣬��νleft��right��ָ��X�ı߽�rank
{
	int mid;
	mid = (left + right) >> 1;
	if (x == NULL) //���xΪ�գ�������ڵ�
	{
		x = tr.insertAsRoot(X[(left + right) >> 1], X[left], X[right], false);
		for (int i = begin[left];i <= end[right];i++) //��ʱi�����TP(ԭ�ṹ������)��rank
			x->Y.insert(i);
		quickSort(0, end[right] - begin[left], x->Y);
		//x->Y.print();
		//x->Y.printy();
		struct rangeStack rightStack(x, mid+1, right);
		struct rangeStack leftStack(x, left, mid);
		S.push(rightStack);
		S.push(leftStack); //��������ȳ�
		//BinNodePosi(int) tmp = x;

		//rangeBuild(tr, x, left, mid, TP, X, begin, end);
		//rangeBuild(tr, tmp, mid + 1, right, TP, X, begin, end);
		return;
	}

	if (right == left) //������䳤��Ϊ0������Ҷ�ڵ�
	{
		if (x->data >= X[right])
		{
			tr.insertAsLC(x, X[left], X[left], X[right], true);
			for (int i = begin[left];i <= end[right];i++)
				x->lc->Y.insert(i);
			quickSort(0, end[right] - begin[left], x->lc->Y);
		}
		else
		{
			tr.insertAsRC(x, X[left], X[left], X[right], true);
			for (int i = begin[left];i <= end[right];i++)
				x->rc->Y.insert(i);
			quickSort(0, end[right] - begin[left], x->rc->Y);
		}
		//printf("left=%d, right=%d\n", left, right);x->Y.printy();
		return;
	}

	if (left + 1 <= right) //���䳤��>=1
	{
		x = (x->data >= X[mid]) ? tr.insertAsLC(x, X[mid], X[left], X[right], false) : \
			tr.insertAsRC(x, X[mid], X[left], X[right], false);
		for (int i = begin[left];i <= end[right];i++) //��ʱi�����TP(ԭ�ṹ������)��rank
			x->Y.insert(i);
		quickSort(0, end[right] - begin[left], x->Y);
		struct rangeStack rightStack(x, mid + 1, right);
		struct rangeStack leftStack(x, left, mid);
		S.push(rightStack);
		S.push(leftStack); //��������ȳ�
		//printf("left=%d, right=%d\n", left, right);x->Y.printy();
		//BinNodePosi(int) tmp = x;
		//rangeBuild(tr, x, left, mid, TP, X, begin, end);
		//rangeBuild(tr, tmp, mid + 1, right, TP, X, begin, end);
	}
}

void RangeBuild(BinTree<int> &tr, BinNodePosi(int) &x, int left, int right, Vector<int> &X, Vector<int> &begin, Vector<int> &end)
{
	struct rangeStack temp;
	Stack<rangeStack> S;
	rangeBuild(tr, x, left, right, TP, X, begin, end, S);
	while (!S.empty())
	{
		temp = S.pop();
		rangeBuild(tr, temp.x, temp.left, temp.right, TP, X, begin, end, S);
	}
}

void query_y(Vector<int> &y, int lo_y, int hi_y, long long &t, int &count)
//��ѯy�����䡣��ע��y��TP�����rank�������Ѿ�����TP�����yֵ��С��������
//���ǵ�Ŀ���ǣ���ѯ���д��ڵ���lo_y��С�ڵ���hi_y��ֵ
//��Ҫ��Զ��ֲ�����һ��΢С�ĸĶ����ܲ�����
{
	//y.printy();
	int lo = 0;
	int hi = y.size();
	if (TP[y[lo]].y > hi_y || TP[y[hi - 1]].y < lo_y) //�޽���
		return;
	int st, ed;
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		lo_y <= TP[y[mi]].y ? hi = mi: lo = mi + 1; //(lo, mi] or (mi, hi]
	} //hi-1�Ǵ��ڵ���Ŀ��ֵ����Сֵ��rank
	//printf("lo=%d hi=%d\n", lo, hi);
	//printf("find =%d", y[hi]);
	st = hi;
	lo = 0;
	hi = y.size();
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		hi_y < TP[y[mi]].y ? hi = mi : lo = mi + 1; //[lo, mi) or [mi, hi)
	}//lo-1��С�ڵ���Ŀ��ֵ�����ֵ��rank
	ed = lo - 1;

	//��¼�¶Ⱥͼ�����
	for (int i = st;i <= ed;i++)
	{
		//printf("%d %d %d\n", TP[y[i]].x, TP[y[i]].y, TP[y[i]].t);
		t += TP[y[i]].t;
		count++;
	}
}

void query(BinTree<int> &tr, BinNodePosi(int) x, int lo_x, int hi_x, int lo_y, int hi_y, long long &sum_t, int &count, Stack<BinNodePosi(int)> &temp)
{
	int x_mid = x->data; //��λ��
	int x_left = x->left; //��߽�
	int x_right = x->right; //right boundary
	if (x_left > hi_x || x_right < lo_x)
		return; //û�н���
	if (x->isExternal) //����Ҷ�ڵ�
	{
		if (x->data >= lo_x && x->data <= hi_x)//Ҷ�ڵ���������
			query_y(x->Y, lo_y, hi_y, sum_t, count);
		return;
	}
	if ((x_left >= lo_x && x_right <= hi_x)) //��ǰx���䱻�����ڲ�ѯ��x����
	{
		query_y(x->Y, lo_y, hi_y, sum_t, count);
		return; //����
	}

	if (x_mid >= lo_x && x_mid < hi_x) //��ǰx������λ�������ڴ���ѯ�����У�ע��mid�����ǹ������ӵģ�
	{
		temp.push(x->rc);
		temp.push(x->lc);
	}
	else if (x_mid >= hi_x)
		temp.push(x->lc);
	else if (x_mid < lo_x)
		temp.push(x->rc);
}

int Query(BinTree<int> &tr, int lo_x, int hi_x, int lo_y, int hi_y)
{
	int re;
	long long sum_t = 0;
	int count = 0;
	BinNodePosi(int) x = tr.getroot();
	Stack<BinNodePosi(int)> temp;
	BinNodePosi(int) c;
	query(tr, x, lo_x, hi_x, lo_y, hi_y, sum_t, count, temp);
	while (!temp.empty())
	{
		c = temp.pop();
		query(tr, c, lo_x, hi_x, lo_y, hi_y, sum_t, count, temp);
	}
	//printf("%lld %d\n", sum_t, count);
	return re = (count == 0) ? 0 : (int)(sum_t / (long long)count);
}