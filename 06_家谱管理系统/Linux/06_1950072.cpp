//本项目家谱中不支持重名
#include<iostream>
#include<string>
#include"06_1950072.h"
using namespace std;

class FamilyTree;//左长子，右兄弟

//家庭成员类
class FamilyMember {
	friend class FamilyTree;
	friend class Queue;
private:
	string name;
	FamilyMember* child;
	FamilyMember* brother;
	FamilyMember* parent;
public:
	FamilyMember()
	{
		name = '#';
		child = NULL;
		brother = NULL;
		parent = NULL;
	}
	FamilyMember(const string vname)
	{
		name = vname;
		child = NULL;
		brother = NULL;
		parent = NULL;
	}
	~FamilyMember() {};
};

//家谱树类
class FamilyTree {
private:
	FamilyMember* ancestor;
public:
	FamilyTree() { ancestor = NULL; };
	~FamilyTree() {};
	void Init();
	bool SelectOperation();
	bool Find(string vname, FamilyMember* start, FamilyMember*& target);
	void CreateFamily();
	void AddMember();
	void RemovepartFamily();
	void Altername();
	void PrintTree();
};

void FamilyTree::Init()
{
	cout << "**          家谱管理系统            **" << endl;
	cout << "======================================" << endl;
	cout << "**        请选择要执行的操作：      **" << endl;
	cout << "**          A---完善家庭            **" << endl;
	cout << "**          B---添加家庭成员        **" << endl;
	cout << "**          C---解散局部家庭        **" << endl;
	cout << "**          D---更改家庭成员姓名    **" << endl;
	cout << "**          E---退出程序            **" << endl;
	cout << "======================================" << endl;
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string name; cin >> name;
	cout << "此家谱的祖先是：" << name << endl;
	cout << endl;
	ancestor = new FamilyMember(name);
	while (SelectOperation())
	{
		PrintTree();
		cout << endl;
	}
}

bool FamilyTree::SelectOperation()
{
	char option;
	cout << "请选择要执行的操作：";
	cin >> option;
	switch (option)
	{
	case'A':CreateFamily(); return 1;
	case'B':AddMember(); return 1;
	case'C':RemovepartFamily(); return 1;
	case'D':Altername(); return 1;
	case'E':return 0;
	}
	return 0;
}

bool FamilyTree::Find(string vname,FamilyMember* start,FamilyMember*&target)
{
	bool result = false;
	if (start->name == vname)
	{
		result = true; target = start;
	}
	else
	{
		FamilyMember* temp = start->child;
		while (temp != NULL && !(result = Find(vname, temp,target)))
		{
			temp = temp->brother;
		}
	}
	return result;
}

//完善家庭
void FamilyTree::CreateFamily()
{
	while(1)
	{
		string name; int childnum; string childname;
		FamilyMember* temp1 = NULL; FamilyMember* temp2 = NULL;//变量
		FamilyMember* current = NULL;//锁定修改目标位置
		FamilyMember* check = NULL;//检测人名
		cout << "请输入要建立家庭的人的姓名:";
		cin >> name;
		//遍历树找到要新建家庭的人
		if (Find(name, ancestor,current) == 0)
		{
			cout<<"查无此人,请重新操作"<<endl; 
			break;
		};
		temp2 = current;
		cout << "请输入" << name << "的儿女人数:";
		cin >> childnum;
		cout << "请依次输入" << name << "的儿女的姓名:";
		int sign = 0;
		for (int i = 0; i < childnum; i++)
		{
			cin >> childname;
			if (Find(childname, ancestor, check) == 1)
			{
				cout<<"该人名已存在,请重新操作"<<endl;
				sign = 1;
				break;
			};
			temp1 = new FamilyMember(childname);
			temp1->parent = current;
			if (i == 0)
			{
				temp2->child = temp1;
				temp2 = temp2->child;
			}
			else
			{
				temp2->brother = temp1;
				temp2 = temp2->brother;
			}
		}
		if (sign == 1)
		{
			break;
		}
		cout << name << "的第一代子孙是:";
		temp2 = current->child;
		while (temp2 != NULL)
		{
			cout << temp2->name << " ";
			temp2 = temp2->brother;
		}
		cout << endl;
		break;
	}
}

