#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <common.h>


typedef struct queNode
{
	int data;
	struct queNode *next;
}QueNode;

typedef struct
{
	QueNode *front;
	QueNode *rear;
}LinkQueue;

LinkQueue *createLinkQueue();

void releaseLinkQueue(LinkQueue *queue);

int enLinkQueue(LinkQueue *queue, int e);

int deLinkQueue(LinkQueue *queue, int *e);

#endif //LINKQUEUE_H