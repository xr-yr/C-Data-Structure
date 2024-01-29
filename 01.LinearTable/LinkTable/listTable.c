#include "listTable.h"


//创建表头
ListTable *createListTable() {
	ListTable *table = (ListTable*)malloc(sizeof(ListTable));
	if(table == NULL)
	{
		printf("table malloc failed!\n");
		return NULL;
	}

	table->header = (ListNode*)malloc(sizeof(ListNode));
	table->header->data = 0;
	table->header->next = NULL;
	table->cnt = 0;
	table->flags = 0;
	return table;
}

//释放
void releaseListTable(ListTable *table) {
	if(table)
	{
		while(table->header->next)
		{
			//释放所有节点
			ListNode *node = table->header->next;
			table->header->next = node->next;
			free(node);
			--table->cnt;
		}
		free(table->header);
		printf("\ntable cnt = %d", table->cnt);
		free(table);
		printf("\ttable release success!\n");
	}
}

//插入元素, 可头部插入，也可尾部插入，在pos处插入
//尾插法
int insertlistTableFromTail(ListTable *table, int e) {
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	if(node ==NULL)
	{
		printf("node malloc failed!\n");
		return -1;
	}
	ListNode *move = table->header;
	//尾插法
	while(move->next)
	{
		move = move->next;
	}
	node->data = e;
	node->next = NULL;
	move->next = node;
	//cnt统计插入元素个数
	++table->cnt;
	return 0;
}

//头插法
int insertlistTableFromHead(ListTable *table, int e) {
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	if(node ==NULL)
	{
		printf("node malloc failed!\n");
		return -1;
	}
	ListNode *move = table->header;

	node->data = e;
	node->next = move->next;
	move->next = node;
	//cnt统计插入元素个数
	++table->cnt;
	return 0;
}

//在pos处插入
int insertlistTableInPos(ListTable *table, int e, int pos) {
	if((table->cnt < pos - 1) || (pos <= 0))
	{
		printf("pos failed!\n");
		return -1;
	}
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	if(node ==NULL)
	{
		printf("node malloc failed!\n");
		return -1;
	}
	ListNode *move = table->header;

	while((pos - 1) && (move->next))
	{
		move = move->next;
		--pos;
	}
	node->data = e;
	node->next = move->next;
	move->next = node;
	//cnt统计插入元素个数
	++table->cnt;
	return 0;
}

//遍历查看链表数据
void showlistTable(ListTable *table) {
	ListNode *node = table->header->next;

	if(node == NULL)
	{
		printf("not insertlistNode!\n");
	}
	while(node)
	{
		printf("%d\t", node->data);
		node = node->next;
	}
	printf("\ncnt = %d\n", table->cnt);
}

//删除元素
//指定待删除元素
void deletelistTableForE(ListTable *table, int e) {
	ListNode *move = table->header;

	if(move->next == NULL)
	{
		//若链表是否插入元素
		printf("not insertlistNode!\n");
		return;
	}

	while(move->next)
	{
		if(move->next->data == e)
		{
			ListNode *tmp = move->next;
			move->next = tmp->next;
			--table->cnt;
			free(tmp);
			return;
		}
		move = move->next;
	}

	//链表中未插入待删除元素
	printf("%d not in listNode!\n", e);
}

//指定下标删除
void deletelistTableForIndex(ListTable *table, int index) {
	if((table->cnt < index - 1) || (index <= 0))
	{
		printf("%d not in 1-%d ---> index failed!\n", index, table->cnt);
		return;
	}

	ListNode *move = table->header;

	while((index - 1) && (move->next))
	{
		move = move->next;
		--index;
	}
	ListNode *tmp = move->next;
	move->next = tmp->next;
	--table->cnt;
	free(tmp);
}

//查找
ListNode *findlistTable(ListTable *table, int e) {
	ListNode *move = table->header;
	if(move == NULL)
	{
		printf("not insertlistNode!\n");
		return NULL;
	}

	while(move->next)
	{
		if(move->next->data == e)
		{
			return move->next;
		}
		move = move->next;
	}

	//未找到
	printf("%d not in listNode!\n", e);
	return NULL;
}

//修改元素
void modifylistTable(ListTable *table, int e, int new_e) {
	ListNode *move = table->header;
	if(move == NULL)
	{
		printf("not insertlistNode!\n");
		return;
	}

	while(move->next)
	{
		if(move->next->data == e)
		{
			move->next->data = new_e;
			return;
		}
		move = move->next;
	}

	//未找到
	printf("%d not in listNode!\n", e);
}

//元素排序
void sortlisttable(ListTable *table) {
	//冒泡排序	其他排序不会
	if(table->header->next == NULL)
	{
		printf("not insertlistNode!\n");
		return;
	}
	ListNode *move;
	ListNode *turn;

	for(turn = table->header->next; turn->next; turn = turn->next)
	{
		for(move = table->header->next; move->next; move = move->next)
		{
			if(move->data < move->next->data)
			{
				int tmp = move->data;
				move->data = move->next->data;
				move->next->data = tmp;
			}
		}
	}
}

//反转链表
void reverselistTable(ListTable *table) {
	ListNode *move = table->header->next;
	ListNode *tmp = move;
	table->header->next = NULL;
	while(move)
	{
		tmp = move->next;
		move->next = table->header->next;
		table->header->next = move;
		move = tmp;
	}
}
