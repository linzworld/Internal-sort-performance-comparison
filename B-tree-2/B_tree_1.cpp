#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>         
#include<stdlib.h>
#include<time.h>  
#define BTREELENGTH 50
#define BTLEN (sizeof(BTNode))
#define MAXINT 100  
typedef enum status
{
	TRUE,
	FALSE,
	OK,
	ERROR,
	OVERFLOW,
	EMPTY
}Status;
typedef int KeyType;

//**********************************B树****************************************
#define  m  3   // B树的阶，此设为4
typedef struct
{
	KeyType  key;
	char     data;
} Record;
typedef struct BTNode
{
	int             keynum;        // 结点中关键字个数，即结点的大小
	struct BTNode* parent;        // 指向双亲结点
	KeyType         key [m + 1];      // 关键字向量，0号单元未用
	struct BTNode* ptr [m + 1];      // 子树指针向量
//  Record         *recptr[m + 1];   // 记录指针向量，0号单元未用
									 //在此添加其他自定义数据
} BTNode, * BTree;                // B树结点和B树的类型
typedef struct
{
	BTNode* pt;      // 指向找到的结点
	int      i;       // 1..m，在结点中的关键字序号
	int      tag;     // 1:查找成功，0:查找失败
} Result;           // 在B树的查找结果类型   
//**********************************B树****************************************

//**********************************队列***************************************
typedef struct LNode {
	BTree data;     // 数据域
	struct LNode* next;     // 指针域
} LNode, * LinkList;
//**********************************队列***************************************

/***
*  @name           Status InitQueue_L(LinkList &L)
*  @description    初始化队列
*  @return         成功返回OK，开辟空间失败返回OVERFLOW
*  @notice
***/
Status InitQueue_L( LinkList& L )
{ // 初始化一个只含头结点的空单链表L
	if (NULL == ( L = (LNode* )malloc( sizeof( LNode ) ) )) // 生成新结点
		return OVERFLOW;
	L->next = NULL;
	return OK;
}
/***
*  @name           LNode* MakeNode_L(BTree e)
*  @description    构造队列结点
*  @return         返回结点地址
*  @notice
***/
LNode* MakeNode_L( BTree e )
{ // 构造数据域为e的单链表结点
	LNode* p;
	p = (LNode* )malloc( sizeof( LNode ) ); // 分配结点空间
	if (p != NULL)
	{
		p->data = e;
		p->next = NULL;
	}
	return p;
}
/***
*  @name           Status Enqueue_L(LNode *p, BTree e)
*  @description    队列的入队
*  @return         成功返回OK，否则返回ERROR
*  @notice
***/
Status Enqueue_L( LNode* p, BTree e )
{ //在p结点之后插入q结点
	if (NULL == p) return ERROR; // 参数不合理
	while (p->next != NULL)
		p = p->next;
	p->next = MakeNode_L( e );         // 对应图4.11（b）的②，修改p结点的指针域
	return OK;
}

/***
*  @name           Status Dequeue_L(LNode *p, BTree &e)
*  @description    队列的出队
*  @return         成功返回OK，否则返回ERROR
*  @notice
***/
Status Dequeue_L( LNode* p, BTree& e )
{
	// 删除p结点的直接后继结点并用参数e返回被删结点的值
	LNode* q;
	if (NULL == p || NULL == p->next) return ERROR; // 删除位置不合理 
	q = p->next;
	p->next = q->next; // 修改被删结点q的指针域
	e = q->data;
	free( q ); // 释放结点q
	return OK;
}

