#ifndef LISTTABLE_H
#define LISTTABLE_H

#include "common.h"


//定义节点结构
typedef struct listNode
{
	int data;
	struct listNode *next;
}ListNode;

//定义链表表头结构
typedef struct
{
	ListNode *header;
	int cnt;
	int flags;
}ListTable;

//创建表头
ListTable *createListTable();

//释放
void releaseListTable(ListTable *table);

//插入元素, 可头部插入，也可尾部插入，在pos处插入
//创建节点失败返回-1
//尾插法
int insertlistTableFromTail(ListTable *table, int e);

//头插法
int insertlistTableFromHead(ListTable *table, int e);

//在pos处插入
int insertlistTableInPos(ListTable *table, int e, int pos);

//删除元素
//指定待删除元素
void deletelistTableForE(ListTable *table, int e);

//指定下标删除
void deletelistTableForIndex(ListTable *table, int index);

//遍历查看链表数据
void showlistTable(ListTable *table);

//查找
ListNode *findlistTable(ListTable *table, int e);

//修改元素
void modifylistTable(ListTable *table, int e, int new_e);

//元素排序
void sortlisttable(ListTable *table);

//反转链表
void reverselistTable(ListTable *table);

#endif //LISTTABLE_H
