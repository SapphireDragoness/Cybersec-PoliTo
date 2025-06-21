import re
import matplotlib.pyplot as plt
import numpy as np


def parse_iperf_output(file_path):
    with open(file_path, "r") as f:
        lines = f.readlines()

    time_intervals = []
    transfer_rates = []
    bitrates = []

    time = 0  # Accumulate time across tests

    for line in lines:
        match = re.search(
            r"\[\s*\d+]\s+(\d+\.\d+)-(\d+\.\d+)\s+sec\s+(\d+\.?\d*)\s+([KMGT]?Bytes)\s+(\d+\.?\d*)\s+([KMGT]?bits/sec)",
            line,
        )
        if match:
            start, end, transfer, transfer_unit, bitrate, bitrate_unit = match.groups()

            start, end, transfer, bitrate = (
                float(start),
                float(end),
                float(transfer),
                float(bitrate),
            )

            # Convert units to Megabytes (MB) and Megabits per second (Mbps)
            unit_conversion = {
                "KBytes": 0.001,
                "MBytes": 1,
                "GBytes": 1000,
                "TBytes": 1000000,
                "Kbits/sec": 0.000001,
                "Mbits/sec": 1,
                "Gbits/sec": 1000,
                "Tbits/sec": 1000000,
            }

            transfer *= unit_conversion[transfer_unit]
            bitrate *= unit_conversion[bitrate_unit]

            time_intervals.append(time + (start + end) / 2)
            transfer_rates.append(transfer)
            bitrates.append(bitrate)

        elif "Server listening on" in line:  # Reset time at each test
            time += 10  # Assuming each test runs for 10 seconds

    return time_intervals, transfer_rates, bitrates


def plot_data(time_intervals, transfer_rates, bitrates):
    fig, ax1 = plt.subplots()

    color = "tab:blue"
    ax1.set_xlabel("Time (s)")
    ax1.set_ylabel("Transfer (MB)", color=color)
    ax1.plot(
        time_intervals,
        transfer_rates,
        marker="o",
        linestyle="-",
        color=color,
        label="Transfer Rate",
    )
    ax1.tick_params(axis="y", labelcolor=color)

    ax2 = ax1.twinx()
    color = "tab:red"
    ax2.set_ylabel("Bitrate (Mbps)", color=color)
    ax2.plot(
        time_intervals,
        bitrates,
        marker="s",
        linestyle="--",
        color=color,
        label="Bitrate",
    )
    ax2.tick_params(axis="y", labelcolor=color)

    fig.tight_layout()
    plt.show()


if __name__ == "__main__":
    file_path = "wifi-wifi.txt"  # Change this to your actual iperf log file
    time_intervals, transfer_rates, bitrates = parse_iperf_output(file_path)
    plot_data(time_intervals, transfer_rates, bitrates)
