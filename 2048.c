// Nick Cheung 2048 Game on Processing

//creating global variables
int[][] grid = new int[4][4]; //row, column
int[][] gridCopy = new int [4][4]; //copies of the board to compare later
int[][] gridCopy2 = new int [4][4]; //*2
int score = 0;
int moves = 0;
PFont font1;
PFont font2;
String move;
int screen = 0;
int r, g, b; //color of the blocks
int textX = 400; //location variables
int textX2 = 3000;
int textWinX = 3000;
int winLoseCoord = 802;
int timeS = 0; //time variables
int timeM = 0;
int startTimeS = 0;
int startTimeM = 0;
int resetTimeS = 0;
int resetTimeM = 0;
boolean startT = true; //booleans
boolean mouseReleased = false;
boolean win = false;
boolean lose = false;
boolean cont = false;

//canvas size to be 800 by 800 pixels
void setup() {
  size(800, 800);
}

void draw() {
  //creates background color and loads fonts  
  background(255, 242, 204);
  font1 = loadFont("Verdana-Bold-48.vlw");
  font2 = loadFont("Sana-48.vlw");

  //welcome text on start screen
  textFont(font2);
  fill(0); //color is black
  textAlign(CENTER); //aligned to the center
  textSize(50); //size is 50 px
  text("WELCOME TO", textX, 70);

  textFont(font1);
  fill(237, 194, 46);
  textSize(200);
  text("2048", textX, 280);

  textFont(font2);
  fill(0);
  textSize(30);
  text("Use the arrow keys or 'w' 'a' 's' d' to move.", textX, 350);
  text("Blocks with the same value add when combined.", textX, 400);
  text("If no more moves can be made, you lose.", textX, 450);
  text("Try to form 2048!", textX, 500);
  text("Press the 2048 icon to start/restart.", textX, 550);

  fill(80);
  textSize(15);
  text("Original game created by Gabriele Cirulli", textX, 700);

  textFont(font1);
  textAlign(LEFT);
  fill(237, 194, 46); //color for 2048 block
  textSize(100);
  text("2048", textX2, 105);

  textFont(font2);
  fill(0);
  textSize(35);
  text("Score:", textX2 + 550, 52.5);
  text("Moves:" + moves, textX2 + 300, 97.5);

  textAlign(CENTER);
  text(score, textX2 + 600, 97.5);
  textAlign(LEFT);

  //the time on screen 0, counted only on screen 0
  if (startT == true) {
    startTimeS = millis() / 1000;
    startTimeM = millis() / 60000;
  }

  timeS = (millis() / 1000);
  timeM = (timeS - startTimeS) / 60;

  //time on screen 1 minus the time on screen 0, capable of being reset using the resetTime variables
  if (timeM - startTimeM - resetTimeM < 10) {
    text("Time:0" + ((timeM - startTimeM) - resetTimeM), textX2 + 300, 52.5);
  } else {
    text("Time:" + ((timeM - startTimeM) - resetTimeM), textX2 + 300, 52.5);
  }
  if ((timeS - startTimeS - resetTimeS) % 60 < 10) {
    text(":0" + (timeS - startTimeS - resetTimeS) % 60, textX2 + 415, 52.5);
  } else {
    text(":" + (timeS - startTimeS - resetTimeS) % 60, textX2 + 415, 52.5);
  }

  //welcome screen
  if (screen == 0) {
    //resets the board, moves, time, and spawns in 2 pieces and moves text onto the screen  
    reset();
    textX = 400;

    //if the user clicks on the 2048, the game starts and the time on screen 0 stops being counted
    if (mouseX >= 140 && mouseX <= 665 && mouseY >= 115 && mouseY <= 283 && mousePressed == true) {
      screen++;
      startT = false;
    }
    //actual game screen
  } else if (screen == 1) {
    //moves some text outside of the canvas and other onto the canvas    
    textX = 3000;
    textX2 = 15;
    textWinX = 3000;
    winLoseCoord = 3000;
    //score is the sum of all blocks (different from the original game)
    score = grid[0][0] + grid[0][1] + grid[0][2] + grid[0][3] + grid[1][0] + grid[1][1] + grid[1][2] + grid[1][3] + grid[2][0] 
      + grid[2][1] + grid[2][2] +  grid[2][3] + grid[3][0] + grid[3][1] + grid[3][2] + grid[3][3]; 

    //draws the board
    stroke(146, 135, 125);
    strokeWeight(10);
    fill(0);
    rect(100, 135, 600, 600, 7);

    //if user clicks on the 2048 icon, the game restarts
    if (mouseX >= 17 && mouseX <= 290 && mouseY >= 15 && mouseY <= 115 && mousePressed == true && mouseReleased == true) {
      reset1();
      mouseReleased = false;
    }

    //finds the move given the key pressed
    if (keyPressed == true) {
      if (key == 's') {
        move = "down";
      } else if (key == 'w') {
        move = "up";
      } else if (key == 'a') {
        move = "left";
      } else if (key == 'd') {
        move = "right";
        //to win on next move
      } else if (key == '2') { 
        grid[0][0] = 1024;
        grid[0][1] = 1024;
        //to lose on next move
      } else if (key == 'l') { 
        grid[0][0] = 2;
        grid[0][1] = 4;
        grid[0][2] = 8;
        grid[0][3] = 16;

        grid[1][0] = 4;
        grid[1][1] = 8;
        grid[1][2] = 16;
        grid[1][3] = 32;

        grid[2][0] = 8;
        grid[2][1] = 16;
        grid[2][2] = 32;
        grid[2][3] = 64;

        grid[3][0] = 0;
        grid[3][1] = 16;
        grid[3][2] = 32;
        grid[3][3] = 64;

        //if a non-valid key for move is pressed, the board doesn't change
      } else if (key != 'w' || key != 'a' || key != 's' || key != 'd') { 
        move = null;
      }
      //same as above, but for arrow keys instead of 'w''a''s''d'
      if (key == CODED) {
        if (keyCode == DOWN) {
          move = "down";
        } else if (keyCode == UP) {
          move = "up";
        } else if (keyCode == LEFT) {
          move = "left";
        } else if (keyCode == RIGHT) {
          move = "right";
        } else {
          move = null;
        }
      }
    }

    //drawing the blocks with text (functions with input parameters)
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
        drawRect(100 + 150 * col, 135 + 150 * row, 150, 150, row, col);

//The first two input parameters are the x and y coordinates (respectively), and the second two are the row and column values the for loops are at
        if (grid[row][col] > 0) { //only calls if the value of the block is greater than 0
          drawRectText(175 + 150 * col, 225 + 150 * row, row, col);
        }
      }
    }

    //goes to win screen if the user gets 2048 (checkWin function called in keyReleased function)
    if (win == true) {
      screen++;
    }

    //goes to lose screen if user cannot make another move (checkLose function also called in keyReleased function)    
    if (lose == true) {
      screen = 3;
    }

    //win screen
  } else if (screen == 2) {
    //moves text out of the canvas and other text onto the canvas
    winLoseCoord = -1;
    textWinX = width/2;

    //prints the board (a move cannot be made)
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
        drawRect(100 + 150 * col, 135 + 150 * row, 150, 150, row, col);  
        if (grid[row][col] > 0) {
          drawRectText(175 + 150 * col, 225 + 150 * row, row, col);
        }
      }
    }


    //win text
    fill(211, 211, 211, 200);
    noStroke();
    strokeWeight(1);
    rect(winLoseCoord, winLoseCoord, 802, 802);

    textFont(font2);
    textAlign(CENTER);
    fill(0);
    textSize(55);
    text("Congratulations, you WIN!!!", textWinX, 175);
    textSize(30);
    //displays the score, number of moves, and time
    text("Score: " + score, textWinX, 300);
    text("Number of Moves: " + moves, textWinX, 350);
    if (timeM - startTimeM - resetTimeM < 10) {
      text("Time:0" + ((timeM - startTimeM) - resetTimeM), textWinX, 400);
    } else {
      text("Time:" + ((timeM - startTimeM) - resetTimeM), textWinX, 400);
    }
    if ((timeS - startTimeS - resetTimeS) % 60 < 10) {
      text(":0" + (timeS - startTimeS - resetTimeS) % 60, textWinX + 83, 400);
    } else {
      text(":" + (timeS - startTimeS - resetTimeS) % 60, textWinX + 83, 400);
    }
    text("Click to restart or press the space bar to continue.", textWinX, 450);

    //continue without the ability to win again (to try to get more than 2048)
    if (keyPressed) {
      if (key == ' ') {
        screen = 1;
        win = false;
        cont = true;
      }
    }

    //lose screen
  } else if (screen == 3) {
    winLoseCoord = -1;
    textWinX = width/2;

    //prints the board (a move cannot be made) 
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
        drawRect(100 + 150 * col, 135 + 150 * row, 150, 150, row, col);

        if (grid[row][col] > 0) {
          drawRectText(175 + 150 * col, 225 + 150 * row, row, col);
        }
      }
    }


    //lose text
    fill(211, 211, 211, 200);
    noStroke();
    strokeWeight(1);
    rect(winLoseCoord, winLoseCoord, 802, 802);

    textFont(font2);
    textAlign(CENTER);
    fill(0);
    textSize(55);
    text("Oh no, you LOSE!!!", textWinX, 175);
    textSize(30);
    //displays the score, number of moves, and time
    text("Score: " + score, textWinX, 300);
    text("Number of Moves: " + moves, textWinX, 350);
    if (timeM - startTimeM - resetTimeM < 10) {
      text("Time:0" + ((timeM - startTimeM) - resetTimeM), textWinX, 400);
    } else {
      text("Time:" + ((timeM - startTimeM) - resetTimeM), textWinX, 400);
    }
    if ((timeS - startTimeS - resetTimeS) % 60 < 10) {
      text(":0" + (timeS - startTimeS - resetTimeS) % 60, textWinX + 83, 400);
    } else {
      text(":" + (timeS - startTimeS - resetTimeS) % 60, textWinX + 83, 400);
    }
    text("Click to restart and try again!", textWinX, 450);
  }
}

