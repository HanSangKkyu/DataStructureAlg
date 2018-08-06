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
	Point i;//현재 자신의 위치 정보를 가지고 있는 객체
	Point stack[100];//스택
	int stackPointer = 0;//스택포인터

	i.x = 1;
	i.y = 1;

	//맵을 만든다.
	time_t t = time(NULL);
	int map[12][12];
	srand(t);
	//테두리는 1로 채운다.
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
	//맵 안을 만든다.
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			map[i][j] = rand() % 2;
		}
	}
	map[1][1] = 0;//시작점
	map[10][10] = 0;//출발점


	stack[stackPointer] = i;//스택에 현위치 저장
	stackPointer++;//스택포인터을 올려준다.
	map[i.x][i.y] = 2;//지나간 길을 2로 표시해준다.
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
	int check;//길이 막히지않았는지 확인하기 위한 변수
	while (1)
	{
		check = 0;//반복문을 시작할 때마다 0으로 시작한다.
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
			check = 1;//길이 다 막혀있으면 1로 값이 바뀐다.
		}
		if (check == 0)//check가 0일때만 현재 위치정보를 스택에 저장한다.
		{
			stack[stackPointer] = i;
			stackPointer++;
			map[i.x][i.y] = 2;
		}

		//도착지에 도착했는지 확인한다.
		if (i.x == 10 && i.y == 10) {
			cout << "길을 찾았습니다." << endl;
			while (1)
			{
				map[stack[stackPointer - 1].x][stack[stackPointer - 1].y] = 3;//스택에 쌓여있는 위치들을 3으로 구분해준다.
				stackPointer--;
				if (stackPointer == 0)
					break;
			}
			break;
		}

		//길을 찾지 못했을 경우
		if (stackPointer == 0)
		{
			cout << "노답" << endl;
			break;
		}
	}

	//최종 결과 화면을 띄워준다.
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}
