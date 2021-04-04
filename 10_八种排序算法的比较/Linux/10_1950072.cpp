#include<iostream>
#include<time.h>
#include<math.h>
#include<chrono>
using namespace std;
using namespace chrono;

//---------------------------------------------------------------------------------//
//交换函数
inline void Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

//---------------------------------------------------------------------------------//
//快速排序递归函数，用于快速排序
void quicksort(int* array, int left, int right, long long& cnt,long long&compare)
{
	if (left < right)
	{
		//划分区域
		int pivotpos = left; int pivot = array[left];
		for (int i = left + 1; i <= right; i++)
		{
			compare++;
			if (array[i] < pivot&&++pivotpos!=i)
			{
				Swap(array[pivotpos], array[i]);
				cnt++;
			}
		}
		Swap(array[left], array[pivotpos]);
		cnt++;
		//对划分的序列进行同样的操作
		quicksort(array, left, pivotpos - 1, cnt,compare);
		quicksort(array, pivotpos + 1, right, cnt,compare);
	}
}

//---------------------------------------------------------------------------------//
//大顶堆，用于堆排序
class MaxHeap {
	friend class SortSystem;
private:
	int* heap;
	//堆的最大大小
	int maxsize;
	//当前堆的大小
	int cursize;
public:
	//构造函数
	MaxHeap()
	{
		heap = new int[1];
		maxsize = cursize = 0;
	};
	MaxHeap(int sz)
	{
		heap = new int[sz];
		maxsize = cursize = sz;
	}
	//析构函数
	~MaxHeap() {};
	//从start开始自顶向下调整为最大堆(用于调整成最大堆）
	void Siftdown(int start, int end,long long&cnt,long long&compare);
};

void MaxHeap::Siftdown(int start, int end,long long&cnt,long long&compare)
{
	int parent = start, son = parent * 2 + 1, temp = heap[parent];
	while (son <= end)
	{
		compare++;
		if (son < end && heap[son] < heap[son + 1])
		{
			son++;
		}
		compare++;
		if (temp >= heap[son])
		{
			break;
		}
		else
		{
			heap[parent] = heap[son];
			cnt++;
			parent = son;
			son = son * 2 + 1;
		}
	}
	heap[parent] = temp;
	cnt++;
};

//---------------------------------------------------------------------------------//
//合并两个序列的函数，用于归并排序
void merge(int* array, int* copy, const int left, const int mid, const int right, long long& cnt,long long&compare)
{
	for (int k = left; k <= right; k++)
	{
		copy[k] = array[k];
		cnt++;
	}
	int s1 = left, s2 = mid + 1, t = left;
	while (s1 <= mid && s2 <= right)
	{
		compare++;
		if (copy[s1] <= copy[s2])
		{
			array[t++] = copy[s1++];
			cnt++;
		}
		else
		{
			array[t++] = copy[s2++];
			cnt++;
		}
	}
	while (s1 <= mid) { array[t++] = copy[s1++]; cnt++; }
	while (s2 <= right) { array[t++] = copy[s2++]; cnt++; }
}

//归并排序递归函数，用于归并排序
void mergesort(int* array, int* copy, int left, int right, long long& cnt,long long&compare)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	mergesort(array, copy, left, mid, cnt,compare);
	mergesort(array, copy, mid + 1, right, cnt,compare);
	merge(array, copy, left, mid, right, cnt,compare);
}

//---------------------------------------------------------------------------------//
//静态链表节点
class Staticlinkedlist {
public:
	int data;
	int link;
	int totallength;
	Staticlinkedlist() { data = 0; link = 0; totallength = 0; }
	~Staticlinkedlist() {};
};

//基数排序辅助函数
int GetDigit(int num, int d)
{
	return (int)(num / pow(10, d - 1)) % 10;
}