//initial reset function to reset the board and other variables
void reset() {
  //resets variables and moves text out of the screen
  score = 0;
  moves = 0;
  win = false;
  lose = false;
  winLoseCoord = 802;
  //when reset is clicked, every block on the board is set to 0; allows for the game to restart and start
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      grid[row][col] = 0;
    }
  }
  //spawns in 2 new blocks
  spawn();
  spawn();
  timeS = 0;
  timeM = 0;
}

//copy reset function with the start time to be able to restart from within the game
void reset1() {
  score = 0;
  moves = 0;
  win = false;
  lose = false;
  cont = false;
  winLoseCoord = 802;
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      grid[row][col] = 0;
    }
  }
  spawn();
  spawn();
  timeS = 0;
  timeM = 0;
  resetTimeS = (millis() / 1000) - startTimeS;
  resetTimeM = (resetTimeS) / 60 - startTimeM;
}

//function to draw the blocks
void drawRect(int x, int y, int w, int h, int row, int col) {
  //colors were taken from https://github.com/yangshun/2048-python/commit/b3e20fb61376c84fba34e490de38fc4b6c6f6665 (colors for each block)
  if (grid[row][col] == 0) {
    r = 158;
    g = 148;
    b = 138;
  } else if (grid[row][col] == 2) {
    r = 238;
    g = 228;
    b = 218;
  } else if (grid[row][col] == 4) {
    r = 237;
    g = 224;
    b = 200;
  } else if (grid[row][col] == 8) {
    r = 242;
    g = 177;
    b = 121;
  } else if (grid[row][col] == 16) {
    r = 245;
    g = 149;
    b = 99;
  } else if (grid[row][col] == 32) {
    r = 246;
    g = 124;
    b = 95;
  } else if (grid[row][col] == 64) {
    r = 246;
    g = 94;
    b = 59;
  } else if (grid[row][col] == 128) {
    r = 237;
    g = 207;
    b = 114;
  } else if (grid[row][col] == 256) {
    r = 237;
    g = 204;
    b = 97;
  } else if (grid[row][col] == 512) {
    r = 237;
    g = 200;
    b = 80;
  } else if (grid[row][col] == 1024) {
    r = 237;
    g = 197;
    b = 63;
  } else if (grid[row][col] == 2048) { 
    r = 237;
    g = 194;
    b = 46;
  } else if (grid[row][col] == 4096) {
    r =  119;
    g = 110;
    b = 101;
  } else if (grid[row][col] == 8192) {
    r = 50;
    g = 50;
    b = 50;
  } else if (grid[row][col] == 16384) {
    r = 25;
    g = 25;
    b = 25;
  } else if (grid[row][col] >= 32768) {
    r = 0;
    g = 0;
    b = 0;
  }

  //drawing the blocks from the color found above and input parameters from when the function was called
  fill(r, g, b);
  stroke(146, 135, 125);
  strokeWeight(10);
  rect(x, y, w, h);
}

