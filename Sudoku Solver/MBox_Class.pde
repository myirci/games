class MBox
{
  LBox[] boxes;
  int x;
  int y;
  int bsize;
  
  MBox(int x1, int y1, int bs)
  {
    x = x1;
    y = y1;
    bsize = bs;
    
    int lbs = (int)(bsize / 3);
    int index = 0;
    boxes = new LBox[9];
           
    for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
      {
         boxes[index] = new LBox(x + j*lbs, y + i*lbs, lbs);
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
  }
  
  int test(int mx, int my)
  {
    int r = -1;
    
    for(int i = 0; i < 9; i++)
    {
      if(boxes[i].test(mx,my))
      {
        r = i;
      }
    }
    
    return r;
  }
  
}
