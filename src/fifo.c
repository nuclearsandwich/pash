int fifo_peek(int fifoc, int fifo[], int *fifohead, int level) {
	int i = *fifohead - level;
	if (i < 0) {
		i += fifoc;
	}
	return fifo[i];
}

int fifo_push(int fifoc, int fifo[], int *fifohead, int newitem) {
	if (++*fifohead >= fifoc) {
		*fifohead -= fifoc;
	}
	return fifo[*fifohead] = newitem;
}