//基数排序递归函数
void radixsort(Staticlinkedlist* copy, int d,long long&cnt,long long&compare)
{
	int rear[10], front[10];
	int i, j, k, last, current, n = copy[1].totallength;
	for (i = 0; i < n; i++)
	{
		copy[i].link = i + 1;
	}
	copy[n].link = 0;
	current = 1; 
	for (i = 1; i <=d; i++)
	{
		for (j = 0; j < 10; j++)
		{
			front[j] = 0;
		}
		while (current!=0)
		{
			k = GetDigit(copy[current].data, i);
			if (front[k] == 0)
			{
				front[k] = current;
			}
			else
			{
				copy[rear[k]].link = current;
			}
			rear[k] = current;
			current = copy[current].link;
		}
		j = 0;
		while (front[j] == 0)
		{
			j++;
		}
		copy[0].link = current = front[j];
		last = rear[j];
		for (k = j + 1; k < 10; k++)
		{
			if (front[k] != 0)
			{
				copy[last].link = front[k];
				last = rear[k];
			}
		}
		copy[last].link = 0;
		int temp = current;
	}
}

//---------------------------------------------------------------------------------//
//全部按升序排列
class SortSystem {
private:
	int* array;
	int num;
public:
	//构造函数
	SortSystem() { array = new int[1]; num = 0; };
	//析构函数
	~SortSystem() {};
	//初始化
	void Initialize();
	//循环模块
	bool Run();
	//冒泡排序
	void BubbleSort();
	//选择排序
	void SelectSort();
	//直接插入排序
	void InsertSort();
	//希尔排序
	void ShellSort();
	//快速排序
	void QuickSort();
	//堆排序
	void HeapSort();
	//归并排序
	void MergeSort();
	//基数排序
	void RadixSort();
};

//初始化
void SortSystem::Initialize()
{
	cout << "**          排序算法比较          **" << endl;
	cout << "====================================" << endl;
	cout << "**          1---冒泡排序          **" << endl;
	cout << "**          2---选择排序          **" << endl;
	cout << "**          3---直接插入排序      **" << endl;
	cout << "**          4---希尔排序          **" << endl;
	cout << "**          5---快速排序          **" << endl;
	cout << "**          6---堆排序            **" << endl;
	cout << "**          7---归并排序          **" << endl;
	cout << "**          8---基数排序          **" << endl;
	cout << "**          9---退出程序          **" << endl;
	cout << "====================================" << endl;
	cout << endl;
	cout << "请输入要产生的随机数的个数：";
	int arraysize = 0; cin >> arraysize;
	array = new int[arraysize];
	num = arraysize;
	cout << endl;
	srand((unsigned)time(NULL));
	for (int i = 0; i < arraysize; i++)
	{
		array[i] = rand();
	}
	while (Run())
	{
		cout << endl;
	}
}

//运行
bool SortSystem::Run()
{
	cout << "请选择排序算法：";
	int sortnum = 0;
	cin >> sortnum;
	switch (sortnum)
	{
	case 1:BubbleSort(); break;
	case 2:SelectSort(); break;
	case 3:InsertSort(); break;
	case 4:ShellSort(); break;
	case 5:QuickSort(); break;
	case 6:HeapSort(); break;
	case 7:MergeSort(); break;
	case 8:RadixSort(); break;
	case 9:return false;
	default:cout << "未知操作码，请重新选择。"; break;
	}
	return true;
}

