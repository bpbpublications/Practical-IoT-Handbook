def read_file(file_name):
    try:
        with open(file_name, 'r') as file:
            content = file.read()
            print(f"Contents of {file_name}:\n{content}")
    except FileNotFoundError:
        print(f"The file '{file_name}' does not exist.")
    except Exception as e:
        print(f"An error occurred while reading the file: {e}")
