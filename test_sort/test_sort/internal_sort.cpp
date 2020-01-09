/*************************************************
File name: internal_sort.cpp
Author: �����
Version: 1.0
Date: 2020-01-09
Description:�ó�������ͨ��������ݱȽϸ��㷨�Ĺؼ���
			�Ƚϴ����͹ؼ����ƶ���������ͼ�����ʽ��
			��ȡ��ֱ�۸��ܣ���ȫ�Լ�������ɣ�
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
const int NUMBER = 6; //����������㷨����
const int Max = 1000000;
const int GroupMaxCount = 10;//����������������
int arr[Max] = { 0 }, b[Max];//�����������
long long int 
	compare_number[NUMBER] = { 0 }, //�Ƚ�
	swap_number[NUMBER] = { 0 },
	move_number[NUMBER] = { 0 }; 
typedef struct {
	long long int num;//�������е��±�
	long long int sort_time;//�������㷨��Ҫ���ѵ�ʱ�䣨��λ��ms��
	int ranking;//�����㷨������ʱ��Ķ���˳��
} Time;//�����洢�Ƚ���Ϣ�Ľṹ��

typedef struct {
	long long int num[NUMBER];//�������е��±�
	long long int sort_time[NUMBER];//�������㷨��Ҫ���ѵ�ʱ�䣨��λ��ms��
	long long int compare_number[NUMBER];
	long long int swap_number[NUMBER];
	long long int move_number[NUMBER];
	int ranking[NUMBER];//�����㷨������ʱ��Ķ���˳��
} Result;//�����洢�Ƚ���Ϣ�Ľṹ��

typedef struct {
	Result * result;//�������
	int group_count;//������
} Group;//�����洢����Ƚ���Ϣ
int group_num = 1;//���������

Time t[NUMBER];
long long int total_sort_time = 0, total_START = 0, START = 0, total_END = 0, END = 0;

Group g;
int* numArr;

//��ʼ������ĺ���
Group InitGroup( ) {
	//���Ľṹ�������������ڴ�ռ�
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
//��ʼ�����������
void Init(int num) {
	int i;
	if (num >= Max) {
		printf("��������̫�󣡣�����������");
		exit(2);
	}
	srand((unsigned)time(NULL));
	for (i = 0; i < num; i++) {
		b[i] = arr[i] = rand() % 10000;
	}
	return;
}

//��ԭ
void Restore(int num) {
	int i;
	for (i = 0; i < num; i++) {
		arr[i] = b[i];
	}
}
//��������
void InsertSort(int arr[], int n) { // �������ݴ���arr[]��,Ĭ��Ϊ����,����Ϊn

	int i, j;
	for (i = 1; i < n; i++)//ѭ���ӵ�2��Ԫ�ؿ�ʼ
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
			//��a[i]�ŵ���ȷλ����
			arr[j + 1] = temp;
		}
	}

}
//ϣ������
void ShellSort(int arr[], int len) {
	int h = 0, i = 0, j = 0, temp; //���ò���
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
//��ѡ������
void SelectSort(int R[], int n) {
	int i, j, k;
	int  temp;
	for (i = 0; i < n ; ++i) {
		k = i;
		for (j = i + 1; j < n; ++j)  /*���ѭ�����㷨�Ĺؼ���������������������һ����С��Ԫ��*/
			if (R[k] > R[j]) {
				move_number[2]++;
				swap_number[2]++;
				compare_number[2]++;
				k = j;
			}  
		//ÿ�������Ƚ�ʱ���ǰ�С�������������ҽ��������һ�ֱȽ�������
		/*�����3�������СԪ�����������е�һ��Ԫ�صĽ���*/
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
//��������
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
//�鲢����
void MegerSort(int arr[], int low, int high, int len) {
	MSort(arr, arr, low, high, len);
}

//ð������
void  BubbleSort(int* arr, int n) {

	int i, j;
	int flag = 1;
	int  temp;
	for (i = 0; i < n  && flag; i++)
	{
		flag = 0;
		for (j = n; j > i; j--)		//ð��һ���ǴӺ���ǰ�Ƚ�
		{
			compare_number[5]++;
			if (arr[j] <arr[j-1])
			{
				temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;

				swap_number[5]++;
				
				move_number[5] += 3;

				flag = 1;						//���û�н���˵���Ѿ��ź�����
			}
		}
	}

}

//����ֱ�Ӳ�������ϣ������ѡ������ð������
void TestMostSort(int sort_num,int* num,void (Sort)(int* , int ) ) {
	total_START = START = GetTickCount64();
	Init(*num);//��ʼ������

	Sort( arr, *num);


	END = GetTickCount64();
	t[sort_num].sort_time = END - START;
	t[sort_num].num = sort_num;
}

//���Կ�������
void TestQuickSort( int* num ) {
	total_START = START = GetTickCount64();
	Init(*num);//��ʼ������
	QuickSort(arr, 0,*num);
	END = GetTickCount64();
	t[Three_QuickSort].sort_time = END - START;
	t[Three_QuickSort].num = Three_QuickSort;
}


