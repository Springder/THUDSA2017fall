/******************************************************************************************
* Data Structures in C++
* ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
* Junhui DENG, deng@tsinghua.edu.cn
* Computer Science & Technology, Tsinghua University
* Copyright (c) 2006-2013. All rights reserved.
******************************************************************************************/

#pragma once
#include <cstring>
#include "vector.h" //��������
#include "stack.h"
#include "release.h"
#define INT_MAX 2147483647
#define INT_MIN (-2147483647 - 1)

template <typename Tv> struct Vertex { //�������Ϊ���������δ�ϸ��װ��
	Tv data; int inDegree, outDegree;
	Vertex(Tv const& d = (Tv)0) : //�����¶���
		data(d), inDegree(0), outDegree(0){} //�ݲ�����Ȩ�����
};

template <typename Te> struct Edge { //�߶���Ϊ���������δ�ϸ��װ��
	Te data; int weight;
	Edge(Te const& d, int w) : data(d), weight(w) {} //����
};


template <typename Tv, typename Te> //�������͡�������
class GraphMatrix { //�������������ڽӾ�����ʽʵ�ֵ�ͼ
private:
	Vector< Vertex< Tv > > V; //���㼯��������
	Vector< Vector< Edge< Te > * > > E; //�߼����ڽӾ���
public:
	GraphMatrix() { n = e = 0; } //����
	~GraphMatrix() { //����
		for (int j = 0; j < n; j++) //���ж�̬������
			for (int k = 0; k < n; k++) //�߼�¼
				delete E[j][k]; //�������
	}
	int n;
	// ����Ļ�����������ѯ��i�����㣨0 <= i < n��
	Tv& vertex(int i) { return V[i].data; } //����
	int inDegree(int i) { return V[i].inDegree; } //���
	int outDegree(int i) { return V[i].outDegree; } //����
	int firstNbr(int i) { return nextNbr(i, n); } //�׸��ڽӶ���
	int nextNbr(int i, int j) //����ڶ���j����һ�ڽӶ��㣨�����ڽӱ�����Ч�ʣ�
	{
		while ((-1 < j) && (!exists(i, --j))); return j;
	} //����������̽

	int lastNbr(int i) { return nextNbrClock(i, -1); }
	int nextNbrClock(int i, int j)
	{
		while (j < n && !exists(i, ++j)); return j;
	}

	int firstInvNbr(int i) { return nextInvNbr(i, n); } //�׸��ڽӶ���
	int nextInvNbr(int i, int j)
	{
		while ((-1 < j) && (!exists(--j, i))); return j;
	}

	int e; //������
		   // ����Ķ�̬����
	int insert(Tv const& vertex) { //���붥�㣬���ر��
		for (int j = 0; j < n; j++) E[j].insert(NULL); n++; //������Ԥ��һ��Ǳ�ڵĹ�����
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*) NULL)); //�����¶����Ӧ�ı�����
		return V.insert(Vertex<Tv>(vertex)); //������������һ������
	}
	Tv remove(int i) { //ɾ����i�����㼰������ߣ�0 <= i < n��
		for (int j = 0; j < n; j++) //���г���
			if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; } //����ɾ��
		E.remove(i); n--; //ɾ����i��
		Tv vBak = vertex(i); V.remove(i); //ɾ������i
		for (int j = 0; j < n; j++) //�������
			if (Edge<Te> * e = E[j].remove(i)) { delete e; V[j].outDegree--; } //����ɾ��
		return vBak; //���ر�ɾ���������Ϣ
	}
	// �ߵ�ȷ�ϲ���
	bool exists(int i, int j) //��(i, j)�Ƿ����
	{
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}
	// �ߵĻ�����������ѯ����i��j֮������ߣ�0 <= i, j < n��exists(i, j)��
	Te& edge(int i, int j) { return E[i][j]->data; } //��(i, j)������
	int& weight(int i, int j) { return E[i][j]->weight; } //��(i, j)��Ȩ��
														  // �ߵĶ�̬����
	void insert(Te const& edge, int w, int i, int j) { //����Ȩ��Ϊw�ı�e = (i, j)
		if (exists(i, j) && E[i][j]->weight >= w) return;
		else if (exists(i, j) && E[i][j]->weight < w) { E[i][j]->weight = w; return; }
		E[i][j] = new Edge<Te>(edge, w); //�����±�
		e++; V[i].outDegree++; V[j].inDegree++; //���±߼������������Ķ���
												//printf("%d %d\n", E[i][j]->data, E[i][j]->weight);
	}
	Te remove(int i, int j) { //ɾ������i��j֮������ߣ�exists(i, j)��
		Te eBak = edge(i, j); delete E[i][j]; E[i][j] = NULL; //���ݺ�ɾ���߼�¼
		e--; V[i].outDegree--; V[j].inDegree--; //���±߼������������Ķ���
		return eBak; //���ر�ɾ���ߵ���Ϣ
	}

	void printedge() {
		for (int j = 0; j < n; j++) //���ж�̬������
			for (int k = 0; k < n; k++) //�߼�¼
				printf("%d %d", E[j][k]->data, E[j][k]->weight);
	}

	void printedge(int i, int j) {
		printf("%d %d", E[i][j]->data, E[i][j]->weight);
	}
	void printvertex() {
		for (int j = 0; j < n; j++) //���ж�̬������
			printf("%d ", V[j].data);
	}
	void longestPath(); //�·��
	void longestValue(Stack<Tv> &ts);
	Stack<Tv>* tSort(int); //����DFS�����������㷨
	void gatSort(Stack<Tv> &); //�V�����������
};

