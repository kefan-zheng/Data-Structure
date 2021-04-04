//勇闯迷宫游戏项目
#include<iostream>
#include<string.h>
#include<iomanip>
//#include"MySTL.h"
using namespace std;

const int row = 7;
const int column = 7;

class Maze;

class Point {
	friend class Maze;
private:
	int x, y;
public:
	Point() { x = y = 0; }
	~Point() {};
};

class Maze {
private:
	//迷宫地图
	char map[row][column]{};
	//访问数组
	bool visited[row][column]{};
	//4个方向向量
	Point dir[4];
	//起点终点
	Point start;
	Point end;
public:
	//构造函数，构造迷宫
	Maze()
	{
		//初始化地图和访问数组
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				map[i][j] = '0';
				visited[i][j] = 0;
			}
		}
		//设置障碍物
		int barnum = 30;
		int bar[row * column][2] = {
			{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{1,2},{1,6},{2,0},{2,2},{2,4},{2,5},{2,6},{3,0},
			{3,4},{3,6},{4,0},{4,2},{4,6},{5,0},{5,2},{5,4},{5,6},{6,0},{6,1},{6,2},{6,3},{6,4},{6,6}
		};
		for (int i = 0; i < barnum; i++)
		{
			map[bar[i][0]][bar[i][1]] = '#';
		}
		//设置四个方向向量和起点终点坐标
		dir[0].x = -1; dir[0].y = 0;
		dir[1].x = 0; dir[1].y = 1;
		dir[2].x = 1; dir[2].y = 0;
		dir[3].x = 0; dir[3].y = -1;
		start.x = 0; start.y = 0;
		end.x = 0; end.y = 0;
	};
	//析构函数，清除迷宫
	~Maze() {};
	//个性化初始化迷宫
	bool Init();
	//输出迷宫
	void Display();
	//获取起点信息
	int Getstartx() { return start.x; }
	int Getstarty() { return start.y; }
	//寻找通路
	bool SeekPath(int x,int y);
};

bool Maze::Init()
{
	while (1)
	{
		//个性化初始化
		int num, row2, column2;
		while (1)
		{
			cout << "请输入你想添加的障碍物个数(输入0取消操作):";
			cin >> num;
			if (num <= 0)
			{
				break;
			}
			cout << "请依次输入你想置为障碍物的地图坐标" << endl;
			for (int i = 0; i < num; i++)
			{
				cin >> row2 >> column2;
				if (row2 >= 0 && row2 < row && column2 >= 0 && column2 < column)
				{
					map[row2][column2] = '#';
				}
				else
				{
					cout << "输入坐标不合法，请重新输入！" << endl << endl;
				}
			}
			this->Display();
		}
		//起点终点坐标互换，便于回溯时输出路径
		int x, y;
		cout << "请输入起点坐标(如：0 0)："; cin >> x >> y;
		if (x >= 0 && x < row && y >= 0 && y < column && map[x][y] == '0')
		{
			end.x = x; end.y = y;
		}
		else
		{
			cout << "输入的坐标不规范,请重新输入" << endl;
			return 0;
		}
		cout << "请输入终点坐标(如：0 0)："; cin >> x >> y;
		if (x >= 0 && x < row && y >= 0 && y < column && map[x][y] == '0')
		{
			start.x = x; start.y = y;
		}
		else
		{
			cout << "输入的坐标不规范,请重新输入" << endl;
			return 0;
		}
		break;
	}
	return 1;
}

