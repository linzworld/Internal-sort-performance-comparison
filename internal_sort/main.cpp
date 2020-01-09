#define _CRT_SECURE_NO_WARNINGS
#include"SORT.h"


int delay_time = 0;//延时时间的设置
int compare_number ;//比较次数
int move_number ;//移动次数
const int length = 30;
RcdSqList L;
RcdType* rcd = RandomNumberGeneration(length + 1);

void TestSort( void (Sort)(RcdSqList&) ) {
	 InitList(L, rcd, length);
	 PrintList(L);
	 PrintfTime(L, Sort);

	 printf("\t移动次数m:%d\n", move_number);
	 printf("\t比较次数c:%d\n\n", compare_number);
 }

void TestQuickSort() {
	
}

void test1() {
	RcdSqList L;
	const int length = 10;
	RcdType rcd[length + 1] = { 0,9,3,2,7,4,8,6,5,0,1 };//第一个位置闲置
	//RcdType* rcd = RandomNumberGeneration( length+1 );
	InitList(L, rcd, length);
	PrintList(L);

	//InsertSort( L );
	//PrintList( L );
	PrintfTime(L, InsertSort);
	InitList(L, rcd, length);
	PrintList(L);
	PrintfTime(L, BubbleSort);


	const int d_length = 3;
	int d[d_length] = { 5,3,1 };
	InitList(L, rcd, length);
	PrintList(L);
	PrintfTimeForShellSort(L, d, d_length);
	PrintList(L);
}
//由随机数组成的调用内部排序的主函数
void test2() {
	printf("\n");
	FormattingPrint((char*)"生成随机数的内部排序");
	printf("\n");


	//const int length = 30;
	//RcdType* rcd = RandomNumberGeneration(length + 1);

	TestSort(  BubbleSort);
	TestSort(  InsertSort);
	TestSort(  SimpleSort);
	FormattingPrint((char*)"HeapSort");
	TestSort(  HeapSort );


	const int d_length = 3;
	int d[d_length] = { 5,3,1 };
	InitList(L, rcd, length);
	PrintList(L);
	PrintfTimeForShellSort(L, d, d_length);

	printf("\t移动次数m:%d\n", move_number);
	printf("\t比较次数c:%d\n", compare_number);

	InitList(L, rcd, length);
	PrintList(L);
	FormattingPrint((char*)"QuickSort");
	PrintfTimeForQuickSort(L, 0, L.length);
	printf("\t移动次数m:%d\n", move_number);
	printf("\t比较次数c:%d\n", compare_number);


}
int main( ) {
	system("color 0A");
	printf("请输入控制台打印延时的时间(单位：ms):\t");
	scanf_s("%d",&delay_time);
	//test1();
	test2();

}
