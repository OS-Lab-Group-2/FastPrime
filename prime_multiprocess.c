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
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
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
// ==========================================


// ==========================================
// Roll 15 AREA: Main Function
// ==========================================

    // TODO: Person 1 connects everything here
    return 0;
}
