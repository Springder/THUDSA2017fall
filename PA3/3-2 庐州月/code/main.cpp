#include <iostream>
#include <cstring>

//#include "AVL.h"
#include "final.h" //����ʵ������AVL����
#include "fastio.h"

#define MAXN 350000
#define MAXM 500000
struct data {
	int p, v; //�۸�������
	bool operator >= (const data data2){return (v > data2.v) || ((v == data2.v) && (p >= data2.p));} //�жϴ��ڵ��ڣ���v�ϴ�ʱ����v��ȵ���p���ڵ���
	bool operator <= (const data data2) { return (v < data2.v) || ((v == data2.v) && (p <= data2.p)); }
	bool operator == (data data2) { return (v == data2.v) && (p == data2.p); }
	bool operator < (data data2) {
		return (v < data2.v) || ((v == data2.v) && (p < data2.p));
	}
	bool operator > (data data2) { return (v >= data2.v) && (p >= data2.p); }
	void print() { printf("v=%d, p=%d\n", v, p); }
} bri[MAXN], mat[MAXM]; //bridge and material

void quicksort(int left, int right, struct data *a) //�����������ɴ�С�������򡣼�����������ȣ���Ƚϼ۸��ж������ڽṹ����ʵ�֣�
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
		while (a[j] <= temp && i < j) j--;
		//�����ұߵ� 
		while ( temp <= a[i] && i<j) i++;
		//�����������������е�λ�� 
		if (i < j) { t = a[i]; a[i] = a[j]; a[j] = t; }
	}
	//���ս���׼����λ 
	a[left] = a[i];
	a[i] = temp;
	quicksort(left, i - 1, a);//����������ߵģ�������һ���ݹ�Ĺ��� 
	quicksort(i + 1, right, a);//���������ұߵ� ��������һ���ݹ�Ĺ��� 
}

int main()
{
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
//#ifndef _OJ_
//	freopen("input.txt", "r", stdin);
//	//	freopen("output.txt", "w", stdout);
//#endif
	int n = GetInt(), m = GetInt();
	//int n, m;
	//scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		//scanf("%d %d", &bri[i].p, &bri[i].v);
		bri[i].p = GetInt(), bri[i].v = GetInt();
	}
	for (int i = 0; i < m; i++)
	{
		//scanf("%d %d", &mat[i].p, &mat[i].v);
		mat[i].p = GetInt(), mat[i].v = GetInt();
	}
	quicksort(0, n - 1, bri);
	quicksort(0, m - 1, mat);

	AVL<int> tr;

//	for (int i = 0; i < n; i++) bri[i].print();
//	//AVLTree<int> tr;
	long long ans = 0;
	int j = 0;

	for (int i = 0; i < n; i++)
	{
		//printf("i=%d ", i);
		//bri[i].print();
		while ((j < m) && (/*(mat[j].p >= bri[i].p) &&*/ (mat[j].v >= bri[i].v))) 
			//��j�ֲ��Ͽ��������i���ţ�ע�⣬����������j�ֲ����������i�ţ��ض��������i+1�ţ�
		//����ط��Һ��ɻ���Ϊ��Ŀ���Ѿ�˵�˶��ڵ� i ����������ܳɹ������ j ��ʯ�ŵ������ǣ����ҽ��� hi �� pj��di �� vj������������ֻҪ������������Ҫ���Ҿͼӵ��������ˡ�
		//������debug�ܾã�50%����ֻ��һ����ȷ������Ⱥ��ı�����ͬѧ˵�еĲ����Ƚ����⣬�����ʯ��ȫ�ڲ������½ǵ������
		//��������ȷ���Ǹ�Ӧ��ǡ�ö�Ӧ��������������ƶϳ��ҵ�����̫ǿ�ˣ������ҷֱ�����ȥ��һ��������
		//��������ֻҪ����������Ҫ������ˡ������е���֡�
		{
			//printf("insert: v=%d p=%d\n", mat[j].v, mat[j].p);
			tr.insert(mat[j].p);//����AVL���С�ע�⣬AVL��insert�㷨�иĶ������ҵ���֮��ýڵ��num+1����������½ڵ�
			//printf("insert%d num=%d\n", mat[j].p, in->num);
			j++;
		}
		//�������ڵ�ǰ�����ҵ���������i�ŵĲ�����p��С�Ĳ���
		ans += (long long) tr.take(bri[i].p);
	}
	printf("%lld", ans);

}
