Board myBoard;
Solver sobj;
PFont font;
int xx1, yy1, ss1;
float tsize;
color color1;
color color2; 

void setup()
{
  size(650, 650);
  frameRate(20);
  color1 = color(216,195,111);
  color2 = color(203,26,216);
  smooth();
  xx1 = yy1 = 100;
  ss1 = 450;
  tsize = ss1/9 - ss1/90;
  myBoard = new Board(xx1, yy1, ss1);
  sobj = new Solver();
  // font = loadFont("ComicSansMS-48.vlw");
  // textFont(font);
  textSize(tsize);
  init_for_debug_3();
}

void draw()
{
  background(255);
  textSize(tsize/2);
  fill(2,245,56,85);
  text("Designed & Coded by Murat Yirci", 0.45*width, 0.92*height);
  text("19.10.2009", 0.63*width, 0.96*height);
  noFill();
  textSize(tsize); 
  myBoard.display(); 
}

void mousePressed()
{
  if(mouseButton == LEFT)
  {
    myBoard.test(mouseX,mouseY);
  }
}

void keyPressed()
{
  int mbox = myBoard.csMBox;
  int lbox = myBoard.csLBox;

  if(mbox >= 0 && mbox <= 8 && lbox >= 0 && lbox <= 8)
  {
    if(key == CODED)
    {
      if(keyCode == UP)
      {
        if((mbox == 0 || mbox == 1 || mbox == 2) && (lbox == 0 || lbox == 1 || lbox == 2))
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox+6].boxes[lbox+6].selected = true;
          myBoard.csMBox += 6;
          myBoard.csLBox += 6;
        }
        else if(lbox == 0 || lbox == 1 || lbox == 2)
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox-3].boxes[lbox+6].selected = true;
          myBoard.csMBox -= 3;
          myBoard.csLBox += 6;
        }
        else
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox].boxes[lbox-3].selected = true;
          myBoard.csLBox -= 3;
        }
      }
      else if(keyCode == DOWN)
      {
        if((mbox == 6 || mbox == 7 || mbox == 8) && (lbox == 6 || lbox == 7 || lbox == 8))
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox-6].boxes[lbox-6].selected = true;
          myBoard.csMBox -= 6;
          myBoard.csLBox -= 6;
        }
        else if(lbox == 6 || lbox == 7 || lbox == 8)
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox+3].boxes[lbox-6].selected = true;
          myBoard.csMBox += 3;
          myBoard.csLBox -= 6;
        }
        else
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox].boxes[lbox+3].selected = true;
          myBoard.csLBox += 3;
        }
      }
      else if(keyCode == LEFT)
      {
        if((mbox == 0 || mbox == 3 || mbox == 6) && (lbox == 0 || lbox == 3 || lbox == 6))
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox+2].boxes[lbox+2].selected = true;
          myBoard.csMBox += 2;
          myBoard.csLBox += 2;
        }
        else if(lbox == 0 || lbox == 3 || lbox == 6)
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox-1].boxes[lbox+2].selected = true;
          myBoard.csMBox -= 1;
          myBoard.csLBox += 2;
        }
        else
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox].boxes[lbox-1].selected = true;
          myBoard.csLBox -= 1;
        }
      }
      else if(keyCode == RIGHT)
      {
        if((mbox == 2 || mbox == 5 || mbox == 8) && (lbox == 2 || lbox == 5 || lbox == 8))
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox-2].boxes[lbox-2].selected = true;
          myBoard.csMBox -= 2;
          myBoard.csLBox -= 2;
        }
        else if(lbox == 2 || lbox == 5 || lbox == 8)
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox+1].boxes[lbox-2].selected = true;
          myBoard.csMBox += 1;
          myBoard.csLBox -= 2;
        }
        else
        {
          myBoard.boxes[mbox].boxes[lbox].selected = false;
          myBoard.boxes[mbox].boxes[lbox+1].selected = true;
          myBoard.csLBox += 1;
        }
      }
    }
    else if(key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9')
    {
      myBoard.boxes[mbox].boxes[lbox].num = key - 48;
      sobj.boxArray[mbox][lbox] = key - 48;
         
    }
    else if(key == DELETE || key == BACKSPACE)
    {
      myBoard.boxes[mbox].boxes[lbox].num = -1;
      sobj.boxArray[mbox][lbox] = -1;
    }
  }
  if(key == ENTER || key == RETURN)
  {
    int res = 0;
    res = sobj.solve();
    if(res == 0)  // Solution is successful
    {
      myBoard.show_text = 1; 
    }
    else if(res == 1) // Invalid board
    {
      myBoard.show_text = 2;
    }
  }
}


