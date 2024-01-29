#include "seqQueue.h"


int main()
{
	SeqQueue *queue = createSeqQueue(5);
	if(queue == NULL)
	{
		return -1;
	}

	for (int i = 0; i < 4; ++i) {
		enSeqQueue(queue, i + 10);
	}

	enSeqQueue(queue, 100);

	int e;
	int res = deSeqQueue(queue, &e);
	while(!res)
	{
		printf("%d\t", e);
		res = deSeqQueue(queue, &e);
	}

	releaseSeqQueue(queue);

	return 0;
}