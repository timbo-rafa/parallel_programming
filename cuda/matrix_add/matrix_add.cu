#include<stdio.h>

#define THREADS_PER_BLOCK 1024
#define MEDIUM_THREADS_PER_BLOCK 120
#define SMALL_THREADS_PER_BLOCK 8

__global__ void add(int *a, int *b, int *c, int n) {
  int index = blockIdx.x * blockDim.x + threadIdx.x;

  if (index < n)
    c[index] = a[index] + b[index];

}

void random_ints(int *a, int l, int c){
  int i, j;
  for (i = 0; i < l; ++i){
    for (j = 0; j < c; ++j) {
      a[i * c + j] = i + j;
    }
  }
}

int main(void) {
  int *a, *b, *c, nl, nc;
  int *d_a, *d_b, *d_c;
  int n, blockSize, gridSize, i, size;
  long long int sum;
  scanf("%d %d", &nl, &nc);
  n = nl * nc;
  size = sizeof(int) * n;
  //allocate space for device copies of a, b, c
  cudaMalloc(&d_a, size);
  cudaMalloc(&d_b, size);
  cudaMalloc(&d_c, size);

  //allocate space for host copies of a, b, c and setup input values
  a = (int *) malloc(size); random_ints(a, nl, nc);
  b = (int *) malloc(size); random_ints(b, nl, nc);
  c = (int *) malloc(size);

  //copy inputs to device
  cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

  if (n < THREADS_PER_BLOCK) {
    if (n < MEDIUM_THREADS_PER_BLOCK) {
      blockSize = SMALL_THREADS_PER_BLOCK;
      if (n < blockSize) blockSize = 1;
    } else {
      blockSize = MEDIUM_THREADS_PER_BLOCK;
    }
  } else {
    blockSize = THREADS_PER_BLOCK;
  }
  gridSize = (int) ceil((float)n/blockSize);

  //Launch add() kernel on GPU with N threads
  add<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);

  //copy result back to host
  cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

  sum = 0;
  for(i=0; i < n; i++) {
    sum += c[i];
  }
  printf("%lli\n", sum);
  
  //cleanup
  cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
  return 0;
}
