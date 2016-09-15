/* Count Sort Paralelo
 *
 * RA 106228
 * Rafael Timbo Matos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

double count_sort_paralelo(double a[], int n, int nthreads) {
  int i, phase;
  double tmp, duracao, start, end;

  //inicie o temporizador
  start = omp_get_wtime();
  // Utilizaremos um numero de *nthreads*  threads
  // variaveis auxiliares e contadores privados para cada thread
  // vetor e seu tamanho sao compartilhados
# pragma omp parallel num_threads(nthreads) \
    default(none) shared(a, n) private(i, tmp, phase)
  for (phase = 0; phase < n; phase++) {
    // Em uma fase par, ordenamos todas as posicoes pares
    // com a posicao seguinte
    // 0 com 1 ; 2 com 3 ...
    // as iteracoes nao possuem dependencia
    if (phase % 2 == 0) {
#     pragma omp for
      for ( i = 1; i < n; i += 2) {
        if (a[i - 1] > a[i]) {
          tmp = a[i - 1];
          a[i - 1] = a[i];
          a[i] = tmp;
        }
      }
    // Em uma fase impar, ordenamos todas as posicoes impares
    // com a posicao seguinte
    // 1 com 2 ; 3 com 4 ...
    } else {
#     pragma omp for
      for (i = 1; i < n - 1; i += 2) {
        if (a[i] > a[i+1]) {
          tmp = a[i + 1];
          a[i + 1] = a[i];
          a[i] = tmp;
        }
      }
    }
  }
  end = omp_get_wtime();
  duracao = end - start;
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
  duracao = count_sort_paralelo(a, n, nthreads);
  for (i = 0 ; i < n ; i++) {
    printf("%.2lf ", a[i]);
  }
  printf("\n%lf", duracao);
  free(a); 
  return 0;
}
