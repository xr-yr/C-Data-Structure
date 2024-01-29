#include "listTable.h"


int main()
{
	//创建头节点
	ListTable *table = createListTable();
	if(table == NULL)
	{
		return -1;
	}

	//尾插法
	insertlistTableFromTail(table, 1);
	insertlistTableFromTail(table, 2);
	insertlistTableFromTail(table, 3);

	//头插法
	insertlistTableFromHead(table, 4);
	insertlistTableFromHead(table, 5);
	insertlistTableFromHead(table, 6);

	//在pos处插入
	insertlistTableInPos(table, 7, 1);
	insertlistTableInPos(table, 8, 3);
	insertlistTableInPos(table, 9, 7);

	//遍历查看链表数据
	showlistTable(table);

	printf("--------------------\n");

	//指定待删除元素
	deletelistTableForE(table, 15);

	//指定下标删除
	deletelistTableForIndex(table, 0);

	showlistTable(table);

	printf("--------------------\n");

	//查找
	ListNode *node = findlistTable(table, 5);
	if(node)
	{
		printf("find success ---> %d\n", node->data);
	}

	printf("--------------------\n");

	//修改元素
	modifylistTable(table, 100, 10);

	showlistTable(table);

	printf("--------------------\n");

	//元素排序
	sortlisttable(table);

	showlistTable(table);

	printf("--------------------\n");

	//反转链表
	reverselistTable(table);

	showlistTable(table);

	printf("--------------------\n");

	//释放
	releaseListTable(table);

	return 0;
}