clear
#gcc test.c -o prog -lpthread
gcc -O3 -msse4 -fopenmp test.c
./prog
