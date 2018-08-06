//2017-05-06 건국대학교 소프트웨어학과 201611244 한상규
//용어 설명
//*경계 : 더미노드, 내가 보고있는 레벨보다 높은 레벨을 가지고 있는 노드
#include<iostream>
#include<Windows.h>
using namespace std;

void gotoxy(int x, int y)//스킬리스트 예쁘게 출력하려고 gotoxy씁니다.
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

class Node {
public:
	int level;//노드가 현재 몇 레벨인지 저장한다. 같은 숫자를 저장하고 있는 노드들은 모두 같은 레벨값을 갖는다.
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
	int topLevel;//현재까지 만들어진 레벨의 최댓값
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
	Node* n1 = new Node;//더미노드
	Node* n2 = new Node;//더미노드
	n1->num = -2147483648;//int형 으로 표현할 수 있는 최솟값
	n2->num = 2147483647;//int형 으로 표현할 수 있는 최댓값
	n1->level = 0;
	n2->level = 0;
	n1->right = n2;
	n1->down = head;
	head = n1;
	n2->left = n1;
	topLevel++;//새로운 레벨이 만들어졌으니깐 레벨 최댓값을 증가시킨다.
}

int SkipList::search(int a, Node**p)
{
	*p = head->right;

	//level이 1이상인 애들
	while (*p != NULL && (*p)->down != NULL)
	{
		if ((*p)->num == a)
			return (*p)->num;//찾음
		else if ((*p)->num > a)
			*p = (*p)->down->left;
		else
			*p = (*p)->down->right;
	}

	//level 1에 도착해서
	if ((*p)->num == a)
		return (*p)->num;
	else if ((*p)->num > a)
	{
		while (!((*p)->left->num < a&&a < (*p)->num))
		{
			*p = (*p)->left;
			if ((*p)->num == a)
				return (*p)->num;//찾음
		}
	}
	else if ((*p)->num < a)
	{
		while (!((*p)->num < a && a < (*p)->right->num))
		{
			*p = (*p)->right;
			if ((*p)->num == a)
				return (*p)->num;//찾음
		}
	}

	return -1;//못 찾음

}

void SkipList::insert(int a)
{
	if (head == NULL)
		creatLevel();//위에 레벨이 없으면 새로운 레벨을 만든다

	Node*p;//내가 삽입할 위치를 가르키는 포인터

	//삽입할 노드 생성
	Node*n = new Node;
	n->num = a;

	//1. 노드 삽입
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

	//2. 규칙에 맞게 정리하기
	int checkLevel = 1;//현재 비교하고있는 레벨이 몇인지 확인하기 위한 변수
	int sameLevelNodeNum;
	while (1)
	{
		sameLevelNodeNum = 1;//같은 레벨을 가지고 있는 노드가 몇개인지 저장하는 변수
		if (p->left != NULL)
		{
			while (p->left->level == checkLevel)
			{
				if (p->level != checkLevel&&p->right != NULL)//p가 원래부터 경계를 가르키고 있을 경우를 대비해서 
					p = p->right;
				else
					p = p->left;//p가 왼쪽 경계의 오른쪽 노드를 가르키게 한다.
			}
		}
		else if (p->level != checkLevel)//p가 왼쪽 더미노드를 가르키고 있는 경우를 대비한다.
			p = p->right;
		//경계사이에 같은 레벨을 가지고 있는 노드의 개수를 센다.
		while (p->right->level == checkLevel)
		{
			sameLevelNodeNum++;
			p = p->right;
		}


		if (sameLevelNodeNum == 3)//경계사이에 같은 레벨을 갖는 노드가 3개 존재하면
		{
			//중간값 복사노드만들기
			Node*copy = new Node;
			copy->num = p->left->num;
			if (topLevel == checkLevel)
			{
				creatLevel();//레벨 생성
			}

			copy->down = p->left;
			//같은 레벨로 만들어주기
			p = copy;
			while (p != NULL)
			{
				p->level = checkLevel + 1;
				p = p->down;
			}
			checkLevel++;//다음 레벨을 검사한다.

			//올려주는 노드가 들어갈 위치를 찾기위해 헤드의 레벨을 찾는다.
			p = head;//p가 헤드를 가르키게 한다.

			while (p->right->level != checkLevel && p->right->level != 0)//p가 내가 보고 있는 레벨의 왼쪽 더미노드를 가르키게 한다.
			{
				p = p->down;
			}
			while (!(p->num < copy->num&&copy->num < p->right->num))
				p = p->right;

			//윗 레벨로 올라간 중간값의 복사노드를 연결시켜준다.
			p->right->left = copy;
			copy->right = p->right;
			copy->left = p;
			p->right = copy;
		}
		else//경계사이에 같은 레벨을 갖는 노드가 3개가 아니면 insert종료
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
