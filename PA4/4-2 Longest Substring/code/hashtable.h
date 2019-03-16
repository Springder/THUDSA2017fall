/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once
#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "Dictionary.h" //����ʵ�ADT
#include "Bitmap.h" //����λͼ
#include "release.h"
#define mod 2128733
#define base 32
#define base2 13
#define mod2 19260817
#define LL long long
//#include <string.h>

LL mul(LL a, LL b) //�������㷨�п�����������long long��Χ�ģ�����mul����
{
	LL ans = 0;
	while (b)
	{
		if (b & 1) ans = (ans + a) % mod;
		a = (a + a) % mod;
		b = b >> 1;
	}
	return ans;
}

LL Pow(int n, int m) //�������㷨
{
	LL a = n;
	LL b = m;
	LL result = 1;
	LL x = a % mod;
	while (b)
	{
		if (b & 1) result = mul(result, x) % mod;
		x = mul(x, x) % mod;
		b = b >> 1;
	}
	return result;
}

LL mul2(LL a, LL b) //�������㷨�п�����������long long��Χ�ģ�����mul����
{
	LL ans = 0;
	while (b)
	{
		if (b & 1) ans = (ans + a) % mod2;
		a = (a + a) % mod2;
		b = b >> 1;
	}
	return ans;
}

LL Pow2(int n, int m) //�������㷨
{
	LL a = n;
	LL b = m;
	LL result = 1;
	LL x = a % mod2;
	while (b)
	{
		if (b & 1) result = mul(result, x) % mod2;
		x = mul(x, x) % mod2;
		b = b >> 1;
	}
	return result;
}

static size_t hashCode2(char s[], int mid, int st) { //���ɿ�ʼ��mid�����ַ����Ķ���ʽɢ����
	int h = 0; //ɢ����
	for (int i = st; i < st+mid; i++) //�������ң��������ÿһ�ַ�
	{
		h = (h*base2 + s[i]) % mod2;
	}
	return (size_t)h;
}

int primeNLT(int c, int n, char* file) { //����file�ļ��еļ�¼����[c, n)��ȡ��С������
	Bitmap B(file, n); //file�Ѿ���λͼ��ʽ����¼��n���ڵ��������������ֻҪ
	while (c < n) //��c��ʼ����λ��
		if (B.test(c)) c++; //���ԣ�����
		else return c; //�����׸����ֵ�����
		return c; //��û������������������n��ʵ���в�����˼򻯴���
}

template <typename K, typename V> struct Entry { //����ģ����
	K key; V value; //�ؼ��롢��ֵ
	Entry(K k = K(), V v = V()) : key(k), value(v) {}; //Ĭ�Ϲ��캯��
	Entry(Entry<K, V> const& e) : key(e.key), value(e.value) {}; //���ڿ�¡�Ĺ��캯��
	bool operator< (Entry<K, V> const& e) { return key <  e.key; }  //�Ƚ�����С��
	bool operator> (Entry<K, V> const& e) { return key >  e.key; }  //�Ƚ���������
	bool operator== (Entry<K, V> const& e) { return key == e.key; } //�е���������
	bool operator!= (Entry<K, V> const& e) { return key != e.key; } //�е�����������
}; //�����ڱȽ������е������Ӵ����󣬲����ϸ����ִ��������Ӧ�Ĺؼ���

static size_t hashCode(char c) { return (size_t)c; } //�ַ�
static size_t hashCode(int k) { return (size_t)k; } //�����Լ���������
static size_t hashCode(long long i) { return (size_t)((i >> 32) + (int)i); }

static size_t hashCode(char s[], int mid = NULL, int st=NULL) { //���ɿ�ʼ��mid�����ַ����Ķ���ʽɢ����
	int h = 0; //ɢ����
	if (!mid) mid = strlen(s); //���û�����Ƴ��ȣ���ô����ȫ������
	if (!st) st = 0;
	for (int i = st; i < st + mid; i++) //�������ң��������ÿһ�ַ�
	{
		h = (h*base + s[i]) % mod;
	}
	return (size_t)h; 
} 


//static size_t hashCode(char s[], int mid, int st, static size_t formerHC)
////����ʽȡģhash
////mid ���м�ֵ��Ҳ����Ҫ�ҵĳ���
////st�ǵ�ǰ��ʼ��
////formerHC����һ���ַ�����hashcode
//{
//	int h = 0;
//	int head = 0;
//	return (size_t)h;
//}



template <typename K, typename V> //key��value
class Hashtable : public Dictionary<K, V> { //����Dictionary�ӿڵ�Hashtableģ����
   ///*DSA*/friend class UniPrint;
private:
   Entry<K, V>** ht; //Ͱ���飬��Ŵ���ָ��
   int M; //Ͱ��������
   int N; //��������
   Bitmap* lazyRemoval; //����ɾ�����
#define lazilyRemoved(x)  (lazyRemoval->test(x))
#define markAsRemoved(x)  (lazyRemoval->set(x))
protected:
   int probe4Hit ( const K& k ); //�عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ
   int probe4Free ( const K& k ); //�عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ
   void rehash(); //��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
public:
   Hashtable ( int c = 8 ); //����һ��������С��c��ɢ�б�Ϊ������ʱѡ�ý�С��Ĭ��ֵ��
   ~Hashtable(); //�ͷ�Ͱ���鼰���и����ǿգ�Ԫ����ָ��Ĵ���
   int size() const { return N; } // ��ǰ�Ĵ�����Ŀ
   bool put ( K, V ); //���루��ֹ��ͬ�������ʿ���ʧ�ܣ�
   V* get ( K k ); //��ȡ
   bool remove ( K k ); //ɾ��
};

