
#include <WiFi.h>
#include <Arduino_LSM6DS3.h>

int status = WL_IDLE_STATUS;

float x, y, z;
int plusThreshold = 30, minusThreshold = -30;
int amount = 25;

int LED = 13;
 char ssid[] = "Taylor";
 char pass[] = "cody1315";

IPAddress serverIP(192, 168, 0, 100); // change to the IP address of your server
int serverPort = 1234; // change to the port number of your server

WiFiClient client; // declare the client object

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

   while (status != WL_CONNECTED) {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
    status = WiFi.begin(ssid, pass);
    IPAddress ip = WiFi.localIP();
    Serial.println(ip);
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

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  if (!client.connect(serverIP, serverPort)) {
    Serial.println("Connection to server failed!");
    return;
  }
  Serial.println("Connected to server!");
}

void loop() {
  
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
  }
  if(y > plusThreshold)
  {
    client.write('f'); // send 'f' to indicate collision front
    delay(amount);
  }
  if(y < minusThreshold)
  {
    client.write('b'); // send 'b' to indicate collision back
    delay(amount);
  }
  if(x < minusThreshold)
  {
    client.write('r'); // send 'r' to indicate collision right
    delay(amount);
  }
    if(x > plusThreshold)
  {
    client.write('l'); // send 'l' to indicate collision left
    delay(amount);
  }
}
