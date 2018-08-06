#include <iostream>
using namespace std;
class Node {
public:
	int a;
	Node* n;
};
class Queue {
public:
	Queue();
	void Insert(int x);
	void Delete();
	void showState();
private:
	Node * h;
	Node * t;
};

int main()
{
	Queue queue;
	queue.Insert(1);
	queue.Insert(2);
	queue.Insert(3);
	queue.Insert(4);
	queue.Insert(5);
	queue.showState();

	cout << "--------------------" << endl;
	queue.Delete();
	queue.Delete();
	queue.showState();
}

Queue::Queue()
{
	h = NULL;
	t = NULL;
}

void Queue::Insert(int x)
{
	Node *n = new Node;
	n->a = x;
	if (h == NULL)
	{
		h = n;
		t = n;
	}
	else
	{
		t->n = n;
		t = n;
	}
}

void Queue::Delete()
{
	Node*p;
	p = h;
	h = h->n;
	delete p;
}

void Queue::showState()
{
	Node *p=h;
	while (p != t->n)
	{
		cout << p->a << " ";
		p = p->n;
	}
	cout << endl;
	
}
