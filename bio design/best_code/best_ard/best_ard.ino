#include <Arduino_LSM6DS3.h> // include the LSM6DS3 library

void setup() {
  Serial.begin(115200); // initialize serial communication with the computer
  while (!Serial); // wait for serial communication to be ready

  if (!IMU.begin()) { // check if the IMU is connected and ready to use
    Serial.println("Failed to initialise IMU!"); // if not, print an error message and stop the sketch
    while (1);
  }

  Serial.print("Gyroscope sample rate = "); // print the gyroscope sample rate
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");  
  Serial.println();
  Serial.println("Gyroscope in degrees/second"); // print a header for the gyroscope data
}

void loop() {
  if (IMU.gyroscopeAvailable()) { // check if new gyroscope data is available
    float x, y, z; // create variables to store the x, y and z gyroscope values
    IMU.readGyroscope(x, y, z); // read the gyroscope values and store them in x, y and z

    Serial.print("x:"); // print the x value label
    Serial.print(x - 1); // print the modified x value
    Serial.print(",y:"); // print the y value label
    Serial.print(y + 3); // print the modified y value
    Serial.print(",z:"); // print the z value label
    Serial.println(z); // print the unmodified z value

    // Send x and y values through the serial port
    Serial.print(x); // print the unmodified x value
    Serial.print(","); // separate the x and y values with a comma
    Serial.println(y); // print the unmodified y value
  
  }
 delay(50); // wait for 50 milliseconds before checking for new gyroscope data again
}
