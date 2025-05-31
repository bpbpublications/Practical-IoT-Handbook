#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SERVER "SERVER-IP:1880" //Replace SERVER-IP with the IP address of your server
#define RESOURCE_PATH "/office/door"
#define DOOR_SENSOR_PIN 14

volatile int doorState = 0; // Variable to store the door state
volatile int state_change = 0; // Variable to trigger the HTTP publication

#define STASSID "WIFI-SSID"
#define STAPSK "WIFI-KEY"

void ICACHE_RAM_ATTR doorStateChanged();

void setup() {
  
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();

  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // Set GPIO 14 as input for the door sensor

  // Connect to the WiFi network
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Attach interrupt to handle changes in door sensor state
  attachInterrupt(digitalPinToInterrupt(DOOR_SENSOR_PIN), doorStateChanged, CHANGE);
}

// Interrupt Service Routine (ISR) for handling changes in door sensor state
void ICACHE_RAM_ATTR doorStateChanged() {
  doorState = !digitalRead(DOOR_SENSOR_PIN);
  state_change = 1;
}

void loop() {
  // Wait for WiFi connection
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    if (state_change == 1) {
      state_change = 0;

      Serial.print("[HTTP] begin...\n");

      // Concatenate server IP address with resource path
      String url = "http://" + String(SERVER) + String(RESOURCE_PATH);

      // Begin the HTTP PUT request to the server's URL
      http.begin(client, url);  // HTTP
      http.addHeader("Content-Type", "application/json");

      Serial.print("[HTTP] PUT...\n");

      // Prepare the payload based on the door state
      String payload = "{\"status\":\"" + String(doorState) + "\"}";

      // Start the connection and send HTTP header and body
      int httpCode = http.PUT(payload);

      // HTTP code will be negative on error
      if (httpCode > 0) {
        // HTTP header has been sent, and the server response header has been handled
        Serial.printf("[HTTP] PUT... code: %d\n", httpCode);
        // File found at the server
        if (httpCode == HTTP_CODE_OK) {
          const String& response = http.getString();
          Serial.println("Received response:\n<<");
          Serial.println(response);
          Serial.println(">>");
        }
      } else {
      Serial.printf("[HTTP] PUT... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

    http.end();
    }
  }
  delay(100); // Wait for 0,1 seconds before the next iteration
}
