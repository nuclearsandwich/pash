CFLAGS=-Wall -g

cuke:
	cucumber features/

# Eventually extend to also run cunit tests.
test: cuke

