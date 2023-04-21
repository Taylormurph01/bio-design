#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>


 //char ssid[] = "VODAFONE-06C0";
 //char pass[] = "2kT9P3smtFHA3Eda";
 char ssid[] = "Taylor";
 char pass[] = "cody1315";

const char* host = "your_HOST_ADDRESS";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");  
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
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

    // Send x and y values through the WiFi connection
    WiFiClient client;
    if (!client.connect(host, 80)) {
      Serial.println("Connection failed!");
      return;
    }
    String data = String(x) + "," + String(y);
    client.print("GET /send_data?data=" + data + " HTTP/1.1\r\n");
    client.print("Host: " + String(host) + "\r\n");
    client.print("Connection: close\r\n\r\n");
    Serial.println("Data sent: " + data);
  }
}
