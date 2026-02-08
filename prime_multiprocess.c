/* * GROUP PROJECT: Prime Benchmark
 * -----------------------------
 * Person 1: Main & Input Parsing
 * Person 2: is_prime() logic
 * Person 3: get_logical_cores()
 * Person 4: Time calculation
 * Person 5: Forking & Process Management
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

// ==========================================
// Roll 11 AREA: Prime Logic
// ==========================================
int is_prime(int n) {
    // TODO: Person 2 implements prime check here
    return 0; 
}

// ==========================================
// Roll 12 AREA: System Info
// ==========================================
int get_logical_cores() {
    // TODO: Person 3 implements core counting here
    return 1; 
}

int main(int argc, char *argv[]) {
// ==========================================
// Roll 13 AREA: Timer Helper
// ==========================================


// ==========================================
// Roll 14 AREA: Process Manager

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
// ==========================================


// ==========================================
// Roll 15 AREA: Main Function
// ==========================================
for (int i = 0; i < n_procs; i++)
        wait(NULL);

gettimeofday(&end, NULL);

double time_taken =(end.tv_sec - start.tv_sec) +(end.tv_usec - start.tv_usec) / 1000000.0;

printf("%f", time_taken);
    // TODO: Person 1 connects everything here
    return 0;
}
