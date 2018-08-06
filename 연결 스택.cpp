#include <iostream>
using namespace std;
class Node {
public:
	int a;
	Node* n;
};
class Stack {
public:
	Stack();
	void push(int x);
	void pop();
	void showState();
private:
	Node * h;
};

int main()
{
	Stack s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);
	s.showState();
	cout << "--------------------" << endl;
	s.pop();
	s.pop();
	s.showState();
}

Stack::Stack()
{
	h = NULL;
}

void Stack::push(int x)
{
	Node * n = new Node;
	n->a = x;
	n->n = h;
	h = n;
	
}

void Stack::pop()
{
	Node*p = h;
	h = h->n;
	delete p;
}

void Stack::showState()
{
	Node *p = h;
	while (p != NULL)
	{
		cout << p->a << " ";
		p = p->n;
	}
	cout << endl;
}
