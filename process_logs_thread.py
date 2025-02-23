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
log_dir = "logs/threads"  # Update this path if needed
metrics_dir = "metrics"
image_dir = os.path.join(metrics_dir, "image")
data_file = os.path.join(metrics_dir, "thread_data.csv")

os.makedirs(image_dir, exist_ok=True)

# Mapping filenames to short labels
file_mapping = {
    "threads1.txt": "1",
    "threads2.txt": "2",
    "threads4.txt": "4",
    "threads6.txt": "6",
    "threads8.txt": "8"
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
    mean_values["Thread Count"] = short_label  # Use short label instead of filename
    mean_metrics.append(mean_values)

df_metrics = pd.DataFrame(mean_metrics)
df_metrics.to_csv(data_file, index=False)

# Set the phase column as categorical for correct plotting order
df_metrics["Thread Count"] = pd.Categorical(df_metrics["Thread Count"], categories=["1", "2", "4", "6", "8"], ordered=True)

# Create a figure with 6 subplots (3 rows, 2 columns) for better visualization
fig, axes = plt.subplots(3, 2, figsize=(12, 15))
fig.suptitle("Performance Metrics Across Thread Counts", fontsize=14)  # Adjusted title position

# Define metric titles and labels
metrics = [
    ("Load Time (ms)", "Load Time vs Thread Count"),
    ("Zipcode Query (ms)", "Zipcode Query Time vs Thread Count"),
    ("Injuries Query (ms)", "Injuries Query Time vs Thread Count"),
    ("Latitude Query (ms)", "Latitude Query Time vs Thread Count"),
    ("Date Range Query (ms)", "Date Range Query Time vs Thread Count"),
    ("Borough Query (ms)", "Borough Query Time vs Thread Count")
]

# Plot each metric on a separate subplot
for ax, (metric, title) in zip(axes.flatten(), metrics):
    ax.plot(df_metrics["Thread Count"], df_metrics[metric], marker='o', linestyle='-')
    ax.set_title(title, fontsize=12, pad=10)  # Added padding
    ax.set_xlabel("Thread Count")  # Padding for X-axis
    ax.set_ylabel("Time (ms)")  # Padding for Y-axis
    ax.grid(True)

# Adjust layout with more spacing to prevent overlapping
plt.subplots_adjust(hspace=0.6, wspace=0.4)

# Save the comparison plot
comparison_plot_path = os.path.join(image_dir, "thread_comparison.png")
plt.savefig(comparison_plot_path)
plt.close()