void init_for_debug_1()
{
  myBoard.boxes[0].boxes[5].num = 7;
  sobj.boxArray[0][5] = 7;
  myBoard.boxes[0].boxes[8].num = 9;
  sobj.boxArray[0][8] = 9;
  
  myBoard.boxes[1].boxes[2].num = 5;
  sobj.boxArray[1][2] = 5;
  myBoard.boxes[1].boxes[3].num = 2;
  sobj.boxArray[1][3] = 2;
  myBoard.boxes[1].boxes[5].num = 8;
  sobj.boxArray[1][5] = 8;
  
  myBoard.boxes[2].boxes[3].num = 6;
  sobj.boxArray[2][3] = 6;
  myBoard.boxes[2].boxes[5].num = 9;
  sobj.boxArray[2][5] = 9;
  myBoard.boxes[2].boxes[7].num = 8;
  sobj.boxArray[2][7] = 8;
  myBoard.boxes[2].boxes[8].num = 7;
  sobj.boxArray[2][8] = 7;
  
  myBoard.boxes[3].boxes[3].num = 8;
  sobj.boxArray[3][3] = 8;
  myBoard.boxes[3].boxes[5].num = 1;
  sobj.boxArray[3][5] = 1;
  myBoard.boxes[3].boxes[6].num = 2;
  sobj.boxArray[3][6] = 2;
  
  myBoard.boxes[4].boxes[1].num = 2;
  sobj.boxArray[4][1] = 2;
  myBoard.boxes[4].boxes[2].num = 4;
  sobj.boxArray[4][2] = 4;
  myBoard.boxes[4].boxes[3].num = 7;
  sobj.boxArray[4][3] = 7;
  myBoard.boxes[4].boxes[5].num = 9;
  sobj.boxArray[4][5] = 9;
  myBoard.boxes[4].boxes[6].num = 8;
  sobj.boxArray[4][6] = 8;
  myBoard.boxes[4].boxes[7].num = 5;
  sobj.boxArray[4][7] = 5;
  
  myBoard.boxes[5].boxes[2].num = 8;
  sobj.boxArray[5][2] = 8;
  myBoard.boxes[5].boxes[3].num = 4;
  sobj.boxArray[5][3] = 4;
  myBoard.boxes[5].boxes[5].num = 2;
  sobj.boxArray[5][5] = 2;
  
  myBoard.boxes[6].boxes[0].num = 7;
  sobj.boxArray[6][0] = 7;
  myBoard.boxes[6].boxes[1].num = 6;
  sobj.boxArray[6][1] = 6;
  myBoard.boxes[6].boxes[3].num = 5;
  sobj.boxArray[6][3] = 5;
  myBoard.boxes[6].boxes[5].num = 8;
  sobj.boxArray[6][5] = 8;
  
  myBoard.boxes[7].boxes[3].num = 4;
  sobj.boxArray[7][3] = 4;
  myBoard.boxes[7].boxes[5].num = 6;
  sobj.boxArray[7][5] = 6;
  myBoard.boxes[7].boxes[6].num = 5;
  sobj.boxArray[7][6] = 5;
  
  myBoard.boxes[8].boxes[0].num = 8;
  sobj.boxArray[8][0] = 8;
  myBoard.boxes[8].boxes[3].num = 2;
  sobj.boxArray[8][3] = 2;
}

