CC = gcc
OPT = -O2
#OPT = -Og -g
VERSION = -std=c89

FLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -Wpedantic
WARNINGS =
UNUSED_WARNINGS = -Wno-unused-variable
REMOVE_WARNINGS =

INPUT = ./*.c
OUTPUT = a.out

all: default

default:
	$(CC) $(OPT) $(VERSION) $(FLAGS) $(WARNINGS) $(UNUSED_WARNINGS) $(REMOVE_WARNINGS) $(INPUT) -o $(OUTPUT)

clean:
	$(RM) -r $(OUTPUT)
	$(RM) -r ./*.dSYM
	$(RM) -r __intermediate.tsv
	$(RM) -r Rgroupby.tsv
