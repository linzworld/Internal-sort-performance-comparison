#define _CRT_SECURE_NO_WARNINGS
#include"SORT.h"

int main( ) {
	RcdSqList L;
	const int length = 10;
	RcdType rcd[length+1] = { 0,9,3,2,7,4,8,6,5,0,1};//第一个位置闲置
	//RcdType* rcd = RandomNumberGeneration( length+1 );
	InitList( L, rcd, length );
	PrintList( L );
	
	//InsertSort( L );
	//PrintList( L );
	PrintfTime(L, InsertSort );

	InitList( L, rcd, length );
	PrintList( L );
	PrintfTime( L, BubbleSort );

	
	InitList( L, rcd, length );
	PrintList( L );
	PrintfTimeForShellSort( L, ShellSort );
	PrintList( L );
}

