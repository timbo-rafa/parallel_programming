alias c='clear && gcc count_sort_paralelo.c -fopenmp -o count_sort_paralelo'
alias p1='clear && gcc count_sort_paralelo.c -fopenmp -o count_sort_paralelo && clear && ./count_sort_paralelo < in/arq1.in > out/arq1.out && diff -y res/arq1.res out/arq1.out'
alias p2='clear && gcc count_sort_paralelo.c -fopenmp -o count_sort_paralelo && clear && ./count_sort_paralelo < in/arq2.in > out/arq2.out && diff -y res/arq2.res out/arq2.out'
alias p3='clear && gcc count_sort_paralelo.c -fopenmp -o count_sort_paralelo && clear && ./count_sort_paralelo < in/arq3.in > out/arq3.out && diff -y res/arq3.res out/arq3.out'
alias s1='clear && gcc count_sort_serial.c -fopenmp -o count_sort_serial && clear && ./count_sort_serial < in/arq1.in > out/arq1.out && diff -y res/arq1.res out/arq1.out'
alias s2='clear && gcc count_sort_serial.c -fopenmp -o count_sort_serial && clear && ./count_sort_serial < in/arq2.in > out/arq2.out && diff -y res/arq2.res out/arq2.out'
