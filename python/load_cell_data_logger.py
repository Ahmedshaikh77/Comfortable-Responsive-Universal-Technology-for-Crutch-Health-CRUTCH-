#!/usr/bin/env python3
"""
Real-time Load Cell Data Logger and Visualizer
Captures load cell data from ESP32, plots in real-time, and saves to CSV
"""

import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from datetime import datetime

# Configuration
SERIAL_PORT = '/dev/cu.usbserial-0001'  # Replace with your ESP32 port
BAUD_RATE = 115200

# Open serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Data storage
timestamps_seconds = []
forces = []

# Create a CSV file to save data
output_filename = f"load_cell_data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
with open(output_filename, 'w') as f:
    f.write("Timestamp (s),Time (min),Force (N)\n")  # Updated header


# Function to parse the ESP32 data
def parse_data(line_data):
    """Parses the raw data from ESP32."""
    try:
        if ',' not in line_data:
            print("Invalid data format, skipping:", line_data)
            return None, None
        
        parts = line_data.split(',')
        if len(parts) != 2:
            print("Unexpected number of parts, skipping:", parts)
            return None, None
        
        timestamp_part = parts[0].strip()
        force_part = parts[1].strip()
        
        seconds = float(timestamp_part.split(' ')[0])
        force = float(force_part.replace('N', '').strip())
        return seconds, force
    except ValueError as e:
        print(f"Error parsing data: {e} – Raw Data: {line_data}")
        return None, None


# Plot setup
fig, ax = plt.subplots()
line, = ax.plot([], [], linewidth=2, label="Force (N)", color='blue')
ax.set_xlim(0, 10)
ax.set_ylim(0, 100)
ax.set_xlabel("Time (s)")
ax.set_ylabel("Force (N)")
ax.set_title("Real-Time Load Cell Data")
ax.legend()


# Initialize the plot
def init():
    return line,


# Update the plot with new data
def update(frame):
    global timestamps_seconds, forces
    
    try:
        # Read data from ESP32
        line_data = ser.readline().decode('utf-8').strip()
        print(f"Raw Data: {line_data}")  # Print raw data to the terminal
        
        # Parse the data
        seconds, force = parse_data(line_data)
        if seconds is None or force is None:
            return line  # Skip this frame if parsing failed
        
        # Store parsed values
        timestamps_seconds.append(seconds)
        forces.append(force)
        
        # Calculate time in minutes
        minutes = seconds / 60
        
        # Save data to CSV
        with open(output_filename, 'a') as f:
            f.write(f"{seconds},{minutes:.3f},{force}\n")  # Include minutes in the CSV
        
        # Plot only the most recent 50 points
        recent_timestamps = timestamps_seconds[-50:]
        recent_forces = forces[-50:]
        
        line.set_data(recent_timestamps, recent_forces)
        
        # Dynamically adjust axis limits
        ax.set_xlim(0, max(recent_timestamps[-1], 10))  # Expand X-axis dynamically
        ax.set_ylim(0, max(recent_forces) * 1.1 if recent_forces else 100)  # Adjust Y-axis dynamically
    except Exception as e:
        print(f"Error in update(): {e}")
    
    return line,


# Animate the plot
ani = FuncAnimation(fig, update, init_func=init, blit=False, interval=100)

# Show the plot
plt.show()

# Save the final graph when the script stops
plt.plot(timestamps_seconds, forces, linewidth=2, label="Force (N)", color='blue')
plt.xlabel("Time (s)")
plt.ylabel("Force (N)")
plt.title("Final Load Cell Data")
plt.legend()
graph_filename = f"load_cell_plot_{datetime.now().strftime('%Y%m%d_%H%M%S')}.png"
plt.savefig(graph_filename)
print(f"Data saved to {output_filename}")
print(f"Graph saved as {graph_filename}")
