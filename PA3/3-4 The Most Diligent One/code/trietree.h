#include <iostream>
#include "vector.h"
int max_num = 0; //��¼�����ִ�����ÿ��num�����仯����֮����max_num���������ȫ������
char* max_str = new char[8];
int len;
//void strcopy(string *a, string b)
//{
//	string *a = new string();
//	for (int i = 0; i < b.length(); i++)
//	{
//		a[i] = b[i];
//	}
//}
class Node {
private:
	char mContent; //������ַ�
	bool mMarker;//��Ǵ���
	Vector<Node*> mChildren;  //��һ���ַ���㣬ע������������
public:
	Node() { mContent = ' '; mMarker = false; }
	~Node() {}
	char content() { return mContent; }
	void setContent(char c) { mContent = c; }
	bool wordMarker() { return mMarker; }
	void setWordMarker() { mMarker = true; } 
	Node* findChild(char c);
	void appendChild(Node* child) { mChildren.insert(child); }
	Vector<Node*> children() { return mChildren;}
	int num; //��¼�������
};

class Trie {
public:
	Trie() {root = new Node();}
	~Trie() {} //��������
	void addWord(char* s, int length);
	//bool searchWord(string s);
	//void deleteWord(string s);
private:
	Node* root;
};

Node* Node::findChild(char c)
{
	for (int i = 0; i < mChildren.size(); i++)
	{
		Node* tmp = mChildren[i];
		if (tmp->content() == c) { return tmp; }
	}
	return NULL;
}

void Trie::addWord(char* s, int length)
{
	Node* current = root;
	if (s[0] == 0) //�ַ�Ϊ��
	{
		current->setWordMarker(); // an empty word
		return;
	}
	for(int i=0;i<length;i++)
	{
		Node* child = current->findChild(s[i]);
		if (child != NULL) { current = child; } //�ҵ���i���ַ���������һ�����㣩
		else //�����ں��������һ���ַ�
		{
			Node* tmp = new Node();
			tmp->setContent(s[i]);
			current->appendChild(tmp);
			current = tmp;
		}
		if (i == length - 1)
		{
			if (current->wordMarker()) //����Ѿ��иô���
			{
				current->num++;//����+1
				if (current->num > max_num)
				{
					for (int i = 0; i < length; i++)
					{
						max_str[i] = s[i];
					}
					max_num =current->num;
					len = length;
				}
			}
			else
			{
				current->setWordMarker();
				current->num = 1;
				if (current->num > max_num)
				{
					for (int i = 0; i < length; i++)
					{
						max_str[i] = s[i];
					}
					max_num = current->num;
					len = length;
				}
			}//�����Ǹô�����ִ���Ϊ1
		}
	}
}

//bool Trie::searchWord(string s)
//{
//	Node* current = root;
//	while (current != NULL)
//	{
//		for (int i = 0; i < s.length(); i++)
//		{
//			Node* tmp = current->findChild(s[i]);
//			if (tmp == NULL)
//				return false;
//			current = tmp;
//		}
//		//���ܼ�����current�������һ��
//		printf("num=%d\n", current->num);
//		return current->wordMarker();
//	}
//	return false;
//}