/***
*  @name           void DestroyQueue(LinkList L)
*  @description    队列的销毁
*  @return         无返回
*  @notice
***/
void DestroyQueue( LinkList L )
{
	// 销毁整个链表
	LinkList p;
	if (L != NULL)
	{
		p = L;
		L = L->next;
		free( p );
		DestroyQueue( L );
	}
}
/***
*  @name           Status  IfEmpty(LinkList L)
*  @description    判断队列是否为空
*  @return         空返回TRUE，不空返回FALSE，否则返回ERROR
*  @notice
***/
Status  IfEmpty( LinkList L )
{
	if (L == NULL) return ERROR;
	if (L->next == NULL) return TRUE;
	return FALSE;
}
/***
*  @name           Status ergodic(BTree T, LinkList L, int newline, int sum)
*  @description    print需要用到的递归遍历程序
*  @return         成功返回OK
*  @notice         此处用到队列
***/
Status ergodic( BTree T, LinkList L, int newline, int sum )
{
	int index;
	BTree p;
	if (T != NULL)
	{
		printf( "[ " );
		Enqueue_L( L, T->ptr [0] );
		for (index = 1; index <= T->keynum; index++)
		{
			printf( "%d ", T->key [index] );
			Enqueue_L( L, T->ptr [index] );
		}
		sum += T->keynum + 1;
		printf( "]" );
		if (newline == 0)
		{
			printf( "\n" );
			newline = sum - 1;
			sum = 0;
		}
		else
		{
			--newline;
		}
	}
	if (IfEmpty( L ) == FALSE)
	{
		Dequeue_L( L, p );
		ergodic( p, L, newline, sum );
	}
	return OK;
}
/***
*  @name           Status print(BTree T)
*  @description    层次遍历并分层输出B树
*  @return         成功返回OK
*  @notice
***/
Status print( BTree T )
{
	LinkList L;
	if (T == NULL)
	{
		printf( "[ ]\n" );
		return OK;
	}
	InitQueue_L( L );
	ergodic( T, L, 0, 0 );
	DestroyQueue( L );
	return OK;
}

