//2017-05-06 �Ǳ����б� ����Ʈ�����а� 201611244 �ѻ��
//��� ����
//*��� : ���̳��, ���� �����ִ� �������� ���� ������ ������ �ִ� ���
#include<iostream>
#include<Windows.h>
using namespace std;

void gotoxy(int x, int y)//��ų����Ʈ ���ڰ� ����Ϸ��� gotoxy���ϴ�.
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

class Node {
public:
	int level;//��尡 ���� �� �������� �����Ѵ�. ���� ���ڸ� �����ϰ� �ִ� ������ ��� ���� �������� ���´�.
	int num;
	Node*left;
	Node*right;
	Node*down;
	Node();
};

class SkipList {
public:
	SkipList();
	void creatLevel();
	int search(int a, Node**p);
	void insert(int a);
	void show();
private:
	Node*head;
	int topLevel;//������� ������� ������ �ִ�
};

int main()
{
	SkipList s;

	s.insert(6);
	s.insert(22);
	s.insert(23);
	s.insert(19);
	s.insert(14);
	s.insert(4);
	s.insert(24);
	s.insert(7);
	s.insert(10);
	s.insert(20);
	s.insert(9);
	s.insert(8);
	s.insert(11);
	s.insert(13);
	s.insert(44);
	s.insert(12);
	s.insert(30);
	s.insert(18);
	s.insert(21);
	s.insert(1);
	s.insert(64);
	s.insert(50);

	s.show();
}

Node::Node()
{
	left = NULL;
	right = NULL;
	down = NULL;
	level = 1;
}

SkipList::SkipList()
{
	head = NULL;
	topLevel = 0;
}

void SkipList::creatLevel()
{
	Node* n1 = new Node;//���̳��
	Node* n2 = new Node;//���̳��
	n1->num = -2147483648;//int�� ���� ǥ���� �� �ִ� �ּڰ�
	n2->num = 2147483647;//int�� ���� ǥ���� �� �ִ� �ִ�
	n1->level = 0;
	n2->level = 0;
	n1->right = n2;
	n1->down = head;
	head = n1;
	n2->left = n1;
	topLevel++;//���ο� ������ ����������ϱ� ���� �ִ��� ������Ų��.
}

int SkipList::search(int a, Node**p)
{
	*p = head->right;

	//level�� 1�̻��� �ֵ�
	while (*p != NULL && (*p)->down != NULL)
	{
		if ((*p)->num == a)
			return (*p)->num;//ã��
		else if ((*p)->num > a)
			*p = (*p)->down->left;
		else
			*p = (*p)->down->right;
	}

	//level 1�� �����ؼ�
	if ((*p)->num == a)
		return (*p)->num;
	else if ((*p)->num > a)
	{
		while (!((*p)->left->num < a&&a < (*p)->num))
		{
			*p = (*p)->left;
			if ((*p)->num == a)
				return (*p)->num;//ã��
		}
	}
	else if ((*p)->num < a)
	{
		while (!((*p)->num < a && a < (*p)->right->num))
		{
			*p = (*p)->right;
			if ((*p)->num == a)
				return (*p)->num;//ã��
		}
	}

	return -1;//�� ã��

}

void SkipList::insert(int a)
{
	if (head == NULL)
		creatLevel();//���� ������ ������ ���ο� ������ �����

	Node*p;//���� ������ ��ġ�� ����Ű�� ������

	//������ ��� ����
	Node*n = new Node;
	n->num = a;

	//1. ��� ����
	if (search(a, &p) == -1)
	{
		if (p->num > a)
		{
			n->left = p->left;
			p->left->right = n;
			n->right = p;
			p->left = n;
		}
		else if (p->num < a)
		{
			n->right = p->right;
			p->right->left = n;
			p->right = n;
			n->left = p;
		}
	}

	//2. ��Ģ�� �°� �����ϱ�
	int checkLevel = 1;//���� ���ϰ��ִ� ������ ������ Ȯ���ϱ� ���� ����
	int sameLevelNodeNum;
	while (1)
	{
		sameLevelNodeNum = 1;//���� ������ ������ �ִ� ��尡 ����� �����ϴ� ����
		if (p->left != NULL)
		{
			while (p->left->level == checkLevel)
			{
				if (p->level != checkLevel&&p->right != NULL)//p�� �������� ��踦 ����Ű�� ���� ��츦 ����ؼ� 
					p = p->right;
				else
					p = p->left;//p�� ���� ����� ������ ��带 ����Ű�� �Ѵ�.
			}
		}
		else if (p->level != checkLevel)//p�� ���� ���̳�带 ����Ű�� �ִ� ��츦 ����Ѵ�.
			p = p->right;
		//�����̿� ���� ������ ������ �ִ� ����� ������ ����.
		while (p->right->level == checkLevel)
		{
			sameLevelNodeNum++;
			p = p->right;
		}


		if (sameLevelNodeNum == 3)//�����̿� ���� ������ ���� ��尡 3�� �����ϸ�
		{
			//�߰��� �����常���
			Node*copy = new Node;
			copy->num = p->left->num;
			if (topLevel == checkLevel)
			{
				creatLevel();//���� ����
			}

			copy->down = p->left;
			//���� ������ ������ֱ�
			p = copy;
			while (p != NULL)
			{
				p->level = checkLevel + 1;
				p = p->down;
			}
			checkLevel++;//���� ������ �˻��Ѵ�.

			//�÷��ִ� ��尡 �� ��ġ�� ã������ ����� ������ ã�´�.
			p = head;//p�� ��带 ����Ű�� �Ѵ�.

			while (p->right->level != checkLevel && p->right->level != 0)//p�� ���� ���� �ִ� ������ ���� ���̳�带 ����Ű�� �Ѵ�.
			{
				p = p->down;
			}
			while (!(p->num < copy->num&&copy->num < p->right->num))
				p = p->right;

			//�� ������ �ö� �߰����� �����带 ��������ش�.
			p->right->left = copy;
			copy->right = p->right;
			copy->left = p;
			p->right = copy;
		}
		else//�����̿� ���� ������ ���� ��尡 3���� �ƴϸ� insert����
			break;
	}
}

void SkipList::show()
{

	Node*phead = head;
	Node*p;
	int x = 0, y = 0;
	while (phead != NULL)
	{
		p = phead->right;
		while (p->level != 0)
		{
			Node*pp = p;
			while (pp->down != NULL)
			{
				pp = pp->down;
				y++;
			}
			while (pp->level != 0)
			{
				x += 3;
				pp = pp->left;
			}
			while (y >= 0)
			{
				gotoxy(x, topLevel - y);
				cout << p->num;
				y--;
			}
			x = 0, y = 0;
			p = p->right;
		}
		phead = phead->down;
	}
	gotoxy(0, 10);

}
