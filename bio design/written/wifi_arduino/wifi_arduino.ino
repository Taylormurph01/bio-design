#include <WiFi.h>
#include <Arduino_LSM6DS3.h>
void setup() {
  // Initialize serial port
  Serial.begin(115200);
  while (!Serial);

  // Connect to WiFi network
  WiFi.begin("store", "cody1318");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Initialize IMU sensor
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // Print gyroscope sample rate
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");

  // Print header for gyroscope data
  Serial.println("Gyroscope in degrees/second");
}


void loop() {
  static float x_array[100];
  static float y_array[100];
  static int count = 0;

  if (IMU.gyroscopeAvailable()) {
    float x, y, z;
    IMU.readGyroscope(x, y, z);

    Serial.print("x:");
    Serial.print(x);
    Serial.print(",y:");
    Serial.print(y);
    Serial.print(",z:");
    Serial.println(z);

    // Store x and y values in arrays
    x_array[count] = x;
    y_array[count] = y;
    count++;

    // Wait a bit before reading the sensor again
    delay(20);
  }

  // Send the recorded gyroscope values over WiFi
  if (count >= 100) {
    // Create JSON payload with the gyroscope data
    String payload = "{\"x\":[";
    for (int i = 0; i < 100; i++) {
      payload += String(x_array[i]);
      if (i < 99) {
        payload += ",";
      }
    }
    payload += "],\"y\":[";
    for (int i = 0; i < 100; i++) {
      payload += String(y_array[i]);
      if (i < 99) {
        payload += ",";
      }
    }
    payload += "]}";

    // Send the payload to a remote server using HTTP POST method
    WiFiClient client;
    if (client.connect("server_address", 80)) {
      client.println("POST /endpoint HTTP/1.1");
      client.println("Host: server_address");
      client.println("Content-Type: application/json");
      client.print("Content-Length: ");
      client.println(payload.length());
      client.println();
      client.println(payload);
      client.println();
    }

    // Reset the count and clear the arrays
    count = 0;
    memset(x_array, 0, sizeof(x_array));
    memset(y_array, 0, sizeof(y_array));
  }
}
