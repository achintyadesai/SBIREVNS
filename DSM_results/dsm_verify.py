import dsm
from types import SimpleNamespace


def load_traces_from_file(file_path):
    with open(file_path, 'r') as file:
        # Read each line and split it into components (assuming space-separated)
        traces = [line.strip().split() for line in file]
    return traces

# Example usage
# file_path = 'results/input_sim_steering_rpps_abs/steering_rpps_abs.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_steering_rpps_abs/steering_rpps_abs_extra.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_steering_rpps_abs/steering_urpps_abs.txt'  # Replace with your actual file path

# fsa_directory = 'results/sim_steering_rpps_abs'  # Replace with the actual directory path


# file_path = 'results/input_sim_steering_rpds_abs/steering_rpds_abs.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_steering_rpds_abs/steering_rpds_abs_extra.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_steering_rpds_abs/steering_urpds_abs.txt'  # Replace with your actual file path

# fsa_directory = 'results/sim_steering_rpds_abs'  # Replace with the actual directory path


# file_path = 'results/input_sim_speed_rpds_abs/speed_rpds_abs.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_speed_rpds_abs/speed_rpds_abs_extra.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_speed_rpds_abs/speed_urpds_abs.txt'  # Replace with your actual file path

# fsa_directory = 'results/sim_speed_rpds_abs'  # Replace with the actual directory path


# file_path = 'results/input_sim_speed_rpps_abs/speed_rpps_abs.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_speed_rpps_abs/speed_rpps_abs_extra.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_speed_rpps_abs/speed_urpps_abs.txt'  # Replace with your actual file path

# fsa_directory = 'results/sim_speed_rpps_abs'  # Replace with the actual directory path












# file_path = 'results/input_sim_steering_rpps/steering_rpps_main.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_steering_rpps/steering_rpps_main_extra.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_steering_rpps/steering_urpps_main_crash.txt'  # Replace with your actual file path

# fsa_directory = 'results/sim_steering_rpps'  # Replace with the actual directory path


# file_path = 'results/input_sim_steering_rpds/steering_rpds_main.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_steering_rpds/steering_rpds_main_extra.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_steering_rpds/steering_urpds_main_crash.txt'  # Replace with your actual file path

# fsa_directory = 'results/sim_steering_rpds'  # Replace with the actual directory path


# file_path = 'results/input_sim_speed_rpds/speed_rpds_main.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_speed_rpds/speed_rpds_main_extra.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_speed_rpds/speed_urpds_main_crash.txt'  # Replace with your actual file path

# fsa_directory = 'results/sim_speed_rpds'  # Replace with the actual directory path


# file_path = 'results/input_sim_speed_rpps/speed_rpps_main.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_speed_rpps/speed_rpps_main_extra.txt'  # Replace with your actual file path
# file_path = 'results/input_sim_speed_rpps/speed_urpps_main_crash.txt'  # Replace with your actual file path

# fsa_directory = 'results/sim_speed_rpps'  # Replace with the actual directory path




# file_path = 'results/input_real_speed_parallel/input.txt'  # Replace with your actual file path
# file_path = 'results/input_real_speed_parallel/test_data_speed_parallel.txt'  # Replace with your actual file path

# fsa_directory = 'results/real_speed_parallel'  # Replace with the actual directory path


# file_path = 'results/input_real_speed_reverse/input.txt'  # Replace with your actual file path
# file_path = 'results/input_real_speed_reverse/test_data_speed_reverse.txt'  # Replace with your actual file path

# fsa_directory = 'results/real_speed_reverse'  # Replace with the actual directory path

# file_path = 'results/input_real_steering_parallel/input.txt'  # Replace with your actual file path
# file_path = 'results/input_real_steering_parallel/test_data_steering_parallel.txt'  # Replace with your actual file path

# fsa_directory = 'results/real_steering_parallel'  # Replace with the actual directory path


# file_path = 'results/input_real_steering_reverse/input.txt'  # Replace with your actual file path
file_path = 'results/input_real_steering_reverse/test_data_steering_reverse.txt'  # Replace with your actual file path

fsa_directory = 'results/real_steering_reverse'  # Replace with the actual directory path




# Load traces from the file
traces = load_traces_from_file(file_path)

# Call the accept_traces function
result = dsm.accept_traces(traces, fsa_directory)

print(result)
print("Accepted Traces: " + str(result.count(True)))
print("Rejected Traces: " + str(result.count(False)))