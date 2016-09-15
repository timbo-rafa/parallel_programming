#include <omp.h>
#include <stdio.h>

int main() {
  double x = omp_get_wtime();

  printf("%f\n", x);
  return 0;
}
