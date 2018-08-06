#include<iostream>
using namespace std;

class Node {
public:
	int a;
	Node*n;
};

class LinkedList {
public:
	LinkedList();
	~LinkedList();
	int search(int x, Node**p, Node**l);
	void Insert(int x);
	void Delete(int x, Node**q);
private:
	Node*head;

};

int main()
{
	LinkedList l;
	l.Insert(1);
l.Insert(3);
	l.Insert(2);
	

}

LinkedList::LinkedList()
{
	head = NULL;
}

LinkedList::~LinkedList()
{
	/*Node*l;
	l = head;
	while (l != NULL)
	{
		delete l;
		l = l->n;
		delete l;
	}*/
}

int LinkedList::search(int x, Node ** p, Node ** l)
{
	*p = NULL;
	*l = head;
	while (*l != NULL)
	{
		if ((*l)->a == x)
			return 1;
		else if ((*l)->a > x)
			return 0;
		else {
			*p = *l;
			*l = (*l)->n;
		}
	}
	return 0;
}

void LinkedList::Insert(int x)
{
	Node*p, *l;
	if (search(x, &p, &l) == 0)
	{
		Node*n = new Node;
		n->a = x;
		if (p == NULL)head = n;
		else p->n = n;
		if (l == NULL)n->n = NULL;
		else n->n = l;
	}
}

void LinkedList::Delete(int x, Node ** q)
{
	Node*p, *l;
	if (search(x, &p, &l) == 1)
	{
		if (p == NULL)head = l->n;
		else p->n = l->n;
		*q = l;
		delete *q;
	}
}
