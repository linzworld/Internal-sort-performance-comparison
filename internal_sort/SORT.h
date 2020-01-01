#include<stdio.h>         
#include<stdlib.h>
#include<time.h>  
#ifndef SORT_H
#define SORT_H
#define init_length 10
#define init_size 10
#define OK 1
#define ERROR 0
typedef int KeyType;
typedef int Status;

typedef struct {
	KeyType key;
}RecordType,RcdType;

typedef struct {
	RcdType* rcd;//存储空间基址
	int length;//当前长度,0为闲置位
	int size;//当前容量
}RcdSqList;

void InsertSort( RcdSqList &L );
Status InitList( RcdSqList& L, RcdType rcd[], int length );
void PrintList( RcdSqList& L );
void  BubbleSort( );
void PrintfTime( RcdSqList& L, void ( InsertSort )( RcdSqList &) );
KeyType  SingleRandomNumberGeneration( );
RcdType* RandomNumberGeneration( int length );
#endif 