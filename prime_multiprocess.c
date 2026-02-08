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
// Getting number of logical processors using lscpu
int get_logical_cores() {
    FILE *fp = popen("lscpu | grep '^CPU(s):' | awk '{print $2}'", "r");
    if (!fp) return 1;

    int cores = 1;
    fscanf(fp, "%d", &cores);
    pclose(fp);
    return cores;
}

int main(int argc, char *argv[]) {
// ==========================================
// Roll 13 AREA: Timer Helper
// ==========================================


// ==========================================
// Roll 14 AREA: Process Manager
// ==========================================


// ==========================================
// Roll 15 AREA: Main Function
// ==========================================

    // TODO: Person 1 connects everything here
    return 0;
}
