#include<iostream>
#include<algorithm>
#include <windows.h>
#include <cstdio>
#include <malloc.h>
#include <time.h>
using namespace std;
#define TRUE 1
#define FALSE 0
const int NUMBER = 6; //进行排序的算法个数
const int Max = 1000000;
int arr[Max] = { 0 }, b[Max];
long long int 
	compare_number[NUMBER] = { 0 }, //比较
	swap_number[NUMBER] = { 0 },
	move_number[NUMBER] = { 0 };
typedef struct {
	long long int num;
	long long int sort_time;
	int ranking;//排序算法的所用时间的多少顺序
} Time;

int CompareWithSortTime(const Time& a, const Time& b) {
	return a.sort_time < b.sort_time;
}

int CompareWithNum(const Time& a, const Time& b) {
	return a.num < b.num;
}
//初始化排序的数组
void Init(int num) {
	int i;
	if (num >= Max) {
		printf("输入数字太大！！！结束程序");
		exit(2);
	}
	srand((unsigned)time(NULL));
	for (i = 0; i < num; i++) {
		b[i] = arr[i] = rand() % 10000;
	}
	return;
}

//还原
void Restore(int num) {
	int i;
	for (i = 0; i < num; i++) {
		arr[i] = b[i];
	}
}
//插入排序
void InsertSort(int R[], int n) { // 待排数据存在R[]中,默认为整型,个数为n
	int i = 0, j = 0, temp = 0;
	for (i = 2; i <= n; i++) { /*  数组从下标1开始存储,第一个元素有序,所以从第二个元素开始处理  */
		if (R[i] < R[i - 1]) {
			compare_number[0]++;
			move_number[0]++;
			temp = R[i];   // 将待插入元素暂时存于temp中
			j = i - 1;
			while (temp < R[j] && j >= 1) { // 下面的循环完成寻找插入位置的功能
				compare_number[0]++;
				move_number[0]++;
				R[j + 1] = R[j];
				swap_number[0]++;
				j--;
			}
		}
		R[j + 1] = temp;
		// 找到插入位置后将temp中暂存的待插入元素插入
	}
}
//希尔排序
void ShellSort(int arr[], int len) {
	int h = 0, i = 0, j = 0, temp; //设置步长
	for (h = 1; h < len; h = 3 * h + 1) move_number[1]++;
	while (h) {
		h /= 3;
		move_number[1] += h / 3;
		if (h < 1) break;
		for (i = h; i < len; i++) for (j = i; j >= h; j -= h) {
			if (arr[j - h] < arr[j]) break;
			compare_number[1] += h / 3;
			swap_number[1] += h / 3;
			move_number[1] += h / 3;
			temp = arr[j - h];
			arr[j - h] = arr[j];
			arr[j] = temp;
		}
	}
}
//简单选择排序
void SelectSort(int R[], int n) {
	int i, j, k;
	int  temp;
	for (i = 0; i <= n - 1; ++i) {
		k = i;
		for (j = i + 1; j <= n; ++j)  /*这个循环是算法的关键，它从无序序列中挑出一个最小的元素*/
			if (R[k] > R[j]) {
				move_number[2]++;
				swap_number[2]++;
				compare_number[2]++;
				k = j;
			}  //每两个数比较时总是把小的挑出来，并且将其放入下一轮比较数据中
		/*下面的3句完成最小元素与无序序列第一个元素的交换*/
		swap_number[2]++;
		compare_number[2]++;
		move_number[2] += 3;
		temp = R[i];
		R[i] = R[k];
		R[k] = temp;
	}
}

int Partition(int arr[], int low, int high) {
	int key;
	key = arr[low];
	while (low < high) {
		while (low < high && arr[high] >= key) {
			high--;
			compare_number[3]++;
		}

		if (low < high) {
			move_number[3]++;
			swap_number[3]++;
			arr[low++] = arr[high];
			compare_number[3]++;
		}

		while (low < high && arr[low] <= key) {
			low++;
			compare_number[3]++;
		}

		if (low < high) {
			swap_number[3]++;
			compare_number[3]++;
			move_number[3]++;
			arr[high--] = arr[low];
		}

	}
	arr[low] = key;
	return low;
}
//快速排序
void QuickSort(int arr[], int start, int end) {
	int pos;
	if (start < end) {
		compare_number[3]++;
		swap_number[3]++;
		pos = Partition(arr, start, end);
		QuickSort(arr, start, pos - 1);
		QuickSort(arr, pos + 1, end);
	}
	return;
}

void Merge(int src[], int des[], int low, int high, int mid) {
	int i = low;
	int k = low;
	int j = mid + 1;
	while ((i <= mid) && (j <= high)) {
		compare_number[4]++;
		if (src[i] < src[j]) {
			des[k++] = src[i++];
		}
		else {
			des[k++] = src[j++];
		}
	}
	while (i <= mid) {
		compare_number[4]++;
		move_number[4]++;
		swap_number[4]++;
		des[k++] = src[i++];
	}
	while (j <= high) {
		compare_number[4]++;
		move_number[4]++;
		swap_number[4]++;
		des[k++] = src[j++];
	}
}
void MSort(int src[], int des[], int low, int high, int max_size) {
	int mid = (low + high) / 2;
	if (low == high) {
		compare_number[4]++;
		move_number[4]++;
		swap_number[4]++;
		des[low] = src[low];
	}
	else {
		swap_number[4]++;
		int mid = (low + high) / 2;
		int* des_space = (int*)malloc(sizeof(int) * max_size);
		if (NULL != des_space) {
			swap_number[4]++;
			move_number[4]++;
			MSort(src, des_space, low, mid, max_size);
			MSort(src, des_space, mid + 1, high, max_size);
			Merge(des_space, des, low, high, mid);
		}
		free(des_space);
	}
}
//归并排序
void MegerSort(int arr[], int low, int high, int len) {
	MSort(arr, arr, low, high, len);
}

