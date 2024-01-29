#ifndef SEQTABLE_H
#define SEQTABLE_H

#include "common.h"


//定义顺序表结构
typedef struct
{
	int *data;
	int len;			//描述顺序表中元素个数 同时指向待插入位置
	int capacity;		//顺序表容量 判断是否扩容
}SeqTable;

//创建顺序表头
//申请n个容量的顺序表
SeqTable *createSeqTable(int n);

//释放
void releaseSeqTable(SeqTable *table);

//添加数据
void pushBackSeqTable(SeqTable *table, int e);

//删除数据
void deleteSeqTable(SeqTable *table, int e);

//查看数据
void showSeqTable(SeqTable  *table);

#endif //SEQTABLE_H
