CC=gcc
OBJ_DIR=obj
INC_DIR=include
SRC_DIR=src
BIN_DIR=bin
DYN_DIR=dylibs
UTIL_DIR=test_utils
LIB_DEPS=-lreadline
CFLAGS=-Wall -g -I$(INC_DIR)

testutils: $(patsubst $(UTIL_DIR)/$(SRC_DIR)/%.c,$(UTIL_DIR)/%,$(wildcard $(UTIL_DIR)/$(SRC_DIR)/*.c))

examples: $(patsubst examples/$(SRC_DIR)/%.c,examples/%,$(wildcard examples/$(SRC_DIR)/*.c))

dylibs: $(DYN_DIR)/test_function.so $(DYN_DIR)/path_lookup.so

$(BIN_DIR)/sh142: $(SRC_DIR)/main.c
	$(CC) -o $@ $(LIB_DEPS) $^ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(DYN_DIR)/%.so: $(SRC_DIR)/%.c
	$(CC) -fPIC -shared -Wl,-soname,$@ -o $@ $<

$(UTIL_DIR)/%: $(UTIL_DIR)/$(SRC_DIR)/%.c
	$(CC) -o $@ $< $(CFLAGS)

test: testutils cuke

unit: dylibs
	ruby -r"rake" -r"rake/testtask" -e"Rake::TestTask.new; Rake::Task[:test].invoke"

cuke:
	cucumber features/ -t ~@skipme

modules.png: modules.dot
	dot $^ -Tpng >$@

REPORT.pdf: REPORT.latex modules.png
	pdflatex REPORT.latex

clean:
	# Cleaning _NEVER_ fails.
	rm *.o sh142 obj/* bin/* examples/* test_utils/* &>/dev/null && exit 0 || exit 0

.PHONY: clean cuke test testutils unit

