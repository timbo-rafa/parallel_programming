/* 
 * sum_scalar.c - A simple parallel sum program to sum a series of scalars
 */

//	compile as: gcc sum_scalar.c -lpthread -o sum_scalar
//			
//	run as: ./sum_scalar <n> <num_threads>

#include <pthread.h>	
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

#define MAXTHREADS 	8

void *sum(void *p);

// global shared variables
unsigned long int sumtotal = 0;
unsigned long int n;
int numthreads;
pthread_mutex_t mutex;

int main(int argc, char **argv) {
	pthread_t tid[MAXTHREADS];
	int i, myid[MAXTHREADS];
	struct timeval start, end;

	gettimeofday(&start, NULL); /* start timing */

		scanf("%lu %d", &n, &numthreads);
		for (i = 0; i < numthreads; i++) {
			myid[i] = i;
			pthread_create(&tid[i], NULL, sum, &myid[i]);
		}
		for (i = 0; i < numthreads; i++) {
			pthread_join(tid[i], NULL);
		}
		pthread_mutex_destroy(&mutex);
	gettimeofday(&end, NULL); /* end timing */
	long spent = (end.tv_sec * 1000000 + end.tv_usec)
			- (start.tv_sec * 1000000 + start.tv_usec);

	printf("%lu\n%ld\n", sumtotal, spent);

	return 0;
}
//-----------------------------------------------
void *sum(void *p) {
	int myid = *((int *) p);
	unsigned long int start = (myid * (unsigned long int) n) / numthreads;
	unsigned long int end = ((myid + 1) * (unsigned long int) n) / numthreads;
	unsigned long int i;
  unsigned long int local_sum = 0.0;

	for (i = start; i < end; i++) {
		local_sum += 2;
	}
	
	pthread_mutex_lock(&mutex);
	sumtotal += local_sum;
	pthread_mutex_unlock(&mutex);

	return NULL ;
}


/*
 * Time      Original   Padding  Padding Speedup   Private   Private Speedup
 * arq1.in      41759     11591            3.602     20007             2.087
 * arq2.in     219508     52050            4.217     51804             4.237
 * arq3.in     348175     97511            3.570     99830             3.488
 */
