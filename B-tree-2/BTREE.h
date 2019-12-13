#ifndef _BTREE_H
#define _BTREE_H
#define MAXM 10                     //定义B树的最大的阶数
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

Status InitQueue_L( LinkList& L );
#endif 