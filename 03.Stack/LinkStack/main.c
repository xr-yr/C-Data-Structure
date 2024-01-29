#include "linkStack.h"


int main()
{
	LinkStack *top = createLinkStack();
	if(top == NULL)
	{
		return -1;
	}

	for (int i = 0; i < 5; ++i) {
		pushLinkStack(top, i + 10);
	}

	int e;
	int res = popLinkStack(top, &e);
	while(!res)
	{
		printf("%d\t", e);
		res = popLinkStack(top, &e);
	}

	releaseLinkStack(top);

	return 0;
}