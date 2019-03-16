#include <iostream>
#include "list.h"
#define MAX_COORDINATE 33554432
#define MIN_COORDINATE -33554432
struct node {
	int x;
	int y;
};
bool isSamePoint(struct node node1, struct node node2)
{
	return (node1.x == node2.x && node1.y == node2.y);
}

bool collinear(struct node node1, struct node node2, struct node node3)
{
	long long judegSide = (long long)(node2.x - node1.x) * (long long)(node3.y - node1.y) -
		(long long)(node3.x - node1.x) * (long long)(node2.y - node1.y);
	return judegSide == 0; //���������z�������Ϊ0������������
}
int main()
{
//#ifndef _OJ_
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
//#endif
	int n;
	fread(&n, sizeof(int), 1, stdin);
	struct node *P = new struct node[n];
for (int i=0; i<n; i++) {
    fread(&P[i].x, sizeof(int), 1, stdin);
    fread(&P[i].y, sizeof(int), 1, stdin);
}
	List<struct node> pointOnHull;
	//��һ���ҵ����µĵ㣨����ж�����µĵ�Ҳû�й�ϵ��ֻҪ�ҵ����Ǹ������¼��ɣ�
	struct node lowestPoint;
	lowestPoint.y = MAX_COORDINATE; //���µ��ʼ��Ϊ���int
	lowestPoint.x = MAX_COORDINATE;
	for (int i = 0; i < n; i++)
		if (P[i].y < lowestPoint.y || (P[i].y == lowestPoint.y && P[i].x < lowestPoint.x)) 
			lowestPoint = P[i];
			
	pointOnHull.push(lowestPoint);
	//�ڶ�����ѭ�����ӵ���һ��
	//��ĳһ��Ϊpi����һ��Ϊpi+1��Ӧ��֤pi->pi+1��ʹ�����еĵ㶼�����ǵ��󷽣�����ʱ��Ѱ�ң�
	//��ν�ҷ�����pi->pi+1��pi->��������һ��Ĳ��ָ��z�����򣬼�������������0
	//���г˷�ʱ��long long����
	while (isSamePoint(pointOnHull.top(), lowestPoint) == false || pointOnHull.size() == 1)
	//ѭ�������������ص���ʼ����Ҵ�С����1
	{
		struct node top = pointOnHull.top();
		struct node endPoint = P[0];
		for (int i = 1; i < n; i++) //P[0]�ѱ�ѡȡ
		{
			long long judegSide = (long long)(endPoint.x - top.x) * (long long)(P[i].y - top.y) -
				(long long)(P[i].x - top.x) * (long long)(endPoint.y - top.y);
			if (isSamePoint(endPoint, top) == true || judegSide < 0)//�ҵ�һ�����ҷ�����Ҫ������Ϊ�µ�endPoint�������ɵ�endPoint������top������
				endPoint = P[i];
		}
		//���������ѭ���Ѿ��ҵ��������һ��endPoint����ʱ��endPoint,top,top->prec�Ƿ���
		//������ߣ�pop()
		if (pointOnHull.size() >= 2 && collinear(pointOnHull.last()->pred->data, top, endPoint) == true)
			pointOnHull.pop();
		pointOnHull.push(endPoint);
	}
	//printf("%d", pointOnHull.size());
	ListNodePosi(struct node) anode = pointOnHull.first();
	for (int i = 0; i < pointOnHull.size() - 1; i++)
	{
		printf("%d %d\n", anode->data.x, anode->data.y);
		anode = anode->succ;
	}
}