//function to draw the text on the block
void drawRectText(int x, int y, int row, int col) {
  //text color, also taken from https://github.com/yangshun/2048-python/commit/b3e20fb61376c84fba34e490de38fc4b6c6f6665
  //colors of the text, which is darker for the light blocks (2 and 4) and lighter for the dark blocks (>4)
  if (grid[row][col] == 2 || grid[row][col] == 4) {
    r = 119;
    g = 110;
    b= 101;
  } else {
    r = 249;
    g = 246;
    b = 242;
  }

  //draws the score of each block in the middle of the block
  font1 = loadFont("Verdana-Bold-48.vlw");
  textFont(font1);
  fill(r, g, b);
  textAlign(CENTER);
  textSize(40);
  text(grid[row][col], x, y);
}

//function to spawn a new block
void spawn() {
  //picks a random number between 1 and 10
  float key = round(random(1, 10));
  int newPiece;
  float randC;
  float randR;

  //decides if the new block is a 2 (80%) or a 4 (20%)
  if (key < 9) {
    newPiece = 2;
  } else {
    newPiece = 4;
  }

  //changes the value of a random block that was 0
  while (true) {
    randR = round(random(0, 3));
    randC = round(random(0, 3));
    if (grid[int(randR)][int(randC)] == 0) {
      grid[int(randR)][int(randC)] = newPiece;
      break;
    }
  }
}

