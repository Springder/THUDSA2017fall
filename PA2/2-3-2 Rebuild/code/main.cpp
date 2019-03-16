#include "iostream"
#include "bintree.h"
#include "stack.h"
#define MAX_N 4000000

struct part {
	BinNodePosi(int) binnode;
	int pre_st;
	int pre_ed; 
	int post_st;
	int post_ed;
};

void rebuild(BinTree<int> &bt, BinNodePosi(int) &x, int  *pre, int pre_st, int pre_ed, int *post,  int post_st, int post_ed)
// x���ϴε�����bt�Ľڵ㣬�Ѵ����ϴνڵ���ֵ
{
	//printf("%d %d %d %d\n", pre_st, pre_ed, post_st, post_ed);
	BinNodePosi(int) lc = bt.insertAsLC(x, pre[pre_st+1]);
	BinNodePosi(int) rc = bt.insertAsRC(x, post[post_ed-1]);

	int post_st_l = post_st;
	int post_ed_l = post_st;
	for (int i = post_st+1; i <= post_ed - 1; i++)
	{
		if (post[i] == pre[pre_st+1])
		{
			post_ed_l = i;
			break;
		}
	}
	int post_st_r = post_ed_l + 1;
	int post_ed_r = post_ed - 1;

	int pre_st_l = pre_st + 1;
	int pre_ed_l = post_ed_l - post_st_l + pre_st_l;
	int pre_st_r = pre_ed_l + 1;
	int pre_ed_r = post_ed_r - post_st_r + pre_st_r;
	//printf("%d %d %d %d\n", pre_st_l, pre_ed_l, post_st_l, post_ed_l);

	if (pre_ed_l - pre_st_l >= 2)
		rebuild(bt, lc, pre, pre_st_l, pre_ed_l, post, post_st_l, post_ed_l);

	if (pre_st_r - pre_ed_r >=2)
		rebuild(bt, rc, pre, pre_st_r, pre_ed_r, post, post_st_r, post_ed_r);
}

void chai(BinTree<int> &bt, BinNodePosi(int) &x, Stack<part> &S, int  *pre, int pre_st, int pre_ed, int *post, int post_st, int post_ed)
{
	while (pre_ed - pre_st >= 2) //�ڵ���Ҷ��֮ǰ���Ͻ���
	{
		BinNodePosi(int) lc = bt.insertAsLC(x, pre[pre_st + 1]);
		BinNodePosi(int) rc = bt.insertAsRC(x, post[post_ed - 1]);
		int post_st_l = post_st;
		int post_ed_l = post_st;
		for (int i = post_st + 1; i <= post_ed - 1; i++)
		{
			if (post[i] == pre[pre_st + 1])
			{
				post_ed_l = i;
				break;
			}
		}
		int post_st_r = post_ed_l + 1;
		int post_ed_r = post_ed - 1;
		int pre_st_l = pre_st + 1;
		int pre_ed_l = post_ed_l - post_st_l + pre_st_l;
		int pre_st_r = pre_ed_l + 1;
		int pre_ed_r = post_ed_r - post_st_r + pre_st_r;

		struct part right = { rc, pre_st_r, pre_ed_r, post_st_r, post_ed_r};
		S.push(right);

		x = lc;
		pre_st = pre_st_l;
		pre_ed = pre_ed_l;
		post_st = post_st_l;
		post_ed = post_ed_l;
	}
}

void build(BinTree<int> &bt, int *pre, int *post, int n)
{
	Stack<part> S;
	BinNodePosi(int) root = bt.insertAsRoot(pre[0]);
	struct part temp = { root, 0, n - 1, 0, n - 1 };
	S.push(temp);
	while (true)
	{
		if (S.empty()) break;
		struct part temp = S.pop();
		chai(bt, temp.binnode, S, pre, temp.pre_st, temp.pre_ed, post, temp.post_st, temp.post_ed);
	}
}


static void goAlongLeftBranch(BinNodePosi(int) x, Stack<BinNodePosi(int)>& S) {
	while (x) { S.push(x); x = x->lc; } //��ǰ�ڵ���ջ���漴������֧���룬����ֱ��������
}

void travIn(BinNodePosi(int) x) { //��������������㷨��������#1��
	Stack<BinNodePosi(int)> S; //����ջ
	while (true) {
		goAlongLeftBranch(x, S); //�ӵ�ǰ�ڵ������������ջ
		if (S.empty()) break; //ֱ�����нڵ㴦�����
		x = S.pop(); printf("%d ", x->data); //����ջ���ڵ㲢����֮
		x = x->rc; //ת��������
	}
}
int main() {
//#ifndef _OJ_
//	freopen("input1.txt", "r", stdin);
//	//freopen("output2.txt", "w", stdout);
//#endif
	int n;
	scanf("%d", &n);
	int *pre = new int[n];
	int *post = new int[n];
	for (int i = 0; i < n; i++)
		scanf("%d", &pre[i]);
	for (int i=0;i<n;i++)
		scanf("%d", &post[i]);
	
	BinTree<int> bt;
	build(bt, pre, post, n);
	travIn(bt.getroot());
	//BinNodePosi(int) ha = bt.insertAsRoot(pre[0]);
	//rebuild(bt, ha, pre, 0, n - 1, post, 0, n - 1);
	//travIn(bt.getroot());
}