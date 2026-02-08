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


# ==========================================
# Roll 20 AREA: Main Configuration
# ==========================================


plt.xlabel("Number of Processes (n)")
plt.ylabel("Execution Time (seconds)")
plt.title("FASTprime: n vs Execution Time")
plt.legend()
plt.grid(True)
plt.savefig("fastprime_plot.png")

print("\nPlot saved as fastprime_plot.png")