/***
*  @name           Status findMax(BTree T, BTree &p,int ans)
*  @description    寻找最大关键字的结点,T为要寻找的树，p为返回的节点,ans为第几个
*  @return         成功返回OK,否则返回ERROR
*  @notice
***/
Status findMax( BTree T, BTree& p, int& ans )
{
	if (T == NULL)
		return ERROR;
	p = T;
	while (p->ptr [p->keynum] != NULL)
	{
		p = p->ptr [p->keynum];
	}
	ans = p->keynum;
	return OK;
}
/***
*  @name           Status findMin(BTree T, BTree &p,int ans)
*  @description    寻找最小关键字的结点,T为要寻找的树，p为返回的节点,ans为第几个
*  @return         成功返回OK,否则返回ERROR
*  @notice
***/
/***
*  @name           Status findBTree(BTree T, BTree &p, int &ans, KeyType k)
*  @description    寻找 ,T为要寻找的树，p为返回的节点，ans为第几个元素，k为要找的值
*  @return         成功返回OK,否则返回ERROR
*  @notice
***/
Status findBTree( BTree T, BTree& p, int& ans, KeyType k )
{
	BTree q;
	int index = 1;
	KeyType  keynow;
	if (T == NULL)
		return ERROR;
	q = T;
	keynow = T->key [1];
	while (q != NULL)                 //深度的遍历
	{
		index = 1;
		keynow = q->key [index];
		while (index <= q->keynum) //节点内对各真值进行遍历
		{
			if (k == keynow)           //找到元素
			{
				p = q;
				ans = index;
				return TRUE;
			}
			if (k > keynow)
			{
				if (index == q->keynum)
				{
					if (q->ptr [index] == NULL)
					{
						p = q;
						ans = q->keynum + 1;
						return FALSE;
					}
					q = q->ptr [index];
					break;
				}
				++index;
				keynow = q->key [index];
				continue;
			}
			if (k < keynow)
			{
				if (q->ptr [index - 1] == NULL)
				{
					p = q;
					ans = index;
					return FALSE;
				}
				q = q->ptr [index - 1];
				break;
			}
		}
	}

	return ERROR;
}
/***
*  @name           Status renewParent(BTree p)
*  @description    告诉孩子们亲身爸爸是谁
*  @return         成功返回OK,否则返回ERROR
*  @notice
***/
Status renewParent( BTree p )
{
	int index;
	if (p == NULL) return ERROR;
	for (index = 0; index <= p->keynum; ++index)
	{
		if (p->ptr [index] != NULL)
		{
			p->ptr [index]->parent = p;
			renewParent( p->ptr [index] );
		}
	}
	return OK;
}
/***
*  @name           int whichSon(BTree T)
*  @description    找出是父亲的第几个孩子
*  @return         成功返回第几个孩子,否则返回-1
*  @notice
***/
int whichSon( BTree T )
{
	int index = -1;
	if (T == NULL) return -1;
	for (index = 0; index <= T->parent->keynum; ++index) //找出是父亲的第几个孩子
	{
		if (T->parent->ptr [index] == T) return index;
	}
	return -1;
}
/***
*  @name           status splitBTree(BTree T)
*  @description    递归实现分裂节点操作
*  @return         成功返回OK,否则返回ERROR
*  @notice
***/
Status splitBTree( BTree T ) //此时分裂的节点一定会是超出最大值的。
{
	BTree t1, t2;
	int index, index_1;
	if (T->parent == NULL)
	{
		t1 = (BTree )malloc( BTLEN );
		if (NULL == t1) return OVERFLOW;
		t2 = (BTree )malloc( BTLEN );
		if (NULL == t2) return OVERFLOW;

		t1->keynum = m / 2;
		t2->keynum = m - ( m / 2 ) - 1;
		t1->parent = T;
		t2->parent = T;
		for (index = 0; index <= m; ++index)  //先全部初始化
		{
			t1->ptr [index] = NULL;
			t1->key [index] = 0;
			t2->ptr [index] = NULL;
			t2->key [index] = 0;
		}
		for (index = 0; index <= m / 2; ++index)  //初始化t1
		{
			t1->ptr [index] = T->ptr [index];
			t1->key [index] = T->key [index];
		}
		t2->ptr [0] = T->ptr [( m / 2 ) + 1];
		for (index = ( m / 2 ) + 2; index <= m; ++index)  //初始化t2
		{
			t2->ptr [index - ( ( m / 2 ) + 1 )] = T->ptr [index];
			t2->key [index - ( ( m / 2 ) + 1 )] = T->key [index];
		}
		T->keynum = 1;
		T->ptr [0] = t1;
		T->ptr [1] = t2;
		T->key [1] = T->key [m / 2 + 1];
		for (index = 2; index <= m; ++index)  //初始化T
		{
			T->ptr [index] = NULL;
			T->key [index] = 0;
		}
		return OK;
	}

	index = whichSon( T );
	for (index_1 = T->parent->keynum; index_1 > index; --index_1) //腾出父亲的位置
	{
		T->parent->ptr [index_1 + 1] = T->parent->ptr [index_1];
		T->parent->key [index_1 + 1] = T->parent->key [index_1];
	}
	T->parent->keynum++;
	T->parent->key [index + 1] = T->key [m / 2 + 1];
	t2 = T->parent->ptr [index + 1] = (BTree )malloc( BTLEN );
	if (NULL == t2) return OVERFLOW;
	for (index = 0; index <= m; ++index)  //先全部初始化
	{
		t2->ptr [index] = NULL;
		t2->key [index] = 0;
	}
	t2->keynum = m - ( m / 2 ) - 1;
	t2->parent = T->parent;
	t2->ptr [0] = T->ptr [( m / 2 ) + 1];
	for (index = ( m / 2 ) + 2; index <= m; ++index)  //初始化t2
	{
		t2->ptr [index - ( ( m / 2 ) + 1 )] = T->ptr [index];
		t2->key [index - ( ( m / 2 ) + 1 )] = T->key [index];
	}
	T->keynum = m / 2;
	for (index = ( m / 2 ) + 1; index <= m; ++index)  //初始化t2
	{
		T->ptr [index] = NULL;
		T->key [index] = 0;
	}
	if (T->parent->keynum == m)
	{
		splitBTree( T->parent );
	}
	return OK;
}
/***
*  @name           Status insertBTree(BTree &T, Record e)
*  @description    插入实现元素的插入
*  @return         成功返回OK,如果存在则返回FALSE，否则返回ERROR
*  @notice
***/
Status insertBTree( BTree& T, Record e )
{
	BTree p;
	int index, temp;
	Status find_flag;
	if (NULL == T)
	{
		T = (BTree )malloc( BTLEN );
		if (NULL == T) return OVERFLOW;
		T->keynum = 1;
		T->parent = NULL;
		for (index = 0; index <= m; ++index)
		{
			T->ptr [index] = NULL;
			T->key [index] = 0;
		}
		T->key [1] = e.key;
		return OK;
	}
	find_flag = findBTree( T, p, temp, e.key );
	if (find_flag == TRUE)
	{
		return FALSE;
	}
	if (find_flag == FALSE)
	{                                //不管怎样先直接插入
		p->keynum++;
		for (index = p->keynum; index > temp; --index)
		{
			p->key [index] = p->key [index - 1];
			p->ptr [index] = p->ptr [index - 1];
		}
		p->ptr [temp] = NULL;
		p->key [temp] = e.key;
		if (p->keynum == m)      //这种情况得分裂
		{
			splitBTree( p );
		}
		renewParent( T );
		return OK;
	}
	return ERROR;
}
/***
*  @name           Status borrowBNode(BTree &T)
*  @description    递归实现，向兄弟借元素，否则和兄弟合并
*  @return         成功返回OK,否则返回ERROR
*  @notice         这种情况应该是T为单元素结点
***/
Status borrowBNode( BTree T )
{
	int mynum, bronum, index;
	BTree b = NULL, f = NULL;
	if (T == NULL) return ERROR;
	f = T->parent;
	if (f == NULL)//考虑父亲结点不存在的情况
	{
		if (T->keynum == 0)
		{
			f = T->ptr [0];
			if (f == NULL)
			{
				free( T );
				return EMPTY;
			}
			for (index = 0; index <= f->keynum; index++)
			{
				T->key [index] = f->key [index];
				T->ptr [index] = f->ptr [index];
			}
			T->keynum = f->keynum;
			free( f );
			renewParent( T );
		}
		return OK;
	}
	mynum = whichSon( T );
	if (mynum == 0)
		bronum = 1;
	else
		bronum = mynum - 1;
	b = f->ptr [bronum];
	if (b->keynum == ( m + 1 ) / 2 - 1) //如果兄弟帮不了你了
	{
		//那么就和这个兄弟合体
		if (bronum < mynum)                    //如果我不是第一个
		{
			b->keynum++;
			b->key [b->keynum] = f->key [mynum];
			b->ptr [b->keynum] = T->ptr [0];
			for (index = 1; index <= T->keynum; index++)
			{
				b->key [index + b->keynum] = T->key [index];
				b->ptr [index + b->keynum] = T->ptr [index];
				b->keynum++;
			}
			free( T );
			for (index = mynum; index <= f->keynum; index++)
			{
				f->key [index] = f->key [index + 1];
				f->ptr [index] = f->ptr [index + 1];
			}
			f->keynum--;
		}
		else
		{
			T->keynum++;
			T->key [T->keynum] = f->key [bronum];
			T->ptr [T->keynum] = b->ptr [0];
			for (index = 1; index <= b->keynum; index++)
			{
				T->key [index + T->keynum] = b->key [index];
				T->ptr [index + T->keynum] = b->ptr [index];
				T->keynum++;
			}
			free( b );
			for (index = bronum; index <= f->keynum; index++)
			{
				f->key [index] = f->key [index + 1];
				f->ptr [index] = f->ptr [index + 1];
			}
			f->keynum--;
		}
		renewParent( f );
		if (f->keynum == ( m + 1 ) / 2 - 2)
		{
			//调用借兄弟的函数
			return borrowBNode( f );
		}
	}
	else//如果兄弟能够帮你
	{
		if (bronum < mynum)                    //如果我不是第一个
		{
			for (index = 1; index <= T->keynum; index++)
			{
				T->key [index + 1] = T->key [index];
				T->ptr [index + 1] = T->ptr [index];
			}
			T->ptr [1] = T->ptr [0];
			T->key [1] = f->key [mynum];
			T->ptr [0] = b->ptr [b->keynum];
			T->keynum++;
			f->key [mynum] = b->key [b->keynum];
			b->key [b->keynum] = 0;
			b->ptr [b->keynum] = NULL;
			b->keynum--;

		}
		else                                    //如果我是第一个
		{
			T->keynum++;
			T->key [T->keynum] = f->key [1];
			T->ptr [T->keynum] = b->ptr [0];
			f->key [1] = b->key [1];
			b->ptr [0] = b->ptr [1];
			for (index = 1; index <= b->keynum; index++)
			{
				b->key [index] = b->key [index + 1];
				b->ptr [index] = b->ptr [index + 1];
			}
			b->keynum--;
		}
	}
	return OK;
}

