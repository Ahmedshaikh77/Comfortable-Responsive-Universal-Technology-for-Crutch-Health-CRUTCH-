#!/usr/bin/env python3
"""
Accelerometer Data Logger and Visualizer
Captures MPU6050 accelerometer data from ESP32, plots in real-time, and saves to CSV
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
accel_x = []
accel_y = []
accel_z = []

# Create a CSV file to save data
output_filename = f"accelerometer_data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
with open(output_filename, 'w') as f:
    f.write("Timestamp (s),Accel_X (m/s²),Accel_Y (m/s²),Accel_Z (m/s²)\n")


# Function to parse the ESP32 accelerometer data
def parse_acceleration_data(line_data):
    """Parses the raw accelerometer data from ESP32."""
    try:
        # Expected format: "X: 0.12, Y: 0.34, Z: 9.81"
        if 'X:' not in line_data or 'Y:' not in line_data or 'Z:' not in line_data:
            print("Invalid data format, skipping:", line_data)
            return None, None, None
        
        # Extract values
        parts = line_data.split(',')
        x_val = float(parts[0].split(':')[1].strip())
        y_val = float(parts[1].split(':')[1].strip())
        z_val = float(parts[2].split(':')[1].strip())
        
        return x_val, y_val, z_val
    except (ValueError, IndexError) as e:
        print(f"Error parsing data: {e} – Raw Data: {line_data}")
        return None, None, None


# Plot setup for 3-axis acceleration
fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 8))

line_x, = ax1.plot([], [], linewidth=2, label="Accel X", color='red')
line_y, = ax2.plot([], [], linewidth=2, label="Accel Y", color='green')
line_z, = ax3.plot([], [], linewidth=2, label="Accel Z", color='blue')

for ax in [ax1, ax2, ax3]:
    ax.set_xlim(0, 10)
    ax.set_ylim(-20, 20)
    ax.set_xlabel("Time (s)")
    ax.set_ylabel("Acceleration (m/s²)")
    ax.legend()
    ax.grid(True)

ax1.set_title("Real-Time Accelerometer Data - X Axis")
ax2.set_title("Real-Time Accelerometer Data - Y Axis")
ax3.set_title("Real-Time Accelerometer Data - Z Axis")


# Initialize the plot
def init():
    return line_x, line_y, line_z


# Update the plot with new data
def update(frame):
    global timestamps_seconds, accel_x, accel_y, accel_z
    
    try:
        # Read data from ESP32
        line_data = ser.readline().decode('utf-8').strip()
        print(f"Raw Data: {line_data}")  # Print raw data to the terminal
        
        # Parse the data
        x, y, z = parse_acceleration_data(line_data)
        if x is None or y is None or z is None:
            return line_x, line_y, line_z  # Skip this frame if parsing failed
        
        # Store parsed values
        timestamps_seconds.append(len(timestamps_seconds))
        accel_x.append(x)
        accel_y.append(y)
        accel_z.append(z)
        
        # Save data to CSV
        with open(output_filename, 'a') as f:
            f.write(f"{len(timestamps_seconds)},{x},{y},{z}\n")
        
        # Plot only the most recent 50 points
        recent_timestamps = list(range(max(0, len(timestamps_seconds) - 50), len(timestamps_seconds)))
        recent_x = accel_x[-50:]
        recent_y = accel_y[-50:]
        recent_z = accel_z[-50:]
        
        line_x.set_data(recent_timestamps, recent_x)
        line_y.set_data(recent_timestamps, recent_y)
        line_z.set_data(recent_timestamps, recent_z)
        
        # Dynamically adjust axis limits
        max_time = len(timestamps_seconds)
        ax1.set_xlim(max(0, max_time - 50), max_time)
        ax2.set_xlim(max(0, max_time - 50), max_time)
        ax3.set_xlim(max(0, max_time - 50), max_time)
        
        # Adjust Y-axis based on data
        all_values = recent_x + recent_y + recent_z
        if all_values:
            y_max = max(all_values) * 1.1
            y_min = min(all_values) * 1.1
            for ax in [ax1, ax2, ax3]:
                ax.set_ylim(y_min, y_max)
    except Exception as e:
        print(f"Error in update(): {e}")
    
    return line_x, line_y, line_z


# Animate the plot
ani = FuncAnimation(fig, update, init_func=init, blit=False, interval=100)

# Show the plot
plt.tight_layout()
plt.show()

# Save the final graph when the script stops
fig_final, ax_final = plt.subplots()
ax_final.plot(timestamps_seconds, accel_x, linewidth=2, label="X", color='red')
ax_final.plot(timestamps_seconds, accel_y, linewidth=2, label="Y", color='green')
ax_final.plot(timestamps_seconds, accel_z, linewidth=2, label="Z", color='blue')
ax_final.set_xlabel("Sample")
ax_final.set_ylabel("Acceleration (m/s²)")
ax_final.set_title("Accelerometer Data Summary")
ax_final.legend()
graph_filename = f"accelerometer_plot_{datetime.now().strftime('%Y%m%d_%H%M%S')}.png"
plt.savefig(graph_filename)
print(f"Data saved to {output_filename}")
print(f"Graph saved as {graph_filename}")
