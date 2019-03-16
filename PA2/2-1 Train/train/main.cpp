#include <iostream>
#include "stack.h"
int n, m;
struct movement { //�ƶ��ṹ��
	int code; //�ƶ����г��Ĵ���
	char move; //�ƶ����г��Ķ�������
} temp;

int move1step(int t, Stack<int> &A, Stack<int> &S, Stack<movement> &trainmove)
// -1��������ƶ���Ѱ��ͬ�г���
// 1�����ƶ��ɹ�
// 0�����ƶ�ʧ��
{
	/*if (S.empty() || t != S.top())//Ӧ�ô�A��ȡ
	{
		if (A.empty() || (t != A.top() && S.getsize() == m)) return 0;
		if (t == A.top())
		{
			temp.code = A.pop(); temp.move = 'P';
			trainmove.push(temp);
			return 1;
		}
		else
		{
			S.push(A.pop()); //��A��ͷ������Ȼ��ѹ��S
			temp.code = S.top(); temp.move = 'I';
			trainmove.push(temp);
			return -1; //Ӧ�ü����ƶ�
		}
	}
	temp.code = S.pop(); temp.move = 'O';
	trainmove.push(temp);
	return 1;*/
	if((!A.empty()) && A.top()==t){
		temp.code = A.pop(); temp.move = 'P';
		trainmove.push(temp);
		return 1;
	} 
	else if((!S.empty()) && S.top() == t){
		temp.code = S.pop(); temp.move = 'O';
		trainmove.push(temp);
		return 1;
	}
	else{
		if(A.empty() || S.getsize()>=m) return 0;
		S.push(A.pop()); //��A��ͷ������Ȼ��ѹ��S
		temp.code = S.top(); temp.move = 'I';
		trainmove.push(temp);
		return -1; //Ӧ�ü����ƶ�
	}
}
void printmove(Stack<movement> &A)
{
	ListNodePosi(movement) tm = A.first();
	int j = 0;
	while (j < A.getsize())
	{
		printf("%d %c\n", tm->data.code, tm->data.move);
		tm = tm->succ;
		j++;
	}
}
int main()
{
//#ifndef _OJ_
//	freopen("input1.txt", "r", stdin);
//	//freopen("output1.txt", "w", stdout);
//#endif
	
	scanf("%d %d", &n, &m);
	Stack<int> S; Stack<int> A;
	Stack<movement> trainmove;
	int tr;
	for (int i = 0; i < n; i++)
	{
		if (scanf("%d", &tr) != EOF)
			A.insertAsFirst(tr);
	}
	int flag;
	int i = 1;
	for (int i = 1; i <= n; i++)
	{
		//printf("%d\n", i);
		//S.printStack();
		flag = move1step(i, A, S, trainmove);
		while (flag == -1)
			flag = move1step(i, A, S, trainmove);
		if (flag == 0) break;
	}

	if (flag == 0)
		printf("No\n");
	else
		printmove(trainmove);
}	

