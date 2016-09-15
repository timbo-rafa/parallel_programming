#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void producer_consumer(int *buffer, int size, int *vec, int n) {
	int i, j;
	long long unsigned int sum = 0;
  double end, start, duracao;

  start = omp_get_wtime();
	for(i=0;i<n;i++) {
		if(i % 2 == 0) {	// PRODUTOR
			for(j=0;j<size;j++) {
				buffer[j] = vec[i] + j*vec[i+1];
			}
		}
		else {	// CONSUMIDOR
			for(j=0;j<size;j++) {
				sum += (long long unsigned) buffer[j];
			}
		}
	}
  end = omp_get_wtime();
  duracao = end - start;
	printf("%llu\n%lf",sum, duracao);
}

int main(void) {
  int n, size, nthreads, *buffer, *vec, i;

  scanf("%d %d %d", &nthreads, &n, &size);
  buffer = (int *) malloc( (unsigned) size * sizeof(int));
  vec = (int *) malloc( (unsigned) n * sizeof(int));

  for(i = 0; i < n; i++) {
    scanf("%d", vec + i);
  }
  producer_consumer(buffer, size, vec, n);

  free(buffer); free(vec);
  return 0;
}

/*
 *Architecture:          x86_64
 *CPU op-mode(s):        32-bit, 64-bit
 *Byte Order:            Little Endian
 *CPU(s):                8
 *On-line CPU(s) list:   0-7
 *Thread(s) per core:    2
 *Core(s) per socket:    4
 *Socket(s):             1
 *NUMA node(s):          1
 *Vendor ID:             GenuineIntel
 *CPU family:            6
 *Model:                 60
 *Stepping:              3
 *CPU MHz:               800.000
 *BogoMIPS:              4390.19
 *Virtualization:        VT-x
 *L1d cache:             32K
 *L1i cache:             32K
 *L2 cache:              256K
 *L3 cache:              6144K
 *NUMA node0 CPU(s):     0-7
 *
 * 
 * Speed Up programa serial com flags de otimizacao
 *
 * arq1.in:
 *
 *          O0     O1      O2      O3
 * Time     0.007  0.0015  0.0015  0.0010
 * Speedup  1      4.67    4.67    7.0
 * 
 * arq2.in:
 *          O0     O1      O2      O3
 * Time     0.279  0.058   0.059   0.044
 * Speedup  1      4.81    4.72    6.34
 *
 * arq3.in:
 *          O0     O1      O2      O3
 * Time     2.775  0.525   0.545   0.369
 * Speedup  1      5.285   5.091   7.520
 *
 * Profiling:
 *
 * arq1.in:
 * 
 * Each sample counts as 0.01 seconds.
 *  no time accumulated
 * 
 *   %   cumulative   self              self     total           
 *  time   seconds   seconds    calls  Ts/call  Ts/call  name    
 *   0.00      0.00     0.00        1     0.00     0.00  producer_consumer
 *
 * arq2.in:
 * 
 * Each sample counts as 0.01 seconds.
 *   %   cumulative   self              self     total           
 *  time   seconds   seconds    calls  ms/call  ms/call  name    
 * 100.81      0.27     0.27        1   272.20   272.20  producer_consumer
 *
 * arq3.in:
 * 
 * Each sample counts as 0.01 seconds.
 *   %   cumulative   self              self     total           
 *  time   seconds   seconds    calls   s/call   s/call  name    
 * 100.81      2.78     2.78        1     2.78     2.78  producer_consumer
 */