//冒泡排序
void SortSystem::BubbleSort()
{
	//初始化拷贝数组
	int* copy = new int[num];
	for (int i = 0; i < num; i++)
	{
		copy[i] = array[i];
	}
	//定义时间
	steady_clock::time_point starttime, endtime;
	steady_clock::duration durationtime;
	long long compare = 0;//记录比较次数
	long long cnt = 0;//记录交换次数
	starttime = steady_clock::now();
	int pass = 1; int exchange = 1;
	while (pass < num && exchange)
	{
		exchange = 0;
		for (int i = num - 1; i >= pass; i--)
		{
			if (copy[i - 1] > copy[i])
			{
				Swap(copy[i - 1], copy[i]);
				cnt++;
				exchange = 1;
			}
			compare++;
		}
		pass++;
	}
	endtime = steady_clock::now();
	durationtime = endtime - starttime;
	cout << "冒泡排序所用时间: " << double(durationtime.count()) * microseconds::period::num / microseconds::period::den/1000 << "s"<<endl;
	cout << "冒泡排序比较次数：" << compare << endl;
	cout << "冒泡排序交换次数：" << cnt << endl;
}

//选择排序
void SortSystem::SelectSort()
{
	int* copy = new int[num];
	for (int i = 0; i < num; i++)
	{
		copy[i] = array[i];
	}
	steady_clock::time_point starttime, endtime;
	steady_clock::duration durationtime;
	long long compare = 0;//记录比较次数
	long long cnt=0;//记录交换次数
	starttime = steady_clock::now();
	for (int i = 0; i < num-1; i++)
	{
		int min = i;
		for (int j = i + 1; j < num; j++)
		{
			if (copy[j] < copy[min])
			{
				min = j;
			}
			compare++;
		}
		if (min != i)
		{
			Swap(copy[i], copy[min]);
			cnt++;
		}
	}
	endtime = steady_clock::now();
	durationtime = endtime - starttime;
	cout << "选择排序所用时间: " << double(durationtime.count()) * microseconds::period::num / microseconds::period::den / 1000 << "s" << endl;
	cout << "选择排序比较次数：" << compare << endl;
	cout << "选择排序交换次数：" << cnt << endl;
}

//直接插入排序
void SortSystem::InsertSort()
{
	int* copy = new int[num];
	for (int i = 0; i < num; i++)
	{
		copy[i] = array[i];
	}
	steady_clock::time_point starttime, endtime;
	steady_clock::duration durationtime;
	long long compare = 0;//记录比较次数
	long long cnt = 0;//记录交换次数
	starttime = steady_clock::now();
	for (int i = 1; i < num; i++)
	{
		int temp = copy[i]; int j = i;
		while (j > 0 && temp < copy[j - 1])
		{
			compare++;
			copy[j] = copy[j - 1];
			cnt++;
			j--;
		}
		compare++;
		copy[j] = temp;
		cnt++;
	}
	endtime = steady_clock::now();
	durationtime = endtime - starttime;
	cout << "直接插入排序所用时间: " << double(durationtime.count()) * microseconds::period::num / microseconds::period::den / 1000 << "s" << endl;
	cout << "直接插入排序比较次数：" << compare << endl;
	cout << "直接插入排序交换次数：" << cnt << endl;
}

//希尔排序
void SortSystem::ShellSort()
{
	int* copy = new int[num];
	for (int i = 0; i < num; i++)
	{
		copy[i] = array[i];
	}
	steady_clock::time_point starttime, endtime;
	steady_clock::duration durationtime;
	long long compare = 0;//记录比较次数
	long long cnt = 0;//记录交换次数
	starttime = steady_clock::now();
	int gap = num / 2;
	while (gap)
	{
		for (int i = gap; i < num; i++)
		{
			int temp = copy[i]; int j = i;
			while (j >= gap && temp < copy[j - gap])
			{
				compare++;
				copy[j] = copy[j - gap];
				cnt++;
				j -= gap;
			}
			compare++;
			copy[j] = temp;
			cnt++;
		}
		gap = (gap == 2) ? 1 : (int)(gap / 2.2);
	}
	endtime = steady_clock::now();
	durationtime = endtime - starttime;
	cout << "希尔排序所用时间: " << double(durationtime.count()) * microseconds::period::num / microseconds::period::den / 1000 << "s" << endl;
	cout << "希尔排序比较次数：" << compare << endl;
	cout << "希尔排序交换次数：" << cnt << endl;
}