//function that is called once when a key is released
void keyReleased() {
  //makes sure it only works on game screen
  if (screen == 1) {
    //moving the blocks given the move from the user and makes sure the board is changed to spawn a new block in    
    if (move == "left") {
      //copies the grid twice, and condenses/combines the row to the left      
      gridCopy();
      squishLeft();
      combineLeft();
      squishLeft();
      gridCopy2();

      //checks the copy of the grid to see if it hasn't changed
      int matchValue = 0;
      for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
          if (gridCopy[row][col] == gridCopy2[row][col]) {
            matchValue ++;
          } else {
            matchValue += 100;
          }
        }
        //if they are the different, spawn a new piece in and add 1 to the move variable. If it is the same, do nothing
      }
      if (matchValue != 16) {
        spawn();
        moves++;
      }
      //repeat for the other moves
    } else if (move == "right") {
      gridCopy();
      squishRight();
      combineRight();
      squishRight();
      gridCopy2();

      int matchValue = 0;
      for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
          if (gridCopy[row][col] == gridCopy2[row][col]) {
            matchValue ++;
          } else {
            matchValue += 100;
          }
        }
      }
      if (matchValue != 16) {
        spawn();
        moves++;
      }
    } else if (move == "down") {
      gridCopy();
      squishDown();
      combineDown();
      squishDown();
      gridCopy2();

      int matchValue = 0;
      for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
          if (gridCopy[row][col] == gridCopy2[row][col]) {
            matchValue ++;
          } else {
            matchValue += 100;
          }
        }
      }
      if (matchValue != 16) {
        spawn();
        moves++;
      }
    } else if (move == "up") {
      gridCopy();
      squishUp();
      combineUp();
      squishUp();
      gridCopy2();

      int matchValue = 0;
      for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
          if (gridCopy[row][col] == gridCopy2[row][col]) {
            matchValue ++;
          } else {
            matchValue += 100;
          }
        }
      }
      if (matchValue != 16) {
        spawn();
        moves++;
      }
    }
    //checks to see if the user wins/loses and if they continue past 2048, only checks if they lose
    if (key == 's' || key == 'w' || key == 'a' || key == 'd' || key == CODED && keyCode == DOWN || keyCode == UP || keyCode == LEFT 
      || keyCode == RIGHT) {
      if (cont == false) {
        checkWin();
        checkLose();
      } else {
        checkLose();
      }
    }
  }
}