//冒泡排序
void  BubbleSort(int arr[], int n) {

	int i, j;
	int flag = 1;
	int  temp;
	for (i = 1; i < n  && flag; i++)
	{
		flag = 0;
		for (j = n; j > i; j--)		//冒泡一定是从后往前比较
		{
			compare_number[5]++;
			if (arr[j] <arr[j-1])
			{
				temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;

				swap_number[5]++;
				
				move_number[5] += 3;

				flag = 1;						//如果没有交换说明已经排好序了
			}
		}
	}

}

//进行排序
void RunSort(int num) {
	int i;
	Time t[NUMBER];
	long long int total_sort_time  = 0, total_start = 0, start = 0, total_end = 0, end = 0;

	printf("\t\|                                                   \|\n");
	printf("\t ----------------------------------------------------\n");
	printf("\t\|  请稍等......                                     \|\n");

	printf("\t\|                                                   \|\n");

	total_start = start = GetTickCount64();
	Init(num);//初始化数组
	InsertSort(arr, num);
	end = GetTickCount64();
	t[0].sort_time = end - start;
	t[0].num = 0;

	Restore(num);
	start = GetTickCount64();
	ShellSort(arr, num);
	end = GetTickCount64();
	t[1].sort_time = end - start;
	t[1].num = 1;

	Restore(num);
	start = GetTickCount64();
	SelectSort(arr, num);
	end = GetTickCount64();
	t[2].sort_time = end - start;
	t[2].num = 2;

	Restore(num);
	start = GetTickCount64();
	QuickSort(arr, 0, num);
	end = GetTickCount64();
	t[3].sort_time = end - start;
	t[3].num = 3;

	Restore(num);
	start = GetTickCount64();
	MegerSort(arr, 0, num - 1, num);
	end = GetTickCount64();
	t[4].sort_time = end - start;
	t[4].num = 4;


	Restore(num);
	start = GetTickCount64();
	BubbleSort(arr, num);
	end = GetTickCount64();
	t[5].sort_time = end - start;
	t[5].num = 5;

	sort(t, t + NUMBER, CompareWithSortTime);
	t[0].ranking = 1;
	for (i = 1; i < NUMBER; i++) {
		if (t[i].sort_time == t[i - 1].sort_time)
			t[i].ranking = t[i - 1].ranking;
		else
			t[i].ranking = i + 1;
	}
	sort(t, t + NUMBER, CompareWithNum);
	total_end = end = GetTickCount64();
	total_sort_time  = total_end - total_start;

	printf("\t\|  总共用时为：%I64d毫秒\n", total_sort_time);
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\|                 -----      五种算法性能比较结果如下          ------              \|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 排 序 方 法\| 比较的次数 \| 交换的次数 \| 移动的次数 \|时间（ms）\|时间排名\|时间复杂度\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\|直接插入排序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n", compare_number[0], swap_number[0], move_number[0], t[0].sort_time, t[0].ranking);
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 希 尔 排 序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", compare_number[1], swap_number[1], move_number[1], t[1].sort_time, t[1].ranking);	
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\|简单选择排序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n", compare_number[2], swap_number[2], move_number[2], t[2].sort_time, t[2].ranking);
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 快 速 排 序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", compare_number[3], swap_number[3], move_number[3], t[3].sort_time, t[3].ranking);
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 归 并 排 序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", compare_number[4], swap_number[4], move_number[4], t[4].sort_time, t[4].ranking);
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 冒 泡 排 序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", compare_number[5], swap_number[5], move_number[5], t[5].sort_time, t[5].ranking);
	printf("\t ----------------------------------------------------------------------------------\n");
	return;
}










//对输入的数字进行分析，判断格式是否全为十进制
int NumberJudge() {
	int n;
	int sign = 0;
	int retur;
	do {
		sign = 0;
		retur = scanf_s("%d", &n);//如果输入的n是十进制数字，则返回1（符合条件的参数）
		if (retur == 0) {		//不断循环，直到输入的n是十进制数字，则退出循环
			printf("\n非法输入，请重新输入！\n");
			for (; getchar() != '\n';);
			sign = -1;
		}
	} while (sign == -1);
	return n;
}

int main() {
	system("color 0A");
	int num;//数字元素的个数
	system("cls");
	printf("\t\|                                                   \|\n");
	printf("\t\|  请你输入待排序数列的数字元素的个数 n(按0退出)（数字越大，时间越长，大于十万数字请耐心等待）：");
	num = NumberJudge();
	if (num == 0) {
		printf("退出排序程序\n");
		return 0;
	}

	RunSort(num);
	system("pause");
	while (num !=0)
	{
		system("cls");
		printf("\t\|                                                   \|\n");
		printf("\t\|  请你输入待排序数列的数字元素的个数 n(按0退出)（数字越大，时间越长，大于十万数字请耐心等待）：");
		num = NumberJudge();
		if (num == 0) {
			printf("退出排序程序\n");
			return 0;
		}
		RunSort(num);
		system("pause");
	}
	printf("退出排序\n");
	return 0;
}


