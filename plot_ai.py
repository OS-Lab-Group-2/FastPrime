import subprocess
import matplotlib.pyplot as plt
import os
import sys

# Configuration
c_source = "prime_ai.c"
exe = "./prime_ai"

# Ranges to test (as per your original request)
ranges = [
    (100, 10000), 
    (100, 100000), 
    (1000, 500000)
]

# 1. Compile the NEW C Code
if not os.path.exists(exe) or os.path.getmtime(c_source) > os.path.getmtime(exe):
    print(f"Compiling {c_source}...")
    ret = os.system(f"gcc {c_source} -o {exe}")
    if ret != 0:
        print("Compilation failed.")
        sys.exit(1)

# 2. Detect Core Count
try:
    # We run the C code without arguments; it defaults to printing core count
    output = subprocess.check_output([exe]).decode().strip()
    max_cores = int(output)
except:
    max_cores = os.cpu_count() or 4

print(f"Detected {max_cores} Cores. Starting Benchmark...")

plt.figure(figsize=(10, 6))

# 3. Run Benchmarks
for rl, rh in ranges:
    print(f"Benchmarking Range: {rl} - {rh}")
    times = []
    procs_list = range(1, max_cores + 1)
    
    for p in procs_list:
        try:
            # Run the C executable
            cmd = [exe, str(rl), str(rh), str(p)]
            result = subprocess.check_output(cmd)
            
            # Parse the time (C code prints ONLY the float value)
            elapsed = float(result.decode().strip())
            times.append(elapsed)
            print(f"  n={p}: {elapsed:.5f}s")
        except subprocess.CalledProcessError:
            print(f"  Error running n={p}")
            times.append(None)

    # Plot
    plt.plot(procs_list, times, marker='o', label=f'Range {rl}-{rh}')

# 4. Finalize Graph
plt.xlabel("Number of Processes (n)")
plt.ylabel("Execution Time (seconds)")
plt.title("Performance: IPC Pipes Implementation")
plt.legend()
plt.grid(True)
plt.xticks(procs_list)

filename = "plot_pipes.png"
plt.savefig(filename)
print(f"\nDone! Graph saved as '{filename}'")
plt.show()