template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::gatSort(Stack<Tv>& ts)
{
	Stack<Tv> ad; //����ջ�����ڴ������Ϊ0�Ľ��
	for (int i = 0; i < n; i++)
		if (V[i].inDegree == 0)
			ad.push(i);
	while (!ad.empty())
	{
		Tv v = ad.pop();
		ts.push(vertex(v));
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) //ö��v�������ھ�u
			if (--V[u].inDegree == 0)
				ad.push(u);
	}
}


template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::longestPath()
{
	Vector<int> In; //���ڴ����ܲ�����ǰȫ���·�������Ϊ0�ĵ�
	Vector<int> D;//���ڴ����ܵ�ǰȫ���·��
	Vector<int> Out;//���ڴ����ܲ���ȫ���·���ĳ���Ϊ0�ĵ�
	Stack<Tv> ts;
	gatSort(ts);
	int DIST_MAX = INT_MIN; //��ǰȫ���·����ֵ
	int *DIST;
	for (int i = 0; i < n; i++)
		if (V[i].inDegree == 0) //�������Ϊ0�ĵ㣬����·�����ȼ���
		{
			int *dist = new int[n];
			int out; //out������ʱ����ӱ������Ϊ0�ĵ����ܵ�����յ�
			for (int i = 0; i < n; i++)
				dist[i] = INT_MIN; //���о����ʼ��Ϊ�������
								   //��ʼ������ʼ��Ϊ0
			dist[i] = 0; //���i��distΪ0
						 //�����������������ҵ����Ϊ0�ĵ�
			ListNodePosi(Tv) cursor = ts->last();
			for (int j = 0; j < n; j++)
				if (vertex(i) == cursor->data)
					break;
			//�������¼��������
			while (cursor->pred != NULL)
			{
				int v = cursor->data - 1;
				for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
					if (dist[v] + weight(v, u) > dist[u])  dist[u] = dist[v] + weight(v, u);
				cursor = cursor->pred;
			}
			int dist_max = INT_MIN; //�������ʼ��Ϊ�������
			for (int i = 0; i < n; i++)
				if (dist[i] > dist_max)
				{
					dist_max = dist[i];
					out = i;
				}
			if (dist_max >= DIST_MAX)
			{
				DIST_MAX = dist_max;
				DIST = dist;
				In.insert(i); D.insert(dist_max); Out.insert(out);
			}
		}

	int v = n; //ȫ���·����Ӧ�Ľ�����С���
	int flag;
	for (int i = 0; i < In.size(); i++)
	{
		if (D[i] == DIST_MAX && In[i] <= v)
		{
			v = In[i];
			flag = i;
		}
	}
	int *DISTINV;
	for (int i = 0; i < Out.size(); i++)
	{
		if (In[i] == v)
		{
			int out = Out[i];
			int *distInv = new int[n];
			for (int i = 0; i < n; i++)
				distInv[i] = INT_MAX; //���о����ʼ��Ϊ�������
									  //��ʼ������ʼ��Ϊ0
			distInv[out] = DIST_MAX;
			//�����������������ҵ�out
			ListNodePosi(Tv) cursor = ts->first();
			while (cursor->succ != NULL)
			{
				if (cursor->data == vertex(out)) break;
				cursor = cursor->succ;
			}
			//�������ϸ��¾��루ȡС�ߣ�
			while (cursor->succ != NULL)
			{
				int v = cursor->data - 1;
				for (int u = firstInvNbr(v); -1 < u; u = nextInvNbr(v, u))
					if (distInv[v] - weight(u, v) < distInv[u])  distInv[u] = distInv[v] - weight(u, v);
				cursor = cursor->succ;
			}
			for (int j = 0; j < n; j++)
			{
				if (distInv[j] == 0)
					DISTINV = distInv;
			}
		}
	}
	for (int i = 0; i < Out.size(); i++)
	{
		if (In[i] == v)
		{
			printf("%d ", vertex(v));
			int now = v;
			while (V[now].outDegree != 0)
			{
				for (int u = lastNbr(now); u < n; u = nextNbrClock(now, u))
				{
					if (DIST[u] == DISTINV[u])
					{
						now = u; printf("%d ", vertex(u));
					}
				}
			}
		}
	}
}

template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::longestValue(Stack<Tv> &ts)
{
	gatSort(ts);
	int DIST_MAX = INT_MIN; //��ǰȫ���·����ֵ
	for (int i = 0; i < n; i++)
		if (V[i].inDegree == 0) //�������Ϊ0�ĵ㣬����·�����ȼ���
		{
			int *dist = new int[n];
			int out; //out������ʱ����ӱ������Ϊ0�ĵ����ܵ�����յ�
			memset(dist, 0, sizeof(int)*n);
			//for (int i = 0; i < n; i++)
			//	dist[i] = INT_MIN; //���о����ʼ��Ϊ�������
			//					   //��ʼ������ʼ��Ϊ0
			//dist[i] = 0; //���i��distΪ0
			//			 //�����������������ҵ����Ϊ0�ĵ�
			ListNodePosi(Tv) cursor = ts.first();
			while (cursor->succ != NULL)
			{
				if (cursor->data == vertex(i)) break;
				cursor = cursor->succ;
			}
			//�������¼��������
			while (cursor->succ != NULL)
			{
				int v = cursor->data - 1;
				for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
					if (dist[v] + weight(v, u) > dist[u])  dist[u] = dist[v] + weight(v, u);
				cursor = cursor->succ;
			}
			int dist_max = INT_MIN; //�������ʼ��Ϊ�������
			for (int i = 0; i < n; i++)
				if (dist[i] > dist_max)
				{
					dist_max = dist[i];
					out = i;
				}
			if (dist_max >= DIST_MAX)
			{
				DIST_MAX = dist_max;
			}
		}
	printf("%d", DIST_MAX);
	return;
}