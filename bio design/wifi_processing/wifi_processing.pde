import processing.net.*;

Client client;
int x, y, z;

ball player;
wall[] walls; 
boolean gameStarted = false;

void setup() {
  size(750, 750);

  client = new Client(this, "192.168.1.23", 80); // Change the IP address and port to match your setup

  player = new ball(50,300);
  walls = new wall[2];
  walls[0] = new wall(250,0,40,500);
  walls[1] = new wall(500,250,40,500);
} 

void draw() {
  background(240, 223, 156); 
  noStroke(); 

  if (gameStarted) { // only draw player and walls if game has started
    player.moveWithInput(x, y);
    player.draw();
    for(int i = 0; i < walls.length; i++){
      walls[i].draw();
    }
  } else { // draw start button if game hasn't started
    fill(0, 255,0);
    rect(width/2-50, height/2-25, 100, 50);
    fill(255);
    textAlign(CENTER, CENTER);
    textSize(20);
    text("initiate test", width/2, height/2);
  }
}

void clientEvent(Client client) {
  String data = client.readStringUntil('\n');
  if (data != null) {
    data = data.trim();
    String[] values = split(data, ",");
    if (values.length == 2) {
      try {
        x = int(float(values[0]));
        y = int(float(values[1]));
      } catch (Exception e) {
        // Handle exception
      }
    }
  }
}

void mousePressed() {
  if (!gameStarted && mouseX > width/2-50 && mouseX < width/2+50 && mouseY > height/2-25 && mouseY < height/2+25) {
    gameStarted = true;
  }
}

int speed = 4;

class ball {
  float x;
  float y;
  float xSpeed = 0;
  float ySpeed = 0;

  ball(float _x, float _y){
    x = _x;
    y = _y;
  }

  void draw(){
    fill(240,10,0);
    ellipse(x,y,60,60);
  }

  void moveWithInput(int inputX, int inputY) {
    if (inputX > 30) {
      xSpeed = speed;
    } else if (inputX < -30) {
      xSpeed = -speed;
    } else {
      xSpeed = 0;
    }
    
    if (inputY > 30) {
      ySpeed = speed;
    } else if (inputY < -30) {
      ySpeed = -speed;
    } else {
      ySpeed = 0;
    }

    float possibleX = x + xSpeed;
    float possibleY = y + ySpeed;

    for(int i = 0; i < walls.length; i++){
      if(possibleX > walls[i].x && possibleX < (walls[i].x + walls[i].w) && possibleY > walls[i].y && possibleY < walls[i].y + walls[i].h){
        return;
      }
    }

    x = possibleX;
    y = possibleY;
  }
}

class wall {
  float x;
  float y;
  float w;
  float h;

  wall(float _x, float _y, float _w, float _h){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
  }

  void draw(){
    fill(0);
    rect(x,y,w,h);
  }
}
