//此头文件包含自主实现的栈，队列，顺序表等数据结构容器
#ifndef MYSTL_H_
#define MYSTL_H_

#include<iostream>

using namespace std;

//结点
template <class Type>
class Node {
private:
	Type data;
	Node<Type>* next;
public:
	Node() { next = NULL; }
	~Node() {};
	//获取结点信息
	Type GetData() { return data; }
	//获取下个结点地址
	Node<Type>* GetNext() { return next; }
	//修改数据
	void ModifyData(Type tmp)
	{
		data = tmp;
	};
	//修改地址
	void ModifyNext(Node<Type>*tmp)
	{
		next = tmp;
	}
};

//链式栈
template <class Type>
class LinkStack {
private:
	//栈顶元素地址
	Node<Type>* top;
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
	void Push(Type tmp)
	{
		Node<Type>* temp = new Node<Type>;
		temp->ModifyData(tmp);
		temp->ModifyNext(this->GetTop());
		this->top = temp;
		this->size++;
	};
	//将栈顶的坐标弹出
	void Pop(Type& tmp)
	{
		Node<Type>* temp = this->GetTop();
		tmp = temp->GetData();
		top = top->GetNext();
		size--;
		delete temp;
	};
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
	//获取栈顶元素地址
	Node<Type>* GetTop() { return top; };
	//获取栈的大小
	int GetSize() { return size; }
};

//链式队列
template <class Type>
class MyQueue {
private:
	//队列头尾地址
	Node<Type>* front;
	Node<Type>* rear;
	//队列的长度
	int size;
public:
	//队列的构造函数
	MyQueue() {
		front = rear = NULL; size = 0;
	};
	//析构函数
	~MyQueue() {};
	//判断队列是否为空
	bool IsEmpty() { return (size == 0) ? 1 : 0; }
	//添加节点
	void EnQueue(Type element)
	{
		//队列为空
		if (front == NULL)
		{
			front = rear = new Node<Type>;
			rear->ModifyData(element);
		}
		//队列非空
		else
		{
			Node<Type>* temp = new Node<Type>;
			rear->ModifyNext(temp);
			rear = rear->GetNext();
			rear->ModifyData(element);
		}
		size++;
	};
	//队头出列
	void DeQueue()
	{
		if (IsEmpty() == 0)
		{
			Node<Type>* temp = front;
			front=front->GetNext();
			delete temp;
			size--;
		}
	};
	//获取队头
	Node<Type>* GetFront() { return front; }
	//获取队尾
	Node<Type>* GetRear() { return rear; }
	//获取队列长度
	int GetSize() { return size; }
};

//顺序表
template<class Type>
class MyVector {
private:
	Node<Type>* head;
	Node<Type>* tail;
	int size;
public:
	MyVector() { head = new Node<Type>;tail=head;size = 0; };
	~MyVector() {};
	//插入表尾
	void push_back(Type element)
	{
		Node<Type>* temph = new Node<Type>;
		tail->ModifyNext(temph);
		tail = tail->GetNext();
		temph->ModifyData(element);
		size++;
	}
	//获取第num位的元素
	Node<Type>* get_element(int num)
	{
		if (num >= size)
		{
			return NULL;
		}
		Node<Type>* temp = head->GetNext();
		while (num >= 1)
		{
			temp = temp->GetNext();
			num--;
		}
		return temp;
	};
	//返回顺序表的大小
	int get_size() { return size; };
};


#endif
