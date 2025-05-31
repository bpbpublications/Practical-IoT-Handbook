// Callback function for incoming MQTT messages
void handleIncomingMessage(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message on topic [");
  Serial.print(topic);
  Serial.print("]: ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {      // If message is "1" the LED turns on, otherwise turns off.
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
}


// Function to reconnect to MQTT broker
void attemptMQTTConnection() {
  while (!mqttClient.connected()) {   // While not connected, try to connect to the MQTT broker
    Serial.print("Attempting MQTT connection..."); 
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("MQTT connected");
      client.subscribe(MQTT_TOPIC); // Subscribe to the topic
    } else {
      Serial.print("Connection failed, return code=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);         // Set serial baudrate
  establishWiFiConnection();
  mqttClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT); // Establish MQTT server
  mqttClient.setCallback(handleIncomingMessage);
}

void loop() {
  if (!mqttClient.connected()) {
    attemptMQTTConnection();
  }
  mqttClient.loop();
}

