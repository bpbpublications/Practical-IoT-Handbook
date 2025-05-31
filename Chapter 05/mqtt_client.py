import sys
import paho.mqtt.client as mqtt



# Function to report if the connection was successful or not, as shown below:
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to broker")
    else:
        print(f"Failed to connect, return code: {rc}")

# Function to report disconnection from the broker, as shown below:
def on_disconnect(client, userdata, rc):
    print("Disconnected from broker")

# Function to show the available options for executing the script, as shown below:
def print_help():
    help_text = """
    Usage: python mqtt_client.py <broker_address> <broker_port> <username> <password> <client_id> <-s/-p> <topic_name> [payload]
    Options:
        -h, --help          Show this help message and exit
        -s, --subscribe     Subscribe to the specified topic
        -p, --publish       Publish a message to the specified topic
    """
    print(help_text)
    sys.exit()

# Function to display received messages from the MQTT broker, as shown below:
def on_message(client, userdata, msg):
    print(f"Received message: {msg.payload.decode()} on topic {msg.topic}")

# This is the main function, that calls all the other functions in the script, as shown below:
def main():
    if len(sys.argv) == 2 and (sys.argv[1] == "-h" or sys.argv[1] == "--help"):
        print_help()
    if len(sys.argv) < 8:
        print("Usage: python mqtt_client.py <broker_address> <broker_port> <username> <password> <client_id> <-s/-p> <topic_name> [payload]")
        sys.exit(1)
# Get all the parameters from the arguments in the command line, as shown below:
    broker_address = sys.argv[1]
    broker_port = sys.argv[2]
    username = sys.argv[3]
    password = sys.argv[4]
    client_id = sys.argv[5]
    operation = sys.argv[6]
    topic = sys.argv[7]

    if not all([broker_address, broker_port, username, password, client_id, operation, topic]):
        print("Missing parameter(s). Please provide all required parameters.")
        sys.exit(1)

    try:
        broker_port = int(broker_port)
    except ValueError:
        print("Broker port should be an integer.")
        sys.exit(1)

# Create the MQTT client, as shown below:
    client = mqtt.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.on_disconnect = on_disconnect

# If it is a subscribe operation, connect to the broker and subscribe to the topic, as shown below:
    if operation == "-s" or operation == "--subscribe":
        client.on_message = on_message
        try:
            client.connect(broker_address, broker_port)
            client.subscribe(topic)
            client.loop_forever()
        except KeyboardInterrupt:
            client.disconnect()
            
# If it is a publish operation, publish the message to the topic, as shown below:
    elif operation == "-p" or operation == "--publish":
        if len(sys.argv) < 9:
            print("Please provide a payload for the publish operation.")
            sys.exit(1)

        payload = sys.argv[8]

        try:
            client.connect(broker_address, broker_port)
            client.publish(topic, payload)
            client.disconnect()
            print(f"Published message '{payload}' to topic {topic}")
        except Exception as e:
            print(f"Error publishing message: {str(e)}")

    else:
        print("Invalid operation. Use -s/--subscribe or -p/--publish.")
        sys.exit(1)

# This line of code calls the main() function when the script is executed, as shown below:
if __name__ == "__main__":
    main()
