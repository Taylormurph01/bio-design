import processing.serial.*;

Serial port;

int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;
float xMovement = 0.0;
float yMovement = 0.0;
float ballX = 50.0;
float ballY = 50.0;
float ballSize = 20.0;

void setup() {
  size(400, 400);
  smooth();
  noStroke();
  
  // Open the serial port at a baud rate of 9600
  port = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  // Clear the screen
  background(255);

  // Draw the maze
  fill(0);
  rect(0, 0, 100, 200);
  rect(300, 0, 100, 200);
  rect(0, 200, 100, 200);
  rect(300, 200, 100, 200);
  
  // Update the ball position based on the movement data
  ballX += xMovement;
  ballY += yMovement;
  
  // Check for collisions with the walls
  if (ballX < ballSize || ballX > width - ballSize) {
    ballX -= xMovement;
  }
  if (ballY < ballSize || ballY > height - ballSize) {
    ballY -= yMovement;
  }
  if ((ballX > 0 && ballX < 100 && ballY > 0 && ballY < 200) ||
      (ballX > 0 && ballX < 100 && ballY > 200 && ballY < 400) ||
      (ballX > 300 && ballX < 400 && ballY > 0 && ballY < 200) ||
      (ballX > 300 && ballX < 400 && ballY > 200 && ballY < 400)) {
    ballX -= xMovement;
    ballY -= yMovement;
  }
  
  // Draw the ball
  fill(255, 0, 0);
  ellipse(ballX, ballY, ballSize, ballSize);
}

void serialEvent(Serial p) {
  // Read the button and movement data from the serial port
  String data = p.readStringUntil('\n').trim();
  String[] values = data.split(",");
  button1State = int(values[0].charAt(0)) - '0';
  button2State = int(values[0].charAt(1)) - '0';
  button3State = int(values[0].charAt(2)) - '0';
  button4State = int(values[0].charAt(3)) - '0';
  xMovement = float(values[1]);
  yMovement = float(values[2]);
}
