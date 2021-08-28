#include <ArduinoJson.h>
#include <DHT.h>
#include <Ethernet.h>
#include <SPI.h>

#define DHTPIN 2
#define DHTTYPE DHT22

// Enter the Ethernet shield MAC Address
byte mac[] = {0xAA, 0xBB, 0xCC, 0xF0, 0xF1, 0xF2};
EthernetServer server(80);

DHT sensor(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  while (!Serial) continue;

  if (!Ethernet.begin(mac)) {
    Serial.println("Failed to configure Ethernet using DHCP");

    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found");
    }

    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected");
    }
  }

  server.begin();
  Serial.println("Server is ready.");

  Serial.print("Please connect to http://");
  Serial.println(Ethernet.localIP());

  sensor.begin();
  Serial.println("Sensor is ready.");
}

void loop() {
  // Wait for an incomming connection
  EthernetClient client = server.available();

  // Do we have a client?
  if (!client) return;

  Serial.print("New client: ");
  Serial.println(client.remoteIP());

  // Read the request (ignore the content for this project)
  while (client.available()) client.read();

  // Allocate JsonBuffer
  // Use arduinojson.org/assistant to compute the capacity.
  DynamicJsonDocument doc(16);

  doc["temperature"] = sensor.readTemperature();
  doc["humidity"] = sensor.readHumidity();

  Serial.print("Sending: ");
  serializeJson(doc, Serial);
  Serial.println();

  // Write response headers
  client.println("HTTP/1.0 200 OK");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();

  // Write JSON document
  serializeJson(doc, client);

  // Disconnect
  client.stop();
}
