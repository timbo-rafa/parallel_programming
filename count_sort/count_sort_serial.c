#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

double count_sort_serial(double a[], int n) {
	int i, j, count;
	double *temp;
	double start, end, duracao;

	temp = (double *)malloc(n*sizeof(double));

	start = omp_get_wtime();
	for (i = 0; i < n; i++) {
		count = 0;
		for (j = 0; j < n; j++)
			if (a[j] < a[i])
				count++;
			else if (a[j] == a[i] && j < i)
				count++;
		temp[count] = a[i];
	}
	end = omp_get_wtime();

	duracao = end - start;

	memcpy(a, temp, n*sizeof(double));
	free(temp);

	return duracao;
}

//int main(int argc, char *argv[]) {
int main() {
  double *a;
  int nthreads;
  int n;
  int i;
  double duracao;

  scanf("%d %d",&nthreads, &n);
  a = (double *) malloc( (unsigned) n * sizeof(double));
  for (i = 0 ; i < n; i++) {
    scanf("%lf", a + i);
  }
  duracao = count_sort_serial(a, n);
  for (i = 0 ; i < n ; i++) {
    printf("%.2lf ", a[i]);
  }
  printf("\n%lf", duracao);
  free(a); 
  return 0;
}
