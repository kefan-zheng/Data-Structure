//本排课软件不支持单双周（每周课表相同）
//规定每周学时不超过35
#include<fstream>
#include<iostream>
#include<iomanip>
#include"MySTL.h"

using namespace std;

//一周总课时
const int MaxCourseTime = 50;
//排课系统支持最大课程数
const int MaxVertices = 100;

//图
//邻接表顶点顺序表中的顶点结点
class Vertex {
	friend class Graph;
	friend class ArrangeSystem;
private:
	//课程对应的数字编号
	int num;
	//课程的相关信息（编号，名称，学时，学期，先修课程，先修课程数量）
	string number, name, learntime, semester;
	string prerequisite[MaxVertices];
	int prenum;
public:
	Vertex() 
	{ 
		num = prenum = 0;
		number = name = learntime = semester = "0";
	};
	~Vertex() {};
};

//邻接表边链表中的边结点
class Edge {
	friend class Graph;
	friend class ArrangeSystem;
private:
	int destnum;
public:
	Edge() { destnum = -1; };
	~Edge() {};
};

//用邻接表存储的图，用来存储所有课程的信息和先修关系
class Graph {
	friend class ArrangeSystem;
private:
	//顶点顺序表存储顶点信息
	MyVector<Vertex>vertextable;
	//邻接表存储边的信息
	MyVector<MyVector<Edge>>edgelist;
	//图顶点的数量
	int vertexnum;
	//count数组，拓扑排序时使用
	int count[MaxVertices]{};
	//visited访问数组，检测某门课程是否已被安排
	bool visited[MaxVertices]{};
public:
	Graph()
	{
		vertexnum = 0;
		for (int i = 0; i < MaxVertices; i++)
		{
			count[i] = 0;
			visited[i] = 0;
		}
	};
	~Graph() {};
	//在邻接表中插入顶点和边的信息
	void InsertVertex(Vertex x);
	void InsertEdge(Vertex x);
	//通过编号获取顶点位置
	int GetVertexNum(string name);
};

void Graph::InsertVertex(Vertex x)
{
	//添加边链表行数
	MyVector<Edge> temp;
	edgelist.push_back(temp);
	//添加顶点
	vertextable.push_back(x);
	vertexnum++;
}

int Graph::GetVertexNum(string namex)
{
	for (int i = 0; i < vertextable.get_size(); i++)
	{
		if (vertextable.get_element(i)->GetData().number == namex)
		{
			return i;
		}
	}
	return -1;
}

void Graph::InsertEdge(Vertex x)
{
	for (int i = 0; i < x.prenum; i++)
	{
		Edge temp;
		temp.destnum = x.num;
		int start = GetVertexNum(x.prerequisite[i]);
		//
		MyVector<Edge> newvector;
		for (int j = 0; j < edgelist.get_element(start)[0].GetData().get_size(); j++)
		{
			newvector.push_back(edgelist.get_element(start)[0].GetData().get_element(j)->GetData());
		}
		newvector.push_back(temp);
		//
		edgelist.get_element(start)->ModifyData(newvector);
	}
	//更新count数组
	count[x.num] = count[x.num] + x.prenum;
}

//排课系统
class ArrangeSystem {
private:
	//所有课程的图表示
	Graph all_courses;
	//存储每个学期的课程
	MyVector<Vertex>schedule[8];
	//生成的8个学期的课表
	int final_schedule[8][5][10]{};
public:
	ArrangeSystem() 
	{ 
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					final_schedule[i][j][k] = -1;
				}
			}
		}
	};
	~ArrangeSystem() {};
	//从文本文件中输入数据
	void Input();
	//将数据输出到文本文件中
	void Output();
	//拓扑排序，并把课程分配到相应的学期中
	void Topologicalsort();
	//将每个学期内的课分配到各个课时，并生成课表
	bool GetFinalSch();
	void InsertCourse(int semester, int j, int courselen);
	bool InsertThree(int semester,int weekday,Vertex x);
	bool InsertTwo(int semester,int weekday, Vertex x);
	bool InsertOne(int semester,int weekday, Vertex x);
};

