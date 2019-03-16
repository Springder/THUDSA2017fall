#include <iostream>
static int binSearch(int *alarm_x, int *alarm_y, int px, int py, int lo, int hi)
{
	while (lo < hi)
	{
		int mi = (hi + lo) >> 1; //�м�
		int ax = alarm_x[mi];
		int ay = alarm_y[mi];
		//Ϊ��ֹ�����long long
		//�ȼ������������˷�Ӧ�ø���
		//Ӧ��ע��miֱ���϶�Ӧ����mi+1����
		//judgeSide < 0ʱ��point�ϸ���ֱ����࣬Ҳ��point����[lo, mi]
		//judgeSide < 0ʱ, point����[mi+1, hi]
		//ע�Ȿ�����Ķ��ֲ��Ҷ�Ӧ��������ұ�����
		long long judegSide = ((long long)px * (long long)py - (long long)(ax - px) * (long long)(ay - py)); 
		if (judegSide > 0)
			lo = mi + 1;
		else if (judegSide < 0)
			hi = mi;
		else return mi+1;//��������ֱ��ʱ��������ӦΪ�������ϸ���࣬�����Ҳ�


		//printf("judgeSide=%d\n", judegSide);
		//printf("	ax ay=%d %d\n", ax, ay);
		//printf("	ay*px + ax*py - ax*ay= %d\n", ay*px + ax*py - ax*ay);
		//printf("	mi=%d hi=%d low=%d\n",mi, hi, lo);
	}
	return lo;
	//while (1 < hi - lo)
	//{
	//	int mi = (hi + lo) >> 1; //�м�
	//	int ax = alarm_x[mi];
	//	int ay = alarm_y[mi];
	//	long long judegSide = ((long long)px * (long long)py - (long long)(ax - px) * (long long)(ay - py));
	//	if (judegSide < 0)
	//		hi = mi;
	//	else
	//		lo = mi;
	//	//else return mi+1;//��������ֱ��ʱ��������ӦΪ�������ϸ���࣬�����Ҳ�

	//	//(judegSide < 0) ? lo = mi + 1 : hi = mi;

	//	//printf("judgeSide=%d\n", judegSide);
	//	//printf("	ax ay=%d %d\n", ax, ay);
	//	//printf("	ay*px + ax*py - ax*ay= %d\n", ay*px + ax*py - ax*ay);
	//	//printf("	mi=%d hi=%d low=%d\n", mi, hi, lo);
	//}
	//return ++lo;
}
int main()
{
#ifndef _OJ_
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int n, m;
	scanf("%d %d", &n, &m);
	int *alarm_x = new int[n];
	int *alarm_y = new int[n];
	int *point_x = new int[m];
	int *point_y = new int[m];
	for (int i = 0; i < n; i++)
	{
		if (scanf("%d %d", &alarm_x[i], &alarm_y[i]) == EOF)
			return 0;
	}
	for (int i = 0; i < m; i++)
	{
		if (scanf("%d %d", &point_x[i], &point_y[i]) == EOF)
			return 0;
	}
	for (int i = 0; i < m; i++)
	{
		int area = binSearch(alarm_x, alarm_y, point_x[i], point_y[i], 0, n);
		printf("%d\n", area);
	}
}
