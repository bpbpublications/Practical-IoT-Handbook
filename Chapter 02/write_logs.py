def write_to_file(file_name, data):
    try:
        with open(file_name, 'a') as file:
            file.write(data + '\n')  # Append data to the file with a newline character
        print(f"Data '{data}' has been successfully written to {file_name}.")
    except Exception as e:
        print(f"An error occurred while writing to the file: {e}")

# Example usage:
data_to_write = "This is some new data."
file_name = "data.txt"
write_to_file(file_name, data_to_write)
