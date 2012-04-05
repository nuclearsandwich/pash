CC=gcc
CFLAGS=-Wall -g -I.

sh142: main.c
	$(CC) -o $@ -lreadline $^ $(CFLAGS)

readspew: readspew.c
	$(CC) -o $@ -lreadline $^ $(CFLAGS)

echo.o: echo.c
	$(CC) -o $@ -lreadline $^ $(CFLAGS)

modules.png: modules.dot
	dot $^ -Tpng >$@

cuke:
	cucumber features/

# Eventually extend to also run cunit tests.
test: testutils cuke

testutils: exitwith succeed fail

clean:
	rm *.o sh142

.PHONY: clean cuke test

