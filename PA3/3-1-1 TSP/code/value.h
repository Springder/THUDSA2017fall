#pragma once
#pragma once
#include <iostream>
#include "vector.h" //��������
#include "list.h"
#include "stack.h"
#include <cstring>
#define INT_MAX 2147483647
#define INT_MIN (-2147483647 - 1)
//INT_MIN
struct Edge { //�߶���Ϊ���������δ�ϸ��װ
	int data;
	int weight;
	int next; //�ߵ���һ������
	Edge(int const& d, int w, int n) : data(d), weight(w), next(n) {}
};


struct Vertex { //�������Ϊ���������δ�ϸ��װ
	int data; int inDegree, outDegree; //���ݡ��������
	List<Edge *> E;
	Vertex(int const& d = (int)0) : //�����¶���
		data(d), inDegree(0), outDegree(0), E() {} //�ݲ�����Ȩ�����
};

struct path
{
	int in, d, out;
	path() : in(NULL), d(NULL), out(NULL) {}
	path(int i, int d, int o) :
		in(i), d(d), out(o) {}
};

class GraphList { //�������������ڽӱ���ʽʵ�ֵ�ͼ
private:
	Vector< Vertex> V; //���㼯��������
public:
	int n; //������
	int e; //����
	GraphList() { n = e = 0; }
	~GraphList() { //����
		for (int i = 0; i < n; i++)
		{
			V[i].E.Outclear();
		}
	}
	// ����Ļ�����������ѯ��i�����㣨0 <= i < n)
	int& vertex(int i) { return V[i].data; } //����
	int inDegree(int i) { return V[i].inDegree; } //���
	int outDegree(int i) { return V[i].outDegree; } //����
													// ����Ķ�̬����
	int insert(int const& vertex) { //���붥�㣬���ر��
		n++;
		return V.insert(Vertex(vertex)); //������������һ������
	}
	// �ߵĶ�̬����
	void insert(int const& edge, int w, int i, int j)
	{ //����Ȩ��Ϊw�ı�e = (i, j)
		ListNodePosi(Edge*) cursor = V[i].E.first();
		bool flag = false;//True: ��i,j������
		while (cursor->succ != NULL)
		{
			if (cursor->data->next == j)
			{
				flag = true; //�ҵ���������
				if (cursor->data->weight < w)
					cursor->data->weight = w; //����ߵ�Ȩ��ҪС�������֮
				break; //�˳�
			}
			cursor = cursor->succ;
		}
		if (!flag) //���û���ҵ�
		{
			Edge * ei = new Edge(edge, w, j);
			V[i].E.insertAsLast(ei);
			e++; V[i].outDegree++; V[j].inDegree++; //���±߼���������������
		}
	}
	void print()
	{
		for (int i = 0; i < n; i++)
		{
			printf("data=%d \n", V[i].data);
			ListNodePosi(Edge*) cursor = V[i].E.first();
			while (cursor->succ != NULL)
			{
				printf("linked %d", vertex(cursor->data->next));
				cursor = cursor->succ;
			}
			printf("\n");
		}
	}

	Stack<int>* gatSort(Stack<int> &zeroIn);
	int longestValue();
	void longestPath();
};
Stack<int>* GraphList::gatSort(Stack<int> &zeroIn) //�V������������㷨
{
	Stack<int> *ts = new Stack<int>;
	Stack<int> ad;
	for (int i = 0; i < n; i++)
		if (V[i].inDegree == 0)
		{
			ad.push(i);
			zeroIn.push(i);
		}
	while (!ad.empty())
	{
		int v = ad.pop();
		ts->push(vertex(v));
		ListNodePosi(Edge *) cursor = V[v].E.first();
		while (cursor->succ != NULL)
		{
			if (--V[cursor->data->next].inDegree == 0)
				ad.push(cursor->data->next);
			cursor = cursor->succ;
		}
	}
	return ts;
}

int GraphList::longestValue()
{
	Stack<int> zeroIn; //�洢��ʼ״̬ʱ�������Ϊ0�ĵ�
	Stack<int>* ts = gatSort(zeroIn);
	//zeroIn.print();
	//ts->print();
	int DIST_MAX = INT_MIN;
	while (!zeroIn.empty())
	{
		int v = zeroIn.pop();
		int *dist = new int[n];
		memset(dist, -1, sizeof(int)*n);
		dist[v] = 0;
		ListNodePosi(int) cursor = ts->first();

		//Move cursor to the vertex whose inDegree is 0
		while (cursor->succ != NULL)
		{
			if (cursor->data == vertex(v))
				break;
			cursor = cursor->succ;
		}

		while (cursor->succ != NULL)
		{
			int vet = cursor->data - 1;
			ListNodePosi(Edge *) edgeCursor = V[vet].E.first();
			while(edgeCursor->succ!=NULL)
			{
				int weight = edgeCursor->data->weight;
				int next = edgeCursor->data->next;
				if (dist[vet] + weight > dist[next])  
					dist[next] = dist[vet] + weight;
				edgeCursor = edgeCursor->succ;
			}
			cursor = cursor->succ;
		}
		int dist_max = INT_MIN;
		for (int i = 0; i < n; i++)
			if (dist[i] > dist_max)
				dist_max = dist[i];
		if (dist_max >= DIST_MAX)
			DIST_MAX = dist_max;
	}
	printf("%d", DIST_MAX);
	return DIST_MAX;
}