//两个有序链表的交集（支持整型，浮点型，均用-1代表结束）
#include<iostream>
#include<string>
#include<iomanip>
#include <typeinfo>
using namespace std;

template<class Type>
class Linklist;

template<class Type>
//存放数字和前后两个节点地址的节点类
class Node {
friend class Linklist<Type>;
private:
	Type num;
	Node<Type>* next;
	Node<Type>* last;
public:
	Node<Type>() {  next = NULL; last = NULL; };
	//析构函数，自动释放空间
	~Node() { next = NULL;last = NULL;};
};

template<class Type>
//链表类
class Linklist {
private:
	int size;//链表长度
	Node<Type>* head;//链表头地址
public:
    //构造函数(存在表头结点)
	Linklist();
	//析构函数，自动释放空间
	~Linklist();
	//输入函数
	void Inport();
	//打印函数。输出链表的各个元素
	void Display();
	//删除函数，删除链表中的某个节点
	void Remove(Node<Type>*Iterator);
	//求交集函数，寻找两链表相同的元素
	void SeekIntersection(Linklist<Type>& S2);
};

template<class Type>
Linklist<Type>::Linklist()
{
	head = new Node<Type>;//分配空间
	size = 0;
	head->num = -1;
	head->last = NULL;
	head->next = NULL;
}

template<class Type>
Linklist<Type>::~Linklist() 
{
	Node<Type>* temp = this->head;
	while (temp != NULL && temp->next != NULL)
	{
		temp = temp->next;
		delete (temp->last);
	}
	delete temp;
};

template<class Type>
void Linklist<Type>::Inport()
{
	cout << "请输入序列元素，以-1结束:";
	Node<Type>* current = this->head;
	Type innum;
	while (cin>>innum)
	{  
		if (innum == -1|| innum=='-')
		{
			break;
		}
		//开辟空间
		current->next = new Node<Type>;
		current->next->num = innum;
		current->next->last = current;
		current->next->next = NULL;
		current = current->next;
		this->size++;
	}
}

template<class Type>
void Linklist<Type>::Display()
{
	cout << "相同的序列元素为:";
	Node<Type>* current = this->head->next;
	if (current == NULL)
	{
		cout << "NULL" << endl;
	}
	else if (current != NULL)
	{
		while (current != NULL)
		{
			cout << current->num << " ";
			current = current->next;
		}
		cout << endl;
	}
}

template<class Type>
void Linklist<Type>::Remove(Node<Type>*Iterator)
{
	if (Iterator->next == NULL)
	{
		Node<Type>* temp = Iterator;
		Iterator->last->next = NULL;
		delete temp;
	}
	else if (Iterator->next != NULL)
	{
		Node<Type>* temp = Iterator;
		Iterator->last->next = Iterator->next;
		Iterator->next->last = Iterator->last;
		delete temp;
	}
	this->size--;
}

template<class Type>
void Linklist<Type>::SeekIntersection(Linklist& S2)
{
	Node<Type>* Iterator1 = this->head;
	Node<Type>* Iterator2 = S2.head;
	//以长度较短的链表作为S3的基链表
	if (this->size > S2.size)
	{
		//交换头指针
		this->head = Iterator2;
		S2.head = Iterator1;
		//交换链表长度
		int tempsize = this->size;
		this->size = S2.size;
		S2.size = tempsize;
		Node<Type>* tempIterator = Iterator1->next;
		Iterator1 = Iterator2->next;
		Iterator2 = tempIterator;
	}
	else if (this->size <= S2.size)
	{
		Iterator1 = Iterator1->next;
		Iterator2 = Iterator2->next;
	}
	while (Iterator1 != NULL && Iterator2 != NULL)
	{
		if (Iterator1->num < Iterator2->num)
		{
			Node<Type>* temp = Iterator1;
			Iterator1 = Iterator1->next;
			this->Remove(temp);
		}
		else if (Iterator1->num > Iterator2->num)
		{
			Iterator2 = Iterator2->next;
		}
		else if (Iterator1->num == Iterator2->num && Iterator1->num != -1)
		{
			Iterator1 = Iterator1->next;
			Iterator2 = Iterator2->next;
		}
		else if (Iterator1->num == Iterator2->num && Iterator1->num == -1)
		{
			break;
		}
	}
	while (Iterator1 != NULL)
	{
		Node<Type>* temp = Iterator1;
		Iterator1 = Iterator1->next;
		this->Remove(temp);
	}
}

int main()
{
	Linklist<int> S1, S2;
	S1.Inport();
	S2.Inport();
	S1.SeekIntersection(S2);
	S1.Display();
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}
