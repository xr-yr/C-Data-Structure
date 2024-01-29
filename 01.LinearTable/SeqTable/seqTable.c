#include "seqTable.h"


//申请n个容量的顺序表
SeqTable *createSeqTable(int n) {
	SeqTable *table = (SeqTable*)malloc(sizeof(SeqTable));
	if(table == NULL)
	{
		printf("table malloc failed!\n");
		return NULL;
	}
	table->data = (int*)malloc(sizeof(int) * n);
	if(table->data == NULL)
	{
		printf("table->data malloc failed!\n");
		free(table);
		return NULL;
	}
	table->len = 0;
	table->capacity = n;
	return table;
}

//释放
void releaseSeqTable(SeqTable *table) {
	if(table)
	{
		if(table->data)
		{
			free(table->data);
		}
		free(table);
		printf("\nrelease success!\n");
	}
}

//添加数据
void pushBackSeqTable(SeqTable *table, int e) {
	//判断是否需要扩容
	if(table->len >= table->capacity)
	{
		int *new_data = (int*)malloc(sizeof(int) * table->capacity * 2);
		{
			if(new_data == NULL)
			{
				printf("realloc failed!\n");
			}
		}
		//清空new_data	清零
		memset(new_data, 0, table->capacity * 2);
		for (int i = 0; i < table->capacity; ++i) {
			new_data[i] = table->data[i];
		}
		free(table->data);
		table->data = new_data;
		table->len = table->capacity;
		table->capacity = table->capacity * 2;
		printf("realloc success!\n");
	}
	table->data[table->len++] = e;
}

//查看数据
void showSeqTable(SeqTable *table) {
	if(table)
	{
		for (int i = 0; i < table->len; ++i) {
			printf("%d\t", table->data[i]);
		}
	}
	printf("\ntable cnt = %d\n", table->len);
}

//删除数据
//删除最后一个
void deleteSeqTable(SeqTable *table, int e) {
	if(table->data[table->len - 1] == e)
	{
		table->data[table->len--] = 0;
	}
	else
	{
		printf("delete failed!\n");
	}
}
