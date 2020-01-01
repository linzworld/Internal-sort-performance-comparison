#define _CRT_SECURE_NO_WARNINGS
#include"SORT.h"
//初始化排序的记录顺序表
Status InitList( RcdSqList& L,RcdType rcd[],int length ) {
	L.rcd = (RcdType* )malloc( ( length +1) * sizeof( RcdType ) );
	for (int i = 1; i <= length; i++)
	{
		L.rcd [i] = rcd [i];
		L.length = length;
		L.size = init_size;
	}
	return OK;
}

//直接插入排序
void InsertSort( RcdSqList& L ){
	int i, j;
	for (i = 1; i < L.length; ++i) {
		if (L.rcd[i+1].key < L.rcd[i].key) { 
			L.rcd [0] = L.rcd [i + 1];
			j = i + 1;
			do {
				j--;
				L.rcd [j + 1] = L.rcd [j];
			} while (L.rcd[0].key<L.rcd[j-1].key);
			L.rcd [j] = L.rcd [0];
		}
	}
}
//打印顺序表中的值
void PrintList( RcdSqList &L){
	for (int  i = 1; i <= L.length; i++)
	{
		printf( "%d ",L.rcd[i].key );
	}
	printf( "\n" );
}
//打印排序函数所需的时间
void PrintfTime( RcdSqList& L,void ( Sort )( RcdSqList& ) ) {
	time_t c_start, c_end ;

	c_start = clock( );    //!< 单位为ms
	
	InsertSort( L );
	PrintList( L );
	//system( "pause" );
	c_end = clock( );

	//!<difftime（time_t, time_t）返回两个time_t变量间的时间间隔，即时间差
	printf( "The pause used %f ms by clock()\n", difftime( c_end, c_start ) );
	system( "pause" );

}

//单个随机数生成
KeyType SingleRandomNumberGeneration( )
{
	int a;
	     srand( (unsigned )clock(  )*100000 );  //读取系统时间，产生一个种子数值
	     a = rand( );
	     printf( "%d\n", a );

	return a;
}

//随机数构成的顺序表中的存储空间内容
RcdType* RandomNumberGeneration( int length ) {
	if (length <= 0)
		return NULL;
	RcdType *rcd = (RcdType*)malloc( (length+1)*sizeof(RcdType) ); 
	for (int i = 0; i <= length; i++)
	{
		rcd [i].key = SingleRandomNumberGeneration();
	}
	return rcd;
}


