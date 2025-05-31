#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebSocketsClient.h>
#include <microDS18B20.h>

// Data wire is plugged in GPIO 28
MicroDS18B20<28> sensor;

float temperature = 0;
bool connected = false;

WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      connected = false;
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      connected = true;
      // send message to server when Connected
      webSocket.sendTXT("Connected");
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);

      // send message to server
      webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);
      break;
    // send data to server
      // webSocket.sendBIN(payload, length);
    case WStype_PING:
      // pong will be send automatically
      Serial.printf("[WSc] get ping\n");
      break;
    case WStype_PONG:
      // answer to a ping we send
      Serial.printf("[WSc] get pong\n");
      break;
  }

}


void ds18b20_read()
{
 sensor.requestTemp();

 delay(500);
 temperature = sensor.getTemp();
 Serial.println("Temperature: ");
 Serial.print(temperature);
 Serial.println();

}

void setup() {
  // Serial.begin(921600);
  Serial.begin(115200);

  //Serial.setDebugOutput(true);
  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFiMulti.addAP("YOUR_SSID", "YOUR_WIFI_KEY");

  //WiFi.disconnect();
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }
 

  // server address, port and URL
  webSocket.begin("YOUR-SERVER-IP", 1880, "/ws/temp_sensor");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(1000);

  webSocket.enableHeartbeat(15000, 3000, 2);

}

void loop() {
  ds18b20_read(); //Read sensor value.
  
  char string_temp[5];  //Create a char array to store the value.
  dtostrf(temperature,5,2,string_temp); //Convert double to char and store it.
  webSocket.loop();   //Maintain the WebSocket client connected.
  if (!connected) return; //VERY IMPORTANT: Check the connection is active.
  webSocket.sendTXT(string_temp); //Send the value as String.
  delay(10000);
}