void Maze::Display()
{
	cout << setiosflags(ios::left);
	cout << setw(10) << " ";
	for (int j = 0; j < column; j++)
	{
		string temp = "0列";
		temp[0] = j + 48;
		cout << setw(10) << temp;
	}
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		string temp = "0行";
		temp[0] = i + 48;
		cout << setw(10) << temp;
		for (int j = 0; j < column; j++)
		{
			cout << setw(10) << map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

bool Maze::SeekPath(int x,int y)
{
	visited[x][y] = 1;
	int nextx, nexty, i;
	if (x == end.x && y == end.y) { return 1; }
	for (i = 0; i < 4; i++)
	{
		nextx = x + dir[i].x;
		nexty = y + dir[i].y;
		if (nextx < 0 || nextx >= row || nexty < 0 || nexty >= column)
		{
			continue;
		}
		if (map[nextx][nexty] == '0' && visited[nextx][nexty] == 0)
		{
			if (SeekPath(nextx, nexty)==1)
			{
				cout << "(" << nextx << "," << nexty << ")-->";
				return 1;
			}
		}
	}
	if(x==start.x&&y==start.y)
	{
		cout << "NO PATH!" << endl;
		return 0;
	}
	return 0;
}

int main()
{
	Maze maze;
	maze.Display();
	if (maze.Init() == 1)
	{
		maze.Display();
		if (maze.SeekPath(maze.Getstartx(), maze.Getstarty()))
		{
			cout << "(" << maze.Getstartx() << "," << maze.Getstarty() << ")" << endl;
		};
	}
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}


//-------------------------------------------------以下为非递归版本---------------------------------------------------//
/*
//坐标类
class Point {
	friend class Maze;
private:
	int x, y;
	int dir;
public:
	Point() { x = y = dir = 0; }
	~Point() {};
};

class Maze {
private:
	//迷宫地图
	char map[row][column]{};
	//访问数组
	bool visited[row][column]{};
	//四个方向向量
	Point dir[4]{};
	//起点终点
	Point start;
	Point end;
public:
	//构造函数，构造迷宫
	Maze()
	{
		//默认初始化
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				map[i][j] = '0';
				visited[i][j] = 0;
			}
		}
		int barnum = 30;
		int bar[row * column][2] = {
			{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{1,2},{1,6},{2,0},{2,2},{2,4},{2,5},{2,6},{3,0},
			{3,4},{3,6},{4,0},{4,2},{4,6},{5,0},{5,2},{5,4},{5,6},{6,0},{6,1},{6,2},{6,3},{6,4},{6,6}
		};
		for (int i = 0; i < barnum; i++)
		{
			map[bar[i][0]][bar[i][1]] = '#';
		}
		//设置四个方向
		dir[0].x = -1; dir[0].y = 0;
		dir[1].x = 0; dir[1].y = 1;
		dir[2].x = 1; dir[2].y = 0;
		dir[3].x = 0; dir[3].y = -1;
		//设置起点终点
		start.x = 0; start.y = 0;
		end.x = 0; end.y = 0;
	};
	//析构函数，清除迷宫
	~Maze() {};
	//个性化初始化迷宫
	bool Init();
	//输出迷宫
	void Display();
	//寻找通路
	void SeekPath();
};

bool Maze::Init()
{
	while (1)
	{
		//个性化初始化
		int num, row2, column2;
		while (1)
		{
			cout << "请输入你想添加的障碍物个数(输入0取消操作):";
			cin >> num;
			if (num <= 0)
			{
				break;
			}
			cout << "请依次输入你想置为障碍物的地图坐标" << endl;
			for (int i = 0; i < num; i++)
			{
				cin >> row2 >> column2;
				if (row2 >= 0 && row2 < row && column2 >= 0 && column2 < column)
				{
					map[row2][column2] = '#';
				}
				else
				{
					cout << "输入坐标不合法，请重新输入！" << endl << endl;
				}
			}
			this->Display();
		}
		//起点终点坐标互换，便于回溯时输出路径
		int x, y;
		cout << "请输入起点坐标(如：0 0)："; cin >> x >> y;
		if (x >= 0 && x < row && y >= 0 && y < column && map[x][y] == '0')
		{
			end.x = x; end.y = y;
		}
		else
		{
			cout << "输入的坐标不规范,请重新输入" << endl;
			return 0;
		}
		cout << "请输入终点坐标(如：0 0)："; cin >> x >> y;
		if (x >= 0 && x < row && y >= 0 && y < column && map[x][y] == '0')
		{
			start.x = x; start.y = y;
		}
		else
		{
			cout << "输入的坐标不规范,请重新输入" << endl;
			return 0;
		}
		break;
	}
	return 1;
}

void Maze::Display()
{
	cout << setiosflags(ios::left);
	cout << setw(10) << " ";
	for (int j = 0; j < column; j++)
	{
		string temp = "0列";
		temp[0] = j + 48;
		cout << setw(10) << temp;
	}
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		string temp = "0行";
		temp[0] = i + 48;
		cout << setw(10) << temp;
		for (int j = 0; j < column; j++)
		{
			cout << setw(10) << map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void Maze::SeekPath()
{
	int nextx, nexty, curx, cury, d;
	visited[start.x][start.y] = 1;
	LinkStack<Point> st; Point tmp;
	tmp.x = start.x; tmp.y = start.y;
	st.Push(tmp);
	while (st.IsEmpty() == 0)
	{
		st.Pop(tmp);
		curx = tmp.x; cury = tmp.y; d = tmp.dir;
		while (d < 4)
		{
			nextx = curx + dir[d].x;
			nexty = cury + dir[d].y;
			if (nextx < 0 || nextx >= row || nexty < 0 || nexty >= column)
			{
				d++;
				continue;
			}
			if (nextx == end.x && nexty == end.y)
			{
				cout << "(" << nextx << "," << nexty << ")";
				cout << "-->(" << curx << "," << cury << ")";
				Node<Point>* temp = st.GetTop();
				while (temp != NULL)
				{
					cout << "-->(" << temp->GetData().x << "," << temp->GetData().y << ")";
					temp = temp->GetNext();
				}
				cout << endl;
				return;
			}
			if (map[nextx][nexty] == '0' && visited[nextx][nexty] == 0)
			{
				visited[nextx][nexty] = 1;
				tmp.x = curx; tmp.y = cury; tmp.dir = d;
				st.Push(tmp);
				curx = nextx; cury = nexty; d = 0;
			}
			else
			{
				d++;
			}
		}
	}
	cout << "NO PATH!" << endl;
}

int main()
{
	Maze maze;
	maze.Display();
	if (maze.Init() == 1)
	{
		maze.Display();
		maze.SeekPath();
	}
	return 0;
}
*/