//���Թ鲢����
void TestMegerSort(int* num) {
	total_START = START = GetTickCount64();
	Init(*num);//��ʼ������
	MegerSort(arr, 0, *num - 1, *num);
	END = GetTickCount64();
	t[Three_QuickSort].sort_time = END - START;
	t[Three_QuickSort].num = Three_QuickSort;
}

//ͨ��һ���������������
void PrintOneSortResult() {
	printf("\t\|  �ܹ���ʱΪ��%I64d����\n", total_sort_time);
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\|          -----        �����ڲ������㷨���ܱȽϽ������            ------       \|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| �� �� �� ��\| �ȽϵĴ��� \| �����Ĵ��� \| �ƶ��Ĵ��� \|ʱ�䣨ms��\|ʱ������\|ʱ�临�Ӷ�\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\|ֱ�Ӳ�������\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n", g.result[0].compare_number[0], g.result[0].swap_number[0], g.result[0].move_number[0], g.result[0].sort_time[0], g.result[0].ranking[0]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\| ϣ �� �� ��\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", g.result[0].compare_number[1], g.result[0].swap_number[1], g.result[0].move_number[1], g.result[0].sort_time[1], g.result[0].ranking[1]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\|��ѡ������\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n", g.result[0].compare_number[2], g.result[0].swap_number[2], g.result[0].move_number[2], g.result[0].sort_time[2], g.result[0].ranking[2]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\| �� �� �� ��\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", g.result[0].compare_number[3], g.result[0].swap_number[3], g.result[0].move_number[3], g.result[0].sort_time[3], g.result[0].ranking[3]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\| �� �� �� ��\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", g.result[0].compare_number[4], g.result[0].swap_number[4], g.result[0].move_number[4], g.result[0].sort_time[4], g.result[0].ranking[4]);
	printf("\t ----------------------------------------------------------------------------------\n");

	printf("\t\| ð �� �� ��\|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n", g.result[0].compare_number[5], g.result[0].swap_number[5], g.result[0].move_number[5], g.result[0].sort_time[5], g.result[0].ranking[5]);
	printf("\t ----------------------------------------------------------------------------------\n");
}
//����ͨ���������������
void PrintGroupSortResult() {
	printf("\t\|  �ܹ���ʱΪ��%I64d����\n", total_sort_time);
	int i = 0;
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\|        -----  ����������������£������ڲ������㷨�����ܽ������  ------       \|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t ------------------------------ֱ�Ӳ�������----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| �����ܺ�ʱ\| �ȽϵĴ��� \| �����Ĵ��� \| �ƶ��Ĵ��� \|ʱ�䣨ms��\|ʱ������\|ʱ�临�Ӷ�\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for ( i = 0; i < group_num; i++)
	{
		printf("\t\| ��  %d  �� \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|    n*n   \|\n",i+1, g.result[i].compare_number[0], g.result[i].swap_number[0], g.result[i].move_number[0], g.result[i].sort_time[0], g.result[i].ranking[0]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}


	printf("\t ---------------------------------ϣ������-------------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| �����ܺ�ʱ\| �ȽϵĴ��� \| �����Ĵ��� \| �ƶ��Ĵ��� \|ʱ�䣨ms��\|ʱ������\|ʱ�临�Ӷ�\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| ��  %d  �� \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[1], g.result[i].swap_number[1], g.result[i].move_number[1], g.result[i].sort_time[1], g.result[i].ranking[1]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}

	printf("\t -------------------------------��ѡ������-----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| �����ܺ�ʱ\| �ȽϵĴ��� \| �����Ĵ��� \| �ƶ��Ĵ��� \|ʱ�䣨ms��\|ʱ������\|ʱ�临�Ӷ�\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| ��  %d  �� \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[2], g.result[i].swap_number[2], g.result[i].move_number[2], g.result[i].sort_time[2], g.result[i].ranking[2]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}


	printf("\t -------------------------------�� �� �� ��-----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| �����ܺ�ʱ\| �ȽϵĴ��� \| �����Ĵ��� \| �ƶ��Ĵ��� \|ʱ�䣨ms��\|ʱ������\|ʱ�临�Ӷ�\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| ��  %d  �� \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[3], g.result[i].swap_number[3], g.result[i].move_number[3], g.result[i].sort_time[3], g.result[i].ranking[3]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}

	printf("\t -------------------------------�� �� �� ��-----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| �����ܺ�ʱ\| �ȽϵĴ��� \| �����Ĵ��� \| �ƶ��Ĵ��� \|ʱ�䣨ms��\|ʱ������\|ʱ�临�Ӷ�\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| ��  %d  �� \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[4], g.result[i].swap_number[4], g.result[i].move_number[4], g.result[i].sort_time[4], g.result[i].ranking[4]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}

	printf("\t -------------------------------ð �� �� ��-----------------------------------------\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	printf("\t\| �����ܺ�ʱ\| �ȽϵĴ��� \| �����Ĵ��� \| �ƶ��Ĵ��� \|ʱ�䣨ms��\|ʱ������\|ʱ�临�Ӷ�\|\n");
	printf("\t ----------------------------------------------------------------------------------\n");
	for (i = 0; i < group_num; i++)
	{
		printf("\t\| ��  %d  �� \|%12lld\|%12lld\|%12lld\|%10lld\|%10d\|  n*log2n \|\n", i + 1, g.result[i].compare_number[5], g.result[i].swap_number[5], g.result[i].move_number[5], g.result[i].sort_time[5], g.result[i].ranking[5]);
		printf("\t ----------------------------------------------------------------------------------\n");

	}
	system("pause");
}
//����һ������Ľ��
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

//�洢һ�ε�������
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

//�洢������
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

//��������
void OneRunSort(int num) {
	int i;
	printf("\t\|                                                   \|\n");
	printf("\t ----------------------------------------------------\n");
	printf("\t\|  ���Ե�......                                     \|\n");
	printf("\t\|                                                   \|\n");
	CalculateSortResult(num);
	StorageSortResult();

	PrintOneSortResult();
	return;
}

//����������ֽ��з������жϸ�ʽ�Ƿ�ȫΪʮ����
int NumberJudge() {
	int n;
	int sign = 0;
	int retur;
	do {
		sign = 0;
		retur = scanf_s("%d", &n);//��������n��ʮ�������֣��򷵻�1�����������Ĳ�����
		if (retur == 0) {		//����ѭ����ֱ�������n��ʮ�������֣����˳�ѭ��
			printf("\n�Ƿ����룬���������룡\n");
			for (; getchar() != '\n';);
			sign = -1;
		}
	} while (sign == -1);
	return n;
}

//��ʾֻ��һ��������㷨����Ĳ˵�
void OneSortMenu() {
	int num;//����Ԫ�صĸ���
	
	system("cls");
	printf("\t\|                                                   \|\n");
	printf("\t\|  ����������������е�����Ԫ�صĸ��� n(��0�������˵�)������Խ��ʱ��Խ���������ĵȴ�����");
	num = NumberJudge();
	if (num == 0) {
		printf("�˳��������\n");
		return ;
	}
	OneRunSort(num);
	system("pause");
	while (num != 0)
	{
		system("cls");
		printf("\t\|                                                   \|\n");
		printf("\t\|  ����������������е�����Ԫ�صĸ��� n(��0�������˵�)������Խ��ʱ��Խ�������ִ���ʮ�������ĵȴ�����");
		num = NumberJudge();
		if (num == 0) {
			printf("�˳��������\n");
			return ;
		}
		OneRunSort(num);
		system("pause");
	}
	printf("\t�������˵�ҳ��\n");
}

//��ʾ����������㷨����Ĳ˵�
void GroupSortMenu() {
	int num =0;//����Ԫ�صĸ���
	system("cls");
	printf("\t\|                                                   \|\n");
	printf("\t\|  �����������ĸ��� n(��0�������˵�)");
	group_num = NumberJudge();
	if (group_num == 0) {
		return;
	}
	while (group_num!=0)
	{

		InitGroup();
		numArr = (int*)malloc(group_num * sizeof(int));
		if (numArr == NULL) {
			printf("�ڴ������\n");
			return;
		}

		printf("\t\|  ��������������������е�����Ԫ�صĸ��� e(��0�������˵�)\n");
		for (int i = 0; i < group_num; i++)
		{
			printf("\t\|  �����%d��Ԫ��\t", i + 1);
			numArr[i] = NumberJudge();
		}

		StorageSortResult();

		printf("\n\t\|������ʾ��������Ľ��\n");
		PrintGroupSortResult();

		free(numArr);
		system("cls");
		printf("\t\|                                                   \|\n");
		printf("\t\|  �����������ĸ��� n(��0�������˵�)");
		group_num = NumberJudge();
		if (group_num == 0) {
			return;
		}

	}

}

//��ӡ�����ܽ���
void MainMenu() {
	printf("\t ----------------------------------------------------\n");
	printf("\t\|            �����ڲ������㷨�����ܱȽ�             \|\n");
	printf("\t----------------------------------------------------\n");
	printf("\t\|                                                   \|\n");
	printf("\t\|  1-����һ��Ŀ���б�Ƚϸ��������㷨������         \|\n");
	printf("\t\|  2-���ɶ���������ݱȽϸ��������㷨������         \|\n");
	printf("\t\|  0-�˳���ϵͳ                                     \|\n");
	printf("\t\|                                                   \|\n");
	printf("\t\|                                                   \|\n");
	printf("\t ----------------------------------------------------\n");
	printf("\t��������Ҫѡ�����ţ�");
}
int main() {
	//system("color 1A");
	int  op = 0;
	group_num = 1;//���±�Ϊ1��ֻ��һ����������
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
				printf("�Ƿ�����,���������룡\n");
				break;
		}
		system("cls");
		MainMenu();
		op = NumberJudge();
	}
	return 0;
}


