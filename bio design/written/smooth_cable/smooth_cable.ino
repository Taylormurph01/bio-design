#include <Arduino_LSM6DS3.h>

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

  // Display the recorded gyroscope values
  if (count >= 100) {
    for (int i = 0; i < 100; i++) {
      Serial.print("x:");
      Serial.print(x_array[i]);
      Serial.print(",y:");
      Serial.println(y_array[i]);
    }
    count = 0;
  }
}
