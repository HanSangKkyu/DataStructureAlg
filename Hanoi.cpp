#include<iostream>
using namespace std;

int hanoi(int n, char x, char y, char z)
{
	if (n == 1)
	{
		cout << 1 << "��° ������" << x << "���� " << y << "�� �̵�" << endl;
		return 1;
	}
	int num = 0;
	num += hanoi(n - 1, x, z, y);
	cout << n << "��° ������" << x << "���� " << y << "�� �̵�" << endl;
	num++;
	num += hanoi(n - 1, z, y, x);
	return num;
}

int main()
{
	cout <<"�ּ� �̵��� "<< hanoi(4, 'a', 'b', 'c')<<"�� �Դϴ�."<<endl;
}