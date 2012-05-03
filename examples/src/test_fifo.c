#include <stdio.h>
#include <stdlib.h>
#include "../../include/fifo.h"

#define FIFO_SIZE  5

int main(int argc, char *argv[]) {
	int fifo[FIFO_SIZE];
	int *fifohead;
	int fifoc = FIFO_SIZE;
	int i;
	for (i = i; i < fifoc; i++) {
		fifo[i] = 0;
	}

	*fifohead = 0;

	printf("The value of fifohead is %d\n", *fifohead);

	fifo_push(fifoc, fifo, fifohead, 1);
	fifo_push(fifoc, fifo, fifohead, 2);
	fifo_push(fifoc, fifo, fifohead, 4);
	fifo_push(fifoc, fifo, fifohead, 8);
	fifo_push(fifoc, fifo, fifohead, 16);
	fifo_push(fifoc, fifo, fifohead, 32);

	printf("The value of fifohead is %d\n", *fifohead);
	printf("fifo_peek(..., 0) should be 32 and is in reality %d.\n",
			fifo_peek(fifoc, fifo, fifohead, 0));
	printf("fifo_peek(..., 3) should be 4 and is in reality %d.\n",
			fifo_peek(fifoc, fifo, fifohead, 3));

	return 0;
}

