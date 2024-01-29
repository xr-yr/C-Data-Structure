#include "linkStack.h"


LinkStack *createLinkStack() {
	LinkStack *top = (LinkStack*)malloc(sizeof(LinkStack));
	if(top == NULL)
	{
		return NULL;
	}
	top->data = 0;
	top->next = NULL;

	return top;
}

int pushLinkStack(LinkStack *top, int e) {
	LinkStack *new_data = (LinkStack*)malloc(sizeof(LinkStack));
	if(new_data == NULL)
	{
		printf("malloc failed!\n");
		return -1;
	}

	new_data->data = e;
	new_data->next = top->next;
	top->next = new_data;

	return 0;
}

int popLinkStack(LinkStack *top, int *e) {
	if(top->next == NULL)
	{
		printf("\nUnderflow!\n");
		return -1;
	}
	LinkStack *tmp = top->next;
	top->next = tmp->next;
	*e = tmp->data;
	free(tmp);

	return 0;
}

void releaseLinkStack(LinkStack *top) {
	if(top)
	{
		while (top->next)
		{
			LinkStack *tmp = top->next;
			top->next = tmp->next;
			free(tmp);
		}
		free(top);
	}
}
