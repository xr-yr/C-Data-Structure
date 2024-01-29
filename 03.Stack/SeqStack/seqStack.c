#include "seqStack.h"


SeqStack *createSeqStack() {
	SeqStack *stack = (SeqStack *) malloc(sizeof(SeqStack));
	if (stack == NULL) {
		return NULL;
	}

	stack->top = 0;        //空栈，递增
	//清零
	memset(stack->data, 0, sizeof(stack->data));

	return stack;
}

void releaseSeqStack(SeqStack *stack) {
	if(stack)
	{
		free(stack);
	}
}

int pushSeqStack(SeqStack *stack, int e) {
	if(stack->top >= MAX_STACK_SIZE)
	{
		printf("\nOverflow!\n");
		return -1;
	}
	stack->data[stack->top++] = e;

	return 0;
}

int popSeqStack(SeqStack *stack, int *e) {
	if(stack->top <= 0)
	{
		printf("\nUnderflow!\n");
		return -1;
	}
	--stack->top;
	if(e)
	{
		*e = stack->data[stack->top];
	}

	return 0;
}
