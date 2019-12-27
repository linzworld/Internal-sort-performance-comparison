#pragma once
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<math.h> 
#define ListInitSize 20
#define ListIncrement 5
#define INIT_N 3
#define OK 1
#define ERROR 0

typedef struct Student
{
	char num [20];
	char name [20];
	char sex;
	int age;
	int score;
}stu;

typedef int Status;

typedef struct LNode
{
	stu *elem;	//储存空间的基地址 
	Status length;	//当前长度
	Status listsize;	//当前分配的储存容量 
}LNode,*LinkList;

Status InitList( LinkList* L );
//初始化线性表L;
Status ListInsert( LinkList L, Status i, stu s );
//插入记录
void print( LinkList L );
//打印线性表中的信息
void print_single( stu s );
//打印指定学生的信息
void Scan_In( LinkList L );
//输入信息
Status ListDelete( LinkList L, int i, stu* s );
//删除第i条记录
void Sort( LinkList L );
//按照学号升序排列
int LocateElem( LinkList L, stu s, Status( *compare )( stu, stu ) );
//定位某个元素 
void SearchName( LinkList L, Status( *equal )( stu, stu ) );
//按姓名查找 
void Modifyinfo( LinkList L, Status( *equal )( stu, stu ) );
//修改信息
Status EqualName( stu a, stu b );
//比较名字是否相同
void menu( );
