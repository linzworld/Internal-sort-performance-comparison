#define _CRT_SECURE_NO_WARNINGS
#include"BTREE.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void Test1( ) {
	system( "color 70" );
	BTNode* t = NULL;
	Result s;                                       //设定查找结果 
	int j, n = 15;
	KeyType k;
	KeyType a[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	printf( "创建一棵%d阶B树:\n", m );
	for (j = 0; j < n; j++) {                               //逐一插入元素 
		s = SearchBTree( t, a [j] );
		if (s.tag == 0)
			InsertBTree( t, s.i, a [j], s.pt );
		printf( "   第%d步,插入元素%d:\n ", j + 1, a [j] );
		PrintBTree( t );
	}

	printf( "\n" );
	printf( "删除操作:\n" );                          //删除操作 
	k = 9;
	BTreeDelete( t, k );
	printf( "  删除%d:\n ", k );
	printf( "  删除后的B树: \n" );
	PrintBTree( t );
	printf( "\n" );

	k = 1;
	BTreeDelete( t, k );
	printf( "  删除%d:\n ", k );
	printf( "  删除后的B树: \n" );
	PrintBTree( t );
	printf( "\n" );

	printf( "  递归释放B树\n" );                       //递归释放B树
	DestroyBTree( t );
	PrintBTree( t );
}

void Test2( ) {
	int i, k;
	system( "color 70" );
	BTree t = NULL;
	Result s;                                       //设定查找结果 
	//printf( "Enter number for degree of the tree:_____\b\b\b" );
	//scanf( "%d", &m );
	//int* p;//通过指针变量改变全局变量
	//p = &Max;
	//*p = m - 1;
	//p = &Min;
	//*p = ( m - 1 ) / 2;
	while (1) {
		//system( "cls" );
		printf( "============================================\n" );
		printf( "B树的阶数为%d:\n", m );
		printf( "此时的B树：\n" );
		PrintBTree( t );
		printf( "\n" );
		printf( "=============Operation Table=============\n" );
		printf( "   1.Init     2.Insert    3.Delete    \n" );
		printf( "   4.Destroy  5.Exit      \n" );
		printf( "=========================================\n" );
		printf( "Enter number to choose operation:_____\b\b\b" );
		scanf( "%d", &i );
		switch (i) {
			case 1: {
					InitBTree( t );
					printf( "InitBTree successfully.\n" );
					break;
				}


			case 2: {
					printf( "Enter number to InsertBTree:_____\b\b\b" );
					scanf( "%d", &k );
					s = SearchBTree( t, k );
					InsertBTree( t, s.i, k, s.pt );
					printf( "InsertBTree successfully.\n" );
					break;
				}
			case 3: {
					printf( "Enter number to DeleteBTree:_____\b\b\b" );
					scanf( "%d", &k );
					BTreeDelete( t, k );
					printf( "\n" );
					printf( "DeleteBTree successfully.\n" );
					break;
				}
			case 4: {
					DestroyBTree( t );
					break;
					printf( "DestroyBTree successfully.\n" );
				}
			case 5: {
					exit( -1 );
					break;
				}
		}
	}
}

int main( ) {
	//Test1( );
	Test2( );
	return 0;
}