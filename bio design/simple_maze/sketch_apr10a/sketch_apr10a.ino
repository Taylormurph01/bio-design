#include <WiFi.h>
#include <WiFiUdp.h>
#include <Arduino_LSM6DS3.h>

MPU6050 IMU;
WiFiUDP udp;

const char* ssid = "VODAFONE-06C0";
const char* password = "2kT9P3smtFHA3Eda";
//const char* host = "192.168.1.100"; // IP address of the server
//const int port = 8888; // Port number of the server

void setup() {
  Serial.begin(115200);
  while (!Serial);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");

  IMU.begin();
  udp.begin(port);
}

void loop() {
  if (IMU.gyroscopeAvailable()) {
    float x, y, z;
    IMU.readGyroscope(x, y, z);

    Serial.print("x:");
    Serial.print(x);
    Serial.print(",y:");
    Serial.print(y);
    Serial.print(",z:");
    Serial.println(z);

    // Send x and y values through UDP
    String data = String(x) + "," + String(y);
    udp.beginPacket(host, port);
    udp.write(data.c_str(), data.length());
    udp.endPacket();
  }
}