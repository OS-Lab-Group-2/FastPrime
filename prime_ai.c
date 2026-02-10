#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>

// ---------------------------------------------------------
// LOGIC: Optimized Prime Check (6k +/- 1)
// ---------------------------------------------------------
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

// ---------------------------------------------------------
// LOGIC: Get Cores using 'lscpu' (Requirement)
// ---------------------------------------------------------
int get_cores_from_system() {
    FILE *fp = popen("lscpu", "r");
    if (!fp) return 1;

    char line[256];
    int cores = 1;

    // Parse lscpu output line by line
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "CPU(s):", 7) == 0) {
            // Found the line, parse the number
            char *token = strtok(line, ":"); // "CPU(s)"
            token = strtok(NULL, ":");       // " 8" (value)
            if (token) cores = atoi(token);
            break;
        }
    }
    pclose(fp);
    return (cores < 1) ? 1 : cores;
}

// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------
int main(int argc, char *argv[]) {
    // Helper mode: just print cores if no args provided
    if (argc != 4) {
        printf("%d", get_cores_from_system());
        return 0;
    }

    int rl = atoi(argv[1]);
    int rh = atoi(argv[2]);
    int n_procs = atoi(argv[3]);

    // Cap processes to avoid empty ranges
    if (n_procs > (rh - rl + 1)) n_procs = (rh - rl + 1);

    // Array to store read-end of pipes for each child
    int *pipes = malloc(n_procs * sizeof(int));

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int range = rh - rl + 1;
    int chunk = range / n_procs;
    int remainder = range % n_procs;
    int current_rl = rl;

    // --- STEP 1: Forking & Calculation ---
    for (int i = 0; i < n_procs; i++) {
        int fd[2];
        if (pipe(fd) == -1) { perror("Pipe failed"); exit(1); }

        // Calculate specific range for this child
        int my_chunk = chunk + (i < remainder ? 1 : 0);
        int my_rl = current_rl;
        int my_rh = current_rl + my_chunk - 1;
        current_rl += my_chunk;

        pid_t pid = fork();

        if (pid == 0) {
            // == CHILD PROCESS ==
            close(fd[0]); // Close read end, we only write

            // Iterate and find primes
            for (int num = my_rl; num <= my_rh; num++) {
                if (is_prime(num)) {
                    // Write raw integer to pipe (Binary write is fast)
                    write(fd[1], &num, sizeof(int));
                }
            }
            
            close(fd[1]); // Close pipe to signal EOF to parent
            free(pipes);  // Clean up child's copy of memory
            exit(0);      // Die
        } else {
            // == PARENT PROCESS ==
            close(fd[1]);   // Close write end, we only read
            pipes[i] = fd[0]; // Store read end to collect later
        }
    }

    // --- STEP 2: Collection & File Writing ---
    // The parent acts as the "Master Collector"
    FILE *fout = fopen("prime.txt", "w");
    if (!fout) { perror("File error"); exit(1); }

    int prime_buffer;
    
    // Read from children sequentially to keep order sorted
    for (int i = 0; i < n_procs; i++) {
        // Read raw integers until pipe is empty
        while (read(pipes[i], &prime_buffer, sizeof(int)) > 0) {
            fprintf(fout, "%d\n", prime_buffer);
        }
        close(pipes[i]); // Done with this child
    }
    
    fclose(fout);
    free(pipes);

    // --- STEP 3: Cleanup & Timing ---
    // Wait for all ghosts to leave
    for (int i = 0; i < n_procs; i++) wait(NULL);

    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) + 
                        (end.tv_usec - start.tv_usec) / 1e6;

    printf("%f", time_taken);

    return 0;
}
