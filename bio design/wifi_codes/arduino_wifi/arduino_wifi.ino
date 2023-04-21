#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Arduino_LSM6DS3.h>

//const char* ssid = "Taylor";
//const char* password = "cody1315";
//const char* ssid = "ed";
//const char* password = "pleasework";
const char* ssid = "Arduino";
const char* password = "password123";
const char* host = "your_SERVER_IP"; // IP address or domain name of the receiver
const int port = 80; // Port to run the server on

WiFiClient client;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");  
  Serial.println();
  Serial.println("Gyroscope in degrees/second");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to the server
  Serial.print("Connecting to ");
  Serial.print(host);
  Serial.print(":");
  Serial.println(port);
  while (!client.connect(host, port)) {
    Serial.println("Connection failed, retrying...");
    delay(1000);
  }
  Serial.println("Connected to server");
}

void loop() {
  if (IMU.gyroscopeAvailable()) {
    float x, y, z;
    IMU.readGyroscope(x, y, z);

    // Send x and y values to the server over Wi-Fi
    if (client.connected()) {
      client.print(x);
      client.print(",");
      client.println(y);
    }
  }
}