//快速排序
void SortSystem::QuickSort()
{
	int* copy = new int[num];
	for (int i = 0; i < num; i++)
	{
		copy[i] = array[i];
	}
	steady_clock::time_point starttime, endtime;
	steady_clock::duration durationtime;
	long long compare = 0;
	long long cnt = 0;
	starttime = steady_clock::now();
	quicksort(copy, 0, num - 1, cnt, compare);
	endtime = steady_clock::now();
	durationtime = endtime - starttime;
	cout << "快速排序所用时间: " << double(durationtime.count()) * microseconds::period::num / microseconds::period::den / 1000 << "s" << endl;
	cout << "快速排序比较次数：" << compare << endl;
	cout << "快速排序交换次数：" << cnt << endl;
}

//堆排序
void SortSystem::HeapSort()
{
	MaxHeap hp;
	hp.heap = new int[num];
	for (int i = 0; i < num; i++)
	{
		hp.heap[i] = array[i];
	}
	hp.cursize = hp.maxsize = num;
	steady_clock::time_point starttime, endtime;
	steady_clock::duration durationtime;
	long long compare = 0;//记录比较次数
	long long cnt = 0;//记录交换次数
	starttime = steady_clock::now();
	//将整个堆调整成最大堆
	for (int i = (hp.cursize - 2) / 2; i >= 0; i--)
	{
		hp.Siftdown(i, hp.cursize - 1,cnt,compare);
	}
	//交换顺序
	for (int i = hp.cursize - 1; i >= 1; i--)
	{
		Swap(hp.heap[0], hp.heap[i]);
		cnt++;
		hp.Siftdown(0, i - 1,cnt,compare);
	}
	endtime = steady_clock::now();
	durationtime = endtime - starttime;
	cout << "堆排序所用时间: " << double(durationtime.count()) * microseconds::period::num / microseconds::period::den / 1000 << "s" << endl;
	cout << "堆排序比较次数：" << compare << endl;
	cout << "堆排序交换次数：" << cnt << endl;
}

//归并排序
void SortSystem::MergeSort()
{
	int* copy1 = new int[num];
	int* copy2 = new int[num];
	for (int i = 0; i < num; i++)
	{
		copy1[i] = array[i];
	}
	steady_clock::time_point starttime, endtime;
	steady_clock::duration durationtime;
	long long compare = 0;//记录比较次数
	long long cnt = 0;//记录交换次数
	starttime = steady_clock::now();
	mergesort(copy1, copy2, 0, num - 1, cnt,compare);
	endtime = steady_clock::now();
	durationtime = endtime - starttime;
	cout << "归并排序所用时间: " << double(durationtime.count()) * microseconds::period::num / microseconds::period::den / 1000 << "s" << endl;
	cout << "归并排序比较次数：" << compare << endl;
	cout << "归并排序交换次数：" << cnt << endl;
}

//基数排序
void SortSystem::RadixSort()//LSD
{
	Staticlinkedlist* copy = new Staticlinkedlist[num+1];
	for (int i = 1; i <= num; i++)
	{
		copy[i].data = array[i-1];
		copy[i].totallength = num;
	}
	steady_clock::time_point starttime, endtime;
	steady_clock::duration durationtime;
	long long compare = 0;//记录比较次数
	long long cnt = 0;//记录交换次数
	starttime = steady_clock::now();
	radixsort(copy,8,cnt,compare);
	endtime = steady_clock::now();
	durationtime = endtime - starttime;
	cout << "基数排序所用时间: " << double(durationtime.count()) * microseconds::period::num / microseconds::period::den / 1000 << "s" << endl;
	cout << "基数排序比较次数：" << compare << endl;
	cout << "基数排序交换次数：" << cnt << endl;
}

int main()
{
	SortSystem system;
	system.Initialize();
	cout << endl;
	cout << "按回车键结束";
	getchar(); getchar();
	return 0;
}
