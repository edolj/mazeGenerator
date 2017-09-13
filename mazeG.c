#include <stdio.h>
#include <stdlib.h>

struct node {
	int x;
	int y;
	struct node *ptr;
}*top, *top1, *temp;

/* Push data into stack */
void push(int dataX, int dataY) {

	if (top == NULL)
	{
		top = (struct node *)malloc(1 * sizeof(struct node));
		top->ptr = NULL;
		top->x = dataX;
		top->y = dataY;
	}
	else
	{
		temp = (struct node *)malloc(1 * sizeof(struct node));
		temp->ptr = top;
		temp->x = dataX;
		temp->y = dataY;
		top = temp;
	}
}

/* Check if stack is empty or not */
int empty() {
	if (top == NULL)
		return 1;
	else
		return 0;
}

/* Display stack elements */
void display() {

	top1 = top;

	if (top1 == NULL)
	{
		printf("Stack is empty\n");
		return;
	}

	while (top1 != NULL)
	{
		printf("[%d %d]\n", top1->x, top1->y);
		top1 = top1->ptr;
	}
}

// to store position of x in y
int x, y;	
/* Pop Operation on stack */
void pop() {

	top1 = top;

	if (top1 == NULL)
	{
		printf("\n Error : Trying to pop from empty stack");
		return;
	}
	else
		top1 = top1->ptr;
	x = top->x;
	y = top->y;
	//printf("Popped value : [%d %d]\n", top->x, top->y);
	free(top);
	top = top1;
}

void printMaze(int visina, int sirina) {
	int i, j;
	for (i = 0; i < visina; i++) {
		for (j = 0; j < sirina; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}

int **maze;

int main() {

	int i, j;
	int visina, sirina;
	
	printf("Type height: ");
	scanf("%d", &visina);
	
	printf("Type width: ");
	scanf("%d", &sirina);

	maze = (int**)malloc(visina * sizeof(int*));
	for (i = 0; i<visina; i++) 
		maze[i] = (int*)malloc(sirina * sizeof(int));

	for (i = 0; i < visina; i++)
		for (j = 0; j < sirina; j++)
			maze[i][j] = 1;

	int vr, st;

	int smeri[] = { 1,2,3,4 };

	int startX = 1;
	int startY = 1;

	maze[startX][startY] = 0;

	push(startX, startY);

	while (top != NULL) {
		pop();
		//printf("[x,y] = %d %d\n",x,y);
		vr = x; st = y;
		//printf("[vr,st] = %d %d\n", vr, st);
		
		int pogoj = 0;
		for (int i = 0; i < 4; i++) {
			int smer = (rand() % 4);
			if (pogoj) break;
			switch (smeri[smer]) {
				case 1: // up 
					if (vr - 2 <= 0)
						continue;
					if (maze[vr - 2][st] != 0) {
						maze[vr - 2][st] = 0;
						maze[vr - 1][st] = 0;
						vr = vr - 2;
						pogoj = 1;
					}
					break;
				case 2: // right
					if (st + 2 >= sirina - 1)
						continue;
					if (maze[vr][st + 2] != 0) {
						maze[vr][st + 2] = 0;
						maze[vr][st + 1] = 0;
						st = st + 2;
						pogoj = 1;
					}
					break;
				case 3:	// down
					if (vr + 2 >= visina - 1)
						continue;
					if (maze[vr + 2][st] != 0) {
						maze[vr + 2][st] = 0;
						maze[vr + 1][st] = 0;
						vr = vr + 2;
						pogoj = 1;
					}
					break;
				case 4: // left
					if (st - 2 <= 0)
						continue;
					if (maze[vr][st - 2] != 0) {
						maze[vr][st - 2] = 0;
						maze[vr][st - 1] = 0;
						st = st - 2;
						pogoj = 1;
					}
					break;
				}
		}
		
		// if all neighbours checked
		if (pogoj == 0 && empty() == 0) {
			pop();
		}
		else {
			push(x, y);
			push(vr, st);
		}
	}

	printMaze(visina, sirina);

	for (i = 0; i<visina; i++)
		free(maze[i]); 
	free(maze);

	getchar();
	return 0;
}