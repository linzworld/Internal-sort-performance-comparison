//放置一些常用的工具
#define _CRT_SECURE_NO_WARNINGS
#include"SORT.h"
extern int delay_time ;//延时时间的设置

//格式化输出字符串
void FormattingPrint(char* str) {
	printf("=====");
	printf("%s",str);
	printf("=====");
	printf("\n");
}

//打印顺序表中的值
void PrintList(RcdSqList& L) {
	for (int i = 1; i <= L.length; i++)
	{
		Sleep(delay_time);// 滞停1s打印a

		printf("%d ", L.rcd[i].key);
	}
	printf("\n");
}
//打印排序函数所需的时间
void PrintfTime(RcdSqList& L, void (Sort)(RcdSqList&)) {
	time_t c_start, c_end;
	c_start = clock();    //!< 单位为ms
	Sort(L);
	c_end = clock();
	PrintList(L);

	//!<difftime（time_t, time_t）返回两个time_t变量间的时间间隔，即时间差
	printf("The sort used %f ms by sort()\n", difftime(c_end, c_start));
}
//希尔排序的打印函数
void PrintfTimeForShellSort(RcdSqList& L, int d[], int d_length) {
	time_t c_start, c_end;
	c_start = clock();    //!< 单位为ms
	ShellSort(L, d, d_length);
	c_end = clock();
	PrintList(L);

	//!<difftime（time_t, time_t）返回两个time_t变量间的时间间隔，即时间差
	printf("The sort used %f ms by sort()\n", difftime(c_end, c_start));
}
//快速排序的打印函数
void PrintfTimeForQuickSort(RcdSqList& L, int low, int high) {
	time_t c_start, c_end;
	c_start = clock();    //!< 单位为ms
	QuickSort(L, low, high);
	c_end = clock();
	PrintList(L);
	//!<difftime（time_t, time_t）返回两个time_t变量间的时间间隔，即时间差
	printf("The sort used %f ms by sort()\n", difftime(c_end, c_start));
}
//随机数构成的顺序表中的存储空间内容
RcdType* RandomNumberGeneration(int length) {
	if (length <= 0)
		return FALSE;
	RcdType* rcd = (RcdType*)malloc(((unsigned long long)length + 1) * sizeof(RcdType));
	// 消除C6086警告
	if (rcd == NULL)
		return NULL;
	rcd[0].key = 0;

	srand((unsigned)time(NULL));

	int i;
	for ( i = 1; i <= length; i++)
	{
		rcd[i].key = rand()%length;
	}
	return rcd;
}