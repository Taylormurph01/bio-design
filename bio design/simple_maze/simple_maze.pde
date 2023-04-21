int speed = 4;

Ball player;
wall[] walls; 
boolean gameStarted = false;

void setup() {
  size(750, 750);
  player = new Ball(80, 300);
  walls = new wall[7];
  walls[0] = new wall(200, 240, 40, 355);
  walls[1] = new wall(500, 500, 40, 290);
  walls[2] = new wall(500, 0, 40, 300);
  walls[3] = new wall(0, 740, 750, 10);
  walls[4] = new wall(0, 0, 750, 10);
  walls[5] = new wall(0, 0, 10, 750);
  walls[6] = new wall(740, 0, 10, 750);
  
 
} 

void draw() {
  background(240, 223, 156); 
  noStroke(); 

  if (gameStarted) { // only draw player and walls if game has started
    player.draw();
    player.move(walls);
    for (int i = 0; i < walls.length; i++) {
      walls[i].draw();
    }
    // Draw finish line
    fill(0, 255, 0);
    rect(700, 250, 30, 300);
    
  } else { // draw start button if game hasn't started
    fill(0, 255, 0);
    rect(width/2-50, height/2-25, 100, 50);
    fill(255);
    textAlign(CENTER, CENTER);
    textSize(20);
    text("Start Game", width/2, height/2);
  }
  
  if (player.gameFinished) { // game is finished
    // clear canvas
    background(240, 223, 156); 
    
    // draw text box with result
    fill(255);
    rect(0, 325, 750, 100);
    fill(0);
    textAlign(CENTER, CENTER);
    textSize(30);
    text("Result: Low Concern", width/2, height/2);
    
    textSize(20);
    text("(monitor patient at home)", 375 , 410);
  }
 
}



void mousePressed() {
  if (!gameStarted && mouseX > width/2-50 && mouseX < width/2+50 && mouseY > height/2-25 && mouseY < height/2+25) {
    gameStarted = true;
  }
}

class Ball {
  float x;
  float y;
  float diameter = 55;
  float xSpeed = 0;
  float ySpeed = 0;
  boolean gameFinished = false;
  
  Ball(float _x, float _y) {
    x = _x;
    y = _y;
  }
  
  void draw() {
    fill(255, 0, 0);
    ellipse(x, y, diameter, diameter);
  }

  void move(wall[] walls) {
    if (gameFinished) {
      fill(240, 223, 156);
      rect(0, 0, width, height);
      fill(0);
      return;
    }
    
    float possibleX = x + xSpeed;
    float possibleY = y + ySpeed;

    for (int i = 0; i < walls.length; i++) {
      if (possibleX > walls[i].x && possibleX < walls[i].x + walls[i].w && possibleY > walls[i].y && possibleY < walls[i].y + walls[i].h) {
        return;
      }
    }

    x = possibleX;
    y = possibleY;

    // Check if the ball has reached the finish line
    if (x > 700 && y > 250) 
   // 700, 250, 30, 300
    {
      gameFinished = true;
    }
  }

  void keyPressed() {
    if (key == 'a') {
      xSpeed = -speed;
    }
    if (key == 'd') {
      xSpeed = speed;
    }
    if (key == 'w') {
      ySpeed = -speed;
    }
    if (key == 's') {
      ySpeed
 = speed;
    }
  }
  
  void keyReleased() {
    if (key == 'a' || key == 'd') {
      xSpeed = 0;
    }
    if (key == 'w' || key == 's') {
      ySpeed = 0;
    }
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

void keyPressed() {
  player.keyPressed();
}

void keyReleased() {
  player.keyReleased();
}