template <typename K, typename V> int Hashtable<K, V>::probe4Hit(const K& k) {
	int r = hashCode(k) % M; //����ʼͰ�������෨ȷ��������
							 //*DSA*/printf(" ->%d", r);
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r)))
		r = (r + 1) % M; //�ز�����������̽���������г�ͻ��Ͱ���Լ�������ɾ����ǵ�Ͱ
	return r; //�����߸���ht[r]�Ƿ�Ϊ�գ������жϲ����Ƿ�ɹ�
}

template <typename K, typename V> int Hashtable<K, V>::probe4Free(const K& k) {
	int r = hashCode(k) % M; //����ʼͰ�������෨ȷ��������
							 //*DSA*/printf(" ->%d", r); //�׸���̽��Ͱ��Ԫ��ַ
	while (ht[r]) r = (r + 1) % M; //�ز�������Ͱ��̽��ֱ���׸���Ͱ�������Ƿ��������ɾ����ǣ�
								   //*DSA*/   while (ht[r]) { r = (r+1) % M; printf(" ->%d", r); } printf("\n");
	return r; //Ϊ��֤��Ͱ�����ҵ���װ�����Ӽ�ɢ�б���Ҫ��������
}

template <typename K, typename V> void Hashtable<K, V>::rehash() {
	int old_capacity = M; Entry<K, V>** old_ht = ht;
	M = primeNLT(2 * M, 1048576, "prime-1048576-bitmap.txt"); //�������ټӱ�
	N = 0; ht = new Entry<K, V>*[M]; memset(ht, 0, sizeof(Entry<K, V>*) * M); //��Ͱ����
	release(lazyRemoval); lazyRemoval = new Bitmap(M); //�¿�����ɾ����Ǳ���ͼ
													   //*DSA*/printf("A bucket array has been created with capacity = %d\n\n", M);
	for (int i = 0; i < old_capacity; i++) //ɨ��ԭͰ����
		if (old_ht[i]) //���ǿ�Ͱ�еĴ�����һ
			put(old_ht[i]->key, old_ht[i]->value); //�������µ�Ͱ����
	release(old_ht); //�ͷ�ԭͰ���顪����������ԭ�ȴ�ŵĴ�������ת�ƣ���ֻ���ͷ�Ͱ���鱾��
}

template <typename K, typename V> Hashtable<K, V>::Hashtable(int c) { //����ɢ�б�����Ϊ
	M = primeNLT(c, 1048576, "prime-1048576-bitmap.txt"); //��С��c������M
	N = 0; ht = new Entry<K, V>*[M]; //����Ͱ���飨����˶�����ɹ�������ʼװ������ΪN/M = 0%
	memset(ht, 0, sizeof(Entry<K, V>*) *M); //��ʼ����Ͱ
	lazyRemoval = new Bitmap(M); //����ɾ����Ǳ���ͼ
								 //*DSA*/printf("A bucket array has been created with capacity = %d\n\n", M);
}

template <typename K, typename V> Hashtable<K, V>::~Hashtable() { //����ǰ�ͷ�Ͱ���鼰�ǿմ���
	for (int i = 0; i < M; i++) //��һ����Ͱ
		if (ht[i]) release(ht[i]); //�ͷŷǿյ�Ͱ
	release(ht); //�ͷ�Ͱ����
	release(lazyRemoval); //�ͷ�����ɾ�����
}

template <typename K, typename V> bool Hashtable<K, V>::put(K k, V v) { //ɢ�б��������
	if (ht[probe4Hit(k)]) return false; //��ͬԪ�ز����ظ�����
	int r = probe4Free(k); //Ϊ�´����Ҹ���Ͱ��ֻҪװ�����ӿ��Ƶõ�����Ȼ�ɹ���
	ht[r] = new Entry<K, V>(k, v); ++N; //���루ע�⣺����ɾ��������踴λ��
	if (N * 2 > M) rehash(); //װ�����Ӹ���50%����ɢ��
	return true;
}

template <typename K, typename V> V* Hashtable<K, V>::get(K k) //ɢ�б���������㷨
{
	int r = probe4Hit(k); 
	return ht[r] ? &(ht[r]->value) : NULL;
} //��ֹ������keyֵ��ͬ

template <typename K, typename V> bool Hashtable<K, V>::remove(K k) { //ɢ�б����ɾ���㷨
	int r = probe4Hit(k); if (!ht[r]) return false; //��Ӧ����������ʱ���޷�ɾ��
	release(ht[r]); ht[r] = NULL; markAsRemoved(r); N--; return true;
	//�����ͷ�Ͱ�д�������������ɾ����ǣ������´�������
}