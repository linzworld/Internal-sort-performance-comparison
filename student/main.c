#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4700)
#include"student.h"

void main( )
{
	LinkList L  = NULL;
	int i, select;
	if (InitList( &L ) != OK)
		printf( "\n\t线性表初始化失败！\n" );
	stu stuArr [INIT_N] = { 
		{"1","马东",'m',18 ,90},
		{"2","李东",'m',19,89 },
		{"3","马西",'f',20,93 } 
	};
	stu* s2 = L->elem;
	menu( );
	scanf( "%d", &select );
	while (select) {
		switch (select) {
			case 0:
				return;
				break;
			case 1:
				for (i = 0; i < INIT_N; i++) {
					printf( "%s %s %c %d %d\n", &stuArr [i].num, &stuArr [i].name, stuArr [i].sex, stuArr [i].age, stuArr [i].score );
					
					if (ListInsert( L, i + 1, stuArr [i] ) != OK)
						printf( "\t初始化数据失败！\n" );
				}
				if (i == INIT_N)
					printf( "\t初始化数据成功\n\n" );
				print( L );
				printf( "\n输入0：退出，输入11：返回主菜单\t" );
				break;
			case 2:
				print( L );
				printf( "\n输入0：退出，输入11：返回主菜单\t" );
				break;
			case 3:
				Scan_In( L );
				print( L );
				printf( "\n输入0：退出，输入11：返回主菜单\t" );
				break;
			case 4:
				print( L );
				printf( "您想删除第几条通讯录1~%d:\n", L->length );
				int k;
				scanf( "%d", &k );
				stu delete_stu ;
				if (ListDelete( L, k, &delete_stu ) == OK) {
					print( L );
					printf( "\t%-6s 已经删除成功！\n", delete_stu.name );
				}
				printf( "\n输入0：退出，输入11：返回主菜单\t" );
				break;
			case 5:
				               //ModifyName(L,EqualName);
				printf( "\n输入0：退出，输入11：返回主菜单\t" );
				break;
			case 6:
				//                searchName(L,EqualName);
				printf( "\n输入0：退出，输入11：返回主菜单\t" );
				break;
			case 7:
				Sort( L );
				print( L );
				printf( "\n输入0：退出，输入11：返回主菜单\t" );
				break;
			case 11:
				menu( );
				break;
		}
		scanf( "%d", &select );
	}
}
