#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

//学生对象类
class Student {
private:
	//准考证号，姓名，性别，年龄，报考类别
	int Id;
	string Name;
	string Gender;
	int Age;
	string Type;
public:
	Student()
	{
		Id = 0; Name = "0"; Gender = "0"; Age = 0; Type = "0";
	}
	Student(int id, string name, string gender, int age, string type)
	{
		Id = id; Name = name; Gender = gender;
		Age = age; Type = type;
	}
	~Student() {};
	int getStuId(){return this->Id;}
	string getStuName(){return this->Name;}
	string getStuGender(){return this->Gender;}
	int getStuAge(){return this->Age;}
	string getStuType(){return this->Type;}
};

//存放考生数据和下个节点地址的节点类
class Node {
	friend class Linklist;
private:
	Student rec;
	Node* next;
	Node* last;
	Node() { rec = Student(); next = NULL; last = NULL; };
	~Node() {};//析构函数，自动释放空间
};

//链表类
class Linklist {
	int size;//链表长度
	Node* head;//链表头地址
public:
	//构造函数(存在表头结点)
	Linklist();
	//析构函数，自动释放空间
	~Linklist();
	//输入考生信息
	void Inport();
	//输出全部考生信息
	void Display();
	//查询考生信息
	void Inquire();
	//添加考生信息
	void Append();
	//修改考生信息
	void Modify();
	//删除考生信息
	void Remove();
	//操作选择函数
	void selectOperation();
};

Linklist::Linklist()
{
	head = new Node;//分配空间
	size = 1;
	head->last = NULL;
	head->next = NULL;
}

Linklist::~Linklist() 
{
	Node* temp = this->head;
	while (temp != NULL && temp->next != NULL)
	{
		temp = temp->next;
		delete temp->last;
	}
	delete temp;
};

