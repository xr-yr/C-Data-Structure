#include "linkQueue.h"

LinkQueue *createLinkQueue() {
	LinkQueue *queue = (LinkQueue*)malloc(sizeof(LinkQueue));
	if(queue == NULL)
	{
		return NULL;
	}
	queue->front = NULL;
	queue->rear = NULL;

	return queue;
}

void releaseLinkQueue(LinkQueue *queue) {
	QueNode *tmp;
	if(queue)
	{
		while(queue->front)
		{
			tmp = queue->front;
			queue->front = tmp->next;
			free(tmp);
		}
		free(queue);
	}
}

int enLinkQueue(LinkQueue *queue, int e) {
	QueNode *node = (QueNode*)malloc(sizeof(QueNode));
	if(node == NULL)
	{
		return -1;
	}
	node->data = e;
	node->next = NULL;

	if(queue->front)
	{
		queue->rear->next = node;
		queue->rear = node;
	}
	else
	{
		queue->front = node;
		queue->rear = node;
	}

	return 0;
}

int deLinkQueue(LinkQueue *queue, int *e) {
	if(queue->front == NULL)
	{
		printf("\nEmpty queue!\n");
		return -1;
	}

	QueNode *tmp = queue->front;
	if(e)
	{
		*e = tmp->data;
	}
	queue->front = tmp->next;
	free(tmp);

	if(queue->front == NULL)
	{
		queue->rear = NULL;
	}

	return 0;
}
