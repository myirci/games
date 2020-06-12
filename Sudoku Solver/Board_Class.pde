class Board
{
  MBox[] boxes;
  int x;
  int y;
  int bsize;
  int csMBox;
  int csLBox;
  int show_text;
  
  Board(int x1, int y1, int bs)
  {
    x = x1;
    y = y1;
    bsize = bs;
    csMBox = -1;
    csLBox = -1;
    show_text = 0;
        
    int mbs = bsize / 3;
    int index = 0;
    boxes = new MBox[9];
    
    for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
      {
        boxes[index] = new MBox(x + j*mbs, y + i*mbs, mbs);
        index++;
      }
    }
  }
  
  void display()
  {
    for(int i = 0; i < 9; i++)
    {
      boxes[i].display();
    }
    
    strokeWeight(1);
    line(boxes[0].x, boxes[0].y, boxes[0].x + bsize, boxes[0].y);
    line(boxes[3].x, boxes[3].y, boxes[3].x + bsize, boxes[3].y);
    line(boxes[6].x, boxes[6].y, boxes[6].x + bsize, boxes[6].y);
    line(boxes[0].x, boxes[0].y + bsize, boxes[0].x + bsize, boxes[0].y + bsize );
    line(boxes[0].x, boxes[0].y, boxes[0].x, boxes[0].y + bsize);
    line(boxes[1].x, boxes[1].y, boxes[1].x, boxes[1].y + bsize);
    line(boxes[2].x, boxes[2].y, boxes[2].x, boxes[2].y + bsize);
    line(boxes[0].x + bsize, boxes[0].y, boxes[0].x + bsize, boxes[0].y + bsize);
    strokeWeight(0);
    
    if(show_text == 0)  // Default case, user is expected to insert the intial numbers.
    {
      fill(68,2,185);
      textSize(tsize/2);
      text("Insert the intial numbers, then press Enter to solve", width/10, yy1/2);
      textSize(tsize);
      noFill();
    }
    else if(show_text == 1) // Solution is completed and successful.
    {
      textSize(tsize/2);
      fill(68,2,185);
      text("Solution is completed!", width/3, yy1/2);
      textSize(tsize);
      noFill();
    }
    else if(show_text == 2) // Inserted numbers are invalid.
    {
      textSize(tsize/2);
      fill(255, 0, 0);
      text("Invalid initial numbers!", width/3, yy1/2);
      textSize(tsize);
      noFill();
    }
  }
  
  void test(int mx, int my)
  {
    boolean hit = false;
    int r = 0;
    for(int i = 0; i < 9; i++)
    {
      r = boxes[i].test(mx,my);
      if(r != -1)
      {
        csMBox = i;
        csLBox = r;
        hit = true;
      }
    }
    
    if(!hit)
    {
      csMBox = -1;
      csLBox = -1;
    }
  }
}
