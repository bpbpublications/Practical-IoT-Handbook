#include <WiFi.h>
#include <WiFiUdp.h>
#include <coap-simple.h>

// WiFi credentials
const char* ssid = "WIFI-SSID";
const char* password = "WIFI-KEY";

// Server details
IPAddress serverIP(XXX, XXX, XXX, XXX); // Replace with your server's IP
int serverPort = 5683; // Replace with server's CoAP port
const char* endpointURL = "actuators/relay"; // Replace with your server's endpoint

WiFiUDP udp; // UDP object
Coap coap(udp); // CoAP object initialized with UDP

void requestDataUsingGET() {
  // Perform GET request to receive data from the server
  coap.get(serverIP, serverPort, endpointURL);
}

void callback_response(CoapPacket &packet, IPAddress ip, int port) {
  // Handle the response received from the server after the GET request
  Serial.println("[Coap Response got]");

  // Copy the payload into a character array
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL; // Null-terminate the string

  // Print the received payload
  Serial.println(p);

  // Control the built-in LED based on the received payload
  if (strcmp(p, "1") == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}


  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Set up built-in LED pin as an output and turn it on
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Print WiFi connection details
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up callback function for handling server responses
  Serial.println("Setup Response Callback");
  coap.response(callback_response);

  // Start CoAP client
  coap.start();
}


void loop() {
  // Request data using GET method from the CoAP server
  requestDataUsingGET();

  coap.loop(); // Handle CoAP tasks
  delay(1000); // Add delay between loop iterations
}
