#include "seqStack.h"


int main()
{
	SeqStack *stack = createSeqStack();
	if(stack == NULL)
	{
		return -1;
	}

	for (int i = 0; i < 5; ++i) {
		pushSeqStack(stack, i + 10);
	}

	pushSeqStack(stack, 100);

	int e;
	int res = popSeqStack(stack, &e);
	while(!res)
	{
		printf("%d\t", e);
		res = popSeqStack(stack, &e);
	}

	releaseSeqStack(stack);

	return 0;
}