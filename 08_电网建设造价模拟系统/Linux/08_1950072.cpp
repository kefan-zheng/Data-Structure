#include<iostream>
#include"08_1950072.h"

using namespace std;

const int Maxn = 100000000;
const int MaxVertices = 10;
const int MaxEdges = 45;

//边结点，存储最小生成树中的边信息
class EdgeNode {
	friend class Graph;
private:
	string head;
	string tail;
	int cost;
public:
	EdgeNode() { head = tail = "0"; cost = 0; };
	~EdgeNode() {};
};

class Graph {
	friend class PowerSystem;
private:
	//动态数组，用于存放顶点
	string* Vertices;
	//邻接矩阵存放边
	int **Edge;
	//顺序表存放最小生成树
	MyVector<EdgeNode> MinSpanT;
	//图顶点的数量
	int Verticesnum;
public:
	Graph() 
	{ 
		Vertices = new string[MaxVertices];
		Edge = new int* [MaxVertices];
		for (int i = 0; i < MaxVertices; i++)
		{
			Edge[i] = new int[MaxVertices];
			for (int j = 0; j < MaxVertices; j++)
			{
				Edge[i][j] = Maxn;
			}
		}
		Verticesnum = MaxVertices;
	};
	~Graph() {};
	//设置顶点数量
	void SetVerticesnum(int num){ Verticesnum = num; }
	//通过名字找顶点编号
	int FindV(string x);
	//获得边权值
	int GetEdge(string start, string end);
	//电网系统运行
	void Run();
	//创建顶点
	void CreateVertices();
	//添加边
	void AddEdges();
	//构造最小生成树
	void CreateMinSpanT();
	//打印最小生成树
	void PrintMinSpanT();
};

int Graph::FindV(string x)
{
	for (int i = 0; i < Verticesnum; i++)
	{
		if (x == Vertices[i])
		{
			return i;
		}
	}
	return -1;
}

int Graph::GetEdge(string start, string end)
{
	int u = FindV(start);
	int v = FindV(end);
	if (u != -1 && v != -1)
	{
		return Edge[u][v];
	}
	return -1;
}


//电网系统运行
void Graph::Run()
{
	char option = 'A';
	cout << "**          电网造价模拟系统            **" << endl
	     << "==========================================" << endl
	     << "**          A---创建电网顶点            **" << endl
	     << "**          B---添加电网的边            **" << endl
	     << "**          C---构造最小生成树          **" << endl
	     << "**          D---显示最小生成树          **" << endl
	     << "**          E---退出程序                **" << endl
	     << "==========================================" << endl;
	while (option != 'E')
	{
		cout << "请选择操作：";
		cin >> option;
		switch (option)
		{
		case'A':CreateVertices(); break;
		case'B':AddEdges(); break;
		case'C':CreateMinSpanT(); break;
		case'D':PrintMinSpanT(); break;
		case'E':break;
		default:option = 'A'; cout << "未知操作码，请重新选择！" << endl;
		}
	}
	cout << "程序已退出！" << endl;
}

//创建顶点
void Graph::CreateVertices()
{
	int verticesnum; string verticesname;
	cout << "请输入顶点的个数：";
	cin >> verticesnum;
	Vertices = new string[verticesnum];
	Edge = new int*[verticesnum];
	for (int i = 0; i < verticesnum; i++)
	{
		Edge[i] = new int[verticesnum];
		for (int j = 0; j < verticesnum; j++)
		{
			Edge[i][j] = Maxn;
		}
	}
	SetVerticesnum(verticesnum);
	cout << "请依次输入各顶点的名称：" << endl;
	for (int i = 0; i < verticesnum; i++)
	{
		cin >> verticesname;
		Vertices[i] = verticesname;
	}
	cout << endl;

}

//添加边
void Graph::AddEdges()
{
	cout << "输入？ ？ 0代表结束" << endl;
	string start, end; int value;
	cout << "请输入两个顶点及边：";
	cin >> start >> end >> value;
	while (start != "?" && end != "?")
	{
		int u = FindV(start);
		int v = FindV(end);
		if (u != -1 && v != -1)
		{
			Edge[u][v] = value;
			Edge[v][u] = value;
		}
		else
		{
			cout << "您输入了无效的顶点，请重新输入" << endl;
		}
		cout << "请输入两个顶点及边：";
		cin >> start >> end >> value;
	}
	cout << endl;
}

//构造最小生成树
void Graph::CreateMinSpanT()
{
	string point;
	int startpoint = 0;
	cout << "请输入起始顶点：";
	cin >> point;
	startpoint = FindV(point);
	int verticesnum = Verticesnum;
	int* lowcost = new int[verticesnum];
	int* nearvex = new int[verticesnum];
	for (int i = 0; i < verticesnum; i++)
	{
		if (i != startpoint)
		{
			lowcost[i] = Edge[startpoint][i];
			nearvex[i] = startpoint;
		}
	}
	nearvex[startpoint] = -1;
	EdgeNode temp;//最小生成树结点辅助单元
	for (int i = 1; i < verticesnum; i++)
	{
		int min = Maxn; int v = -1;
		for (int j = 0; j < verticesnum; j++)
		{
			if (nearvex[j] != -1 && lowcost[j] < min)
			{
				v = j; min = lowcost[j];
			}
		}
		if (v>=0)
		{
			temp.head = Vertices[nearvex[v]];
			temp.tail = Vertices[v];
			temp.cost = lowcost[v];
			MinSpanT.push_back(temp);
			nearvex[v] = -1;
			for (int j = 0; j < verticesnum; j++)
			{
				if (nearvex[j] != -1 && Edge[v][j] < lowcost[j])
				{
					lowcost[j] = Edge[v][j];
					nearvex[j] = v;
				}
			}
		}
	}
	cout << "生成Prim最小生成树！" << endl << endl;;
}

void Graph::PrintMinSpanT()
{
	int verticesnum = Verticesnum;
	for (int i = 0; i < verticesnum-1; i++)
	{
		cout << MinSpanT.get_element(i)->GetData().head << "-(" << MinSpanT.get_element(i)->GetData().cost << ")->" << MinSpanT.get_element(i)->GetData().tail<<endl;
	}
	cout << endl;
}

int main()
{
	Graph Estates;
	Estates.Run();
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}
