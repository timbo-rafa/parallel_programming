FLAGS := -std=c99 -Wall -pedantic -fopenmp -lm -pg
WARN_FLAGS := $(FLAGS) -Wextra -Wconversion -Wshadow -Wpointer-arith \
	-Wcast-align -Wstrict-prototypes -Wwrite-strings -Wswitch-default -Wswitch-default \
	-Wswitch-enum -Wunreachable-code -Wuninitialized -Wfloat-equal -Wundef \
	-g3 #-Werror
prod_cons_paralelo: 
	gcc $(FLAGS) -o prod_cons_paralelo prod_cons_paralelo.c

warn:
	gcc $(WARN_FLAGS) -o prod_cons_paralelo prod_cons_paralelo.c

rigid: warn

all: prod_cons_paralelo

clean:
	rm prod_cons_paralelo