//输入函数
void ArrangeSystem::Input()
{
	//读取文件
	fstream in;
	in.open("in.txt",ios::in);
	int num = 0;
	char str[1024];
	in.getline(str, 1024);
	while (!in.eof())
	{
		//临时课程变量，辅助输入
		Vertex curcourse;
		//课程数字编号
		curcourse.num = num;
		num++;
		//从文本中按行读取数据并分割字符串
		int cnt=0;
		in >> curcourse.number >> curcourse.name >> curcourse.learntime >> curcourse.semester;
		while (!in.eof())
		{
			if (in.get() != '\n')
			{
				in >> curcourse.prerequisite[cnt];
				cnt++;
			}
			else
			{
				break;
			}
		}
		curcourse.prenum = cnt;
		//---------------------------------------------------------------------------------------//
		//将顶点和边插入图
		//优先处理已确定学期的课程
		switch (curcourse.semester[0])
		{
		case'1':schedule[0].push_back(curcourse); all_courses.visited[curcourse.num] = 1; break;
		case'2':schedule[1].push_back(curcourse); all_courses.visited[curcourse.num] = 1; break;
		case'3':schedule[2].push_back(curcourse); all_courses.visited[curcourse.num] = 1; break;
		case'4':schedule[3].push_back(curcourse); all_courses.visited[curcourse.num] = 1; break;
		case'5':schedule[4].push_back(curcourse); all_courses.visited[curcourse.num] = 1; break;
		case'6':schedule[5].push_back(curcourse); all_courses.visited[curcourse.num] = 1; break;
		case'7':schedule[6].push_back(curcourse); all_courses.visited[curcourse.num] = 1; break;
		case'8':schedule[7].push_back(curcourse); all_courses.visited[curcourse.num] = 1; break;
		default:break;
		}
		//通用插入操作
		all_courses.InsertVertex(curcourse);
		if (curcourse.prenum != 0)
		{
			all_courses.InsertEdge(curcourse);
		}
	}
	in.close();
}

//输出函数
void ArrangeSystem::Output()
{
	ofstream out("out.txt");
	//控制台应用程序打印，方便观察
	for (int i = 0; i < 8; i++)
	{
		cout << setiosflags(ios::left);
		cout << "第" << i + 1 << "学期" <<endl << setw(15) << "星期一" << setw(15) << "星期二"
			<< setw(15) << "星期三" << setw(15) << "星期四" << setw(15) << "星期五" << endl ;
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				int num = final_schedule[i][k][j];
				if (num == -1)
				{
					cout << setw(15) << "/";
				}
				else
				{
					cout << setw(15) << all_courses.vertextable.get_element(num)->GetData().name;
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	//输出到文件中
	out << "请修改字体为新宋体，否则可能出现排版错误！" << endl;
	for (int i = 0; i < 8; i++)
	{
		out << setiosflags(ios::left);
		out << "第" << i + 1 << "学期" << endl << setw(20) << "星期一" << setw(20) << "星期二"
			<< setw(20) << "星期三" << setw(20) << "星期四" << setw(20) << "星期五" << endl;
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				int num = final_schedule[i][k][j];
				if (num == -1)
				{
					out << setw(20) << "/";
				}
				else
				{
					out << setw(20) << all_courses.vertextable.get_element(num)->GetData().name;
				}
			}
			out << endl;
		}
		out << endl;
	}
	out.close();
}

//根据课程学时进行拓扑排序
void ArrangeSystem::Topologicalsort()
{
	for(int semester=0;semester<8;semester++)
	{
		//记录学时并初始化
		int learnedtime=0;
		for (int i = 0; i < schedule[semester].get_size(); i++)
		{
			learnedtime += schedule[semester].get_element(i)->GetData().learntime[0]-48;
		}
		//存储被选中课程，在最后进行入度更新
		MyVector<Vertex>zero;
		for (int i = 0; i < all_courses.vertexnum; i++)
		{
			if (learnedtime >= MaxCourseTime)//学时数已满，进入下一个学期排课
			{
				break;
			}
			if (all_courses.visited[i] == 0)//未确定学期
			{
				if (all_courses.count[i] == 0)//入度为0
				{
					if (learnedtime + all_courses.vertextable.get_element(i)->GetData().learntime[0]-48 <= 35)//未超过学时数
					{
						//更新学时
						learnedtime += all_courses.vertextable.get_element(i)->GetData().learntime[0] - 48;
						//将该课程加入该学期,并进行标记
						Vertex xxxx;
						xxxx = all_courses.vertextable.get_element(i)->GetData();
						schedule[semester].push_back(xxxx);
						all_courses.visited[xxxx.num] = 1;
						//将该课程加入零度表
						zero.push_back(xxxx);
					}
				}
			}
		}
		//对count表进行更新
		for (int i = 0; i < zero.get_size(); i++)
		{
			for (int j = 0; j < all_courses.edgelist.get_element(zero.get_element(i)[0].GetData().num)[0].GetData().get_size(); j++)
			{
				int curvertexnum = all_courses.edgelist.get_element(zero.get_element(i)->GetData().num)->GetData().get_element(j)->GetData().destnum;
				all_courses.count[curvertexnum]--;
			}
		}
	}
}

