int fifo_peek(int fifoc, int fifo[], int *fifohead, int level) {
	if ((level -= *fifohead) < 0) {
		level += fifoc;
	}
	return fifo[level];
}

int fifo_push(int fifoc, int fifo[], int *fifohead, int newitem) {
	if (++*fifohead > fifoc) {
		fifohead -= fifoc;
	}
	return fifo[*fifohead] = newitem;
}