//function that runs once when the mouse is released
void mouseReleased() {
  mouseReleased = true;
  //resets the board in a win/lose screen  
  if (screen == 2 || screen == 3) {
    reset1();
    screen = 1;
  }
}

//function to copy the grid 
void gridCopy() {
  for (int row = 0; row < 4; row++) {
    for (int col = 1; col < 4; col++) {
      gridCopy[row][col] = grid[row][col];
    }
  }
}

//function copy the gird again called after the move to check if the board changed
void gridCopy2() {
  for (int row = 0; row < 4; row++) {
    for (int col = 1; col < 4; col++) {
      gridCopy2[row][col] = grid[row][col];
    }
  }
}

//function to move all non-zero blocks to the left for example [0][2][0][4] -> [2][4][0][0]
void squishLeft() { 
  for (int row = 0; row < 4; row++) {
    for (int col = 1; col < 4; col++) {
      int place = col;
      //if the starting block is not equal to 0, move it as far to the left as possible and set the block's value to 0
      if (grid[row][col] != 0) {
        while (place > 0) {
          if (grid[row][place - 1] == 0) {
            place -= 1;
          } else {
            break;
          }
        }
        if (place != col) {
          grid[row][place] = grid[row][col];
          grid[row][col] = 0;
        }
      }
    }
  }
}

void combineLeft() {
  for (int row = 0; row < 4; row ++) {
    for (int col = 0; col < 3; col ++) {
      //if adjacent blocks are the same, combine to the left and set the block on the right to 0
      if (grid[row][col] == grid[row][col + 1]) {
        grid[row][col] *= 2;
        grid[row][col + 1] = 0;
      }
    }
  }
  //cannot move again unless a valid key is pressed
  move = null;
}

//repeat for each direction
void squishRight() { 
  for (int row = 0; row < 4; row++) {
    for (int col = 2; col > -1; col--) {
      int place = col;
      if (grid[row][col] != 0) {
        while (place < 3) {
          if (grid[row][place + 1] == 0) {
            place += 1;
          } else {
            break;
          }
        }
        if (place != col) {
          grid[row][place] = grid[row][col];
          grid[row][col] = 0;
        }
      }
    }
  }
}

void combineRight() {
  for (int row = 0; row < 4; row ++) {
    for (int col = 3; col >0; col --) {
      if (grid[row][col] == grid[row][col - 1]) {
        grid[row][col] *= 2;
        grid[row][col - 1] = 0;
      }
    }
  }
  move = null;
}

void squishDown() { 
  for (int col = 0; col < 4; col++) {
    for (int row = 2; row > -1; row--) {
      int place = row;
      if (grid[row][col] != 0) {
        while (place < 3) {
          if (grid[place + 1][col] == 0) {
            place += 1;
          } else {
            break;
          }
        }
        if (place != row) {
          grid[place][col] = grid[row][col];
          grid[row][col] = 0;
        }
      }
    }
  }
}

void combineDown() {
  for (int col = 0; col < 4; col ++) {
    for (int row = 3; row >0; row --) {
      if (grid[row][col] == grid[row - 1][col]) {
        grid[row][col] *= 2;
        grid[row - 1][col] = 0;
      }
    }
  }
  move = null;
}

void squishUp() { 
  for (int col = 0; col < 4; col++) {
    for (int row = 1; row < 4; row++) {
      int place = row;
      if (grid[row][col] != 0) {
        while (place > 0) {
          if (grid[place - 1][col] == 0) {
            place -= 1;
          } else {
            break;
          }
        }
        if (place != row) {
          grid[place][col] = grid[row][col];
          grid[row][col] = 0;
        }
      }
    }
  }
}

void combineUp() {
  for (int col = 0; col < 4; col ++) {
    for (int row = 0; row < 3; row ++) {
      if (grid[row][col] == grid[row + 1][col]) {
        grid[row][col] *= 2;
        grid[row + 1][col] = 0;
      }
    }
  }
  move = null;
}

