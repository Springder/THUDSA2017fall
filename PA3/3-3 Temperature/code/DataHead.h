#pragma once
#define MAXN 50000

struct data {
	int x, y, t; //x����,y����,�¶�
	bool operator >= (const data data2) { return (x > data2.x) || ((x == data2.x) && (y >= data2.y)); } //�жϴ��ڵ��ڣ���x�ϴ�ʱ����x��ȵ���p���ڵ���
	bool operator <= (const data data2) { return (x < data2.x) || ((x == data2.x) && (y <= data2.y)); }
	bool operator == (data data2) { return (x == data2.x) && (y == data2.y); }
	bool operator > (data data2) { return (x > data2.x); }
	bool operator < (data data2) { return (x < data2.x); }

} TP[MAXN]; //