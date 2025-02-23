import os
import pandas as pd
import matplotlib.pyplot as plt
import re

# Function to extract float values from log lines
def extract_float(pattern, line, default=0.0):
    match = re.search(pattern, line)
    return float(match.group(1)) if match else default

# Function to parse log files
def parse_runs(filename):
    data = []
    with open(filename, "r") as file:
        content = file.read()

    runs = content.split("Run #")[1:]  # Split based on "Run #" but exclude first empty entry
    for run in runs:
        lines = run.strip().split("\n")

        # Extract values using regex
        run_number = int(lines[0])
        load_time = extract_float(r"(\d+\.\d+) seconds", lines[1])
        zipcode_time = extract_float(r"(\d+\.\d+) seconds", lines[2])
        injuries_time = extract_float(r"(\d+\.\d+) seconds", lines[3])
        latitude_time = extract_float(r"(\d+\.\d+) seconds", lines[4])
        date_range_time = extract_float(r"(\d+\.\d+) seconds", lines[5])
        borough_time = extract_float(r"(\d+\.\d+) seconds", lines[6])

        # Store the extracted values as a row
        data.append([run_number, load_time * 1000, zipcode_time * 1000, injuries_time * 1000, latitude_time * 1000,
                     date_range_time * 1000, borough_time * 1000])

    # Convert to DataFrame
    df = pd.DataFrame(data, columns=[
        "Run#", "Load Time (ms)", "Zipcode Query (ms)", "Injuries Query (ms)",
        "Latitude Query (ms)", "Date Range Query (ms)", "Borough Query (ms)"
    ])

    return df

# Paths and file list
log_dir = "logs/general"  # Update this path if needed
metrics_dir = "metrics"
image_dir = os.path.join(metrics_dir, "image")
data_file = os.path.join(metrics_dir, "phase_data.csv")

os.makedirs(image_dir, exist_ok=True)

# Mapping filenames to short labels
file_mapping = {
    "phase-1.txt": "1",
    "phase-2a.txt": "2a",
    "phase-2b.txt": "2b",
    "phase-2c.txt": "2c",
    "phase-3a.txt": "3a",
    "phase-3b.txt": "3b"
}

mean_metrics = []

# Process each file
for file, short_label in file_mapping.items():
    file_path = os.path.join(log_dir, file)
    if not os.path.exists(file_path):
        print(f"WARNING: {file_path} not found, skipping...")
        continue

    df = parse_runs(file_path)

    # Save mean values with short labels instead of filenames
    mean_values = df.mean().to_dict()
    del mean_values["Run#"]
    mean_values["Phase"] = short_label  # Use short label instead of filename
    mean_metrics.append(mean_values)

    # Create visualization
    fig, axes = plt.subplots(3, 2, figsize=(12, 15))
    fig.suptitle(f"Performance Metrics - Phase {short_label}", fontsize=14)

    metrics = [
        ("Load Time (ms)", "Load Time vs Run#"),
        ("Zipcode Query (ms)", "Zipcode Query Time vs Run#"),
        ("Injuries Query (ms)", "Injuries Query Time vs Run#"),
        ("Latitude Query (ms)", "Latitude Query Time vs Run#"),
        ("Date Range Query (ms)", "Date Range Query Time vs Run#"),
        ("Borough Query (ms)", "Borough Query Time vs Run#")
    ]

    for ax, (metric, title) in zip(axes.flatten(), metrics):
        ax.plot(df["Run#"], df[metric], marker='o', linestyle='-')
        ax.set_title(title, fontsize=12, pad=10)
        ax.set_xlabel("Run#")
        ax.set_ylabel("Time (ms)")
        ax.grid(True)

    plt.subplots_adjust(hspace=0.6, wspace=0.4)
    image_path = os.path.join(image_dir, f"phase-{short_label}.png")
    plt.savefig(image_path)
    plt.close()
    
df_metrics = pd.DataFrame(mean_metrics)
df_metrics.to_csv(data_file, index=False)

# Set the phase column as categorical for correct plotting order
df_metrics["Phase"] = pd.Categorical(df_metrics["Phase"], categories=["1", "2a", "2b", "2c", "3a", "3b"], ordered=True)

# Create a figure with 6 subplots (3 rows, 2 columns) for better visualization
fig, axes = plt.subplots(3, 2, figsize=(12, 15))
fig.suptitle("Performance Metrics Across Phases", fontsize=14)  # Adjusted title position

# Define metric titles and labels
metrics = [
    ("Load Time (ms)", "Load Time vs Phase"),
    ("Zipcode Query (ms)", "Zipcode Query Time vs Phase"),
    ("Injuries Query (ms)", "Injuries Query Time vs Phase"),
    ("Latitude Query (ms)", "Latitude Query Time vs Phase"),
    ("Date Range Query (ms)", "Date Range Query Time vs Phase"),
    ("Borough Query (ms)", "Borough Query Time vs Phase")
]

# Plot each metric on a separate subplot
for ax, (metric, title) in zip(axes.flatten(), metrics):
    ax.plot(df_metrics["Phase"], df_metrics[metric], marker='o', linestyle='-')
    ax.set_title(title, fontsize=12, pad=10)  # Added padding
    ax.set_xlabel("Phase")  # Padding for X-axis
    ax.set_ylabel("Time (ms)")  # Padding for Y-axis
    ax.grid(True)

# Adjust layout with more spacing to prevent overlapping
plt.subplots_adjust(hspace=0.6, wspace=0.4)

# Save the comparison plot
comparison_plot_path = os.path.join(image_dir, "metrics_comparison.png")
plt.savefig(comparison_plot_path)
plt.close()