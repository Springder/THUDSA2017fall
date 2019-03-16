#include <iostream>
#include <string.h>
//#include "bitmap.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int EmployeeCode[10000001] = { -1 }; //�洢Ա������
typedef int Rank;
class Bitmap { //λͼBitmap�ࣺ�Կռ���Ϊ��������ʡ��ʼ��ʱ�䣨��������룬��֧��ɾ����
private:
	Rank* F; Rank N; //��ģΪN������F����¼[k]����ǵĴ��򣨼�����ջT[]�е��ȣ�
	Rank* T; Rank top; //����ΪN��ջT����¼����Ǹ�λ�ȵ�ջ���Լ�ջ��ָ��

protected:
	inline bool valid(Rank r) { return (0 <= r) && (r < top); }
	inline bool erased(Rank k) //�ж�[k]�Ƿ�������ǹ����Һ����ֱ����
	{
		return valid(F[k]) && !(T[F[k]] + 1 + k);
	} //����Լ����T[ F[k] ] = - 1 - k

public:
	Bitmap(Rank n = 8) //��ָ������Ĭ�ϣ���ģ��������ͼ��Ϊ������ʱѡ�ý�С��Ĭ��ֵ��
	{
		N = n; F = new Rank[N]; T = new Rank[N]; top = 0;
	} //��O(1)ʱ������ʽ�س�ʼ��
	~Bitmap() { delete[] F; delete[] T; } //����ʱ�ͷſռ�

										  // �ӿ�
	inline void set(Rank k) { //����
		if (test(k)) return; //�����Ѵ���ǵ�λ
		if (!erased(k)) F[k] = top++; //��ϵ���α�ǣ��򴴽���У�黷
		T[F[k]] = k; //��ϵ������Ǻ��������ָ�ԭУ�黷
	}
	inline void clear(Rank k) //ɾ��
	{
		if (test(k)) T[F[k]] = -1 - k;
	} //���Բ�����ǵ�λ
	inline bool test(Rank k) //����
	{
		return valid(F[k]) && (k == T[F[k]]);
	}
	inline void reset() //��λ
	{
		top = 0;
	}
};
int main() {
	//#ifndef _OJ_
	//	freopen("input.txt", "r", stdin);
	//	freopen("output.txt", "w", stdout);
	//#endif
	int n, m;
	// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	scanf("%d\n%d", &n, &m);
	Bitmap bitmap(n);
	memset(EmployeeCode, 0xff, (n + 1) * sizeof(int));
	char buf[8];
	int cmd1, cmd2;
	int output = 0;
	int working = 0; //��¼�����ϰ��Ա������
	for (int i = 0; i < m;i++)
	{
		// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
		// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
		scanf("%s", buf);
		switch (buf[0])
		{
		case 'I':
		{
			// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
			// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
			scanf("%d%d", &cmd1, &cmd2);
			if (!bitmap.test(cmd1)) //���δ��¼
			{
				bitmap.set(cmd1);
				working++;
			}
			EmployeeCode[cmd1] = cmd2; //���۵�¼���Ըı�code
			break;
		}
		case 'O':
		{
			// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
			// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
			scanf("%d", &cmd1);
			if (bitmap.test(cmd1)) //����ѵ�¼����ע��
			{
				bitmap.clear(cmd1);
				working--;
				EmployeeCode[cmd1] = -1;
			}
			break;
		}
		case 'C':
		{
			bitmap.reset(); //��λ
			working = 0;
			break;
		}
		case 'N':
		{
			output += working;
			break;
		}
		case 'Q':
		{
			// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
			// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
			scanf("%d", &cmd1);
			if (bitmap.test(cmd1))
				output += EmployeeCode[cmd1];
			else
				output += -1;
			break;
		}
		default: break;
		}
	}
	// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	// setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	printf("%d", output);
	return 0;
}