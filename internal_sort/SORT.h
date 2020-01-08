#include<stdio.h>         
#include<stdlib.h>
#include<time.h>  
#include <windows.h>//用于Sleep函数的使用
#ifndef SORT_H
#define SORT_H

#define init_length 10
#define init_size 10

#define OVERFLOW -1
#define OK 1
#define ERROR 0

#define TRUE 1
#define FALSE 0
#define random(x) (rand()%x)


constexpr auto MAXN = 1 << 20;
typedef int KeyType;
typedef int Status;

//单个基本记录的定义
typedef struct {
	KeyType key;
}RecordType,RcdType;

typedef struct {
	RcdType* rcd;//存储空间基址
	int length;//当前长度,0为闲置位
	int size;//当前容量
}RcdSqList;



Status InitList(RcdSqList& L, RcdType rcd[], int length);
void swap( int* a, int* b );
void BubbleSort( RcdSqList& L );
void InsertSort( RcdSqList& L );
void SimpleSort( RcdSqList& L);
void ShellInsert( RcdSqList& L, int dk );
void ShellSort(RcdSqList& L, int d[], int t);
void QuickSort(RcdSqList& L, int low, int high);





void PrintList( RcdSqList& L );
void PrintfTime( RcdSqList& L, void ( Sort )( RcdSqList &) );
RcdType* RandomNumberGeneration( int length );
void PrintfTimeForShellSort( RcdSqList& L,   int d[], int d_length );
void PrintfTimeForQuickSort(RcdSqList& L, int low, int high);
void FormattingPrint(char* str);

#endif 