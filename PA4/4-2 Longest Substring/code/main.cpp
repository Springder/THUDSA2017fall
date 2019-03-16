#include <iostream>
//#include <cstring>
//#include "hashtable.h"
//#include "KMP.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXN 40000
#include "hashtable.h"

int longerThan(int mid, char *s, int n) //���ȴ��ڵ���mid���Ӵ��ĳ��ִ���
{
	Hashtable<int, int> ht; //keyΪhashcode��valueΪ�ַ�������ʼλ�ã��ȼ��賤��Ϊmid��
	int st = 1;
	LL code = hashCode(s, mid);
	int *times = new int[n - mid + 1]; //��¼���ִ���
	memset(times, 0, sizeof(int) * (n - mid + 1));
	times[0] = 1;
	ht.put((int)code, 0);
	while (st <= n - mid)
	{
		//printf("st=%d %lld\n", st, code);
		//for (int i = st;i < st + mid;i++) printf("%c", s[i]);printf("\n");
		code = (mul((code - (LL)s[st - 1] * Pow(base, mid - 1)), (LL)base) % mod + s[st + mid - 1]) % mod;
		if (code < 0)
			code += mod;
		if (ht.get((int)code))
		{
			LL code2_old = hashCode2(s, mid, *ht.get((int)code));
			LL code2_now = hashCode2(s, mid, st);
			//printf("get st=%d\n", *ht.get((int)code));
			times[*ht.get((int)code)]++;
		}
		else
		{
			ht.put((int)code, st);
			times[st] = 1;
		}
		st++;
	}
	int maxtime = 0; //�����ִ���
	//printf("mid=%d\n", mid);
	for (int i = 0;i <= n - mid;i++)
	{
		//printf("%d ", times[i]);
		if (times[i] > maxtime) maxtime = times[i];
	}
	//printf("\n");

	return maxtime;
}

int findRightest(int mid, char* s, int n, int m) //�������Ϊmid�Ҵ������ڵ���3������
{

	Hashtable<int, int> ht; //keyΪhashcode��valueΪ�ַ�������ʼλ�ã��ȼ��賤��Ϊmid��
	int st = 1;
	LL code = hashCode(s, mid);
	int *times = new int[n - mid + 1]; //��¼���ִ���
	memset(times, 0, sizeof(int) * (n - mid + 1));
	times[0] = 1;
	ht.put((int)code, 0);
	while (st <= n - mid)
	{
		//printf("st=%d %lld\n", st, code);
		//for (int i = st;i < st + mid;i++) printf("%c", s[i]);printf("\n");
		code = (mul((code - (LL)s[st - 1] * Pow(base, mid - 1)), (LL)base) % mod + s[st + mid - 1]) % mod;
		if (code < 0)
			code += mod;
		if (ht.get((int)code))
		{
			//printf("get st=%d\n", *ht.get((int)code));
			times[*ht.get((int)code)]++;
			times[st] = times[*ht.get((int)code)];
		}
		else
		{
			ht.put((int)code, st);
			times[st] = 1;
		}
		st++;
	}

	int ST;
	int maxtime = 0;
	for (int i = 0;i <= n - mid;i++)
	{
		if (times[i] >= m)
		{
			 //maxtime = times[i];
			 ST = i;
		}
	}
	//�����ҳ��˳��ִ������ڵ���m�Ĵ��У�������������
	//���������ɢ����
	int h = 0; //ɢ����
	for (int i = ST; i < ST + mid; i++) //�������ң��������ÿһ�ַ�
	{
		h = (h*base + s[i]) % mod;
	}
	//����ҵ�����
	code = hashCode(s, mid);
	int right = 0;
	st = 1;
	while (st <= n - mid)
	{
		code = (mul((code - (LL)s[st - 1] * Pow(base, mid - 1)), (LL)base) % mod + s[st + mid - 1]) % mod;
		if (code < 0)
			code += mod;
		if ((int)(code - h) == 0) right = st;
		st++;
	}
	return right;
}
int main()
{
#ifndef _OJ_
	freopen("input1.txt", "r", stdin);
		//freopen("output.txt", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while (T-- > 0)
	{
		int m;
		scanf("%d", &m);
		char s[MAXN];
		scanf("%s", s);
		int n = strlen(s);
		int hi = n;
		int lo = 1;
		int mid;
		while (lo < hi)
		{
			mid = (hi + lo) >> 1;
			int maxtime = longerThan(mid, s, n);
			//printf("mid=%d, maxtime=%d\n", mid, maxtime);
			m > maxtime? hi = mid : lo = mid+1;
		}
		if (lo - 1 == 0)
			printf("none\n");
		else
		{
			printf("%d %d\n", lo - 1, findRightest(lo-1, s, n, m));
			//printf("%d\n", lo - 1);
		}
		//printf("maxtime of 5: %d\n", longerThan(5, s, n));
	}
	//printf("%d\n", hashCode(s, strlen(s)));
}
