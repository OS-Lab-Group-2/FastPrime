 // GROUP PROJECT: Prime Calculation

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
 
}

int get_logical_cores() {
    // TODO: Person 3 implements core counting here
    return 1; 
}

int main(int argc, char *argv[]) {

    if (argc != 4) return 1;

    int rl = atoi(argv[1]);
    int rh = atoi(argv[2]);
    int n_procs = atoi(argv[3]);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int range_size = (rh - rl + 1) / n_procs;

    for (int i = 0; i < n_procs; i++) {
        if (fork() == 0) {
            int start_num = rl + i * range_size;
            int end_num = (i == n_procs - 1) ? rh : start_num + range_size - 1;

            for (int j = start_num; j <= end_num; j++) {
                is_prime(j);   // computation only (benchmarking)
            }
            exit(0);
        }
    }

    for (int i = 0; i < n_procs; i++)
         wait(NULL);

    gettimeofday(&end, NULL);

    double time_taken =(end.tv_sec - start.tv_sec) +(end.tv_usec - start.tv_usec) / 1000000.0;

    printf("%f", time_taken);
    return 0;
}
