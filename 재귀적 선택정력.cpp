#include <iostream>
using namespace std;

void selectionSort(int* a, const int n, int start)
{
	int j = start;//j�� ���� ���� ���� ����ִ� ��ȣ
	if (start == n)
		return;
	for (int k = start; k < n; k++) {
		if (a[k] < a[j])
			j = k;
	}
	//���� ���� ���� a[j]�� ������ �Ű��ش�.
	int temp = a[start];
	a[start] = a[j];
	a[j] = temp;
	selectionSort(a, n, start + 1);
}

int main()
{
	int arr[10] = { 4,3,5,6,1,2,7,8,0,9 };
	selectionSort(arr, 10, 0);
	for (int i = 0; i < 10; i++)
		cout << arr[i] << " ";
}