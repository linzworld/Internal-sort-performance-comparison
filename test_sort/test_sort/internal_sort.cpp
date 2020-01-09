/*************************************************
File name: internal_sort.cpp
Author: 林泽鸿
Version: 1.0
Date: 2020-01-09
Description:该程序用于通过随机数据比较各算法的关键字
			比较次数和关键字移动次数，用图表的形式，
			以取得直观感受（完全自己开发完成）
*************************************************/
#include<iostream>
#include<algorithm>
#include <windows.h>
#include <cstdio>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

using namespace std;
#define TRUE 1
#define FALSE 0
#define Zero_InsertSort 0
#define One_ShellSort 1
#define Two_SelectSort 2
#define Three_QuickSort 3
#define Four_MegerSort 4
#define Five_BubbleSort 5
const int NUMBER = 6; //进行排序的算法个数
const int Max = 1000000;
const int GroupMaxCount = 10;//分组排序的最大组数
int arr[Max] = { 0 }, b[Max];//随机数的数组
long long int 
	compare_number[NUMBER] = { 0 }, //比较
	swap_number[NUMBER] = { 0 },
	move_number[NUMBER] = { 0 }; 
typedef struct {
	long long int num;//在数组中的下标
	long long int sort_time;//该排序算法需要花费的时间（单位：ms）
	int ranking;//排序算法的所用时间的多少顺序
} Time;//用来存储比较信息的结构体

typedef struct {
	long long int num[NUMBER];//在数组中的下标
	long long int sort_time[NUMBER];//该排序算法需要花费的时间（单位：ms）
	long long int compare_number[NUMBER];
	long long int swap_number[NUMBER];
	long long int move_number[NUMBER];
	int ranking[NUMBER];//排序算法的所用时间的多少顺序
} Result;//用来存储比较信息的结构体

typedef struct {
	Result * result;//结果数组
	int group_count;//分组数
} Group;//用来存储分组比较信息
int group_num = 1;//分组的数量

Time t[NUMBER];
long long int total_sort_time = 0, total_START = 0, START = 0, total_END = 0, END = 0;

Group g;
int* numArr;

