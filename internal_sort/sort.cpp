#define _CRT_SECURE_NO_WARNINGS
#include"SORT.h"


extern int compare_number;//比较次数
extern int move_number;//移动次数

//初始化排序的记录顺序表
Status InitList( RcdSqList& L,RcdType rcd[],int length ) {
	if (length <= 0)
		return FALSE;
	L.rcd = (RcdType*)malloc(((unsigned long long)length + 1) * sizeof(RcdType));

	int i;
	// 消除C6086警告
	if (L.rcd == NULL)
	{
		return OVERFLOW;
	}
	for (i = 1; i <= length; i++)
	{
		L.rcd[i] = rcd[i];
		L.length = length;
		L.size = init_size;
	}
	return OK;
	
}


void swap( int* a, int* b ) {
	int ret = 0;
	ret = *a;
	*a = *b;
	*b = ret;
}

//冒泡排序
void  BubbleSort( RcdSqList& L ) {
	FormattingPrint((char*)__func__);
	compare_number = 0;//比较次数 
	move_number = 0;//移动次数 
	int i, j;
	int flag = 1;
	for (i = 1; i < L.length && flag; i++)
	{
		flag = 0;
		for (j = L.length; j > i; j--)		//冒泡一定是从后往前比较
		{
			if (L.rcd [j].key < L.rcd [j - 1].key)
			{
				swap( &L.rcd[j].key, &L.rcd [j-1].key );
				move_number++;
				flag = 1;						//如果没有交换说明已经排好序了
			}
			compare_number++;
		}
	}

}

//直接插入排序
void InsertSort( RcdSqList& L ){
	FormattingPrint((char*)__func__);
	compare_number = 0;//比较次数 
	move_number = 0;//移动次数 
	int i, j;
	for (i = 1; i < L.length; ++i) {
		if (L.rcd[i+1].key < L.rcd[i].key) { 
			L.rcd [0] = L.rcd [i + 1];
			move_number++;
			j = i + 1;
			do {
				j--;
				L.rcd [j + 1] = L.rcd [j];
				move_number++;
			} while (L.rcd[0].key<L.rcd[j-1].key);
			L.rcd [j] = L.rcd [0];
			move_number++;
		}
		compare_number++;
	}
}

//简单选择排序
void SimpleSort( RcdSqList& L ) {
	FormattingPrint((char*)__func__);
	compare_number = 0;//比较次数 
	move_number = 0;//移动次数 
	for (int i = 0; i < L.length - 1; i++) {
		int min = i;
		for (int j = i + 1; j < L.length; j++) {
			if (L.rcd[min].key > L.rcd[j].key) {//找到最小值得下标
				min = j;
				move_number++;
			}
			compare_number++;

		}
		if (min != i) {//交换最小数L.rcd[min].key和第i位数的位置
			swap(&L.rcd[min].key, &L.rcd[i].key);
			move_number++;

		}

	}

}

//用来递归操作的快速排序
int Partition(RcdSqList& L, int low, int high) {
	L.rcd[0] = L.rcd[low];
	while (low < high) {
		while (low < high && L.rcd[0].key <= L.rcd[high].key) --high;
		compare_number++;
		L.rcd[low].key = L.rcd[high].key;
		move_number++;
		while (low < high && L.rcd[low].key <= L.rcd[0].key) ++low;
		compare_number++;
		L.rcd[high].key = L.rcd[low].key;
		move_number++;
	}
	compare_number++;
	L.rcd[low].key = L.rcd[0].key;
	move_number++;
	return low;
} 

// 对顺序表L中的子序列L.rcd[low..high]进行快速排序
void QuickSort(RcdSqList& L, int low, int high) {
	
	int pivotloc;
	if (low < high) {
		pivotloc = Partition(L, low, high);
		QuickSort(L, low, pivotloc - 1);
		QuickSort(L, pivotloc + 1, high);
	}
} 


//希尔排序
void ShellSort(RcdSqList& L, int dlta[], int t) {
	//按增量序列dlta[0..t-1]对顺序表L作希尔排序。

	FormattingPrint((char*)__func__);
	compare_number = 0;//比较次数 
	move_number = 0;//移动次数 
	for (int k = 0; k < t; ++k)
		ShellInsert(L, dlta[k]); //一趟增量为dlta[k]的插入排序
}
//一趟希尔排序
void ShellInsert(RcdSqList& L, int dk) {
	//对顺序表L作一趟希尔插入排序。
	for (int i = dk + 1; i <= L.length; ++i)
		if (L.rcd[i].key < L.rcd[i - dk].key) {//需将L.rcd[i]插入有序增量子表
			L.rcd[0] = L.rcd[i];//暂存在L.rcd[0]
			move_number++;
			int j;
			for ( j = i - dk; j > 0 && (L.rcd[0].key < L.rcd[j].key); j -= dk)
			{
				L.rcd[j + dk] = L.rcd[j]; //记录后移，查找插入位置
				move_number++;
				compare_number++;
			}
			L.rcd[j + dk] = L.rcd[0];//插入
			move_number++;
			compare_number++;
		}
	compare_number++;
}




