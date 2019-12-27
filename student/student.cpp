#define _CRT_SECURE_NO_WARNINGS
#include"student.h"
#include<stdio.h>

Status InitList( LinkList* L )
{
	L.elem = (stu* )malloc( ListInitSize * sizeof( stu ) );
	if (!L.elem)
		exit( -2 );
	L.length = 0;
	L.listsize = ListInitSize;
	return OK;
}

Status ListInsert( LinkList L, Status i, stu s )
{
	stu* newstu;
	int j;
	if (i<1 || i>L.length + 1)
		return ERROR;
	if (L.length >= L.listsize)
	{
		newstu = (stu* )malloc( sizeof( stu ) * ( ListInitSize + ListIncrement ) );
		if (!newstu)
			exit( -2 );
		L.elem = newstu;
		L.listsize += ListIncrement;
	}
	for (j = L.length; j >= i; j--)
	{
		L.elem [j] = L.elem [j - 1];
		L.elem [i - 1] = s;
		L.length++;
	}
	return OK;
}


void print( LinkList L )
{
	int i = 0;
	if (L.length == 0)
	{
		printf( "空表，无任何记录！\n\n" );
		printf( "学号 姓名 性别 年龄 成绩\n" );
		printf( "************************" );
	}
	for (i = 0; i < L.length; i++)
	{
		printf( "%s %s", L.elem [i].num, L.elem [i].name );
		if (L.elem [i].sex == 'm')
			printf( "男" );
		else
			printf( "女" );
		printf( "%d %d", L.elem [i].age, L.elem [i].score );
		printf( "\n" );
	}
	printf( "------------------------------\n" );
}

void print_single( stu s )
{
	printf( "学号 姓名 性别 年龄 成绩\n" );
	printf( "******************************\n" );
	printf( "%s %s", s.num, s.name );
	if (s.sex == 'm')printf( "男" );
	else printf( "女" );
	printf( "%d %d", s.age, s.score );
	printf( "\n" );
	printf( "------------------------------\n" );
}

void Scan_In( LinkList L )
{
	char a [2], b [2];
	int i;
	printf( "输入你要插入的学生信息：\n" );
	do {
		stu s;
		printf( "\t请输入学号：\n" );
		scanf( "%s", s.num );
		printf( "\t请输入姓名：\n" );
		scanf( "%s", s.name );
		printf( "\t请输入性别：（m：男，f：女）\n" );
		scanf( "%c", &s.sex );
		printf( "\t请输入年龄：\n" );
		scanf( "%d", &s.age );
		printf( "\t请输入平均成绩：\n" );
		scanf( "%d", &s.score );
		printf( "\t 请输入你要插入的位置(1<=i<=%d)：", L.length + 1 );
		scanf( "%d", &i );
		printf( "\t是否信息无误，插入信息？（y/n）\n" );
		scanf( "%c", a );
		if (strcmp( a, "y" ) == 0 || strcmp( a, "Y" ) == 0)
			ListInsert( L, i, s );
		printf( "\t是否继续插入？（y/n）\n" );
		scanf( "%c", b );
	} while (strcmp( b, "y" ) == 0 || strcmp( b, "Y" ) == 0);
}

Status ListDelete( LinkList L, int i, stu s )
{
	int j;
	if (i<1 || i>L.length)
		return ERROR;
	else {
		s = L.elem [i - 1];
		for (j = i; j <= L.length; j++)L.elem [j - 1] = L.elem [j];
		L.length--;
		return OK;
	}
}

void Sort( LinkList L )
{
	stu s;
	int i, j;
	for (i = 0; i < L.length - 1; i++)
		for (j = 0; j < L.length - i - 1; j++)
		{
			if (strcmp( L.elem [j].num, L.elem [j + 1].num ) > 0)
			{
				s = L.elem [j];
				L.elem [j] = L.elem [j + 1];
				L.elem [j + 1] = s;
			}
		}
	printf( "*****按照升序排序成功！******\n\n" );
}

int LocateElem( LinkList L, stu s, Status( *compare )( stu, stu ) )
{
	int i = 1;
	stu* p = L.elem;
	for (i = 1; i <= L.length && !compare( *p++, s ); i++)
	{
		if (i <= L.length)
			return i;
		else
			return 0;
	}
	return 0;
}

void searchName( LinkList L, Status( *equal )( stu, stu ) )
{
	stu s;
	int j;
	char a [2];
	do {
		printf( "\t 请输入你要查找的学生的姓名：" );
		scanf( "%s", s.name );
		j = LocateElem( L, s, equal );
		if (!j)printf( "没有查找到你所要查找的学生记录！\n" );
		else print_single( L.elem [j - 1] );
		printf( "\t 您想继续查找吗？(y/n)\t" );
		scanf( "%s", a );
	} while (strcmp( a, "y" ) == 0 || strcmp( a, "Y" ) == 0);
}

void ModifyName( LinkList L, Status( *equal )( stu, stu ) )
{
	stu s;
	int j;
	char num_new [20], name_new [20], sex_new;
	int age_new, score_new;
	char a [2];
	do {
		printf( "\t 请输入你要更改的学生的姓名：" );
		scanf( "%s", s.name );
		j = LocateElem( L, s, equal );
		if (!j)
			printf( "没有查找到你所要查找的学生记录！\n" );
		else {
			print_single( L.elem [j - 1] );
			int isOrNo = 1;
			printf( "\n修改通讯录：1 学号，2 姓名，3 性别，4 年龄，5 成绩，0 取消\n" );
			while (isOrNo)
			{
				printf( "--------------------------\n" );
				printf( "请选择需要修改的属性序号：" );
				scanf( "%d", &isOrNo );
				switch (isOrNo) {
					case 1:
						printf( "请输入更改后的学号：" );
						scanf( "%s", num_new );
						strcpy( L.elem [j - 1].num, num_new );
						break;
					case 2:
						printf( "请输入更改后的姓名：" );
						scanf( "%s", name_new );
						strcpy( L.elem [j - 1].name, name_new );
						break;
					case 3:
						printf( "请输入更改后的性别：" );
						scanf( "%c", &sex_new );
						break;
					case 4:
						printf( "请输入更改后的年龄：" );
						scanf( "%d", &age_new );
						L.elem [j - 1].age = age_new;
						break;
					case 5:
						printf( "请输入更改后的成绩：" );
						scanf( "%d", &score_new );
						L.elem [j - 1].score = score_new;
						break;
				}
			}
			printf( "\n****更改后该条记录变为****\n\n" );
			print_single( L.elem [j - 1] );
		}
		printf( "您想继续修改吗？(y/n)\t" );
		scanf( "%s", a );
	} while (strcmp( a, "y" ) == 0 || strcmp( a, "Y" ) == 0);
}

void menu( )
{
	printf( "\t*********************\n" );
	printf( "\t**欢迎使用学生通讯录管理系统**\n" );
	printf( "\t*********************\n" );
	printf( "\t**请选择如下操作，输入序号**\n" );
	printf( "\t  0：退出系统\n" );
	printf( "\t  1：将初始学生记录插入线性表\n" );
	printf( "\t  2：显示线性表中所有内容\n" );
	printf( "\t  3：向线性表中增加一条记录\n" );
	printf( "\t  4：从线性表中删除一条记录\n" );
	printf( "\t  5：按照姓名修改一条记录\n" );
	printf( "\t  6：按照姓名查找一条记录\n" );
	printf( "\t  7：按照学号升序排列通讯录\n" );
	printf( "\t*********************\n" );
	printf( "\t  您想进行什么操作，请选择\n" );
}
