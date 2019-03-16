#pragma once
/*K��MëPƬ�㷨*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define printString(s) { for (size_t m = strlen(s), k = 0; k < m; k++) printf("%c", (s)[k]); printf("\n"); }

int* buildNext(char const* P) { //����ģʽ��P��next���Ľ��汾��. P is pattern
	size_t m = strlen(P), j = 0; //��������ָ��
	int* N = new int[m]; //next��
	int t = N[0] = -1; //ģʽ��ָ��
	while (j < m - 1)
		if (0 > t || P[j] == P[t]) { //ƥ��
			N[j] = (P[++j] != P[++t] ? t : N[t]); //ע��˾���δ�Ľ�֮ǰ������
		}
		else //ʧ��
			t = N[t];
	return N;
}

int match(char const* P, char* T)
{
	int *next = buildNext(P);
	int n = (int)strlen(T), i = 0;
	int m = (int)strlen(P), j = 0;
	while (j < m && i < n)
	{
		if (0 > j || T[i] == P[j])
		{
			i++;
			j++;
		}
		else j = next[j];
	}
	delete[] next;
	return i - j;
}