//function to check if the user obtained 2048
void checkWin() {
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      if (grid[row][col] == 2048 && cont == false) {
        win = true;
      }
    }
  }
}

//function to check if the user can no longer make a move
void checkLose() {
  //booleans to see if a move can be made from each block
  boolean live00 = true;
  boolean live01 = true;
  boolean live02 = true;
  boolean live03 = true;

  boolean live10 = true;
  boolean live11 = true;
  boolean live12 = true;
  boolean live13 = true;

  boolean live20 = true;
  boolean live21 = true;
  boolean live22 = true;
  boolean live23 = true;

  boolean live30 = true;
  boolean live31 = true;
  boolean live32 = true;
  boolean live33 = true;

  //*if the adjacent blocks are not equivalent to the block, the block's boolean is set to false
  //first row  
  if (grid[0][0] != grid[0][1] && grid[0][0] != grid[1][0] && grid[0][0] != 0) {
    live00 = false;
  }
  if (grid[0][1] != grid[0][0] && grid[0][1] != grid[0][2] && grid[0][1] != grid[1][1] && grid[0][1] != 0) {
    live01 = false;
  }
  if (grid[0][2] != grid[0][1] && grid[0][2] != grid[0][3] && grid[0][2] != grid[1][2] && grid[0][2] != 0) {
    live02 = false;
  }
  if (grid[0][3] != grid[0][2] && grid[0][3] != grid[1][3] && grid[0][3] != 0) {
    live03 = false;
  }

  //second row
  if (grid[1][0] != grid[1][1] && grid[1][0] != grid[2][0] && grid[1][0] != grid[0][0] && grid[1][0] != 0) {
    live10 = false;
  }
  if (grid[1][1] != grid[1][0] && grid[1][1] != grid[1][2] && grid[1][1] != grid[0][1] && grid[1][1] != grid[2][1] && grid[1][1] != 0) {
    live11 = false;
  }
  if (grid[1][2] != grid[1][1] && grid[1][2] != grid[1][3] && grid[1][2] != grid[0][2] && grid[1][2] != grid[2][2] && grid[1][2] != 0) {
    live12 = false;
  }
  if (grid[1][3] != grid[1][2] && grid[1][3] != grid[2][3] && grid[1][3] != grid[0][3] && grid[1][3] != 0) {
    live13 = false;
  }

  //third row  
  if (grid[2][0] != grid[2][1] && grid[2][0] != grid[3][0] && grid[2][0] != grid[1][0] && grid[2][0] != 0) {
    live20 = false;
  }
  if (grid[2][1] != grid[2][0] && grid[2][1] != grid[2][2] && grid[2][1] != grid[1][1] && grid[2][1] != grid[3][1] && grid[2][1] != 0) {
    live21 = false;
  }
  if (grid[2][2] != grid[2][1] && grid[2][2] != grid[2][3] && grid[2][2] != grid[1][2] && grid[2][2] != grid[3][2] && grid[2][2] != 0) {
    live22 = false;
  }
  if (grid[2][3] != grid[2][2] && grid[2][3] != grid[1][3] && grid[2][3] != grid[3][3] && grid[2][3] != 0) {
    live23 = false;
  }

  //fourth row
  if (grid[3][0] != grid[3][1] && grid[3][0] != grid[2][0] && grid[3][0] != 0) {
    live30 = false;
  }
  if (grid[3][1] != grid[3][0] && grid[3][1] != grid[3][2] && grid[3][1] != grid[2][1] && grid[3][1] != 0) {
    live31 = false;
  }
  if (grid[3][2] != grid[3][1] && grid[3][2] != grid[3][3] && grid[3][2] != grid[2][2] && grid[3][2] != 0) {
    live32 = false;
  }
  if (grid[3][3] != grid[3][2] && grid[3][3] != grid[2][3] && grid[3][3] != 0) {
    live33 = false;
  }

  //if all booleans are false, user loses  
  if (live00 == false && live01 == false && live02 == false && live03 == false && live10 == false && live11 == false && live12 == false
    && live13 == false && live20 == false && live21 == false && live22 == false && live23 == false && live30 == false && live31 == false
    && live32 == false && live33 == false) {
    lose = true;
  }
}