//插入课程
void ArrangeSystem::InsertCourse(int semester, int j,int courselen)
{
	int weekday = 0;
	if (courselen == 3)
	{
		weekday = 0;
	}
	else if (courselen == 2)
	{
		weekday = 2;
	}
	else if (courselen == 1)
	{
		weekday = 4;
	}
	Vertex curvertex = schedule[semester].get_element(j)->GetData();
	int learntime = schedule[semester].get_element(j)->GetData().learntime[0] - 48;
	while (learntime >= courselen)
	{
		if (courselen == 3 && learntime == 4)
		{
			break;
		}
		int sign = 0;
		for (int fre = 0; fre < 10; fre++)
		{
			bool judge=0;
			if(courselen==3)
			{
				judge = InsertThree(semester, weekday, curvertex);
			}
			else if (courselen == 2)
			{
				judge = InsertTwo(semester, weekday, curvertex);
			}
			else if (courselen == 1)
			{
				judge = InsertOne(semester, weekday, curvertex);
			}
			if (judge==1)
			{
				Vertex newvertex= schedule[semester].get_element(j)->GetData();
				newvertex.learntime[0] -=  courselen;
				schedule[semester].get_element(j)->ModifyData(newvertex);
				learntime -= courselen;
				weekday = (weekday - 3 >= 0) ? (weekday - 3) : (weekday + 2);
				sign = 1;
				break;
			}
			weekday++;
			weekday = weekday % 5;
		}
		if (sign == 0)
		{
			break;
		}
	}
}

bool ArrangeSystem::InsertThree(int semester,int weekday,Vertex x)
{
	if (final_schedule[semester][weekday][2] == -1)
	{
		for (int j = 2; j < 5; j++)
		{
			final_schedule[semester][weekday][j] = x.num;
		}
		return 1;
	}
	if (final_schedule[semester][weekday][7] == -1)
	{
		for (int j = 7; j < 10; j++)
		{
			final_schedule[semester][weekday][j] = x.num;
		}
		return 1;
	}
	return 0;
}

bool ArrangeSystem::InsertTwo(int semester, int weekday,Vertex x)
{
	if (final_schedule[semester][weekday][0] == -1)
	{
		for (int j = 0; j < 2; j++)
		{
			final_schedule[semester][weekday][j] = x.num;
		}
		return 1;
	}
	if (final_schedule[semester][weekday][5] == -1)
	{
		for (int j = 5; j < 7; j++)
		{
			final_schedule[semester][weekday][j] = x.num;
		}
		return 1;
	}
	return 0;
}

bool ArrangeSystem::InsertOne(int semester, int weekday,Vertex x)
{
	for (int j = 0; j < 10; j++)
	{
		if (final_schedule[semester][weekday][j] == -1)
		{
			final_schedule[semester][weekday][j] = x.num;
			return 1;
		}
	}
	return 0;
}

//生成课表
bool ArrangeSystem::GetFinalSch()
{
	Topologicalsort();
	for (int i = 0; i < all_courses.vertexnum; i++)
	{
		if (all_courses.visited[i] == 0)
		{
			cout << "课程输入有误，请检查课程的学期和先修关系!"<<endl;
			return 0;
		}
	}
	for (int semester = 0; semester < 8; semester++)
	{
		//先处理三节的大课，两节次之，一节最末
		for (int turn = 0; turn < 3; turn++)
		{
			for (int j = 0; j < schedule[semester].get_size(); j++)
			{
				if (schedule[semester].get_element(j)->GetData().learntime[0] == 48)
				{
					continue;
				}
				switch (turn)
				{
				case 0:InsertCourse(semester, j, 3); break;
				case 1:InsertCourse(semester, j, 2); break;
				case 2:InsertCourse(semester, j, 1); break;
				}
			}
		}
	}
	return 1;
}

int main()
{
	ArrangeSystem wave;
	wave.Input();
	if (wave.GetFinalSch()==1)
	{
		wave.Output();
	}
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}