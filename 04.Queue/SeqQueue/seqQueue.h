#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include "common.h"


typedef struct
{
	int *data;
	int capacity;
	int front;
	int rear;
}SeqQueue;

SeqQueue *createSeqQueue(int n);

void releaseSeqQueue(SeqQueue *queue);

int enSeqQueue(SeqQueue *queue, int e);

int deSeqQueue(SeqQueue *queue, int *e);

#endif //SEQQUEUE_H