#include <Arduino_LSM6DS3.h>

float x, y, z;
int plusThreshold = 30, minusThreshold = -30;
int amount = 15;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

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
    IMU.readGyroscope(x, y, z);
  }
  if(y > plusThreshold)
  {
    Serial.write('w'); // send 'f' to indicate collision front
    delay(amount);
  }
  if(y < minusThreshold)
  {
    Serial.write('s'); // send 'b' to indicate collision back
    delay(amount);
  }
  if(x < minusThreshold)
  {
    Serial.write('d'); // send 'r' to indicate collision right
    delay(amount);
  }
    if(x > plusThreshold)
  {
    Serial.write('a'); // send 'l' to indicate collision left
    delay(amount);
  }
}
