#ifndef SEQSTACK_H
#define SEQSTACK_H

#include "common.h"


#define MAX_STACK_SIZE 5

//栈结构
typedef struct
{
	int data[MAX_STACK_SIZE];
	int top;
}SeqStack;

//申请栈
SeqStack *createSeqStack();

//释放栈
void releaseSeqStack(SeqStack *stack);

//压栈
int pushSeqStack(SeqStack *stack, int e);

//出栈
int popSeqStack(SeqStack *stack, int *e);

#endif //SEQSTACK_H