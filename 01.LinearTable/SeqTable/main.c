#include "seqTable.h"


int main()
{
	//申请容量
	int n = 10;

	//申请n个容量的顺序表
	SeqTable *table = createSeqTable(n);
	if(table == NULL)
	{
		return -1;
	}

	for (int i = 0; i < 10; ++i) {
		pushBackSeqTable(table, i + 1);
	}

	//查看数据
	showSeqTable(table);

	pushBackSeqTable(table, 6);	//？？？
	printf("table->data[10] = %d\n", table->data[10]);
	pushBackSeqTable(table, 15);
	// pushBackSeqTable(table, 16);
	// pushBackSeqTable(table, 17);
	// pushBackSeqTable(table, 18);
	printf("table->data[11] = %d\n", table->data[11]);

	showSeqTable(table);

	//删除数据
	deleteSeqTable(table, 15);

	showSeqTable(table);

	//释放
	releaseSeqTable(table);

	return 0;
}