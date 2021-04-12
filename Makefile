CC = gcc
#OPT = -O2
OPT = -Og -g
#VERSION = -std=c89
VERSION = -std=c99

FLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic
WARNINGS =
UNUSED_WARNINGS_NIX = -Wno-unused-result -Wno-unused-variable -Wno-unused-but-set-variable
UNUSED_WARNINGS_OSX = -Wno-unused-variable
REMOVE_WARNINGS =

INPUT = ./*.c
OUTPUT = a.out

all: $(shell uname)

Darwin:
	$(CC) $(OPT) $(VERSION) $(FLAGS) $(WARNINGS) $(UNUSED_WARNINGS_OSX) $(REMOVE_WARNINGS) $(INPUT) -o $(OUTPUT)

Linux:
	$(CC) $(OPT) $(VERSION) $(FLAGS) $(WARNINGS) $(UNUSED_WARNINGS_NIX) $(REMOVE_WARNINGS) $(INPUT) -o $(OUTPUT)

clean:
	$(RM) -r $(OUTPUT)
	$(RM) -r ./*.dSYM
	$(RM) -r __intermediate.tsv
	$(RM) -r Rgroupby.tsv
