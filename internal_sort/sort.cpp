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


void swap( int* a, int* b ) {
	int ret = 0;
	ret = *a;
	*a = *b;
	*b = ret;
}


//冒泡排序
void  BubbleSort( RcdSqList& L ) {
	char func_buf [50] = { 0 };
	sprintf( func_buf, "%s", __FUNCTION__ );
	printf( "======%s \n", func_buf );
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
				flag = 1;						//如果没有交换说明已经排好序了
			}
		}
	}

}

//直接插入排序
void InsertSort( RcdSqList& L ){
	char func_buf [50] = { 0 };
	sprintf( func_buf, "%s", __FUNCTION__ );
	printf( "======%s \n", func_buf );
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

//一趟希尔排序
void ShellInsert( RcdSqList& L, int dk ) {
	int i, j;
	for(i=1;i==L.length-dk;++i)
		if (L.rcd[i+dk].key<L.rcd[i].key)
		{
			L.rcd [0] = L.rcd [i + dk];
			j = i + dk;
			do
			{
				j -= dk;
				L.rcd [j + dk] = L.rcd [j];
			} while (j-dk>0&&L.rcd[0].key<L.rcd[j-dk].key);
			L.rcd [j] = L.rcd [0];
		}

}
//希尔排序
void ShellSort( RcdSqList& L, int d[],int t) {
	int k;
	for (k = 0; k < t; k++) {
		ShellInsert( L, d [k] );
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
	
	Sort( L );
	PrintList( L );
	//system( "pause" );
	c_end = clock( );
 
	//!<difftime（time_t, time_t）返回两个time_t变量间的时间间隔，即时间差
	printf( "The sort used %f ms by clock()\n", difftime( c_end, c_start ) );
	//system( "pause" );

}

void PrintfTimeForShellSort( RcdSqList& L, void ( Sort )( RcdSqList& L, int d[], int t ) ) {
	time_t c_start, c_end;
	const int t = 3;
	int d [t] = { 5,3,1 };
	c_start = clock( );    //!< 单位为ms

	ShellSort( L,d,t );
	PrintList( L );
	//system( "pause" );
	c_end = clock( );

	//!<difftime（time_t, time_t）返回两个time_t变量间的时间间隔，即时间差
	printf( "The sort used %f ms by clock()\n", difftime( c_end, c_start ) );
}

//单个随机数生成
KeyType SingleRandomNumberGeneration( )
{
	int a;
	     srand( (unsigned )clock(  )*100000 );  //读取系统时间，产生一个种子数值
	     a = rand( );
	     //printf( "%d\n", a );

	return a;
}

//随机数构成的顺序表中的存储空间内容
RcdType* RandomNumberGeneration( int length ) {
	if (length <= 0)
		return NULL;
	RcdType *rcd = (RcdType*)malloc( (length+1)*sizeof(RcdType) ); 
	rcd [0].key = 0;
	for (int i = 1; i <= length; i++)
	{
		rcd [i].key = SingleRandomNumberGeneration();
	}
	return rcd;
}