void init_for_debug_2()
{
  myBoard.boxes[0].boxes[0].num = 3;
  sobj.boxArray[0][0] = 3;
  myBoard.boxes[0].boxes[2].num = 2;
  sobj.boxArray[0][2] = 2;
  myBoard.boxes[0].boxes[4].num = 6;
  sobj.boxArray[0][4] = 6;
  myBoard.boxes[0].boxes[7].num = 7;
  sobj.boxArray[0][7] = 7;
  
  myBoard.boxes[1].boxes[2].num = 5;
  sobj.boxArray[1][2] = 5;
  myBoard.boxes[1].boxes[3].num = 1;
  sobj.boxArray[1][3] = 1;
  myBoard.boxes[1].boxes[6].num = 2;
  sobj.boxArray[1][6] = 2;
  
  myBoard.boxes[2].boxes[0].num = 4;
  sobj.boxArray[2][0] = 4;
  myBoard.boxes[2].boxes[3].num = 8;
  sobj.boxArray[2][3] = 8;
  myBoard.boxes[2].boxes[6].num = 6;
  sobj.boxArray[2][6] = 6;
  
  myBoard.boxes[3].boxes[0].num = 9;
  sobj.boxArray[3][0] = 9;
  myBoard.boxes[3].boxes[3].num = 5;
  sobj.boxArray[3][3] = 5;
  myBoard.boxes[3].boxes[4].num = 1;
  sobj.boxArray[3][4] = 1;
  myBoard.boxes[3].boxes[6].num = 2;
  sobj.boxArray[3][6] = 2;
  
  myBoard.boxes[4].boxes[0].num = 6;
  sobj.boxArray[4][0] = 6;
  myBoard.boxes[4].boxes[1].num = 3;
  sobj.boxArray[4][1] = 3;
  myBoard.boxes[4].boxes[7].num = 4;
  sobj.boxArray[4][7] = 4;
  myBoard.boxes[4].boxes[8].num = 1;
  sobj.boxArray[4][8] = 1;
  
  myBoard.boxes[5].boxes[2].num = 1;
  sobj.boxArray[5][2] = 1;
  myBoard.boxes[5].boxes[4].num = 3;
  sobj.boxArray[5][4] = 3;
  myBoard.boxes[5].boxes[5].num = 4;
  sobj.boxArray[5][5] = 4;
  myBoard.boxes[5].boxes[8].num = 9;
  sobj.boxArray[5][8] = 9;
  
  myBoard.boxes[6].boxes[2].num = 3;
  sobj.boxArray[6][2] = 3;
  myBoard.boxes[6].boxes[5].num = 4;
  sobj.boxArray[6][5] = 4;
  myBoard.boxes[6].boxes[8].num = 1;
  sobj.boxArray[6][8] = 1;
  
  myBoard.boxes[7].boxes[2].num = 8;
  sobj.boxArray[7][2] = 8;
  myBoard.boxes[7].boxes[5].num = 9;
  sobj.boxArray[7][5] = 9;
  myBoard.boxes[7].boxes[6].num = 7;
  sobj.boxArray[7][6] = 7;
  
  myBoard.boxes[8].boxes[1].num = 5;
  sobj.boxArray[8][1] = 5;
  myBoard.boxes[8].boxes[4].num = 7;
  sobj.boxArray[8][4] = 7;
  myBoard.boxes[8].boxes[6].num = 3;
  sobj.boxArray[8][6] = 3;
  myBoard.boxes[8].boxes[8].num = 2;
  sobj.boxArray[8][8] = 2;   
}

void init_for_debug_3()
{
  myBoard.boxes[0].boxes[3].num = 7;
  sobj.boxArray[0][3] = 7;
  myBoard.boxes[0].boxes[6].num = 2;
  sobj.boxArray[0][6] = 2;
  myBoard.boxes[0].boxes[8].num = 5;
  sobj.boxArray[0][8] = 5;
  
  myBoard.boxes[1].boxes[3].num = 1;
  sobj.boxArray[1][3] = 1;
  myBoard.boxes[1].boxes[4].num = 5;
  sobj.boxArray[1][4] = 5;
  myBoard.boxes[1].boxes[5].num = 4;
  sobj.boxArray[1][5] = 4;
  myBoard.boxes[1].boxes[6].num = 9;
  sobj.boxArray[1][6] = 9;
  myBoard.boxes[1].boxes[8].num = 8;
  sobj.boxArray[1][8] = 8;
  
  myBoard.boxes[2].boxes[5].num = 8;
  sobj.boxArray[2][5] = 8;
  myBoard.boxes[2].boxes[6].num = 1;
  sobj.boxArray[2][6] = 1;
  myBoard.boxes[2].boxes[8].num = 6;
  sobj.boxArray[2][8] = 6;
  
  myBoard.boxes[3].boxes[2].num = 6;
  sobj.boxArray[3][2] = 6;
  myBoard.boxes[3].boxes[4].num = 3;
  sobj.boxArray[3][4] = 3;
  myBoard.boxes[3].boxes[8].num = 7;
  sobj.boxArray[3][8] = 7;
  
  myBoard.boxes[4].boxes[0].num = 7;
  sobj.boxArray[4][0] = 7;
  myBoard.boxes[4].boxes[2].num = 3;
  sobj.boxArray[4][2] = 3;
  myBoard.boxes[4].boxes[6].num = 2;
  sobj.boxArray[4][6] = 2;
  myBoard.boxes[4].boxes[8].num = 9;
  sobj.boxArray[4][8] = 9;
  
  myBoard.boxes[5].boxes[0].num = 4;
  sobj.boxArray[5][0] = 4;
  myBoard.boxes[5].boxes[4].num = 2;
  sobj.boxArray[5][4] = 2;
  myBoard.boxes[5].boxes[6].num = 6;
  sobj.boxArray[5][6] = 6;
  
  myBoard.boxes[6].boxes[0].num = 8;
  sobj.boxArray[6][0] = 8;
  myBoard.boxes[6].boxes[2].num = 3;
  sobj.boxArray[6][2] = 3;
  myBoard.boxes[6].boxes[3].num = 5;
  sobj.boxArray[6][3] = 5;
  
  myBoard.boxes[7].boxes[0].num = 4;
  sobj.boxArray[7][0] = 4;
  myBoard.boxes[7].boxes[2].num = 2;
  sobj.boxArray[7][2] = 2;
  myBoard.boxes[7].boxes[3].num = 8;
  sobj.boxArray[7][3] = 8;
  myBoard.boxes[7].boxes[4].num = 7;
  sobj.boxArray[7][4] = 7;
  myBoard.boxes[7].boxes[5].num = 6;
  sobj.boxArray[7][5] = 6;
  
  myBoard.boxes[8].boxes[0].num = 9;
  sobj.boxArray[8][0] = 9;
  myBoard.boxes[8].boxes[2].num = 5;
  sobj.boxArray[8][2] = 5;
  myBoard.boxes[8].boxes[5].num = 2;
  sobj.boxArray[8][5] = 2;
}

