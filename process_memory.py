import matplotlib.pyplot as plt
import numpy as np
import os

# Data
phases = ["1", "2a", "2b", "2c", "3b"]
values = [
    [2560.19, 2559.07, 2560.30],  # Phase 1
    [3023.91, 3092.44, 3026.18],  # Phase 2a
    [3092.54, 3023.85, 3024.57],  # Phase 2b
    [2714.69, 2715.07, 2713.83],  # Phase 2c
    [2691.83, 2691.29, 2697.98]   # Phase 3b
]

# Compute averages
averages = [np.mean(v) for v in values]

# Plot
plt.figure(figsize=(8, 5))
plt.bar(phases, averages)

# Labels and title
plt.xlabel("Phase")
plt.ylabel("Average Memory Usage (MB)")
plt.title("Average Memory Usage Across Phases")
plt.grid(axis='y', linestyle='', alpha=0.7)

metrics_dir = "metrics"
image_dir = os.path.join(metrics_dir, "image")
comparison_plot_path = os.path.join(image_dir, "memory_comparison.png")
plt.savefig(comparison_plot_path)
plt.close()