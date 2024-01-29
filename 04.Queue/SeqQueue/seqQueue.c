#include "seqQueue.h"


SeqQueue *createSeqQueue(int n) {
	SeqQueue *queue = (SeqQueue*)malloc(sizeof(SeqQueue));
	if(queue == NULL)
	{
		return NULL;
	}

	queue->data = (int*)malloc(sizeof(int) * n);
	queue->capacity = n;
	queue->front = 0;
	queue->rear = 0;

	return queue;
}

void releaseSeqQueue(SeqQueue *queue) {
	if(queue)
	{
		if(queue->data)
		{
			free(queue->data);
		}
		free(queue);
	}
}

int enSeqQueue(SeqQueue *queue, int e) {
	//先判断队列是否满
	if((queue->rear + 1) % queue->capacity == queue->front)
	{
		printf("\nFull queue!\n");
		return -1;
	}
	queue->rear = (queue->rear + 1) % queue->capacity;

	queue->data[queue->rear] = e;

	return 0;
}

int deSeqQueue(SeqQueue *queue, int *e) {
	//先判断队列是否空
	if(queue->rear == queue->front)
	{
		printf("\nEmpty queue!\n");
		return -1;
	}
	queue->front = (queue->front + 1) % queue->capacity;

	if(e)
	{
		*e = queue->data[queue->front];
	}

	return 0;
}
