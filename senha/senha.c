#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define SCHEDULE_CHUNK_SIZE 100000

FILE *popen(const char *command, const char *type);

double rtclock()
{
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday (&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d",stat);
    return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}

typedef enum { false = 0, true = 1} bool;

int main () {
  int nt;

  char filename[100];
  double t_start, t_end;

  bool found = false; 
  int i;
  scanf("%d", &nt);
  scanf("%s", filename);

  t_start = rtclock();
#pragma omp parallel for num_threads(nt) schedule(static, SCHEDULE_CHUNK_SIZE) \
  default(none) shared(stdout, filename, nt, found) private(i) 
  for(i=0; i < 500000; i++){
    //variaveis utlizadas dentro do loop sao privadas.
    char finalcmd[300] = "unzip -P%d -t %s 2>&1";
    char cmd[400];
    char ret[200];
    FILE * fp;
    sprintf((char*)&cmd, finalcmd, i, filename);
    //printf("Comando a ser executado: %s \n", cmd); 

    fp = popen(cmd, "r");	
    while (!feof(fp)) {
      fgets((char*)&ret, 200, fp);
      if (strcasestr(ret, "ok") != NULL) {
        fprintf(stdout, "Senha:%d\n", i);
        //finalize o loop nesta thread
        i = 500000;
        //notifique as outras threads
        found = true;
      //verifique se a senha ja foi encontrada (por outras threads inclusive)
      } else if (found) {
        //Alguma thread encontrou a senha. Finalize o loop
        i = 500000;
      }
    }
   pclose(fp);
 }
 t_end = rtclock();

 fprintf(stdout, "%0.6lf\n", t_end - t_start);  
}
/* SCHEDULE_CHUNK_SIZE = 500000/nt
 *
 *                             Tempos
 *          Threads  Senha   Serial  Paralelo Speedup
 * arq1.in        2  10000   26.490    25.593   1.035
 * arq2.in        2 100000  283.918   249.978   1.135
 * arq3.in        4 450000 1052.046   173.694   6.056
 * arq4.in        4 310000  656.431   139.239   4.714
 * arq5.in        8  65000  140.507     8.792  15.981
 * arq6.in        4 245999  496.951   278.543   1.784
 *
 * Com base na divisao de workload por chunks, temos que:
 *   arq1 nao teve ganho consideravel em performance pois a segunda thread começou a 
 * tentar a senha a partir do valor 250000, levando mesmo tempo similar
 * ao serial para chegar a senha
 *   arq2 logica parecida ao primeiro arquivo de entrada
 *   arq3 teve um ganho de desempenho consideravel, pois as threads começaram nos valores
 * de senha 0 / 125000 / 250000 / 375000. Ou seja, começando de 375000 na ultima thread
 * para alcancar a senha 450000 leva o mesmo tempo que o programa serial levaria pra tentar
 * a senha 450000 - 375000 = 75000. Numero este 6x menor que 450000, justamente o valor do
 * speedup.
 *   arq5 teve um ganho de desempenho excelente, pois as threads comecaram em multiplos de
 *   62500. Assim, a segunda thread comecou bem proxima a senha 65000.
 *   arq6 A segunda thread comecou em 125000, obtendo um ganho significativo de speedup.
 *
 *
 * Em seguida trocamos SCHEDULE_CHUNK_SIZE = 100000
 *
 *                             Tempos
 *          Threads  Senha   Serial  Paralelo   Speedup
 * arq1.in        2  10000   26.490    25.974     1.019
 * arq2.in        2 100000  283.918     0.030  9463.900 << Senha encontrada rapidamente
 * arq3.in        4 450000 1052.046   366.040     2.874
 * arq4.in        4 310000  656.431    24.485    26.809
 * arq5.in        8  65000  140.507   177.078     0.793 << Overhead de threads somente
 * arq6.in        4 245999  496.951   104.274     4.765
 */
