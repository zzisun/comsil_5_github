#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CNT 5
typedef struct _NODE* NODE_P;
typedef struct _NODE {
	char command[10];
	NODE_P next;
}NODE;
typedef struct {
	NODE_P front;
	int count;
	NODE_P rear;
}QUEUE;
QUEUE* command_list;

void init_queue() {
	command_list = (QUEUE*)malloc(sizeof(QUEUE));
	command_list->count = 0;
	command_list->front = command_list->rear = NULL;
}
void print_queue() {
	NODE_P p;
	int i = 1;
	if (command_list->count == 0)
		printf("NO HISTORY!\n");
	else {
		for (p = command_list->front; p != NULL; p = p->next) {
			printf("%d : %s\n", i++, p->command);
		}
	}
}
void enqueue(char* command) {

	NODE_P new = (NODE*)malloc(sizeof(NODE));
	strcpy(new->command, command);
	new->next = NULL;

	if (command_list->count == 0) {
		command_list->front = command_list->rear = new;
	}
	else {
		command_list->rear->next = new;
		command_list->rear = new;
	}

	command_list->count++;
}
void dequeue() {
	NODE_P dlt;
	dlt = command_list->front;
	command_list->front = dlt->next;
	command_list->count--;

	free(dlt);
}
int main() {

	int flag_quit = 0;
	char c[10];

	init_queue();

	while (1) {
		if (flag_quit)
			break;

		printf(">>");
		scanf("%s", c);
		if (strncmp(c, "quit", 4) == 0)
			flag_quit = 1;
		else if (strncmp(c, "history", 7) == 0) {
			print_queue();
			enqueue(c);
		}
		else
			enqueue(c);

		if (command_list->count > 5)
			dequeue();

	}

	return 0;
}