//将考生信息输入系统
void Linklist::Inport()
{
	cout << "首先请建立考生信息系统！" << endl;
	int studentnum = 0;
	cout << "请输入考生人数：";
	while (1)
	{
		cin >> studentnum;
		if (!cin.good()||studentnum<0)
		{
			cout << "输入不规范，请重新输入:" ;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
		{
			break;
		}
	}
	cin.get();
	this->size = studentnum;
	if (studentnum == 0) { return; }
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	int id = 0; string name; string gender; int age = 0; string type;
	Node* current = this->head;
	Node* tempnode;
	for (int i = 0; i < studentnum; i++)
	{
		//开辟空间
		tempnode = current;
		current->next = new Node;
		current = current->next;
		current->last = tempnode;
		//输入数据
		cin >> id >> name >> gender >> age >> type;
		current->rec = Student(id, name, gender, age, type);
	}
	cout << endl;
}

//统计考生名单
void Linklist::Display()
{
	Node* temp = this->head->next;
	if (temp == NULL)
	{
		cout << "无考生信息" << endl;
	}
	else
	{
		cout << setiosflags(ios::left);
		cout << setw(10) << "考号" << setw(10) << "姓名" << setw(10) << "性别" << setw(10) << "年龄" << setw(10) << "报考类别" << endl;
		while (temp != NULL)
		{
			cout << setw(10) << temp->rec.getStuId() << setw(10) << temp->rec.getStuName() << setw(10) << temp->rec.getStuGender() << setw(10) << temp->rec.getStuAge() << setw(10) << temp->rec.getStuType() << endl;
			temp = temp->next;
		}
	}
	cout << endl;
}

//查询考生信息
void Linklist::Inquire()
{
	int num = 0;
	cout << "请输入要查找的考生考号：";
	cin >> num;
	Node* temp = this->head->next;
	while (temp != NULL)
	{
		if (temp->rec.getStuId() == num)
		{
			cout << setiosflags(ios::left);
			cout << setw(10) << "考号" << setw(10) << "姓名" << setw(10) << "性别" << setw(10) << "年龄" << setw(10) << "报考类别" << endl;
			cout << setw(10) << temp->rec.getStuId() << setw(10) << temp->rec.getStuName() << setw(10) << temp->rec.getStuGender() << setw(10) << temp->rec.getStuAge() << setw(10) << temp->rec.getStuType() << endl;
			cout << endl;
			return;
		}
		else if (temp->rec.getStuId() != num)
		{
			temp = temp->next;
		}
	}
	cout << "此考号不存在,请继续选择操作" << endl;
	cout << endl;
	return;
}

//添加考生信息
void Linklist::Append()
{
	int num = 0;
	cout << "请输入要插入的考生位置：";
	cin >> num; cin.get();
	if (num <= 0 || num > this->size + 1)
	{
		cout << "输入不规范，请重新选择操作" << endl;
		cout << endl;
		return;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	int id = 0; string name; string gender; int age = 0; string type; 
	cin >> id >> name >> gender >> age >> type;
	//检测是否有重复
	Node* temp = this->head->next;
	while (temp != NULL)
	{
		if (temp->rec.getStuId() == id)
		{
			cout << "考生考号重复，请重新选择操作" << endl;
			cout << endl;
			return;
		}
		else if (temp->rec.getStuId() != id)
		{
			temp = temp->next;
		}
	}
	//插入
	temp = this->head;
	while (num != 1)
	{
		temp = temp->next;
		num--;
	}
	if (temp->next == NULL)
	{
		temp->next = new Node;
		temp->next->rec = Student(id, name, gender, age, type);
		temp->next->last = temp;
		temp->next->next = NULL;
		this->size++;
		cout << "操作成功！" << endl;
		cout << endl;
	}
	else if (temp->next != NULL)
	{
		Node* extra = new Node;
		extra->rec = Student(id, name, gender, age, type);
		extra->next = temp->next;
		extra->last = temp;
		temp->next = extra;
		extra->next->last = extra;
		this->size++;
		cout << "操作成功！" << endl;
		cout << endl;
	}
}

//修改考生信息
void Linklist::Modify()
{
	int num = 0;
	cout << "请输入要修改的考生考号：";
	cin >> num;
	Node* temp = this->head->next;
	while (temp != NULL)
	{
		if (temp->rec.getStuId() == num)
		{
			cout << "请依次输入修改后考生的考号，姓名，性别，年龄及报考类别！" << endl;
			int id = 0; string name; string gender; int age = 0; string type;
			cin >> id >> name >> gender >> age >> type;
			//检测是否有重复
			Node* temppp = this->head->next;
			while (temppp != NULL)
			{
				if (temppp->rec.getStuId() == id&&temppp!=temp)
				{
					cout << "考生考号重复，请重新选择操作" << endl;
					cout << endl;
					return;
				}
				else
				{
					temppp = temppp->next;
				}
			}
			//进行修改
			temp->rec = Student(id, name, gender, age, type);
			cout << "操作成功！" << endl;
			cout << endl;
			return;
		}
		else if (temp->rec.getStuId() != num)
		{
			temp = temp->next;
		}
	}
	cout << "此考号不存在,请继续选择操作" << endl;
	cout << endl;
	return;
}

//删除考生信息
void Linklist::Remove()
{
	int num = 0;
	cout << "请输入要删除的考生考号：";
	cin >> num;
	Node* temp = this->head->next;
	while (temp != NULL)
	{
		if (temp->rec.getStuId() == num)
		{
			cout << "你删除的考生信息是：";
			cout << setiosflags(ios::left);
			cout << setw(10) << temp->rec.getStuId() << setw(10) << temp->rec.getStuName() << setw(10) << temp->rec.getStuGender() << setw(10) << temp->rec.getStuAge() << setw(10) << temp->rec.getStuType() << endl;
			if (temp->next == NULL)
			{
				temp->last->next = NULL;
				delete temp;
			}
			else if (temp->next != NULL)
			{
				temp->next->last = temp->last;
				temp->last->next = temp->next;
				delete temp;
			}
			cout << "操作成功！" << endl;
			this->size--;
			return;
		}
		else if (temp->rec.getStuId() != num)
		{
			temp = temp->next;
		}
	}
	cout << "此考号不存在,请继续选择操作" << endl;
	cout << endl;
	return;
}

void Linklist::selectOperation()
{
	int operation = 5;
	while (operation!=0)
	{
		switch (operation)
		{
		case 1:this->Append(); break;
		case 2:this->Remove(); break;
		case 3:this->Inquire(); break;
		case 4:this->Modify(); break;
		case 5:this->Display(); break;
		default:cout << "未知操作码，请重新选择" << endl; break;
		}
		cout << "请选择您要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)" << endl;
		cout << "请选择您要进行的操作：";
		cin >> operation;
	}
	cout << "操作结束" << endl;
}

int main()
{
	Linklist studentExamSystem;
	studentExamSystem.Inport();
	studentExamSystem.selectOperation();
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}
