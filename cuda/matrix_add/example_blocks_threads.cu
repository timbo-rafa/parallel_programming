#define N (2048 * 2048)
#define THREADS_PER_BLOCK 512

__global__ void add(int *a, int *b, int *c) {
  int index = threadIdx.x + blockIdx.x * blockDim.x;
  c[index] = a[index] + b[index];
}

void random_ints(int *a, int n){
  int i;
  for(i = 0; i < n; i++){
    a[i] = i;
  }
}

int main(void) {
  int *a, *b, *c;
  int *d_a, *d_b, *d_c;
  int size = N * sizeof(int);

  //allocate space for device copies of a, b, c
  cudaMalloc((void **)&d_a, size);
  cudaMalloc((void **)&d_b, size);
  cudaMalloc((void **)&d_c, size);

  //allocate space for host copies of a, b, c and setup input values
  a = (int *) malloc(size); random_ints(a, N);
  b = (int *) malloc(size); random_ints(b, N);
  c = (int *) malloc(size);

  //copy inputs to device
  cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);

  //Launch add() kernel on GPU with N threads
  add<<<N/THREADS_PER_BLOCK, THREADS_PER_BLOCK>>>(d_a, d_b, d_c);

  //copy result back to host
  cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);
  
  //cleanup
  cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
  return 0;
}
