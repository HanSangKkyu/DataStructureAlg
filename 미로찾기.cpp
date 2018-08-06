#include<iostream>
#include<time.h>
#include<cstdlib>
using namespace std;

class Point {
public:
	int x;
	int y;
};
int main()
{
	Point i;//���� �ڽ��� ��ġ ������ ������ �ִ� ��ü
	Point stack[100];//����
	int stackPointer = 0;//����������

	i.x = 1;
	i.y = 1;

	//���� �����.
	time_t t = time(NULL);
	int map[12][12];
	srand(t);
	//�׵θ��� 1�� ä���.
	for (int i = 0; i < 12; i++)
	{
		map[i][0] = 1;
		map[i][11] = 1;
	}
	for (int i = 1; i < 11; i++)
	{
		map[0][i] = 1;
		map[11][i] = 1;
	}
	//�� ���� �����.
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			map[i][j] = rand() % 2;
		}
	}
	map[1][1] = 0;//������
	map[10][10] = 0;//�����


	stack[stackPointer] = i;//���ÿ� ����ġ ����
	stackPointer++;//������������ �÷��ش�.
	map[i.x][i.y] = 2;//������ ���� 2�� ǥ�����ش�.
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
	int check;//���� �������ʾҴ��� Ȯ���ϱ� ���� ����
	while (1)
	{
		check = 0;//�ݺ����� ������ ������ 0���� �����Ѵ�.
		if (map[i.x - 1][i.y - 1] == 0) {
			i.x--;
			i.y--;
		}
		else if (map[i.x][i.y - 1] == 0) {
			i.y--;
		}
		else if (map[i.x + 1][i.y - 1] == 0) {
			i.x++;
			i.y--;
		}
		else if (map[i.x - 1][i.y] == 0) {
			i.x--;
		}
		else if (map[i.x + 1][i.y] == 0) {
			i.x++;
		}
		else if (map[i.x - 1][i.y + 1] == 0) {
			i.x--;
			i.y++;
		}
		else if (map[i.x][i.y + 1] == 0) {
			i.y++;
		}
		else if (map[i.x + 1][i.y + 1] == 0) {
			i.x++;
			i.y++;
		}
		else {
			i = stack[--stackPointer];
			check = 1;//���� �� ���������� 1�� ���� �ٲ��.
		}
		if (check == 0)//check�� 0�϶��� ���� ��ġ������ ���ÿ� �����Ѵ�.
		{
			stack[stackPointer] = i;
			stackPointer++;
			map[i.x][i.y] = 2;
		}

		//�������� �����ߴ��� Ȯ���Ѵ�.
		if (i.x == 10 && i.y == 10) {
			cout << "���� ã�ҽ��ϴ�." << endl;
			while (1)
			{
				map[stack[stackPointer - 1].x][stack[stackPointer - 1].y] = 3;//���ÿ� �׿��ִ� ��ġ���� 3���� �������ش�.
				stackPointer--;
				if (stackPointer == 0)
					break;
			}
			break;
		}

		//���� ã�� ������ ���
		if (stackPointer == 0)
		{
			cout << "���" << endl;
			break;
		}
	}

	//���� ��� ȭ���� ����ش�.
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}
