CC=gcc
OBJ_DIR=obj
INC_DIR=include
SRC_DIR=src
BIN_DIR=bin
DYN_DIR=dylibs
UTIL_DIR=test_utils
LIB_DEPS=-lreadline
CFLAGS=-Wall -g -I$(INC_DIR)

default: bin/pash

testutils: $(patsubst $(UTIL_DIR)/$(SRC_DIR)/%.c,$(UTIL_DIR)/%,$(wildcard $(UTIL_DIR)/$(SRC_DIR)/*.c))

examples: $(patsubst examples/$(SRC_DIR)/%.c,examples/%,$(wildcard examples/$(SRC_DIR)/*.c))

dependencies: $(INC_DIR)/tokenizer.h $(INC_DIR)/parser.h $(INC_DIR)/interpreter.h $(INC_DIR)/fifo.h $(INC_DIR)/chomp.h $(INC_DIR)/path_lookup.h $(OBJ_DIR)/tokenizer.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/interpreter.o $(OBJ_DIR)/fifo.o $(OBJ_DIR)/chomp.o $(OBJ_DIR)/path_lookup.o



examples/%: examples/src/%.c
	$(CC) $(OBJ_DIR)/* $^ $(CFLAGS) $(LIB_DEPS) -o $@

dylibs: $(DYN_DIR)/test_function.so $(DYN_DIR)/path_lookup.so

$(BIN_DIR)/pash: $(SRC_DIR)/main.c dependencies
	$(CC) obj/* $(LIB_DEPS) $(SRC_DIR)/main.c $(CFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) -c $< $(CFLAGS) -o $@

$(DYN_DIR)/%.so: $(SRC_DIR)/%.c
	$(CC) -fPIC -shared -Wl,-soname,$@ $< -o $@

$(UTIL_DIR)/%: $(UTIL_DIR)/$(SRC_DIR)/%.c
	$(CC) -o $@ $< $(CFLAGS)

test: testutils cuke

unit: dylibs
	ruby -r"rake" -r"rake/testtask" -e"Rake::TestTask.new; Rake::Task[:test].invoke"

cuke: bin/pash
	cucumber features/ -t ~@skipme

modules.png: modules.dot
	dot $^ -Tpng >$@

REPORT.pdf: REPORT.latex modules.png
	pdflatex REPORT.latex

clean:
	# Cleaning _NEVER_ fails.
	rm *.o pash obj/* bin/* examples/* test_utils/* &>/dev/null && exit 0 || exit 0

.PHONY: clean cuke test testutils unit default