//初始化分组的函数
Group InitGroup( ) {
	//外层的结构体数组先申请内存空间
	g.result = (Result*)malloc(group_num *sizeof(Result));
	g.group_count = group_num;
	return g;
}

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
void InsertSort(int arr[], int n) { // 待排数据存在arr[]中,默认为整型,个数为n

	int i, j;
	for (i = 1; i < n; i++)//循环从第2个元素开始
	{
		move_number[0]++;
		if (arr[i] < arr[i - 1])
		{
			compare_number[0]++;
			int temp = arr[i];
			for (j = i - 1; j >= 0 && arr[j] > temp; j--)
			{
				arr[j + 1] = arr[j];
				move_number[0]++;
				swap_number[0]++;
			}
			//将a[i]放到正确位置上
			arr[j + 1] = temp;
		}
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
	for (i = 0; i < n ; ++i) {
		k = i;
		for (j = i + 1; j < n; ++j)  /*这个循环是算法的关键，它从无序序列中挑出一个最小的元素*/
			if (R[k] > R[j]) {
				move_number[2]++;
				swap_number[2]++;
				compare_number[2]++;
				k = j;
			}  
		//每两个数比较时总是把小的挑出来，并且将其放入下一轮比较数据中
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
void QuickSort(int arr[], int START, int END) {
	int pos;
	if (START < END) {
		compare_number[3]++;
		swap_number[3]++;
		pos = Partition(arr, START, END);
		QuickSort(arr, START, pos - 1);
		QuickSort(arr, pos + 1, END);
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
void  BubbleSort(int* arr, int n) {

	int i, j;
	int flag = 1;
	int  temp;
	for (i = 0; i < n  && flag; i++)
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

//测试直接插入排序，希尔排序，选择排序，冒泡排序
void TestMostSort(int sort_num,int* num,void (Sort)(int* , int ) ) {
	total_START = START = GetTickCount64();
	Init(*num);//初始化数组

	Sort( arr, *num);


	END = GetTickCount64();
	t[sort_num].sort_time = END - START;
	t[sort_num].num = sort_num;
}

//测试快速排序
void TestQuickSort( int* num ) {
	total_START = START = GetTickCount64();
	Init(*num);//初始化数组
	QuickSort(arr, 0,*num);
	END = GetTickCount64();
	t[Three_QuickSort].sort_time = END - START;
	t[Three_QuickSort].num = Three_QuickSort;
}


//测试归并排序
void TestMegerSort(int* num) {
	total_START = START = GetTickCount64();
	Init(*num);//初始化数组
	MegerSort(arr, 0, *num - 1, *num);
	END = GetTickCount64();
	t[Three_QuickSort].sort_time = END - START;
	t[Three_QuickSort].num = Three_QuickSort;
}

//通过一个随机数的排序结果
void PrintOneSortResult() {
	printf("\t\|  总共用时为：%I64d毫秒\n", total_sort_time);
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\|          -----        六种内部排序算法性能比较结果如下            ------       \|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 排 序 方 法\| 比较的次数 \| 交换的次数 \| 移动的次数 \|时间（ms）\|时间排名\|时间复杂度\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\|直接插入排序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n", g.result[0].compare_number[0], g.result[0].swap_number[0], g.result[0].move_number[0], g.result[0].sort_time[0], g.result[0].ranking[0]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\| 希 尔 排 序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", g.result[0].compare_number[1], g.result[0].swap_number[1], g.result[0].move_number[1], g.result[0].sort_time[1], g.result[0].ranking[1]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\|简单选择排序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n", g.result[0].compare_number[2], g.result[0].swap_number[2], g.result[0].move_number[2], g.result[0].sort_time[2], g.result[0].ranking[2]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\| 快 速 排 序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", g.result[0].compare_number[3], g.result[0].swap_number[3], g.result[0].move_number[3], g.result[0].sort_time[3], g.result[0].ranking[3]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\| 归 并 排 序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", g.result[0].compare_number[4], g.result[0].swap_number[4], g.result[0].move_number[4], g.result[0].sort_time[4], g.result[0].ranking[4]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\| 冒 泡 排 序\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n", g.result[0].compare_number[5], g.result[0].swap_number[5], g.result[0].move_number[5], g.result[0].sort_time[5], g.result[0].ranking[5]);
	printf("\t ----------------------------------------------------------------------------------\n");
}
//分组通过随机数的排序结果
void PrintGroupSortResult() {
	printf("\t\|  总共用时为：%I64d毫秒\n", total_sort_time);
	int i = 0;
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\|        -----  多种输入数的情况下，六种内部排序算法的性能结果如下  ------       \|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t ------------------------------直接插入排序----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 排序总耗时\| 比较的次数 \| 交换的次数 \| 移动的次数 \|时间（ms）\|时间排名\|时间复杂度\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for ( i = 0; i < group_num; i++)
	{
		printf("\t\| 第  %d  组 \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n",i+1, g.result[i].compare_number[0], g.result[i].swap_number[0], g.result[i].move_number[0], g.result[i].sort_time[0], g.result[i].ranking[0]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}


	printf("\t ---------------------------------希尔排序-------------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 排序总耗时\| 比较的次数 \| 交换的次数 \| 移动的次数 \|时间（ms）\|时间排名\|时间复杂度\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| 第  %d  组 \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[1], g.result[i].swap_number[1], g.result[i].move_number[1], g.result[i].sort_time[1], g.result[i].ranking[1]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}

	printf("\t -------------------------------简单选择排序-----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 排序总耗时\| 比较的次数 \| 交换的次数 \| 移动的次数 \|时间（ms）\|时间排名\|时间复杂度\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| 第  %d  组 \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[2], g.result[i].swap_number[2], g.result[i].move_number[2], g.result[i].sort_time[2], g.result[i].ranking[2]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}


	printf("\t -------------------------------快 速 排 序-----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 排序总耗时\| 比较的次数 \| 交换的次数 \| 移动的次数 \|时间（ms）\|时间排名\|时间复杂度\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| 第  %d  组 \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[3], g.result[i].swap_number[3], g.result[i].move_number[3], g.result[i].sort_time[3], g.result[i].ranking[3]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}

	printf("\t -------------------------------归 并 排 序-----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 排序总耗时\| 比较的次数 \| 交换的次数 \| 移动的次数 \|时间（ms）\|时间排名\|时间复杂度\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| 第  %d  组 \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[4], g.result[i].swap_number[4], g.result[i].move_number[4], g.result[i].sort_time[4], g.result[i].ranking[4]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}

	printf("\t -------------------------------冒 泡 排 序-----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| 排序总耗时\| 比较的次数 \| 交换的次数 \| 移动的次数 \|时间（ms）\|时间排名\|时间复杂度\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| 第  %d  组 \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[5], g.result[i].swap_number[5], g.result[i].move_number[5], g.result[i].sort_time[5], g.result[i].ranking[5]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}
	system("pause");
}
//计算一次排序的结果
void CalculateSortResult(int num) {
	int i;
	TestMostSort(0, &num, InsertSort);
	TestMostSort(1, &num, ShellSort);
	TestMostSort(2, &num, SelectSort);
	TestQuickSort(&num);
	TestMegerSort(&num);
	TestMostSort(5, &num, BubbleSort);

	sort(t, t + NUMBER, CompareWithSortTime);
	t[0].ranking = 1;
	for (i = 1; i < NUMBER; i++) {
		if (t[i].sort_time == t[i - 1].sort_time)
			t[i].ranking = t[i - 1].ranking;
		else
			t[i].ranking = i + 1;
	}
	sort(t, t + NUMBER, CompareWithNum);
	total_END = END = GetTickCount64();
	total_sort_time = total_END - total_START;
}

//存储一次的排序结果
void StorageOneSortResult(Group* gPoint, int i) {

	for (int j = 0; j < 6; j++)
	{
		(*gPoint).result[i].compare_number[j] = compare_number[j];
		(*gPoint).result[i].swap_number[j] = swap_number[j];
		(*gPoint).result[i].move_number[j] = move_number[j];

		(*gPoint).result[i].num[j] = t[j].num;
		(*gPoint).result[i].sort_time[j] = t[j].sort_time;
		(*gPoint).result[i].ranking[j] = t[j].ranking;
	}
}

//存储排序结果
void StorageSortResult() {
	Group* gPoint = &InitGroup();
	if (group_num == 1)
	{
		StorageOneSortResult(gPoint,0);
		return;
	}
	for (int i = 0; i < group_num; i++)
	{
		CalculateSortResult(numArr[i]);
		StorageOneSortResult(gPoint, i);
	}
	return;
}

//进行排序
void OneRunSort(int num) {
	int i;
	printf("\t\|                                                   \|\n");
	printf("\t ----------------------------------------------------\n");
	printf("\t\|  请稍等......                                     \|\n");
	printf("\t\|                                                   \|\n");
	CalculateSortResult(num);
	StorageSortResult();

	PrintOneSortResult();
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

//显示只有一组的排序算法结果的菜单
void OneSortMenu() {
	int num;//数字元素的个数
	
	system("cls");
	printf("\t\|                                                   \|\n");
	printf("\t\|  请你输入待排序数列的数字元素的个数 n(按0返回主菜单)（数字越大，时间越长，请耐心等待）：");
	num = NumberJudge();
	if (num == 0) {
		printf("退出排序程序\n");
		return ;
	}
	OneRunSort(num);
	system("pause");
	while (num != 0)
	{
		system("cls");
		printf("\t\|                                                   \|\n");
		printf("\t\|  请你输入待排序数列的数字元素的个数 n(按0返回主菜单)（数字越大，时间越长，数字大于十万请耐心等待）：");
		num = NumberJudge();
		if (num == 0) {
			printf("退出排序程序\n");
			return ;
		}
		OneRunSort(num);
		system("pause");
	}
	printf("\t返回主菜单页面\n");
}

//显示多组的排序算法结果的菜单
void GroupSortMenu() {
	int num =0;//数字元素的个数
	system("cls");
	printf("\t\|                                                   \|\n");
	printf("\t\|  请你输入分组的个数 n(按0返回主菜单)");
	group_num = NumberJudge();
	if (group_num == 0) {
		return;
	}
	while (group_num!=0)
	{

		InitGroup();
		numArr = (int*)malloc(group_num * sizeof(int));
		if (numArr == NULL) {
			printf("内存溢出！\n");
			return;
		}

		printf("\t\|  请你依次输入待排序数列的数字元素的个数 e(按0返回主菜单)\n");
		for (int i = 0; i < group_num; i++)
		{
			printf("\t\|  输入第%d个元素\t", i + 1);
			numArr[i] = NumberJudge();
		}

		StorageSortResult();

		printf("\n\t\|下面显示多组排序的结果\n");
		PrintGroupSortResult();

		free(numArr);
		system("cls");
		printf("\t\|                                                   \|\n");
		printf("\t\|  请你输入分组的个数 n(按0返回主菜单)");
		group_num = NumberJudge();
		if (group_num == 0) {
			return;
		}

	}

}

//打印主功能界面
void MainMenu() {
	printf("\t ----------------------------------------------------\n");
	printf("\t\|            六种内部排序算法的性能比较             \|\n");
	printf("\t----------------------------------------------------\n");
	printf("\t\|                                                   \|\n");
	printf("\t\|  1-生成一组目标列表比较各种排序算法的性能         \|\n");
	printf("\t\|  2-生成多组随机数据比较各种排序算法的性能         \|\n");
	printf("\t\|  0-退出该系统                                     \|\n");
	printf("\t\|                                                   \|\n");
	printf("\t\|                                                   \|\n");
	printf("\t ----------------------------------------------------\n");
	printf("\t请输入你要选择的序号：");
}
int main() {
	//system("color 1A");
	int  op = 0;
	group_num = 1;//重新变为1，只有一个分组的情况
	MainMenu();
	op = NumberJudge();
	while (op)
	{
		switch (op)
		{
			
			case 1:
				OneSortMenu();
				break;
			case 2:
				GroupSortMenu();
				break;
			default:
				printf("非法输入,请重新输入！\n");
				break;
		}
		system("cls");
		MainMenu();
		op = NumberJudge();
	}
	return 0;
}


