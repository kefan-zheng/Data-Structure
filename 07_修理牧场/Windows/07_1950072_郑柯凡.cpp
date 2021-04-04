#include<iostream>

using namespace std;

class MinHeap {
	friend class Field;
private:
	int* heap;
	//堆的最大大小
	int maxsize;
	//当前堆的大小
	int cursize;
public:
	//构造函数
	MinHeap() 
	{
		heap = new int[1];
		maxsize = cursize = 0; 
	};
	MinHeap(int sz)
	{
		heap = new int[sz];
		maxsize = cursize = sz;
	}
	//析构函数
	~MinHeap() {};
	//将x插入到堆中
	bool Insert(const int& x);
	//从start到0上滑调整为最小堆(用于插入）
	void Siftup();
	//把整个序列调整成最小堆
	void Adjust();
	//从start开始自顶向下调整为最小堆(用于调整成最小堆）
	void Siftdown(int start);
	//获取堆顶的元素,并将其删除
	int GetMin();
};

bool MinHeap::Insert(const int& x)
{
	if (cursize < maxsize)
	{
		heap[cursize] = x;
		Siftup();
		cursize++;
		return true;
	}
	else
	{
		cout << "堆已满，无法插入!" << endl;
		return false;
	}
}

//从start到0上滑调整为最小堆(用于插入）
void MinHeap::Siftup()
{
	int child = cursize, parent = (cursize - 1) / 2; int temp = heap[child];
	while (child > 0)
	{
		if (heap[parent] <= temp)
		{
			break;
		}
		else
		{
			heap[child] = heap[parent];
			child = parent;
			parent = (parent - 1) / 2;
		}
	}
	heap[child] = temp;
}

void MinHeap::Adjust()
{
	for (int i = (cursize - 1) / 2; i >= 0; i--)
	{
		Siftdown(i);
	}
}

//从start开始自顶向下调整为最小堆(用于调整成最小堆）
void MinHeap::Siftdown(int start)
{
	int parent = start, son = parent*2+1,temp=heap[parent];
	while (son < cursize)
	{
		if (son<cursize - 1 && heap[son]>heap[son + 1])
		{
			son++;
		}
		if (temp <= heap[son])
		{
			break;
		}
		else
		{
			heap[parent] = heap[son];
			parent = son;
			son = son * 2 + 1;
		}
	}
	heap[parent] = temp;
};

int MinHeap::GetMin()
{
	int temp = heap[0];
	heap[0] = heap[cursize - 1];
	cursize = cursize - 1;
	Adjust();
	return temp;
}

class Field {
private:
	MinHeap wood;
	int woodnum;
public:
	//构造函数
	Field() { woodnum = 0; };
	//析构函数
	~Field() {};
	//输入牧场的具体信息
	void Input();
	//构造霍夫曼树，计算最小花费
	void Huffmantree();
};

void Field::Input()
{
	int sz, woodlen, cnt = 0;
	cout << "请输入你想把木头锯成几段:" << endl;
	cin >> sz;
	woodnum = sz - 1;
	wood = MinHeap(sz);
	cout << "请依次输入木头的长度:" << endl;
	while (sz > 0)
	{
		cin >> woodlen;
		wood.heap[cnt] = woodlen;
		cnt++; sz--;
	}
	//调整成为最小堆
	wood.Adjust();
}

//计算最小花费
void Field::Huffmantree()
{
	int ans = 0;
	while (wood.cursize > 1)
	{
		int min1 = wood.GetMin();
		int min2 = wood.GetMin();
		int merge = min1 + min2;
		ans = ans + merge;
		wood.Insert(merge);
	}
	cout << "所需的最小花费为：" << ans << endl;
}

int main()
{
	Field field1;
	field1.Input();
	field1.Huffmantree();
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}