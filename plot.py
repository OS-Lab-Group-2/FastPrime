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
# ==========================================


# ==========================================
# Roll 18 AREA: Data Collector
# ==========================================


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
