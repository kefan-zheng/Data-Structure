#include<iostream>
#include"05_1950072.h"

using namespace std;

//节点类
class Customer {
	friend class Bank;
private:
	//存储的数据
	int num;
	int time;
public:
	Customer() { num = 0; time = 0; }
	~Customer() {};
};

//银行业务类
class Bank {
private:
	MyQueue<Customer>queueA;
	MyQueue<Customer>queueB;
public:
	Bank() {}
	~Bank() {};
	//处理业务
	void Run();
};

void Bank::Run()
{
	//输入放进两个队列
	cout << "请输入顾客人数和各顾客编号：";
	int total = 0; int num2;
	Customer temp ;
	cin >> total;
	for (int i = 0; i < total; i++)
	{
		cin >> num2;
		temp.num = num2;
		if (num2 % 2 == 1)
		{
			queueA.EnQueue(temp);
		}
		else if (num2 % 2 == 0)
		{
			queueB.EnQueue(temp);
		}
	}
	//根据先后顺序输出
	while (queueA.IsEmpty() == 0 || queueB.IsEmpty() == 0)
	{
		if (queueA.IsEmpty() == 0)
		{
			if (queueA.GetFront()->GetData().time == 1)
			{
				cout << queueA.GetFront()->GetData().num;
				queueA.DeQueue();
				if (!queueA.IsEmpty() || !queueB.IsEmpty())
				{
					cout << " ";
				}
			}
			if (queueA.IsEmpty() == 0)
			{
				temp.num = queueA.GetFront()->GetData().num;
				temp.time = queueA.GetFront()->GetData().time + 1;
				queueA.GetFront()->ModifyData(temp);
			}
			
		}
		if (queueB.IsEmpty() == 0)
		{
			if (queueB.GetFront()->GetData().time == 2)
			{
				cout << queueB.GetFront()->GetData().num;
				queueB.DeQueue();
				if (!queueA.IsEmpty() || !queueB.IsEmpty())
				{
					cout << " ";
				}
			}
			if (queueB.IsEmpty() == 0)
			{
				temp.num = queueB.GetFront()->GetData().num;
				temp.time = queueB.GetFront()->GetData().time + 1;
				queueB.GetFront()->ModifyData(temp);
			}
		}
	}
	cout << endl;
}

int main()
{
	Bank bank1;
	bank1.Run();
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}
