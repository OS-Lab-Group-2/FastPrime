"""
GROUP PROJECT: Python Plotter
-----------------------------
Person 1: Main Config & Execution
Person 2: System Checks
Person 3: Subprocess Runner
Person 4: Data Collection Logic
Person 5: Plotting & Saving
"""
import subprocess
import matplotlib.pyplot as plt
import os

# ==========================================
# Roll 17 AREA: Runner
c_executable = "./prime_multiprocess"

ranges = [
    (1000, 10000),
    (50000, 100000),
    (100000, 500000)
]

# Get logical processors dynamically
max_processes = os.cpu_count()
plt.figure(figsize=(10, 6))
# ==========================================

if not os.path.exists(c_executable):
    print("Executable not found. Compile C code first.")
    exit()

for rl, rh in ranges:
    print(f"\nRunning benchmarks for range {rl}-{rh}")
    x = []
    y = []


# ==========================================
# Roll 19 AREA: Visualizer
# ==========================================

    for p in range(1, max_processes + 1):
        result = subprocess.run(
            [c_executable, str(rl), str(rh), str(p)],
            capture_output=True,
            text=True
        )

        time_taken = float(result.stdout.strip())
        x.append(p)
        y.append(time_taken)
        print(f"Processes: {p} | Time: {time_taken:.6f}s")

    plt.plot(x, y, marker='o', label=f"{rl}-{rh}")


# ==========================================
# Roll 20 AREA: Main Configuration
# ==========================================
