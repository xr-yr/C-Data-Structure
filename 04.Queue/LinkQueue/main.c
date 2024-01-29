#include "linkQueue.h"


int main()
{
	LinkQueue *queue = createLinkQueue();
	if(queue == NULL)
	{
		return -1;
	}

	for (int i = 0; i < 5; ++i) {
		enLinkQueue(queue, i + 10);
	}

	int e;
	int res = deLinkQueue(queue, &e);
	while(!res)
	{
		printf("%d\t", e);
		res = deLinkQueue(queue, &e);
	}

	releaseLinkQueue(queue);

	return 0;
}