void init_for_debug_4()
{
  // very hard:
  myBoard.boxes[0].boxes[3].num = 8;
  sobj.boxArray[0][3] = 8;
  myBoard.boxes[0].boxes[8].num = 7;
  sobj.boxArray[0][8] = 7;
  
  myBoard.boxes[1].boxes[2].num = 4;
  sobj.boxArray[1][2] = 4;
  myBoard.boxes[1].boxes[3].num = 2;
  sobj.boxArray[1][3] = 2;
  myBoard.boxes[1].boxes[4].num = 1;
  sobj.boxArray[1][4] = 1;
  myBoard.boxes[1].boxes[7].num = 9;
  sobj.boxArray[1][7] = 9;
  
  myBoard.boxes[2].boxes[1].num = 7;
  sobj.boxArray[2][1] = 7;
  myBoard.boxes[2].boxes[2].num = 1;
  sobj.boxArray[2][2] = 1;
  myBoard.boxes[2].boxes[6].num = 3;
  sobj.boxArray[2][6] = 3;
  
  myBoard.boxes[3].boxes[3].num = 2;
  sobj.boxArray[3][3] = 2;
  myBoard.boxes[3].boxes[6].num = 6;
  sobj.boxArray[3][6] = 6;
  myBoard.boxes[3].boxes[7].num = 5;
  sobj.boxArray[3][7] = 5;
  myBoard.boxes[3].boxes[8].num = 9;
  sobj.boxArray[3][8] = 9;
  
  myBoard.boxes[5].boxes[0].num = 4;
  sobj.boxArray[5][0] = 4;
  myBoard.boxes[5].boxes[1].num = 2;
  sobj.boxArray[5][1] = 2;
  myBoard.boxes[5].boxes[2].num = 6;
  sobj.boxArray[5][2] = 6;
  myBoard.boxes[5].boxes[5].num = 7;
  sobj.boxArray[5][5] = 7;
  
  myBoard.boxes[6].boxes[2].num = 5;
  sobj.boxArray[6][2] = 5;
  myBoard.boxes[6].boxes[6].num = 4;
  sobj.boxArray[6][6] = 4;
  myBoard.boxes[6].boxes[7].num = 1;
  sobj.boxArray[6][7] = 1;
  
  myBoard.boxes[7].boxes[1].num = 6;
  sobj.boxArray[7][1] = 6;
  myBoard.boxes[7].boxes[4].num = 4;
  sobj.boxArray[7][4] = 4;
  myBoard.boxes[7].boxes[5].num = 9;
  sobj.boxArray[7][5] = 9;
  myBoard.boxes[7].boxes[6].num = 3;
  sobj.boxArray[7][6] = 3;
  
  myBoard.boxes[8].boxes[0].num = 1;
  sobj.boxArray[8][0] = 1;
  myBoard.boxes[8].boxes[5].num = 5;
  sobj.boxArray[8][5] = 5;
}