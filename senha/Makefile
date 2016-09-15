FILE := senha
FLAGS := -std=c99 -Wall -pedantic -pg
LIB_FLAGS := -lpthread -lm  -fopenmp
WARN_FLAGS := $(FLAGS) -Wextra -Wconversion -Wshadow -Wpointer-arith \
	-Wcast-align -Wstrict-prototypes -Wwrite-strings -Wswitch-default -Wswitch-default \
	-Wswitch-enum -Wunreachable-code -Wuninitialized -Wfloat-equal -Wundef \
	-g3 #-Werror

$(FILE): $(FILE).c
	gcc $(FLAGS) -o $(FILE) $(FILE).c $(LIB_FLAGS)

rigid:
	gcc $(WARN_FLAGS) -o $(FILE) $(FILE).c $(LIB_FLAGS)

debug:
	gcc $(WARN_FLAGS) -o $(FILE) $(FILE).c $(LIB_FLAGS) -DDEBUG

verbose: debug

run: $(FILE)
	for i in 1 2 3 ; do \
		./$(FILE) < in/arq$$i.in > out/arq$$i.out ; \
	done

diff: $(FILE)
	for i in 1 2 3 ; do \
		echo diff arq$$i res out ; \
		diff -y res/arq$$i.res out/arq$$i.out ; \
	done

prepare_test:
	./test.sh

all: $(FILE)

clean:
	rm $(FILE)
	rm test -R
	rm -Rf perf
