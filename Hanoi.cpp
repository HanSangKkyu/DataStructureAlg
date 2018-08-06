#include<iostream>
using namespace std;

int hanoi(int n, char x, char y, char z)
{
	if (n == 1)
	{
		cout << 1 << "번째 원반을" << x << "에서 " << y << "로 이동" << endl;
		return 1;
	}
	int num = 0;
	num += hanoi(n - 1, x, z, y);
	cout << n << "번째 원반을" << x << "에서 " << y << "로 이동" << endl;
	num++;
	num += hanoi(n - 1, z, y, x);
	return num;
}

int main()
{
	cout <<"최소 이동은 "<< hanoi(4, 'a', 'b', 'c')<<"번 입니다."<<endl;
}