#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_VERSION MQTT_VERSION_3_1_1

// WiFi Credentials
const char* WIFI_SSID = "WIFI_NAME";
const char* WIFI_PASSWORD = "WIFI_PASS";

// MQTT Configuration: ID, Server IP, Port, User, Password
const PROGMEM char* MQTT_CLIENT_ID = "YOUR_CLIENT_ID";
const PROGMEM char* MQTT_SERVER_IP = "YOUR_BROKER_IP";
const PROGMEM uint16_t MQTT_SERVER_PORT = YOUR_BROKER_PORT;
const PROGMEM char* MQTT_USER = "YOUR_BROKER_USER";
const PROGMEM char* MQTT_PASSWORD = "YOUR_BROKER_PASS";



WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
unsigned long lastMessageTime = 0;
#define MAX_MSG_BUFFER_SIZE (16000)
char message[MAX_MSG_BUFFER_SIZE];
int counter = 0;

// Establishing a WiFi Connection
void establishWiFiConnection() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Reconnecting to MQTT Broker
void reconnectToMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      mqttClient.publish("outTopic", "hello world"); // Publish initial message after connection
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}


void setup() {
  pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  establishWiFiConnection(); // Connect to WiFi
  mqttClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT); // Set MQTT server and port
}


void loop() {
  if (!mqttClient.connected()) {
    reconnectToMQTT(); // Reconnect to MQTT if not connected
  }
  mqttClient.loop(); // Maintain MQTT connection

  unsigned long currentTime = millis();
  if (currentTime - lastMessageTime > 2000) {
    lastMessageTime = currentTime;
    ++counter;
    snprintf(message, MAX_MSG_BUFFER_SIZE, "hello world #%d", counter);
    Serial.print("Publishing message: ");
    Serial.println(message);
    mqttClient.publish("outTopic", message); // Publish message to 'outTopic'
  }
}