/***
*  @name           Status deleteBTreeRecord(BTree &T, Record e)
*  @description    实现B树元素的删除
*  @return         成功返回OK,否则返回ERROR
*  @notice
***/
Status deleteBTreeRecord( BTree& T, Record e )
{
	BTree p, q;
	int num, temp, index;
	Status find_flag;
	if (T == NULL)
		return ERROR;
	find_flag = findBTree( T, p, temp, e.key );
	if (find_flag == FALSE)
	{
		return FALSE;
	}
	if (find_flag == TRUE)
	{
		//deleteBTreeBNode(p,temp);
		if (p->ptr [temp] == NULL)                //如果是叶子节点的话
		{
			for (index = temp; index <= p->keynum; ++index)
			{
				p->key [index] = p->key [index + 1];
				p->ptr [index] = p->ptr [index + 1];
			}
			p->keynum--;
			if (p->keynum == ( m + 1 ) / 2 - 2)
			{
				//调用借兄弟的函数
				if (borrowBNode( p ) == EMPTY) T = NULL;
				else renewParent( T );
			}
			return OK;
		}
		else                                    //不是叶子结点的话
		{
			//遍历
			findMax( p->ptr [temp - 1], q, num );//返回的q一定会是叶子节点
			p->key [temp] = q->key [num];
			q->key [num] = 0;
			q->keynum--;
			if (q->keynum == ( m + 1 ) / 2 - 2)
			{
				//调用借兄弟的函数
				if (borrowBNode( q ) == EMPTY) T = NULL;
				else renewParent( T );
			}
			return OK;
		}
		return OK;
	}
	return ERROR;
}
/***
*  @name           Status initBTree(BTree &t)
*  @description    初始化一个空B树
*  @return         成功返回OK
*  @notice
***/
Status initBTree( BTree& t )
{
	t = NULL;
	return OK;
}
/***
*  @name           Status test()
*  @description    针对数据结构实验做的测试函数
*  @return         成功返回OK
*  @notice
***/
Status test( )
{
	// 测试代码
	int n, i;
	int arr [BTREELENGTH];
	BTree a;
	Record  d;
	srand( (unsigned )time( NULL ) );
	n = rand( ) % BTREELENGTH;
	//scanf("%d", &n);                    //可以改为自己输入数据
	printf( "B树的阶为:%d,插入次数为:%d\n", m, n );
	initBTree( a );
	for (i = 0; i < n; i++)
	{
		d.key = rand( ) % MAXINT;
		//scanf("%d", &d.key);            //可以改为自己输入数据
		arr [i] = d.key;
		if (insertBTree( a, d ) == OK)
			printf( "第%d次插入%d:\n", i + 1, d.key );
		else
			printf( "第%d次插入%d不成功:\n", i + 1, d.key );
		print( a );
	}
	for (i = 0; i < n; i++)
	{
		d.key = arr [i];
		if (deleteBTreeRecord( a, d ) == OK)
			printf( "第%d次删除%d:\n", i + 1, d.key );
		else
			printf( "第%d次删除%d不成功:\n", i + 1, d.key );
		print( a );
	}
	return OK;

}
/***
主函数
***/
int  main( )
{
	test( );
	return 0;
}
