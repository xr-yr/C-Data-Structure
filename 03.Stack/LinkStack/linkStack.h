#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "common.h"


typedef struct linkStack
{
	int data;
	struct  linkStack *next;
}LinkStack;

LinkStack *createLinkStack();

int pushLinkStack(LinkStack *top, int e);

int popLinkStack(LinkStack *top, int *e);

void releaseLinkStack(LinkStack *top);

#endif //LINKSTACK_H