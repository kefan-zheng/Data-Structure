#include<iostream>
#include<math.h>

using namespace std;

//链式栈，用于将中缀表达式修改为后缀表达式
class LinkStack;

//队列，用于存放表达式
class Queue;

//表达式计算类
class Calculator;

//节点类，用于存储表达式中各个部分的值
class Node {
	friend class LinkStack;
	friend class Queue;
	friend class Calculator;
private:
	//存储的数据类型（0为整型，1为字符）
	bool type;
	int intnum;
	char charnum;
	//栈内优先级
	int isp;
	//栈外优先级
	int icp;
	//下一个结点地址
	Node* next;
public:
	Node() { type = 0; intnum = 0; charnum = '#'; isp = 0; icp = 0; next = NULL; }
	~Node() {};
};

//栈
class LinkStack {
friend class Queue;
friend class Calculator;
private:
	//栈顶元素地址
	Node* top;
	//栈的大小
	int size;
public:
	//链式栈的构造函数(置空栈)
	LinkStack() {
		this->top = NULL;
		this->size = 0;
	};
	//析构函数
	~LinkStack() {};
	//将坐标放入栈顶
	void Push(Node* address);
	//将栈顶的坐标弹出
	void Pop();
	//判断栈是否为空
	bool IsEmpty() {
		if (this->size > 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
};

void LinkStack::Push(Node*address)
{
	Node* current = this->top;
	Node* temp = new Node;
	temp->type = address->type;
	temp->intnum = address->intnum;
	temp->charnum = address->charnum;
	temp->next = current;
	switch (temp->charnum)
	{
	case'(':temp->isp = 1; temp->icp = 8; break;
	case')':temp->isp = 8; temp->icp = 1; break;
	case'+':temp->isp = 3; temp->icp = 2; break;
	case'-':temp->isp = 3; temp->icp = 2; break;
	case'*':temp->isp = 5; temp->icp = 4; break;
	case'/':temp->isp = 5; temp->icp = 4; break;
	case'%':temp->isp = 5; temp->icp = 4; break;
	case'^':temp->isp = 7; temp->icp = 6; break;
	case'#':temp->isp = 0; temp->icp = 0; break;
	}
	this->top = temp;
	this->size++;
}

void LinkStack::Pop()
{
	Node* temp = this->top;
	if (IsEmpty()==0)
	{
		this->top = this->top->next;
		delete temp;
		this->size--;
	}
}


//队列，存放表达式
class Queue {
friend class Calculator;
private:
	//队列头尾地址
	Node* front;
	Node* rear;
	//队列的长度
	int size;
public:
	//队列的构造函数
	Queue() {
		front = rear = new Node; size = 1;
	};
	//析构函数
	~Queue() {};
	//判断队列是否为空
	bool IsEmpty() { return (size <= 1) ? 1 : 0; }
	//添加节点
	void EnQueue(Node*& address);
	//队头出列
	void DeQueue();
	//转换成后缀表达式
	void Postfix(Node* current);
};

void Queue::EnQueue(Node*& address)
{
	//队列为空
	if (front == NULL)
	{
		front = rear = new Node;
		rear->type = address->type;
		rear->intnum = address->intnum;
		rear->charnum = address->charnum;
	}
	//队列非空
	else
	{
		rear->next = new Node;
		rear = rear->next;
		rear->type = address->type;
		rear->intnum = address->intnum;
		rear->charnum = address->charnum;
	}
	switch (rear->charnum)
	{
	case'(':rear->isp = 1; rear->icp = 8; break;
	case')':rear->isp = 8; rear->icp = 1; break;
	case'+':rear->isp = 3; rear->icp = 2; break;
	case'-':rear->isp = 3; rear->icp = 2; break;
	case'*':rear->isp = 5; rear->icp = 4; break;
	case'/':rear->isp = 5; rear->icp = 4; break;
	case'%':rear->isp = 5; rear->icp = 4; break;
	case'^':rear->isp = 7; rear->icp = 6; break;
	case'#':rear->isp = 0; rear->icp = 0; break;
	}
	size++;
}

void Queue::DeQueue()
{
	if (IsEmpty() == 0)
	{
		Node* temp = front;
		front = front->next;
		delete temp;
		size--;
	}
}

//将中缀表达式转换为后缀表达式
void Queue::Postfix(Node*current)
{
	LinkStack box;
	box.Push(current);
	current = current->next;
	while (!box.IsEmpty() || current->charnum != '#')
	{
		//是操作数，直接输出至新队列
		if (current->type == 0)
		{
			this->EnQueue(current);
			current = current->next;
		}
		//是操作符，进行判断
		else if (current->type == 1)
		{
			//进栈
			if (current->icp > box.top->isp)
			{
				box.Push(current);
				current = current->next;
			}
			//退栈并输出
			else if (current->icp < box.top->isp)
			{
				this->EnQueue(box.top);
				box.Pop();
			}
			//退栈但不输出
			else if (current->icp == box.top->isp)
			{
				if (box.top->charnum == '(')
				{
					current = current->next;
				}
				box.Pop();
			}
		}
	}
}

//模拟计算器
class Calculator {
public:
	//构造函数
	Calculator() { expre = Queue(); };
	//析构函数
	~Calculator() {};
	//初始化
	void Initialize();
private:
	Queue expre;
	//模拟栈
	LinkStack box;
	//输入算数表达式。
	void Input();
	void Run();
	//从栈中获取操作数
	bool Get2operands(int& left, int& right);
	//根据操作符进行计算
	bool Calculate(Node*&current);
	//清空队列和栈
	void Clear()
	{
		while (expre.IsEmpty() == 0)
		{
			expre.DeQueue();
		}
		while (box.IsEmpty() == 0)
		{
			box.Pop();
		}
	}
};

//初始化
void Calculator::Initialize()
{
	this->Run();
	this->Clear();
	char option = '#'; int iscontinue = 1;
	while (iscontinue)
	{
		cout << "是否继续（y，n）？";
		cin >> option;
		cout << endl;
		switch (option)
		{
		case'y':this->Run(); this->Clear(); break;
		case'n':iscontinue = 0; break;
		}
	}
}

void Calculator::Input()
{
	cout << "请输入您要计算的算数表达式：" << endl;
	string num;
	Node* temp = new Node;
	cin >> num;
	num = '#' + num + '#';
	for (unsigned int i = 1; i < num.length() - 1; i++)
	{
		if ((num[i] >= 48 && num[i] < 58) || ((num[i] < 48 && num[i] != '(') && ((num[i - 1] < 48 || num[i - 1] >= 58) && num[i - 1] != ')') && (num[i + 1] >= 48 && num[i + 1] < 58)))
		{
			int tempnum = 0, templen = 0, negative = 1, j = i;
			switch (num[i])
			{
			case'-':negative = 2; j++; break;
			case'+':negative = 3; j++; break;
			}
			while (1)
			{
				if (num[j] < 48 || num[j] >= 58)
				{
					break;
				}
				else
				{
					templen++;
					j++;
				}
			}
			for (int k = (negative == 1) ? i : i + 1; k < j; k++)
			{
				tempnum = tempnum + ((double)num[k] - 48) * pow(10, templen - 1);
				templen--;
			}
			i = j - 1;
			temp->type = 0;
			if (negative == 2)
			{
				negative = -1;
			}
			else if (negative == 3)
			{
				negative = 1;
			}
			temp->intnum = negative * tempnum;
			temp->charnum = '#';
			expre.EnQueue(temp);
		}
		else if ((num[i] < 48 || num[i] >= 58))
		{
			if (num[i] == '=')
			{
				temp->type = 1;
				temp->intnum = 0;
				temp->charnum = '#';
				expre.EnQueue(temp);
				break;
			}
			temp->type = 1;
			temp->intnum = 0;
			temp->charnum = num[i];
			expre.EnQueue(temp);
		}
	}
}

void Calculator:: Run()
{
	this->Input();
	//获得后缀表达式
	Queue postexpre;
	postexpre.Postfix(this->expre.front);
	Node* current = postexpre.front->next;
	while (current != NULL)
	{
		//操作数进栈
		if (current->type == 0)
		{
			box.Push(current);
			current = current->next;
		}
		//操作符运算
		if (current->type == 1)
		{
			if (current->charnum == '#')
			{
				current = current->next;
				continue;
			}
			if (this->Calculate(current) == false)
			{
				return;
			};
		}
	}
	cout << "计算结果为：" << box.top->intnum << endl<<endl;
};

bool Calculator::Get2operands(int& left, int& right)
{
	//取两个操作数
	if (box.IsEmpty() == 0)
	{
		right = box.top->intnum;
		box.Pop();
	}
	else
	{
		return false;
	}
	if (box.IsEmpty() == 0)
	{
		left = box.top->intnum;
		box.Pop();
	}
	else
	{
		return false;
	}
	return true;
};

//计算后缀表达式
bool Calculator::Calculate(Node*& current)
{
	//左右操作数和结果
	int left, right;
	Node* temp = new Node;
	//根据操作符进行运算
	if (this->Get2operands(left, right) == true)
	{
		switch (current->charnum)
		{
		case'+':temp->intnum = left + right; box.Push(temp); break;
		case'-':temp->intnum = left - right; box.Push(temp); break;
		case'*':temp->intnum = left * right; box.Push(temp); break;
		case'/':if(right==0)
		        {
		        	cout << "除零错误！请重新输入" << endl<<endl;
		        	return false;
	        	}
			temp->intnum = left / right; box.Push(temp); break;
		case'%':temp->intnum = left % right; box.Push(temp); break;
		case'^':
			int value = left;
			for (int i = 0; i < right - 1; i++)
			{
				value = value * left;
			}
			temp->intnum = value;
			box.Push(temp);
			break;
		}
		current = current->next;
		return true;
	}
	else
	{
		cout << "表达式有误！请重新输入" << endl<<endl;
		return false;
	}
};

int main()
{
	Calculator expression;
	expression.Initialize();
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}