void FamilyTree::AddMember()
{
	while(1)
	{
		string name, childname;
		FamilyMember* current = NULL;
		FamilyMember* check = NULL;
		cout << "请输入要添加儿女的人的姓名:";
		cin >> name;
		if (Find(name, ancestor,current) == 0)
		{
			cout << "查无此人,请重新操作"<<endl;
			break;
		};
		cout << "请输入" << name << "要新添加的儿女的姓名:";
		cin >> childname;
		if (Find(childname, ancestor, check) == 1)
		{
			cout << "该人名已存在,请重新操作"<<endl;
			break;
		};
		FamilyMember* temp = new FamilyMember(childname);
		temp->parent = current;
		if (current->child != NULL)
		{
			current = current->child;
			while (current->brother != NULL)
			{
				current = current->brother;
			}
			current->brother = temp;
		}
		else
		{
			current->child = temp;
		}
		cout << name << "的第一代子孙是：";
		temp = temp->parent->child;
		while (temp != NULL)
		{
			cout << temp->name << " ";
			temp = temp->brother;
		}
		cout << endl;
		break;
	}
}

void FamilyTree::RemovepartFamily()
{
	while(1)
	{
		string name;
		FamilyMember* current = NULL;
		cout << "请输入要解散家庭的人的姓名：";
		cin >> name;
		if (Find(name, ancestor,current) == 0)
		{
			cout << "查无此人,请重新操作"<<endl;
			break;
		};
		FamilyMember* temp = current;
		current = current->parent;
		if (current->child == temp)
		{
			current->child = temp->brother;
		}
		else
		{
			current = current->child;
			while (current->brother == temp)
			{
				current->brother = current->brother->brother;
			}
		}
		cout << "要解散家庭的人是：" << name << endl;
		cout << name << "的第一代子孙是：";
		FamilyMember* temp2;
		FamilyMember* temp3;
		temp3 = temp;
		temp = temp->child;
		delete temp3;
		while (temp != NULL)
		{
			if (temp->brother != NULL)
			{
				temp2 = temp->brother;
				while (temp2 != NULL)
				{
					temp3 = temp2;
					temp2 = temp2->brother;
					cout << temp3->name << " ";
					delete temp3;
				}
			}
			temp3 = temp;
			temp = temp->child;
			cout << temp3->name << " ";
			delete temp3;
		}
		cout << endl;
		break;
	}
}

void FamilyTree::Altername()
{
	while (1)
	{
		string name1, name2;
		FamilyMember* current = NULL;
		FamilyMember* check = NULL;
		cout << "请输入要更改姓名的人的目前姓名：";
		cin >> name1;
		if (Find(name1, ancestor, current) == 0)
		{
			cout << "查无此人,请重新操作"<<endl;
			break;
		};
		cout << "请输入更改后的姓名：";
		cin >> name2;
		if (Find(name2, ancestor, check) == 1)
		{
			cout << "该人名已存在,请重新操作"<<endl;
			break;
		};
		current->name = name2;
		cout << name1 << "已更名为" << name2;
		cout << endl;
		break;
	}
}

void FamilyTree::PrintTree()
{
	MyQueue<FamilyMember> A, B;
	FamilyMember temp ;
	temp.brother = ancestor->brother;
	temp.child = ancestor->child;
	temp.name = ancestor->name;
	temp.parent = ancestor->parent;
	A.EnQueue(temp);
	int cnt = 0;
	while (A.IsEmpty() == 0)
	{
		cout << "第" << cnt << "代：";
		while (A.IsEmpty() == 0)
		{
			cout << A.GetFront()->GetData().name << " ";
			temp.brother = A.GetFront()->GetData().brother;
			temp.child = A.GetFront()->GetData().child;
			temp.name = A.GetFront()->GetData().name;
			temp.parent = A.GetFront()->GetData().parent;
			A.DeQueue();
			FamilyMember* cur = temp.child;
			while (cur != NULL)
			{
				temp.brother = cur->brother;
				temp.child = cur->child;
				temp.name = cur->name;
				temp.parent = cur->parent;
				B.EnQueue(temp);
				cur = cur->brother;
			}
		}
		cout << endl;
		while (B.IsEmpty() == 0)
		{
			temp.brother = B.GetFront()->GetData().brother;
			temp.child = B.GetFront()->GetData().child;
			temp.name = B.GetFront()->GetData().name;
			temp.parent = B.GetFront()->GetData().parent;
			B.DeQueue();
			A.EnQueue(temp);
		}
		cnt++;
	}
}

int main()
{
	FamilyTree xio;
	xio.Init();
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}
